/*
*  Copyright (C) 1998, 1999 Angel Jimenez Jimenez, Carlos Jimenez Moreno and Pete Barnett
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

#include "llapi/warning_eliminator.h"
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include "pat_brick.h"

DEFINE_PLUGIN ("PatternBrick", FX_PATTERN_CLASS, TPatternBrick);

TScalar TPatternBrick::evaluate (const TVector& rktPOINT, TVector* ptGRADIENT) const
{

  TScalar   tValue, tX, tY, tZ, tWX, tWY, tWZ;
  TScalar   tTotalWidth  = tBrickWidth + tMortarThickness;
  TScalar   tTotalHeight = tBrickHeight + tMortarThickness;
  TScalar   tMortarW     = tMortarThickness * 0.5 / tTotalWidth;
  TScalar   tMortarH     = tMortarThickness * 0.5 / tTotalHeight;
  
  // Scale coordinates into the interval 0..1  
  tX = rktPOINT.x() / tTotalWidth;
  tY = rktPOINT.y() / tTotalHeight;
  tZ = rktPOINT.z() / tTotalWidth;
  
  // Offset x and z for alternate layers of bricks

  if ( mod (tY * 0.5, 1.0) < 0.5 )
  {
    tX += 0.5;
    tZ += 0.5;
  }
  
  // Get x, y, and z as offsets into scaled brick  
  tX -= floor (tX);
  tY -= floor (tY);
  tZ -= floor (tZ);
  
  tWX = smoothstep (0.0, tMortarW, tX) - smoothstep (1.0 - tMortarW, 1.0, tX);
  tWY = smoothstep (0.0, tMortarH, tY) - smoothstep (1.0 - tMortarH, 1.0, tY);
  tWZ = smoothstep (0.0, tMortarW, tZ) - smoothstep (1.0 - tMortarW, 1.0, tZ);

  tValue = tWX * tWY * tWZ;
    
  if ( ptGRADIENT )
  {
    TScalar   tGx, tGy, tGz;

    tGx = smoothstepdiff (1.0 - tMortarW, 1.0, tX) - smoothstepdiff (0.0, tMortarW, tX);
    tGy = smoothstepdiff (1.0 - tMortarH, 1.0, tY) - smoothstepdiff (0.0, tMortarH, tY);
    tGz = smoothstepdiff (1.0 - tMortarW, 1.0, tZ) - smoothstepdiff (0.0, tMortarW, tZ);
    
    ptGRADIENT->set (tGx * tValue, tGy * tValue, tGz * tValue);
  }
  
  return tValue;

}  /* evaluate() */


int TPatternBrick::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "color" )
  {
    if ( eTYPE == FX_COLOR )
    {
      setColor (*((TColor*) nVALUE.pvValue));
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "base_color" )
  {
    if ( eTYPE == FX_COLOR )
    {
      setBaseColor (*((TColor*) nVALUE.pvValue));
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "zoom" )
  {
    if ( eTYPE == FX_VECTOR )
    {
      tZoomOriginal = *((TVector*) nVALUE.pvValue);

      tZoom.set (1.0 / tZoomOriginal.x(), 1.0 / tZoomOriginal.y(), 1.0 / tZoomOriginal.z());
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "width" )
  {
    if ( eTYPE == FX_REAL )
    {
      tBrickWidth = nVALUE.dValue;
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "height" )
  {
    if ( eTYPE == FX_REAL )
    {
      tBrickHeight = nVALUE.dValue;
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "mortar" )
  {
    if ( eTYPE == FX_REAL )
    {
      tMortarThickness = nVALUE.dValue;
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }  
  else
  {
    return TPattern::setAttribute (rktNAME, nVALUE, eTYPE);
  }

  return FX_ATTRIB_OK;

}  /* setAttribute() */


int TPatternBrick::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "color" )
  {
    rnVALUE.pvValue = &tColor;
  }
  else if ( rktNAME == "base_color" )
  {
    rnVALUE.pvValue = &tBaseColor;
  }
  else if ( rktNAME == "zoom" )
  {
    rnVALUE.pvValue = &tZoomOriginal;
  }
  else if ( rktNAME == "width" )
  {
    rnVALUE.dValue = tBrickWidth;
  }
  else if ( rktNAME == "height" )
  {
    rnVALUE.dValue = tBrickHeight;
  }
  else if ( rktNAME == "mortar" )
  {
    rnVALUE.dValue = tMortarThickness;
  }
  else
  {
    return TPattern::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TPatternBrick::getAttributeList (TAttributeList& rtLIST) const
{

  TPattern::getAttributeList (rtLIST);

  rtLIST ["color"]      = FX_COLOR;
  rtLIST ["base_color"] = FX_COLOR;
  rtLIST ["zoom"]       = FX_VECTOR;
  rtLIST ["width"]      = FX_REAL;
  rtLIST ["height"]     = FX_REAL;
  rtLIST ["mortar"]     = FX_REAL;

}  /* getAttributeList() */

