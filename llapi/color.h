/*
*  Copyright (C) 1998, 1999 Angel Jimenez Jimenez and Carlos Jimenez Moreno
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

#ifndef _COLOR__
#define _COLOR__

#include <cmath>
#include <iostream>
#include "llapi/base_class.h"
#include "llapi/math_tools.h"

class TColor : public TBaseClass
{

  protected:

    float   fRed;
    float   fGreen;
    float   fBlue;  

  public:

    static TColor _black (void) { return TColor (0, 0, 0); }
    static TColor _white (void) { return TColor (1, 1, 1); }
    static TColor _null (void) { return TColor (0, 0, 0); }

    TColor (void) :
      fRed (0),
      fGreen (0),
      fBlue (0) {}
    
    TColor (float fRED, float fGREEN, float fBLUE) :
      fRed (fRED),
      fGreen (fGREEN),
      fBlue (fBLUE) {}

    TColor (const TColor& rktCOLOR) :
      fRed (rktCOLOR.fRed),
      fGreen (rktCOLOR.fGreen),
      fBlue (rktCOLOR.fBlue) {}

    float red (void) const { return fRed; }
    float green (void) const { return fGreen; }
    float blue (void) const { return fBlue; }

    void setRed (float fRED) { fRed = fRED; }
    void setGreen (float fGREEN) { fGreen = fGREEN; }
    void setBlue (float fBLUE) { fBlue = fBLUE; }

    TColor& operator += (const TColor& rktCOLOR);
    TColor& operator -= (const TColor& rktCOLOR);
    TColor& operator *= (const TColor& rktCOLOR);
    TColor& operator /= (const TColor& rktCOLOR);

    TColor& operator += (float fVALUE);
    TColor& operator -= (float fVALUE);
    TColor& operator *= (float fVALUE);
    TColor& operator /= (float fVALUE);
    
    TColor convertTo24Bits (void) const;
    TColor convertFrom24Bits (void) const;
    TColor convertToGrey (void) const;
                          
    float average (void) const;
    float intensity (void) const;

    void clamp (void);

    float min (void) const { return min3 (fRed, fGreen, fBlue); }
    float max (void) const { return max3 (fRed, fGreen, fBlue); }

    bool saturated (void) const;

    void printDebug (void) const;

    EClass classType (void) const { return FX_COLOR_CLASS; }
    string className (void) const { return "Color"; }

};  /* class TColor */


inline TColor& TColor::operator += (const TColor& rktCOLOR)
{

  fRed   += rktCOLOR.red();
  fGreen += rktCOLOR.green();
  fBlue  += rktCOLOR.blue();

  return *this;

}  /* operator += */


inline TColor& TColor::operator -= (const TColor& rktCOLOR)
{

  fRed   -= rktCOLOR.red();
  fGreen -= rktCOLOR.green();
  fBlue  -= rktCOLOR.blue();

  return *this;

}  /* operator -= */


inline TColor& TColor::operator *= (const TColor& rktCOLOR)
{

  fRed   *= rktCOLOR.red();
  fGreen *= rktCOLOR.green();
  fBlue  *= rktCOLOR.blue();

  return *this;

}  /* operator *= */


inline TColor& TColor::operator /= (const TColor& rktCOLOR)
{

  fRed   /= rktCOLOR.red();
  fGreen /= rktCOLOR.green();
  fBlue  /= rktCOLOR.blue();

  return *this;

}  /* operator /= */


inline TColor& TColor::operator += (float fVALUE)
{

  fRed   += fVALUE;
  fGreen += fVALUE;
  fBlue  += fVALUE;

  return *this;

}  /* operator += */


inline TColor& TColor::operator -= (float fVALUE)
{

  fRed   -= fVALUE;
  fGreen -= fVALUE;
  fBlue  -= fVALUE;

  return *this;

}  /* operator -= */


inline TColor& TColor::operator *= (float fVALUE)
{

  fRed   *= fVALUE;
  fGreen *= fVALUE;
  fBlue  *= fVALUE;

  return *this;

}  /* operator *= */


inline TColor& TColor::operator /= (float fVALUE)
{

  fRed   /= fVALUE;
  fGreen /= fVALUE;
  fBlue  /= fVALUE;

  return *this;

}  /* operator /= */


inline TColor TColor::convertTo24Bits (void) const
{

  const float   kfValue = 255;

  return TColor (fRed * kfValue, fGreen * kfValue, fBlue * kfValue);

}  /* convertTo24Bits() */


inline TColor TColor::convertFrom24Bits (void) const
{

  const float   kfValue = 255;

  return TColor (fRed / kfValue, fGreen / kfValue, fBlue / kfValue);

}  /* convertFrom24Bits() */


inline TColor TColor::convertToGrey (void) const
{

  float   fValue = intensity();

  return TColor (fValue, fValue, fValue);

}  /* convertToGrey() */


inline float TColor::average (void) const
{

  return (fRed + fGreen + fBlue) / 3.0;

}  /* average() */


inline float TColor::intensity (void) const
{

  return (fRed * 0.2125 + fGreen * 0.7154 + fBlue * 0.0721);

}  /* intensity() */


inline void TColor::clamp (void)
{

  if ( fRed > 1 ) fRed = 1;
  else if ( fRed < 0 ) fRed = 0;

  if ( fGreen > 1 ) fGreen = 1;
  else if ( fGreen < 0 ) fGreen = 0;

  if ( fBlue > 1 ) fBlue = 1;
  else if ( fBlue < 0 ) fBlue = 0;

}  /* clamp() */


inline bool TColor::saturated (void) const
{

  return ( (fRed >= 1) && (fGreen >= 1) && (fBlue >= 1) );

}  /* saturated() */


inline void TColor::printDebug (void) const
{

  cerr << "TColor (" << fRed << ", " << fGreen << ", " << fBlue << ")" << endl;

}  /* printDebug() */


inline TColor operator * (const TColor& rktCOLOR, float fVALUE)
{

  return TColor (fVALUE * rktCOLOR.red()  ,
                 fVALUE * rktCOLOR.green(),
                 fVALUE * rktCOLOR.blue() );
  
}  /* operator * () */


inline TColor operator / (const TColor& rktCOLOR, float fVALUE)
{

  return TColor (rktCOLOR.red()   / fVALUE,
                 rktCOLOR.green() / fVALUE,
                 rktCOLOR.blue()  / fVALUE);
  
}  /* operator / () */


inline TColor operator + (const TColor& rktCOLOR1, const TColor& rktCOLOR2)
{

  return TColor (rktCOLOR1.red()   + rktCOLOR2.red()  ,
                 rktCOLOR1.green() + rktCOLOR2.green(),
                 rktCOLOR1.blue()  + rktCOLOR2.blue() );
  
}  /* operator + () */


inline TColor operator - (const TColor& rktCOLOR1, const TColor& rktCOLOR2)
{

  return TColor (rktCOLOR1.red()   - rktCOLOR2.red()  ,
                 rktCOLOR1.green() - rktCOLOR2.green(),
                 rktCOLOR1.blue()  - rktCOLOR2.blue() );
  
}  /* operator - () */


inline TColor operator * (const TColor& rktCOLOR1, const TColor& rktCOLOR2)
{

  return TColor (rktCOLOR1.red()   * rktCOLOR2.red()  ,
                 rktCOLOR1.green() * rktCOLOR2.green(),
                 rktCOLOR1.blue()  * rktCOLOR2.blue() );

}  /* operator * () */


inline TColor operator / (const TColor& rktCOLOR1, const TColor& rktCOLOR2)
{

  return TColor (rktCOLOR1.red()   / rktCOLOR2.red()  ,
                 rktCOLOR1.green() / rktCOLOR2.green(),
                 rktCOLOR1.blue()  / rktCOLOR2.blue() );

}  /* operator / () */


inline bool operator == (const TColor& rktCOLOR1, const TColor& rktCOLOR2)
{

  return ( ( rktCOLOR1.red()   == rktCOLOR2.red() )   &&
           ( rktCOLOR1.green() == rktCOLOR2.green() ) &&
           ( rktCOLOR1.blue()  == rktCOLOR2.blue() )  );

}  /* operator == () */


inline bool operator != (const TColor& rktCOLOR1, const TColor& rktCOLOR2)
{

  return ( ( rktCOLOR1.red()   != rktCOLOR2.red() )   ||
           ( rktCOLOR1.green() != rktCOLOR2.green() ) ||
           ( rktCOLOR1.blue()  != rktCOLOR2.blue() )  );

}  /* operator != () */


inline float MaxColorDiff (const TColor& rktCOLOR1, const TColor& rktCOLOR2)
{

  return max3 (fabs (rktCOLOR1.red() - rktCOLOR2.red()),
               fabs (rktCOLOR1.green() - rktCOLOR2.green()),
               fabs (rktCOLOR1.blue() - rktCOLOR2.blue()));
  
}  /* MaxColorDiff() */


inline TColor ColorDiff (const TColor& rktCOLOR1, const TColor& rktCOLOR2)
{

  return TColor (fabs (rktCOLOR1.red() - rktCOLOR2.red()),
                 fabs (rktCOLOR1.green() - rktCOLOR2.green()),
                 fabs (rktCOLOR1.blue() - rktCOLOR2.blue()));
  
}  /* ColorDiff() */
                             
#endif  /* _COLOR__ */
