#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([1.00])
AC_INIT(LibTwitter,0.1,neozaru@mailoo.org)
AC_CONFIG_SRCDIR([src/Twitter/JSON_Parser.cpp])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([subdir-objects])
LT_INIT

AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

#LT
# Used for making libraries
AM_PROG_LIBTOOL
AC_PROG_MAKE_SET

# Remove is libcurl is statically linked
PKG_CHECK_MODULES([libcurl],[libcurl])

PKG_CHECK_MODULES([libtwitterc],[libtwitter-core])
PKG_CHECK_MODULES([jsoncpp],[jsoncpp])

# Checks for header files.
AC_CHECK_HEADERS([inttypes.h limits.h memory.h stdint.h stdlib.h string.h sys/socket.h sys/time.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
		src/Makefile])
AC_OUTPUT
