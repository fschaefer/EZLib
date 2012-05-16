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
 
#ifndef __EZMARCOS_H__
#define __EZMARCOS_H__

/* Guard C code in headers, while including them from C++ */
#ifdef  __cplusplus
#define EZ_BEGIN_DECLS  extern "C" {
#define EZ_END_DECLS    }
#else
#define EZ_BEGIN_DECLS ;
#define EZ_END_DECLS ;
#endif

#if !(defined (EZ_STMT_START) && defined (EZ_STMT_END))
#define EZ_STMT_START  do
#define EZ_STMT_END    while (0)
#endif

#define ez_return_if_fail(expr) \
    EZ_STMT_START {                                 \
    if (!(expr)) {                                  \
        return;                                     \
    }; } EZ_STMT_END

#define ez_return_val_if_fail(expr, val)            \
    EZ_STMT_START {                                 \
    if (!(expr)) {                                  \
        return (val);                               \
    }; } EZ_STMT_END

#define MIN(a, b)  (((a) < (b)) ? (a) : (b))
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))

#endif /* _EZMACROS_H_ */
