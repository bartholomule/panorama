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

#ifndef _CONE__
#define _CONE__

#include "llapi/object.h"

/**
* Cone object.
* The cone is specified in terms of two coordinates and two scalars; 
* the centre of the cap, the centre of the base, and the two associated
* radii. If these parameters are not specified, the object defaults to a canonical cone.
*/
class TCone : public TObject
{

  protected:

/** 
* Coordinate of the centre of the base (set by the user).
*/
    TVector   tMaxCirclePoint;

/** 
* Coordinate of the centre of the cap (set by the user).
*/
    TVector   tMinCirclePoint;

/**
* Radius of the base (set by the user).
*/
    TScalar   tMaxRadius;

/**
* Radius of the cap (set by the user).
*/
    TScalar   tMinRadius;

/**
* Height from the cap to what would be the apex if the cone were not truncated;
* this is transformed to the origin before intersection tests are done.
*/
    TScalar   tHeightToMinCircle;

/**
* Height from the base to the cap.
*/
    TScalar   tHeight;

/**
* Max radius divided by the height squared :-) precalculated for use in intersection tests.
*/
    TScalar   tMaxRadiusByHeight2;

/**
* Precalculated maximum radius squared.
*/
    TScalar   tMaxRadius2;

/**
* Precalculated minimum radius squared.
*/
    TScalar   tMinRadius2;

/**
* localNormal Returns the normal at a point on the cone's surface.
* @param rktPOINT A point on the surface.
* @return The normal at that point.
*/
    TVector localNormal (const TVector& rktPOINT) const;

/**
* Intersection test with canonical cone, with apex at the origin and axis along the -ve y-axis.
* @param rktRay The ray to be tested for intersection.
* @param rtLIST The list of returned intersections.
* @return A boolean value indicating whether the ray intersected the cone.
*/
    bool intersectionsWithCanonicalCone (const TRay& rktRAY, TSpanList& rtLIST) const;

/**
* Intersection with parameterised cone.
* @param rktRay The ray to be tested for intersection.
* @param rtLIST The list of returned intersections (if any).
* @return A boolean value indicating whether the ray intersected the cone.
*/
    bool intersectionsWithRootCone (const TRay& rktRAY, TSpanList& rtLIST) const;
      
  public:

/**
* Cone constructor; builds a canonical cone.
*/
    TCone (void) :
      TObject()
    {
      sCapabilities.gInfinite = false;
      tMinRadius              = 0;
      tHeightToMinCircle      = 0;
    }

/**
* Initialize the cone object.
* This routine calculates the transform and inverse transform required to map between world
* and object space.
*/      
    void initialize (void);

/*
* Generic intersection test.
* The routine checks for a canonical cone, and calls the appropriate test.
* @param rktRAY The ray to be tested for intersection.
* @param rtLIST The list of returned intersections (if any).
* @see intersectionsWithCanonicalCone()
* @see intersectionsWithRootCone()
* @return  A boolean value indicating whether the ray intersected the cone.
*/    
    bool findAllIntersections (const TRay& rktRAY, TSpanList& rtLIST) const;

    /**
    * Set the value of a named attribute of the object.
    * @param rktNAME the name of the attribute to set.
    * @param nVALUE the value to be set.
    * @param eTYPE the type of the attribute.
    * @return FX_ATTRIB_OK if successful, or one of
    * FX_ATTRIB_WRONG_PARAM,
    * FX_ATTRIB_WRONG_TYPE,
    * FX_ATTRIB_WRONG_VALUE, or
    * FX_ATTRIB_USER_ERROR if there is an error.
    */
    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);

    /**
    * Get the value of a named attribute of the object.
    * @param rktNAME The name of the attribute; valid names are
    * 'max_circle_point', 'min_circle_point', 'max_radius', and 'min_radius'.
    * @param rnVALUE The returned value.
    * @see getAttributeList()
    */
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);

    /**
    * Get a list of the object's attribute names and types.
    * @see getAttribute()
    */
    void getAttributeList (TAttributeList& rtLIST) const;

    /**
    * Get the name of the object class as a string.
    * @return the name of the class
    */
    string className (void) const { return "Cone"; }

};  /* class TCone */

#endif  /* _CONE__ */
