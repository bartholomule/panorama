#define PROVIDE_AUTO_TEST_MAIN
#include "AutoTest.hpp"
#include "panorama/common/Types.hpp"

using namespace panorama;

double DELTA = 0.00001;
#define ASSERT_EQUAL(a, b) unitAssertDoublesEqual((a), (b), DELTA)

AUTO_UNIT_TEST(point2_string_convert)
{
	// Test the tag-based string conversion operations -- we don't want
	// inheritance or virtual functions.
	Point2 vec(1,2);

	unitAssertEquals("(1,2)", vec.toString());
	unitAssertEquals("(1,2)", panorama::toString(vec));
	unitAssertEquals("Point2\n{\n  x = 1;\n  y = 2;\n}", toStringAsMembers(vec));
}

AUTO_UNIT_TEST(point2_reinterpret)
{
	// This test proves that the structure is packed and double-aligned.  If
	// this fails anywhere then changes will need to be made to the structure.
	Point2 vecs[2];
	unitAssertEquals(sizeof(double) * 2, sizeof(vecs[0]));
	unitAssertEquals(sizeof(double) * 4, sizeof(vecs));

	vecs[0][0] = 1;
	vecs[0][1] = 2;
	vecs[1][0] = 10;
	vecs[1][1] = 20;

	double* cp = (double*)&vecs[0];
	ASSERT_EQUAL(1, cp[0]);
	ASSERT_EQUAL(2, cp[1]);
	ASSERT_EQUAL(10, cp[2]);
	ASSERT_EQUAL(20, cp[3]);

	cp[1] = 4;
	ASSERT_EQUAL(1, vecs[0].x());
	ASSERT_EQUAL(4, vecs[0].y());
	ASSERT_EQUAL(10, vecs[1].x());
	ASSERT_EQUAL(20, vecs[1].y());
}

AUTO_UNIT_TEST(point2_set_and_get)
{
	Point2 c(0,1);
	const Point2 c2(c);

	// Non-const getters.
	ASSERT_EQUAL(0, c.x());
	ASSERT_EQUAL(0, c[Point2::X]);
	ASSERT_EQUAL(1, c.y());
	ASSERT_EQUAL(1, c[Point2::Y]);

	// Const getters
	ASSERT_EQUAL(0, c2.x());
	ASSERT_EQUAL(0, c2[Point2::X]);
	ASSERT_EQUAL(1, c2.y());
	ASSERT_EQUAL(1, c2[Point2::Y]);

	// Setters.
	c.set(4,5);
	ASSERT_EQUAL(4, c.x());
	ASSERT_EQUAL(5, c.y());
	c.y() = 10;
	ASSERT_EQUAL(10, c[1]);
	c.x() = 3;
	ASSERT_EQUAL(3, c[0]);
	c[0] = 100;
	ASSERT_EQUAL(100, c.x());
	c[1] = 63;
	ASSERT_EQUAL(63, c.y());
}

AUTO_UNIT_TEST(point2_member_operators)
{
	Point2 vecA(2,5);
	Point2 vecB(10,20);
	// =
	{
		Point2 vecC;
		vecC = vecA;
		ASSERT_EQUAL(2, vecC.x());
		ASSERT_EQUAL(5, vecC.y());

		Point2 vecD;
		vecC = vecD = vecB;
		ASSERT_EQUAL(10, vecD.x());
		ASSERT_EQUAL(20, vecD.y());
		ASSERT_EQUAL(10, vecC.x());
		ASSERT_EQUAL(20, vecC.y());
	}
	// +=
	{
		Point2 vecC = vecA;
		vecC += Vector2(vecC.getcoord());
		ASSERT_EQUAL(4, vecC.x());
		ASSERT_EQUAL(10, vecC.y());

		vecC += Vector2(vecB.getcoord());
		ASSERT_EQUAL(14, vecC.x());
		ASSERT_EQUAL(30, vecC.y());
	}
	// -=
	{
		Point2 vecC = vecA;
		vecC -= Vector2(vecC.getcoord());
		ASSERT_EQUAL(0, vecC.x());
		ASSERT_EQUAL(0, vecC.y());

		vecC -= Vector2(vecB.getcoord());
		ASSERT_EQUAL(-10, vecC.x());
		ASSERT_EQUAL(-20, vecC.y());

		vecC -= Vector2(vecA.getcoord());
		ASSERT_EQUAL(-12, vecC.x());
		ASSERT_EQUAL(-25, vecC.y());
	}
}

AUTO_UNIT_TEST(point2_non_member_operators)
{
	Point2 vecA(2,5);
	Point2 vecB(10,20);

	// +
	{
		Point2 vecC = vecA + Vector2(vecA.getcoord()) + Vector2(vecA.getcoord());
		ASSERT_EQUAL(6, vecC.x());
		ASSERT_EQUAL(15, vecC.y());

		Point2 vecD = vecC + Vector2(vecB.getcoord());
		ASSERT_EQUAL(16, vecD.x());
		ASSERT_EQUAL(35, vecD.y());
	}
	// -
	{
		Point2 vecC = vecA - Vector2(vecA.getcoord()) - Vector2(vecA.getcoord());
		ASSERT_EQUAL(-2, vecC.x());
		ASSERT_EQUAL(-5, vecC.y());

		Point2 vecD = vecC - Vector2(vecB.getcoord());
		ASSERT_EQUAL(-12, vecD.x());
		ASSERT_EQUAL(-25, vecD.y());
	}
}

AUTO_UNIT_TEST(point2_non_member_functions)
{
	// averageComponent
	{
		ASSERT_EQUAL(5, averageComponent(Point2(4,6)));
		ASSERT_EQUAL(5, averageComponent(Point2(6,4)));
		ASSERT_EQUAL(50, averageComponent(Point2(0,100)));
		ASSERT_EQUAL(50, averageComponent(Point2(100,0)));
	}
	// maxComponent
	{
		ASSERT_EQUAL(100, maxComponent(Point2(0,100)));
		ASSERT_EQUAL(100, maxComponent(Point2(100,0)));
		ASSERT_EQUAL(0, maxComponent(Point2(0,0)));
		ASSERT_EQUAL(0, maxComponent(Point2(-1,0)));
		ASSERT_EQUAL(0, maxComponent(Point2(0,-1)));
	}
}
