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

#include "llapi/warning_eliminator.h"
#include "llapi/span_list.h"

void TSpanList::printDebug (void) const
{

  cerr << TDebug::_indent() << "[_SpanList_]" << endl;

  TDebug::_push();

  for (TSpanList::const_iterator tIter = begin(); ( tIter != end() ) ;tIter++)
  {
    (*tIter).second.printDebug();
  }

  TDebug::_pop();
  
}  /* printDebug() */
