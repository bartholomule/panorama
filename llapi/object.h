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

#ifndef _OBJECT__
#define _OBJECT__

#include "llapi/volume.h"
#include "llapi/mesh.h"
#include "llapi/bounding_box.h"
#include "llapi/span_list.h"
#include "llapi/object_filter.h"

class TMaterial;

class TObject : public TVolume
{

  protected:

    TBoundingBox                 tBoundingBox;
    TMaterial*                   ptMaterial;
    list<const TObjectFilter*>   tObjectFilterList;
    size_t                       zObjectCode;
    TMatrix*                     ptMatrix;
    TMatrix*                     ptInverseMatrix;

    struct
    {
      
      unsigned   gInfinite : 1;
      
    } sCapabilities;

    void createMatrices (void);

    virtual TVector localNormal (const TVector& rktPOINT) const { return TVector (0, 0 ,0); }

  public:

    TObject (void) :
      ptMaterial (NULL),
      ptMatrix (NULL),
      ptInverseMatrix (NULL)
    {
      createMatrices();
    }
      
    virtual ~TObject (void)
    {
      delete ptMatrix;
      delete ptInverseMatrix;
    }
      
    TObject (const TObject& rktOBJ)
    {
      createMatrices();
      
      *ptMatrix        = *(rktOBJ.ptMatrix);
      *ptInverseMatrix = *(rktOBJ.ptInverseMatrix);

      ptMaterial        = rktOBJ.ptMaterial;
      zObjectCode       = rktOBJ.zObjectCode;
      tObjectFilterList = rktOBJ.tObjectFilterList;
    }

    TObject& operator = (const TObject& rktOBJ)
    {
      if ( !ptMatrix )
      {
        createMatrices();
      }
      
      *ptMatrix        = *(rktOBJ.ptMatrix);
      *ptInverseMatrix = *(rktOBJ.ptInverseMatrix);

      ptMaterial        = rktOBJ.ptMaterial;
      zObjectCode       = rktOBJ.zObjectCode;
      tObjectFilterList = rktOBJ.tObjectFilterList;

      return *this;
    }
      
    virtual void initialize (void);

    virtual bool intersects (const TRay& rktRAY) const
    {
      TSurfaceData   tSurfaceData;

      return findFirstIntersection (rktRAY, tSurfaceData);
    }
      
    virtual bool findFirstIntersection (const TRay& rktRAY, TSurfaceData& rtDATA) const
    {
      TSpanList   tList;
      bool        gIntersection = findAllIntersections (rktRAY, tList);

      if ( gIntersection )
      {
        rtDATA = tList.first();
      }

      return gIntersection;
    }
      
    virtual bool findAllIntersections (const TRay& rktRAY, TSpanList& rtLIST) const = 0;

    void translate (const TVector& rktNEW_POS);
    void rotate (const TVector& rktAXISPOINT1, const TVector& rktAXISPOINT2, TScalar tANGLE);
    void rotate (const TVector& rktANGLESXYZ);
    void scale (const TVector& rktSCALING_XYZ, const TVector& rktPOINT);

    virtual TVector normal (const TSurfaceData& rktDATA) const;

    TBoundingBox boundingBox (void) const { return tBoundingBox; }
    TMaterial* material (void) const { return ptMaterial; }
    size_t objectCode (void) const { return zObjectCode; }
    const list<const TObjectFilter*>& filterList (void) const { return tObjectFilterList; }

    virtual void setMaterial (TMaterial* ptMAT) { ptMaterial = ptMAT; }
    virtual void setObjectCode (size_t zCODE) { zObjectCode = zCODE; }

    virtual TMatrix* transformMatrix (void) const { return ptMatrix; }
    virtual TMatrix* inverseTransformMatrix (void) const { return ptInverseMatrix; }

    virtual void setTransformMatrix (const TMatrix& rktMATRIX)
    {
      assert ( ptMatrix );
      
      *ptMatrix = rktMATRIX;
    }
    
    virtual void setInverseTransformMatrix (const TMatrix& rktMATRIX)
    {
      assert ( ptInverseMatrix );
      
      *ptInverseMatrix = rktMATRIX;
    }
    
    virtual void addFilter (const TObjectFilter* pktFILTER) { tObjectFilterList.push_back (pktFILTER); }
      
    virtual void getMesh (list<TMesh*>& rtMESH_LIST) const {}
    
    void printDebug (void) const;

    EClass classType (void) const { return FX_OBJECT_CLASS; }
      
};  /* class TObject */

inline TVector TObject::normal (const TSurfaceData& rktDATA) const
{

  TVector   tPoint  = (*ptInverseMatrix) * rktDATA.point();
  TVector   tNormal = localNormal (tPoint);

  tNormal.applyTransform (ptInverseMatrix);
  tNormal.normalize();

  return tNormal;

}  /* normal() */

#endif  /* _OBJECT__ */
