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

#include "subdivvert.h"
#include "subdivedge.h"
#include "subdivface.h"

void TSubdivVert::addNormalFrom (TVector& rtSUM, 
                                 TSubdivEdge& rktFIRST, TSubdivEdge& rktSECOND)
                               const
{
  TVector   tTangentA, tTangentB;

  tTangentA = rktFIRST.otherVert (this)->tPosition - tPosition;
  tTangentB = rktSECOND.otherVert (this)->tPosition - tPosition;

  rtSUM += crossProduct (tTangentA, tTangentB);

}  /* addNormalFrom() */


TSubdivVert::TSubdivVert (const string& rktNAME, const TVector& rktPOSITION)
{
  gFoundNormal = false;

  tPosition = rktPOSITION;
  tName = rktNAME;
  bRemainingDepth = 4;
  ptNextVert = NULL;

}  /* TSubdivVert() */


void TSubdivVert::addFace (TSubdivFace* ptFACE)
{
  tFaces.push_back (ptFACE);  

}  /* addFace() */


TSubdivVert::const_face_iterator TSubdivVert::beginFace() const
{
  return tFaces.begin();

}  /* beginFace() */


TSubdivVert::const_face_iterator TSubdivVert::endFace() const
{
  return tFaces.end();

}  /* endFace() */


void TSubdivVert::addEdge (TSubdivEdge* ptEDGE)
{
  tEdges.push_back(ptEDGE);

}  /* addEdge() */


TSubdivVert::const_edge_iterator TSubdivVert::beginEdge() const
{
  return tEdges.begin();

}  /* beginFace() */


TSubdivVert::const_edge_iterator TSubdivVert::endEdge() const
{
  return tEdges.end();

}  /* endEdge() */


TVector TSubdivVert::findNormal (const TSubdivFace& rktFACE)
{
  TVector              tSum (0, 0, 0);
  TSubdivEdge*         ptEdge;
  TSubdivEdge*         ptLastEdge;
  const TSubdivFace*   pktFace;

  ptLastEdge = rktFACE.edgeAfter (this);  
  ptEdge = rktFACE.edgeBefore (this);
  pktFace = &rktFACE;
  while ( true )
  {
    addNormalFrom (tSum, *ptLastEdge, *ptEdge);
    pktFace = ptEdge->otherFace (pktFace);

    if ( pktFace == NULL )
    {
      break;
    }

    if ( pktFace == &rktFACE )
    {
      tSum.normalize();
      return tSum;
    }

    ptLastEdge = ptEdge;
    ptEdge = pktFace->otherEdge (this, ptEdge);
  }

  ptLastEdge = rktFACE.edgeBefore (this);  
  ptEdge = rktFACE.edgeAfter (this);
  pktFace = &rktFACE;
  while ( true )
  {
    pktFace = ptEdge->otherFace (pktFace);

    if ( pktFace == NULL )
    {
      break;
    }

    ptLastEdge = ptEdge;
    ptEdge = pktFace->otherEdge (this, ptEdge);
    addNormalFrom (tSum, *ptEdge, *ptLastEdge);
  }

  tSum.normalize();
  return tSum;

}  /* findNormal() */


TSubdivVert* TSubdivVert::findPoint()
{
  TVector   tFacePoint (0, 0, 0);
  DWord     dwFaceCount;
  TVector   tEdgePoint (0, 0, 0);
  DWord     dwEdgeCount;
  TVector   tPosition;

  if ( ptNextVert != NULL )
  {
    return ptNextVert;
  }

  dwFaceCount = 0;
  for (const_face_iterator tIter = beginFace(); ( tIter != endFace() ) ;tIter++)
  {
    dwFaceCount++;
    tFacePoint += (*tIter)->findPoint()->tPosition;
  }

  dwEdgeCount = 0;
  for (const_edge_iterator tIter = beginEdge(); ( tIter != endEdge() ) ;tIter++)
  {
    TSubdivVert*   ptFirst = (*tIter)->ptFirstVert;
    TSubdivVert*   ptSecond = (*tIter)->ptSecondVert;

    dwEdgeCount++;
    tEdgePoint += ptFirst->tPosition + ptSecond->tPosition;
  }
  
  tPosition = tFacePoint / (TScalar)dwFaceCount;
  tPosition += tEdgePoint / (TScalar)dwEdgeCount;
  tPosition += (TScalar)(dwEdgeCount - 3) * this->tPosition;
  tPosition /= (TScalar)dwEdgeCount;

  ptNextVert = new TSubdivVert("", tPosition);
  ptNextVert->bRemainingDepth = bRemainingDepth - 1;

  return ptNextVert;

}  /* findPoint() */
