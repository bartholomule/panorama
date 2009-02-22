/*
*  Copyright (C) 1999 Angel Jimenez Jimenez and Carlos Jimenez Moreno
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
#include "llapi/procedural.h"
#include "llapi/object_required.h"

namespace panorama
{
  DEFINE_EXCEPTION(AttributeException);
  DEFINE_EXCEPTION_BASE(IncorrectTypeException, AttributeException);
  DEFINE_EXCEPTION_BASE(InvalidNameException, AttributeException);

  int TProcedural::setAttribute (const std::string& rktNAME, NAttribute nVALUE)
  {
    if( !nVALUE )
    {
      THROW(IncorrectTypeException, "Cannot extract type from NULL attribute");
    }

    if( rktNAME == "identifier" )
    {
      if( !getString(nVALUE, tIdentifier) )
      {
        return FX_ATTRIB_OK;
      }
    }
    else
    {
      THROW(InvalidNameException, string_format("Attribute name is invalid: %1", rktNAME).c_str());
    }
  }

  int TProcedural::setAttribute (const std::string& rktNAME,
    const std::list<NAttribute>& rktLIST)
  {
    if( !rktLIST.empty() )
    {
      for(std::list<NAttribute>::const_iterator it = rktLIST.begin();
          it != rktLIST.end();
          ++it)
      {
        setAttribute(rktNAME, *it);
      }
    }
    TProcedural::_tUserErrorMessage = "cannot set values from empty list";
    return FX_ATTRIB_USER_ERROR;
  }

  int TProcedural::setAttribute (const std::string& rktNAME,
    const std::list<NAttribute>& rktLIST,
    EAttribType eTYPE)
  {
    if( !rktLIST.empty() )
    {
      for(std::list<NAttribute>::const_iterator it = rktLIST.begin();
          it != rktLIST.end();
          ++it)
      {
        setAttribute(rktNAME, *it, eTYPE);
      }
    }
    TProcedural::_tUserErrorMessage = "cannot set values from empty list";
    return FX_ATTRIB_USER_ERROR;
  }

  int TProcedural::getAttribute (const std::string& rktNAME, NAttribute& rnVALUE)
  {
    if(rktNAME == "name")
    {
      rnVALUE = user_arg_type(new TAttribString (tIdentifier));
      return FX_ATTRIB_OK;
    }
    return FX_ATTRIB_WRONG_PARAM;
  }

  void TProcedural::getAttributeList (TAttributeList& rtLIST) const
  {
    rtLIST ["name"] = FX_STRING;
  }


  TUserFunctionMap TProcedural::getUserFunctions()
  {
    TUserFunctionMap tufm;

    tufm["setName"] = create_user_function(this, &TProcedural::setIdentifier);
    // This is safe to do, because the base class will call the virtual
    // function...
    std::string (TBaseClass::*fn)(void) const = &TBaseClass::printDebug;
    tufm["printDebug"] = create_user_function((TBaseClass*)this,fn);


    return tufm;
  }

} // end namespace panorama

