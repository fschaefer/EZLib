#include "../src/ezlib.h"

int main (int argc, char **argv) {

    char* base64_preencoded = "Sm9uIERvZSBKb2huIFN0aWxlcyBSaWNoYXJkIE1pbGVz";
    char* base64_decoded = ez_base64_decode (base64_preencoded);
    char* base64_encoded = ez_base64_encode (base64_decoded, strlen (base64_decoded));
    printf ("%s\n", base64_preencoded);
    printf ("%s\n", base64_decoded);
    
    printf ("%s\n", base64_encoded);
    
    if (ez_str_equal (base64_preencoded, base64_encoded))
        printf ("%s\n", "encoded strings are equal");
    
    
    return 0;
}

