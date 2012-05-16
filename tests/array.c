#include "../src/ezlib.h"

void my_array_print_element (void *element) {
    printf ("%s\n", element);
}

void my_array_free_data (void *element) {
    ez_free (element);
}

int main (int argc, char **argv) {

    EZArray *my_array = ez_array_new ();
    EZArray *my_array_dup = NULL;

    ez_array_push (my_array, ez_strdup ("Jon Doe"));
    ez_array_push (my_array, ez_strdup ("John Stiles"));
    ez_array_push (my_array, ez_strdup ("Richard Miles"));

    ez_free (ez_array_remove_index (my_array, 0));
    
    int i;    
    for (i = 0; i < 200; i++) 
        ez_array_push (my_array, ez_strprintf ("%s%d", "string", i));
    
    my_array_dup = ez_array_dup (my_array);

    ez_array_free (my_array);
    
    printf ("%s\n", ez_array_get_index (my_array_dup, 0));
    printf ("%d\n", ez_array_index (my_array_dup, ez_array_get_index (my_array_dup, 15)));
    ez_array_foreach (my_array_dup, my_array_print_element);
    
    ez_array_foreach (my_array_dup, my_array_free_data);
    ez_array_free (my_array_dup);  
    
    return 0;
}

