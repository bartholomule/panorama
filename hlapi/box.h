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

#ifndef _BOX__
#define _BOX__

#include "llapi/object.h"

/**
* A rectilinear box object specified by two diagonally opposite points.
* The box is aligned with the x, y, and z axes.
*/

class TBox : public TObject
{
  public:

    /**
    * Default constructor; defines a unit cube centred at the origin.
    */
    
    TBox (void) : TObject()
    {
      tXmin = -0.5;
      tYmin = -0.5;
      tZmin = -0.5;
      tXmax =  0.5;
      tYmax =  0.5;
      tZmax =  0.5;
      tP1   =  TVector (-0.5,-0.5,-0.5);
      tP2   =  TVector ( 0.5, 0.5, 0.5);
       
      sCapabilities.gInfinite = false;
    }

    /**
    * Sets the bounding box and transformation matrix
    */
    void initialize (void);
    
    /**
    * Returns the first intersection of a given ray with the object.
    * @param rktRAY the ray to be tested for intersection
    * @param rtDATA surface data for point of intersection
    * @return boolean value; true if the ray intersects the object
    * @see findAllIntersections()
    */
    bool findFirstIntersection (const TRay& rktRAY, TSurfaceData& rtDATA) const;
    
    /**
    * Returns a list of intersections of a given ray with the object.
    * @param rktRAY the ray to be tested for intersection
    * @param rtLIST surface data list for the points of intersection
    * @return boolean value; true if the ray intersects the object
    * @see findFirstIntersection()
    */
    bool findAllIntersections (const TRay& rktRAY, TSpanList& rtLIST) const;

    /**
    * Returns the object defined as a list of triangles.
    * @return rtMESH_LIST the list of triangles
    */
    void getMesh (list<TMesh*>& rtMESH_LIST) const;
    
    /**
    * Get the name of the object class as a string.
    * @return the name of the class
    */
    string className (void) const { return "Box"; }

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
    * 'point1' and 'point2'.
    * @param rnVALUE The returned value; for 'point1' and 'point2'
    * this will be a TVector.
    * @see getAttributeList()
    */
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);

    /**
    * Get a list of the object's attribute names and types.
    * @see getAttribute()
    */
    void getAttributeList (TAttributeList& rtLIST) const;

  protected:

    /**
    * A point defining one corner of the box.
    */
    TVector tP1;

    /**
    * A point defining the opposite corner of the box.
    */
    TVector tP2;
    
    /**
    * x-coordinate of the left face of the box.
    */
    TScalar tXmin;

    /**
    * y-coordinate of the bottom face of the box.
    */
    TScalar tYmin;

    /**
    * z-coordinate of the back face of the box.
    */
    TScalar tZmin;

    /**
    * x-coordinate of the right face of the box.
    */
    TScalar tXmax;

    /**
    * y-coordinate of the top face of the box.
    */
    TScalar tYmax;

    /**
    * z-coordinate of the front face of the box.
    */
    TScalar tZmax;

    /**
    * Get the local surface normal
    * @param rktPOINT A point on the box's surface
    * @return The local unit-vector normal
    */
    TVector localNormal (const TVector& rktPOINT) const;
            
};  /* class TBox */

#endif  /* _BOX__ */
