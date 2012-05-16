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

#include "ezstring.h"

EZString* ez_string_new (const char* init) {
    
    if (init == NULL)
        init = "";
        
    EZString *new_string;
    new_string = ez_new0 (EZString, 1);
    
    new_string->str = ez_new0 (char, strlen(init) + 1);
    new_string->len = strlen (init);
    
    strcpy (new_string->str, init);
    
    new_string->str[new_string->len] = 0;
        
    talloc_set_name_const (new_string->str, new_string->str);
    return new_string;
}

EZString* ez_string_sized_new (size_t dfl_size) {

    ez_return_val_if_fail (dfl_size >= 0, NULL);
    
    EZString *new_string;
    new_string = ez_new0 (EZString, 1);
    
    new_string->str = ez_new0 (char, dfl_size + 1);
    new_string->len = dfl_size;

    return new_string;
}

EZString* ez_string_append (EZString *string, const char *val) {
    
    ez_return_val_if_fail (string != NULL, NULL);
    ez_return_val_if_fail (val != NULL, string);
    
    size_t val_len;
    val_len = strlen (val);
    
    string->str = ez_renew (string->str, char, (string->len + val_len) + 1);
    memcpy (string->str + string->len, val, val_len);
    
    string->len += val_len;
    string->str[string->len] = 0;

    talloc_set_name_const (string->str, string->str);
    return string;        
}

EZString* ez_string_append_c (EZString *string, const char val) {
    
    ez_return_val_if_fail (string != NULL, NULL);
    ez_return_val_if_fail (val != '\0', string);
    
    string->str = talloc_realloc_size (NULL, string->str, (string->len + 1) * sizeof (*(string)->str) + sizeof (val));
    memcpy (string->str + string->len, &val, sizeof (val));
        
    string->len++;
    string->str[string->len] = 0;
    
    talloc_set_name_const (string->str, string->str);
    return string;           
}

EZString* ez_string_prepend (EZString *string, const char *val) {
    
    ez_return_val_if_fail (string != NULL, NULL);
    ez_return_val_if_fail (val != NULL, string);

    size_t val_len;
    val_len = strlen (val);
    
    string->str = talloc_realloc_size (NULL, string->str, (string->len + val_len) * sizeof (*(string)->str) + sizeof (*val));
    memmove (string->str + val_len, string->str, string->len);
    memcpy (string->str, val, val_len);
        
    string->len += val_len;
    string->str[string->len] = 0;
    
    talloc_set_name_const (string->str, string->str);
    return string;
}

EZString* ez_string_prepend_c (EZString *string, const char val) {
    
    ez_return_val_if_fail (string != NULL, NULL);
    ez_return_val_if_fail (val != '\0', string);
    
    string->str = talloc_realloc_size (NULL, string->str, (string->len + 1) * sizeof (*(string)->str) + sizeof (val));
    memmove (string->str + sizeof (val), string->str, string->len);
    memcpy (string->str, &val, sizeof (val));
        
    string->len++;
    string->str[string->len] = 0;
    
    talloc_set_name_const (string->str, string->str);
    return string;
}

EZString* ez_string_reverse (EZString *string) {
    
    ez_return_val_if_fail (string != NULL, NULL);
        
    int c;
    int i;
    int j;
   
    for (i = 0, j = string->len-1; i < j; i++, j--) {
        c = string->str[i];
        string->str[i] = string->str[j];
        string->str[j] = c;
    }

    talloc_set_name_const (string->str, string->str);
    return string;
}

EZString* ez_string_up (EZString *string) {

    ez_return_val_if_fail (string != NULL, NULL);

    uchar *s;
    long n;

    n = string->len;
    s = (uchar *) string->str;

    while (n) {
        if (islower (*s))
            *s = toupper (*s);
        s++;
        n--;
    }

    talloc_set_name_const (string->str, string->str);
    return string;
}

EZString* ez_string_down (EZString *string) {

    ez_return_val_if_fail (string != NULL, NULL);

    uchar *s;
    long n;

    n = string->len;
    s = (uchar *) string->str;

    while (n) {
        if (isupper (*s))
            *s = tolower (*s);
        s++;
        n--;
    }

    talloc_set_name_const (string->str, string->str);
    return string;
}

EZString* ez_string_overwrite (EZString *string, size_t pos, const char *val) {
    
    ez_return_val_if_fail (string != NULL, NULL);
    ez_return_val_if_fail (val != NULL, string);
    ez_return_val_if_fail (pos >= 0, string);
    ez_return_val_if_fail (pos < string->len, string);

    size_t len;
    len = string->len - pos;
    
    memcpy (string->str + pos, val, len);
    
    talloc_set_name_const (string->str, string->str);
    return string;
}

EZString* ez_string_erase (EZString *string, size_t pos, size_t len) {

    ez_return_val_if_fail (string != NULL, NULL);
    ez_return_val_if_fail (pos >= 0, string);
    ez_return_val_if_fail (pos < string->len, string);

    if (len < 0)
        len = string->len - pos;
    else {
        ez_return_val_if_fail (pos + len < string->len, string);
        if (pos + len < string->len)
            memmove (string->str + pos, string->str + pos + len, string->len - (pos + len));
    }

    string->len -= len;
    string->str[string->len] = 0;
    
    talloc_set_name_const (string->str, string->str);
    return string;
}

EZString* ez_string_printf (const char *format, ...) {

    ez_return_val_if_fail (format != NULL, NULL);

    va_list args;   
    va_start (args, format);

    EZString *string;
    string = ez_string_sized_new (vsnprintf (NULL, 0, format, args));

    vsnprintf (string->str, string->len + sizeof (*(string)->str), format, args);

    va_end (args);
    
    talloc_set_name_const (string->str, string->str);
    return string;
}

EZString* ez_string_append_printf (EZString *string, const char *format, ...) {

    ez_return_val_if_fail (string != NULL, NULL);
    ez_return_val_if_fail (format != NULL, NULL);

    size_t str_len;

    va_list args;   
    va_start (args, format);

    str_len = vsnprintf (NULL, 0, format, args);

    string->str = talloc_realloc_size (NULL, string->str, string->len + str_len + sizeof (*(string)->str));
    vsnprintf (string->str + string->len, str_len + sizeof (*(string)->str), format, args);
    
    va_end (args);

    string->len += str_len;
    
    talloc_set_name_const (string->str, string->str);
    return string;
}

EZString* ez_string_prepend_printf (EZString *string, const char *format, ...) {

    ez_return_val_if_fail (string != NULL, NULL);
    ez_return_val_if_fail (format != NULL, NULL);

    size_t str_len;
    char save_chr;    

    va_list args;   
    va_start (args, format);

    str_len = vsnprintf (NULL, 0, format, args);

    string->str = talloc_realloc_size (NULL, string->str, string->len + str_len + sizeof (*(string)->str));

    save_chr = *string->str;
    memmove (string->str + str_len, string->str, string->len);
    vsnprintf (string->str, str_len + sizeof (*(string)->str), format, args);
    string->str[str_len] = save_chr;
    
    va_end (args);
    
    string->len += str_len;
    
    talloc_set_name_const (string->str, string->str);
    return string;
}

EZString* ez_string_truncate (EZString *string, size_t len) {

    ez_return_val_if_fail (string != NULL, NULL);

    string->len = MIN (len, string->len);
    string->str[string->len] = 0;

    talloc_set_name_const (string->str, string->str);
    return string;
}

EZString* ez_string_dup (const EZString *string) {

    ez_return_val_if_fail (string != NULL, NULL);

    EZString *new_string;
    new_string = ez_string_new (string->str);

    return new_string;
}

bool ez_string_equal (const EZString *v, const EZString *v2) {
    return (strcmp (v->str, v2->str) == 0);
}

uint ez_string_hash (const EZString *string) {
    
    ez_return_val_if_fail (string != NULL, (uint) NULL);
    
    const char *p = string->str;
    size_t n = string->len;    
    uint h = 0;

    while (n--) {
        h = (h << 5) - h + *p;
        p++;
    }

    return (int) h;
}

char* ez_string_free (EZString *string, bool free_segment) {

    ez_return_val_if_fail (string != NULL, NULL);
    
    char *tmp_str = string->str;
    
    if (free_segment == true) {
        ez_free (string->str);
        tmp_str = NULL;
    }
    
    ez_free (string);
    
    return tmp_str;
}
