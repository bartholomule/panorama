/*
*  Copyright (C) 1998 Angel Jimenez Jimenez and Carlos Jimenez Moreno
*  Copyright (C) 1999 Peter Barnett
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

#ifndef _PERTURBATION_NOISE__
#define _PERTURBATION_NOISE__

#include "llapi/perlin_noise.h"
#include "llapi/perturbation.h"
#include "llapi/gradient.h"
#include "hlapi/plugin_manager.h"
#include "../../pattern/noise/pat_noise.h"


class TPerturbationNoise : public TPerturbation
{

  protected:

    TScalar          tBumpFactor;
    TPatternNoise*   ptNoisePattern;

  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TPerturbationNoise (void) :
      TPerturbation(),
      tBumpFactor (0),
      ptNoisePattern (NULL) {}
      
    TVector perturbNormal (const TSurfaceData& rktDATA) const;

    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    void setNoisePattern (TPatternNoise* ptPATTERN) { ptNoisePattern = ptPATTERN; }

    string className (void) const { return "PerturbationNoise"; }

};  /* class TPerturbationNoise */


inline TVector TPerturbationNoise::perturbNormal (const TSurfaceData& rktDATA) const
{

  TVector   tNewNormal = rktDATA.normal();

  if ( tBumpFactor )
  {
    TVector   tGradient;
    TVector   tPoint;

    if ( !ptNoisePattern )
    {
      cout << ("Error: noise_pattern must be set") << endl;
      exit (1);
    }

    tPoint = ptNoisePattern->warp (rktDATA.localPoint()) * ptNoisePattern->tZoom;

    ptNoisePattern->tNoise.noise (tPoint, &tGradient);

    tNewNormal = rktDATA.normal() + tGradient * tBumpFactor;
    tNewNormal.normalize();
  }
  
  return tNewNormal;
  
}  /* perturbNormal() */

#endif  /* _PERTURBATION_NOISE__ */
