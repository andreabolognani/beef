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

/* Remove once readline 7.0, which (correctly) includes
 * the header itself, is common enough */
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>
#include "compat.h"
#include "io.h"

/**
 * INPUT_BUFFER_SIZE:
 *
 * Requested size for each read operation.
 */
#define INPUT_BUFFER_SIZE 1024

/**
 * PROMPT_BUFFER_SIZE:
 *
 * Size of the buffer used to store the prompt.
 */
#define PROMPT_BUFFER_SIZE 256

/**
 * prompt:
 *
 * The last line of output. Must be passed to readline() for line
 * editing to work as expected.
 */
static gchar  *prompt = NULL;
static gulong  prompt_cursor = 0;
static gulong  prompt_length = 0;

static void
prompt_append (gint8 c)
{
    gchar  *temp;

    if (prompt == NULL)
    {
        /* First use.
         * Allocate a small buffer */
        prompt = (gchar *) g_slice_alloc (PROMPT_BUFFER_SIZE);
        prompt_length = PROMPT_BUFFER_SIZE;
    }

    if (prompt_cursor > prompt_length - 2)
    {
        /* The buffer needs to be extended */
        temp = (gchar *) g_slice_alloc (prompt_length + PROMPT_BUFFER_SIZE);

        /* Copy existing data */
        memcpy (temp, prompt, prompt_length * sizeof (gint8));

        if (prompt != NULL)
        {
            g_slice_free1 (prompt_length, prompt);
        }

        prompt = temp;
        prompt_length += PROMPT_BUFFER_SIZE;
    }

    prompt[prompt_cursor] = c;
    prompt[prompt_cursor + 1] = '\0';

    prompt_cursor++;
}

static void
prompt_reset (void)
{
    if (prompt != NULL)
    {
        prompt[0] = '\0';
    }

    prompt_cursor = 0;
}

/**
 * load_file_contents:
 * @file: a #GFile
 * @error: (allow-none): return location for a #GError, or %NULL
 *
 * Load the contents of @file, with good error checking and proper
 * handling of magic bytes.
 *
 * Returns: (transfer full): the contents of @file, or %NULL
 */
CattleBuffer*
load_file_contents (GFile   *file,
                    GError **error)
{
    CattleBuffer     *contents;
    GError           *inner_error;
    g_autofree gchar *buffer;
    gchar            *start;
    gsize             size;
    gboolean          success;

    g_return_val_if_fail (G_IS_FILE (file), NULL);
    g_return_val_if_fail (error == NULL || *error == NULL, NULL);

    /* Load file contents */
    inner_error = NULL;
    success = g_file_load_contents (file,
                                    NULL,
                                    &buffer,
                                    &size,
                                    NULL, /* No etag */
                                    &inner_error);

    if (!success)
    {
        g_propagate_error (error,
                           inner_error);

        return NULL;
    }

    /* Mark the start of the input */
    start = buffer;

    /* Detect and handle magic bytes */
    if (size > 2)
    {
        if (buffer[0] == '#' && buffer[1] == '!')
        {
            /* Look for the first newline */
            while (size > 0 && start[0] != '\n')
            {
                start++;
                size--;
            }

            /* Move past it */
            start++;
            size--;
        }
    }

    contents = cattle_buffer_new (size);
    cattle_buffer_set_contents (contents, (gint8 *) start);

    return contents;
}

/**
 * output_handler:
 *
 * Dump interpreter's output to a #GOutputStream.
 */
gboolean
output_handler (CattleInterpreter  *interpreter G_GNUC_UNUSED,
                gint8               output,
                gpointer            data,
                GError            **error)
{
    GOutputStream *stream;
    GError        *inner_error;

    if (G_IS_OUTPUT_STREAM (data))
    {
        /* Writing to a file: get the stream */
        stream = G_OUTPUT_STREAM (data);

        inner_error = NULL;
        g_output_stream_write (stream,
                               &output,
                               1,
                               NULL,
                               &inner_error);

        if (inner_error != NULL) {

            g_propagate_error (error,
                               inner_error);

            return FALSE;
        }
    }
    else
    {
        /* Write to standard output */
        g_print ("%c", output);
    }

    /* Update the prompt */

    if (output != '\n')
    {
        prompt_append (output);
    }
    else
    {
        prompt_reset ();
    }

    return TRUE;
}

/**
 * input_handler:
 *
 * Read interpreter's input from a #GInputStream.
 */
gboolean
input_handler (CattleInterpreter  *interpreter,
               gpointer            data,
               GError            **error)
{
    g_autoptr (CattleBuffer)  input = NULL;
    GInputStream             *stream;
    GError                   *inner_error;
    gchar                     buffer[INPUT_BUFFER_SIZE];
    gssize                    size;

    stream = G_INPUT_STREAM (data);

    inner_error = NULL;
    size = g_input_stream_read (stream,
                                buffer,
                                INPUT_BUFFER_SIZE,
                                NULL,
                                &inner_error);

    if (inner_error != NULL)
    {
        g_propagate_error (error,
                           inner_error);

        return FALSE;
    }

    /* Copy the input to a CattleBuffer */
    input = cattle_buffer_new (size);
    cattle_buffer_set_contents (input, (gint8 *) buffer);

    /* Feed the interpreter with the new input */
    cattle_interpreter_feed (interpreter, input);

    return TRUE;
}

/**
 * input_handler_interactive:
 *
 * Retrieve input from the user interactively.
 */
gboolean
input_handler_interactive (CattleInterpreter  *interpreter,
                           gpointer            data G_GNUC_UNUSED,
                           GError            **error G_GNUC_UNUSED)
{
    g_autoptr (CattleBuffer)  input = NULL;
    gchar                    *buffer;
    gulong                    size;

    /* Use readline to fetch user input. readline is notified of
     * the fact that it should not handle the prompt itself, as there
     * is actually no prompt, but there could be some program output */
    rl_already_prompted = 1;
    buffer = readline (prompt);

    /* Reset prompt after input, because the cursor is certainly at
     * the beginning of a new line */
    prompt_reset ();

    if (buffer == NULL)
    {
        input = cattle_buffer_new (0);
    }
    else
    {
        /* Size of the input */
        size = strlen (buffer) + 1;

        /* Copy the input, overwriting the trailing null byte
         * with the newline that's been stripped by readline */
        input = cattle_buffer_new (size);
        cattle_buffer_set_contents (input, (gint8 *) buffer);
        cattle_buffer_set_value (input, size - 1, '\n');

        free (buffer);
    }

    /* Feed the interpreter with the new input */
    cattle_interpreter_feed (interpreter, input);

    return TRUE;
}
