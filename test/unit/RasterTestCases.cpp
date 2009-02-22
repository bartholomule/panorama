#define PROVIDE_AUTO_TEST_MAIN
#include "AutoTest.hpp"
#include "panorama/common/Raster.hpp"

AUTO_UNIT_TEST(simple_raster_ops)
{
	panorama::Raster<int> simple(5,6);
	unitAssert(!simple.empty());
	unitAssertEquals(5u, simple.getWidth());
	unitAssertEquals(6u, simple.getHeight());
	unitAssertEquals(30u, simple.getNumPixels());

	const panorama::Raster<int> simple2 = simple;
	unitAssert(!simple2.empty());
	unitAssertEquals(5u, simple2.getWidth());
	unitAssertEquals(6u, simple2.getHeight());
	unitAssertEquals(30u, simple2.getNumPixels());
}

AUTO_UNIT_TEST(raster_bounds_checks)
{
	panorama::Raster<int> raster(5,6);
	{
		unitAssertThrowsEx(raster[6][0], blocxx::OutOfBoundsException);
		unitAssertThrowsEx(raster(0,6), blocxx::OutOfBoundsException);
		unitAssertThrowsEx(raster[0][5], blocxx::OutOfBoundsException);
		unitAssertThrowsEx(raster(5,0), blocxx::OutOfBoundsException);
		unitAssertThrowsEx(raster(5,6), blocxx::OutOfBoundsException);
		unitAssertNoThrow(raster[0][0]);
		unitAssertNoThrow(raster[5][4]);
		unitAssertNoThrow(raster(0,0));
		unitAssertNoThrow(raster(4,5));
	}

	const panorama::Raster<int> raster2 = raster;
	{
		unitAssertThrowsEx(raster2[6][0], blocxx::OutOfBoundsException);
		unitAssertThrowsEx(raster2(0,6), blocxx::OutOfBoundsException);
		unitAssertThrowsEx(raster2[0][5], blocxx::OutOfBoundsException);
		unitAssertThrowsEx(raster2(5,0), blocxx::OutOfBoundsException);
		unitAssertThrowsEx(raster2(5,6), blocxx::OutOfBoundsException);
		unitAssertNoThrow(raster2[0][0]);
		unitAssertNoThrow(raster2[5][4]);
		unitAssertNoThrow(raster2(0,0));
		unitAssertNoThrow(raster2(4,5));
	}
}

namespace
{
	panorama::Raster<int> getFilledRaster(int width, int height)
	{
		panorama::Raster<int> retval(width, height);

		for(int y = 0; y < height; ++y)
		{
			panorama::Scanline<int> line = retval[y];

			for(int x = 0; x < width; ++x)
			{
				line[x] = (x + 1) * (y + 1);
			}
		}
		return retval;
	}
}

AUTO_UNIT_TEST(raster_reinterpret)
{
	panorama::Raster<int> raster = getFilledRaster(3,3);
	const int* data = raster.reinterpret<const int*>();
	unitAssert(data);
	unitAssertEquals(1, data[0 * 3 + 0]);
	unitAssertEquals(2, data[0 * 3 + 1]);
	unitAssertEquals(3, data[0 * 3 + 2]);
	unitAssertEquals(2, data[1 * 3 + 0]);
	unitAssertEquals(4, data[1 * 3 + 1]);
	unitAssertEquals(6, data[1 * 3 + 2]);
	unitAssertEquals(3, data[2 * 3 + 0]);
	unitAssertEquals(6, data[2 * 3 + 1]);
	unitAssertEquals(9, data[2 * 3 + 2]);
}

AUTO_UNIT_TEST(raster_resize_regular)
{
	// FIXME!
}

AUTO_UNIT_TEST(raster_resize_fill)
{
	// FIXME!
}

AUTO_UNIT_TEST(raster_subraster)
{
	// FIXME!
}
