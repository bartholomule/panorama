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
#include "pat_amplifier.h"
#include "llapi/attribute.h"
#include "llapi/extended_attribute.h"

DEFINE_PLUGIN ("PatternAmplifier", FX_PATTERN_CLASS, TPatternAmplifier);


int TPatternAmplifier::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "source" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_PATTERN )
    {
      setPattern (((TPattern*) nVALUE.pvValue)->clone_new());
    }
#else
    magic_pointer<TAttribPattern> pat = get_pattern(nVALUE);
    if( !!pat )
    {
      setPattern (pat->tValue);
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "offset" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_REAL )
    {
      tOffset = nVALUE.dValue;
    }
#else
    magic_pointer<TAttribReal> r = get_real(nVALUE);
    if( !!r )
    {
      tOffset = r->tValue;
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }  
  else if ( rktNAME == "amplification" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_REAL )
    {
      tAmplification = nVALUE.dValue;
    }
#else
    magic_pointer<TAttribReal> r = get_real(nVALUE);
    if( !!r )
    {
      tAmplification = r->tValue;
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


int TPatternAmplifier::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

#if !defined(NEW_ATTRIBUTES)  
  if ( rktNAME == "source" )
  {
    rnVALUE.pvValue = ptPattern.get_pointer();
  }
  else if ( rktNAME == "offset" )
  {
    rnVALUE.dValue = tOffset;
  }
  else if ( rktNAME == "amplification" )
  {
    rnVALUE.dValue = tAmplification;
  }
#else
  if ( rktNAME == "source" )
  {
    rnVALUE = new TAttribPattern (ptPattern);
  }
  else if ( rktNAME == "offset" )
  {
    rnVALUE = new TAttribReal (tOffset);
  }
  else if ( rktNAME == "amplification" )
  {
    rnVALUE = new TAttribReal (tAmplification);
  }
#endif
  else
  {
    return TPattern::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TPatternAmplifier::getAttributeList (TAttributeList& rtLIST) const
{

  TPattern::getAttributeList (rtLIST);

  rtLIST ["source"]        = FX_PATTERN;
  rtLIST ["offset"]        = FX_REAL;
  rtLIST ["amplification"] = FX_REAL;

}  /* getAttributeList() */

