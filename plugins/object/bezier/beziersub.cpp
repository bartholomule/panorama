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

#include "bezier.h"
#include "beziersub.h"

#define MAX_DEVIATION   1e-2

bool TBezierSubsurface::_findTriangleIntersection (const TRay& rktRAY,
                                                   const TVector& rktVECA,
                                                   const TVector& rktVECB,
                                                   const TVector& rktVECC,
                                                   TScalar& T,
                                                   TScalar& U,
						   TScalar& V)
{

  TScalar   IX, IY, IZ;
  TScalar   JX, JY, JZ;
  TScalar   KX, KY, KZ;
  TScalar   LX, LY, LZ;
  TVector   tBase, tDir;
  TScalar   tDet;

  tBase = rktRAY.location();
  tDir  = rktRAY.direction();

  IX = tDir[0];
  IY = tDir[1];
  IZ = tDir[2];

  JX = rktVECA[0] - rktVECB[0];
  JY = rktVECA[1] - rktVECB[1];
  JZ = rktVECA[2] - rktVECB[2];

  KX = rktVECA[0] - rktVECC[0];
  KY = rktVECA[1] - rktVECC[1];
  KZ = rktVECA[2] - rktVECC[2];

  LX = rktVECA[0] - tBase[0];
  LY = rktVECA[1] - tBase[1];
  LZ = rktVECA[2] - tBase[2];

  //
  //  | IX JX KX |   | T |   | LX |
  //  | IY JY KY | * | U | = | LY |
  //  | IZ JZ KZ |   | V |   | LZ |
  //
  //  Now, solving by Cramer's rule...
  //

  T = LX * JY * KZ - LX * KY * JZ + 
      JX * KY * LZ - JX * LY * KZ +
      KX * LY * JZ - KX * JY * LZ;
  U = IX * LY * KZ - IX * KY * LZ + 
      LX * KY * IZ - LX * IY * KZ +
      KX * IY * LZ - KX * LY * IZ;
  V = IX * JY * LZ - IX * LY * JZ + 
      JX * LY * IZ - JX * IY * LZ +
      LX * IY * JZ - LX * JY * IZ;

  tDet = IX * JY * KZ - IX * KY * JZ + 
         JX * KY * IZ - JX * IY * KZ +
         KX * IY * JZ - KX * JY * IZ;

  if ( fabs (tDet) < FX_EPSILON )
  {
    return false;
  }

  tDet = 1.0 / tDet;  

  T *= tDet;
  U *= tDet;
  V *= tDet;

  if ( ( U < 0.0 )  || ( V < 0.0 ) || ( V + U > 1.0 ) )
  {
    return false;
  }

  return true;

}  /* _findTriangleIntersection() */


//
//  Calculate the distance of a point from a line segment as a fraction
//  of the total length of the line segment.
//
TScalar TBezierSubsurface::_lineDistance (const TVector& tPOINT,
                                          const TVector& tBEGIN, 
                                          const TVector& tEND)
{
  TScalar tDist, tPos, tSegLen;
  TVector tSeg, tPt;

  tSeg    = tEND - tBEGIN;
  tSegLen = tSeg.norm();
  tPt     = tPOINT - tBEGIN;

  if(tSegLen < FX_EPSILON && tPt.norm() < FX_EPSILON)
  {
    return 0.0;
  }

  tPos = dotProduct(tPOINT - tBEGIN, tSeg) / (tSegLen * tSegLen);

  tPos = tPos > 1.0 ? 1.0 : tPos;
  tPos = tPos < 0.0 ? 0.0 : tPos;

  tDist = (tPOINT - (tBEGIN + tPos * tSeg)).norm();

  return tDist;

}  /*  _lineDistance()  */



//
//  Calculate the subdivision depth required to find a good representation
//  of this particular cubic Bezier curve.  Each subdivision level cuts
//  the curve in half.
//
Byte TBezierSubsurface::_curveSubdivisionDepth (const TVector& C0,
                                                const TVector& C1,
                                                const TVector& C2,
                                                const TVector& C3)
{
  Byte bDepth, bSecondDepth;
  bool gCloseEnough;

  gCloseEnough = true;

  if ( _lineDistance (C1, C0, C3) <= MAX_DEVIATION 
       && _lineDistance (C2, C0, C3) <= MAX_DEVIATION )
  {
    return 0;
  }

  bDepth = _curveSubdivisionDepth (C0, 
                                   0.5 * C0 + 0.5 * C1,
                                   0.25 * C0 + 2.0 * 0.25 * C1 + 0.25 * C2,
                                   0.125 * C0 + 3.0 * 0.125 * C1 
                                   + 3.0 * 0.125 * C2 + 0.125 * C3);

  bSecondDepth = _curveSubdivisionDepth (0.125 * C0 + 3.0 * 0.125 * C1
                                         + 3.0 * 0.125 * C2 + 0.125 * C3,
                                         0.25 * C1 + 2.0 * 0.25 * C2
                                         + 0.25 * C3,
                                         0.5 * C2 + 0.5 * C3,
                                         C3);
  if ( bSecondDepth > bDepth )
  {
    bDepth = bSecondDepth;
  }

  if ( bDepth == 255 )
  {
    return bDepth;
  }
  return bDepth + 1;

}  /* _curveSubdivisionDepth() */

TBezierSubsurface::TBezierSubsurface (TBezierSurface* ptOBJECT)
{

  ptObject = ptOBJECT;

  gBoundingBoxCurrent    = false;
  gSubdivided            = false;
  bPatchSubdivisionDepth = 0;
  ptAncestor             = this;
  tParametricPos         = TVector2(0.0, 0.0);
  tParametricVecU        = TVector2(1.0, 0.0);
  tParametricVecV        = TVector2(0.0, 1.0);

  for (Byte N = 0; ( N < 4 ) ;N++)
  {
    aptChildren[N]           = NULL;
    bEdgeSubdivisionDepth[N] = 0;
  }

  for (Byte N = 0; ( N < 4 ) ;N++)
  {
    for(Byte M = 0; ( M < 4 ) ;M++)
    {
      atControlPoints[N][M][0] = 0.0;
      atControlPoints[N][M][1] = 0.0;
      atControlPoints[N][M][2] = 0.0;
    }
  }

}  /* TBezierSubsurface() */


TBezierSubsurface::~TBezierSubsurface (void)
{

  for (Byte N = 0; (N < 4) ;N++)
  {
    delete aptChildren[N];
  }

}  /* ~TBezierSubsurface() */


TVector TBezierSubsurface::getPoint (Byte S, Byte T)
{

  assert ( ( S < 4 ) && ( T < 4 ) );

  return atControlPoints[S][T];

}  /* getPoint() */


void TBezierSubsurface::setPoint (Byte S, Byte T, const TVector& rktVECT)
{

  assert ( ( S < 4 ) && ( T < 4 ) );

  atControlPoints[S][T] = rktVECT;

  //
  //  Since one of the control points changed, we need to reset some
  //  things we may have precomputed about this patch.
  //
  gBoundingBoxCurrent = false;

  if ( gSubdivided )
  {
    for (Byte N = 0; ( N < 4 ) ; N++)
    {
      delete aptChildren[N];
      aptChildren[N] = NULL;
    }
    gSubdivided = false;
  }

}  /* setPoint() */

//
//  Compute our control points as the patch which makes up the 
//  upper-left corner of the patch defined by the given control
//  points.  (That is, the patch from [0.0, 0.0] to [0.5, 0.5].)
//
void TBezierSubsurface::subpatch (TVector& C0, TVector& C1, 
                                  TVector& C2, TVector& C3,
                                  TVector& C4, TVector& C5,
                                  TVector& C6, TVector& C7,
                                  TVector& C8, TVector& C9,
                                  TVector& C10, TVector& C11,
                                  TVector& C12, TVector& C13,
                                  TVector& C14, TVector& C15,
                                  bool gSubdivideTop, bool gSubdivideLeft)
{
  atControlPoints[0][0] = C0;
  if ( gSubdivideTop )
  {
    atControlPoints[1][0] = 0.5 * C0 + 0.5 * C1;
    atControlPoints[2][0] = 0.25 * C0 + 2.0 * 0.25 * C1 + 0.25 * C2;
    atControlPoints[3][0] = 0.125 * C0 + 3.0 * 0.125 * C1 + 
                            3.0 * 0.125 * C2 + 0.125 * C3;
  }
  else
  {
    atControlPoints[1][0] = 5.0 / 6.0 * C0 + 1.0 / 6.0 * C3;
    atControlPoints[2][0] = 4.0 / 6.0 * C0 + 2.0 / 6.0 * C3;
    atControlPoints[3][0] = 1.0 / 2.0 * C0 + 1.0 / 2.0 * C3;
  }

  if ( gSubdivideLeft )
  {
    atControlPoints[0][1] = 0.5 * C0 + 0.5 * C4;
  }
  else
  {
    atControlPoints[0][1] = 5.0 / 6.0 * C0 + 1.0 / 6.0 * C12;
  }
  atControlPoints[1][1] = 0.5 * (0.5 * C0 + 0.5 * C1) +
                          0.5 * (0.5 * C4 + 0.5 * C5);
  atControlPoints[2][1] = 0.5 * (0.25 * C0 + 2.0 * 0.25 * C1 + 0.25 * C2) +
                          0.5 * (0.25 * C4 + 2.0 * 0.25 * C5 + 0.25 * C6);
  atControlPoints[3][1] = 0.5 * (0.125 * C0 + 3.0 * 0.125 * C1 + 
                                 3.0 * 0.125 * C2 + 0.125 * C3) +
                          0.5 * (0.125 * C4 + 3.0 * 0.125 * C5 + 
                                 3.0 * 0.125 * C6 + 0.125 * C7);

  if ( gSubdivideLeft )
  {
    atControlPoints[0][2] = 0.25 * C0 + 2.0 * 0.25 * C4 + 0.25 * C8;
  }
  else
  {
    atControlPoints[0][2] = 4.0 / 6.0 * C0 + 2.0 / 6.0 * C12;
  }
  atControlPoints[1][2] = 0.25 * (0.5 * C0 + 0.5 * C1) +
                          2.0 * 0.25 * (0.5 * C4 + 0.5 * C5) +
                          0.25 * (0.5 * C8 + 0.5 * C9);
  atControlPoints[2][2] = 0.25 * (0.25 * C0 + 2.0 * 0.25 * C1 + 0.25 * C2) +
                          2.0 * 0.25 * (0.25 * C4 + 2.0 * 0.25 * C5 + 0.25 * C6) +
                          0.25 * (0.25 * C8 + 2.0 * 0.25 * C9 + 0.25 * C10);
  atControlPoints[3][2] = 0.25 * (0.125 * C0 + 3.0 * 0.125 * C1 + 
                                  3.0 * 0.125 * C2 + 0.125 * C3) +
                          2.0 * 0.25 * (0.125 * C4 + 3.0 * 0.125 * C5 +
                                      3.0 * 0.125 * C6 + 0.125 * C7) +
                          0.25 * (0.125 * C8 + 3.0 * 0.125 * C9 + 
                                  3.0 * 0.125 * C10 + 0.125 * C11);

  if ( gSubdivideLeft )
  {
    atControlPoints[0][3] = 0.125 * C0 + 3.0 * 0.125 * C4 + 
                            3.0 * 0.125 * C8 + 0.125 * C12;
  }
  else
  {
    atControlPoints[0][3] = 1.0 / 2.0 * C0 + 1.0 / 2.0 * C12;
  }
  atControlPoints[1][3] = 0.125 * (0.5 * C0 + 0.5 * C1) +
                          3.0 * 0.125 * (0.5 * C4 + 0.5 * C5) +
                          3.0 * 0.125 * (0.5 * C8 + 0.5 * C9) +
                          0.125 * (0.5 * C12 + 0.5 * C13);
  atControlPoints[2][3] = 0.125 * (0.25 * C0 + 2.0 * 0.25 * C1 + 0.25 * C2) +
                          3.0 * 0.125 * (0.25 * C4 + 2.0 * 0.25 * C5 + 0.25 * C6) +
                          3.0 * 0.125 * (0.25 * C8 + 2.0 * 0.25 * C9 + 0.25 * C10) +
                          0.125 * (0.25 * C12 + 2.0 * 0.25 * C13 + 0.25 * C14);
  atControlPoints[3][3] = 0.125 * (0.125 * C0 + 3.0 * 0.125 * C1 +
                                   3.0 * 0.125 * C2 + 0.125 * C3) +
                          3.0 * 0.125 * (0.125 * C4 + 3.0 * 0.125 * C5 +
                                       3.0 * 0.125 * C6 + 0.125 * C7) +
                          3.0 * 0.125 * (0.125 * C8 + 3.0 * 0.125 * C9 +
                                       3.0 * 0.125 * C10 + 0.125 * C11) +
                          0.125 * (0.125 * C12 + 3.0 * 0.125 * C13 + 
                                   3.0 * 0.125 * C14 + 0.125 * C15);

}  /* subpatch() */
                                  

//
//  When we need a bounding box, we will simple find the bounding box which
//  will contain all of our control points.  
// 
void TBezierSubsurface::findBoundingBox (void)
{

  TVector   tMin, tMax;

  if ( gBoundingBoxCurrent )
  {
    return;
  }

  tMin = atControlPoints[0][0];
  tMax = atControlPoints[0][0];

  for (Byte N = 0; ( N < 4 ) ;N++)
  {
    for (Byte M = 0; ( M < 4 ) ;M++)
    {
      if ( atControlPoints[N][M][0] < tMin[0] )
      {
        tMin[0] = atControlPoints[N][M][0];
      }
      if ( atControlPoints[N][M][0] > tMax[0] )
      {
        tMax[0] = atControlPoints[N][M][0];
      }

      if ( atControlPoints[N][M][1] < tMin[1] )
      {	
        tMin[1] = atControlPoints[N][M][1];
      }
      if ( atControlPoints[N][M][1] > tMax[1] )
      {
        tMax[1] = atControlPoints[N][M][1];
      }

      if ( atControlPoints[N][M][2] < tMin[2] )
      {
        tMin[2] = atControlPoints[N][M][2];
      }
      if ( atControlPoints[N][M][2] > tMax[2] )
      {
        tMax[2] = atControlPoints[N][M][2];
      }
    }
  }

  tBoundingBox.set (tMin, tMax);
  gBoundingBoxCurrent = true;

}  /* findBoundingBox() */


//
//  This is called when we are about to find a ray intersection with
//  our surface.  It determines if we are already flat enough, and if
//  we aren't, then it will subdivide ourself into four subpatches.
//
void TBezierSubsurface::subdivide (void)
{

  if ( gSubdivided || bPatchSubdivisionDepth == 0 )
  {
    return;
  }

  for (Byte N = 0; ( N < 4 ) ;N++)
  {
    aptChildren[N] = new TBezierSubsurface (ptObject);
  }

  //
  //  Find the four subpatches.  Rotate the control points 90 degrees
  //  to find the next subpatch.
  //
  aptChildren[0]->subpatch (atControlPoints[0][0], atControlPoints[1][0], 
                            atControlPoints[2][0], atControlPoints[3][0],
 
                            atControlPoints[0][1], atControlPoints[1][1],
                            atControlPoints[2][1], atControlPoints[3][1],
 
                            atControlPoints[0][2], atControlPoints[1][2],
                            atControlPoints[2][2], atControlPoints[3][2],
 
                            atControlPoints[0][3], atControlPoints[1][3],
                            atControlPoints[2][3], atControlPoints[3][3],

                            bEdgeSubdivisionDepth[0], bEdgeSubdivisionDepth[3]);

  if ( bPatchSubdivisionDepth ) 
  {
    aptChildren[0]->bPatchSubdivisionDepth = bPatchSubdivisionDepth - 1;
  }
  if ( bEdgeSubdivisionDepth[0] )
  {
    aptChildren[0]->bEdgeSubdivisionDepth[0] = bEdgeSubdivisionDepth[0] - 1;
  }
  if ( bEdgeSubdivisionDepth[3] )
  {
    aptChildren[0]->bEdgeSubdivisionDepth[3] = bEdgeSubdivisionDepth[3] - 1;
  }
  aptChildren[0]->bEdgeSubdivisionDepth[1] = aptChildren[0]->bPatchSubdivisionDepth;
  aptChildren[0]->bEdgeSubdivisionDepth[2] = aptChildren[0]->bPatchSubdivisionDepth;

  aptChildren[0]->ptAncestor      = ptAncestor;
  aptChildren[0]->tParametricPos  = tParametricPos;
  aptChildren[0]->tParametricVecU = 0.5 * tParametricVecU;
  aptChildren[0]->tParametricVecV = 0.5 * tParametricVecV;

  aptChildren[1]->subpatch (atControlPoints[3][0], atControlPoints[3][1], 
                            atControlPoints[3][2], atControlPoints[3][3],
 
                            atControlPoints[2][0], atControlPoints[2][1],
                            atControlPoints[2][2], atControlPoints[2][3],
 
                            atControlPoints[1][0], atControlPoints[1][1],
                            atControlPoints[1][2], atControlPoints[1][3],
 
                            atControlPoints[0][0], atControlPoints[0][1],
                            atControlPoints[0][2], atControlPoints[0][3],

                            bEdgeSubdivisionDepth[1], bEdgeSubdivisionDepth[0]);

  aptChildren[1]->bPatchSubdivisionDepth = aptChildren[0]->bPatchSubdivisionDepth;
  if ( bEdgeSubdivisionDepth[1] )
  {
    aptChildren[1]->bEdgeSubdivisionDepth[0] = bEdgeSubdivisionDepth[1] - 1;
  }
  if ( bEdgeSubdivisionDepth[0] )
  {
    aptChildren[1]->bEdgeSubdivisionDepth[3] = bEdgeSubdivisionDepth[0] - 1;
  }
  aptChildren[1]->bEdgeSubdivisionDepth[1] = aptChildren[0]->bPatchSubdivisionDepth;
  aptChildren[1]->bEdgeSubdivisionDepth[2] = aptChildren[0]->bPatchSubdivisionDepth;

  aptChildren[1]->ptAncestor      = ptAncestor;
  aptChildren[1]->tParametricPos  = tParametricPos + tParametricVecU;
  aptChildren[1]->tParametricVecU =  0.5 * tParametricVecV;
  aptChildren[1]->tParametricVecV = -0.5 * tParametricVecU;

  aptChildren[2]->subpatch (atControlPoints[3][3], atControlPoints[2][3], 
                            atControlPoints[1][3], atControlPoints[0][3],
 
                            atControlPoints[3][2], atControlPoints[2][2],
                            atControlPoints[1][2], atControlPoints[0][2],

                            atControlPoints[3][1], atControlPoints[2][1],
                            atControlPoints[1][1], atControlPoints[0][1],
 
                            atControlPoints[3][0], atControlPoints[2][0],
                            atControlPoints[1][0], atControlPoints[0][0],

                            bEdgeSubdivisionDepth[2], bEdgeSubdivisionDepth[1]);

  aptChildren[2]->bPatchSubdivisionDepth = aptChildren[0]->bPatchSubdivisionDepth;
  if ( bEdgeSubdivisionDepth[2] )
  {
    aptChildren[2]->bEdgeSubdivisionDepth[0] = bEdgeSubdivisionDepth[2] - 1;
  }
  if ( bEdgeSubdivisionDepth[1] )
  {
    aptChildren[2]->bEdgeSubdivisionDepth[3] = bEdgeSubdivisionDepth[1] - 1;
  }
  aptChildren[2]->bEdgeSubdivisionDepth[1] = aptChildren[0]->bPatchSubdivisionDepth;
  aptChildren[2]->bEdgeSubdivisionDepth[2] = aptChildren[0]->bPatchSubdivisionDepth;

  aptChildren[2]->ptAncestor      = ptAncestor;
  aptChildren[2]->tParametricPos  = tParametricPos + tParametricVecU + tParametricVecV;
  aptChildren[2]->tParametricVecU = -0.5 * tParametricVecU;
  aptChildren[2]->tParametricVecV = -0.5 * tParametricVecV;

  aptChildren[3]->subpatch (atControlPoints[0][3], atControlPoints[0][2], 
                            atControlPoints[0][1], atControlPoints[0][0],
 
                            atControlPoints[1][3], atControlPoints[1][2],
                            atControlPoints[1][1], atControlPoints[1][0],
 
                            atControlPoints[2][3], atControlPoints[2][2],
                            atControlPoints[2][1], atControlPoints[2][0],
 
                            atControlPoints[3][3], atControlPoints[3][2],
                            atControlPoints[3][1], atControlPoints[3][0],

                            bEdgeSubdivisionDepth[3], bEdgeSubdivisionDepth[2]);

  aptChildren[3]->bPatchSubdivisionDepth = aptChildren[0]->bPatchSubdivisionDepth;
  if ( bEdgeSubdivisionDepth[3] )
  {
    aptChildren[3]->bEdgeSubdivisionDepth[0] = bEdgeSubdivisionDepth[3] - 1;
  }
  if ( bEdgeSubdivisionDepth[2] )
  {
    aptChildren[3]->bEdgeSubdivisionDepth[3] = bEdgeSubdivisionDepth[2] - 1;
  }
  aptChildren[3]->bEdgeSubdivisionDepth[1] = aptChildren[0]->bPatchSubdivisionDepth;
  aptChildren[3]->bEdgeSubdivisionDepth[2] = aptChildren[0]->bPatchSubdivisionDepth;

  aptChildren[3]->ptAncestor      = ptAncestor;
  aptChildren[3]->tParametricPos  = tParametricPos + tParametricVecV;
  aptChildren[3]->tParametricVecU = -0.5 * tParametricVecV;
  aptChildren[3]->tParametricVecV =  0.5 * tParametricVecU;
  
  gSubdivided = true;

}  /* subdivide() */


//
//  Find the tangent vector in the S direction, given a position in
//  parametric space.
//
TVector TBezierSubsurface::getTangentS (const TVector2 &rktPOS)
{
  TScalar   tDU     = 1.0;
  TScalar   tDMinU  = -1.0;
  TScalar   tDU2    = 2.0 * rktPOS.x();
  TScalar   tDMinU2 = 2.0 * (1.0 - rktPOS.x()) * -1.0;
  TScalar   tDU3    = 3.0 * rktPOS.x() * rktPOS.x();
  TScalar   tDMinU3 = 3.0 * (1.0 - rktPOS.x()) * (1.0 - rktPOS.x()) * -1.0;

  TScalar   tU     = rktPOS.x();
  TScalar   tMinU  = 1.0 - rktPOS.x();
  TScalar   tU2    = rktPOS.x() * rktPOS.x();
  TScalar   tMinU2 = (1.0 - rktPOS.x()) * (1.0 - rktPOS.x());

  TScalar   tV     = rktPOS.y();
  TScalar   tMinV  = 1.0 - rktPOS.y();
  TScalar   tV2    = rktPOS.y() * rktPOS.y();
  TScalar   tMinV2 = (1.0 - rktPOS.y()) * (1.0 - rktPOS.y());
  TScalar   tV3    = rktPOS.y() * rktPOS.y() * rktPOS.y();
  TScalar   tMinV3 = (1.0 - rktPOS.y()) * (1.0 - rktPOS.y()) * (1.0 - rktPOS.y());

  return tDMinU3 * tMinV3 * atControlPoints[0][0] +
         3.0 * tDMinU2 * tU * tMinV3 * atControlPoints[1][0] +
         3.0 * tMinU2 * tDU * tMinV3 * atControlPoints[1][0] +
         3.0 * tDMinU * tU2 * tMinV3 * atControlPoints[2][0] +
         3.0 * tMinU * tDU2 * tMinV3 * atControlPoints[2][0] +
         tDU3 * tMinV3 * atControlPoints[3][0] +

         3.0 * tDMinU3 * tMinV2 * tV * atControlPoints[0][1] +
         9.0 * tDMinU2 * tU * tMinV2 * tV * atControlPoints[1][1] +
         9.0 * tMinU2 * tDU * tMinV2 * tV * atControlPoints[1][1] +
         9.0 * tDMinU * tU2 * tMinV2 * tV * atControlPoints[2][1] +
         9.0 * tMinU * tDU2 * tMinV2 * tV * atControlPoints[2][1] +
         3.0 * tDU3 * tMinV2 * tV * atControlPoints[3][1] +

         3.0 * tDMinU3 * tMinV * tV2 * atControlPoints[0][2] +
         9.0 * tDMinU2 * tU * tMinV * tV2 * atControlPoints[1][2] +
         9.0 * tMinU2 * tDU * tMinV * tV2 * atControlPoints[1][2] +
         9.0 * tDMinU * tU2 * tMinV * tV2 * atControlPoints[2][2] +
         9.0 * tMinU * tDU2 * tMinV * tV2 * atControlPoints[2][2] +
         3.0 * tDU3 * tMinV * tV2 * atControlPoints[3][2] +

         tDMinU3 * tV3 * atControlPoints[0][3] +
         3.0 * tDMinU2 * tU * tV3 * atControlPoints[1][3] +
         3.0 * tMinU2 * tDU * tV3 * atControlPoints[1][3] +
         3.0 * tDMinU * tU2 * tV3 * atControlPoints[2][3] +
         3.0 * tMinU * tDU2 * tV3 * atControlPoints[2][3] +
         tDU3 * tV3 * atControlPoints[3][3];

}  /* getTangentS() */


//
//  Find the tangent vector in the T direction, given a position in
//  parametric space.
//
TVector TBezierSubsurface::getTangentT (const TVector2 &rktPOS)
{

  TScalar   tU     = rktPOS.x();
  TScalar   tMinU  = 1.0 - rktPOS.x();
  TScalar   tU2    = rktPOS.x() * rktPOS.x();
  TScalar   tMinU2 = (1.0 - rktPOS.x()) * (1.0 - rktPOS.x());
  TScalar   tU3    = rktPOS.x() * rktPOS.x() * rktPOS.x();
  TScalar   tMinU3 = (1.0 - rktPOS.x()) * (1.0 - rktPOS.x()) * (1.0 - rktPOS.x());

  TScalar   tDV     = 1.0;
  TScalar   tDMinV  = -1.0;
  TScalar   tDV2    = 2.0 * rktPOS.y();
  TScalar   tDMinV2 = 2.0 * (1.0 - rktPOS.y()) * -1.0;
  TScalar   tDV3    = 3.0 * rktPOS.y() * rktPOS.y();
  TScalar   tDMinV3 = 3.0 * (1.0 - rktPOS.y()) * (1.0 - rktPOS.y()) * -1.0;

  TScalar   tV     = rktPOS.y();
  TScalar   tMinV  = 1.0 - rktPOS.y();
  TScalar   tV2    = rktPOS.y() * rktPOS.y();
  TScalar   tMinV2 = (1.0 - rktPOS.y()) * (1.0 - rktPOS.y());

  return tMinU3 * tDMinV3 * atControlPoints[0][0] +
         3.0 * tMinU2 * tU * tDMinV3 * atControlPoints[1][0] +
         3.0 * tMinU * tU2 * tDMinV3 * atControlPoints[2][0] +
         tU3 * tDMinV3 * atControlPoints[3][0] +

         3.0 * tMinU3 * tDMinV2 * tV * atControlPoints[0][1] +
         3.0 * tMinU3 * tMinV2 * tDV * atControlPoints[0][1] +
         9.0 * tMinU2 * tU * tDMinV2 * tV * atControlPoints[1][1] +
         9.0 * tMinU2 * tU * tMinV2 * tDV * atControlPoints[1][1] +
         9.0 * tMinU * tU2 * tDMinV2 * tV * atControlPoints[2][1] +
         9.0 * tMinU * tU2 * tMinV2 * tDV * atControlPoints[2][1] +
         3.0 * tU3 * tDMinV2 * tV * atControlPoints[3][1] +
         3.0 * tU3 * tMinV2 * tDV * atControlPoints[3][1] +

         3.0 * tMinU3 * tDMinV * tV2 * atControlPoints[0][2] +
         3.0 * tMinU3 * tMinV * tDV2 * atControlPoints[0][2] +
         9.0 * tMinU2 * tU * tDMinV * tV2 * atControlPoints[1][2] +
         9.0 * tMinU2 * tU * tMinV * tDV2 * atControlPoints[1][2] +
         9.0 * tMinU * tU2 * tDMinV * tV2 * atControlPoints[2][2] +
         9.0 * tMinU * tU2 * tMinV * tDV2 * atControlPoints[2][2] +
         3.0 * tU3 * tDMinV * tV2 * atControlPoints[3][2] +
         3.0 * tU3 * tMinV * tDV2 * atControlPoints[3][2] +

         tMinU3 * tDV3 * atControlPoints[0][3] +
         3.0 * tMinU2 * tU * tDV3 * atControlPoints[1][3] +
         3.0 * tMinU * tU2 * tDV3 * atControlPoints[2][3] +
         tU3 * tDV3 * atControlPoints[3][3];

}  /* getTangentT() */


//
//  Solve for the ray-triangle intersection by inverting a 3x3
//  matrix.
//
bool TBezierSubsurface::findFlatIntersection (const TRay& rktRAY, 
                                              const TScalar& rktSCALE,
                                              const TRay& rktORIG_RAY,
                                              TSpanList& rtLIST,
                                              const TVector& rktVECA, 
                                              const TVector2 &rktPOSA,
                                              const TVector& rktVECB,
                                              const TVector2 &rktPOSB,
                                              const TVector& rktVECC,
                                              const TVector2 &rktPOSC)
{

  TScalar        T, U, V;
  TSurfaceData   tDATA;
  TVector        tTangentU, tTangentV, tNormal;
  TVector2       tIntersectionPos, tAncestorPos;

  if ( !_findTriangleIntersection (rktRAY, rktVECA, rktVECB, rktVECC,
                                   T, U, V) )
  {
    return false;
  }

  if ( ( T < FX_EPSILON ) || ( T > rktRAY.limit() ) )
  {
    return false;
  }

  tIntersectionPos = rktPOSA + U * (rktPOSB - rktPOSA) + 
                               V * (rktPOSC - rktPOSA);
  tAncestorPos = tParametricPos + tIntersectionPos.x() * tParametricVecU
                                + tIntersectionPos.y() * tParametricVecV;

  tDATA.setup (ptObject, rktORIG_RAY);
  tDATA.setPoint (T * rktSCALE);

  tTangentU = ptAncestor->getTangentS (tAncestorPos);
  tTangentV = ptAncestor->getTangentT (tAncestorPos);

  tTangentU.applyTransform (ptObject->ptInverseMatrix);
  tTangentV.applyTransform (ptObject->ptInverseMatrix);

  tNormal = crossProduct (tTangentU, tTangentV);
  tNormal.normalize();

  if ( dotProduct (tNormal, rktORIG_RAY.direction()) > 0.0 )
  {
    tDATA.setNormal (-tNormal);
  }
  else 
  {
    tDATA.setNormal (tNormal);   
  }

  rtLIST.add (tDATA);

  return true;

}  /* findFlatIntersection() */


//
//  This is called if we have determined that we are "flat enough".
//  It will find the ray intersection with us, as if we were 
//  planar.  We do ray-triangle intersections with the eighteen
//  triangles defined by the control points.
//
bool TBezierSubsurface::findFlatIntersection (const TRay& rktRAY,
                                              const TScalar& rktSCALE,
                                              const TRay& rktORIG_RAY,
					      TSpanList& rtLIST)
{
  if ( findFlatIntersection (rktRAY, rktSCALE, rktORIG_RAY, rtLIST, 
			     atControlPoints[0][0],
			     TVector2 (0.0, 0.0),
			     atControlPoints[3][0],
			     TVector2 (1.0, 0.0),
			     atControlPoints[0][3],
			     TVector2 (0.0, 1.0)) )
  {
    return true;
  }
    
  if ( findFlatIntersection (rktRAY, rktSCALE, rktORIG_RAY, rtLIST, 
			     atControlPoints[0][3],
			     TVector2 (0.0, 1.0),
			     atControlPoints[3][0],
			     TVector2 (1.0, 0.0),
			     atControlPoints[3][3],
			     TVector2 (1.0, 1.0)) )
  {
    return true;
  }

  return false;

}  /* findFlatIntersection() */


//
//  Calculate the maximum subdivion depth for each of the edges of
//  this patch, and for the surface as a whole.
// 
void TBezierSubsurface::calculateSubdivisionDepth (void)
{
  Byte N, bDepth;

  bPatchSubdivisionDepth = 0;

  for (N = 0; ( N < 4 ) ;N++)
  {
    bDepth = _curveSubdivisionDepth (atControlPoints[0][N], 
                                     atControlPoints[1][N],
                                     atControlPoints[2][N],
                                     atControlPoints[3][N]);
    if ( bDepth > bPatchSubdivisionDepth )
    {
      bPatchSubdivisionDepth = bDepth;
    }
    
    if ( N == 0 )
    {
      bEdgeSubdivisionDepth[0] = bDepth;
    }
    
    if ( N == 3 )
    {
      bEdgeSubdivisionDepth[2] = bDepth;
    }
  }

  for (N = 0; ( N < 4 ) ;N++)
  {
    bDepth = _curveSubdivisionDepth (atControlPoints[N][0], 
                                     atControlPoints[N][1],
                                     atControlPoints[N][2],
                                     atControlPoints[N][3]);
    if ( bDepth > bPatchSubdivisionDepth )
    {
      bPatchSubdivisionDepth = bDepth;
    }
    
    if ( N == 0 )
    {
      bEdgeSubdivisionDepth[3] = bDepth;
    }
    
    if ( N == 3 )
    {
      bEdgeSubdivisionDepth[1] = bDepth;
    }
  }

}  /* calculateSubdivionDepth() */


//
//  Called when we need an intersection with this subsurface.  
//  It may trigger subdivision.
//
bool TBezierSubsurface::findAllIntersections (const TRay& rktRAY, 
                                              const TScalar& rktSCALE,
                                              const TRay& rktORIG_RAY,
                                              TSpanList& rtLIST)
{

  findBoundingBox();
  if ( !tBoundingBox.intersects (rktRAY) )
  {
    return false;
  }

  subdivide();

  if ( gSubdivided )
  {
    bool   gFoundAnyIntersections = false;

    for (Byte N = 0; ( N < 4 ) ;N++)
    {
      bool   gFoundMoreIntersections = aptChildren[N]->findAllIntersections (rktRAY, rktSCALE, rktORIG_RAY, rtLIST);

      gFoundAnyIntersections = gFoundAnyIntersections || gFoundMoreIntersections;
    }

    return gFoundAnyIntersections;
  } 
  else if ( bPatchSubdivisionDepth == 0 )
  {
    if ( findFlatIntersection (rktRAY, rktSCALE, rktORIG_RAY, rtLIST) )
    {
      return true;
    }
  }

  return false;

}  /* findAllIntersections() */
