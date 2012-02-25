lib_LTLIBRARIES = libgbm.la

libgbm_la_SOURCES =	\
	gbm.c		\
	backend.c	\
	common.c

libgbm_la_LIBADD =	\
	@UDEV_LIBS@

libgbm_la_CFLAGS =	\
	@UDEV_CFLAGS@	\
	-D_OS_UNIX=1	\
	-DMODULEDIR='"$(exec_prefix)/lib/gbm"'

extdir = $(includedir)/gbm
ext_HEADERS =		\
	gbm.h		\
	gbmint.h	\
	common_drm.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = gbm.pc
