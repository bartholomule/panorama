/*
 * $Id: GenericVector3.hpp,v 1.1.2.1 2009/06/15 01:26:18 kpharris Exp $
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

#if    !defined(PANORAMA__GENERICVECTOR3_HPP)
#define         PANORAMA__GENERICVECTOR3_HPP

/*
  GenericVector3.hpp

  This goes along with the GenericPoint3 class, and has very few internal functions.
  It is intended for use as you would any vector.
*/


/*
  Revision history:
  17jan1999 Wrote this file, did some basic testing.
  20jan1999 Added a default constructor.
  09Mar1999 Added the operator* to make the sgi compiler happy.  It was
  complaining that there were multiple ways to do the multiplication
  operation by converting the vector to other types.
  Added the - operator for the same reason.
  18May2001 "Templatized" the class...
  17Sep2003 Changed the inheritence from public to private.  Added accessors,
  fixed implementation to use those accessors.
  ...
  14Jun2009 Renamed to be GenericVector3, fixed the string conversions to match
  the new style.
*/

#include "panorama/common/GenericCoord3.hpp"

namespace panorama
{
	template <class T>
	class GenericVector3: private GenericCoord3<T>
	{
	public:
		// This tag allows use in the StringDumpable.hpp toString functions
		// without requiring the overridden virtual functions.
		typedef bool CanBeStringDumpedTag;

		using GenericCoord3<T>::COORD_VALUES;
		using GenericCoord3<T>::X;
		using GenericCoord3<T>::Y;
		using GenericCoord3<T>::Z;

		typedef T base;

		inline GenericVector3() : GenericCoord3<T>()
		{
		}
		inline GenericVector3(T x, T y, T z): GenericCoord3<T>(x,y,z)
		{
		}
		inline explicit GenericVector3(const GenericCoord3<T>& c): GenericCoord3<T>(c)
		{
		}
		inline GenericVector3(const GenericVector3<T>& c): GenericCoord3<T>(c)
		{
		}

		inline void set(T x, T y, T z)
		{
			GenericCoord3<T>::set(x,y,z);
		}

		/* Accessors */
		inline T& operator[](unsigned coord_index)
		{
			return(GenericCoord3<T>::operator[](coord_index));
		}

		inline T  operator[](unsigned coord_index) const
		{
			return(GenericCoord3<T>::operator[](coord_index));
		}

		T& x()
		{
			return(GenericCoord3<T>::x());
		}
		T  x() const
		{
			return(GenericCoord3<T>::x());
		}
		T& y()
		{
			return(GenericCoord3<T>::y());
		}
		T  y() const
		{
			return(GenericCoord3<T>::y());
		}
		T& z()
		{
			return(GenericCoord3<T>::z());
		}
		T  z() const
		{
			return(GenericCoord3<T>::z());
		}


		GenericVector3<T>& operator=(const GenericVector3<T>& p2);
		inline GenericVector3<T>& operator+=(const GenericVector3<T>& p2);
		inline GenericVector3<T>& operator-=(const GenericVector3<T>& p2);
		inline GenericVector3<T>& operator*=(T factor);
		inline GenericVector3<T>& operator/=(T factor);

		template <class U>
		inline GenericVector3<T>& operator*=(U factor);
		template <class U>
		inline GenericVector3<T>& operator/=(U factor);


		void collectInternalMembers(MemberStringDumpCollector& collector) const;
		blocxx::String toString(const Indentation& indent = Indentation(), StringDumpable::PrefixType prefix = StringDumpable::E_PREFIX_NONE ) const;

		blocxx::String name() const { return "Vector3"; }

	}; // class GenericVector3

	template <class T>
	inline GenericVector3<T>& GenericVector3<T>::operator=(const GenericVector3<T>& p2)
	{
		set( p2.x(), p2.y(), p2.z() );
		return(*this);
	}

	template <class T>
	inline GenericVector3<T>& GenericVector3<T>::operator+=(const GenericVector3<T>& p2)
	{
		x() += p2.x();
		y() += p2.y();
		z() += p2.z();
		return(*this);
	}

	template <class T>
	inline GenericVector3<T>& GenericVector3<T>::operator-=(const GenericVector3<T>& p2)
	{
		x() -= p2.x();
		y() -= p2.y();
		z() -= p2.z();
		return(*this);
	}

	template <class T>
	inline GenericVector3<T>& GenericVector3<T>::operator*=(T d)
	{
		x() *= d;
		y() *= d;
		z() *= d;
		return(*this);
	}

	template <class T>
	inline GenericVector3<T>& GenericVector3<T>::operator/=(T d)
	{
		x() /= d;
		y() /= d;
		z() /= d;
		return(*this);
	}

	template <class T>
	template <class U>
	inline GenericVector3<T>& GenericVector3<T>::operator*=(U factor)
	{
		set( T(x() * factor),
			T(y() * factor),
			T(z() * factor) );
		return *this;
	}

	template <class T>
	template <class U>
	inline GenericVector3<T>& GenericVector3<T>::operator/=(U factor)
	{
		set( T(x() / factor),
			T(y() / factor),
			T(z() / factor) );
		return *this;
	}


	template <class T>
	inline GenericVector3<T> operator-(const GenericVector3<T>& v1)
	{
		return(T(-1)*v1);
	}

	template <class T>
	inline GenericVector3<T> operator*(const GenericVector3<T>& v, T d)
	{
		GenericVector3<T> temp(v);
		temp *= d;
		return temp;
	}

	template <class T>
	inline GenericVector3<T> operator*(T d, const GenericVector3<T>& v)
	{
		GenericVector3<T> temp(v);
		temp *= d;
		return temp;
	}

	template <class T, class U>
	inline GenericVector3<T> operator*(const GenericVector3<T>& v, U factor)
	{
		GenericVector3<T> temp(v);
		temp *= factor;
		return temp;
	}

	template <class T, class U>
	inline GenericVector3<T> operator*(U factor, const GenericVector3<T>& v)
	{
		GenericVector3<T> temp(v);
		temp *= factor;
		return temp;
	}

	template <class T>
	inline GenericVector3<T> operator/(const GenericVector3<T>& v, T factor)
	{
		GenericVector3<T> temp(v);
		temp /= factor;
		return temp;
	}

	template <class T, class U>
	inline GenericVector3<T> operator/(const GenericVector3<T>& v, U factor)
	{
		GenericVector3<T> temp(v);
		temp /= factor;
		return temp;
	}

	template <class T>
	inline GenericVector3<T> operator-(const GenericVector3<T>& v1, const GenericVector3<T>& v2)
	{
		GenericVector3<T> temp(v1);
		temp -= v2;
		return temp;
	}

	template <class T>
	inline GenericVector3<T> operator+(const GenericVector3<T>& v1, const GenericVector3<T>& v2)
	{
		GenericVector3<T> temp(v1);
		temp += v2;
		return temp;
	}


	template <class T>
	inline T dotprod(const GenericVector3<T>& v1, const GenericVector3<T>& v2)
	{
		return((v1.x() * v2.x()) +
			(v1.y() * v2.y()) +
			(v1.z() * v2.z()));
	}

	template <class T>
	inline GenericVector3<T> crossprod(const GenericVector3<T>& v1, const GenericVector3<T>& v2)
	{
		return GenericVector3<T>(
			(v1.y()*v2.z()) - (v2.y()*v1.z()),
			(v2.x()*v1.z()) - (v1.x()*v2.z()),
			(v1.x()*v2.y()) - (v2.x()*v1.y())
		);
	}

	template <class T>
	inline T length(const GenericVector3<T>& v)
	{
		T squared_length = dotprod(v,v);
		return T(sqrt(double(squared_length)));
	}

	template <class T>
	inline T squared_length(const GenericVector3<T>& v)
	{
		return dotprod(v,v);
	}

	template <class T>
	inline GenericVector3<T> unit(const GenericVector3<T>& v)
	{
		T len = length(v);
		return v / len;
	}

	template <class T>
	inline GenericVector3<T> invert(const GenericVector3<T>& v)
	{
		return(GenericVector3<T>(1/v.x(), 1/v.y(), 1/v.z()));
	}

	template <class T>
	inline T averageComponent(const GenericVector3<T>& v)
	{
		return (v.x() + v.y() + v.z()) / T(3);
	}

	template <class T>
	inline T maxComponent(const GenericVector3<T>& v)
	{
		return std::max(std::max(v.x(), v.y()), v.z());
	}

	template <class T>
	inline GenericVector3<T> abs(const GenericVector3<T>& v)
	{
		return GenericVector3<T>(
			std::max(v.x(), -v.x()),
			std::max(v.y(), -v.y()),
			std::max(v.z(), -v.z()));
	}


	template <class T>
	void GenericVector3<T>::collectInternalMembers(MemberStringDumpCollector& collector) const
	{
		GenericCoord3<T>::collectInternalMembers(collector);
	}

	template <class T>
	blocxx::String GenericVector3<T>::toString(const Indentation& indent, StringDumpable::PrefixType prefix) const
	{
		blocxx::String tag;
		if( prefix == StringDumpable::E_PREFIX_CLASSNAME )
		{
			tag = GenericVector3<T>::name();
		}

		return indent + tag +
			"<" +
			panorama::toString(x(), indent.indentInside(), prefix) +
			"," +
			panorama::toString(y(), indent.indentInside(), prefix) +
			"," +
			panorama::toString(z(), indent.indentInside(), prefix) +
			">";
	}
} // namespace panorama

#endif /* !defined(PANORAMA__GENERICVECTOR3_HPP) */
