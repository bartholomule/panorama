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

#include "llapi/warning_eliminator.h"
#if defined(STATIC_LINK) && ( STATIC_LINK == 0 )
#include <dlfcn.h>
#endif

#include <fstream>
#include <iostream>
#include "llapi/file.h"
#include "hlapi/plugin_manager.h"

extern multimap<string, string>   tConfigData;

TPluginManager   tPluginManager;

// DEC OSF does not have this variable
#ifndef RTLD_GLOBAL
#define RTLD_GLOBAL 0
#endif

int TPluginManager::loadPlugin (const string& rktNAME)
{
#if ( STATIC_LINK == 0 )

  int                  iError;
  const char*          pkcError;
  TRegisterFunction*   pfRegister;
  TPluginData*         ptPluginData;
  void*                pvHandle      = NULL;
  bool                 gAbsolutePath = ( rktNAME[0] == '/' );

  if ( gAbsolutePath )
  {
    pvHandle = dlopen (rktNAME.c_str(), RTLD_NOW | RTLD_GLOBAL);
  }
  else
  {
    multimap<string, string>::const_iterator   iter;

    iter = tConfigData.find ("PluginPath");
    while ( ( iter != tConfigData.end() ) && ( (*iter).first == "PluginPath" ) )
    {
      string   tAux (iter->second + '/' + rktNAME);
      
      if ( FileExists (tAux) )
      {
        pvHandle = dlopen (tAux.c_str(), RTLD_NOW | RTLD_GLOBAL);
        break;
      }
      iter++;
    }
  }
  
  if ( !pvHandle )
  {
    cerr << "Cannot open plugin " << rktNAME << endl;
    cerr << dlerror() << endl;
  }
  else
  {
    pfRegister = (TRegisterFunction*) dlsym (pvHandle, FX_REGISTER_PLUGIN);
  
    pkcError = dlerror();
    if ( pkcError )
    {
      cerr << "ERROR: " << pkcError << endl;
      dlclose (pvHandle);
    }
    else
    {
      static string filler;
      if(rktNAME.length() > filler.length())
      {
	filler.insert(filler.begin(),
		      rktNAME.length() - filler.length(),
		      ' ');
      }
	
      ptPluginData = new TPluginData();
    
      iError = (*pfRegister) (dwVersion, ptPluginData);
    
      if ( iError )
      {
        cerr << "Error registering plugin" << endl;
        dlclose (pvHandle);
      }
      else
      {
	cerr << "Loading plugin "
	     << rktNAME
	     << filler.substr(0,max(filler.length() - rktNAME.length(),(size_t)1))
	     << "\r"
	     << flush;
	registerPlugin (ptPluginData);
      }
    }
  }
  
#endif

  return 0;

}  /* loadPlugin() */


bool TPluginManager::initialize (const string& rktCONFIG_FILE, DWord dwVERSION)
{

#if defined(DEBUG)
#if defined(__PRETTY_FUNCTION__)
  cout << __PRETTY_FUNCTION__ << endl;
#elif defined(__FUNCTION__)
  cout << __FUNCTION__ << endl;
#elif defined(__FUNCTION)
#endif /* defined(__PRETTY_FUNCTION__) */
#endif /* defined(DEBUG) */
  bool val = true;
#if ( STATIC_LINK == 0 )

  ifstream   tFile;
  char       acPluginName [200];

  dwVersion = dwVERSION;

  tFile.open (rktCONFIG_FILE.c_str(), ios::in);

  while ( !tFile.eof() )
  {
    tFile.getline ((char*) acPluginName, 200);

    if ( strlen (acPluginName) == 0 )
    {
      continue;
    }
    
    if ( acPluginName[0] == '#' )
    {
      continue;
    }

    loadPlugin (acPluginName);
  }
  
#endif
  return val;
}  /* initialize() */


int TPluginManager::registerPlugin (TPluginData* ptDATA)
{

  TPluginList::iterator   tIter;
  
  if ( tPluginDataMap.find (ptDATA->tPluginName) != tPluginDataMap.end() )
  {
    cerr << "ERROR: Plugin already loaded : \"" << ptDATA->tPluginName << "\""<< endl;
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
