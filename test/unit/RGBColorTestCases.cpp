#define PROVIDE_AUTO_TEST_MAIN
#include "blocxx_test/CppUnit/AutoTest.hpp"
#include "panorama/common/Types.hpp"

using namespace panorama;

double DELTA = 0.00001;
#define ASSERT_EQUAL(a, b) unitAssertDoublesEqual((a), (b), DELTA)

AUTO_UNIT_TEST(rgbcolor_string_convert)
{
	// Test the tag-based string conversion operations -- we don't want
	// inheritance or virtual functions.
	RGBColor color(1,2,3);

	unitAssertEquals("[- 1,2,3 -]", color.toString());
	unitAssertEquals("[- 1,2,3 -]", panorama::toString(color));
	unitAssertEquals("RGBColor\n{\n  r = 1;\n  g = 2;\n  b = 3;\n}", toStringAsMembers(color));
	unitAssertEquals(color[0], 1);
	unitAssertEquals(color[1], 2);
	unitAssertEquals(color[2], 3);

	GenericRGBColor<int, BGRColorTraits<int> > color2(4,5,6);
	unitAssertEquals("[- 4,5,6 -]", color2.toString());
	unitAssertEquals("[- 4,5,6 -]", panorama::toString(color2));
	unitAssertEquals("BGRColor\n{\n  r = 4;\n  g = 5;\n  b = 6;\n}", toStringAsMembers(color2));
	unitAssertEquals(color2[0], 6);
	unitAssertEquals(color2[1], 5);
	unitAssertEquals(color2[2], 4);

	unitAssertEquals("[- 5,7,9 -]", panorama::toString(color + color2));
}

AUTO_UNIT_TEST(rgbcolor_reinterpret)
{
	// This test proves that the structure is packed and double-aligned.  If
	// this fails anywhere then changes will need to be made to the structure.
	RGBColor colors[2];
	unitAssertEquals(sizeof(double) * 3, sizeof(colors[0]));
	unitAssertEquals(sizeof(double) * 6, sizeof(colors));

	colors[0][0] = 1;
	colors[0][1] = 2;
	colors[0][2] = 3;
	colors[1][0] = 10;
	colors[1][1] = 20;
	colors[1][2] = 30;

	double* cp = (double*)&colors[0];
	ASSERT_EQUAL(1, cp[0]);
	ASSERT_EQUAL(2, cp[1]);
	ASSERT_EQUAL(3, cp[2]);
	ASSERT_EQUAL(10, cp[3]);
	ASSERT_EQUAL(20, cp[4]);
	ASSERT_EQUAL(30, cp[5]);

	cp[2] = 4;
	ASSERT_EQUAL(1, colors[0].r());
	ASSERT_EQUAL(2, colors[0].g());
	ASSERT_EQUAL(4, colors[0].b());
	ASSERT_EQUAL(10, colors[1].r());
	ASSERT_EQUAL(20, colors[1].g());
	ASSERT_EQUAL(30, colors[1].b());
}

AUTO_UNIT_TEST(rgbcolor_set_and_get)
{
	RGBColor c(0,1,2);
	const RGBColor c2(c);

	// Non-const getters.
	ASSERT_EQUAL(0, c.r());
	ASSERT_EQUAL(0, c[RGBColor::R]);
	ASSERT_EQUAL(1, c.g());
	ASSERT_EQUAL(1, c[RGBColor::G]);
	ASSERT_EQUAL(2, c.b());
	ASSERT_EQUAL(2, c[RGBColor::B]);

	// Const getters
	ASSERT_EQUAL(0, c2.r());
	ASSERT_EQUAL(0, c2[RGBColor::R]);
	ASSERT_EQUAL(1, c2.g());
	ASSERT_EQUAL(1, c2[RGBColor::G]);
	ASSERT_EQUAL(2, c2.b());
	ASSERT_EQUAL(2, c2[RGBColor::B]);

	// Setters.
	c.set(4,5,6);
	ASSERT_EQUAL(4, c.r());
	ASSERT_EQUAL(5, c.g());
	ASSERT_EQUAL(6, c.b());
	c.b() = 7;
	ASSERT_EQUAL(7, c[2]);
	c.g() = 10;
	ASSERT_EQUAL(10, c[1]);
	c.r() = 3;
	ASSERT_EQUAL(3, c[0]);
	c[0] = 100;
	ASSERT_EQUAL(100, c.r());
	c[1] = 63;
	ASSERT_EQUAL(63, c.g());
	c[2] = 43;
	ASSERT_EQUAL(43, c.b());
}

AUTO_UNIT_TEST(rgbcolor_member_operators)
{
	RGBColor colorA(2,5,11);
	RGBColor colorB(10,20,30);
	// =
	{
		RGBColor colorC;
		colorC = colorA;
		ASSERT_EQUAL(2, colorC.r());
		ASSERT_EQUAL(5, colorC.g());
		ASSERT_EQUAL(11, colorC.b());

		RGBColor colorD;
		colorC = colorD = colorB;
		ASSERT_EQUAL(10, colorD.r());
		ASSERT_EQUAL(20, colorD.g());
		ASSERT_EQUAL(30, colorD.b());
		ASSERT_EQUAL(10, colorC.r());
		ASSERT_EQUAL(20, colorC.g());
		ASSERT_EQUAL(30, colorC.b());
	}
	// +=
	{
		RGBColor colorC = colorA;
		colorC += colorC;
		ASSERT_EQUAL(4, colorC.r());
		ASSERT_EQUAL(10, colorC.g());
		ASSERT_EQUAL(22, colorC.b());

		colorC += colorB;
		ASSERT_EQUAL(14, colorC.r());
		ASSERT_EQUAL(30, colorC.g());
		ASSERT_EQUAL(52, colorC.b());
	}
	// -=
	{
		RGBColor colorC = colorA;
		colorC -= colorC;
		ASSERT_EQUAL(0, colorC.r());
		ASSERT_EQUAL(0, colorC.g());
		ASSERT_EQUAL(0, colorC.b());

		colorC -= colorB;
		ASSERT_EQUAL(-10, colorC.r());
		ASSERT_EQUAL(-20, colorC.g());
		ASSERT_EQUAL(-30, colorC.b());

		colorC -= colorA;
		ASSERT_EQUAL(-12, colorC.r());
		ASSERT_EQUAL(-25, colorC.g());
		ASSERT_EQUAL(-41, colorC.b());
	}
	// *= (factor)
	{
		RGBColor colorC = colorA;
		colorC *= 1.5;
		ASSERT_EQUAL(3, colorC.r());
		ASSERT_EQUAL(7.5, colorC.g());
		ASSERT_EQUAL(16.5, colorC.b());
	}
	// *= (generic factor)
	{
		RGBColor colorC = colorA;
		colorC *= short(3);
		ASSERT_EQUAL(6, colorC.r());
		ASSERT_EQUAL(15, colorC.g());
		ASSERT_EQUAL(33, colorC.b());
	}
	// /= (factor)
	{
		RGBColor c = colorA;
		c /= 2.0;
		ASSERT_EQUAL(1, c.r());
		ASSERT_EQUAL(2.5, c.g());
		ASSERT_EQUAL(5.5, c.b());

		c /= 1.0;
		ASSERT_EQUAL(1, c.r());
		ASSERT_EQUAL(2.5, c.g());
		ASSERT_EQUAL(5.5, c.b());
	}
	// /= (generic factor)
	{
		RGBColor c = colorA;
		c /= short(2);
		ASSERT_EQUAL(1, c.r());
		ASSERT_EQUAL(2.5, c.g());
		ASSERT_EQUAL(5.5, c.b());

		c /= long(10);
		ASSERT_EQUAL(0.10, c.r());
		ASSERT_EQUAL(0.25, c.g());
		ASSERT_EQUAL(0.55, c.b());
	}
}

AUTO_UNIT_TEST(rgbcolor_non_member_operators)
{
	// FIXME!
	RGBColor colorA(2,5,11);
	RGBColor colorB(10,20,30);

	// +
	{
		RGBColor colorC = colorA + colorA + colorA;
		ASSERT_EQUAL(6, colorC.r());
		ASSERT_EQUAL(15, colorC.g());
		ASSERT_EQUAL(33, colorC.b());

		RGBColor colorD = colorC + colorB;
		ASSERT_EQUAL(16, colorD.r());
		ASSERT_EQUAL(35, colorD.g());
		ASSERT_EQUAL(63, colorD.b());
	}
	// -
	{
		RGBColor colorC = colorA - colorA - colorA;
		ASSERT_EQUAL(-2, colorC.r());
		ASSERT_EQUAL(-5, colorC.g());
		ASSERT_EQUAL(-11, colorC.b());

		RGBColor colorD = colorC - colorB;
		ASSERT_EQUAL(-12, colorD.r());
		ASSERT_EQUAL(-25, colorD.g());
		ASSERT_EQUAL(-41, colorD.b());
	}
	// * (factor left)
	{
		RGBColor colorC = 2.0 * (2.0 * colorA);
		ASSERT_EQUAL(8, colorC.r());
		ASSERT_EQUAL(20, colorC.g());
		ASSERT_EQUAL(44, colorC.b());

		RGBColor colorD = 3.0 * (-10.0 * (5.0 * colorB));
		ASSERT_EQUAL(-1500, colorD.r());
		ASSERT_EQUAL(-3000, colorD.g());
		ASSERT_EQUAL(-4500, colorD.b());
	}
	// * (factor right)
	{
		RGBColor colorC = ((colorA * 2.0) * 2.0);
		ASSERT_EQUAL(8, colorC.r());
		ASSERT_EQUAL(20, colorC.g());
		ASSERT_EQUAL(44, colorC.b());

		RGBColor colorD = ((colorB * 5.0) * -10.0) * 3.0;
		ASSERT_EQUAL(-1500, colorD.r());
		ASSERT_EQUAL(-3000, colorD.g());
		ASSERT_EQUAL(-4500, colorD.b());
	}
	// * (factor generic left)
	{
		RGBColor colorC = 2.0f * (long(2) * colorA);
		ASSERT_EQUAL(8, colorC.r());
		ASSERT_EQUAL(20, colorC.g());
		ASSERT_EQUAL(44, colorC.b());

		RGBColor colorD = float(3) * (char(-10) * (short(5) * colorB));
		ASSERT_EQUAL(-1500, colorD.r());
		ASSERT_EQUAL(-3000, colorD.g());
		ASSERT_EQUAL(-4500, colorD.b());
	}
	// * (factor generic right)
	{
		RGBColor colorC = ((colorA * int(2)) * float(2));
		ASSERT_EQUAL(8, colorC.r());
		ASSERT_EQUAL(20, colorC.g());
		ASSERT_EQUAL(44, colorC.b());

		RGBColor colorD = ((colorB * char(5)) * float(-10)) * int(3);
		ASSERT_EQUAL(-1500, colorD.r());
		ASSERT_EQUAL(-3000, colorD.g());
		ASSERT_EQUAL(-4500, colorD.b());
	}
	// - (unary)
	{
		RGBColor colorC = -colorA;
		ASSERT_EQUAL(-2, colorC.r());
		ASSERT_EQUAL(-5, colorC.g());
		ASSERT_EQUAL(-11, colorC.b());

		RGBColor colorD = -colorB;
		ASSERT_EQUAL(-10, colorD.r());
		ASSERT_EQUAL(-20, colorD.g());
		ASSERT_EQUAL(-30, colorD.b());
	}
}

AUTO_UNIT_TEST(rgbcolor_non_member_functions)
{
	// averageComponent
	{
		ASSERT_EQUAL(6, averageComponent(RGBColor(4,6,8)));
		ASSERT_EQUAL(6, averageComponent(RGBColor(4,8,6)));
		ASSERT_EQUAL(6, averageComponent(RGBColor(8,4,6)));
		ASSERT_EQUAL(6, averageComponent(RGBColor(8,6,4)));
		ASSERT_EQUAL(6, averageComponent(RGBColor(6,4,8)));
		ASSERT_EQUAL(6, averageComponent(RGBColor(6,8,4)));

		ASSERT_EQUAL(66.6666666, averageComponent(RGBColor(0,100,100)));
		ASSERT_EQUAL(100, averageComponent(RGBColor(0,100,200)));
		ASSERT_EQUAL(5, averageComponent(RGBColor(4,5,6)));
	}
	// maxComponent
	{
		ASSERT_EQUAL(100, maxComponent(RGBColor(0,50,100)));
		ASSERT_EQUAL(100, maxComponent(RGBColor(0,100,50)));
		ASSERT_EQUAL(100, maxComponent(RGBColor(50,0,100)));
		ASSERT_EQUAL(100, maxComponent(RGBColor(50,100,0)));
		ASSERT_EQUAL(100, maxComponent(RGBColor(100,0,50)));
		ASSERT_EQUAL(100, maxComponent(RGBColor(100,50,0)));
		ASSERT_EQUAL(0, maxComponent(RGBColor(0,0,0)));
		ASSERT_EQUAL(0, maxComponent(RGBColor(-1,0,-1)));
		ASSERT_EQUAL(0, maxComponent(RGBColor(0,-1,-4)));
	}
	// abs
	{
		RGBColor c = abs(RGBColor(-3,5,1));
		ASSERT_EQUAL(3, c.r());
		ASSERT_EQUAL(5, c.g());
		ASSERT_EQUAL(1, c.b());

		c = abs(RGBColor(5,-3, 1));
		ASSERT_EQUAL(5, c.r());
		ASSERT_EQUAL(3, c.g());
		ASSERT_EQUAL(1, c.b());

		c = abs(RGBColor(5,3, -1));
		ASSERT_EQUAL(5, c.r());
		ASSERT_EQUAL(3, c.g());
		ASSERT_EQUAL(1, c.b());

		c = abs(RGBColor(0,0,0));
		ASSERT_EQUAL(0, c.r());
		ASSERT_EQUAL(0, c.g());
		ASSERT_EQUAL(0, c.b());
	}
}
