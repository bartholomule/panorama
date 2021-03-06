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
#include "atm_const.h"

DEFINE_PLUGIN ("AtmConst", FX_ATM_OBJECT_CLASS, TAtmConst);

TAtmConst::TAtmConst (void) :
  TAtmosphericObject()
{

  tSampleData.tExtinction = 0.1;
  tSampleData.tAlbedo     = 0.5;

}  /* TAtmConst() */


int TAtmConst::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "extinction" )
  {
    if ( eTYPE == FX_REAL )
    {
      tSampleData.tExtinction = nVALUE.dValue;
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "albedo" )
  {
    if ( eTYPE == FX_REAL )
    {
      tSampleData.tAlbedo = nVALUE.dValue;
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "from" )
  {
    if ( eTYPE == FX_VECTOR )
    {
      tBBFrom = *((TVector*) nVALUE.pvValue);
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "to" )
  {
    if ( eTYPE == FX_VECTOR )
    {
      tBBTo = *((TVector*) nVALUE.pvValue);
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else
  {
    return TAtmosphericObject::setAttribute (rktNAME, nVALUE, eTYPE);
  }

  return FX_ATTRIB_OK;

}  /* setAttribute() */


int TAtmConst::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "extinction" )
  {
    rnVALUE.dValue = tSampleData.tExtinction;
  }
  else if ( rktNAME == "albedo" )
  {
    rnVALUE.dValue = tSampleData.tAlbedo;
  }
  else if ( rktNAME == "from" )
  {
    rnVALUE.pvValue = &tBBFrom;
  }
  else if ( rktNAME == "to" )
  {
    rnVALUE.pvValue = &tBBTo;
  }
  else
  {
    return TAtmosphericObject::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TAtmConst::getAttributeList (TAttributeList& rtLIST) const
{

  TAtmosphericObject::getAttributeList (rtLIST);

  rtLIST ["extinction"] = FX_REAL;
  rtLIST ["albedo"]     = FX_REAL;
  rtLIST ["from"]       = FX_VECTOR;
  rtLIST ["to"]         = FX_VECTOR;

}  /* getAttributeList() */


bool TAtmConst::initialize (TScene* ptSCENE)
{

  bool val = TAtmosphericObject::initialize (ptSCENE);

  tBoundingBox.set (tBBFrom, tBBTo);

  return val;
}  /* initialize() */
