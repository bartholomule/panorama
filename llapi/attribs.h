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

#ifndef _ATTRIBUTES__
#define _ATTRIBUTES__

enum EAttribType
{

  FX_NONE,

  FX_INTEGER, // int       (iValue)
  FX_REAL,    // double    (dValue)
  FX_BOOL,    // bool      (gValue)
  FX_STRING,  // char*     (pvValue)
  FX_COLOR,   // &TColor   (pvValue)
  FX_VECTOR,  // &TVector  (pvValue)
  FX_VECTOR2, // &TVector2 (pvValue)

  // These next ones are for returning from something, to show a list of
  // possible options.  The results are read-only!!!  When making a selection,
  // send the value back as its normal type (without the _LIST).
  // They will be returned as a pointer to a vector of the type (pvValue).
  FX_INTEGER_LIST, // &vector<int>
  FX_REAL_LIST,    // &vector<TScalar>
  FX_BOOL_LIST,    // &vector<bool>
  FX_STRING_LIST,  // &vector<string>
  FX_COLOR_LIST,   // &vector<TColor>
  FX_VECTOR_LIST,  // &vector<TVector>
  FX_VECTOR2_LIST, // &vector<TVector2>

  FX_IMAGE,

  FX_BSDF,
  FX_CAMERA,
  FX_LIGHT,
  FX_PATTERN,
  FX_PERTURBATION,
  FX_MATERIAL,
  FX_RENDERER,
  FX_OBJECT,
  FX_AGGREGATE,
  FX_OBJECT_FILTER,
  FX_IMAGE_FILTER,
  FX_SCENE,
  FX_IMAGE_IO,
  
#if defined(NEW_ATTRIBUTES)
  FX_ARRAY = FX_IMAGE_IO + 1 // Requires new attributes
#endif
  
};  /* enum EAttribType */

#include <string>
using std::string;

#if defined(BROKEN_RETURN_SUBTYPES_ON_VIRTUAL)
// The compiler is BROKEN!  It does not recognize that returning a pointer to a
// subtype can be converted (virtually) to the base pointer (on singely
// derived, public subclasses). 
//
#define TATTRIB_CLONE_NEW_DEF(name) virtual TAttribute* clone_new() const { return new name(*this); }
#else
// Do it the right way!
#define TATTRIB_CLONE_NEW_DEF(name) virtual name* clone_new() const { return new name(*this); }
#endif /* defined(BROKEN_RETURN_SUBTYPES_ON_VIRTUAL) */


/*
  A base class (struct) for attribute values.
 */
struct TAttribute
{

  EAttribType   eType;

  TAttribute(): eType(FX_NONE) { }  
  TAttribute(EAttribType type): eType(type) { }
  virtual ~TAttribute() { }
  virtual string AttributeName() const { return "NONE"; }
  virtual string toString() const { return "NONE"; }

  TATTRIB_CLONE_NEW_DEF(TAttribute);
  
};  /* struct TAttribute */

#if !defined(NEW_ATTRIBUTES)
union NAttribute
{

  bool     gValue;
  double   dValue;
  int      iValue;
  void*    pvValue;

};  /* union NAttribute */
#else /* defined(NEW_ATTRIBUTES) */

#include "generic/magic_pointer.h"
typedef magic_pointer<TAttribute> NAttribute;

#endif /* defined(NEW_ATTRIBUTES) */


#endif  /* _ATTRIBUTES__ */
