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

#ifndef _TORUS__
#define _TORUS__

#include "llapi/object.h"

class TTorus : public TObject
{

  protected:

    TScalar   tRadiusA;
    TScalar   tRadiusA2, tRadiusB2;
  
    TVector localNormal (const TVector& rktPOINT) const;

  public:

    TTorus (void) :
      TObject()
    {
      tRadiusA  = 1;
      tRadiusA2 = tRadiusA * tRadiusA;
      tRadiusB2 = 0.25;

      sCapabilities.gInfinite = false;
    }
      
    bool initialize (void);
    
    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;
    
    bool findAllIntersections (const TRay& rktRAY, TSpanList& rtLIST) const;

    TVector RandomPointOnSurface() const;
  
    string className (void) const { return "Torus"; }

};  /* class TTorus */

#endif  /* _TORUS__ */
