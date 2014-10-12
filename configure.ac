AC_PREREQ(2.59)
AC_INIT(gjournal, 0.1)

AC_CONFIG_AUX_DIR([scripts])

AC_CANONICAL_SYSTEM

AM_INIT_AUTOMAKE([subdir-objects])

AC_CONFIG_MACRO_DIR([m4])

AC_PROG_CXX

AC_LANG(C++)

AX_CXX_COMPILE_STDCXX_11

AM_SILENT_RULES([yes])

pkg_modules="gtkmm-3.0"

PKG_CHECK_MODULES(PACKAGE, [$pkg_modules])
AC_SUBST(PACKAGE_CFLAGS)
AC_SUBST(PACKAGE_LDFLAGS)
AC_SUBST(PACKAGE_LIBS)

AC_CHECK_PROG([DOXYGEN], [doxygen], [doxygen])
AM_CONDITIONAL([HAVE_DOXYGEN], [test "x$doxygen" != "xno"])

AC_CONFIG_FILES(Makefile
                doc/Doxyfile
                doc/Makefile
                src/Makefile
                ui/Makefile)

AC_OUTPUT
