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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */
 
#include "class.h"

// Noone should instantiate Object directly. this should be already
// allocated therefore:

inline void Object_alloc (Object self) {
    self->__class__ = &__Object;
    self->__super__ = NULL;
}

inline void Object_init () {
    Object_alloc (&__Object);
}

struct Object __Object = {
    .__class__ = &__Object,
    .__super__ = &__Object,
    .__name__ = "Object",
    .__size__ = sizeof (struct Object)
};

int issubclass (Object obj, Object class, void (init)()) {

    init ();

    obj = obj->__class__;
    while (1) {
        if (obj == class->__class__)
            return 1;

        obj = obj->__super__;

        if (obj == &__Object || obj == NULL)
            return 0;
    }
}
