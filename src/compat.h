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

#ifndef __COMPAT_H__
#define __COMPAT_H__

#include <glib.h>
#include <glib-object.h>
#include <cattle/cattle.h>

G_BEGIN_DECLS

#if !CATTLE_CHECK_VERSION(1, 4, 0)
G_DEFINE_AUTOPTR_CLEANUP_FUNC (CattleBuffer, g_object_unref);
G_DEFINE_AUTOPTR_CLEANUP_FUNC (CattleConfiguration, g_object_unref);
G_DEFINE_AUTOPTR_CLEANUP_FUNC (CattleInstruction, g_object_unref);
G_DEFINE_AUTOPTR_CLEANUP_FUNC (CattleInterpreter, g_object_unref);
G_DEFINE_AUTOPTR_CLEANUP_FUNC (CattleProgram, g_object_unref);
G_DEFINE_AUTOPTR_CLEANUP_FUNC (CattleTape, g_object_unref);
#endif

G_END_DECLS

#endif /* __COMPAT_H__ */
