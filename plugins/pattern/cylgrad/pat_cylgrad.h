/*
*  Copyright (C) 1999 Angel Jimenez Jimenez, Carlos Jimenez Moreno and Peter Barnett
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

#ifndef _PATTERN_CYLGRAD__
#define _PATTERN_CYLGRAD__

#include "llapi/pattern.h"
#include "llapi/gradient.h"
#include "llapi/mat_utils.h"
#include "hlapi/plugin_manager.h"

class TPatternCylGrad : public TPattern
{

  protected:
   
    TColor      tColor;
    TGradient   tGradient;    
    TColor      tBaseColor;
    bool        bGradientLoaded;
    TScalar     tCycles;
    TScalar     tSwirl;

    TColor evaluate (const TVector& rktPOINT) const;

  public:
  
    TPatternCylGrad() :
      TPattern(),
      bGradientLoaded ( false ),
      tCycles (1),
      tSwirl (0) {}

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TColor pattern (const TSurfaceData& rktDATA) const
     {
      TVector tPoint = rktDATA.localPoint();
      return evaluate (tPoint);
    }

    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;
 
    void setColor (const TColor& rktCOLOR)
    {
      tColor = rktCOLOR;
    }
    void setBaseColor (const TColor& rktCOLOR)
    {
      tBaseColor = rktCOLOR;
    }

    string className (void) const { return "PatternCylGrad"; }

};  /* class TPatternCylGrad */

#endif  /* _PATTERN_CYLGRAD__ */
