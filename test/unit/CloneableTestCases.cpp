#define PROVIDE_AUTO_TEST_MAIN
#include "blocxx_test/CppUnit/AutoTest.hpp"
#include "panorama/common/Cloneable.hpp"
#include "CopyCounter.hpp"

using panorama::Test::CopyCounter;

namespace // anonymous
{
	class Cloner : public panorama::Cloneable
	{
	public:
		virtual panorama::CloneableRef clone() const
		{
			return panorama::CloneableRef(new Cloner(*this));
		}

	private:
		CopyCounter c;
	};

	class ChildCloner : public Cloner
	{
	public:
		virtual panorama::CloneableRef clone() const
		{
			return panorama::CloneableRef(new ChildCloner(*this));
		}

	private:
		CopyCounter c2;
	};

	class GrandchildCloner : public ChildCloner
	{
	public:
		virtual panorama::CloneableRef clone() const
		{
			return panorama::CloneableRef(new GrandchildCloner(*this));
		}

	private:
		CopyCounter c3;
	};
} // end anonymous namespace


AUTO_UNIT_TEST(test_simpleClone)
{
	CopyCounter::resetCounts();
	unitAssertEquals(0, CopyCounter::construct_count);
	unitAssertEquals(0, CopyCounter::destruct_count);
	unitAssertEquals(0, CopyCounter::copy_count);
	unitAssertEquals(0, CopyCounter::assign_count);
	{
		Cloner c;
		unitAssertEquals(1, CopyCounter::construct_count);
		c.clone();
		unitAssertEquals(1, CopyCounter::copy_count); // The clone (return value)
		unitAssertEquals(1, CopyCounter::destruct_count); // The return value
	}
	unitAssertEquals(1, CopyCounter::construct_count);
	unitAssertEquals(2, CopyCounter::destruct_count);
	unitAssertEquals(1, CopyCounter::copy_count);
	unitAssertEquals(0, CopyCounter::assign_count);
}

// The same as test_simpleClone with doubling of every count due to use in both
// the child class and the parent class.
AUTO_UNIT_TEST(test_derivedClone)
{
	CopyCounter::resetCounts();
	unitAssertEquals(0, CopyCounter::construct_count);
	unitAssertEquals(0, CopyCounter::destruct_count);
	unitAssertEquals(0, CopyCounter::copy_count);
	unitAssertEquals(0, CopyCounter::assign_count);
	{
		ChildCloner c;
		unitAssertEquals(2, CopyCounter::construct_count);
		c.clone();
		unitAssertEquals(2, CopyCounter::copy_count); // The clone (return value)
		unitAssertEquals(2, CopyCounter::destruct_count); // The return value
	}
	unitAssertEquals(2, CopyCounter::construct_count);
	unitAssertEquals(4, CopyCounter::destruct_count);
	unitAssertEquals(2, CopyCounter::copy_count);
	unitAssertEquals(0, CopyCounter::assign_count);
}

AUTO_UNIT_TEST(test_deeperDerivedClone)
{
	CopyCounter::resetCounts();
	unitAssertEquals(0, CopyCounter::construct_count);
	unitAssertEquals(0, CopyCounter::destruct_count);
	unitAssertEquals(0, CopyCounter::copy_count);
	unitAssertEquals(0, CopyCounter::assign_count);
	{
		GrandchildCloner c;
		unitAssertEquals(3, CopyCounter::construct_count);
		c.clone();
		unitAssertEquals(3, CopyCounter::copy_count); // The clone (return value)
		unitAssertEquals(3, CopyCounter::destruct_count); // The return value
	}
	unitAssertEquals(3, CopyCounter::construct_count);
	unitAssertEquals(6, CopyCounter::destruct_count);
	unitAssertEquals(3, CopyCounter::copy_count);
	unitAssertEquals(0, CopyCounter::assign_count);
}
