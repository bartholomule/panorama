/*
*  Copyright (C) 2000 Fausto Espinal
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

#ifndef _PARALLEL__
#define _PARALLEL__

#include "llapi/camera.h"
#include "hlapi/plugin_manager.h"

class TParallelCamera : public TCamera
{

  protected:

    TScalar   tWidth, tHeight;
    TScalar   tPixelSizeX, tPixelSizeY;
    TVector   I, J;
    TVector   tDirection;

  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TParallelCamera (void) :
      TCamera(),
      tWidth(200), tHeight(200) {}

    bool initialize (void);
    
    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    void setWidth (TScalar tWIDTH)
    {
      tWidth=tWIDTH;
    }

    TScalar getWidth (void) const
    {
      return tWidth;
    }

    void setHeight (TScalar tHEIGHT)
    {
      tHeight=tHEIGHT;
    }

    TScalar getHeight (void) const
    {
      return tHeight;
    }

    void getRay (TScalar X, TScalar Y, TRay& rtRAY) const
    {
      rtRAY.setLocation (location() + (I * (X - tHalfResX)) + (J * (tHalfResY - Y)));
      rtRAY.setDirection (tDirection);
      rtRAY.normalize();
    }
    bool getPlaneProjection (const TVector& rktPOINT, TVector2& rtPROJ) const;

    TScalar getZ (const TVector& rktPOINT) const
    {
      return -dotProduct (tDirection, rktPOINT);
    }
    
    string className (void) const { return "ParallelCamera"; }
    virtual TParallelCamera* clone_new() const { return new TParallelCamera(*this); }
  
    void printDebug (const string& indent) const;
    
};  /* class TParallelCamera */

#endif  /* _PARALLEL__ */
