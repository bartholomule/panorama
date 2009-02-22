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

namespace panorama
{
  std::string TSpanList::internalMembers(const Indentation& indent,
    StringDumpable::PrefixType prefix) const;
  {
    std::string tag = indent.level();
    if( prefix == E_PREFIX_CLASSNAME )
    {
      tag = indent.level() + TSpanList::name() + "::";
    }

    Indentation nextIndent = indent.nextLevel();
    std::string retval;

    if( !empty() )
    {
      for (TSpanList::const_iterator tIter = begin(); ( tIter != end() ) ;tIter++)
      {
        retval += tag + string_format("%1=%2\n", tIter->first, toString(tIter->second, nextIndent, prefix));
      }
    }
    else
    {
      retval = "EMPTY";
    }
    return retval;
  }

  std::string TSpanList::name() const
  {
    return "SpanList";
  }
} // namespace panroama
