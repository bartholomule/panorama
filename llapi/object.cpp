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

#include <string>
#include "llapi/debug.h"
#include "llapi/object.h"
#include "llapi/material.h"
#include "llapi/object_required.h"

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
  if ( !ptMaterial )
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

  return val;
}  /* initialize() */


void TObject::translate (const TVector& rktNEW_POS)
{
  //  cerr << "TObject: Translating:"; rktNEW_POS.printDebug(""); cerr << endl;
  ptMatrix.copy_for_write();
  ptInverseMatrix.copy_for_write();  
  
  TMatrix   tMatrix;

  tMatrix.setTranslation (rktNEW_POS); 
  (*ptMatrix) = tMatrix * (*ptMatrix);
  tMatrix.setTranslation (-rktNEW_POS);
  (*ptInverseMatrix) = (*ptInverseMatrix) * tMatrix;

  // FIXME!  If it proves that translations are not working correctly, fix this:
  //TVolume::translate (rktNEW_POS);

  //  cerr << "TObject: translate: new location="; location().printDebug(""); cerr << endl;
  
}  /* translate() */


void TObject::rotate (const TVector& rktAXISPOINT1, const TVector& rktAXISPOINT2, TScalar tANGLE)
{
  ptMatrix.copy_for_write();
  ptInverseMatrix.copy_for_write();    

  TMatrix   tMatrix;

  tMatrix.setRotation (rktAXISPOINT1, rktAXISPOINT2, tANGLE);
  (*ptMatrix) = tMatrix * (*ptMatrix);

  tMatrix.setRotation (rktAXISPOINT1, rktAXISPOINT2, -tANGLE);
  (*ptInverseMatrix) = (*ptInverseMatrix) * tMatrix;

}  /* rotate() */


void TObject::rotate (const TVector& rktANGLESXYZ)
{
  ptMatrix.copy_for_write();
  ptInverseMatrix.copy_for_write();
  
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
  mat.printDebug("");
  
  cerr << "rotate... m,i=";
  ptMatrix->printDebug("");
  ptInverseMatrix->printDebug("");
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

TVector TObject::location (void) const
{
  static const TVector zero_vector(0.0,0.0,0.0);

  return local_point_to_world(zero_vector);
}

void TObject::setLocation(const TVector& rktLOCATION)
{
  static const TVector zero_vector(0.0,0.0,0.0);
  
  TVector difference = rktLOCATION - location();

  translate (difference);

  // FIXME!  If TEntity::tLocation is no longer modified by anything, remove
  // this! 
  //  TEntity::tLocation = zero_vector;
}

void TObject::streamDebug (ostream& o, const string& indent) const
{
  TVolume::streamDebug (o,indent);
  string new_indent = TDebug::Indent(indent);
  
  o << new_indent << "Code     : " << zObjectCode << endl;
  o << new_indent << "Location : "; location().printDebug(new_indent); o << endl;
  if( !!ptMaterial )
  {
    ptMaterial->printDebug(new_indent);
  }
  else
  {
    o << new_indent << "Material : NULL" << endl;
  }
  o << indent << "." << endl;  
}

int TObject::setAttribute (const string& rktNAME, NAttribute nVALUE,
			       EAttribType eTYPE)
{
  if(rktNAME == "material")
  {
#if !defined(NEW_ATTRIBUTES)    
    if(eTYPE == FX_MATERIAL)
    {
      setMaterial(((TMaterial*)nVALUE.pvValue)->clone_new());
      return FX_ATTRIB_OK;
    }
#else
    magic_pointer<TAttribMaterial> mat = get_material(nVALUE);
    if( !!mat )
    {
      setMaterial (mat->tValue);
      return FX_ATTRIB_OK;
    }
#endif
    return FX_ATTRIB_WRONG_TYPE;
  }
  else
  {
    return TVolume::setAttribute (rktNAME, nVALUE, eTYPE);
  }
}

int TObject::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{
  if(rktNAME == "material")
  {
#if !defined(NEW_ATTRIBUTES)    
    rnVALUE.pvValue = (void*)ptMaterial.get_pointer();
#else
    rnVALUE = new TAttribMaterial (ptMaterial);
#endif
    return FX_ATTRIB_OK;
  }
  return TVolume::getAttribute( rktNAME, rnVALUE );
}

void TObject::getAttributeList (TAttributeList& rtLIST) const
{
  TVolume::getAttributeList(rtLIST);
  
  rtLIST ["material"] = FX_MATERIAL;
}

TUserFunctionMap TObject::getUserFunctions()
{
  TUserFunctionMap ufm = TVolume::getUserFunctions();

  ufm["translate"]   = create_user_function(this,&TObject::translate);
  ufm["setMaterial"] = create_user_function(this,&TObject::setMaterial);
  ufm["getMaterial"] = create_user_function(this,&TObject::material);
  ufm["randomPoint"] = create_user_function(this,&TObject::RandomPointOnSurface);
  ufm["setLocation"] = create_user_function(this,&TObject::setLocation);

  // A temp variable, so that full compile-time checking can be done (not
  // possible with a direct cast). 
  void (TObject::*scale_fn)(const TVector&) = &TObject::scale;
  ufm["scale"] = create_user_function(this,scale_fn);
  void (TObject::*rot_fn)(const TVector&) = &TObject::rotate;  
  ufm["rotate"]      = create_user_function(this,rot_fn);

  return ufm;
}


TVector TObject::world_point_to_local(const TVector& point) const
{
  if(!!ptMatrix)
  {
    const TMatrix& rktMat = *ptInverseMatrix;

    TScalar h = (rktMat.getElement(3, 0) * point.x() +
		 rktMat.getElement(3, 1) * point.y() +
		 rktMat.getElement(3, 2) * point.z() +
		 rktMat.getElement(3, 3));
    
    TVector retvec ((rktMat.getElement(0, 0) * point.x() +
		     rktMat.getElement(0, 1) * point.y() +
		     rktMat.getElement(0, 2) * point.z() +
		     rktMat.getElement(0, 3)) / h,
		    (rktMat.getElement(1, 0) * point.x() +
		     rktMat.getElement(1, 1) * point.y() +
		     rktMat.getElement(1, 2) * point.z() +
		     rktMat.getElement(1, 3)) / h,
		    (rktMat.getElement(2, 0) * point.x() +
		     rktMat.getElement(2, 1) * point.y() +
		     rktMat.getElement(2, 2) * point.z() +
		     rktMat.getElement(2, 3)) / h);
    
    return retvec;
  }
  return point;
}
TVector TObject::world_vector_to_local(const TVector& vec) const
{
  if(!!ptMatrix)
  {
    const TMatrix& rktMat = *ptInverseMatrix;
    
    TVector retvec ((rktMat.getElement(0, 0) * vec.x() +
		     rktMat.getElement(0, 1) * vec.y() +
		     rktMat.getElement(0, 2) * vec.z()),
		    (rktMat.getElement(1, 0) * vec.x() +
		     rktMat.getElement(1, 1) * vec.y() +
		     rktMat.getElement(1, 2) * vec.z()),
		    (rktMat.getElement(2, 0) * vec.x() +
		     rktMat.getElement(2, 1) * vec.y() +
		     rktMat.getElement(2, 2) * vec.z()));
    
    return retvec;
  }
  return vec;
}
TVector TObject::world_normal_to_local(const TVector& norm) const
{
  if(!!ptMatrix)
  {
    const TMatrix& rktMat = *ptInverseMatrix;
    
    TVector retvec ((rktMat.getElement(0, 0) * norm.x() +
		     rktMat.getElement(1, 0) * norm.y() +
		     rktMat.getElement(2, 0) * norm.z()),
		    (rktMat.getElement(0, 1) * norm.x() +
		     rktMat.getElement(1, 1) * norm.y() +
		     rktMat.getElement(2, 1) * norm.z()),
		    (rktMat.getElement(0, 2) * norm.x() +
		     rktMat.getElement(1, 2) * norm.y() +
		     rktMat.getElement(2, 2) * norm.z()));
    
    return retvec / retvec.norm();
  }
  return norm;    
}
TVector TObject::local_point_to_world(const TVector& point) const
{
  if(!!ptInverseMatrix)
  {
    const TMatrix& rktMat = *ptMatrix;

    TScalar h = (rktMat.getElement(3, 0) * point.x() +
		 rktMat.getElement(3, 1) * point.y() +
		 rktMat.getElement(3, 2) * point.z() +
		 rktMat.getElement(3, 3));
    
    TVector retvec ((rktMat.getElement(0, 0) * point.x() +
		     rktMat.getElement(0, 1) * point.y() +
		     rktMat.getElement(0, 2) * point.z() +
		     rktMat.getElement(0, 3)) / h,
		    (rktMat.getElement(1, 0) * point.x() +
		     rktMat.getElement(1, 1) * point.y() +
		     rktMat.getElement(1, 2) * point.z() +
		     rktMat.getElement(1, 3)) / h,
		    (rktMat.getElement(2, 0) * point.x() +
		     rktMat.getElement(2, 1) * point.y() +
		     rktMat.getElement(2, 2) * point.z() +
		     rktMat.getElement(2, 3)) / h);
    
    return retvec;
  }
  return point;
}
TVector TObject::local_vector_to_world(const TVector& vec) const
{
  if(!!ptInverseMatrix)
  {
    const TMatrix& rktMat = *ptMatrix;
    
    TVector retvec ((rktMat.getElement(0, 0) * vec.x() +
		     rktMat.getElement(0, 1) * vec.y() +
		     rktMat.getElement(0, 2) * vec.z()),
		    (rktMat.getElement(1, 0) * vec.x() +
		     rktMat.getElement(1, 1) * vec.y() +
		     rktMat.getElement(1, 2) * vec.z()),
		    (rktMat.getElement(2, 0) * vec.x() +
		     rktMat.getElement(2, 1) * vec.y() +
		     rktMat.getElement(2, 2) * vec.z()));
    
    return retvec;
  }
  return vec;
}
TVector TObject::local_normal_to_world(const TVector& norm) const
{
  if(!!ptInverseMatrix)
  {
    const TMatrix& rktMat = *ptMatrix;
    
    TVector retvec ((rktMat.getElement(0, 0) * norm.x() +
		     rktMat.getElement(1, 0) * norm.y() +
		     rktMat.getElement(2, 0) * norm.z()),
		    (rktMat.getElement(0, 1) * norm.x() +
		     rktMat.getElement(1, 1) * norm.y() +
		     rktMat.getElement(2, 1) * norm.z()),
		    (rktMat.getElement(0, 2) * norm.x() +
		     rktMat.getElement(1, 2) * norm.y() +
		     rktMat.getElement(2, 2) * norm.z()));
    
    return retvec / retvec.norm();
  }
  return norm;    
}

