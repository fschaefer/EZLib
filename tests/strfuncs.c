#include "../src/ezlib.h"

int main (int argc, char **argv) {

    char *first;
    char *second;
    char *third;
    char *fourth;
    char *fifth;
    char *sixth;
    char **str_array;

    first = ez_strdup ("   first string   ");
    printf ("first string '%s' with strlen '%d'\n", first, strlen (first));
    
    second = ez_strndup ("second string", 14);
    printf ("second string '%s', strlen should be 13 == '%d'\n", second, strlen (second));
    
    printf ("removing leading whitespace from first string: '%s'\n", ez_strchug (first));
    printf ("removing trailing whitespace from first string: '%s'\n", ez_strchomp (first));

    third = ez_strconcat (first, second, 0);
    printf ("concatenation of the first and second string: '%s'\n", third);

    printf ("checking if prefix of string: '%s' is 'first'\n", third);
    if (ez_str_has_prefix (third, "first") == true) {
        printf ("prefix ok\n");
    }

    printf ("checking if suffix of string: '%s' is 'string'\n", third);
    if (ez_str_has_suffix (third, "string") == true) {
        printf ("suffix ok\n");
    }
    
    printf ("%s\n", "compare fist string with 'first string'");
    if (ez_strcmp0 ("first string", first) == 0) {
        printf ("compare ok\n");
    }
    
    printf ("first string all upper case: '%s'\n", ez_strup (first));
    printf ("first string all lower case: '%s'\n", ez_strdown (first));

    printf ("first string reversed: '%s'\n", ez_strreverse (first));
    printf ("first string reversed again: '%s'\n", ez_strreverse (first));

    printf ("case insensitive compare of first string\n");
    if (ez_strcasecmp ("FIRST STRING", first) == 0) {
        printf ("insensitive compare ok\n");
    }
    
    printf ("case insensitive compare of first string with fixed length\n");
    if (ez_strncasecmp ("FIRST", first, 5) == 0) {
        printf ("insensitive compare with fixed length ok\n");
    }

    printf ("trancating first string to strlen '5': %s\n", ez_strtruncate (first, 5));
    printf ("overwriting second string with 'foobar': %s\n", ez_stroverwrite (second, 0, "foobar"));

    printf ("copying 'second' into second string with ez_stpcpy\n");
    if (ez_str_equal (ez_stpcpy (second, "second"), "\0")) {
        printf ("ez_stpcpy ok\n");
    }
    
    fourth = ez_strprintf ("%s", second);
    printf ("ez_strprintf 'second' into fourth string: %s\n", fourth);

    printf ("erasing 'second' from position '1' with len '4': %s\n", ez_strerase (fourth, 1, 4));
    
    fifth = ez_strdup ("\"\"\"fifth string\"\"\"\"");
    printf ("removing leading \" from fifth string: '%s'\n", ez_strchugc (fifth, '\"'));
    printf ("removing trailing \" from fifth string: '%s'\n", ez_strchompc (fifth, '\"'));
    
    printf ("splitting string '%s'\n", "Jon Doe:John Stiles:Richard Miles:Mary Major");
    str_array = ez_strsplit ("Jon Doe:John Stiles:Richard Miles:Mary Major", ":", -1);
    
    int i = 0;
    while (str_array[i] != 0) {
        printf ("%s\n", str_array[i]);
        i++;
    }
    
    printf ("length of array: %d\n", ez_strv_length (str_array));
    printf ("joining array back to string: '%s'\n", ez_steal (str_array, ez_strjoinv ("#", str_array)));
    printf ("joining several strings: '%s'\n", ez_steal (str_array, ez_strjoin ("#", "this", "is", "a", "new", "string", NULL)));
    
    sixth = ez_strreplace ("John Stiles", "Stiles", "Miles");
    printf ("replacing \"Stiles\" in \"John Stiles\" with \"Miles\": '%s'\n", sixth);    
    
    ez_strfreev (str_array);
    
    ez_free (first);
    ez_free (second);
    ez_free (third);
    ez_free (fourth);
    ez_free (fifth);
    ez_free (sixth);
        
    return 0;
}

