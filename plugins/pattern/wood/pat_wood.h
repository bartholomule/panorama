/*
*  Copyright (C) 1999 Angel Jimenez Jimenez, Carlos Jimenez Moreno and Peter Barnett
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

#ifndef _PATTERN_WOOD__
#define _PATTERN_WOOD__

#include "llapi/pattern.h"
#include "llapi/wood.h"
#include "llapi/gradient.h"
#include "llapi/mat_utils.h"
#include "hlapi/plugin_manager.h"


class TPatternWood : public TPattern
{

  protected:

    TWood           tWood;
    TGradient       tGradient;
    
    TColor          tColor;
    bool            bGradientLoaded;
    TColor          tBaseColor;
    TVector         tZoom;
    TScalar         tRingScale;
    TScalar         tGrainFactor;
    TColor          evaluate (const TVector& rktPOINT) const;

  public:
  
    TPatternWood() :
      TPattern(),
      bGradientLoaded (false),
      tZoom (1, 1, 1),
      tRingScale (15),
      tGrainFactor (1) {}

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TColor pattern (const TSurfaceData& rktDATA) const
    {
      TVector tPoint = rktDATA.localPoint() * tZoom;

      return evaluate (tPoint);
    }

    int setAttribute (const std::string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const std::string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    void setColor (const TColor& rktCOLOR)
    {
      tColor = rktCOLOR;
    }
    void setBaseColor (const TColor& rktCOLOR)
    {
      tBaseColor = rktCOLOR;
    }

    std::string className (void) const { return "PatternWood"; }
    TPatternWood* clone_new() const { return new TPatternWood(*this); }

};  /* class TPatternWood */

#endif  /* _PATTERN_WOOD__ */
