#include "../src/ezlib.h"

int main (int argc, char **argv) {

    void *global_ctx;
    char* tmp_string;
    EZStack *the_stack = NULL;
    
    global_ctx = ez_new0 (void, 0);
    
    ez_stack_push (&the_stack, ez_strdup_ctx (global_ctx, "Jon Doe"));
    ez_stack_push (&the_stack, ez_strdup_ctx (global_ctx, "John Stiles"));
    ez_stack_push (&the_stack, ez_strdup_ctx (global_ctx, "Richard Miles"));
    ez_stack_push (&the_stack, ez_strdup_ctx (global_ctx, "Mary Major"));

    while (tmp_string = ez_stack_pop (&the_stack)) {
        printf ("%s\n", tmp_string);
    }
    
    ez_free (global_ctx);
    return 0;
}

