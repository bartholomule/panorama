/*
*  Copyright (C) 2003 Kevin Harris
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

#ifndef _CLASS_MGR_BASE__
#define _CLASS_MGR_BASE__

#include <string>
#include "llapi/base_class.h"

/*
  This is a class which can be used an instantiated, if neccessary, to create
  other classes.
 */
class TClassManagerBase
{
 public:
  TClassManagerBase() { }
  virtual ~TClassManagerBase() { }

  virtual TBaseClass* newObject( const string& classname, const TBaseClass* copy_source = NULL ) = 0;
};

/*
  Globals are nasty, but this allows a real separation between the LLAPI and
  the HLAPI libs. NOTE: it must be defined and allocated to an instance of
  TClassManager when the program is run.  If this doesn't happen, it won't
  link. 

  I may, at some point, want to put this variable in class_mgr_base.cpp, but
 I'm lazy right now, and just want to see if I can get a real library
 separation, so it can compile correctly as 'libtool' libraries.
 */
extern TClassManagerBase* GlobalClassManager;

#endif
