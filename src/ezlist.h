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

#ifndef __EZLIST_H__
#define __EZLIST_H__

#include <stdlib.h>

#include "eztypes.h"
#include "ezmacros.h"
#include "ezmem.h"

EZ_BEGIN_DECLS

typedef struct _EZList EZList;

struct _EZList {
    ezpointer data;
    EZList *next;
    EZList *prev;
};

typedef bool (*ez_list_func) (ezpointer value, ezpointer user_data);
typedef void (*ez_list_free_func) (ezpointer data);

extern EZList* ez_list_alloc ();
extern EZList* ez_list_append (EZList *list, ezpointer data);
extern EZList* ez_list_last (EZList *list);
extern EZList* ez_list_first (EZList *list);
extern size_t ez_list_length (EZList *list);
extern void ez_list_free (EZList *list);
extern void ez_list_free_with_data (EZList *list, ez_list_free_func func);
#define ez_list_free_1 ez_list_free1
extern void ez_list_free_1 (EZList *list);
extern EZList* ez_list_prepend (EZList *list, ezpointer data);
extern EZList* ez_list_insert (EZList *list, ezpointer data, int position);
extern EZList* ez_list_nth (EZList *list, uint n);
extern EZList* ez_list_remove (EZList *list, ezpointer data);
extern void ez_list_foreach (EZList *list, ez_list_func func, ezpointer user_data);

#define ez_list_previous(list)  ((list) ? (((EZList *)(list))->prev) : NULL)
#define ez_list_next(list)  ((list) ? (((EZList *)(list))->next) : NULL)

EZ_END_DECLS

#endif /* __EZLIST_H__ */
