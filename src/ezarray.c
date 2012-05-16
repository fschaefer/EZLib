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

#include "ezarray.h"

#define MIN_ARRAY_SIZE \
    (128 / sizeof (ezpointer))

EZArray* ez_array_new () {

    EZArray *new = NULL;

    new = ez_new0 (EZArray, 1);
    new->len = 0;
    new->size = MIN_ARRAY_SIZE;

    new->data = (ezpointer*) ez_new0_ctx (new, ezpointer, new->size);

    return new;
}

void ez_array_free (EZArray *array) {
  
    ez_return_if_fail (array != NULL);

    array->data = NULL;
    ez_free (array);
}

EZArray* ez_array_dup (EZArray *array) {

    EZArray *new;

    ez_return_val_if_fail (array != NULL, NULL);

    new = ez_memdup (array, sizeof (EZArray));
    new->data = (ezpointer*) ez_memdup_ctx (new, array->data, array->size * sizeof (ezpointer));

    return new;
}

void ez_array_foreach (EZArray *array, ez_array_func foreach) {
    
    int i;
    
    ez_return_if_fail (array != NULL);
    ez_return_if_fail (foreach != NULL);
    
    for (i = 0; i < array->len; i++) {
        foreach (array->data[i]);
    }
}

int ez_array_index (EZArray *array, ezpointer value) {

    int i;

    ez_return_val_if_fail (array != NULL, -1);
    ez_return_val_if_fail (value != NULL, -1);

    for (i = 0; i < array->len; i++) {
        if (array->data[i] == value) {
            return i;
        }
    }
    
    return -1;
}

int ez_array_push (EZArray *array, ezpointer value) {

    ez_return_val_if_fail (array != NULL, -1);

    if (array->len + 1 == array->size) {
        array->size += MIN_ARRAY_SIZE;
        array->data = (ezpointer*) ez_renew (array->data, ezpointer, array->size);
    }

    array->data[array->len++] = value;

    return array->len - 1;
}

ezpointer ez_array_pop (EZArray *array) {

    ez_return_val_if_fail (array != NULL, NULL);

    array->data[array->len] = NULL;

    return (array->data[--array->len]);
}

ezpointer ez_array_remove_index (EZArray *array, int index) {

    ezpointer result;
    
    ez_return_val_if_fail (array != NULL, NULL);
    ez_return_val_if_fail (index < array->len, NULL);

    result = array->data[index];

    if (index != array->len - 1)
        memmove (array->data + index, array->data + index + 1,
                 sizeof (ezpointer) * (array->len - index - 1));
    
    array->len -= 1;

    return result;
}

ezpointer ez_array_get_index (EZArray *array, int index) {

    ez_return_val_if_fail (array != NULL, NULL);
    ez_return_val_if_fail (index < array->len, NULL);

    return (array->data[index]);
}

void ez_array_set_index (EZArray *array, int index, ezpointer value) {

    ez_return_if_fail (array != NULL);
    ez_return_if_fail (index < array->len);

    array->data[index] = value;
}

