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

  public:

    TObject (void) :
      ptMaterial (NULL),
      ptMatrix (NULL),
      ptInverseMatrix (NULL) {}
      
    virtual void initialize (void)
    {
      assert ( ptMaterial );
    }

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

    virtual TVector normal (const TSurfaceData& rktDATA) const = 0;

    TBoundingBox boundingBox (void) const { return tBoundingBox; }
    TMaterial* material (void) const { return ptMaterial; }
    size_t objectCode (void) const { return zObjectCode; }
    const list<const TObjectFilter*>& filterList (void) const { return tObjectFilterList; }

    virtual void setMaterial (TMaterial* ptMAT) { ptMaterial = ptMAT; }
    virtual void setObjectCode (size_t zCODE) { zObjectCode = zCODE; }

    virtual TMatrix* transformMatrix (void) const { return ptMatrix; }
    virtual TMatrix* inverseTransformMatrix (void) const { return ptInverseMatrix; }

    virtual void addFilter (const TObjectFilter* pktFILTER) { tObjectFilterList.push_back (pktFILTER); }
      
    virtual void getMesh (list<TMesh*>& rtMESH_LIST) const {}
    
    void printDebug (void) const;

    EClass classType (void) const { return FX_OBJECT_CLASS; }
      
};  /* class TObject */

#endif  /* _OBJECT__ */
