/*
*  Copyright (C) 1998, 1999 Angel Jimenez Jimenez and Carlos Jimenez Moreno
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

#ifndef _CLASS_MANAGER__
#define _CLASS_MANAGER__

#include <string>
#include "llapi/base_class.h"
#include "llapi/class_mgr_base.h"

/*
  TODO: Add a 'deleteObject' function, or something similar, so that it will 
  be possible for a class to provide its own deallocation routines.  This is
  neccessary for windows-based DLLs, where if something is allocated from a
  DLL, it MUST be deallocated from the same DLL; No other part of the program
  can attempt to free up the memory.  This may be the case for other operating
  systems as well.  In any case, it would be a nice feature.
 */
class TClassManager : public TClassManagerBase
{
  public:

    static TBaseClass* _newObject (const string& rktCLASS, const TBaseClass* pktPARENT);

  TClassManager() { }
  virtual ~TClassManager() { }

  virtual TBaseClass* newObject( const string& classname, const TBaseClass* copy_source = NULL )
  {
    return TClassManager::_newObject(classname, copy_source);
  }

};  /* class TClassManager */

#endif  /* _CLASS_MANAGER__ */
