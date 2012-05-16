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

#ifndef __EZArray_H__
#define __EZArray_H__

#include <stdlib.h>

#include "eztypes.h"
#include "ezmem.h"

EZ_BEGIN_DECLS

typedef void (*ez_array_func) (ezpointer);

typedef struct _EZArray EZArray;

struct _EZArray {
  void **data;
  int size;
  int len;
};

extern EZArray* ez_array_new ();
extern void ez_array_free (EZArray *array);
extern EZArray* ez_array_dup (EZArray *array);
extern void ez_array_foreach (EZArray *array, ez_array_func foreach);
extern int ez_array_index (EZArray *array, ezpointer value);
extern int ez_array_push (EZArray *array, ezpointer value);
extern ezpointer ez_array_pop (EZArray *array);
extern ezpointer ez_array_get_index (EZArray *array, int index);
extern void ez_array_set_index (EZArray *array, int index, ezpointer value);
extern ezpointer ez_array_remove_index (EZArray *array, int index);

EZ_END_DECLS

#endif /* __EZArray_H__ */
