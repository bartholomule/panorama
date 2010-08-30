#define PROVIDE_AUTO_TEST_MAIN
#include "blocxx_test/CppUnit/AutoTest.hpp"
#include "panorama/common/Types.hpp"

using namespace panorama;

double DELTA = 0.00001;
#define ASSERT_EQUAL(a, b) unitAssertDoublesEqual((a), (b), DELTA)

AUTO_UNIT_TEST(vector3_string_convert)
{
	// Test the tag-based string conversion operations -- we don't want
	// inheritance or virtual functions.
	Vector3 vec(1,2,3);

	unitAssertEquals("<1,2,3>", vec.toString());
	unitAssertEquals("<1,2,3>", panorama::toString(vec));
	unitAssertEquals("Vector3\n{\n  x = 1;\n  y = 2;\n  z = 3;\n}", toStringAsMembers(vec));
}

AUTO_UNIT_TEST(vector3_reinterpret)
{
	// This test proves that the structure is packed and double-aligned.  If
	// this fails anywhere then changes will need to be made to the structure.
	Vector3 vecs[2];
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

AUTO_UNIT_TEST(vector3_set_and_get)
{
	Vector3 c(0,1,2);
	const Vector3 c2(c);

	// Non-const getters.
	ASSERT_EQUAL(0, c.x());
	ASSERT_EQUAL(0, c[Vector3::X]);
	ASSERT_EQUAL(1, c.y());
	ASSERT_EQUAL(1, c[Vector3::Y]);
	ASSERT_EQUAL(2, c.z());
	ASSERT_EQUAL(2, c[Vector3::Z]);

	// Const getters
	ASSERT_EQUAL(0, c2.x());
	ASSERT_EQUAL(0, c2[Vector3::X]);
	ASSERT_EQUAL(1, c2.y());
	ASSERT_EQUAL(1, c2[Vector3::Y]);
	ASSERT_EQUAL(2, c2.z());
	ASSERT_EQUAL(2, c2[Vector3::Z]);

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

AUTO_UNIT_TEST(vector3_member_operators)
{
	Vector3 vecA(2,5,11);
	Vector3 vecB(10,20,30);
	// =
	{
		Vector3 vecC;
		vecC = vecA;
		ASSERT_EQUAL(2, vecC.x());
		ASSERT_EQUAL(5, vecC.y());
		ASSERT_EQUAL(11, vecC.z());

		Vector3 vecD;
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
		Vector3 vecC = vecA;
		vecC += vecC;
		ASSERT_EQUAL(4, vecC.x());
		ASSERT_EQUAL(10, vecC.y());
		ASSERT_EQUAL(22, vecC.z());

		vecC += vecB;
		ASSERT_EQUAL(14, vecC.x());
		ASSERT_EQUAL(30, vecC.y());
		ASSERT_EQUAL(52, vecC.z());
	}
	// -=
	{
		Vector3 vecC = vecA;
		vecC -= vecC;
		ASSERT_EQUAL(0, vecC.x());
		ASSERT_EQUAL(0, vecC.y());
		ASSERT_EQUAL(0, vecC.z());

		vecC -= vecB;
		ASSERT_EQUAL(-10, vecC.x());
		ASSERT_EQUAL(-20, vecC.y());
		ASSERT_EQUAL(-30, vecC.z());

		vecC -= vecA;
		ASSERT_EQUAL(-12, vecC.x());
		ASSERT_EQUAL(-25, vecC.y());
		ASSERT_EQUAL(-41, vecC.z());
	}
	// *= (factor)
	{
		Vector3 vecC = vecA;
		vecC *= 1.5;
		ASSERT_EQUAL(3, vecC.x());
		ASSERT_EQUAL(7.5, vecC.y());
		ASSERT_EQUAL(16.5, vecC.z());
	}
	// *= (generic factor)
	{
		Vector3 vecC = vecA;
		vecC *= short(3);
		ASSERT_EQUAL(6, vecC.x());
		ASSERT_EQUAL(15, vecC.y());
		ASSERT_EQUAL(33, vecC.z());
	}
	// /= (factor)
	{
		Vector3 c = vecA;
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
		Vector3 c = vecA;
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

AUTO_UNIT_TEST(vector3_non_member_operators)
{
	// FIXME!
	Vector3 vecA(2,5,11);
	Vector3 vecB(10,20,30);

	// +
	{
		Vector3 vecC = vecA + vecA + vecA;
		ASSERT_EQUAL(6, vecC.x());
		ASSERT_EQUAL(15, vecC.y());
		ASSERT_EQUAL(33, vecC.z());

		Vector3 vecD = vecC + vecB;
		ASSERT_EQUAL(16, vecD.x());
		ASSERT_EQUAL(35, vecD.y());
		ASSERT_EQUAL(63, vecD.z());
	}
	// -
	{
		Vector3 vecC = vecA - vecA - vecA;
		ASSERT_EQUAL(-2, vecC.x());
		ASSERT_EQUAL(-5, vecC.y());
		ASSERT_EQUAL(-11, vecC.z());

		Vector3 vecD = vecC - vecB;
		ASSERT_EQUAL(-12, vecD.x());
		ASSERT_EQUAL(-25, vecD.y());
		ASSERT_EQUAL(-41, vecD.z());
	}
	// * (factor left)
	{
		Vector3 vecC = 2.0 * (2.0 * vecA);
		ASSERT_EQUAL(8, vecC.x());
		ASSERT_EQUAL(20, vecC.y());
		ASSERT_EQUAL(44, vecC.z());

		Vector3 vecD = 3.0 * (-10.0 * (5.0 * vecB));
		ASSERT_EQUAL(-1500, vecD.x());
		ASSERT_EQUAL(-3000, vecD.y());
		ASSERT_EQUAL(-4500, vecD.z());
	}
	// * (factor right)
	{
		Vector3 vecC = ((vecA * 2.0) * 2.0);
		ASSERT_EQUAL(8, vecC.x());
		ASSERT_EQUAL(20, vecC.y());
		ASSERT_EQUAL(44, vecC.z());

		Vector3 vecD = ((vecB * 5.0) * -10.0) * 3.0;
		ASSERT_EQUAL(-1500, vecD.x());
		ASSERT_EQUAL(-3000, vecD.y());
		ASSERT_EQUAL(-4500, vecD.z());
	}
	// / (factor right)
	{
		Vector3 vecC = ((vecA / 2.0) / 2.0);
		ASSERT_EQUAL(0.5, vecC.x());
		ASSERT_EQUAL(1.25, vecC.y());
		ASSERT_EQUAL(2.75, vecC.z());

		Vector3 vecD = ((vecB / 5.0) / -10.0) / 2.0;
		ASSERT_EQUAL(-0.1, vecD.x());
		ASSERT_EQUAL(-0.2, vecD.y());
		ASSERT_EQUAL(-0.3, vecD.z());
	}
	// / (factor generic right)
	{
		Vector3 vecC = ((vecA / 2.0f) / int(2));
		ASSERT_EQUAL(0.5, vecC.x());
		ASSERT_EQUAL(1.25, vecC.y());
		ASSERT_EQUAL(2.75, vecC.z());

		Vector3 vecD = ((vecB / 5.0f) / long(-10)) / short(2);
		ASSERT_EQUAL(-0.1, vecD.x());
		ASSERT_EQUAL(-0.2, vecD.y());
		ASSERT_EQUAL(-0.3, vecD.z());
	}
	// * (factor generic left)
	{
		Vector3 vecC = 2.0f * (long(2) * vecA);
		ASSERT_EQUAL(8, vecC.x());
		ASSERT_EQUAL(20, vecC.y());
		ASSERT_EQUAL(44, vecC.z());

		Vector3 vecD = float(3) * (char(-10) * (short(5) * vecB));
		ASSERT_EQUAL(-1500, vecD.x());
		ASSERT_EQUAL(-3000, vecD.y());
		ASSERT_EQUAL(-4500, vecD.z());
	}
	// * (factor generic right)
	{
		Vector3 vecC = ((vecA * int(2)) * float(2));
		ASSERT_EQUAL(8, vecC.x());
		ASSERT_EQUAL(20, vecC.y());
		ASSERT_EQUAL(44, vecC.z());

		Vector3 vecD = ((vecB * char(5)) * float(-10)) * int(3);
		ASSERT_EQUAL(-1500, vecD.x());
		ASSERT_EQUAL(-3000, vecD.y());
		ASSERT_EQUAL(-4500, vecD.z());
	}
	// - (unary)
	{
		Vector3 vecC = -vecA;
		ASSERT_EQUAL(-2, vecC.x());
		ASSERT_EQUAL(-5, vecC.y());
		ASSERT_EQUAL(-11, vecC.z());

		Vector3 vecD = -vecB;
		ASSERT_EQUAL(-10, vecD.x());
		ASSERT_EQUAL(-20, vecD.y());
		ASSERT_EQUAL(-30, vecD.z());
	}
}

AUTO_UNIT_TEST(vector3_non_member_functions)
{
	// dotprod
	{
		ASSERT_EQUAL(81, dotprod(Vector3(1,4,8), Vector3(1,4,8)));
		ASSERT_EQUAL(32, dotprod(Vector3(1,2,3), Vector3(4,5,6)));
	}
	// length
	{
		ASSERT_EQUAL(9, length(Vector3(1,4,8)));
	}
	// unit
	{
		Vector3 c = unit(Vector3(174,282,389)); // length 511
		ASSERT_EQUAL(0.340508806262, c.x()); // 174/511
		ASSERT_EQUAL(0.551859099804, c.y()); // 282/511
		ASSERT_EQUAL(0.761252446184, c.z()); // 389/511
	}
	// invert
	{
		Vector3 c = invert(Vector3(2, 5, 8));
		ASSERT_EQUAL(0.500, c.x());
		ASSERT_EQUAL(0.200, c.y());
		ASSERT_EQUAL(0.125, c.z());
	}
	// averageComponent
	{
		ASSERT_EQUAL(6, averageComponent(Vector3(4,6,8)));
		ASSERT_EQUAL(6, averageComponent(Vector3(4,8,6)));
		ASSERT_EQUAL(6, averageComponent(Vector3(8,4,6)));
		ASSERT_EQUAL(6, averageComponent(Vector3(8,6,4)));
		ASSERT_EQUAL(6, averageComponent(Vector3(6,4,8)));
		ASSERT_EQUAL(6, averageComponent(Vector3(6,8,4)));

		ASSERT_EQUAL(66.6666666, averageComponent(Vector3(0,100,100)));
		ASSERT_EQUAL(100, averageComponent(Vector3(0,100,200)));
		ASSERT_EQUAL(5, averageComponent(Vector3(4,5,6)));
	}
	// maxComponent
	{
		ASSERT_EQUAL(100, maxComponent(Vector3(0,50,100)));
		ASSERT_EQUAL(100, maxComponent(Vector3(0,100,50)));
		ASSERT_EQUAL(100, maxComponent(Vector3(50,0,100)));
		ASSERT_EQUAL(100, maxComponent(Vector3(50,100,0)));
		ASSERT_EQUAL(100, maxComponent(Vector3(100,0,50)));
		ASSERT_EQUAL(100, maxComponent(Vector3(100,50,0)));
		ASSERT_EQUAL(0, maxComponent(Vector3(0,0,0)));
		ASSERT_EQUAL(0, maxComponent(Vector3(-1,0,-1)));
		ASSERT_EQUAL(0, maxComponent(Vector3(0,-1,-4)));
	}
	// abs
	{
		Vector3 c = abs(Vector3(-3,5,1));
		ASSERT_EQUAL(3, c.x());
		ASSERT_EQUAL(5, c.y());
		ASSERT_EQUAL(1, c.z());

		c = abs(Vector3(5,-3, 1));
		ASSERT_EQUAL(5, c.x());
		ASSERT_EQUAL(3, c.y());
		ASSERT_EQUAL(1, c.z());

		c = abs(Vector3(5,3, -1));
		ASSERT_EQUAL(5, c.x());
		ASSERT_EQUAL(3, c.y());
		ASSERT_EQUAL(1, c.z());

		c = abs(Vector3(0,0,0));
		ASSERT_EQUAL(0, c.x());
		ASSERT_EQUAL(0, c.y());
		ASSERT_EQUAL(0, c.z());
	}
	//	squared_length
	{
		ASSERT_EQUAL(1620529, squared_length(Vector3(177,788,984)));
		ASSERT_EQUAL(25, squared_length(Vector3(0,3,4)));
		ASSERT_EQUAL(49, squared_length(Vector3(2,3,6)));
	}
	// crossprod
	{
		Vector3 x(1,0,0);
		Vector3 y(0,1,0);
		Vector3 z(0,0,1);

		Vector3 c = crossprod(x,y);
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
