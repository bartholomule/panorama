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

#ifndef _DEBUG__
#define _DEBUG__

#include "llapi/machine.h"
#include <string>

class TDebug
{

  private:

    static char   _acIndent[];
    static Byte   _bMaxIndent;
    static Byte   _bIndentLevel;
    static Byte   _bIndentStep;

  public:

    static void _push (void)
    {
      if ( (_bIndentLevel + _bIndentStep) <= _bMaxIndent )
      {
        _bIndentLevel            += _bIndentStep;
        _acIndent [_bIndentLevel] = '\0';
      }
    }
    
    static void _pop (void)
    {
      if ( _bIndentLevel > _bIndentStep )
      {
        _acIndent [_bIndentLevel] = ' ';
        _bIndentLevel            -= _bIndentStep;
      }
    }
  
    static const char* _indent (void)
    {
      return _acIndent;
    }

  static std::string StandardIndent();


    static std::string Indent(const std::string& indent)
    {
      return indent + StandardIndent();
    }
    
};  /* class TDebug */

#endif  /* _DEBUG__ */

