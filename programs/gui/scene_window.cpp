/*
*  Copyright (C) 1998 Angel Jimenez Jimenez
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
#include "llapi/math_tools.h"
#include "hlapi/scene_manager.h"
#include "scene_callbacks.h"
#include "scene_window.h"
#include "message_dialog.h"
#include <gtk--/fileselection.h>
#include <gtk--/box.h>
#include <gtk--/menu.h>
#include "common.h"

using SigC::slot;
using SigC::bind;

size_t TSceneWindow::_zWindows = 0;

TSceneWindow::TSceneWindow (Gtk::Main* ptMAIN)
{
  Gtk::VBox *ptVBox = manage(new Gtk::VBox);
  ptMain          = ptMAIN;
  ptFileSelection = NULL;
  ptScene         = NULL;
  ptTree          = NULL;
  gModified       = false;

  ptSWnd = new Gtk::ScrolledWindow;
  //  ptVBox->add (*ptSWnd);

  ptMenuBar = manage(new Gtk::MenuBar());
  using namespace Gtk::Menu_Helpers;
  MenuList* menu_list;
  Gtk::Menu* scene_menu = manage(new Gtk::Menu());
  Gtk::Menu* render_menu = manage(new Gtk::Menu());
  Gtk::Menu* objects_menu = manage(new Gtk::Menu());
  Gtk::Menu* windows_menu = manage(new Gtk::Menu());
  Gtk::Menu* help_menu = manage(new Gtk::Menu());      

  menu_list = &scene_menu->items();
  menu_list->push_back(MenuElem("_New window",ALT|'n',bind(slot(sceneNewCB),this)));
  menu_list->push_back(MenuElem("_Open",ALT|'o',bind(slot(sceneReplaceCB),this)));
  menu_list->push_back(MenuElem("_Save",ALT|'s',bind(slot(sceneMenuCB),"save")));
  menu_list->push_back(MenuElem("Save _as",ALT|'a',bind(slot(sceneMenuCB),"save as")));
  menu_list->push_back(MenuElem("_Close",ALT|'c',bind(slot(sceneCloseCB),this)));
  menu_list->push_back(SeparatorElem());
  menu_list->push_back(MenuElem("E_xit",ALT|'x',slot(sceneQuitCB)));

  menu_list = &render_menu->items();
  menu_list->push_back(MenuElem("_Render",ALT|'r',bind(slot(sceneRenderCB),this)));

  menu_list = &objects_menu->items();
  Gtk::Menu* tmp_menu = createPluginMenu(FX_CAMERA_CLASS,sceneCameraCB,this);
  menu_list->push_back(MenuElem("_Camera",*manage(tmp_menu)));
  tmp_menu = createPluginMenu(FX_LIGHT_CLASS,sceneLightCB,this);  
  menu_list->push_back(MenuElem("_Light",*manage(tmp_menu)));

  menu_list = &windows_menu->items();
  menu_list->push_back(MenuElem("_Material editor",ALT|'m',slot(sceneMaterialWindowCB)));
  menu_list->push_back(MenuElem("_Plugin list",ALT|'p',slot(scenePluginWindowCB)));  

  menu_list = &help_menu->items();
  menu_list->push_back(MenuElem("A_bout",bind(slot(sceneMenuCB),"about")));  

  // Add them to the bar...
  menu_list = &ptMenuBar->items();
  menu_list->push_back(MenuElem("_Scene",*scene_menu));
  menu_list->push_back(MenuElem("_Render",*render_menu));
  menu_list->push_back(MenuElem("_Objects",*objects_menu));
  menu_list->push_back(MenuElem("_Windows",*windows_menu));
  menu_list->push_back(MenuElem("_Help",*help_menu));      

  ptVBox->pack_start (*ptMenuBar, 0, 0, 0);
  ptVBox->pack_start (*ptSWnd, 1, 1, 0);  
  add(*ptVBox);
  
  show_all();
  
  set_usize (600, 400);

  setSceneFile();

  _zWindows++;

}  /* TSceneWindow() */


void TSceneWindow::setSceneFile (void)
{

  string   tTitle;
  string   tName;
  string   tFormat;

  if ( ptFileSelection )
  {
    tName = ptFileSelection->get_filename();
    ptFileSelection->hide();
    delete ptFileSelection;
    ptFileSelection = NULL;
  }
  
  if ( gModified )
  {
    // Save last scene file
    ptScene->finalize();
  }

  delete ptScene;

  if ( tName != "" )
  {
    tFormat = FileExtension (tName);

    if ( !TSceneManager::_knownFormat (tFormat) )
    {
      cout << "ERROR: Scene format not supported" << endl;
      exit (1);
    }
  
    ptScene = TSceneManager::_load (tName, tFormat);
  
    if ( ptScene )
    {
      setSensitive ("<Main>/Scene/Save", true);
      setSensitive ("<Main>/Scene/Save as", true);
      setSensitive ("<Main>/Scene/Close", true);
      setSensitive ("<Main>/Render/Render", true);
    }
  }
  else
  {
    ptScene = new TScene;
    
    setSensitive ("<Main>/Scene/Save", false);
    setSensitive ("<Main>/Scene/Save as", false);
    setSensitive ("<Main>/Scene/Close", false);
    setSensitive ("<Main>/Render/Render", false);
  }

  if ( tName == "" )
  {
    set_title ("Scene : <none>");
  }
  else
  {
    tTitle = string ("Scene - ") + tName;
    set_title (tTitle.c_str());
  }
  
  gModified  = false;
  tSceneName = tName;

  if ( ptTree )
  {
    ptTree->hide();
    ptSWnd->remove (); // (*ptTree);
    delete ptTree;
  }
  
  ptTree = new TSceneTree (ptScene);
  ptTree->show();

  ptSWnd->add_with_viewport (*ptTree);
}  /* setSceneFile() */


void TSceneWindow::openNewSceneWindow (void)
{

  TSceneWindow*   ptWnd;
  
  ptWnd = new TSceneWindow (ptMain);

  ptWnd->ptFileSelection = ptFileSelection;
  ptFileSelection        = NULL;
  
  ptWnd->show();

  ptWnd->setSceneFile();
  
}  /* openNewSceneWindow() */


bool TSceneWindow::setSensitive (const char* pkcPATH, bool gSENSITIVE)
{

#if FIXME
  Gtk::MenuPath*   ptMenuPath;

  if ( (ptMenuPath = ptMenuFactory->factory_find (pkcPATH)) != NULL )
  {
//    ptMenuPath->widget->set_sensitive (gSENSITIVE);
    return true;
  }

#endif /* FIXME */
  return false;
  
}  /* setSensitive() */
