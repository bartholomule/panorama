/*
*  Copyright (C) 1999 Angel Jimenez Jimenez and Carlos Jimenez Moreno
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

#include "abvh.h"

DEFINE_PLUGIN ("ABVH", FX_OBJECT_CLASS, TABVH);

float TABVH::costByMethod1 (TNode* ptTREE, TObject* ptOBJ)
{

  TBoundingBox   tBBox = Union (ptTREE->boundingBox(), ptOBJ->boundingBox());

  return 2 * tBBox.cost();
  
}  /* costByMethod1() */


float TABVH::costByMethod2 (TNode* ptTREE, TObject* ptOBJ)
{

  TBoundingBox   tBBox = Union (ptTREE->boundingBox(), ptOBJ->boundingBox());

  return (tBBox.cost() - ptTREE->boundingBox().cost()) * ptTREE->tChildList.size() + tBBox.cost();
  
}  /* costByMethod2() */


TABVH::TNode* TABVH::applyMethod1 (TNode* ptTREE, TObject* ptOBJ)
{

  TBoundingBox   tNewBBox  = Union (ptOBJ->boundingBox(), ptTREE->boundingBox());
  float          fNewCost  = ptTREE->cost() + 2 * tNewBBox.cost();
  TNode*         ptNewTree = new TNode (new TBoundingBox (tNewBBox), fNewCost);

  ptNewTree->addChild (ptTREE);
  ptNewTree->addChild (ptOBJ);

  return ptNewTree;
  
}  /* applyMethod1() */


TABVH::TNode* TABVH::applyMethod2 (TNode* ptTREE, TObject* ptOBJ)
{

  ptTREE->addChild (ptOBJ);

  return ptTREE;
  
}  /* applyMethod2() */


TABVH::TNode* TABVH::applyMethod3 (TNode* ptTREE, TObject* ptOBJ, float fINHERITANCE_COST, float fPARENT_BEST_COST)
{

  return NULL;
  /*
  
  list<TNode*>::iterator   tIter;
  
  //
  // Select best child for recursion
  //
  zBestChild = 0;
  tIter      = ptTree->tChildList.begin();
  fBestCost  = Union (ptOBJ->boundingBox(), (*tIter)->boundingBox()).cost();
  
  for (tIter++; ( tIter != ptTree->tChildList.end() ) ;tIter++)
  {
    fNewCost = Union (ptOBJ->boundingBox(), (*tIter)->boundingBox()).cost();
    if ( fNewCost < fBestCost )
    {
      fBestCost  = fNewCost;
      zBestChild = J;
    }
  }
  */
  
}  /* applyMethod3() */


void TABVH::insertObject (TObject* ptOBJ)
{

  float          fCost1, fCost2;
  float          fInheritanceCost, fLocalBestCost;
  TBoundingBox   tOldBBox, tNewBBox;
  TNode*         ptNewTree;

//  if ( ptTree->ptVolume->classType() == FX_OBJECT_CLASS )
//  {
    //
    // Insert directly using method 1
    //
    ptTree = applyMethod1 (ptTree, ptOBJ);

    return;
//  }
  
  tOldBBox = ptTree->boundingBox();
  tNewBBox = Union (tOldBBox, ptOBJ->boundingBox());

  //
  // Calculate cost difference for each method
  //
  fCost1 = 2 * tNewBBox.cost();
  fCost2 = (tNewBBox.cost() - tOldBBox.cost()) * ptTree->tChildList.size() + tNewBBox.cost();

  fLocalBestCost   = min (fCost1, fCost2);
  fInheritanceCost = (tNewBBox.cost() - tOldBBox.cost()) * ptTree->tChildList.size();

  ptNewTree = applyMethod3 (ptTree, ptOBJ, fInheritanceCost, fLocalBestCost);
  
  if ( ptNewTree )
  {
    ptTree = ptNewTree;
  }
  else
  {
    if ( fLocalBestCost == fCost1 )
    {
      applyMethod1 (ptTree, ptOBJ);
    }
    else
    {
      applyMethod2 (ptTree, ptOBJ);
    }
  }
  
}  /* insertObject() */


void TABVH::initialize (void)
{

  size_t                       zPos;
  TObject*                     ptObj;
  vector<TObject*>::iterator   tIter;

  if ( tObjectList.empty() )
  {
    return;
  }

  for (tIter = tObjectList.begin(); ( tIter != tObjectList.end() ) ;tIter++)
  {
    (*tIter)->initialize();
  }

  //
  // Shuffle contents of the object list.
  //
  for (size_t J = 0; ( J < tObjectList.size() ); J++)
  {
    zPos              = size_t (frand() * tObjectList.size());
    ptObj             = tObjectList [J];
    tObjectList[J]    = tObjectList [zPos];
    tObjectList[zPos] = ptObj;
  }

  //
  // Create tree using first object as root node.
  //
  tIter  = tObjectList.begin();
  ptObj  = *tIter;
  ptTree = new TNode (ptObj, 1);

  //
  // Insert every object into the tree.
  //
  for (tIter++; ( tIter != tObjectList.end() ) ;tIter++)
  {
    insertObject (*tIter);
  }
  
  //
  // Finally, clear the object list.
  //
  tObjectList.erase (tObjectList.begin(), tObjectList.end());
  
}  /* initialize() */


bool TABVH::findFirstIntersection (const TRay& rktRAY, TSurfaceData& rtDATA) const
{

  TNode*     ptNode;
  TObject*   ptObj;
  TNode*     ptOldTree;
  TRay       tRay          = rktRAY;
  bool       gIntersection = false;

  /*
  if ( !ptTree->boundingBox().intersects (tRay) )
  {
    return false;
  }
  */
  
  for (list<TNode*>::const_iterator tIter = ptTree->tChildList.begin(); ( tIter != ptTree->tChildList.end() ) ;tIter++)
  {
    ptNode = *tIter;

    if ( ptNode->ptVolume->classType() == FX_OBJECT_CLASS )
    {
      ptObj = (TObject*) ptNode->ptVolume;

      if ( ptObj->findFirstIntersection (tRay, rtDATA) )
      {
        tRay.setLimit (rtDATA.distance());
        gIntersection = true;
      }
    }
    else
    {
      ptOldTree = ptTree;
      ptTree    = ptNode;
      gIntersection |= findFirstIntersection (tRay, rtDATA);
      ptTree    = ptOldTree;
    }
  }

  return gIntersection;

}  /* findFirstIntersection() */


bool TABVH::findAllIntersections (const TRay& rktRAY, TSpanList& rtLIST) const
{

  bool   gIntersection = false;

//  if ( !tBoundingBox.intersects (rktRAY, tLIMIT) )
//  {
//    return false;
//  }
  
  for (vector<TObject*>::const_iterator tIter = tObjectList.begin(); ( tIter != tObjectList.end() ) ;tIter++)
  {
    if ( (*tIter)->findAllIntersections (rktRAY, rtLIST) )
    {
      gIntersection = true;
    }
  }
  
  return gIntersection;

}  /* findAllIntersections() */
