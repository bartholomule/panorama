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

#ifndef _POINT_LIGHT__
#define _POINT_LIGHT__

#include "llapi/light.h"
#include "hlapi/plugin_manager.h"

class TPointLight : public TLight
{

  protected:

    TScalar   tDistanceThreshold;
    TScalar   tCosThreshold;
    TVector   tFalloff;
    TVector   tConeAxis;

    virtual bool visible (const TVector& rktPOINT) const;
    virtual TScalar attenuation (const TVector& rktPOINT) const
    {
      TScalar   tDist = Distance (rktPOINT, tLocation);

      return min (1 / (tFalloff.z() + tDist * (tFalloff.y() + (tFalloff.x() * tDist))), TScalar (1));
    }

  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TPointLight (void) :
      TLight(),
      tDistanceThreshold (0),
      tCosThreshold (0) {}
    
    void initialize (void);

    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;
    
    void setFalloff (const TVector& rktFALLOFF)
    {
      tFalloff = rktFALLOFF;
    }
    void setAxis (const TVector& rktAXIS)
    {
      tConeAxis = rktAXIS;
    }
    void setAngleThreshold (TScalar tANGLE)
    {
      tCosThreshold = cos (degreeToRadian (tANGLE));
    }
    void setDistanceThreshold (TScalar tDIST)
    {
      tDistanceThreshold = tDIST;
    }
    
    TColor color (const TVector& rktPOINT) const
    {
      if ( !visible (rktPOINT) )
      {
        return TColor::_black();
      }

      return tColor * tIntensity * attenuation (rktPOINT);
    }
    
    string className (void) const { return "PointLight"; }
 
    void printDebug (void) const;

};  /* class TPointLight */

#endif  /* _POINT_LIGHT__ */
