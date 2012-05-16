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

#ifndef __EZMEM_H__
#define __EZMEM_H__

#include <stdlib.h>
#include "talloc.h"
#include "ezmacros.h"

#define ez_new(type, count)  \
    talloc_array (NULL, type, count)

#define ez_new0(type, count)  \
    talloc_zero_array (NULL, type, count)

#define ez_renew(mem, type, count)    \
    talloc_realloc (NULL, mem, type, count)

#define ez_memdup(mem, count)    \
    talloc_memdup (NULL, mem, count)

#define ez_new_ctx \
    talloc_array

#define ez_new0_ctx \
    talloc_zero_array

#define ez_renew_ctx \
    talloc_realloc

#define ez_memdup_ctx \
    talloc_memdup

#define ez_reference \
    talloc_reference

#define ez_steal \
    talloc_steal

#define ez_unlink \
    talloc_unlink

#define ez_free \
    talloc_free

#endif /* __EZMEM_H__ */
