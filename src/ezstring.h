/* EZLIB - Library of useful routines for C programming
 *
 * Copyright (C) 2008 Florian Schäfer <florian.schaefer@gmail.com>
 * 
 * This library may contain copyrighted material by:
 *
 * Peter Mattis, Spencer Kimball and Josh MacDonald,
 * David Crawshaw, the GLib Team and others.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef __EZSTRING_H__
#define __EZSTRING_H__

#include <ctype.h>

#include "eztypes.h"
#include "ezmem.h"

EZ_BEGIN_DECLS

typedef struct {
    char  *str;
    size_t len;
} EZString;

extern EZString* ez_string_new (const char* init);
extern EZString* ez_string_sized_new (size_t dfl_size);
extern EZString* ez_string_append (EZString *string, const char *val);
extern EZString* ez_string_append_c (EZString *string, const char val);
extern EZString* ez_string_prepend (EZString *string, const char *val);
extern EZString* ez_string_prepend_c (EZString *string, const char val);
extern EZString* ez_string_reverse (EZString *string);
extern EZString* ez_string_up (EZString *string);
extern EZString* ez_string_down (EZString *string);
extern EZString* ez_string_overwrite (EZString *string, size_t pos, const char *val);
extern EZString* ez_string_erase (EZString *string, size_t pos, size_t len);
extern EZString* ez_string_printf (const char *format, ...);
extern EZString* ez_string_append_printf (EZString *string, const char *format, ...);
extern EZString* ez_string_prepend_printf (EZString *string, const char *format, ...);
extern EZString* ez_string_truncate (EZString *string, size_t len);
extern EZString* ez_string_dup (const EZString *string);
extern bool ez_string_equal (const EZString *v, const EZString *v2);
extern unsigned int ez_string_hash (const EZString *string);
extern char* ez_string_free (EZString *string, bool free_segment);

EZ_END_DECLS

#endif /* __EZSTRING_H__ */
