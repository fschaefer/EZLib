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

#ifndef __EZSTACK_H__
#define __EZSTACK_H__

#include <stdlib.h>

#include "eztypes.h"
#include "ezmem.h"

EZ_BEGIN_DECLS

typedef struct _EZStack EZStack;

struct _EZStack {
    ezpointer data;
    EZStack *prev;
};

extern EZStack* ez_stack_alloc ();
extern void ez_stack_push (EZStack **stack, ezpointer data);
extern ezpointer ez_stack_pop (EZStack **stack);

EZ_END_DECLS

#endif /* __EZSTACK_H__ */
