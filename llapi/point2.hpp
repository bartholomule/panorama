/*
 * $Id: point2.hpp,v 1.1.2.1 2009/02/22 10:22:10 kpharris Exp $
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

#if    !defined(PANORAMA__POINT2_HPP)
#define         PANORAMA__POINT2_HPP

/*
  point2.hpp

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
*/

#include "llapi/coord2.hpp"
#include "llapi/vector2.hpp"

namespace panorama
{

  template <class T>
  class point2: private coord2<T>, public virtual StringDumpable
  {
  public:
    typedef T base;

    inline point2():coord2<T>()
    {
    }
    inline point2(T x, T y): coord2<T>(x,y)
    {
    }
    inline explicit point2(const coord2<T>& c): coord2<T>(c)
    {
    }
    inline point2(const point2<T>& p): coord2<T>(p)
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

    point2<T>& operator=(const point2<T>& p);
    point2<T>& operator+=(const vector2<T>& v1);
    point2<T>& operator-=(const vector2<T>& v1);

    std::string internalMembers(const Indentation& indent, StringDumpable::PrefixType prefix) const;
    std::string toString(const Indentation& indent, StringDumpable::PrefixType prefix) const;
  }; // class point2

  template <class T>
  inline point2<T>& point2<T>::operator=(const point2<T>& p)
  {
    set( p.x(), p.y() );

    return *this;
  }

  template <class T>
  inline point2<T>& point2<T>::operator+=(const vector2<T>& v1)
  {
    set( x() + v1.x(),
      y() + v1.y() );
    return *this;
  }

  template <class T>
  inline point2<T>& point2<T>::operator-=(const vector2<T>& v1)
  {
    set( x() - v1.x(),
      y() - v1.y() );
    return *this;
  }

  template <class T>
  inline vector2<T> operator-(const point2<T>& p1, const point2<T>& p2)
  {
    return vector2<T>(p1.x() - p2.x(), p1.y() - p2.y());
  }

  template <class T>
  inline point2<T>  operator+(const point2<T>& p1, const vector2<T>& v1)
  {
    return point2<T>(p1.x() + v1.x(), p1.y() + v1.y());
  }

  template <class T>
  inline point2<T>  operator-(const point2<T>& p1, const vector2<T>& v1)
  {
    return point2<T>(p1.x() - v1.x(), p1.y() - v1.y());
  }

  template <class T>
  std::string point2<T>::internalMembers(const Indentation& indent, PrefixType prefix) const
  {
    std::string tag = indent.level();
    if( prefix == E_PREFIX_CLASSNAME )
    {
      tag += point2<T>::name() + "::";
    }

    return ( tag + string_format("x=%1\n", x()) +
      tag + string_format("y=%1\n", y()));
  }

  template <class T>
  std::string point2<T>::toString(const Indentation& indent, PrefixType prefix) const
  {
    std::string tag;
    if( prefix == E_PREFIX_CLASSNAME )
    {
      tag = point2<T>::name();
    }

    return indent + tag + string_format("(%1,%2)", x(), y());
  }

} // namespace panorama

#endif /* !defined(PANORAMA__POINT2_HPP) */
