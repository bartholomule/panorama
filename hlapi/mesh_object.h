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

#ifndef _MESH_OBJECT__
#define _MESH_OBJECT__

#include "llapi/mesh.h"
#include "llapi/object.h"
#include "hlapi/triangle.h"

class TMeshObject : public TObject
{

  protected:

    std::vector<TVector>        tVertexList;
    std::vector<TMesh::TFace>   tFaceList;
    
  public:

    TMeshObject (void) :
      TObject()
    {
      sCapabilities.gInfinite = false;
    }
      
    bool findFirstIntersection (const TRay& rktRAY, TSurfaceData& rtDATA) const;
    bool findAllIntersections (const TRay& rktRAY, TSpanList& rtLIST) const;

    void addTriangle (const TTriangle* pktTRIANGLE);
    void addTriangle (const TVector& rktVERTEX1, const TVector& rktVERTEX2, const TVector& rktVERTEX3);

    std::vector<TVector>& vertexList (void) { return tVertexList; }
    std::vector<TMesh::TFace>& faceList (void) { return tFaceList; }
    
    void clear (void)
    {
      tVertexList.clear();
      tFaceList.clear();
    }

    size_t addVertex (const TVector& rktVERTEX);
    
    void getMesh (std::list<TMesh*>& rtMESH_LIST) const;
    
    std::string className (void) const { return "Mesh"; }
    
};  /* class TMeshObject */

#endif  /* _MESH_OBJECT__ */
