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

#ifndef _SPHERE__
#define _SPHERE__

#include "llapi/object.h"

class TSphere : public TObject
{

  protected:

    TScalar   tRadius;
    TScalar   tRadius2;

    TVector localNormal (const TVector& rktPOINT) const
    {
      return (rktPOINT) / tRadius;
    }

  public:

    TSphere (void) :
      TObject()
    {
      tRadius  = 1;
      tRadius2 = 1;
      sCapabilities.gInfinite = false;
    }
      
    void initialize (void);

    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;
    
    void setRadius (TScalar tRADIUS);

    bool findFirstIntersection (const TRay& rktRAY, TSurfaceData& rtDATA) const;
    bool findAllIntersections (const TRay& rktRAY, TSpanList& rtLIST) const;


    TVector RandomPointOnSurface() const;
  
    void printDebug (void) const;
    string className (void) const { return "Sphere"; }

};  /* class TSphere */

#endif  /* _SPHERE__ */
