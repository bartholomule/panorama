/*
 * $Id: point3.hpp,v 1.1.2.1 2009/02/22 10:22:10 kpharris Exp $
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

#if    !defined(PANORAMA__POINT3_HPP)
#define         PANORAMA__POINT3_HPP

/*
  point3.hpp

  An expansion of the coord3 class to allow the creation of distinct types.

  It allows for creation of a vector by subtracting two points, and creation of
  another point by addition or subtraction of a vector to a point.
*/


/*
  Revision history:
  17jan1999 Wrote this file, did some basic testing.  Added the extraction
  operator to this, and the other '3' classes (vector3, coord3).
  This will make different output when dumped on a stream.  It could
  come in handy when debugging something.
  20jan1999 Added a default constructor.
  18May2001 "Templatized" the class...
  17Sep2003 Changed the inheritence from public to private.  Added accessors,
  fixed implementation to use those accessors.
*/

#include "llapi/coord3.hpp"
#include "llapi/vector3.hpp"

namespace panorama
{

  template <class T>
  class point3: private coord3<T>, public virtual StringDumpable
  {
  public:
    typedef T base;

    inline point3(): coord3<T>()
    {
    }
    inline point3(T x, T y, T z): coord3<T>(x,y,z)
    {
    }
    inline explicit point3(const coord3<T>& c): coord3<T>(c)
    {
    }
    inline point3(const point3<T>& c): coord3<T>(c)
    {
    }

    coord3<T> getcoord() const
    {
      return coord3<T>(x(), y(), z());
    }

    inline void set(T x, T y, T z)
    {
      coord3<T>::set(x,y,z);
    }

    /* Accessors */
    inline T& operator[](int coord_index)
    {
      return(coord3<T>::operator[](coord_index));
    }

    inline T  operator[](int coord_index) const
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

    point3<T>& operator=(const point3<T>& p);
    point3<T>& operator+=(const vector3<T>& v1);
    point3<T>& operator-=(const vector3<T>& v1);

    std::string internalMembers(const Indentation& indent, StringDumpable::PrefixType prefix) const;
    std::string toString(const Indentation& indent, StringDumpable::PrefixType prefix) const;

  }; // class point3

  template <class T>
  inline point3<T>& point3<T>::operator=(const point3<T>& p)
  {
    set(p.x(), p.y(), p.z());
    return(*this);
  }

  template <class T>
  inline point3<T>& point3<T>::operator+=(const vector3<T>& v1)
  {
    set(x() + v1.x(),
      y() + v1.y(),
      z() + v1.z());
    return(*this);
  }

  template <class T>
  inline point3<T>& point3<T>::operator-=(const vector3<T>& v1)
  {
    set(x() - v1.x(),
      y() - v1.y(),
      z() - v1.z());
    return(*this);
  }


  template <class T>
  inline vector3<T> operator-(const point3<T>& p1, const point3<T>& p2)
  {
    return vector3<T>(p1.x() - p2.x(),
      p1.y() - p2.y(),
      p1.z() - p2.z());
  }
  template <class T>
  inline point3<T>  operator+(const point3<T>& p1, const vector3<T>& v1)
  {
    return point3<T>(p1.x() + v1.x(),
      p1.y() + v1.y(),
      p1.z() + v1.z());
  }
  template <class T>
  inline point3<T>  operator-(const point3<T>& p1, const vector3<T>& v1)
  {
    return point3<T>(p1.x() - v1.x(),
      p1.y() - v1.y(),
      p1.z() - v1.z());
  }
  template <class T>
  inline point3<T>  operator+(const vector3<T>& v1, const point3<T>& p1)
  {
    return point3<T>(p1.x() + v1.x(),
      p1.y() + v1.y(),
      p1.z() + v1.z());
  }
  template <class T>
  inline point3<T>  operator-(const vector3<T>& v1, const point3<T>& p1)
  {
    return point3<T>(v1.x() - p1.x(),
      v1.y() - p1.y(),
      v1.z() - p1.z());
  }

  template <class T>
  std::string point3<T>::internalMembers(const Indentation& indent, PrefixType prefix) const
  {
    std::string tag = indent.level();
    if( prefix == E_PREFIX_CLASSNAME )
    {
      tag += point3<T>::name() + "::";
    }

    return ( tag + string_format("x=%1\n", x()) +
      tag + string_format("y=%1\n", y()),
      tag + string_format("z=%1\n", z()) );
  }

  template <class T>
  std::string point3<T>::toString(const Indentation& indent, PrefixType prefix) const
  {
    std::string tag;
    if( prefix == E_PREFIX_CLASSNAME )
    {
      tag = point3<T>::name();
    }

    return indent + tag + string_format("(%1,%2,%3)", x(), y(), z());
  }

} // namespace panorama

#endif /* !defined(PANORAMA__POINT3_HPP) */
