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

#include "hlapi/scene_manager.h"
#include "plugins/scene_io/rt/rt_io.h"

TSceneFormatMap   TSceneManager::_tSceneFormatMap;

TScene* TSceneManager::_load (const string& rktNAME, const string& rktFORMAT)
{

  TSceneFormatData*     ptData;
  TSceneLoadFunction*   pfLoad;

  if ( !_knownFormat (rktFORMAT) )
  {
    cerr << "ERROR: Scene format does not exist" << endl;
    return NULL;
  }

  ptData = _tSceneFormatMap [rktFORMAT];
  pfLoad = ptData->pfLoad;

  return ((*pfLoad) (rktNAME));
  
}  /* _load() */


int TSceneManager::_save (const string& rktNAME, const string& rktFORMAT, const TScene* pktSCENE)
{

  TSceneFormatData*     ptData;
  TSceneSaveFunction*   pfSave;

  if ( !_knownFormat (rktFORMAT) )
  {
    return -1;
  }
  
  ptData = _tSceneFormatMap [rktFORMAT];
  pfSave = ptData->pfSave;

  return ((*pfSave) (rktNAME, pktSCENE));
  
}  /* _save() */


bool TSceneManager::_knownFormat (const string& rktNAME)
{

  return ( _tSceneFormatMap.find (rktNAME) != _tSceneFormatMap.end() );
    
}  /* _knownFormat() */


void TSceneManager::_addFormat (const string& rktNAME, TSceneLoadFunction* pfLOAD, TSceneSaveFunction* pfSAVE)
{

  TSceneFormatData*   ptData;

  // [_TODO_] Check if this format is already registered.
  ptData                     = new TSceneFormatData;
  ptData->pfLoad             = pfLOAD;
  ptData->pfSave             = pfSAVE;
  _tSceneFormatMap [rktNAME] = ptData;

}  /* _addFormat() */


void TSceneManager::_initialize (void)
{

#if ( STATIC_LINK == 1 )
  _addFormat ("rt", &TSceneRT::_load, &TSceneRT::_save);
#endif
  
}  /* _initialize() */
