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

#ifndef _ATTRIBUTE__
#define _ATTRIBUTE__

#include <string>
#include "llapi/attribs.h"
#include "llapi/llapi_defs.h"

struct TAttribute
{

  EAttribType   eType;
  
};  /* struct TAttribute */


struct TAttribReal : public TAttribute
{

  TScalar   tValue;

  TAttribReal (void)
  {
    eType = FX_REAL;
  }
  
};  /* struct TAttribReal */


struct TAttribBool : public TAttribute
{

  bool   gValue;
  
  TAttribBool (void)
  {
    eType = FX_BOOL;
  }
  
};  /* struct TAttribBool */


struct TAttribString : public TAttribute
{

  string   tValue;
  
  TAttribString (void)
  {
    eType = FX_STRING;
  }
  
};  /* struct TAttribString */


struct TAttribColor : public TAttribute
{

  TColor   tValue;
  
  TAttribColor (void)
  {
    eType = FX_COLOR;
  }
  
};  /* struct TAttribColor */


struct TAttribVector : public TAttribute
{

  TVector   tValue;
  
  TAttribVector (void)
  {
    eType = FX_VECTOR;
  }
  
};  /* struct TAttribVector */


struct TAttribVector2 : public TAttribute
{

  TVector2   tValue;
  
  TAttribVector2 (void)
  {
    eType = FX_VECTOR2;
  }
  
};  /* struct TAttribVector2 */

#endif  /* _ATTRIBUTE__ */
