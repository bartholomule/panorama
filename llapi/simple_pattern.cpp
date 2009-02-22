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

#include "simple_pattern.hpp"

namespace panorama
{
  SimplePattern::SimplePattern()
  {
  }

  SimplePattern::SimplePattern(const TColor& color)
    : m_color(color)
  {
  }

  SimplePattern::SimplePattern(const TVector& color)
    : m_color(color.x(), color.y(), color.z())
  {
  }

  SimplePattern::SimplePattern(TScalar color)
    : m_color(color, color, color)
  {
  }

  SimplePattern::~SimplePattern()
  {
  }

  std::string SimplePattern::name (void) const
  {
    return "SimplePattern";
  }

  std::string SimplePattern::internalMembers(const Indentation& indent, PrefixType prefix) const
  {
    std::string tag = indent.level();
    if( prefix == E_PREFIX_CLASSNAME )
    {
      tag = indent + SimplePattern::name() + "::";
    }

    std::string retval;

    retval += tag + "color=" + ::panorama::toString(m_color, indent.nextLevel(), prefix) + "\n";

    return retval;
  }

  SimplePattern* SimplePattern::clone_new() const
  {
    return new SimplePattern(*this);
  }

  void SimplePattern::getAttributeList (TAttributeList& rtLIST) const
  {
    TPattern::getAttributeList (rtLIST);

    rtLIST["color"] = Attribute::E_COLOR;
  }

  AttributeErrorCode SimplePattern::getAttribute(const std::string& rktNAME, Attribute& rnVALUE)
  {
    if( rktNAME == "color" )
    {
      rnVALUE = Attribute(m_color);
    }
    else
    {
      return TPattern::getAttribute(rktNAME, rnVALUE);
    }

    return FX_ATTRIB_OK;
  }

  AttributeErrorCode SimplePattern::setAttribute(const std::string& rktNAME, Attribute nVALUE)
  {
    if( rktNAME == "color" )
    {
      m_color = nVALUE.convertTo<TColor>();
    }
    else
    {
      return TPattern::setAttribute(rktNAME, nVALUE);
    }

    return FX_ATTRIB_OK;
  }

  TColor SimplePattern::pattern(const TSurfaceData& rktDATA) const
  {
    return m_color;
  }

} // end namespace panorama
