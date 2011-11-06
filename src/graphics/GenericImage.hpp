/*
 * $Id: GenericImage.hpp,v 1.1.2.1 2011/11/06 03:30:51 kpharris Exp $
 *
 * Part of "Panorama" a playground for graphics development
 * Copyright (C) 2003 Kevin Harris
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

#if       !defined(PANORAMA_GENERICIMAGE_HPP)
#define            PANORAMA_GENERICIMAGE_HPP

#include "panorama/common/Raster.hpp"
#include "panorama/common/GenericRGBColor.hpp"

// FIXME! Subclass this for RGB and alpha images.
// FIXME! Add image capabilities

namespace panorama
{

	// Sorry about these comments, as they are meant to be viewed in html form.
	/**
	 *
	 * A generic class which combines the capabilities of Raster and RGBColor.
	 * This class has almost no functionality of its own.
	 *
	 * Note the neat feature of this class: it can be reinterpreted as a pointer
	 * to the base type given to it.
	 *
	 * For example:<br>
	 * <font color="#008800">GenericImage</font>&lt;<font color="#000088">unsigned
	 * char</font>&gt im(640, 480);
	 *
	 * <font color="#880000">
	 * // This next variable can be treated as a single array of size      <br>
	 * // im.numpixels( ) in length, which would be 307200 in this case.   <br>
	 * </font>
	 * <font color="#000088">unsigned char</font>*
	 * image_data</font> =
	 * im.<font color="#008800">reinterpret</font>
	 * &lt;<font color="#000088">unsigned char</font>*&gt; ( );<br>
	 * ...<br>
	 * <font color="#880000">
	 * // Act on the data, being careful not to go beyond bounds on either <br>
	 * // end, or (whether intentional or not) deallocate the pointer.     <br>
	 * </font>
	 *
	 * @author Kevin Harris <kpharris@users.sourceforge.net>
	 * @version $Revision: 1.1.2.1 $
	 * @see Raster
	 * @see RGBColor
	 *
	 */
	template <typename ColorType, typename T = typename ColorType::number_type>
	class GenericImage : public Raster<ColorType>
	{
	public:
		typedef ColorType color_type;
		typedef Raster<color_type> parent;

		GenericImage();
		GenericImage(const parent& r);
		GenericImage(unsigned width, unsigned height);
		virtual ~GenericImage();
		GenericImage(const GenericImage& old);
		GenericImage& operator= (const GenericImage& old);

		CloneableRef clone() const { return CloneableRef(new GenericImage(*this)); }
		blocxx::String name() const { return "Image"; }
		void collectInternalMembers(MemberStringDumpCollector& collector) const;

		// Return if the pixel at x,y is visible.  For most uses, you really
		// don't want to do this for each pixel.  Know what image type you have
		// before you try to draw it.
		virtual bool visible(int x, int y) const;

		GenericImage subImage(const GenericRectangle<unsigned>& rect) const
		{
			return GenericImage(parent::subRaster(rect));
		}

		GenericImage subImage(unsigned x1, unsigned y1, unsigned x2, unsigned y2) const
		{
			return subImage(GenericRectangle<unsigned>(x1, x2, y1, y2));
		}
	}; // class GenericImage

	template <typename ColorType, typename T>
	GenericImage<ColorType,T>::GenericImage()
		: parent()
	{

	} // GenericImage()

	template <typename ColorType, typename T>
	GenericImage<ColorType,T>::GenericImage(const parent& r) :
		parent(r)
	{
	}

	template <typename ColorType, typename T>
	GenericImage<ColorType,T>::GenericImage(unsigned width, unsigned height):
		parent(width, height)
	{

	} // GenericImage(w,h)

	template <typename ColorType, typename T>
	GenericImage<ColorType,T>::~GenericImage()
	{

	} // ~GenericImage()

	template <typename ColorType, typename T>
	GenericImage<ColorType,T>::GenericImage(const GenericImage<ColorType,T>& old):
		parent(old)
	{

	} // GenericImage(GenericImage)

	template <typename ColorType, typename T>
	GenericImage<ColorType,T>& GenericImage<ColorType,T>::operator= (const GenericImage<ColorType,T>& old)
	{
		// Generic check for self-assignment
		if( &old != this )
		{
			// The class currently has no members, but if they are added, they need
			// to be assigned here.

			parent::operator=(old);
		}
		return(*this);
	} // GenericImage::operator=(GenericImage)

	template <typename ColorType, typename T>
	void GenericImage<ColorType,T>::collectInternalMembers(MemberStringDumpCollector& collector) const
	{
		parent::collectInternalMembers(collector);
	}

	template <typename ColorType, typename T>
	bool GenericImage<ColorType,T>::visible(int x, int y) const
	{
		return parent::inside(x,y);
	}

	template <typename ColorType, typename T>
	GenericImage<ColorType,T> scaleImage(const GenericImage<ColorType,T>& img, unsigned scale)
	{
		// FIXME! Allow scales other than block (eg. interpolated)
		GenericImage<ColorType,T> ret_image(img.getWidth() * scale, img.getHeight() * scale);

		for(unsigned y = 0; y < ret_image.getHeight(); ++y)
		{
			unsigned y_norm = y / scale;
			for(unsigned x = 0; x < ret_image.getWidth(); ++x)
			{
				unsigned x_norm = x / scale;
				ret_image(x,y) = img(x_norm, y_norm);
			}
		}
		return ret_image;
	}

} // namespace panorama


#endif /* !defined(PANORAMA_GENERICIMAGE_HPP) */

