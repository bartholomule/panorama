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

#ifndef _PERTURBATION_LEOPARD__
#define _PERTURBATION_LEOPARD__

#include "llapi/perturbation.h"
#include "hlapi/plugin_manager.h"
#include "../../pattern/leopard/pat_leopard.h"


class TPerturbationLeopard : public TPerturbation
{

  protected:

    TScalar            tBumpFactor;
    TPatternLeopard*   ptLeopardPattern;

  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TPerturbationLeopard (void) :
      TPerturbation(),
      tBumpFactor (0),
      ptLeopardPattern (NULL) {}
      
    TVector perturbNormal (const TSurfaceData& rktDATA) const;

    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    void setLeopardPattern (TPatternLeopard* ptPATTERN) { ptLeopardPattern = ptPATTERN; }

    string className (void) const { return "PerturbationLeopard"; }

};  /* class TPerturbationLeopard */


inline TVector TPerturbationLeopard::perturbNormal (const TSurfaceData& rktDATA) const
{

  TVector   tNewNormal = rktDATA.unperturbedNormal();

  if ( tBumpFactor )
  {
    TVector   tGradient;
    TVector   tPoint;

    if ( !ptLeopardPattern )
    {
      cout << ("Error: leopard_pattern must be set") << endl;
      exit (1);
    }

    tPoint = ptLeopardPattern->warp (rktDATA.localPoint()) * ptLeopardPattern->tZoom;

    ptLeopardPattern->evaluate (tPoint, &tGradient);

    tNewNormal += tGradient * tBumpFactor;
    tNewNormal.normalize();
  }
  
  return tNewNormal;
  
}  /* perturbNormal() */

#endif  /* _PERTURBATION_LEOPARD__ */
