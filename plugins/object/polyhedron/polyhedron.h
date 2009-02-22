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

#ifndef _POLYHEDRON__
#define _POLYHEDRON__

#include "llapi/object.h"
#include "hlapi/plugin_manager.h"

struct TPlaneData
{

  TVector   tNormal;
  TScalar   D;

  TPlaneData (TScalar A, TScalar B, TScalar C, TScalar DD) :
    tNormal (A, B, C),
    D (DD) {}

};  /* struct TPlaneData */

enum EShape
{

  FX_TETRAHEDRON = 0,
  FX_CUBE,
  FX_OCTAHEDRON,
  FX_ICOSAHEDRON,
  FX_DODECAHEDRON

};  /* enum EShape */

class TPolyhedron : public TObject
{

  protected:

    static bool               _gClassInitialized;
    static std::list<TPlaneData>   _atPlaneDataList[5];

    EShape   eShape;
    
  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    static void _initializeClass (void);

    TPolyhedron (void) :
      TObject(),
      eShape (FX_CUBE) {}
    
    bool initialize (void);
    
    int setAttribute (const std::string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const std::string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;
    
    bool findAllIntersections (const TRay& rktRAY, TSpanList& rtLIST) const;

    std::string className (void) const { return "Polyhedron"; }

};  /* class TPolyhedron */

#endif  /* _POLYHEDRON__ */
