/*
 * $Id: GenericRectangle.hpp,v 1.1.2.1 2011/11/06 03:37:48 kpharris Exp $
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
#if       !defined(PANORAMA_GENERIC_RECTANGLE_HPP)
#define            PANORAMA_GENERIC_RECTANGLE_HPP

#include "panorama/common/GenericSize2.hpp"
#include "panorama/common/GenericPoint2.hpp"
#include "panorama/common/GenericVector2.hpp"
#include "panorama/common/Fuzzy.hpp"

namespace panorama
{

	/**
	 *
	 * A simple Rectangle class.
	 *
	 * @author Kevin Harris <kpharris@users.sourceforge.net>
	 * @version $Revision: 1.1.2.1 $
	 *
	 */
	template<typename base>
	struct GenericRectangle
	{

		enum Components
		{
			E_Left = 0,
			E_Right,
			E_Top,
			E_Bottom
		};

		union
		{
			struct
			{
				base left;
				base right;
				base top;
				base bottom;
			};
			base components[4];
		};

		GenericRectangle(base l, base r, base t, base b);
		virtual ~GenericRectangle();
		GenericRectangle(const GenericRectangle& old);
		GenericRectangle& operator= (const GenericRectangle& old);

		base width() const { return std::abs(right - left); }
		base height() const { return std::abs(bottom - top); }

		static GenericRectangle makeCenteredOn(const GenericPoint2<base>& center, const GenericSize2<base>& size);

		base& operator[](Components c) { return components[c]; }
		base operator[](Components c) const { return components[c]; }

	}; // class GenericRectangle

	template<typename base>
	GenericRectangle<base>::GenericRectangle(base l, base r, base t, base b):
		left(l), right(r),
		top(t), bottom(b)
	{

	} // GenericRectangle()

	template<typename base>
	GenericRectangle<base>::~GenericRectangle()
	{

	} // ~GenericRectangle()

	template<typename base>
	GenericRectangle<base>::GenericRectangle(const GenericRectangle<base>& old):
		left(old.left), right(old.right),
		top(old.top), bottom(old.bottom)
	{

	} // GenericRectangle(GenericRectangle)

	template<typename base>
	GenericRectangle<base>& GenericRectangle<base>::operator= (const GenericRectangle<base>& old)
	{
		// Generic check for self-assignment
		if( &old != this)
		{
			left = old.left;
			right = old.right;
			top = old.top;
			bottom = old.bottom;
		}
		return (*this);
	} // GenericRectangle::operator=(GenericRectangle)

	template<typename base>
	GenericRectangle<base> GenericRectangle<base>::makeCenteredOn(const GenericPoint2<base>& center, const GenericSize2<base>& size)
	{
		return GenericRectangle<base>(
			center.x() - size.width()/base(2),
			center.x() + size.width()/base(2),
			center.y() + size.height()/base(2),
			center.y() - size.height()/base(2));
	}

	template<typename base>
	bool operator==(const GenericRectangle<base>& lhs, const GenericRectangle<base>& rhs)
	{
		return fuzzyEquals(lhs.left, rhs.left)
			&& fuzzyEquals(lhs.right, rhs.right)
			&& fuzzyEquals(lhs.top, rhs.top)
			&& fuzzyEquals(lhs.bottom, rhs.bottom);
	}

	template<typename base>
	inline GenericRectangle<base> operator+(const GenericRectangle<base>& rect, const GenericVector2<base>& vec)
	{
		return GenericRectangle<base>(
			rect.left + vec.x(),
			rect.right + vec.x(),
			rect.top + vec.y(),
			rect.bottom + vec.y());
	}

	template<typename base>
	bool operator!=(const GenericRectangle<base>& lhs, const GenericRectangle<base>& rhs)
	{
		return !(lhs == rhs);
	}

	template <typename base>
	bool intersecting(const GenericRectangle<base>& r1, const GenericRectangle<base>& r2)
	{
		if( fuzzyGreater(r2.left, r1.right) )
		{
			return false;
		}
		if( fuzzyGreater(r1.left, r2.right) )
		{
			return false;
		}
		if( fuzzyGreater(r1.bottom, r2.top) )
		{
			return false;
		}
		if( fuzzyGreater(r2.bottom, r1.top) )
		{
			return false;
		}
		return true;
	}

	template <typename base>
	GenericPoint2<base> center(const GenericRectangle<base>& r)
	{
		return GenericPoint2<base>(
			(r.left + r.right) / 2,
			(r.top + r.bottom) / 2);
	}

} // namespace panorama


#endif /* !defined(PANORAMA_GENERIC_RECTANGLE_HPP) */

