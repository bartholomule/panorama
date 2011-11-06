# Add new tests to this
BUILT_TESTS = \
CopyCounterTestCases \
CloneableTestCases \
StringDumpableTestCases \
RasterTestCases \
Coord2TestCases \
Coord3TestCases \
Vector2TestCases \
Vector3TestCases \
Point2TestCases \
Point3TestCases \
RGBColorTestCases \
RGBAColorTestCases \
ONBTestCases \
FrameTestCases \
CapabilitiesTestCases \
IntervalTestCases \
Line2TestCases \
Line3TestCases \
ImageTestCases

# Put new test source lists here.
CopyCounterTestCases_SOURCES = CopyCounterTestCases.cpp
CloneableTestCases_SOURCES = CloneableTestCases.cpp
StringDumpableTestCases_SOURCES = StringDumpableTestCases.cpp
RasterTestCases_SOURCES = RasterTestCases.cpp
Coord2TestCases_SOURCES = Coord2TestCases.cpp
Coord3TestCases_SOURCES = Coord3TestCases.cpp
Vector2TestCases_SOURCES = Vector2TestCases.cpp
Vector3TestCases_SOURCES = Vector3TestCases.cpp
Point2TestCases_SOURCES = Point2TestCases.cpp
Point3TestCases_SOURCES = Point3TestCases.cpp
RGBColorTestCases_SOURCES = RGBColorTestCases.cpp
RGBAColorTestCases_SOURCES = RGBAColorTestCases.cpp
ONBTestCases_SOURCES = ONBTestCases.cpp
FrameTestCases_SOURCES = FrameTestCases.cpp
CapabilitiesTestCases_SOURCES = CapabilitiesTestCases.cpp
IntervalTestCases_SOURCES = IntervalTestCases.cpp
Line2TestCases_SOURCES = Line2TestCases.cpp
Line3TestCases_SOURCES = Line3TestCases.cpp
ImageTestCases_SOURCES = ImageTestCases.cpp

# Needed for a new automake
CopyCounterTestCases_LDFLAGS =
CloneableTestCases_LDFLAGS =
StringDumpableTestCases_LDFLAGS =
RasterTestCases_LDFLAGS =
Coord2TestCases_LDFLAGS =
Coord3TestCases_LDFLAGS =
Vector2TestCases_LDFLAGS =
Vector3TestCases_LDFLAGS =
Point2TestCases_LDFLAGS =
Point3TestCases_LDFLAGS =
RGBColorTestCases_LDFLAGS =
RGBAColorTestCases_LDFLAGS =
ONBTestCases_LDFLAGS =
FrameTestCases_LDFLAGS =
CapabilitiesTestCases_LDFLAGS =
IntervalTestCases_LDFLAGS =
Line2TestCases_LDFLAGS =
Line3TestCases_LDFLAGS =
ImageTestCases_LDFLAGS =

#
# Everything below here should normally be ignored
#
noinst_LTLIBRARIES = libpanorama_test.la

libpanorama_test_la_SOURCES = \
CopyCounter.cpp \
CopyCounter.hpp

BLOCXX_LIBDIR = $(top_builddir)/src/blocxx
BLOCXX_TEST_LIBDIR = $(top_builddir)/src/blocxx_test

COMMON_PROJECT_LIBS = \
-L$(BLOCXX_LIBDIR) -lblocxx \
-L$(top_builddir)/src/common -lpanorama_common \
$(top_builddir)/test/unit/libpanorama_test.la

BLOCXX_TEST_LIBS = \
-L$(BLOCXX_TEST_LIBDIR) -lblocxx_test

COMMON_EXTERNAL_LIBS = \
$(BLOCXX_TEST_LIBS)

TESTS = $(BUILT_TESTS)

# For each program we run as a test, execute it with this script.
TESTS_ENVIRONMENT = $(top_builddir)/src/blocxx_export/test/unit/set_test_libpath.sh

INCLUDES = \
-I$(top_srcdir)/src

# A hack to include the specific include flags for a particular target in the
# includes.  The need for hacks like this is part of why automake sucks so bad.
AM_CPPFLAGS = $($(@:%.o=%)_INCLUDES)

noinst_PROGRAMS = $(PROGS) $(BUILT_TESTS)

all-local: $(BUILT_TESTS)

include $(top_srcdir)/Makefile-executable.inc
