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

#ifndef _SUBDIVFACE__
#define _SUBDIVFACE__

#include <vector>
#include "llapi/llapi_all.h"

class TSubdiv;
class TSubdivVert;
class TSubdivEdge;

class TSubdivFace
{

    bool                              gSubdivided, gFinal, gFoundBoundingBox;
    TBoundingBox                      tBoundingBox;
    std::vector<TSubdivVert*>              tVerts;
    std::map<TSubdivVert*, TSubdivFace*>   tGeneratedFaces;
    std::vector<TSubdivFace*>              tFaces;
    TSubdivVert*                      ptFacePoint;

    TSubdivFace*   ptParent;

    void _addToBox(TVector& rtMIN, TVector& rtMAX, const TVector& rktVEC);

    static bool _findTriangleIntersection (const TRay& rktRAY,
                                           const TVector& rktVECA,
                                           const TVector& rktVECB,
                                           const TVector& rktVECC,
                                           TScalar& T,
                                           TScalar& U,
                                           TScalar& V);

    bool determineFinality() const;

    bool findBoundingBoxFromChildren();
    void findBoundingBoxFromPoints();
    void findBoundingBox();

    void generateFace (TSubdivVert* ptVERT);
    void subdivide();

    TVector findNormal (TSubdivVert* ptBASE, TSubdivVert* ptVERTU,
                        TSubdivVert* ptVERTV,
                        TScalar U, TScalar V) const;

    bool findLocalIntersections (const TSubdiv& rktSUBDIV, 
                                 const TRay& rktORIGRAY, 
                                 const TScalar& rktSCALE,
                                 const TRay& rktRAY, TSpanList& rtLIST) const;

  public:
 
    TSubdivFace (const std::vector<TSubdivVert*>& rktVERTLIST);

    bool findAllIntersections (const TSubdiv& rktSUBDIV, 
                               const TRay& rktORIGRAY, 
                               const TScalar& rktSCALE,
                               const TRay& rktRAY, TSpanList& rtLIST);

    TSubdivVert* findPoint();
 
    TSubdivEdge* edgeBefore (TSubdivVert* ptVERT) const;
    TSubdivEdge* edgeAfter (TSubdivVert* ptVERT) const;
    TSubdivEdge* otherEdge (TSubdivVert* ptVERT, TSubdivEdge* ptEDGE) const;

};  /*  class TSubdivFace  */

#endif  /* _SUBDIVFACE__ */
