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

map<TSubdivEdge::TVertPair, TSubdivEdge*, TSubdivEdge::TVertPairCompare>   TSubdivEdge::_tEdgeMap;

bool TSubdivEdge::TVertPairCompare::operator() (const TVertPair& rktFIRST, 
                                                const TVertPair& rktSECOND)
{
  if ( rktFIRST.ptFirst < rktSECOND.ptFirst )
  {
    return true;
  }

  if ( rktFIRST.ptFirst > rktSECOND.ptFirst )
  {
    return false;
  }

  if ( rktFIRST.ptSecond < rktSECOND.ptSecond )
  {
    return true;
  }

  if ( rktFIRST.ptSecond > rktSECOND.ptSecond )
  {
    return false;
  }

  return false;

}  /* opreator() */


TSubdivEdge::TSubdivEdge (TSubdivVert *ptFIRST, TSubdivVert *ptSECOND)
{
  ptEdgePoint = NULL;  
  ptFirstVert = ptFIRST;
  ptSecondVert = ptSECOND;
  ptFirstFace = NULL;
  ptSecondFace = NULL;

  ptFIRST->addEdge (this);
  ptSECOND->addEdge (this);

}  /* TSubdivEdge() */


TSubdivEdge* TSubdivEdge::_findEdge (TSubdivVert* ptFIRST, 
                                     TSubdivVert* ptSECOND)
{
  TVertPair tKey;

  if ( ptFIRST < ptSECOND )
  {
    tKey.ptFirst = ptFIRST;
    tKey.ptSecond = ptSECOND;
  }
  else
  {
    tKey.ptFirst = ptSECOND;
    tKey.ptSecond = ptFIRST;
  }

  if ( _tEdgeMap.find (tKey) == _tEdgeMap.end() )
  {
    TSubdivEdge *ptNewEdge;
   
    ptNewEdge = new TSubdivEdge (ptFIRST, ptSECOND);
    _tEdgeMap[tKey] = ptNewEdge;
  }

  return _tEdgeMap[tKey];

}  /* _findEdge() */


TSubdivVert* TSubdivEdge::otherVert (const TSubdivVert* ptVERT) const
{

  if ( ptVERT == ptFirstVert )
  {
    return ptSecondVert;
  }
  if ( ptVERT == ptSecondVert )
  {
    return ptFirstVert;
  }
  return NULL;

}  /* otherVert() */


TSubdivFace* TSubdivEdge::otherFace (const TSubdivFace* ptFACE) const
{
  if ( ptFACE == ptFirstFace )
  {
    return ptSecondFace;
  }
  if ( ptFACE == ptSecondFace )
  {
    return ptFirstFace;
  }
  return NULL;

}  /* otherFace() */


TSubdivVert* TSubdivEdge::findPoint()
{
  if ( ptEdgePoint != NULL )
  {
    return ptEdgePoint;
  }

  if ( ptSecondFace == NULL ) 
  {    
    TVector   tPos = 0.5 * (ptFirstVert->tPosition + ptSecondVert->tPosition);

    ptEdgePoint = new TSubdivVert ("", tPos);  

    ptEdgePoint->bRemainingDepth = (ptFirstVert->bRemainingDepth - 1
                                    + ptSecondVert->bRemainingDepth - 1) / 2;
  }
  else
  {
    TSubdivVert*   ptFirstFaceVert = ptFirstFace->findPoint();    
    TSubdivVert*   ptSecondFaceVert = ptSecondFace->findPoint();    

    TVector   tPos = 0.25 * (ptFirstVert->tPosition + ptSecondVert->tPosition 
                             + ptFirstFaceVert->tPosition
                             + ptSecondFaceVert->tPosition);

    ptEdgePoint = new TSubdivVert ("", tPos);  

    ptEdgePoint->bRemainingDepth = (ptFirstVert->bRemainingDepth - 1
                                    + ptSecondVert->bRemainingDepth - 1
                                    + ptFirstFaceVert->bRemainingDepth
                                    + ptSecondFaceVert->bRemainingDepth) / 4;
  }

  return ptEdgePoint;

}  /* findPoint() */


void TSubdivEdge::addFace (TSubdivFace *ptFACE)
{
  if ( ptFirstFace == NULL )
  {
    ptFirstFace = ptFACE;
  }
  else
  { 
    ptSecondFace = ptFACE;
  }

}  /* addFace() */

