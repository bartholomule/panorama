/*
*  Copyright (C) 2000 Jon Frydensbjerg
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
#include "pat_composite.h"

DEFINE_PLUGIN ("PatternComposite", FX_PATTERN_CLASS, TPatternComposite);


int TPatternComposite::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "pattern1" )
  {
    if ( eTYPE == FX_PATTERN )
    {
      setPattern1 ((TPattern*) nVALUE.pvValue);
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "pattern2" )
  {
    if ( eTYPE == FX_PATTERN )
    {
      setPattern2 ((TPattern*) nVALUE.pvValue);
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "amount1" )
  {
    if ( eTYPE == FX_REAL )
    {
      tPattern1Amount = nVALUE.dValue;
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }  
  else if ( rktNAME == "amount2" )
  {
    if ( eTYPE == FX_REAL )
    {
      tPattern2Amount = nVALUE.dValue;
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


int TPatternComposite::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "pattern1" )
  {
    rnVALUE.pvValue = ptPattern1;
  }
  else if ( rktNAME == "pattern2" )
  {
    rnVALUE.pvValue = ptPattern2;
  }
  else if ( rktNAME == "amount1" )
  {
    rnVALUE.dValue = tPattern1Amount;
  }
  else if ( rktNAME == "amount2" )
  {
    rnVALUE.dValue = tPattern2Amount;
  }
  else
  {
    return TPattern::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TPatternComposite::getAttributeList (TAttributeList& rtLIST) const
{

  TPattern::getAttributeList (rtLIST);

  rtLIST ["pattern1"] = FX_PATTERN;
  rtLIST ["pattern2"] = FX_PATTERN;
  rtLIST ["amount1"]  = FX_REAL;
  rtLIST ["amount2"]  = FX_REAL;

}  /* getAttributeList() */

