#include "../src/ezlib.h"

int main (int argc, char **argv) {

    char *pattern = "Bcast:(\\d*).(\\d*).(\\d*).(\\d*)";
    char *subject = "inet Adresse:192.168.4.85  Bcast:192.168.4.255  Maske:255.255.255.05";

    EZRegex *tc = ez_regex_new (pattern);
    if (tc) {
        
        bool match = ez_regex_match (tc, subject);
        if (match) {
        
            printf ("pattern: %s\nsubject: %s\n", pattern, subject);
            printf ("substrings: %i\n", ez_regex_substrings (tc));
            
            int i;
            for (i = 0; i < ez_regex_substrings (tc); i++)
                printf ("substrings %d: %s\n", i, ez_regex_get_substring (tc, i));
            
            ez_regex_free (tc);
        }
    } else {

        printf ("%s\n", ez_regex_error ());
    }

    return 0;
}

