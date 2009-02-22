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
#include <cmath>
#include <iostream>
#include "hlapi/box.h"
#include "llapi/attribute.h"

TVector TBox::localNormal (const TVector& rktPOINT) const
{

  TVector   tNormal;

  if ( fabs (rktPOINT.x() - tXmin) <= FX_EPSILON  )
  {
    tNormal.set (-1, 0, 0);
  }
  else if ( fabs (rktPOINT.x() - tXmax) <= FX_EPSILON )
  {
    tNormal.set (1, 0, 0);
  }
  else if ( fabs (rktPOINT.y() - tYmin) <= FX_EPSILON  )
  {
    tNormal.set (0, -1, 0);
  }
  else if ( fabs (rktPOINT.y() - tYmax) <= FX_EPSILON )
  {
    tNormal.set (0, 1, 0);
  }
  else if ( fabs (rktPOINT.z() - tZmin) <= FX_EPSILON  )
  {
    tNormal.set (0, 0, -1);
  }
  else if ( fabs (rktPOINT.z() - tZmax) <= FX_EPSILON )
  {
    tNormal.set (0, 0, 1);
  }
  else
  {
    rktPOINT.printDebug("");
    assert ( false );
  }

  return tNormal;

}  /* localNormal() */


bool TBox::initialize (void)
{
  tBoundingBox.set (TVector (tXmin, tYmin, tZmin), TVector (tXmax, tYmax, tZmax));
  tBoundingBox.applyTransform (*ptMatrix);

  return TObject::initialize();
  
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

  // [CHECKME!]
  // >>>>>>>>>>>>>>>> 100.99
  // I [KH] have removed this test, as I don't see the purpose.  If the ray
  // had a limit of +inf, then why shouldn't the new sub-ray?
  //  if ( rktRAY.range() < SCALAR_MAX )
  //  {
  //    tRayIT.setRange (FX_EPSILON, rktRAY.maxLimit() / tFactor);
  //  }
  tRayIT.applyRangeFactor(1.0 / tFactor);

  if ( fabs (tRayIT.direction().x()) < FX_EPSILON )
  {
    // Ray is parallel to YZ plane
    if ( !( ( tRayIT.location().x() >= tXmin ) && ( tRayIT.location().x() <= tXmax ) ) )
    {
      return false;
    }
    tIntX.set (0, SCALAR_MAX);
  }
  else
  {
    tIntX.set ((tXmin - tRayIT.location().x()) / tRayIT.direction().x(), (tXmax - tRayIT.location().x()) / tRayIT.direction().x());
  }

  if ( fabs (tRayIT.direction().y()) < FX_EPSILON )
  {
    // Ray is parallel to ZX plane
    if ( !( ( tRayIT.location().y() >= tYmin ) && ( tRayIT.location().y() <= tYmax ) ) )
    {
      return false;
    }
    tIntY.set (0, SCALAR_MAX);
  }
  else
  {
    tIntY.set ((tYmin - tRayIT.location().y()) / tRayIT.direction().y(), (tYmax - tRayIT.location().y()) / tRayIT.direction().y());
  }

  if ( fabs (tRayIT.direction().z()) < FX_EPSILON )
  {
    // Ray is parallel to XY plane
    if ( !( ( tRayIT.location().z() >= tZmin ) && ( tRayIT.location().z() <= tZmax ) ) )
    {
      return false;
    }
    tIntZ.set (0, SCALAR_MAX);
  }
  else
  {
    tIntZ.set ((tZmin - tRayIT.location().z()) / tRayIT.direction().z(), (tZmax - tRayIT.location().z()) / tRayIT.direction().z());
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

  // [CHECKME!]  >>>>>>>>>>>>>>>> 100.99
  // if ( ( tIntTmp.min() >= FX_EPSILON ) && ( tIntTmp.min() <= tRayIT.limit() ) )
  if( tRayIT.range().inside(tIntTmp.min()) )
  {
    rtDATA.setup (this, rktRAY);
    rtDATA.setPoint (tIntTmp.min() * tFactor);

    return true;
  }
  // if ( ( tIntTmp.max() >= FX_EPSILON ) && ( tIntTmp.max() <= tRayIT.limit() ) )
  if( tRayIT.range().inside(tIntTmp.max()) )
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

  // [Checkme!]
  // >>>>>>>>>>>>>>>> 100.99  
  //  if ( rktRAY.limit() < SCALAR_MAX )
  //  {
  //    tRayIT.setLimit (rktRAY.limit() / tFactor);
  //  }
  tRayIT.applyRangeFactor(1.0 / tFactor);

  if ( fabs (tRayIT.direction().x()) < FX_EPSILON )
  {
    // Ray is parallel to YZ plane
    if ( !( ( tRayIT.location().x() >= tXmin ) && ( tRayIT.location().x() <= tXmax ) ) )
    {
      return false;
    }
    tIntX.set (0, SCALAR_MAX);
  }
  else
  {
    tIntX.set ((tXmin - tRayIT.location().x()) / tRayIT.direction().x(), (tXmax - tRayIT.location().x()) / tRayIT.direction().x());
  }

  if ( fabs (tRayIT.direction().y()) < FX_EPSILON )
  {
    // Ray is parallel to ZX plane
    if ( !( ( tRayIT.location().y() >= tYmin ) && ( tRayIT.location().y() <= tYmax ) ) )
    {
      return false;
    }
    tIntY.set (0, SCALAR_MAX);
  }
  else
  {
    tIntY.set ((tYmin - tRayIT.location().y()) / tRayIT.direction().y(), (tYmax - tRayIT.location().y()) / tRayIT.direction().y());
  }

  if ( fabs (tRayIT.direction().z()) < FX_EPSILON )
  {
    // Ray is parallel to XY plane
    if ( !( ( tRayIT.location().z() >= tZmin ) && ( tRayIT.location().z() <= tZmax ) ) )
    {
      return false;
    }
    tIntZ.set (0, SCALAR_MAX);
  }
  else
  {
    tIntZ.set ((tZmin - tRayIT.location().z()) / tRayIT.direction().z(), (tZmax - tRayIT.location().z()) / tRayIT.direction().z());
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

  // [Checkme!]
  //  >>>>>>>>>>>>>>>> 100.99
  //  if ( ( tIntTmp.min() >= FX_EPSILON ) && ( tIntTmp.min() <= tRayIT.limit() ) )
  if( tRayIT.range().inside(tIntTmp.min()) )
  {
    if ( tSurfaceData.setPoint (tIntTmp.min() * tFactor) )
    {
      rtLIST.add (tSurfaceData);
      gIntersection = true;
    }
  }
  //  if ( ( tIntTmp.max() >= FX_EPSILON ) && ( tIntTmp.max() <= tRayIT.limit() ) )
  if( tRayIT.range().inside(tIntTmp.max()) )  
  {
    if ( tSurfaceData.setPoint (tIntTmp.max() * tFactor) )
    {
      rtLIST.add (tSurfaceData);
      gIntersection = true;
    }
  }

  return gIntersection;

}  /* findAllIntersections() */


void TBox::getMesh (std::list<TMesh*>& rtMESH_LIST) const
{

  TMesh*   ptMesh;

  // Upper face
  ptMesh = new TMesh;
  
  ptMesh->addFace ((*ptMatrix) * TVector (tXmin, tYmax, tZmin),
                   (*ptMatrix) * TVector (tXmin, tYmax, tZmax),
                   (*ptMatrix) * TVector (tXmax, tYmax, tZmin),
                   this);
  ptMesh->addFace ((*ptMatrix) * TVector (tXmax, tYmax, tZmin),
                   (*ptMatrix) * TVector (tXmin, tYmax, tZmax),
                   (*ptMatrix) * TVector (tXmax, tYmax, tZmax),
                   this);
  
  rtMESH_LIST.push_back (ptMesh);
  
  // Lower face
  ptMesh = new TMesh;
  
  ptMesh->addFace ((*ptMatrix) * TVector (tXmin, tYmin, tZmin),
                   (*ptMatrix) * TVector (tXmax, tYmin, tZmin),
                   (*ptMatrix) * TVector (tXmin, tYmin, tZmax),
                   this);
  ptMesh->addFace ((*ptMatrix) * TVector (tXmax, tYmin, tZmin),
                   (*ptMatrix) * TVector (tXmax, tYmin, tZmax),
                   (*ptMatrix) * TVector (tXmin, tYmin, tZmax),
                   this);
  
  rtMESH_LIST.push_back (ptMesh);
  
  // Left face
  ptMesh = new TMesh;
  
  ptMesh->addFace ((*ptMatrix) * TVector (tXmin, tYmax, tZmin),
                   (*ptMatrix) * TVector (tXmin, tYmin, tZmin),
                   (*ptMatrix) * TVector (tXmin, tYmin, tZmax),
                   this);
  ptMesh->addFace ((*ptMatrix) * TVector (tXmin, tYmax, tZmin),
                   (*ptMatrix) * TVector (tXmin, tYmin, tZmax),
                   (*ptMatrix) * TVector (tXmin, tYmax, tZmax),
                   this);

  rtMESH_LIST.push_back (ptMesh);
  
  // Right face
  ptMesh = new TMesh;
  
  ptMesh->addFace ((*ptMatrix) * TVector (tXmax, tYmax, tZmax),
                   (*ptMatrix) * TVector (tXmax, tYmin, tZmax),
                   (*ptMatrix) * TVector (tXmax, tYmin, tZmin),
                   this);
  ptMesh->addFace ((*ptMatrix) * TVector (tXmax, tYmax, tZmax),
                   (*ptMatrix) * TVector (tXmax, tYmin, tZmin),
                   (*ptMatrix) * TVector (tXmax, tYmax, tZmin),
                   this);
  
  rtMESH_LIST.push_back (ptMesh);
  
  // Front face
  ptMesh = new TMesh;
  
  ptMesh->addFace ((*ptMatrix) * TVector (tXmin, tYmax, tZmax),
                   (*ptMatrix) * TVector (tXmin, tYmin, tZmax),
                   (*ptMatrix) * TVector (tXmax, tYmin, tZmax),
                   this);
  ptMesh->addFace ((*ptMatrix) * TVector (tXmin, tYmax, tZmax),
                   (*ptMatrix) * TVector (tXmax, tYmin, tZmax),
                   (*ptMatrix) * TVector (tXmax, tYmax, tZmax),
                   this);
  
  rtMESH_LIST.push_back (ptMesh);
  
  // Back face
  ptMesh = new TMesh;
  
  ptMesh->addFace ((*ptMatrix) * TVector (tXmax, tYmax, tZmin),
                   (*ptMatrix) * TVector (tXmax, tYmin, tZmin),
                   (*ptMatrix) * TVector (tXmin, tYmin, tZmin),
                   this);
  ptMesh->addFace ((*ptMatrix) * TVector (tXmax, tYmax, tZmin),
                   (*ptMatrix) * TVector (tXmin, tYmin, tZmin),
                   (*ptMatrix) * TVector (tXmin, tYmax, tZmin),
                   this);
  
  rtMESH_LIST.push_back (ptMesh);
  
}  /* getMesh() */


int TBox::setAttribute (const std::string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{
  if ( rktNAME == "point1" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_VECTOR )
    {
      tP1 = *((TVector*) nVALUE.pvValue);
    }
#else
    magic_pointer<TAttribVector> vec = get_vector(nVALUE);
    if( !!vec )
    {
      tP1 = vec->tValue;
    }
#endif    
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "point2" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_VECTOR )
    {
      tP2 = *((TVector*) nVALUE.pvValue);
    }
#else
    magic_pointer<TAttribVector> vec = get_vector(nVALUE);
    if( !!vec )
    {
      tP2 = vec->tValue;
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

  tXmin = std::min (tP1.x(), tP2.x());
  tYmin = std::min (tP1.y(), tP2.y());
  tZmin = std::min (tP1.z(), tP2.z());
  tXmax = std::max (tP1.x(), tP2.x());
  tYmax = std::max (tP1.y(), tP2.y());
  tZmax = std::max (tP1.z(), tP2.z());  
  
  return FX_ATTRIB_OK;

}  /* setAttribute() */


int TBox::getAttribute (const std::string& rktNAME, NAttribute& rnVALUE)
{

#if !defined(NEW_ATTRIBUTES)
  if ( rktNAME == "point1" )
  {
    rnVALUE.pvValue = &tP1;
  }
  else if ( rktNAME == "point2" )
  {
    rnVALUE.pvValue = &tP2;
  }
#else
  if ( rktNAME == "point1" )
  {
    rnVALUE = (user_arg_type)new TAttribVector(tP1);
  }
  else if ( rktNAME == "point2" )
  {
    rnVALUE = (user_arg_type)new TAttribVector(tP2);
  }
#endif    
  else
  {
    return TObject::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TBox::getAttributeList (TAttributeList& rtLIST) const
{

  TObject::getAttributeList (rtLIST);

  rtLIST ["point1"] = FX_VECTOR;
  rtLIST ["point2"] = FX_VECTOR;

}  /* getAttributeList() */

TVector TBox::RandomPointOnSurface() const
{
  return TVector(frand() * (tXmax - tXmin),
		 frand() * (tYmax - tYmin),
		 frand() * (tZmax - tZmin));
}
