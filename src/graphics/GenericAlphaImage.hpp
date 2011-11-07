/*
 * $Id: GenericAlphaImage.hpp,v 1.1.2.1 2011/11/07 06:07:38 kpharris Exp $
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

#if       !defined(PANORAMA_GENERIC_ALPHA_IMAGE_HPP)
#define            PANORAMA_GENERIC_ALPHA_IMAGE_HPP

#include "panorama/common/GenericRGBAColor.hpp"
#include "panorama/graphics/GenericImage.hpp"
#include "panorama/graphics/GenericRGBImage.hpp"
#include "panorama/graphics/MaskedImage.hpp"

namespace panorama
{
	template <typename T>
	class GenericAlphaImage : public GenericImage<GenericRGBAColor<T> >
	{
	public:
		typedef GenericRGBAColor<T> color_type;
		typedef GenericImage<color_type> parent_type;

		GenericAlphaImage() { }
		GenericAlphaImage(unsigned width, unsigned height) : parent_type(width,height) { }
		GenericAlphaImage(const parent_type& p) : parent_type(p) { }
		GenericAlphaImage(const GenericRGBImage<T>& img);
		template<typename ColorType, typename MaskType>
		GenericAlphaImage(const MaskedImage<ColorType, MaskType>& img);

		CloneableRef clone() const { return CloneableRef(new GenericAlphaImage(*this)); }
		blocxx::String name() const { return "AlphaImage"; }
	};

	template<typename T>
	GenericAlphaImage<T>::GenericAlphaImage(const GenericRGBImage<T>& img)
		: parent_type(img.getWidth(), img.getHeight())
	{
		// Convert each RGB color to an alpha color while copying.  We know that
		// the bounds are good, so this is much faster than using the
		// bounds-checked Raster::operator() on each pixel.
		const typename GenericRGBImage<T>::color_type* source = img.getRawData();
		std::copy(source, source + parent_type::getNumPixels(), parent_type::getRawData());
	}

	template<typename T>
	template<typename ColorType, typename MaskType>
	GenericAlphaImage<T>::GenericAlphaImage(const MaskedImage<ColorType, MaskType>& img)
		: parent_type(img.getWidth(), img.getHeight())
	{
		for( unsigned y = 0; y < parent_type::getHeight(); ++y )
		{
			for( unsigned x = 0; x < parent_type::getWidth(); ++x )
			{
				ColorType c = img(x,y);
				color_type o = c;
				o.set_a( img.mask(x,y) ? 0 : ColorType::color_traits_type::max() );
				(*this)(x,y) = o;
			}
		}
	}
} // namespace panorama


#endif /* !defined(PANORAMA_GENERIC_ALPHA_IMAGE_HPP) */
