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

#if       !defined(TYPE_FUNCTIONS_H)
#define            TYPE_FUNCTIONS_H

#include "llapi/llapi_defs.h"
#include "llapi/procedural.h"
#include "generic/rc_pointer.hpp"
#include "llapi/attribute.h"
#include "llapi/exception.hpp"
#include "llapi/string_format.hpp"

#include <typeinfo>

namespace panorama
{
  DECLARE_EXCEPTION(TypeConversionException);

  template <typename A, typename B>
  struct Convertable
  {
    static const bool value = false;
  };

  template <typename A, typename B, bool value>
  struct ConvertHelper
  {
    inline static B convert(const A&)
    {
      THROW(TypeConversionException, string_format("Types cannot be converted: %1 --> %2", typeid(A).name(), typeid(B).name).c_str());
    }
  };

  template<>
  template <typename A, typename B>
  struct ConvertHelper<A,B,true>
  {
    inline static B convert(const A& a)
    {
      return B(a);
    }
  };

  template <typename A, typename B>
  struct Convert
  {
    inline static B convert(const A& a)
    {
      return ConvertHelper<A,B,Convertable<A,B>::value>(a);
    }
  };

  // ---------------------------------------------------------------------------
  // Functions for std::string-[FX]type conversion, type comparison
  // ---------------------------------------------------------------------------
  // Return a std::string for the given attribute type
  std::string EAttribType_to_str (Attribute::AttributeType eTYPE);


  // Return an attribute type for the given std::string (opposite of previous)
  Attribute::AttributeType str_to_EAttribType (const std::string& s);

  // Return if the second type can be coerced into something that will match the
  // first.
  bool types_match(const Attribute& a1, const Attribute& a2);
  bool types_match(const AttributeArray& a1, const AttributeArray& a2);

  // ---------------------------------------------------------------------------
  // Functions that should be specialized for every type that is used as:
  // 1. return types
  // 2. function parameters
  // 3. attributes
  //
  // These 4 functions are:
  // 1. Attribute::AttributeType type_to_etype<T>(T t);
  //      Return the FX_ type for the object.
  // 2. Attribute type_to_attrib<T>(T t);
  //      Return the attribute type with the correct values for the object.
  // 3. T attrib_to_type<T>(Attribute);
  //      Return the extracted value from the attribute.
  // 4. Attribute get_attrib<T>();
  //      Return an attribute type with junk values (used for type comparison).
  // ---------------------------------------------------------------------------


  // Convert an attribute back to its real form (the reverse of the above
  // function.  Again, the default template should NEVER be used, only a
  // specialization thereof.
  // The pointer 'data' is some place where temporary data may be
  // stored so that it may live longer than the extent of the function body
  // (ie. for returning references).
  template <class T>
  inline T attrib_to_type(Attribute atp,
    Attribute& data)
  {
    T t;
    t.BREAK_HERE();
    THROW(Exception, "Specialize this function, or try including <llapi/extended_type_functions.h>");
  }

  // A function similar to type_to_attrib, however, this will return an empty
  // shell of an attribute which can be used in type comparison.  Again, the
  // default template should NEVER be used, only a specialization thereof.
  template <class T>
  inline Attribute get_attrib()
  {
    T t;
    t.BREAK_HERE();
    THROW(Exception, "Specialize this function, or try including <llapi/extended_type_functions.h>");
  }


  // ---------------------------------------------------------------------------
  // Void (return, param) (some of these are not templated, due to C++
  // limitations on void template parameters [it allows void template parameters
  // to match return types, but apparently not arguments].
  // ---------------------------------------------------------------------------

  //template <>
  //inline Attribute type_to_attrib<void>(void)
  inline Attribute type_to_attrib(void)
  {
    return Attribute();
  }

  template <>
  inline void attrib_to_type<void>(Attribute atp,
    Attribute& data)
  {
  }

  template <>
  inline Attribute get_attrib<void>()
  {
    return Attribute();
  }
}

#endif /* !defined(TYPE_FUNCTIONS_H) */
