/*
 *  Copyright (C) 2001 Kevin Harris
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

#if       !defined(KH_TIFF_IO_H)
#define            KH_TIFF_IO_H

#include <string>
using std::string;

#include "llapi/image.h"
#include "hlapi/plugin_manager.h"

/*
  A tiff image loader plugin.

  Notes:  This will only write 24 bit images, but can read any tiff images
  supported by the libtiff library.

  The only real reason that this plugin was written was to further the
  capabilities of panorama, and not for anything I (KH) considered truly
  neccessary.  I also wanted to test out the libtiff library.

  This is known to work with LIBTIFF Version 3.5.6 beta.  If it works with any
  other versions, that's great.  Otherwise, you should fix it, and/or find
  someone willing to work on it (I may be willing, if I can find your library
  version and some motivation to work on it).
 */

class TImageTiff : public TImageIO
{

  public:

    TImageTiff (void) :
      compression (false) {}

    static TBaseClass* _create (const TBaseClass* pktPARENT);

    int save (const TImage* pktIMAGE);
    TImage* load (void);

    std::string className (void) const { return "ImageTiff"; }
    
    int setAttribute (const std::string& rktNAME, NAttribute nVALUE,
		      EAttribType eTYPE);
    int getAttribute (const std::string& rktNAME, NAttribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    void setCompression (bool comp) { compression = comp; }

  protected:

    bool compression; /* 0 = uncompressed,
			 1 = compressed (LZW if supported, otherwise PACKBITS)
		      */

};  /* class TImageTiff */

#endif /* KH_TIFF_IO_H */
