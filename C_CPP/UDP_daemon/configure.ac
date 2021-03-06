#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([stationd],[0.1.0])
AM_INIT_AUTOMAKE([-Wall])
AC_CONFIG_SRCDIR([src/server.h])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_SEARCH_LIBS([i2c_smbus_read_word_data], [i2c], [], [AC_MSG_ERROR([I2C library not found])])
AC_SEARCH_LIBS([pow], [m], [], [AC_MSG_ERROR([Math library not found])])
AC_SEARCH_LIBS([pthread_create], [pthread], [], [AC_MSG_ERROR([pthread library not found])])

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h fcntl.h netdb.h stdint.h stdlib.h string.h sys/ioctl.h sys/socket.h syslog.h unistd.h pthread.h i2c.h math.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_INT32_T
AC_TYPE_PID_T
AC_TYPE_UINT16_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_FORK
AC_CHECK_FUNCS([alarm memset pow socket strcspn strerror])

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
