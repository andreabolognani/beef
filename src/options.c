/* Beef - Flexible Brainfuck interpreter
 * Copyright (C) 2005-2017  Andrea Bolognani <eof@kiyuko.org>
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
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Homepage: http://kiyuko.org/software/beef
 */

#include <glib-object.h>
#include <cattle/cattle.h>
#include "options.h"

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
 * option_entries:
 *
 * Commandline options definition.
 */
static GOptionEntry option_entries[] =
{
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
	{ NULL, '\0', 0, 0, NULL, NULL, NULL }
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
