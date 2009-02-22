/*
 *  Copyright (C) 2008 Kevin Harris
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

#include "llapi/user_functions.h"
#include "llapi/string_format.hpp"

namespace panorama
{
  DEFINE_EXCEPTION(InvalidArgumentException);

  void checkParameterLength(const AttributeArray& args, size_t required)
  {
    if( args.size() != reqired )
    {
      THROW(InvalidArgumentException, string_format("Incorrect number of arguments (%1) supplied (should be %2)", args.size(), required).c_str());
    }
  }

  void checkTypesMatch(const AttributeArray& required, const AttributeArray& supplied)
  {
    CheckParameterLength(supplied, required.size());

    AttributeArray::const_iterator reqIter = required.begin();
    AttributeArray::const_iterator supIter = supplied.begin();

    for( ; supIter != supplied.end(); ++supIter, ++reqIter )
    {
      if( !types_match(*supIter, *reqIter) )
      {
        THROW(InvalidArgumentException, string_format("Parameter %1 was supplied an incorrect type.  Expected=%2, Supplied=%3",
            std::distance(supplied.begin(), supIter),
            reqIter->name(), supIter->name()).c_str());
      }
    }
  }

};
