AC_PREREQ(2.59)
AC_INIT(gjournal, 0.1)

AC_CONFIG_AUX_DIR([scripts])

AC_CANONICAL_SYSTEM

AM_INIT_AUTOMAKE([subdir-objects -Wno-portability])

AC_CONFIG_MACRO_DIR([m4])

AC_PROG_CC
AC_PROG_CXX

AC_LANG(C++)

AX_CXX_COMPILE_STDCXX_11

AM_SILENT_RULES([yes])

AC_ARG_VAR([GLIB_COMPILE_RESOURCES],[the glib-compile-resources programme])
AC_PATH_PROG([GLIB_COMPILE_RESOURCES],[glib-compile-resources],[])
if test -z "$GLIB_COMPILE_RESOURCES"; then
  AC_MSG_ERROR([glib-compile-resources not found])
fi

pkg_cpp_modules="gtkmm-3.0 >= 3.14 libxml++-2.6"
pkg_cc_modules="gio-2.0"

PKG_CHECK_MODULES(PACKAGE_CPP, [$pkg_cpp_modules])
PKG_CHECK_MODULES(PACKAGE_CC, [$pkg_cc_modules])

AC_SUBST(PACKAGE_CPP_CFLAGS)
AC_SUBST(PACKAGE_CPP_LDFLAGS)
AC_SUBST(PACKAGE_CPP_LIBS)

AC_SUBST(PACKAGE_CC_CFLAGS)
AC_SUBST(PACKAGE_CC_LDFLAGS)
AC_SUBST(PACKAGE_CC_LIBS)

AC_CHECK_PROG([DOXYGEN], [doxygen], [doxygen])
AM_CONDITIONAL([HAVE_DOXYGEN], [test "x$doxygen" != "xno"])

AC_CONFIG_FILES(Makefile
                doc/Doxyfile
                doc/Makefile
                src/Makefile
                ui/Makefile)

AC_OUTPUT
