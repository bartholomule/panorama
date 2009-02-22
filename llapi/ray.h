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

#ifndef PANORAMA_RAY_H_INCLUDED
#define PANORAMA_RAY_H_INCLUDED

#include "llapi/llapi_defs.h"
#include "llapi/interval.h"
#include "llapi/string_dumpable.hpp"
#include "generic/rc_pointer.hpp"

namespace panorama
{

  class TRay : public virtual StringDumpable
  {

  protected:

    TPoint tLocation;
    TVector tDirection;
    TScalar tIor;
    //    TScalar   tLimit;
    TInterval tRange;

  public:

    TRay (void) :
      tIor (FX_MEDIUM_IOR),
      tRange (FX_EPSILON, SCALAR_MAX) {}

    TRay (const TPoint& rktLOC, const TVector& rktDIR) :
      tLocation (rktLOC),
      tDirection (rktDIR),
      tIor (FX_MEDIUM_IOR),
      tRange (FX_EPSILON, SCALAR_MAX) {}

    TRay (const TRay& rktRAY) :
      tLocation (rktRAY.location()),
      tDirection (rktRAY.direction()),
      tIor (rktRAY.ior()),
      tRange (rktRAY.range()) {}

    TRay& operator = (const TRay& rktRAY)
    {
      tLocation  = rktRAY.location();
      tDirection = rktRAY.direction();
      tIor       = rktRAY.ior();
      tRange     = rktRAY.range();

      return *this;
    }

    TPoint location (void) const { return tLocation; }
    TVector direction (void) const { return tDirection; }
    TPoint destination (void) const { return (tLocation + tDirection); }
    const TInterval& range (void) const { return tRange; }
    TScalar maxLimit (void) const { return tRange.max(); }
    TScalar ior (void) const { return tIor; }

    void setLocation (const TPoint& rktLOC) { tLocation = rktLOC; }
    void setDirection (const TVector& rktDIR) { tDirection = rktDIR; }
    void setDestination (const TPoint& rktDEST) { tDirection = (rktDEST - tLocation); }
    void setRange (TInterval tRANGE) { tRange = tRANGE; }
    void setRange (TScalar tMin, TScalar tMax) { tRange = TInterval(tMin, tMax); }
    // apply a factor (=multiply) the parts of the range by the factor.
    void applyRangeFactor(TScalar fact);

    void normalize (void)
    {
      tDirection = unit(tDirection);
    }

    void reflect (const TVector& rktNORMAL, const TVector& rktORIGINAL)
    {
      TVector  tOldDirection = tDirection;

      tDirection -= rktNORMAL * (2.0 * dotprod (rktNORMAL, tDirection));

      if ( dotprod (rktORIGINAL, tDirection) <= 0.1 )
      {
        tDirection = tOldDirection - rktORIGINAL * (2.0 * dotprod (tOldDirection, rktORIGINAL));
      }
    }

    bool refract (const TVector& rktNORMAL, TScalar tIOR, bool& gTIR);

    TScalar applyTransform (const TMatrix* pktMATRIX);
    TScalar applyTransform (const rc_pointer<TMatrix>& pktMATRIX);
    TScalar applyTransform (const TMatrix& rktMATRIX);

    virtual std::string internalMembers(const Indentation& indent, PrefixType prefix) const;
    virtual std::string name() const;

  };  /* class TRay */


  // FIXME!
  // I don't understand what good this function does...
  inline TRay operator - (const TRay& rktRAY)
  {

    TRay   tRay = rktRAY;

    TPoint origin = rktRAY.location();

    tRay.setLocation (TPoint(-origin.x(), -origin.y(), -origin.z()));
    tRay.setDirection (-rktRAY.direction());

    return tRay;

  }  /* operator - () */

} // end namespace panorama

#endif  /* PANORAMA_RAY_H_INCLUDED */
