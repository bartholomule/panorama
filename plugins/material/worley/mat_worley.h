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

#ifndef _MAT_WORLEY__
#define _MAT_WORLEY__

#include "llapi/worley_basis.h"
#include "llapi/material.h"
#include "hlapi/plugin_manager.h"

class TMaterialWorley : public TMaterial
{

  protected:

    TColor         tBaseColor;
    TVector        tZoom;
    TScalar        tBumpFactor;
    TWorleyBasis   tWorleyBasis;

  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TMaterialWorley (void) :
      TMaterial(),
      tZoom (1, 1, 1),
      tBumpFactor (0),
      tWorleyBasis (1) {}
      
    TColor color (const TSurfaceData& rktDATA) const;
    TVector perturbNormal (const TSurfaceData& rktDATA) const;

    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    virtual void setBaseColor (const TColor& rktCOLOR)
    {
      tBaseColor = rktCOLOR;
    }

    string className (void) const { return "MaterialWorley"; }

};  /* class TMaterialWorley */


inline TColor TMaterialWorley::color (const TSurfaceData& rktDATA) const
{

  TVector                                     tPoint   = rktDATA.localPoint() * tZoom;
  TPriorityQueue<TWorleyBasis::TPointData>*   ptPQueue = tWorleyBasis.evaluate (tPoint);
  TScalar                                     tValue   = (*ptPQueue)[0].tData.tDistance;

  delete ptPQueue;
  
  return lerp (tBaseColor, tColor, tValue);
  
}  /* color() */


inline TVector TMaterialWorley::perturbNormal (const TSurfaceData& rktDATA) const
{

  TVector                                     tPoint;
  TVector                                     tVector;
  TPriorityQueue<TWorleyBasis::TPointData>*   ptPQueue;
  TVector                                     tNewNormal = rktDATA.normal();

  if ( tBumpFactor )
  {
    tPoint   = rktDATA.localPoint() * tZoom;
    ptPQueue = tWorleyBasis.evaluate (tPoint);

    tVector = (*ptPQueue)[0].tData.tVector;
    
    tNewNormal = rktDATA.normal() + tVector * tBumpFactor;
    tNewNormal.normalize();
  
    delete ptPQueue;
  }
  
  return tNewNormal;
  
}  /* perturbNormal() */

#endif  /* _MAT_WORLEY__ */
