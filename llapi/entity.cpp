/*
*  Copyright (C) 2001 Kevin Harris
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
#include "llapi/entity.h"


void TEntity::translate (const TVector& rktNEW_POS)
{
  //  GOM.debug() << className() << "::" << __FUNCTION__ << " - as TEntity" << endl;
  tLocation += rktNEW_POS;
  update();
}

void TEntity::rotate (const TVector& rktAXISPOINT1, const TVector& rktAXISPOINT2, TScalar tANGLE)
{
  //  GOM.debug() << className() << "::" << __FUNCTION__ << " - as TEntity (empty)" << endl;
}

void TEntity::rotate (const TVector& rktANGLESXYZ)
{
  //  GOM.debug() << className() << "::" << __FUNCTION__ << " - as TEntity (empty)" << endl;
}

void TEntity::rotate (const TQuaternion& rktQUAT)
{
  //  GOM.debug() << className() << "::" << __FUNCTION__ << " - as TEntity (empty)" << endl;
}

TUserFunctionMap TEntity::getUserFunctions()
{
  TUserFunctionMap ufm = TProcedural::getUserFunctions();
  
  ufm["translate"]   = create_user_function(this,&TEntity::translate);
  ufm["setLocation"] = create_user_function(this,&TEntity::setLocation);
  ufm["location"]    = create_user_function(this,&TEntity::location);
  return ufm;
}
