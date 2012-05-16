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

#include "ezhash.h"

static const uint sizes[] = {
    53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317,
    196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917, 25165843,
    50331653, 100663319, 201326611, 402653189, 805306457, 1610612741
};

static const int sizes_count = sizeof(sizes) / sizeof(sizes[0]);
static const float load_factor = 0.65;

struct _EZHashRecord {
    uint hash;
    const char *key;
    ezpointer value;
};

struct _EZHashTable {
    EZHashRecord *records;
    uint records_count;
    uint size_index;
};

static int ez_hash_table_grow (EZHashTable *hash_table) {

    ez_return_val_if_fail (hash_table != NULL, -1);
    
    int i;
    EZHashRecord *old_recs;
    uint old_recs_length;

    old_recs_length = sizes[hash_table->size_index];
    old_recs = hash_table->records;

    if (hash_table->size_index == sizes_count - 1)
        return -1;
        
    if ((hash_table->records = ez_new0 (EZHashRecord, sizes[++hash_table->size_index])) == NULL) {
        hash_table->records = old_recs;
        return -1;
    }

    hash_table->records_count = 0;

    // rehash table
    for (i = 0; i < old_recs_length; i++)
        if (old_recs[i].hash && old_recs[i].key)
            ez_hash_table_insert (hash_table, old_recs[i].key, old_recs[i].value);

    ez_free (old_recs);

    return 0;
}

static uint ez_hash_table_strhash (const char *str) {

    ez_return_val_if_fail (str != NULL, (uint) NULL);
    
    const char *p = str;
    size_t n = strlen (str);    
    uint h = 0;

    while (n--) {
        h = (h << 5) - h + *p;
        p++;
    }

    return (uint) h;
}

EZHashTable* ez_hash_table_new (uint capacity) {

    EZHashTable *hash_table;
    int i;
    int sind = 0;

    capacity /= load_factor;

    for (i = 0; i < sizes_count; i++) 
        if (sizes[i] > capacity) { sind = i; break; }

    if ((hash_table = ez_new0 (EZHashTable, 1)) == NULL)
        return NULL;
        
    if ((hash_table->records = ez_new0 (EZHashRecord, sizes[sind])) == NULL) {
        ez_free (hash_table);
        return NULL;
    }

    hash_table->records_count = 0;
    hash_table->size_index = sind;

    return hash_table;
}

void ez_hash_table_free (EZHashTable *hash_table) {

    ez_return_if_fail (hash_table != NULL);
    
    ez_free (hash_table->records);
    ez_free (hash_table);
}

int ez_hash_table_insert (EZHashTable *hash_table, const char *key, ezpointer value) {

    ez_return_val_if_fail (hash_table != NULL, -1);
    ez_return_val_if_fail (((key != NULL) || (*key != '\0')), -2);
    
    EZHashRecord *recs;
    int rc;
    uint off, ind, size, code;
    
    if (hash_table->records_count > sizes[hash_table->size_index] * load_factor) {
        rc = ez_hash_table_grow (hash_table);
        if (rc) return rc;
    }

    code = ez_hash_table_strhash (key);
    recs = hash_table->records;
    size = sizes[hash_table->size_index];

    ind = code % size;
    off = 0;

    while (recs[ind].key)
        ind = (code + (int) pow (++off,2)) % size;

    recs[ind].hash = code;
    recs[ind].key = key;
    recs[ind].value = value;

    hash_table->records_count++;

    return 0;
}

ezpointer ez_hash_table_lookup (EZHashTable *hash_table, const char *key) {

    ez_return_val_if_fail (hash_table != NULL, NULL);
    ez_return_val_if_fail (key != NULL, NULL);

    EZHashRecord *recs;
    uint off, ind, size;
    uint code = ez_hash_table_strhash (key);

    recs = hash_table->records;
    size = sizes[hash_table->size_index];
    ind = code % size;
    off = 0;

    // search on hash which remains even if a record has been removed,
    // so hash_remove() does not need to move any collision records
    while (recs[ind].hash) {
        if ((code == recs[ind].hash) && recs[ind].key &&
                strcmp(key, recs[ind].key) == 0)
            return recs[ind].value;
        ind = (code + (int) pow (++off,2)) % size;
    }

    return NULL;
}

ezpointer ez_hash_table_remove (EZHashTable *hash_table, const char *key) {

    ez_return_val_if_fail (hash_table != NULL, NULL);
    ez_return_val_if_fail ((key != NULL || *key != '\0'), NULL);
    
    uint code = ez_hash_table_strhash (key);
    EZHashRecord *recs;
    ezpointer value;
    uint off, ind, size;

    recs = hash_table->records;
    size = sizes[hash_table->size_index];
    ind = code % size;
    off = 0;

    while (recs[ind].hash) {
        if ((code == recs[ind].hash) && recs[ind].key &&
                strcmp(key, recs[ind].key) == 0) {
            // do not erase hash, so probes for collisions succeed
            value = recs[ind].value;
            recs[ind].key = 0;
            recs[ind].value = 0;
            hash_table->records_count--;
            return value;
        }
        ind = (code + (int) pow (++off, 2)) % size;
    }
 
    return NULL;
}

uint ez_hash_table_size (EZHashTable *hash_table) {

    ez_return_val_if_fail (hash_table != NULL, (uint) NULL);
    return hash_table->records_count;
}

void ez_hash_table_foreach (EZHashTable *hash_table, ez_hash_func func, ezpointer user_data) {
   
    ez_return_if_fail (hash_table != NULL);
    ez_return_if_fail (func != NULL);
    
    int i;
    for (i = 0; i < sizes[hash_table->size_index]; i++) {
        if (hash_table->records[i].key != NULL) {
            (*func) ((char*) hash_table->records[i].key, hash_table->records[i].value, user_data);
        }
    }
}

EZList* ez_hash_table_get_keys (EZHashTable *hash_table) {
    
    ez_return_val_if_fail (hash_table != NULL, NULL);
    
    EZList *new_list = NULL;
    
    int i;
    for (i = 0; i < sizes[hash_table->size_index]; i++) {
        if (hash_table->records[i].key != NULL) {
            new_list = ez_list_append (new_list, (char*) hash_table->records[i].key);
        }
    }

    return new_list;
}

EZList* ez_hash_table_get_values (EZHashTable *hash_table) {
    
    ez_return_val_if_fail (hash_table != NULL, NULL);
    
    EZList *new_list = NULL;
    
    int i;
    for (i = 0; i < sizes[hash_table->size_index]; i++) {
        if (hash_table->records[i].key != NULL) {
            new_list = ez_list_append (new_list, (void*) hash_table->records[i].value);
        }
    }

    return new_list;
}
