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

#ifndef _CAMERA__
#define _CAMERA__

#include "llapi/entity.h"
#include "llapi/ray.h"

class TCamera : public TEntity
{

  protected:
    
    TScalar   tHalfResX, tHalfResY;
    TVector   tUp;
    TVector   tLookAt;

  public:

    TCamera (void) :
      TEntity(),
      tUp (0, 1, 0) {}
      
    virtual void initialize (void) {}
    
    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    virtual void setImageResolution (size_t zWIDTH, size_t zHEIGHT)
    {
      tHalfResX = TScalar (zWIDTH) * 0.5;
      tHalfResY = TScalar (zHEIGHT) * 0.5;
    }
    
    virtual void getRay (TScalar tX, TScalar tY, TRay& rtRAY) const = 0;
    virtual bool getPlaneProjection (const TVector& rktPOINT, TVector2& rtPROJ) const = 0;

    virtual void setLookAt (const TVector& rktVECTOR)
    {
      tLookAt = rktVECTOR;
    }
    
    virtual void setUp (const TVector& rktVECTOR)
    {
      tUp = rktVECTOR;
    }
    
    virtual TVector getLookAt (void) const
    {
      return tLookAt;
    }
    
    virtual TVector getUp (void) const
    {
      return tUp;
    }

    EClass classType (void) const { return FX_CAMERA_CLASS; }
    
};  /* class TCamera */

#endif  /* _CAMERA__ */
