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

#ifndef _PLANE__
#define _PLANE__

#include "llapi/object.h"

class TPlane : public TObject
{

  protected:

    TScalar   D;
    TVector   tNormal;
    bool      gOneSided;

    void update (void);

  public:

    TPlane (void) :
      TObject(),
      tNormal (0, 0, 1),
      gOneSided (false)
    {
      sCapabilities.gInfinite = true;
    }
      
    bool findFirstIntersection (const TRay& rktRAY, TSurfaceData& rtDATA) const;
    bool findAllIntersections (const TRay& rktRAY, TSpanList& rtLIST) const;

    TVector normal (const TSurfaceData& rktDATA) const
    {
      if ( gOneSided )
      {
        return tNormal;
      }

      return (( dotProduct (tNormal, rktDATA.ray().direction()) < 0 ) ? tNormal : -tNormal);
    }

    TVector normal (void) const
    {
      return tNormal;
    }

    TBoundingBox boundingBox (void) const
    {
      // Dummy method to avoid compile errors
      TBoundingBox   tBBox;

      return tBBox;
    }
    
    int setAttribute (const std::string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const std::string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    virtual void setNormal (const TVector& rktNORMAL)
    {
      tNormal = rktNORMAL;
      update();
    }
    
    void setOneSided (bool gONE_SIDED)
    {
      gOneSided = gONE_SIDED;
    }

    //
    //  This method will be overriden in descendants (plane objects like
    //  polygons, circle, etc).  
    //
    virtual bool inside (const TVector& rktPOINT) const { return true; }

    void printDebug (const std::string& indent) const;
    std::string className (void) const { return "Plane"; }
    
};  /* class TPlane */

#endif  /* _PLANE__ */
