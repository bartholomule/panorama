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

#ifndef _FLARE_HALO__
#define _FLARE_HALO__

#include "flare.h"

class TFlare_Halo : public TFlare
{
 

  protected:

    float fParameter;

    float calcPixelIntensity (float DX, float DY)
    {
      static float _fPixelIntensity;
 
      _fPixelIntensity  = hypot(DX, DY) / fDistToMid - (1.0f - fParameter);
      _fPixelIntensity /= fParameter;
      _fPixelIntensity  = fabs (_fPixelIntensity);
  
      if ( _fPixelIntensity < 1.0 ) 
      {
        _fPixelIntensity  = 1.0f - _fPixelIntensity;
      }
      else
      {
        _fPixelIntensity  = 0.0f;
      }

      return _fPixelIntensity;
    }

  public:

    TFlare_Halo (TColor tCOLOR, ELFForms eFORM, float fSIZE, float fTRANSLATION, float fPARAMETER, TImage* ptIMAGE) : 
      TFlare (tCOLOR, eFORM, fSIZE, fTRANSLATION, ptIMAGE),
      fParameter (fPARAMETER) {}

    TFlare_Halo (TGradient* ptGRADIENT, ELFForms eFORM, float fSIZE, float fTRANSLATION, float fPARAMETER, TImage *ptIMAGE) : 
      TFlare (ptGRADIENT, eFORM, fSIZE, fTRANSLATION, ptIMAGE),
      fParameter (fPARAMETER) {}

};  /* class TFlare_Halo */

#endif  /* _FLARE_HALO__ */







