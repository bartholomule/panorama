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

#include "llapi/warning_eliminator.h"
#include "hlapi/scene_manager.h"
#include "parser_defs.h"
#include "rt_io.h"

DEFINE_SCENE_IO_PLUGIN ("rt", TSceneRT);

string    TSceneRT::_tInputFileName = "";
DWord     TSceneRT::_dwLineNumber   = 1L;
magic_pointer<TScene> TSceneRT::_ptParsedScene = magic_pointer<TScene>(NULL);

stack<TSceneRT::attrib_type> TSceneRT::_tDataStack;
TUserFunctionMap TSceneRT::_global_functions;
map<string, pair<string,TSceneRT::attrib_type> > TSceneRT::_tDataMap;
TSceneRT::BASE_OBJECT_TYPE   TSceneRT::_ptData;
TSceneRT::BASE_OBJECT_TYPE   TSceneRT::_ptParent;
magic_pointer<TAggregate>    TSceneRT::_ptWorld;
magic_pointer<TImageIO>      TSceneRT::_ptImageIO;  

#include <vector>
static std::vector<bool> condition_vector;
static bool condition_ok = true;

bool reduction_reporting;

#include "parser.hpp"

magic_pointer<TScene> TSceneRT::load (const string& rktNAME)
{

  int   iResult;

  _ptParsedScene  = (magic_pointer<TScene>)new TScene();
  _tInputFileName = rktNAME;
  
  rt_in = fopen (_tInputFileName.c_str(), "rb");

  if ( !rt_in )
  {
    GOM.error() << "ERROR: Could not open scene file." << std::endl;
    return (magic_pointer<TScene>)NULL;
  }

  //  rt_debug = 0;

  // [CHECKME!] Where do these really belong?
  // Set some values that need to be set somewhere... 
  condition_ok = true;
#if defined(REDUCTION_REPORTING)
  reduction_reporting = true;
#else
  reduction_reporting = false;
#endif
  
  RT_InitParser();

  yy::Parser rt_parser(true);
  
  iResult = rt_parser.parse();//rt_parse();

  RT_CloseParser();

  
  fclose (rt_in);
  
  if ( iResult != 0 )
  {
    _ptParsedScene = (magic_pointer<TScene>)NULL;    
    //    delete _ptParsedScene;
    return _ptParsedScene;
  }

  return _ptParsedScene;
  
}  /* _load() */


int TSceneRT::save (const string& rktNAME, const TScene* pktSCENE)
{

  return 0;
  
}  /* _save() */


void rt_enter_condition(bool condition)
{
  if( !condition )
  {
    condition_ok = false;
  }
  
  GOM.debug() << "rt_enter_condition(" << condition << ") level " << condition_vector.size() + 1 << " exec_ok=" << condition_ok << std::endl;
  
  condition_vector.push_back(condition);
}

void rt_leave_condition()
{
  if( !condition_vector.empty() )
  {
    // Remove the last element.
    condition_vector.pop_back();
    
    // Care must be taken when leaving to make sure that the conditions all add
    // up again. 
    bool cond = true;
    for( std::vector<bool>::iterator i = condition_vector.begin();
	 i != condition_vector.end();
	 ++i )
    {
      cond = cond && *i;
    }
    condition_ok = cond;
  }
  else
  {
    GOM.error() << "rt_leave_condition: Left more than entered!" << std::endl;
    condition_ok = true;
  }
  GOM.debug() << "rt_leave_condition(" << *condition_vector.rbegin() << ") level " << condition_vector.size() << " Recalculated condition=" << condition_ok << std::endl;
}

bool rt_exec_ok()
{
  GOM.debug() << "rt_exec_ok() returning " << condition_ok << std::endl;
  return condition_ok;
}
