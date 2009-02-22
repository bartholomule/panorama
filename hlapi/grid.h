/*
*  Copyright (C) 2003 Kevin Harris
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


#if       !defined(KH_GRID_H)
#define            KH_GRID_H

/*
  grid.h -- A file for a grid-based ray intersection acceleration.

  [FIXME] This is not *yet* functional for panorama.  It was functional in my
  own graphics project, but something broke in the conversion. 
 */
/*
  Revision History:
  10Jun2001 Created this file, wrote the accel_grid and grid_entry classes.
 */

#include <llapi/object.h>
#include <cassert>

class accel_grid: public TObject
{
public:
  typedef TObject base_object;
  typedef magic_pointer<base_object> base_ptr;  
  typedef TBoundingBox bounding_box;
  //  typedef magic_pointer<bounding_box> box_ptr;

  // A class for entries in the grid.
  class grid_entry
  {
  public:

    grid_entry(): sub_grid() { }

    const magic_pointer<base_object>& operator()(size_t index) const
    {
      return objects_in_entry[index];
    }
    magic_pointer<base_object>& operator()(size_t index)
    {
      return objects_in_entry[index];    
    }

    void add_object(const magic_pointer<base_object>& obj)
    {
      objects_in_entry.push_back(obj);

      if(sub_grid)
      {
	sub_grid->add_object(obj);
      }
    }

    bool findFirstIntersection(const TRay& rktRAY, TSurfaceData& rtDATA) const;
    bool findAllIntersections (const TRay& rktRAY, TSpanList& rtLIST) const;  

    /* Data members */
    std::vector<base_ptr> objects_in_entry;
    magic_pointer<accel_grid> sub_grid;
  };
  
public:

  // !
  accel_grid(const std::vector<magic_pointer<base_object> >& objects);
  // !  
  accel_grid(int x_divisions = 10,
	     int y_divisions = 10,
	     int z_divisions = 10,
	     const TVector& min_vals = TVector(-SCALAR_MAX/2),
	     const TVector& max_vals = TVector( SCALAR_MAX/2));
  // !  
  virtual ~accel_grid();

  virtual bool initialize ();
  
  // !
  virtual void add_object(const magic_pointer<base_object>& obj);
  virtual void add_object_nr(const magic_pointer<base_object> obj) { add_object(obj); }

  // !  
  virtual void create_block_grid(int subgrids = 0);
  // !  
  virtual void create_self_sized_grid(int subgrids = 0);  
  
  inline const grid_entry& entry(int i, int j, int k) const
  {
    int x_step = 1;
    int y_step = x_step * nx;    
    int z_step = y_step * ny;
    
    return all_grid_entries[i * x_step + j * y_step + k * z_step];
  }
  
  inline grid_entry& entry(int i, int j, int k)
  {
    int x_step = 1;
    int y_step = x_step * nx;    
    int z_step = y_step * ny;
    
    return all_grid_entries[i * x_step + j * y_step + k * z_step];    
  }

  virtual bool findFirstIntersection (const TRay& rktRAY, TSurfaceData& rtDATA) const;
  virtual bool findAllIntersections (const TRay& rktRAY, TSpanList& rtLIST) const;
  virtual bool findFirstGridIntersection (const TRay& rktRAY, TSurfaceData& rtDATA) const;
  virtual bool findAllGridIntersections (const TRay& rktRAY, TSpanList& rtLIST) const;    

  virtual std::string className (void) const { return "accel_grid"; }
  
  bool findInfiniteObjectIntersection(const TRay& rktRAY, TSurfaceData& rtDATA) const;
  bool findAllInfiniteObjectIntersections(const TRay& rktRAY, TSpanList& rtLIST) const;  

    // Attribute management
  virtual int setAttribute (const std::string& rktNAME, NAttribute nVALUE, EAttribType eTYPE);
  
  virtual int getAttribute (const std::string& rktNAME, NAttribute& rnVALUE);
  virtual void getAttributeList (TAttributeList& rtLIST) const;  
  virtual TUserFunctionMap getUserFunctions();
  
  virtual const base_ptr get_object(int index) const
  {
    return objects_in_grid[index];
  }

  virtual size_t num_objects() const
  {
    return objects_in_grid.size();
  }  
  
private:
  int nx, ny, nz; // Number of subdivisions in x,y,z
  TVector min_coord;
  TVector max_coord;
  std::vector<grid_entry> all_grid_entries;
  std::vector<base_ptr> objects_in_grid;
  std::vector<base_ptr> infinite_objects;
  
};

#endif /* !defined(KH_GRID_H) */
