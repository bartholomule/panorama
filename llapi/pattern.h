/*
*  Copyright (C) 2000 Jon Frydensbjerg
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

#ifndef _PATTERN__
#define _PATTERN__

#include "llapi/procedural.h"
#include "llapi/surface_data.h"
#include "llapi/object.h"

enum EWarps
{

  FX_NO_WARP = 0,
  FX_SPHERICAL_WARP,
  FX_CYLINDRICAL_WARP

};  /* enum EWarps */

class TPattern : public TProcedural
{

  protected:

    TVector          tRotation;
    TVector          tScaling;
    TVector          tTranslation;
    TVector          tRSTScaling;
    EWarps           eWarp;

    mutable TColor   tColor;

    TMatrix          tMatrix;
    TMatrix          tInverseMatrix;
    TMatrix          tMatrixRotation;

    bool             gTransformIdentity;

    void recalculateMatrix (void);

    void sphericalWarp (TVector& rtPOINT) const;
    void cylindricalWarp (TVector& rtPOINT) const;

    void sphericalAntiWarp (TVector& rtPOINT) const;
    void cylindricalAntiWarp (TVector& rtPOINT) const;

  public:

    TPattern (void) 
    {
      initialize();
    }
    TPattern (const TColor& rktCOLOR) :
      tColor (rktCOLOR) 
    {
      initialize();
    }
    TPattern (const TScalar& rktSCALAR) 
    {
      setScalar (rktSCALAR);

      initialize();
    }

    virtual TScalar scalar (const TSurfaceData& rktDATA) const { return color (rktDATA).average(); }
    virtual TColor  color  (const TSurfaceData& rktDATA) const;

    virtual TColor pattern (const TSurfaceData& rktDATA) const { return tColor; }

    void setColor (const TColor& rktCOLOR) { tColor = rktCOLOR; }
    void setScalar (const TScalar& rktSCALAR)
    {
      tColor.setRed (rktSCALAR);
      tColor.setGreen (rktSCALAR);
      tColor.setBlue (rktSCALAR);
    }

    TVector warp (const TVector& rktPOINT) const;
    TVector antiWarp (const TVector& rktPOINT) const;
    
    TColor  lastColor  (void) const { return tColor; }
    TScalar lastScalar (void) const { return tColor.average(); }

    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    EClass classType (void) const { return FX_PATTERN_CLASS; }
    string className (void) const { return "Pattern"; }

    virtual bool initialize (void);
};  /* class TPattern */

#endif  /* _PATTERN__ */

