/*
*  Copyright (C) 1998 Angel Jimenez Jimenez and Carlos Jimenez Moreno
*
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful, but
*  WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program; if not, write to the Free Software
*  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#ifndef _INTERVAL__
#define _INTERVAL__

#include <cassert>
#include <iostream>
#include "llapi/machine.h"
#include "llapi/math_tools.h"
#include "llapi/string_dumpable.hpp"

namespace panorama
{
  template <class TItem>
  class TBaseInterval : public StringDumpable
  {

  protected:

    TItem tMin;
    TItem tMax;
    bool gEmpty;

  public:

    TBaseInterval (void) :
      gEmpty (true) {}

    TBaseInterval (TItem tVALUE1, TItem tVALUE2);

    TBaseInterval (const TBaseInterval& rktINT) :
      tMin (rktINT.tMin),
      tMax (rktINT.tMax),
      gEmpty (rktINT.gEmpty) {}

    TBaseInterval& operator = (const TBaseInterval& rktINT)
    {
      tMin   = rktINT.tMin;
      tMax   = rktINT.tMax;
      gEmpty = rktINT.gEmpty;

      return *this;
    }

    void set (TItem tVALUE1, TItem tVALUE2);

    // clamp the given value to fit within this interval.
    TItem clamp (TItem tVALUE) const;
    inline TItem adjustValue (TItem tVALUE) const { return clamp(tVALUE); }

    TItem min (void) const { return tMin; }
    TItem max (void) const { return tMax; }
    TItem mid (void) const { return (tMin + tMax) / 2; }
    TItem size (void) const { return (tMax - tMin); }
    bool empty (void) const { return gEmpty; }

    bool inside (TItem tVALUE) const;
    bool outside (TItem tVALUE) const;
    bool overlaps(TBaseInterval& tINTERVAL) const;
    bool subset(TBaseInterval& tINTERVAL) const;


    virtual std::string internalMembers(const Indentation& indent, PrefixType prefix) const;
    virtual std::string name() const;
    virtual std::string toString(const Indentation& indent, PrefixType prefix) const;

  };  /* class TBaseInterval */


  template <class TItem>
  inline TBaseInterval<TItem>::TBaseInterval (TItem tVALUE1, TItem tVALUE2)
  {

    set (tVALUE1, tVALUE2);

  }  /* TBaseInterval() */


  template <class TItem>
  inline void TBaseInterval<TItem>::set (TItem tVALUE1, TItem tVALUE2)
  {

    if ( tVALUE1 < tVALUE2 )
    {
      tMin = tVALUE1;
      tMax = tVALUE2;
    }
    else
    {
      tMin = tVALUE2;
      tMax = tVALUE1;
    }

    // [CHECKME!]
    // Question -- If the interval has the same top and bottom values, is it in
    // fact an interval?  Should the interval be empty in that case?
    // If I do set the interval to be empty, there are some problems with
    // indirect use of intervals from within certain objects not being visible
    // (cones, for example).
    //  gEmpty = tMin != tMax;
    gEmpty = false;

  }  /* set() */


  template <class TItem>
  inline bool TBaseInterval<TItem>::inside (TItem tVALUE) const
  {

    if ( !gEmpty )
    {
      return ( ( tVALUE >= tMin ) && ( tVALUE <= tMax ) );
    }
    return false;

  }  /* inside() */

  template <class TItem>
  inline bool TBaseInterval<TItem>::outside (TItem tVALUE) const
  {

    if ( !gEmpty )
    {
      return ( ( tVALUE < tMin ) || ( tVALUE > tMax ) );
    }
    return false;

  }  /* outside() */

  template <class TItem>
  inline bool TBaseInterval<TItem>::overlaps(TBaseInterval& tINTERVAL) const
  {
    if( empty() || tINTERVAL.empty() )
    {
      return false;
    }
    return ( inside(tINTERVAL.min()) || inside(tINTERVAL.max()) );

  } /* overlaps() */

  template <class TItem>
  inline bool TBaseInterval<TItem>::subset(TBaseInterval& tINTERVAL) const
  {
    if( empty() || tINTERVAL.empty() )
    {
      return false;
    }
    return ( inside(tINTERVAL.min()) && inside(tINTERVAL.max()) );

  } /* subset() */

  template <class TItem>
  inline TItem TBaseInterval<TItem>::clamp (TItem tVALUE) const
  {
    // Return value not specified if interval is empty

    if ( tVALUE < tMin )
    {
      tVALUE = tMin;
    }
    if ( tVALUE > tMax )
    {
      tVALUE = tMax;
    }

    return tVALUE;

  }  /* clamp() */


  /*
  template <class TItem>
  inline void TBaseInterval<TItem>::printDebug (const std::string& indent) const
  {

    if ( gEmpty )
    {
      GOM.debug() << indent << "Interval [ empty ]" << std::endl;
    }
    else
    {
      GOM.debug() << indent << "Interval [" << tMin << ", " << tMax << "]" << std::endl;
    }

  }
  */


  template <class TItem>
  inline TBaseInterval<TItem> operator + (TBaseInterval<TItem> tINT, TItem tVALUE)
  {

    if ( !tINT.empty() )
    {
      tINT.set (tINT.min() + tVALUE, tINT.max() + tVALUE);
    }

    return tINT;

  }  /* operator + () */


  template <class TItem>
  inline TBaseInterval<TItem> operator - (TBaseInterval<TItem> tINT, TItem tVALUE)
  {

    if ( !tINT.empty() )
    {
      tINT.set (tINT.min() - tVALUE, tINT.max() - tVALUE);
    }

    return tINT;

  }  /* operator - () */


  template <class TItem>
  inline bool operator < (TBaseInterval<TItem> tINT, TItem tVALUE)
  {

    return ( tINT.max() < tVALUE );

  }  /* operator < () */


  template <class TItem>
  inline bool operator > (TBaseInterval<TItem> tINT, TItem tVALUE)
  {

    return ( tINT.min() > tVALUE );

  }  /* operator > () */


  template <class TItem>
  inline bool operator < (TItem tVALUE, TBaseInterval<TItem> tINT)
  {

    return ( tVALUE < tINT.min() );

  }  /* operator < () */


  template <class TItem>
  inline bool operator > (TItem tVALUE, TBaseInterval<TItem> tINT)
  {

    return ( tVALUE > tINT.max() );

  }  /* operator > () */


  template <class TItem>
  inline bool operator < (TBaseInterval<TItem> tINT1, TBaseInterval<TItem> tINT2)
  {

    return ( tINT1.max() < tINT2.min() );

  }  /* operator < () */

  template <class TItem>
  inline bool operator > (TBaseInterval<TItem> tINT1, TBaseInterval<TItem> tINT2)
  {

    return ( tINT1.min() > tINT2.max() );

  }  /* operator < () */

  template <class TItem>
  inline bool operator <= (TBaseInterval<TItem> tINT, TItem tVALUE)
  {

    return ( tINT.max() <= tVALUE );

  }  /* operator <= () */


  template <class TItem>
  inline bool operator >= (TBaseInterval<TItem> tINT, TItem tVALUE)
  {

    return ( tINT.min() >= tVALUE );

  }  /* operator >= () */


  template <class TItem>
  inline bool operator <= (TItem tVALUE, TBaseInterval<TItem> tINT)
  {

    return ( tVALUE <= tINT.min() );

  }  /* operator <= () */


  template <class TItem>
  inline bool operator >= (TItem tVALUE, TBaseInterval<TItem> tINT)
  {

    return ( tVALUE >= tINT.max() );

  }  /* operator >= () */


  template <class TItem>
  inline bool operator <= (TBaseInterval<TItem> tINT1, TBaseInterval<TItem> tINT2)
  {

    return ( tINT1.max() <= tINT2.min() );

  }  /* operator <= () */

  template <class TItem>
  inline bool operator >= (TBaseInterval<TItem> tINT1, TBaseInterval<TItem> tINT2)
  {

    return ( tINT1.min() >= tINT2.max() );

  }  /* operator >= () */

  template <class TItem>
  inline bool Disjoint (TBaseInterval<TItem> tINT1, TBaseInterval<TItem> tINT2)
  {

    if ( tINT1.empty() || tINT2.empty() )
    {
      return true;
    }

    return ( ( tINT1 < tINT2 ) || ( tINT2 < tINT1 ) );

  }  /* Disjoint() */


  template <class TItem>
  inline TBaseInterval<TItem> Union (TBaseInterval<TItem> tINT1, TBaseInterval<TItem> tINT2)
  {

    if ( tINT1.empty() )
    {
      return tINT2;
    }
    if ( tINT2.empty() )
    {
      return tINT1;
    }

    return TBaseInterval<TItem> (std::min (tINT1.min(), tINT2.min()), std::max (tINT1.max(), tINT2.max()));

  }  /* Union() */


  template <class TItem>
  inline TBaseInterval<TItem> Intersection (TBaseInterval<TItem> tINT1, TBaseInterval<TItem> tINT2)
  {

    TBaseInterval<TItem>   tInt;

    if ( !Disjoint (tINT1, tINT2) )
    {
      tInt.set (std::max (tINT1.min(), tINT2.min()), std::min (tINT1.max(), tINT2.max()));
    }

    return tInt;

  }  /* Intersection() */

  template <class T>
  std::string TBaseInterval<T>::name() const
  {
    return "Interval";
  }

  template <class T>
  std::string TBaseInterval<T>::toString(const Indentation& indent, StringDumpable::PrefixType prefix) const
  {
    std::string outprefix = indent.level();
    if( prefix == E_PREFIX_CLASSNAME )
    {
      outprefix = indent + "Interval";
    }
    if( empty() )
    {
      return outprefix + "[empty]";
    }
    return outprefix + string_format("[%1,%2]", tMin, tMax);
  }

  template <class T>
  std::string TBaseInterval<T>::internalMembers(const Indentation& indent, PrefixType prefix) const
  {
    std::string tag = indent.level();
    if( prefix == E_PREFIX_CLASSNAME )
    {
      tag += TBaseInterval::name() + "::";
    }

    return ( tag + string_format("min=%1\n", tMin) +
      tag + string_format("max=%1\n", tMax));
  }

} // end namespace panorama

#endif  /* _INTERVAL__ */
