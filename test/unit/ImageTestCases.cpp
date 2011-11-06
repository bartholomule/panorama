#define PROVIDE_AUTO_TEST_MAIN
#include "blocxx_test/CppUnit/AutoTest.hpp"
#include "panorama/graphics/GenericImage.hpp"

typedef panorama::GenericImage<int,int> SimpleImage;
typedef panorama::GenericRectangle<int> Rectangle;

AUTO_UNIT_TEST(simple_raster_ops)
{
	SimpleImage simple(5,6);
	unitAssert(!simple.empty());
	unitAssertEquals(5u, simple.getWidth());
	unitAssertEquals(6u, simple.getHeight());
	unitAssertEquals(30u, simple.getNumPixels());

	const SimpleImage simple2 = simple;
	unitAssert(!simple2.empty());
	unitAssertEquals(5u, simple2.getWidth());
	unitAssertEquals(6u, simple2.getHeight());
	unitAssertEquals(30u, simple2.getNumPixels());
}

AUTO_UNIT_TEST(image_bounds_checks)
{
	SimpleImage image(5,6);
	{
		unitAssertThrowsEx(image[6][0], blocxx::OutOfBoundsException);
		unitAssertThrowsEx(image(0,6), blocxx::OutOfBoundsException);
		unitAssertThrowsEx(image[0][5], blocxx::OutOfBoundsException);
		unitAssertThrowsEx(image(5,0), blocxx::OutOfBoundsException);
		unitAssertThrowsEx(image(5,6), blocxx::OutOfBoundsException);
		unitAssertNoThrow(image[0][0]);
		unitAssertNoThrow(image[5][4]);
		unitAssertNoThrow(image(0,0));
		unitAssertNoThrow(image(4,5));
	}

	const SimpleImage image2 = image;
	{
		unitAssertThrowsEx(image2[6][0], blocxx::OutOfBoundsException);
		unitAssertThrowsEx(image2(0,6), blocxx::OutOfBoundsException);
		unitAssertThrowsEx(image2[0][5], blocxx::OutOfBoundsException);
		unitAssertThrowsEx(image2(5,0), blocxx::OutOfBoundsException);
		unitAssertThrowsEx(image2(5,6), blocxx::OutOfBoundsException);
		unitAssertNoThrow(image2[0][0]);
		unitAssertNoThrow(image2[5][4]);
		unitAssertNoThrow(image2(0,0));
		unitAssertNoThrow(image2(4,5));
	}
}

namespace
{
	SimpleImage getFilledImage(int width, int height)
	{
		SimpleImage retval(width, height);

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

AUTO_UNIT_TEST(image_reinterpret)
{
	SimpleImage image = getFilledImage(3,3);
	const int* data = image.reinterpret<const int*>();
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

AUTO_UNIT_TEST(image_resize_regular)
{
	SimpleImage image = getFilledImage(7,4);
	unitAssertEquals(28u, image.getNumPixels());
	image.resize(2,3);
	unitAssertEquals(6u, image.getNumPixels());
	unitAssertEquals(2u, image.getWidth());
	unitAssertEquals(3u, image.getHeight());

	// The data must be preserved...
	unitAssertEquals(1, image(0,0));
	unitAssertEquals(2, image(1,0));
	unitAssertEquals(2, image(0,1));
	unitAssertEquals(4, image(1,1));
	unitAssertEquals(3, image(0,2));
	unitAssertEquals(6, image(1,2));
}

AUTO_UNIT_TEST(image_resize_fill)
{
	SimpleImage image = getFilledImage(2,2);
	unitAssertEquals(4u, image.getNumPixels());
	image.resize(4,4,1,1,-1);
	unitAssertEquals(16u, image.getNumPixels());

	// Verify the fill spots.
	unitAssertEquals(-1, image(0,0));
	unitAssertEquals(-1, image(1,0));
	unitAssertEquals(-1, image(2,0));
	unitAssertEquals(-1, image(3,0));
	unitAssertEquals(-1, image(0,1));
	unitAssertEquals(-1, image(3,1));
	unitAssertEquals(-1, image(0,2));
	unitAssertEquals(-1, image(3,2));
	unitAssertEquals(-1, image(0,3));
	unitAssertEquals(-1, image(1,3));
	unitAssertEquals(-1, image(2,3));
	unitAssertEquals(-1, image(3,3));

	// Verify the copied data.
	unitAssertEquals(1, image(1,1));
	unitAssertEquals(2, image(2,1));
	unitAssertEquals(2, image(1,2));
	unitAssertEquals(4, image(2,2));

	image.resize(0,0);
	unitAssert(image.empty());
	unitAssertEquals(0u, image.getNumPixels());
	// Since the image was zeroed, resizing it with a fill should fill everything.
	image.resize(3,3,1,1,10);
	unitAssertEquals(9u, image.getNumPixels());
	unitAssertEquals(10, image(0,0));
	unitAssertEquals(10, image(1,0));
	unitAssertEquals(10, image(2,0));
	unitAssertEquals(10, image(0,1));
	unitAssertEquals(10, image(1,1));
	unitAssertEquals(10, image(2,1));
	unitAssertEquals(10, image(0,2));
	unitAssertEquals(10, image(1,2));
	unitAssertEquals(10, image(2,2));
}

AUTO_UNIT_TEST(image_scale)
{
	SimpleImage image = getFilledImage(2,2);
	unitAssertEquals(4u, image.getNumPixels());
	SimpleImage image2 = scaleImage(image, 2);
	unitAssertEquals(16u, image2.getNumPixels());

	unitAssertEquals(1, image2(0,0));
	unitAssertEquals(1, image2(1,0));
	unitAssertEquals(2, image2(2,0));
	unitAssertEquals(2, image2(3,0));

	unitAssertEquals(1, image2(0,1));
	unitAssertEquals(1, image2(1,1));
	unitAssertEquals(2, image2(2,1));
	unitAssertEquals(2, image2(3,1));

	unitAssertEquals(2, image2(0,2));
	unitAssertEquals(2, image2(1,2));
	unitAssertEquals(4, image2(2,2));
	unitAssertEquals(4, image2(3,2));

	unitAssertEquals(2, image2(0,3));
	unitAssertEquals(2, image2(1,3));
	unitAssertEquals(4, image2(2,3));
	unitAssertEquals(4, image2(3,3));
}

AUTO_UNIT_TEST(image_subimage)
{
	SimpleImage image = getFilledImage(10,10);

	// Bad...
	{
		unitAssertThrows(image.subImage(1,0,0,1)); // x1 > x2
		unitAssertThrows(image.subImage(0,1,1,0)); // y1 > y2
		unitAssertThrows(image.subImage(0,0,1,10)); // y2 >= height
		unitAssertThrows(image.subImage(0,0,1,11)); // y2 >= height
		unitAssertThrows(image.subImage(0,0,10,1)); // x1 >= width
		unitAssertThrows(image.subImage(0,0,11,1)); // x1 >= width
	}
	{
		// The one pixel at 0,0
		SimpleImage r1 = image.subImage(0,0,0,0);
		unitAssertEquals(1u, r1.getWidth());
		unitAssertEquals(1u, r1.getHeight());
		unitAssertEquals(1u, r1.getNumPixels());
		unitAssertEquals(1, r1(0,0));
	}
	{
		// Four pixels: (5,5), (6,5), (5,6), (6,6)
		SimpleImage r1 = image.subImage(5,5,6,6);
		unitAssertEquals(2u, r1.getWidth());
		unitAssertEquals(2u, r1.getHeight());
		unitAssertEquals(4u, r1.getNumPixels());
		unitAssertEquals(36, r1(0,0));
		unitAssertEquals(42, r1(1,0));
		unitAssertEquals(42, r1(0,1));
		unitAssertEquals(49, r1(1,1));
	}
}
