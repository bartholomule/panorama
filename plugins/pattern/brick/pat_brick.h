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

#ifndef _PATTERN_BRICK__
#define _PATTERN_BRICK__

#include "llapi/pattern.h"
#include "hlapi/plugin_manager.h"

class TPerturbationBrick;


class TPatternBrick : public TPattern
{

  friend class TPerturbationBrick;

  protected:

    TColor    tColor;
    TColor    tBaseColor;
    TVector   tZoomOriginal;
    TVector   tZoom;
    TScalar   tBrickWidth;
    TScalar   tBrickHeight;
    TScalar   tMortarThickness;
    
    TScalar evaluate (const TVector& rktPOINT, TVector* ptGRADIENT = NULL) const;

  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TPatternBrick (void) :
      TPattern(),
      tZoom (1, 1, 1),
      tBrickWidth (2.5),
      tBrickHeight (0.8),
      tMortarThickness(0.1) {}
    
    TScalar step( TScalar a, TScalar x) const;
    TScalar mod( TScalar a, TScalar x) const;
    TScalar smoothstep( TScalar a, TScalar b, TScalar x) const;
    TScalar smoothstepdiff( TScalar a, TScalar b, TScalar x) const;
      
    TColor pattern (const TSurfaceData& rktDATA) const
    {
      TVector   tPoint = rktDATA.localPoint() * tZoom;
      TScalar   tValue = evaluate (tPoint);

      return lerp (tBaseColor, tColor, tValue);
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

    string className (void) const { return "PatternBrick"; }

};  /* class TPatternBrick */


inline TScalar TPatternBrick::step (TScalar a, TScalar x) const
{

  return (TScalar) ( x >= a );

}  /* step() */


inline TScalar TPatternBrick::mod (TScalar a, TScalar x) const
{
  int n = (int) (a / x);
  a -= n * x;
  if( a < 0 )
  {
    a += x;
  }

  return a;
}  /* mod() */


inline TScalar TPatternBrick::smoothstep (TScalar a, TScalar b, TScalar x) const
{

  if (x < a) 
  {
    return 0.0;
  }
  if (x >= b) 
  {
    return 1.0;
  }

  // Normalize x 
  x = (x - a) / (b - a); 

  return x * x * (3 - 2 * x);

}  /* smoothstep() */


inline TScalar TPatternBrick::smoothstepdiff (TScalar a, TScalar b, TScalar x) const
{

  if ( ( x < a ) || ( x >= b ) ) 
  {
    return 0.0;
  }
  
  // Normalize x 
  x = (x - a) / (b - a); 

  return 4.0 * x * (1.0 - x);

}  /* smoothstepdiff() */


#endif  /* _PATTERN_BRICK__ */

