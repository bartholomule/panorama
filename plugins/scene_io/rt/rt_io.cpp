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

#include "hlapi/scene_manager.h"
#include "rt_io.h"

DEFINE_SCENE_IO_PLUGIN ("rt", TSceneRT);

string    TSceneRT::_tInputFileName = "";
DWord     TSceneRT::_dwLineNumber   = 1L;
TScene*   TSceneRT::_ptParsedScene  = NULL;

TScene* TSceneRT::_load (const string& rktNAME)
{

  int   iResult;

  _ptParsedScene  = new TScene();
  _tInputFileName = rktNAME;
  
  yyin = fopen (_tInputFileName.c_str(), "rb");

  if ( !yyin )
  {
    cerr << "ERROR: Could not open scene file." << endl;
    return NULL;
  }

  yydebug = 0;

  InitParser();
  
  iResult = yyparse();

  CloseParser();
  
  fclose (yyin);
  
  if ( iResult != 0 )
  {
    delete _ptParsedScene;
    return NULL;
  }

  return _ptParsedScene;
  
}  /* _load() */


int TSceneRT::_save (const string& rktNAME, const TScene* pktSCENE)
{

  return 0;
  
}  /* _save() */
