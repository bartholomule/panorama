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

#ifndef _WORLEY_BASIS__
#define _WORLEY_BASIS__

#include "llapi/priority_queue.h"
#include "llapi/llapi_defs.h"

#define FX_RANDOM_TABLE_SIZE         256

class TWorleyBasis
{

  public:

    struct TPointData
    {
      TVector   tPoint;
      TScalar   tDistance;
      TVector   tVector;
    };
      
  protected:

    Byte      bNearestPoints;
    TScalar   atProbabilities [8];
    TScalar   atData [FX_RANDOM_TABLE_SIZE];
    int       aiPermutation [FX_RANDOM_TABLE_SIZE];

    mutable TVector   tBasePoint;
    
    TScalar hash (const TVector& rktPOINT) const;
    Byte getPoints (TScalar tVALUE) const;
    TScalar distance (const TVector& rktPOINT1, const TVector& rktPOINT2) const;
    void checkVoxel (const TVector& rktBASE_POINT,
                     const TVector& rktPOINT,
                     TPriorityQueue<TPointData>* ptPQUEUE) const;
    void checkVoxels (const TVector& rktBASE_POINT,
                      const TVector& rktPOINT,
                      Byte bMASK,
                      TPriorityQueue<TPointData>* ptPQUEUE) const;

  public:

    TWorleyBasis (Byte bNEAREST_POINTS, TScalar tLAMBDA = 3);

    TPriorityQueue<TPointData>* evaluate (const TVector& rktPOINT) const;

};  /* class TWorleyBasis */

#endif  /* _WORLEY_BASIS__ */
