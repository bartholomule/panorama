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

#ifndef _RT_IO__
#define _RT_IO__

#include "llapi/object_required.h"
#include "llapi/scene.h"
#include "llapi/scene_io.h"
#include "hlapi/plugin_manager.h"
#include <stack>

class TSceneRT : public TSceneIO
{

public:
  
  static TBaseClass* _create (const TBaseClass* pktPARENT);
  
  static string    _tInputFileName;
  static DWord     _dwLineNumber;
  static magic_pointer<TScene> _ptParsedScene;

  typedef magic_pointer<TBaseClass> BASE_OBJECT_TYPE;
  typedef magic_pointer<TAttribute> attrib_type;
  static stack<attrib_type> _tDataStack;
  static TUserFunctionMap _global_functions;
  static map<string, pair<string,attrib_type> > _tDataMap;

  static BASE_OBJECT_TYPE   _ptData;
  static BASE_OBJECT_TYPE   _ptParent;
  static magic_pointer<TAggregate> _ptWorld;
  static magic_pointer<TImageIO> _ptImageIO;  
  
  virtual int save (const string& rktNAME, const TScene* pktSCENE);
  virtual magic_pointer<TScene> load (const string& rktNAME);
  virtual string className() const { return "scenert"; }
  virtual TSceneRT* clone_new() const { return new TSceneRT(*this); }
  
};  /* class TSceneRT */

#endif  /* _RT_IO__ */


