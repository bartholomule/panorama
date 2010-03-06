#define PROVIDE_AUTO_TEST_MAIN
#include "AutoTest.hpp"
#include "panorama/common/Types.hpp"

using namespace panorama;

double DELTA = 0.00001;
#define ASSERT_EQUAL(a, b) unitAssertDoublesEqual((a), (b), DELTA)
#define ASSERT_VECTORS_EQUAL(a, b) ASSERT_EQUAL((a).x(), (b).x()); ASSERT_EQUAL((a).y(), (b).y()); ASSERT_EQUAL((a).z(), (b).z())

AUTO_UNIT_TEST(frame_string_convert)
{
	Vector3 u(1,0,0);
	Vector3 v(0,1,0);
	Vector3 w(0,0,1);
	Point3 o(1,2,3);
	Frame f(o,u,v,w);
	unitAssertEquals("{(1,2,3),<1,0,0>,<0,1,0>,<0,0,1>}", panorama::toString(f));
	unitAssertEquals("Frame\n{\n  origin = (1,2,3);\n  u = <1,0,0>;\n  v = <0,1,0>;\n  w = <0,0,1>;\n}", toStringAsMembers(f));
	ONB::CanBeStringDumpedTag foo;
}

AUTO_UNIT_TEST(onb_identity_transform)
{
	Frame f; // no transform
	Vector3 x(1,0,0);
	Vector3 y(0,1,0);
	Vector3 z(0,0,1);

	ASSERT_VECTORS_EQUAL(x, f.globalToLocal(x));
	ASSERT_VECTORS_EQUAL(x, f.localToGlobal(x));

	ASSERT_VECTORS_EQUAL(y, f.globalToLocal(y));
	ASSERT_VECTORS_EQUAL(y, f.localToGlobal(y));

	ASSERT_VECTORS_EQUAL(z, f.globalToLocal(z));
	ASSERT_VECTORS_EQUAL(z, f.localToGlobal(z));
}

AUTO_UNIT_TEST(onb_identity_transform_explicit)
{
	Vector3 x(1,0,0);
	Vector3 y(0,1,0);
	Vector3 z(0,0,1);
	Point3 o(0,0,0);
	Frame f(o, x, y, z); // no transform

	ASSERT_VECTORS_EQUAL(x, f.globalToLocal(x));
	ASSERT_VECTORS_EQUAL(x, f.localToGlobal(x));

	ASSERT_VECTORS_EQUAL(y, f.globalToLocal(y));
	ASSERT_VECTORS_EQUAL(y, f.localToGlobal(y));

	ASSERT_VECTORS_EQUAL(z, f.globalToLocal(z));
	ASSERT_VECTORS_EQUAL(z, f.localToGlobal(z));
}

AUTO_UNIT_TEST(onb_identity_transform_explicit_normalized)
{
	Vector3 x(1,0,0);
	Vector3 y(0,1,0);
	Vector3 z(0,0,1);
	Point3 o(0,0,0);
	Frame f(o, 2*x, 3*y, 4*z); // no net transform as these are all normalized

	ASSERT_VECTORS_EQUAL(x, f.globalToLocal(x));
	ASSERT_VECTORS_EQUAL(x, f.localToGlobal(x));

	ASSERT_VECTORS_EQUAL(y, f.globalToLocal(y));
	ASSERT_VECTORS_EQUAL(y, f.localToGlobal(y));

	ASSERT_VECTORS_EQUAL(z, f.globalToLocal(z));
	ASSERT_VECTORS_EQUAL(z, f.localToGlobal(z));
}


AUTO_UNIT_TEST(onb_translate)
{
	Vector3 x(1,0,0);
	Vector3 y(0,1,0);
	Vector3 z(0,0,1);

	Point3 o(1,2,3);
	Frame f(o, x, y, z); // Simple translate by (1,2,3)

	Point3 p1(0,0,0);
	Point3 p2(3,2,1);

	ASSERT_VECTORS_EQUAL(Point3(-1,-2,-3), f.globalToLocal(p1));
	ASSERT_VECTORS_EQUAL(Point3(1, 2, 3), f.localToGlobal(p1));

	ASSERT_VECTORS_EQUAL(Point3(2, 0, -2), f.globalToLocal(p2));
	ASSERT_VECTORS_EQUAL(Point3(4, 4, 4), f.localToGlobal(p2));

	// No rotation is done.
	ASSERT_VECTORS_EQUAL(x, f.globalToLocal(x));
	ASSERT_VECTORS_EQUAL(x, f.localToGlobal(x));

	ASSERT_VECTORS_EQUAL(y, f.globalToLocal(y));
	ASSERT_VECTORS_EQUAL(y, f.localToGlobal(y));

	ASSERT_VECTORS_EQUAL(z, f.globalToLocal(z));
	ASSERT_VECTORS_EQUAL(z, f.localToGlobal(z));
}

AUTO_UNIT_TEST(onb_rotate_90_degrees_around_z)
{
	Vector3 u(0,1,0);
	Vector3 v(-1,0,0);
	Vector3 w(0,0,1);

	Vector3 x(1,0,0);
	Vector3 y(0,1,0);
	Vector3 z(0,0,1);

	Point3 o(0,0,0);
	Frame f(o, u, v, w); // Simple rotation 90 degrees around Z

	Point3 p1(0,0,0);
	Point3 p2(3,2,1);

	ASSERT_VECTORS_EQUAL(p1, f.globalToLocal(p1));
	ASSERT_VECTORS_EQUAL(p1, f.localToGlobal(p1));

	ASSERT_VECTORS_EQUAL(Point3(2,-3,1), f.globalToLocal(p2));
	ASSERT_VECTORS_EQUAL(Point3(-2,3,1), f.localToGlobal(p2));

	ASSERT_VECTORS_EQUAL(-y, f.globalToLocal(x));
	ASSERT_VECTORS_EQUAL(y, f.localToGlobal(x));

	ASSERT_VECTORS_EQUAL(x, f.globalToLocal(y));
	ASSERT_VECTORS_EQUAL(-x, f.localToGlobal(y));

	ASSERT_VECTORS_EQUAL(z, f.globalToLocal(z));
	ASSERT_VECTORS_EQUAL(z, f.localToGlobal(z));
}

AUTO_UNIT_TEST(onb_rotate_90_degrees_around_z_and_translate)
{
	Vector3 u(0,1,0);
	Vector3 v(-1,0,0);
	Vector3 w(0,0,1);

	Vector3 x(1,0,0);
	Vector3 y(0,1,0);
	Vector3 z(0,0,1);
	Point3 o(1,2,3);
	Frame f(o, u, v, w); // Simple rotation 90 degrees around Z

	Point3 p1(0,0,0);
	Point3 p2(3,2,1);

	ASSERT_VECTORS_EQUAL(Point3(-2,1,-3), f.globalToLocal(p1));
	ASSERT_VECTORS_EQUAL(Point3(1,2,3), f.localToGlobal(p1));

	ASSERT_VECTORS_EQUAL(Point3(0,-2,-2), f.globalToLocal(p2));
	ASSERT_VECTORS_EQUAL(Point3(-1,5,4), f.localToGlobal(p2));

	ASSERT_VECTORS_EQUAL(-y, f.globalToLocal(x));
	ASSERT_VECTORS_EQUAL(y, f.localToGlobal(x));

	ASSERT_VECTORS_EQUAL(x, f.globalToLocal(y));
	ASSERT_VECTORS_EQUAL(-x, f.localToGlobal(y));

	ASSERT_VECTORS_EQUAL(z, f.globalToLocal(z));
	ASSERT_VECTORS_EQUAL(z, f.localToGlobal(z));
}

AUTO_UNIT_TEST(onb_rotate_merge1)
{
	// This u,v,w is a 180 degree rotation, so applying it twice should result in no net rotation.
	Vector3 u(-1,0,0);
	Vector3 v(0,-1,0);
	Vector3 w(0,0,1);

	Vector3 x(1,0,0);
	Vector3 y(0,1,0);
	Vector3 z(0,0,1);
	Point3 o(1,2,0); // Shifted x by 1, y by 2, rotated 180 degrees and shifted x by 1, y by 2 again means no net movement.
	Frame f = mergeFrames(Frame(o,u,v,w), Frame(o,u,v,w));;

	Point3 p1(0,0,0);
	Point3 p2(3,2,1);

	ASSERT_VECTORS_EQUAL(p1, f.globalToLocal(p1));
	ASSERT_VECTORS_EQUAL(p1, f.localToGlobal(p1));

	ASSERT_VECTORS_EQUAL(p2, f.globalToLocal(p2));
	ASSERT_VECTORS_EQUAL(p2, f.localToGlobal(p2));

	ASSERT_VECTORS_EQUAL(x, f.globalToLocal(x));
	ASSERT_VECTORS_EQUAL(x, f.localToGlobal(x));

	ASSERT_VECTORS_EQUAL(y, f.globalToLocal(y));
	ASSERT_VECTORS_EQUAL(y, f.localToGlobal(y));

	ASSERT_VECTORS_EQUAL(z, f.globalToLocal(z));
	ASSERT_VECTORS_EQUAL(z, f.localToGlobal(z));
}

AUTO_UNIT_TEST(onb_rotate_merge2)
{
	// This u,v,w is a 180 degree rotation, so applying it twice should result in no net rotation.
	Vector3 u(-1,0,0);
	Vector3 v(0,-1,0);
	Vector3 w(0,0,1);

	Vector3 x(1,0,0);
	Vector3 y(0,1,0);
	Vector3 z(0,0,1);
	Point3 o(1,2,0);
	// This merged frame results in a net translate of <1,-1,0> (local to global)
	Frame f = mergeFrames(Frame(o,u,v,w), Frame(o - x + y,u,v,w));;

	Point3 p1(0,0,0);
	Point3 p2(3,2,1);

	ASSERT_VECTORS_EQUAL(p1 - x + y, f.globalToLocal(p1));
	ASSERT_VECTORS_EQUAL(p1 + x - y, f.localToGlobal(p1));

	ASSERT_VECTORS_EQUAL(p2 - x + y, f.globalToLocal(p2));
	ASSERT_VECTORS_EQUAL(p2 + x - y, f.localToGlobal(p2));

	ASSERT_VECTORS_EQUAL(x, f.globalToLocal(x));
	ASSERT_VECTORS_EQUAL(x, f.localToGlobal(x));

	ASSERT_VECTORS_EQUAL(y, f.globalToLocal(y));
	ASSERT_VECTORS_EQUAL(y, f.localToGlobal(y));

	ASSERT_VECTORS_EQUAL(z, f.globalToLocal(z));
	ASSERT_VECTORS_EQUAL(z, f.localToGlobal(z));
}

// FIXME! More tests needed.
