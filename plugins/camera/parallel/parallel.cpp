/*
*  Copyright (C) 2000 Fausto Espinal
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
#include "parallel.h"

DEFINE_PLUGIN ("ParallelCamera", FX_CAMERA_CLASS, TParallelCamera);

int TParallelCamera::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "width" )
  {
    if ( eTYPE == FX_REAL )
    {
      setWidth (nVALUE.dValue);
    }
    else
    {
      return FX_ATTRIB_WRONG_TYPE;
    }
  }
  else if ( rktNAME == "height" )
  {
    if ( eTYPE == FX_REAL )
    {
      setHeight (nVALUE.dValue);
    }
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


int TParallelCamera::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "width" )
  {
    rnVALUE.dValue = tWidth;
  }
  else if ( rktNAME == "height" )
  {
    rnVALUE.dValue = tHeight;
  }
  else
  {
    return TCamera::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TParallelCamera::getAttributeList (TAttributeList& rtLIST) const
{

  TCamera::getAttributeList (rtLIST);

  rtLIST ["width"]  = FX_REAL;
  rtLIST ["height"] = FX_REAL;

}  /* getAttributeList() */


bool TParallelCamera::initialize (void)
{
  bool val = true;

  tDirection = (tLookAt - tLocation);
  tDirection.normalize();

  if ( fabs (dotProduct (tDirection, tUp)) == 1 )
  {
    cout << "Error: Camera direction and up vectors cannot be parallel" << endl;
    val = false;
  }
  
  I = crossProduct (tDirection, tUp);
  J = crossProduct (I, tDirection);
  I.normalize();
  J.normalize();

  // Calculate pixel dimensions from given view window width and height.
  tPixelSizeX=tWidth/tHalfResX;
  tPixelSizeY=tHeight/tHalfResY;

  I *= tPixelSizeX;
  J *= tPixelSizeY;

  return val && TCamera::initialize();
  
}  /* initialize() */


bool TParallelCamera::getPlaneProjection (const TVector& rktPOINT, TVector2& rtPROJ) const
{

  TScalar   u, v;
  TScalar   pt, pu, pv;
  TVector   tPoint = (rktPOINT - tLocation);
  
  pt = dotProduct (tDirection, tPoint);
  pu = dotProduct (I, tPoint) / tPixelSizeX;
  pv = dotProduct (J, tPoint) / tPixelSizeY;

  u = tHalfResX + ((pu / pt) / tPixelSizeX);
  if ( ( u < 0 ) || ( u > (tHalfResX * 2) ) )
  {
    return false;
  }
  v = tHalfResY - ((pv / pt) / tPixelSizeY);
  if ( ( v < 0 ) || ( v > (tHalfResY * 2) ) )
  {
    return false;
  }

  rtPROJ.set (u, v);
  
  return true;
  
}  /* getPlaneProjection() */


void TParallelCamera::printDebug (void) const
{

  cerr << TDebug::_indent() << "[_" << className() << "_]" << endl;

  TDebug::_push();

  cerr << TDebug::_indent() << "Width     : " << getWidth() << endl;
  cerr << TDebug::_indent() << "Height    : " << getHeight() << endl;
  cerr << TDebug::_indent() << "Up vector : "; tUp.printDebug();
  cerr << TDebug::_indent() << "Look at   : "; tLookAt.printDebug();

  TDebug::_pop();
  
}  /* printDebug() */
