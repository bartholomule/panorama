#define PROVIDE_AUTO_TEST_MAIN
#include "blocxx_test/CppUnit/AutoTest.hpp"
#include "panorama/common/Types.hpp"

using namespace panorama;

double DELTA = 0.00001;
#define ASSERT_EQUAL(a, b) unitAssertDoublesEqual((a), (b), DELTA)
#define ASSERT_VECTORS_EQUAL(a, b) ASSERT_EQUAL((a).x(), (b).x()); ASSERT_EQUAL((a).y(), (b).y())

AUTO_UNIT_TEST(line3_string_convert)
{
	Point3 o(1,2,3);
	Vector3 d(0,1,0);
	Interval l(10,20);
	Line3 line(o, d, l);
	unitAssertEquals("|(1,2,3),<0,1,0>,[10,20]|", panorama::toString(line));
	unitAssertEquals("Line\n{\n  origin = (1,2,3);\n  direction = <0,1,0>;\n  limits = [10,20];\n}", toStringAsMembers(line));
}

AUTO_UNIT_TEST(line3_minmax)
{
	Point3 o(1,2,3);
	Vector3 d(0,1,0);
	Interval l(10,20);
	Line3 line(o, d, l);

	unitAssertEquals(false, line.infinite());
	ASSERT_VECTORS_EQUAL(o, line.origin());
	ASSERT_VECTORS_EQUAL(d, line.direction());
	ASSERT_VECTORS_EQUAL(Point3(1,12,3), line.minimum());
	ASSERT_VECTORS_EQUAL(Point3(1,22,3), line.maximum());
	ASSERT_VECTORS_EQUAL(Point3(1,2,3), line.point_at(0)); // Not inside the line due to limits.
	unitAssertEquals(false, line.inside(0));
	ASSERT_VECTORS_EQUAL(Point3(1,22,3), line.point_at(20));
}

// FIXME! More tests
