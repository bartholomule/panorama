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

#ifndef _FRAME__
#define _FRAME__

#include <assert.h>
#include <stdlib.h>
#include "llapi/debug.h"
#include "llapi/color.h"

template <class TItem>
class TFrame
{

  protected:

    size_t   zWidth;
    size_t   zHeight;
    TItem*   ptBuffer;

    TFrame (void) :
      ptBuffer (NULL) {}

  public:

    TFrame (size_t zWIDTH, size_t zHEIGHT);
    TFrame (const TFrame<TItem>& rktFRAME);

    virtual ~TFrame (void);

    size_t width (void) const { return zWidth; }
    size_t height (void) const { return zHeight; }

    void setWidth (size_t zWIDTH) { zWidth = zWIDTH; }
    void setHeight (size_t zHEIGHT) { zHeight = zHEIGHT; }

    virtual void setPixel (size_t zCX, size_t zCY, const TItem& rktITEM);
    virtual const TItem& getPixel (size_t zCX, size_t zCY) const;

    void printDebug (void) const;

};  /* class TFrame */


template <class TItem>
TFrame<TItem>::TFrame (size_t zWIDTH, size_t zHEIGHT) :
  zWidth (zWIDTH),
  zHeight (zHEIGHT)
{

  ptBuffer = new TItem [zWIDTH * zHEIGHT];

}  /* TFrame() */


template <class TItem>
TFrame<TItem>::TFrame (const TFrame<TItem>& rktFRAME) :
  zWidth (rktFRAME.width()),
  zHeight (rktFRAME.height())
{

  ptBuffer = new TItem [zWidth * zHeight];

  for (size_t J = 0; ( J < zHeight ) ;J++)
  {
    for (size_t I = 0; ( I < zWidth ) ;I++)
    {
      setPixel (I, J, rktFRAME.getPixel (I, J));
    }
  }

}  /* TFrame() */


template <class TItem>
TFrame<TItem>::~TFrame (void)
{

  delete[] ptBuffer;

}  /* ~TFrame() */


template <class TItem>
inline void TFrame<TItem>::setPixel (size_t zCX, size_t zCY, const TItem& rktITEM)
{

  // [_OPT_] We could optimize this by keeping a table of line offsets.
  ptBuffer [zCY * zWidth + zCX] = rktITEM;

}  /* setPixel() */


template <class TItem>
inline const TItem& TFrame<TItem>::getPixel (size_t zCX, size_t zCY) const
{

  return ptBuffer [zCY * zWidth + zCX];

}  /* getPixel() */


template <class TItem>
void TFrame<TItem>::printDebug (void) const
{

  cerr << TDebug::_indent() << "[_Frame_]" << endl;
  
  TDebug::_push();

  cerr << TDebug::_indent() << "Height : " << zHeight << endl;
  cerr << TDebug::_indent() << "Width  : " << zWidth << endl;

  TDebug::_pop();

}  /* printDebug() */

#endif  /* _FRAME__ */
