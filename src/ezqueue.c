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

#include "ezqueue.h"

EZQueue* ez_queue_alloc () {

    EZQueue *queue;
    queue = ez_new0 (EZQueue, 1);

    queue->data = NULL;
    queue->next = NULL;
    
    return queue;
}

void ez_queue_push (EZQueue **queue, ezpointer data) {

    EZQueue *new_top = NULL;
    EZQueue *top = NULL;
    
    new_top = ez_queue_alloc ();
    new_top->data = data;
    
    if (*queue != NULL) {
        top = *queue;
        
        while (top->next)
            top = top->next;
        
        top->next = new_top;        
        
    } else {
        *queue = new_top;
    }
}

ezpointer ez_queue_pop (EZQueue **queue) {

    EZQueue *new_bottom = NULL;
    ezpointer data = NULL;
    
    ez_return_val_if_fail (*queue != NULL, NULL);

    new_bottom = (*queue)->next;
    
    data = (*queue)->data;
    ez_free (*queue);
    
    *queue = new_bottom;
    
    return data; 
}

