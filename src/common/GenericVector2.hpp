/*
 * $Id: GenericVector2.hpp,v 1.1.2.2 2010/03/03 17:54:10 kpharris Exp $
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

#if    !defined(PANORAMA__GENERICVECTOR2_HPP)
#define         PANORAMA__GENERICVECTOR2_HPP

/*
  GenericVector2.hpp

  The 2d equiv of the stuff in vector3.hpp
*/

/*
  Revision history:
  17Jan1999 Wrote this file, did some basic testing.
  20jan1999 Added a default constructor.
  18May2001 "Templatized" the class...
*/

#include "panorama/common/GenericCoord2.hpp"

namespace panorama
{
	template <class T>
	class GenericVector2 : private GenericCoord2<T>
	{
	public:
		// This tag allows use in the StringDumpable.hpp toString functions
		// without requiring the overridden virtual functions.
		typedef bool CanBeStringDumpedTag;

		using GenericCoord2<T>::COORD_VALUES;
		using GenericCoord2<T>::X;
		using GenericCoord2<T>::Y;

		typedef T base;

		inline GenericVector2() : GenericCoord2<T>()
		{
		}
		inline GenericVector2(T x, T y): GenericCoord2<T>(x,y)
		{
		}
		inline GenericVector2(const GenericCoord2<T>& c): GenericCoord2<T>(c)
		{
		}

		inline void set(T x, T y)
		{
			GenericCoord2<T>::set(x,y);
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

		GenericVector2<T>& operator=(const GenericVector2<T>& v2);
		GenericVector2<T>& operator+=(const GenericVector2<T>& v1);
		GenericVector2<T>& operator-=(const GenericVector2<T>& v1);
		inline GenericVector2<T>& operator*=(T factor);
		inline GenericVector2<T>& operator/=(T factor);

		template <class U>
		inline GenericVector2<T>& operator*=(U factor);
		template <class U>
		inline GenericVector2<T>& operator/=(U factor);

		inline T length() const
		{
			return(T(sqrt(double(x() * x() + y() * y()))));
		}

		void collectInternalMembers(MemberStringDumpCollector& collector) const;
		blocxx::String toString(const Indentation& indent = Indentation(), StringDumpable::PrefixType prefix = StringDumpable::E_PREFIX_NONE ) const;

		blocxx::String name() const { return "Vector2"; }

	}; // class GenericVector2;

	template <class T>
	inline GenericVector2<T>& GenericVector2<T>::operator=(const GenericVector2<T>& p2)
	{
		set( p2.x(), p2.y() );
		return(*this);
	}

	template <class T>
	inline GenericVector2<T>& GenericVector2<T>::operator+=(const GenericVector2<T>& p2)
	{
		x() += p2.x();
		y() += p2.y();
		return(*this);
	}

	template <class T>
	inline GenericVector2<T>& GenericVector2<T>::operator-=(const GenericVector2<T>& p2)
	{
		x() -= p2.x();
		y() -= p2.y();
		return(*this);
	}

	template <class T>
	inline GenericVector2<T>& GenericVector2<T>::operator*=(T d)
	{
		x() *= d;
		y() *= d;
		return(*this);
	}

	template <class T>
	inline GenericVector2<T>& GenericVector2<T>::operator/=(T d)
	{
		x() /= d;
		y() /= d;
		return(*this);
	}

	template <class T>
	template <class U>
	inline GenericVector2<T>& GenericVector2<T>::operator*=(U factor)
	{
		set( T(x() * factor),
			T(y() * factor) );
		return *this;
	}

	template <class T>
	template <class U>
	inline GenericVector2<T>& GenericVector2<T>::operator/=(U factor)
	{
		set( T(x() / factor),
			T(y() / factor) );
		return *this;
	}


	template <class T>
	inline GenericVector2<T> operator-(const GenericVector2<T>& v1)
	{
		return(T(-1)*v1);
	}

	template <class T>
	inline GenericVector2<T> operator*(const GenericVector2<T>& v, T d)
	{
		GenericVector2<T> temp(v);
		temp *= d;
		return temp;
	}

	template <class T>
	inline GenericVector2<T> operator*(T d, const GenericVector2<T>& v)
	{
		GenericVector2<T> temp(v);
		temp *= d;
		return temp;
	}

	template <class T, class U>
	inline GenericVector2<T> operator*(const GenericVector2<T>& v, U factor)
	{
		GenericVector2<T> temp(v);
		temp *= factor;
		return temp;
	}

	template <class T, class U>
	inline GenericVector2<T> operator*(U factor, const GenericVector2<T>& v)
	{
		GenericVector2<T> temp(v);
		temp *= factor;
		return temp;
	}

	template <class T>
	inline GenericVector2<T> operator/(const GenericVector2<T>& v, T factor)
	{
		GenericVector2<T> temp(v);
		temp /= factor;
		return temp;
	}

	template <class T, class U>
	inline GenericVector2<T> operator/(const GenericVector2<T>& v, U factor)
	{
		GenericVector2<T> temp(v);
		temp /= factor;
		return temp;
	}

	template <class T>
	inline GenericVector2<T> operator-(const GenericVector2<T>& v1, const GenericVector2<T>& v2)
	{
		GenericVector2<T> temp(v1);
		temp -= v2;
		return temp;
	}

	template <class T>
	inline GenericVector2<T> operator+(const GenericVector2<T>& v1, const GenericVector2<T>& v2)
	{
		GenericVector2<T> temp(v1);
		temp += v2;
		return temp;
	}

	template <class T>
	inline T dotprod(const GenericVector2<T>& v1, const GenericVector2<T>& v2)
	{
		return((v1.x() * v2.x()) +
			(v1.y() * v2.y()));
	}

	template <class T>
	inline T length(const GenericVector2<T>& v)
	{
		return v.length();
	}

	template <class T>
	inline GenericVector2<T> unit(const GenericVector2<T>& v)
	{
		return v / length(v);
	}

	template <class T>
	inline GenericVector2<T> invert(const GenericVector2<T>& v)
	{
		return(GenericVector2<T>(1/v.x(), 1/v.y()));
	}

	template <class T>
	inline T averageComponent(const GenericVector2<T>& v)
	{
		return((v.x() + v.y()) / 2);
	}

	template <class T>
	inline T maxComponent(const GenericVector2<T>& v)
	{
		return(std::max(v.x(), v.y()));
	}

	template <class T>
	inline GenericVector2<T> abs(const GenericVector2<T>& v)
	{
		return GenericVector2<T>(std::max(v.x(), -v.x()), std::max(v.y(), -v.y()));
	}

	template <class T>
	void GenericVector2<T>::collectInternalMembers(MemberStringDumpCollector& collector) const
	{
		GenericCoord2<T>::collectInternalMembers(collector);
	}

	template <class T>
	blocxx::String GenericVector2<T>::toString(const Indentation& indent, StringDumpable::PrefixType prefix) const
	{
		blocxx::String tag;
		if( prefix == StringDumpable::E_PREFIX_CLASSNAME )
		{
			tag = GenericVector2<T>::name();
		}

		return indent.initial() + tag +
			"<" +
			panorama::toString(x(), indent.indentInside(), prefix) +
			"," +
			panorama::toString(y(), indent.indentInside(), prefix) +
			">";
	}

} // namespace panorama

#endif /* !defined(PANORAMA__GENERICVECTOR2_HPP) */