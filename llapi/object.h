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
#include "llapi/material.h"

class TMaterial;



class TObject : public TVolume
{

  protected:
    typedef list<magic_pointer<TObjectFilter> > FilterListType;

    TBoundingBox                 tBoundingBox;
    magic_pointer<TMaterial>     ptMaterial;
    FilterListType tObjectFilterList;
    size_t                       zObjectCode;
    magic_pointer<TMatrix>                     ptMatrix;
    magic_pointer<TMatrix>                     ptInverseMatrix;

    struct TCapabilities
    {
      
      unsigned   gInfinite : 1;
      
    } sCapabilities;

    void createMatrices (void);

    virtual TVector localNormal (const TVector& rktPOINT) const { return TVector (0, 0 ,0); }

  public:

    TObject (void) :
      TVolume (),
      ptMaterial (NULL),
      ptMatrix (NULL),
      ptInverseMatrix (NULL)
    {
      createMatrices();
    }
      
    virtual ~TObject (void)
    {
      ptMatrix = NULL;
      ptInverseMatrix = NULL;

      tObjectFilterList.erase(tObjectFilterList.begin(),
			      tObjectFilterList.end());
    }
      
    TObject (const TObject& rktOBJ) : TVolume(rktOBJ)
    {
      createMatrices();
      
      ptMatrix        = rktOBJ.ptMatrix;
      ptInverseMatrix = rktOBJ.ptInverseMatrix;

      ptMaterial        = rktOBJ.ptMaterial;
      zObjectCode       = rktOBJ.zObjectCode;
      tObjectFilterList = rktOBJ.tObjectFilterList;
    }

    TObject& operator = (const TObject& rktOBJ)
    {
      if( &rktOBJ != this )
      {
        ptMatrix        = rktOBJ.ptMatrix;
        ptInverseMatrix = rktOBJ.ptInverseMatrix;
  
        ptMaterial        = rktOBJ.ptMaterial;
        zObjectCode       = rktOBJ.zObjectCode;
        tObjectFilterList = rktOBJ.tObjectFilterList;
  
        tBoundingBox      = rktOBJ.tBoundingBox;
  
        TVolume::operator= (rktOBJ);
      }
      
      return *this;
    }
      
    virtual bool initialize (void);
    virtual void finalize (void) {}


    // These functions do exactly what they say they do.  The reason that they
    // exist, is because points, vectors, and normals should NOT be transformed
    // equally.  They should simplify the life of anyone using an object, as
    // they don't have to worry about which matrix does what, and how to modify
    // the data to make it real.
    // * Vectors do not care about length preservation.
    //   (9 muls, 6 adds)
    // * Normals require re-normalization after transformation, and must be
    //   transformed by the transposed matrix (strange, but there's
    //   mathematical reasons for it, which I no longer remember).
    //   (12 muls, 8 adds, 3 divs, 1 sqrt)
    // * Points must be scaled, translated, and de-homogenized to fully work with
    //   a generic transform matrix.
    //   (12 muls, 12 adds, 3 divs)
    TVector world_point_to_local(const TVector& point) const;
    TVector world_vector_to_local(const TVector& vec) const;
    TVector world_normal_to_local(const TVector& norm) const;
    TVector local_point_to_world(const TVector& point) const;
    TVector local_vector_to_world(const TVector& vec) const;
    TVector local_normal_to_world(const TVector& norm) const;

  
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

    void translate (const TVector& rktREL_POS);
    void rotate (const TVector& rktAXISPOINT1, const TVector& rktAXISPOINT2, TScalar tANGLE);
    void rotate (const TVector& rktANGLESXYZ);
    void rotate (const TQuaternion& rktQUAT);
    void scale (const TVector& rktSCALING_XYZ, const TVector& rktPOINT);
    void scale (const TVector& rktSCALING_XYZ) { scale(rktSCALING_XYZ,
						       TVector(0,0,0)); }
    virtual TVector location (void) const;
    virtual void setLocation(const TVector& rktLOCATION);

    virtual TVector normal (const TSurfaceData& rktDATA) const;

    TBoundingBox boundingBox (void) const { return tBoundingBox; }
    magic_pointer<TMaterial> material (void) const { return ptMaterial; }
    size_t objectCode (void) const { return zObjectCode; }
    const FilterListType filterList (void) const { return tObjectFilterList; }
    const TCapabilities& capabilities (void) const { return sCapabilities; }
    
    virtual void setMaterial (magic_pointer<TMaterial> ptMAT) { ptMaterial = ptMAT; }
    virtual void setObjectCode (size_t zCODE) { zObjectCode = zCODE; }

    virtual magic_pointer<TMatrix> transformMatrix (void) const { return ptMatrix; }
    virtual magic_pointer<TMatrix> inverseTransformMatrix (void) const { return ptInverseMatrix; }

    virtual void setTransformMatrix (const TMatrix& rktMATRIX)
    {
      ptMatrix = new TMatrix(rktMATRIX);
    }
    
    virtual void setInverseTransformMatrix (const TMatrix& rktMATRIX)
    {
      ptInverseMatrix = new TMatrix(rktMATRIX);
    }

    virtual void setTransformMatrix (const magic_pointer<TMatrix>& pktMATRIX)
    {
      ptMatrix = pktMATRIX;
    }
    
    virtual void setInverseTransformMatrix (const magic_pointer<TMatrix>& pktMATRIX)
    {
      ptInverseMatrix = pktMATRIX;
    }  

    virtual void addFilter (const magic_pointer<TObjectFilter> pktFILTER) { tObjectFilterList.push_back (pktFILTER); }
      
    virtual void getMesh (list<TMesh*>& rtMESH_LIST) const {}

    // Return a random point on the surface (preferred to be uniform).  This
    // point may not be required to actually be on the surface, but it is
    // required to hit the object when a ray is sent toward the point from
    // *almost* any origin (as there is always the near-tangent possibility).
    // Note that this point is to be in local coordinates (based on whatever
    // center of the object is defined as normal).  Use of this point should be
    // applied to the transform matrix before being used for anything other
    // than local operations.  
    // This will be most commonly used for things such as area lights.
    virtual TVector RandomPointOnSurface() const { return TVector(0,0,0); }
  
    virtual void streamDebug (ostream& o, const string& indent) const;  

    EClass classType (void) const { return FX_OBJECT_CLASS; }


    // Attribute management
    virtual int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
  
    virtual int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    virtual void getAttributeList (TAttributeList& rtLIST) const;
  
    virtual TUserFunctionMap getUserFunctions();
      
};  /* class TObject */

inline TVector TObject::normal (const TSurfaceData& rktDATA) const
{

  TVector   tPoint  = (*ptInverseMatrix) * rktDATA.point();
  TVector   tNormal = localNormal (tPoint);

  tNormal.applyTransform (&*ptInverseMatrix);
  tNormal.normalize();

  return tNormal;

}  /* normal() */


#endif  /* _OBJECT__ */
