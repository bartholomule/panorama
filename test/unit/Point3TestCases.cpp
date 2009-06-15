#define PROVIDE_AUTO_TEST_MAIN
#include "AutoTest.hpp"
#include "panorama/common/Types.hpp"

using namespace panorama;

double DELTA = 0.00001;
#define ASSERT_EQUAL(a, b) unitAssertDoublesEqual((a), (b), DELTA)

AUTO_UNIT_TEST(point3_string_convert)
{
	// Test the tag-based string conversion operations -- we don't want
	// inheritance or virtual functions.
	Point3 vec(1,2,3);

	unitAssertEquals("(1,2,3)", vec.toString());
	unitAssertEquals("(1,2,3)", panorama::toString(vec));
	unitAssertEquals("Point3\n{\n  x = 1;\n  y = 2;\n  z = 3;\n}", toStringAsMembers(vec));
}

AUTO_UNIT_TEST(point3_reinterpret)
{
	// This test proves that the structure is packed and double-aligned.  If
	// this fails anywhere then changes will need to be made to the structure.
	Point3 vecs[2];
	unitAssertEquals(sizeof(double) * 3, sizeof(vecs[0]));
	unitAssertEquals(sizeof(double) * 6, sizeof(vecs));

	vecs[0][0] = 1;
	vecs[0][1] = 2;
	vecs[0][2] = 3;
	vecs[1][0] = 10;
	vecs[1][1] = 20;
	vecs[1][2] = 30;

	double* cp = (double*)&vecs[0];
	ASSERT_EQUAL(1, cp[0]);
	ASSERT_EQUAL(2, cp[1]);
	ASSERT_EQUAL(3, cp[2]);
	ASSERT_EQUAL(10, cp[3]);
	ASSERT_EQUAL(20, cp[4]);
	ASSERT_EQUAL(30, cp[5]);

	cp[2] = 4;
	ASSERT_EQUAL(1, vecs[0].x());
	ASSERT_EQUAL(2, vecs[0].y());
	ASSERT_EQUAL(4, vecs[0].z());
	ASSERT_EQUAL(10, vecs[1].x());
	ASSERT_EQUAL(20, vecs[1].y());
	ASSERT_EQUAL(30, vecs[1].z());
}

AUTO_UNIT_TEST(point3_set_and_get)
{
	Point3 c(0,1,2);
	const Point3 c2(c);

	// Non-const getters.
	ASSERT_EQUAL(0, c.x());
	ASSERT_EQUAL(0, c[Point3::X]);
	ASSERT_EQUAL(1, c.y());
	ASSERT_EQUAL(1, c[Point3::Y]);
	ASSERT_EQUAL(2, c.z());
	ASSERT_EQUAL(2, c[Point3::Z]);

	// Const getters
	ASSERT_EQUAL(0, c2.x());
	ASSERT_EQUAL(0, c2[Point3::X]);
	ASSERT_EQUAL(1, c2.y());
	ASSERT_EQUAL(1, c2[Point3::Y]);
	ASSERT_EQUAL(2, c2.z());
	ASSERT_EQUAL(2, c2[Point3::Z]);

	// Setters.
	c.set(4,5,6);
	ASSERT_EQUAL(4, c.x());
	ASSERT_EQUAL(5, c.y());
	ASSERT_EQUAL(6, c.z());
	c.z() = 7;
	ASSERT_EQUAL(7, c[2]);
	c.y() = 10;
	ASSERT_EQUAL(10, c[1]);
	c.x() = 3;
	ASSERT_EQUAL(3, c[0]);
	c[0] = 100;
	ASSERT_EQUAL(100, c.x());
	c[1] = 63;
	ASSERT_EQUAL(63, c.y());
	c[2] = 43;
	ASSERT_EQUAL(43, c.z());
}

AUTO_UNIT_TEST(point3_member_operators)
{
	Point3 vecA(2,5,11);
	Point3 vecB(10,20,30);
	// =
	{
		Point3 vecC;
		vecC = vecA;
		ASSERT_EQUAL(2, vecC.x());
		ASSERT_EQUAL(5, vecC.y());
		ASSERT_EQUAL(11, vecC.z());

		Point3 vecD;
		vecC = vecD = vecB;
		ASSERT_EQUAL(10, vecD.x());
		ASSERT_EQUAL(20, vecD.y());
		ASSERT_EQUAL(30, vecD.z());
		ASSERT_EQUAL(10, vecC.x());
		ASSERT_EQUAL(20, vecC.y());
		ASSERT_EQUAL(30, vecC.z());
	}
	// +=
	{
		Point3 vecC = vecA;
		vecC += Vector3(vecC.getcoord());
		ASSERT_EQUAL(4, vecC.x());
		ASSERT_EQUAL(10, vecC.y());
		ASSERT_EQUAL(22, vecC.z());

		vecC += Vector3(vecB.getcoord());
		ASSERT_EQUAL(14, vecC.x());
		ASSERT_EQUAL(30, vecC.y());
		ASSERT_EQUAL(52, vecC.z());
	}
	// -=
	{
		Point3 vecC = vecA;
		vecC -= Vector3(vecC.getcoord());
		ASSERT_EQUAL(0, vecC.x());
		ASSERT_EQUAL(0, vecC.y());
		ASSERT_EQUAL(0, vecC.z());

		vecC -= Vector3(vecB.getcoord());
		ASSERT_EQUAL(-10, vecC.x());
		ASSERT_EQUAL(-20, vecC.y());
		ASSERT_EQUAL(-30, vecC.z());

		vecC -= Vector3(vecA.getcoord());
		ASSERT_EQUAL(-12, vecC.x());
		ASSERT_EQUAL(-25, vecC.y());
		ASSERT_EQUAL(-41, vecC.z());
	}
}

AUTO_UNIT_TEST(point3_non_member_operators)
{
	Point3 vecA(2,5,11);
	Point3 vecB(10,20,30);

	// +
	{
		Point3 vecC = vecA + Vector3(vecA.getcoord()) + Vector3(vecA.getcoord());
		ASSERT_EQUAL(6, vecC.x());
		ASSERT_EQUAL(15, vecC.y());
		ASSERT_EQUAL(33, vecC.z());

		Point3 vecD = vecC + Vector3(vecB.getcoord());
		ASSERT_EQUAL(16, vecD.x());
		ASSERT_EQUAL(35, vecD.y());
		ASSERT_EQUAL(63, vecD.z());
	}
	// -
	{
		Point3 vecC = vecA - Vector3(vecA.getcoord()) - Vector3(vecA.getcoord());
		ASSERT_EQUAL(-2, vecC.x());
		ASSERT_EQUAL(-5, vecC.y());
		ASSERT_EQUAL(-11, vecC.z());

		Point3 vecD = vecC - Vector3(vecB.getcoord());
		ASSERT_EQUAL(-12, vecD.x());
		ASSERT_EQUAL(-25, vecD.y());
		ASSERT_EQUAL(-41, vecD.z());

		Vector3 vecE = vecC - vecB;
		ASSERT_EQUAL(-12, vecE.x());
		ASSERT_EQUAL(-25, vecE.y());
		ASSERT_EQUAL(-41, vecE.z());
	}
}

AUTO_UNIT_TEST(point3_non_member_functions)
{
	// averageComponent
	{
		ASSERT_EQUAL(6, averageComponent(Point3(4,6,8)));
		ASSERT_EQUAL(6, averageComponent(Point3(4,8,6)));
		ASSERT_EQUAL(6, averageComponent(Point3(8,4,6)));
		ASSERT_EQUAL(6, averageComponent(Point3(8,6,4)));
		ASSERT_EQUAL(6, averageComponent(Point3(6,4,8)));
		ASSERT_EQUAL(6, averageComponent(Point3(6,8,4)));

		ASSERT_EQUAL(66.6666666, averageComponent(Point3(0,100,100)));
		ASSERT_EQUAL(100, averageComponent(Point3(0,100,200)));
		ASSERT_EQUAL(5, averageComponent(Point3(4,5,6)));
	}
	// maxComponent
	{
		ASSERT_EQUAL(100, maxComponent(Point3(0,50,100)));
		ASSERT_EQUAL(100, maxComponent(Point3(0,100,50)));
		ASSERT_EQUAL(100, maxComponent(Point3(50,0,100)));
		ASSERT_EQUAL(100, maxComponent(Point3(50,100,0)));
		ASSERT_EQUAL(100, maxComponent(Point3(100,0,50)));
		ASSERT_EQUAL(100, maxComponent(Point3(100,50,0)));
		ASSERT_EQUAL(0, maxComponent(Point3(0,0,0)));
		ASSERT_EQUAL(0, maxComponent(Point3(-1,0,-1)));
		ASSERT_EQUAL(0, maxComponent(Point3(0,-1,-4)));
	}
}
