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

#ifndef _SUBDIVVERT__
#define _SUBDIVVERT__

#include <string>
#include <vector>
#include "llapi/llapi_all.h"

class TSubdivEdge;
class TSubdivFace;

class TSubdivVert
{
 
  protected:

    bool      gFoundNormal;
    TVector   tNormal;

    std::vector<TSubdivFace*>   tFaces;
    std::vector<TSubdivEdge*>   tEdges;
    TSubdivVert*           ptNextVert;

    void addNormalFrom (TVector& rtSUM, 
                        TSubdivEdge& rktFIRST, TSubdivEdge& rktSECOND) const;

  public:
    
    typedef std::vector<TSubdivFace*>::const_iterator   const_face_iterator;
    typedef std::vector<TSubdivEdge*>::const_iterator   const_edge_iterator;

    std::string    tName;
    TVector   tPosition;
    Byte      bRemainingDepth;

    TSubdivVert (const std::string& rktNAME, const TVector& rktPOSITION);

    void addFace (TSubdivFace* ptFACE);

    const_face_iterator beginFace() const;
    const_face_iterator endFace() const;

    void addEdge (TSubdivEdge* ptEDGE);

    const_edge_iterator beginEdge() const;
    const_edge_iterator endEdge() const;

    TVector      findNormal (const TSubdivFace& rktFACE);
    TSubdivVert* findPoint();

};  /*  class TSubdivVert  */

#endif  /* _SUBDIVVERT__ */
