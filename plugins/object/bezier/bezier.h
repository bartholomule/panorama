/*
*  Copyright (C) 1998, 1999 Matt Kimball
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

#ifndef _BEZIER__
#define _BEZIER__

#include <vector>
#include "llapi/object.h"
#include "hlapi/plugin_manager.h"

class TBezierSubsurface;

class TBezierSurface : public TObject
{

  friend class TBezierSubsurface;

  protected:

    std::vector<TBezierSubsurface*>   tSurfaceList;
    TBezierSubsurface*           ptCurrentSurface;
    int                          iBuildU, iBuildV;

  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TBezierSurface (void);
    ~TBezierSurface (void);

    bool findAllIntersections (const TRay& rktRAY, TSpanList& rtLIST) const;

    int setAttribute (const std::string& rktNAME, NAttribute nVALUE, 
                      EAttribType eTYPE);

    std::string className (void) const { return "BezierSurface"; }

};  /* class TBezierSurface */

#endif  /* _BEZIER__ */
