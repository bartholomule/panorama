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

#ifndef _PATTERN_COMPOSITE__
#define _PATTERN_COMPOSITE__

#include "llapi/pattern.h"
#include "hlapi/plugin_manager.h"

class TPatternComposite : public TPattern
{

  protected:

    TPattern*   ptPattern1;
    TPattern*   ptPattern2;
    TScalar     tPattern1Amount;
    TScalar     tPattern2Amount;

  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TPatternComposite (void) :
      TPattern(),
      tPattern1Amount (0.5),
      tPattern2Amount (0.5) {}
    
    TColor pattern (const TSurfaceData& rktDATA) const
    {
      TColor   tColor;
      
      if ( ( !ptPattern1 ) || ( !ptPattern2 ) )
      {
        cerr << "Error: both pattern1 and pattern2 must be set" << endl;
	exit (1);
      }
      
      tColor  = ptPattern1->pattern (rktDATA) * tPattern1Amount;
      tColor += ptPattern2->pattern (rktDATA) * tPattern2Amount;

      return tColor;
    }

    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    void setPattern1 (TPattern* ptPATTERN)
    {
      ptPattern1 = ptPATTERN;
    }
    void setPattern2 (TPattern* ptPATTERN)
    {
      ptPattern2 = ptPATTERN;
    }

    string className (void) const { return "PatternComposite"; }

};  /* class TPatternComposite */

#endif  /* _PATTERN_COMPOSITE__ */

