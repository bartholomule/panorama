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

#include <map>
#include "subdivvert.h"
#include "subdivedge.h"
#include "subdivface.h"
#include "subdiv.h"


void TSubdivFace::_addToBox(TVector& rtMIN, TVector& rtMAX, 
                            const TVector& rktVEC)
{
  if ( rktVEC[0] < rtMIN[0] )
  {
    rtMIN[0] = rktVEC[0];
  }
  if ( rktVEC[0] > rtMAX[0] )
  {
    rtMAX[0] = rktVEC[0];
  }

  if ( rktVEC[1] < rtMIN[1] )
  {	
    rtMIN[1] = rktVEC[1];
  }
  if ( rktVEC[1] > rtMAX[1] )
  {
    rtMAX[1] = rktVEC[1];
  }

  if ( rktVEC[2] < rtMIN[2] )
  {
    rtMIN[2] = rktVEC[2];
  }
  if ( rktVEC[2] > rtMAX[2] )
  {
    rtMAX[2] = rktVEC[2];
  }        
}  /* _addToBox() */


bool TSubdivFace::_findTriangleIntersection (const TRay& rktRAY,
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

  if ( ( U < 0.0 ) || ( V < 0.0 ) || ( V + U > 1.0 ) )
  {
    return false;
  }

  return true;

}  /* _findTriangleIntersection() */


bool TSubdivFace::determineFinality() const
{
  for (vector<TSubdivVert*>::const_iterator tIter = tVerts.begin(); ( tIter != tVerts.end() ) ;tIter++)
  {
    if ( (*tIter)->bRemainingDepth > 0 )
    {
      return false;
    }
  }
  
  return true;

}  /* determineFinality() */


bool TSubdivFace::findBoundingBoxFromChildren()
{
  TVector   tMin, tMax;
  bool      gFirst = true;

  if ( !gSubdivided ) 
  {
    return true;
  }

  for (vector<TSubdivFace*>::const_iterator tIter = tFaces.begin(); ( tIter != tFaces.end() ) ;tIter++)
  {
    const TBoundingBox& rktBox = (*tIter)->tBoundingBox;

    if ( !(*tIter)->gFoundBoundingBox )
    {
      return true;
    }

    if ( gFirst )
    {
      tMin = TVector (rktBox.xlimits().min(), rktBox.ylimits().min(), rktBox.zlimits().min());
      tMax = tMin;
      gFirst = false;
    }

    _addToBox (tMin, tMax, TVector (rktBox.xlimits().min(), rktBox.ylimits().min(), rktBox.zlimits().min()));
    _addToBox (tMin, tMax, TVector (rktBox.xlimits().max(), rktBox.ylimits().max(), rktBox.zlimits().max()));
  }

  tBoundingBox.set (tMin, tMax);
  return false;

}  /* findBoundingBoxFromChildren() */

void TSubdivFace::findBoundingBoxFromPoints()
{
  TVector   tMin, tMax;
  bool      gFirst = true;

  for (vector<TSubdivVert*>::const_iterator tVertIter = tVerts.begin(); ( tVertIter != tVerts.end() ) ;tVertIter++)
  {
    if ( gFinal )
    {
      const TVector& rkPos = (*tVertIter)->tPosition;
      if ( gFirst )
      {
        tMin = rkPos;
        tMax = rkPos;
        gFirst = false;
      }

      _addToBox(tMin, tMax, rkPos);
    }
    else
    {
      for (TSubdivVert::const_face_iterator tFaceIter = (*tVertIter)->beginFace(); ( tFaceIter != (*tVertIter)->endFace() ) ;tFaceIter++)
      {
        for (vector<TSubdivVert*>::const_iterator tNeighborIter = (*tFaceIter)->tVerts.begin(); ( tNeighborIter != (*tFaceIter)->tVerts.end() ) ;tNeighborIter++)
        {
          const TVector& rkPos = (*tNeighborIter)->tPosition;
          if ( gFirst )
          {
            tMin = rkPos;
            tMax = rkPos;
            gFirst = false;
          }

          _addToBox(tMin, tMax, rkPos);
	}
      }
    }
  }
  
  tBoundingBox.set (tMin, tMax);

}  /* findBoundingBoxFromPoints() */


void TSubdivFace::findBoundingBox()
{
  if ( findBoundingBoxFromChildren() ) 
  {
    findBoundingBoxFromPoints();
  }
  gFoundBoundingBox = true;

  if ( ptParent != NULL )
  {
    ptParent->findBoundingBox();
  }

}  /* findBoundingBox() */


void TSubdivFace::generateFace (TSubdivVert* ptVERT)
{
  TSubdivEdge*          tEdgeBefore;
  TSubdivEdge*          tEdgeAfter;
  TSubdivFace*          tNewFace;
  vector<TSubdivVert*>  tVertList;

  if ( tGeneratedFaces.find (ptVERT) != tGeneratedFaces.end() )
  {
    return;
  }

  tEdgeBefore = edgeBefore (ptVERT);
  tEdgeAfter = edgeAfter (ptVERT);
      
  tVertList.push_back (ptVERT->findPoint());
  tVertList.push_back (tEdgeAfter->findPoint());
  tVertList.push_back (findPoint());
  tVertList.push_back (tEdgeBefore->findPoint());
  tNewFace = new TSubdivFace (tVertList);
  tNewFace->ptParent = this;

  tFaces.push_back (tNewFace);
  tGeneratedFaces[ptVERT] = tNewFace;

}  /* generateFace() */


//
//  To get the next subdivision level, we need to consider each vert which 
//  makes up this face.  For each of those verts, we need to consider all
//  of the faces that vert is connected to.  For each of those faces, we 
//  will create a new subface quad which connect the vertex point, the
//  face point and the two edge points.  
//
void TSubdivFace::subdivide()
{
  for (vector<TSubdivVert*>::const_iterator tVertIter = tVerts.begin(); ( tVertIter != tVerts.end() ) ;tVertIter++)
  {
    for (TSubdivVert::const_face_iterator tFaceIter = (*tVertIter)->beginFace(); ( tFaceIter != (*tVertIter)->endFace() ) ;tFaceIter++)
    {
      (*tFaceIter)->generateFace(*tVertIter);
    }
  }

}  /* subdivide() */


TVector TSubdivFace::findNormal (TSubdivVert* ptBASE, TSubdivVert* ptVERTU,
                                 TSubdivVert* ptVERTV,
                                 TScalar U, TScalar V) const
{
  TVector   tNormBase, tNormU, tNormV;
  TVector   tSum;

  tNormBase = ptBASE->findNormal (*this);
  tNormU    = ptVERTU->findNormal (*this);
  tNormV    = ptVERTV->findNormal (*this);

  tSum = U * tNormU + V * tNormV + (TScalar (1.0) - U - V) * tNormBase;
  tSum.normalize();

  return tSum;

}  /* findNormal() */


bool TSubdivFace::findLocalIntersections (const TSubdiv& rktSUBDIV, 
                                          const TRay& rktORIGRAY, 
                                          const TScalar& rktSCALE,
                                          const TRay& rktRAY, 
                                          TSpanList& rtLIST) const
{
  vector<TSubdivVert*>::const_iterator   tIter;
  TSubdivVert*                           ptPivot;
  TSubdivVert*                           ptLast;
  TSubdivVert*                           ptCurrent;
  bool                                   gFoundIntersection;
  TScalar                                T, U, V;
  TVector                                tNormal;
  TSurfaceData                           tData;

  gFoundIntersection = false;

  tIter = tVerts.begin();
  ptPivot = *tIter;
  tIter++;

  ptLast = *tIter;
  tIter++;

  while ( tIter != tVerts.end() )
  {
    ptCurrent = *tIter;
    tIter++;

    if ( _findTriangleIntersection (rktRAY, ptPivot->tPosition, 
                                    ptLast->tPosition, ptCurrent->tPosition,
                                    T, U, V) )
    {
      if ( ( T > FX_EPSILON ) && ( T < rktRAY.limit() ) )
      {
        gFoundIntersection = true;
  
        tData.setup (&rktSUBDIV, rktORIGRAY);
        tData.setPoint (T * rktSCALE);

        tNormal = findNormal (ptPivot, ptLast, ptCurrent, U, V);

        tNormal.applyTransform (rktSUBDIV.ptInverseMatrix);
        tNormal.normalize();

        if ( dotProduct (tNormal, rktORIGRAY.direction()) > 0.0 )
        {
          tData.setNormal (-tNormal);
        }
        else 
        {
          tData.setNormal (tNormal);   
        }

        rtLIST.add (tData);
      }
    }

    ptLast = ptCurrent;  
  }

  return gFoundIntersection;

}  /* findLocalIntersections() */


TSubdivFace::TSubdivFace (const vector<TSubdivVert*>& rktVERTLIST)
{
  TSubdivVert *ptLast;
  TSubdivEdge *ptEdge;

  tVerts = rktVERTLIST;
  gSubdivided = false;
  gFinal = false;
  gFoundBoundingBox = false;
  ptFacePoint = NULL;

  ptParent = NULL;

  ptLast = NULL;
  for (vector<TSubdivVert*>::const_iterator tIter = tVerts.begin(); ( tIter != tVerts.end() ) ;tIter++)
  {
    (*tIter)->addFace(this);
    if ( ptLast != NULL )
    {
      ptEdge = TSubdivEdge::_findEdge (*tIter, ptLast);
      ptEdge->addFace(this);
    }

    ptLast = *tIter;
  }

  ptEdge = TSubdivEdge::_findEdge (*tVerts.begin(), ptLast);
  ptEdge->addFace(this);

}  /* TSubdivFace() */


bool TSubdivFace::findAllIntersections (const TSubdiv& rktSUBDIV, 
                                        const TRay& rktORIGRAY, 
                                        const TScalar& rktSCALE, 
                                        const TRay& rktRAY, TSpanList& rtLIST)
{
  bool   gFoundIntersection = false;

  if ( !gFoundBoundingBox )
  { 
    findBoundingBox();
  }
  if ( !tBoundingBox.intersects (rktRAY) )
  {
    return false;
  }

  if ( !gSubdivided && !gFinal )
  {
    if ( determineFinality() )
    {
      gFinal = true;
      findBoundingBox();
    }
    else
    {
      gSubdivided = true;
      subdivide();
    }
  }

  if ( gFinal ) {
    return findLocalIntersections (rktSUBDIV, rktORIGRAY, rktSCALE, rktRAY, rtLIST);
  }

  if ( gSubdivided )
  {
    for (vector<TSubdivFace*>::const_iterator tIter = tFaces.begin(); ( tIter != tFaces.end() ) ;tIter++)
    {
      if ( (*tIter)->findAllIntersections (rktSUBDIV, rktORIGRAY, rktSCALE,
                                           rktRAY, rtLIST) )
      {
        gFoundIntersection = true;
      }
    }
  }

  return gFoundIntersection;

}  /* findAllIntersections() */


TSubdivVert* TSubdivFace::findPoint()
{
  DWord     dwCount;
  DWord     dwDepthSum;
  TVector   tTotal (0, 0, 0);

  if ( ptFacePoint != NULL )
  {
    return ptFacePoint;
  }
 
  dwCount = 0;
  dwDepthSum = 0;
  for (vector<TSubdivVert*>::const_iterator tIter = tVerts.begin(); ( tIter != tVerts.end() ) ;tIter++)
  {
    dwCount++;
    tTotal += (*tIter)->tPosition;
    dwDepthSum += (*tIter)->bRemainingDepth - 1;
  }

  tTotal /= (TScalar)dwCount;

  ptFacePoint = new TSubdivVert ("", tTotal);
  ptFacePoint->bRemainingDepth = dwDepthSum / dwCount;

  return ptFacePoint;  

}  /* findPoint() */


TSubdivEdge* TSubdivFace::edgeBefore (TSubdivVert* ptVERT) const
{
  TSubdivVert*                           ptLast;
  vector<TSubdivVert*>::const_iterator   tIter;
  
  tIter = tVerts.begin();
  ptLast = *tIter;
  tIter++;

  while ( tIter != tVerts.end() )
  {
    if ( *tIter == ptVERT )
    {
      return TSubdivEdge::_findEdge (*tIter, ptLast);
    }

    ptLast = *tIter;
    tIter++;
  }

  tIter = tVerts.begin();
  if ( *tIter == ptVERT )
  {
    return TSubdivEdge::_findEdge (*tIter, ptLast);
  }
  
  return NULL;

}  /* edgeBefore() */


TSubdivEdge* TSubdivFace::edgeAfter (TSubdivVert* ptVERT) const
{
  bool                                   gFound;
  vector<TSubdivVert*>::const_iterator   tIter;

  gFound = false;
  tIter = tVerts.begin();
  while ( tIter != tVerts.end() )
  {
    if ( gFound )
    {
      return TSubdivEdge::_findEdge (ptVERT, *tIter);
    }
 
    if ( *tIter == ptVERT )
    {
      gFound = true;
    }

    tIter++;
  }

  tIter = tVerts.begin();
  if ( gFound )
  {
    return TSubdivEdge::_findEdge (ptVERT, *tIter);    
  }

  return NULL;

}  /* edgeAfter() */


TSubdivEdge* TSubdivFace::otherEdge (TSubdivVert* ptVERT, 
                                     TSubdivEdge* ptEDGE) const
{
  TSubdivEdge* ptEdgeA;
  TSubdivEdge* ptEdgeB;
 
  ptEdgeA = edgeBefore(ptVERT);
  ptEdgeB = edgeAfter(ptVERT);

  if ( ptEdgeA == ptEDGE )
  {
    return ptEdgeB;
  }
  if ( ptEdgeB == ptEDGE )
  {
    return ptEdgeA;
  }
  return NULL;
 
}  /* otherEdge() */
