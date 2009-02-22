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

#include "hlapi/scene_manager.h"
#include "parser_defs.h"
#include "psl_io.h"

DEFINE_SCENE_IO_PLUGIN ("psl", TScenePsl);

string    TScenePsl::_tInputFileName = "";
DWord     TScenePsl::_dwLineNumber   = 1L;
TScene*   TScenePsl::_ptParsedScene  = NULL;

TScene* TScenePsl::_load (const std::string& rktNAME)
{

  int   iResult;

  _ptParsedScene  = new TScene();
  _tInputFileName = rktNAME;

  psl_in = fopen (_tInputFileName.c_str(), "rb");

  if ( !psl_in )
  {
    GOM.error() << "ERROR: Could not open scene file." << std::endl;
    return NULL;
  }

  psl_debug = 0;

  PSL_InitParser();

  iResult = psl_parse();
  
  PSL_CloseParser();
  
  fclose (psl_in);
  
  if ( iResult != 0 )
  {
    delete _ptParsedScene;
    return NULL;
  }

  return _ptParsedScene;
  
}  /* _load() */


int TScenePsl::_save (const std::string& rktNAME, const TScene* pktSCENE)
{

  return 0;
  
}  /* _save() */
