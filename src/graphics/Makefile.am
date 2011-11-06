lib_LTLIBRARIES = libpanorama_graphics.la
libpanorama_graphics_la_SOURCES = \
ImageFormat.cpp \
PPMLoader.cpp \
XPMLoader.cpp

pkgincludedir = $(includedir)/panorama/graphics
pkginclude_HEADERS = \
ImageFormat.hpp \
GenericImage.hpp \
MaskedImage.hpp \
PPMLoader.hpp \
XPMLoader.hpp

AM_CPPFLAGS = -I$(top_srcdir)/src
libpanorama_graphics_la_LIBADD = $(top_builddir)/src/common/libpanorama_common.la
libpanorama_graphics_la_LDFLAGS = -shared -rpath @prefix@/lib -version-info 1