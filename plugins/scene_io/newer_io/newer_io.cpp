/*
*  Copyright (C) 1998, 1999, 2000 Angel Jimenez Jimenez and Carlos Jimenez Moreno
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

#include <cstdio>
#include "hlapi/scene_manager.h"
#include "newer_io.h"
#include "symtab.h"

DEFINE_SCENE_IO_PLUGIN ("newer", TSceneNEWER);

extern FILE* yyin;

string    TSceneNEWER::_tInputFileName = "";
DWord     TSceneNEWER::_dwLineNumber   = 1L;
TScene*   TSceneNEWER::_ptParsedScene  = NULL;

extern int yyparse();

TScene* TSceneNEWER::_load (const string& rktNAME)
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

  //  newer_debug = 0;

  //  NEWER_InitParser();
  init_symtab();
  
  iResult = yyparse();

  //  NEWER_CloseParser();
  
  fclose (yyin);
  
  fprintf(stderr,"\n\n\n%s: Not done with the useful stuff... bailing...\n",__PRETTY_FUNCTION__);
  exit(1);

  if ( iResult != 0 )
  {
    delete _ptParsedScene;
    return NULL;
  }

  return _ptParsedScene;
  
}  /* _load() */


int TSceneNEWER::_save (const string& rktNAME, const TScene* pktSCENE)
{

  return 0;
  
}  /* _save() */


