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

#include "of_cartoon.h"

DEFINE_PLUGIN ("OF_Cartoon", FX_OBJECT_FILTER_CLASS, TOF_Cartoon);

TColor TOF_Cartoon::filterRadiance (TSurfaceData& rtDATA, const TColor& rktRAD) const
{

  TColor    tRadiance;
  Byte      bTones;
  TScalar   tCos = dotProduct (rtDATA.normal(), -rtDATA.ray().direction());

  if ( tCos < 0.3 )
  {
    tRadiance = tOutlineColor;
  }
  else
  {
    bTones    = Byte (ceil (255.0 / bColorLevels));
    tRadiance = rktRAD.convertTo24Bits();

    tRadiance.setRed (bTones * ceil (tRadiance.red() / bTones));
    tRadiance.setGreen (bTones * ceil (tRadiance.green() / bTones));
    tRadiance.setBlue (bTones * ceil (tRadiance.blue() / bTones));

    tRadiance = tRadiance.convertFrom24Bits();
  }

  return tRadiance;

}  /* filterRadiance() */


int TOF_Cartoon::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
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
  else
  {
    return TObjectFilter::setAttribute (rktNAME, nVALUE, eTYPE);
  }

  return FX_ATTRIB_OK;

}  /* setAttribute() */


int TOF_Cartoon::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "outline" )
  {
    rnVALUE.pvValue = &tOutlineColor;
  }
  else if ( rktNAME == "levels" )
  {
    rnVALUE.dValue = bColorLevels;
  }
  else
  {
    return TObjectFilter::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TOF_Cartoon::getAttributeList (TAttributeList& rtLIST) const
{

  TObjectFilter::getAttributeList (rtLIST);

  rtLIST ["outline"] = FX_COLOR;
  rtLIST ["levels"]  = FX_REAL;
  
}  /* getAttributeList() */
