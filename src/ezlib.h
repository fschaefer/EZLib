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

#ifndef __EZLIB_H__
#define __EZLIB_H__

#ifdef __SOURCE_TEST__

#include "../config.h"

#include "ezmacros.h"
#include "ezmem.h"
#include "eztypes.h"

#include "ezclass.h"
#include "ezarray.h"
#include "ezbase64.h"
#include "ezexceptions.h"
#include "ezhash.h"
#include "ezlist.h"

#ifdef HAVE_PCRE
    #include "ezregex.h"
#endif /* HAVE_PCRE */

#include "ezqueue.h"
#include "ezstack.h"
#include "ezstrfuncs.h"
#include "ezstring.h"

#else /* __SOURCE_TEST__ */

#include "ezlib/config.h"

#include "ezlib/ezmacros.h"
#include "ezlib/ezmem.h"
#include "ezlib/eztypes.h"

#include "ezlib/ezclass.h"
#include "ezlib/ezarray.h"
#include "ezlib/ezbase64.h"
#include "ezlib/ezexceptions.h"
#include "ezlib/ezhash.h"
#include "ezlib/ezlist.h"

#ifdef HAVE_PCRE
    #include "ezlib/ezregex.h"
#endif /* HAVE_PCRE */

#include "ezlib/ezqueue.h"
#include "ezlib/ezstack.h"
#include "ezlib/ezstrfuncs.h"
#include "ezlib/ezstring.h"

#endif /* __SOURCE_TEST__ */

#endif /* __EZLIB_H__ */
