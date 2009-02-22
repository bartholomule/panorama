/*
*  Copyright (C) 1998 Matt Kimball
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

#ifndef _SUBDIV__
#define _SUBDIV__

#include <map>
#include <vector>
#include "llapi/object.h"
#include "hlapi/plugin_manager.h"

class TSubdivVert;
class TSubdivEdge;
class TSubdivFace;

class TSubdiv : public TObject
{
  friend class TSubdivFace;

  protected:

    std::map<std::string, TSubdivVert*>  tPoints;
    std::vector<TSubdivFace*>            tFaces;

    bool addVertex (const std::string& rktVALUE);
    bool addFace (const std::string& rktVALUE);

  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TSubdiv (void);
    ~TSubdiv (void);

    bool findAllIntersections (const TRay& rktRAY, TSpanList& rtLIST) const;

    int setAttribute (const std::string& rktNAME, NAttribute nVALUE, 
                      EAttribType eTYPE);

    std::string className (void) const { return "SubdivisionSurface"; }

};  /*  class TSubdiv  */

#endif  /* _SUBDIV__ */

