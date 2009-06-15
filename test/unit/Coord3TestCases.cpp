#define PROVIDE_AUTO_TEST_MAIN
#include "AutoTest.hpp"
#include "panorama/common/Types.hpp"

using namespace panorama;

double DELTA = 0.00001;
#define ASSERT_EQUAL(a, b) unitAssertDoublesEqual((a), (b), DELTA)

AUTO_UNIT_TEST(coord3_string_convert)
{
	// Test the tag-based string conversion operations -- we don't want
	// inheritance or virtual functions.
	Coord3 coord(1,2,3);

	unitAssertEquals("{1,2,3}", coord.toString());
	unitAssertEquals("{1,2,3}", panorama::toString(coord));
	unitAssertEquals("Coord3\n{\n  x = 1;\n  y = 2;\n  z = 3;\n}", toStringAsMembers(coord));
}

AUTO_UNIT_TEST(coord3_reinterpret)
{
	// This test proves that the structure is packed and double-aligned.  If
	// this fails anywhere then changes will need to be made to the structure.
	Coord3 coords[2];
	unitAssertEquals(sizeof(double) * 3, sizeof(coords[0]));
	unitAssertEquals(sizeof(double) * 6, sizeof(coords));

	coords[0][0] = 1;
	coords[0][1] = 2;
	coords[0][2] = 3;
	coords[1][0] = 10;
	coords[1][1] = 20;
	coords[1][2] = 30;

	double* cp = (double*)&coords[0];
	ASSERT_EQUAL(1, cp[0]);
	ASSERT_EQUAL(2, cp[1]);
	ASSERT_EQUAL(3, cp[2]);
	ASSERT_EQUAL(10, cp[3]);
	ASSERT_EQUAL(20, cp[4]);
	ASSERT_EQUAL(30, cp[5]);

	cp[2] = 4;
	ASSERT_EQUAL(1, coords[0].x());
	ASSERT_EQUAL(2, coords[0].y());
	ASSERT_EQUAL(4, coords[0].z());
	ASSERT_EQUAL(10, coords[1].x());
	ASSERT_EQUAL(20, coords[1].y());
	ASSERT_EQUAL(30, coords[1].z());
}

AUTO_UNIT_TEST(coord3_set_and_get)
{
	Coord3 c(0,1,2);
	const Coord3 c2(c);

	// Non-const getters.
	ASSERT_EQUAL(0, c.x());
	ASSERT_EQUAL(0, c[Coord3::X]);
	ASSERT_EQUAL(1, c.y());
	ASSERT_EQUAL(1, c[Coord3::Y]);
	ASSERT_EQUAL(2, c.z());
	ASSERT_EQUAL(2, c[Coord3::Z]);

	// Const getters
	ASSERT_EQUAL(0, c2.x());
	ASSERT_EQUAL(0, c2[Coord3::X]);
	ASSERT_EQUAL(1, c2.y());
	ASSERT_EQUAL(1, c2[Coord3::Y]);
	ASSERT_EQUAL(2, c2.z());
	ASSERT_EQUAL(2, c2[Coord3::Z]);

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

AUTO_UNIT_TEST(coord3_member_operators)
{
	Coord3 coordA(2,5,11);
	Coord3 coordB(10,20,30);
	// =
	{
		Coord3 coordC;
		coordC = coordA;
		ASSERT_EQUAL(2, coordC.x());
		ASSERT_EQUAL(5, coordC.y());
		ASSERT_EQUAL(11, coordC.z());

		Coord3 coordD;
		coordC = coordD = coordB;
		ASSERT_EQUAL(10, coordD.x());
		ASSERT_EQUAL(20, coordD.y());
		ASSERT_EQUAL(30, coordD.z());
		ASSERT_EQUAL(10, coordC.x());
		ASSERT_EQUAL(20, coordC.y());
		ASSERT_EQUAL(30, coordC.z());
	}
	// +=
	{
		Coord3 coordC = coordA;
		coordC += coordC;
		ASSERT_EQUAL(4, coordC.x());
		ASSERT_EQUAL(10, coordC.y());
		ASSERT_EQUAL(22, coordC.z());

		coordC += coordB;
		ASSERT_EQUAL(14, coordC.x());
		ASSERT_EQUAL(30, coordC.y());
		ASSERT_EQUAL(52, coordC.z());
	}
	// -=
	{
		Coord3 coordC = coordA;
		coordC -= coordC;
		ASSERT_EQUAL(0, coordC.x());
		ASSERT_EQUAL(0, coordC.y());
		ASSERT_EQUAL(0, coordC.z());

		coordC -= coordB;
		ASSERT_EQUAL(-10, coordC.x());
		ASSERT_EQUAL(-20, coordC.y());
		ASSERT_EQUAL(-30, coordC.z());

		coordC -= coordA;
		ASSERT_EQUAL(-12, coordC.x());
		ASSERT_EQUAL(-25, coordC.y());
		ASSERT_EQUAL(-41, coordC.z());
	}
	// *= (piecewise)
	{
		Coord3 coordC = coordA;
		coordC *= coordB;
		ASSERT_EQUAL(20, coordC.x());
		ASSERT_EQUAL(100, coordC.y());
		ASSERT_EQUAL(330, coordC.z());
	}
	// *= (factor)
	{
		Coord3 coordC = coordA;
		coordC *= 1.5;
		ASSERT_EQUAL(3, coordC.x());
		ASSERT_EQUAL(7.5, coordC.y());
		ASSERT_EQUAL(16.5, coordC.z());
	}
	// *= (generic factor)
	{
		Coord3 coordC = coordA;
		coordC *= short(3);
		ASSERT_EQUAL(6, coordC.x());
		ASSERT_EQUAL(15, coordC.y());
		ASSERT_EQUAL(33, coordC.z());
	}
	// /= (factor)
	{
		Coord3 c = coordA;
		c /= 2.0;
		ASSERT_EQUAL(1, c.x());
		ASSERT_EQUAL(2.5, c.y());
		ASSERT_EQUAL(5.5, c.z());

		c /= 1.0;
		ASSERT_EQUAL(1, c.x());
		ASSERT_EQUAL(2.5, c.y());
		ASSERT_EQUAL(5.5, c.z());
	}
	// /= (generic factor)
	{
		Coord3 c = coordA;
		c /= short(2);
		ASSERT_EQUAL(1, c.x());
		ASSERT_EQUAL(2.5, c.y());
		ASSERT_EQUAL(5.5, c.z());

		c /= long(10);
		ASSERT_EQUAL(0.10, c.x());
		ASSERT_EQUAL(0.25, c.y());
		ASSERT_EQUAL(0.55, c.z());
	}
}

AUTO_UNIT_TEST(coord3_non_member_operators)
{
	// FIXME!
	Coord3 coordA(2,5,11);
	Coord3 coordB(10,20,30);

	// +
	{
		Coord3 coordC = coordA + coordA + coordA;
		ASSERT_EQUAL(6, coordC.x());
		ASSERT_EQUAL(15, coordC.y());
		ASSERT_EQUAL(33, coordC.z());

		Coord3 coordD = coordC + coordB;
		ASSERT_EQUAL(16, coordD.x());
		ASSERT_EQUAL(35, coordD.y());
		ASSERT_EQUAL(63, coordD.z());
	}
	// -
	{
		Coord3 coordC = coordA - coordA - coordA;
		ASSERT_EQUAL(-2, coordC.x());
		ASSERT_EQUAL(-5, coordC.y());
		ASSERT_EQUAL(-11, coordC.z());

		Coord3 coordD = coordC - coordB;
		ASSERT_EQUAL(-12, coordD.x());
		ASSERT_EQUAL(-25, coordD.y());
		ASSERT_EQUAL(-41, coordD.z());
	}
	// * (factor left)
	{
		Coord3 coordC = 2.0 * (2.0 * coordA);
		ASSERT_EQUAL(8, coordC.x());
		ASSERT_EQUAL(20, coordC.y());
		ASSERT_EQUAL(44, coordC.z());

		Coord3 coordD = 3.0 * (-10.0 * (5.0 * coordB));
		ASSERT_EQUAL(-1500, coordD.x());
		ASSERT_EQUAL(-3000, coordD.y());
		ASSERT_EQUAL(-4500, coordD.z());
	}
	// * (factor right)
	{
		Coord3 coordC = ((coordA * 2.0) * 2.0);
		ASSERT_EQUAL(8, coordC.x());
		ASSERT_EQUAL(20, coordC.y());
		ASSERT_EQUAL(44, coordC.z());

		Coord3 coordD = ((coordB * 5.0) * -10.0) * 3.0;
		ASSERT_EQUAL(-1500, coordD.x());
		ASSERT_EQUAL(-3000, coordD.y());
		ASSERT_EQUAL(-4500, coordD.z());
	}
	// / (factor right)
	{
		Coord3 coordC = ((coordA / 2.0) / 2.0);
		ASSERT_EQUAL(0.5, coordC.x());
		ASSERT_EQUAL(1.25, coordC.y());
		ASSERT_EQUAL(2.75, coordC.z());

		Coord3 coordD = ((coordB / 5.0) / -10.0) / 2.0;
		ASSERT_EQUAL(-0.1, coordD.x());
		ASSERT_EQUAL(-0.2, coordD.y());
		ASSERT_EQUAL(-0.3, coordD.z());
	}
	// / (factor generic right)
	{
		Coord3 coordC = ((coordA / 2.0f) / int(2));
		ASSERT_EQUAL(0.5, coordC.x());
		ASSERT_EQUAL(1.25, coordC.y());
		ASSERT_EQUAL(2.75, coordC.z());

		Coord3 coordD = ((coordB / 5.0f) / long(-10)) / short(2);
		ASSERT_EQUAL(-0.1, coordD.x());
		ASSERT_EQUAL(-0.2, coordD.y());
		ASSERT_EQUAL(-0.3, coordD.z());
	}
	// * (factor generic left)
	{
		Coord3 coordC = 2.0f * (long(2) * coordA);
		ASSERT_EQUAL(8, coordC.x());
		ASSERT_EQUAL(20, coordC.y());
		ASSERT_EQUAL(44, coordC.z());

		Coord3 coordD = float(3) * (char(-10) * (short(5) * coordB));
		ASSERT_EQUAL(-1500, coordD.x());
		ASSERT_EQUAL(-3000, coordD.y());
		ASSERT_EQUAL(-4500, coordD.z());
	}
	// * (factor generic right)
	{
		Coord3 coordC = ((coordA * int(2)) * float(2));
		ASSERT_EQUAL(8, coordC.x());
		ASSERT_EQUAL(20, coordC.y());
		ASSERT_EQUAL(44, coordC.z());

		Coord3 coordD = ((coordB * char(5)) * float(-10)) * int(3);
		ASSERT_EQUAL(-1500, coordD.x());
		ASSERT_EQUAL(-3000, coordD.y());
		ASSERT_EQUAL(-4500, coordD.z());
	}
	// * (piecewise)
	{
		Coord3 coordC = coordA * coordA * coordA;
		ASSERT_EQUAL(8, coordC.x());
		ASSERT_EQUAL(125, coordC.y());
		ASSERT_EQUAL(1331, coordC.z());

		Coord3 coordD = coordC * coordB;
		ASSERT_EQUAL(80, coordD.x());
		ASSERT_EQUAL(2500, coordD.y());
		ASSERT_EQUAL(39930, coordD.z());
	}
	// - (unary)
	{
		Coord3 coordC = -coordA;
		ASSERT_EQUAL(-2, coordC.x());
		ASSERT_EQUAL(-5, coordC.y());
		ASSERT_EQUAL(-11, coordC.z());

		Coord3 coordD = -coordB;
		ASSERT_EQUAL(-10, coordD.x());
		ASSERT_EQUAL(-20, coordD.y());
		ASSERT_EQUAL(-30, coordD.z());
	}
}

AUTO_UNIT_TEST(coord3_non_member_functions)
{
	// dotprod
	{
		ASSERT_EQUAL(81, dotprod(Coord3(1,4,8), Coord3(1,4,8)));
		ASSERT_EQUAL(32, dotprod(Coord3(1,2,3), Coord3(4,5,6)));
	}
	// length
	{
		ASSERT_EQUAL(9, length(Coord3(1,4,8)));
	}
	// unit
	{
		Coord3 c = unit(Coord3(174,282,389)); // length 511
		ASSERT_EQUAL(0.340508806262, c.x()); // 174/511
		ASSERT_EQUAL(0.551859099804, c.y()); // 282/511
		ASSERT_EQUAL(0.761252446184, c.z()); // 389/511
	}
	// invert
	{
		Coord3 c = invert(Coord3(2, 5, 8));
		ASSERT_EQUAL(0.500, c.x());
		ASSERT_EQUAL(0.200, c.y());
		ASSERT_EQUAL(0.125, c.z());
	}
	// averageComponent
	{
		ASSERT_EQUAL(6, averageComponent(Coord3(4,6,8)));
		ASSERT_EQUAL(6, averageComponent(Coord3(4,8,6)));
		ASSERT_EQUAL(6, averageComponent(Coord3(8,4,6)));
		ASSERT_EQUAL(6, averageComponent(Coord3(8,6,4)));
		ASSERT_EQUAL(6, averageComponent(Coord3(6,4,8)));
		ASSERT_EQUAL(6, averageComponent(Coord3(6,8,4)));

		ASSERT_EQUAL(66.6666666, averageComponent(Coord3(0,100,100)));
		ASSERT_EQUAL(100, averageComponent(Coord3(0,100,200)));
		ASSERT_EQUAL(5, averageComponent(Coord3(4,5,6)));
	}
	// maxComponent
	{
		ASSERT_EQUAL(100, maxComponent(Coord3(0,50,100)));
		ASSERT_EQUAL(100, maxComponent(Coord3(0,100,50)));
		ASSERT_EQUAL(100, maxComponent(Coord3(50,0,100)));
		ASSERT_EQUAL(100, maxComponent(Coord3(50,100,0)));
		ASSERT_EQUAL(100, maxComponent(Coord3(100,0,50)));
		ASSERT_EQUAL(100, maxComponent(Coord3(100,50,0)));
		ASSERT_EQUAL(0, maxComponent(Coord3(0,0,0)));
		ASSERT_EQUAL(0, maxComponent(Coord3(-1,0,-1)));
		ASSERT_EQUAL(0, maxComponent(Coord3(0,-1,-4)));
	}
	// abs
	{
		Coord3 c = abs(Coord3(-3,5,1));
		ASSERT_EQUAL(3, c.x());
		ASSERT_EQUAL(5, c.y());
		ASSERT_EQUAL(1, c.z());

		c = abs(Coord3(5,-3, 1));
		ASSERT_EQUAL(5, c.x());
		ASSERT_EQUAL(3, c.y());
		ASSERT_EQUAL(1, c.z());

		c = abs(Coord3(5,3, -1));
		ASSERT_EQUAL(5, c.x());
		ASSERT_EQUAL(3, c.y());
		ASSERT_EQUAL(1, c.z());

		c = abs(Coord3(0,0,0));
		ASSERT_EQUAL(0, c.x());
		ASSERT_EQUAL(0, c.y());
		ASSERT_EQUAL(0, c.z());
	}
	//	squared_length
	{
		ASSERT_EQUAL(1620529, squared_length(Coord3(177,788,984)));
		ASSERT_EQUAL(25, squared_length(Coord3(0,3,4)));
		ASSERT_EQUAL(49, squared_length(Coord3(2,3,6)));
	}
	// crossprod
	{
		Coord3 x(1,0,0);
		Coord3 y(0,1,0);
		Coord3 z(0,0,1);

		Coord3 c = crossprod(x,y);
		ASSERT_EQUAL(c.x(), z.x());
		ASSERT_EQUAL(c.y(), z.y());
		ASSERT_EQUAL(c.z(), z.z());

		c = crossprod(y,x);
		ASSERT_EQUAL(c.x(), -z.x());
		ASSERT_EQUAL(c.y(), -z.y());
		ASSERT_EQUAL(c.z(), -z.z());

		c = crossprod(x,z);
		ASSERT_EQUAL(c.x(), -y.x());
		ASSERT_EQUAL(c.y(), -y.y());
		ASSERT_EQUAL(c.z(), -y.z());

		c = crossprod(z,x);
		ASSERT_EQUAL(c.x(), y.x());
		ASSERT_EQUAL(c.y(), y.y());
		ASSERT_EQUAL(c.z(), y.z());


		c = crossprod(y,z);
		ASSERT_EQUAL(c.x(), x.x());
		ASSERT_EQUAL(c.y(), x.y());
		ASSERT_EQUAL(c.z(), x.z());

		c = crossprod(z,y);
		ASSERT_EQUAL(c.x(), -x.x());
		ASSERT_EQUAL(c.y(), -x.y());
		ASSERT_EQUAL(c.z(), -x.z());
	}
}
