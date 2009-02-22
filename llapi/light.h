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

#ifndef PANORAMA_LIGHT_H_INCLUDED
#define PANORAMA_LIGHT_H_INCLUDED

#include "llapi/color.h"
#include "llapi/object.h"

namespace panorama
{
  struct TLightProperties
  {

    unsigned   gShadow : 1;
    unsigned   gVolumetric : 1;
    unsigned   gRaytraced : 1;

  };  /* struct TLightProperties */


  class TLight : public TObject
  {

  protected:

    TColor tColor;
    TScalar tIntensity;
    TLightProperties tProperties;

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

    AttributeErrorCode setAttribute (const std::string& rktNAME, Attribute nVALUE);
    AttributeErrorCode getAttribute (const std::string& rktNAME, Attribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    void setColor (const TColor& rktCOLOR) { tColor = rktCOLOR; }
    void setIntensity (TScalar tINTENSITY) { tIntensity = tINTENSITY; }

    virtual bool initialize (void) { return TObject::initialize(); }

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

    virtual bool findAllIntersections(const class TRay &, class TSpanList &) const;

    // FIXME!
    virtual TLight* clone_new() const = 0;//  { return new TLight(*this); }

  };  /* class TLight */
} // end namespace panorama

#endif  /* PANORAMA_LIGHT_H_INCLUDED */
