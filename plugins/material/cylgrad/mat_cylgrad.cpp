/*
*  Copyright (C) 1999 Angel Jimenez Jimenez, Carlos Jimenez Moreno and Peter Barnett
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


#include "mat_cylgrad.h"

#ifndef M_PI
  #define M_PI 3.141592653589793238467
#endif

DEFINE_PLUGIN ("MaterialCylGrad", FX_MATERIAL_CLASS, TMaterialCylGrad);

inline TScalar mod (TScalar a, TScalar b)
{
    int n = (int) (a/b);

    a -= n * b;

    if ( a < 0 )
    {
        a += b;
    }
    
    return a;
}

inline TColor TMaterialCylGrad::evaluate (const TVector& rktPOINT) const
{
  TScalar  tX = rktPOINT.x();
  TScalar  tY = rktPOINT.y();
  TScalar  tZ = rktPOINT.z();
  TScalar  tValue;
  TScalar  tAngle;
  TColor   tRet;
  int      nCycle;

  // get angle of the point about the y-axis
  
  tAngle = atan2 (tZ, tX) / (M_PI + M_PI);
  if( tAngle < 0.0 ) tAngle += 1.0;

  // swirl if required
  

  if( fabs (tSwirl) > FX_EPSILON)
  {
      tY /= 1000.0;
      tAngle += mod (tY, 1.0);
      tAngle = mod (tAngle, 1.0);
  }

  tAngle *= tCycles;

  // which segment of tCycles segments are we in?

  nCycle = (int) (tAngle);
  tAngle = mod (tAngle, 1.0);

  // interpolate up for even segments, down for odd

  tValue = ( nCycle & 1 ) ? 1.0 - tAngle : tAngle;
  
  if ( bGradientLoaded == true )
  {
    tRet = tGradient.getColorAt (tValue);
  }
  else
  {
    tRet = lerp (tColor, tBaseColor, tValue);
  }
  
  return tRet;
}


int TMaterialCylGrad::setAttribute (const string& rktNAME, NAttribute
nVALUE, EAttribType eTYPE)
{
  if ( rktNAME == "base_color" )
  {
    if ( eTYPE == FX_COLOR )
    {
      setBaseColor (*((TColor*) nVALUE.pvValue));
    }
    else if ( eTYPE == FX_STRING )
    {
      bGradientLoaded = tGradient.loadGradient((char *) nVALUE.pvValue);
    }
    else 
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "cycles" )
  {
    if ( eTYPE == FX_REAL )
    {
      tCycles = nVALUE.dValue;
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "swirl" )
  {
    if ( eTYPE == FX_REAL )
    {
      tSwirl = nVALUE.dValue;
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


int TMaterialCylGrad::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "base_color" )
  {
    rnVALUE.pvValue = &tBaseColor;
  }
  else if ( rktNAME == "cycles" )
  {
    rnVALUE.pvValue = &tCycles;
  }
  else if ( rktNAME == "swirl" )
  {
    rnVALUE.pvValue = &tSwirl;
  }
  else
  {
    return TMaterial::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TMaterialCylGrad::getAttributeList (TAttributeList& rtLIST) const
{

  TMaterial::getAttributeList (rtLIST);

  rtLIST ["base_color"] = FX_COLOR;

}  /* getAttributeList() */
