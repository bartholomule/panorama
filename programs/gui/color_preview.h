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

#ifndef _COLOR_PREVIEW__
#define _COLOR_PREVIEW__

#include "llapi/color.h"
#include <gtk--/preview.h>
#include <gtk--/button.h>
#include <gtk--/colorselection.h>
#include <sigc++/signal_system.h>

using SigC::Signal0;

class TColorPreview : public Gtk::Preview
{

  protected:

    TColor                      tColor;
    Gtk::ColorSelectionDialog*   ptColorDlg;
    
    gint buttonPressCB (GdkEventButton* ptBUTTON);
    void setColorCB (void);
    void closeDialogCB (void);
    
  public:

    TColorPreview (const TColor& rktCOLOR = TColor::_black());

    void drawColorCB (GtkAllocation* ptALLOC);
    
    TColor color (void) const { return tColor; }

    Signal0<void> color_changed;
};  /* class TColorPreview */

#endif  /* _COLOR_PREVIEW__ */
