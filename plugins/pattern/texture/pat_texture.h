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

class TPatternTexture : public TPattern
{

  protected:

    size_t    zTextureWidth, zTextureHeight;
    TImage*   ptImage;

    int correctTexel (int iVALUE, const size_t& rkzMAX) const;
    
    TColor lerpTexel (TScalar ut, TScalar vt) const;

    void sphericalMap (const TVector& rktPOINT, TScalar& rtTHETA, TScalar& rtPHI) const;

  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TPatternTexture (void) :
      TPattern() {}
    
    TColor pattern (const TSurfaceData& rktDATA) const;

    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    string className (void) const { return "PatternTexture"; }

};  /* class TPatternTexture */

#endif  /* _PATTERN_TEXTURE__ */

