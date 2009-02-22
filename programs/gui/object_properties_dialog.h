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

#ifndef _OBJECT_PROPERTIES_DIALOG__
#define _OBJECT_PROPERTIES_DIALOG__

#include <gtkmm/button.h>
#include <gtkmm/widget.h>
#include <gtkmm/dialog.h>
#include "llapi/procedural.h"

class TObjectPropertiesDialog : public Gtk::Dialog
{

  protected:

    TProcedural*   ptObject;
    TProcedural*   ptObjectCopy; // A copy of the object, only in attributes.

    Gtk::Widget* createValueWidget (const std::string& name, EAttribType eTYPE,
				    NAttribute nVALUE);
      
    Gtk::Widget* createInfoWidget (void);
    Gtk::Widget* createPropertiesWidget (void);
    Gtk::Widget* createStatusWidget (void);
    Gtk::Button* ptOkButton;

  public:

    TObjectPropertiesDialog (TProcedural* ptOBJECT);
    ~TObjectPropertiesDialog();

    Gtk::Button& getOk()             { return *ptOkButton; }
    const Gtk::Button& getOk() const { return *ptOkButton; }

    void accept_changes();

    std::vector<std::string> modified_attributes;
  
};  /* class TObjectPropertiesDialog */

#endif  /* _OBJECT_PROPERTIES_DIALOG__ */
