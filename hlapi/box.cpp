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

#include <cmath>
#include <iostream>
#include "hlapi/box.h"

TVector TBox::localNormal (const TVector& rktPOINT) const
{

  TVector   tNormal;

  if ( fabs (rktPOINT.x() + 0.5) <= FX_EPSILON  )
  {
    tNormal.set (-1, 0, 0);
  }
  else if ( fabs (rktPOINT.x() - 0.5) <= FX_EPSILON )
  {
    tNormal.set (1, 0, 0);
  }
  else if ( fabs (rktPOINT.y() + 0.5) <= FX_EPSILON  )
  {
    tNormal.set (0, -1, 0);
  }
  else if ( fabs (rktPOINT.y() - 0.5) <= FX_EPSILON )
  {
    tNormal.set (0, 1, 0);
  }
  else if ( fabs (rktPOINT.z() + 0.5) <= FX_EPSILON  )
  {
    tNormal.set (0, 0, -1);
  }
  else if ( fabs (rktPOINT.z() - 0.5) <= FX_EPSILON )
  {
    tNormal.set (0, 0, 1);
  }
  else
  {
    rktPOINT.printDebug();
    assert ( false );
  }

  return tNormal;

}  /* localNormal() */


void TBox::initialize (void)
{

  tBoundingBox.set (TVector (-0.5, -0.5, -0.5), TVector (0.5, 0.5, 0.5));
  tBoundingBox.applyTransform (*ptMatrix);

  TObject::initialize();

}  /* initialize() */


bool TBox::findFirstIntersection (const TRay& rktRAY, TSurfaceData& rtDATA) const
{

  TInterval   tIntX, tIntY, tIntZ, tIntTmp;
  TScalar     tFactor;
  TRay        tRayIT = rktRAY;

  if ( !tBoundingBox.intersects (rktRAY) )
  {
    return false;
  }
  
  tFactor = tRayIT.applyTransform (ptInverseMatrix);

  if ( rktRAY.limit() < SCALAR_MAX )
  {
    tRayIT.setLimit (rktRAY.limit() / tFactor);
  }

  if ( fabs (tRayIT.direction().x()) < FX_EPSILON )
  {
    // Ray is parallel to YZ plane
    if ( !( ( tRayIT.location().x() >= -0.5 ) && ( tRayIT.location().x() <= 0.5 ) ) )
    {
      return false;
    }
    tIntX.set (0, SCALAR_MAX);
  }
  else
  {
    tIntX.set ((-0.5 - tRayIT.location().x()) / tRayIT.direction().x(), (0.5 - tRayIT.location().x()) / tRayIT.direction().x());
  }

  if ( fabs (tRayIT.direction().y()) < FX_EPSILON )
  {
    // Ray is parallel to ZX plane
    if ( !( ( tRayIT.location().y() >= -0.5 ) && ( tRayIT.location().y() <= 0.5 ) ) )
    {
      return false;
    }
    tIntY.set (0, SCALAR_MAX);
  }
  else
  {
    tIntY.set ((-0.5 - tRayIT.location().y()) / tRayIT.direction().y(), (0.5 - tRayIT.location().y()) / tRayIT.direction().y());
  }

  if ( fabs (tRayIT.direction().z()) < FX_EPSILON )
  {
    // Ray is parallel to XY plane
    if ( !( ( tRayIT.location().z() >= -0.5 ) && ( tRayIT.location().z() <= 0.5 ) ) )
    {
      return false;
    }
    tIntZ.set (0, SCALAR_MAX);
  }
  else
  {
    tIntZ.set ((-0.5 - tRayIT.location().z()) / tRayIT.direction().z(), (0.5 - tRayIT.location().z()) / tRayIT.direction().z());
  }

  tIntTmp = Intersection (tIntX, tIntY);
  tIntTmp = Intersection (tIntTmp, tIntZ);

  if ( tIntTmp.empty() || ( tIntTmp.size() <= FX_EPSILON ) )
  {
    //
    // If there is no intersection or the intersection is in a single point.
    //
    return false;
  }

  if ( ( tIntTmp.min() >= FX_EPSILON ) && ( tIntTmp.min() <= rktRAY.limit() ) )
  {
    rtDATA.setup (this, rktRAY);
    rtDATA.setPoint (tIntTmp.min() * tFactor);

    return true;
  }
  
  if ( ( tIntTmp.max() >= FX_EPSILON ) && ( tIntTmp.max() <= rktRAY.limit() ) )
  {
    rtDATA.setup (this, rktRAY);
    rtDATA.setPoint (tIntTmp.max() * tFactor);

    return true;
  }

  return false;

}  /* findFirstIntersection() */


bool TBox::findAllIntersections (const TRay& rktRAY, TSpanList& rtLIST) const
{

  TSurfaceData   tSurfaceData;
  TInterval      tIntX, tIntY, tIntZ, tIntTmp;
  TScalar        tFactor;
  TRay           tRayIT        = rktRAY;
  bool           gIntersection = false;

  if ( !tBoundingBox.intersects (rktRAY) )
  {
    return false;
  }
  
  tFactor = tRayIT.applyTransform (ptInverseMatrix);

  if ( rktRAY.limit() < SCALAR_MAX )
  {
    tRayIT.setLimit (rktRAY.limit() / tFactor);
  }

  if ( fabs (tRayIT.direction().x()) < FX_EPSILON )
  {
    // Ray is parallel to YZ plane
    if ( !( ( tRayIT.location().x() >= -0.5 ) && ( tRayIT.location().x() <= 0.5 ) ) )
    {
      return false;
    }
    tIntX.set (0, SCALAR_MAX);
  }
  else
  {
    tIntX.set ((-0.5 - tRayIT.location().x()) / tRayIT.direction().x(), (0.5 - tRayIT.location().x()) / tRayIT.direction().x());
  }

  if ( fabs (tRayIT.direction().y()) < FX_EPSILON )
  {
    // Ray is parallel to ZX plane
    if ( !( ( tRayIT.location().y() >= -0.5 ) && ( tRayIT.location().y() <= 0.5 ) ) )
    {
      return false;
    }
    tIntY.set (0, SCALAR_MAX);
  }
  else
  {
    tIntY.set ((-0.5 - tRayIT.location().y()) / tRayIT.direction().y(), (0.5 - tRayIT.location().y()) / tRayIT.direction().y());
  }

  if ( fabs (tRayIT.direction().z()) < FX_EPSILON )
  {
    // Ray is parallel to XY plane
    if ( !( ( tRayIT.location().z() >= -0.5 ) && ( tRayIT.location().z() <= 0.5 ) ) )
    {
      return false;
    }
    tIntZ.set (0, SCALAR_MAX);
  }
  else
  {
    tIntZ.set ((-0.5 - tRayIT.location().z()) / tRayIT.direction().z(), (0.5 - tRayIT.location().z()) / tRayIT.direction().z());
  }

  tIntTmp = Intersection (tIntX, tIntY);
  tIntTmp = Intersection (tIntTmp, tIntZ);

  if ( tIntTmp.empty() || ( tIntTmp.size() <= FX_EPSILON ) )
  {
    //
    // If there is no intersection or the intersection is in a single point.
    //
    return false;
  }

  tSurfaceData.setup (this, rktRAY);
  
  if ( ( tIntTmp.min() >= FX_EPSILON ) && ( tIntTmp.min() <= rktRAY.limit() ) )
  {
    if ( tSurfaceData.setPoint (tIntTmp.min() * tFactor) )
    {
      rtLIST.add (tSurfaceData);
      gIntersection = true;
    }
  }
  if ( ( tIntTmp.max() >= FX_EPSILON ) && ( tIntTmp.max() <= rktRAY.limit() ) )
  {
    if ( tSurfaceData.setPoint (tIntTmp.max() * tFactor) )
    {
      rtLIST.add (tSurfaceData);
      gIntersection = true;
    }
  }

  return gIntersection;

}  /* findAllIntersections() */


void TBox::getMesh (list<TMesh*>& rtMESH_LIST) const
{

  TMesh*   ptMesh;

  // Upper face
  ptMesh = new TMesh;
  
  ptMesh->addFace ((*ptMatrix) * TVector (-0.5, 0.5, -0.5),
                   (*ptMatrix) * TVector (-0.5, 0.5, 0.5),
                   (*ptMatrix) * TVector (0.5, 0.5, -0.5),
                   this);
  ptMesh->addFace ((*ptMatrix) * TVector (0.5, 0.5, -0.5),
                   (*ptMatrix) * TVector (-0.5, 0.5, 0.5),
                   (*ptMatrix) * TVector (0.5, 0.5, 0.5),
                   this);
  
  rtMESH_LIST.push_back (ptMesh);
  
  // Lower face
  ptMesh = new TMesh;
  
  ptMesh->addFace ((*ptMatrix) * TVector (-0.5, -0.5, -0.5),
                   (*ptMatrix) * TVector (0.5, -0.5, -0.5),
                   (*ptMatrix) * TVector (-0.5, -0.5, 0.5),
                   this);
  ptMesh->addFace ((*ptMatrix) * TVector (0.5, -0.5, -0.5),
                   (*ptMatrix) * TVector (0.5, -0.5, 0.5),
                   (*ptMatrix) * TVector (-0.5, -0.5, 0.5),
                   this);
  
  rtMESH_LIST.push_back (ptMesh);
  
  // Left face
  ptMesh = new TMesh;
  
  ptMesh->addFace ((*ptMatrix) * TVector (-0.5, 0.5, -0.5),
                   (*ptMatrix) * TVector (-0.5, -0.5, -0.5),
                   (*ptMatrix) * TVector (-0.5, -0.5, 0.5),
                   this);
  ptMesh->addFace ((*ptMatrix) * TVector (-0.5, 0.5, -0.5),
                   (*ptMatrix) * TVector (-0.5, -0.5, 0.5),
                   (*ptMatrix) * TVector (-0.5, 0.5, 0.5),
                   this);

  rtMESH_LIST.push_back (ptMesh);
  
  // Right face
  ptMesh = new TMesh;
  
  ptMesh->addFace ((*ptMatrix) * TVector (0.5, 0.5, 0.5),
                   (*ptMatrix) * TVector (0.5, -0.5, 0.5),
                   (*ptMatrix) * TVector (0.5, -0.5, -0.5),
                   this);
  ptMesh->addFace ((*ptMatrix) * TVector (0.5, 0.5, 0.5),
                   (*ptMatrix) * TVector (0.5, -0.5, -0.5),
                   (*ptMatrix) * TVector (0.5, 0.5, -0.5),
                   this);
  
  rtMESH_LIST.push_back (ptMesh);
  
  // Front face
  ptMesh = new TMesh;
  
  ptMesh->addFace ((*ptMatrix) * TVector (-0.5, 0.5, 0.5),
                   (*ptMatrix) * TVector (-0.5, -0.5, 0.5),
                   (*ptMatrix) * TVector (0.5, -0.5, 0.5),
                   this);
  ptMesh->addFace ((*ptMatrix) * TVector (-0.5, 0.5, 0.5),
                   (*ptMatrix) * TVector (0.5, -0.5, 0.5),
                   (*ptMatrix) * TVector (0.5, 0.5, 0.5),
                   this);
  
  rtMESH_LIST.push_back (ptMesh);
  
  // Back face
  ptMesh = new TMesh;
  
  ptMesh->addFace ((*ptMatrix) * TVector (0.5, 0.5, -0.5),
                   (*ptMatrix) * TVector (0.5, -0.5, -0.5),
                   (*ptMatrix) * TVector (-0.5, -0.5, -0.5),
                   this);
  ptMesh->addFace ((*ptMatrix) * TVector (0.5, 0.5, -0.5),
                   (*ptMatrix) * TVector (-0.5, -0.5, -0.5),
                   (*ptMatrix) * TVector (-0.5, 0.5, -0.5),
                   this);
  
  rtMESH_LIST.push_back (ptMesh);
  
}  /* getMesh() */
