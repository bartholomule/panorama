/*
*  Copyright (C) 2001 Kevin Harris, Angel Jimenez Jimenez,
*  and Carlos Jimenez Moreno
*
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

#ifndef _THINLENS__
#define _THINLENS__

#include "llapi/camera.h"
#include "hlapi/plugin_manager.h"
#include "../pinhole/pinhole.h"

// Notes:  My measurements in here for the defaults are assumed to be in
// meters.  Someone using this class (in a scene or whatever) can set the
// values at whatever they want and make any kind of assumptions about their
// measurement system.
class TThinlensCamera : public TPinholeCamera
{
protected:
  TScalar aperture;        // The aperture of the lens
  TScalar focal_distance;  // The distance to the object in focus
  TScalar focal_length;    // The focal length of the lens
  TScalar disc_radius;     // The radius of the disc to be sampled (calculated
                           // from the aperture and the focal length)
  TScalar film_width;      // The width and height of the film for the camera
  TScalar film_height;     // (determines the field of view for the camera) --
                           // Camera specific (36mm x 24mm for 35mm cameras). 
public:

  static TBaseClass* _create (const TBaseClass* pktPARENT);
  
  TThinlensCamera (void) :
    TPinholeCamera(),
    focal_distance(2),      // Default focal distance of about 6 feet (PAS).
    film_width(36e-3),
    film_height(24e-3)
  {
    setAperture(11);        // Default aperture of a typical 35mm camera (PAS).
    setFocalLength(52.2e-3);// This will give the 45 degree view that the
                            // default camera has (equiv to a 52.2mm lens).
                            // NOTE: a 35mm PAS (point and shoot) camera
                            // typically has a 55mm lens. 
    adjAngle();             // Set the angle in the base class.
  }
  
  void initialize (void);
  
  int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
  int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
  void getAttributeList (TAttributeList& rtLIST) const;
  
  void getRay (TScalar X, TScalar Y, TRay& rtRAY) const;


  TScalar getAperture (void) const      { return aperture; }
  TScalar getFocalDistance (void) const { return focal_distance; }
  TScalar getFocalLength (void) const   { return focal_length; }
  TScalar getFilmWidth (void) const     { return film_width;  }
  TScalar getFilmHeight (void) const    { return film_height; }      
  
  void setAperture (TScalar ap)
  {
    aperture = ap;
    disc_radius = (focal_length / aperture)/2;
  }
  void setFocalDistance (TScalar dist) { focal_distance = dist; }
  void setFocalLength (TScalar dist)    
  {
    focal_length = dist;
    disc_radius = (focal_length / aperture)/2;
  }
  void setFilmWidth(TScalar width)   { film_width = width;   }
  void setFilmHeight(TScalar height) { film_height = height; }  

  void adjAngle()
  {
    TScalar dist_to_film_corner = sqrt(film_height * film_height +
				       film_width  * film_width) / 2;
    TScalar angle_in_degrees = 2 * atan(dist_to_film_corner /
					focal_length)*180./PI;
    setAngle(angle_in_degrees);
  }
  
  string className (void) const { return "ThinlensCamera"; }
  
  void printDebug (void) const;
  
};  /* class TThinlensCamera */

/*
  Things I will need to accurately model a camera (nothing that the thin-lens
  approach will have artifacts for objects that are in the FOV and inbetween
  the film back-plane and the lens plane)...

  Here's a pretty bad ascii picture of a camera, with some labels on it.
                             +------+
                             |      |
                             |   ./||
                     +-------+  /I'|| v
		    (|)    fp   |  || h'
  ..................(|)....*...... |. ^
 v                  (|)         |  ||
 h                   +-------+  \. ||
 ^  I                        |    \||
    ------> D <-------       |      |
    ------> p <-------       +------+
		     -->F<--
		           --->B<---
		     ------>q<------

  The thin-lens equation says: 1/p + 1/q = 1/F
  Thus: 1/D + 1/(F+B) = 1/F
  And for magnification: M = h'/h = -q/p = -(F+B)/D

  * Aperture -- Used to find lens diameter: (A) = Focal length / Lens Diameter
  * Focal length (F)
  * Film width (fw) -- 36mm for 35mm film
  * Film height (fh) -- 24mm for 35mm film
  * Back plane distance (B) -- distance from the focal point to the backplane.
  Note that this value has a minimum that should be set for each unique camera
  type.  For a simple approximation, we should be able to say that B=0.  This
  provides results that are consistant with the angle numbers in "Photography"
  by Bruce Warren. 
  * Distance to object in focus (from backplane) == viewer -- This is used to 
  solve for an effective black plane distance.
  
  Now... The angle of maximum viewing (to reach the farthest spot on the edge
  of the film) should be able to be calculated as such (assuming b=0):
		   
                    sqrt(fh*fh + fw*fw)
  theta = 2 * atan( ------------------ )
                           2 * F

  Where theta is twice the angle from the center-line to the limit of viewing
  for the particular film size (total viewing angle).  


  Some defaults to place in a define:
  35mm: fw=36e-3, fh=24e-3
  med_format: fw=??, fh=??
  point-and-shoot: 35mm film, F=55mm, A=11
*/

#endif  /* _THINLENS__ */
