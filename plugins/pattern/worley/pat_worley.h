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

#ifndef _PATTERN_WORLEY__
#define _PATTERN_WORLEY__

#include "llapi/worley_basis.h"
#include "llapi/pattern.h"
#include "hlapi/plugin_manager.h"

class TPerturbationWorley;


class TPatternWorley : public TPattern
{

  friend class TPerturbationWorley;

  protected:

    TColor         tColor;
    TColor         tBaseColor;
    TVector        tZoom;
    TWorleyBasis   tWorleyBasis;

  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TPatternWorley (void) :
      TPattern(),
      tZoom (1, 1, 1),
      tWorleyBasis (1) {}
      
    TColor pattern (const TSurfaceData& rktDATA) const;

    int setAttribute (const std::string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
    int getAttribute (const std::string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    void setColor (const TColor& rktCOLOR)
    {
      tColor = rktCOLOR;
    }
    void setBaseColor (const TColor& rktCOLOR)
    {
      tBaseColor = rktCOLOR;
    }

    std::string className (void) const { return "PatternWorley"; }
    TPatternWorley* clone_new() const { return new TPatternWorley(*this); }

};  /* class TPatternWorley */


inline TColor TPatternWorley::pattern (const TSurfaceData& rktDATA) const
{

  TVector                                     tPoint   = rktDATA.localPoint() * tZoom;
  TPriorityQueue<TWorleyBasis::TPointData>*   ptPQueue = tWorleyBasis.evaluate (tPoint);
  TScalar                                     tValue   = (*ptPQueue)[0].tData.tDistance;

  delete ptPQueue;
  
  return lerp (tBaseColor, tColor, tValue);
  
}  /* color() */

#endif  /* _PATTERN_WORLEY__ */
