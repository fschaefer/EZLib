/***************************************************
  Classes and objects in C

  This file makes it easy to implement classes and objects in C. To
  define a class we need to perform three steps:

  Define the class prototype. This is suitable to go in a .h file for
  general use by other code.

  Note all classes extend Object.

  Example::

CLASS(Foo, Object)
    int x;
    int y;

    //This declares a method of a class Foo, called Con returning a
    //Foo object. In other words it is a constructor.
    Foo METHOD(Foo, Con, int x, int y);
    int METHOD(Foo, add);

END_CLASS

Now we need to define some functions for the constructor and
methods. Note that the constuctor is using ALLOCATE_CLASS to allocate
space for the class structures. Callers may call with self==NULL to
force allocation of a new class. Note that we do not call the
constructor of our superclass implicitly here. (Calling the sperclass
constructor is optional, but ALLOCATE_CLASS is not.).

Foo Foo_Con(Foo self,int x,int y) {
  self->x = x;
  self->y = y;

  return self;
};

int Foo_add(Foo self) {
  return (self->x + self->y);
};

Now we need to define the Virtual function table - These are those
functions and attributes which are defined in this class (over its
superclass). Basically these are all those things in the class
definition above, with real function names binding them. (Note that by
convention we preceed the name of the method with the name of the
class):

VIRTUAL(Foo,Object)
   VMETHOD(Con) = Foo_Con;
   VMETHOD(add) = Foo_add;
END_VIRTUAL

We can use inheritance too:

CLASS(Bar, Foo)
   Bar METHOD(Bar, Con, char *something)
END_CLASS

Here Bar extends Foo and defines a new constructor with a different prototype:

VIRTUAL(Bar,Foo)
   VMETHOD(Con) = Bar_Con
END_VIRTUAL

If there is a function which expects a Foo, we will need to over ride
the Foo constructor in the Bar, so the function will not see the
difference between the Foo and Bar:

CLASS(Bar,Foo)
  int bar_attr;
END_CLASS

Foo Bar_Con(Foo self, int x, int y) {
...
}

VIRTUAL(Bar, Foo)
  VMETHOD(super.Con) = Bar_Con
END_VIRTUAL

Note that in this case we are over riding the Con method defined in
Foo while creating derived Bar classes. The notation in the VIRTUAL
table is to use super.Con, because Foo's Con method (the one we are
over riding), can be located by using super.Con inside a Bar object.

Imagine now that in Bar_Con we wish to use methods and attributes
defined in Bar. Since Bar_Con over rides Bar's base class (Foo) it
must have the prototype described above. Since self is of type Foo its
impossible to use self->bar_attr (There is no bar_attr in Foo - its in
Bar).

In this case, we need to make a type cast to convice C that self is
actually a Bar not a Foo:

Foo Bar_Con(Foo self, int x, int y) {
   Bar this = (Bar)self;

   self->bar_attr=1
};

This allows us to access bars attributes.

This is a general oddity with C style classes, which C++ and Java
hide. In C we must always know which class defines which method and
attribute and reference the right class's method. So for example if we
want to call a Bar's add method:

Bar a;

a->super.add()

because add is defined in Bar's super class (Foo). Constract this with
C++ or Java which hide where methods are defined and simply make all
methods appear like they were defined inside the derived class. This
takes a while to get used to but the compiler will ensure that the
references are correct - otherwise things will generally not compile
properly.

This difference can be used for good and bad. It is possible in C to
call the base class's version of the method at any time (despite the
fact it was over ridden). 

For example:

CLASS(Derived, Foo)
      int METHOD(Derived, add);
END_CLASS

VIRTUAL(Derived, Foo)
   VMETHOD(add) = Derived_add
END_VIRTUAL

If d is a Derived object, we can call Foo's version like this:
d->super.add()

But Derived's version is accessed by:
d->add()

Sometimes a derived class may want to over ride the base class's
methods as well, in this case the VIRTUAL section should over ride
super.add as well.

*/

/* EZLIB - Library of useful routines for C programming
 *
 * Copyright (C) 2008 Michael Cohen <scudette@users.sourceforge.net>
 * Modification: Florian Schäfer <florian.schaefer@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef __CLASS_H__
#define __CLASS_H__

#include "ezmacros.h"
#include "talloc.h"

EZ_BEGIN_DECLS

#define CLASS(class, super_class) \
    typedef struct class *class; \
    inline void class ## _init (); \
    void class ## _alloc (class self); \
    extern int __ ## class ## _initialised; \
    extern struct class __ ## class; \
    struct class { \
        struct super_class super; \
        class __class__; \
        super_class __super__;

#define METHOD(class, name, ...) \
    (*name)(class self, ## __VA_ARGS__)

#define ATTRIBUTE(class, attribute, type) \
    type attribute; \
    void (*set_ ## attribute) (class self, type attribute); \
    type (*get_ ## attribute) (class self);

#define ACCESSOR(class, attribute, type) \
    void class ## _set_ ## attribute (class self, type attribute) { \
        self->attribute = attribute; \
    }; \
    type class ## _get_ ## attribute (class self) { \
        return self->attribute; \
    };
   
#define VACCESSOR(class, attribute) \
    self->set_ ## attribute = class ## _set_ ## attribute; \
    self->get_ ## attribute = class ## _get_ ## attribute;

/***************************************************
    This is a convenience macro which may be used if x is really large

***************************************************/
#define CALL(x, method, ...) \
    x->method (x, ## __VA_ARGS__)

#define END_CLASS };

/***************************************************
    This is used to set the classes up for use:

    class_init = checks the class template (__class) to see if it has
    been allocated. otherwise allocates it in the global context.

    class_alloc = Allocates new memory for an instance of the
    class. This is a recursive function calling each super class in
    turn and setting the currently over ridden defaults. So for eample
    suppose this class (foo) derives from bar, we first fill the
    template with bars methods, and attributes. Then we over write
    those with foos methods and attributes.

**********************************************************/

#define VIRTUAL(class, superclass)\
    struct class __ ## class; \
    inline void class ## _alloc (class self); \
    inline void class ## _init () { \
        if (!__ ## class ## _initialised) { \
            class ## _alloc (&__ ## class); \
            __ ## class ## _initialised = 1; \
        }; \
    }; \
    int __ ## class ## _initialised=0;\
    inline void class ## _alloc (class self) { \
        superclass ## _init (); \
        superclass ##_alloc ((superclass)self); \
        ((Object)self)->__class__ = (Object)&__ ## class; \
        self->__class__ = &__ ## class;	\
        ((Object)self)->__super__ = (Object)&__ ## superclass; \
        self->__super__ = &__ ## superclass; \
        ((Object)self)->__size__ = sizeof(struct class); \
        ((Object)self)->__name__ = #class;

#define END_VIRTUAL };

#define IMPLEMENTS(interface) \
    struct interface interface

#define INTERFACE(interface) \
    struct interface {
    
#define END_INTERFACE };

#define VTABLE VIRTUAL

#define END_VTABLE END_VIRTUAL

#define VMETHOD(method) \
    (self)->method
#define VATTR(attribute) \
    (self)->attribute

#define INIT_CLASS(class) \
    if (!__ ## class ## _initialised) { class ## _init (); }

#define NAMEOF(obj) \
    ((Object)obj)->__name__

#define DOCSTRING(obj) \
    ((Object)obj)->__doc__

#define SET_DOCSTRING(string) \
    ((Object)self)->__doc__ = string

/*************************************************************
    This MACRO is used to construct a new Class using a constructor.

    This is done to try and hide the bare (unbound) method names in
    order to prevent name space pollution. (Bare methods may be
    defined as static within the implementation file). This macro
    ensures that class structures are initialised properly before
    calling their constructors.

    We require the following args:
    class - the type of class to make
    virt_class - The class where the method was defined
    constructors - The constructor method to use
    context - a talloc context to use.


    Note that the class and virt_class do not have to be the same if
    the method was not defined in the current class. For example
    suppose Foo extends Bar, but method is defined in Bar but
    inherited in Foo:

    CONSTRUCT(Foo, Bar, super.method, context)

    virt_class is Bar because thats where method was defined.
*************************************************************/

#ifdef EZ_DEBUG

#define CONSTRUCT(class, virt_class, constructor, context, ...) \
    (class) (class ## _init (), virt_class ## _init (),\
   __ ## class.constructor(\
   (virt_class) _talloc_memdup (context, &__ ## class, sizeof (struct class), \
    __location__ "(" #class ")"), ## __VA_ARGS__))
    
#else

#define CONSTRUCT(class, virt_class, constructor, context, ...) \
    (class)( class ## _init (), virt_class ## _init (), \
        __ ## class.constructor ( \
            (virt_class) talloc_memdup (context, &__ ## class, sizeof (struct class)), \
            ## __VA_ARGS__))

#endif

/** Finds the size of the class in x */
#define CLASS_SIZE(class) \
    ((Object)class)->__size__

typedef struct Object *Object;

struct Object {
    //A reference to a class instance - this is useful to be able to
    //tell which class an object really belongs to:
    Object __class__;

    //And its super class:
    Object __super__;

    char *__name__;

    /** Objects may have a doc string associated with them. */
    char *__doc__;

    //How large the class is:
    int __size__;
};

#define GETCLASS(class) \
    (Object)&__ ## class

// Returns true if the obj belongs to the class
#define ISINSTANCE(obj, class) \
    (((Object)obj)->__class__ == GETCLASS (class))

// This is a string comparison version of ISINSTANCE which works
// across different shared objects.
#define ISNAMEINSTANCE(obj, class) \
    (obj && !strcmp (class, NAMEOF (obj)))

// We need to ensure that class was properly initialised:
#define ISSUBCLASS(obj, class) \
    issubclass ((Object)obj, (Object)&__ ## class, &class ## _init)

#define CLASSOF(obj) \
    ((Object)obj)->__class__

inline void Object_init ();
inline void Object_alloc (Object self);

extern struct Object __Object;

int issubclass (Object obj, Object class, void (init)());

EZ_END_DECLS

#endif /* __CLASS_H__ */
