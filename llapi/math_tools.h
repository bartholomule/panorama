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

#ifndef _TOOLS__
#define _TOOLS__

#include <cstdlib>
#include <algorithm>
#include "llapi/machine.h"

#undef USE_RAND_FUNCTION

static DWord   _dwRandomSeed;

inline int sign (double dNUMBER)
{

  return (( dNUMBER > 0 ) ? 1 : ((dNUMBER < 0 ) ? -1 : 0));

}  /* sign() */

template <class TItem>
inline const TItem& min3 (const TItem& tITEM1, const TItem& tITEM2, const TItem& tITEM3)
{

  return CPPMIN (CPPMIN (tITEM1, tITEM2), tITEM3);

}  /* min3() */


template <class TItem>
inline const TItem& max3 (const TItem& tITEM1, const TItem& tITEM2, const TItem& tITEM3)
{

  return CPPMAX (CPPMAX (tITEM1, tITEM2), tITEM3);

}  /* max3() */


inline void SeedRandom (DWord dwSEED)
{

#ifdef USE_RAND_FUNCTION

  srand (dwSEED);

#else

  _dwRandomSeed = dwSEED;

#endif
  
}  /* SeedRandom() */


inline float frand (void)
{

#ifdef USE_RAND_FUNCTION

  return (float (rand()) / RAND_MAX);

#else

  _dwRandomSeed = _dwRandomSeed * 17231723L + 2001L;
  
  return (float ((_dwRandomSeed >> 16) & 0x7fff) / float (0x7fff));

#endif
  
}  /* frand() */


inline float srand (void)
{

  return (1.0 - frand() * 2);

}  /* srand() */


inline double degreeToRadian (double dDEGREE)
{

  return ((dDEGREE * PI) / 180.0);

}  /* degreeToRadian() */


inline double factorial (Byte bNUMBER)
{

  double   dValue = bNUMBER;

  if ( bNUMBER == 0 )
  {
    return 1;
  }

  while ( --bNUMBER )
  {
    dValue *= bNUMBER;
  }

  return dValue;

}  /* factorial() */


template <class TItem>
inline TItem lerp (const TItem& rktMIN, const TItem& rktMAX, double dFACTOR)
{

  return ((rktMIN * (1 - dFACTOR)) + (rktMAX * dFACTOR));
//  return (rktMIN + (rktMAX - rktMIN) * dFACTOR);

}  /* lerp() */


template <class TItem>
inline size_t mod (TItem tITEM1, size_t zITEM2)
{

  int   n = (int) (tITEM1 / zITEM2);

  tITEM1 -= n * zITEM2;
  if ( tITEM1 < 0 )
  {
    tITEM1 += zITEM2;
  }

  return size_t (tITEM1);
  
}  /* mod() */

#endif  /* _TOOLS__ */
