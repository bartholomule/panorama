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

#include <iostream.h>
#include "material_graph.h"

gint TMaterialGraph::handleMouseMove (GdkEventMotion* ptEVENT)
{

  move (*ptButton, short(ptEVENT->x), short(ptEVENT->y));
  
  return 1;
  
}  /* handleMouseMove() */


TMaterialGraph::TMaterialGraph (void)
{

  ptButton = new Gtk::Button ("PRUEBA");
  ptButton->show();

  set_events (get_events()  |
              GDK_BUTTON1_MOTION_MASK |
              GDK_BUTTON_PRESS_MASK   |
              GDK_BUTTON_RELEASE_MASK );
  
  motion_notify_event.connect(slot(this, &TMaterialGraph::handleMouseMove));

  put (*ptButton, 100, 100);

}  /* TMaterialGraph() */
