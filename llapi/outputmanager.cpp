/*
 * $Header: /home/kevin/work/migrate_me/cvs/panorama/panorama/panorama/llapi/Attic/outputmanager.cpp,v 1.1.2.2 2009/02/22 10:14:20 kpharris Exp $
 *
 * Part of GNU Panorama - A framework for 3D graphics production
 * Copyright (C) 2003 Kevin Harris
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
 * *  You should have received a copy of the GNU General Public License 
 * along with this program; if not, write to the Free Software          
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 */

#include "outputmanager.h"


class crap_streambuf : public std::streambuf
{
public: 
  crap_streambuf() : std::streambuf() { }
};

//---------------------------------------------
// Default constructor for class TOutputManager
//---------------------------------------------
TOutputManager::TOutputManager():
  maxDebugLevel(0)
{
  CreateStream("out", &std::cout, false, true);
  CreateStream("debug", &std::cout, false, true);
  CreateStream("error", &std::cerr, false, true);
  CreateStream("tom::junk", new std::ostream(new crap_streambuf), true, false);
} // TOutputManager()

//------------------------------------
// Destructor for class TOutputManager
//------------------------------------
TOutputManager::~TOutputManager()
{

} // ~TOutputManager()

//------------------------------------------
// Copy constructor for class TOutputManager
//------------------------------------------
TOutputManager::TOutputManager(const TOutputManager& old):
  streamMap(old.streamMap),
  maxDebugLevel(0)
{

} // TOutputManager(TOutputManager)

//---------------------------------------------
// Assignment operator for class TOutputManager
//---------------------------------------------
TOutputManager& TOutputManager::operator= (const TOutputManager& old)
{
  // Generic check for self-assignment
  if( &old != this)
  {
    streamMap = old.streamMap;
    maxDebugLevel = old.maxDebugLevel;
  }
  return (*this);
} // TOutputManager::operator=(TOutputManager)


void TOutputManager::CreateStream(const std::string& name,
		  std::ostream* stream,
		  bool deleteable,
		  bool enabled)
{
  if( stream )
  {
    StreamData dat(stream, deleteable, enabled);
    
    streamMap[name] = dat;
  }
}

std::ostream& TOutputManager::Stream(const std::string& name)
{
  map_type::iterator i = streamMap.find(name);
  if( i != streamMap.end() )
  {
    // If the stream was enabled, return it, so that output can proceed.
    // If not, let it use the junk stream.
    if( i->second.enabled )
    {
      return *(i->second.stream);
    }
  }
  return *streamMap["tom::junk"].stream;
}

std::ostream& TOutputManager::operator[](const std::string& name)
{
  return this->Stream(name);
}

bool TOutputManager::EnableStream(const std::string& name)
{
  map_type::iterator i = streamMap.find(name);
  if( i != streamMap.end() )
  {
    bool temp =  i->second.enabled;
    i->second.enabled = true;

    return temp;
  }
  return false;
}

bool TOutputManager::DisableStream(const std::string& name)
{
  map_type::iterator i = streamMap.find(name);
  if( i != streamMap.end() )
  {
    bool temp =  i->second.enabled;
    i->second.enabled = false;

    return temp;
  }
  return false;  
}

#if !defined(MEMBER_TEMPLATES_WORK)
void TOutputManager::WriteToStream(const std::string& name,
				   const std::string& text)
{
  Stream(name) << text;
}
#endif


TOutputManager GOM;
