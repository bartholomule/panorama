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

#include "llapi/warning_eliminator.h"
#include <cmath>
#include "llapi/math_tools.h"
#include "llapi/vector_tools.h"
#include "hlapi/triangle.h"

bool TTriangle::initialize (void)
{
  bool val = true;

  TVector   tMin (std::min (atVertex[0].x(), std::min (atVertex[1].x(), atVertex[2].x())),
                  std::min (atVertex[0].y(), std::min (atVertex[1].y(), atVertex[2].y())),
                  std::min (atVertex[0].z(), std::min (atVertex[1].z(), atVertex[2].z())));
  TVector   tMax (std::max (atVertex[0].x(), std::max (atVertex[1].x(), atVertex[2].x())),
                  std::max (atVertex[0].y(), std::max (atVertex[1].y(), atVertex[2].y())),
                  std::max (atVertex[0].z(), std::max (atVertex[1].z(), atVertex[2].z())));

  tBoundingBox.set (tMin, tMax);

  return val && TPlane::initialize();
  
}  /* initialize() */


void TTriangle::update (void)
{

  TVector   tVector1 = (atVertex[1] - atVertex[0]);
  TVector   tVector2 = (atVertex[2] - atVertex[0]);

  // FIXME!  Does this work at all now?  Re-adjust things so that tLocation is
  // assumed to be at the origin, as setLocation does. 
  setLocation(atVertex[0]);
  //tLocation = atVertex[0];
  tNormal   = crossProduct (tVector1, tVector2);
  bDom      = Dominant (tNormal);

  //
  // Convert vertices to 2D std::vectors.
  //
  atCoord[0] = Convert3DTo2D (atVertex[0], bDom);
  atCoord[1] = Convert3DTo2D (atVertex[1], bDom);
  atCoord[2] = Convert3DTo2D (atVertex[2], bDom);

  TPlane::update();

}  /* update() */


void TTriangle::translate (const TVector& rktNEW_POS)
{

  TVector   tDiff = (rktNEW_POS - atVertex[0]);

  atVertex[0] = atVertex[0] + tDiff;
  atVertex[1] = atVertex[1] + tDiff;
  atVertex[2] = atVertex[2] + tDiff;

  update();

}  /* translate() */


bool TTriangle::inside (const TVector& rktPOINT) const
{

  Byte       bCrossings;
  TVector2   v1, v2, v3;
  TVector2   tInt;

  //
  // Convert point to a 2D std::vector.
  //
  tInt = Convert3DTo2D (rktPOINT, bDom);

  //
  // Center coordinate axis around test point.
  //
  v1 = (atCoord[0] - tInt);
  v2 = (atCoord[1] - tInt);
  v3 = (atCoord[2] - tInt);
  tInt.set (0, 0);

  //
  // Sums number of crossings in each side of the triangle.
  //
  bCrossings = Crossings (v1, v2) +
               Crossings (v2, v3) +
               Crossings (v3, v1);

  return ( bCrossings == 1 );

}  /* inside() */


void TTriangle::setVertex (const TVector& rktVERTEX)
{
  if ( bVertex <= 2 )
  {
    atVertex [bVertex] = rktVERTEX;
	 ++bVertex;
    if ( bVertex == 3 )
    {
      update();
    }
  }
  else
  {
    GOM.error() << "setVertex: Too many vertices (need exactly 3)" << std::endl;
  }
}  /* setVertex() */


void TTriangle::getMesh (std::list<TMesh*>& rtMESH_LIST) const
{

  TMesh*   ptMesh = new TMesh;
  
  ptMesh->addFace (atVertex[0], atVertex[1], atVertex[2], this);

  rtMESH_LIST.push_back (ptMesh);
  
}  /* getMesh() */

TVector TTriangle::RandomPointOnSurface() const
{
  TVector u = atVertex[1] - atVertex[0];
  TVector v = atVertex[2] - atVertex[0];

  return  (double(frand()) * u) + (double(frand()) * v) + atVertex[0];
  
}


void TTriangle::printDebug (const std::string& indent) const
{

  GOM.debug() << indent << "[_Triangle_]" << std::endl;

  std::string new_indent = TDebug::Indent(indent);
  
  GOM.debug() << new_indent << "Vertex 1 : "; atVertex[0].printDebug(new_indent); GOM.debug() << std::endl;
  GOM.debug() << new_indent << "Vertex 2 : "; atVertex[1].printDebug(new_indent); GOM.debug() << std::endl;
  GOM.debug() << new_indent << "Vertex 3 : "; atVertex[2].printDebug(new_indent); GOM.debug() << std::endl;
  GOM.debug() << new_indent << "Normal   : ";     tNormal.printDebug(new_indent); GOM.debug() << std::endl;

}  /* printDebug() */

TUserFunctionMap TTriangle::getUserFunctions()
{
  TUserFunctionMap ufm = TPlane::getUserFunctions();

  ufm["addVertex"] = create_user_function(this,&TTriangle::setVertex);

  return ufm;
}
