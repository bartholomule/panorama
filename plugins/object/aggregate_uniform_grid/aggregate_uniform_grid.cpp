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
#include "aggregate_uniform_grid.h"
#include "llapi/attribute.h"

DEFINE_PLUGIN ("AggregateUniformGrid", FX_OBJECT_CLASS, TAggregateUniformGrid);

void TAggregateUniformGrid::add (magic_pointer<TObject> ptOBJ)
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


bool TAggregateUniformGrid::initialize (void)
{

  magic_pointer<TObject> ptObj;
  magic_pointer<TMatrix>   ptMat;
  
  bool val = TAggregate::initialize();

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

    val = val && ptObj->initialize();
  }
  
  if ( fabs (tVoxelSize) < FX_EPSILON )
  {
    ptUniformGrid->calculateVoxelSize (tObjectList);
  }
  else
  {
    ptUniformGrid->setVoxelSize (tVoxelSize);
  }

  for (TObjectList::iterator tIter2 = tObjectList.begin(); ( tIter2 != tObjectList.end() ) ;tIter2++)
  {
    ptUniformGrid->addObject (*tIter2);
  }

  return val && ptUniformGrid->initialize();

}  /* initialize() */


int TAggregateUniformGrid::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "voxel_size" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_REAL )
    {
      tVoxelSize = nVALUE.dValue;
    }
#else
    magic_pointer<TAttribReal> r = get_real(nVALUE);
    if( !!r )
    {
      tVoxelSize = r->tValue;
    }
#endif
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
      //      tRay.setLimit (rtDATA.distance());
      tRay.setRange(tRay.range().min(), rtDATA.distance());
      gIntersection = true;
    }
  }

  return ( ptUniformGrid->findFirstIntersection (tRay, rtDATA) || gIntersection );

}  /* findFirstIntersection() */


void TAggregateUniformGrid::printDebug (const string& indent) const
{

  cerr << indent << "[_" << className() << "_]" << endl;

  string new_indent = TDebug::Indent(indent);

  cerr << new_indent << "Bounding box = "; tBoundingBox.printDebug(new_indent); cerr << endl;
  
  for (TObjectList::const_iterator tIter = tObjectList.begin(); ( tIter != tObjectList.end() ) ;tIter++)
  {
    (*tIter)->printDebug(new_indent);
  }

}  /* printDebug() */
