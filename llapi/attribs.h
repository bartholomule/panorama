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
  FX_IMAGE_FILTER

};  /* enum EAttribType */

union NAttribute
{

  bool     gValue;
  double   dValue;
  int      iValue;
  void*    pvValue;

};  /* union NAttribute */

#endif  /* _ATTRIBUTES__ */
