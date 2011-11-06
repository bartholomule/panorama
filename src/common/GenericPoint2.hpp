/*
 * $Id: GenericPoint2.hpp,v 1.1.2.3 2011/11/06 03:37:10 kpharris Exp $
 *
 * Part of GNU Panorama
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

#if    !defined(PANORAMA__GENERICPOINT2_HPP)
#define         PANORAMA__GENERICPOINT2_HPP

/*
  GenericPoint2.hpp

  A 2d equiv of the stuff in point3.hpp
*/

/*
  revision history:
  17Jan1999 Wrote this file, did some basic testing.
  20jan1999 Added a default constructor.
  02feb1999 Fixed the broken constructor.
  18May2001 "Templatized" the class...
  17Sep2003 Changed the inheritence from public to private.  Added accessors,
  fixed implementation to use those accessors.
  14Jun2009 Renamed from point2 to GenericPoint2
*/

#include "panorama/common/GenericCoord2.hpp"
#include "panorama/common/GenericVector2.hpp"
#include "panorama/common/Fuzzy.hpp"

namespace panorama
{

	template <class T>
	class GenericPoint2: private GenericCoord2<T>
	{
	public:
		// This tag allows use in the StringDumpable.hpp toString functions
		// without requiring the overridden virtual functions.
		typedef bool CanBeStringDumpedTag;

		using GenericCoord2<T>::COORD_VALUES;
		using GenericCoord2<T>::X;
		using GenericCoord2<T>::Y;

		typedef T base;

		inline GenericPoint2():GenericCoord2<T>()
		{
		}
		inline GenericPoint2(T x, T y): GenericCoord2<T>(x,y)
		{
		}
		inline explicit GenericPoint2(const GenericCoord2<T>& c): GenericCoord2<T>(c)
		{
		}
		inline GenericPoint2(const GenericPoint2<T>& p): GenericCoord2<T>(p)
		{
		}

		inline void set(T x, T y)
		{
			GenericCoord2<T>::set(x,y);
		}

		GenericCoord2<T> getcoord() const
		{
			return GenericCoord2<T>(x(), y());
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

		T& x()
		{
			return(GenericCoord2<T>::x());
		}
		T  x() const
		{
			return(GenericCoord2<T>::x());
		}
		T& y()
		{
			return(GenericCoord2<T>::y());
		}
		T  y() const
		{
			return(GenericCoord2<T>::y());
		}

		GenericPoint2<T>& operator=(const GenericPoint2<T>& p);
		GenericPoint2<T>& operator+=(const GenericVector2<T>& v1);
		GenericPoint2<T>& operator-=(const GenericVector2<T>& v1);

		void collectInternalMembers(MemberStringDumpCollector& collector) const;
		blocxx::String toString(const Indentation& indent = Indentation(), StringDumpable::PrefixType prefix = StringDumpable::E_PREFIX_NONE ) const;

		blocxx::String name() const { return "Point2"; }
	}; // class GenericPoint2

	template <class T>
	inline GenericPoint2<T>& GenericPoint2<T>::operator=(const GenericPoint2<T>& p)
	{
		set( p.x(), p.y() );

		return *this;
	}

	template <class T>
	inline GenericPoint2<T>& GenericPoint2<T>::operator+=(const GenericVector2<T>& v1)
	{
		set( x() + v1.x(),
			y() + v1.y() );
		return *this;
	}

	template <class T>
	inline GenericPoint2<T>& GenericPoint2<T>::operator-=(const GenericVector2<T>& v1)
	{
		set( x() - v1.x(),
			y() - v1.y() );
		return *this;
	}

	template <class T>
	inline GenericVector2<T> operator-(const GenericPoint2<T>& p1, const GenericPoint2<T>& p2)
	{
		return GenericVector2<T>(p1.x() - p2.x(), p1.y() - p2.y());
	}

	template <class T>
	inline GenericPoint2<T>  operator+(const GenericPoint2<T>& p1, const GenericVector2<T>& v1)
	{
		return GenericPoint2<T>(p1.x() + v1.x(), p1.y() + v1.y());
	}

	template <class T>
	inline GenericPoint2<T>  operator-(const GenericPoint2<T>& p1, const GenericVector2<T>& v1)
	{
		return GenericPoint2<T>(p1.x() - v1.x(), p1.y() - v1.y());
	}

	template <class T>
	inline T averageComponent(const GenericPoint2<T>& v)
	{
		return((v.x() + v.y()) / 2);
	}

	template <class T>
	inline T maxComponent(const GenericPoint2<T>& v)
	{
		return(std::max(v.x(), v.y()));
	}
	
	template <class T>
	inline GenericPoint2<T> midpoint(const GenericPoint2<T>& p1, const GenericPoint2<T>& p2)
	{
		return GenericPoint2<T>((p1.x() + p2.x()) / 2, (p1.y() + p2.y()) / 2);
	}

	template <class T>
	void GenericPoint2<T>::collectInternalMembers(MemberStringDumpCollector& collector) const
	{
		GenericCoord2<T>::collectInternalMembers(collector);
	}

	template <class T>
	blocxx::String GenericPoint2<T>::toString(const Indentation& indent, StringDumpable::PrefixType prefix) const
	{
		blocxx::String tag;
		if( prefix == StringDumpable::E_PREFIX_CLASSNAME )
		{
			tag = GenericPoint2<T>::name();
		}

		return indent.initial() + tag +
			"(" +
			panorama::toString(x(), indent.indentInside(), prefix) +
			"," +
			panorama::toString(y(), indent.indentInside(), prefix) +
			")";
	}

	template <class T>
	bool operator==(const GenericPoint2<T>& lhs, const GenericPoint2<T>& rhs)
	{
		return fuzzyEquals(lhs.x(), rhs.x()) && fuzzyEquals(lhs.y(), rhs.y());
	}

	template <class T>
	bool operator!=(const GenericPoint2<T>& lhs, const GenericPoint2<T>& rhs)
	{
		return !(lhs == rhs);
	}

} // namespace panorama

#endif /* !defined(PANORAMA__GENERICPOINT2_HPP) */
