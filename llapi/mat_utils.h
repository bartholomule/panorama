/*
*  Copyright (C) 1999 Angel Jimenez Jimenez and Carlos Jimenez Moreno
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

#ifndef _MAT_UTILS__
#define _MAT_UTILS__

#include "llapi/llapi_defs.h"


inline TScalar tfloor (TScalar tA)
{
  return (TScalar) ((long)tA - ( tA < 0.0));
}  /*  tfloor */


inline TScalar smoothstep (TScalar tA, TScalar tB, TScalar tX)
{
  if ( tX < tA )
  {
    return 0;
  }

  if ( tX > tB )
  {
    return 1;
  }

  return (tX * tX * (3.0 - tX * 2));
}  /* smoothstep */


inline TScalar clamp (const TScalar tX, const TScalar tA, const TScalar tB)
{
  return tX < tA ? tA : ( tX > tB ? tB : tX );
}  /* clamp */


#endif  /* _MAT_UTILS__ */
