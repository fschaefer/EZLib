/* EZLIB - Library of useful routines for C programming
 * 
 * Copyright (C) 2008 Florian Schäfer <florian.schaefer@gmail.com>
 * 
 * This library may contain copyrighted material by:
 *
 * David Crawshaw
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

#ifndef __EZHASH_H__
#define __EZHASH_H__

#include <stdlib.h>
#include <math.h>

#include "eztypes.h"
#include "ezmacros.h"
#include "ezmem.h"
#include "ezlist.h"

EZ_BEGIN_DECLS

typedef struct _EZHashRecord EZHashRecord;
typedef struct _EZHashTable EZHashTable;

typedef void (*ez_hash_func) (char *key, ezpointer value, ezpointer user_data);

extern EZHashTable* ez_hash_table_new (uint capacity);
extern void ez_hash_table_free (EZHashTable *hash_table);
extern int ez_hash_table_insert (EZHashTable *hash_table, const char *key, ezpointer value);
extern ezpointer ez_hash_table_lookup (EZHashTable *hash_table, const char *key);
extern ezpointer ez_hash_table_remove (EZHashTable *hash_table, const char *key);
extern uint ez_hash_table_size (EZHashTable *hash_table);
extern void ez_hash_table_foreach (EZHashTable *hash_table, ez_hash_func func, ezpointer user_data);
extern EZList* ez_hash_table_get_keys (EZHashTable *hash_table);
extern EZList* ez_hash_table_get_values (EZHashTable *hash_table);

EZ_END_DECLS

#endif /* __EZHASH_H__ */
