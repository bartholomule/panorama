/*
*  Copyright (C) 2008 Kevin Harris
*
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 3 of the License, or
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

#ifndef PANORAMA_SIMPLE_PATTERN_H_INCLUDED
#define PANORAMA_SIMPLE_PATTERN_H_INCLUDED

#include "llapi/pattern.h"

namespace panorama
{
  class SimplePattern : public TPattern
  {
  public:
    SimplePattern();
    SimplePattern(const TColor& color);
    SimplePattern(const TVector& color);
    SimplePattern(TScalar color);

    virtual ~SimplePattern();

    virtual std::string name (void) const;
    virtual std::string internalMembers(const Indentation& indent, PrefixType prefix) const;
    virtual SimplePattern* clone_new() const;

    AttributeErrorCode setAttribute (const std::string& rktNAME, Attribute nVALUE);
    AttributeErrorCode getAttribute (const std::string& rktNAME, Attribute& rnVALUE);
    void getAttributeList (TAttributeList& rtLIST) const;

    TColor pattern(const TSurfaceData& rktDATA) const;

  private:
    TColor m_color;
  };
} // end namespace panorama

#endif  /* PANORAMA_SIMPLE_PATTERN_H_INCLUDED */
