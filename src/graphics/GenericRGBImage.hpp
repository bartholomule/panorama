/*
 * $Id: GenericRGBImage.hpp,v 1.1.2.1 2011/11/07 06:07:38 kpharris Exp $
 *
 * Part of "Panorama" a playground for graphics development
 * Copyright (C) 2011 Kevin Harris
  *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 */

#if       !defined(PANORAMA_GENERIC_RGB_IMAGE_HPP)
#define            PANORAMA_GENERIC_RGB_IMAGE_HPP

#include "panorama/common/GenericRGBColor.hpp"
#include "panorama/graphics/GenericImage.hpp"

namespace panorama
{
	template <typename T>
	class GenericRGBImage : public GenericImage<GenericRGBColor<T> >
	{
	public:
		typedef GenericRGBColor<T> color_type;
		typedef GenericImage<color_type> parent_type;

		GenericRGBImage() { }
		GenericRGBImage(unsigned width, unsigned height) : parent_type(width,height) { }
		GenericRGBImage(const parent_type& p) : parent_type(p) { }

		CloneableRef clone() const { return CloneableRef(new GenericRGBImage(*this)); }
		blocxx::String name() const { return "RGBImage"; }
	};
} // namespace panorama


#endif /* !defined(PANORAMA_GENERIC_RGB_IMAGE_HPP) */
