#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([cmics], [2.0.1], [Fork on GitHub])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_SRCDIR([src/url.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
PKG_CHECK_MODULES([CURL], [libcurl])
PKG_CHECK_MODULES([CURSES], [ncurses])
AC_SUBST([CURL_CFLAGS])
AC_SUBST([CURL_LIBS])
AC_SUBST([CURSES_CFLAGS])
AC_SUBST([CURSES_LIBS])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([mkdir regcomp])

AC_CONFIG_FILES([
  Makefile
  src/Makefile
])

AC_OUTPUT
