/*
*  Copyright (C) 2001 Kevin Harris, Angel Jimenez Jimenez,
*  and Carlos Jimenez Moreno
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

#include "thinlens.h"

DEFINE_PLUGIN ("ThinlensCamera", FX_CAMERA_CLASS, TThinlensCamera);

#define MUST_BE_TYPE(type, required_type) \
if(type != required_type)                 \
{                                         \
  return FX_ATTRIB_WRONG_TYPE;            \
}

int TThinlensCamera::setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{

  if ( rktNAME == "aperture" )
  {
    MUST_BE_TYPE(eTYPE, FX_REAL);
    setAperture (nVALUE.dValue);
  }
  else if ( rktNAME == "focal_distance" )
  {
    MUST_BE_TYPE(eTYPE, FX_REAL);    
    setFocalDistance (nVALUE.dValue);
  }
  else if ( rktNAME == "focal_length" )
  {
    MUST_BE_TYPE(eTYPE, FX_REAL);    
    setFocalLength (nVALUE.dValue);
    adjAngle();    
  }
  else if ( rktNAME == "film_width" )
  {
    MUST_BE_TYPE(eTYPE, FX_REAL);    
    setFilmWidth (nVALUE.dValue);
    adjAngle();
  }
  else if ( rktNAME == "film_height" )
  {
    MUST_BE_TYPE(eTYPE, FX_REAL);
    setFilmHeight (nVALUE.dValue);
    adjAngle();
  }  
  else
  {
    return TPinholeCamera::setAttribute (rktNAME, nVALUE, eTYPE);
  }

  return FX_ATTRIB_OK;

}  /* setAttribute() */


int TThinlensCamera::getAttribute (const string& rktNAME, NAttribute& rnVALUE)
{

  if ( rktNAME == "aperture" )
  {
    rnVALUE.dValue = getAperture();
  }
  else if ( rktNAME == "focal_distance" )
  {
    rnVALUE.dValue = getFocalDistance();
  }
  else if ( rktNAME == "focal_length" )
  {
    rnVALUE.dValue = getFocalLength();
  }
  else if ( rktNAME == "film_width" )
  {
    rnVALUE.dValue = getFilmWidth();
  }
  else if ( rktNAME == "film_height" )
  {
    rnVALUE.dValue = getFilmHeight();
  }        
  else
  {
    return TCamera::getAttribute (rktNAME, rnVALUE);
  }

  return FX_ATTRIB_OK;

}  /* getAttribute() */


void TThinlensCamera::getAttributeList (TAttributeList& rtLIST) const
{

  TCamera::getAttributeList (rtLIST);

  rtLIST ["aperture"] = FX_REAL;
  rtLIST ["focal_distance"] = FX_REAL;
  rtLIST ["focal_length"] = FX_REAL;        
  rtLIST ["film_width"] = FX_REAL;
  rtLIST ["film_height"] = FX_REAL;
}  /* getAttributeList() */


void TThinlensCamera::initialize (void)
{
  TPinholeCamera::initialize ();
}  /* initialize() */


/*
  Here's a set of comments that I (KH) wrote 2 years ago (Feb 1999), when I was
  writing a thin-lens camera.  I know that it isn't the fastest method
  possible, but it is fairly simple.
  ---------------------------------------------------------------------------
  The plan for how to generate rays to simulate a thin-lens system:
  1. Find the ray as with the pinhole camera (unit vector), call this b.
  2. Generate a vector of the correct length by scaling b by d/(a dot b), where
     a is the unit vector look_at.
  3. Find the point in space where the vector would hit at that distance (the
     point of focus) by adding the scaled vector to the eye location.
  4. generate the random point on the disc in 3space (using the
     disc_ray_source).
  5. generate the ray using the random point as the origin, and the unit vector
     in the direction to the focal point calculated in #3.
     
---------------------------------------------------------------------------
  For future reference, it may be helpful to know where the scalar in step 2
  above came from.
  What I wanted to do was make the projection of the vector b onto the look_at
  vector be of length d.
  I figured projection (length) to be:
  (a dot b) == mag(a)*mag(b)*cos(theta)
  projection of b on a = (a dot b)/mag(a) == mag(b)*cos(theta)
  Since I want to figure out what cos(theta) is, I need both a and b to be unit
  vectors, I can then just use (a_unit dot b_unit) as the cos(theta) term.

  d = mag(b)*cos(theta) == mag(b)*(a_unit dot b_unit)

  since I want to solve for the desired mag(b) (I need to set the length of b).

  mag(b) = d/cos(theta) = d/(a_unit dot b_unit)

  thus, the resulting vector is b_unit*d/(a_unit dot b_unit)
---------------------------------------------------------------------------
  If I didn't do this scaling, It would end up with a half-sphere of radius d
  in focus, and not the desired focal plane.
 */

void TThinlensCamera::getRay (TScalar X, TScalar Y, TRay& rtRAY) const
{
  TPinholeCamera::getRay(X,Y,rtRAY);

  // Find a random point on the disc (more comments from Feb1999):
  // --------------------------------------------------------------
  // To pick a random point on a disk, given the two random numbers
  // r1 and r2:
  // warped_theta = 2*pi*r1
  // warped_r = radius*sqrt(r2)
  //
  // I then do the normal transformation from polar to rectangle:
  //  x = r*cos(theta);
  //  y = r*sin(theta);
  //  z = 0
  // Where the r and theta used are the warped versions.
  const TScalar r1 = frand(), r2 = frand();
  const TScalar theta = 2 * PI * r1;
  const TScalar r = disc_radius * sqrt(r2);
  const TScalar x = r * cos(theta);
  const TScalar y = r * sin(theta);
  const TVector new_origin = I * x + J * y + tLocation;

  // Scale the ray to find the point which i
  const TVector scaled_b(rtRAY.direction() *
			 (focal_distance /
			  dotProduct(tDirection, rtRAY.direction())));
  const TVector point_in_3space = scaled_b + tLocation;
  
  rtRAY.setLocation (new_origin);
  rtRAY.setDirection (point_in_3space - new_origin);
  rtRAY.normalize();
}

void TThinlensCamera::printDebug (void) const
{

  cerr << TDebug::_indent() << "[_" << className() << "_]" << endl;

  TDebug::_push();

  TPinholeCamera::printDebug();
  cerr << TDebug::_indent() << "Aperture     : " << getAperture() << endl;
  cerr << TDebug::_indent() << "Focal Dist   : " << getFocalDistance() << endl;
  cerr << TDebug::_indent() << "Focal Length : " << getFocalLength() << endl;
  cerr << TDebug::_indent() << "Film Width   : " << getFilmWidth() << endl;
  cerr << TDebug::_indent() << "Film Height  : " << getFilmHeight() << endl;

  TDebug::_pop();
  
}  /* printDebug() */
