ACLOCAL_AMFLAGS = -I m4
AM_CFLAGS = -O3
AM_LDFLAGS = 

bin_PROGRAMS = litelog4cpp
sbin_PROGRAMS = litelog4cpp

litelog4cpp_SOURCES = litelogSample.c
litelog4cpp_LDADD = liblitelog4cpp.la

lib_LTLIBRARIES = liblitelog4cpp.la
liblitelog4cpp_la_SOURCES = litelog4cpp.cpp litelog4cpp.h
liblitelog4cpp_la_LDFLAGS = -version-info $(LIBLITELOG_LIBRARY_VERSION) -release $(LIBLITELOG_RELEASE_VERSION)



