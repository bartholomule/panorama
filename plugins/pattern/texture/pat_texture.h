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
*
*/

#ifndef _PATTERN_TEXTURE__
#define _PATTERN_TEXTURE__

#include "llapi/image.h"
#include "llapi/pattern.h"
#include "hlapi/plugin_manager.h"

enum EMappings
{

  FX_SPHERICAL = 0,
  FX_CYLINDRICAL,
  FX_PLANAR

};  /* enum EMappings */

class TPatternTexture : public TPattern
{

  protected:

    TColor      tColor;
    TImage*     ptImage;
    TVector2    tTiling;
    TVector2    tOffset;
    bool        gMirror;
    bool        gTile;
    EMappings   eMapping;

    size_t     zTextureWidth, zTextureHeight;
 
    int correctTexel (int iVALUE, const size_t& rkzMAX) const;
    
    TColor lerpTexel (const TVector2& rktUVCOORD) const;

    void sphericalMap (const TVector& rktPOINT, TVector2& rtUVCOORD) const;
    void cylindricalMap (const TVector& rktPOINT, TVector2& rtUVCOORD) const;
    void planarMap (const TVector& rktPOINT, TVector2& rtUVCOORD) const;
    
  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TPatternTexture (void);
    
    TColor pattern (const TSurfaceData& rktDATA) const;

    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    string className (void) const { return "PatternTexture"; }

};  /* class TPatternTexture */

#endif  /* _PATTERN_TEXTURE__ */

