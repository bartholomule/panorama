/*
*  Copyright (C) 1999 Jon Frydensbjerg
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

#ifndef _FLARE_STREAKS__
#define _FLARE_STREAKS__

#include "flare.h"

struct TStreakEntry
{

  float  fStartAngle; 
  float  fWidth;
  float  fEndAngle;
  float  fIntensity;

};  /* struct TStreakEntry */

class TFlare_Streaks : public TFlare
{
 
  protected:

    TStreakEntry*  aptStreakTable;
    size_t         zNoStreaks;
    float          fCoverageBase;
    float          fCoverageDeviation;
    float          fIntensityBase;
    float          fIntensityDeviation;

    float calcPixelIntensity (float DX, float DY)
    {
      static float         _fPixelIntensity;
      static float         _fStreakIntensity;
      static float         _fAngle;
      static float         _fDAngle;
      static TStreakEntry  _tCurStreak;
      
      if ( ( DX == 0.0f ) && ( DY == 0.0f ) )
      {
        return 1.0f;
      }

      _fAngle = atan2 (DY, DX) + PI;

      _fPixelIntensity = 0.0f;

      for (size_t I = 0; ( I < zNoStreaks) ;I++)
      {
        _tCurStreak = aptStreakTable[I];

        if ( ( _tCurStreak.fEndAngle >= (PI * 2.0f) ) &&
             (               _fAngle <  (PI / 2.0f) ) )
	{
	  _fAngle += 2.0f * (float)PI;
	}

        if ( ( _fAngle >= _tCurStreak.fStartAngle ) &&
             ( _fAngle <= _tCurStreak.fEndAngle ) )
	{
          _fDAngle = (_fAngle - _tCurStreak.fStartAngle) / _tCurStreak.fWidth;
          _fDAngle = sin (_fDAngle * PI);
          
          _fStreakIntensity = (1.0f - (hypot(DX, DY) / fDistToMid)) * _fDAngle * _tCurStreak.fIntensity;

          if ( _fStreakIntensity > 0.0f )
	  {
            _fPixelIntensity += sqr (_fStreakIntensity);
          }
        }
      }

      return _fPixelIntensity;
    }

    void initTables (void) 
    {
      TStreakEntry  tCurStreak;

      SeedRandom(0xBEEF);

      aptStreakTable = (TStreakEntry *) malloc (zNoStreaks * sizeof(TStreakEntry));

      for (size_t I = 0; ( I < zNoStreaks) ;I++)
      {
         tCurStreak.fStartAngle = frand() * 2.0f * PI;
         tCurStreak.fWidth      = fCoverageBase + srand() * fCoverageDeviation;
         tCurStreak.fEndAngle   = tCurStreak.fStartAngle + tCurStreak.fWidth;

         tCurStreak.fIntensity  = fIntensityBase + srand() * fIntensityDeviation;

         aptStreakTable[I] = tCurStreak;
      }
    }

  public:
 
    TFlare_Streaks (TColor tCOLOR, float fSIZE, float fTRANSLATION, size_t zNOSTREAKS, float fCOVERAGEBASE, 
                      float fCOVERAGEDEVIATION, float fINTENSITYBASE, float fINTENSITYDEVIATION, TImage* ptIMAGE) : 
      TFlare (tCOLOR, FX_CIRCLE, fSIZE, fTRANSLATION, ptIMAGE),
      zNoStreaks (zNOSTREAKS),
      fCoverageBase (fCOVERAGEBASE),
      fCoverageDeviation (fCOVERAGEDEVIATION),
      fIntensityBase (fINTENSITYBASE),
      fIntensityDeviation (fINTENSITYDEVIATION)
    {
      initTables(); 
    }

    TFlare_Streaks (TGradient* ptGRADIENT, float fSIZE, float fTRANSLATION, size_t zNOSTREAKS, float fCOVERAGEBASE, 
                      float fCOVERAGEDEVIATION, float fINTENSITYBASE, float fINTENSITYDEVIATION, TImage* ptIMAGE) : 
      TFlare (ptGRADIENT, FX_CIRCLE, fSIZE, fTRANSLATION, ptIMAGE),
      zNoStreaks (zNOSTREAKS),
      fCoverageBase (fCOVERAGEBASE),
      fCoverageDeviation (fCOVERAGEDEVIATION),
      fIntensityBase (fINTENSITYBASE),
      fIntensityDeviation (fINTENSITYDEVIATION)
    {
      initTables(); 
    }

    ~TFlare_Streaks (void)
    {
      free (aptStreakTable);
    }

};  /* class TFlare_Streaks */

#endif  /* _FLARE_STREAKS__ */







