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
#include "hlapi/torus.h"
#include "llapi/root_solver.h"
#include "llapi/attribute.h"

TVector TTorus::localNormal (const TVector& rktPOINT) const
{

  TVector   tNormal;
  TScalar   tDistance = sqrt (rktPOINT.x() * rktPOINT.x() + rktPOINT.z() * rktPOINT.z());

  if ( tDistance > FX_EPSILON )
  {
    tNormal.set (rktPOINT.x() - tRadiusA * rktPOINT.x() / tDistance,
                 rktPOINT.y(),
                 rktPOINT.z() - tRadiusA * rktPOINT.z() / tDistance);
  }

  return tNormal;

}  /* localNormal() */


bool TTorus::initialize (void)
{
  bool val = true;

  TScalar   a  = sqrt (tRadiusA2);
  TScalar   b  = sqrt (tRadiusB2);
  TScalar   ab = a + b;
  
  tBoundingBox.set (TVector (-ab, -b, -ab), TVector (ab, b, ab));
  tBoundingBox.applyTransform (*ptMatrix);

  return val && TObject::initialize();
  
}  /* initialize() */


int TTorus::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "radius_a" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_REAL )
    {
      tRadiusA  = nVALUE.dValue;
      tRadiusA2 = tRadiusA * tRadiusA;
    }
#else
    magic_pointer<TAttribReal> r = get_real(nVALUE);
    if( !!r )
    {
      tRadiusA = r->tValue;
      tRadiusA2 = tRadiusA * tRadiusA;
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "radius_b" )
  {
#if !defined(NEW_ATTRIBUTES)    
    if ( eTYPE == FX_REAL )
    {
      tRadiusB2 = nVALUE.dValue * nVALUE.dValue;
    }
#else
    magic_pointer<TAttribReal> r = get_real(nVALUE);
    if( !!r )
    {
      tRadiusB2 = r->tValue * r->tValue;
    }
#endif    
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


int TTorus::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

#if !defined(NEW_ATTRIBUTES)  
  if ( rktNAME == "radius_a" )
  {
    rnVALUE.dValue = tRadiusA;
  }
  else if ( rktNAME == "radius_b" )
  {
    rnVALUE.dValue = sqrt (tRadiusB2);
  }
#else
  if ( rktNAME == "radius_a" )
  {
    rnVALUE = (user_arg_type)new TAttribReal (tRadiusA);
  }
  else if ( rktNAME == "radius_b" )
  {
    rnVALUE = (user_arg_type)new TAttribReal (sqrt (tRadiusB2));
  }
#endif
  else
  {
    return TObject::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TTorus::getAttributeList (TAttributeList& rtLIST) const
{

  TObject::getAttributeList (rtLIST);

  rtLIST ["radius_a"] = FX_REAL;
  rtLIST ["radius_b"] = FX_REAL;

}  /* getAttributeList() */


bool TTorus::findAllIntersections (const TRay& rktRAY, TSpanList& rtLIST) const
{

  TSurfaceData   tSurfaceData;
  TScalar        a[5], s[4];
  TScalar        c, d;
  TScalar        tFactor;
  int            iRoots;
  TRay           tRayIT        = rktRAY;
  bool           gIntersection = false;

  if ( !tBoundingBox.intersects (rktRAY) )
  {
    return false;
  }

  tFactor = tRayIT.applyTransform (ptInverseMatrix);

  // [CHECKME!]
  // >>>>>>>>>>>>>>>> 100.99
  //  if ( rktRAY.limit() < SCALAR_MAX )
  //  {
  //    tRayIT.setLimit (rktRAY.limit() / tFactor);
  //  }
  tRayIT.applyRangeFactor( 1.0 / tFactor );

  tSurfaceData.setup (this, rktRAY);

  c = dotProduct (tRayIT.location(), tRayIT.direction());
  d = dotProduct (tRayIT.location(), tRayIT.location()) - (tRadiusA2 + tRadiusB2);

  a[4] = 1.0;
  a[3] = 4 * c;
  a[2] = 2 * d + 4 * c * c + 4 * tRadiusA2 * tRayIT.direction().y() * tRayIT.direction().y();
  a[1] = 4 * c * d + 8 * tRadiusA2 * tRayIT.location().y() * tRayIT.direction().y();
  a[0] = d * d - 4 * tRadiusA2 * (tRadiusB2 - tRayIT.location().y() * tRayIT.location().y());

  iRoots = SolveQuartic (a, s);

  if ( iRoots > 0 )
  {
    //    if ( ( s[0] > FX_EPSILON ) && ( s[0] <= tRayIT.limit() ) )
    if( tRayIT.range().inside(s[0]) )
    {
      if ( tSurfaceData.setPoint (tFactor * s[0]) )
      {
        rtLIST.add (tSurfaceData);
        gIntersection = true;
      }
    }
    
    //    if ( ( s[1] > FX_EPSILON ) && ( s[1] <= tRayIT.limit() ) )
    if( tRayIT.range().inside(s[1]) )
    {
      if ( tSurfaceData.setPoint (tFactor * s[1]) )
      {
        rtLIST.add (tSurfaceData);
        gIntersection = true;
      }
    }
  }

  if ( iRoots > 2 )
  {
    //    if ( ( s[2] > FX_EPSILON ) && ( s[2] <= tRayIT.limit() ) )
    if( tRayIT.range().inside(s[2]) )
    {
      if ( tSurfaceData.setPoint (tFactor * s[2]) )
      {
        rtLIST.add (tSurfaceData);
        gIntersection = true;
      }
    }
    
    //    if ( ( s[3] > FX_EPSILON ) && ( s[3] <= tRayIT.limit() ) )
    if( tRayIT.range().inside(s[3]) )
    {
      if ( tSurfaceData.setPoint (tFactor * s[3]) )
      {
        rtLIST.add (tSurfaceData);
        gIntersection = true;
      }
    }
  }

  return gIntersection;

}  /* findAllIntersections() */


TVector TTorus::RandomPointOnSurface() const
{
  // For a torus, there are 2 angles, a theta, specifying how far around the z
  // axis to go, and a phi specifying how far around the tube to go.
  // FIXME!! This is not a uniformly random point.

  // The radius of the tube
  TScalar tube_rad = sqrt(tRadiusB2);

  // Randomly pick a theta in [0,2pi]
  TScalar theta = frand() * 2 * PI;

  // Randomly pick a phi in [0,2pi]
  TScalar phi = frand() * 2 * PI;

  // Find the y component (based on phi)
  TScalar y = tube_rad * sin(phi);

  // find the radius of the surface at the plane given by y
  TScalar rad1 = tRadiusA + tube_rad * cos(phi);

  // Find the x and z portions now (x = r * cos(theta), z = r * sin(theta) )

  TScalar x = rad1 * cos(theta);
  TScalar z = rad1 * sin(theta);
    
  return TVector(x,y,z);
}
