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

#include "ezregex.h"

const char *__ez_regex_error_message = NULL;
int         __ez_regex_error_offset = 0;

static void clear_substr_list (EZRegex *ezre) {

    if (ezre->substr_list) {
        pcre_free_substring_list (ezre->substr_list);
        ezre->substr_list = NULL;
    }
}

const char* ez_regex_error () {

    ez_return_val_if_fail (__ez_regex_error_message != NULL, NULL);
    
    return __ez_regex_error_message;
}

int ez_regex_error_offset () {
    return __ez_regex_error_offset;
}
   
EZRegex* ez_regex_new_with_options (const char *regex, int options) {

    pcre *re = NULL;
    EZRegex *ezre;

    re = pcre_compile (regex, options, &__ez_regex_error_message, &__ez_regex_error_offset, NULL);

    if (re == NULL) {
        return NULL;
    }
    
    ezre = ez_new0 (EZRegex, 1);
    ezre->substr_count = 0;
    
    ezre->re = re;
    ezre->pe = pcre_study (ezre->re, 0, &__ez_regex_error_message);
    pcre_fullinfo (ezre->re, ezre->pe, PCRE_INFO_CAPTURECOUNT, &ezre->substr_count);
    
    ezre->substr_count++;
    ezre->ovector = ez_new0_ctx (ezre, int, 3 * ezre->substr_count);
    ezre->substr_list = NULL;
    
    return ezre;
}

void ez_regex_free (EZRegex *ezre) {

    clear_substr_list (ezre);

    if (ezre->pe)
        pcre_free (ezre->pe);
        
    pcre_free (ezre->re);
        
    ez_free (ezre);
}

int ez_regex_substrings (EZRegex *ezre) {
    return ezre->substr_count;
}

bool ez_regex_match_with_options (EZRegex *ezre, const char *subject, int len, int options) {

    clear_substr_list (ezre);
    return (pcre_exec (ezre->re,
                       ezre->pe,
                       ezre->subject = subject,
                       ezre->subject_len = (len >= 0) ? len : strlen (subject),
                       0,
                       options,
                       ezre->ovector, 
                       3 * ezre->substr_count) > 0);
}

bool ez_regex_match_again_with_options (EZRegex *ezre, int options) {

    clear_substr_list (ezre);
    return (pcre_exec (ezre->re,
                       ezre->pe,
                       ezre->subject,
                       ezre->subject_len,
                       ezre->ovector[1],
                       options,
                       ezre->ovector, 
                       3 * ezre->substr_count) > 0);
}

char* ez_regex_get_substring (EZRegex *ezre, int index) {

    if (index < 0)
        return (char*) ezre->subject;

    if (ezre->substr_list == NULL)
        pcre_get_substring_list (ezre->subject, ezre->ovector, ezre->substr_count, &ezre->substr_list);
        
    return (char*) ezre->substr_list[index];
}

