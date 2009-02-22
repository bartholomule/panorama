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

#ifndef PANORAMA_PROCEDURAL_H_INCLUDED
#define PANORAMA_PROCEDURAL_H_INCLUDED

#include "llapi/base_class.h"
#include "llapi/program.h"
#include "llapi/user_functions.h"
#include "llapi/exception.hpp"

namespace panorama
{
  enum AttributeErrorCode
  {
    FX_ATTRIB_OK,
    FX_ATTRIB_USER_ERROR1,
    FX_ATTRIB_WRONG_PARAM,
    FX_ATTRIB_WRONG_TYPE3,
    FX_ATTRIB_WRONG_VALUE
  };

  DECLARE_EXCEPTION_BASE(IncorrectTypeException, AttributeException);
  DECLARE_EXCEPTION_BASE(InvalidNameException, AttributeException);

  typedef std::map<std::string, Attribute::AttributeType> TAttributeList;
  typedef std::map<std::string, rc_pointer<user_function> > TUserFunctionMap;

  class TProcedural : public TBaseClass
  {
  public:
    // Attribute management
    virtual AttributeErrorCode setAttribute (const std::string& rktNAME, Attribute nVALUE);
    virtual AttributeErrorCode setAttribute (const std::string& rktNAME, const std::list<Attribute>& rktLIST);
    virtual AttributeErrorCode getAttribute (const std::string& rktNAME, Attribute& rnVALUE);
    virtual TAttributeList getAttributeList () const;

    virtual TUserFunctionMap getUserFunctions();
  };  /* class TProcedural */
} // end namespace panorama

#endif  /* PANORAMA_PROCEDURAL_H_INCLUDED */
