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
#include "pat_checker.h"
#include "llapi/attribute.h"
#include "llapi/extended_attribute.h"

DEFINE_PLUGIN ("PatternChecker", FX_PATTERN_CLASS, TPatternChecker);

int TPatternChecker::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
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
#else
    magic_pointer<TAttribColor> col = get_color(nVALUE);
    if( !!col )
    {
      setBaseColor (col->tValue);
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "size" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_REAL )
    {
      setSize (nVALUE.dValue);
    }
#else
    magic_pointer<TAttribReal> r = get_real(nVALUE);
    if( !!r )
    {
      setSize (r->tValue);
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "border" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_REAL )
    {
      setBorder (nVALUE.dValue);
    }
#else
    magic_pointer<TAttribReal> r = get_real(nVALUE);
    if( !!r )
    {
      setBorder (r->tValue);
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


int TPatternChecker::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
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
  else if ( rktNAME == "size" )
  {
    rnVALUE.dValue = tCheckerBoard.size();
  }
  else if ( rktNAME == "border" )
  {
    rnVALUE.dValue = tCheckerBoard.border();
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
  else if ( rktNAME == "size" )
  {
    rnVALUE = (user_arg_type)new TAttribReal (tCheckerBoard.size());
  }
  else if ( rktNAME == "border" )
  {
    rnVALUE = (user_arg_type)new TAttribReal (tCheckerBoard.border());
  }  
#endif
  else
  {
    return TPattern::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TPatternChecker::getAttributeList (TAttributeList& rtLIST) const
{

  TPattern::getAttributeList (rtLIST);

  rtLIST ["color"]      = FX_COLOR;
  rtLIST ["base_color"] = FX_COLOR;
  rtLIST ["size"]       = FX_REAL;
  rtLIST ["border"]     = FX_REAL;

}  /* getAttributeList() */
