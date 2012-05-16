EZLib
=====

EZLib is a C utility library, which provides some useful data types, string utilities and memory handling macros. It also provides macros for using object oriented programming in ISO C and a simple implementation of structured exception handling with try/catch blocks.

About
-----

EZLib is a C utility library, which provides some useful data types, string utilities and memory handling macros.<br />
It also provides macros for using object oriented programming in ISO C and a simple implementation of structured exception handling with try/catch blocks.<br />
<br />
EZLib is free software, licensed under the GNU LGPL.

Why
---

While working on small and embedded systems where the GLib isn't available, I started collecting functions for my own utility library.<br />
Whereas GLib is a "huge beast" for embedded systems when only using a small subset of the provided functionality, EZLib is very simple and small.
And that's what it meant to be, simple and small.

Features
--------

A list of features of EZLib:

* Simple macros for Memory handling with the Samba trivial allocation library.
* Many functions for easy string handling of plain C char arrays.
* A EZString data type (like GLib's GString) and appropriate functions.
* EZList, an doubly linked lists type (borrowed from GLib's GList).
* EZArray, a simple dynamiccally growing array.
* EZStack and EZQueue.
* EZHashTable, an hash table implementation.
* Macros for using classes and objects in C with the full gammit of things you expect with normal object oriented languages, for example inheritance and even introspection.
* Macros for structured exception handling in C with ''try'', ''throw'' and ''catch''.

Todo
----

* Complete feature tests.
* Documentation.
* Examples on Wiki.
* Unicode support.
* A lot more.

Examples
--------

A basic class example.

$ cat TestClass.h:
<pre>
#include <ezlib.h>

CLASS (TestClass, Object)
    ATTRIBUTE (TestClass, x, int);
    ATTRIBUTE (TestClass, y, int);
    ATTRIBUTE (TestClass, name, char*);
    TestClass METHOD (TestClass, ctor);
    void METHOD (TestClass, dtor);
END_CLASS
</pre>

$ cat TestClass.c:
<pre>
#include "TestClass.h"

TestClass TestClass_ctor (TestClass self) {
    printf ("%s '%s'\n", "in constructor of", NAMEOF (self));

    self->set_name (self, ez_strdup_ctx (self, "Jon Doe"));
    
    return self;
}

void TestClass_dtor (TestClass self) {
    printf ("%s '%s'\n", "in destructor of", NAMEOF (self));

    ez_free (self);
}

ACCESSOR (TestClass, x, int);
ACCESSOR (TestClass, y, int);
ACCESSOR (TestClass, name, char*);

VTABLE (TestClass, Object)
    VACCESSOR (TestClass, x);
    VACCESSOR (TestClass, y);
    VACCESSOR (TestClass, name);
    VMETHOD (ctor) = TestClass_ctor;
    VMETHOD (dtor) = TestClass_dtor;
END_VTABLE
</pre>

$ cat test.c:
<pre>
#include "TestClass.h"

int main (int argc, char **argv) {

    TestClass tc = CONSTRUCT (TestClass, TestClass, ctor, NULL);

    printf ("name: %s\n", tc->get_name (tc));
    
    tc->set_x (tc, 15);
    CALL (tc, set_y, 22);

    printf ("pos x: %d\n", tc->get_x (tc));
    printf ("pos y: %d\n", tc->get_y (tc));

    tc->dtor (tc);

    return 0;
}
</pre>

$ gcc TestClass.c test.c -lezlib -o test && ./test:
<pre>
in constructor of 'TestClass'
name: Jon Doe
pos x: 15
pos y: 22
in destructor of 'TestClass'
</pre>

Functions
---------

<pre>
/*    ezarray.c    */
EZArray*  ez_array_new ();
void      ez_array_free (EZArray *array);
EZArray*  ez_array_dup (EZArray *array);
void      ez_array_foreach (EZArray *array, ez_array_func foreach);
int       ez_array_index (EZArray *array, ezpointer value);
int       ez_array_push (EZArray *array, ezpointer value);
ezpointer ez_array_pop (EZArray *array);
ezpointer ez_array_remove_index (EZArray *array, int index);
ezpointer ez_array_get_index (EZArray *array, int index);
void      ez_array_set_index (EZArray *array, int index, ezpointer value);

/*    ezbase64.c    */
char* ez_base64_encode (const void *data, size_t size);
void* ez_base64_decode (const char *str);

/*    ezhash.c    */
static int   ez_hash_table_grow (EZHashTable *hash_table);
static uint  ez_hash_table_strhash (const char *str);
EZHashTable* ez_hash_table_new (uint capacity);
void         ez_hash_table_free (EZHashTable *hash_table);
int          ez_hash_table_insert (EZHashTable *hash_table, const char *key, ezpointer value);
ezpointer    ez_hash_table_lookup (EZHashTable *hash_table, const char *key);
ezpointer    ez_hash_table_remove (EZHashTable *hash_table, const char *key);
uint         ez_hash_table_size (EZHashTable *hash_table);
void         ez_hash_table_foreach (EZHashTable *hash_table, ez_hash_func func, ezpointer user_data);
EZList*      ez_hash_table_get_keys (EZHashTable *hash_table);
EZList*      ez_hash_table_get_values (EZHashTable *hash_table);

/*    ezlist.c    */
EZList* ez_list_alloc ();
EZList* ez_list_append (EZList *list, ezpointer data);
EZList* ez_list_last (EZList *list);
EZList* ez_list_first (EZList *list);
size_t  ez_list_length (EZList *list);
void    ez_list_free (EZList *list);
void    ez_list_free_with_data (EZList *list, ez_list_free_func func);
void    ez_list_free_1 (EZList *list);
EZList* ez_list_prepend (EZList *list, ezpointer data);
EZList* ez_list_insert (EZList *list, ezpointer data, int position);
EZList* ez_list_nth (EZList *list, uint n);
EZList* ez_list_remove (EZList *list, ezpointer data);
void    ez_list_foreach (EZList *list, ez_list_func func, ezpointer user_data);

/*    ezqueue.c    */
EZQueue*  ez_queue_alloc ();
void      ez_queue_push (EZQueue **queue, ezpointer data);
ezpointer ez_queue_pop (EZQueue **queue);

/*    ezregex.c    */
const char* ez_regex_error ();
int         ez_regex_error_offset ();
EZRegex*    ez_regex_new (const char *regex);
EZRegex*    ez_regex_new_with_options (const char *regex, int options);
void        ez_regex_free (EZRegex *ezre);
int         ez_regex_substrings (EZRegex *ezre);
bool        ez_regex_match_with_options (EZRegex *ezre, const char *subject, int len, int options);
bool        ez_regex_match_again_with_options (EZRegex *ezre, int options);
char*       ez_regex_get_substring (EZRegex *ezre, int index);

/*    ezstack.c    */
EZStack*  ez_stack_alloc ();
void      ez_stack_push (EZStack **stack, ezpointer data);
ezpointer ez_stack_pop (EZStack **stack);

/*    ezstrfuncs.c    */
char*  ez_strchug (char *string);
char*  ez_strchomp (char *string);
char*  ez_strstrip (char *string);
char*  ez_strchugc (char *string, char c);
char*  ez_strchompc (char *string, char c);
char*  ez_strstripc (char *string, char c);
char*  ez_stpcpy (char *dest, const char *src);
char*  ez_strconcat (const char *string1, ...);
char** ez_strsplit (const char *string, const char *delimiter, int max_tokens);
char*  ez_strjoinv (const char *separator, char **str_array);
void   ez_strfreev (char **str_array);
uint   ez_strv_length (char **str_array);
char*  ez_strjoin (const char *separator, ...);
bool   ez_str_has_suffix (const char *str, const char *suffix);
bool   ez_str_has_prefix (const char *str, const char *prefix);
int    ez_strcmp0 (const char *str1, const char *str2);
char*  ez_strdown (char *string);
char*  ez_strup (char *string);
char*  ez_strreverse (char *string);
int    ez_strcasecmp (const char *s1, const char *s2);
int    ez_strncasecmp (const char *s1, const char *s2, size_t n);
char*  ez_strtruncate (char *string, size_t len);
char*  ez_stroverwrite (char *string, size_t pos, const char *val);
char*  ez_strerase (char *string, size_t pos, size_t len);
char*  ez_strprintf (const char *format, ...);
char*  ez_strreplace (char *string, char *needle, char *replace);

/*    ezstring.c    */
EZString* ez_string_new (const char* init);
EZString* ez_string_sized_new (size_t dfl_size);
EZString* ez_string_append (EZString *string, const char *val);
EZString* ez_string_append_c (EZString *string, const char val);
EZString* ez_string_prepend (EZString *string, const char *val);
EZString* ez_string_prepend_c (EZString *string, const char val);
EZString* ez_string_reverse (EZString *string);
EZString* ez_string_up (EZString *string);
EZString* ez_string_down (EZString *string);
EZString* ez_string_overwrite (EZString *string, size_t pos, const char *val);
EZString* ez_string_erase (EZString *string, size_t pos, size_t len);
EZString* ez_string_printf (const char *format, ...);
EZString* ez_string_append_printf (EZString *string, const char *format, ...);
EZString* ez_string_prepend_printf (EZString *string, const char *format, ...);
EZString* ez_string_truncate (EZString *string, size_t len);
EZString* ez_string_dup (const EZString *string);
bool      ez_string_equal (const EZString *v, const EZString *v2);
uint      ez_string_hash (const EZString *string);
char*     ez_string_free (EZString *string, bool free_segment);
</pre>

Download
--------
No releases yet.

FAQ
---

Q: Why? How? What!?<br />
A: ...

