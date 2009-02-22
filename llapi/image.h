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

#ifndef PANORAMA_IMAGE_H_INCLUDED
#define PANORAMA_IMAGE_H_INCLUDED

#include <map>
#include <string>
#include <fstream>
#include "llapi/llapi_defs.h"
#include "llapi/frame.h"

namespace panorama
{

  class TImage : public TFrame<TColor>
  {

  protected:

    float   fMinIntensity;
    float   fMaxIntensity;

  public:

    TImage (size_t zWIDTH, size_t zHEIGHT) :
      TFrame<TColor> (zWIDTH, zHEIGHT),
      fMinIntensity (10e6),
      fMaxIntensity (0) {}

    TImage (const TImage& rktIMAGE) :
      TFrame<TColor> (rktIMAGE),
      fMinIntensity (rktIMAGE.fMinIntensity),
      fMaxIntensity (rktIMAGE.fMaxIntensity) {}

    void setPixel (size_t X, size_t Y, const TColor& rktCOLOR, bool gSUM = false);
    void setAAPixel (TScalar X, TScalar Y, const TColor& rktCOLOR, bool gSUM = false);

    float minIntensity (void) const { return fMinIntensity; }
    float maxIntensity (void) const { return fMaxIntensity; }

  };  /* class TImage */
} // end namespace panorama

#endif  /* PANORAMA_IMAGE_H_INCLUDED */
