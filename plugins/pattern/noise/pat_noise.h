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

#ifndef _PATTERN_NOISE__
#define _PATTERN_NOISE__

#include "llapi/perlin_noise.h"
#include "llapi/pattern.h"
#include "llapi/gradient.h"
#include "hlapi/plugin_manager.h"

class TPerturbationNoise;


class TPatternNoise : public TPattern
{

  friend TPerturbationNoise;

  protected:

    TColor         tColor;
    TColor         tBaseColor;
    TVector        tZoom;
    bool           bGradientLoaded;
    TPerlinNoise   tNoise;
    TGradient      tGradient;

  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TPatternNoise (void) :
      TPattern(),
      tZoom (1, 1, 1),
      bGradientLoaded (false) {}
      
    TColor pattern (const TSurfaceData& rktDATA) const
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

    string className (void) const { return "PatternNoise"; }

};  /* class TPatternNoise */

#endif  /* _PATTERN_NOISE__ */
