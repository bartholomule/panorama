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

#ifndef _TRANSFORM_OBJECT__
#define _TRANSFORM_OBJECT__

#include "llapi/object.h"

class TTransformObject : public TObject
{
  
  protected:

    TMatrix*   ptMatrix;
    TMatrix*   ptInverseMatrix;
    
    virtual TVector localNormal (const TVector& rktPOINT) const { return TVector (0, 0 ,0); }
    void createMatrices (void);

  public:

    TTransformObject (void) :
      TObject()
    {
      createMatrices();
    }

    virtual ~TTransformObject (void)
    {
      delete ptMatrix;
      delete ptInverseMatrix;
    }
      
    void translate (const TVector& rktNEW_POS);
    void rotate (const TVector& rktAXISPOINT1, const TVector& rktAXISPOINT2, TScalar tANGLE);
    void rotate (const TVector& rktANGLESXYZ);
    void scale (const TVector& rktSCALING_XYZ, const TVector& rktPOINT);

    virtual TMatrix* transformMatrix (void) const { return ptMatrix; }
    virtual TMatrix* inverseTransformMatrix (void) const { return ptInverseMatrix; }

    virtual TVector normal (const TSurfaceData& rktDATA) const;
    
};  /* class TTransformObject */


inline TVector TTransformObject::normal (const TSurfaceData& rktDATA) const
{

  TVector   tPoint  = (*ptInverseMatrix) * rktDATA.point();
  TVector   tNormal = localNormal (tPoint);

  tNormal.applyTransform (ptInverseMatrix);
  tNormal.normalize();

  return tNormal;

}  /* normal() */

#endif  /* _TRANSFORM_OBJECT__ */
