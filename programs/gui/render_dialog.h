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

#ifndef _RENDER_DIALOG__
#define _RENDER_DIALOG__

#include <string>
#include "llapi/scene.h"
#include <gtk--/dialog.h>
#include <gtk--/checkbutton.h>

class TRenderDialog : public Gtk::Dialog
{

  protected:

    Word      wNeededBuffers;
    TScene*   ptScene;

    void toggleZBuffer (Gtk::CheckButton* ptBUTTON);
    void toggleNBuffer (Gtk::CheckButton* ptBUTTON);
                        
  public:

    TRenderDialog (TScene* ptSCENE);

    void render (void);
    void cancel (void);
    
};  /* class TRenderDialog */

#endif  /* _RENDER_DIALOG__ */
