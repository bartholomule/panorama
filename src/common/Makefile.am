lib_LTLIBRARIES = libpanorama_common.la
libpanorama_common_la_SOURCES = \
BaseClass.cpp \
Capabilities.cpp \
Cloneable.cpp \
StringDumpable.cpp \
TextUtils.cpp

pkgincludedir = $(includedir)/panorama/common
pkginclude_HEADERS = \
Config.hpp \
BaseClass.hpp \
Capabilities.hpp \
Cloneable.hpp \
GenericCoord2.hpp \
GenericCoord3.hpp \
GenericVector2.hpp \
GenericVector3.hpp \
GenericPoint2.hpp \
GenericPoint3.hpp \
GenericRGBColor.hpp \
GenericRGBAColor.hpp \
GenericONB.hpp \
GenericFrame.hpp \
GenericInterval.hpp \
GenericLine.hpp \
GenericLine2.hpp \
Raster.hpp \
StringDumpable.hpp \
TextUtils.hpp \
Types.hpp


AM_CPPFLAGS = -I$(top_srcdir)/src
libpanorama_common_la_LIBADD =
libpanorama_common_la_LDFLAGS = -shared -rpath @prefix@/lib -version-info 1
