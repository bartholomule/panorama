#define PROVIDE_AUTO_TEST_MAIN
#include "AutoTest.hpp"
#include "panorama/common/Types.hpp"

using namespace panorama;

double DELTA = 0.00001;
#define ASSERT_EQUAL(a, b) unitAssertDoublesEqual((a), (b), DELTA)
#define ASSERT_VECTORS_EQUAL(a, b) ASSERT_EQUAL((a).x(), (b).x()); ASSERT_EQUAL((a).y(), (b).y())

AUTO_UNIT_TEST(line2_string_convert)
{
	Point2 o(0,0);
	Vector2 d(0,1);
	Interval l(10,20);
	Line2 line(o, d, l);
	unitAssertEquals("|(0,0),<0,1>,[10,20]|", panorama::toString(line));
	unitAssertEquals("Line\n{\n  origin = (0,0);\n  direction = <0,1>;\n  limits = [10,20];\n}", toStringAsMembers(line));
}

AUTO_UNIT_TEST(line2_minmax)
{
	Point2 o(0,0);
	Vector2 d(0,1);
	Interval l(10,20);
	Line2 line(o, d, l);

	unitAssertEquals(false, line.infinite());
	ASSERT_VECTORS_EQUAL(o, line.origin());
	ASSERT_VECTORS_EQUAL(d, line.direction());
	ASSERT_VECTORS_EQUAL(Point2(0,10), line.minimum());
	ASSERT_VECTORS_EQUAL(Point2(0,20), line.maximum());
	ASSERT_VECTORS_EQUAL(Point2(0,0), line.point_at(0)); // Not inside the line due to limits.
	unitAssertEquals(false, line.inside(0));
	ASSERT_VECTORS_EQUAL(Point2(0,20), line.point_at(20));
}

// FIXME! More tests
