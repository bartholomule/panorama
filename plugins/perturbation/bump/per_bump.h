/*
*  Copyright (C) 2000 Jon Frydensbjerg
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

#ifndef _PERTURBATION_BUMP__
#define _PERTURBATION_BUMP__

#include "llapi/perturbation.h"
#include "llapi/pattern.h"
#include "llapi/gradient.h"
#include "hlapi/plugin_manager.h"


class TPerturbationBump : public TPerturbation
{

  protected:

    TPattern*   ptPattern;
    TVector2    tGradientDisplacement;
    TScalar     tBumpFactor;
    TVector2    tSamples;

    TScalar     tTotalNoSamples;

    void calcTotalNoSamples (void)
    { 
      tTotalNoSamples = 1.0 / (tSamples.x() * tSamples.y());
    }  

  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TPerturbationBump (void);

    TVector perturbNormal (const TSurfaceData& rktDATA) const;

    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    void setPattern (TPattern* ptPATTERN) { ptPattern = ptPATTERN; }

    string className (void) const { return "PerturbationBump"; }

};  /* class TPerturbationBump */

#endif  /* _PERTURBATION_BUMP__ */
