#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(litelog-devel, 0.0.1, dukim@makequest.com)
AC_CONFIG_FILES([litelog4cpp.pc])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE
AM_PROG_LIBTOOL

# Checks for programs.
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_CONFIG_MACRO_DIR([m4])
AC_PROG_RANLIB

# Checks for libraries.

# Extra definitions.
LIBLITELOG_LIBRARY_VERSION=1:0:0
LIBLITELOG_RELEASE_VERSION=1
AC_SUBST(LIBLITELOG_LIBRARY_VERSION)
AC_SUBST(LIBLITELOG_RELEASE_VERSION)

# Checks for header files.
AC_CHECK_HEADERS([netinet/in.h stdlib.h string.h sys/socket.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([gethostname strdup])

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
