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

#ifndef _PERTURBATION_WORLEY__
#define _PERTURBATION_WORLEY__

#include "llapi/worley_basis.h"
#include "llapi/perturbation.h"
#include "hlapi/plugin_manager.h"
#include "../../pattern/worley/pat_worley.h"

class TPerturbationWorley : public TPerturbation
{
 
  protected:

    TScalar           tBumpFactor;
    magic_pointer<TPatternWorley>   ptWorleyPattern;

  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TPerturbationWorley (void) :
      TPerturbation(),
      tBumpFactor (0),
      ptWorleyPattern (NULL) {}

    TVector perturbNormal (const TSurfaceData& rktDATA) const;
      
    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    void setWorleyPattern (magic_pointer<TPatternWorley> ptPATTERN) { ptWorleyPattern = ptPATTERN; }

    string className (void) const { return "PerturbationWorley"; }
    TPerturbationWorley* clone_new() const { return new TPerturbationWorley(*this); }
};  /* class TPerturbationWorley */


inline TVector TPerturbationWorley::perturbNormal (const TSurfaceData& rktDATA) const
{

  TVector                                     tPoint;
  TVector                                     tVector;
  TPriorityQueue<TWorleyBasis::TPointData>*   ptPQueue;
  TVector                                     tNewNormal = rktDATA.unperturbedNormal();

  if ( tBumpFactor )
  {
    if ( !ptWorleyPattern )
    {
      GOM.error() << ("Error: worley_pattern must be set") << endl;
      exit (1);
    }

    tPoint   = ptWorleyPattern->warp (rktDATA.localPoint()) * ptWorleyPattern->tZoom;
    ptPQueue = ptWorleyPattern->tWorleyBasis.evaluate (tPoint);

    tVector = (*ptPQueue)[0].tData.tVector;
    
    tNewNormal += tVector * tBumpFactor;
    tNewNormal.normalize();
  
    delete ptPQueue;
  }
  
  return tNewNormal;
  
}  /* perturbNormal() */

#endif  /* _PERTURBATION_WORLEY__ */
