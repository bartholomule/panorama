/*
*  Copyright (C) 1999 Angel Jimenez Jimenez and Carlos Jimenez Moreno
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

#include "mat_parquet.h"


DEFINE_PLUGIN ("MaterialParquet", FX_MATERIAL_CLASS, TMaterialParquet);

const int akiLookup[8][8] =
  {
    {  0,  1,  2,  4,  4,  3,  5,  0 },
    {  7,  1,  6,  6,  9,  3,  8,  8 },
    {  7, 10, 10, 11,  9, 12, 12, 13 },
    { 14, 14, 15, 11, 16, 16, 17, 13 },
    { 18, 19, 15, 20, 20, 21, 17, 18 },
    { 23, 19, 22, 22, 25, 21, 24, 24 },
    { 23, 26, 26, 27, 25, 28, 28, 29 },
    { 30, 30,  2, 27, 32, 32,  5, 29 }
  };


inline TColor TMaterialParquet::evaluate (const TVector& rktPOINT) const
{
  TScalar  tValue;
  TColor   tRet;
  TScalar  tX  = rktPOINT.x()/3;
  TScalar  tY  = rktPOINT.y()/3;
  TScalar  tZ  = rktPOINT.z()/3;
  int      iX  = ((int) tfloor (rktPOINT.x() / 8.0)) & 7;
  int      iZ  = ((int) tfloor (rktPOINT.z() / 8.0)) & 7;
  int      iT  = akiLookup [ iX ][ iZ ];
  TScalar  tT  = (TScalar) iT;

  if (iT & 1)
  {
    tValue = tWood.wood (tZ, tY + tT / 3, tX, 15 + tT/2, 1);
  }
  else
  {
    tValue = tWood.wood (tX, tY + tT / 3, tZ, 15 + tT/2, 1);
  }

  tValue = clamp (tValue, 0, 1);

  tRet = lerp (tColor, tBaseColor, tValue);
  
  srand (iT << 2);

  tRet *= 1.0 - frand() * 0.4;
  
  return tRet;
}


int TMaterialParquet::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
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
      tZoom = *((TVector*) nVALUE.pvValue);
      tZoom.set (1.0 / tZoom.x(), 1.0 / tZoom.y(), 1.0 / tZoom.z());
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
      tBump = nVALUE.dValue;
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


int TMaterialParquet::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "base_color" )
  {
    rnVALUE.pvValue = &tBaseColor;
  }
  else if ( rktNAME == "zoom" )
  {
    // [_ERROR_] It should return the inverse of this vector.
    rnVALUE.pvValue = &tZoom;
  }
  else if ( rktNAME == "bump" )
  {
    rnVALUE.dValue = tBump;
  }
  else
  {
    return TMaterial::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TMaterialParquet::getAttributeList (TAttributeList& rtLIST) const
{

  TMaterial::getAttributeList (rtLIST);

  rtLIST ["base_color"] = FX_COLOR;

}  /* getAttributeList() */
