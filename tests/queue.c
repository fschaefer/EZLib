#include "../src/ezlib.h"

int main (int argc, char **argv) {

    void *global_ctx;
    char* tmp_string;
    EZQueue *the_queue = NULL;
    
    global_ctx = ez_new0 (void, 0);
    
    ez_queue_push (&the_queue, ez_strdup_ctx (global_ctx, "Jon Doe"));
    ez_queue_push (&the_queue, ez_strdup_ctx (global_ctx, "John Stiles"));
    ez_queue_push (&the_queue, ez_strdup_ctx (global_ctx, "Richard Miles"));
    ez_queue_push (&the_queue, ez_strdup_ctx (global_ctx, "Mary Major"));

    while (tmp_string = ez_queue_pop (&the_queue)) {
        printf ("%s\n", tmp_string);
    }
    
    ez_free (global_ctx);
    return 0;
}

