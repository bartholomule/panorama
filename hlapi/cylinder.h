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

#ifndef _CYLINDER__
#define _CYLINDER__

#include "llapi/object.h"

class TCylinder : public TObject
{

  protected:

    TVector   tTopPoint;
    TVector   tBottomPoint;
    TScalar   tRadius;
    TScalar   tRadius2;
    TScalar   tHeight;
    bool      gOpen;
    
    TVector localNormal (const TVector& rktPOINT) const;

  public:

    TCylinder (void) :
      TObject()
    {
      sCapabilities.gInfinite = false;
      
      tTopPoint    = TVector ( 0, 1, 0);
      tBottomPoint = TVector ( 0,-1, 0);
      tRadius      = 1.0;
      gOpen        = false;
    }
      
    bool initialize (void);
    
    bool findAllIntersections (const TRay& rktRAY, TSpanList& rtLIST) const;

    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);

    /**
    * Get the value of a named attribute of the object.
    * @param rktNAME The name of the attribute; valid names are
    * 'point1', 'point2', 'open' and 'radius'.
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
    string className (void) const { return "Cylinder"; }

};  /* class TCylinder */

#endif  /* _CYLINDER__ */
