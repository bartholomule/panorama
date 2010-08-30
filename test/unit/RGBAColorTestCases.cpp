#define PROVIDE_AUTO_TEST_MAIN
#include "blocxx_test/CppUnit/AutoTest.hpp"
#include "panorama/common/Types.hpp"
#include "panorama/common/Larger.hpp"

using namespace panorama;

double DELTA = 0.00001;
#define ASSERT_EQUAL(a, b) unitAssertDoublesEqual((a), (b), DELTA)

AUTO_UNIT_TEST(rgbacolor_string_convert)
{
	// Test the tag-based string conversion operations -- we don't want
	// inheritance or virtual functions.
	RGBAColor color(1,2,3,4);

	unitAssertEquals("[- 1,2,3,4 -]", color.toString());
	unitAssertEquals("[- 1,2,3,4 -]", panorama::toString(color));
	unitAssertEquals("RGBAColor\n{\n  r = 1;\n  g = 2;\n  b = 3;\n  a = 4;\n}", toStringAsMembers(color));
	unitAssertEquals(color[0], 1);
	unitAssertEquals(color[1], 2);
	unitAssertEquals(color[2], 3);
	unitAssertEquals(color[3], 4);

	GenericRGBAColor<int, BGRAColorTraits<int> > color2(4,5,6,7);
	unitAssertEquals("[- 4,5,6,7 -]", color2.toString());
	unitAssertEquals("[- 4,5,6,7 -]", panorama::toString(color2));
	unitAssertEquals("BGRAColor\n{\n  r = 4;\n  g = 5;\n  b = 6;\n  a = 7;\n}", toStringAsMembers(color2));
	unitAssertEquals(color2[0], 6);
	unitAssertEquals(color2[1], 5);
	unitAssertEquals(color2[2], 4);
	unitAssertEquals(color2[3], 7);

	// FIXME! No valid conversion yet exists.
	//	unitAssertEquals("[- 5,7,9,11 -]", panorama::toString(color + RGBColor(color2)));
}

AUTO_UNIT_TEST(rgbacolor_reinterpret)
{
	// This test proves that the structure is packed and double-aligned.  If
	// this fails anywhere then changes will need to be made to the structure.
	RGBAColor colors[2];
	unitAssertEquals(sizeof(double) * 4, sizeof(colors[0]));
	unitAssertEquals(sizeof(double) * 2 * 4, sizeof(colors));

	colors[0][0] = 1;
	colors[0][1] = 2;
	colors[0][2] = 3;
	colors[0][3] = 4;
	colors[1][0] = 10;
	colors[1][1] = 20;
	colors[1][2] = 30;
	colors[1][3] = 40;

	double* cp = (double*)&colors[0];
	ASSERT_EQUAL(1, cp[0]);
	ASSERT_EQUAL(2, cp[1]);
	ASSERT_EQUAL(3, cp[2]);
	ASSERT_EQUAL(4, cp[3]);
	ASSERT_EQUAL(10, cp[4]);
	ASSERT_EQUAL(20, cp[5]);
	ASSERT_EQUAL(30, cp[6]);
	ASSERT_EQUAL(40, cp[7]);

	cp[2] = 4;
	ASSERT_EQUAL(1, colors[0].r());
	ASSERT_EQUAL(2, colors[0].g());
	ASSERT_EQUAL(4, colors[0].b());
	ASSERT_EQUAL(4, colors[0].a());
	ASSERT_EQUAL(10, colors[1].r());
	ASSERT_EQUAL(20, colors[1].g());
	ASSERT_EQUAL(30, colors[1].b());
	ASSERT_EQUAL(40, colors[1].a());
}

AUTO_UNIT_TEST(rgbacolor_set_and_get)
{
	RGBAColor c(0,1,2,3);
	const RGBAColor c2(c);

	// Non-const getters.
	ASSERT_EQUAL(0, c.r());
	ASSERT_EQUAL(0, c[RGBAColor::R]);
	ASSERT_EQUAL(1, c.g());
	ASSERT_EQUAL(1, c[RGBAColor::G]);
	ASSERT_EQUAL(2, c.b());
	ASSERT_EQUAL(2, c[RGBAColor::B]);
	ASSERT_EQUAL(3, c.a());
	ASSERT_EQUAL(3, c[RGBAColor::A]);

	// Const getters
	ASSERT_EQUAL(0, c2.r());
	ASSERT_EQUAL(0, c2[RGBAColor::R]);
	ASSERT_EQUAL(1, c2.g());
	ASSERT_EQUAL(1, c2[RGBAColor::G]);
	ASSERT_EQUAL(2, c2.b());
	ASSERT_EQUAL(2, c2[RGBAColor::B]);
	ASSERT_EQUAL(3, c2.a());
	ASSERT_EQUAL(3, c2[RGBAColor::A]);

	// Setters.
	c.set(4,5,6);
	ASSERT_EQUAL(4, c.r());
	ASSERT_EQUAL(5, c.g());
	ASSERT_EQUAL(6, c.b());
	ASSERT_EQUAL(0, c.a());
	c.b() = 7;
	ASSERT_EQUAL(7, c[2]);
	c.g() = 10;
	ASSERT_EQUAL(10, c[1]);
	c.r() = 3;
	ASSERT_EQUAL(3, c[0]);
	c.a() = 14;
	ASSERT_EQUAL(14, c[3]);
	c[0] = 100;
	ASSERT_EQUAL(100, c.r());
	c[1] = 63;
	ASSERT_EQUAL(63, c.g());
	c[2] = 43;
	ASSERT_EQUAL(43, c.b());
	c[3] = 52;
	ASSERT_EQUAL(52, c.a());
}

AUTO_UNIT_TEST(rgbacolor_member_operators)
{
	RGBAColor colorA(2,5,11, 0.5);
	RGBAColor colorB(10,20,30, 0.5);
	// =
	{
		RGBAColor colorC;
		colorC = colorA;
		ASSERT_EQUAL(2, colorC.r());
		ASSERT_EQUAL(5, colorC.g());
		ASSERT_EQUAL(11, colorC.b());

		RGBAColor colorD;
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
		RGBAColor colorC = colorA;
		colorC += colorC;
		ASSERT_EQUAL(0.25, colorC.a());
		ASSERT_EQUAL(2, colorC.r());
		ASSERT_EQUAL(5, colorC.g());
		ASSERT_EQUAL(11, colorC.b());

		colorC += colorB;
		ASSERT_EQUAL(6, colorC.r());
		ASSERT_EQUAL(12.5, colorC.g());
		ASSERT_EQUAL(20.5, colorC.b());
		ASSERT_EQUAL(0.125, colorC.a());
	}
	// *= (factor)
	{
		RGBAColor colorC = colorA;
		colorC *= 1.5;
		ASSERT_EQUAL(3, colorC.r());
		ASSERT_EQUAL(7.5, colorC.g());
		ASSERT_EQUAL(16.5, colorC.b());
	}
	// *= (generic factor)
	{
		RGBAColor colorC = colorA;
		colorC *= short(3);
		ASSERT_EQUAL(6, colorC.r());
		ASSERT_EQUAL(15, colorC.g());
		ASSERT_EQUAL(33, colorC.b());
	}
	// /= (factor)
	{
		RGBAColor c = colorA;
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
		RGBAColor c = colorA;
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

AUTO_UNIT_TEST(rgbacolor_non_member_operators)
{
	// FIXME!
	RGBAColor colorA(2,5,11,0.5);
	RGBAColor colorB(10,20,30,0.5);

	// +
	{
		RGBAColor colorC = colorA + colorA + colorA;
		ASSERT_EQUAL(2, colorC.r());
		ASSERT_EQUAL(5, colorC.g());
		ASSERT_EQUAL(11, colorC.b());
		ASSERT_EQUAL(0.125, colorC.a());

		RGBAColor colorD = colorC + colorB;
		ASSERT_EQUAL(6, colorD.r());
		ASSERT_EQUAL(12.5, colorD.g());
		ASSERT_EQUAL(20.5, colorD.b());
		ASSERT_EQUAL(0.0625, colorD.a());
	}
	// * (factor left)
	{
		RGBAColor colorC = 2.0 * (2.0 * colorA);
		ASSERT_EQUAL(8, colorC.r());
		ASSERT_EQUAL(20, colorC.g());
		ASSERT_EQUAL(44, colorC.b());

		RGBAColor colorD = 3.0 * (-10.0 * (5.0 * colorB));
		ASSERT_EQUAL(-1500, colorD.r());
		ASSERT_EQUAL(-3000, colorD.g());
		ASSERT_EQUAL(-4500, colorD.b());
	}
	// * (factor right)
	{
		RGBAColor colorC = ((colorA * 2.0) * 2.0);
		ASSERT_EQUAL(8, colorC.r());
		ASSERT_EQUAL(20, colorC.g());
		ASSERT_EQUAL(44, colorC.b());

		RGBAColor colorD = ((colorB * 5.0) * -10.0) * 3.0;
		ASSERT_EQUAL(-1500, colorD.r());
		ASSERT_EQUAL(-3000, colorD.g());
		ASSERT_EQUAL(-4500, colorD.b());
	}
	// * (factor generic left)
	{
		RGBAColor colorC = 2.0f * (long(2) * colorA);
		ASSERT_EQUAL(8, colorC.r());
		ASSERT_EQUAL(20, colorC.g());
		ASSERT_EQUAL(44, colorC.b());

		RGBAColor colorD = float(3) * (char(-10) * (short(5) * colorB));
		ASSERT_EQUAL(-1500, colorD.r());
		ASSERT_EQUAL(-3000, colorD.g());
		ASSERT_EQUAL(-4500, colorD.b());
	}
	// * (factor generic right)
	{
		RGBAColor colorC = ((colorA * int(2)) * float(2));
		ASSERT_EQUAL(8, colorC.r());
		ASSERT_EQUAL(20, colorC.g());
		ASSERT_EQUAL(44, colorC.b());

		RGBAColor colorD = ((colorB * char(5)) * float(-10)) * int(3);
		ASSERT_EQUAL(-1500, colorD.r());
		ASSERT_EQUAL(-3000, colorD.g());
		ASSERT_EQUAL(-4500, colorD.b());
	}
	// - (unary)
	{
		RGBAColor colorC = -colorA;
		ASSERT_EQUAL(-2, colorC.r());
		ASSERT_EQUAL(-5, colorC.g());
		ASSERT_EQUAL(-11, colorC.b());

		RGBAColor colorD = -colorB;
		ASSERT_EQUAL(-10, colorD.r());
		ASSERT_EQUAL(-20, colorD.g());
		ASSERT_EQUAL(-30, colorD.b());
	}
}

AUTO_UNIT_TEST(rgbacolor_non_member_functions)
{
	// averageComponent
	{
		ASSERT_EQUAL(6, averageComponent(RGBAColor(4,6,8)));
		ASSERT_EQUAL(6, averageComponent(RGBAColor(4,8,6)));
		ASSERT_EQUAL(6, averageComponent(RGBAColor(8,4,6)));
		ASSERT_EQUAL(6, averageComponent(RGBAColor(8,6,4)));
		ASSERT_EQUAL(6, averageComponent(RGBAColor(6,4,8)));
		ASSERT_EQUAL(6, averageComponent(RGBAColor(6,8,4)));

		ASSERT_EQUAL(66.6666666, averageComponent(RGBAColor(0,100,100)));
		ASSERT_EQUAL(100, averageComponent(RGBAColor(0,100,200)));
		ASSERT_EQUAL(5, averageComponent(RGBAColor(4,5,6)));
	}
	// maxComponent
	{
		ASSERT_EQUAL(100, maxComponent(RGBAColor(0,50,100)));
		ASSERT_EQUAL(100, maxComponent(RGBAColor(0,100,50)));
		ASSERT_EQUAL(100, maxComponent(RGBAColor(50,0,100)));
		ASSERT_EQUAL(100, maxComponent(RGBAColor(50,100,0)));
		ASSERT_EQUAL(100, maxComponent(RGBAColor(100,0,50)));
		ASSERT_EQUAL(100, maxComponent(RGBAColor(100,50,0)));
		ASSERT_EQUAL(0, maxComponent(RGBAColor(0,0,0)));
		ASSERT_EQUAL(0, maxComponent(RGBAColor(-1,0,-1)));
		ASSERT_EQUAL(0, maxComponent(RGBAColor(0,-1,-4)));
	}
	// abs
	{
		RGBAColor c = abs(RGBAColor(-3,5,1));
		ASSERT_EQUAL(3, c.r());
		ASSERT_EQUAL(5, c.g());
		ASSERT_EQUAL(1, c.b());

		c = abs(RGBAColor(5,-3, 1));
		ASSERT_EQUAL(5, c.r());
		ASSERT_EQUAL(3, c.g());
		ASSERT_EQUAL(1, c.b());

		c = abs(RGBAColor(5,3, -1));
		ASSERT_EQUAL(5, c.r());
		ASSERT_EQUAL(3, c.g());
		ASSERT_EQUAL(1, c.b());

		c = abs(RGBAColor(0,0,0));
		ASSERT_EQUAL(0, c.r());
		ASSERT_EQUAL(0, c.g());
		ASSERT_EQUAL(0, c.b());
	}
}
