/*
 * $Id: MaskedImage.hpp,v 1.1.2.1 2011/11/06 03:30:51 kpharris Exp $
 *
 * Part of "Panorama"
 * Copyright (C) 2010 Kevin Harris
 */

#if       !defined(PANORAMA_MASKEDIMAGE_HPP)
#define            PANORAMA_MASKEDIMAGE_HPP

#include "panorama/common/Raster.hpp"
#include "panorama/common/GenericRectangle.hpp"
#include "panorama/graphics/GenericImage.hpp"

// FIXME! Add unit tests.

namespace panorama
{

	/**
	 *
	 * An Image which has a mask for use in determining weather or not the color
	 * value should be used.
	 *
	 * @author Kevin Harris <kpharris@users.sourceforge.net>
	 * @version $Revision: 1.1.2.1 $
	 *
	 */
	template <typename ColorType, typename MaskType = bool>
	class MaskedImage : public GenericImage<ColorType>, public virtual StringDumpable
	{
	private:
		typedef GenericImage<ColorType> parent;
	public:
		typedef ColorType color_type;

		MaskedImage();
		MaskedImage(const GenericImage<ColorType>& img, const color_type& transparent);
		MaskedImage(const GenericImage<ColorType>& img, const Raster<MaskType>& msk);
		MaskedImage(unsigned width, unsigned height);
		MaskedImage(unsigned width, unsigned height,	const color_type* pdata, const MaskType* mdata);

		virtual ~MaskedImage();
		MaskedImage(const MaskedImage& old);
		MaskedImage& operator= (const MaskedImage& old);

		color_type& operator()(unsigned x, unsigned y) { return parent::operator()(x,y); }
		const color_type& operator()(unsigned x, unsigned y) const { return parent::operator()(x,y); }

		bool empty() const { return parent::empty(); }
		unsigned getWidth() const { return parent::getWidth(); }
		unsigned getHeight() const { return parent::getHeight(); }

		/**
		 * Get the mask element at the given (x,y)
		 * @param x The column.
		 * @param y The row.
		 */
		MaskType& mask(unsigned x, unsigned y)
		{
			return my_mask(x,y);
		}

		/**
		 * Get the mask element at the given (x,y)
		 * @param x The column.
		 * @param y The row.
		 */
		MaskType mask(unsigned x, unsigned y) const
		{ return my_mask(x,y); }

		/**
		 * Resize the current masked Image to the given width and height.  If
		 * preserve is given, the current data (if any), is copied across. If
		 * either width or height is zero, the current masked Image will be resized
		 * to 0.
		 */
		void resize(unsigned width, unsigned height, bool preserve = true)
		{
			GenericImage<ColorType>::resize(width, height, preserve);
			my_mask.resize(width, height, preserve);
		}

		/**
		 * Resize the current masked Image to the given width and height, shifting
		 * old data to be centered at cx,cy in the newly sized masked Image, and
		 * filling the rest with the given fill data.
		 */
		void resize(unsigned width, unsigned height,
			int cx, int cy, const ColorType& fill1, const MaskType& fill2)
		{
			parent::resize(width, height, cx, cy, fill1);
			my_mask.resize(width, height, cx, cy, fill2);
		}


		/**
		 * Return a Image which contains the elements in the range
		 * (x1,y1) to (x2,y2) inclusive.
		 * @returns a new Image that contains the data from the specified region.
		 */
		MaskedImage subImage(unsigned x1, unsigned y1, unsigned x2, unsigned y2) const
		{
			return MaskedImage(parent::subImage(x1,y1,x2,y2), my_mask.subRaster(x1,y1,x2,y2));
		}

		/**
		 * Return a Image which contains the elements in the range
		 * (rect.left, rect.top) to (rect.right, rect.bottom) inclusive.
		 * @returns a new Image that contains the data from the specified region.
		 */
		MaskedImage subImage(const GenericRectangle<unsigned>& rect) const
		{
			return MaskedImage(parent::subImage(rect), my_mask.subRaster(rect));
		}

		bool visible(int x, int y) const;

		CloneableRef clone() const { return CloneableRef(new MaskedImage(*this)); }
		blocxx::String name() const { return "MaskedImage"; }
		void collectInternalMembers(MemberStringDumpCollector& collector) const;

	private:
		Raster<MaskType> my_mask;
	}; // class MaskedImage

	template <typename ColorType, typename MaskType>
	MaskedImage<ColorType,MaskType>::MaskedImage():
		GenericImage<ColorType>(),
		my_mask()
	{

	} // MaskedImage()

	template <typename ColorType, typename MaskType>
	MaskedImage<ColorType,MaskType>::MaskedImage(unsigned w, unsigned h):
		GenericImage<ColorType>(w, h),
		my_mask(w, h)
	{

	} // MaskedImage(w,h)

	template <typename ColorType, typename MaskType>
	MaskedImage<ColorType,MaskType>::MaskedImage(const GenericImage<ColorType>& img,
		const Raster<MaskType>& msk):
		GenericImage<ColorType>(img),
		my_mask(msk)
	{

		// Make sure the sizes are the same....
		my_mask.resize(this->getWidth(), this->getHeight(), true);

	} // MaskedImage(Image,raster)

	template <typename ColorType, typename MaskType>
	MaskedImage<ColorType,MaskType>::MaskedImage(unsigned width, unsigned height,
		const color_type* pdata,
		const MaskType* mdata):
		GenericImage<ColorType>(width, height, pdata),
		my_mask(width, height, mdata)
	{

	} // MaskedImage(unsigned,unsigned,rgbcolor*,MaskType*)

	template <typename ColorType, typename MaskType>
	MaskedImage<ColorType,MaskType>::~MaskedImage()
	{

	} // ~MaskedImage()

	template <typename ColorType, typename MaskType>
	MaskedImage<ColorType,MaskType>::MaskedImage(const MaskedImage& old):
		GenericImage<ColorType>(old),
		my_mask(old.my_mask)
	{

	} // MaskedImage(MaskedImage)

	template <typename ColorType, typename MaskType>
	MaskedImage<ColorType,MaskType>& MaskedImage<ColorType,MaskType>::operator= (const MaskedImage& old)
	{
		// Generic check for self-assignment
		if( &old != this)
		{
			my_mask = old.my_mask;

			GenericImage<ColorType>::operator=(old);
		}
		return (*this);
	} // MaskedImage::operator=(MaskedImage)


	template <typename ColorType, typename MaskType>
	MaskedImage<ColorType,MaskType>::MaskedImage(const GenericImage<ColorType>& image, const color_type& transparent)
		: GenericImage<ColorType>(image)
		, my_mask(image.getWidth(), image.getHeight())
	{
		for( unsigned y = 0; y < getHeight(); ++y )
		{
			for(unsigned x = 0; x < getWidth(); ++x )
			{
				const color_type& c = (*this)(x,y);
				mask(x,y) = !((c.r() == transparent.r()) && (c.g() == transparent.g()) && (c.b() == transparent.b()));
			}
		}
	}

	template <typename ColorType, typename MaskType>
	MaskedImage<ColorType,MaskType> scaleImage(const MaskedImage<ColorType,MaskType>& image, unsigned scale)
	{

		MaskedImage<ColorType,MaskType> ret_image(image.getWidth() * scale,
			image.getHeight() * scale);

		for(unsigned y = 0; y < ret_image.getHeight(); ++y)
		{
			unsigned y_norm = y / scale;
			for(unsigned x = 0; x < ret_image.getWidth(); ++x)
			{
				unsigned x_norm = x / scale;
				ret_image(x,y) = image(x_norm, y_norm);
				ret_image.mask(x,y) = image.mask(x_norm, y_norm);
			}
		}
		return ret_image;
	}

	template <typename ColorType, typename MaskType>
	bool MaskedImage<ColorType,MaskType>::visible(int x, int y) const
	{
		return (
			(x > 0)
			&& (y > 0)
			&& (x < int(my_mask.getWidth()))
			&& (y < int(my_mask.getHeight()))
			&& my_mask(x,y));
	}

	template <typename ColorType, typename MaskType>
	void MaskedImage<ColorType,MaskType>::collectInternalMembers(MemberStringDumpCollector& collector) const
	{
		parent::collectInternalMembers(collector);
		collector.addMember("mask", "...");
	}

} // namespace panorama


#endif /* !defined(PANORAMA_MASKEDIMAGE_HPP) */
