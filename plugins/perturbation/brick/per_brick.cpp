/*
*  Copyright (C) 1998, 1999 Angel Jimenez Jimenez, Carlos Jimenez Moreno and Pete Barnett
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
#include "per_brick.h"
#include "llapi/attribute.h"
#include "llapi/extended_attribute.h"

DEFINE_PLUGIN ("PerturbationBrick", FX_PERTURBATION_CLASS, TPerturbationBrick);


int TPerturbationBrick::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
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
  else if ( rktNAME == "brick_pattern" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_PATTERN )
    {
      setBrickPattern (((TPatternBrick*) nVALUE.pvValue)->clone_new());

      if ( ptBrickPattern->className() != "PatternBrick" )
      {
	return FX_ATTRIB_WRONG_TYPE;
      }
    }
#else
    magic_pointer<TAttribPattern> pat = get_pattern(nVALUE);
    if( !!pat )
    {
      if( !pat->tValue || (!!pat->tValue &&
			   pat->tValue->className() != "PatternBrick" ) )
      {
	return FX_ATTRIB_WRONG_TYPE;	
      }
      setBrickPattern(rcp_static_cast<TPatternBrick>(pat->tValue));
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


int TPerturbationBrick::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

#if !defined(NEW_ATTRIBUTES)
  if ( rktNAME == "bump" )
  {
    rnVALUE.dValue = tBumpFactor;
  }
  else if ( rktNAME == "brick_pattern" )
  {
    rnVALUE.pvValue = ptBrickPattern.get_pointer();
  }
#else
  if ( rktNAME == "bump" )
  {
    rnVALUE = (user_arg_type)new TAttribReal (tBumpFactor);
  }
  else if ( rktNAME == "brick_pattern" )
  {
    rnVALUE = (user_arg_type)new TAttribPattern (rcp_static_cast<TPattern>(ptBrickPattern));
  }  
#endif
  else
  {
    return TPerturbation::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TPerturbationBrick::getAttributeList (TAttributeList& rtLIST) const
{

  TPerturbation::getAttributeList (rtLIST);

  rtLIST ["brick_pattern"] = FX_PATTERN;
  rtLIST ["bump"]          = FX_REAL;

}  /* getAttributeList() */

