/*
*  Copyright (C) 1998, 1999 Angel Jimenez Jimenez and Carlos Jimenez Moreno
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

#ifndef _SURFACE_DATA__
#define _SURFACE_DATA__

#include "llapi/ray.h"

class TObject;

class TSurfaceData
{

  protected:
    
    const TObject*   pktObject;   // Object intersected
    size_t           zObjectCode; // Code of object intersected
    TRay             tRay;        // Ray that intersected with object
    TScalar          tDistance;   // Distance from ray location to intersection
    TVector          tPoint;      // Point of intersection
    void*            pvData;      // User assignable data

    mutable TVector   tNormal;     // Surface normal in that point
    mutable bool      gNormalAssigned;
    mutable bool      gFlipNormal; // Normal must be flipped (for CSG difference)

  public:

    size_t   zReflection;
    size_t   zTransmission;
    TColor   tLightRadiance;

    TSurfaceData (void) :
      pktObject (NULL),
      zObjectCode (0),
      tDistance (SCALAR_MAX),
      pvData (NULL),
      gNormalAssigned (false),
      gFlipNormal (false),
      zReflection (0),
      zTransmission (0),
      tLightRadiance (TColor::_black()) {}

    TSurfaceData (const TSurfaceData& rktDATA) :
      pktObject (rktDATA.pktObject),
      zObjectCode (rktDATA.zObjectCode),
      tRay (rktDATA.tRay),
      tDistance (rktDATA.tDistance),
      tPoint (rktDATA.tPoint),
      pvData (rktDATA.pvData),
      tNormal (rktDATA.tNormal),
      gNormalAssigned (rktDATA.gNormalAssigned),
      gFlipNormal (false),
      zReflection (rktDATA.zReflection),
      zTransmission (rktDATA.zTransmission),
      tLightRadiance (rktDATA.tLightRadiance) {}

    TSurfaceData& operator = (const TSurfaceData& rktDATA)
    {
      pktObject       = rktDATA.pktObject;
      zObjectCode     = rktDATA.zObjectCode;
      tRay            = rktDATA.tRay;
      tDistance       = rktDATA.tDistance;
      tPoint          = rktDATA.tPoint;
      pvData          = rktDATA.pvData;
      tNormal         = rktDATA.tNormal;
      gNormalAssigned = rktDATA.gNormalAssigned;
      gFlipNormal     = rktDATA.gFlipNormal;
      zReflection     = rktDATA.zReflection;
      zTransmission   = rktDATA.zTransmission;
      tLightRadiance  = rktDATA.tLightRadiance;

      return *this;
    }

    void setup (const TObject* pktOBJ, const TRay& rktRAY);

    bool setPoint (TScalar tDISTANCE)
    {
      gNormalAssigned = false;
      tDistance       = tDISTANCE;
  
      if ( pktObject )
      {
        tPoint = tRay.location() + (tRay.direction() * tDISTANCE);

        return true;
      }

      return false;
    }
    
    bool setPoint (TScalar tDISTANCE, const TVector& rktNORMAL);

    void setPoint (const TVector& rktPOINT)
    {
      tPoint          = rktPOINT;
      gNormalAssigned = false;
    }

    void setNormal (const TVector& rktNORMAL)
    {
      tNormal         = rktNORMAL;
      gNormalAssigned = true;
    }

    bool checkObject (const TObject* pktOBJECT) const
    {
      return ( pktObject == pktOBJECT );
    }

    void flipNormal (void)
    {
      if ( gNormalAssigned )
      {
        tNormal     = -tNormal;
        gFlipNormal = false;
      }
      else
      {
        gFlipNormal = true;
      }
    }
    
    TVector localPoint (void) const;
    
    TVector normal (void) const;
    
    TVector point (void) const { return tPoint; }
    TScalar distance (void) const { return tDistance; }
    TRay ray (void) const { return tRay; }
    const TObject* object (void) const { return pktObject; }
    size_t objectCode (void) const { return zObjectCode; }
    void* data (void) const { return pvData; }
    bool normalAssigned (void) const { return gNormalAssigned; }

    void printDebug (void) const;
  
};  /* struct TSurfaceData */

#endif  /* _SURFACE_DATA__ */
