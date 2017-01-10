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

#ifndef __IO_H__
#define __IO_H__

#include <glib.h>
#include <glib-object.h>
#include <gio/gio.h>
#include <cattle/cattle.h>

G_BEGIN_DECLS

CattleBuffer* load_file_contents        (GFile              *file,
                                         GError            **error);

gboolean      output_handler            (CattleInterpreter  *interpreter,
                                         gint8               output,
                                         gpointer            data,
                                         GError            **error);
gboolean      input_handler             (CattleInterpreter  *interpreter,
                                         gpointer            data,
                                         GError            **error);
gboolean      input_handler_interactive (CattleInterpreter  *interpreter,
                                         gpointer            data,
                                         GError            **error);

G_END_DECLS

#endif /* __IO_H__ */
