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

#ifndef _PROCEDURAL__
#define _PROCEDURAL__

#include "llapi/base_class.h"
#include "llapi/program.h"

#define FX_ATTRIB_OK             0
#define FX_ATTRIB_WRONG_PARAM   -1
#define FX_ATTRIB_WRONG_TYPE    -2
#define FX_ATTRIB_WRONG_VALUE   -3
#define FX_ATTRIB_USER_ERROR     1

typedef map<string, EAttribType, less<string> >   TAttributeList;

class TProcedural : public TBaseClass
{

  protected:

    TProgram   tProgram;
    
  public:

    static string _tUserErrorMessage;

    virtual int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
    {
      return FX_ATTRIB_WRONG_PARAM;
    }
    virtual int getAttribute (const string& rktNAME, NAttribute& rnVALUE)
    {
      return FX_ATTRIB_WRONG_PARAM;
    }
    virtual void getAttributeList (TAttributeList& rtLIST) const {}

    void sendEvent (const string& rktEVENT);
    void sendEvent (const string& rktEVENT, NAttribute nAttrib);

    TProgram* program (void) { return &tProgram; }
    
};  /* class TProcedural */

#endif  /* _PROCEDURAL__ */
