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

#include <dlfcn.h>
#include <fstream>
#include <iostream>
#include "hlapi/plugin_manager.h"

TPluginManager   tPluginManager;

// DEC OSF does not have this variable
#ifndef RTLD_GLOBAL
#define RTLD_GLOBAL 0
#endif

int TPluginManager::loadPlugin (const string& rktNAME)
{

  int                  iError;
  void*                pvHandle;
  const char*          pkcError;
  TRegisterFunction*   pfRegister;
  TPluginData*         ptPluginData;
  string               tAux = tPluginPath + rktNAME;

  pvHandle = dlopen (tAux.c_str(), RTLD_NOW | RTLD_GLOBAL);

  if ( !pvHandle )
  {
    cerr << "Cannot open plugin " << rktNAME << endl;
    cerr << dlerror() << endl;
    exit (1);
  }

  pfRegister = (TRegisterFunction*) dlsym (pvHandle, FX_REGISTER_PLUGIN);

  pkcError = dlerror();
  if ( pkcError )
  {
    cerr << "ERROR: " << pkcError << endl;
    dlclose (pvHandle);
    exit (1);
  }

  ptPluginData = new TPluginData();
  
  iError = (*pfRegister) (dwVersion, ptPluginData);

  if ( iError )
  {
    cerr << "Error registering plugin" << endl;
    dlclose (pvHandle);
    exit (1);
  }

  if ( ptPluginData->tPluginName != "" )
  {
    registerPlugin (ptPluginData);
  }

  return 0;

}  /* loadPlugin() */


void TPluginManager::initialize (const string& rktCONFIG_FILE, const string& rktPATH, DWord dwVERSION)
{

#if ( STATIC_LINK == 0 )

  ifstream   tFile;
  char       acPluginName [200];

  tPluginPath = rktPATH;
  dwVersion   = dwVERSION;

  tFile.open (rktCONFIG_FILE.c_str(), ios::in | ios::nocreate);

  while ( !tFile.eof() )
  {
    tFile.getline ((char*) acPluginName, 200);
    if ( strlen (acPluginName) > 0 )
    {
      loadPlugin (acPluginName);
    }
  }
  
#endif
  
}  /* initialize() */


int TPluginManager::registerPlugin (TPluginData* ptDATA)
{

  TPluginList::iterator   tIter;
  
  if ( tPluginDataMap.find (ptDATA->tPluginName) != tPluginDataMap.end() )
  {
    cerr << "ERROR: Plugin already loaded : " << ptDATA->tPluginName << endl;
    return -1;
  }

  tIter = tPluginList.find (ptDATA->eClass);

  if ( tIter != tPluginList.end() )
  {
    // Class already registered.
    (*tIter).second.push_back (ptDATA->tPluginName);
  }
  else
  {
    // Register class
    list<string>   tList;

    tList.push_back (ptDATA->tPluginName);
    tPluginList [ptDATA->eClass] = tList;
  }
               
  tPluginDataMap [ptDATA->tPluginName] = ptDATA;

  return 0;

}  /* registerPlugin() */


TBaseClass* TPluginManager::newObject (const string& rktCLASS, const TBaseClass* pktPARENT)
{

  TPluginData*               ptPluginData;
  TCreateFunction*           pfCreate;
  TPluginDataMap::iterator   tIter = tPluginDataMap.find (rktCLASS);
  
  if ( tIter == tPluginDataMap.end() )
  {
    return NULL;
  }

  ptPluginData = (*tIter).second;
  pfCreate     = ptPluginData->pfCreateFunction;

  return (*pfCreate) (pktPARENT);

}  /* newObject() */
