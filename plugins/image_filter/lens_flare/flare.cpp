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

#include <stdio.h>
#include "flare.h"

TFlare::TFlare (TColor tCOLOR, ELFForms eFORM, float fSIZE, float fTRANSLATION, TImage* ptIMAGE) :
  tColor (tCOLOR),
  eForm (eFORM),
  fSize (fSIZE),
  fTranslation (fTRANSLATION),
  ptImage (ptIMAGE)
{
 
  gGradientActive = false;

  initialize();
  
}  /* TFlare() */


TFlare::TFlare (TGradient* ptGRADIENT, ELFForms eFORM, float fSIZE, float fTRANSLATION, TImage* ptIMAGE) :
  eForm (eFORM),
  fSize (fSIZE),
  fTranslation (fTRANSLATION),
  ptImage (ptIMAGE),
  ptGradient (ptGRADIENT)
{
  
  gGradientActive = true;

  initialize();

}  /* TFlare() */


TFlare::~TFlare (void) 
{
  
  delete ptFlareImage;

}  /* ~TFlare() */


void TFlare::initialize (void)
{

  float  fMaxWidth;

  iImWidth  = ptImage->width();
  iImHeight = ptImage->height();

  fMaxWidth = max (iImWidth, iImHeight);

  fFlWidth  = (2.0 * fSize) * fMaxWidth;
  fFlHeight = (2.0 * fSize) * fMaxWidth;

  fFlMidX   = fFlWidth  / 2.0;
  fFlMidY   = fFlHeight / 2.0;

  iFlWidth  = (int) ceil (fFlWidth);
  iFlHeight = (int) ceil (fFlHeight);

  ptFlareImage = new TImage (iFlWidth, iFlHeight);

  gFlareGenerated = false;

  fDistToMid = min (fFlMidX, fFlMidY);

  fIncX = fFlWidth  / ((float) (iFlWidth));
  fIncY = fFlHeight / ((float) (iFlHeight));

  if ( eForm == FX_PENTAGON )
  {
    setupCorrection (5, 0.0f);
  }
  else if ( eForm == FX_HEXAGON )
  {
    setupCorrection (6, 0.0f);
  }

}  /* initialize() */


void TFlare::setupCorrection (size_t zNOEDGES, float fROTATION)
{

  fROTATION -= (float) (zNOEDGES - 2) * (PI / 2.0f) / (float) zNOEDGES;

  fRotation = fmod (double(fROTATION), double(2.0f * PI));

  fArcLength = (2.0f * PI) / (float) zNOEDGES;

}  /* setupCorrection() */


void TFlare::calculateCorrectedXY (float& rfDX, float& rfDY)
{

  static TVector2  _tVectP0;
  static TVector2  _tVectV;
  static TVector2  _tVectI;
  static TVector2  _tVectNi;
  static TScalar   _tDot1;
  static TScalar   _tDot2;
  static float     fAngle;
  static float     fFraction;
  static float     fBaseAngle;
  static float     fP0x, fP0y;
  static float     fP1x, fP1y;
  static float     fVx, fVy;
  static float     fRadius;
  static float     T;

  if ( ( rfDX == 0.0f ) && ( rfDY == 0.0f ) )
  {
    return;
  }

  fRadius = hypot (rfDX, rfDY);
  fAngle  = atan2 (rfDY, rfDX) + PI - fRotation;

  if ( fAngle < 0.0f )
  {
    fAngle += PI * 2.0f;
  }

  fFraction  = fmod (fAngle, fArcLength);
  fBaseAngle = fAngle - fFraction + fRotation - PI;

  fP0x = cos (fBaseAngle) * fRadius;
  fP0y = sin (fBaseAngle) * fRadius;

  fP1x = cos (fBaseAngle + fArcLength) * fRadius;
  fP1y = sin (fBaseAngle + fArcLength) * fRadius;

  fVx = fP1x - fP0x;
  fVy = fP1y - fP0y;

  _tVectV.set (fVx, fVy);

  _tVectI.set  ((rfDX + fVy), (rfDY - fVx));
  _tVectNi.set ((rfDY - _tVectI.y()), (_tVectI.x() - rfDX));

  _tVectP0.set (fP0x, fP0y);

  _tDot1 =  (dotProduct (_tVectNi, _tVectP0 - _tVectI));
  _tDot2 = -(dotProduct (_tVectNi, _tVectV));

  T = _tDot1 / _tDot2;

  rfDX = fP0x + fVx * T;
  rfDY = fP0y + fVy * T;
   
}  /* calculateCorrectedXY() */


void TFlare::generate (void)
{

  float  X, Y;
  float  DX, DY;
  float  NX;
  float  fPixelIntensity; 
  float  fRecip;
  int    M, N;
  Word*  apwHitGrid;

  for (int I = 0; ( I < iFlWidth ) ;I++) 
  {
    for (int J = 0; ( J < iFlHeight ) ;J++) 
    {
      ptFlareImage->setPixel (I, J, TColor::_black());
    }
  }

  apwHitGrid = (Word *) calloc (sizeof(Word), iFlWidth * iFlHeight);

  //
  // Calculate lens flare (with supersampling)
  //
 
  fIncX /= 2.0f;
  fIncY /= 2.0f;

  X = 0.0f;

  for (int I = 0; ( I < (2 * iFlWidth) ) ;I++) 
  {
    DX = (X - fFlMidX);

    Y = 0.0f;

    for (int J = 0; ( J < (2 * iFlHeight) ) ;J++) 
    {
      DY = (Y - fFlMidY);
  
      if ( gGradientActive )
      {
	tColor = ptGradient->getColorAt(1.0f - hypot(DX, DY) / fDistToMid);
      }
 
      fPixelIntensity = calcPixelIntensity (DX, DY);

      if ( eForm == FX_CIRCLE )
      {
        M = (I / 2);	
        N = (J / 2);
      }
      else 
      {
	NX = DX;

      	calculateCorrectedXY (NX, DY);

        M = (int) (fFlMidX + NX);	
        N = (int) (fFlMidY + DY);	
      }

      ptFlareImage->setPixel (M, N, (ptFlareImage->getPixel (M, N) + tColor * fPixelIntensity));
      
      apwHitGrid [(N * iFlWidth) + M]++;

      Y += fIncY; 
    }

    X += fIncX;
  }

  for (int I = 0; ( I < iFlWidth ) ;I++) 
  {
    for (int J = 0; ( J < iFlHeight ) ;J++) 
    {
      fRecip = (float) apwHitGrid [(J * iFlWidth) + I];

      if ( fRecip != 0.0f )
      {
        ptFlareImage->setPixel (I, J, ptFlareImage->getPixel (I, J) / fRecip);
      }      
    }
  }

  free (apwHitGrid);

}  /* generate() */


TColor& TFlare::calcFlareColor (int X, int Y)
{

  static TColor _tFinalColor;
  
  _tFinalColor = TColor::_black();

  if ( ( X < iFlWidth ) && ( Y < iFlHeight ) )
  {
    _tFinalColor = ptFlareImage->getPixel (X, Y) * fXifrac_Yifrac;
  }
  if ( ( X > 0 ) && ( Y < iFlHeight ) ) 
  {
    _tFinalColor += ptFlareImage->getPixel ((X - 1), Y) * fXfrac_Yifrac;
  }
  if ( ( X < iFlWidth ) && ( Y > 0 ) ) 
  {
    _tFinalColor += ptFlareImage->getPixel (X, (Y - 1)) * fXifrac_Yfrac;
  }
  if ( ( X > 0 ) && ( Y > 0 ) ) 
  {
    _tFinalColor += ptFlareImage->getPixel ((X - 1), (Y - 1)) * fXfrac_Yfrac;
  }

  return _tFinalColor;

}  /* calcFlareColor() */


void TFlare::render (float fINTENSITY, float fHPOSITION, float fVPOSITION)
{

  TColor   tNewPixel;
  double   dIntegral;
  float    fXpos;
  float    fYpos;
  float    fXfrac;
  float    fXifrac;
  float    fYfrac;
  float    fYifrac;
  int      iStartX;
  int      iStartY;
  int      iEndX;
  int      iEndY;
  int      iFlXstart;
  int      iFlXend;
  int      iFlYstart;
  int      iFlYend;

  if ( !gFlareGenerated ) 
  {
    generate();

    gFlareGenerated = true;
  }

  fXpos = (0.5f - fHPOSITION) * fTranslation + 0.5f;
  fYpos = (0.5f - fVPOSITION) * fTranslation + 0.5f;

  fXfrac  = modf ((fXpos * (iImWidth - 1) - (fFlWidth / 2.0)), &dIntegral);
  fXifrac = 1.0f - fXfrac;
  iStartX = (int) dIntegral; 
  iEndX   = iStartX + iFlWidth;

  fYfrac  = modf ((fYpos * (iImHeight - 1) - (fFlHeight / 2.0)), &dIntegral);
  fYifrac = 1.0f - fYfrac;
  iStartY = (int) dIntegral; 
  iEndY   = iStartY + iFlHeight;

  /* Clipping */

  iFlXstart = 0;
  iFlXend   = iFlWidth;
  iFlYstart = 0;
  iFlYend   = iFlHeight;
  
  if ( iStartX < 0 )
  {
    iFlXstart -= iStartX;
    iStartX = 0;
    fXfrac  = 0.0f;
    fXifrac = 1.0f;
  }
  if ( iStartY < 0 )
  {
    iFlYstart -= iStartY;
    iStartY = 0;
    fYfrac  = 0.0f;
    fYifrac = 1.0f;
  }
  if ( iEndX >= iImWidth )
  {
    iFlXend -= (iEndX - (iImWidth - 1));
  }
  if ( iEndY >= iImHeight )
  {
    iFlYend -= (iEndY - (iImHeight - 1));
  }

  fXifrac_Yifrac = fXifrac * fYifrac;
  fXfrac_Yifrac  = fXfrac  * fYifrac;
  fXifrac_Yfrac  = fXifrac * fYfrac;
  fXfrac_Yfrac   = fXfrac  * fYfrac;

  for (int I = iFlXstart, M = iStartX; ( I <= iFlXend ) ;I++, M++) 
  {
    for (int J = iFlYstart, N = iStartY; ( J <= iFlYend ) ;J++, N++) 
    {
      tNewPixel = ptImage->getPixel (M, N);
      tNewPixel.clamp();

      tNewPixel += (TColor::_white() - tNewPixel) * (calcFlareColor (I, J) * fINTENSITY);

      ptImage->setPixel (M, N, tNewPixel);
    }
  }

}  /* render() */









































