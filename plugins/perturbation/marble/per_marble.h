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
*/

#ifndef _PERTURBATION_MARBLE__
#define _PERTURBATION_MARBLE__

#include "llapi/perlin_noise.h"
#include "llapi/perturbation.h"
#include "llapi/gradient.h"
#include "hlapi/plugin_manager.h"
#include "../../pattern/marble/pat_marble.h"


class TPerturbationMarble : public TPerturbation
{

  protected:

    TScalar           tBumpFactor;
    magic_pointer<TPatternMarble> ptMarblePattern;

  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TPerturbationMarble (void) :
      TPerturbation(),
      tBumpFactor (0),
      ptMarblePattern (NULL) {}
      
    TVector perturbNormal (const TSurfaceData& rktDATA) const;

    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    void setMarblePattern (magic_pointer<TPatternMarble> ptPATTERN) { ptMarblePattern = ptPATTERN; }

    string className (void) const { return "PerturbationMarble"; }
    TPerturbationMarble* clone_new() const { return new TPerturbationMarble(*this); }
};  /* class TPerturbationMarble */


inline TVector TPerturbationMarble::perturbNormal (const TSurfaceData& rktDATA) const
{

  TVector   tNewNormal = rktDATA.unperturbedNormal();

  if ( tBumpFactor )
  {
    TVector   tGradient;
    TVector   tPoint;

    if ( !ptMarblePattern )
    {
      cout << ("Error: marble_pattern must be set") << endl;
      exit (1);
    }

    tPoint = ptMarblePattern->warp (rktDATA.localPoint()) * ptMarblePattern->tZoom;

    ptMarblePattern->evaluate (tPoint, &tGradient);

    tNewNormal += tGradient * tBumpFactor;
    tNewNormal.normalize();
  }
  
  return tNewNormal;
  
}  /* perturbNormal() */

#endif  /* _PERTURBATION_MARBLE__ */
