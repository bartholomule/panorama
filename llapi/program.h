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

#ifndef _PROGRAM__
#define _PROGRAM__

#include <string>
#include <list>
#include <map>
#include "llapi/attribs.h"

struct TVariableData
{

  EAttribType   eType;
  NAttribute    nValue;
  
};  /* struct TVariableData */

typedef map<string, TVariableData, less<string> >   TVarList;

enum EInstructionCode
{

  RT_CODE_PUSH,
  RT_CODE_POP_OBJECT_VAR,
  RT_CODE_POP_GLOBAL_VAR

};  /* enum EInstructionCode */

struct TInstruction
{

  EInstructionCode   eCode;
  EAttribType        eType;
  NAttribute         nParam;
  
};  /* struct TInstruction */

typedef list<TInstruction>                       TEventCode;
typedef map<string, TEventCode, less<string> >   TEventList;

class TProgram
{

  protected:

    TVarList     tVarList;
    TEventList   tEventList;
  
  public:

    int addVariable (const string& rktNAME, EAttribType eTYPE, NAttribute nVALUE);

    TEventCode* getEventCode (const string& rktNAME);

    void printDebug (void) const;
    
};  /* class TProgram */

#endif  /* _PROGRAM__ */
