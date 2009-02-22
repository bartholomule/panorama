/*
 * $Header: /home/kevin/work/migrate_me/cvs/panorama/panorama/panorama/llapi/Attic/outputmanager.h,v 1.1.2.2 2009/02/22 10:14:20 kpharris Exp $
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

#if       !defined(__OUTPUTMANAGER_H__)
#define            __OUTPUTMANAGER_H__

#include <cstddef>
#include "generic/ref_count_object.h"
#include <map>
#include <iostream>
#include <string>


#error "Don't use this.  I want to delete it."

#if defined(NO_DEBUG)
// A barfbucket to drop stuff that we don't care about.  This should be (in
// theory) a little faster than the default debug ignoring mechanism.
class barfbucket
{
public:
  inline barfbucket() { }

  inline friend barfbucket& operator<<(barfbucket& b, const std::string& s) { return b; }
  inline friend barfbucket& operator<<(barfbucket& b, const char* s) { return b; }
};

template <typename trash>
inline barfbucket& operator<<(barfbucket& b, const trash& t)
{
  return b;
}

inline barfbucket& operator<<(barfbucket& b, std::ostream&(*ignored)(std::ostream&))
{
  return b;
}

#endif /* defined(NO_DEBUG) */
typedef std::ostream& (*strmanip)(std::ostream&);

/**
 *
 * This is a class to be used in managing output for most everything.
 * It will handle:
 * debug
 * error
 * out
 * Any other named stream.
 *
 * This file was hacked (Kevin Harris) for use in my personal project, and to
 * reverse the order of comparison for debug output.  This leads me to question
 * whether or not it worked in Panorama (it was never checked in).
 *
 * @author Kevin Harris <kpharris@users.sourceforge.net>
 * @version $Revision: 1.1.2.2 $
 *
 */
class TOutputManager
{

private:

protected:
  /**
   * A class to hold the stream information (pointer, reference counts, enabled
   * flag, deleteable flag).
   */
  struct StreamData
  {
    StreamData(bool en = true):
      enabled(en), deleteable(false), stream(&std::cout)
    {
    }
    StreamData(std::ostream* str, bool deleteme = false, bool en = true):
      enabled(en), deleteable(deleteme), stream(str)
    {
    }
    StreamData& operator=(const StreamData& str)
    {
      if( &str != this )
      {
	if( stream )
	{
	  stream->flush();
	  if( deleteable && int(counts) <= 1 )
	  {
	    delete stream;
	  }
	}
	stream = str.stream;
	counts = str.counts;
	enabled = str.enabled;
	deleteable = str.deleteable;
      }
      return *this;
    }
    virtual ~StreamData()
    {
      if( stream )
      {
	stream->flush();
	if( deleteable  && int(counts) <= 1 )
	{
	  delete stream;
	  stream = NULL;
	}
      }
    }
    /** Says if the stream is enabled or not. */
    bool enabled;
    /** Says if the stream is deleteable (upon reassign or destructor). */
    bool deleteable;
    /** The actual stream pointer */
    std::ostream* stream;
    /** The counts of the instance of StreamData. */
    reference_counting_object<int> counts;
  }; // class StreamData

  typedef std::map<std::string, StreamData> map_type;
  /** A map of std::string->stream, used to name streams. */
  map_type streamMap;

  /** The minimum debug level of a message before output is done. */
  int maxDebugLevel;

public:
  /**@name Functions required for existance of a class */
  /** Default constructor */
  TOutputManager();

  /** Destructor */
  virtual ~TOutputManager();

  /** Copy constructor */
  TOutputManager(const TOutputManager& old);

  /** Assignment operator */
  TOutputManager& operator= (const TOutputManager& old);

  /**
   * Set the given "named stream" (name) to use the stream provided.  If this
   * name is already used, the old stream will be replaced (and deleted, if it
   * was given a deleteable value of true upon creation.
   *
   *@param name      The name of the stream
   *@param stream    The stream to use for each access of its name
   *@param deletable Specifies if the given stream can be deleted or not
   *@param enabled   Sets the stream to be enabled or disabled by default
   */
  virtual void CreateStream(const std::string& name,
			    std::ostream* stream,
			    bool deleteable = false,
			    bool enabled = true);

  /**
   *@returns The stream corresponding to the given name
   */
  virtual std::ostream& Stream(const std::string& name);

  /**
   * Sets the maximum debug level (the level at which output will be sent to
   * the debug stream) to the given value.
   *
   *@param level The new maximum debug level
   *@returns the old maximum debug level
   */
  int SetDebugLevel(int level) { int temp = maxDebugLevel; maxDebugLevel = level; return temp; }

  bool debugOK(int level) { return level <= maxDebugLevel; }

  /**
   * An alternative way to access a named stream.
   *@returns The stream which is mapped to this name, or if it doesn't exist, a
   * junk stream (which will discard output).
   */
  std::ostream& operator[](const std::string& name);

  /**@returns the 'output' stream */
  std::ostream& out()   { return Stream("out");   }
#if !defined(NO_DEBUG)
  /**@returns the 'debug' stream. This will output at the upper end of the debug level, IFF debugging is enabled. */
  std::ostream& debug()
  {
    return debug(maxDebugLevel);
  }
  /**@returns the 'debug' stream, only if the minimum debug level is met */
  std::ostream& debug(int level)
  {
    if( level <= maxDebugLevel)
    {
      return Stream("debug");
    }
    return Stream("tom::junk");
  }
#else
  barfbucket& debug(int level = 0)
  {
    static barfbucket b;
    return b;
  }
#endif
  /**@returns the 'error' stream */
  std::ostream& error() { return Stream("error"); }

  /**
   * Enables the stream of the given name.
   *@returns if the stream was already enabled.
   */
  virtual bool EnableStream(const std::string& name);
  /**
   * Disable the stream of the given name.
   *@returns if the stream was enabled.
   */
  virtual bool DisableStream(const std::string& name);

#if defined(MEMBER_TEMPLATES_WORK)
  /**
   * Send the given data to the named stream.
   */
  template <class T>
  void WriteToStream(const std::string& name,
		     const T& data)
  {
    Stream(name) << data;
  }

  /**
   * A stream insertion operator which will send output to the 'output' stream
   */
  template <class T>
  std::ostream& operator<<(const T& data) { return out(data); }
  /** Send the given data to the 'output' stream */
  template <class T>
  std::ostream& out(const T& data)   { return out() << data;   }
#if !defined(NO_DEBUG)
  /** Send the given data to the 'debug' stream (only if the level is met) */
  template <class T>
  std::ostream& debug(int level, const T& data) { return debug(level) << data; }
#else
  /** Absorb all of the junk... (level doesn't matter) */
  template <class T>
  barfbucket& debug(int level, const T& data) { return debug(); }
#endif /* !defined(NO_DEBUG) */

  /** Send the given data to the 'error' stream */
  template <class T>
  std::ostream& error(const T& data) { return error() << data; }
#else /* Member templates don't work */
  /**
   * Send the given text to the named stream.
   */
  void WriteToStream(const std::string& name,
		     const std::string& text);

  /** A stream insertion operator which will send output to the 'output' stream
   */
  std::ostream& operator<<(const std::string& text) { return out(text); }
  /** A stream insertion operator which will send output to the 'output' stream
   */
  std::ostream& operator<<(const char* text)        { return out(text); }

  /** Send the given text to the 'output' stream */
  std::ostream& out(const std::string& text)        { return out() << text;   }
  /** Send the given text to the 'output' stream */
  std::ostream& out(const char* text)               { return out() << text;   }
#if !defined(NO_DEBUG)
  /** Send the given text to the 'debug' stream (only if the level is met) */
  std::ostream& debug(int level, const std::string& text) { return debug(level) << text; }
  /** Send the given text to the 'debug' stream (only if the level is met) */
  std::ostream& debug(int level, const char* text)        { return debug(level) << text; }
#else
  /* Eat the input, and ignore it. (level doesn't matter) */
  barfbucket& debug(int level, const std::string& text) { return debug(); }
  /* Eat the input, and ignore it. (level doesn't matter) */
  barfbucket& debug(int level, const char* text)        { return debug(); }

#endif /* !defined(NO_DEBUG)   */
  /** Send the given text to the 'error' stream */
  std::ostream& error(const std::string& text) { return error() << text; }
  /** Send the given text to the 'error' stream */
  std::ostream& error(const char* text)        { return error() << text; }
#endif
}; // class TOutputManager

/**
 * A global output manager.  With this, there isn't normally a need to create
 * instances of this.  Output can be redirected as desired by changing the
 * streams that this output manager sends data to.  This could be useful, for
 * example, if a given stream will send it's output to a window, it can be used
 * in place of the default output stream.
 *
 * @see TOutputManager::CreateStream
 */
extern TOutputManager GOM;


#endif /* !defined(__OUTPUTMANAGER_H__) */

