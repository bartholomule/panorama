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

#ifndef _PLUGIN_MANAGER__
#define _PLUGIN_MANAGER__

#include <map>
#include "llapi/machine.h"
#include "llapi/base_class.h"
#include "llapi/scene.h"

#define FX_REGISTER_PLUGIN            "_registerPlugin"

#if ( STATIC_LINK == 0 )

#define DEFINE_PLUGIN(NAME, CLASS, TYPE) \
  extern "C" int _registerPlugin (DWord dwVERSION, TPluginData* ptDATA) \
  { \
    ptDATA->tPluginName      = NAME; \
    ptDATA->eClass           = CLASS; \
    ptDATA->pfCreateFunction = &TYPE::_create; \
    return 0; \
  } \
  \
  TBaseClass* TYPE::_create (const TBaseClass* pktPARENT) \
  { \
    if ( pktPARENT ) \
    { \
      return new TYPE (*((TYPE*) pktPARENT)); \
    } \
    return new TYPE(); \
  }

#define DEFINE_SCENE_IO_PLUGIN(NAME, TYPE) \
  extern "C" int _registerPlugin (DWord dwVERSION, TPluginData* ptDATA) \
  { \
    TSceneManager::_addFormat (NAME, &TYPE::_load, &TYPE::_save); \
    return 0; \
  }

#define DEFINE_IMAGE_IO_PLUGIN(NAME, TYPE) \
  extern "C" int _registerPlugin (DWord dwVERSION, TPluginData* ptDATA) \
  { \
    TImageManager::_addFormat (NAME, &TYPE::_create); \
    return 0; \
  } \
  \
  TBaseClass* TYPE::_create (const TBaseClass* pktPARENT) \
  { \
    if ( pktPARENT ) \
    { \
      return new TYPE (*((TYPE*) pktPARENT)); \
    } \
    return new TYPE(); \
  }

#define DEFINE_IMAGE_IO_PLUGIN_WITH_ALIAS(NAME, ALIAS, TYPE) \
  extern "C" int _registerPlugin (DWord dwVERSION, TPluginData* ptDATA) \
  { \
    TImageManager::_addFormat (NAME, &TYPE::_create, ALIAS); \
    return 0; \
  } \
  \
  TBaseClass* TYPE::_create (const TBaseClass* pktPARENT) \
  { \
    if ( pktPARENT ) \
    { \
      return new TYPE (*((TYPE*) pktPARENT)); \
    } \
    return new TYPE(); \
  }

#else

#define DEFINE_PLUGIN(NAME, CLASS, TYPE)
#define DEFINE_SCENE_IO_PLUGIN(NAME, TYPE)
#define DEFINE_IMAGE_IO_PLUGIN(NAME, TYPE) \
  TBaseClass* TYPE::_create (const TBaseClass* pktPARENT) \
  { \
    if ( pktPARENT ) \
    { \
      return new TYPE (*((TYPE*) pktPARENT)); \
    } \
    return new TYPE(); \
  }
#define DEFINE_IMAGE_IO_PLUGIN_WITH_ALIAS(NAME, ALIAS, TYPE) \
  TBaseClass* TYPE::_create (const TBaseClass* pktPARENT) \
  { \
    if ( pktPARENT ) \
    { \
      return new TYPE (*((TYPE*) pktPARENT)); \
    } \
    return new TYPE(); \
  }

#endif

struct TPluginData;

typedef TBaseClass* (TCreateFunction)(const TBaseClass*);
typedef int (TRegisterFunction)(DWord, TPluginData*);

struct TPluginData
{

  //
  // Data set by plugin
  //
  string             tPluginName;
  EClass             eClass;
  TCreateFunction*   pfCreateFunction;

};  /* struct TPluginData */

typedef map<string, TPluginData*, less<string> >   TPluginDataMap;
typedef map<EClass, list<string>, less<EClass> >   TPluginList;

class TPluginManager
{

  protected:

    DWord            dwVersion;
    TPluginDataMap   tPluginDataMap;
    TPluginList      tPluginList;

    int loadPlugin (const string& rktNAME);

  public:

    bool initialize (const string& rktCONFIG_FILE, DWord dwVERSION);

    int registerPlugin (TPluginData* ptDATA);

    TPluginList* pluginList (void) { return &tPluginList; }
      
    TBaseClass* newObject (const string& rktCLASS, const TBaseClass* pktPARENT = NULL);

};  /* class TPluginManager */

extern TPluginManager   tPluginManager;

#endif  /* _PLUGIN_MANAGER__ */
