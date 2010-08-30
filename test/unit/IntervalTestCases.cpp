#define PROVIDE_AUTO_TEST_MAIN
#include "blocxx_test/CppUnit/AutoTest.hpp"
#include "panorama/common/GenericInterval.hpp"

using namespace panorama;

typedef GenericInterval<int> interval;

AUTO_UNIT_TEST(interval_string_convert)
{
	interval i;
	unitAssertEquals("[empty]", panorama::toString(i));
	unitAssertEquals("Interval\n{\n  begin = 0;\n  end = 0;\n}", toStringAsMembers(i));

	interval i2(-2,6);
	unitAssertEquals("[-2,6]", panorama::toString(i2));
	unitAssertEquals("Interval\n{\n  begin = -2;\n  end = 6;\n}", toStringAsMembers(i2));
}

AUTO_UNIT_TEST(interval_begin_end_empty)
{
	interval i(1,10);
	unitAssertEquals(1, i.begin());
	unitAssertEquals(10, i.end());
	unitAssertEquals(false, i.empty());

	unitAssertEquals(true, interval().empty());
	unitAssertEquals(true, interval(1,1).empty());
}

AUTO_UNIT_TEST(interval_inside)
{
	interval i(1,10);
	unitAssertEquals(false, i.inside(0));
	unitAssertEquals(false, i.inside(1)); // The endpoint is not considered inside.
	unitAssertEquals(true, i.inside(2));
	unitAssertEquals(true, i.inside(5));
	unitAssertEquals(true, i.inside(9));
	unitAssertEquals(false, i.inside(10)); // The endpoint is not considered inside.
	unitAssertEquals(false, i.inside(11));
}

AUTO_UNIT_TEST(interval_outside)
{
	interval i(1,10);
	unitAssertEquals(true, i.outside(0));
	unitAssertEquals(true, i.outside(1)); // The endpoint is considered outside.
	unitAssertEquals(false, i.outside(2));
	unitAssertEquals(false, i.outside(5));
	unitAssertEquals(false, i.outside(9));
	unitAssertEquals(true, i.outside(10)); // The endpoint is considered outside.
	unitAssertEquals(true, i.outside(11));
}

AUTO_UNIT_TEST(interval_subset)
{
	interval i1(1,5);
	interval i2(5,10);
	interval i3(1,10); // Overlaps completely i1 and i2
	interval i4(-3,1);
	interval i5(10,15);
	interval i6(-9,-3);
	interval i7(20,27);
	interval i8(3,7); // Overlaps completely i1 and i2, but is only a subset of i3

	unitAssertEquals(true, i1.subset(i1));
	unitAssertEquals(false, i1.subset(i2));
	unitAssertEquals(false, i1.subset(i3));
	unitAssertEquals(false, i1.subset(i4));
	unitAssertEquals(false, i1.subset(i5));
	unitAssertEquals(false, i1.subset(i6));
	unitAssertEquals(false, i1.subset(i7));
	unitAssertEquals(false, i1.subset(i8));

	unitAssertEquals(false, i2.subset(i1));
	unitAssertEquals(true, i2.subset(i2));
	unitAssertEquals(false, i2.subset(i3));
	unitAssertEquals(false, i2.subset(i4));
	unitAssertEquals(false, i2.subset(i5));
	unitAssertEquals(false, i2.subset(i6));
	unitAssertEquals(false, i2.subset(i7));
	unitAssertEquals(false, i2.subset(i8));

	unitAssertEquals(true, i3.subset(i1));
	unitAssertEquals(true, i3.subset(i2));
	unitAssertEquals(true, i3.subset(i3));
	unitAssertEquals(false, i3.subset(i4));
	unitAssertEquals(false, i3.subset(i5));
	unitAssertEquals(false, i3.subset(i6));
	unitAssertEquals(false, i3.subset(i7));
	unitAssertEquals(true, i3.subset(i8));
}

AUTO_UNIT_TEST(interval_overlaps)
{
	interval i1(1,5);
	interval i2(5,10);
	interval i3(1,10);
	interval i4(-3,1);
	interval i5(10,15);
	interval i6(-9,-3);
	interval i7(20,27);
	interval i8(3,7);

	unitAssertEquals(true, i1.overlaps(i1));
	unitAssertEquals(false, i1.overlaps(i2));
	unitAssertEquals(true, i1.overlaps(i3));
	unitAssertEquals(false, i1.overlaps(i4));
	unitAssertEquals(false, i1.overlaps(i5));
	unitAssertEquals(false, i1.overlaps(i6));
	unitAssertEquals(false, i1.overlaps(i7));
	unitAssertEquals(true, i1.overlaps(i8));

	unitAssertEquals(false, i2.overlaps(i1));
	unitAssertEquals(true, i2.overlaps(i2));
	unitAssertEquals(true, i2.overlaps(i3));
	unitAssertEquals(false, i2.overlaps(i4));
	unitAssertEquals(false, i2.overlaps(i5));
	unitAssertEquals(false, i2.overlaps(i6));
	unitAssertEquals(false, i2.overlaps(i7));
	unitAssertEquals(true, i2.overlaps(i8));

	unitAssertEquals(true, i3.overlaps(i1));
	unitAssertEquals(true, i3.overlaps(i2));
	unitAssertEquals(true, i3.overlaps(i3));
	unitAssertEquals(false, i3.overlaps(i4));
	unitAssertEquals(false, i3.overlaps(i5));
	unitAssertEquals(false, i3.overlaps(i6));
	unitAssertEquals(false, i3.overlaps(i7));
	unitAssertEquals(true, i3.overlaps(i8));
}

AUTO_UNIT_TEST(interval_intersection)
{
	interval i1(1,5);
	interval i2(3,7);
	interval i3(5,10);
	interval i4(1,10);

	// (3,5)
	{
		interval j1 = intersection(i1, i2);
		unitAssertEquals(3, j1.begin());
		unitAssertEquals(5, j1.end());

		interval j2 = intersection(i2, i1);
		unitAssertEquals(3, j2.begin());
		unitAssertEquals(5, j2.end());
	}

	// (5,7)
	{
		interval j1 = intersection(i3, i2);
		unitAssertEquals(5, j1.begin());
		unitAssertEquals(7, j1.end());

		interval j2 = intersection(i2, i3);
		unitAssertEquals(5, j2.begin());
		unitAssertEquals(7, j2.end());
	}

	// (1,5)
	{
		interval j1 = intersection(i1, i4);
		unitAssertEquals(1, j1.begin());
		unitAssertEquals(5, j1.end());

		interval j2 = intersection(i4, i1);
		unitAssertEquals(1, j2.begin());
		unitAssertEquals(5, j2.end());
	}

	// (5,10)
	{
		interval j1 = intersection(i3, i4);
		unitAssertEquals(5, j1.begin());
		unitAssertEquals(10, j1.end());

		interval j2 = intersection(i4, i3);
		unitAssertEquals(5, j2.begin());
		unitAssertEquals(10, j2.end());
	}

	// (3,7)
	{
		interval j1 = intersection(i2, i4);
		unitAssertEquals(3, j1.begin());
		unitAssertEquals(7, j1.end());

		interval j2 = intersection(i4, i2);
		unitAssertEquals(3, j2.begin());
		unitAssertEquals(7, j2.end());
	}

	// No intersection
	unitAssertEquals(true, intersection(i1,i3).empty());
	unitAssertEquals(true, intersection(i3,i1).empty());
	unitAssertEquals(true, intersection(interval(0,1), interval(2,3)).empty());
	unitAssertEquals(true, intersection(interval(2,3), interval(0,1)).empty());
}

AUTO_UNIT_TEST(interval_compare)
{
	unitAssertEquals(false, interval() < interval());
	unitAssertEquals(false, interval() > interval());

	unitAssertEquals(false, interval() < interval(1,2));
	unitAssertEquals(false, interval() > interval(1,2));
	unitAssertEquals(false, interval(1,2) < interval());
	unitAssertEquals(false, interval(1,2) > interval());

	unitAssertEquals(false, interval(1,2) < interval(1,2));
	unitAssertEquals(false, interval(1,2) > interval(1,2));

	unitAssertEquals(true, interval(1,2) < interval(2,3));
	unitAssertEquals(false, interval(1,2) > interval(2,3));

	unitAssertEquals(true, interval(1,2) < interval(2,3));
	unitAssertEquals(true, interval(2,3) > interval(1,2));

	unitAssertEquals(true, interval(1,2) < 3.0);
	unitAssertEquals(true, 3.0 > interval(1,2));
	unitAssertEquals(true, 0 < interval(1,2));
	unitAssertEquals(true, interval(1,2) < 2);
	unitAssertEquals(true, 1 < interval(1,2));

	unitAssertEquals(false, 2 < interval(1,3));
	unitAssertEquals(false, interval(1,3) < 2);
	unitAssertEquals(false, 2.5 < interval(1,3));
	unitAssertEquals(false, interval(1,3) < 2.5);
}
