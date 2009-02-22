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
#include <gtkmm/fileselection.h>
#include <gtkmm/box.h>
#include <gtkmm/menu.h>
#include <gtkmm/stock.h>
#include "common.h"

size_t TSceneWindow::window_count = 0;

TSceneWindow::TSceneWindow (Gtk::Main* ptMAIN)
{
  Gtk::VBox *ptVBox = manage(new Gtk::VBox);
  ptFileSelection = NULL;
  ptScene.set(NULL);
  ptTree          = NULL;
  gModified       = false;

  ptSWnd = new Gtk::ScrolledWindow;
  //  ptVBox->add (*ptSWnd);

  action_group = Gtk::ActionGroup::create();

  action_group->add(Gtk::Action::create("SceneNewWindow", Gtk::Stock::NEW, "_New window"),
		    sigc::bind(sigc::mem_fun(*this, &TSceneWindow::unimplemented),
			       "New"));

  action_group->add(Gtk::Action::create("SceneOpen", Gtk::Stock::OPEN, "_Open"),
		    sigc::bind(sigc::mem_fun(*this, &TSceneWindow::unimplemented),
			       "Open"));

  action_group->add(Gtk::Action::create("SceneSave", Gtk::Stock::SAVE, "_Save"),
		    sigc::bind(sigc::mem_fun(*this, &TSceneWindow::unimplemented),
			       "Save"));

  action_group->add(Gtk::Action::create("SceneSaveAs", Gtk::Stock::SAVE_AS, "Save _as"),
		    sigc::bind(sigc::mem_fun(*this, &TSceneWindow::unimplemented),
			       "Save As"));

  action_group->add(Gtk::Action::create("SceneClose", Gtk::Stock::CLOSE, "_Close"),
		    sigc::bind(sigc::mem_fun(*this, &TSceneWindow::unimplemented),
			       "Close"));

  action_group->add(Gtk::Action::create("SceneExit", Gtk::Stock::QUIT, "E_xit"),
		    sigc::bind(sigc::mem_fun(*this, &TSceneWindow::unimplemented),
			       "Exit"));

  action_group->add(Gtk::Action::create("Render", "_Render"),
		    sigc::bind(sigc::mem_fun(*this, &TSceneWindow::unimplemented),
			       "Render"));

  action_group->add(Gtk::Action::create("MaterialEditor", "_Material editor"),
		    sigc::bind(sigc::mem_fun(*this, &TSceneWindow::unimplemented),
			       "Material editor"));

  action_group->add(Gtk::Action::create("PluginList", "_Plugin list"),
		    sigc::bind(sigc::mem_fun(*this, &TSceneWindow::unimplemented),
			       "Plugin list"));

  action_group->add(Gtk::Action::create("HelpAbout", Gtk::Stock::HELP, "_About"),
		    sigc::bind(sigc::mem_fun(*this, &TSceneWindow::unimplemented),
			       "About"));

  Glib::ustring menu_xml =
    "<ui>"
    "  <menubar name='Menu'>"
    "    <menu action='SceneMenu'>"
    "      <menu action='SceneNewWindow'/>"
    "      <menu action='SceneOpen'/>"
    "      <menu action='SceneSave'/>"
    "      <menu action='SceneSaveAs'/>"
    "      <menu action='SceneClose'/>"
    "      <menu action='SceneExit'/>"
    "    </menu>"
    "    <menu action='RenderMenu'>"
    "      <menu action='Render'/>"
    "    </menu>"
    "    <menu action='ObjectsMenu'>"
    "      <menu action='Camera'/>"
    "      <menu action='Light'/>"
    "    </menu>"
    "    <menu action='WindowsMenu'>"
    "      <menu action='MaterialEditor'/>"
    "      <menu action='PluginList'/>"
    "    </menu>"
    "    <menu action='HelpMenu'>"
    "      <menu action='HelpAbout'/>"
    "    </menu>"
    "  </menubar>"
    "</ui>";

  try
  {
    ui_manager->add_ui_from_string(menu_xml);
  }
  catch(const Glib::Error& ex)
  {
    std::cerr << "building menus failed: " <<  ex.what();
  }

  //Get the menubar and add it to a container widget:
  Gtk::Widget* menu_bar = ui_manager->get_widget("/Menu");
  if(menu_bar)
  {
    ptVBox->pack_start(*menu_bar, Gtk::PACK_SHRINK);
  }

  // FIXME! Get the proper menu entries for cameras, objects, lights
  /*
  Gtk::Menu* tmp_menu = createPluginMenu(FX_CAMERA_CLASS,sceneCameraCB,this);
  menu_list->push_back(MenuElem("_Camera",*manage(tmp_menu)));
  tmp_menu = createPluginMenu(FX_LIGHT_CLASS,sceneLightCB,this);  
  menu_list->push_back(MenuElem("_Light",*manage(tmp_menu)));
  */

  ptVBox->pack_start (*ptSWnd, 1, 1, 0);  
  add(*ptVBox);

  show_all();

  set_default_size (600, 400);

  setSceneFile();

  window_count++;

}  /* TSceneWindow() */


void TSceneWindow::setSceneFile (void)
{

  std::string   tTitle;
  std::string   tName;
  std::string   tFormat;

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

  ptScene.set(NULL);

  if ( tName != "" )
  {
    tFormat = FileExtension (tName);

    if ( !TSceneManager::_knownFormat (tFormat) )
    {
      GOM.error() << "ERROR: Scene format not supported" << std::endl;
      exit (1);
    }

    ptScene = TSceneManager::_load (tName, tFormat);

    if ( ptScene )
    {
      setSensitive("/Menu/SceneMenu/SceneSave", true);
      setSensitive("/Menu/SceneMenu/SceneSaveAs", true);
      setSensitive("/Menu/SceneMenu/SceneClose", true);
      setSensitive("/Menu/RenderMenu/Render", true);
    }
  }
  else
  {
    ptScene.set(new TScene);

    setSensitive("/Menu/SceneMenu/SceneSave", false);
    setSensitive("/Menu/SceneMenu/SceneSaveAs", false);
    setSensitive("/Menu/SceneMenu/SceneClose", false);
    setSensitive("/Menu/RenderMenu/Render", false);
  }

  if ( tName == "" )
  {
    set_title ("Scene : <none>");
  }
  else
  {
    tTitle = std::string ("Scene - ") + tName;
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

  ptSWnd->add(*ptTree);
}  /* setSceneFile() */


void TSceneWindow::openNewSceneWindow (void)
{

  TSceneWindow*   ptWnd;
  
  ptWnd = new TSceneWindow (NULL);

  ptWnd->ptFileSelection = ptFileSelection;
  ptFileSelection        = NULL;
  
  ptWnd->show();

  ptWnd->setSceneFile();
  
}  /* openNewSceneWindow() */


void TSceneWindow::setSensitive(const std::string& name, bool value)
{
  Gtk::Widget* widget = ui_manager->get_widget(name);
  if( widget )
  {
    widget->set_sensitive(value);
  }
  else
  {
    std::cerr << "Unable to get widget for \"" << name << "\"" << std::endl;
  }
}
