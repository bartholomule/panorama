/*
*  Copyright (C) 1999 Jon Frydensbjerg
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

#ifndef _IF_LENS_FLARE__
#define _IF_LENS_FLARE__

#include "flare.h"
#include "llapi/image_filter.h"
#include "hlapi/plugin_manager.h"

#define MAX_ARTEFACTS 40

enum ELFTypes
{

  FX_NEAR = 0,
  FX_NORMAL,
  FX_FAR

};  /* enum ELFTypes */

class TIF_Lens_Flare : public TImageFilter
{

  protected:

    ELFTypes  eType;
    ELFForms  eForm;
    float     fScale;
    float     fThreshold;
    float     fIntensity;
    float     fInfluence;
    bool      gArtefacts;

    size_t    iNoHotspots;
    size_t    iNoArtefacts;

    TFlare*   aptHotspotTable [MAX_ARTEFACTS];
    TFlare*   aptArtefactTable[MAX_ARTEFACTS];

    bool*     apgMarkedMap; 

    TImage*   ptCurrentImage;
    TImage*   ptImageCopy;

    float     fMaxIntensity;
    int       iMaxXpos;
    int       iMaxYpos;

  protected:

    void generateNearFlares (void);
    void generateNormalFlares (void);
    void generateFarFlares (void);

    void renderFlares (float fATTENUATION, float fXOFFSET, float fYOFFSET);

    bool checkPixel (int X, int Y);
    void markArea (int X, int Y);
    inline bool getMapPixel (int X, int Y) 
    { 
      return apgMarkedMap[Y * ptCurrentImage->width() + X]; 
    }
    inline void setMapPixel (int X, int Y, bool gVALUE) 
    { 
      apgMarkedMap[Y * ptCurrentImage->width() + X] = gVALUE; 
    }

    void flaresByReflections (void);
    void flaresByLightsources (void);

  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TIF_Lens_Flare (void);

    void filter (SBuffers& rsBUFFERS);

    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    string className (void) const { return "IF_Lens_Flare"; }

    virtual TIF_Lens_Flare* clone_new() const { return new TIF_Lens_Flare(*this); }

};  /* class TIF_Lens_Flare */

#endif  /* _IF_LENS_FLARE__ */







