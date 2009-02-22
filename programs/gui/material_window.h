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

#ifndef _MATERIAL_WINDOW__
#define _MATERIAL_WINDOW__

#include "llapi/scene.h"
#include "material_graph.h"
#include <gtkmm/notebook.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/window.h>


#define FX_PREVIEW_WIDTH    120
#define FX_PREVIEW_HEIGHT   120

class TMaterialWindow : public Gtk::Window
{

  protected:

    TMaterial*        ptMaterial;
    TScene*           ptScene;
    TMaterialGraph*   ptGraph;
    Gtk::DrawingArea* ptPreview;
    Gtk::Notebook*    ptNotebook;

    void setupScene (void);

    void previewButtonCB (Gtk::Button* ptBUTTON);
                                   
  public:

    TMaterialWindow (void);
    ~TMaterialWindow (void);

    void drawPreview (void);
    
};  /* class TMaterialWindow */

#endif  /* _MATERIAL_WINDOW__ */
