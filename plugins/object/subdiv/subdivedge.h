/*
*  Copyright (C) 1998 Matt Kimball
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

#ifndef _SUBDIVEDGE__
#define _SUBDIVEDGE__

#include <map>

class TSubdivVert;
class TSubdivFace;

class TSubdivEdge
{

  protected:

    struct TVertPair
    {
      TSubdivVert*   ptFirst;
      TSubdivVert*   ptSecond;
    };

    struct TVertPairCompare : public std::binary_function<TVertPair, TVertPair, bool>
    {
      bool operator() (const TVertPair& rktFIRST, const TVertPair& rktSECOND) const;
    };

    static std::map<TVertPair, TSubdivEdge*, TVertPairCompare>   _tEdgeMap;

    TSubdivEdge (TSubdivVert *ptFIRST, TSubdivVert *ptSECOND);

  public:

    TSubdivVert*   ptEdgePoint;
    TSubdivVert*   ptFirstVert;
    TSubdivVert*   ptSecondVert;
    TSubdivFace*   ptFirstFace;
    TSubdivFace*   ptSecondFace;

    static TSubdivEdge* _findEdge (TSubdivVert* ptFIRST, 
                                   TSubdivVert* ptSECOND);

    TSubdivVert* otherVert (const TSubdivVert* pktVERT) const;
    TSubdivFace* otherFace (const TSubdivFace* pktFACE) const;

    TSubdivVert* findPoint();

    void addFace (TSubdivFace *ptFACE);

};  /*  class TSubdivEdge  */

#endif  /* _SUBDIVEDGE__ */
