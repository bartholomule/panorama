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

#ifndef _TRIANGLE__
#define _TRIANGLE__

#include "hlapi/plane.h"

class TTriangle : public TPlane
{

  protected:

    Byte       bDom;
    Byte       bVertex;
    TVector    atVertex [3];
    TVector2   atCoord  [3];

    void update (void);

  public:

    TTriangle (void) :
      TPlane(),
      bVertex (0)
    {
      sCapabilities.gInfinite = false;
    }

    void initialize (void);

    void translate (const TVector& rktNEW_POS);

    virtual void setVertex (const TVector& rktVERTEX);

    TVector vertex (Byte bVERTEX) const
    {
      assert ( bVERTEX < 3 );
      
      return atVertex [bVERTEX];
    }

    bool inside (const TVector& rktPOINT) const;

    void getMesh (list<TMesh*>& rtMESH_LIST) const;
    
    void printDebug (void) const;
    string className (void) const { return "Triangle"; }
    
};  /* class TTriangle */

#endif  /* _TRIANGLE__ */
