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

#include "llapi/debug.h"
#include "llapi/object.h"
#include "llapi/material.h"

void TObject::createMatrices (void)
{

  ptMatrix        = new TMatrix();
  ptInverseMatrix = new TMatrix();

  ptMatrix->setIdentity();
  ptInverseMatrix->setIdentity();
  
}  /* createMatrices() */


bool TObject::initialize (void)
{
  bool val = TProcedural::initialize();
  if ( ptMaterial == NULL )
  {
    bool is_light_only = false;
    bool contains_objects = false;
    TAttributeList tal;
    getAttributeList(tal);

    if(tal.find("lightonly") != tal.end())
    {
      is_light_only = true;
    }
    if(tal.find("containsobjects") != tal.end())
    {
      contains_objects = true;
    }
    
    if(!contains_objects && !is_light_only)
    {
      val = false;
      cerr << "Object of type " << className() << " has no material." << endl;
    }
  }
  else
  {
    val = val && ptMaterial->initialize();
  }

//  tLocation = (*ptMatrix) * tLocation;

  return val;
}  /* initialize() */


void TObject::translate (const TVector& rktNEW_POS)
{
  
  TMatrix   tMatrix;

  tMatrix.setTranslation (rktNEW_POS);
  (*ptMatrix) = tMatrix * (*ptMatrix);
  tMatrix.setTranslation (-rktNEW_POS);
  (*ptInverseMatrix) = (*ptInverseMatrix) * tMatrix;

  TVolume::translate (rktNEW_POS);
  
}  /* translate() */


void TObject::rotate (const TVector& rktAXISPOINT1, const TVector& rktAXISPOINT2, TScalar tANGLE)
{

  TMatrix   tMatrix;

  tMatrix.setRotation (rktAXISPOINT1, rktAXISPOINT2, tANGLE);
  (*ptMatrix) = tMatrix * (*ptMatrix);

  tMatrix.setRotation (rktAXISPOINT1, rktAXISPOINT2, -tANGLE);
  (*ptInverseMatrix) = (*ptInverseMatrix) * tMatrix;

}  /* rotate() */


void TObject::rotate (const TVector& rktANGLESXYZ)
{

  TMatrix   tMatrix;
  TVector   tOrigin = TVector (0, 0, 0);
  TVector   tAxisX  = TVector (1, 0, 0);
  TVector   tAxisY  = TVector (0, 1, 0);
  TVector   tAxisZ  = TVector (0, 0, 1);

  tOrigin = (*ptMatrix) * tOrigin;

  tAxisX = (*ptMatrix) * tAxisX;
  tAxisY = (*ptMatrix) * tAxisY;
  tAxisZ = (*ptMatrix) * tAxisZ;

  tMatrix.setRotation (tOrigin, tAxisX, rktANGLESXYZ.x());
  (*ptMatrix) = tMatrix * (*ptMatrix);
  tMatrix.setRotation (tOrigin, tAxisX, -(rktANGLESXYZ.x()));
  (*ptInverseMatrix) = (*ptInverseMatrix) * tMatrix;

  tMatrix.setRotation (tOrigin, tAxisY, rktANGLESXYZ.y());
  (*ptMatrix) = tMatrix * (*ptMatrix);
  tMatrix.setRotation (tOrigin, tAxisY, -(rktANGLESXYZ.y()));
  (*ptInverseMatrix) = (*ptInverseMatrix) * tMatrix;

  tMatrix.setRotation (tOrigin, tAxisZ, rktANGLESXYZ.z());
  (*ptMatrix) = tMatrix * (*ptMatrix);
  tMatrix.setRotation (tOrigin, tAxisZ, -(rktANGLESXYZ.z()));
  (*ptInverseMatrix) = (*ptInverseMatrix) * tMatrix;
    
}  /* rotate() */

void TObject::rotate (const TQuaternion& rktQUAT)
{
  TMatrix mat = matrixFromQuaternion (rktQUAT);
  
  (*ptMatrix) = mat * (*ptMatrix);
  (*ptInverseMatrix) = (*ptInverseMatrix) * invert(mat);
  
#if DEBUG_IT
  cerr << "mat=";
  mat.printDebug();
  
  cerr << "rotate... m,i=";
  ptMatrix->printDebug();
  ptInverseMatrix->printDebug();
#endif /* DEBUG_IT */
}


void TObject::scale (const TVector& rktSCALING_XYZ, const TVector& rktPOINT)
{

  TVector   tInverseScaling;
  TMatrix   tMatrix;

  tMatrix.setScaling (rktSCALING_XYZ, rktPOINT);
  (*ptMatrix) = tMatrix * (*ptMatrix);

  tInverseScaling.set (1.0 / rktSCALING_XYZ.x(), 1.0 / rktSCALING_XYZ.y(), 1.0 / rktSCALING_XYZ.z());
  tMatrix.setScaling (tInverseScaling, rktPOINT);
  (*ptInverseMatrix) = (*ptInverseMatrix) * tMatrix;

}  /* scale() */


void TObject::printDebug (void) const
{

  cerr << TDebug::_indent() << "[_" << className() << "_]" << endl;

  TDebug::_push();
  
  cerr << TDebug::_indent() << "Code     : " << zObjectCode << endl;
  cerr << TDebug::_indent() << "Location : "; tLocation.printDebug(); cerr << endl;
  cerr << TDebug::_indent(); ptMaterial->printDebug(); cerr << endl;

  TDebug::_pop();
  
}  /* printDebug() */
