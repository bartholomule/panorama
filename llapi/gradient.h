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

    static string   _tGradientPath;
    
    mutable list<TGradientSegment*> tSegmentList;
    string                          tName;
    string                          tFileName;
    mutable bool                    bLoaded;
    
    TScalar  calcLinearFactor (TScalar tMIDDLE, TScalar tPOS) const;
    TScalar  calcCurvedFactor (TScalar tMIDDLE, TScalar tPOS) const;
    TScalar  calcSineFactor (TScalar tMIDDLE, TScalar tPOS) const;
    TScalar  calcSphereIncreasingFactor (TScalar tMIDDLE, TScalar tPOS) const;
    TScalar  calcSphereDecreasingFactor (TScalar tMIDDLE, TScalar tPOS) const;
    void     calcRGBtoHSV (const TColor& ktRGB, TScalar& rtHUE, TScalar& rtSAT, TScalar& rtVAL) const;
    TColor   calcHSVtoRGB (const TScalar& rktHUE, const TScalar& rktSAT, const TScalar& rktVAL) const;
    
  public:

    static void _initialize (const string& rktPATH)
    {
      _tGradientPath = rktPATH;
    }
    
    TGradient();
    ~TGradient();
    bool    loadGradient (const string& rktNAME);
    TColor  getColorAt (const TScalar& rktPOSITION) const;

};  /* class TGradient */

#endif  /* _GRADIENT__ */

