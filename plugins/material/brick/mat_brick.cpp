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

#include <stdlib.h>
#include <iostream>
#include <time.h>
#include "mat_brick.h"

DEFINE_PLUGIN ("MaterialBrick", FX_MATERIAL_CLASS, TMaterialBrick);


inline TScalar TMaterialBrick::step (TScalar a, TScalar x) const
{

  return (TScalar) ( x >= a );

}


inline TScalar TMaterialBrick::smoothstep (TScalar a, TScalar b, TScalar x) const
{

  if (x < a) 
  {
    return 0.0;
  }
  if (x >= b) 
  {
    return 1.0;
  }

	// Normalize x 
  x = (x - a) / (b - a); 

  return x * x * (3 - 2 * x);

}


inline TScalar TMaterialBrick::smoothstepdiff (TScalar a, TScalar b, TScalar x) const
{

  if ( ( x < a ) || ( x >= b ) ) 
  {
    return 0.0;
  }
  
	// Normalize x 
  x = (x - a) / (b - a); 

  return 4.0 * x * (1.0 - x);

}


inline TScalar TMaterialBrick::evaluate (const TVector& rktPOINT, TVector* ptGRADIENT) const
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


inline TVector TMaterialBrick::perturbNormal (const TSurfaceData& rktDATA) const
{

  TVector   tNewNormal = rktDATA.normal();

  if ( fabs(tBumpFactor) > FX_EPSILON )
  {
    TVector   tGradient;
    TVector   tPoint = rktDATA.localPoint() * tZoom;

    tPoint = tPoint + tNewNormal * evaluate (tPoint);

    evaluate (tPoint, &tGradient);

    tNewNormal = rktDATA.normal() + tGradient * tBumpFactor;
    tNewNormal.normalize();
  }
  
  return tNewNormal;  

}  /* perturbNormal() */


int TMaterialBrick::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "base_color" )
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
  else if ( rktNAME == "bump" )
  {
    if ( eTYPE == FX_REAL )
    {
      tBumpFactor = nVALUE.dValue;
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
    return TMaterial::setAttribute (rktNAME, nVALUE, eTYPE);
  }

  return FX_ATTRIB_OK;

}  /* setAttribute() */


int TMaterialBrick::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "base_color" )
  {
    rnVALUE.pvValue = &tBaseColor;
  }
  else if ( rktNAME == "zoom" )
  {
    rnVALUE.pvValue = &tZoomOriginal;
  }
  else if ( rktNAME == "bump" )
  {
    rnVALUE.dValue = tBumpFactor;
  }
  else
  {
    return TMaterial::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TMaterialBrick::getAttributeList (TAttributeList& rtLIST) const
{

  TMaterial::getAttributeList (rtLIST);

  rtLIST ["base_color"] = FX_COLOR;
  rtLIST ["zoom"]       = FX_VECTOR;
  rtLIST ["bump"]       = FX_REAL;

}  /* getAttributeList() */

