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

#include "llapi/warning_eliminator.h"
#include "pat_cylgrad.h"
#include "llapi/attribute.h"
#include "llapi/extended_attribute.h"

DEFINE_PLUGIN ("PatternCylGrad", FX_PATTERN_CLASS, TPatternCylGrad);

TScalar mod (TScalar a, TScalar b)
{
    int n = (int) (a/b);

    a -= n * b;

    if ( a < 0 )
    {
        a += b;
    }
    
    return a;
}


TColor TPatternCylGrad::evaluate (const TVector& rktPOINT) const
{
  TScalar  tX = rktPOINT.x();
  TScalar  tY = rktPOINT.y();
  TScalar  tZ = rktPOINT.z();
  TScalar  tValue;
  TScalar  tAngle;
  TColor   tRet;
  int      nCycle;

  // get angle of the point about the y-axis
  
  tAngle = atan2 (tZ, tX) / (PI + PI);
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


int TPatternCylGrad::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "color" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_COLOR )
    {
      setColor (*((TColor*) nVALUE.pvValue));
    }
#else
    magic_pointer<TAttribColor> col = get_color(nVALUE);
    if( !!col )
    {
      setColor (col->tValue);
    }
#endif
    else 
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "base_color" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_COLOR )
    {
      setBaseColor (*((TColor*) nVALUE.pvValue));
    }
    else if ( eTYPE == FX_STRING )
    {
      bGradientLoaded = tGradient.loadGradient((char *) nVALUE.pvValue);
    }
#else
    magic_pointer<TAttribColor> col = get_color(nVALUE);
    magic_pointer<TAttribString> str = get_string(nVALUE);    
    if( !!col )
    {
      setBaseColor (col->tValue);
    }
    else if( !!str )
    {
      bGradientLoaded = tGradient.loadGradient (str->tValue);
    }
#endif
    else 
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "cycles" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_REAL )
    {
      tCycles = nVALUE.dValue;
    }
#else
    magic_pointer<TAttribReal> r = get_real(nVALUE);
    if( !!r )
    {
      tCycles = r->tValue;
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "swirl" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_REAL )
    {
      tSwirl = nVALUE.dValue;
    }
#else
    magic_pointer<TAttribReal> r = get_real(nVALUE);
    if( !!r )
    {
      tSwirl = r->tValue;
    }
#endif
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


int TPatternCylGrad::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

#if !defined(NEW_ATTRIBUTES)
  if ( rktNAME == "color" )
  {
    rnVALUE.pvValue = &tColor;
  }
  else if ( rktNAME == "base_color" )
  {
    rnVALUE.pvValue = &tBaseColor;
  }
  else if ( rktNAME == "cycles" )
  {
    rnVALUE.dValue = tCycles;
  }
  else if ( rktNAME == "swirl" )
  {
    rnVALUE.dValue = tSwirl;
  }
#else
  if ( rktNAME == "color" )
  {
    rnVALUE = (user_arg_type)new TAttribColor (tColor);
  }
  else if ( rktNAME == "base_color" )
  {
    rnVALUE = (user_arg_type)new TAttribColor (tBaseColor);
  }
  else if ( rktNAME == "cycles" )
  {
    rnVALUE = (user_arg_type)new TAttribReal (tCycles);
  }
  else if ( rktNAME == "swirl" )
  {
    rnVALUE = (user_arg_type)new TAttribReal (tSwirl);
  }  
#endif
  else
  {
    return TPattern::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TPatternCylGrad::getAttributeList (TAttributeList& rtLIST) const
{

  TPattern::getAttributeList (rtLIST);
 
  rtLIST ["color"]      = FX_COLOR;
  rtLIST ["base_color"] = FX_COLOR;
  rtLIST ["cycles"]     = FX_REAL;
  rtLIST ["swirl"]      = FX_REAL;

}  /* getAttributeList() */
