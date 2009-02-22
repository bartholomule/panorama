/*
 * $Id: coord2.hpp,v 1.1.2.1 2009/02/22 10:22:10 kpharris Exp $
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

#if    !defined(PANORAMA__COORD2_HPP)
#define         PANORAMA__COORD2_HPP

/*
  coord2.hpp

  The 2d equiv of everything that I placed initially in coord3.h, except for
  the cross product, as there is no 2d equiv.
*/

/*
  Revision history:
  17Jan1999 Wrote this file, did some basic testing.
  20jan1999 Added a default constructor for the coord2 class.
  Added a default constructor for the union in the coord2 class.
  25jan1999 Added a unary - operator, and an invert function.
  18May2001 "Templatized" the class...
  17Sep2003 Reordered the class, made it a part of namespace panorama, changed
  extension to .hpp, added a GPL heading.
*/

#include <cmath>
#include <ostream>
#include <algorithm>
#include "llapi/string_dumpable.hpp"

namespace panorama
{

  template <class T>
  class coord2 : public virtual StringDumpable
  {
  private:
    /* class that has 2 Ts stored directly */
    struct coord2_direct
    {
      T x; T y;
    };
    /* class that has 2 Ts stored in an array */
    struct coord2_array
    {
      T coords[2];
    };
    /* union to allow accesses to both indirectly through an array, and directly
       through a name, without adding any extra processing time or space
       requirements */
    union  coord2_union
    {
      coord2_union()
      {
      }
      coord2_union(T x, T y)
      {
        direct.x = x; direct.y = y;
      }
      T& operator[](int index)
      {
        return(array.coords[index]);
      }
      T  operator[](int index) const
      {
        return(array.coords[index]);
      }
      coord2_direct direct;
      coord2_array  array;
    };

    /* The internal coordinates of this class */
    coord2_union coords;

  public:
    enum COORD_VALUES
      {
        X = 0, Y = 1
      };
    typedef T base;

    coord2()
    {
    }
    inline coord2(T x, T y):coords(x,y)
    {
    }
    inline coord2(const coord2& old_coord):coords(old_coord.coords)
    {
    }

    inline void set(T x, T y)
    {
      coords.direct.x = x; coords.direct.y = y;
    }

    /* Accessors */
    inline T& operator[](int coord_index)
    {
      return(coords[coord_index]);
    }

    inline T  operator[](int coord_index) const
    {
      return(coords[coord_index]);
    }

    T& x()
    {
      return(coords.direct.x);
    }
    T  x() const
    {
      return(coords.direct.x);
    }
    T& y()
    {
      return(coords.direct.y);
    }
    T  y() const
    {
      return(coords.direct.y);
    }


    coord2& operator=(const coord2& old_coord);
    coord2& operator+=(const coord2& p2);
    coord2& operator-=(const coord2& p2);
    coord2& operator*=(const coord2& p2); // Piecewise multiplication.
    coord2& operator*=(T factor);
    coord2& operator/=(T factor);
    template <class U>
    coord2& operator*=(U factor);
    template <class U>
    coord2& operator/=(U factor);

    /* Functions that more relate to vectors, but are needed */
    inline T length()          const
    {
      return(T(sqrt(double(x() * x() + y() * y()))));
    }


    virtual std::string internalMembers(const Indentation& indent, PrefixType prefix = E_PREFIX_NONE ) const;

    virtual std::string toString(const Indentation& indent = Indentation(), PrefixType prefix = E_PREFIX_NONE ) const;

    virtual std::string name() const { return "coord2"; }
  }; // class coord2

  template <class T>
  inline coord2<T>& coord2<T>::operator=(const coord2<T>& old_coord)
  {
    // No self-assignment comparison is done, because the compare/jump
    // should take longer than the assignment (for built-in types).
    coords.direct.x = old_coord.coords.direct.x;
    coords.direct.y = old_coord.coords.direct.y;

    return *this;
  }


  template <class T>
  inline coord2<T>& coord2<T>::operator+=(const coord2<T>& p2)
  {
    coords.direct.x += p2.coords.direct.x;
    coords.direct.y += p2.coords.direct.y;

    return *this;
  }

  template <class T>
  inline coord2<T>& coord2<T>::operator-=(const coord2<T>& p2)
  {
    coords.direct.x -= p2.coords.direct.x;
    coords.direct.y -= p2.coords.direct.y;

    return *this;
  }

  // Piecewise multiplication...
  template <class T>
  inline coord2<T>& coord2<T>::operator*=(const coord2<T>& p2)
  {
    coords.direct.x *= p2.coords.direct.x;
    coords.direct.y *= p2.coords.direct.y;

    return *this;
  }

  template <class T>
  inline coord2<T>& coord2<T>::operator*=(T factor)
  {
    coords.direct.x *= factor;
    coords.direct.y *= factor;

    return *this;
  }

  template <class T>
  inline coord2<T>& coord2<T>::operator/=(T factor)
  {
    coords.direct.x /= factor;
    coords.direct.y /= factor;

    return *this;
  }

  template <class T>
  template <class U>
  inline coord2<T>& coord2<T>::operator*=(U factor)
  {
    coords.direct.x = T(coords.direct.x * factor);
    coords.direct.y = T(coords.direct.y * factor);

    return *this;
  }

  template <class T>
  template <class U>
  inline coord2<T>& coord2<T>::operator/=(U factor)
  {
    coords.direct.x = T(coords.direct.x / factor);
    coords.direct.y = T(coords.direct.y / factor);

    return *this;
  }


  /* non-member math functions (also inlined for an attempt at some speed) */
  template <class T>
  inline coord2<T> operator+(const coord2<T>& p1, const coord2<T>& p2)
  {
    coord2<T> p(p1); p += p2; return(p);
  }
  template <class T>
  inline coord2<T> operator-(const coord2<T>& p1, const coord2<T>& p2)
  {
    coord2<T> p(p1); p -= p2; return(p);
  }
  template <class T>
  inline coord2<T> operator*(const coord2<T>& p1, T d)
  {
    coord2<T> p(p1); p *= d;  return(p);
  }
  template <class T>
  inline coord2<T> operator*(T d, const coord2<T>& p1)
  {
    coord2<T> p(p1); p *= d;  return(p);
  }
  template <class T>
  inline coord2<T> operator/(const coord2<T>& p1, T d)
  {
    coord2<T> p(p1); p /= d;  return(p);
  }

  template <class T, class U>
  inline coord2<T> operator*(const coord2<T>& p1, U d)
  {
    coord2<T> p(p1); p *= d;  return(p);
  }

  template <class T, class U>
  inline coord2<T> operator*(U d, const coord2<T>& p1)
  {
    coord2<T> p(p1); p *= d;  return(p);
  }

  template <class T>
  inline coord2<T> operator*(const coord2<T>& p1, const coord2<T>& p2)
  {
    return(coord2<T>(p1.x() * p2.x(),
        p1.y() * p2.y()));
  }

  template <class T, class U>
  inline coord2<T> operator/(const coord2<T>& p1, U d)
  {
    coord2<T> p(p1); p /= d;  return(p);
  }

  /* Unary minus */
  template <class T>
  inline coord2<T> operator-(const coord2<T>& p1)
  {
    return(T(-1)*p1);
  }


  /* exports from this header file */
  template <class T>
  inline T dotprod(const coord2<T>& c1, const coord2<T>& c2)
  {
    return( (c1.x()*c2.x()) + (c1.y()*c2.c.y()));
  }

  template <class T>
  inline T length(const coord2<T>& c)
  {
    return(c.length());
  }

  template <class T>
  inline coord2<T> unit(const coord2<T>& c)
  {
    return(c/c.length());
  }

  template <class T>
  inline coord2<T> invert(const coord2<T>& c)
  {
    return(coord2<T>(1/c.x(), 1/c.y()));
  }

  template <class T>
  inline T average(const coord2<T>& c)
  {
    return((c.x() + c.y()) / 2);
  }

  template <class T>
  inline T max(const coord2<T>& c)
  {
    return(std::max(c.x(), c.y()));
  }

  template <class T>
  inline coord2<T> abs_vector(const coord2<T>& v)
  {
    return coord2<T>(my_abs(v.x()), my_abs(v.y()));
  }

  template <class T>
  std::string coord2<T>::internalMembers(const Indentation& indent, PrefixType prefix) const
  {
    std::string tag = indent.level();
    if( prefix == E_PREFIX_CLASSNAME )
    {
      tag += coord2<T>::name() + "::";
    }

    return ( tag + string_format("x=%1\n", x()) +
      tag + string_format("y=%1\n", y()) );
  }

  template <class T>
  std::string coord2<T>::toString(const Indentation& indent, PrefixType prefix) const
  {
    std::string tag;
    if( prefix == E_PREFIX_CLASSNAME )
    {
      tag = coord2<T>::name();
    }
    return indent + tag + string_format("{%1,%2}", x(), y());
  }

} // namespace panorama

#endif /* !defined(PANORAMA__COORD2_HPP) */
