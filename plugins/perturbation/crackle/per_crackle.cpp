/*
*  Copyright (C) 1998, 1999 Angel Jimenez Jimenez, Carlos Jimenez Moreno and Peter Barnett
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
*
*  Algorithm based on public domain code by Jim McElhiney,
*  CompuServe 71201,1326, aka mcelhiney@acm.org
*/

#include "llapi/warning_eliminator.h"
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include "per_crackle.h"
#include "llapi/attribute.h"
#include "llapi/extended_attribute.h"

DEFINE_PLUGIN ("PerturbationCrackle", FX_PERTURBATION_CLASS, TPerturbationCrackle);


int TPerturbationCrackle::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "bump" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_REAL )
    {
      tBumpFactor = nVALUE.dValue;
    }
#else
    magic_pointer<TAttribReal> r = get_real(nVALUE);
    if( !!r )
    {
      tBumpFactor = r->tValue;
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "crackle_pattern" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_PATTERN )
    {
      setCracklePattern (((TPatternCrackle*) nVALUE.pvValue)->clone_new());

      if ( ptCracklePattern->className() != "PatternCrackle" )
      {
	return FX_ATTRIB_WRONG_TYPE;
      }
    }
#else
    magic_pointer<TAttribPattern> pat = get_pattern(nVALUE);
    if( !!pat )
    {
      if( pat->tValue->className() != "PatternCrackle" )
      {
	return FX_ATTRIB_WRONG_TYPE;	
      }
      setCracklePattern (rcp_static_cast<TPatternCrackle>(pat->tValue));
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else
  {
    return TPerturbation::setAttribute (rktNAME, nVALUE, eTYPE);
  }

  return FX_ATTRIB_OK;

}  /* setAttribute() */


int TPerturbationCrackle::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

#if !defined(NEW_ATTRIBUTES)
  if ( rktNAME == "bump" )
  {
    rnVALUE.dValue = tBumpFactor;
  }
  else if ( rktNAME == "crackle_pattern" )
  {
    rnVALUE.pvValue = ptCracklePattern.get_pointer();
  }
#else
  if ( rktNAME == "bump" )
  {
    rnVALUE = (user_arg_type)new TAttribReal (tBumpFactor);
  }
  else if ( rktNAME == "crackle_pattern" )
  {
    rnVALUE = (user_arg_type)new TAttribPattern (rcp_static_cast<TPattern>(ptCracklePattern));
  }
#endif
  else
  {
    return TPerturbation::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TPerturbationCrackle::getAttributeList (TAttributeList& rtLIST) const
{

  TPerturbation::getAttributeList (rtLIST);

  rtLIST ["crackle_pattern"] = FX_PATTERN;
  rtLIST ["bump"]            = FX_REAL;

}  /* getAttributeList() */

