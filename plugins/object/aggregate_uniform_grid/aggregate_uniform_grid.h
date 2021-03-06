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

#ifndef _AGGREGATE_UNIFORM_GRID__
#define _AGGREGATE_UNIFORM_GRID__

#include "hlapi/aggregate.h"
#include "hlapi/plugin_manager.h"
#include "uniform_grid.h"

class TAggregateUniformGrid : public TAggregate
{

  protected:

    TObjectList     tObjectList2;    // For objects without bounding box
    TUniformGrid*   ptUniformGrid;
    TScalar         tVoxelSize;

  public:

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    TAggregateUniformGrid (void) :
      TAggregate()
    {
      ptUniformGrid = new TUniformGrid();
      tVoxelSize    = 0;
    }

    void add (TObject* ptOBJ);
      
    bool initialize (void);

    int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);

    bool findFirstIntersection (const TRay& rktRAY, TSurfaceData& rtDATA) const;

    void printDebug (void) const;

    string className (void) const { return "AggregateUniformGrid"; }

};  /* class TAggregateUniformGrid */

#endif  /* _AGGREGATE_UNIFORM_GRID__ */
