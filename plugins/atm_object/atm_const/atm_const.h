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

#ifndef _ATM_TEST__
#define _ATM_TEST__

#include "llapi/atmospheric_object.h"
#include "hlapi/plugin_manager.h"

class TAtmConst : public TAtmosphericObject
{

  protected:

    TVector   tBBFrom, tBBTo;
    
    mutable TAtmSampleData   tSampleData;
    
  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TAtmConst (void);

    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;
    
    TAtmSampleData sampleData (const TVector& rktPOINT) const
    {
      return tSampleData;
    }

    TScalar transparency (const TVector& rktPOINT1, const TVector& rktPOINT2) const
    {
      return exp (-tSampleData.tExtinction * Distance (rktPOINT1, rktPOINT2));
    }

    bool initialize (TScene* ptSCENE);
    
    string className (void) const { return "AtmConst"; }

};  /* class TAtmConst */

#endif  /* _ATM_TEST__ */
