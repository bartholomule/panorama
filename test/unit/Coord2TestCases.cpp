#define PROVIDE_AUTO_TEST_MAIN
#include "AutoTest.hpp"
#include "panorama/common/Types.hpp"

using namespace panorama;

double DELTA = 0.00001;
#define ASSERT_EQUAL(a, b) unitAssertDoublesEqual((a), (b), DELTA)

AUTO_UNIT_TEST(coord2_string_convert)
{
	// Test the tag-based string conversion operations -- we don't want
	// inheritance or virtual functions.
	Coord2 coord(1,2);

	unitAssertEquals("{1,2}", coord.toString());
	unitAssertEquals("{1,2}", panorama::toString(coord));
	unitAssertEquals("Coord2\n{\n  x = 1;\n  y = 2;\n}", toStringAsMembers(coord));
}

AUTO_UNIT_TEST(coord2_reinterpret)
{
	// This test proves that the structure is packed and double-aligned.  If
	// this fails anywhere then changes will need to be made to the structure.
	Coord2 coords[2];
	unitAssertEquals(sizeof(double) * 2, sizeof(coords[0]));
	unitAssertEquals(sizeof(double) * 4, sizeof(coords));

	coords[0][0] = 1;
	coords[0][1] = 2;
	coords[1][0] = 10;
	coords[1][1] = 20;

	double* cp = (double*)&coords[0];
	ASSERT_EQUAL(1, cp[0]);
	ASSERT_EQUAL(2, cp[1]);
	ASSERT_EQUAL(10, cp[2]);
	ASSERT_EQUAL(20, cp[3]);

	cp[1] = 4;
	ASSERT_EQUAL(1, coords[0].x());
	ASSERT_EQUAL(4, coords[0].y());
	ASSERT_EQUAL(10, coords[1].x());
	ASSERT_EQUAL(20, coords[1].y());
}

AUTO_UNIT_TEST(coord2_set_and_get)
{
	Coord2 c(0,1);
	const Coord2 c2(c);

	// Non-const getters.
	ASSERT_EQUAL(0, c.x());
	ASSERT_EQUAL(0, c[Coord2::X]);
	ASSERT_EQUAL(1, c.y());
	ASSERT_EQUAL(1, c[Coord2::Y]);

	// Const getters
	ASSERT_EQUAL(0, c2.x());
	ASSERT_EQUAL(0, c2[Coord2::X]);
	ASSERT_EQUAL(1, c2.y());
	ASSERT_EQUAL(1, c2[Coord2::Y]);

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

AUTO_UNIT_TEST(coord2_member_operators)
{
	Coord2 coordA(2,5);
	Coord2 coordB(10,20);
	// =
	{
		Coord2 coordC;
		coordC = coordA;
		ASSERT_EQUAL(2, coordC.x());
		ASSERT_EQUAL(5, coordC.y());

		Coord2 coordD;
		coordC = coordD = coordB;
		ASSERT_EQUAL(10, coordD.x());
		ASSERT_EQUAL(20, coordD.y());
		ASSERT_EQUAL(10, coordC.x());
		ASSERT_EQUAL(20, coordC.y());
	}
	// +=
	{
		Coord2 coordC = coordA;
		coordC += coordC;
		ASSERT_EQUAL(4, coordC.x());
		ASSERT_EQUAL(10, coordC.y());

		coordC += coordB;
		ASSERT_EQUAL(14, coordC.x());
		ASSERT_EQUAL(30, coordC.y());
	}
	// -=
	{
		Coord2 coordC = coordA;
		coordC -= coordC;
		ASSERT_EQUAL(0, coordC.x());
		ASSERT_EQUAL(0, coordC.y());

		coordC -= coordB;
		ASSERT_EQUAL(-10, coordC.x());
		ASSERT_EQUAL(-20, coordC.y());

		coordC -= coordA;
		ASSERT_EQUAL(-12, coordC.x());
		ASSERT_EQUAL(-25, coordC.y());
	}
	// *= (piecewise)
	{
		Coord2 coordC = coordA;
		coordC *= coordB;
		ASSERT_EQUAL(20, coordC.x());
		ASSERT_EQUAL(100, coordC.y());
	}
	// *= (factor)
	{
		Coord2 coordC = coordA;
		coordC *= 1.5;
		ASSERT_EQUAL(3, coordC.x());
		ASSERT_EQUAL(7.5, coordC.y());
	}
	// *= (generic factor)
	{
		Coord2 coordC = coordA;
		coordC *= short(3);
		ASSERT_EQUAL(6, coordC.x());
		ASSERT_EQUAL(15, coordC.y());
	}
	// /= (factor)
	{
		Coord2 c = coordA;
		c /= 2.0;
		ASSERT_EQUAL(1, c.x());
		ASSERT_EQUAL(2.5, c.y());

		c /= 1.0;
		ASSERT_EQUAL(1, c.x());
		ASSERT_EQUAL(2.5, c.y());
	}
	// /= (generic factor)
	{
		Coord2 c = coordA;
		c /= short(2);
		ASSERT_EQUAL(1, c.x());
		ASSERT_EQUAL(2.5, c.y());

		c /= long(10);
		ASSERT_EQUAL(0.1, c.x());
		ASSERT_EQUAL(0.25, c.y());
	}
}

AUTO_UNIT_TEST(coord2_non_member_operators)
{
	Coord2 coordA(2,5);
	Coord2 coordB(10,20);

	// +
	{
		Coord2 coordC = coordA + coordA + coordA;
		ASSERT_EQUAL(6, coordC.x());
		ASSERT_EQUAL(15, coordC.y());

		Coord2 coordD = coordC + coordB;
		ASSERT_EQUAL(16, coordD.x());
		ASSERT_EQUAL(35, coordD.y());
	}
	// -
	{
		Coord2 coordC = coordA - coordA - coordA;
		ASSERT_EQUAL(-2, coordC.x());
		ASSERT_EQUAL(-5, coordC.y());

		Coord2 coordD = coordC - coordB;
		ASSERT_EQUAL(-12, coordD.x());
		ASSERT_EQUAL(-25, coordD.y());
	}
	// * (factor left)
	{
		Coord2 coordC = 2.0 * (2.0 * coordA);
		ASSERT_EQUAL(8, coordC.x());
		ASSERT_EQUAL(20, coordC.y());

		Coord2 coordD = 3.0 * (-10.0 * (5.0 * coordB));
		ASSERT_EQUAL(-1500, coordD.x());
		ASSERT_EQUAL(-3000, coordD.y());
	}
	// * (factor right)
	{
		Coord2 coordC = ((coordA * 2.0) * 2.0);
		ASSERT_EQUAL(8, coordC.x());
		ASSERT_EQUAL(20, coordC.y());

		Coord2 coordD = ((coordB * 5.0) * -10.0) * 3.0;
		ASSERT_EQUAL(-1500, coordD.x());
		ASSERT_EQUAL(-3000, coordD.y());
	}
	// / (factor right)
	{
		Coord2 coordC = ((coordA / 2.0) / 2.0);
		ASSERT_EQUAL(0.5, coordC.x());
		ASSERT_EQUAL(1.25, coordC.y());

		Coord2 coordD = ((coordB / 5.0) / -10.0) / 2.0;
		ASSERT_EQUAL(-0.1, coordD.x());
		ASSERT_EQUAL(-0.2, coordD.y());
	}
	// / (factor generic right)
	{
		Coord2 coordC = ((coordA / 2.0f) / int(2));
		ASSERT_EQUAL(0.5, coordC.x());
		ASSERT_EQUAL(1.25, coordC.y());

		Coord2 coordD = ((coordB / 5.0f) / long(-10)) / short(2);
		ASSERT_EQUAL(-0.1, coordD.x());
		ASSERT_EQUAL(-0.2, coordD.y());
	}
	// * (factor generic left)
	{
		Coord2 coordC = 2.0f * (long(2) * coordA);
		ASSERT_EQUAL(8, coordC.x());
		ASSERT_EQUAL(20, coordC.y());

		Coord2 coordD = float(3) * (char(-10) * (short(5) * coordB));
		ASSERT_EQUAL(-1500, coordD.x());
		ASSERT_EQUAL(-3000, coordD.y());
	}
	// * (factor generic right)
	{
		Coord2 coordC = ((coordA * int(2)) * float(2));
		ASSERT_EQUAL(8, coordC.x());
		ASSERT_EQUAL(20, coordC.y());

		Coord2 coordD = ((coordB * char(5)) * float(-10)) * int(3);
		ASSERT_EQUAL(-1500, coordD.x());
		ASSERT_EQUAL(-3000, coordD.y());
	}
	// * (piecewise)
	{
		Coord2 coordC = coordA * coordA * coordA;
		ASSERT_EQUAL(8, coordC.x());
		ASSERT_EQUAL(125, coordC.y());

		Coord2 coordD = coordC * coordB;
		ASSERT_EQUAL(80, coordD.x());
		ASSERT_EQUAL(2500, coordD.y());
	}
	// - (unary)
	{
		Coord2 coordC = -coordA;
		ASSERT_EQUAL(-2, coordC.x());
		ASSERT_EQUAL(-5, coordC.y());

		Coord2 coordD = -coordB;
		ASSERT_EQUAL(-10, coordD.x());
		ASSERT_EQUAL(-20, coordD.y());
	}
}

AUTO_UNIT_TEST(coord2_non_member_functions)
{
	// dotprod
	{
		ASSERT_EQUAL(25, dotprod(Coord2(3,4), Coord2(3,4)));
		ASSERT_EQUAL(11, dotprod(Coord2(1,2), Coord2(3,4)));
	}
	// length
	{
		ASSERT_EQUAL(5, length(Coord2(3,4)));
	}
	// unit
	{
		Coord2 c = unit(Coord2(3,4));
		ASSERT_EQUAL(0.6, c.x()); // 3/5
		ASSERT_EQUAL(0.8, c.y()); // 4/5
	}
	// invert
	{
		Coord2 c = invert(Coord2(2, 5));
		ASSERT_EQUAL(0.5, c.x());
		ASSERT_EQUAL(0.2, c.y());
	}
	// averageComponent
	{
		ASSERT_EQUAL(5, averageComponent(Coord2(4,6)));
		ASSERT_EQUAL(5, averageComponent(Coord2(6,4)));
		ASSERT_EQUAL(50, averageComponent(Coord2(0,100)));
		ASSERT_EQUAL(50, averageComponent(Coord2(100,0)));
	}
	// maxComponent
	{
		ASSERT_EQUAL(100, maxComponent(Coord2(0,100)));
		ASSERT_EQUAL(100, maxComponent(Coord2(100,0)));
		ASSERT_EQUAL(0, maxComponent(Coord2(0,0)));
		ASSERT_EQUAL(0, maxComponent(Coord2(-1,0)));
		ASSERT_EQUAL(0, maxComponent(Coord2(0,-1)));
	}
	// abs
	{
		Coord2 c = abs(Coord2(-3,5));
		ASSERT_EQUAL(3, c.x());
		ASSERT_EQUAL(5, c.y());

		c = abs(Coord2(5,-3));
		ASSERT_EQUAL(5, c.x());
		ASSERT_EQUAL(3, c.y());

		c = abs(Coord2(0,0));
		ASSERT_EQUAL(0, c.x());
		ASSERT_EQUAL(0, c.y());
	}
}
