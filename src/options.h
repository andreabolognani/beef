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

#ifndef __OPTIONS_H__
#define __OPTIONS_H__

#include <glib.h>
#include <cattle/cattle.h>

G_BEGIN_DECLS

typedef struct _OptionValues OptionValues;

struct _OptionValues
{
	CattleConfiguration *configuration;
	gchar               *output_filename;
	gchar               *input_filename;
};

GOptionEntry* get_option_entries (void);

G_END_DECLS

#endif /* __OPTIONS_H__ */
