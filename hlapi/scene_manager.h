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

#ifndef _SCENE_MANAGER__
#define _SCENE_MANAGER__

#include <string>
#include "hlapi/plugin_manager.h"
#include "llapi/scene.h"


#if 0
typedef TScene* (TSceneLoadFunction) (const string&);
typedef int (TSceneSaveFunction) (const string&, const TScene*);

struct TSceneFormatData
{

  TSceneLoadFunction*   pfLoad;
  TSceneSaveFunction*   pfSave;

};  /* struct TSceneFormatData */
#endif

typedef map<string, TCreateFunction*, less<string> > TSceneFormatMap;

class TSceneManager
{

  protected:

    static TSceneFormatMap   _tSceneFormatMap;

  public:

    static magic_pointer<TScene> _load (const string& rktNAME, const string& rktFORMAT);
    static int _save (const string& rktNAME, const string& rktFORMAT, const TScene* pktSCENE);
    static bool _knownFormat (const string& rktFORMAT);
    static void _addFormat (const string& rktNAME, TCreateFunction* pfLOAD);
    static void _initialize (void);
    
};  /* class TSceneManager */

#endif  /* _SCENE_MANAGER__ */
