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

#include <glib.h>
#include <glib-object.h>
#include <gio/gio.h>
#include <cattle/cattle.h>
/* Remove once readline 7.0, which (correctly) includes
 * the header itself, is common enough */
#include <stdio.h>
#include <readline/readline.h>
#include <config.h>
#include <unistd.h>
#include "io.h"
#include "options.h"

/**
 * display_error:
 * @context: (allow-none): error context
 * @message: error message
 *
 * Display an error encountered by @program while performing an action
 * in @context (usually a file).
 */
void
display_error (const gchar *context,
               const gchar *message)
{
	if (context != NULL)
	{
		g_printerr ("%s: %s: %s\n", g_get_prgname (),
		                            context,
		                            message);
	}
	else
	{
		g_printerr ("%s: %s\n", g_get_prgname (),
		                        message);
	}
}

/**
 * main:
 *
 * Application entry point.
 */
gint
main (gint    argc,
      gchar **argv)
{
	CattleInterpreter *interpreter;
	CattleProgram     *program;
	CattleBuffer      *buffer;
	GFile             *file;
	GFileOutputStream *output_stream;
	GFileInputStream  *input_stream;
	GOptionContext    *context;
	GOptionGroup      *group;
	GError            *error;
	OptionValues      *option_values;
	gboolean           success;

#if !GLIB_CHECK_VERSION(2, 36, 0)
	g_type_init ();
#endif

	g_set_prgname ("beef");

	/* Set up a configuration group for commanline options */
	option_values = g_new0 (OptionValues, 1);
	option_values->configuration = cattle_configuration_new ();
	context = g_option_context_new ("FILE - Flexible Brainfuck interpreter");
	group = g_option_group_new ("",
	                            "",
	                            "",
	                            option_values,
	                            NULL);
	g_option_group_add_entries (group,
	                            get_option_entries ());
	g_option_context_set_main_group (context, group);

	/* Parse commandline options */
	error = NULL;
	success = g_option_context_parse (context, &argc, &argv, &error);

	if (!success)
	{
		display_error (NULL,
		               error->message);

		g_object_unref (option_values->configuration);
		g_free (option_values->output_filename);
		g_free (option_values->input_filename);
		g_free (option_values);

		return 1;
	}

	/* Make sure a file has been specified on the commandline */
	if (argc != 2)
	{
		g_printerr ("Usage: %s [OPTION...] FILE\n", g_get_prgname ());

		g_object_unref (option_values->configuration);
		g_free (option_values->output_filename);
		g_free (option_values->input_filename);
		g_free (option_values);

		return 1;
	}

	/* Load file contents */
	file = g_file_new_for_commandline_arg (argv[1]);

	error = NULL;
	buffer = load_file_contents (file,
	                             &error);
	g_object_unref (file);

	if (buffer == NULL)
	{
		display_error (argv[1],
		               error->message);

		g_object_unref (option_values->configuration);
		g_free (option_values->output_filename);
		g_free (option_values->input_filename);
		g_free (option_values);

		return 1;
	}

	interpreter = cattle_interpreter_new ();
	program = cattle_interpreter_get_program (interpreter);

	/* Load program */
	error = NULL;
	success = cattle_program_load (program,
	                               buffer,
	                               &error);
	g_object_unref (program);
	g_object_unref (buffer);

	if (!success)
	{
		display_error (argv[1],
		               error->message);

		g_object_unref (interpreter);
		g_object_unref (option_values->configuration);
		g_free (option_values->output_filename);
		g_free (option_values->input_filename);
		g_free (option_values);

		return 1;
	}

	output_stream = NULL;
	input_stream = NULL;

	/* Assign configuration created using commandline options to the
	 * interpreter */
	cattle_interpreter_set_configuration (interpreter,
	                                      option_values->configuration);
	g_object_unref (option_values->configuration);

	/* If output to file was chosen, open the selected output file and
	 * assign a suitable output handler to the interpreter */
	if (option_values->output_filename != NULL)
	{
		file = g_file_new_for_commandline_arg (option_values->output_filename);

		error = NULL;
		output_stream = g_file_replace (file,
		                                NULL,  /* No etag */
		                                FALSE, /* No backups */
		                                G_FILE_CREATE_NONE,
		                                NULL,
		                                &error);
		g_object_unref (file);

		if (error != NULL)
		{
			display_error (option_values->output_filename,
			               error->message);

			g_object_unref (interpreter);
			g_free (option_values->output_filename);
			g_free (option_values->input_filename);
			g_free (option_values);

			return 1;
		}
	}

	/* Set output handler for the interpreter */
	cattle_interpreter_set_output_handler (interpreter,
	                                       output_handler,
	                                       output_stream);

	/* If input from file was chosen, open the selected input file and
	 * assign a suitable input handler to the interpreter */
	if (option_values->input_filename != NULL)
	{
		file = g_file_new_for_commandline_arg (option_values->input_filename);

		error = NULL;
		input_stream = g_file_read (file,
		                            NULL,
		                            &error);
		g_object_unref (file);

		if (error != NULL)
		{
			display_error (option_values->input_filename,
			               error->message);

			g_object_unref (output_stream);
			g_object_unref (interpreter);
			g_free (option_values->output_filename);
			g_free (option_values->input_filename);
			g_free (option_values);

			return 1;
		}

		/* Set input handler for the interpreter */
		cattle_interpreter_set_input_handler (interpreter,
		                                      input_handler,
		                                      input_stream);
	}
	else
	{
		/* Use readline only if standard input is connected to a
		 * terminal; otherwise, eg. when using shell input redirection,
		 * the input is displayed along with the output, which is not nice */
		if (isatty (0))
		{
			/* Initialize readline */
			rl_initialize ();

			/* Disable filename completion on TAB */
			rl_bind_key ('\t', rl_insert);

			/* Use a readline-based interactive input handler */
			cattle_interpreter_set_input_handler (interpreter,
			                                      input_handler_interactive,
			                                      NULL);
		}
	}

	/* Run program */
	error = NULL;
	success = cattle_interpreter_run (interpreter,
	                                  &error);

	if (!success)
	{
		display_error (argv[1],
		               error->message);

		g_object_unref (input_stream);
		g_object_unref (output_stream);
		g_object_unref (interpreter);
		g_free (option_values->output_filename);
		g_free (option_values->input_filename);
		g_free (option_values);

		return 1;
	}

	if (output_stream != NULL)
	{
		/* Close the output file */
		error = NULL;
		g_output_stream_close (G_OUTPUT_STREAM (output_stream),
		                       NULL,
		                       &error);
		g_object_unref (output_stream);

		if (error != NULL)
		{
			display_error (option_values->output_filename,
			               error->message);

			g_object_unref (input_stream);
			g_object_unref (interpreter);
			g_free (option_values->output_filename);
			g_free (option_values->input_filename);
			g_free (option_values);

			return 1;
		}
	}

	if (input_stream != NULL)
	{
		/* Close the input file */
		error = NULL;
		g_input_stream_close (G_INPUT_STREAM (input_stream),
		                      NULL,
		                      &error);
		g_object_unref (input_stream);

		if (error != NULL) {

			display_error (option_values->input_filename,
			               error->message);

			g_object_unref (interpreter);
			g_free (option_values->output_filename);
			g_free (option_values->input_filename);
			g_free (option_values);

			return 1;
		}
	}

	g_object_unref (interpreter);
	g_free (option_values->output_filename);
	g_free (option_values->input_filename);
	g_free (option_values);

	return 0;
}
