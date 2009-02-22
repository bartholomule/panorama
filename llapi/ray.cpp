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

#include "llapi/warning_eliminator.h"
#include "llapi/ray.h"

namespace panorama
{
  bool TRay::refract (const TVector& rktNORMAL, TScalar tIOR, bool& gTIR)
  {

    bool      gEnter;
    TScalar   tCos;
    TScalar   tRad;
    TScalar   tIndex;
    TVector   tNormal;

    tCos = dotProduct (tDirection, rktNORMAL);
    if ( tCos < 0 )
    {
      tCos    = -tCos;
      tNormal = rktNORMAL;
      tIndex  = tIor / tIOR;
      gEnter  = true;
      //    tIor    = tIOR;
    }
    else
    {
      tNormal = -rktNORMAL;
      tIndex  = tIor / tIOR;
      gEnter  = false;
    }

    tRad = 1 - (tIndex * tIndex) * (1 - (tCos * tCos));

    if ( tRad < 0 )
    {
      //    assert ( !gEnter );
      //    reflect (tNormal);
      gTIR = true;

      return gEnter;
    }
    else
    {
      tDirection *= tIndex;
      tDirection += tNormal * ((tIndex * tCos) - TScalar (sqrt (tRad)));
    }

    gTIR = false;
    return gEnter;

  }  /* refract() */


  TScalar TRay::applyTransform (const TMatrix* pktMATRIX)
  {

    TVector   tDest;
    TScalar   tNorm = 1;

    if ( pktMATRIX )
    {
      tDest      = tLocation + tDirection;
      tLocation  = (*pktMATRIX) * tLocation;
      tDirection = ((*pktMATRIX) * tDest) - tLocation;
      tNorm      = tDirection.norm();
      tDirection /= tNorm;
    }

    return TScalar (1) / tNorm;

  }  /* applyTransform() */

  TScalar TRay::applyTransform (const magic_pointer<TMatrix>& pktMATRIX)
  {

    TVector   tDest;
    TScalar   tNorm = 1;

    if ( !!pktMATRIX )
    {
      tDest      = tLocation + tDirection;
      tLocation  = (*pktMATRIX) * tLocation;
      tDirection = ((*pktMATRIX) * tDest) - tLocation;
      tNorm      = tDirection.norm();
      tDirection /= tNorm;
    }

    return TScalar (1) / tNorm;

  }  /* applyTransform() */

  TScalar TRay::applyTransform (const TMatrix& rktMATRIX)
  {

    TVector   tDest;
    TScalar   tNorm = 1;

    tDest      = tLocation + tDirection;
    tLocation  = rktMATRIX * tLocation;
    tDirection = (rktMATRIX * tDest) - tLocation;
    tNorm      = tDirection.norm();
    tDirection /= tNorm;

    return TScalar (1) / tNorm;

  }  /* applyTransform() */

  void TRay::applyRangeFactor(TScalar fact)
  {
    TScalar min = tRange.min();
    TScalar max = tRange.max();

    // If it is an epsilon, preserve it.
    if( min == FX_EPSILON )
    {
      tRange.set(FX_EPSILON, max * fact );
    }
    else
    {
      tRange.set(min * fact, max * fact );
    }
  }

  std::string TRay::internalMembers(const Indentation& indent, PrefixType prefix) const
  {
    std::string tag;
    if( prefix == E_PREFIX_CLASSNAME )
    {
      tag = TRay::name() + "::";
    }

    Indentation nextIndent = indent.nextLevel();

    return string_format("%1location=%3\n%2direction=%4\n%2IOR=%5\n%2range=%6\n",
      indent.initial() + tag,
      indent + tag,
      tLocation.toString(nextIndent, prefix),
      tDirection.toString(nextIndent, prefix),
      tIor,
      tRange.toString(nextIndent, prefix));
  }

  std::string TRay::name() const
  {
    return "Ray";
  }

} // end namespace panorama
