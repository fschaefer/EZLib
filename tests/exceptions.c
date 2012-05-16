#define EZ_DEBUG (1)

#include "../src/ezlib.h"
#include <fcntl.h>

enum _exception {
    E_NOEXCEPTION,
    E_GENERIC,
    E_OVERFLOW,
    E_UNDERFLOW,
    E_IOEXCEPTION,
    E_FILEIOEXCEPTION,
    E_NOMEMORY
};

static char *_exception_descriptions[] = {
    "No Exception",
    "Generic Exception",
    "Overflow Exception",
    "Underflow Exception",
    "IO Exception",
    "File IO Exception",
    "No Memory Exception"
};

#define reason(exception) \
    _exception_descriptions[exception]

#define new CONSTRUCT
#define name_of NAMEOF
#define call CALL

CLASS (TestClass, Object)
    int fd;
    TestClass METHOD (TestClass, ctor);
    void METHOD (TestClass, dtor);
    
    void METHOD (TestClass, open_file, char *filename);
END_CLASS

TestClass TestClass_ctor (TestClass self) {
    printf ("%s '%s'\n", "in constructor of", NAMEOF (self));
    return self;
}

void TestClass_dtor (TestClass self) {
    printf ("%s '%s'\n", "in destructor of", NAMEOF (self));
}

void TestClass_open_file (TestClass self, char *filename) {
    printf ("%s '%s'\n", "in open_file of", NAMEOF (self));
    
    self->fd = open (filename, O_RDONLY);
    if (self->fd < 0) {
        throw (E_FILEIOEXCEPTION);
    } else {
        close (self->fd);
    }
}

VIRTUAL (TestClass, Object)
    VMETHOD (ctor) = TestClass_ctor;
    VMETHOD (dtor) = TestClass_dtor;
    VMETHOD (open_file) = TestClass_open_file;
END_VIRTUAL

int main (int argc, char **argv) {
    printf ("%s\n", "Exceptions Test:");
    
    printf ("%s\n", "new TestClass");
    TestClass tc = new (TestClass, TestClass, ctor, NULL);
    try {
        printf ("calling open_file with filename %s on %s\n", "./exceptions.c", NAMEOF (tc));
        call (tc, open_file, "./exceptions.c");
        
        printf ("calling open_file with filename %s on %s\n", "./exceptions.foobar", NAMEOF (tc));
        call (tc, open_file, "./exceptions.foobar");
        
    } catch (E_FILEIOEXCEPTION) {
        printf ("catching exception %d\n", E_FILEIOEXCEPTION);
        printf ("reason for exception '%s'\n", reason (E_FILEIOEXCEPTION));
    }
    
    printf ("%s\n", "calling Destructor");
    call (tc, dtor);
    ez_free (tc);

    return 0;
}
