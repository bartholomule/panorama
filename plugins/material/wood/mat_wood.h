/*
*  Copyright (C) 1999 Angel Jimenez Jimenez and Carlos Jimenez Moreno
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

#ifndef _MATERIAL_WOOD__
#define _MATERIAL_WOOD__

#include "llapi/material.h"
#include "llapi/wood.h"
#include "llapi/gradient.h"
#include "llapi/mat_utils.h"
#include "hlapi/plugin_manager.h"


class TMaterialWood : public TMaterial
{

  protected:

    TWood           tWood;
    TGradient       tGradient;
    
    bool            bGradientLoaded;
    TColor          tBaseColor;
    TVector         tZoom;
    TScalar         tBump;
    TScalar         tRingScale;
    TScalar         tGrainFactor;
    TColor          evaluate (const TVector& rktPOINT) const;

  public:
  
    TMaterialWood() :
      TMaterial(),
      bGradientLoaded ( false ),
      tZoom ( 1, 1, 1),
      tBump ( 0 ),
      tRingScale ( 15 ),
      tGrainFactor ( 1 )
      {
      }

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TColor color (const TSurfaceData& rktDATA) const
    {
      TVector tPoint = rktDATA.localPoint() * tZoom;
      return evaluate (tPoint);
    }

    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    virtual void setBaseColor (const TColor& rktCOLOR)
    {
      tBaseColor = rktCOLOR;
    }

    string className (void) const { return "MaterialWood"; }

};  /* class TMaterialWood */

#endif  /* _MATERIAL_WOOD__ */
