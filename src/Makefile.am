NULL = 

AM_CPPFLAGS = \
	$(EZLIB_CFLAGS) \
	$(NULL)

AM_CFLAGS = \
	-Wall \
	-D__SOURCE_COMPILE__ \
	$(NULL)

nobase_include_HEADERS = \
	ezlib.h \
	$(NULL)

ezlibincludedir = $(includedir)/ezlib

ezlibinclude_HEADERS = \
    ../config.h \
    ezarray.h \
    ezbase64.h \
    ezclass.h \
    ezexceptions.h \
    ezhash.h \
    ezlist.h \
    ezmacros.h \
    ezmem.h \
    ezqueue.h \
    ezstack.h \
    ezstring.h \
    ezstrfuncs.h \
    eztypes.h \
    class.h \
    talloc.h \
    $(NULL)

if HAVE_PCRE
    ezlibinclude_HEADERS += ezregex.h
endif

#lib_LTLIBRARIES = libezlib.la
#libezlib_la_SOURCES = \
#    talloc.c \
#    class.c \
#    ezarray.c \
#    ezbase64.c \
#    ezexceptions.c \
#    ezhash.c \
#    ezlist.c \
#    ezqueue.c \
#    ezstack.c \
#    ezstring.c \
#    ezstrfuncs.c \
#    $(NULL)
	
#libezlib_la_LDFLAGS = -version-info 0:1:0

#if HAVE_PCRE
#    libezlib_la_SOURCES += ezregex.c
#endif

lib_LIBRARIES = libezlib.a
libezlib_a_SOURCES = \
    talloc.c \
    class.c \
    ezarray.c \
    ezbase64.c \
    ezexceptions.c \
    ezhash.c \
    ezlist.c \
    ezqueue.c \
    ezstack.c \
    ezstring.c \
    ezstrfuncs.c \
	$(NULL)

if HAVE_PCRE
    libezlib_a_SOURCES += ezregex.c
endif

