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

#include <iostream>
#include "llapi/bounding_box.h"
#include "llapi/object.h"

void TBoundingBox::applyTransform (const TMatrix& rktMATRIX)
{

  TScalar   tMinX, tMaxX, tMinY, tMaxY, tMinZ, tMaxZ;
  TVector   atVertex [8] = { tPoint1,
                             tPoint2,
                             TVector (tPoint2.x(), tPoint1.y(), tPoint1.z()),
                             TVector (tPoint2.x(), tPoint1.y(), tPoint2.z()),
                             TVector (tPoint1.x(), tPoint1.y(), tPoint2.z()),
                             TVector (tPoint1.x(), tPoint2.y(), tPoint2.z()),
                             TVector (tPoint1.x(), tPoint2.y(), tPoint1.z()),
                             TVector (tPoint2.x(), tPoint2.y(), tPoint1.z())
                           };

  //
  // Apply the transformation matrix to the points and calculate the min and max of
  // X's, Y's and Z's
  //
  atVertex[0] = rktMATRIX * atVertex[0];

  tMinX = atVertex[0].x();
  tMaxX = atVertex[0].x();
  tMinY = atVertex[0].y();
  tMaxY = atVertex[0].y();
  tMinZ = atVertex[0].z();
  tMaxZ = atVertex[0].z();

  for (size_t I = 1; ( I < 8 ) ;I++)
  {
    atVertex[I] = rktMATRIX * atVertex[I];
    
    tMinX = min (atVertex[I].x(), tMinX);
    tMaxX = max (atVertex[I].x(), tMaxX);
    tMinY = min (atVertex[I].y(), tMinY);
    tMaxY = max (atVertex[I].y(), tMaxY);
    tMinZ = min (atVertex[I].z(), tMinZ);
    tMaxZ = max (atVertex[I].z(), tMaxZ);
  }

  set (TVector (tMinX, tMinY, tMinZ), TVector (tMaxX, tMaxY, tMaxZ));

}  /* applyTransform() */


bool TBoundingBox::intersects (const TRay& rktRAY) const
{

  TInterval   tIntX, tIntY, tIntZ;

  if ( fabs (rktRAY.direction().x()) < FX_EPSILON )
  {
    //
    // Ray is parallel to X axis
    //
    if ( !TInterval (tPoint1.x(), tPoint2.x()).inside (rktRAY.location().x()) )
    {
      return false;
    }
    tIntX = TInterval (0, SCALAR_MAX);
  }
  else
  {
    tIntX = TInterval ((tPoint1.x() - rktRAY.location().x()) / rktRAY.direction().x(),
                       (tPoint2.x() - rktRAY.location().x()) / rktRAY.direction().x());
    if ( ( tIntX < TScalar (0) ) || ( tIntX > rktRAY.limit() ) )
    {
      return false;
    }
  }

  if ( fabs (rktRAY.direction().y()) < FX_EPSILON )
  {
    //
    // Ray is parallel to Y axis
    //
    if ( !TInterval (tPoint1.y(), tPoint2.y()).inside (rktRAY.location().y()) )
    {
      return false;
    }
    tIntY = TInterval (0, SCALAR_MAX);
  }
  else
  {
    tIntY = TInterval ((tPoint1.y() - rktRAY.location().y()) / rktRAY.direction().y(),
                       (tPoint2.y() - rktRAY.location().y()) / rktRAY.direction().y());
    if ( ( tIntY < TScalar (0) ) || ( tIntY > rktRAY.limit() ) )
    {
      return false;
    }
    if ( Disjoint (tIntX, tIntY) )
    {
      return false;
    }
  }

  if ( fabs (rktRAY.direction().z()) < FX_EPSILON )
  {
    //
    // Ray is parallel to Z axis
    //
    if ( !TInterval (tPoint1.z(), tPoint2.z()).inside (rktRAY.location().z()) )
    {
      return false;
    }
    tIntZ = TInterval (0, SCALAR_MAX);
  }
  else
  {
    tIntZ = TInterval ((tPoint1.z() - rktRAY.location().z()) / rktRAY.direction().z(), 
                       (tPoint2.z() - rktRAY.location().z()) / rktRAY.direction().z());
    if ( ( tIntZ < TScalar (0) ) || ( tIntZ > rktRAY.limit() ) )
    {
      return false;
    }
    if ( Disjoint (tIntX, tIntZ) || Disjoint (tIntY, tIntZ) )
    {
      return false;
    }
  }

  return true;

}  /* intersects() */


TInterval TBoundingBox::clipRay (const TRay& rktRAY) const
{

  TInterval   tInt;
  TInterval   tIntX, tIntY, tIntZ;

  tInt = xlimits();
  if ( fabs (rktRAY.direction().x()) <= FX_EPSILON )
  {
    if ( !tInt.inside (rktRAY.location().x()) )
    {
      return TInterval();
    }
    tIntX.set (0, rktRAY.limit());
  }
  else
  {
    tIntX.set ((tInt.min() - rktRAY.location().x()) / rktRAY.direction().x(),
               (tInt.max() - rktRAY.location().x()) / rktRAY.direction().x());
  }

  tInt = ylimits();
  if ( fabs (rktRAY.direction().y()) <= FX_EPSILON )
  {
    if ( !tInt.inside (rktRAY.location().y()) )
    {
      return TInterval();
    }
    tIntY.set (0, rktRAY.limit());
  }
  else
  {
    tIntY.set ((tInt.min() - rktRAY.location().y()) / rktRAY.direction().y(),
               (tInt.max() - rktRAY.location().y()) / rktRAY.direction().y());
  }
    
  tInt = zlimits();
  if ( fabs (rktRAY.direction().z()) <= FX_EPSILON )
  {
    if ( !tInt.inside (rktRAY.location().z()) )
    {
      return TInterval();
    }
    tIntZ.set (0, rktRAY.limit());
  }
  else
  {
    tIntZ.set ((tInt.min() - rktRAY.location().z()) / rktRAY.direction().z(),
               (tInt.max() - rktRAY.location().z()) / rktRAY.direction().z());
  }

  tInt.set (0, rktRAY.limit());
  tInt = Intersection (tInt, tIntX);
  tInt = Intersection (tInt, tIntY);
  tInt = Intersection (tInt, tIntZ);

  return tInt;
  
}  /* clipRay() */


TScalar TBoundingBox::cost (void) const
{

  TScalar   tSizeX = TInterval (tPoint1.x(), tPoint2.x()).size();
  TScalar   tSizeY = TInterval (tPoint1.y(), tPoint2.y()).size();
  TScalar   tSizeZ = TInterval (tPoint1.z(), tPoint2.z()).size();
  
  return (tSizeX * (tSizeY + tSizeZ) + tSizeY * tSizeZ);

}  /* cost() */


void TBoundingBox::printDebug (const string& indent) const
{

  cerr << indent
       << "[_TBoundingBox_] <"
       << tPoint1.x() << ", "
       << tPoint1.y() << ", "
       << tPoint1.z() << "> <"
       << tPoint2.x() << ", "
       << tPoint2.y() << ", "
       << tPoint2.z() << ">" << endl;

}  /* printDebug() */


TBoundingBox Merge (const vector<magic_pointer<TObject> >& rktLIST)
{

  TInterval   tIntX, tIntY, tIntZ;

  if ( !rktLIST.empty() )
  {
    for (vector<magic_pointer<TObject> >::const_iterator tIter = rktLIST.begin();
	 ( tIter != rktLIST.end() );
	 tIter++)
    {
      const TBoundingBox&   rktBBox = (*tIter)->boundingBox();
      
      tIntX  = Union (tIntX, rktBBox.xlimits());
      tIntY  = Union (tIntY, rktBBox.ylimits());
      tIntZ  = Union (tIntZ, rktBBox.zlimits());
    }
  }

  return TBoundingBox (TVector (tIntX.min(), tIntY.min(), tIntZ.min()),
                       TVector (tIntX.max(), tIntY.max(), tIntZ.max()));

}  /* Merge() */


bool Disjoint (const TBoundingBox& rktBBOX1, const TBoundingBox& rktBBOX2)
{

  if ( Disjoint (rktBBOX1.xlimits(), rktBBOX2.xlimits()) )
  {
    return true;
  }
  if ( Disjoint (rktBBOX1.ylimits(), rktBBOX2.ylimits()) )
  {
    return true;
  }
  if ( Disjoint (rktBBOX1.zlimits(), rktBBOX2.zlimits()) )
  {
    return true;
  }

  return false;

}  /* Disjoint() */


TBoundingBox Union (const TBoundingBox& rktBBOX1, const TBoundingBox& rktBBOX2)
{

  TInterval   tIntX = Union (rktBBOX1.xlimits(), rktBBOX2.xlimits());
  TInterval   tIntY = Union (rktBBOX1.ylimits(), rktBBOX2.ylimits());
  TInterval   tIntZ = Union (rktBBOX1.zlimits(), rktBBOX2.zlimits());

  return TBoundingBox (tIntX, tIntY, tIntZ);
  
}  /* Union() */


TBoundingBox Intersection (const TBoundingBox& rktBBOX1, const TBoundingBox& rktBBOX2)
{

  TInterval   tIntX = Intersection (rktBBOX1.xlimits(), rktBBOX2.xlimits());
  TInterval   tIntY = Intersection (rktBBOX1.ylimits(), rktBBOX2.ylimits());
  TInterval   tIntZ = Intersection (rktBBOX1.zlimits(), rktBBOX2.zlimits());

  return TBoundingBox (tIntX, tIntY, tIntZ);
  
}  /* Intersection() */
