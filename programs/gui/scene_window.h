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

#ifndef _SCENE_WINDOW__
#define _SCENE_WINDOW__

#include "llapi/scene.h"
#include "scene_tree.h"
#include <string>
#include <gtk--.h>

class TSceneWindow : public Gtk::Window
{

protected:

  Gtk::ScrolledWindow* ptSWnd;
  Gtk::MenuBar*        ptMenuBar;
  //  Gtk::MenuFactory*   ptMenuFactory;
  //  Gtk::MenuFactory*   ptSubfactory;
  TSceneTree*        ptTree;
  string             tSceneName;
  TScene*            ptScene;
  bool               gModified;

  bool setSensitive (const char* pkcPATH, bool gSENSITIVE);
    
public:

  static size_t   _zWindows;

  Gtk::Main*            ptMain;
  Gtk::FileSelection*   ptFileSelection;

  TSceneWindow (Gtk::Main* ptMAIN);

  void setSceneFile (void);
  void openNewSceneWindow (void);
  void setSceneTree (void);

  TScene* scene (void) const { return ptScene; }
    
  gint delete_event_impl (GdkEventAny* ptEVENT)
  {
    _zWindows--;
    if ( !_zWindows )
    {
      //      ptMain->quit();
      Gtk::Main::quit();
    }
    return 0;
  }

};  /* class TSceneWindow */

#endif  /* _SCENE_WINDOW__ */
