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

#include <math.h>
#include "llapi/math_tools.h"
#include "llapi/vector.h"
#include "hlapi/triangle.h"

void TTriangle::initialize (void)
{

  TVector   tMin (min (atVertex[0].x(), min (atVertex[1].x(), atVertex[2].x())),
                  min (atVertex[0].y(), min (atVertex[1].y(), atVertex[2].y())),
                  min (atVertex[0].z(), min (atVertex[1].z(), atVertex[2].z())));
  TVector   tMax (max (atVertex[0].x(), max (atVertex[1].x(), atVertex[2].x())),
                  max (atVertex[0].y(), max (atVertex[1].y(), atVertex[2].y())),
                  max (atVertex[0].z(), max (atVertex[1].z(), atVertex[2].z())));

  tBoundingBox.set (tMin, tMax);

}  /* initialize() */


void TTriangle::update (void)
{

  TVector   tVector1 = (atVertex[1] - atVertex[0]);
  TVector   tVector2 = (atVertex[2] - atVertex[0]);

  tLocation = atVertex[0];
  tNormal   = crossProduct (tVector1, tVector2);
  bDom      = Dominant (tNormal);

  //
  // Convert vertices to 2D vectors.
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
  // Convert point to a 2D vector.
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
    atVertex [bVertex++] = rktVERTEX;
    if ( bVertex == 3 )
    {
      update();
    }
  }

}  /* setVertex() */


void TTriangle::getMesh (list<TMesh*>& rtMESH_LIST) const
{

  TMesh*   ptMesh = new TMesh;
  
  ptMesh->addFace (atVertex[0], atVertex[1], atVertex[2], this);

  rtMESH_LIST.push_back (ptMesh);
  
}  /* getMesh() */


void TTriangle::printDebug (void) const
{

  cerr << TDebug::_indent() << "[_Triangle_]" << endl;

  TDebug::_push();
  
  cerr << TDebug::_indent() << "Vertex 1 : "; atVertex[0].printDebug(); cerr << endl;
  cerr << TDebug::_indent() << "Vertex 2 : "; atVertex[1].printDebug(); cerr << endl;
  cerr << TDebug::_indent() << "Vertex 3 : "; atVertex[2].printDebug(); cerr << endl;
  cerr << TDebug::_indent() << "Normal   : "; tNormal.printDebug(); cerr << endl;

  TDebug::_pop();
  
}  /* printDebug() */
