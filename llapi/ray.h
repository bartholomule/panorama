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

#ifndef _RAY__
#define _RAY__

#include "llapi/llapi_defs.h"

class TRay
{

  protected:

    TVector   tLocation;
    TVector   tDirection;
    TScalar   tIor;
    TScalar   tLimit;
    
  public:
 
    TRay (void) :
      tIor (FX_MEDIUM_IOR),
      tLimit (SCALAR_MAX) {}

    TRay (const TVector& rktLOC, const TVector& rktDIR) :
      tLocation (rktLOC),
      tDirection (rktDIR),
      tIor (FX_MEDIUM_IOR),
      tLimit (SCALAR_MAX) {}

    TRay (const TRay& rktRAY) :
      tLocation (rktRAY.location()),
      tDirection (rktRAY.direction()),
      tIor (rktRAY.ior()),
      tLimit (rktRAY.limit()) {}

    TRay& operator = (const TRay& rktRAY)
    {
      tLocation  = rktRAY.location();
      tDirection = rktRAY.direction();
      tIor       = rktRAY.ior();
      tLimit     = rktRAY.limit();

      return *this;
    }
    
    TVector location (void) const { return tLocation; }
    TVector direction (void) const { return tDirection; }
    TVector destination (void) const { return (tLocation + tDirection); }
    TScalar limit (void) const { return tLimit; }
    TScalar ior (void) const { return tIor; }

    void setLocation (const TVector& rktLOC) { tLocation = rktLOC; }
    void setDirection (const TVector& rktDIR) { tDirection = rktDIR; }
    void setDestination (const TVector& rktDEST) { tDirection = (rktDEST - tLocation); }
    void setLimit (TScalar tLIMIT) { tLimit = tLIMIT; }

    void normalize (void)
    {
      tDirection.normalize();
    }
    
    void reflect (const TVector& rktNORMAL, const TVector& rktORIGINAL)
    {
      TVector  tOldDirection = tDirection;

      tDirection -= rktNORMAL * (2.0 * dotProduct (rktNORMAL, tDirection));

      if ( dotProduct (rktORIGINAL, tDirection) <= 0.1 )
      {
	tDirection = tOldDirection - rktORIGINAL * (2.0 * dotProduct (tOldDirection, rktORIGINAL));
      }
    }
    
    bool refract (const TVector& rktNORMAL, TScalar tIOR, bool& gTIR);

    TScalar applyTransform (const TMatrix* pktMATRIX);

    void printDebug (const string& indent) const;

};  /* class TRay */


inline TRay operator - (const TRay& rktRAY)
{

  TRay   tRay = rktRAY;

  tRay.setLocation (-rktRAY.location());
  tRay.setDirection (-rktRAY.direction());
  
  return tRay;

}  /* operator - () */

#endif  /* _RAY__ */
