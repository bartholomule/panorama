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

#ifndef _PATTERN_AMPLIFIER__
#define _PATTERN_AMPLIFIER__

#include "llapi/pattern.h"
#include "hlapi/plugin_manager.h"
#include "generic/magic_pointer.h"

class TPatternAmplifier : public TPattern
{

public:
  typedef magic_pointer<TPattern> pattern_pointer;
protected:

    pattern_pointer ptPattern;
    TScalar         tOffset;
    TScalar         tAmplification;

  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TPatternAmplifier (void) :
      TPattern(),
      tOffset (0),
      tAmplification (1) {}
    
    TColor pattern (const TSurfaceData& rktDATA) const
    {
      TColor   tColor;
      
      if ( !ptPattern )
      {
        GOM.error() << "Error: source pattern must be set" << endl;
	exit (1);
      }

      tColor = ptPattern->color (rktDATA);

      tColor *= tAmplification;
      tColor += tOffset;

      return tColor;
    }

    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    void setPattern (pattern_pointer ptPATTERN)
    {
      ptPattern = ptPATTERN;
    }

    string className (void) const { return "PatternAmplifier"; }
  
    TPatternAmplifier* clone_new() const { return new TPatternAmplifier(*this); }  

};  /* class TPatternAmplifier */

#endif  /* _PATTERN_AMPLIFIER__ */

