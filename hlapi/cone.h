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

#ifndef _CONE__
#define _CONE__

#include "llapi/transform_object.h"

class TCone : public TObject
{

  protected:

    TVector   tMaxCirclePoint;      // set by user
    TVector   tMinCirclePoint;      // set by user
    TScalar   tMaxRadius;           // set by user
    TScalar   tMinRadius;           // set by user
    TScalar   tHeightToMinCircle;
    TScalar   tHeight;

    TScalar   tMaxRadiusByHeight2;
    TScalar   tMaxRadius2;
    TScalar   tMinRadius2;
    
    TVector localNormal (const TVector& rktPOINT) const;
    bool intersectionsWithCanonicalCone (const TRay& rktRAY, TSpanList& rtLIST) const;
    bool intersectionsWithRootCone (const TRay& rktRAY, TSpanList& rtLIST) const;
      
  public:

    TCone (void) :
      TObject()
    {
      sCapabilities.gInfinite = false;
      tMinRadius              = 0;
      tHeightToMinCircle      = 0;
    }
      
    void initialize (void);
    
    bool findAllIntersections (const TRay& rktRAY, TSpanList& rtLIST) const;

    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    string className (void) const { return "Cone"; }

};  /* class TCone */

#endif  /* _CONE__ */
