lib_LTLIBRARIES = libpanorama_common.la
libpanorama_common_la_SOURCES = \
Cloneable.cpp \
StringDumpable.cpp \
BaseClass.cpp

pkgincludedir = $(includedir)/panorama/common
pkginclude_HEADERS = \
Cloneable.hpp \
StringDumpable.hpp \
BaseClass.hpp \
Raster.hpp \
GenericCoord2.hpp \
Types.hpp

AM_CPPFLAGS = -I$(top_srcdir)/src
libpanorama_common_la_LIBADD =
libpanorama_common_la_LDFLAGS = -shared -rpath @prefix@/lib -version-info 1
