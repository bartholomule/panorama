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

#include "llapi/warning_eliminator.h"
#include <ctime>
#include <iostream>
#include "llapi/file.h"
#include "llapi/scene.h"
#include "llapi/gradient.h"
#include "hlapi/plugin_manager.h"
#include "hlapi/image_manager.h"
#include "hlapi/scene_manager.h"
#include "llapi/file.h"

multimap<string, string>   tConfigData;

static string   _tInputFileName;
static string   _tInputFileFormat;
static string   _tProgramName;
static string   _tTopDir;
static string   _tLogFileName;
static string   _tLocalPath;
static bool     _gKeepLog = false;

void DisplayHelp (void)
{

  cout << "Usage: " << _tProgramName << " input_file" << endl;

}  /* DisplayHelp() */


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

    if( tOptionValue[0] != '/' )
    {
      tOptionValue = _tLocalPath + tOptionValue;
    }

    // Inserts a new option entry in the map
    rtMAP.insert (pair<const string, string> (tOptionName, tOptionValue));
  }

  tConfigFile.close();
  delete pcBuffer;
  
  return true;
  
}  /* ProcessConfigFile() */


void ProcessCommandLine (int argc, char* argv[])
{

  if ( argc <= 1 )
  {
    DisplayHelp();
    exit (0);
  }
  else
  {
    _tInputFileName   = argv [1];
    _tInputFileFormat = FileExtension (_tInputFileName);

    cout << "File : " << _tInputFileName << endl;
    cout << "Type : " << _tInputFileFormat << endl;
  }

}  /* ProcessCommandLine() */


void SetPaths (void)
{
  
  char*   pcEnv;

  pcEnv = getenv ("PANORAMA");

  if ( pcEnv )
  {
    _tTopDir = FilenameConvert(pcEnv);
  }
  else
  {
    _tTopDir = FilenameConvert(TOPDIR);
  }

  if ( (pcEnv = getenv ("HOME")) != NULL )
  {
    _tLocalPath = FilenameConvert(string (pcEnv) + "/.panorama/");
    if ( !FileExists (_tLocalPath + "config") )
    {
      _tLocalPath = FilenameConvert(_tTopDir + "/etc/");
    }
  }
  else
  {
    _tLocalPath = FilenameConvert(_tTopDir + "/etc/");
  }

  _tLogFileName = FilenameConvert(_tLocalPath + "panorama.log");
  _gKeepLog     = true;

}  /* SetPaths() */


bool FinishedLine (size_t zLINE, void* pvDATA)
{

  cout << "[" << zLINE << "]\r" << flush;
  
  return true;

}  /* FinishedLine() */


int main (int argc, char *argv[])
{

  ofstream   tLogFile;
  TScene*    ptScene;
  char       acTimeString [30];
  time_t     tBaseTime, tInitTime, tRenderTime, tPostProcessTime;

  _tProgramName = "render";

  ProcessCommandLine (argc, argv);

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

//  for (multimap<string, string>::const_iterator iter = tConfigData.begin(); ( iter != tConfigData.end() ) ;iter++)
//  {
//    cout << (*iter).first << " = " << (*iter).second << endl;
//  }
  
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

  if ( !TSceneManager::_knownFormat (_tInputFileFormat) )
  {
    cout << "ERROR: Scene format not supported" << endl;
    exit (1);
  }
  
  cout << "Parsing..." << endl;
  ptScene = TSceneManager::_load (_tInputFileName, _tInputFileFormat);
  cout << "Scene loaded..." << endl;

  if ( !ptScene )
  {
    cerr << "Error parsing input file" << endl;
    exit (1);
  }

  //
  // Uncomment next line for debug information on the whole scene.
  //
  ptScene->printDebug("");

  tBaseTime = time (NULL);

  cout << "Initializing..." << endl;
  if(!ptScene->initialize())
  {
    cerr << "Initialization failed!" << endl;
    exit (1);
  }
  ptScene->printDebug("#");  
  tInitTime = time (NULL);

  cout << "Rendering..." << endl;
  ptScene->render (&FinishedLine);
  tRenderTime = time (NULL);
  
  cout << "Postprocessing..." << endl;
  ptScene->postprocess();
  tPostProcessTime = time (NULL);
  
  cout << "Saving..." << endl;
  if ( !ptScene->saveImage() )
  {
    cout << "Could not save image file" << endl;
  }
  
  ptScene->finalize();

  cout << endl;
  cout << " Total ellapsed time : " << difftime (tPostProcessTime, tBaseTime) << " secs" << endl;
  cout << " - Initialization . . . " << difftime (tInitTime, tBaseTime) << " secs" << endl;
  cout << " - Render         . . . " << difftime (tRenderTime, tInitTime) << " secs" << endl;
  cout << " - Postprocessing . . . " << difftime (tPostProcessTime, tRenderTime) << " secs" << endl;
  cout << "";

  if ( _gKeepLog )
  {
    strftime (acTimeString, 30, "%b %d %H:%M:%S", localtime (&tBaseTime));
    
    tLogFile.open (_tLogFileName.c_str(), ios::out | ios::binary | ios::app);

    tLogFile << acTimeString << " " << _tInputFileName << ", " << difftime (tPostProcessTime, tBaseTime) << " seconds" << endl;

    tLogFile.close();
  }

  return 0;

}  /* main() */
