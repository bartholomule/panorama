/*
*  Copyright (C) 1998, 1999 Angel Jimenez Jimenez, Carlos Jimenez Moreno and Peter Barnett
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

#ifndef _MAT_MARBLE__
#define _MAT_MARBLE__

#include "llapi/perlin_noise.h"
#include "llapi/material.h"
#include "llapi/gradient.h"
#include "hlapi/plugin_manager.h"

class TMaterialMarble : public TMaterial
{

  protected:

    TColor         tBaseColor;
    TVector        tZoom;
    TScalar        tBumpFactor;
    TScalar        tOffset;
    TScalar        tMultiplier;
    TScalar        tNumOctaves;
    bool           bGradientLoaded;
    TScalar        tLacunarity;
    
    TPerlinNoise   tNoise;
    TGradient      tGradient;
    TScalar evaluate (const TVector& rktPOINT, TVector* ptGRADIENT = NULL) const;

  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TMaterialMarble (void) :
      TMaterial(),
      tZoom (1, 1, 1),
      tBumpFactor (0),
      tOffset (1.0),
      tMultiplier (0.5),
      tNumOctaves (3.0),
      bGradientLoaded (false),
      tLacunarity (2.17) {}
      
    TColor color (const TSurfaceData& rktDATA) const;    
    TVector perturbNormal (const TSurfaceData& rktDATA) const;
    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    virtual void setBaseColor (const TColor& rktCOLOR)
    {
      tBaseColor = rktCOLOR;
    }

    string className (void) const { return "MaterialMarble"; }

};  /* class TMaterialMarble */


inline TScalar TMaterialMarble::evaluate (const TVector& rktPOINT, TVector* ptGRADIENT) const
{
  //TScalar   tValue = tNoise.turbulence (rktPOINT, 0.5, 4.0);
  //TScalar   tValue = tNoise.turbulence (rktPOINT, 0.75, 4.0);

  TScalar   tValue;
  TScalar   tFreq;
  int       i;
  int       iNumOctaves = (int) tNumOctaves;
  
  tValue = 0;
  tFreq  = 1;
  
  for (i = 0; i < iNumOctaves ; i++)
  {
    tValue += tNoise.snoise (rktPOINT * tFreq) / tFreq;
    tFreq *= tLacunarity;
  }

  tValue =  (tOffset + tValue) * tMultiplier;
    
  if (ptGRADIENT)
  {
    TVector   tDx, tDy, tDz;
    TScalar   tVx, tVy, tVz;

    tDx.set (1.0E-6, 0.0, 0.0);
    tDy.set (0.0, 1.0E-6, 0.0);
    tDz.set (0.0, 0.0, 1.0E-6);
    
    tVx = tValue - evaluate (rktPOINT + tDx);
    tVy = tValue - evaluate (rktPOINT + tDy);
    tVz = tValue - evaluate (rktPOINT + tDz);
    
    ptGRADIENT->set (tVx, tVy, tVz);
    ptGRADIENT->normalize();
  }

  return ( tValue < 0.0 ) ? 0.0 : ( tValue > 1.0 ) ? 1.0 : tValue;
}


inline TColor TMaterialMarble::color (const TSurfaceData& rktDATA) const  
{
  TVector tPoint = rktDATA.localPoint() * tZoom;
  TScalar tValue = evaluate (tPoint);
  
  if ( bGradientLoaded == true )
  {
    return tGradient.getColorAt (tValue);
  }
  else
  {
    return lerp (tColor, tBaseColor, tValue);
  }
}

inline TVector TMaterialMarble::perturbNormal (const TSurfaceData& rktDATA) const
{
  TVector   tNewNormal = rktDATA.normal();

  if ( tBumpFactor )
  {
    TVector   tGradient;
    TVector   tPoint      = rktDATA.localPoint() * tZoom;

    evaluate (tPoint, &tGradient);

    tNewNormal = rktDATA.normal() + tGradient * tBumpFactor;
    tNewNormal.normalize();
  }
  
  return tNewNormal;
  
}  /* perturbNormal() */

#endif  /* _MAT_MARBLE__ */
