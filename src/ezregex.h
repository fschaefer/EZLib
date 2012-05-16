/* EZLIB - Library of useful routines for C programming
 * 
 * Copyright (C) 2008 Florian Schäfer <florian.schaefer@gmail.com>
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

#ifndef __EZREGEX_H__
#define __EZREGEX_H__

#include "eztypes.h"
#include "ezmem.h"

#include <pcre.h>

EZ_BEGIN_DECLS

typedef struct _EZRegex EZRegex;

struct _EZRegex {
    pcre        *re;
    pcre_extra  *pe;
    int         *ovector;
    const char  *subject;
    int          subject_len;
    int          substr_count;
    const char **substr_list;
};
    
extern EZRegex* ez_regex_new_with_options (const char *regex, int options);
#define ez_regex_new(regex) \
    ez_regex_new_with_options (regex, 0)

extern void ez_regex_free (EZRegex *ezre);
extern int ez_regex_substrings (EZRegex *ezre);
extern bool ez_regex_match_with_options (EZRegex *ezre, const char *subject, int len, int options);
#define ez_regex_match(ezre, subject) \
    ez_regex_match_with_options (ezre, subject, -1, 0)

extern bool ez_regex_match_again_with_options (EZRegex *ezre, int options);
#define ez_regex_match_again(ezre) \
    ez_regex_match_again_with_options (ezre, 0)

extern char* ez_regex_get_substring (EZRegex *ezre, int index);
extern const char* ez_regex_error ();
extern int ez_regex_error_offset ();

EZ_END_DECLS

#endif /* __EZREGEX_H__ */
