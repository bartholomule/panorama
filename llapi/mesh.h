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

#ifndef _MESH__
#define _MESH__

#include <list>
#include <vector>
#include "llapi/llapi_defs.h"

class TObject;

class TMesh
{

  public:

    struct TFace
    {
      size_t           azVertex [3];   // This values are indices in the edge list
      TVector          tNormal;
      TScalar          D;
      const TObject*   pktObject;
    };

    struct TVertex
    {
      TVector        tPoint;
      TVector        tNormal;
      TColor         tColor;
      list<size_t>   tFaceList;
    };

  protected:
    
    vector<TVertex>   tVertexList;
    vector<TFace>     tFaceList;
    
  public:

    TMesh (void) {}

    TMesh (const TMesh& rktMESH)
    {
      tVertexList = rktMESH.tVertexList;
      tFaceList   = rktMESH.tFaceList;
    }
      
    size_t addVertex (const TVector& rktVERTEX, size_t zFACE);
    void addFace (const TVector& rktVERTEX1, const TVector& rktVERTEX2, const TVector& rktVERTEX3, const TObject* pktOBJ);

    TVertex& vertex (size_t zVERTEX) { return tVertexList [zVERTEX]; }
    TFace& face (size_t zFACE) { return tFaceList [zFACE]; }
      
    const TVertex& vertex (size_t zVERTEX) const { return tVertexList [zVERTEX]; }
    const TFace& face (size_t zFACE) const { return tFaceList [zFACE]; }
      
    vector<TFace>* faceList (void) { return &tFaceList; }
    vector<TVertex>* vertexList (void) { return &tVertexList; }

    const vector<TFace>* faceList (void) const { return &tFaceList; }
    const vector<TVertex>* vertexList (void) const { return &tVertexList; }

    void calculateVertexNormals (void);

    void clear (void)
    {
      tFaceList.clear();
      tVertexList.clear();
    }

    void updateFaces (void);

};  /* class TMesh */

#endif  /* _MESH__ */
