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

#include "gradient.h"

string TGradient::_tGradientPath;

TGradient::TGradient()
{
}


TGradient::~TGradient()
{
  tSegmentList.clear();
}


bool TGradient::loadGradient (const string& rktNAME)
{

  ifstream                 tFile;
  string                   tGimp, tGradient;
  int                      i, iNumSegments, iGradientType, iGradientColorType;
  TScalar                  tLeftR, tLeftG, tLeftB, tLeftA;
  TScalar                  tRightR, tRightG, tRightB, tRightA;
  struct TGradientSegment* ptSeg;
  
  tFile.open ((_tGradientPath + rktNAME).c_str(), ios::in);
  
  if ( rktNAME == tName )
  {
    return true;
  }
  
  tName = rktNAME;
  tSegmentList.clear();
  bLoaded = false;
  
  if ( !tFile )
  {
    cerr << "Error opening gradient file " << rktNAME << endl; 
    bLoaded = false;
    
    return bLoaded;
  }
    
  tFile >> tGimp >> tGradient;
  
  if( tGimp != "GIMP" || tGradient != "Gradient")
  {
    cerr << "Incorrect header in gradient file " << rktNAME << endl; 
    bLoaded = false;
    
    return bLoaded;
  }
  
  tFile >> iNumSegments;
  
  if ( iNumSegments < 1 )
  {
    cerr << "Illegal segment count in gradient file " << rktNAME << endl; 
    bLoaded = false;
    
    return bLoaded;
  }

  for (i = 0; i < iNumSegments; i++)
  {
    ptSeg = new struct TGradientSegment;

    tFile >> ptSeg->tLeftPos >> ptSeg->tMiddlePos >> ptSeg->tRightPos
          >> tLeftR  >> tLeftG  >> tLeftB  >> tLeftA
          >> tRightR >> tRightG >> tRightB >> tRightA
          >> iGradientType >> iGradientColorType;

    if (tFile.eof())
    {      
      cerr << "EOF reading gradient file " << rktNAME << endl; 
      bLoaded = false;
      tSegmentList.clear();
      
      return bLoaded;
    }
    
    TColor tLeftColor (tLeftR,  tLeftG,  tLeftB);
    TColor tRightColor(tRightR, tRightG, tRightB);

    //tLeftColor.printDebug();
    //tRightColor.printDebug();
    
    ptSeg->tLeftColor         = tLeftColor;
    ptSeg->tRightColor        = tRightColor;
    ptSeg->eGradientType      = (EGradientType) iGradientType;    
    ptSeg->eGradientColorType = (EGradientColorType) iGradientColorType;    
    
    tSegmentList.push_back (ptSeg);          
  }
  bLoaded = true;
  
  return bLoaded;
} /* loadGradient */


inline TScalar TGradient::calcLinearFactor (TScalar tMIDDLE, TScalar tPOS) const
{
  if ( tPOS <= tMIDDLE )
  {
    if ( tMIDDLE < FX_EPSILON )
    {
      return 0.0;
    }
    else
    {
      return 0.5 * tPOS / tMIDDLE;
    }
  }
  else
  {
    tPOS -= tMIDDLE;
    tMIDDLE = 1.0 - tMIDDLE;
    
    if ( tMIDDLE < FX_EPSILON )
    {
      return 1.0;
    }
    else
    {
      return 0.5 + 0.5 * tPOS / tMIDDLE;
    }
  }
}  /* calc_linear_factor */


inline TScalar TGradient::calcCurvedFactor (TScalar tMIDDLE, TScalar tPOS) const
{
  if ( tMIDDLE < FX_EPSILON )
  {
    tMIDDLE = FX_EPSILON;
  }
  
  return pow (tPOS, log (0.5) / log (tMIDDLE));
}


inline TScalar TGradient::calcSineFactor (TScalar tMIDDLE, TScalar tPOS) const
{
  tPOS = calcLinearFactor (tMIDDLE, tPOS);
  
  return (sin ((-PI / 2.0) + PI * tPOS) + 1.0) / 2.0;
}


inline TScalar TGradient::calcSphereIncreasingFactor (TScalar tMIDDLE, TScalar tPOS) const
{
  tPOS = calcLinearFactor (tMIDDLE, tPOS) - 1.0;
  
  return sqrt (1.0 - tPOS * tPOS);
}


inline TScalar TGradient::calcSphereDecreasingFactor (TScalar tMIDDLE, TScalar tPOS) const
{
  tPOS = calcLinearFactor (tMIDDLE, tPOS);
  
  return 1.0 - sqrt (1.0 - tPOS * tPOS);
}


inline void TGradient::calcRGBtoHSV (const TColor& rktRGB, TScalar& rtHUE, TScalar& rtSAT, TScalar& rtVAL) const
{
  TScalar   tDelta;
  TScalar   tMax = (TScalar) rktRGB.max();
  TScalar   tMin = (TScalar) rktRGB.min();
  
  rtVAL = tMax;
  
  if ( tMax > FX_EPSILON )
  {
    rtSAT = (tMax - tMin) / tMax;
  }
  else
  {
    rtSAT = 0.0;
  }
  
  if ( rtSAT > FX_EPSILON )
  {
    tDelta = tMax - tMin;
    
    if ( fabs(rktRGB.red() - tMax) < FX_EPSILON )
    {
      rtHUE = (rktRGB.green() - rktRGB.blue()) / tDelta;
    }
    else if ( fabs(rktRGB.green() - tMax) < FX_EPSILON )
    {
      rtHUE = 2.0 + (rktRGB.blue() - rktRGB.red()) / tDelta;
    }
    else if ( fabs(rktRGB.blue() - tMax) < FX_EPSILON )
    {
      rtHUE = 4.0 + (rktRGB.red() - rktRGB.green()) / tDelta;
    }
    
    rtHUE /= 6.0;
    
    if ( rtHUE < 0.0 )
    {
      rtHUE += 1.0;
    }
    else if ( rtHUE > 1.0 )
    {
      rtHUE -= 1.0;
    }
  }
  else
  {
    rtHUE = 0.0;
  }
}


inline TColor TGradient::calcHSVtoRGB (const TScalar& rktHUE, const TScalar& rktSAT, const TScalar& rktVAL) const
{
  TScalar   tHue;
  TScalar   tSaturation;
  TScalar   tValue;
  TScalar   tF;
  TScalar   tP;
  TScalar   tQ;
  TScalar   tT;
  TColor    tRet;
  TScalar   tRed    = 0.0;
  TScalar   tGreen  = 0.0;
  TScalar   tBlue   = 0.0;
  
  if ( rktSAT < FX_EPSILON)
  {
    tRet.setRed   (rktVAL);
    tRet.setGreen (rktVAL);
    tRet.setBlue  (rktVAL);
  }
  else
  {
    tHue = rktHUE * 6.0;
    tSaturation = rktSAT;
    tValue = rktVAL;
    
    if ( tHue >= 6.0 )
    {
      tHue = 0.0;
    }
    
    tF = tHue - (int) tHue;
    tP = tValue * (1.0 - tSaturation);
    tQ = tValue * (1.0 - tSaturation * tF);
    tT = tValue * (1.0 - tSaturation * (1.0 - tF));
    
    switch ((int) tHue)
    {
      case 0:
      {
        tRed   = tValue;
        tGreen = tT;
        tBlue  = tP;
      }
      break;
      
      case 1:
      {
        tRed   = tQ;
        tGreen = tValue;
        tBlue  = tP;
      }
      break;
      
      case 2:
      {
        tRed   = tP;
        tGreen = tValue;
        tBlue  = tT;
      }
      break;
      
      case 3:
      {
        tRed   = tP;
        tGreen = tQ;
        tBlue  = tValue;
      }
      break;
      
      case 4:
      {
        tRed   = tT;
        tGreen = tP;
        tBlue  = tValue;
      }
      break;
      
      case 5:
      {
        tRed   = tValue;
        tGreen = tP;
        tBlue  = tQ;
      }
      break;      
    }  /* switch */
  }  /* else */
  tRet.setRed   (tRed);
  tRet.setGreen (tGreen);
  tRet.setBlue  (tBlue);
  
  return tRet;
}  /* calc_hsv_to_rgb */


TColor TGradient::getColorAt (const TScalar& rktPOS) const
{
  TColor             tRet;
  TScalar            tPos;
  TScalar            tMiddle;
  TScalar            tFactor;
  TScalar            tSegmentLength;
  TScalar            tLeftH, tLeftS, tLeftV;
  TScalar            tRightH, tRightS, tRightV;
  TGradientSegment*  ptSegment;
  
  ptSegment = NULL; /* to keep -Wall quiet :-) */

  if ( bLoaded == false )
  {
    return tRet._black();
  }
  
  tPos = ( rktPOS < 0.0 ) ? 0.0 : ( rktPOS > 1.0) ? 1.0 : rktPOS;
  
  for (list<TGradientSegment*>::iterator tIter = tSegmentList.begin(); ( tIter != tSegmentList.end() ) ;tIter++)
  {
    ptSegment = *tIter;
    
    if ( ptSegment->tRightPos > tPos )
    {
      break;
    }
  }

  tSegmentLength = ptSegment->tRightPos - ptSegment->tLeftPos;
  
  if ( tSegmentLength < FX_EPSILON )
  {
    tMiddle = 0.5;
    tPos    = 0.5;
  }
  else
  {
    tMiddle = (ptSegment->tMiddlePos - ptSegment->tLeftPos) / tSegmentLength;
    tPos    = (tPos - ptSegment->tLeftPos) / tSegmentLength;
  }
  
  switch (ptSegment->eGradientType)
  {
    case FX_GRAD_LINEAR:
    {
      tFactor = calcLinearFactor (tMiddle, tPos);
    }
    break;
    
    case FX_GRAD_CURVED:
    {
      tFactor = calcCurvedFactor (tMiddle, tPos);
    }
    break;
    
    case FX_GRAD_SINE:
    {
      tFactor = calcSineFactor (tMiddle, tPos);
    }
    break;
    
    case FX_GRAD_SPHERE_INCREASING:
    {
      tFactor = calcSphereIncreasingFactor (tMiddle, tPos);
    }
    break;
    
    case FX_GRAD_SPHERE_DECREASING:
    {
      tFactor = calcSphereDecreasingFactor (tMiddle, tPos);
    }
    break;
    
    default:
    {
      cerr << "Unknown gradient type " << (int) ptSegment->eGradientType << endl;
      tFactor = 0.0;
    }
    break;
  }  /* switch */
  
  //cerr << tFactor << endl;
  
  if ( ptSegment->eGradientColorType == FX_GRAD_RGB )
  {
    tRet = ptSegment->tLeftColor + (ptSegment->tRightColor - ptSegment->tLeftColor) * tFactor;
  }
  else
  {
    calcRGBtoHSV (ptSegment->tLeftColor,  tLeftH,  tLeftS,  tLeftV);
    calcRGBtoHSV (ptSegment->tRightColor, tRightH, tRightS, tRightV);

    tLeftS += (tRightS - tLeftS) * tFactor;
    tLeftV += (tRightV - tLeftV) * tFactor;
  
    switch (ptSegment->eGradientColorType)
    {
      case FX_GRAD_HSV_CCW:
      {
        if (tLeftH < tRightH)
        {
          tLeftH += (tRightH - tLeftH) * tFactor;
        }
        else
        {
          tLeftH += (1.0 - tLeftH + tRightH) * tFactor;
        }
      
        if ( tLeftH > 1.0 )
        {
          tLeftH -= 1.0;
        }
      }
      break;

      case FX_GRAD_HSV_CW:
      {
        if ( tRightH < tLeftH )
        {
          tLeftH -= (tLeftH - tRightH) * tFactor;
        }
        else
        {
          tLeftH -= (1.0 - tRightH + tLeftH) * tFactor;
        }
      
        if ( tLeftH < 0.0 )
        {
          tLeftH += 1.0;
        }
      }
      break;

      default:
      {
        cerr << "Unknown gradient color type " << (int) ptSegment->eGradientColorType << endl;
        tFactor = 0.0;
      }
      break;
    }  /* switch */

    tRet = calcHSVtoRGB (tLeftH, tLeftS, tLeftV);  
  }  /* else */
  
  return tRet;
}  /* getColorAt */

/*
int main(int argc, char *argv[])
{
  unsigned char   aucTgaHeader[]={0,0,2,0,0,0,0,0,0,0,0,0,0,2,64,0,24,32};
  unsigned char   aucLine[256 * 6];
  //TGradient       tGradient("/usr/share/gimp/gradients/Wood_2");
  TGradient       tGradient(argv[1]);
  FILE            *fp;
  TScalar         tPos;
  TColor          tColor;
  TColor          tColor24;
  int             i,j;

  if (argc < 2)
  {
    puts ("usage:- gradient gradient-file tga-file");
    return 1;
  }
  
  fp = fopen (argv[2], "w");
  
  if ( fp == NULL )
  {
    puts ("Arse!");
    return 1;
  }
  
  fwrite (aucTgaHeader, sizeof(aucTgaHeader), 1, fp);
  
  for(i = 0, j = 0; i < 512 ; i++)
  {
    tPos = (TScalar)i / 512;
    tColor = tGradient.getColorAt (tPos);
    tColor24 = tColor.convertTo24Bits();
    //tColor.printDebug();
    aucLine[j++] = (unsigned char)tColor24.blue();
    aucLine[j++] = (unsigned char)tColor24.green();
    aucLine[j++] = (unsigned char)tColor24.red();
  }
  
  for (i = 0; i < 64 ; i++)
  {
    fwrite(aucLine, sizeof(aucLine), 1, fp);
  }
  
  fclose(fp);

}
*/
