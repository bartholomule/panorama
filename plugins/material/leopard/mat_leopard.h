/*
*  Copyright (C) 1998 Angel Jimenez Jimenez and Carlos Jimenez Moreno
*  Copyright (C) 1998 Peter Barnett
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

#ifndef _MAT_LEOPARD__
#define _MAT_LEOPARD__

#include "llapi/material.h"
#include "hlapi/plugin_manager.h"

class TMaterialLeopard : public TMaterial
{

  protected:

    TColor    tBaseColor;
    TVector   tZoom;
    TScalar   tBumpFactor;

    TScalar evaluate (const TVector& rktPOINT, TVector* ptGRADIENT = NULL) const;

  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TMaterialLeopard (void) :
      TMaterial(),
      tZoom (1, 1, 1),
      tBumpFactor (0) {}
      
    TColor color (const TSurfaceData& rktDATA) const
    {
      TVector   tPoint      = rktDATA.localPoint() * tZoom;
      TScalar   tNoiseValue = evaluate (tPoint);

      return lerp (tBaseColor, tColor, tNoiseValue);
    }
    
    TVector perturbNormal (const TSurfaceData& rktDATA) const;

    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    virtual void setBaseColor (const TColor& rktCOLOR)
    {
      tBaseColor = rktCOLOR;
    }

    string className (void) const { return "MaterialLeopard"; }

};  /* class TMaterialLeopard */


inline TScalar TMaterialLeopard::evaluate (const TVector& rktPOINT, TVector* ptGRADIENT) const
{

  TScalar   tTmp   = sin (rktPOINT.x()) + sin (rktPOINT.y()) + sin (rktPOINT.z());
  TScalar   tValue = tTmp / 3;

  tValue *= tValue;
  
  if ( ptGRADIENT )
  {
    tTmp *= - (2.0 / 9.0);

    ptGRADIENT->set (tTmp * cos (rktPOINT.x()),
                     tTmp * cos (rktPOINT.y()),
                     tTmp * cos (rktPOINT.z()));
    
    ptGRADIENT->normalize();
  }
  
  return tValue;

}  /* evaluate() */


inline TVector TMaterialLeopard::perturbNormal (const TSurfaceData& rktDATA) const
{

  TVector   tNewNormal = rktDATA.normal();

  if ( tBumpFactor )
  {
    TVector   tGradient;
    TVector   tPoint = rktDATA.localPoint() * tZoom;

    evaluate (tPoint, &tGradient);

    tNewNormal = rktDATA.normal() + tGradient * tBumpFactor;
    tNewNormal.normalize();
  }
  
  return tNewNormal;
  
}  /* perturbNormal() */

#endif  /* _MAT_LEOPARD__ */
