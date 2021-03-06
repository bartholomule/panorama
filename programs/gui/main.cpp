/*
*  Copyright (C) 1998, 1999 Angel Jimenez Jimenez
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

#include "llapi/file.h"
#include "hlapi/plugin_manager.h"
#include "hlapi/image_manager.h"
#include "hlapi/scene_manager.h"
#include "llapi/gradient.h"
#include "scene_window.h"

multimap<string, string>   tConfigData;

static string   _tTopDir;
static string   _tLocalPath;

#include "llapi/class_mgr_base.h"
#include "hlapi/class_manager.h"
TClassManagerBase* GlobalClassManager;

bool ProcessConfigFile (const string& rktCONFIG, multimap<string, string>& rtMAP)
{

  string     tOptionName, tOptionValue;
  ifstream   tConfigFile;
  char*      pcBuffer = new char[200];

  tConfigFile.open (rktCONFIG.c_str());
  if ( !tConfigFile )
  {
    return false;
  }

  // Reads configuration file line by line
  while ( !tConfigFile.eof() )
  {
    Byte   J;
    bool   gAppend;
    
    tOptionName  = "";
    tOptionValue = "";
    gAppend      = false;
    
    tConfigFile.getline (pcBuffer, 200);

    // Checks for an empty line
    if ( strlen (pcBuffer) == 0 )
    {
      continue;
    }
    
    // Checks for a comment
    if ( pcBuffer[0] == '#' )
    {
      continue;
    }
    
    // Gets option name (until the first occurrence of character '=')
    for (J = 0; ( ( J < strlen (pcBuffer) ) && ( pcBuffer[J] != '=' ) ) ;J++)
    {
      tOptionName += pcBuffer[J];
    }

    // Checks if the line contains no '=' character
    if ( J == strlen (pcBuffer) )
    {
      continue;
    }
    
    // Checks if we are adding a new value for that option, or substituting previous ones
    if ( ( J > 0 ) && ( pcBuffer[J - 1] == '+' ) )
    {
      tOptionName = tOptionName.substr (0, J - 1);
      gAppend     = true;
    }
         
    // Gets option value (until the end of the line)
    for (J++; ( J < strlen (pcBuffer) ) ;J++)
    {
      tOptionValue += pcBuffer[J];
    }

    if ( !gAppend )
    {
      // Removes every previous option with the same name
      multimap<string, string>::iterator   iter;
      
      while ( (iter = rtMAP.find (tOptionName)) != rtMAP.end() )
      {
        rtMAP.erase (iter);
      }
    }

    // Inserts a new option entry in the map
    rtMAP.insert (pair<const string, string> (tOptionName, tOptionValue));
  }

  tConfigFile.close();
  delete pcBuffer;
  
  return true;
  
}  /* ProcessConfigFile() */


void SetPaths (void)
{
  
  char*   pcEnv;

  _tTopDir = TOPDIR;

  if ( (pcEnv = getenv ("HOME")) != NULL )
  {
    _tLocalPath = string (pcEnv) + "/.panorama/";
    if ( !FileExists (_tLocalPath + "config") )
    {
      _tLocalPath = _tTopDir + "/etc/";
    }
  }
  else
  {
    _tLocalPath = _tTopDir + "/etc/";
  }

}  /* SetPaths() */


int main (int argc, char *argv[])
{

  Gtk::Main      tMainApp (&argc, &argv);
  string         appname = string ("Panorama");
  string         appid = string ("0.0.5");

  GlobalClassManager = new TClassManager();

  SetPaths();

  if ( !FileExists (_tLocalPath + "config") )
  {
    cerr << "WARNING: No configuration file." << endl;
  }
  else
  {
    if ( !ProcessConfigFile (_tLocalPath + "config", tConfigData) )
    {
      cerr << "ERROR: Couldn't read configuration file." << endl;
      exit (1);
    }
  }

  multimap<string, string>::const_iterator   iter = tConfigData.find ("PluginConfigFile");
  string   tPluginConfigFile = ( iter != tConfigData.end() ) ? (*iter).second : _tLocalPath + "pluginrc";

  if ( !FileExists (tPluginConfigFile) )
  {
    cerr << "ERROR: Plugin configuration file '" << tPluginConfigFile << "' does not exist." << endl;
    exit (1);
  }

  cout << "Loading plugins..." << endl;
  tPluginManager.initialize (tPluginConfigFile, 0);

  TGradient::_initialize();
  TImageManager::_initialize();
  TSceneManager::_initialize();
  tImageManager.initialize();

  TSceneWindow   tMainWindow (&tMainApp);
  tMainWindow.show();
  
  tMainApp.run();

  delete GlobalClassManager;
  
  return 0;

}  /* main() */
