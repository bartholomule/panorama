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

#ifndef _PROCEDURAL__
#define _PROCEDURAL__

#include "llapi/base_class.h"
#include "llapi/program.h"
#include "llapi/user_functions.h"

#define FX_ATTRIB_OK             0
#define FX_ATTRIB_WRONG_PARAM   -1
#define FX_ATTRIB_WRONG_TYPE    -2
#define FX_ATTRIB_WRONG_VALUE   -3
#define FX_ATTRIB_USER_ERROR     1

// These flags are reserved for internal use only
#define FX_RESERVED_FLAG_0       0
#define FX_RESERVED_FLAG_1       1
#define FX_RESERVED_FLAG_2       2
#define FX_RESERVED_FLAG_3       3
#define FX_RESERVED_FLAG_4       4
#define FX_RESERVED_FLAG_5       5
#define FX_RESERVED_FLAG_6       6
#define FX_RESERVED_FLAG_7       7

typedef map<string, EAttribType, less<string> >    TAttributeList;
typedef map<string, void*, less<string> >          TUserDataMap;
typedef map<string, magic_pointer<user_function> > TUserFunctionMap;

class TProcedural : public TBaseClass
{

  protected:

    TProgram       tProgram;
    string         tIdentifier;
    DWord          dwFlags;
    TUserDataMap   tUserDataMap;
    
  public:

    static string   _tUserErrorMessage;

    virtual bool initialize (void) { return true; }
  
    // Identifier management
    void setIdentifier (const string& rktIDENT)
    {
      tIdentifier = rktIDENT;
    }

    string identifier (void) const
    {
      return tIdentifier;
    }
                       
    // Flags management
    DWord flags (void) const
    {
      return dwFlags;
    }

    void setFlags (DWord dwFLAGS)
    {
      dwFlags = dwFLAGS;
    }

    void setFlag (Byte bPOS)
    {
      assert ( bPOS < 32 );
      
      dwFlags |= (1 << bPOS);
    }
    
    void resetFlag (Byte bPOS)
    {
      assert ( bPOS < 32 );
      
      dwFlags &= ~(1 << bPOS);
    }

    bool getFlag (Byte bPOS)
    {
      assert ( bPOS < 32 );
      
      return !!( dwFlags & (1 << bPOS) );
    }
    
    // User data map management
    void addUserData (const string& rktNAME, void* pDATA)
    {
      tUserDataMap[rktNAME] = pDATA;
    }

    void* removeUserData (const string& rktNAME)
    {
      void*                    pRet;
      TUserDataMap::iterator   iter = tUserDataMap.find (rktNAME);

      if ( iter == tUserDataMap.end() )
      {
        return NULL;
      }
      else
      {
        pRet = (*iter).second;

        tUserDataMap.erase (iter);
        
        return pRet;
      }
    }

    void* userData (const string& rktNAME) const
    {
      TUserDataMap::const_iterator   iter = tUserDataMap.find (rktNAME);

      if ( iter == tUserDataMap.end() )
      {
        return NULL;
      }
      else
      {
        return (*iter).second;
      }
    }
    
    // Attribute management
  virtual int setAttribute (const string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);

#if defined(NEW_ATTRIBUES)
  // This version will call the above function with the proper type (if it can
  // be determined).  Otherwise, it will set the error message and return an
  // error flag.  It will only work with the new atributes.
  virtual int setAttribute (const string& rktNAME, NAttribute nVALUE);
  virtual int setAttribute (const string& rktNAME, const list<NAttribute>& rktLIST);  
#endif

  virtual int setAttribute (const string& rktNAME, const list<NAttribute>& rktLIST, EAttribType eTYPE);
  
  virtual int getAttribute (const string& rktNAME, NAttribute& rnVALUE);
  virtual void getAttributeList (TAttributeList& rtLIST) const;


  virtual TUserFunctionMap getUserFunctions();
  
    // Event management
    void sendEvent (const string& rktEVENT);
    void sendEvent (const string& rktEVENT, NAttribute nAttrib);

    TProgram* program (void) { return &tProgram; }
  
};  /* class TProcedural */

#endif  /* _PROCEDURAL__ */
