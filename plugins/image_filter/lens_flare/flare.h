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

#ifndef _FLARE__
#define _FLARE__

#include "llapi/image_filter.h"
#include "llapi/image.h"
#include "llapi/gradient.h"

enum ELFForms
{

  FX_PENTAGON = 0,
  FX_HEXAGON,
  FX_CIRCLE

};  /* enum ELFForms */

class TFlare
{

  private:

    float      fXifrac_Yifrac;
    float      fXfrac_Yifrac;
    float      fXifrac_Yfrac;
    float      fXfrac_Yfrac;

  protected:

    TColor       tColor;    
    ELFForms     eForm;
    float        fSize;
    float        fTranslation;
    TImage*      ptImage;

    int          iImWidth, iImHeight;

    TImage*      ptFlareImage;

    float        fFlWidth, fFlHeight;    
    int          iFlWidth, iFlHeight;

    float        fFlMidX, fFlMidY;
    float        fDistToMid;

    float        fIncX, fIncY;

    bool         gGradientActive;
    TGradient*   ptGradient;

    bool         gFlareGenerated;

    float        fRotation;
    float        fArcLength;

  private:

    TColor& calcFlareColor (int X, int Y);

    void initialize (void);
    void generate (void);

    void setupCorrection (size_t zNOEDGES, float fROTATION);
    void calculateCorrectedXY (float& rfDX, float& rfDY);

  protected:

    inline float sqr (float X) { return (X * X); }
    inline float hypot (float DX, float DY)
    {
      return (float) sqrt ((DX * DX) + (DY * DY));
    }

    virtual float calcPixelIntensity (float DX, float DY) = 0;

  public:

    TFlare (TColor tColor, ELFForms eFORM, float fSIZE, float fTRANSLATION, TImage* ptIMAGE);
    TFlare (TGradient* ptCOLOR, ELFForms eFORM, float fSIZE, float fTRANSLATION, TImage* ptIMAGE);
    virtual ~TFlare (void);

    void render (float fINTENSITY, float fHPOSITION, float fVPOSITION);

};  /* class TFlare */

#endif  /* _FLARE__ */







