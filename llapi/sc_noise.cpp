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

#include "llapi/sc_noise.h"


const unsigned char akucPerm[TABSIZE] = 
{
        225,155,210,108,175,199,221,144,203,116, 70,213, 69,158, 33,252,
          5, 82,173,133,222,139,174, 27,  9, 71, 90,246, 75,130, 91,191,
        169,138,  2,151,194,235, 81,  7, 25,113,228,159,205,253,134,142,
        248, 65,224,217, 22,121,229, 63, 89,103, 96,104,156, 17,201,129,
         36,  8,165,110,237,117,231, 56,132,211,152, 20,181,111,239,218,
        170,163, 51,172,157, 47, 80,212,176,250, 87, 49, 99,242,136,189,
        162,115, 44, 43,124, 94,150, 16,141,247, 32, 10,198,223,255, 72,
         53,131, 84, 57,220,197, 58, 50,208, 11,241, 28,  3,192, 62,202,
         18,215,153, 24, 76, 41, 15,179, 39, 46, 55,  6,128,167, 23,188,
        106, 34,187,140,164, 73,112,182,244,195,227, 13, 35, 77,196,185,
         26,200,226,119, 31,123,168,125,249, 68,183,230,177,135,160,180,
         12,  1,243,148,102,166, 38,238,251, 37,240,126, 64, 74,161, 40,
        184,149,171,178,101, 66, 29, 59,146, 61,254,107, 42, 86,154,  4,
        236,232,120, 21,233,209, 45, 98,193,114, 78, 19,206, 14,118,127,
         48, 79,147, 85, 30,207,219, 54, 88,234,190,122, 95, 67,143,109,
        137,214,145, 93, 92,100,245,  0,216,186, 60, 83,105, 97,204, 52
};


TScNoise::TScNoise()
{
  int i;
  TScalar* p = atImpulseTab;
  
  srand(12345);
  
  for (i=0; i < TABSIZE ; i++)
  {
    *p++ = frand();
    *p++ = frand();
    *p++ = frand();
    *p++ = 1.0 - frand() * 2.0;
  }
}  /* TScNoise */


inline int TScNoise::perm (int ix) const
{
  return akucPerm [ix & TABMASK]; 
}  /* perm */


inline int TScNoise::index (int ix, int iy, int iz) const
{
  return perm (ix +perm (iy + perm (iz)));
}  /* index */


TScalar TScNoise::noise (const TVector& rktPOINT) const
{
  TScalar*  fp;
  TScalar   s, fx, fy, fz, dx, dy, dz, d2;
  int       i, j, k, h, n, ix, iy, iz;
  
  ix = (int) tfloor (rktPOINT.x());
  iy = (int) tfloor (rktPOINT.y());
  iz = (int) tfloor (rktPOINT.z());
  
  fx = rktPOINT.x() - (TScalar) ix;
  fy = rktPOINT.y() - (TScalar) iy;
  fz = rktPOINT.z() - (TScalar) iz;

  s = 0.0;
  
  for (i = -2; i <= 2; i++)
  {
    for (j = -2; j <= 2; j++)
    {
      for (k = -2; k <= 2; k++)
      {
        h = index (ix + i, iy + j, iz + k);
        
        for (n = NIMPULSES; n > 0 ; n--, ++h &= TABMASK)
        {
          fp = &atImpulseTab [h << 2];
          
          dx = fx - (i + *fp++);
          dy = fy - (j + *fp++);
          dz = fz - (k + *fp++);
          
          d2 = dx * dx + dy * dy + dz * dz;
          
          s += tCatRom2.filter (d2) * *fp;
        }
      }
    }
  }
  
  return s / NIMPULSES;
}  /* scnoise */


