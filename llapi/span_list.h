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

#ifndef _SPAN_LIST__
#define _SPAN_LIST__

#include <map>
#include "llapi/surface_data.h"

class TSpanList : public map<TScalar, TSurfaceData, less <TScalar> >
{

  public:

    void add (const TSurfaceData& rktDATA)
    {
      (*this) [rktDATA.distance()] = rktDATA;
    }

    TSurfaceData first (void) const
    {
      TSpanList::const_iterator   tIter = begin();

      return (*tIter).second;
    }

    TSurfaceData last (void) const
    {
      TSpanList::const_iterator   tIter = end();

      tIter--;
      return (*tIter).second;
    }

    void printDebug (void) const;
    
};  /* class TSpanList */

#endif  /* _SPAN_LIST__ */
