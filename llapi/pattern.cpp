/*
*  Copyright (C) 2000 Jon Frydensbjerg
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

#include "llapi/warning_eliminator.h"
#include "llapi/pattern.h"
#include "llapi/object.h"
#include "llapi/attribute.h"
#include "llapi/user_functions.h"
#include "llapi/object_required.h"

static std::map<EWarps,const char*> warp_strings;

static void set_warp_strings (void)
{
  warp_strings[FX_NO_WARP] = "none";
  warp_strings[FX_SPHERICAL_WARP] = "spherical";
  warp_strings[FX_CYLINDRICAL_WARP] = "cylindrical";
}

bool TPattern::initialize (void)
{
  tScaling    = TVector (1.0, 1.0, 1.0);
  tRSTScaling = TVector (1.0, 1.0, 1.0);

  eWarp = FX_NO_WARP;

  recalculateMatrix();

  gTransformIdentity = true;

  return TProcedural::initialize();
}  /* initialize() */


void TPattern::recalculateMatrix (void)
{

  static const TVector _ktTestVector = TVector (1.0, 2.0, 3.0);

  TMatrix   tTempMatrix;
  TVector   tInverseScaling;
  TVector   tVector = _ktTestVector;

  tInverseScaling.set (1.0 / tScaling.x(), 1.0 / tScaling.y(), 1.0 / tScaling.z());

  tMatrix.setIdentity();
  tInverseMatrix.setIdentity();
  tMatrixRotation.setIdentity();

  // Translation
  tTempMatrix.setTranslation (tTranslation);
  tMatrix = tTempMatrix * tMatrix;
  tTempMatrix.setTranslation (-tTranslation);
  tInverseMatrix = tInverseMatrix * tTempMatrix;

  // X Rotation
  tTempMatrix.setRotationX (tRotation.x());
  tMatrixRotation = tTempMatrix * tMatrixRotation;
  tMatrix = tTempMatrix * tMatrix;
  tTempMatrix.setRotationX (-tRotation.x());
  tInverseMatrix = tInverseMatrix * tTempMatrix;

  // Y Rotation
  tTempMatrix.setRotationY (tRotation.y());
  tMatrixRotation = tTempMatrix * tMatrixRotation;
  tMatrix = tTempMatrix * tMatrix;
  tTempMatrix.setRotationY (-tRotation.y());
  tInverseMatrix = tInverseMatrix * tTempMatrix;

  // Z Rotation
  tTempMatrix.setRotationZ (tRotation.z());
  tMatrixRotation = tTempMatrix * tMatrixRotation;
  tMatrix = tTempMatrix * tMatrix;
  tTempMatrix.setRotationZ (-tRotation.z());
  tInverseMatrix = tInverseMatrix * tTempMatrix;

  // Scaling
  tTempMatrix.setScaling (tScaling, TVector(0, 0, 0));
  tMatrix = tTempMatrix * tMatrix;
  tTempMatrix.setScaling (tInverseScaling, TVector(0, 0, 0));
  tInverseMatrix = tInverseMatrix * tTempMatrix;

  gTransformIdentity = false;

  tVector = tMatrix * tVector;

  if ( tVector == _ktTestVector )
  {
    gTransformIdentity = true;
  }

}  /* recalculateMatrix() */


void TPattern::sphericalWarp (TVector& rtPOINT) const
{

  TScalar  fx = rtPOINT.x();
  TScalar  fy = rtPOINT.y();
  TScalar  fz = rtPOINT.z();

  TScalar  r    = rtPOINT.norm();
  TScalar  elev = atan2 (fy, sqrt (fx * fx + fz *fz)) / PI * 0.5;
  TScalar  ang  = atan2 (fz, fx) / PI * 0.5;

  rtPOINT.set (r, elev, ang);

}  /* sphericalWarp() */


void TPattern::sphericalAntiWarp (TVector& rtPOINT) const
{

  TScalar  r    = rtPOINT.x();
  TScalar  elev = rtPOINT.y() * PI * 2.0;
  TScalar  ang  = rtPOINT.z() * PI * 2.0;

  TScalar  x = r * cos (elev) * cos (ang);
  TScalar  y = r * sin (elev);
  TScalar  z = r * cos (elev) * sin (ang);

  rtPOINT.set (x, y, z);

}  /* sphericalAntiWarp() */


void TPattern::cylindricalWarp (TVector& rtPOINT) const
{

  TScalar  fx   = rtPOINT.x();
  TScalar  fz   = rtPOINT.z();
  TScalar  r    = sqrt (fx * fx + fz * fz);
  TScalar  ang  = atan2 (fz, fx) / PI * 0.5;

  rtPOINT.setX (r);
  rtPOINT.setZ (ang);

}  /* cylindricalWarp() */


void TPattern::cylindricalAntiWarp (TVector& rtPOINT) const
{

  TScalar  r    = rtPOINT.x();
  TScalar  ang  = rtPOINT.z() * PI * 2.0;

  TScalar  x = r * cos (ang);
  TScalar  z = r * sin (ang);

  rtPOINT.setX (x);
  rtPOINT.setZ (z);

}  /* cylindricalAntiWarp() */


TVector TPattern::warp (const TVector& rktPOINT) const
{

  TVector  tNewPoint = rktPOINT;

  if ( !gTransformIdentity )
  {
    tNewPoint = tMatrix * tNewPoint;
  }

  switch (eWarp)
  {
    case (FX_SPHERICAL_WARP) :
      sphericalWarp (tNewPoint);
      break;

    case (FX_CYLINDRICAL_WARP) :
      cylindricalWarp (tNewPoint);
      break;

    default:
      break;
  }

  return tNewPoint * tRSTScaling;

}  /* warp() */


TVector TPattern::antiWarp (const TVector& rktPOINT) const
{

  TVector  tNewPoint = rktPOINT / tRSTScaling;

  switch (eWarp)
  {
    case (FX_SPHERICAL_WARP) :
      sphericalAntiWarp (tNewPoint);
      break;

    case (FX_CYLINDRICAL_WARP) :
      cylindricalAntiWarp (tNewPoint);
      break;

    default:
      break;
  }

  if ( !gTransformIdentity )
  {
    tNewPoint = tInverseMatrix * tNewPoint;
  }

  return tNewPoint;

}  /* antiWarp() */


TColor TPattern::color (const TSurfaceData& rktDATA) const
{

  TSurfaceData  tData   = rktDATA;
  TPoint tPoint = warp(rktDATA.localPoint());
  TVector tNormal;

  if ( rktDATA.object() )
  {
    tNormal = rktDATA.unperturbedNormal();

    if ( !gTransformIdentity )
    {
      tNormal.applyTransform (tMatrixRotation);
    }

    // Convoluted junk?
    tPoint = *rktDATA.object()->transformMatrix() * tPoint;

    tData.setPoint  (tPoint);
    tData.setUnperturbedNormal (tNormal);
  }
  else
  {
    tData.setPoint (tPoint);

    tNormal = -tPoint;
    tNormal.normalize();

    tData.setUnperturbedNormal (tNormal);
  }

  tColor = pattern (tData);

  return tColor;

}  /* color() */

TScalar TPattern::scalar(const TSurfaceData& rktDATA) const
{
  return average(color(rktDATA));
}


int TPattern::setAttribute (const std::string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "rotation" )
  {
    magic_pointer<TAttribVector> vec = get_vector(nVALUE);
    if( !!vec )
    {
      tRotation = vec->tValue;

      recalculateMatrix();
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "scaling" )
  {
    magic_pointer<TAttribVector> vec = get_vector(nVALUE);
    if( !!vec )
    {
      tScaling = vec->tValue;

      recalculateMatrix();
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "translation" )
  {
    magic_pointer<TAttribVector> vec = get_vector(nVALUE);
    if( !!vec )
    {
      tTranslation = vec->tValue;

      recalculateMatrix();
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "warp" )
  {
    if ( eTYPE == FX_STRING )
    {
      magic_pointer<TAttribString> str = get_string(nVALUE);
      if( !str )
      {
        return FX_ATTRIB_WRONG_TYPE;
      }
      std::string tWarp = str->tValue;

      if ( tWarp == "spherical" )
      {
        eWarp = FX_SPHERICAL_WARP;
      }
      else if ( tWarp == "cylindrical" )
      {
        eWarp = FX_CYLINDRICAL_WARP;
      }
      else if ( tWarp == "none" )
      {
        eWarp = FX_NO_WARP;
      }
      else
      {
        return FX_ATTRIB_WRONG_VALUE;
      }
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "rst_scaling" )
  {
    magic_pointer<TAttribVector> vec = get_vector(nVALUE);
    if( !!vec )
    {
      tRSTScaling = vec->tValue;
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else
  {
    return TProcedural::setAttribute (rktNAME, nVALUE, eTYPE);
  }

  return FX_ATTRIB_OK;

}  /* setAttribute() */


int TPattern::getAttribute (const std::string& rktNAME, NAttribute& rnVALUE)
{
  if( warp_strings.empty() )
  {
    set_warp_strings ();
  }

  if ( rktNAME == "rotation" )
  {
    rnVALUE = (user_arg_type)new TAttribVector (tRotation);
  }
  else if ( rktNAME == "scaling" )
  {
    rnVALUE = (user_arg_type)new TAttribVector (tScaling);
  }
  else if ( rktNAME == "translation" )
  {
    rnVALUE = (user_arg_type)new TAttribVector (tTranslation);
  }
  else if ( rktNAME == "warp" )
  {
    const char* warp_name = warp_strings[eWarp];
    std::vector<std::string> choices;
    choices.push_back (warp_strings[FX_NO_WARP]);
    choices.push_back (warp_strings[FX_SPHERICAL_WARP]);
    choices.push_back (warp_strings[FX_CYLINDRICAL_WARP]);
    rnVALUE = (user_arg_type)new TAttribStringList (choices, warp_name);
  }
  else if ( rktNAME == "rst_scaling" )
  {
    rnVALUE = (user_arg_type)new TAttribVector (tRSTScaling);
  }
  else
  {
    return TProcedural::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TPattern::getAttributeList (TAttributeList& rtLIST) const
{

  TProcedural::getAttributeList (rtLIST);

  rtLIST ["rotation"]    = FX_VECTOR;
  rtLIST ["scaling"]     = FX_VECTOR;
  rtLIST ["translation"] = FX_VECTOR;
  rtLIST ["warp"]        = FX_STRING_LIST;
  rtLIST ["rst_scaling"] = FX_VECTOR;

}  /* getAttributeList() */

TUserFunctionMap TPattern::getUserFunctions()
{
  TUserFunctionMap ufm = TProcedural::getUserFunctions();

  ufm["setColor"]  = create_user_function(this,&TPattern::setColor);
  ufm["setScalar"] = create_user_function(this,&TPattern::setScalar);
  ufm["warp"]      = create_user_function(this,&TPattern::warp);
  ufm["unwarp"]    = create_user_function(this,&TPattern::antiWarp);

  return ufm;
}
