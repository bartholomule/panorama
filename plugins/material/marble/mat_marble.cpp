/*
*  Copyright (C) 1998 Angel Jimenez Jimenez and Carlos Jimenez Moreno
*  Copyright (C) 1998 Pete Barnett
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
#include "mat_marble.h"

DEFINE_PLUGIN ("MaterialMarble", FX_MATERIAL_CLASS, TMaterialMarble);



int TMaterialMarble::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
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
      tBumpFactor = nVALUE.dValue;
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "start_freq" )
  {
    if ( eTYPE == FX_REAL )
    {
      if ( nVALUE.dValue > 0.0 )
      {
        tStartFreq = nVALUE.dValue;
        tEndFreq   = tStartFreq;
        
        for (int i = 0; i < (int) tNumOctaves; i++)
        {
          tEndFreq *= 2.17;
        }
      }
      else
      {
        return FX_ATTRIB_WRONG_VALUE;
      }
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "octaves" )
  {
    if ( eTYPE == FX_REAL )
    {
      if ( nVALUE.dValue >= 1.0 )
      {
        tNumOctaves = nVALUE.dValue;
        tEndFreq   = tStartFreq;
        
        for (int i = 0; i < (int) tNumOctaves; i++)
        {
          tEndFreq *= 2.17;
        }
      }
      else
      {
        return FX_ATTRIB_WRONG_VALUE;
      }
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


int TMaterialMarble::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
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
    rnVALUE.dValue = tBumpFactor;
  }
  else if ( rktNAME == "start_freq" )
  {
    rnVALUE.dValue = tStartFreq;
  }
  else if ( rktNAME == "octaves" )
  {
    rnVALUE.dValue = tNumOctaves;
  }
  else
  {
    return TMaterial::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TMaterialMarble::getAttributeList (TAttributeList& rtLIST) const
{

  TMaterial::getAttributeList (rtLIST);

  rtLIST ["base_color"] = FX_COLOR;
  rtLIST ["zoom"]       = FX_VECTOR;
  rtLIST ["bump"]       = FX_REAL;

}  /* getAttributeList() */