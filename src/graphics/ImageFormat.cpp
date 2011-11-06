/*
 * $Id: ImageFormat.cpp,v 1.1.2.1 2011/11/06 03:45:19 kpharris Exp $
 *
 * Part of GNU Panorama
 *
 * Copyright (C) 2011 Kevin Harris
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 */

#include "panorama/graphics/ImageFormat.hpp"

namespace panorama
{
	ImageFormat::ImageFormat(const ImageCapabilities& imageCaps, const ColorCapabilities& colorCaps,
		const blocxx::StringArray& extensions, const blocxx::String& preferredExtension,
		const blocxx::String& givenFormatName, ImageFormat::TagType tag)
		: m_imageCapabilities(imageCaps)
		, m_colorCapabilities(colorCaps)
		, m_fileExtensions(extensions)
		, m_preferredExtension(preferredExtension)
		, m_formatName(givenFormatName)
		, m_formatTag(tag)
	{
	}

	ImageCapabilities ImageFormat::imageCapabilities() const
	{
		return m_imageCapabilities;
	}
	ColorCapabilities ImageFormat::colorCapabilities() const
	{
		return m_colorCapabilities;
	}
	blocxx::StringArray ImageFormat::defaultFileExtensions() const
	{
		return m_fileExtensions;
	}
	blocxx::String ImageFormat::preferredFileExtension() const
	{
		return m_preferredExtension;
	}
	blocxx::String ImageFormat::formatName() const
	{
		return m_formatName;
	}
	ImageFormat::TagType ImageFormat::formatTag() const
	{
		return m_formatTag;
	}

	void ImageFormat::collectInternalMembers(MemberStringDumpCollector& collector) const
	{
		collector.addMember("imageCaps", m_imageCapabilities);
		collector.addMember("colorCaps", m_colorCapabilities);
		collector.addMember("extensions", m_fileExtensions);
		collector.addMember("defaultExtension", m_preferredExtension);
		collector.addMember("formatName", m_formatName);
		collector.addMember("tag", m_formatTag);
	}

	blocxx::String ImageFormat::toString(const Indentation& indent, StringDumpable::PrefixType prefix ) const
	{
		return toStringAsMembers(*this, indent, prefix);
	}
} // namespace panorama
