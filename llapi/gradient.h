/*
*  Copyright (C) 1999 Peter Barnett
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

#ifndef _GRADIENT__
#define _GRADIENT__

#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include "llapi/llapi_defs.h"


enum EGradientType
{

	FX_GRAD_LINEAR,
	FX_GRAD_CURVED,
	FX_GRAD_SINE,
	FX_GRAD_SPHERE_INCREASING,
	FX_GRAD_SPHERE_DECREASING
  
};  /* enum EGradientType */


enum EGradientColorType
{

	FX_GRAD_RGB,
	FX_GRAD_HSV_CCW,
	FX_GRAD_HSV_CW

};  /* EGradientColorType */


struct TGradientSegment
{
  TScalar              tLeftPos;
  TScalar              tMiddlePos;
  TScalar              tRightPos;
  TColor               tLeftColor;
  TColor               tRightColor;
  EGradientType        eGradientType;
  EGradientColorType   eGradientColorType;
};  /* struct TGradientSegment */


class TGradient
{

  protected:

    mutable std::list<TGradientSegment*> tSegmentList;
    std::string                          tName;
    std::string                          tFileName;
    mutable bool                    bLoaded;
    
    TScalar  calcLinearFactor (TScalar tMIDDLE, TScalar tPOS) const;
    TScalar  calcCurvedFactor (TScalar tMIDDLE, TScalar tPOS) const;
    TScalar  calcSineFactor (TScalar tMIDDLE, TScalar tPOS) const;
    TScalar  calcSphereIncreasingFactor (TScalar tMIDDLE, TScalar tPOS) const;
    TScalar  calcSphereDecreasingFactor (TScalar tMIDDLE, TScalar tPOS) const;
    void     calcRGBtoHSV (const TColor& ktRGB, TScalar& rtHUE, TScalar& rtSAT, TScalar& rtVAL) const;
    TColor   calcHSVtoRGB (const TScalar& rktHUE, const TScalar& rktSAT, const TScalar& rktVAL) const;
    
  public:

    static void _initialize (void) {}
    
    TGradient();
    ~TGradient();
    bool    loadGradient (const std::string& rktNAME);
    TColor  getColorAt (const TScalar& rktPOSITION) const;

};  /* class TGradient */

#endif  /* _GRADIENT__ */

