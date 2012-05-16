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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.     See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "ezbase64.h"

static char base64_alphabet[] = 
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

#define XX -1

static int base64_index[256] = {
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,62, XX,XX,XX,63,
    52,53,54,55, 56,57,58,59, 60,61,XX,XX, XX,XX,XX,XX,
    XX, 0, 1, 2,  3, 4, 5, 6,  7, 8, 9,10, 11,12,13,14,
    15,16,17,18, 19,20,21,22, 23,24,25,XX, XX,XX,XX,XX,
    XX,26,27,28, 29,30,31,32, 33,34,35,36, 37,38,39,40,
    41,42,43,44, 45,46,47,48, 49,50,51,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
};

char* ez_base64_encode (const void *data, size_t size) {

    char *s;
    char *p;
    int c;
    const uchar *q;
    
    ez_return_val_if_fail (data != NULL, NULL);
    ez_return_val_if_fail (size > 0, NULL);

    p = s = ez_new0 (char, size * 4 / 3 + 4);
    
    if (p == NULL)
        return NULL;
        
    q = (const uchar *) data;
    
    int i;
    for (i = 0; i < size;) {
        c = q[i++];
        c *= 256;
        if (i < size)
            c += q[i];
            
        i++;

        c *= 256;
        if (i < size)
            c += q[i];
            
        i++;
        
        p[0] = base64_alphabet[(c & 0x00fc0000) >> 18];
        p[1] = base64_alphabet[(c & 0x0003f000) >> 12];
        p[2] = base64_alphabet[(c & 0x00000fc0) >> 6];
        p[3] = base64_alphabet[(c & 0x0000003f) >> 0];
        
        if (i > size)
            p[3] = '=';
            
        if (i > size + 1)
            p[2] = '=';
            
        p += 4;
    }
    
    *p = 0;
    
    return s;
}

#define DECODE_ERROR 0xffffffff

static uint base64_decode_token (const char *token) {

    int val = 0;
    int marker = 0;
    
    if (strlen (token) < 4)
        return DECODE_ERROR;

    int i;        
    for (i = 0; i < 4; i++) {
        val *= 64;
        if (token[i] == '=') {
            marker++;
        } else if (marker > 0) {
            return DECODE_ERROR;
        } else {
            val += base64_index[(int) token[i]];
        }
    }

    if (marker > 2)
        return DECODE_ERROR;

    return (marker << 24) | val;
}

void* ez_base64_decode (const char *str) {

    void *data;
    const char *p;
    uchar *q;

    ez_return_val_if_fail (str != NULL, NULL);

    q = data = ez_new (char, strlen (str) / 4 * 3);
    
    for (p = str; *p && (*p == '=' || strchr (base64_alphabet, *p)); p += 4) {
        uint val = base64_decode_token (p);
        uint marker = (val >> 24) & 0xff;

        if (val == DECODE_ERROR)
            return NULL;

        *q++ = (val >> 16) & 0xff;

        if (marker < 2)
            *q++ = (val >> 8) & 0xff;

        if (marker < 1)
            *q++ = val & 0xff;
    }
    
    return data;
}

