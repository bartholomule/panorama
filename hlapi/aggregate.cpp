/*
*  Copyright (C) 1998, 1999 Angel Jimenez Jimenez and Carlos Jimenez Moreno
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
#include "hlapi/aggregate.h"
#include "llapi/object_required.h"


bool TAggregate::initialize (void)
{
  bool val = TObject::initialize();
  
  TObjectList::iterator   tIter;
  magic_pointer<TObject>  ptObj;
  magic_pointer<TMatrix>  ptMat;

  for (tIter = tObjectList.begin(); ( tIter != tObjectList.end() ) ;tIter++)
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

  tBoundingBox = Merge (tObjectList);

  return val;
}  /* initialize() */


void TAggregate::finalize (void)
{

  magic_pointer<TObject> ptObj;

  for (TObjectList::iterator tIter = tObjectList.begin(); ( tIter != tObjectList.end() ) ;tIter++)
  {
    ptObj = *tIter;
    
    ptObj->finalize();
  }

}  /* finalize() */


bool TAggregate::findFirstIntersection (const TRay& rktRAY, TSurfaceData& rtDATA) const
{

  TRay   tRay          = rktRAY;
  bool   gIntersection = false;

//  if ( !tBoundingBox.intersects (rktRAY) )
//  {
//    return false;
//  }
  
  for (TObjectList::const_iterator tIter = tObjectList.begin(); ( tIter != tObjectList.end() ) ;tIter++)
  {
    if ( (*tIter)->findFirstIntersection (tRay, rtDATA) )
    {
      // Set the maximum distance in the distance to filter out all subsequent
      // hits at larger distances.
      tRay.setRange (tRay.range().min(), rtDATA.distance());
      gIntersection = true;
    }
  }

  return gIntersection;

}  /* findFirstIntersection() */


bool TAggregate::findAllIntersections (const TRay& rktRAY, TSpanList& rtLIST) const
{

  bool   gIntersection = false;

//  if ( !tBoundingBox.intersects (rktRAY) )
//  {
//    return false;
//  }
  
  for (TObjectList::const_iterator tIter = tObjectList.begin(); ( tIter != tObjectList.end() ) ;tIter++)
  {
    if ( (*tIter)->findAllIntersections (rktRAY, rtLIST) )
    {
      gIntersection = true;
    }
  }
  
  return gIntersection;

}  /* findAllIntersections() */


void TAggregate::setMaterial (magic_pointer<TMaterial> ptMATERIAL)
{

  for (TObjectList::iterator tIter = tObjectList.begin(); ( tIter != tObjectList.end() ) ;tIter++)
  {
    (*tIter)->setMaterial (ptMATERIAL);
  }

  ptMaterial = ptMATERIAL;
  
}  /* setMaterial() */


void TAggregate::setObjectCode (size_t zCODE)
{

  zObjectCode = zCODE++;
  
  for (TObjectList::iterator tIter = tObjectList.begin(); ( tIter != tObjectList.end() ) ;tIter++)
  {
    (*tIter)->setObjectCode (zCODE++);
  }

}  /* setObjectCode() */


void TAggregate::addFilter (const magic_pointer<TObjectFilter> pktFILTER)
{

  for (TObjectList::iterator tIter = tObjectList.begin(); ( tIter != tObjectList.end() ) ;tIter++)
  {
    (*tIter)->addFilter (pktFILTER);
  }

  tObjectFilterList.push_back (pktFILTER);
  
}  /* addFilter() */


// Attribute management
int TAggregate::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{
  if ( rktNAME == "containsobjects" )
  {
    return FX_ATTRIB_USER_ERROR;
  }
  else
  {
    return TObject::setAttribute (rktNAME, nVALUE, eTYPE);
  }
  return FX_ATTRIB_OK;
} /* setAttribute() */

int TAggregate::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{
  if ( rktNAME == "containsobjects" )
  {
#if !defined(NEW_ATTRIBUTES)
    rnVALUE.gValue = !tObjectList.empty();
#else
    rnVALUE = (user_arg_type)new TAttribBool(!tObjectList.empty());
#endif
  }
  else
  {
    return TObject::getAttribute (rktNAME, rnVALUE);
  }
  
  return FX_ATTRIB_OK;
} /* getAttribute() */

void TAggregate::getAttributeList (TAttributeList& rtLIST) const
{
  TObject::getAttributeList(rtLIST);

  rtLIST ["containsobjects"] = FX_BOOL;
  
} /* getAttributeList() */

void TAggregate::printDebug (const string& indent) const
{

  GOM.debug() << indent << "[_" << className() << "_]" << endl;

  string new_indent = TDebug::Indent(indent);
  
  GOM.debug() << new_indent << "Bounding box = ";
  tBoundingBox.printDebug(new_indent);
  GOM.debug() << endl;
  
  for (TObjectList::const_iterator tIter = tObjectList.begin(); ( tIter != tObjectList.end() ) ;tIter++)
  {
    (*tIter)->printDebug(new_indent);
  }
  GOM.debug() << indent << "." << endl;
  
}  /* printDebug() */

bool TAggregate::containsObject (const magic_pointer<TObject> pktObject)
{
  for( TObjectList::const_iterator i = tObjectList.begin();
       i != tObjectList.end();
       ++i )
  {
    if( *i == pktObject )
    {
      return true;
    }
  }
  return false;
}

TUserFunctionMap TAggregate::getUserFunctions()
{
  TUserFunctionMap ufm = TObject::getUserFunctions();

  ufm["setMaterial"]     = create_user_function(this,&TAggregate::setMaterial);
  ufm["addObject"]       = create_user_function(this,&TAggregate::add);
  ufm["containsObjects"] = create_user_function(this,&TAggregate::containsObjects);
  ufm["containsObject"]  = create_user_function(this,&TAggregate::containsObject);
  ufm["getClassName"]    = create_user_function(this,&TAggregate::className);  
  
  return ufm;
}
