/*
*  Copyright (C) 1998 Angel Jimenez Jimenez and Carlos Jimenez Moreno
*  Copyright (C) 1999 Peter Barnett
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

#ifndef _MAT_NOISE__
#define _MAT_NOISE__

#include "llapi/perlin_noise.h"
#include "llapi/material.h"
#include "llapi/gradient.h"
#include "hlapi/plugin_manager.h"

class TMaterialNoise : public TMaterial
{

  protected:

    TColor         tBaseColor;
    TVector        tZoom;
    TScalar        tBumpFactor;
    bool           bGradientLoaded;
    TPerlinNoise   tNoise;
    TGradient      tGradient;

  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TMaterialNoise (void) :
      TMaterial(),
      tZoom (1, 1, 1),
      tBumpFactor (0),
      bGradientLoaded (false) {}
      
    TColor color (const TSurfaceData& rktDATA) const
    {
      TVector   tPoint = rktDATA.localPoint() * tZoom;
      TScalar   tValue = tNoise.noise (tPoint);
      
      if ( bGradientLoaded == true )
      {
        return tGradient.getColorAt (tValue);
      }
      else
      {
        return lerp (tColor, tBaseColor, tValue);
      }
    }
    
    TVector perturbNormal (const TSurfaceData& rktDATA) const;

    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    virtual void setBaseColor (const TColor& rktCOLOR)
    {
      tBaseColor = rktCOLOR;
    }

    string className (void) const { return "MaterialNoise"; }

};  /* class TMaterialNoise */


inline TVector TMaterialNoise::perturbNormal (const TSurfaceData& rktDATA) const
{

  TVector   tNewNormal = rktDATA.normal();

  if ( tBumpFactor )
  {
    TVector   tGradient;
    TScalar   tNoiseValue;
    TVector   tPoint = rktDATA.localPoint() * tZoom;

    tNoiseValue = tNoise.noise (tPoint);

    tPoint      = tPoint + rktDATA.normal() * tNoiseValue;
    tNoiseValue = tNoise.noise (tPoint, &tGradient);

    tNewNormal = rktDATA.normal() + tGradient * tBumpFactor;
    tNewNormal.normalize();
  }
  
  return tNewNormal;
  
}  /* perturbNormal() */

#endif  /* _MAT_NOISE__ */
