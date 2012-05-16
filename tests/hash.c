#include "../src/ezlib.h"


void my_hash_func (char *key, ezpointer value, ezpointer user_data) {
    printf ("%s:%s:%s\n", key, value, user_data);
}

bool my_list_func (ezpointer value, ezpointer user_data) {
    printf ("%s:%s\n", user_data, value);
}

int main (int argc, char **argv) {

    void *global_ctx;
    EZHashTable *hash = NULL;
    EZList *keys = NULL;
    EZList *values = NULL;
    
    global_ctx = ez_new0 (void, 0);
    
    hash = ez_hash_table_new (1);
    
    ez_hash_table_insert (hash, "1", ez_strdup_ctx (global_ctx, "Jon Doe"));
    ez_hash_table_insert (hash, "2", ez_strdup_ctx (global_ctx, "John Stiles"));
    ez_hash_table_insert (hash, "3", ez_strdup_ctx (global_ctx, "Richard Miles"));
    ez_hash_table_insert (hash, "4", ez_strdup_ctx (global_ctx, "Mary Major"));
    
    printf ("%s:%s\n", "2", ez_hash_table_lookup (hash, "2"));
    printf ("%s:%s\n", "2", ez_hash_table_remove (hash, "2"));

    ez_hash_table_foreach (hash, my_hash_func, "user data");
    
    printf ("%d\n", ez_hash_table_size (hash));
    
    keys = ez_hash_table_get_keys (hash);
    ez_list_foreach (keys, my_list_func, "key");
    ez_list_free (keys);
    
    values = ez_hash_table_get_values (hash);
    ez_list_foreach (values, my_list_func, "value");
    ez_list_free (values);
    
    ez_hash_table_free (hash);

    ez_free (global_ctx);
    
    return 0;
}

