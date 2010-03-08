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
ONBTestCases \
FrameTestCases \
CapabilitiesTestCases \
IntervalTestCases \
Line2TestCases \
Line3TestCases

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
ONBTestCases_SOURCES = ONBTestCases.cpp
FrameTestCases_SOURCES = FrameTestCases.cpp
CapabilitiesTestCases_SOURCES = CapabilitiesTestCases.cpp
IntervalTestCases_SOURCES = IntervalTestCases.cpp
Line2TestCases_SOURCES = Line2TestCases.cpp
Line3TestCases_SOURCES = Line3TestCases.cpp

#
# Everything below here should normally be ignored
#
noinst_LTLIBRARIES = libpanorama_test.la

libpanorama_test_la_SOURCES = \
CopyCounter.cpp \
CopyCounter.hpp

COMMON_PROJECT_LIBS = \
-L$(top_builddir)/src/blocxx -lblocxx \
-L$(top_builddir)/src/common -lpanorama_common \
-L. -lpanorama_test

# CppUnit is listed here because as a static object, it must occur *AFTER* the
# objects that use it.
CPPUNIT_DIRECTORY = src/blocxx_export/test/CppUnit
COMMON_EXTERNAL_LIBS = \
-L$(top_builddir)/$(CPPUNIT_DIRECTORY) -lCppUnit

TESTS = $(BUILT_TESTS)

# For each program we run as a test, execute it with this script.
TESTS_ENVIRONMENT = $(top_builddir)/src/blocxx_export/test/unit/set_test_libpath.sh

INCLUDES = \
-I$(top_srcdir)/$(CPPUNIT_DIRECTORY) \
-I$(top_srcdir)/src

# A hack to include the specific include flags for a particular target in the
# includes.  The need for hacks like this is part of why automake sucks so bad.
AM_CPPFLAGS = $($(@:%.o=%)_INCLUDES)

noinst_PROGRAMS = $(PROGS) $(BUILT_TESTS)

all-local: $(BUILT_TESTS)

include $(top_srcdir)/Makefile-executable.inc
