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

#ifndef _BASE_CLASS__
#define _BASE_CLASS__

#include <map>
#include <string>
#include "llapi/debug.h"

#define FX_ATTRIB_OK             0
#define FX_ATTRIB_WRONG_PARAM   -1
#define FX_ATTRIB_WRONG_TYPE    -2
#define FX_ATTRIB_WRONG_VALUE   -3
#define FX_ATTRIB_USER_ERROR     1

enum EClass
{

  FX_COLOR_CLASS,
  FX_MATERIAL_CLASS,
  FX_FRAME_CLASS,
  FX_IMAGE_CLASS,
  FX_SCENE_CLASS,
  FX_LIGHT_CLASS,
  FX_CAMERA_CLASS,
  FX_OBJECT_CLASS,
  FX_AGGREGATE_CLASS,
  FX_IMAGE_FILTER_CLASS,
  FX_RENDERER_CLASS,
  FX_BSDF_CLASS,
  FX_OBJECT_FILTER_CLASS,
  FX_BOUNDING_BOX_CLASS,
  FX_ATM_OBJECT_CLASS,
  FX_IMAGE_IO_CLASS

};  /* enum EClass */


enum EAttribType
{

  FX_NONE,

  FX_REAL,
  FX_BOOL,
  FX_STRING,
  FX_COLOR,
  FX_VECTOR,
  FX_VECTOR2,

  FX_IMAGE,

  FX_BSDF,
  FX_CAMERA,
  FX_LIGHT,
  FX_MATERIAL,
  FX_RENDERER,
  FX_OBJECT,
  FX_AGGREGATE,
  FX_OBJECT_FILTER,
  FX_IMAGE_FILTER

};  /* enum EAttribType */

typedef map<string, EAttribType, less<string> >   TAttributeList;

union NAttribute
{

  bool     gValue;
  double   dValue;
  void*    pvValue;

};  /* union NAttribute */


class TBaseClass
{

  public:

    static string _tUserErrorMessage;

    static string classTypeString (EClass eCLASS);
      
    virtual ~TBaseClass (void) {}
    
    virtual int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
    {
      return FX_ATTRIB_WRONG_PARAM;
    }
    virtual int getAttribute (const string& rktNAME, NAttribute& rnVALUE)
    {
      return FX_ATTRIB_WRONG_PARAM;
    }
    virtual void getAttributeList (TAttributeList& rtLIST) const {}

    virtual void printDebug (void) const {};

    virtual EClass classType (void) const = 0;
    virtual string className (void) const = 0;

};  /* class TBaseClass */

#endif  /* _BASE_CLASS__ */
