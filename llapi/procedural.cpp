/*
*  Copyright (C) 1999 Angel Jimenez Jimenez
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

#include "llapi/procedural.h"

string   TProcedural::_tUserErrorMessage = "";

void TProcedural::sendEvent (const string& rktEVENT)
{

  cout << "Object <" << className() << "> send event <" << rktEVENT << ">" << endl;

}  /* sendEvent() */


void TProcedural::sendEvent (const string& rktEVENT, NAttribute nAttrib)
{

  cout << "Object <" << className() << "> send event <" << rktEVENT << "> with argument" << endl;

}  /* sendEvent() */