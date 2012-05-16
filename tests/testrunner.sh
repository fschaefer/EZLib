#!/bin/bash
# testrunner.sh
#
# Copyright (C) 2006-2008  Jürg Billeter
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
#
# Author:
#   Jürg Billeter <j@bitron.ch>
# Modification:
#   Florian Schäfer <florian.schaefer@gmail.com>

builddir=$PWD
topbuilddir=$builddir/../src
srcdir=`dirname $0`
topsrcdir=$srcdir/../src
headerdir=
exe=$EXEEXT

# make sure we detect failed test cases
set -o pipefail

CC="gcc"
CFLAGS="-O0 -g3 -D__SOURCE_TEST__"
LDLIBS="../src/libezlib.a"

CODE=0

if [ "$1" = "" ]
then
    SOURCES="*.c"
else
    SOURCES="$@"
fi

HAVE_PCRE=`grep 'HAVE_PCRE 1' ../config.h -o`

for testcasesource in $SOURCES
do
    testsrc=${testcasesource/.c/}
    testbuild=`basename "$testsrc"`
    

    if [ "$testbuild" = "regex" ]
    then
        if [ "$HAVE_PCRE" = "" ]
        then
            continue
        else
            LDLIBS="$LDLIBS -lpcre"
        fi
    fi
    
    if ! $CC $CFLAGS $testbuild.c $LDLIBS -o $testbuild > $testbuild.err 2>&1 
    then
        echo "FAILED: $testbuild"
        echo "ERROR: Compiling" $testbuild.c
        cat $testbuild.err
        CODE=1
        continue
    fi
    if ./$testbuild 2>&1 | tee $testbuild.err | cmp -s $testsrc.exp
    then
        rm $testbuild$exe $testbuild.err 2>&1
    else
        echo "FAILED: $testbuild"
        echo "ERROR: test failed. This is the difference between" $testbuild.exp "and" $testbuild.err
        diff -u $testbuild.exp $testbuild.err
        CODE=1
    fi
    
    if [ "$CODE" = "0" ]
    then
        echo "OK: $testbuild"
    fi
done

if [ "$CODE" = "0" ]
then
    echo "SUCCESS: all tests passed."
fi

exit $CODE
