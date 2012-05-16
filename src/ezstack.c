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

#include "ezstack.h"

EZStack* ez_stack_alloc () {

    EZStack *stack;
    stack = ez_new0 (EZStack, 1);

    stack->data = NULL;    
    stack->prev = NULL;
    
    return stack;
}

void ez_stack_push (EZStack **stack, ezpointer data) {

    EZStack *stack_top = NULL;

    stack_top = ez_stack_alloc ();
    stack_top->data = data;

    if (*stack != NULL) {
        stack_top->prev = *stack;
    } else {
        stack_top->prev = NULL;
    }

    *stack = stack_top;
}

ezpointer ez_stack_pop (EZStack **stack) {

    EZStack *stack_top = NULL;
    ezpointer data = NULL;
    
    ez_return_val_if_fail (*stack != NULL, NULL);

    data = (*stack)->data;

    stack_top = (*stack)->prev;
    ez_free (*stack);
    *stack = stack_top;
    
    return data; 
}

