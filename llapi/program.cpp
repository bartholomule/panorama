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

#include <string>
#include "llapi/debug.h"
#include "llapi/program.h"

int TProgram::addVariable (const string& rktNAME, TVarReference tREF)
{

  TVariableMap::iterator   tIter = tVarList.find (rktNAME);

  if ( tIter == tVarList.end() )
  {
    tVarList [rktNAME] = tREF;

    return 0;
  }

  return -1;

}  /* addVariable() */


TEventCode* TProgram::getEventCode (const string& rktEVENT)
{

  TEventList::iterator   tIter = tEventList.find (rktEVENT);

  if ( tIter != tEventList.end() )
  {
    return &(tIter->second);
  }

  return NULL;

}  /* getEventCode() */


void TProgram::printDebug (void) const
{

  cerr << TDebug::_indent() << "[_Program_]" << endl;

  TDebug::_push();
  
  cerr << TDebug::_indent() << "Variables : " << endl;

  TDebug::_push();

  for (TVariableMap::const_iterator iter = tVarList.begin(); ( iter != tVarList.end() ) ;iter++)
  {
    cerr << TDebug::_indent() << "Name : " << (*iter).first << ", type : " << (int) (*iter).second->tAttrib.eType << endl;
  }
  
  TDebug::_pop();

  TDebug::_pop();

}  /* printDebug() */
