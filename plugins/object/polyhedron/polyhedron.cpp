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

#include <list>
#include "polyhedron.h"

bool               TPolyhedron::_gClassInitialized = false;
list<TPlaneData>   TPolyhedron::_atPlaneDataList[5];

DEFINE_PLUGIN ("Polyhedron", FX_OBJECT_CLASS, TPolyhedron);

void TPolyhedron::_initializeClass (void)
{

  // Cube
  _atPlaneDataList[FX_CUBE].push_back (TPlaneData (0, 1, 0, -1));
  _atPlaneDataList[FX_CUBE].push_back (TPlaneData (0, -1, 0, -1));
  _atPlaneDataList[FX_CUBE].push_back (TPlaneData (-1, 0, 0, -1));
  _atPlaneDataList[FX_CUBE].push_back (TPlaneData (1, 0, 0, -1));
  _atPlaneDataList[FX_CUBE].push_back (TPlaneData (0, 0, 1, -1));
  _atPlaneDataList[FX_CUBE].push_back (TPlaneData (0, 0, -1, -1));

}  /* _initializeClass() */


void TPolyhedron::initialize (void)
{

  if ( !_gClassInitialized )
  {
    _initializeClass();
  }

//  tBoundingBox.set (TVector (-ab, -b, -ab), TVector (ab, b, ab));
//  tBoundingBox.applyTransform (*ptMatrix);

}  /* initialize() */


int TPolyhedron::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "shape" )
  {
    if ( eTYPE == FX_REAL )
    {
      eShape = (EShape) ((int) nVALUE.dValue);
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else
  {
    return TObject::setAttribute (rktNAME, nVALUE, eTYPE);
  }

  return FX_ATTRIB_OK;

}  /* setAttribute() */


int TPolyhedron::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "shape" )
  {
    rnVALUE.dValue = eShape;
  }
  else
  {
    return TObject::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TPolyhedron::getAttributeList (TAttributeList& rtLIST) const
{

  TObject::getAttributeList (rtLIST);

  rtLIST ["shape"] = FX_REAL;

}  /* getAttributeList() */


bool TPolyhedron::findAllIntersections (const TRay& rktRAY, TSpanList& rtLIST) const
{

  TSurfaceData        tSurfaceData;
  TScalar             tFactor;
  TScalar             t, tDen, tDist;
  const TPlaneData*   pktPlaneData;
  TVector             tNormalNear, tNormalFar;
  TRay                tRayIT        = rktRAY;
  bool                gIntersection = false;
  TScalar             tNear         = -SCALAR_MAX;
  TScalar             tFar          = SCALAR_MAX;

//  if ( !tBoundingBox.intersects (rktRAY) )
//  {
//    return false;
//  }

  tFactor = tRayIT.applyTransform (ptInverseMatrix);

  if ( rktRAY.limit() < SCALAR_MAX )
  {
    tRayIT.setLimit (rktRAY.limit() / tFactor);
  }

  tSurfaceData.setup (this, rktRAY);

//  cout << "poly : " << endl;
  
  for (list<TPlaneData>::const_iterator tIter = _atPlaneDataList[eShape].begin(); ( tIter != _atPlaneDataList[eShape].end() ) ;tIter++)
  {
    pktPlaneData = &(*tIter);

    tDist = dotProduct (pktPlaneData->tNormal, tRayIT.location()) + pktPlaneData->D;
    tDen  = dotProduct (pktPlaneData->tNormal, tRayIT.direction());

    if ( fabs (tDen) < FX_EPSILON )
    {
      // Ray is parallel to plane
      if ( tDist >= 0 )
      {
        return false;
      }
    }
    else
    {
      t = -tDist / tDen;

      if ( tDen > 0 )
      {
//        cout << "t (far) = " << t;
        if ( ( t < tFar ) )
        {
//          cout << ", assigned";
          tFar       = t;
          tNormalFar = pktPlaneData->tNormal;
        }
      }
      else
      {
//        cout << "t (near) = " << t;
        if ( ( t > tNear ) )
        {
//          cout << ", assigned";
          tNear       = t;
          tNormalNear = pktPlaneData->tNormal;
        }
      }
//      cout << endl;
      if ( tNear >= tFar )
      {
        return false;
      }
    }
  }

//  cout << "near : " << tNear << endl;
//  cout << "far  : " << tFar << endl;

  if ( ( tNear > FX_EPSILON ) && ( tNear < tRayIT.limit() ) )
  {
    tNormalNear.applyTransform (ptMatrix);
    tNormalNear.normalize();
      
    tSurfaceData.setPoint (tFactor * tNear, tNormalNear);
    
    rtLIST.add (tSurfaceData);
    gIntersection = true;
  }
    
  if ( ( tFar > FX_EPSILON ) && ( tFar < tRayIT.limit() ) )
  {
    tNormalFar.applyTransform (ptMatrix);
    tNormalFar.normalize();
      
    tSurfaceData.setPoint (tFactor * tFar, tNormalFar);
    
    rtLIST.add (tSurfaceData);
    gIntersection = true;
  }
  
  return gIntersection;

}  /* findAllIntersections() */


/*bool TPolyhedron::findAllIntersections (const TRay& rktRAY, TSpanList& rtLIST) const
{

  TSurfaceData        tSurfaceData;
  TScalar             tFactor;
  TScalar             t, tDen, tDist;
  const TPlaneData*   pktPlaneData;
  TRay                tRayIT        = rktRAY;
  bool                gIntersection = false;
  TInterval           tInt (-SCALAR_MAX, SCALAR_MAX);

//  if ( !tBoundingBox.intersects (rktRAY) )
//  {
//    return false;
//  }

  tFactor = tRayIT.applyTransform (ptInverseMatrix);

  if ( rktRAY.limit() < SCALAR_MAX )
  {
    tRayIT.setLimit (rktRAY.limit() / tFactor);
  }

  tSurfaceData.setup (this, rktRAY);

//  cout << "poly : " << endl;
  
  for (list<TPlaneData>::const_iterator tIter = atPlaneDataList[eShape].begin(); ( tIter != atPlaneDataList[eShape].end() ) ;tIter++)
  {
    pktPlaneData = &(*tIter);

    tDist = dotProduct (pktPlaneData->tNormal, tRayIT.location()) + pktPlaneData->D;
    tDen  = dotProduct (pktPlaneData->tNormal, tRayIT.direction());

    if ( fabs (tDen) < FX_EPSILON )
    {
      // Ray is parallel to plane
      if ( tDist >= 0 )
      {
        return false;
      }
    }
    else
    {
      t = -tDist / tDen;
      
      if ( tDen > 0 )
      {
        tInt = Intersection (tInt, TInterval (-SCALAR_MAX, t));
      }
      else
      {
        tInt = Intersection (tInt, TInterval (t, SCALAR_MAX));
      }

      if ( tInt.empty() )
      {
        return false;
      }
    }
  }

//  cout << "min : " << tInt.min() << endl;
//  cout << "max : " << tInt.max() << endl;

  if ( ( tInt.min() > FX_EPSILON ) && ( tInt.min() < tRayIT.limit() ) )
  {
    if ( tSurfaceData.setPoint (tFactor * tInt.min()) )
    {
      rtLIST.add (tSurfaceData);
      gIntersection = true;
    }
  }
    
  if ( ( tInt.max() > FX_EPSILON ) && ( tInt.max() < tRayIT.limit() ) )
  {
    if ( tSurfaceData.setPoint (tFactor * tInt.max()) )
    {
      rtLIST.add (tSurfaceData);
      gIntersection = true;
    }
  }
    
  return gIntersection;

}*/  /* findAllIntersections() */
