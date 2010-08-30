#define PROVIDE_AUTO_TEST_MAIN
#include "blocxx_test/CppUnit/AutoTest.hpp"
#include "panorama/common/Types.hpp"

using namespace panorama;

double DELTA = 0.00001;
#define ASSERT_EQUAL(a, b) unitAssertDoublesEqual((a), (b), DELTA)

AUTO_UNIT_TEST(vector2_string_convert)
{
	// Test the tag-based string conversion operations -- we don't want
	// inheritance or virtual functions.
	Vector2 vec(1,2);

	unitAssertEquals("<1,2>", vec.toString());
	unitAssertEquals("<1,2>", panorama::toString(vec));
	unitAssertEquals("Vector2\n{\n  x = 1;\n  y = 2;\n}", toStringAsMembers(vec));
}

AUTO_UNIT_TEST(vector2_reinterpret)
{
	// This test proves that the structure is packed and double-aligned.  If
	// this fails anywhere then changes will need to be made to the structure.
	Vector2 vecs[2];
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

AUTO_UNIT_TEST(vector2_set_and_get)
{
	Vector2 c(0,1);
	const Vector2 c2(c);

	// Non-const getters.
	ASSERT_EQUAL(0, c.x());
	ASSERT_EQUAL(0, c[Vector2::X]);
	ASSERT_EQUAL(1, c.y());
	ASSERT_EQUAL(1, c[Vector2::Y]);

	// Const getters
	ASSERT_EQUAL(0, c2.x());
	ASSERT_EQUAL(0, c2[Vector2::X]);
	ASSERT_EQUAL(1, c2.y());
	ASSERT_EQUAL(1, c2[Vector2::Y]);

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

AUTO_UNIT_TEST(vector2_member_operators)
{
	Vector2 vecA(2,5);
	Vector2 vecB(10,20);
	// =
	{
		Vector2 vecC;
		vecC = vecA;
		ASSERT_EQUAL(2, vecC.x());
		ASSERT_EQUAL(5, vecC.y());

		Vector2 vecD;
		vecC = vecD = vecB;
		ASSERT_EQUAL(10, vecD.x());
		ASSERT_EQUAL(20, vecD.y());
		ASSERT_EQUAL(10, vecC.x());
		ASSERT_EQUAL(20, vecC.y());
	}
	// +=
	{
		Vector2 vecC = vecA;
		vecC += vecC;
		ASSERT_EQUAL(4, vecC.x());
		ASSERT_EQUAL(10, vecC.y());

		vecC += vecB;
		ASSERT_EQUAL(14, vecC.x());
		ASSERT_EQUAL(30, vecC.y());
	}
	// -=
	{
		Vector2 vecC = vecA;
		vecC -= vecC;
		ASSERT_EQUAL(0, vecC.x());
		ASSERT_EQUAL(0, vecC.y());

		vecC -= vecB;
		ASSERT_EQUAL(-10, vecC.x());
		ASSERT_EQUAL(-20, vecC.y());

		vecC -= vecA;
		ASSERT_EQUAL(-12, vecC.x());
		ASSERT_EQUAL(-25, vecC.y());
	}
	// *= (factor)
	{
		Vector2 vecC = vecA;
		vecC *= 1.5;
		ASSERT_EQUAL(3, vecC.x());
		ASSERT_EQUAL(7.5, vecC.y());
	}
	// *= (generic factor)
	{
		Vector2 vecC = vecA;
		vecC *= short(3);
		ASSERT_EQUAL(6, vecC.x());
		ASSERT_EQUAL(15, vecC.y());
	}
	// /= (factor)
	{
		Vector2 c = vecA;
		c /= 2.0;
		ASSERT_EQUAL(1, c.x());
		ASSERT_EQUAL(2.5, c.y());

		c /= 1.0;
		ASSERT_EQUAL(1, c.x());
		ASSERT_EQUAL(2.5, c.y());
	}
	// /= (generic factor)
	{
		Vector2 c = vecA;
		c /= short(2);
		ASSERT_EQUAL(1, c.x());
		ASSERT_EQUAL(2.5, c.y());

		c /= long(10);
		ASSERT_EQUAL(0.1, c.x());
		ASSERT_EQUAL(0.25, c.y());
	}
}

AUTO_UNIT_TEST(vector2_non_member_operators)
{
	Vector2 vecA(2,5);
	Vector2 vecB(10,20);

	// +
	{
		Vector2 vecC = vecA + vecA + vecA;
		ASSERT_EQUAL(6, vecC.x());
		ASSERT_EQUAL(15, vecC.y());

		Vector2 vecD = vecC + vecB;
		ASSERT_EQUAL(16, vecD.x());
		ASSERT_EQUAL(35, vecD.y());
	}
	// -
	{
		Vector2 vecC = vecA - vecA - vecA;
		ASSERT_EQUAL(-2, vecC.x());
		ASSERT_EQUAL(-5, vecC.y());

		Vector2 vecD = vecC - vecB;
		ASSERT_EQUAL(-12, vecD.x());
		ASSERT_EQUAL(-25, vecD.y());
	}
	// * (factor left)
	{
		Vector2 vecC = 2.0 * (2.0 * vecA);
		ASSERT_EQUAL(8, vecC.x());
		ASSERT_EQUAL(20, vecC.y());

		Vector2 vecD = 3.0 * (-10.0 * (5.0 * vecB));
		ASSERT_EQUAL(-1500, vecD.x());
		ASSERT_EQUAL(-3000, vecD.y());
	}
	// * (factor right)
	{
		Vector2 vecC = ((vecA * 2.0) * 2.0);
		ASSERT_EQUAL(8, vecC.x());
		ASSERT_EQUAL(20, vecC.y());

		Vector2 vecD = ((vecB * 5.0) * -10.0) * 3.0;
		ASSERT_EQUAL(-1500, vecD.x());
		ASSERT_EQUAL(-3000, vecD.y());
	}
	// / (factor right)
	{
		Vector2 vecC = ((vecA / 2.0) / 2.0);
		ASSERT_EQUAL(0.5, vecC.x());
		ASSERT_EQUAL(1.25, vecC.y());

		Vector2 vecD = ((vecB / 5.0) / -10.0) / 2.0;
		ASSERT_EQUAL(-0.1, vecD.x());
		ASSERT_EQUAL(-0.2, vecD.y());
	}
	// / (factor generic right)
	{
		Vector2 vecC = ((vecA / 2.0f) / int(2));
		ASSERT_EQUAL(0.5, vecC.x());
		ASSERT_EQUAL(1.25, vecC.y());

		Vector2 vecD = ((vecB / 5.0f) / long(-10)) / short(2);
		ASSERT_EQUAL(-0.1, vecD.x());
		ASSERT_EQUAL(-0.2, vecD.y());
	}
	// * (factor generic left)
	{
		Vector2 vecC = 2.0f * (long(2) * vecA);
		ASSERT_EQUAL(8, vecC.x());
		ASSERT_EQUAL(20, vecC.y());

		Vector2 vecD = float(3) * (char(-10) * (short(5) * vecB));
		ASSERT_EQUAL(-1500, vecD.x());
		ASSERT_EQUAL(-3000, vecD.y());
	}
	// * (factor generic right)
	{
		Vector2 vecC = ((vecA * int(2)) * float(2));
		ASSERT_EQUAL(8, vecC.x());
		ASSERT_EQUAL(20, vecC.y());

		Vector2 vecD = ((vecB * char(5)) * float(-10)) * int(3);
		ASSERT_EQUAL(-1500, vecD.x());
		ASSERT_EQUAL(-3000, vecD.y());
	}
	// - (unary)
	{
		Vector2 vecC = -vecA;
		ASSERT_EQUAL(-2, vecC.x());
		ASSERT_EQUAL(-5, vecC.y());

		Vector2 vecD = -vecB;
		ASSERT_EQUAL(-10, vecD.x());
		ASSERT_EQUAL(-20, vecD.y());
	}
}

AUTO_UNIT_TEST(vector2_non_member_functions)
{
	// dotprod
	{
		ASSERT_EQUAL(25, dotprod(Vector2(3,4), Vector2(3,4)));
		ASSERT_EQUAL(11, dotprod(Vector2(1,2), Vector2(3,4)));
	}
	// length
	{
		ASSERT_EQUAL(5, length(Vector2(3,4)));
	}
	// unit
	{
		Vector2 c = unit(Vector2(3,4));
		ASSERT_EQUAL(0.6, c.x()); // 3/5
		ASSERT_EQUAL(0.8, c.y()); // 4/5
	}
	// invert
	{
		Vector2 c = invert(Vector2(2, 5));
		ASSERT_EQUAL(0.5, c.x());
		ASSERT_EQUAL(0.2, c.y());
	}
	// averageComponent
	{
		ASSERT_EQUAL(5, averageComponent(Vector2(4,6)));
		ASSERT_EQUAL(5, averageComponent(Vector2(6,4)));
		ASSERT_EQUAL(50, averageComponent(Vector2(0,100)));
		ASSERT_EQUAL(50, averageComponent(Vector2(100,0)));
	}
	// maxComponent
	{
		ASSERT_EQUAL(100, maxComponent(Vector2(0,100)));
		ASSERT_EQUAL(100, maxComponent(Vector2(100,0)));
		ASSERT_EQUAL(0, maxComponent(Vector2(0,0)));
		ASSERT_EQUAL(0, maxComponent(Vector2(-1,0)));
		ASSERT_EQUAL(0, maxComponent(Vector2(0,-1)));
	}
}
