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

#include "llapi/warning_eliminator.h"
#include "hlapi/circle.h"
#include "llapi/attribute.h"

int TCircle::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "radius" )
  {
#if !defined(NEW_ATTRIBUTES)      
    if ( eTYPE == FX_REAL )
    {
      setRadius (nVALUE.dValue);
    }
#else
    magic_pointer<TAttribReal> r = get_real(nVALUE);
    if( !!r )
    {
      setRadius(r->tValue);
    }
#endif    
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else
  {
    return TPlane::setAttribute (rktNAME, nVALUE, eTYPE);
  }

  return FX_ATTRIB_OK;

}  /* setAttribute() */


int TCircle::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "radius" )
  {
#if !defined(NEW_ATTRIBUTES)    
    rnVALUE.dValue = sqrt (tRadius2);
#else
    rnVALUE = (user_arg_type)new TAttribReal (sqrt (tRadius2));
#endif
  }
  else
  {
    return TPlane::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TCircle::getAttributeList (TAttributeList& rtLIST) const
{

  TPlane::getAttributeList (rtLIST);

  rtLIST ["radius"] = FX_REAL;

}  /* getAttributeList() */


TVector TCircle::RandomPointOnSurface() const
{
  // theta = 2 * PI * rand1
  // r = R * sqrt(rand2)
  TScalar r = sqrt(frand() * tRadius2);
  TScalar theta = 2 * PI * frand();

  return TVector(r * cos(theta), r * sin(theta), 0);
}
