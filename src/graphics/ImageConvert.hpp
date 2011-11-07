/*
 * $Id: ImageConvert.hpp,v 1.1.2.1 2011/11/07 06:08:00 kpharris Exp $
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

#if       !defined(PANORAMA_IMAGE_CONVERT_HPP)
#define            PANORAMA_IMAGE_CONVERT_HPP

#include "panorama/common/GenericRGBColor.hpp"
#include "panorama/common/GenericRGBAColor.hpp"
#include "panorama/graphics/GenericImage.hpp"
#include "panorama/graphics/GenericRGBImage.hpp"
#include "panorama/graphics/GenericAlphaImage.hpp"
#include "panorama/graphics/MaskedImage.hpp"

namespace panorama
{
	template <typename U, typename T>
	U convertColorItem(T t)
	{
		return t;
	}

	template<> unsigned char convertColorItem<unsigned char,float>(float f);
	template<> unsigned char convertColorItem<unsigned char,double>(double d);
	template<> unsigned char convertColorItem<unsigned char,unsigned short>(unsigned short s);

	template<> unsigned short convertColorItem<unsigned short,unsigned char>(unsigned char s);
	template<> unsigned short convertColorItem<unsigned short,float>(float f);
	template<> unsigned short convertColorItem<unsigned short,double>(double d);

	template<> float convertColorItem<float,unsigned char>(unsigned char f);
	template<> float convertColorItem<float,double>(double d);
	template<> float convertColorItem<float,unsigned short>(unsigned short s);

	template<> double convertColorItem<double,unsigned char>(unsigned char d);
	template<> double convertColorItem<double,float>(float f);
	template<> double convertColorItem<double,unsigned short>(unsigned short s);

	// FIXME! Finish the color conversion.
	// FIXME! Unit tests.
} // namespace panorama


#endif /* !defined(PANORAMA_IMAGE_CONVERT_HPP) */
