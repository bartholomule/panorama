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

#ifndef _LIGHT__
#define _LIGHT__

#include "llapi/color.h"
#include "llapi/entity.h"
#include "llapi/object.h"

struct TLightProperties
{

  unsigned   gShadow : 1;
  unsigned   gVolumetric : 1;
  unsigned   gRaytraced : 1;

};  /* struct TLightProperties */


class TLight : public TEntity
{

  protected:

    TColor             tColor;
    TScalar            tIntensity;
    TLightProperties   tProperties;

    virtual bool visible (const TVector& rktPOINT) const
    {
      return true;
    }

  public:

    TLight (void) :
      tColor (TColor::_white()),
      tIntensity (1)
    {
      tProperties.gShadow     = true;
      tProperties.gVolumetric = true;
      tProperties.gRaytraced  = true;
    }

    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;
    
    void setColor (const TColor& rktCOLOR) { tColor = rktCOLOR; }
    void setIntensity (TScalar tINTENSITY) { tIntensity = tINTENSITY; }

    virtual void initialize (void) {}
    
    virtual TColor color (const TVector& rktPOINT) const
    {
      if ( !visible (rktPOINT) )
      {
        return TColor::_black();
      }

      return tColor * tIntensity;
    }

    virtual TColor scatteredLight (const TSurfaceData& rktDATA) const
    {
      return TColor::_null();
    }
    
    bool shadow (void) const { return tProperties.gShadow; }
    bool volumetric (void) const { return tProperties.gVolumetric; }
    bool raytraced (void) const { return tProperties.gRaytraced; }

    EClass classType (void) const { return FX_LIGHT_CLASS; }
    
};  /* class TLight */

#endif  /* _LIGHT__ */
