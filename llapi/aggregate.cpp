/*
*  Copyright (C) 1998 Angel Jimenez Jimenez and Carlos Jimenez Moreno
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

#include "llapi/aggregate.h"

void TAggregate::initialize (void)
{

  vector<TObject*>::iterator   tIter;

  for (tIter = tObjectList.begin(); ( tIter != tObjectList.end() ) ;tIter++)
  {
    (*tIter)->initialize();
  }

  tBoundingBox = Merge (tObjectList);
  
}  /* initialize() */


bool TAggregate::findFirstIntersection (const TRay& rktRAY, TSurfaceData& rtDATA) const
{

  TRay   tRay          = rktRAY;
  bool   gIntersection = false;

//  if ( !tBoundingBox.intersects (rktRAY, tLIMIT) )
//  {
//    return false;
//  }
  
  for (vector<TObject*>::const_iterator tIter = tObjectList.begin(); ( tIter != tObjectList.end() ) ;tIter++)
  {
    if ( (*tIter)->findFirstIntersection (tRay, rtDATA) )
    {
      tRay.setLimit (rtDATA.distance());
      gIntersection = true;
    }
  }

  return gIntersection;

}  /* findFirstIntersection() */


bool TAggregate::findAllIntersections (const TRay& rktRAY, TSpanList& rtLIST) const
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


void TAggregate::setMaterial (TMaterial* ptMATERIAL)
{

  for (vector<TObject*>::iterator tIter = tObjectList.begin(); ( tIter != tObjectList.end() ) ;tIter++)
  {
    (*tIter)->setMaterial (ptMATERIAL);
  }

  ptMaterial = ptMATERIAL;
  
}  /* setMaterial() */


void TAggregate::setObjectCode (size_t zCODE)
{

  zObjectCode = zCODE++;
  
  for (vector<TObject*>::iterator tIter = tObjectList.begin(); ( tIter != tObjectList.end() ) ;tIter++)
  {
    (*tIter)->setObjectCode (zCODE++);
  }

}  /* setObjectCode() */


void TAggregate::printDebug (void) const
{

  cerr << TDebug::_indent() << "[_" << className() << "_]" << endl;

  TDebug::_push();

  cerr << TDebug::_indent() << "Bounding box = "; tBoundingBox.printDebug(); cerr << endl;
  
  for (vector<TObject*>::const_iterator tIter = tObjectList.begin(); ( tIter != tObjectList.end() ) ;tIter++)
  {
    (*tIter)->printDebug();
  }

  TDebug::_pop();
  
}  /* printDebug() */
