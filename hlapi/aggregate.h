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

#ifndef _AGGREGATE__
#define _AGGREGATE__

#include <vector>
#include "hlapi/class_manager.h"
#include "llapi/object.h"

class TAggregate : public TObject
{

  protected:

    vector<TObject*>   tObjectList;

  public:

    TAggregate (void) :
      TObject() {}
      
    TAggregate (const TAggregate& rktAGGREGATE) :
      TObject()
    {
      copy (rktAGGREGATE.tObjectList);
    }

    TAggregate& operator = (const TAggregate& rktAGGREGATE)
    {
      copy (rktAGGREGATE.tObjectList);

      return *this;
    }

    virtual void copy (const vector<TObject*>& rktLIST)
    {
      for (vector<TObject*>::const_iterator iter = rktLIST.begin(); ( iter != rktLIST.end() ); iter++)
      {
        tObjectList.push_back ((TObject*) TClassManager::_newObject ((*iter)->className(), (TObject*) (*iter)));
      }
    }
      
    virtual void add (TObject* ptOBJ)
    {
      tObjectList.push_back (ptOBJ);
    }

    void setMaterial (TMaterial* ptMATERIAL);
    void setObjectCode (size_t zCODE);

    void initialize (void);

    bool findFirstIntersection (const TRay& rktRAY, TSurfaceData& rtDATA) const;
    bool findAllIntersections (const TRay& rktRAY, TSpanList& rtLIST) const;

    TVector normal (const TSurfaceData& rktDATA) const
    {
      return rktDATA.object()->normal (rktDATA);
    }

    vector<TObject*>* objectList (void)
    {
      return &tObjectList;
    }

    void getMesh (list<TMesh*>& rtMESH_LIST) const
    {
      for (vector<TObject*>::const_iterator tIter = tObjectList.begin(); ( tIter != tObjectList.end() ) ;tIter++)
      {
        (*tIter)->getMesh (rtMESH_LIST);
      }
    }
    
    void printDebug (void) const;

    EClass classType (void) const { return FX_AGGREGATE_CLASS; }
    string className (void) const { return "Aggregate"; }

};  /* class TAggregate */

#endif  /* _AGGREGATE__ */
