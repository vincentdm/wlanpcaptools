#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([wlan-tools],[0.0.2], [vincentdm@gmail.com])
AC_CONFIG_HEADERS([common/config.h])

AM_INIT_AUTOMAKE

LT_INIT

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lpcap':
AC_CHECK_LIB([pcap], [main])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 libwlanmergecap/Makefile
                 libwlanmergecap/include/Makefile
                 libwlanmergecap/src/Makefile
                 libwlanpcap/Makefile
                 libwlanpcap/include/Makefile
                 libwlanpcap/src/Makefile
                 wlanmergecap/Makefile
                 wlanmergecap/src/Makefile])
AC_OUTPUT
