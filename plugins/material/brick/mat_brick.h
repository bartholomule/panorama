/*
*  Copyright (C) 1998 Angel Jimenez Jimenez and Carlos Jimenez Moreno
*  Copyright (C) 1998 Pete Barnett
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
*
*/

#ifndef _MAT_BRICK__
#define _MAT_BRICK__

#include "llapi/material.h"
#include "hlapi/plugin_manager.h"

class TMaterialBrick : public TMaterial
{

  protected:

    TColor    tBaseColor;
    TVector   tZoom;
    TScalar   tBumpFactor;
    TScalar   tBrickWidth;
    TScalar   tBrickHeight;
    TScalar   tMortarThickness;
    
    TScalar evaluate (const TVector& rktPOINT, TVector* ptGRADIENT = NULL) const;

  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TMaterialBrick (void) :
      TMaterial(),
      tZoom (1, 1, 1),
      tBumpFactor (0),
      tBrickWidth (2.5),
      tBrickHeight (0.8),
      tMortarThickness(0.1) {}
    
    TScalar step( TScalar a, TScalar x) const;
    TScalar smoothstep( TScalar a, TScalar b, TScalar x) const;
    TScalar smoothstepdiff( TScalar a, TScalar b, TScalar x) const;
      
    TColor color (const TSurfaceData& rktDATA) const
    {
      TVector   tPoint = rktDATA.localPoint() * tZoom;
      TScalar   tValue = evaluate (tPoint);

      return lerp (tBaseColor, tColor, tValue);
    }
    
    TVector perturbNormal (const TSurfaceData& rktDATA) const;

    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    virtual void setBaseColor (const TColor& rktCOLOR)
    {
      tBaseColor = rktCOLOR;
    }

    string className (void) const { return "MaterialBrick"; }
};  /* class TMaterialBrick */

#endif

