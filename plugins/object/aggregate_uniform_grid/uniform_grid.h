/*
*  Copyright (C) 1999 Angel Jimenez Jimenez and Carlos Jimenez Moreno
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

#ifndef _UNIFORM_GRID__
#define _UNIFORM_GRID__

#include <list>
#include "llapi/object.h"

#define ktHashBit           5
#define ktHashSize          (size_t) (1 << (3 * ktHashBit) )   // Hash table size (32768)
#define ktMask              ((1 << ktHashBit) - 1)             // 32 - 1 = 31 (11111)
#define ktLatticeCoordMax   32767
#define ktLatticeCoordMin   -32768

typedef Word    TUGBucketType;     // 2 bytes; [0, 65536]
typedef short   TUGLatticeCoord;   // 2 bytes; [0, 65536] (signed)

struct TUGVoxel
{		   

  TUGLatticeCoord         i, j, k;      // Cube key (lattice location of cube)
  list<const TObject*>    tObjectList;

};  /* struct TUGVoxel */

class TUniformGrid
{

  protected:

    list<TUGVoxel>*   aptVoxelHashTable [ktHashSize];

    TScalar   tVoxelSize;
    TScalar   tVoxelSize2;
    TScalar   tInvVoxelSize;

    TVector           tBoundingBoxPoint1;   // LBF (Left Bottom Far Point). Global coords
    TVector           tBoundingBoxPoint2;   // RTN (Right Top Near Point). Global coords
    TUGLatticeCoord   tMinX;                // tBoundingBoxPoint1 lattice coords
    TUGLatticeCoord   tMinY;
    TUGLatticeCoord   tMinZ;
    TUGLatticeCoord   tMaxX;                // tBoundingBoxPoint2 lattice coords
    TUGLatticeCoord   tMaxY;
    TUGLatticeCoord   tMaxZ;
    
    inline TUGBucketType hash (TUGLatticeCoord I, TUGLatticeCoord J, TUGLatticeCoord K) const
    {
      return (((((I & ktMask) << ktHashBit) | (J & ktMask)) << ktHashBit) | (K & ktMask));
    }

    bool boundingBoxIntersection (const TRay& rktRAY, TVector& rtVECT) const;

    bool findIntersectionInsideVoxel (TUGLatticeCoord tVOXEL_X, TUGLatticeCoord tVOXEL_Y, TUGLatticeCoord tVOXEL_Z,
                                      const TVector& rktPOINT_LC1, const TVector& rktPOINT_LC2,
                                      const TRay& rktRAY, TSurfaceData& rtDATA) const;
    
    void boundingPointRayDestination1 (const TRay& rktRAY, TUGLatticeCoord& rtBX, TUGLatticeCoord& rtBY, TUGLatticeCoord& rtBZ,
                                       TUGLatticeCoord tLATTICE_INC_X, TUGLatticeCoord tLATTICE_INC_Y, TUGLatticeCoord tLATTICE_INC_Z,
                                       TVector& rtRAY_DESTINATION_LC) const;
    void boundingPointRayDestination2 (const TRay& rktRAY, TUGLatticeCoord& rtBX, TUGLatticeCoord& rtBZ,
                                       TUGLatticeCoord tLATTICE_INC_X, TUGLatticeCoord tLATTICE_INC_Z,
                                       TVector& rtRAY_DESTINATION_LC) const;
    void boundingPointRayDestination3 (const TRay& rktRAY, TUGLatticeCoord& rtBY, TUGLatticeCoord& rtBZ,
                                       TUGLatticeCoord tLATTICE_INC_Y, TUGLatticeCoord tLATTICE_INC_Z,
                                       TVector& rtRAY_DESTINATION_LC) const;
    void boundingPointRayDestination4 (const TRay& rktRAY, TUGLatticeCoord& rtBX, TUGLatticeCoord& rtBY,
                                       TUGLatticeCoord tLATTICE_INC_X, TUGLatticeCoord tLATTICE_INC_Y,
                                       TVector& rtRAY_DESTINATION_LC) const;
    void boundingPointRayDestination5 (const TRay& rktRAY, TUGLatticeCoord& rtBY,
                                       TUGLatticeCoord tLATTICE_INC_Y,
                                       TVector& rtRAY_DESTINATION_LC) const;
    void boundingPointRayDestination6 (const TRay& rktRAY, TUGLatticeCoord& rtBX,
                                       TUGLatticeCoord tLATTICE_INC_X,
                                       TVector& rtRAY_DESTINATION_LC) const;
    void boundingPointRayDestination7 (const TRay& rktRAY, TUGLatticeCoord& rtBZ,
                                       TUGLatticeCoord tLATTICE_INC_Z,
                                       TVector& rtRAY_DESTINATION_LC) const;
    bool findFirstIntersection1 (const TRay& rktRAY, TSurfaceData& rtDATA) const;
    bool findFirstIntersection2 (const TRay& rktRAY, TSurfaceData& rtDATA) const;
    bool findFirstIntersection3 (const TRay& rktRAY, TSurfaceData& rtDATA) const;
    bool findFirstIntersection4 (const TRay& rktRAY, TSurfaceData& rtDATA) const;
    bool findFirstIntersection5 (const TRay& rktRAY, TSurfaceData& rtDATA) const;
    bool findFirstIntersection6 (const TRay& rktRAY, TSurfaceData& rtDATA) const;
    bool findFirstIntersection7 (const TRay& rktRAY, TSurfaceData& rtDATA) const;

    void add (TUGLatticeCoord tI, TUGLatticeCoord tJ, TUGLatticeCoord tK, const TObject* pktOBJECT);

  public:

    TUniformGrid (void)
    {
      tVoxelSize = 0;
      
      // Hash table initialization
      for (size_t m = 0; ( m < ktHashSize ) ;m++)
      {
        aptVoxelHashTable [m] = (list<TUGVoxel>*) NULL;
      }
    }

    ~TUniformGrid (void)
    {
      for (size_t m = 0; ( m < ktHashSize ) ;m++)
      {
        if ( aptVoxelHashTable [m] )
        {
          (aptVoxelHashTable [m])->clear();
          delete (aptVoxelHashTable [m]);
        }
      }
    }

    bool initialize (void);
    
    TVector boundingBoxPoint1 (void) const { return tBoundingBoxPoint1; }
    TVector boundingBoxPoint2 (void) const { return tBoundingBoxPoint2; }

    void setVoxelSize (TScalar tVOXEL_SIZE)
    {
      tVoxelSize    = tVOXEL_SIZE;
      tVoxelSize2   = tVOXEL_SIZE * tVOXEL_SIZE;
      tInvVoxelSize = 1.0 / tVoxelSize;
    }
    void calculateVoxelSize (const vector<TObject*>& rktOBJECT_LIST);

    void addObject (const TObject* pktOBJECT);

    bool findFirstIntersection (const TRay& rktRAY, TSurfaceData& rtDATA) const;
    
    void printGrid (void) const;

};  /* class TUniformGrid */

#endif  /* _UNIFORM_GRID__ */
