/* Beef - Flexible Brainfuck interpreter
 * Copyright (C) 2005-2020  Andrea Bolognani <eof@kiyuko.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Homepage: https://kiyuko.org/software/beef
 */

#include <glib-object.h>
#include <cattle/cattle.h>
#include "compat.h"
#include "options.h"

/**
 * option_values_new:
 *
 * Allocate a new #OptionValues.
 */
OptionValues*
option_values_new (void)
{
    OptionValues *self;

    self = g_new0 (OptionValues, 1);

    self->configuration = cattle_configuration_new ();

    return self;
}

/**
 * option_values_free:
 *
 * Free an existing #OptionValues.
 */
void
option_values_free (OptionValues *self)
{
    g_object_unref (self->configuration);
    g_free (self->program);
    g_free (self->program_filename);
    g_free (self->output_filename);
    g_free (self->input_filename);
    g_free (self);
}

/**
 * parse_store:
 *
 * Parse the argument of the --store option.
 */
static gboolean
parse_store (const gchar  *option_name,
             const gchar  *value,
             gpointer      data,
             GError      **error)
{
    CattleConfiguration *configuration;
    OptionValues        *option_values;

    option_values = (OptionValues*) data;
    configuration = option_values->configuration;

    if (g_utf8_collate (value, "zero") == 0)
    {
        cattle_configuration_set_end_of_input_action (configuration,
                                                      CATTLE_END_OF_INPUT_ACTION_STORE_ZERO);
    }
    else if (g_utf8_collate (value, "eof") == 0)
    {
        cattle_configuration_set_end_of_input_action (configuration,
                                                      CATTLE_END_OF_INPUT_ACTION_STORE_EOF);
    }
    else if (g_utf8_collate (value, "same") == 0)
    {
        cattle_configuration_set_end_of_input_action (configuration,
                                                      CATTLE_END_OF_INPUT_ACTION_DO_NOTHING);
    }
    else
    {
        g_set_error (error,
                     G_OPTION_ERROR,
                     G_OPTION_ERROR_FAILED,
                     "Invalid argument %s for %s",
                     value,
                     option_name);

        return FALSE;
    }

    return TRUE;
}

/**
 * parse_debugging:
 *
 * Parse the argument of the --enable-debugging option.
 */
static gboolean
parse_debugging (const gchar  *option_name G_GNUC_UNUSED,
                 const gchar  *value G_GNUC_UNUSED,
                 gpointer      data,
                 GError      **error G_GNUC_UNUSED)
{
    CattleConfiguration *configuration;
    OptionValues        *option_values;

    option_values = (OptionValues*) data;
    configuration = option_values->configuration;

    cattle_configuration_set_debug_is_enabled (configuration,
                                               TRUE);

    return TRUE;
}

/**
 * parse_program:
 *
 * Parse the argument for the --program option.
 */
static gboolean
parse_program (const gchar  *option_name G_GNUC_UNUSED,
               const gchar  *value,
               gpointer      data,
               GError      **error G_GNUC_UNUSED)
{
    OptionValues *option_values;

    option_values = (OptionValues*) data;

    if (option_values->program_filename)
    {
        g_set_error (error,
                     G_OPTION_ERROR,
                     G_OPTION_ERROR_FAILED,
                     "Can't use both --program and provide a FILE");

        return FALSE;
    }

    option_values->program = g_strdup (value);

    return TRUE;
}

/**
 * parse_output_filename:
 *
 * Parse the argument for the --output-file option.
 */
static gboolean
parse_output_filename (const gchar  *option_name G_GNUC_UNUSED,
                       const gchar  *value,
                       gpointer      data,
                       GError      **error G_GNUC_UNUSED)
{
    OptionValues *option_values;

    option_values = (OptionValues*) data;

    if (g_utf8_collate (value, "-") == 0)
    {
        option_values->output_filename = NULL;
    }
    else
    {
        option_values->output_filename = g_strdup (value);
    }

    return TRUE;
}

/**
 * parse_input_filename:
 *
 * Parse the argument for the --input-file option.
 */
static gboolean
parse_input_filename (const gchar  *option_name G_GNUC_UNUSED,
                      const gchar  *value,
                      gpointer      data,
                      GError      **error G_GNUC_UNUSED)
{
    OptionValues *option_values;

    option_values = (OptionValues*) data;

    if (g_utf8_collate (value, "-") == 0)
    {
        option_values->input_filename = NULL;
    }
    else
    {
        option_values->input_filename = g_strdup (value);
    }

    return TRUE;
}

/**
 * parse_program_filename:
 *
 * Parse the remaining arguments (program filename).
 */
static gboolean
parse_program_filename (const gchar  *option_name G_GNUC_UNUSED,
                        const gchar  *value,
                        gpointer      data,
                        GError      **error)
{
    OptionValues *option_values;

    option_values = (OptionValues*) data;

    if (option_values->program)
    {
        g_set_error (error,
                     G_OPTION_ERROR,
                     G_OPTION_ERROR_FAILED,
                     "Can't use both --program and provide a FILE");

        return FALSE;
    }

    if (option_values->program_filename)
    {
        g_set_error (error,
                     G_OPTION_ERROR,
                     G_OPTION_ERROR_FAILED,
                     "Only one program can be executed at a time");

        return FALSE;
    }

    if (g_utf8_collate (value, "-") == 0)
    {
        g_set_error (error,
                     G_OPTION_ERROR,
                     G_OPTION_ERROR_FAILED,
                     "Reading the program from stdin is not supported");

        return FALSE;
    }
    else
    {
        option_values->program_filename = g_strdup (value);
    }

    return TRUE;
}

/**
 * option_entries:
 *
 * Commandline options definition.
 */
static GOptionEntry option_entries[] =
{
    {
        "program",
        'p',
        0,
        G_OPTION_ARG_CALLBACK,
        parse_program,
        "Execute PROGRAM",
        "PROGRAM"
    },
    {
        "store",
        's',
        0,
        G_OPTION_ARG_CALLBACK,
        parse_store,
        "Choose what to store when the end of input is reached",
        "zero|eof|same"
    },
    {
        "enable-debugging",
        'd',
        G_OPTION_FLAG_NO_ARG,
        G_OPTION_ARG_CALLBACK,
        parse_debugging,
        "Enable debugging support",
        NULL
    },
    {
        "output-file",
        'o',
        G_OPTION_FLAG_FILENAME,
        G_OPTION_ARG_CALLBACK,
        parse_output_filename,
        "Write program's output to FILE",
        "FILE"
    },
    {
        "input-file",
        'i',
        G_OPTION_FLAG_FILENAME,
        G_OPTION_ARG_CALLBACK,
        parse_input_filename,
        "Read program's input from FILE",
        "FILE"
    },
    {
        G_OPTION_REMAINING,
        0,
        G_OPTION_FLAG_FILENAME,
        G_OPTION_ARG_CALLBACK,
        parse_program_filename,
        "Read program from FILE",
        "FILE"
    },
    { NULL, 0, 0, 0, NULL, NULL, NULL }
};

/**
 * get_option_entries:
 *
 * Obtain a pointer to the option entries.
 */
GOptionEntry*
get_option_entries (void)
{
    return option_entries;
}
