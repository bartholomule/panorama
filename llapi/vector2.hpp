/*
 * $Id: vector2.hpp,v 1.1.2.1 2009/02/22 10:22:10 kpharris Exp $
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

#if    !defined(PANORAMA__VECTOR2_HPP)
#define         PANORAMA__VECTOR2_HPP

/*
  vector2.hpp

  The 2d equiv of the stuff in vector3.hpp
*/

/*
  Revision history:
  17Jan1999 Wrote this file, did some basic testing.
  20jan1999 Added a default constructor.
  18May2001 "Templatized" the class...
*/

#include "coord2.hpp"

namespace panorama
{
  template <class T>
  class vector2 : public virtual StringDumpable, private coord2<T>
  {
  public:
    typedef T base;

    inline vector2() : coord2<T>()
    {
    }
    inline vector2(T x, T y): coord2<T>(x,y)
    {
    }
    inline vector2(const coord2<T>& c): coord2<T>(c)
    {
    }

    inline void set(T x, T y)
    {
      coord2<T>::set(x,y);
    }

    /* Accessors */
    inline T& operator[](int coord_index)
    {
      return(coord2<T>::operator[](coord_index));
    }

    inline T  operator[](int coord_index) const
    {
      return(coord2<T>::operator[](coord_index));
    }

    T& x()
    {
      return(coord2<T>::x());
    }
    T  x() const
    {
      return(coord2<T>::x());
    }
    T& y()
    {
      return(coord2<T>::y());
    }
    T  y() const
    {
      return(coord2<T>::y());
    }

    vector2<T>& operator=(const vector2<T>& v2);
    vector2<T>& operator+=(const vector2<T>& v1);
    vector2<T>& operator-=(const vector2<T>& v1);
    inline vector2<T>& operator*=(T factor);
    inline vector2<T>& operator/=(T factor);

    template <class U>
    inline vector2<T>& operator*=(U factor);
    template <class U>
    inline vector2<T>& operator/=(U factor);

    std::string internalMembers(const Indentation& indent, StringDumpable::PrefixType prefix) const;
    std::string toString(const Indentation& indent, StringDumpable::PrefixType prefix) const;

  }; // class vector2;

  template <class T>
  inline vector2<T>& vector2<T>::operator=(const vector2<T>& p2)
  {
    set( p2.x(), p2.y() );
    return(*this);
  }

  template <class T>
  inline vector2<T>& vector2<T>::operator+=(const vector2<T>& p2)
  {
    x() += p2.x();
    y() += p2.y();
    return(*this);
  }

  template <class T>
  inline vector2<T>& vector2<T>::operator-=(const vector2<T>& p2)
  {
    x() -= p2.x();
    y() -= p2.y();
    return(*this);
  }

  template <class T>
  inline vector2<T>& vector2<T>::operator*=(T d)
  {
    x() *= d;
    y() *= d;
    return(*this);
  }

  template <class T>
  inline vector2<T>& vector2<T>::operator/=(T d)
  {
    x() /= d;
    y() /= d;
    return(*this);
  }

  template <class T>
  template <class U>
  inline vector2<T>& vector2<T>::operator*=(U factor)
  {
    set( T(x() * factor),
      T(y() * factor) );
    return *this;
  }

  template <class T>
  template <class U>
  inline vector2<T>& vector2<T>::operator/=(U factor)
  {
    set( T(x() / factor),
      T(y() / factor) );
    return *this;
  }


  template <class T>
  inline vector2<T> operator-(const vector2<T>& v1)
  {
    return(T(-1)*v1);
  }

  template <class T>
  inline vector2<T> operator*(const vector2<T>& v, T d)
  {
    vector2<T> temp(v);
    temp *= d;
    return temp;
  }

  template <class T>
  inline vector2<T> operator*(T d, const vector2<T>& v)
  {
    vector2<T> temp(v);
    temp *= d;
    return temp;
  }

  template <class T, class U>
  inline vector2<T> operator*(const vector2<T>& v, U factor)
  {
    vector2<T> temp(v);
    temp *= factor;
    return temp;
  }

  template <class T, class U>
  inline vector2<T> operator*(U factor, const vector2<T>& v)
  {
    vector2<T> temp(v);
    temp *= factor;
    return temp;
  }

  template <class T>
  inline vector2<T> operator/(const vector2<T>& v, T factor)
  {
    vector2<T> temp(v);
    temp /= factor;
    return temp;
  }

  template <class T, class U>
  inline vector2<T> operator/(const vector2<T>& v, U factor)
  {
    vector2<T> temp(v);
    temp /= factor;
    return temp;
  }

  template <class T>
  inline vector2<T> operator-(const vector2<T>& v1, const vector2<T>& v2)
  {
    vector2<T> temp(v1);
    temp -= v2;
    return temp;
  }

  template <class T>
  inline vector2<T> operator+(const vector2<T>& v1, const vector2<T>& v2)
  {
    vector2<T> temp(v1);
    temp += v2;
    return temp;
  }

  template <class T>
  inline T dotprod(const vector2<T>& v1, const vector2<T>& v2)
  {
    return((v1.x() * v2.x()) +
      (v1.y() * v2.y()));
  }

  template <class T>
  inline T length(const vector2<T>& v)
  {
    T squared_length = dotprod(v,v);
    return T(sqrt(squared_length));
  }

  // FIXME! Find an exception to throw...
  template <class T>
  inline vector2<T> unit(const vector2<T>& v)
  {
    T len = length(v);
    // FIXME! Check the squared length >= 0
    return v / len;
  }

  template <class T>
  inline vector2<T> invert(const vector2<T>& v)
  {
    return(vector2<T>(1/v.x(), 1/v.y()));
  }

  template <class T>
  inline T average(const vector2<T>& v)
  {
    return((v.x() + v.y()) / 2);
  }


  template <class T>
  std::string vector2<T>::internalMembers(const Indentation& indent, PrefixType prefix) const
  {
    std::string tag = indent.level();
    if( prefix == E_PREFIX_CLASSNAME )
    {
      tag += vector2<T>::name() + "::";
    }

    return ( tag + string_format("x=%1\n", x()) +
      tag + string_format("y=%1\n", y()));
  }

  template <class T>
  std::string vector2<T>::toString(const Indentation& indent, PrefixType prefix) const
  {
    std::string tag;
    if( prefix == E_PREFIX_CLASSNAME )
    {
      tag = vector2<T>::name();
    }

    return indent + tag + string_format("<%1,%2>", x(), y());
  }

} // namespace panorama

#endif /* !defined(PANORAMA__VECTOR2_HPP) */
