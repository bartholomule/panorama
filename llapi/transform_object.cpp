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

#include <assert.h>
#include "llapi/transform_object.h"

void TTransformObject::createMatrices (void)
{

  ptMatrix        = new TMatrix();
  ptInverseMatrix = new TMatrix();

  ptMatrix->setIdentity();
  ptInverseMatrix->setIdentity();
  
}  /* createMatrices() */


void TTransformObject::translate (const TVector& rktNEW_POS)
{
  
  TMatrix   tMatrix;

  tMatrix.setTranslation (rktNEW_POS);
  (*ptMatrix) = tMatrix * (*ptMatrix);
  tMatrix.setTranslation (-rktNEW_POS);
  (*ptInverseMatrix) = (*ptInverseMatrix) * tMatrix;

  tLocation = rktNEW_POS;
  update();
  
}  /* translate() */


void TTransformObject::rotate (const TVector& rktAXISPOINT1, const TVector& rktAXISPOINT2, TScalar tANGLE)
{

  TMatrix   tMatrix;

  tMatrix.setRotation (rktAXISPOINT1, rktAXISPOINT2, tANGLE);
  (*ptMatrix) = tMatrix * (*ptMatrix);

  tMatrix.setRotation (rktAXISPOINT1, rktAXISPOINT2, -tANGLE);
  (*ptInverseMatrix) = (*ptInverseMatrix) * tMatrix;

}  /* rotate() */


void TTransformObject::rotate (const TVector& rktANGLESXYZ)
{

  TMatrix   tMatrix;
  TVector   tOrigin = TVector (0, 0, 0);
  TVector   tAxisX  = TVector (1, 0, 0);
  TVector   tAxisY  = TVector (0, 1, 0);
  TVector   tAxisZ  = TVector (0, 0, 1);

  tOrigin = (*ptMatrix) * tOrigin;

  tAxisX  = (*ptMatrix) * tAxisX;
  tMatrix.setRotation (tOrigin, tAxisX, rktANGLESXYZ.x());
  (*ptMatrix) = tMatrix * (*ptMatrix);
  tMatrix.setRotation (tOrigin, tAxisX, -(rktANGLESXYZ.x()));
  (*ptInverseMatrix) = (*ptInverseMatrix) * tMatrix;

  tAxisY = (*ptMatrix) * tAxisY;
  tMatrix.setRotation (tOrigin, tAxisY, rktANGLESXYZ.y());
  (*ptMatrix) = tMatrix * (*ptMatrix);
  tMatrix.setRotation (tOrigin, tAxisY, -(rktANGLESXYZ.y()));
  (*ptInverseMatrix) = (*ptInverseMatrix) * tMatrix;

  tAxisZ = (*ptMatrix) * tAxisZ;
  tMatrix.setRotation (tOrigin, tAxisZ, rktANGLESXYZ.z());
  (*ptMatrix) = tMatrix * (*ptMatrix);
  tMatrix.setRotation (tOrigin, tAxisZ, -(rktANGLESXYZ.z()));
  (*ptInverseMatrix) = (*ptInverseMatrix) * tMatrix;
    
}  /* rotate() */


void TTransformObject::scale (const TVector& rktSCALING_XYZ, const TVector& rktPOINT)
{

  TVector   tInverseScaling;
  TMatrix   tMatrix;

  tMatrix.setScaling (rktSCALING_XYZ, rktPOINT);
  (*ptMatrix) = tMatrix * (*ptMatrix);

  tInverseScaling.set (1.0 / rktSCALING_XYZ.x(), 1.0 / rktSCALING_XYZ.y(), 1.0 / rktSCALING_XYZ.z());
  tMatrix.setScaling (tInverseScaling, rktPOINT);
  (*ptInverseMatrix) = (*ptInverseMatrix) * tMatrix;

}  /* scale() */
