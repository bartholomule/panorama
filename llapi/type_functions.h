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
#include "generic/magic_pointer.h"
#include "llapi/attribute.h"

// ---------------------------------------------------------------------------
// Functions for string-[FX]type conversion, type comparison
// ---------------------------------------------------------------------------
// Return a string for the given attribute type 
string EAttribType_to_str (EAttribType eTYPE);


// Return an attribute type for the given string (opposite of previous)
EAttribType str_to_EAttribType (const string& s);

// Return if the second type can be coerced into something that will match the
// first.
bool types_match(const magic_pointer<TAttribute>& a1,
		 const magic_pointer<TAttribute>& a2);

// ---------------------------------------------------------------------------
// Functions that should be specialized for every type that is used as:
// 1. return types
// 2. function parameters
// 3. attributes
//
// These 4 functions are:
// 1. EAttribType type_to_etype<T>(T t);
//      Return the FX_ type for the object.
// 2. magic_pointer<TAttribute> type_to_attrib<T>(T t);
//      Return the attribute type with the correct values for the object.
// 3. T attrib_to_type<T>(magic_pointer<TAttribute>);
//      Return the extracted value from the attribute.
// 4. magic_pointer<TAttribute> get_attrib<T>();
//      Return an attribute type with junk values (used for type comparison).
// ---------------------------------------------------------------------------

// Return an attribute type for the given item.  Specialize this function!
template <class T>
inline EAttribType type_to_etype(T t)
{
  t.BREAK_HERE();
  GOM.error() << "Specialize this function, or try including <llapi/extended_type_functions.h>" << endl
	      << __PRETTY_FUNCTION__ << endl;
  exit(1);
}

// Convert the type into something that can be used as an attribute or passed
// to a user function.  Note that the original templated version should NEVER
// be used, only a specialization thereof. 
template <class T>
inline magic_pointer<TAttribute> type_to_attrib(T t)
{
  t.BREAK_HERE();
  GOM.error() << "Specialize this function, or try including <llapi/extended_type_functions.h>" << endl
       << __PRETTY_FUNCTION__ << endl;  
  exit(1);
}

// Convert an attribute back to its real form (the reverse of the above
// function.  Again, the default template should NEVER be used, only a
// specialization thereof.
// The pointer 'data' is some place where temporary data may be
// stored so that it may live longer than the extent of the function body
// (ie. for returning references). 
template <class T>
inline T attrib_to_type(magic_pointer<TAttribute> atp,
			magic_pointer<TAttribute>& data)
{
  T t;
  t.BREAK_HERE();
  GOM.error() << "Specialize this function, or try including <llapi/extended_type_functions.h>" << endl
       << __PRETTY_FUNCTION__ << endl;  
  exit(1);
}

// A function similar to type_to_attrib, however, this will return an empty
// shell of an attribute which can be used in type comparison.  Again, the
// default template should NEVER be used, only a specialization thereof.
template <class T>
inline magic_pointer<TAttribute> get_attrib()
{
  T t;
  t.BREAK_HERE();
  GOM.error() << "Specialize this function, or try including <llapi/extended_type_functions.h>" << endl
       << __PRETTY_FUNCTION__ << endl;  
  exit(1);
}


// ---------------------------------------------------------------------------
// Void (return, param) (some of these are not templated, due to C++
// limitations on void template parameters [it allows void template parameters
// to match return types, but apparently not arguments].
// ---------------------------------------------------------------------------
//template <>
//inline EAttribType type_to_etype<void>(void)
inline EAttribType type_to_etype(void)
{
  return FX_NONE;
}

//template <>
//inline magic_pointer<TAttribute> type_to_attrib<void>(void)
inline magic_pointer<TAttribute> type_to_attrib(void)
{
  return magic_pointer<TAttribute>(new TAttribute);
}

template <>
inline void attrib_to_type<void>(magic_pointer<TAttribute> atp,
				 magic_pointer<TAttribute>& data)
{
}

template <>
inline magic_pointer<TAttribute> get_attrib<void>()
{
  return magic_pointer<TAttribute>(new TAttribute);
}


// ---------------------------------------------------------------------------
// Generic attribute -- For use in functions which can take ANY type (such as
// print, etc.).
// ---------------------------------------------------------------------------
template <>
inline EAttribType type_to_etype<magic_pointer<TAttribute> >(magic_pointer<TAttribute> atp)
{
  return FX_NONE;
}

template <>
inline magic_pointer<TAttribute>
type_to_attrib<magic_pointer<TAttribute> >(magic_pointer<TAttribute> atp)
{
  return atp;
}

template <>
inline magic_pointer<TAttribute>
attrib_to_type<magic_pointer<TAttribute> >(magic_pointer<TAttribute> atp,
					   magic_pointer<TAttribute>& data)
{
  return atp;
}

template <>
inline magic_pointer<TAttribute> get_attrib<magic_pointer<TAttribute> >()
{
  return magic_pointer<TAttribute>(new TAttribute);
}

// ---------------------------------------------------------------------------
// Integer
// ---------------------------------------------------------------------------
template <>
inline EAttribType type_to_etype<int>(int i)
{
  return FX_INTEGER;
}

template <>
inline magic_pointer<TAttribute> type_to_attrib<int>(int i)
{
  return magic_pointer<TAttribute>(new TAttribInt(i));
}

template <>
inline int attrib_to_type<int>(magic_pointer<TAttribute> atp,
			       magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribInt> i = get_int(atp);
  if( !!i )
  {
    return i->tValue;
  }
  return -1;
}

template <>
inline magic_pointer<TAttribute> get_attrib<int>()
{
  return magic_pointer<TAttribute>(new TAttribInt(0));
}

// ---------------------------------------------------------------------------
// Unsigned Integer
// ---------------------------------------------------------------------------
template <>
inline EAttribType type_to_etype<unsigned int>(unsigned int i)
{
  return FX_INTEGER;
}

template <>
inline magic_pointer<TAttribute> type_to_attrib<unsigned int>(unsigned int i)
{
  return magic_pointer<TAttribute>(new TAttribInt(i));
}

template <>
inline unsigned int attrib_to_type<unsigned int>(magic_pointer<TAttribute> atp,
						 magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribInt> i = get_int(atp);
  if( !!i )
  {
    return i->tValue;
  }
  return 0;
}

template <>
inline magic_pointer<TAttribute> get_attrib<unsigned int>()
{
  return magic_pointer<TAttribute>(new TAttribInt(0));
}

// ---------------------------------------------------------------------------
// Long Integer
// ---------------------------------------------------------------------------
template <>
inline EAttribType type_to_etype<long int>(long int i)
{
  return FX_INTEGER;
}

template <>
inline magic_pointer<TAttribute> type_to_attrib<long int>(long int i)
{
  return magic_pointer<TAttribute>(new TAttribInt(int(i)));
}

template <>
inline long int attrib_to_type<long int>(magic_pointer<TAttribute> atp,
					 magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribInt> i = get_int(atp);
  if( !!i )
  {
    return i->tValue;
  }
  return 0;
}

template <>
inline magic_pointer<TAttribute> get_attrib<long int>()
{
  return magic_pointer<TAttribute>(new TAttribInt(0));
}

// ---------------------------------------------------------------------------
// Unsigned Long Integer
// ---------------------------------------------------------------------------
template <>
inline EAttribType type_to_etype<unsigned long>(unsigned long i)
{
  return FX_INTEGER;
}

template <>
inline magic_pointer<TAttribute> type_to_attrib<unsigned long>(unsigned long i)
{
  return magic_pointer<TAttribute>(new TAttribInt(int(i)));
}

template <>
inline unsigned long attrib_to_type<unsigned long>(magic_pointer<TAttribute>
						   atp,
						   magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribInt> i = get_int(atp);
  if( !!i )
  {
    return i->tValue;
  }
  return 0;
}

template <>
inline magic_pointer<TAttribute> get_attrib<unsigned long>()
{
  return magic_pointer<TAttribute>(new TAttribInt(0));
}

// ---------------------------------------------------------------------------
// Boolean
// ---------------------------------------------------------------------------
template <>
inline EAttribType type_to_etype<bool>(bool b)
{
  return FX_BOOL;
}

template <>
inline magic_pointer<TAttribute> type_to_attrib<bool>(bool b)
{
  return magic_pointer<TAttribute>(new TAttribBool(b));
}

template <>
inline bool attrib_to_type<bool>(magic_pointer<TAttribute> atp,
				 magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribBool> b = get_bool(atp);
  if( !!b )
  {
    return b->tValue;
  }
  return false;
}

template <>
inline magic_pointer<TAttribute> get_attrib<bool>()
{
  return magic_pointer<TAttribute>(new TAttribBool(false));
}

// ---------------------------------------------------------------------------
// String
// ---------------------------------------------------------------------------
template <>
inline EAttribType type_to_etype<string>(string s)
{
  return FX_STRING;
}

template <>
inline magic_pointer<TAttribute> type_to_attrib<string>(string s)
{
  return magic_pointer<TAttribute>(new TAttribString(s));
}

template <>
inline string attrib_to_type<string>(magic_pointer<TAttribute> atp,
				     magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribString> s = get_string(atp);
  if( !!s )
  {
    return s->tValue;
  }
  return string();
}

template <>
inline magic_pointer<TAttribute> get_attrib<string>()
{
  return magic_pointer<TAttribute>(new TAttribString());
}

// ---------------------------------------------------------------------------
// const string&
// ---------------------------------------------------------------------------
template <>
inline EAttribType type_to_etype<const string&>(const string& s)
{
  return FX_STRING;
}

template <>
inline magic_pointer<TAttribute> type_to_attrib<const string&>(const string& s)
{
  return magic_pointer<TAttribute>(new TAttribString(s));
}

template <>
inline const string& attrib_to_type<const string&>(magic_pointer<TAttribute> atp,
						   magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribString> str = get_string(atp);
  
  if( !!str )
  {
    data = rcp_static_cast<TAttribute>(str);
    return str->tValue;
  }
  GOM.error() << "Error: Cannot extract string." << endl;
  exit(1);
}

template <>
inline magic_pointer<TAttribute> get_attrib<const string&>()
{
  return magic_pointer<TAttribute>(new TAttribString());
}

// ---------------------------------------------------------------------------
// String List
// ---------------------------------------------------------------------------
template <>
inline EAttribType type_to_etype<vector<string> >(vector<string> vs)
{
  return FX_STRING_LIST;
}

template <>
inline magic_pointer<TAttribute> type_to_attrib<vector<string> >(vector<string> vs)
{
  return magic_pointer<TAttribute>(new TAttribStringList(vs));
}

template <>
inline vector<string> attrib_to_type<vector<string> >(magic_pointer<TAttribute> atp,
						      magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribStringList> sl = get_stringlist(atp);
  if( !!sl )
  {
    return vector<string>(sl->choices);
  }
  return vector<string>();
}

template <>
inline magic_pointer<TAttribute> get_attrib<vector<string> >()
{
  return magic_pointer<TAttribute>(new TAttribStringList());
}

// ---------------------------------------------------------------------------
// Color
// ---------------------------------------------------------------------------
template <>
inline EAttribType type_to_etype<TColor>(TColor c)
{
  return FX_COLOR;
}

template <>
inline magic_pointer<TAttribute> type_to_attrib<TColor>(TColor c)
{
  return magic_pointer<TAttribute>(new TAttribColor(c));
}

template <>
inline TColor attrib_to_type<TColor>(magic_pointer<TAttribute> atp,
				     magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribColor> col = get_color(atp);
  if( !!col )
  {
    return col->tValue;
  }
  return TColor();
}

template <>
inline magic_pointer<TAttribute> get_attrib<TColor>()
{
  return magic_pointer<TAttribute>(new TAttribColor());
}

// ---------------------------------------------------------------------------
// const TColor&
// ---------------------------------------------------------------------------
template <>
inline EAttribType type_to_etype<const TColor&>(const TColor& v)
{
  return FX_COLOR;
}

template <>
inline magic_pointer<TAttribute> type_to_attrib<const TColor&>(const TColor& v)
{
  return magic_pointer<TAttribute>(new TAttribColor(v));
}

template <>
inline const TColor&
attrib_to_type<const TColor&>(magic_pointer<TAttribute> atp,
			      magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribColor> col = get_color(atp);
  if( !!col )
  {
    data = rcp_static_cast<TAttribute>(col);
    return col->tValue;
  }
  GOM.error() << "Error: Cannot extract color." << endl;
  exit(1);
}

template <>
inline magic_pointer<TAttribute> get_attrib<const TColor&>()
{
  return magic_pointer<TAttribute>(new TAttribColor());
}

// ---------------------------------------------------------------------------
// TVector
// ---------------------------------------------------------------------------
template <>
inline EAttribType type_to_etype<TVector>(TVector v)
{
  return FX_VECTOR;
}

template <>
inline magic_pointer<TAttribute> type_to_attrib<TVector>(TVector v)
{
  return magic_pointer<TAttribute>(new TAttribVector(v));
}

template <>
inline TVector attrib_to_type<TVector>(magic_pointer<TAttribute> atp,
				       magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribVector> vec = get_vector(atp);
  if( !!vec )
  {
    return vec->tValue;
  }
  return TVector();
}

template <>
inline magic_pointer<TAttribute> get_attrib<TVector>()
{
  return magic_pointer<TAttribute>(new TAttribVector());
}

// ---------------------------------------------------------------------------
// const TVector&
// ---------------------------------------------------------------------------
template <>
inline EAttribType type_to_etype<const TVector&>(const TVector& v)
{
  return FX_VECTOR;
}

template <>
inline magic_pointer<TAttribute> type_to_attrib<const TVector&>(const TVector& v)
{
  return magic_pointer<TAttribute>(new TAttribVector(v));
}

template <>
inline const TVector&
attrib_to_type<const TVector&>(magic_pointer<TAttribute> atp,
			       magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribVector> vec = get_vector(atp);
  if( !!vec )
  {
    data = rcp_static_cast<TAttribute>(vec);
    return vec->tValue;
  }
  GOM.error() << "Error: Cannot extract vector." << endl;
  exit(1);
}

template <>
inline magic_pointer<TAttribute> get_attrib<const TVector&>()
{
  return magic_pointer<TAttribute>(new TAttribVector());
}


// ---------------------------------------------------------------------------
// TVector2
// ---------------------------------------------------------------------------
template <>
inline EAttribType type_to_etype<TVector2>(TVector2 v)
{
  return FX_VECTOR2;
}

template <>
inline magic_pointer<TAttribute> type_to_attrib<TVector2>(TVector2 v)
{
  return magic_pointer<TAttribute>(new TAttribVector2(v));
}

template <>
inline TVector2 attrib_to_type<TVector2>(magic_pointer<TAttribute> atp,
					 magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribVector2> vec = get_vector2(atp);
  if( !!vec )
  {
    return vec->tValue;
  }
  return TVector2();
}

template <>
inline magic_pointer<TAttribute> get_attrib<TVector2>()
{
  return magic_pointer<TAttribute>(new TAttribVector2());
}

// ---------------------------------------------------------------------------
// const TVector2&
// ---------------------------------------------------------------------------
template <>
inline EAttribType type_to_etype<const TVector2&>(const TVector2& v)
{
  return FX_VECTOR2;
}

template <>
inline magic_pointer<TAttribute> type_to_attrib<const TVector2&>(const TVector2& v)
{
  return magic_pointer<TAttribute>(new TAttribVector2(v));
}

template <>
inline const TVector2&
attrib_to_type<const TVector2&>(magic_pointer<TAttribute> atp,
				magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribVector2> vec = get_vector2(atp);
  if( !!vec )
  {
    data = rcp_static_cast<TAttribute>(vec);
    return vec->tValue;
  }
  GOM.error() << "Error: Cannot extract vector2." << endl;
  exit(1);
}

template <>
inline magic_pointer<TAttribute> get_attrib<const TVector2&>()
{
  return magic_pointer<TAttribute>(new TAttribVector2());
}


// ---------------------------------------------------------------------------
//  vector<TScalar>
// ---------------------------------------------------------------------------
template <>
inline EAttribType type_to_etype<std::vector<TScalar> >( std::vector<TScalar> v)
{
  return FX_ARRAY;
}

template <>
inline magic_pointer<TAttribute> type_to_attrib<std::vector<TScalar> >( std::vector<TScalar> v)
{
  return magic_pointer<TAttribute>(new TAttribArray(v));
}

template <>
inline  std::vector<TScalar>
attrib_to_type<std::vector<TScalar> >(magic_pointer<TAttribute> atp,
				magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribArray> vec = get_array(atp);
  if( !!vec )
  {
    data = rcp_static_cast<TAttribute>(vec);
    return vec->tValue;
  }
  GOM.error() << "Error: Cannot extract array." << endl;
  exit(1);
}

template <>
inline magic_pointer<TAttribute> get_attrib<std::vector<TScalar> >()
{
  return magic_pointer<TAttribute>(new TAttribArray());
}

// ---------------------------------------------------------------------------
//  vector<TScalar>&
// ---------------------------------------------------------------------------
template <>
inline EAttribType type_to_etype<std::vector<TScalar>&>( std::vector<TScalar>& v)
{
  return FX_ARRAY;
}

template <>
inline magic_pointer<TAttribute> type_to_attrib<std::vector<TScalar>&>( std::vector<TScalar>& v)
{
  return magic_pointer<TAttribute>(new TAttribArray(v));
}

template <>
inline  std::vector<TScalar>&
attrib_to_type<std::vector<TScalar>&>(magic_pointer<TAttribute> atp,
				magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribArray> vec = get_array(atp);
  if( !!vec )
  {
    data = rcp_static_cast<TAttribute>(vec);
    return vec->tValue;
  }
  GOM.error() << "Error: Cannot extract array." << endl;
  exit(1);
}

template <>
inline magic_pointer<TAttribute> get_attrib<std::vector<TScalar>&>()
{
  return magic_pointer<TAttribute>(new TAttribArray());
}


// ---------------------------------------------------------------------------
// const vector<TScalar>&
// ---------------------------------------------------------------------------
template <>
inline EAttribType type_to_etype<const std::vector<TScalar>&>(const std::vector<TScalar>& v)
{
  return FX_ARRAY;
}

template <>
inline magic_pointer<TAttribute> type_to_attrib<const std::vector<TScalar>&>(const std::vector<TScalar>& v)
{
  return magic_pointer<TAttribute>(new TAttribArray(v));
}

template <>
inline const std::vector<TScalar>&
attrib_to_type<const std::vector<TScalar>&>(magic_pointer<TAttribute> atp,
				magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribArray> vec = get_array(atp);
  if( !!vec )
  {
    data = rcp_static_cast<TAttribute>(vec);
    return vec->tValue;
  }
  GOM.error() << "Error: Cannot extract array." << endl;
  exit(1);
}

template <>
inline magic_pointer<TAttribute> get_attrib<const std::vector<TScalar>&>()
{
  return magic_pointer<TAttribute>(new TAttribArray());
}



// ---------------------------------------------------------------------------
// Double
// ---------------------------------------------------------------------------
template <>
inline EAttribType type_to_etype<double>(double d)
{
  return FX_REAL;
}

template <>
inline magic_pointer<TAttribute> type_to_attrib<double>(double d)
{
  return magic_pointer<TAttribute>(new TAttribReal(d));
}

template <>
inline double attrib_to_type<double>(magic_pointer<TAttribute> atp,
				     magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribReal> d = get_real(atp);
  if( !!d )
  {
    return d->tValue;
  }
  return -1;
}

template <>
inline magic_pointer<TAttribute> get_attrib<double>()
{
  return magic_pointer<TAttribute>(new TAttribReal(0));
}

// ---------------------------------------------------------------------------
// Float
// ---------------------------------------------------------------------------
template <>
inline EAttribType type_to_etype<float>(float f)
{
  return FX_REAL;
}

template <>
inline magic_pointer<TAttribute> type_to_attrib<float>(float f)
{
  return magic_pointer<TAttribute>(new TAttribReal(f));
}

template <>
inline float attrib_to_type<float>(magic_pointer<TAttribute> atp,
				   magic_pointer<TAttribute>& data)
{
  magic_pointer<TAttribReal> f = get_real(atp);
  if( !!f )
  {
    return float(f->tValue);
  }
  return -1;
}

template <>
inline magic_pointer<TAttribute> get_attrib<float>()
{
  return magic_pointer<TAttribute>(new TAttribReal(0));
}

#endif /* !defined(TYPE_FUNCTIONS_H) */
