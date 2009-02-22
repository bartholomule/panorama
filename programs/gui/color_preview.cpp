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

#include "color_preview.h"

gint TColorPreview::buttonPressCB (GdkEventButton* ptEVENT)
{

  gdouble   adColor [3];

  GOM.error() << "Color Preview::Button press callback!!!" << std::endl;
  
  if ( ( ptEVENT->type == GDK_2BUTTON_PRESS ) && ( ptEVENT->button == 1 ) )
  {
    if ( !ptColorDlg )
    {
      ptColorDlg = new Gtk::ColorSelectionDialog ("Select color");
      ptColorDlg->show();

      adColor[0] = tColor.red();
      adColor[1] = tColor.green();
      adColor[2] = tColor.blue();
      
      ptColorDlg->get_colorsel()->set_color (adColor);
      
      ptColorDlg->get_ok_button()->clicked.connect(slot(this, &TColorPreview::setColorCB));
      ptColorDlg->get_cancel_button()->clicked.connect(slot(this, &TColorPreview::closeDialogCB));
    }
  }

  return 1;

}  /* buttonPressCB() */


void TColorPreview::closeDialogCB (void)
{

  ptColorDlg->hide();
  delete ptColorDlg;

  ptColorDlg = NULL;
  
  
}  /* closeDialogCB() */


void TColorPreview::setColorCB (void)
{
  gdouble adColor [3];
  ptColorDlg->get_colorsel()->get_color (adColor);

  tColor = TColor(adColor[0], adColor[1], adColor[2]);

  // Get rid of the dialog...
  ptColorDlg->hide();
  delete ptColorDlg;
  ptColorDlg = NULL;
  
  drawColorCB (NULL);

  GOM.debug() << "Emitting color change..." << std::endl;
  color_changed();  
}  /* setColorCB() */


TColorPreview::TColorPreview (const TColor& rktCOLOR) :
  Gtk::Preview (GTK_PREVIEW_COLOR)
{
  ptColorDlg = NULL;
  tColor     = rktCOLOR;

  add_events (GDK_BUTTON_PRESS_MASK);

  size_allocate.connect(slot(this, &TColorPreview::drawColorCB));
  button_press_event.connect(slot(this, &TColorPreview::buttonPressCB));
  
}  /* TColorPreview() */


void TColorPreview::drawColorCB (GtkAllocation* ptALLOC)
{
  TColor   tColor24;
  size_t   zWidth   = width();
  size_t   zHeight  = height();
  Byte*    pbBuffer = new Byte [zWidth * 3];

  tColor24 = tColor.convertTo24Bits();
  
  for (size_t J = 0; ( J < zWidth ) ;J++)
  {
    pbBuffer [J * 3 + 0] = (Byte) tColor24.red();
    pbBuffer [J * 3 + 1] = (Byte) tColor24.green();
    pbBuffer [J * 3 + 2] = (Byte) tColor24.blue();
  }
  
  for (size_t J = 0; ( J < zHeight ) ;J++)
  {
    draw_row (pbBuffer, 0, J, zWidth);
  }

  gtk_widget_queue_draw (GTK_WIDGET (gtkobj()));
  
  delete pbBuffer;
  
}  /* drawColorCB() */



