/*
*  Copyright (C) 1998 Angel Jimenez Jimenez and Carlos Jimenez Moreno
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

#include <cmath>
#include "llapi/scene.h"
#include "if_cartoon.h"

DEFINE_PLUGIN ("IF_Cartoon", FX_IMAGE_FILTER_CLASS, TIF_Cartoon);

#define FX_MAX_Z            (SCALAR_MAX / 2)

TIF_Cartoon::TIF_Cartoon (void) :
  TImageFilter(),
  bColorLevels (2),
  fNThreshold (0.6),
  fZThreshold (50.0),
  tOutlineColor (TColor::_black())
{

  wNeededBuffers = FX_ZBUFFER | FX_NBUFFER;
  
}  /* TIF_Cartoon() */


void TIF_Cartoon::filter (SBuffers& rsBUFFERS)
{

  TColor      tPixel;
  TVector     N, nu, nd, nl, nr;
  TScalar     Z, zu, zd, zl, zr;
  Byte        bTones    = Byte (ceil (255.0 / bColorLevels));
  TImage*     ptImage   = rsBUFFERS.ptImage;
  TZBuffer*   ptZBuffer = rsBUFFERS.ptZBuffer;
  TNBuffer*   ptNBuffer = rsBUFFERS.ptNBuffer;
  TInterval   tIntX (0, ptImage->width() - 1);
  TInterval   tIntY (0, ptImage->height() - 1);

  for (size_t J = 0; ( J < ptImage->height() ) ;J++)
  {
    for (size_t I = 0; ( I < ptImage->width() ) ;I++)
    {
      Z  = ptZBuffer->getPixel (I, J);
      if ( Z < FX_MAX_Z )
      {
        zu = ptZBuffer->getPixel (I, size_t (tIntY.adjustValue (J - 1)));
        zd = ptZBuffer->getPixel (I, size_t (tIntY.adjustValue (J + 1)));
        zl = ptZBuffer->getPixel (size_t (tIntX.adjustValue (I - 1)), J);
        zr = ptZBuffer->getPixel (size_t (tIntX.adjustValue (I + 1)), J);

        if ( (zu - Z) > fZThreshold )
        {
          ptImage->setPixel (I, J, tOutlineColor);
          continue;
        }
        if ( (zd - Z) > fZThreshold )
        {
          ptImage->setPixel (I, J, tOutlineColor);
          continue;
        }
        if ( (zl - Z) > fZThreshold )
        {
          ptImage->setPixel (I, J, tOutlineColor);
          continue;
        }
        if ( (zr - Z) > fZThreshold )
        {
          ptImage->setPixel (I, J, tOutlineColor);
          continue;
        }

        N  = ptNBuffer->getPixel (I, J);
        nu = ptNBuffer->getPixel (I, size_t (tIntY.adjustValue (J - 1)));
        nd = ptNBuffer->getPixel (I, size_t (tIntY.adjustValue (J + 1)));
        nl = ptNBuffer->getPixel (size_t (tIntX.adjustValue (I - 1)), J);
        nr = ptNBuffer->getPixel (size_t (tIntX.adjustValue (I + 1)), J);

        if ( dotProduct (N, nu) < fNThreshold )
        {
          ptImage->setPixel (I, J, tOutlineColor);
          continue;
        }
        if ( dotProduct (N, nd) < fNThreshold )
        {
          ptImage->setPixel (I, J, tOutlineColor);
          continue;
        }
        if ( dotProduct (N, nl) < fNThreshold )
        {
          ptImage->setPixel (I, J, tOutlineColor);
          continue;
        }
        if ( dotProduct (N, nr) < fNThreshold )
        {
          ptImage->setPixel (I, J, tOutlineColor);
          continue;
        }
      }

      tPixel = ptImage->getPixel (I, J);
//      tPixel.clamp();
      tPixel = tPixel.convertTo24Bits();

      tPixel.setRed (bTones * ceil (tPixel.red() / bTones));
      tPixel.setGreen (bTones * ceil (tPixel.green() / bTones));
      tPixel.setBlue (bTones * ceil (tPixel.blue() / bTones));

      tPixel = tPixel.convertFrom24Bits();
      ptImage->setPixel (I, J, tPixel);
    }
  }
  
}  /* filter() */


int TIF_Cartoon::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "outline" )
  {
    if ( eTYPE == FX_COLOR )
    {
      tOutlineColor = *((TColor*) nVALUE.pvValue);
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "levels" )
  {
    if ( eTYPE == FX_REAL )
    {
      bColorLevels = Byte (nVALUE.dValue);
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "distance_th" )
  {
    if ( eTYPE == FX_REAL )
    {
      fZThreshold = nVALUE.dValue;
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "normal_th" )
  {
    if ( eTYPE == FX_REAL )
    {
      fNThreshold = nVALUE.dValue;
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else
  {
    return TImageFilter::setAttribute (rktNAME, nVALUE, eTYPE);
  }

  return FX_ATTRIB_OK;

}  /* setAttribute() */


int TIF_Cartoon::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "outline" )
  {
    rnVALUE.pvValue = &tOutlineColor;
  }
  else if ( rktNAME == "levels" )
  {
    rnVALUE.dValue = bColorLevels;
  }
  else if ( rktNAME == "distance_th" )
  {
    rnVALUE.dValue = fZThreshold;
  }
  else if ( rktNAME == "normal_th" )
  {
    rnVALUE.dValue = fNThreshold;
  }
  else
  {
    return TImageFilter::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TIF_Cartoon::getAttributeList (TAttributeList& rtLIST) const
{

  TImageFilter::getAttributeList (rtLIST);

  rtLIST ["outline"]     = FX_COLOR;
  rtLIST ["levels"]      = FX_REAL;
  rtLIST ["distance_th"] = FX_REAL;
  rtLIST ["normal_th"]   = FX_REAL;

}  /* getAttributeList() */
