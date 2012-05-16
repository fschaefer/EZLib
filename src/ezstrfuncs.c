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

#include "ezstrfuncs.h"

char* ez_strchug (char *string) {

    uchar *start;

    ez_return_val_if_fail (string != NULL, NULL);

    for (start = (uchar*) string; *start && isspace (*start); start++)
    ;;

    memmove (string, start, strlen ((char *) start) + 1);

    talloc_set_name_const (string, string);
    return string;
}

char* ez_strchomp (char *string) {
  
    char *s;

    ez_return_val_if_fail (string != NULL, NULL);

    for (s = string + strlen (string) - 1; s >= string && isspace ((uchar)*s); s--)
        *s = '\0';

    talloc_set_name_const (string, string);
    return string;
}

char* ez_strstrip (char *string) {
    ez_return_val_if_fail (string != NULL, NULL);
        
    ez_strchug (string);
    ez_strchomp (string);
    
    return string;
}

char* ez_strchugc (char *string, char c) {

    uchar *s;

    ez_return_val_if_fail (string != NULL, NULL);

    for (s = (uchar*) string; *s && (uchar)*s == c; s++)
    ;;

    memmove (string, s, strlen ((char *) s) + 1);

    talloc_set_name_const (string, string);
    return string;
}

char* ez_strchompc (char *string, char c) {
  
    char *s;

    ez_return_val_if_fail (string != NULL, NULL);

    for (s = string + strlen (string) - 1; s >= string && (uchar)*s == c; s--)
        *s = '\0';

    talloc_set_name_const (string, string);
    return string;
}

char* ez_strstripc (char *string, char c) {
    ez_return_val_if_fail (string != NULL, NULL);
        
    ez_strchugc (string, c);
    ez_strchompc (string, c);
    
    return string;
}

char* ez_stpcpy (char *dest, const char *src) {
#ifdef HAVE_STPCPY
    ez_return_val_if_fail (dest != NULL, NULL);
    ez_return_val_if_fail (src != NULL, NULL);
    
    return stpcpy (dest, src);
#else
    register char *d = dest;
    register const char *s = src;

    ez_return_val_if_fail (dest != NULL, NULL);
    ez_return_val_if_fail (src != NULL, NULL);
    
    do {
        *d++ = *s;
    } while (*s++ != '\0');

    return d - 1;
#endif
}

char* ez_strconcat (const char *string1, ...) {

    size_t l;     
    va_list args;
    char *s;
    char *concat;
    char *ptr;

    ez_return_val_if_fail (string1 != NULL, NULL);

    l = 1 + strlen (string1);

    va_start (args, string1);
    s = va_arg (args, char*);

    while (s) {
        l += strlen (s);
        s = va_arg (args, char*);
    }
   
    va_end (args);

    concat = ez_new (char, l);

    ptr = concat;

    ptr = ez_stpcpy (ptr, string1);
     
    va_start (args, string1);
    s = va_arg (args, char*);
    
    while (s) {
        ptr = ez_stpcpy (ptr, s);
        s = va_arg (args, char*);
    }
    
    va_end (args);

    talloc_set_name_const (concat, concat);
    return concat;
}

char** ez_strsplit (const char *string, const char *delimiter, int max_tokens) {

    EZStack *string_stack = NULL;
    char **str_array;
    char *tmp_string;
    char *s;
    uint i;
    uint n = 1;

    ez_return_val_if_fail (string != NULL, NULL);
    ez_return_val_if_fail (delimiter != NULL, NULL);

    if (max_tokens < 1)
        max_tokens = INT_MAX;

    s = strstr (string, delimiter);

    if (s) {
    
        uint delimiter_len = strlen (delimiter);
        
        do {
            uint len;
            char *new_string;

            len = s - string;
            new_string = ez_new (char, len + 1);
            strncpy (new_string, string, len);
            new_string[len] = 0;
            ez_stack_push (&string_stack, new_string);
            n++;
            string = s + delimiter_len;
            s = strstr (string, delimiter);
        } while (--max_tokens && s);
    }
    
    if (*string) {
        n++;
        ez_stack_push (&string_stack, ez_strdup (string));
    }

    str_array = ez_new (char*, n);

    i = n - 1;

    str_array[i--] = NULL;
    
    while ((tmp_string = ez_stack_pop (&string_stack)))
        str_array[i--] = tmp_string;

    return str_array;
}

char* ez_strjoinv (const char *separator, char **str_array) {

    char *string;

    ez_return_val_if_fail (str_array != NULL, NULL);

    if (separator == NULL)
        separator = "";

    if (*str_array) {

        uint i, len;
        uint separator_len;

        separator_len = strlen (separator);
        len = 1 + strlen (str_array[0]);
        
        for(i = 1; str_array[i] != NULL; i++)
            len += separator_len + strlen (str_array[i]);

        string = ez_new (char, len);
        *string = 0;
        strcat (string, *str_array);
        
        for (i = 1; str_array[i] != NULL; i++) {
            strcat (string, separator);
            strcat (string, str_array[i]);
        }
    } else {
        string = ez_strdup ("");
    }
    
    return string;
}

void ez_strfreev (char **str_array) {
    
    if (str_array) {
        
        int i;
        for(i = 0; str_array[i] != NULL; i++)
            ez_free(str_array[i]);

        ez_free (str_array);
    }
}

uint ez_strv_length (char **str_array) {

    int length = 0;
    
    ez_return_val_if_fail (str_array != NULL, 0);
    
    for (length = 0; str_array[length] != NULL; length++);
    
    return length;
}

char* ez_strjoin (const char *separator, ...) {

    char *string, *s;
    va_list args;
    uint len;
    uint separator_len;

    if (separator == NULL)
        separator = "";

    separator_len = strlen (separator);

    va_start (args, separator);

    s = va_arg (args, char*);

    if (s) {    
        len = strlen (s);

        s = va_arg (args, char*);
        while (s) {
            len += separator_len + strlen (s);
            s = va_arg (args, char*);
        }
        va_end (args);
      
        string = ez_new (char, len + 1);
        *string = 0;

        va_start (args, separator);

        s = va_arg (args, char*);
        strcat (string, s);

        s = va_arg (args, char*);
        while (s) {
            strcat (string, separator);
            strcat (string, s);
            s = va_arg (args, char*);
        }
    } else {
        string = ez_strdup ("");
    }
    va_end (args);

    return string;
}

bool ez_str_has_suffix (const char *str, const char *suffix) {

    size_t str_len;
    size_t suffix_len;
    
    ez_return_val_if_fail (str != NULL, false);
    ez_return_val_if_fail (suffix != NULL, false);
    
    str_len = strlen (str);
    suffix_len = strlen (suffix);

    if (str_len < suffix_len)
        return false;
        
    return strcmp (str + str_len - suffix_len, suffix) == 0;
}

bool ez_str_has_prefix (const char *str, const char *prefix) {

    size_t str_len;
    size_t prefix_len;

    ez_return_val_if_fail (str != NULL, false);
    ez_return_val_if_fail (prefix != NULL, false);

    str_len = strlen (str);
    prefix_len = strlen (prefix);

    if (str_len < prefix_len)
        return false;
        
    return strncmp (str, prefix, prefix_len) == 0;
}

int ez_strcmp0 (const char *str1, const char *str2) {

    ez_return_val_if_fail (str1 != NULL, -1);
    ez_return_val_if_fail (str2 != NULL, 1);
    
    return strcmp (str1, str2);
};

char* ez_strdown (char *string) {

    register uchar *s;

    ez_return_val_if_fail (string != NULL, NULL);

    s = (uchar *) string;
  
    while (*s) {
        if (isupper (*s)) {
            *s = tolower (*s);
        }
        s++;
    }

    talloc_set_name_const (string, string);
    return (char *) string;
}

char* ez_strup (char *string) {

    register uchar *s;

    ez_return_val_if_fail (string != NULL, NULL);

    s = (uchar *) string;

    while (*s) {
        if (islower (*s)) {
            *s = toupper (*s);
        }
        s++;
    }

    talloc_set_name_const (string, string);
    return (char *) string;
}

char* ez_strreverse (char *string) {

    ez_return_val_if_fail (string != NULL, NULL);

    if (*string) {
        register char *h, *t;

        h = string;
        t = string + strlen (string) - 1;

        while (h < t) {
            register char c;

            c = *h;
            *h = *t;
            h++;
            *t = c;
            t--;
        }
    }

    talloc_set_name_const (string, string);
    return string;
}

int ez_strcasecmp (const char *s1, const char *s2) {
#ifdef HAVE_STRCASECMP
    ez_return_val_if_fail (s1 != NULL, 0);
    ez_return_val_if_fail (s2 != NULL, 0);

    return strcasecmp (s1, s2);
#else
    int c1, c2;

    ez_return_val_if_fail (s1 != NULL, 0);
    ez_return_val_if_fail (s2 != NULL, 0);

    while (*s1 && *s2) {
        c1 = isupper ((uchar)*s1) ? tolower ((uchar)*s1) : *s1;
        c2 = isupper ((uchar)*s2) ? tolower ((uchar)*s2) : *s2;
        
        if (c1 != c2) {
            return (c1 - c2);
        }
        
        s1++; s2++;
    }

    return (((int)(uchar) *s1) - ((int)(uchar) *s2));
#endif
}

int ez_strncasecmp (const char *s1, const char *s2, size_t n) {
#ifdef HAVE_STRNCASECMP
    return strncasecmp (s1, s2, n);
#else
    int c1, c2;

    ez_return_val_if_fail (s1 != NULL, 0);
    ez_return_val_if_fail (s2 != NULL, 0);

    while (n && *s1 && *s2) {
        n -= 1;
    
        c1 = isupper ((uchar)*s1) ? tolower ((uchar)*s1) : *s1;
        c2 = isupper ((uchar)*s2) ? tolower ((uchar)*s2) : *s2;
        
        if (c1 != c2) {
            return (c1 - c2);
        }
        
        s1++; s2++;
    }

    if (n) {
        return (((int) (uchar) *s1) - ((int) (uchar) *s2));
    } else {
        return 0;
    }
#endif
}

char* ez_strtruncate (char *string, size_t len) {

    ez_return_val_if_fail (string != NULL, NULL);

    size_t str_len = MIN (len, strlen(string));
    string[str_len] = 0;

    talloc_set_name_const (string, string);
    return string;
}

char* ez_stroverwrite (char *string, size_t pos, const char *val) {
    
    size_t str_len;
    str_len = strlen (string);
    
    ez_return_val_if_fail (string != NULL, NULL);
    ez_return_val_if_fail (val != NULL, string);
    ez_return_val_if_fail (pos >= 0, string);
    ez_return_val_if_fail (pos < str_len, string);

    size_t len;
    len = str_len - pos;
    
    memcpy (string + pos, val, len);

    talloc_set_name_const (string, string);
    return string;
}

char* ez_strerase (char *string, size_t pos, size_t len) {

    size_t str_len;
    str_len = strlen (string);
        
    ez_return_val_if_fail (string != NULL, NULL);
    ez_return_val_if_fail (pos >= 0, string);
    ez_return_val_if_fail (pos < str_len, string);

    if (len < 0)
        len = str_len - pos;
    else {
        ez_return_val_if_fail (pos + len < str_len, string);
        if (pos + len < str_len)
            memmove (string + pos, string + pos + len, str_len - (pos + len));
    }

    string[str_len - len] = 0;

    talloc_set_name_const (string, string);
    return string;
}

char* ez_strprintf (const char *format, ...) {

    char *string;
    size_t str_len;

    ez_return_val_if_fail (format != NULL, NULL);
    
    va_list args;   
    va_start (args, format);

    str_len = vsnprintf (NULL, 0, format, args);
    string = ez_new0 (char, str_len + sizeof (char));

    vsnprintf (string, str_len + sizeof (char), format, args);

    va_end (args);

    talloc_set_name_const (string, string);
    return string;
}

char* ez_strreplace (const char *string, const char *needle, const char *replace) {

    char *pos;
    char *new_string;
    int len1;
    int len2;
    int len_new;
    int count;
    
    ez_return_val_if_fail (string != NULL, NULL);
    ez_return_val_if_fail (needle != NULL, NULL);
    ez_return_val_if_fail (replace != NULL, NULL);    
    
    len1 = strlen (needle);
    len2 = strlen (replace);
    
    count = 0;
    pos = string;
    while (pos && pos[0] && (pos = strstr (pos, needle))) {
        count++;
        pos += len1;
    }
    
    if (count == 0) {
        return ez_strdup (string);
    }
    
    len_new = strlen (string) - (count * len1) + (count * len2) + 1;
    
    new_string = ez_new0 (char, len_new);

    if (new_string == NULL) {
        return ez_strdup (string);
    }
    
    while (string && string[0]) {
        pos = strstr (string, needle);
        if (pos != 0) {
            strncat (new_string, string, pos - string);
            strcat (new_string, replace);
            pos += len1;
        } else {
            strcat (new_string, string);
        }
        
        string = pos;
    }
    
    return new_string;
}

