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

#include "aggregate_uniform_grid.h"

DEFINE_PLUGIN ("AggregateUniformGrid", FX_OBJECT_CLASS, TAggregateUniformGrid);

void TAggregateUniformGrid::add (TObject* ptOBJ)
{

  if ( ptOBJ->capabilities().gInfinite == true )
  {
    sCapabilities.gInfinite = true;
    tObjectList2.push_back (ptOBJ);
  }
  else
  {
    tObjectList.push_back (ptOBJ);
  }
  
}  /* add() */


void TAggregateUniformGrid::initialize (void)
{

  TObject*   ptObj;
  TMatrix*   ptMat;
  
  TAggregate::initialize();

  for (TObjectList::iterator tIter = tObjectList2.begin(); ( tIter != tObjectList2.end() ) ;tIter++)
  {
    ptObj = *tIter;
    
    ptMat = ptObj->transformMatrix();
    if ( ptMat )
    {
      ptObj->setTransformMatrix ((*ptMatrix) * (*ptMat));
    }

    ptMat = ptObj->inverseTransformMatrix();
    if ( ptMat )
    {
      ptObj->setInverseTransformMatrix ((*ptMat) * (*ptInverseMatrix));
    }

    ptObj->initialize();
  }
  
  if ( fabs (tVoxelSize) < FX_EPSILON )
  {
    ptUniformGrid->calculateVoxelSize (tObjectList);
  }
  else
  {
    ptUniformGrid->setVoxelSize (tVoxelSize);
  }

  for (vector<TObject*>::iterator tIter = tObjectList.begin(); ( tIter != tObjectList.end() ) ;tIter++)
  {
    ptUniformGrid->addObject (*tIter);
  }

  ptUniformGrid->initialize();

}  /* initialize() */


int TAggregateUniformGrid::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "voxel_size" )
  {
    if ( eTYPE == FX_REAL )
    {
      tVoxelSize = nVALUE.dValue;
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else
  {
    return TAggregate::setAttribute (rktNAME, nVALUE, eTYPE);
  }

  return FX_ATTRIB_OK;

  
}  /* setAttribute() */


bool TAggregateUniformGrid::findFirstIntersection (const TRay& rktRAY, TSurfaceData& rtDATA) const
{

  TRay   tRay          = rktRAY;
  bool   gIntersection = false;

  for (TObjectList::const_iterator tIter = tObjectList2.begin(); ( tIter != tObjectList2.end() ) ;tIter++)
  {
    if ( (*tIter)->findFirstIntersection (tRay, rtDATA) )
    {
      tRay.setLimit (rtDATA.distance());
      gIntersection = true;
    }
  }

  return ( ptUniformGrid->findFirstIntersection (tRay, rtDATA) || gIntersection );

}  /* findFirstIntersection() */


void TAggregateUniformGrid::printDebug (void) const
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
