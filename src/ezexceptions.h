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

#ifndef __EZEXCEPTIONS_H__
#define __EZEXCEPTIONS_H__

#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>
#include "eztypes.h"
#include "ezmacros.h"

EZ_BEGIN_DECLS

#define NO_EXCEPTION 0

#define ez_exception_unhandled __ez_exception_unhandled

#define try \
    ez_exception_id = setjmp (ez_exception_env_stack[ez_exception_env_stack_pos++]); \
    if (ez_exception_id == NO_EXCEPTION)

#define catch(e) \
    else if (ez_exception_id == (e))

#define otherwise \
    else

#define passthrough() \
    throw (ez_exception_id)

#ifndef EZ_DEBUG
#define throw(e) \
    EZ_STMT_START { \
    ez_exception_id = e; \
    if (ez_exception_env_stack_pos == 0) \
       ez_exception_unhandled (); \
    longjmp (ez_exception_env_stack[--ez_exception_env_stack_pos], (e)); \
    } EZ_STMT_END
#else
#define throw(e) \
    EZ_STMT_START { \
    ez_exception_id = e; \
    if (ez_exception_env_stack_pos == 0) \
       ez_exception_unhandled (); \
    printf ("ezlib: throwing exception ‘%d’ in ‘%s’ at %s:%d\n", ez_exception_id, __func__, __FILE__, __LINE__); fflush (stdout);\
    longjmp (ez_exception_env_stack[--ez_exception_env_stack_pos], (e)); \
    } EZ_STMT_END
    
#endif /* EZ_DEBUG */

#define __throws(e,...)

#ifndef MAX_NEST_EXCEPTION
#  define MAX_NEST_EXCEPTION 256
#endif

#ifndef __SOURCE_COMPILE__

extern jmp_buf ez_exception_env_stack[];
extern uint ez_exception_env_stack_pos;
extern uint ez_exception_id;

#endif /* __SOURCE_COMPILE__ */

EZ_END_DECLS

#endif /* __EZEXCEPTIONS_H__ */
