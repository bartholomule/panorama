/*
*  Copyright (C) 1998, 1999 Angel Jimenez Jimenez, Carlos Jimenez Moreno and Peter Barnett
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

#ifndef _PATTERN_CRACKLE__
#define _PATTERN_CRACKLE__

#include "llapi/pattern.h"
#include "llapi/gradient.h"
#include "hlapi/plugin_manager.h"

#define CACHESIZE 81
#define HASHMASK 0xfff
#define USE_NEWRAND

class TPerturbationCrackle;

class TVoronoi
{

  protected:

    mutable TVector atPointCache[CACHESIZE];
    int             aiHashTable[HASHMASK + 1];
    mutable long    lRandomSeed;
    mutable long    lLastHashValue;
    mutable int     iPointsInCache;
    
    long   Random () const;
    double Drandom () const;
    void   SeedRandom (long lSeed) const;
    int    Hash3d (int iX, int iY, int iZ) const;
    long   GeneratePointInCube (const TVector& rktCorner, TVector& tPoint) const;
    void   BuildPointCache (const TVector& rktPOINT) const;

  public:

    TVoronoi();

    TScalar   GetValueAtPoint (const TVector& rktPOINT, TVector* ptGRADIENT = NULL) const;

};  /* class TVoronoi */


class TPatternCrackle : public TPattern
{

  friend class TPerturbationCrackle;

  protected:

    TColor      tColor;
    TColor      tBaseColor;
    TVector     tZoom;
    bool        bGradientLoaded;
    TVoronoi    tVoronoi;
    TGradient   tGradient;
    
    TScalar evaluate (const TVector& rktPOINT, TVector* ptGRADIENT = NULL) const;
    TScalar eval     (TScalar tX, TScalar tY, TScalar tZ, int iDebug = 0) const;

  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TPatternCrackle (void) :
      TPattern(),
      tZoom (1, 1, 1),
      bGradientLoaded (false),
      tVoronoi() {}
      
    TColor pattern (const TSurfaceData& rktDATA) const
    {
      TVector   tPoint      = rktDATA.localPoint() * tZoom;
      TScalar   tNoiseValue = evaluate (tPoint);

      if ( bGradientLoaded )
      {
        return tGradient.getColorAt (tNoiseValue);
      }
      else
      {
        return lerp (tBaseColor, tColor, tNoiseValue);
      }
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

    string className (void) const { return "PatternCrackle"; }

};  /* class TPatternCrackle */

#endif  /* _PATTERN_CRACKLE__ */

