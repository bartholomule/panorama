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

string   TProcedural::_tUserErrorMessage = "";

void TProcedural::sendEvent (const string& rktEVENT)
{

  cout << "Object <" << className() << "> send event <" << rktEVENT << ">" << endl;

}  /* sendEvent() */


void TProcedural::sendEvent (const string& rktEVENT, NAttribute nAttrib)
{

  cout << "Object <" << className() << "> send event <" << rktEVENT << "> with argument" << endl;

}  /* sendEvent() */


#if defined(NEW_ATTRIBUES)
int TProcedural::setAttribute (const string& rktNAME, NAttribute nVALUE)
{
  if( !!nVALUE )
  {
    return setAttribute (rktNAME, nVALUE, nVALUE->eType);
  }
  
  TProcedural::_tUserErrorMessage = "cannot extract type from NULL attribute";
  return FX_ATTRIB_USER_ERROR;
}

int TProcedural::setAttribute (const string& rktNAME,
			       const list<NAttribute>& rktLIST)
{
  if( !rktLIST.empty() )
  {
    for(list<NAttribute>::const_iterator it = rktLIST.begin();
	it != rktLIST.end();
	++it)
    {
      setAttribute(rktNAME, *it);
    }
  }
  TProcedural::_tUserErrorMessage = "cannot set values from empty list";
  return FX_ATTRIB_USER_ERROR;
}
#endif

int TProcedural::setAttribute (const string& rktNAME,
			       const list<NAttribute>& rktLIST,
			       EAttribType eTYPE)
{
  if( !rktLIST.empty() )
  {
    for(list<NAttribute>::const_iterator it = rktLIST.begin();
	it != rktLIST.end();
	++it)
    {
      setAttribute(rktNAME, *it, eTYPE);
    }
  }
  TProcedural::_tUserErrorMessage = "cannot set values from empty list";
  return FX_ATTRIB_USER_ERROR;  
}

int TProcedural::setAttribute (const string& rktNAME, NAttribute nVALUE,
			       EAttribType eTYPE)
{
  if(rktNAME == "name")
  {
#if !defined(NEW_ATTRIBUTES)    
    if(eTYPE == FX_STRING)
    {
      setIdentifier((char*)nVALUE.pvValue);
      return FX_ATTRIB_OK;
    }
#else
    magic_pointer<TAttribString> str = get_string(nVALUE);
    if( !!str )
    {
      setIdentifier (str->tValue);
      return FX_ATTRIB_OK;
    }
#endif
    return FX_ATTRIB_WRONG_TYPE;
  }  
  return FX_ATTRIB_WRONG_PARAM;
}

int TProcedural::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{
  if(rktNAME == "name")
  {
#if !defined(NEW_ATTRIBUTES)    
    rnVALUE.pvValue = (void*)tIdentifier.c_str();
#else
    rnVALUE = new TAttribString (tIdentifier);
#endif
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

  tufm["setName"]=create_user_function(this,&TProcedural::setIdentifier);
  // This is safe to do, because the base class will call the virtual function...
  void (TBaseClass::*fn)(void) const = &TBaseClass::printDebug;
  tufm["printDebug"]           = create_user_function((TBaseClass*)this,fn);
  
  
  return tufm;
}

