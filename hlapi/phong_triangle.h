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

#ifndef _PHONG_TRIANGLE__
#define _PHONG_TRIANGLE__

#include "hlapi/triangle.h"

class TPhongTriangle : public TTriangle
{

  protected:

    Byte      bNormal;
    TVector   atNormal [3];
    TVector   tV2V1;
    TScalar   tV2V1norm;
    TScalar   tProyV2V0overV2V1;
    TScalar   tMinDisV0overV2V1;

    void update (void);
    
  public:

    TPhongTriangle (void) :
      TTriangle(),
      bNormal (0) {}

    void setNormal (const TVector& rktNORMAL);
    TVector normal (const TSurfaceData& rktDATA) const;

    void addVertex (const TVector& rktVERTEX, const TVector& rktNORMAL );

    void printDebug (const string& indent) const;
    string className (void) const { return "PhongTriangle"; }

    virtual TUserFunctionMap getUserFunctions();  
    
};  /* class TPhongTriangle */

#endif  /* _PHONG_TRIANGLE__ */
