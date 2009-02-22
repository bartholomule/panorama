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

#ifndef _SCENE_TREE__
#define _SCENE_TREE__

#include "llapi/scene.h"
#include <string>
#include <gtkmm/treeview.h>
#include <gtkmm/button.h>

class TSceneTree : public Gtk::TreeView
{

  protected:

    magic_pointer<TScene> ptScene;

    bool recSetObjects (Gtk::TreeView* ptTREE, magic_pointer<TObject> ptOBJ);
    
    bool setCamera (Gtk::TreeView* ptTREE);
    bool setLights (Gtk::TreeView* ptTREE);
    bool setRenderer (Gtk::TreeView* ptTREE);  
    bool setObjects (Gtk::TreeView* ptTREE);
    
  public:

    TSceneTree (magic_pointer<TScene> ptSCENE);

    gint manageButtonPress (GdkEventButton* ptBUTTON, magic_pointer<TProcedural> ptOBJECT);

};  /* class TSceneTree */

#endif  /* _SCENE_TREE__ */
