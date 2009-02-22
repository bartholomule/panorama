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
#include "llapi/outputmanager.h"

#include <iostream>
using std::cerr;

int TProgram::addVariable (const std::string& rktNAME, TVarReference tREF)
{

  TVariableMap::iterator   tIter = tVarList.find (rktNAME);

  if ( tIter == tVarList.end() )
  {
    tVarList [rktNAME] = tREF;

    return 0;
  }

  return -1;

}  /* addVariable() */


TEventCode* TProgram::getEventCode (const std::string& rktEVENT)
{

  TEventList::iterator   tIter = tEventList.find (rktEVENT);

  if ( tIter != tEventList.end() )
  {
    return &(tIter->second);
  }

  return NULL;

}  /* getEventCode() */


void TProgram::printDebug (const std::string& indent) const
{

  GOM.debug() << indent << "[_Program_]" << std::endl;

  std::string new_indent = TDebug::Indent(indent);
  
  GOM.debug() << new_indent << "Variables : " << std::endl;

  new_indent = TDebug::Indent(new_indent);

  for (TVariableMap::const_iterator iter = tVarList.begin(); ( iter != tVarList.end() ) ;iter++)
  {
    GOM.debug() << new_indent << "Name : " << (*iter).first << ", type : " << (int) (*iter).second->tAttrib.eType << std::endl;
  }
  
}  /* printDebug() */
