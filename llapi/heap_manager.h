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

#ifndef _HEAP_MANAGER__
#define _HEAP_MANAGER__

#include <list>
#include "llapi/attribute.h"

#define FX_REFERENCE_MAX    65535   // Reference count is defined as Word

struct TVariable
{

  TAttribute   tAttrib;
  Word         tReferenceCount;

  TVariable (const TAttribute& rktATTRIB)
  {
    tAttrib         = rktATTRIB;
    tReferenceCount = 0;
  }

};  /* struct TVariable */

typedef std::list<TVariable>      TVariableList;
typedef TVariableList::iterator   TVarReference;

class THeapManager
{

  protected:

    TVariableList   tHeap;

  public:

    TVarReference addVariable (EAttribType eType);
                               
};  /* class THeapManager */

extern THeapManager   tHeapManager;

#endif  /* _HEAP_MANAGER__ */
