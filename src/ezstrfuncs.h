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
 
#ifndef __EZSTRFUNCS_H__
#define __EZSTRFUNCS_H__

#include <ctype.h>
#include <limits.h>

#include "eztypes.h"
#include "ezmacros.h"
#include "ezmem.h"

#include "ezstack.h"

EZ_BEGIN_DECLS

#define ez_str_equal(val, val2) \
    (ez_strcmp0 (val, val2) == 0)

#define ez_strdup_ctx \
    talloc_strdup

#define ez_strndup_ctx \
    talloc_strndup

#define ez_strdup(str) \
    talloc_strdup (NULL, str)

#define ez_strndup(str, size) \
    talloc_strndup (NULL, str, size)

extern char* ez_strchug (char *string);
extern char* ez_strchomp (char *string);
extern char* ez_strstrip (char *string);
extern char* ez_strchugc (char *string, char c);
extern char* ez_strchompc (char *string, char c);
extern char* ez_strstripc (char *string, char c);
extern char* ez_stpcpy (char *dest, const char *src);
extern char* ez_strconcat (const char *string1, ...);
extern char** ez_strsplit (const char *string, const char *delimiter, int max_tokens);
extern char* ez_strjoinv (const char *separator, char **str_array);
extern void ez_strfreev (char **str_array);
extern uint ez_strv_length (char **str_array);
extern char* ez_strjoin (const char *separator, ...);
extern bool ez_str_has_suffix (const char *str, const char *suffix);
extern bool ez_str_has_prefix (const char *str, const char *prefix);
extern int ez_strcmp0 (const char *str1, const char *str2);
extern char* ez_strdown (char *string);
extern char* ez_strup (char *string);
extern char* ez_strreverse (char *string);
extern int ez_strcasecmp (const char *s1, const char *s2);
extern int ez_strncasecmp (const char *s1, const char *s2, size_t n);
extern char* ez_strtruncate (char *string, size_t len);
extern char* ez_stroverwrite (char *string, size_t pos, const char *val);
extern char* ez_strerase (char *string, size_t pos, size_t len);
extern char* ez_strprintf (const char *format, ...);
extern char* ez_strreplace (const char *string, const char *needle, const char *replace);

EZ_END_DECLS

#endif /* __EZSTRFUNCS_H__ */
