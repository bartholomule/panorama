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

#ifndef _BOUNDING_BOX__
#define _BOUNDING_BOX__

#include <vector>
#include "llapi/volume.h"

class TObject;

class TBoundingBox : public TVolume
{

  protected:

    TVector   tPoint1, tPoint2;

  public:

    TBoundingBox (void) {}

    TBoundingBox (const TVector& rktPOINT1, const TVector& rktPOINT2) :
      TVolume(),
      tPoint1 (rktPOINT1),
      tPoint2 (rktPOINT2) {}

    TBoundingBox (const TInterval& tINTX, const TInterval& tINTY, const TInterval& tINTZ) :
      TVolume(),
      tPoint1 (tINTX.min(), tINTY.min(), tINTZ.min()),
      tPoint2 (tINTX.max(), tINTY.max(), tINTZ.max()) {}

    TBoundingBox (const TBoundingBox& rktBBOX) :
      TVolume(rktBBOX),
      tPoint1 (rktBBOX.tPoint1),
      tPoint2 (rktBBOX.tPoint2) {}
      
    TBoundingBox& operator = (const TBoundingBox& rktBBOX)
    {
      if( &rktBBOX != this )
      {
        tPoint1 = rktBBOX.tPoint1;
        tPoint2 = rktBBOX.tPoint2;

        TVolume::operator= (rktBBOX);
      }
      
      return *this;
    }

    void set (const TVector& rktPOINT1, const TVector& rktPOINT2)
    {
      tPoint1 = rktPOINT1;
      tPoint2 = rktPOINT2;
    }

    void translate (const TVector& rktNEW_POS)
    {
      set (rktNEW_POS, rktNEW_POS + (tPoint2 - tPoint1));
    }
    
    void applyTransform (const TMatrix& rktMATRIX);
    
    bool intersects (const TRay& rktRAY) const;

    TInterval limits (Byte bAXIS) const
    {
      assert ( bAXIS < 3 );
      if ( bAXIS == 0)
      {
        return xlimits();
      }
      else if ( bAXIS == 1 )
      {
        return ylimits();
      }
      return zlimits();
    }
    
    TInterval xlimits (void) const { return TInterval (tPoint1.x(), tPoint2.x()); }
    TInterval ylimits (void) const { return TInterval (tPoint1.y(), tPoint2.y()); }
    TInterval zlimits (void) const { return TInterval (tPoint1.z(), tPoint2.z()); }

    TInterval clipRay (const TRay& rktRAY) const;
    
    TScalar cost (void) const;
    
    void printDebug (void) const;
    
    EClass classType (void) const { return FX_BOUNDING_BOX_CLASS; }
    string className (void) const { return "BoundingBox"; }

};  /* class TBoundingBox */


bool Disjoint (const TBoundingBox& rktBBOX1, const TBoundingBox& rktBBOX2);
TBoundingBox Merge (const vector<TObject*>& rktLIST);
TBoundingBox Union (const TBoundingBox& rktBBOX1, const TBoundingBox& rktBBOX2);
TBoundingBox Intersection (const TBoundingBox& rktBBOX1, const TBoundingBox& rktBBOX2);

#endif  /* _BOUNDING_BOX__ */
