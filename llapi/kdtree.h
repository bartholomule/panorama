/*
*  Copyright (C) 2000 Angel Jimenez Jimenez and Carlos Jimenez Moreno
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

#ifndef _KDTREE__
#define _KDTREE__

#include <vector>
#include "llapi/priority_queue.h"

#define BLOCK_SIZE         10000
#define MAX_BLOCKS           500
#define HAS_LEFT_SON           1
#define HAS_RIGHT_SON          2

template <class TItem>
class TKDTree
{

  protected:

    struct TKDTreeNode
    {

      TItem    tData;
      Byte     bAxis;
      Byte     bFlags;
      size_t   zLeftSon;
      size_t   zRightSon;

    };  /* struct TKDTreeNode */

    TKDTreeNode*   aptNodes [MAX_BLOCKS];
    size_t         zNumPoints;
    size_t         zNumBlocks;
    
    void swapPoints (size_t I, size_t J);
    void balanceTree (size_t zFIRST, size_t zLAST);
    Byte findMaxSpreadDimension (size_t zFIRST, size_t zLAST);
    void classify (size_t zFIRST, size_t zLAST, Byte bDIM);
    void searchNN (TPriorityQueue<TItem>* ptPQUEUE, size_t zROOT, size_t N, const TVector& rktPOINT) const;
    void recursiveRangeSearch (vector<TItem>* ptARRAY, size_t zROOT, TScalar tDISTANCE2, const TVector& rktPOINT) const;
    void recursiveLinearRangeSearch (vector<TItem>* ptARRAY, size_t zROOT, TScalar tDISTANCE2, const TVector& rktPOINT, const TVector& rktVECTOR) const;
    TScalar searchRadius (TPriorityQueue<TItem>* ptPQUEUE) const;

    TKDTreeNode* getNode (size_t zPOS) const
    {
      if ( zPOS >= zNumPoints )
      {
        cout << "zPOS = " << zPOS << endl;
        cout << "zNumPoints = " << zNumPoints << endl;
      }
      assert ( zPOS < zNumPoints );
      return &(aptNodes [zPOS / BLOCK_SIZE][zPOS % BLOCK_SIZE]);
    }

  public:

    TKDTree (void) :
      zNumPoints (0),
      zNumBlocks (0) {}

    void insertNode (TItem tDATA);
    void balance (void);
    
    TPriorityQueue<TItem>* nearestNeighbours (size_t N, const TVector& rktPOINT) const;
    vector<TItem>* rangeSearch (TScalar tDISTANCE2, const TVector& rktPOINT) const;
    vector<TItem>* linearRangeSearch (TScalar tDISTANCE2, const TVector& rktPOINT, const TVector& rktVECTOR) const;

    TKDTreeNode* operator [] (size_t zPOS)
    {
      return getNode (zPOS);
    }
    
    void printDebug (void) const;
    
};  /* class TKDTree */


template <class TItem>
inline void TKDTree<TItem>::swapPoints (size_t I, size_t J)
{

  TKDTreeNode*   ptLeft  = getNode (I);
  TKDTreeNode*   ptRight = getNode (J);
  TItem          tData   = ptLeft->tData;

  ptLeft->tData  = ptRight->tData;
  ptRight->tData = tData;

}  /* swapPoints() */


template <class TItem>
void TKDTree<TItem>::balanceTree (size_t zFIRST, size_t zLAST)
{

  Byte           bDimension;
  size_t         zMedianPos;
  TKDTreeNode*   ptNode = getNode (zFIRST);

  if ( zLAST > zFIRST )
  {
//    cout << "Balancing [" << zFIRST << ", " << zLAST << "] (" << zLAST - zFIRST + 1 << ")" << endl;

    bDimension = findMaxSpreadDimension (zFIRST, zLAST);
    classify (zFIRST, zLAST, bDimension);

    zMedianPos = (zFIRST + zLAST) / 2;
    swapPoints (zFIRST, zMedianPos);
    
    ptNode->bAxis  = bDimension;
    ptNode->bFlags = 0;
    
    if ( zMedianPos >= (zFIRST + 1) )
    {
      balanceTree (zFIRST + 1, zMedianPos);
      ptNode->bFlags  |= HAS_LEFT_SON;
      ptNode->zLeftSon = zFIRST + 1;
    }

    if ( zLAST >= (zMedianPos + 1) )
    {
      balanceTree (zMedianPos + 1, zLAST);
      ptNode->bFlags   |= HAS_RIGHT_SON;
      ptNode->zRightSon = zMedianPos + 1;
    }
  }
  
}  /* balanceTree() */


template <class TItem>
Byte TKDTree<TItem>::findMaxSpreadDimension (size_t zFIRST, size_t zLAST)
{

  TKDTreeNode*   ptNode;
  TVector        tMin (SCALAR_MAX, SCALAR_MAX, SCALAR_MAX);
  TVector        tMax (-SCALAR_MAX, -SCALAR_MAX, -SCALAR_MAX);

  for (size_t J = zFIRST; ( J <= zLAST ) ;J++)
  {
    ptNode  = getNode (J);
    tMin[0] = min (tMin[0], ptNode->tData.tLocation[0]);
    tMin[1] = min (tMin[1], ptNode->tData.tLocation[1]);
    tMin[2] = min (tMin[2], ptNode->tData.tLocation[2]);
    tMax[0] = max (tMax[0], ptNode->tData.tLocation[0]);
    tMax[1] = max (tMax[1], ptNode->tData.tLocation[1]);
    tMax[2] = max (tMax[2], ptNode->tData.tLocation[2]);
  }

  TVector   tSpread = tMax - tMin;

  if ( fabs (tSpread[0]) > fabs (tSpread[1]) )
  {
    return ( fabs (tSpread[0]) > fabs (tSpread[2]) ) ? 0 : 2;
  }

  return ( fabs (tSpread[1]) > fabs (tSpread[2]) ) ? 1 : 2;

}  /* findMaxSpreadDimension() */


template <class TItem>
void TKDTree<TItem>::classify (size_t zFIRST, size_t zLAST, Byte bDIM)
{

  size_t   i, j;
  float    v;
  TItem    tData;
  size_t   k = (zFIRST + zLAST) / 2;

//  cout << "Classifying [" << zFIRST << ", " << zLAST << "] (" << zLAST - zFIRST + 1 << ")" << endl;

  while ( zFIRST < zLAST )
  {
    v = (getNode (zLAST))->tData.tLocation [bDIM];
    i = zFIRST;
    j = zLAST - 1;

    do
    {
      while ( ( (getNode (i))->tData.tLocation[bDIM] <= v ) && ( i < zLAST ) ) { i++; }
      while ( ( (getNode (j))->tData.tLocation[bDIM] >= v ) && ( j > zFIRST ) ) { j--; }
      tData                = (getNode (i))->tData;
      (getNode (i))->tData = (getNode (j))->tData;
      (getNode (j))->tData = tData;
    } while ( j > i );

    (getNode (j))->tData     = (getNode (i))->tData;
    (getNode (i))->tData     = (getNode (zLAST))->tData;
    (getNode (zLAST))->tData = tData;
    
    if ( i >= k )
    {
      zLAST = i - 1;
    }
    if ( i <= k )
    {
      zFIRST = i + 1;
    }
  }
  
}  /* classify() */


template <class TItem>
void TKDTree<TItem>::searchNN (TPriorityQueue<TItem>* ptPQUEUE, size_t zROOT, size_t N, const TVector& rktPOINT) const
{

  TKDTreeNode*   ptRoot;
  TVector        tVector;
  TScalar        tDistance2, tVal;

//  cout << "Searching node : " << zROOT << endl;

  ptRoot = getNode (zROOT);
  if ( ( ptRoot->bFlags & HAS_LEFT_SON ) || ( ptRoot->bFlags & HAS_RIGHT_SON ) )
  {
    tVector    = ptRoot->tData.tLocation - rktPOINT;
    tDistance2 = dotProduct (tVector, tVector);
//    cout << "Inserting : " << zROOT << ", " << sqrt (tDistance2) << endl;
    ptPQUEUE->insert (ptRoot->tData, tDistance2);

    tVal = rktPOINT [ptRoot->bAxis] - ptRoot->tData.tLocation [ptRoot->bAxis];
    if ( tVal < 0 )
    {
      if ( ptRoot->bFlags & HAS_LEFT_SON )
      {
//        cout << "Searching left son of " << zROOT << " : " << ptRoot->zLeftSon << endl;
        searchNN (ptPQUEUE, ptRoot->zLeftSon, N, rktPOINT);
      }
      if ( (tVal * tVal) < searchRadius (ptPQUEUE) )
      {
        if ( ptRoot->bFlags & HAS_RIGHT_SON )
        {
//          cout << "Searching right son of " << zROOT << " : " << ptRoot->zRightSon << endl;
          searchNN (ptPQUEUE, ptRoot->zRightSon, N, rktPOINT);
        }
      }
    }
    else
    {
      if ( ptRoot->bFlags & HAS_RIGHT_SON )
      {
//        cout << "Searching right son : " << ptRoot->zRightSon << endl;
        searchNN (ptPQUEUE, ptRoot->zRightSon, N, rktPOINT);
      }
      if ( (tVal * tVal) < searchRadius (ptPQUEUE) )
      {
        if ( ptRoot->bFlags & HAS_LEFT_SON )
        {
//          cout << "Searching left son : " << ptRoot->zLeftSon << endl;
          searchNN (ptPQUEUE, ptRoot->zLeftSon, N, rktPOINT);
        }
      }
    }
  }
  else
  {
    tVector    = ptRoot->tData.tLocation - rktPOINT;
    tDistance2 = dotProduct (tVector, tVector);

//    cout << "Inserting : " << zROOT << ", " << sqrt (tDistance2) << endl;
    ptPQUEUE->insert (ptRoot->tData, tDistance2);
  }
  
}  /* searchNN() */


template <class TItem>
void TKDTree<TItem>::recursiveRangeSearch (vector<TItem>* ptARRAY, size_t zROOT, TScalar tDISTANCE2, const TVector& rktPOINT) const
{

  TScalar        tDistance2, tVal;
  TKDTreeNode*   ptRoot = getNode (zROOT);

  if ( ( ptRoot->bFlags & HAS_LEFT_SON ) || ( ptRoot->bFlags & HAS_RIGHT_SON ) )
  {
    TVector   tVector = ptRoot->tData.tLocation - rktPOINT;
    
    tDistance2 = dotProduct (tVector, tVector);
    if ( tDistance2 <= tDISTANCE2 )
    {
      ptARRAY->push_back (ptRoot->tData);
    }

    tVal = rktPOINT [ptRoot->bAxis] - ptRoot->tData.tLocation [ptRoot->bAxis];
    if ( tVal < 0 )
    {
      if ( ptRoot->bFlags & HAS_LEFT_SON )
      {
        recursiveRangeSearch (ptARRAY, ptRoot->zLeftSon, tDISTANCE2, rktPOINT);
      }
      if ( (tVal * tVal) <= tDISTANCE2 )
      {
        if ( ptRoot->bFlags & HAS_RIGHT_SON )
        {
          recursiveRangeSearch (ptARRAY, ptRoot->zRightSon, tDISTANCE2, rktPOINT);
        }
      }
    }
    else
    {
      if ( ptRoot->bFlags & HAS_RIGHT_SON )
      {
        recursiveRangeSearch (ptARRAY, ptRoot->zRightSon, tDISTANCE2, rktPOINT);
      }
      if ( (tVal * tVal) < tDISTANCE2 )
      {
        if ( ptRoot->bFlags & HAS_LEFT_SON )
        {
          recursiveRangeSearch (ptARRAY, ptRoot->zLeftSon, tDISTANCE2, rktPOINT);
        }
      }
    }
  }
  else
  {
    TVector   tVector = ptRoot->tData.tLocation - rktPOINT;
    
    tDistance2 = dotProduct (tVector, tVector);

    if ( tDistance2 <= tDISTANCE2 )
    {
      ptARRAY->push_back (ptRoot->tData);
    }
  }
  
}  /* recursiveRangeSearch() */


template <class TItem>
void TKDTree<TItem>::recursiveLinearRangeSearch (vector<TItem>* ptARRAY, size_t zROOT, TScalar tDISTANCE2, const TVector& rktPOINT, const TVector& rktVECTOR) const
{

  TScalar        tDistance2, tVal;
  TKDTreeNode*   ptRoot = getNode (zROOT);

  if ( ( ptRoot->bFlags & HAS_LEFT_SON ) || ( ptRoot->bFlags & HAS_RIGHT_SON ) )
  {
    TVector   tVector = ptRoot->tData.tLocation - rktPOINT;
    TScalar   tAux    = dotProduct (tVector, rktVECTOR);
    
    tDistance2 = dotProduct (tVector, tVector) - (tAux * tAux);
    if ( tDistance2 <= tDISTANCE2 )
    {
      ptARRAY->push_back (ptRoot->tData);
    }

    if ( ptRoot->bFlags & HAS_LEFT_SON )
    {
      recursiveLinearRangeSearch (ptARRAY, ptRoot->zLeftSon, tDISTANCE2, rktPOINT, rktVECTOR);
    }
    if ( ptRoot->bFlags & HAS_RIGHT_SON )
    {
      recursiveLinearRangeSearch (ptARRAY, ptRoot->zRightSon, tDISTANCE2, rktPOINT, rktVECTOR);
    }
  }
  else
  {
    TVector   tVector = ptRoot->tData.tLocation - rktPOINT;
    TScalar   tAux    = dotProduct (tVector, rktVECTOR);
    
    tDistance2 = dotProduct (tVector, tVector) - (tAux * tAux);

    if ( tDistance2 <= tDISTANCE2 )
    {
      ptARRAY->push_back (ptRoot->tData);
    }
  }
  
}  /* recursiveLinearRangeSearch() */


template <class TItem>
TScalar TKDTree<TItem>::searchRadius (TPriorityQueue<TItem>* ptPQUEUE) const
{

  if ( ptPQUEUE->full() )
  {
    return (*ptPQUEUE)[0].tDistance;
  }

  return SCALAR_MAX;

}  /* searchRadius() */


template <class TItem>
void TKDTree<TItem>::insertNode (TItem tDATA)
{

  if ( zNumPoints == BLOCK_SIZE * zNumBlocks )
  {
    aptNodes [zNumBlocks] = new TKDTreeNode [BLOCK_SIZE];
    zNumBlocks++;
  }
  
  zNumPoints++;

  (getNode (zNumPoints - 1))->tData = tDATA;
  
}  /* insertNode() */


template <class TItem>
inline void TKDTree<TItem>::balance (void)
{

  balanceTree (0, zNumPoints - 1);

}  /* balance() */


template <class TItem>
TPriorityQueue<TItem>* TKDTree<TItem>::nearestNeighbours (size_t N, const TVector& rktPOINT) const
{

  TPriorityQueue<TItem>*   ptPQueue = new TPriorityQueue<TItem> (N);

  searchNN (ptPQueue, 0, N, rktPOINT);

  return ptPQueue;
  
}  /* nearestNeighbours() */


template <class TItem>
vector<TItem>* TKDTree<TItem>::rangeSearch (TScalar tDISTANCE2, const TVector& rktPOINT) const
{

  vector<TItem>*   ptArray = new vector<TItem>();

  recursiveRangeSearch (ptArray, 0, tDISTANCE2, rktPOINT);

  return ptArray;
  
}  /* rangeSearch() */


template <class TItem>
vector<TItem>* TKDTree<TItem>::linearRangeSearch (TScalar tDISTANCE2, const TVector& rktPOINT, const TVector& rktVECTOR) const
{

  TVector          tVector = rktVECTOR;
  vector<TItem>*   ptArray = new vector<TItem>();

  tVector.normalize();
  
  recursiveLinearRangeSearch (ptArray, 0, tDISTANCE2, rktPOINT, tVector);

  return ptArray;
  
}  /* linearRangeSearch() */


template <class TItem>
void TKDTree<TItem>::printDebug (void) const
{

  TKDTreeNode*   ptNode;

  cerr << TDebug::_indent() << "[_KDTree_]" << endl;

  TDebug::_push();
  
  for (size_t J = 0; ( J < zNumPoints ) ;J++)
  {
    ptNode = getNode (J);
    cerr << "<" << ptNode->tData.tLocation[0] << ", ";
    cerr << ptNode->tData.tLocation[1] << ", ";
    cerr << ptNode->tData.tLocation[2] << ">  <Axis : ";
    cerr << (int) ptNode->bAxis << "> <Flags : ";
    cerr << (bool) (ptNode->bFlags & HAS_LEFT_SON) << ", ";
    cerr << (bool) (ptNode->bFlags & HAS_RIGHT_SON) << ">";
    cerr << endl;
  }

  TDebug::_pop();
  
}  /* printDebug() */

#endif  /* _KDTREE__ */
