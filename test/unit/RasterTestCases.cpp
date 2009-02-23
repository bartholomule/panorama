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
	panorama::Raster<int> raster = getFilledRaster(7,4);
	unitAssertEquals(28u, raster.getNumPixels());
	raster.resize(2,3);
	unitAssertEquals(6u, raster.getNumPixels());
	unitAssertEquals(2u, raster.getWidth());
	unitAssertEquals(3u, raster.getHeight());

	// The data must be preserved...
	unitAssertEquals(1, raster(0,0));
	unitAssertEquals(2, raster(1,0));
	unitAssertEquals(2, raster(0,1));
	unitAssertEquals(4, raster(1,1));
	unitAssertEquals(3, raster(0,2));
	unitAssertEquals(6, raster(1,2));
}

AUTO_UNIT_TEST(raster_resize_fill)
{
	panorama::Raster<int> raster = getFilledRaster(2,2);
	unitAssertEquals(4u, raster.getNumPixels());
	raster.resize(4,4,1,1,-1);
	unitAssertEquals(16u, raster.getNumPixels());

	// Verify the fill spots.
	unitAssertEquals(-1, raster(0,0));
	unitAssertEquals(-1, raster(1,0));
	unitAssertEquals(-1, raster(2,0));
	unitAssertEquals(-1, raster(3,0));
	unitAssertEquals(-1, raster(0,1));
	unitAssertEquals(-1, raster(3,1));
	unitAssertEquals(-1, raster(0,2));
	unitAssertEquals(-1, raster(3,2));
	unitAssertEquals(-1, raster(0,3));
	unitAssertEquals(-1, raster(1,3));
	unitAssertEquals(-1, raster(2,3));
	unitAssertEquals(-1, raster(3,3));

	// Verify the copied data.
	unitAssertEquals(1, raster(1,1));
	unitAssertEquals(2, raster(2,1));
	unitAssertEquals(2, raster(1,2));
	unitAssertEquals(4, raster(2,2));

	raster.resize(0,0);
	unitAssert(raster.empty());
	unitAssertEquals(0u, raster.getNumPixels());
	// Since the raster was zeroed, resizing it with a fill should fill everything.
	raster.resize(3,3,1,1,10);
	unitAssertEquals(9u, raster.getNumPixels());
	unitAssertEquals(10, raster(0,0));
	unitAssertEquals(10, raster(1,0));
	unitAssertEquals(10, raster(2,0));
	unitAssertEquals(10, raster(0,1));
	unitAssertEquals(10, raster(1,1));
	unitAssertEquals(10, raster(2,1));
	unitAssertEquals(10, raster(0,2));
	unitAssertEquals(10, raster(1,2));
	unitAssertEquals(10, raster(2,2));
}

AUTO_UNIT_TEST(raster_subraster)
{
	panorama::Raster<int> raster = getFilledRaster(10,10);

	// Bad...
	{
		unitAssertThrows(raster.subRaster(1,0,0,1)); // x1 > x2
		unitAssertThrows(raster.subRaster(0,1,1,0)); // y1 > y2
		unitAssertThrows(raster.subRaster(0,0,1,10)); // y2 >= height
		unitAssertThrows(raster.subRaster(0,0,1,11)); // y2 >= height
		unitAssertThrows(raster.subRaster(0,0,10,1)); // x1 >= width
		unitAssertThrows(raster.subRaster(0,0,11,1)); // x1 >= width
	}
	{
		// The one pixel at 0,0
		panorama::Raster<int> r1 = raster.subRaster(0,0,0,0);
		unitAssertEquals(1u, r1.getWidth());
		unitAssertEquals(1u, r1.getHeight());
		unitAssertEquals(1u, r1.getNumPixels());
		unitAssertEquals(1, r1(0,0));
	}
	{
		// Four pixels: (5,5), (6,5), (5,6), (6,6)
		panorama::Raster<int> r1 = raster.subRaster(5,5,6,6);
		unitAssertEquals(2u, r1.getWidth());
		unitAssertEquals(2u, r1.getHeight());
		unitAssertEquals(4u, r1.getNumPixels());
		unitAssertEquals(36, r1(0,0));
		unitAssertEquals(42, r1(1,0));
		unitAssertEquals(42, r1(0,1));
		unitAssertEquals(49, r1(1,1));
	}
}
