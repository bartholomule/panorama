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
#include "hlapi/cone.h"
#include "llapi/attribute.h"

TVector TCone::localNormal (const TVector& rktPOINT) const
{

  if ( tMinRadius == 0 )
  {
    if ( fabs (rktPOINT.y() - 1) < FX_EPSILON )
    {
      return TVector (0, 1, 0);
    }
  
    TVector   tVect (rktPOINT.x(), rktPOINT.y() - 1, rktPOINT.z());
    TVector   tNormal = crossProduct (tVect, rktPOINT);
  
    tNormal = crossProduct (rktPOINT, tNormal);
  
    return tNormal;
  }
  else
  {
    if ( fabs (rktPOINT.y() - tHeight) < FX_EPSILON )
    {
      return TVector (0, 1, 0);
    }
    if ( fabs (rktPOINT.y() - tHeightToMinCircle) < FX_EPSILON )
    {
      return TVector (0, -1, 0);
    }
  
    TVector   tVect (rktPOINT.x(), rktPOINT.y() - tHeight, rktPOINT.z());
    TVector   tNormal = crossProduct (tVect, rktPOINT);
  
    tNormal = crossProduct (rktPOINT, tNormal);
  
    return tNormal;
  }

}  /* localNormal() */


bool TCone::intersectionsWithCanonicalCone (const TRay& rktRAY, TSpanList& rtLIST) const
{

  // [FIXME!] For some reason, this does NOT work.
  
  TSurfaceData   tSurfaceData;
  TScalar        a, b, c, d;
  TScalar        s1, s2;
  TVector        tPoint;
  TScalar        tFactor;
  TRay           tRayIT        = rktRAY;
  bool           gIntersection = false;

  tFactor = tRayIT.applyTransform (ptInverseMatrix);

  // [CHECKME!]
  // >>>>>>>>>>>>>>>> 100.99
  //  if ( rktRAY.limit() < SCALAR_MAX )
  //  {
  //    tRayIT.setLimit (rktRAY.limit() / tFactor);
  //  }
  tRayIT.applyRangeFactor (1.0 / tFactor);

  tSurfaceData.setup (this, rktRAY);
  
  if ( !( fabs (tRayIT.direction().y()) < FX_EPSILON ) )
  {
    //
    // Intersection with base circle
    //
    s1     = (1 - tRayIT.location().y()) / tRayIT.direction().y();
    tPoint = tRayIT.location() + (tRayIT.direction() * s1);
    if ( ( (tPoint.x() * tPoint.x() + tPoint.z() * tPoint.z()) <= 1 ) &&
	 //         ( s1 >= FX_EPSILON ) && ( s1 <= tRayIT.limit() )
	 tRayIT.range().inside(s1)
       )
    {
      if ( tSurfaceData.setPoint (tFactor * s1) )
      {
        rtLIST.add (tSurfaceData);
        gIntersection = true;
      }
    }
  }

  a = tRayIT.direction().x() * tRayIT.direction().x() +
      tRayIT.direction().z() * tRayIT.direction().z() -
      tRayIT.direction().y() * tRayIT.direction().y();
  b = (tRayIT.location().x() * tRayIT.direction().x() +
       tRayIT.location().z() * tRayIT.direction().z() -
       tRayIT.location().y() * tRayIT.direction().y()) * 2.0;
  c = tRayIT.location().x() * tRayIT.location().x() +
      tRayIT.location().z() * tRayIT.location().z() -
      tRayIT.location().y() * tRayIT.location().y();
  d = (b * b) - (4 * a * c);

  if ( d <= FX_EPSILON ) 
  {
    //
    // If there is no intersection or the intersection is in a single point.
    //
    return gIntersection;
  }
  else
  {
    d  = sqrt (d);
    s1 = (-b + d) / (2.0 * a);
    s2 = (-b - d) / (2.0 * a);

    //    if ( ( s1 >= FX_EPSILON ) && ( s1 <= tRayIT.limit() ) )
    if( tRayIT.range().inside(s1) )
    {
      tPoint = tRayIT.location() + (tRayIT.direction() * s1);
      if ( ( tPoint.y() > 0 ) && ( tPoint.y() < 1 ) )
      {
        if ( tSurfaceData.setPoint (tFactor * s1) )
        {
          rtLIST.add (tSurfaceData);
          gIntersection = true;
        }
      }
    }
    //    if ( ( s2 >= FX_EPSILON ) && ( s2 <= tRayIT.limit() ) )
    if( tRayIT.range().inside(s2) )
    {
      tPoint = tRayIT.location() + (tRayIT.direction() * s2);
      if ( ( tPoint.y() > 0 ) && ( tPoint.y() < 1 ) )
      {
        if ( tSurfaceData.setPoint (tFactor * s2) )
        {
          rtLIST.add (tSurfaceData);
          gIntersection = true;
        }
      }
    }
  }

  return gIntersection;

}  /* intersectionsWithCanonicalCone() */


bool TCone::intersectionsWithRootCone (const TRay& rktRAY, TSpanList& rtLIST) const
{

  TSurfaceData   tSurfaceData;
  TScalar        a, b, c, d;
  TScalar        s1, s2;
  TVector        tPoint;
  TScalar        tFactor;
  TRay           tRayIT            = rktRAY;
  bool           gIntersection     = false;
  Byte           bCapIntersections = 0;

  tFactor = tRayIT.applyTransform (ptInverseMatrix);
  
  // [CHECKME!]
  // >>>>>>>>>>>>>>>> 100.99
  //  if ( rktRAY.limit() < SCALAR_MAX )
  //  {
  //    tRayIT.setLimit (rktRAY.limit() / tFactor);
  //  }
  tRayIT.applyRangeFactor(1.0 / tFactor);

  tSurfaceData.setup (this, rktRAY);
  
  if ( !( fabs (tRayIT.direction().y()) < FX_EPSILON ) )
  {
    //
    // Intersection with Max circle
    //
    s1     = (tHeight - tRayIT.location().y()) / tRayIT.direction().y();
    tPoint = tRayIT.location() + (tRayIT.direction() * s1);
    if ( ( (tPoint.x() * tPoint.x() + tPoint.z() * tPoint.z()) <= tMaxRadius2 ) &&
	 //    ( s1 >= FX_EPSILON ) && ( s1 <= tRayIT.limit() )
	 tRayIT.range().inside(s1)
       )
    {
      if ( tSurfaceData.setPoint (tFactor * s1) )
      {
        rtLIST.add (tSurfaceData);
        bCapIntersections++;
        gIntersection = true;
      }
    }

    //
    // Intersection with Min circle
    //
    s1     = (tHeightToMinCircle - tRayIT.location().y()) / tRayIT.direction().y();
    tPoint = tRayIT.location() + (tRayIT.direction() * s1);
    if ( ( (tPoint.x() * tPoint.x() + tPoint.z() * tPoint.z()) <= tMinRadius2 ) &&
	 //         ( s1 >= FX_EPSILON ) && ( s1 <= tRayIT.limit() )
	 tRayIT.range().inside(s1)
       )
    {
      if ( tSurfaceData.setPoint (tFactor * s1) )
      {
        rtLIST.add (tSurfaceData);
        bCapIntersections++;
        gIntersection = true;
      }
    }
  }

  if ( bCapIntersections == 2 )
  {
    //
    // Ray intersects both caps, so there are no more intersections
    //
    return gIntersection;
  }
  
  a = tRayIT.direction().x() * tRayIT.direction().x() +
      tRayIT.direction().z() * tRayIT.direction().z() -
      tRayIT.direction().y() * tRayIT.direction().y() * tMaxRadiusByHeight2;
  b = (tRayIT.location().x() * tRayIT.direction().x() +
       tRayIT.location().z() * tRayIT.direction().z() -
       tRayIT.location().y() * tRayIT.direction().y() * tMaxRadiusByHeight2) * 2.0;
  c = tRayIT.location().x() * tRayIT.location().x() +
      tRayIT.location().z() * tRayIT.location().z() -
      tRayIT.location().y() * tRayIT.location().y() * tMaxRadiusByHeight2;
  d = (b * b) - (4 * a * c);

  if ( d <= FX_EPSILON ) 
  {
    //
    // If there is no intersection or the intersection is in a single point.
    //
    return gIntersection;
  }
  else
  {
    d  = sqrt (d);
    s1 = (-b + d) / (2.0 * a);
    s2 = (-b - d) / (2.0 * a);

    //    if ( ( s1 >= FX_EPSILON ) && ( s1 <= tRayIT.limit() ) )
    if( tRayIT.range().inside(s1) )
    {
      tPoint = tRayIT.location() + (tRayIT.direction() * s1);
      if ( ( tPoint.y() > tHeightToMinCircle ) && ( tPoint.y() < tHeight ) )
      {
        if ( tSurfaceData.setPoint (tFactor * s1) )
        {
          rtLIST.add (tSurfaceData);
          gIntersection = true;
        }
      }
    }
    //    if ( ( s2 >= FX_EPSILON ) && ( s2 <= tRayIT.limit() ) )
    if( tRayIT.range().inside(s2) )
    {
      tPoint = tRayIT.location() + (tRayIT.direction() * s2);
      if ( ( tPoint.y() > tHeightToMinCircle ) && ( tPoint.y() < tHeight ) )
      {
        if ( tSurfaceData.setPoint (tFactor * s2) )
        {
          rtLIST.add (tSurfaceData);
          gIntersection = true;
        }
      }
    }
  }

  return gIntersection;

}  /* intersectionsWithRootCone() */


bool TCone::initialize (void)
{
  bool val = true;
  
  if ( tMinRadius != 0 )
  {
    TVector   tTmp;
    TVector   tAxis;
    TMatrix   tMatrix = *ptMatrix;
    
    tMaxCirclePoint = tMatrix * tMaxCirclePoint;
    tMinCirclePoint = tMatrix * tMinCirclePoint;
    tAxis           = tMaxCirclePoint - tMinCirclePoint;
    tHeight         = tAxis.norm();
    
    tMatrix.setIdentity();
    ptMatrix->setIdentity();
    ptInverseMatrix->setIdentity();
    
    // We need that tMaxRadius > tMinRadius for the construction of the bounding box
    // We need that tMaxRadius - tMinRadius > FX_EPSILON for the next division
    // Joining both conditions...
    assert ( tMaxRadius - tMinRadius > FX_EPSILON );
    tHeightToMinCircle = tMinRadius * tHeight / (tMaxRadius - tMinRadius);
    tHeight           += tHeightToMinCircle;
    assert ( fabs (tHeight) > FX_EPSILON );
    tMaxRadiusByHeight2 = tMaxRadius2 / (tHeight * tHeight);

    // Find the coordinates of the apex, then translate it to the origin
    
    if ( ( fabs (tAxis.x()) < FX_EPSILON ) && ( fabs (tAxis.z()) < FX_EPSILON ) )
    {
      if ( dotProduct (tAxis, TVector (0, 1, 0)) < 0 )
      {
        rotate (TVector (180, 0, 0));
      }
    }
    else
    {
      TVector   tTmpX;
      TVector   tTmpZ;
      TScalar   tAxisYProyection;
      TScalar   tAxistTmpZProyection;
      
      tTmpX = crossProduct (TVector (0, 1, 0), tAxis);
      tTmpX.normalize();
      tTmpZ = crossProduct (tTmpX, TVector (0, 1, 0));
      tTmpZ.normalize();
      tAxisYProyection     = dotProduct (tAxis, TVector (0, 1, 0));
      tAxistTmpZProyection = dotProduct (tAxis, tTmpZ);

      rotate (tTmpX * 1.0, tTmpX * 2.0, atan2 (tAxistTmpZProyection, tAxisYProyection) * 180 / PI);
    }

    tTmp = (*ptMatrix) * TVector (0, tHeightToMinCircle, 0);
    translate ((tMatrix * tMinCirclePoint) - tTmp);

    tBoundingBox.set (TVector (-tMaxRadius, tHeightToMinCircle, -tMaxRadius), TVector (tMaxRadius, tHeight, tMaxRadius));
    tBoundingBox.applyTransform (*ptMatrix);
  }
  else
  {
    tBoundingBox.set (TVector (-1, 0, -1), TVector (1, 1, 1));
    tBoundingBox.applyTransform (*ptMatrix);
  }

  return val && TObject::initialize();

}  /* initialize() */


bool TCone::findAllIntersections (const TRay& rktRAY, TSpanList& rtLIST) const
{

  if ( !tBoundingBox.intersects (rktRAY) )
  {
    return false;
  }

  // [FIXME!] The canonical cone intersection does NOT work for some reason.
  // Fix it, then uncomment the below...
  /*
  if ( tMinRadius == 0 )
  {
    return intersectionsWithCanonicalCone (rktRAY, rtLIST);
  }
  else
  */
  {
    return intersectionsWithRootCone (rktRAY, rtLIST);
  }

  return false;
  
}  /* findAllIntersections() */


int TCone::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "max_circle_point" )
  {
#if !defined(NEW_ATTRIBUTES)    
    if ( eTYPE == FX_VECTOR )
    {
     tMaxCirclePoint = *((TVector*) nVALUE.pvValue);
    }
#else
    magic_pointer<TAttribVector> vec = get_vector(nVALUE);
    if( !!vec )
    {
      tMaxCirclePoint = vec->tValue;
    }
#endif    
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "min_circle_point" )
  {
#if !defined(NEW_ATTRIBUTES)        
    if ( eTYPE == FX_VECTOR )
    {
      tMinCirclePoint = *((TVector*) nVALUE.pvValue);
    }
#else
    magic_pointer<TAttribVector> vec = get_vector(nVALUE);
    if( !!vec )
    {
      tMinCirclePoint = vec->tValue;
    }
#endif    
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "max_radius" )
  {
#if !defined(NEW_ATTRIBUTES)    
    if ( eTYPE == FX_REAL )
    {
      tMaxRadius  = nVALUE.dValue;
      tMaxRadius2 = tMaxRadius * tMaxRadius;
    }
#else
    magic_pointer<TAttribReal> r = get_real(nVALUE);
    if( !!r )
    {
      tMaxRadius = r->tValue;
      tMaxRadius2 = tMaxRadius * tMaxRadius;      
    }
#endif    
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "min_radius" )
  {
#if !defined(NEW_ATTRIBUTES)    
    if ( eTYPE == FX_REAL )
    {
      tMinRadius  = nVALUE.dValue;
      tMinRadius2 = tMinRadius * tMinRadius;
    }
#else
    magic_pointer<TAttribReal> r = get_real(nVALUE);
    if( !!r )
    {
      tMinRadius = r->tValue;
      tMinRadius2 = tMinRadius * tMinRadius;      
    }
#endif    
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
    // [FIXME!]  This is a hack so that the cone will work.  When the canonical
    // cone is fixed, remove this section.
    if( tMinRadius == 0 )
    {
      tMinRadius = FX_EPSILON * 2;
      
      cerr << "[FIXME!] Hacking cone to prevent zero-radius." << endl;
    } // end [fixme]    
  }
  else
  {
    return TObject::setAttribute (rktNAME, nVALUE, eTYPE);
  }

  return FX_ATTRIB_OK;

}  /* setAttribute() */


int TCone::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "max_circle_point" )
  {
#if !defined(NEW_ATTRIBUTES)        
    rnVALUE.pvValue = &tMaxCirclePoint;
#else
    rnVALUE = (user_arg_type)new TAttribVector(tMaxCirclePoint);
#endif
  }
  else if ( rktNAME == "min_circle_point" )
  {
#if !defined(NEW_ATTRIBUTES)            
    rnVALUE.pvValue = &tMinCirclePoint;
#else
    rnVALUE = (user_arg_type)new TAttribVector(tMinCirclePoint);
#endif    
  }
  else if ( rktNAME == "max_radius" )
  {
#if !defined(NEW_ATTRIBUTES)            
    rnVALUE.dValue = tMaxRadius;
#else
    rnVALUE = (user_arg_type)new TAttribReal(tMaxRadius);
#endif
  }
  else if ( rktNAME == "min_radius" )
  {
#if !defined(NEW_ATTRIBUTES)            
    rnVALUE.dValue = tMinRadius;
#else
    rnVALUE = (user_arg_type)new TAttribReal(tMinRadius);
#endif
  }
  else
  {
    return TObject::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TCone::getAttributeList (TAttributeList& rtLIST) const
{

  TObject::getAttributeList (rtLIST);

  rtLIST ["max_circle_point"] = FX_VECTOR;
  rtLIST ["min_circle_point"] = FX_VECTOR;
  rtLIST ["max_radius"]       = FX_REAL;
  rtLIST ["min_radius"]       = FX_REAL;

}  /* getAttributeList() */
