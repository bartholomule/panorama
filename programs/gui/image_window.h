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

#ifndef _IMAGE_WINDOW__
#define _IMAGE_WINDOW__

#include "llapi/scene.h"
#include <gtk--.h>
#include "object_properties_dialog.h"
#include "message_dialog.h"

void FinishedRenderLine (size_t zROW, void* pvDATA);

class TImageWindow;
  
struct TImageFilterCallbackData
{

  string          tName;
  TImageWindow*   ptWindow;
  
};  /* struct TImageFilterCallbackData */


class TImageWindow : public Gtk::Window
{

protected:

  Gtk::VBox*          ptVBox;
  Gtk::MenuBar*       ptMenuBar;
  Gtk::Preview*       ptPreview;
  TImage*             ptImage;

  Gtk::Menu* createFilterMenu (void);
                        
public:

  Gtk::FileSelection*      ptFileSelection;
  Gtk::ProgressBar*        ptProgress;
  TScene*                  ptScene;
  bool                     gRenderingDone;

  TImageWindow (TScene* ptSCENE);

  void saveImage (void);
    
  void drawRow (size_t zROW);
  void drawImage (void);

  void filterImage(TImageFilter* ptFilter);

  size_t image_width() const { return ptImage->width(); }
  size_t image_height() const { return ptImage->height(); }  
  void set_progress(size_t line_number);

};  /* class TImageWindow */

#endif  /* _IMAGE_WINDOW__ */
