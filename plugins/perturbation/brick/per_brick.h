 /*
*  Copyright (C) 1998, 1999 Angel Jimenez Jimenez, Carlos Jimenez Moreno and Pete Barnett
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

#ifndef _PERTURBATION_BRICK__
#define _PERTURBATION_BRICK__

#include "llapi/perturbation.h"
#include "hlapi/plugin_manager.h"
#include "../../pattern/brick/pat_brick.h"


class TPerturbationBrick : public TPerturbation
{

  protected:

    TScalar          tBumpFactor;
    TPatternBrick*   ptBrickPattern;

  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TPerturbationBrick (void) :
      TPerturbation(),
      tBumpFactor (0),
      ptBrickPattern (NULL) {}

    TVector perturbNormal (const TSurfaceData& rktDATA) const;
    
    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    void setBrickPattern (TPatternBrick* ptPATTERN) { ptBrickPattern = ptPATTERN; }

    string className (void) const { return "PerturbationBrick"; }

};  /* class TPerturbationBrick */


inline TVector TPerturbationBrick::perturbNormal (const TSurfaceData& rktDATA) const
{

  TVector   tNewNormal = rktDATA.unperturbedNormal();

  if ( fabs(tBumpFactor) > FX_EPSILON )
  {
    TVector   tGradient;
    TVector   tPoint;

    if ( !ptBrickPattern )
    {
      cout << ("Error: brick_pattern must be set") << endl;
      exit (1);
    }

    tPoint = ptBrickPattern->warp (rktDATA.localPoint()) * ptBrickPattern->tZoom;

    ptBrickPattern->evaluate (tPoint, &tGradient);

    tNewNormal += tGradient * tBumpFactor;
    tNewNormal.normalize();
  }
  
  return tNewNormal;  

}  /* perturbNormal() */


#endif  /* _PERTURBATION_BRICK__ */
