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

#ifndef _PINHOLE__
#define _PINHOLE__

#include "llapi/camera.h"
#include "hlapi/plugin_manager.h"

class TPinholeCamera : public TCamera
{

  protected:

    TScalar   tHalfAngle;
    TScalar   tPixelSize;
    TVector   I, J;
    TVector   tDirection;

  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TPinholeCamera (void) :
      TCamera(),
      tHalfAngle (degreeToRadian (45) / 2) {}

    void initialize (void);
    
    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    void setAngle (TScalar tANGLE)
    {
      tHalfAngle = degreeToRadian (tANGLE) / 2;
    }

    TScalar getAngle (void) const
    {
      return tHalfAngle * 2;
    }

    void getRay (TScalar X, TScalar Y, TRay& rtRAY) const
    {
      rtRAY.setLocation (tLocation);
      rtRAY.setDirection (tDirection + (I * (X - tHalfResX)) + (J * (tHalfResY - Y)));
      rtRAY.normalize();
    }
    bool getPlaneProjection (const TVector& rktPOINT, TVector2& rtPROJ) const;

    TScalar getZ (const TVector& rktPOINT) const
    {
      return -dotProduct (tDirection, rktPOINT);
    }
    
    string className (void) const { return "PinholeCamera"; }

    void printDebug (void) const;
    
};  /* class TPinholeCamera */

#endif  /* _PINHOLE__ */
