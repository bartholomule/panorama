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

#ifndef _BEZIER_SUB__
#define _BEZIER_SUB__

#include "llapi/llapi_defs.h"
#include "llapi/bounding_box.h"
#include "llapi/ray.h"
#include "llapi/span_list.h"

class TBezierSurface;

class TBezierSubsurface
{

  protected:

    Byte   bEdgeSubdivisionDepth[4];
    Byte   bPatchSubdivisionDepth;
    bool   gSubdivided;

    TBezierSubsurface*   ptAncestor;
    TVector2             tParametricPos;
    TVector2             tParametricVecU, tParametricVecV;

    TBezierSubsurface*   aptChildren[4];
    TVector              atControlPoints[4][4];
    TBoundingBox         tBoundingBox;
    bool                 gBoundingBoxCurrent;
    TBezierSurface*      ptObject;

    static bool _findTriangleIntersection (const TRay& rktRAY,
                                           const TVector& rktVECA,
                                           const TVector& rktVECB,
                                           const TVector& rktVECC,
                                           TScalar& T,
                                           TScalar& U,
					   TScalar& V);

    static TScalar _lineDistance (const TVector& tPOINT,
                                  const TVector& tBEGIN, const TVector& tEND);
  
    static Byte _curveSubdivisionDepth (const TVector& C0,
                                        const TVector& C1,
                                        const TVector& C2,
                                        const TVector& C3);

    void subpatch (TVector& C0, TVector& C1, TVector& C2, TVector& C3,
                   TVector& C4, TVector& C5, TVector& C6, TVector& C7,
                   TVector& C8, TVector& C9, TVector& C10, TVector& C11,
                   TVector& C12, TVector& C13, TVector& C14, TVector& C15,
                   bool gSubdivideTop, bool gSubdivideLeft);

    void findBoundingBox (void);

    void subdivide (void);

    TVector getTangentS (const TVector2 &rktPOS);
    TVector getTangentT (const TVector2 &rktPOS);

   bool findFlatIntersection (const TRay& rktRAY, const TScalar& rktSCALE,
                              const TRay& rktORIG_RAY, 
                              TSpanList& rtLIST,
                              const TVector& rktVECA, const TVector2& rktPOSA,
                              const TVector& rktVECB, const TVector2& rktPOSB,
                              const TVector& rktVECC, const TVector2& rktPOSC);
    bool findFlatIntersection (const TRay& rktRAY, const TScalar& rktSCALE,
                               const TRay& rktORIG_RAY, 
                               TSpanList& rtLIST);

  public:

    TBezierSubsurface (TBezierSurface* ptOBJECT);
    ~TBezierSubsurface (void);
  
    TVector getPoint (Byte S, Byte T);
    void setPoint (Byte S, Byte T, const TVector& rktVECT);

    void calculateSubdivisionDepth (void);

    bool findAllIntersections (const TRay& rktRAY, const TScalar& rktSCALE,
                               const TRay& rktORIG_RAY, 
                               TSpanList& rtLIST);

};  /* class TBezierSurface */

#endif  /* _BEZIER_SUB__ */

