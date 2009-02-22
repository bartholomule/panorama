#define PROVIDE_AUTO_TEST_MAIN
#include "AutoTest.hpp"
#include "CopyCounter.hpp"

using panorama::Test::CopyCounter;

AUTO_UNIT_TEST(test_counter_construct)
{
	CopyCounter::resetCounts();
	unitAssertEquals(0, CopyCounter::construct_count);
	unitAssertEquals(0, CopyCounter::destruct_count);
	unitAssertEquals(0, CopyCounter::copy_count);
	unitAssertEquals(0, CopyCounter::assign_count);
	{
		CopyCounter c;
	}
	unitAssertEquals(1, CopyCounter::construct_count); // c
	unitAssertEquals(1, CopyCounter::destruct_count); // c
	unitAssertEquals(0, CopyCounter::copy_count);
	unitAssertEquals(0, CopyCounter::assign_count);
}

AUTO_UNIT_TEST(test_counter_copy)
{
	CopyCounter::resetCounts();
	unitAssertEquals(0, CopyCounter::construct_count);
	unitAssertEquals(0, CopyCounter::destruct_count);
	unitAssertEquals(0, CopyCounter::copy_count);
	unitAssertEquals(0, CopyCounter::assign_count);
	{
		CopyCounter c;
		CopyCounter d = c;
	}
	unitAssertEquals(1, CopyCounter::construct_count); // c
	unitAssertEquals(2, CopyCounter::destruct_count); // c & d
	unitAssertEquals(1, CopyCounter::copy_count); // d
	unitAssertEquals(0, CopyCounter::assign_count);
}

AUTO_UNIT_TEST(test_counter_assign)
{
	CopyCounter::resetCounts();
	unitAssertEquals(0, CopyCounter::construct_count);
	unitAssertEquals(0, CopyCounter::destruct_count);
	unitAssertEquals(0, CopyCounter::copy_count);
	unitAssertEquals(0, CopyCounter::assign_count);
	{
		CopyCounter c;
		CopyCounter d;
		d = c;
	}
	unitAssertEquals(2, CopyCounter::construct_count); // c & d
	unitAssertEquals(2, CopyCounter::destruct_count); // c & d
	unitAssertEquals(1, CopyCounter::assign_count); // d
	unitAssertEquals(0, CopyCounter::copy_count);
}

AUTO_UNIT_TEST(test_counter_temp)
{
	CopyCounter::resetCounts();
	unitAssertEquals(0, CopyCounter::construct_count);
	unitAssertEquals(0, CopyCounter::destruct_count);
	unitAssertEquals(0, CopyCounter::copy_count);
	unitAssertEquals(0, CopyCounter::assign_count);
	{
		CopyCounter c;
		CopyCounter d;
		d = CopyCounter(c);
	}
	unitAssertEquals(2, CopyCounter::construct_count); // c, d
	unitAssertEquals(3, CopyCounter::destruct_count); // c, d, temp
	unitAssertEquals(1, CopyCounter::assign_count); // d
	unitAssertEquals(1, CopyCounter::copy_count); // temp
}
