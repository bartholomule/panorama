/*
*  Material definitions
*
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

#include "colors.inc"

define material MLambertian
{
  bsdf : class BsdfLambertian
  {
  }
  ambient	0.2
  diffuse	0.6
}

define material MPlastic
{
  bsdf : class BsdfPhong
  {
    exponent    50
  }
  ambient	0.2
  diffuse	0.6
  specular	0.2
}

define material MCrystal
{
  bsdf : class BsdfPhong
  {
    exponent	500
  }
  ambient	0
  diffuse	0
  specular	0.2
  opacity	0.01
  ior		1.52
  caustics	20
}

define material MDiamond : extends MCrystal
{
  ior		2.47
  caustics	30
}

define material MMirror
{
  bsdf : class BsdfPhong
  {
    exponent	500
  }
  color		CWhite
  ambient	0
  diffuse	0
  specular      1
}

define material MChecker : class MaterialChecker
{
  bsdf : class BsdfPhong
  {
    exponent    50
  }
  ambient	0.2
  diffuse	0.6
  specular	0.2
}

define material MNoise : class MaterialNoise
{
  bsdf : class BsdfPhong
  {
    exponent    50
  }
  ambient	0.2
  diffuse	0.6
  specular	0.2
}

define material MWorley : class MaterialWorley
{
  bsdf : class BsdfPhong
  {
    exponent    50
  }
  ambient	0.2
  diffuse	0.6
  specular	0.2
}
