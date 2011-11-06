/*
 * $Id: GenericSize2.hpp,v 1.1.2.1 2011/11/06 03:38:39 kpharris Exp $
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

#if    !defined(PANORAMA__GENERICSIZE2_HPP)
#define         PANORAMA__GENERICSIZE2_HPP

/*
  GenericSize2.hpp

  A representation of a size with width and height.
*/


#include "panorama/common/GenericCoord2.hpp"
#include "panorama/common/GenericVector2.hpp"

namespace panorama
{

	template <class T>
	class GenericSize2: private GenericCoord2<T>
	{
	public:
		// This tag allows use in the StringDumpable.hpp toString functions
		// without requiring the overridden virtual functions.
		typedef bool CanBeStringDumpedTag;

		using GenericCoord2<T>::COORD_VALUES;
		using GenericCoord2<T>::X;
		using GenericCoord2<T>::Y;

		typedef T base;

		inline GenericSize2():GenericCoord2<T>()
		{
		}
		inline GenericSize2(T width, T height): GenericCoord2<T>(width,height)
		{
		}
		inline explicit GenericSize2(const GenericCoord2<T>& c): GenericCoord2<T>(c)
		{
		}
		inline GenericSize2(const GenericSize2<T>& p): GenericCoord2<T>(p)
		{
		}

		inline void set(T width, T height)
		{
			GenericCoord2<T>::set(width,height);
		}

		GenericCoord2<T> getcoord() const
		{
			return GenericCoord2<T>(width(), height());
		}

		/* Accessors */
		inline T& operator[](int coord_index)
		{
			return(GenericCoord2<T>::operator[](coord_index));
		}

		inline T  operator[](int coord_index) const
		{
			return(GenericCoord2<T>::operator[](coord_index));
		}

		T& width()
		{
			return(GenericCoord2<T>::x());
		}
		T  width() const
		{
			return(GenericCoord2<T>::x());
		}
		T& height()
		{
			return(GenericCoord2<T>::y());
		}
		T  height() const
		{
			return(GenericCoord2<T>::y());
		}

		GenericSize2<T>& operator=(const GenericSize2<T>& p);
		GenericSize2<T>& operator+=(const GenericVector2<T>& v1);
		GenericSize2<T>& operator-=(const GenericVector2<T>& v1);

		void collectInternalMembers(MemberStringDumpCollector& collector) const;
		blocxx::String toString(const Indentation& indent = Indentation(), StringDumpable::PrefixType prefix = StringDumpable::E_PREFIX_NONE ) const;

		blocxx::String name() const { return "Size2"; }
	}; // class GenericSize2

	template <class T>
	inline GenericSize2<T>& GenericSize2<T>::operator=(const GenericSize2<T>& p)
	{
		set( p.width(), p.height() );

		return *this;
	}

	template <class T>
	inline GenericSize2<T>& GenericSize2<T>::operator+=(const GenericVector2<T>& v1)
	{
		set( width() + v1.x(),
			height() + v1.y() );
		return *this;
	}

	template <class T>
	inline GenericSize2<T>& GenericSize2<T>::operator-=(const GenericVector2<T>& v1)
	{
		set( width() - v1.x(),
			height() - v1.y() );
		return *this;
	}

	template <class T>
	inline GenericVector2<T> operator-(const GenericSize2<T>& p1, const GenericSize2<T>& p2)
	{
		return GenericVector2<T>(p1.width() - p2.width(), p1.height() - p2.height());
	}

	template <class T>
	inline GenericSize2<T>  operator+(const GenericSize2<T>& p1, const GenericVector2<T>& v1)
	{
		return GenericSize2<T>(p1.width() + v1.x(), p1.height() + v1.y());
	}

	template <class T>
	inline GenericSize2<T>  operator-(const GenericSize2<T>& p1, const GenericVector2<T>& v1)
	{
		return GenericSize2<T>(p1.width() - v1.x(), p1.height() - v1.y());
	}

	template <class T>
	inline T averageComponent(const GenericSize2<T>& v)
	{
		return((v.width() + v.height()) / 2);
	}

	template <class T>
	inline T maxComponent(const GenericSize2<T>& v)
	{
		return(std::max(v.width(), v.height()));
	}

	template <class T>
	void GenericSize2<T>::collectInternalMembers(MemberStringDumpCollector& collector) const
	{
		GenericCoord2<T>::collectInternalMembers(collector);
	}

	template <class T>
	blocxx::String GenericSize2<T>::toString(const Indentation& indent, StringDumpable::PrefixType prefix) const
	{
		blocxx::String tag;
		if( prefix == StringDumpable::E_PREFIX_CLASSNAME )
		{
			tag = GenericSize2<T>::name();
		}

		return indent.initial() + tag +
			"(" +
			panorama::toString(width(), indent.indentInside(), prefix) +
			"," +
			panorama::toString(height(), indent.indentInside(), prefix) +
			")";
	}

} // namespace panorama

#endif /* !defined(PANORAMA__GenericSize2_HPP) */
