/*
*  Copyright (C) 1998, 1999 Angel Jimenez Jimenez and Carlos Jimenez Moreno
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
#include "llapi/image_io.h"
#include "llapi/attribute.h"

int TImageIO::setAttribute (const std::string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  GOM.debug() << __FUNCTION__ << "(" << rktNAME << ")" << std::endl;
  if ( rktNAME == "name" )
  {
#if !defined(NEW_ATTRIBUTES)    
    if ( eTYPE == FX_STRING )
    {
      tFileName = (char*) nVALUE.pvValue;
    }
#else
    magic_pointer<TAttribString> s = get_string(nVALUE);
    if( !!s )
    {
      tFileName = s->tValue;
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else
  {
    return TProcedural::setAttribute (rktNAME, nVALUE, eTYPE);
  }

  return FX_ATTRIB_OK;

}  /* setAttribute() */


int TImageIO::getAttribute (const std::string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "name" )
  {
#if !defined(NEW_ATTRIBUTES)    
    rnVALUE.pvValue = (char*) tFileName.c_str();
#else
    rnVALUE = (user_arg_type)new TAttribString (tFileName);
#endif
  }
  else
  {
    return TProcedural::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TImageIO::getAttributeList (TAttributeList& rtLIST) const
{

  TProcedural::getAttributeList (rtLIST);

  rtLIST ["name"] = FX_STRING;

}  /* getAttributeList() */
