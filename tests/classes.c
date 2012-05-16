#include "../src/ezlib.h"

#define new CONSTRUCT
#define name_of NAMEOF
#define call CALL

CLASS (TestClass, Object)
    TestClass METHOD (TestClass, ctor);
    void METHOD (TestClass, dtor);
END_CLASS

TestClass TestClass_ctor (TestClass self) {
    printf ("%s '%s'\n", "in constructor of", NAMEOF (self));
    return self;
}

void TestClass_dtor (TestClass self) {
    printf ("%s '%s'\n", "in destructor of", NAMEOF (self));
}

VTABLE (TestClass, Object)
    VMETHOD (ctor) = TestClass_ctor;
    VMETHOD (dtor) = TestClass_dtor;
END_VTABLE

INTERFACE (ITest)
    void METHOD (void*, print);
END_INTERFACE

CLASS (DerivedTestClass, TestClass)
    IMPLEMENTS (ITest);
    ATTRIBUTE (DerivedTestClass, pos, int);
    DerivedTestClass METHOD (DerivedTestClass, ctor);
    void METHOD (DerivedTestClass, dtor);
END_CLASS

DerivedTestClass DerivedTestClass_ctor (DerivedTestClass self) {
    printf ("%s '%s'\n", "explicit calling constructor of", "__super__");
    self->super.ctor (self->__super__);
    
    printf ("%s '%s'\n", "in constructor of", NAMEOF (self));
    return self;
}

void DerivedTestClass_dtor (DerivedTestClass self) {
    printf ("%s '%s'\n", "explicit calling destructor of", "__super__");
    self->super.dtor (self->__super__);
    
    printf ("%s '%s'\n", "in destructor of", NAMEOF (self));
}

void ITest_print (DerivedTestClass self) {
    
    printf ("%s '%s'\n", "ITest_print of:", NAMEOF (self));
}

ACCESSOR (DerivedTestClass, pos, int);

VIRTUAL (DerivedTestClass, TestClass)
    VMETHOD (ITest.print) = ITest_print;
    VACCESSOR (DerivedTestClass, pos);
    VMETHOD (ctor) = DerivedTestClass_ctor;
    VMETHOD (dtor) = DerivedTestClass_dtor;
END_VIRTUAL

int main (int argc, char **argv) {
    printf ("%s\n", "Classes Test:");
    
    printf ("%s\n", "new TestClass");
    TestClass tc = new (TestClass, TestClass, ctor, NULL);
    
    printf ("%s\n", "calling Destructor");
    call (tc, dtor);
    ez_free (tc);

    printf ("%s\n", "new DerivedTestClass");    
    DerivedTestClass dtc = new (DerivedTestClass, DerivedTestClass, ctor, NULL);
    printf ("%s\n", "calling Interface Method");
    dtc->ITest.print (dtc);
    
    printf ("class of: %s\n", NAMEOF (dtc));

    printf ("Testing auto accessors of: %s\n", NAMEOF (dtc));
    call (dtc, set_pos, 33);
    printf ("attribute 'pos' value is: %d\n", call (dtc, get_pos));

    call (dtc, dtor);
    ez_free (dtc);
    
    return 0;
}

