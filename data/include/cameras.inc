/*
*  Camera Definitions -- To be used for defining commonly used camera types.
*
*  Copyright (C) 2001 Kevin Harris
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

// A default point-and-shoot 35mm camera.  This uses default numbers for
// aperture, focal length, and film size as given by "Photography" by Bruce
// Warren. 
// If the image needs to be almost identical to that of the pinhole camera,
// when extending an image from this, reset the focal (in the usage, not in
// here) length to 52.2mm (0.0522) 
define pas_35mm class ThinlensCamera
{
  focal_distance = 2;      // (2 meters) about 6 Feet -- Almost standard
  focal_length   = 0.055;  // 55mm lens
  aperture       = 11;     // F11
  film_width     = 0.036;  // 35mm film has dimensions of 36mm x 24mm
  film_height    = 0.024;  
};

define standard class PinholeCamera
{
  angle = 45;  // This is given by default, if not provided (~= 52.2mm lens for
               // 35mm cameras). 
};

define Camera standard;


/*
// Example of use:
define c : extends pas_35mm
{
  translate(<location>);
  look_at=<location>;
};
*/

/*
  Notes about thin-lens cameras:
  1. Zooming may be done with the focal length (large = zoomed in).  A typical
  camera may have lenses with a range of 28-210mm.  Sports photographers
  typically use 500mm+ lenses (expensive to get aith a low aperture number [F-Stop]).
  
  2. The objects in focus are changed by means of the focal distance.
  
  3. The depth of field (range of objects in focus) is changed with the
  aperture (called F-Stop in photography).  It is noteable that the human eye
  is approx 1.0 for aperture.  If more blur is desired, use a small number for
  aperture (0<a<1), although it would be impossible for a real camera to reach
  those values.  Cameras usually range from 1.7 to 32 (much higher F-Stops are
  possible with expensive cameras).

  4. Focal blur only looks good when a fairly large number of samples is
  taken.  As such, the aa_depth value (for raytracers) should be set much
  higher than for images without focal blur.
*/
