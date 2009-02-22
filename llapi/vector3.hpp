/*
 * $Id: vector3.hpp,v 1.1.2.1 2009/02/22 10:22:10 kpharris Exp $
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

#if    !defined(PANORAMA__VECTOR3_HPP)
#define         PANORAMA__VECTOR3_HPP

/*
  vector3.hpp

  This goes along with the point3 class, and has very few internal functions.
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
*/

#include "llapi/coord3.hpp"

namespace panorama
{
  template <class T>
  class vector3: public virtual StringDumpable, private coord3<T>
  {
  public:
    typedef T base;

    inline vector3() : StringDumpable(), coord3<T>()
    {
    }
    inline vector3(T x, T y, T z): coord3<T>(x,y,z)
    {
    }
    inline explicit vector3(const coord3<T>& c): coord3<T>(c)
    {
    }
    inline vector3(const vector3<T>& c): coord3<T>(c)
    {
    }

    inline void set(T x, T y, T z)
    {
      coord3<T>::set(x,y,z);
    }

    /* Accessors */
    inline T& operator[](unsigned coord_index)
    {
      return(coord3<T>::operator[](coord_index));
    }

    inline T  operator[](unsigned coord_index) const
    {
      return(coord3<T>::operator[](coord_index));
    }

    T& x()
    {
      return(coord3<T>::x());
    }
    T  x() const
    {
      return(coord3<T>::x());
    }
    T& y()
    {
      return(coord3<T>::y());
    }
    T  y() const
    {
      return(coord3<T>::y());
    }
    T& z()
    {
      return(coord3<T>::z());
    }
    T  z() const
    {
      return(coord3<T>::z());
    }


    vector3<T>& operator=(const vector3<T>& p2);
    inline vector3<T>& operator+=(const vector3<T>& p2);
    inline vector3<T>& operator-=(const vector3<T>& p2);
    inline vector3<T>& operator*=(T factor);
    inline vector3<T>& operator/=(T factor);

    template <class U>
    inline vector3<T>& operator*=(U factor);
    template <class U>
    inline vector3<T>& operator/=(U factor);

    std::string internalMembers(const Indentation& indent, StringDumpable::PrefixType prefix) const;
    std::string toString(const Indentation& indent, StringDumpable::PrefixType prefix) const;

  }; // class vector3

  template <class T>
  inline vector3<T>& vector3<T>::operator=(const vector3<T>& p2)
  {
    set( p2.x(), p2.y(), p2.z() );
    return(*this);
  }

  template <class T>
  inline vector3<T>& vector3<T>::operator+=(const vector3<T>& p2)
  {
    x() += p2.x();
    y() += p2.y();
    z() += p2.z();
    return(*this);
  }

  template <class T>
  inline vector3<T>& vector3<T>::operator-=(const vector3<T>& p2)
  {
    x() -= p2.x();
    y() -= p2.y();
    z() -= p2.z();
    return(*this);
  }

  template <class T>
  inline vector3<T>& vector3<T>::operator*=(T d)
  {
    x() *= d;
    y() *= d;
    z() *= d;
    return(*this);
  }

  template <class T>
  inline vector3<T>& vector3<T>::operator/=(T d)
  {
    x() /= d;
    y() /= d;
    z() /= d;
    return(*this);
  }

  template <class T>
  template <class U>
  inline vector3<T>& vector3<T>::operator*=(U factor)
  {
    set( T(x() * factor),
      T(y() * factor),
      T(z() * factor) );
    return *this;
  }

  template <class T>
  template <class U>
  inline vector3<T>& vector3<T>::operator/=(U factor)
  {
    set( T(x() / factor),
      T(y() / factor),
      T(z() / factor) );
    return *this;
  }


  template <class T>
  inline vector3<T> operator-(const vector3<T>& v1)
  {
    return(T(-1)*v1);
  }

  template <class T>
  inline vector3<T> operator*(const vector3<T>& v, T d)
  {
    vector3<T> temp(v);
    temp *= d;
    return temp;
  }

  template <class T>
  inline vector3<T> operator*(T d, const vector3<T>& v)
  {
    vector3<T> temp(v);
    temp *= d;
    return temp;
  }

  template <class T, class U>
  inline vector3<T> operator*(const vector3<T>& v, U factor)
  {
    vector3<T> temp(v);
    temp *= factor;
    return temp;
  }

  template <class T, class U>
  inline vector3<T> operator*(U factor, const vector3<T>& v)
  {
    vector3<T> temp(v);
    temp *= factor;
    return temp;
  }

  template <class T>
  inline vector3<T> operator/(const vector3<T>& v, T factor)
  {
    vector3<T> temp(v);
    temp /= factor;
    return temp;
  }

  template <class T, class U>
  inline vector3<T> operator/(const vector3<T>& v, U factor)
  {
    vector3<T> temp(v);
    temp /= factor;
    return temp;
  }

  template <class T>
  inline vector3<T> operator-(const vector3<T>& v1, const vector3<T>& v2)
  {
    vector3<T> temp(v1);
    temp -= v2;
    return temp;
  }

  template <class T>
  inline vector3<T> operator+(const vector3<T>& v1, const vector3<T>& v2)
  {
    vector3<T> temp(v1);
    temp += v2;
    return temp;
  }


  template <class T>
  inline T dotprod(const vector3<T>& v1, const vector3<T>& v2)
  {
    return((v1.x() * v2.x()) +
      (v1.y() * v2.y()) +
      (v1.z() * v2.z()));
  }

  template <class T>
  inline vector3<T> crossprod(const vector3<T>& v1, const vector3<T>& v2)
  {
    return vector3<T>(
      (v1.y()*v2.z()) - (v2.y()*v1.z()),
      (v2.x()*v1.z()) - (v1.x()*v2.z()),
      (v1.x()*v2.y()) - (v2.x()*v1.y())
    );
  }

  template <class T>
  inline T length(const vector3<T>& v)
  {
    T squared_length = dotprod(v,v);
    return T(sqrt(double(squared_length)));
  }

  template <class T>
  inline T squared_length(const vector3<T>& v)
  {
    return dotprod(v,v);
  }

  // FIXME! Find an exception to throw...
  template <class T>
  inline vector3<T> unit(const vector3<T>& v)
  {
    T len = length(v);
    // FIXME! Check the squared length >= 0
    return v / len;
  }

  template <class T>
  std::string vector3<T>::internalMembers(const Indentation& indent, PrefixType prefix) const
  {
    std::string tag = indent.level();
    if( prefix == E_PREFIX_CLASSNAME )
    {
      tag += vector3<T>::name() + "::";
    }

    return ( tag + string_format("x=%1\n", x()) +
      tag + string_format("y=%1\n", y()),
      tag + string_format("z=%1\n", z()) );
  }

  template <class T>
  std::string vector3<T>::toString(const Indentation& indent, PrefixType prefix) const
  {
    std::string tag;
    if( prefix == E_PREFIX_CLASSNAME )
    {
      tag = vector3<T>::name();
    }

    return indent + tag + string_format("<%1,%2,%3>", x(), y(), z());
  }
} // namespace panorama

#endif /* !defined(PANORAMA__VECTOR3_HPP) */
