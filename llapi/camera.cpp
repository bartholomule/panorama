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
#include "llapi/camera.h"
#include "llapi/attribute.h"

int TCamera::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "up" )
  {
#if !defined(NEW_ATTRIBUTES)    
    if ( eTYPE == FX_VECTOR )
    {
      setUp (*((TVector*) nVALUE.pvValue));
    }
#else
    magic_pointer<TAttribVector> vec = get_vector(nVALUE);
    if( !!vec )
    {
      setUp (vec->tValue);
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "look_at" )
  {
#if !defined(NEW_ATTRIBUTES)    
    if ( eTYPE == FX_VECTOR )
    {
      setLookAt (*((TVector*) nVALUE.pvValue));
    }
#else
    magic_pointer<TAttribVector> vec = get_vector(nVALUE);
    if( !!vec )
    {
      setLookAt (vec->tValue);
    }
#endif    
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else
  {
    return TEntity::setAttribute (rktNAME, nVALUE, eTYPE);
  }

  return FX_ATTRIB_OK;

}  /* setAttribute() */


int TCamera::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

#if !defined(NEW_ATTRIBUTES)  
  if ( rktNAME == "up" )
  {
    rnVALUE.pvValue = &tUp;
  }
  else if ( rktNAME == "look_at" )
  {
    rnVALUE.pvValue = &tLookAt;
  }
#else
  if ( rktNAME == "up" )
  {
    rnVALUE = new TAttribVector (tUp);
  }
  else if ( rktNAME == "look_at" )
  {
    rnVALUE = new TAttribVector (tLookAt);
  }  
#endif
  else
  {
    return TEntity::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TCamera::getAttributeList (TAttributeList& rtLIST) const
{

  TEntity::getAttributeList (rtLIST);

  rtLIST ["up"]      = FX_VECTOR;
  rtLIST ["look_at"] = FX_VECTOR;

}  /* getAttributeList() */


TUserFunctionMap TCamera::getUserFunctions()
{
  TUserFunctionMap ufm = TEntity::getUserFunctions();

  ufm["getLookAt"] = create_user_function(this,&TCamera::getLookAt);
  ufm["setLookAt"] = create_user_function(this,&TCamera::setLookAt);
  ufm["getUp"] = create_user_function(this,&TCamera::getUp);
  ufm["setUp"] = create_user_function(this,&TCamera::setUp);    
  
  return ufm;
}


