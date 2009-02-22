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

std::multimap<std::string, std::string>   tConfigData;

static std::string   _tTopDir;
static std::string   _tLocalPath;

bool ProcessConfigFile (const std::string& rktCONFIG, std::multimap<std::string, std::string>& rtMAP)
{

  std::string     tOptionName, tOptionValue;
  std::ifstream   tConfigFile;
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
      std::multimap<std::string, std::string>::iterator   iter;

      while ( (iter = rtMAP.find (tOptionName)) != rtMAP.end() )
      {
        rtMAP.erase (iter);
      }
    }

    // Inserts a new option entry in the map
    rtMAP.insert (std::pair<const std::string, std::string> (tOptionName, tOptionValue));
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
    _tLocalPath = std::string (pcEnv) + "/.panorama/";
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

  SetPaths();

  if ( !FileExists (_tLocalPath + "config") )
  {
    GOM.error() << "WARNING: No configuration file." << std::endl;
  }
  else
  {
    if ( !ProcessConfigFile (_tLocalPath + "config", tConfigData) )
    {
      GOM.error() << "ERROR: Couldn't read configuration file." << std::endl;
      exit (1);
    }
  }

  std::multimap<std::string, std::string>::const_iterator   iter = tConfigData.find ("PluginConfigFile");
  std::string   tPluginConfigFile = ( iter != tConfigData.end() ) ? (*iter).second : _tLocalPath + "pluginrc";

  if ( !FileExists (tPluginConfigFile) )
  {
    GOM.error() << "ERROR: Plugin configuration file '" << tPluginConfigFile << "' does not exist." << std::endl;
    exit (1);
  }

  GOM.out() << "Loading plugins..." << std::endl;
  tPluginManager.initialize (tPluginConfigFile, 0);

  TGradient::_initialize();
  TImageManager::_initialize();
  TSceneManager::_initialize();
  tImageManager.initialize();

  TSceneWindow   tMainWindow ();

  Gtk::Main::run();

  return 0;

}  /* main() */
