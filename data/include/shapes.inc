/*
*  Shape Definitions -- To be used in the simplification of scene files
*
*  Copyright (C) 2001, 2002 Kevin Harris
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

define aggregate class Aggregate { };
define box       class Box       { };
define circle    class Circle    { };
define cone      class Cone      { };
define cylinder  class Cylinder  { };
define plane     class Plane     { };
define rectangle class Rectangle { };
define sphere    class Sphere    { };
define triangle  class Triangle  { };
define torus     class Torus     { };
define Light     class PointLight { };
//define camera    class PinholeCamera { };
define phong_triangle class PhongTriangle { };

// A definition of 'scene' that includes a default material.
define scene     class Scene     
{ 
  defaultmaterial = class Material
  {
    bsdf = class BsdfLambertian { };
    ambient = 0.2;
    diffuse = 0.6;  
    color = <1,1,1>;
  };
};

