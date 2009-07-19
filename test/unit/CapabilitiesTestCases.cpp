#define PROVIDE_AUTO_TEST_MAIN
#include "AutoTest.hpp"
#include "panorama/common/Capabilities.hpp"

using panorama::IntersectionCapabilities;

AUTO_UNIT_TEST(simple_operations)
{
	IntersectionCapabilities cap = IntersectionCapabilities::NONE;
	unitAssertEquals(~cap, IntersectionCapabilities::ALL);
	unitAssertEquals(cap, IntersectionCapabilities::NONE);
	unitAssertEquals(~IntersectionCapabilities::NONE, IntersectionCapabilities::ALL);
	unitAssertEquals(~IntersectionCapabilities::ALL, IntersectionCapabilities::NONE);

	unitAssertEquals(cap, ~~cap);
	unitAssertEquals(~cap, ~~~cap);

	unitAssertEquals(cap & IntersectionCapabilities::NONE, IntersectionCapabilities::NONE);
	unitAssertEquals(cap & IntersectionCapabilities::ALL, IntersectionCapabilities::NONE);
	unitAssertEquals((~cap) & IntersectionCapabilities::ALL, IntersectionCapabilities::ALL);

	unitAssertEquals(cap | IntersectionCapabilities::NONE, IntersectionCapabilities::NONE);
	unitAssertEquals(cap | IntersectionCapabilities::ALL, IntersectionCapabilities::ALL);
	unitAssertEquals((~cap) | IntersectionCapabilities::ALL, IntersectionCapabilities::ALL);
}

AUTO_UNIT_TEST(string_dump)
{
	IntersectionCapabilities cap = IntersectionCapabilities::NONE;
	unitAssertEquals(cap.name(), "IntersectionCapabilities");
	unitAssertEquals(cap.toString(), "{NONE}");
	unitAssertEquals(cap.toStringShort(), "");
	cap |= IntersectionCapabilities::UV_CALCULATION;
	unitAssertEquals(cap.toString(), "{UV Calculation}");
	unitAssertEquals(cap.toStringShort(), "U");
}
