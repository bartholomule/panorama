lib_LTLIBRARIES = libpanorama_common.la
libpanorama_common_la_SOURCES = \
Cloneable.cpp \
StringDumpable.cpp \
BaseClass.cpp \
Capabilities.cpp

pkgincludedir = $(includedir)/panorama/common
pkginclude_HEADERS = \
Config.h \
Cloneable.hpp \
StringDumpable.hpp \
BaseClass.hpp \
Raster.hpp \
GenericCoord2.hpp \
Types.hpp \
GenericCoord2.hpp \
GenericCoord3.hpp \
GenericVector2.hpp \
GenericVector3.hpp \
GenericPoint2.hpp \
GenericPoint3.hpp \
GenericONB.hpp \
GenericFrame.hpp \
Capabilities.hpp

AM_CPPFLAGS = -I$(top_srcdir)/src
libpanorama_common_la_LIBADD =
libpanorama_common_la_LDFLAGS = -shared -rpath @prefix@/lib -version-info 1
