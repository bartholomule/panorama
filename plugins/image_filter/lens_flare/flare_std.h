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

#ifndef _FLARE_STD__
#define _FLARE_STD__

#include "flare.h"

class TFlare_Std : public TFlare
{
 
  protected:

    float calcPixelIntensity (float DX, float DY)
    {
      static float _fPixelIntensity;
 
      _fPixelIntensity = 1.0f - hypot(DX, DY) / fDistToMid;

      _fPixelIntensity = ( _fPixelIntensity < 0.0f ) ? 0.0f : sqr (_fPixelIntensity);

      return _fPixelIntensity;
    }

  public:

    TFlare_Std (TColor tCOLOR, ELFForms eFORM, float fSIZE, float fTRANSLATION, TImage* ptIMAGE) : 
      TFlare (tCOLOR, eFORM, fSIZE, fTRANSLATION, ptIMAGE) {}

    TFlare_Std (TGradient* ptGRADIENT, ELFForms eFORM, float fSIZE, float fTRANSLATION, TImage* ptIMAGE) : 
      TFlare (ptGRADIENT, eFORM, fSIZE, fTRANSLATION, ptIMAGE) {}

};  /* class TFlare_Std */

#endif  /* _FLARE_STD__ */







