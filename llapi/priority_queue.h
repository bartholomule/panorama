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

#ifndef _PRIORITY_QUEUE__
#define _PRIORITY_QUEUE__

#include <cassert>
#include <iostream>
#include "llapi/llapi_defs.h"

#define PARENT(K) ((K) / 2)
#define LEFT_SON(K) ((K) + (K))
#define RIGHT_SON(K) ((K) + (K) + 1)

template <class TItem>
struct TPQNode
{
  
  TItem     tData;
  TScalar   tDistance;

  TPQNode (const TItem& rktITEM, TScalar tDIST) :
    tData (rktITEM),
    tDistance (tDIST) {}
  
};  /* struct TPQNode */


template <class TItem>
class TPriorityQueue
{

  protected:

    float*   afPriority;
    TItem*   atData;
    size_t   zSize;
    size_t   zMaxSize;
    
    void upHeap (size_t zPOS);
    void downHeap (size_t zPOS);
    void replace (const TItem& rktITEM, float fPRIORITY);
    
  public:

    TPriorityQueue (size_t zSIZE);

    ~TPriorityQueue (void)
    {
      delete[] atData;
      delete[] afPriority;
    }

    void insert (const TItem& rktITEM, float fPRIORITY);

    size_t size (void) const
    {
      return zSize;
    }

    bool full (void) const
    {
      return ( zSize == zMaxSize );
    }

    TPQNode<TItem> operator [] (size_t zPOS)
    {
      return TPQNode<TItem> (atData [zPOS + 1], afPriority [zPOS + 1]);
    }

    void printDebug (const std::string& indent) const;
    
};  /* class TPriorityQueue */


template <class TItem>
void TPriorityQueue<TItem>::replace (const TItem& rktITEM, float fPRIORITY)
{

  afPriority[0] = fPRIORITY;
  atData[0]     = rktITEM;

  downHeap (0);

}  /* replace() */


template <class TItem>
TPriorityQueue<TItem>::TPriorityQueue (size_t zSIZE) :
  zSize (0),
  zMaxSize (zSIZE)
{

  atData     = new TItem [zSIZE + 1];
  afPriority = new float [zSIZE + 1];
  
}  /* TPriorityQueue() */


template <class TItem>
void TPriorityQueue<TItem>::insert (const TItem& rktITEM, float fPRIORITY)
{

  if ( zSize == zMaxSize )
  {
    replace (rktITEM, fPRIORITY);
  }
  else
  {
    zSize++;

    afPriority [zSize] = fPRIORITY;
    atData [zSize]     = rktITEM;

    upHeap (zSize);
  }

}  /* insert() */


template <class TItem>
void TPriorityQueue<TItem>::upHeap (size_t zPOS)
{

  float   fPriority = afPriority [zPOS];
  TItem   tData     = atData [zPOS];

  while ( zPOS > 1 )
  {
    if ( afPriority [PARENT (zPOS)] >= fPriority )
    {
      break;
    }
    else
    {
      afPriority [zPOS] = afPriority [PARENT (zPOS)];
      atData [zPOS]     = atData [PARENT (zPOS)];
      zPOS              = PARENT (zPOS);
    }
  }

  afPriority [zPOS] = fPriority;
  atData [zPOS]     = tData;
  
}  /* upHeap() */


template <class TItem>
void TPriorityQueue<TItem>::downHeap (size_t zPOS)
{

  size_t   j;
  float    fPriority = afPriority [zPOS];
  TItem    tData     = atData [zPOS];

  while ( zPOS <= (zSize / 2) )
  {
    j = LEFT_SON (zPOS);
    if ( ( j < zSize ) && ( afPriority [j] < afPriority [j + 1] ) )
    {
      j++;
    }
    if ( fPriority >= afPriority [j] )
    {
      break;
    }
    afPriority [zPOS] = afPriority [j];
    atData [zPOS]     = atData [j];
    zPOS              = j;
  }

  afPriority [zPOS] = fPriority;
  atData [zPOS]     = tData;
  
}  /* downHeap() */


template <class TItem>
void TPriorityQueue<TItem>::printDebug (const std::string& indent) const
{

  GOM.debug(indent + "[_TPriorityQueue_]") << std::endl;

  std::string new_indent = indent + TDebug::StandardIndent();
  
  for (size_t J = 1; ( J <= zSize ) ;J++)
  {
    std::string tString;
    tString << atData[J] + ", " << afPriority[J];
    GOM.debug(new_indent + tString) << std::endl;
  }
  
}  /* printDebug() */

#endif  /* _PRIORITY_QUEUE__ */
