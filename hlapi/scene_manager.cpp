/*
*  Copyright (C) 1998, 1999, 2000 Angel Jimenez Jimenez
*                                 Carlos Jimenez Moreno
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

#include "llapi/warning_eliminator.h"
#include "hlapi/scene_manager.h"
#include "plugins/scene_io/rt/rt_io.h"
#include "plugins/scene_io/psl/psl_io.h"

TSceneFormatMap   TSceneManager::_tSceneFormatMap;

magic_pointer<TScene> TSceneManager::_load (const string& rktNAME, const string& rktFORMAT)
{

  magic_pointer<TScene> ptScene;// = NULL; by default
  TSceneIO* ptSceneIO = NULL;
  TCreateFunction* cf = NULL;

  if ( !_knownFormat (rktFORMAT) )
  {
    cerr << "ERROR: Scene format does not exist" << endl;
    return magic_pointer<TScene>(NULL);
  }
  
  cf = _tSceneFormatMap [rktFORMAT];
  if( cf )
  {
    ptSceneIO = (TSceneIO*)(cf(NULL));
    if( ptSceneIO )
    {
      ptScene = ptSceneIO->load (rktNAME);
    }
    delete ptSceneIO;
  }
  
  return ptScene;
  
}  /* _load() */


int TSceneManager::_save (const string& rktNAME, const string& rktFORMAT, const TScene* pktSCENE)
{

  int result = -1;
  TCreateFunction* cf = NULL;
  TSceneIO* ptSceneIO = NULL;

  if ( !_knownFormat (rktFORMAT) )
  {
    cerr << "ERROR: Scene format does not exist" << endl;
    return -1;
  }
  
  cf = _tSceneFormatMap [rktFORMAT];
  if( cf )
  {
    ptSceneIO = (TSceneIO*)(cf(NULL));
    if( ptSceneIO )
    {
      result = ptSceneIO->save (rktNAME, pktSCENE);
    }
    delete ptSceneIO;
  }
  
  return result;
  
}  /* _save() */


bool TSceneManager::_knownFormat (const string& rktNAME)
{

  return ( _tSceneFormatMap.find (rktNAME) != _tSceneFormatMap.end() );
    
}  /* _knownFormat() */


void TSceneManager::_addFormat (const string& rktNAME, TCreateFunction* pfCREATE )
{

  // [_TODO_] Check if this format is already registered.
  _tSceneFormatMap [rktNAME] = pfCREATE;

}  /* _addFormat() */


void TSceneManager::_initialize (void)
{

#if ( STATIC_LINK == 1 )
  _addFormat ("rt", &TSceneRT::_create);

#if ( EXPERIMENTAL == 1 )
  _addFormat ("psl", &TScenePsl::_create);
#endif

#endif
  
}  /* _initialize() */
