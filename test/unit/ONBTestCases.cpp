#define PROVIDE_AUTO_TEST_MAIN
#include "blocxx_test/CppUnit/AutoTest.hpp"
#include "panorama/common/Types.hpp"

using namespace panorama;

double DELTA = 0.00001;
#define ASSERT_EQUAL(a, b) unitAssertDoublesEqual((a), (b), DELTA)
#define ASSERT_VECTORS_EQUAL(a, b) ASSERT_EQUAL((a).x(), (b).x()); ASSERT_EQUAL((a).y(), (b).y()); ASSERT_EQUAL((a).z(), (b).z())

AUTO_UNIT_TEST(onb_string_convert)
{
	Vector3 u(1,0,0);
	Vector3 v(0,1,0);
	Vector3 w(0,0,1);
	ONB o(u,v,w);
	unitAssertEquals("{<1,0,0>,<0,1,0>,<0,0,1>}", panorama::toString(o));
	unitAssertEquals("ONB\n{\n  u = <1,0,0>;\n  v = <0,1,0>;\n  w = <0,0,1>;\n}", toStringAsMembers(o));
	ONB::CanBeStringDumpedTag foo;
}

AUTO_UNIT_TEST(onb_identity_transform)
{
	ONB o; // no transform
	Vector3 x(1,0,0);
	Vector3 y(0,1,0);
	Vector3 z(0,0,1);

	ASSERT_VECTORS_EQUAL(x, o.globalToLocal(x));
	ASSERT_VECTORS_EQUAL(x, o.localToGlobal(x));

	ASSERT_VECTORS_EQUAL(y, o.globalToLocal(y));
	ASSERT_VECTORS_EQUAL(y, o.localToGlobal(y));

	ASSERT_VECTORS_EQUAL(z, o.globalToLocal(z));
	ASSERT_VECTORS_EQUAL(z, o.localToGlobal(z));
}

AUTO_UNIT_TEST(onb_identity_transform_explicit)
{
	Vector3 x(1,0,0);
	Vector3 y(0,1,0);
	Vector3 z(0,0,1);
	ONB o(x,y,z); // no transform

	ASSERT_VECTORS_EQUAL(x, o.globalToLocal(x));
	ASSERT_VECTORS_EQUAL(x, o.localToGlobal(x));

	ASSERT_VECTORS_EQUAL(y, o.globalToLocal(y));
	ASSERT_VECTORS_EQUAL(y, o.localToGlobal(y));

	ASSERT_VECTORS_EQUAL(z, o.globalToLocal(z));
	ASSERT_VECTORS_EQUAL(z, o.localToGlobal(z));
}

AUTO_UNIT_TEST(onb_identity_transform_explicit_normalized)
{
	Vector3 x(1,0,0);
	Vector3 y(0,1,0);
	Vector3 z(0,0,1);
	ONB o(2*x,3*y,4*z); // no net transform as these are all normalized

	ASSERT_VECTORS_EQUAL(x, o.globalToLocal(x));
	ASSERT_VECTORS_EQUAL(x, o.localToGlobal(x));

	ASSERT_VECTORS_EQUAL(y, o.globalToLocal(y));
	ASSERT_VECTORS_EQUAL(y, o.localToGlobal(y));

	ASSERT_VECTORS_EQUAL(z, o.globalToLocal(z));
	ASSERT_VECTORS_EQUAL(z, o.localToGlobal(z));
}

AUTO_UNIT_TEST(onb_flip_x)
{
	// This is not a rotation.  This is a mirroring.
	ONB o(Vector3(-1,0,0),Vector3(0,1,0),Vector3(0,0,1));

	Vector3 x(1,0,0);
	Vector3 y(0,1,0);
	Vector3 z(0,0,1);

	ASSERT_VECTORS_EQUAL(-x, o.globalToLocal(x));
	ASSERT_VECTORS_EQUAL(-x, o.localToGlobal(x));
	ASSERT_VECTORS_EQUAL(x, o.globalToLocal(-x));
	ASSERT_VECTORS_EQUAL(x, o.localToGlobal(-x));

	ASSERT_VECTORS_EQUAL(y, o.globalToLocal(y));
	ASSERT_VECTORS_EQUAL(y, o.localToGlobal(y));
	ASSERT_VECTORS_EQUAL(-y, o.globalToLocal(-y));
	ASSERT_VECTORS_EQUAL(-y, o.localToGlobal(-y));

	ASSERT_VECTORS_EQUAL(z, o.globalToLocal(z));
	ASSERT_VECTORS_EQUAL(z, o.localToGlobal(z));
	ASSERT_VECTORS_EQUAL(-z, o.globalToLocal(-z));
	ASSERT_VECTORS_EQUAL(-z, o.localToGlobal(-z));

	ASSERT_VECTORS_EQUAL(-x+y, o.globalToLocal(x+y));
	ASSERT_VECTORS_EQUAL(-x+y, o.localToGlobal(x+y));
	ASSERT_VECTORS_EQUAL(-x+z, o.globalToLocal(x+z));
	ASSERT_VECTORS_EQUAL(-x+z, o.localToGlobal(x+z));
	ASSERT_VECTORS_EQUAL(y+z, o.globalToLocal(y+z));
	ASSERT_VECTORS_EQUAL(y+z, o.localToGlobal(y+z));
}

AUTO_UNIT_TEST(onb_flip_y)
{
	// This is not a rotation.  This is a mirroring.
	ONB o(Vector3(1,0,0),Vector3(0,-1,0),Vector3(0,0,1));

	Vector3 x(1,0,0);
	Vector3 y(0,1,0);
	Vector3 z(0,0,1);

	ASSERT_VECTORS_EQUAL(x, o.globalToLocal(x));
	ASSERT_VECTORS_EQUAL(x, o.localToGlobal(x));
	ASSERT_VECTORS_EQUAL(-x, o.globalToLocal(-x));
	ASSERT_VECTORS_EQUAL(-x, o.localToGlobal(-x));

	ASSERT_VECTORS_EQUAL(-y, o.globalToLocal(y));
	ASSERT_VECTORS_EQUAL(-y, o.localToGlobal(y));
	ASSERT_VECTORS_EQUAL(y, o.globalToLocal(-y));
	ASSERT_VECTORS_EQUAL(y, o.localToGlobal(-y));

	ASSERT_VECTORS_EQUAL(z, o.globalToLocal(z));
	ASSERT_VECTORS_EQUAL(z, o.localToGlobal(z));
	ASSERT_VECTORS_EQUAL(-z, o.globalToLocal(-z));
	ASSERT_VECTORS_EQUAL(-z, o.localToGlobal(-z));

	ASSERT_VECTORS_EQUAL(x-y, o.globalToLocal(x+y));
	ASSERT_VECTORS_EQUAL(x-y, o.localToGlobal(x+y));
	ASSERT_VECTORS_EQUAL(x+z, o.globalToLocal(x+z));
	ASSERT_VECTORS_EQUAL(x+z, o.localToGlobal(x+z));
	ASSERT_VECTORS_EQUAL(-y+z, o.globalToLocal(y+z));
	ASSERT_VECTORS_EQUAL(-y+z, o.localToGlobal(y+z));
}

AUTO_UNIT_TEST(onb_flip_z)
{
	// This is not a rotation.  This is a mirroring.
	ONB o(Vector3(1,0,0),Vector3(0,1,0),Vector3(0,0,-1));

	Vector3 x(1,0,0);
	Vector3 y(0,1,0);
	Vector3 z(0,0,1);

	ASSERT_VECTORS_EQUAL(x, o.globalToLocal(x));
	ASSERT_VECTORS_EQUAL(x, o.localToGlobal(x));
	ASSERT_VECTORS_EQUAL(-x, o.globalToLocal(-x));
	ASSERT_VECTORS_EQUAL(-x, o.localToGlobal(-x));

	ASSERT_VECTORS_EQUAL(y, o.globalToLocal(y));
	ASSERT_VECTORS_EQUAL(y, o.localToGlobal(y));
	ASSERT_VECTORS_EQUAL(-y, o.globalToLocal(-y));
	ASSERT_VECTORS_EQUAL(-y, o.localToGlobal(-y));

	ASSERT_VECTORS_EQUAL(-z, o.globalToLocal(z));
	ASSERT_VECTORS_EQUAL(-z, o.localToGlobal(z));
	ASSERT_VECTORS_EQUAL(z, o.globalToLocal(-z));
	ASSERT_VECTORS_EQUAL(z, o.localToGlobal(-z));

	ASSERT_VECTORS_EQUAL(x+y, o.globalToLocal(x+y));
	ASSERT_VECTORS_EQUAL(x+y, o.localToGlobal(x+y));
	ASSERT_VECTORS_EQUAL(x-z, o.globalToLocal(x+z));
	ASSERT_VECTORS_EQUAL(x-z, o.localToGlobal(x+z));
	ASSERT_VECTORS_EQUAL(y-z, o.globalToLocal(y+z));
	ASSERT_VECTORS_EQUAL(y-z, o.localToGlobal(y+z));
}


AUTO_UNIT_TEST(onb_rotation_90degrees_around_z)
{
	ONB o(Vector3(0,1,0),Vector3(-1,0,0),Vector3(0,0,1));

	Vector3 x(1,0,0);
	Vector3 y(0,1,0);
	Vector3 z(0,0,1);

	ASSERT_VECTORS_EQUAL(-y, o.globalToLocal(x));
	ASSERT_VECTORS_EQUAL(y, o.localToGlobal(x));
	ASSERT_VECTORS_EQUAL(y, o.globalToLocal(-x));
	ASSERT_VECTORS_EQUAL(-y, o.localToGlobal(-x));

	ASSERT_VECTORS_EQUAL(x, o.globalToLocal(y));
	ASSERT_VECTORS_EQUAL(-x, o.localToGlobal(y));
	ASSERT_VECTORS_EQUAL(-x, o.globalToLocal(-y));
	ASSERT_VECTORS_EQUAL(x, o.localToGlobal(-y));

	ASSERT_VECTORS_EQUAL(z, o.globalToLocal(z));
	ASSERT_VECTORS_EQUAL(z, o.localToGlobal(z));
	ASSERT_VECTORS_EQUAL(-z, o.globalToLocal(-z));
	ASSERT_VECTORS_EQUAL(-z, o.localToGlobal(-z));

	ASSERT_VECTORS_EQUAL(x-y, o.globalToLocal(x+y));
	ASSERT_VECTORS_EQUAL(-x+y, o.localToGlobal(x+y));
	ASSERT_VECTORS_EQUAL(-y+z, o.globalToLocal(x+z));
	ASSERT_VECTORS_EQUAL(y+z, o.localToGlobal(x+z));
	ASSERT_VECTORS_EQUAL(x+z, o.globalToLocal(y+z));
	ASSERT_VECTORS_EQUAL(-x+z, o.localToGlobal(y+z));
}

AUTO_UNIT_TEST(onb_rotation_minus90degrees_around_z)
{
	ONB o(Vector3(0,-1,0),Vector3(1,0,0),Vector3(0,0,1));

	Vector3 x(1,0,0);
	Vector3 y(0,1,0);
	Vector3 z(0,0,1);

	ASSERT_VECTORS_EQUAL(y, o.globalToLocal(x));
	ASSERT_VECTORS_EQUAL(-y, o.localToGlobal(x));
	ASSERT_VECTORS_EQUAL(-y, o.globalToLocal(-x));
	ASSERT_VECTORS_EQUAL(y, o.localToGlobal(-x));

	ASSERT_VECTORS_EQUAL(-x, o.globalToLocal(y));
	ASSERT_VECTORS_EQUAL(x, o.localToGlobal(y));
	ASSERT_VECTORS_EQUAL(x, o.globalToLocal(-y));
	ASSERT_VECTORS_EQUAL(-x, o.localToGlobal(-y));

	ASSERT_VECTORS_EQUAL(z, o.globalToLocal(z));
	ASSERT_VECTORS_EQUAL(z, o.localToGlobal(z));
	ASSERT_VECTORS_EQUAL(-z, o.globalToLocal(-z));
	ASSERT_VECTORS_EQUAL(-z, o.localToGlobal(-z));

	ASSERT_VECTORS_EQUAL(-x+y, o.globalToLocal(x+y));
	ASSERT_VECTORS_EQUAL(x-y, o.localToGlobal(x+y));
	ASSERT_VECTORS_EQUAL(y+z, o.globalToLocal(x+z));
	ASSERT_VECTORS_EQUAL(-y+z, o.localToGlobal(x+z));
	ASSERT_VECTORS_EQUAL(-x+z, o.globalToLocal(y+z));
	ASSERT_VECTORS_EQUAL(x+z, o.localToGlobal(y+z));
}

AUTO_UNIT_TEST(onb_rotation_180degrees_around_z)
{
	ONB o(Vector3(-1,0,0),Vector3(0,-1,0),Vector3(0,0,1));

	Vector3 x(1,0,0);
	Vector3 y(0,1,0);
	Vector3 z(0,0,1);

	ASSERT_VECTORS_EQUAL(-x, o.globalToLocal(x));
	ASSERT_VECTORS_EQUAL(-x, o.localToGlobal(x));
	ASSERT_VECTORS_EQUAL(x, o.globalToLocal(-x));
	ASSERT_VECTORS_EQUAL(x, o.localToGlobal(-x));

	ASSERT_VECTORS_EQUAL(-y, o.globalToLocal(y));
	ASSERT_VECTORS_EQUAL(-y, o.localToGlobal(y));
	ASSERT_VECTORS_EQUAL(y, o.globalToLocal(-y));
	ASSERT_VECTORS_EQUAL(y, o.localToGlobal(-y));

	ASSERT_VECTORS_EQUAL(z, o.globalToLocal(z));
	ASSERT_VECTORS_EQUAL(z, o.localToGlobal(z));
	ASSERT_VECTORS_EQUAL(-z, o.globalToLocal(-z));
	ASSERT_VECTORS_EQUAL(-z, o.localToGlobal(-z));

	ASSERT_VECTORS_EQUAL(-x-y, o.globalToLocal(x+y));
	ASSERT_VECTORS_EQUAL(-x-y, o.localToGlobal(x+y));
	ASSERT_VECTORS_EQUAL(-x+z, o.globalToLocal(x+z));
	ASSERT_VECTORS_EQUAL(-x+z, o.localToGlobal(x+z));
	ASSERT_VECTORS_EQUAL(-y+z, o.globalToLocal(y+z));
	ASSERT_VECTORS_EQUAL(-y+z, o.localToGlobal(y+z));
}

// FIXME! More tests needed.
