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

#include "llapi/warning_eliminator.h"
#include "hlapi/csg.h"

void TCsg::mergeUnion (TSpanList& rtLIST1, const TSpanList& rktLIST2, const TVector& rktRAY_DIR) const
{

  Byte                        bList;
  const TSurfaceData*         pktData;
  bool                        gUnionInside;
  TSpanList::iterator         tIter1      = rtLIST1.begin();
  TSpanList::const_iterator   tIter2      = rktLIST2.begin();
  bool                        gLInside    = false;
  bool                        gRInside    = false;
  bool                        gListInside = false;
  bool                        gEmptyLeft  = false;
  bool                        gEmptyRight = false;

  gEmptyLeft  = rtLIST1.empty();
  gEmptyRight = rktLIST2.empty();

  if ( !gEmptyLeft )
  {
    gLInside = ( dotProduct (rtLIST1.first().normal(), rktRAY_DIR) >= 0 );
  }
  if ( !gEmptyRight )
  {
    gRInside = ( dotProduct (rktLIST2.first().normal(), rktRAY_DIR) >= 0 );
  }
  
  while ( !gEmptyLeft || !gEmptyRight )
  {
    if ( gEmptyLeft )
    {
      pktData = &((*tIter2).second);
      bList   = 2;
      
      gRInside = !gRInside;
    }
    else if ( gEmptyRight )
    {
      pktData = &((*tIter1).second);
      bList   = 1;
        
      gLInside = !gLInside;
    }
    else
    {
      pktData = &((*tIter1).second);
      if ( pktData->distance() <= (*tIter2).second.distance() )
      {
        bList = 1;
        gLInside = !gLInside;
      }
      else
      {
        pktData = &((*tIter2).second);
        bList   = 2;

        gRInside = !gRInside;
      }
    }

    gUnionInside = ( gLInside || gRInside );

    if ( gUnionInside != gListInside )
    {
      gListInside = gUnionInside;
      if ( bList == 1 )
      {
        tIter1++;
      }
      else
      {
        rtLIST1[(*tIter2).second.distance()] = (*tIter2).second;
        tIter2++;
      }
    }
    else
    {
      if ( bList == 1 )
      {
        TSpanList::iterator   tIterTemp = tIter1;

        tIterTemp++;
        rtLIST1.erase (tIter1);
        tIter1 = tIterTemp;
      }
      else
      {
        tIter2++;
      }
    }
    
    gEmptyLeft  = ( tIter1 == rtLIST1.end() );
    gEmptyRight = ( tIter2 == rktLIST2.end() );
  }

}  /* mergeUnion() */


void TCsg::mergeIntersection (TSpanList& rtLIST1, const TSpanList& rktLIST2, const TVector& rktRAY_DIR) const
{

  Byte                        bList;
  const TSurfaceData*         pktData;
  bool                        gIntersectionInside;
  TSpanList::iterator         tIter1      = rtLIST1.begin();
  TSpanList::const_iterator   tIter2      = rktLIST2.begin();
  bool                        gLInside    = false;
  bool                        gRInside    = false;
  bool                        gListInside = false;
  bool                        gEmptyLeft  = false;
  bool                        gEmptyRight = false;

  gEmptyLeft  = rtLIST1.empty();
  gEmptyRight = rktLIST2.empty();

  if ( !gEmptyLeft )
  {
    gLInside = ( dotProduct (rtLIST1.first().normal(), rktRAY_DIR) >= 0 );
  }
  if ( !gEmptyRight )
  {
    gRInside = ( dotProduct (rktLIST2.first().normal(), rktRAY_DIR) >= 0 );
  }
  
  while ( !gEmptyLeft || !gEmptyRight )
  {
    if ( gEmptyLeft )
    {
      pktData = &((*tIter2).second);
      bList   = 2;
      
      gRInside = !gRInside;
    }
    else if ( gEmptyRight )
    {
      pktData = &((*tIter1).second);
      bList   = 1;
        
      gLInside = !gLInside;
    }
    else
    {
      pktData = &((*tIter1).second);
      if ( pktData->distance() <= (*tIter2).second.distance() )
      {
        bList = 1;
        gLInside = !gLInside;
      }
      else
      {
        pktData = &((*tIter2).second);
        bList   = 2;

        gRInside = !gRInside;
      }
    }

    gIntersectionInside = ( gLInside && gRInside );

    if ( gIntersectionInside != gListInside )
    {
      gListInside = gIntersectionInside;
      if ( bList == 1 )
      {
        tIter1++;
      }
      else
      {
        rtLIST1[(*tIter2).second.distance()] = (*tIter2).second;
        tIter2++;
      }
    }
    else
    {
      if ( bList == 1 )
      {
        TSpanList::iterator   tIterTemp = tIter1;

        tIterTemp++;
        rtLIST1.erase (tIter1);
        tIter1 = tIterTemp;
      }
      else
      {
        tIter2++;
      }
    }
    
    gEmptyLeft  = ( tIter1 == rtLIST1.end() );
    gEmptyRight = ( tIter2 == rktLIST2.end() );
  }
  
}  /* mergeIntersection() */


void TCsg::mergeDifference (TSpanList& rtLIST1, const TSpanList& rktLIST2, const TVector& rktRAY_DIR) const
{

  Byte                        bList;
  const TSurfaceData*         pktData;
  bool                        gDiffInside;
  TSpanList::iterator         tIter1      = rtLIST1.begin();
  TSpanList::const_iterator   tIter2      = rktLIST2.begin();
  bool                        gLInside    = false;
  bool                        gRInside    = false;
  bool                        gListInside = false;
  bool                        gEmptyLeft  = false;
  bool                        gEmptyRight = false;

  gEmptyLeft  = rtLIST1.empty();
  gEmptyRight = rktLIST2.empty();

  if ( !gEmptyLeft )
  {
    gLInside = ( dotProduct (rtLIST1.first().normal(), rktRAY_DIR) >= 0 );
  }
  if ( !gEmptyRight )
  {
    gRInside = ( dotProduct (rktLIST2.first().normal(), rktRAY_DIR) >= 0 );
  }
  
  while ( !gEmptyLeft || !gEmptyRight )
  {
    if ( gEmptyLeft )
    {
      pktData = &((*tIter2).second);
      bList   = 2;
      
      gRInside = !gRInside;
    }
    else if ( gEmptyRight )
    {
      pktData = &((*tIter1).second);
      bList   = 1;
        
      gLInside = !gLInside;
    }
    else
    {
      pktData = &((*tIter1).second);
      if ( (*tIter1).first <= (*tIter2).first )
      {
        bList = 1;
        gLInside = !gLInside;
      }
      else
      {
        pktData = &((*tIter2).second);
        bList   = 2;

        gRInside = !gRInside;
      }
    }

    gDiffInside = ( gLInside && !gRInside );
    if ( gDiffInside != gListInside )
    {
      gListInside = gDiffInside;
      
      if ( bList == 1 )
      {
        tIter1++;
      }
      else
      {
        rtLIST1[(*tIter2).first] = (*tIter2).second;

        TSpanList::iterator   tIterTemp = rtLIST1.find ((*tIter2).first);

        (*tIterTemp).second.flipNormal();
        tIter2++;
      }
    }
    else
    {
      if ( bList == 1 )
      {
        TSpanList::iterator   tIterTemp = tIter1;

        tIterTemp++;
        rtLIST1.erase (tIter1);
        tIter1 = tIterTemp;
      }
      else
      {
        tIter2++;
      }
    }
    
    gEmptyLeft  = ( tIter1 == rtLIST1.end() );
    gEmptyRight = ( tIter2 == rktLIST2.end() );
  }
  
}  /* mergeDifference() */


bool TCsg::findFirstIntersection (const TRay& rktRAY, TSurfaceData& rtDATA) const
{

  TSpanList   tList;
  bool        gIntersection;

  gIntersection = findAllIntersections (rktRAY, tList);

  if ( gIntersection )
  {
    rtDATA = tList.first();
  }

  return gIntersection;

}  /* findFirstIntersection() */


bool TCsg::findAllIntersections (const TRay& rktRAY, TSpanList& rtLIST) const
{

  TSpanList                     tList;
  TObjectList::const_iterator   tIter              = tObjectList.begin();
  bool                          gIntersection      = false;
  bool                          gLeftIntersection  = false;
  bool                          gRightIntersection = false;

  if ( !tBoundingBox.intersects (rktRAY) )
  {
    return false;
  }
  
  gLeftIntersection = (*tIter)->findAllIntersections (rktRAY, rtLIST);

  if ( !gLeftIntersection && ( eOperation != FX_CSG_UNION ) )
  {
    return false;
  }

  for (tIter++; ( tIter != tObjectList.end() ) ;tIter++)
  {
    gRightIntersection = (*tIter)->findAllIntersections (rktRAY, tList);

    switch (eOperation)
    {
      case FX_CSG_UNION:
      {
        mergeUnion (rtLIST, tList, rktRAY.direction());
      }
      break;
      
      case FX_CSG_INTERSECTION:
      {
        mergeIntersection (rtLIST, tList, rktRAY.direction());
      }
      break;
      
      case FX_CSG_DIFFERENCE:
      {
        mergeDifference (rtLIST, tList, rktRAY.direction());
      }
    }

    tList.clear();
    if ( !rtLIST.empty() )
    {
      gIntersection = true;
    }
  }
  
  return gIntersection;
 
}  /* findAllIntersections() */


bool TCsg::initialize (void)
{
  
  TObjectList::iterator   tIter;

  assert ( tObjectList.size() >= 2 );

  bool val = TAggregate::initialize();

  switch ( eOperation )
  {
    case FX_CSG_UNION:
    {
      tBoundingBox = Merge (tObjectList);
    }
    break;

    case FX_CSG_INTERSECTION:
    {
      tIter = tObjectList.begin();
      tBoundingBox = (*tIter)->boundingBox();
      for (tIter++; ( tIter != tObjectList.end() ) ;tIter++)
      {
        tBoundingBox = Intersection (tBoundingBox, (*tIter)->boundingBox());
      }
    }
    break;

    case FX_CSG_DIFFERENCE:
    {
      tBoundingBox = tObjectList.front()->boundingBox();
    }
    break;
  }
  
  return val;

}  /* initialize() */
