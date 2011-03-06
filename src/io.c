/* Beef -- Flexible Brainfuck interpreter
 * Copyright (C) 2005-2011  Andrea Bolognani <eof@kiyuko.org>
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

#include "io.h"

/**
 * load_file_contents:
 * @file: a #GFile
 * @error: (allow-none): return location for a #GError, or %NULL
 *
 * Load the contents of @file, with good error checking and proper
 * handling of magic bytes.
 *
 * Returns: the contents of @file, or %NULL
 */
gchar*
load_file_contents (GFile   *file,
                    GError **error)
{
	GError *inner_error;
	gchar *contents;
	gchar *temp;
	gboolean success;
	gsize len;

	g_return_val_if_fail (G_IS_FILE (file), NULL);
	g_return_val_if_fail (error == NULL || *error == NULL, NULL);

	/* Load file contents */
	inner_error = NULL;
	success = g_file_load_contents (file,
	                                NULL,
	                                &contents,
	                                &len,
	                                NULL, /* No etag */
	                                &inner_error);

	if (!success) {

		g_propagate_error (error,
		                   inner_error);

		return NULL;
	}

	/* Validate the contents as UTF-8 */
	success = g_utf8_validate (contents,
	                           len,
	                           NULL);

	if (!success) {

		g_set_error_literal (error,
		                     G_IO_ERROR,
		                     G_IO_ERROR_FAILED,
		                     "Invalid UTF-8");

		return NULL;
	}

	/* Detect and handle magic bytes */
	if (g_str_has_prefix (contents, "#!")) {

		/* Look for the beginning of the second line */
		temp = g_utf8_strchr (contents,
		                      len,
		                      (gunichar) '\n');
		temp = g_utf8_next_char (temp);

		/* Strip the first line */
		temp = g_strdup_printf ("%s", temp);
		g_free (contents);
		contents = temp;
	}

	return contents;
}
