/*
*  Copyright (C) 1998, 1999 Angel Jimenez Jimenez, Carlos Jimenez Moreno and Peter Barnett
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
*
*/

#ifndef _PERTURBATION_CRACKLE__
#define _PERTURBATION_CRACKLE__

#include "llapi/perturbation.h"
#include "llapi/gradient.h"
#include "hlapi/plugin_manager.h"
#include "../../pattern/crackle/pat_crackle.h"


class TPerturbationCrackle : public TPerturbation
{

  protected:

    TScalar            tBumpFactor;
    TPatternCrackle*   ptCracklePattern;

  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TPerturbationCrackle (void) :
      TPerturbation(),
      tBumpFactor (0),
      ptCracklePattern (NULL) {}

    TVector perturbNormal (const TSurfaceData& rktDATA) const;

    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    void setCracklePattern (TPatternCrackle* ptPATTERN) { ptCracklePattern = ptPATTERN; }

    string className (void) const { return "PerturbationCrackle"; }

};  /* class TPerturbationCrackle */


inline TVector TPerturbationCrackle::perturbNormal (const TSurfaceData& rktDATA) const
{

  TVector   tNewNormal = rktDATA.normal();

  if ( fabs(tBumpFactor) > FX_EPSILON )
  {
    TVector   tGradient;
    TVector   tPoint;

    if ( !ptCracklePattern )
    {
      cout << ("Error: crackle_pattern must be set") << endl;
      exit (1);
    }

    tPoint = ptCracklePattern->warp (rktDATA.localPoint()) * ptCracklePattern->tZoom;

    ptCracklePattern->evaluate (tPoint, &tGradient);

    tNewNormal = rktDATA.normal() + tGradient * tBumpFactor;
    tNewNormal.normalize();
  }
  
  return tNewNormal;
  
}  /* perturbNormal() */

#endif  /* _PERTURBATION_CRACKLE__ */
