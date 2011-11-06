/*
 * $Id: XPMLoader.hpp,v 1.1.2.1 2011/11/06 03:30:51 kpharris Exp $
 *
 * Part of Panorama -- a framework for graphics production.
 * Copyright (C) 2010 Kevin Harris
 */

#if       !defined(PANORAMA_XPM_LOADER_HPP)
#define            PANORAMA_XPM_LOADER_HPP

/**
 * @author Kevin Harris
 */

#include "panorama/graphics/MaskedImage.hpp"

// FIXME! Add a common base and interface for image loaders/savers that includes the image capability data.
// FIXME! Write unit tests for this.
// FIXME! Add a function to write XPM files.

namespace panorama
{
	bool loadXPM(const char* data, MaskedImage<unsigned char>& image);

	// The c-style xpm data array
	bool loadXPM(const char** data, MaskedImage<unsigned char>& image);
} // namespace panorama


#endif /* !defined(PANORAMA_XPM_LOADER_HPP) */
