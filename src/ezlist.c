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

#include "ezlist.h"

EZList* ez_list_alloc () {

    EZList *new_list;
    new_list = ez_new0 (EZList, 1);    
    return new_list;
}

EZList* ez_list_append (EZList *list, ezpointer data) {
  
    EZList *new_list;
    EZList *last;

    new_list = ez_list_alloc ();
    new_list->data = data;

    if (list) {
        last = ez_list_last (list);
        last->next = new_list;
        new_list->prev = last;

        return list;
    } else {
        return new_list;
    }
}

EZList* ez_list_last (EZList *list) {

    if (list) {
        while (list->next)
            list = list->next;
    }

    return list;
}

EZList* ez_list_first (EZList *list) {

    if (list) {
        while (list->prev)
            list = list->prev;
    }

    return list;
}

size_t ez_list_length (EZList *list) {

    size_t length;
    length = 0;
    
    while (list) {
        length++;
        list = list->next;
    }

    return length;
}

void ez_list_free (EZList *list) {

    EZList *last;

    while (list) {
        last = list;
        list = list->next;
        ez_free (last);
    }
}

void ez_list_free_with_data (EZList *list, ez_list_free_func func) {
    EZList *last;

    while (list) {
        last = list;
        list = list->next;
        if (func != NULL) {
            func (last->data);
        }
        ez_free (last);
    }
}

void ez_list_free_1 (EZList *list) {
    ez_free (list);
}

EZList* ez_list_prepend (EZList *list, ezpointer data) {

    EZList *new_list;

    new_list = ez_list_alloc ();
    new_list->data = data;

    if (list) {
        if (list->prev) {
            list->prev->next = new_list;
            new_list->prev = list->prev;
        }
        list->prev = new_list;
        new_list->next = list;
    }

    return new_list;
}

EZList* ez_list_insert (EZList *list, ezpointer data, int position) {

    EZList *new_list;
    EZList *tmp_list;
  
    if (position < 0) {
        return ez_list_append (list, data);
    } else if (position == 0) {
        return ez_list_prepend (list, data);
    }

    tmp_list = ez_list_nth (list, position);
    
    if (!tmp_list)
        return ez_list_append (list, data);

    new_list = ez_list_alloc ();
    new_list->data = data;

    if (tmp_list->prev) {
        tmp_list->prev->next = new_list;
        new_list->prev = tmp_list->prev;
    }
    
    new_list->next = tmp_list;
    tmp_list->prev = new_list;

    if (tmp_list == list) {
        return new_list;
    } else {
        return list;
    }
}

EZList* ez_list_nth (EZList *list, uint n) {

    while ((n-- > 0) && list) {
        list = list->next;
    }

    return list;
}

EZList* ez_list_remove (EZList *list, ezpointer data) {

    EZList *tmp;
    tmp = list;

    while (tmp) {
        if (tmp->data != data) {
            tmp = tmp->next;
        } else {
            if (tmp->prev) {
                tmp->prev->next = tmp->next;
            }
            
            if (tmp->next) {
                tmp->next->prev = tmp->prev;
            }

            if (list == tmp) {
                list = list->next;
            }

            ez_list_free_1 (tmp);
        
            break;
        }
    }
    
    return list;
}

void ez_list_foreach (EZList *list, ez_list_func func, ezpointer user_data) {

    ez_return_if_fail (func != NULL);
    
    while (list) {
        EZList *next = list->next;
        if ((*func) (list->data, user_data) == false){
            break;
        }
        list = next;
    }
}
