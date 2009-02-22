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
#include "llapi/mesh.h"

size_t TMesh::addVertex (const TVector& rktVERTEX, size_t zFACE)
{

  TVertex*   ptVertex;
  size_t     zPos = 0;
      
  for (std::vector<TVertex>::iterator tIter = tVertexList.begin(); ( tIter != tVertexList.end() ) ;tIter++)
  {
    ptVertex = &(*tIter);
    
    if ( Distance (rktVERTEX, ptVertex->tPoint) < FX_EPSILON )
    {
      ptVertex->tFaceList.push_back (zFACE);
      return zPos;
    }

    zPos++;
  }

  {
    TVertex   tVertex;

    tVertex.tPoint = rktVERTEX;
    tVertex.tFaceList.push_back (zFACE);

    tVertexList.push_back (tVertex);
  }

  return zPos;

}  /* addVertex() */


void TMesh::addFace (const TVector& rktVERTEX1, const TVector& rktVERTEX2, const TVector& rktVERTEX3, const TObject* pktOBJ)
{

  TFace     tFace;
  TVertex   atVertex [3];
  size_t    zFace = tFaceList.size();

  tFace.azVertex[0] = addVertex (rktVERTEX1, zFace);
  tFace.azVertex[1] = addVertex (rktVERTEX2, zFace);
  tFace.azVertex[2] = addVertex (rktVERTEX3, zFace);
  
  atVertex [0] = tVertexList [tFace.azVertex[0]];
  atVertex [1] = tVertexList [tFace.azVertex[1]];
  atVertex [2] = tVertexList [tFace.azVertex[2]];

  tFace.tNormal = crossProduct (atVertex[1].tPoint - atVertex[0].tPoint,
                                atVertex[2].tPoint - atVertex[0].tPoint);

  tFace.tNormal.normalize();

  tFace.D = -dotProduct (tFace.tNormal, atVertex[0].tPoint);
    
  tFace.pktObject = pktOBJ;

  tFaceList.push_back (tFace);
  
}  /* addFace() */


void TMesh::calculateVertexNormals (void)
{

  TVertex*   ptVertex;
  
  for (std::vector<TVertex>::iterator tIter = tVertexList.begin(); ( tIter != tVertexList.end() ) ;tIter++)
  {
    ptVertex = &(*tIter);

    ptVertex->tNormal.set (0, 0, 0);

    for (std::list<size_t>::iterator tIter2 = ptVertex->tFaceList.begin(); ( tIter2 != ptVertex->tFaceList.end() ) ;tIter2++)
    {
      ptVertex->tNormal += tFaceList[*tIter2].tNormal;
    }

    ptVertex->tNormal.normalize();
  }

}  /* calculateVertexNormals() */


void TMesh::updateFaces (void)
{

  TFace*     ptFace;
  TVertex*   aptVertex [3];
  size_t     zFace = 0;

  for (std::vector<TFace>::iterator tIter = tFaceList.begin(); ( tIter != tFaceList.end() ) ;tIter++)
  {
    ptFace = &(*tIter);

    aptVertex [0] = &(tVertexList [ptFace->azVertex[0]]);
    aptVertex [1] = &(tVertexList [ptFace->azVertex[1]]);
    aptVertex [2] = &(tVertexList [ptFace->azVertex[2]]);
    
    ptFace->tNormal = crossProduct (aptVertex[1]->tPoint - aptVertex[0]->tPoint,
                                    aptVertex[2]->tPoint - aptVertex[0]->tPoint);
    ptFace->tNormal.normalize();

    ptFace->D = -dotProduct (ptFace->tNormal, aptVertex[0]->tPoint);

    aptVertex[0]->tFaceList.push_back (zFace);
    aptVertex[1]->tFaceList.push_back (zFace);
    aptVertex[2]->tFaceList.push_back (zFace);

    zFace++;
  }
  
}  /* updateFaces() */
