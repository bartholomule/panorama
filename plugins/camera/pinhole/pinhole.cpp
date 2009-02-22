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

#include "llapi/warning_eliminator.h"
#include "pinhole.h"
#include "llapi/attribute.h"

DEFINE_PLUGIN ("PinholeCamera", FX_CAMERA_CLASS, TPinholeCamera);

int TPinholeCamera::setAttribute (const std::string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "angle" )
  {
#if !defined(NEW_ATTRIBUTES)
    if ( eTYPE == FX_REAL )
    {
      setAngle (nVALUE.dValue);
    }
#else
    magic_pointer<TAttribReal> r = get_real(nVALUE);
    if( !!r )
    {
      setAngle (r->tValue);
    }
#endif
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else
  {
    return TCamera::setAttribute (rktNAME, nVALUE, eTYPE);
  }

  return FX_ATTRIB_OK;

}  /* setAttribute() */


int TPinholeCamera::getAttribute (const std::string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "angle" )
  {
#if !defined(NEW_ATTRIBUTES)
    rnVALUE.dValue = tHalfAngle * 2;
#else
    rnVALUE = (user_arg_type)new TAttribReal (tHalfAngle * 2);    
#endif
  }
  else
  {
    return TCamera::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TPinholeCamera::getAttributeList (TAttributeList& rtLIST) const
{

  TCamera::getAttributeList (rtLIST);

  rtLIST ["angle"] = FX_REAL;

}  /* getAttributeList() */


bool TPinholeCamera::initialize (void)
{
  bool val = true;

  tDirection = (tLookAt - location());
  tDirection.normalize();

  if ( fabs (dotProduct (tDirection, tUp)) == 1 )
  {
    GOM.error() << "Error: Camera direction and up std::vectors cannot be parallel" << std::endl;
    val = false;
  }
  
  I = crossProduct (tDirection, tUp);
  J = crossProduct (I, tDirection);
  I.normalize();
  J.normalize();

  tPixelSize = tan (tHalfAngle) / tHalfResX;

  I *= tPixelSize;
  J *= tPixelSize;

  return val && TCamera::initialize();
}  /* initialize() */


bool TPinholeCamera::getPlaneProjection (const TVector& rktPOINT, TVector2& rtPROJ) const
{

  TScalar   u, v;
  TScalar   pt, pu, pv;
  TVector   tPoint = (rktPOINT - location());
  
  pt = dotProduct (tDirection, tPoint);
  pu = dotProduct (I, tPoint) / tPixelSize;
  pv = dotProduct (J, tPoint) / tPixelSize;

  u = tHalfResX + ((pu / pt) / tPixelSize);
  if ( ( u < 0 ) || ( u > (tHalfResX * 2) ) )
  {
    return false;
  }
  v = tHalfResY - ((pv / pt) / tPixelSize);
  if ( ( v < 0 ) || ( v > (tHalfResY * 2) ) )
  {
    return false;
  }

  rtPROJ.set (u, v);
  
  return true;
  
}  /* getPlaneProjection() */


void TPinholeCamera::printDebug (const std::string& indent) const
{

  GOM.debug() << indent << "[_" << className() << "_]" << std::endl;

  std::string new_indent = TDebug::Indent(indent);

  GOM.debug() << new_indent << "Angle     : " << getAngle() << std::endl;
  GOM.debug() << new_indent << "Up std::vector : "; tUp.printDebug(new_indent);
  GOM.debug() << new_indent << "Look at   : "; tLookAt.printDebug(new_indent);
  
}  /* printDebug() */
