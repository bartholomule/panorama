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

#include "message_dialog.h"

void MessageDialog (const string& rktTITLE, const string& rktTEXT)
{

  Gtk::Dialog*   ptDialog;
  Gtk::Label*    ptLabel;
  Gtk::Button*   ptButton;
  
  ptDialog = new Gtk::Dialog;

  ptDialog->get_vbox()->set_border_width (10);
  ptDialog->get_action_area()->set_border_width (10);
  
  ptLabel = new Gtk::Label (rktTEXT.c_str());
  ptLabel->show();
  
  ptDialog->get_vbox()->pack_start (*ptLabel, 1, 1, 0);

  ptButton = new Gtk::Button ("Ok");
  ptButton->show();
  
  ptDialog->get_action_area()->pack_start (*ptButton, 1, 1, 0);

  ptButton->clicked.connect(bind(slot(MessageDialogCloseCB), ptDialog));
  
  ptDialog->set_title (rktTITLE.c_str());
  ptDialog->show();
  
}  /* MessageDialog() */


void MessageDialogCloseCB (Gtk::Dialog* ptDLG)
{

  ptDLG->hide();
  delete ptDLG;
  
}  /* MessageDialogCloseCB() */
