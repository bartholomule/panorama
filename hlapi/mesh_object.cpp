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

#include "hlapi/mesh_object.h"

bool TMeshObject::findFirstIntersection (const TRay& rktRAY, TSurfaceData& rtDATA) const
{

  // [_TODO_] Implement intersection
  
  return false;
  
}  /* findFirstIntersection() */


bool TMeshObject::findAllIntersections (const TRay& rktRAY, TSpanList& rtLIST) const
{

  // [_TODO_] Implement intersection

  return false;
  
}  /* findAllIntersections() */


void TMeshObject::getMesh (list<TMesh*>& rtMESH_LIST) const
{

  TMesh::TVertex   tVertex;
  const TVector*   pktVertex;
  TMesh*           ptMesh = new TMesh();

  for (vector<TVector>::const_iterator tIter = tVertexList.begin(); ( tIter != tVertexList.end() ) ;tIter++)
  {
    pktVertex = &(*tIter);

    tVertex.tPoint = (*ptMatrix) * (*pktVertex);
    
    ptMesh->vertexList()->push_back (tVertex);
  }
  
  for (vector<TMesh::TFace>::const_iterator tIter = tFaceList.begin(); ( tIter != tFaceList.end() ) ;tIter++)
  {
    ptMesh->faceList()->push_back (*tIter);
  }

  ptMesh->updateFaces();
  
  rtMESH_LIST.push_back (ptMesh);
  
}  /* getMesh() */


inline size_t TMeshObject::addVertex (const TVector& rktVERTEX)
{

  TVector*   ptVertex;
  size_t     zPos = 0;
      
  for (vector<TVector>::iterator tIter = tVertexList.begin(); ( tIter != tVertexList.end() ) ;tIter++)
  {
    ptVertex = &(*tIter);
    
    if ( Distance (rktVERTEX, *ptVertex) < FX_EPSILON )
    {
      return zPos;
    }

    zPos++;
  }

  tVertexList.push_back (rktVERTEX);

  return zPos;

}  /* addVertex() */


void TMeshObject::addTriangle (const TTriangle* pktTRIANGLE)
{

  TMesh::TFace   tFace;

  tFace.azVertex[0] = addVertex (pktTRIANGLE->vertex (0));
  tFace.azVertex[1] = addVertex (pktTRIANGLE->vertex (1));
  tFace.azVertex[2] = addVertex (pktTRIANGLE->vertex (2));
  tFace.pktObject   = this;
      
  tFaceList.push_back (tFace);

}  /* addTriangle() */


void TMeshObject::addTriangle (const TVector& rktVERTEX1, const TVector& rktVERTEX2, const TVector& rktVERTEX3)
{

  TMesh::TFace   tFace;

  tFace.azVertex[0] = addVertex (rktVERTEX1);
  tFace.azVertex[1] = addVertex (rktVERTEX2);
  tFace.azVertex[2] = addVertex (rktVERTEX3);
  tFace.pktObject   = this;
      
  tFaceList.push_back (tFace);

}  /* addTriangle() */
