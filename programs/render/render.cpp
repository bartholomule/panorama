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

#include <ctime>
#include <iostream>
#include "llapi/file.h"
#include "llapi/scene.h"
#include "llapi/gradient.h"
#include "hlapi/plugin_manager.h"
#include "hlapi/image_manager.h"
#include "hlapi/scene_manager.h"

static string   _tInputFileName;
static string   _tInputFileFormat;
static string   _tProgramName;
static string   _tTopDir;
static string   _tPluginPath;
static string   _tTexturePath;
static string   _tGradientPath;
static string   _tLogFileName;
static string   _tLocalPath;
static bool     _gKeepLog = false;

void DisplayHelp (void)
{

  cout << "Usage: " << _tProgramName << " input_file" << endl;

}  /* DisplayHelp() */


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

  _tTopDir       = TOPDIR;
  _tPluginPath   = PLUGIN_DIR;
  _tTexturePath  = TEXTURE_DIR;
  _tGradientPath = GRADIENT_DIR;

  TScene::_tIncludePath = INCLUDE_DIR;
  
  if ( (pcEnv = getenv ("HOME")) != NULL )
  {
    _tLocalPath = string (pcEnv) + "/.panorama/";
    if ( !FileExists (_tLocalPath + "pluginrc") )
    {
      _tLocalPath = _tTopDir + "/etc/";
    }
  }
  else
  {
    _tLocalPath = _tTopDir + "/etc/";
  }

  _tLogFileName = _tLocalPath + "panorama.log";
  _gKeepLog     = true;

}  /* SetPaths() */


void FinishedLine (size_t zLINE, void* pvDATA)
{

  cout << "[" << zLINE << "]\r" << flush;

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

  if ( !FileExists (_tLocalPath + "pluginrc") )
  {
    cerr << "ERROR: Plugin configuration file does not exist." << endl;
    exit (1);
  }

  cout << "Loading plugins..." << endl;
  tPluginManager.initialize (_tLocalPath + "pluginrc", _tPluginPath, 0);

  TGradient::_initialize (_tGradientPath);
  TImageManager::_initialize();
  TSceneManager::_initialize();
  tImageManager.initialize (_tTexturePath);

  if ( !TSceneManager::_knownFormat (_tInputFileFormat) )
  {
    cout << "ERROR: Scene format not supported" << endl;
    exit (1);
  }
  
  cout << "Parsing..." << endl;
  ptScene = TSceneManager::_load (_tInputFileName, _tInputFileFormat);

  if ( !ptScene )
  {
    cerr << "Error parsing input file" << endl;
    exit (1);
  }

  //
  // Uncomment next line for debug information on the whole scene.
  //
//  ptScene->printDebug();

  tBaseTime = time (NULL);

  cout << "Initializing..." << endl;
  ptScene->initialize();
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
    
    tLogFile.open (_tLogFileName.c_str(), ios::out | ios::bin | ios::app);

    tLogFile << acTimeString << " " << _tInputFileName << ", " << difftime (tPostProcessTime, tBaseTime) << " seconds" << endl;

    tLogFile.close();
  }

  return 0;

}  /* main() */
