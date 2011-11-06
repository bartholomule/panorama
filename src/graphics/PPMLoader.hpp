/*
 * $Id: PPMLoader.hpp,v 1.1.2.1 2011/11/06 03:30:51 kpharris Exp $
 *
 * Part of Panorama -- a framework for graphics production.
 * Copyright (C) 2010 Kevin Harris
 */

#if       !defined(PANORAMA_PPM_LOADER_HPP)
#define            PANORAMA_PPM_LOADER_HPP

/**
 * @author Kevin Harris
 */

#include "panorama/common/GenericRGBColor.hpp"
#include "panorama/graphics/GenericImage.hpp"

// FIXME! Add a common base and interface for image loaders/savers that includes the image capability data.
// FIXME! Write unit tests for this.

namespace panorama
{
	// Load a PPM image.  P3 (text only) and P6 (binary) are supported.
	bool loadPPM(const char* data, unsigned len, GenericImage<GenericRGBColor<unsigned char> >& image);

	// Save a text-based ppm
	bool savePPM_P3(const GenericImage<GenericRGBColor<unsigned char> >& image, const char* filename);

	// Save a binary (P6) ppm.  This saves a lot of space over the P3,
	// but cannot be easily incorporated into source code.
	bool savePPM(const GenericImage<GenericRGBColor<unsigned char> >& image, const char* filename);
} // namespace panorama

#endif /* !defined(PANORAMA_PPM_LOADER_HPP) */
