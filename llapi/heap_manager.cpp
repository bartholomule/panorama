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

#include "llapi/heap_manager.h"

THeapManager   tHeapManager;

TVarReference THeapManager::addVariable (EAttribType eType)
{

  TVarReference   tRef;

  switch ( eType )
  {
    case FX_REAL:
    {
      tHeap.push_back (TVariable (TAttribReal()));
    }
    break;

    case FX_BOOL:
    {
      tHeap.push_back (TVariable (TAttribBool()));
    }
    break;

    case FX_STRING:
    {
      tHeap.push_back (TVariable (TAttribString()));
    }
    break;

    case FX_COLOR:
    {
      tHeap.push_back (TVariable (TAttribColor()));
    }
    break;

    case FX_VECTOR:
    {
      tHeap.push_back (TVariable (TAttribVector()));
    }
    break;

    case FX_VECTOR2:
    {
      tHeap.push_back (TVariable (TAttribVector2()));
    }
    break;

    default:
    {
      return tHeap.end();
    }
    break;
  }

  tRef = tHeap.end();
  tRef--;
  
  return tRef;

}  /* addVariable() */
