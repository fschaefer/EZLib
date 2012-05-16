AC_INIT([ezlib], [0.1.0], [florian.schaefer@gmail.com], [ezlib])

AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
AM_MAINTAINER_MODE

AM_CONFIG_HEADER(config.h)

dnl Checking for va_copy availability
AC_MSG_CHECKING([for va_copy])
AC_TRY_LINK([#include <stdarg.h>
va_list ap1,ap2;], [va_copy(ap1,ap2);],
have_va_copy=yes,
have_va_copy=no)
AC_MSG_RESULT($have_va_copy)
if test x"$have_va_copy" = x"yes"; then
    AC_DEFINE(HAVE_VA_COPY,1,[Whether va_copy() is available])
else
    AC_MSG_CHECKING([for __va_copy])
    AC_TRY_LINK([#include <stdarg.h>
    va_list ap1,ap2;], [__va_copy(ap1,ap2);],
    have___va_copy=yes,
    have___va_copy=no)
    AC_MSG_RESULT($have___va_copy)
    if test x"$have___va_copy" = x"yes"; then
        AC_DEFINE(HAVE___VA_COPY,1,[Whether __va_copy() is available])
    fi
fi

AC_CHECK_LIB(pcre, pcre_compile, [have_pcre="yes"], [])

AC_ARG_ENABLE(pcre, AS_HELP_STRING(--enable-pcre, enable regex support),,
 [
 have_pcre="yes"
 ]
)

AM_CONDITIONAL(HAVE_PCRE, [test x"$have_pcre" = x"yes"])
if test x"$have_pcre" = x"yes"; then
    AC_DEFINE(HAVE_PCRE,1,[Whether pcre is available])
fi

AC_ISC_POSIX
AC_PROG_CC
AM_PROG_CC_STDC
AC_HEADER_STDC

AM_PROG_LIBTOOL

AC_OUTPUT([
Makefile
src/Makefile
])
