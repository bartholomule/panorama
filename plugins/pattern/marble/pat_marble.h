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

#ifndef _PATTERN_MARBLE__
#define _PATTERN_MARBLE__

#include "llapi/perlin_noise.h"
#include "llapi/pattern.h"
#include "llapi/gradient.h"
#include "hlapi/plugin_manager.h"

class TPerturbationMarble;


class TPatternMarble : public TPattern
{

  friend TPerturbationMarble;

  protected:

    TColor         tColor;
    TColor         tBaseColor;
    TVector        tZoom;
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

    TPatternMarble (void) :
      TPattern(),
      tZoom (1, 1, 1),
      tOffset (1.0),
      tMultiplier (0.5),
      tNumOctaves (3.0),
      bGradientLoaded (false),
      tLacunarity (2.17) {}
      
    TColor pattern (const TSurfaceData& rktDATA) const;    

    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;
 
    void setColor (const TColor& rktCOLOR)
    {
      tColor = rktCOLOR;
    }
    void setBaseColor (const TColor& rktCOLOR)
    {
      tBaseColor = rktCOLOR;
    }

    string className (void) const { return "PatternMarble"; }

};  /* class TPatternMarble */


inline TScalar TPatternMarble::evaluate (const TVector& rktPOINT, TVector* ptGRADIENT) const
{

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


inline TColor TPatternMarble::pattern (const TSurfaceData& rktDATA) const  
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

#endif  /* _PATTERN_MARBLE__ */
