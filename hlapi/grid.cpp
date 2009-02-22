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

// [FIXME!] This does not *yet* work.

#include "grid.h"
#include <cstdio>
#include <generic/template_functions.h>
#include <llapi/type_all.h>

#define DEBUG_IT
#define DEBUG_IT2

bool accel_grid::initialize()
{
  char buffer[1024];
  sprintf(buffer,"Initializing %d objects in accel grid\n", objects_in_grid.size());
  GOM.debug() << buffer << std::endl;
  static const TVector eps_vector(FX_EPSILON, FX_EPSILON, FX_EPSILON);

  bool result = true;

  for(std::vector<base_ptr>::iterator obj_ptr = objects_in_grid.begin();
       obj_ptr != objects_in_grid.end();
      ++obj_ptr)
  {
    result = result && (*obj_ptr)->initialize();
    
    // If the object doesn't have a material, use the one that we have.
    if( !(*obj_ptr)->material() )
    {
      (*obj_ptr)->setMaterial(material());
    }
  }
  GOM.debug() << "accel grid: re-griding things." << std::endl;
  create_self_sized_grid();
  
  tBoundingBox.set (min_coord - eps_vector,
		    max_coord + eps_vector);
  return result;
}

accel_grid::accel_grid(const std::vector<magic_pointer<base_object> >& objects):
  TObject(),
  objects_in_grid(objects)
{
  create_self_sized_grid();
}

accel_grid::accel_grid(int x_divisions, int y_divisions,int z_divisions,
		       const TVector& min_vals, const TVector& max_vals):
  TObject(),
  nx(x_divisions), ny(y_divisions), nz(z_divisions),
  min_coord(min_vals),
  max_coord(max_vals)
{
  create_block_grid();
}

accel_grid::~accel_grid()
{
}


void accel_grid::create_block_grid(int subgrids)
{
  // Force it to empty (erase any previous garbage)...
  all_grid_entries.resize(0);
  // Resize it, to empty any items...
  all_grid_entries.resize(nx * ny * nz);

  if(subgrids > 0)
  {
    TVector divsize = max_coord - min_coord;
    
    divsize.setX( divsize.x() / TScalar(nx) );
    divsize.setY( divsize.y() / TScalar(ny) );
    divsize.setZ( divsize.z() / TScalar(nz) );  
    
    for(int z = 0; z < nz; ++z)
    {
      TScalar zmin = min_coord.z() + divsize.z() * z;
      TScalar zmax = min_coord.z() + divsize.z() * (z + 1);      
      for(int y = 0; y < ny; ++y)
      {
	TScalar ymin = min_coord.y() + divsize.y() * y;
	TScalar ymax = min_coord.y() + divsize.y() * (y + 1);      	
	for(int x = 0; x < nx; ++x)
	{
	  TScalar xmin = min_coord.x() + divsize.x() * x;
	  TScalar xmax = min_coord.x() + divsize.x() * (x + 1);      	

	  TVector cell_min(xmin, ymin, zmin);
	  TVector cell_max(xmax, ymax, zmax);

	  // Initialize the subgrid to match the current, with the proper
	  // ranges...
	  typedef magic_pointer<accel_grid> grid_ptr;
	  entry(x,y,z).sub_grid = (grid_ptr)new accel_grid(nx,ny,nz,
							   cell_min,
							   cell_max);
	  // Have the subgrid create subgrids of its own.
	  entry(x,y,z).sub_grid->create_block_grid(subgrids-1);
	} // for all x divisions
      } // for all y divisions
    } // for all z divisions
  } // if there are subgrids...
} // create block grid

void accel_grid::create_self_sized_grid(int subgrids)
{
  if(objects_in_grid.size() > 0)
  {
    std::vector<TBoundingBox> bounding_boxes;
    for(std::vector<base_ptr>::const_iterator i = objects_in_grid.begin();
	i != objects_in_grid.end();
	++i)
    {
      bounding_boxes.push_back((*i)->boundingBox());
    }
    std::vector<TBoundingBox>::iterator box = bounding_boxes.begin();

    // If there is something left, do some work...
    if(box != bounding_boxes.end())
    {
      // Calculate the initial coords.
      min_coord.setX( my_min(box->corner1().x(),box->corner2().x()) );
      min_coord.setY( my_min(box->corner1().y(),box->corner2().y()) );
      min_coord.setZ( my_min(box->corner1().z(),box->corner2().z()) );

      max_coord.setX( my_max(box->corner1().x(),box->corner2().x()) );
      max_coord.setY( my_max(box->corner1().y(),box->corner2().y()) );
      max_coord.setZ( my_max(box->corner1().z(),box->corner2().z()) );

      for(++box; box != bounding_boxes.end(); ++box)
      {
	for(int i = 0; i < 3; ++i)
	{
	  // If the corners are fooed up, fix them, so that corner1 is less
	  // for every component than corner2.  This is for use right now,
	  // and for use later, when they are going to be binned-up.
	  if(box->corner1()[i] > box->corner2()[i])
	  {
	    my_swap(box->corner1()[i],
		    box->corner2()[i]);
	  }
	  min_coord[i] = my_min(min_coord[i], box->corner1()[i]);
	  max_coord[i] = my_max(max_coord[i], box->corner2()[i]);
	}
      }

      // Now... The min and max coords are correctly set up... Find the
      // appropriate number of divisions in x,y, and z (as per Peter Shirley's
      // "Realistic Raytracing", section 11.2).
      TVector grid_size = max_coord - min_coord;
      
      TVector fixed_grid_size = grid_size;
      clamp(fixed_grid_size.x(), TScalar(1), TScalar(SCALAR_MAX));
      clamp(fixed_grid_size.y(), TScalar(1), TScalar(SCALAR_MAX));
      clamp(fixed_grid_size.z(), TScalar(1), TScalar(SCALAR_MAX));      
      
      int n = bounding_boxes.size();

      TScalar s = pow((fixed_grid_size.x() *
		 fixed_grid_size.y() *
		 fixed_grid_size.z()) / double(n),
		(1/3.0));

      nx = my_max(int((fixed_grid_size.x() / s) + 0.5), 1);
      ny = my_max(int((fixed_grid_size.y() / s) + 0.5), 1);
      nz = my_max(int((fixed_grid_size.z() / s) + 0.5), 1);


      GOM.debug() << "Creating " << nx << "x" << ny << "x" << nz << " grid for " << n << " objects." << std::endl;
#if defined(DEBUG_IT)
      GOM.debug() << "Min and max=" << min_coord << "," << max_coord << std::endl;
      GOM.debug() << "#objects=" << n << std::endl;
      GOM.debug() << "Grid size=" << grid_size << " S=" << s << std::endl;
      GOM.debug() << "Needed dimensions=" << grid_size / s << std::endl;
#endif

      // Resize the grid, removing any previous entries in any grid entry.
      all_grid_entries.resize(0);
      all_grid_entries.resize(nx*ny*nz);      

      TScalar x_step = grid_size.x() / TScalar(nx);
      TScalar y_step = grid_size.y() / TScalar(ny);
      TScalar z_step = grid_size.z() / TScalar(nz);


      int last_percentage = -1;
      std::string completion_string="#";
      
      // The grid is properly sized now...
      // Each object needs to be added to the grid in it's proper locations...
      for(box = bounding_boxes.begin(); box != bounding_boxes.end(); ++box)
      {
	if( (*(objects_in_grid.begin() + (box - bounding_boxes.begin())))->capabilities().gInfinite )
	{
	  // [CHECKME!]
	  // Ignore it
	  continue;
	}
	
	int box_number = box - bounding_boxes.begin();
	double percentage = box_number / double(bounding_boxes.size());
	int i_percent = int(100 * percentage);

	if(i_percent != last_percentage)
	{
	  last_percentage = i_percent;
	  if(i_percent & 1)
	  {
	    // An odd percent...
	    completion_string += '#';
	  }
	  else
	  {
	    // An even percent...
	    // Erase the previous mark.
	    completion_string.erase(completion_string.length() - 1, 1);

	    if((i_percent % 10 ) == 0)
	    {
	      static char s_buf[100];
	      sprintf(s_buf,"%d%%",i_percent);
	      completion_string += s_buf;
	    }
	    else
	    {
	      completion_string += '.';
	    }
	  }
	  GOM.debug() << completion_string + "\r" << std::flush;
	  //	  printf("%s\r",completion_string.c_str());
	  //	  fflush(stdout);
	} // percentage changed..
	
	// Calculate the min and max values for the boxes...	  
	TScalar fx_bin_min= (box->corner1().x() - min_coord.x()) / x_step;
	TScalar fx_bin_max= (box->corner2().x() - min_coord.x()) / x_step;
	
	TScalar fy_bin_min= (box->corner1().y() - min_coord.y()) / y_step;
	TScalar fy_bin_max= (box->corner2().y() - min_coord.y()) / y_step;
	  
	TScalar fz_bin_min= (box->corner1().z() - min_coord.z()) / z_step;
	TScalar fz_bin_max= (box->corner2().z() - min_coord.z()) / z_step;


	  // Clamp the ranges, so they are only added inside the grid...
	  // NOTE: I am clamping before conversion, because large
	  // floats/doubles are likely to cause sign problems after converting
	  // to an int.
	clamp(fx_bin_min, TScalar(0), TScalar(nx - 1));
	clamp(fx_bin_max, TScalar(0), TScalar(nx - 1));
	  
	clamp(fy_bin_min, TScalar(0), TScalar(ny - 1));
	clamp(fy_bin_max, TScalar(0), TScalar(ny - 1));
	  
	clamp(fz_bin_min, TScalar(0), TScalar(nz - 1));
	clamp(fz_bin_max, TScalar(0), TScalar(nz - 1));        
	  
	  
	int x_bin_min = int(fx_bin_min);
	int x_bin_max = int(fx_bin_max);
	  
	int y_bin_min = int(fy_bin_min);
	int y_bin_max = int(fy_bin_max);
	  
	int z_bin_min = int(fz_bin_min);
	int z_bin_max = int(fz_bin_max);	  
	  
	  // Add it to all blocks between the min and max blocks...
	  // And yes, to answer future questions, it should be added to all of
	  // these blocks, as the bounding box is axis aligned, as is the grid
	  // being built.
	for(int z = z_bin_min; z <= z_bin_max; ++z)
	{
	  for(int y = y_bin_min; y <= y_bin_max; ++y)
	  {
	    for(int x = x_bin_min; x <= x_bin_max; ++x)
	    {
	      entry(x,y,z).add_object(*(objects_in_grid.begin() +
					(box - bounding_boxes.begin())));
	    } // x loop
	  } // y loop
	} // z loop
      } // for all boxes

      completion_string.erase(completion_string.length() - 1, 1);      
      printf("%s100%%\n", completion_string.c_str());
      fflush(stdout);


      // If any recursion needs to be done....
      if(subgrids > 0)
      {      
	// Each entry needs to have a sub-grid added...
	for(int z = 0; z < nz; ++z)
	{
	  TScalar z_min = min_coord.z() + (z * z_step);
	  TScalar z_max = min_coord.z() + ((z+1) * z_step);	
	  for(int y = 0; y < ny; ++y)
	  {
	    TScalar y_min = min_coord.y() + (y * y_step);
	    TScalar y_max = min_coord.y() + ((y+1) * y_step);		  
	    for(int x = 0; x < nx; ++x)
	    {
	      TScalar x_min = min_coord.x() + (x * x_step);
	      TScalar x_max = min_coord.x() + ((x+1) * x_step);
	      
	      TVector cell_min(x_min, y_min, z_min);
	      TVector cell_max(x_max, y_max, z_max);
	      
	      typedef magic_pointer<accel_grid> grid_ptr;	      
	      entry(x,y,z).sub_grid = (grid_ptr)new accel_grid(1,1,1,cell_min, cell_max);	      
	      entry(x,y,z).sub_grid->objects_in_grid.insert(entry(x,y,z).sub_grid->objects_in_grid.begin(),
							    entry(x,y,z).objects_in_entry.begin(),
							    entry(x,y,z).objects_in_entry.begin());

	      // Have the entry recreate it's subgrids, if it contains objects.
	      if(!entry(x,y,z).objects_in_entry.empty())
	      {
		entry(x,y,z).sub_grid->create_self_sized_grid(subgrids - 1);
	      }
	    } // for all x divisions
	  } // for all y divisions
	} // for all z divisions
      } // subgrids > 0
    } // if any non-null boxes exist
    else
    {
      // NO NON-NULL BOUNDING BOXES!!!
      // Create a single-cell grid which will encompass anything.
      nx = ny = nz = 1;
      min_coord = TVector(-SCALAR_MAX/2);
      max_coord = TVector( SCALAR_MAX/2);      
      all_grid_entries.resize(1);
      all_grid_entries[0].objects_in_entry.erase(all_grid_entries[0].objects_in_entry.begin(),
						 all_grid_entries[0].objects_in_entry.end());
      all_grid_entries[0].objects_in_entry.insert(all_grid_entries[0].objects_in_entry.begin(),
						  objects_in_grid.begin(),
						  objects_in_grid.end());      
    } 
  } // objects in grid > 0
  else
  {
    // 0 objects... Why grid it?!?!?! Anyways... Create a similar piece of
    // junk to when everything has NULL bounding boxes..
    nx = ny = nz = 1;
    min_coord = TVector(-SCALAR_MAX/2);
    max_coord = TVector( SCALAR_MAX/2);      
    all_grid_entries.resize(1);
      all_grid_entries[0].objects_in_entry.erase(all_grid_entries[0].objects_in_entry.begin(),
						 all_grid_entries[0].objects_in_entry.end());
      all_grid_entries[0].objects_in_entry.insert(all_grid_entries[0].objects_in_entry.begin(),
						  objects_in_grid.begin(),
						  objects_in_grid.end());     
    all_grid_entries[0].sub_grid = magic_pointer<accel_grid >();
  }
} // create self-sized grid


void accel_grid::add_object(const magic_pointer<base_object>& obj)
{
  
  bounding_box box = obj->boundingBox();
  objects_in_grid.push_back(obj);

  if( !obj->capabilities().gInfinite )
  {
    // Bounding box ok..
    TVector grid_size = max_coord - min_coord;
    clamp(grid_size.x(), -SCALAR_MAX, SCALAR_MAX);
    clamp(grid_size.y(), -SCALAR_MAX, SCALAR_MAX);
    clamp(grid_size.z(), -SCALAR_MAX, SCALAR_MAX);
    
    TScalar x_step = grid_size.x() / TScalar(nx);
    TScalar y_step = grid_size.y() / TScalar(ny);
    TScalar z_step = grid_size.z() / TScalar(nz);
    
#if defined(DEBUG_IT2)
    GOM.debug() << "grid size=" << grid_size << std::endl;
    GOM.debug() << "grid divisions=" << nx << ", " << ny << ", " << nz << std::endl;
#endif
    
    // Calculate the min and max values for the boxes...
    TScalar fx_bin_min = (box.corner1().x() - min_coord.x()) / x_step;
    TScalar fx_bin_max = (box.corner2().x() - min_coord.x()) / x_step;
    
    TScalar fy_bin_min = (box.corner1().y() - min_coord.y()) / y_step; 
    TScalar fy_bin_max = (box.corner2().y() - min_coord.y()) / y_step;
    
    TScalar fz_bin_min = (box.corner1().z() - min_coord.z()) / z_step;
    TScalar fz_bin_max = (box.corner2().z() - min_coord.z()) / z_step;
    
    clamp(fx_bin_min, TScalar(0), TScalar(nx - 1));
    clamp(fx_bin_max, TScalar(0), TScalar(nx - 1));
    
    clamp(fy_bin_min, TScalar(0), TScalar(ny - 1));
    clamp(fy_bin_max, TScalar(0), TScalar(ny - 1));
    
    clamp(fz_bin_min, TScalar(0), TScalar(nz - 1));
    clamp(fz_bin_max, TScalar(0), TScalar(nz - 1));        
    
    // Calculate the min and max values for the boxes...
    int x_bin_min = int(fx_bin_min);
    int x_bin_max = int(fx_bin_max);
    
    int y_bin_min = int(fy_bin_min);
    int y_bin_max = int(fy_bin_max);
    
    int z_bin_min = int(fz_bin_min);
    int z_bin_max = int(fz_bin_max);
    
    // Clamp the ranges, so they are only added inside the grid...
#if defined(DEBUG_IT2)
    GOM.debug() << "x bins range from " << x_bin_min << " to " << x_bin_max << std::endl;
    GOM.debug() << "y bins range from " << y_bin_min << " to " << y_bin_max << std::endl;
    GOM.debug() << "z bins range from " << z_bin_min << " to " << z_bin_max << std::endl;
#endif
    
    
    // Add it to all blocks between the min and max blocks...
    // And yes, to answer future questions, it should be added to all of
    // these blocks, as the bounding box is axis aligned, as is the grid
    // being built.
    for(int z = z_bin_min; z <= z_bin_max; ++z)
    {
      for(int y = y_bin_min; y <= y_bin_max; ++y)
      {
	for(int x = x_bin_min; x <= x_bin_max; ++x)
	{
#if defined(DEBUG_IT2)	  
	  GOM.debug() << "Adding object " << obj->className()
	       << " to bin ("
	       << x << ","
	       << y << ","
	       << z << ")" << std::endl;
#endif
	  entry(x,y,z).add_object(obj);
	} // x loop
      } // y loop
    } // z loop    
  }
  else
  {
    infinite_objects.push_back(obj);
  } // infinite object...
} // accel_grid::add_object

bool accel_grid::findFirstIntersection(const TRay& ray, TSurfaceData& hit_info) const
{
  //  GOM.debug() << "accel_grid::findFirstIntersection()" << std::endl;
  bool hit_something = false;
  TSurfaceData inf_data, grid_data;
  bool hit_inf = false;
  hit_inf = findInfiniteObjectIntersection(ray, inf_data);
  bool hit_grid = false;
  hit_grid = findFirstGridIntersection(ray, grid_data);
  if( hit_inf )
  {
    if( hit_grid )
    {
      if( grid_data.distance() < inf_data.distance() )
      {
	hit_info = grid_data;
      }
      else
      {
	hit_info = inf_data;
      }
    }
    else
    {
      hit_info = inf_data;
    }
    hit_something = true;
  }
  else if( hit_grid )
  {
    hit_info = grid_data;
    hit_something = true;
  }
  return hit_something;
}

bool accel_grid::findAllGridIntersections(const TRay& ray, TSpanList& spl) const
{
  GOM.debug() << "accel_grid::findAllGridIntersections()" << std::endl;  
  // This is a long and complex function.  The bulk of it is from Peter
  // Shirley's "Realist Raytracing" (section 11.1 -- almost 3 pages worth)

  // I hate to duplicate this twice--once here, and once in accel_grid::findFirstIntersection --
  // but this will be a whole lot slower than that one (it gets ALL hits).

  //---------------------------------------------------------------------------
  // FIXME! Copy the body from accel_grid::findFirstIntersection and modify all returns to be
  // either returns or breaks (depending on if they are in the loop, or not)
  //---------------------------------------------------------------------------
  assert(("FIXME NOW!",0));

  return false;  
}

bool accel_grid::findFirstGridIntersection(const TRay& ray, TSurfaceData& hit_info) const
{
  //  GOM.debug() << "accel_grid::findFirstGridIntersection()" << std::endl;
  // This is a long and complex function.  The bulk of it is from Peter
  // Shirley's "Realist Raytracing" (section 11.1 -- almost 3 pages worth)

  // I hate to duplicate this twice--once here, and once in accel_grid::findAllIntersections--
  // but this will be a whole lot faster than that one (it bails on the first
  // hit).

  const TVector& d = ray.direction();
  const TVector& o = ray.location();  
  TScalar tx_min, ty_min, tz_min;
  TScalar tx_max, ty_max, tz_max;
  TScalar t0, t1;

  if(d.x() >= 0)
  {
    tx_min = (min_coord.x() - o.x()) / d.x();
    tx_max = (max_coord.x() - o.x()) / d.x();
  }
  else
  {
    tx_min = (max_coord.x() - o.x()) / d.x();
    tx_max = (min_coord.x() - o.x()) / d.x();
  }

  if(d.y() >= 0)
  {
    ty_min = (min_coord.y() - o.y()) / d.y();
    ty_max = (max_coord.y() - o.y()) / d.y();
  }
  else
  {
    ty_min = (max_coord.y() - o.y()) / d.y();
    ty_max = (min_coord.y() - o.y()) / d.y();
  }
  
  if(d.z() >= 0)
  {
    tz_min = (min_coord.z() - o.z()) / d.z();
    tz_max = (max_coord.z() - o.z()) / d.z();
  }
  else
  {
    tz_min = (max_coord.z() - o.z()) / d.z();
    tz_max = (min_coord.z() - o.z()) / d.z();
  }    

  // Find the biggest of tx_min, ty_min, tz_min
  if(tx_min > ty_min)
  {
    t0 = tx_min;
  }
  else
  {
    t0 = ty_min;
  }
  if(tz_min > t0)
  {
    t0 = tz_min;
  }

  // Find the smallest of tx_max, ty_max, tz_max
  if(tx_max < ty_max)
  {
    t1 = tx_max;
  }
  else
  {
    t1 = ty_max;
  }    
  if(tz_max < t1)
  {
    t1 = tz_max;
  }

  if(t0 > t1)
  {
#if defined(DEBUG_IT2)    
    GOM.debug() << "Bailing due to failure to hit grid." << std::endl;
#endif
    // No hit with the grid.
    return false;
  }

  TScalar clip_min = ray.range().min();
  TScalar clip_max = ray.range().max();
  if(clip_min > clip_max)
  {
    my_swap(clip_min, clip_max);
  }
  
  if(t1 < clip_min)
  {
    // [Checkme!]
    // For single hits, I can make this assumption.  For all hits, I need to go
    // both directions. DO I? [10Jun2001]
    return false;
  }

  // Force the T values to be in the range of the ray...
  clamp(t0, clip_min, clip_max);
  clamp(t1, clip_min, clip_max);

  // Now that we know it hit the grid, we need to follow it through the grid,
  // only walking through the cells that need it.
  TScalar dtx = (tx_max - tx_min) / TScalar(nx);
  TScalar dty = (ty_max - ty_min) / TScalar(ny);
  TScalar dtz = (tz_max - tz_min) / TScalar(nz);
  
  TVector p = ray.location() + t0 * ray.direction();
  TVector diff = max_coord - min_coord;
  TVector diff1 = p - min_coord;
  
  int ix, iy, iz;
  // Find the initial x, y, and z spots where the ray enters the grid.
  // DAMNIT!  I only want to start there if the ray originates outside of the
  // grid!
  ix = int(nx * diff1.x() / diff.x());
  iy = int(ny * diff1.y() / diff.y());
  iz = int(nz * diff1.z() / diff.z());

  clamp(ix, 0, nx - 1);
  clamp(iy, 0, ny - 1);
  clamp(iz, 0, nz - 1);

  TScalar tx_next, ty_next, tz_next;   // The next T value in each dimension
  int ix_step, iy_step, iz_step; // The direction, amount of change...
  int ix_stop, iy_stop, iz_stop; // The max before bail.

  if(d.x() > 0)
  {
    tx_next = tx_min + (ix + 1) * dtx;
    ix_step = 1;
    ix_stop = nx;
  }
  else
  {
    tx_next = tx_min + (nx - ix) * dtx;
    ix_step = -1;
    ix_stop = -1;
  }

  if(d.y() > 0)
  {
    ty_next = ty_min + (iy + 1) * dty;
    iy_step = 1;
    iy_stop = ny;
  }
  else
  {
    ty_next = ty_min + (ny - iy) * dty;
    iy_step = -1;
    iy_stop = -1;
  }

  if(d.z() > 0)
  {
    tz_next = tz_min + (iz + 1) * dtz;
    iz_step = 1;
    iz_stop = nz;
  }
  else
  {
    tz_next = tz_min + (nz - iz) * dtz;
    iz_step = -1;
    iz_stop = -1;
  }


  // Now that we have things setup, we can do the real traversal loop.
  TRay sub_ray = ray;
  
  //  TScalar t_min = my_max(ray.range().begin(), t0);  
  //  TScalar t_max = my_min(ray.range().end(), t1);
  TScalar t_min = t0;
  TScalar t_max = t1;
  

#if defined(DEBUG_IT2)  
  GOM.debug() << __FUNCTION__ << ":" << std::endl;
  GOM.debug() << "min=" << t_min
       << " max=" << t_max
       << std::endl;
  GOM.debug() << "range=" << ray.range() << std::endl;
  GOM.debug() << "dx=" << d.x() << " dtx=" << dtx << " tx_next=" << tx_next << std::endl;
  GOM.debug() << "dy=" << d.y() << " dty=" << dty << " ty_next=" << ty_next << std::endl;
  GOM.debug() << "dz=" << d.z() << " dtz=" << dtz << " tz_next=" << tz_next << std::endl;
  GOM.debug() << "tx_min=" << tx_min << " tx_max=" << tx_max << std::endl;
  GOM.debug() << "ty_min=" << ty_min << " ty_max=" << ty_max << std::endl;
  GOM.debug() << "tz_min=" << tz_min << " tz_max=" << tz_max << std::endl;  
  GOM.debug() << "ix=" << ix << " iy=" << iy << " iz=" << iz << std::endl;
#endif
  
  while(1)
  {
    if((tx_next < ty_next) && (tx_next < tz_next))
    {
      // X grid boundary is next...
      sub_ray.setRange(t_min, tx_next);
#if defined(DEBUG_IT2)      
      GOM.debug() << " (X) range=" << sub_ray.range() << std::endl;
#endif
      
      // Check to see if there was a hit in the proper range.
      if((!entry(ix,iy,iz).objects_in_entry.empty()) &&
	 (entry(ix,iy,iz).findFirstIntersection(sub_ray, hit_info)))
      {
#if defined(DEBUG_IT2)	  
	GOM.debug() << " Hit object " << hit_info.object()->className()
	     << " at T=" << hit_info.distance() << std::endl;
#endif
	return true;
      } // entry contains items, and entry had hit

      t_min = tx_next;
      tx_next += dtx;
      ix += ix_step;
      if(ix == ix_stop)
      {
#if defined(DEBUG_IT2)	
	GOM.debug() << "ix (" << ix << ") hit its limit" << std::endl;
#endif
	return false;
      }
      else if(t_min >= t_max)
      {
#if defined(DEBUG_IT2)	
	GOM.debug() << "T hit its limit (" << t_max << ")" << std::endl;
#endif
	return false;
      }
    } // tx_next is closest
    else if(ty_next < tz_next)
    {
      // Y grid boundary is next...
      sub_ray.setRange(t_min, ty_next);
#if defined(DEBUG_IT2)      
      GOM.debug() << " (Y) range=" << sub_ray.range() << std::endl;
#endif
      
      // Check to see if there was a hit in the proper range.      
      if((!entry(ix,iy,iz).objects_in_entry.empty()) &&
	 (entry(ix,iy,iz).findFirstIntersection(sub_ray, hit_info)))
      {
#if defined(DEBUG_IT2)	  
	GOM.debug() << " Hit object " << hit_info.object()->className()
	     << " at T=" << hit_info.distance() << std::endl;
#endif
	return true;
      } // entry contains items, and entry had hit

      t_min = ty_next;
      ty_next += dty;
      iy += iy_step;
      if(iy == iy_stop)
      {
#if defined(DEBUG_IT2)	
	GOM.debug() << "iy (" << ix << ") hit its limit" << std::endl;
#endif
	return false;
      }
      else if(t_min >= t_max)
      {
#if defined(DEBUG_IT2)	
	GOM.debug() << "T hit its limit (" << t_max << ")" << std::endl;
#endif
	return false;
      }      
    } // ty_next is closest
    else
    {
      // Z grid boundary is next...
      sub_ray.setRange(t_min, tz_next);
#if defined(DEBUG_IT2)      
      GOM.debug() << " (Z) range=" << sub_ray.range() << std::endl;
#endif

      // Check to see if there was a hit in the proper range.      
      if((!entry(ix,iy,iz).objects_in_entry.empty()) &&
	 (entry(ix,iy,iz).findFirstIntersection(sub_ray, hit_info)))
      {
#if defined(DEBUG_IT2)	  
	GOM.debug() << " Hit object " << hit_info.object()->className()
	     << " at T=" << hit_info.distance() << std::endl;
#endif
	return true;
      } // entry contains items, and entry had hit

      t_min = tz_next;
      tz_next += dtz;
      iz += iz_step;
      if(iz == iz_stop)
      {
#if defined(DEBUG_IT2)	
	GOM.debug() << "iz (" << ix << ") hit its limit" << std::endl;
#endif
	return false;
      }
      else if(t_min >= t_max)
      {
#if defined(DEBUG_IT2)	
	GOM.debug() << "T hit its limit (" << t_max << ")" << std::endl;
#endif
	return false;
      }      
    } // tz_next is closest.
  } // Main loop (while(1))
} // accel_grid::findFirstIntersection

bool accel_grid::findAllIntersections(const TRay& ray, TSpanList& spl) const
{
  GOM.debug() << "accel_grid::findAllIntersections()" << std::endl;  
  return ( findAllInfiniteObjectIntersections(ray, spl) ||
	   findAllGridIntersections(ray, spl) );
} // accel_grid::findAllIntersections

bool accel_grid::grid_entry::findAllIntersections(const TRay& ray, TSpanList& spl) const
{
  //  GOM.debug() << "accel_grid::grid_entry::findallIntersections()" << std::endl;  
  bool hit_something = false;
  if(!!sub_grid)
  {
    hit_something = sub_grid->findAllIntersections(ray, spl);
  }
  else
  {
    // No sub grid... Do some dirty work.
    for(std::vector<base_ptr>::const_iterator i = objects_in_entry.begin();
	i != objects_in_entry.end();
	++i)
    {
      TSpanList new_hits;
      if( (*i)->findAllIntersections(ray, new_hits) )
      {
	hit_something = true;
	spl.insert(new_hits.begin(), new_hits.end());
      }
    } // for each object.
  } // no sub grid
  return hit_something;
} // accell_grid::grid_entry::findAllIntersections


bool accel_grid::grid_entry::findFirstIntersection(const TRay& ray, TSurfaceData& hit_info) const
{
  GOM.debug() << "accel_grid::grid_entry::findFirstIntersection()" << std::endl;  
  if(sub_grid)
  {
    GOM.debug() << "accel_grid::grid_entry has a sub grid." << std::endl;
    bool sub_hit = sub_grid->findFirstIntersection(ray,hit_info);
    //    GOM.debug() << "sub hit=" << sub_hit << std::endl;
    return sub_hit;
  }
  else
  {
    // No sub grid... We have to do the messy work.
    GOM.debug() << "accel_grid::grid_entry has no sub grid." << std::endl;
    GOM.debug() << "accel_grid::grid_entry contains " << objects_in_entry.size() << " objects." << std::endl;
    GOM.debug() << "The range of the ray is " << ray.range() << std::endl;
    GOM.debug() << "from " << ray.location() + ray.direction() * ray.range().min()
	 << " to " <<  ray.location() + ray.direction() * ray.range().max()
	 << std::endl;

    TSpanList first_hits;
    TSurfaceData hr;
    for(std::vector<base_ptr>::const_iterator i = objects_in_entry.begin();
	i != objects_in_entry.end();
	++i)
    {
      GOM.debug() << "checking object at " << (*i)->location();
      if((*i)->findFirstIntersection(ray, hr))
      {
	GOM.debug() << "Hit!" << std::endl;
	first_hits.add(hr);
      }
      else
      {
	GOM.debug() << "Missed!" << std::endl;
      }
    } // for each object.
    if(first_hits.size() > 0)
    {
      hit_info = first_hits.first();
      //      GOM.debug() << "No sub... Hit anyways." << std::endl;
      return true;
    } // contains hits.
  } // no sub grid
  return false;
} // accell_grid::grid_entry::findFirstIntersection


bool accel_grid::findInfiniteObjectIntersection(const TRay& rktRAY, TSurfaceData& rtDATA) const
{
  //  GOM.debug() << "accel_grid::findInfiniteObjectIntersection()" << std::endl;  
  TSpanList hits;

  for(std::vector<base_ptr>::const_iterator i = infinite_objects.begin(); i != infinite_objects.end(); ++i)
  {
    TSurfaceData temp_data;
    if( (*i)->findFirstIntersection(rktRAY, temp_data) )
    {
      hits.add(temp_data);
    }
  }
  if( hits.size() > 0 )
  {
    rtDATA = hits.first();
    return true;
  }
  return false;
}

bool accel_grid::findAllInfiniteObjectIntersections(const TRay& rktRAY, TSpanList& rtLIST) const
{
  GOM.debug() << "accel_grid::findAllInfiniteObjectIntersections()" << std::endl;
  bool hit_something = false;

  for(std::vector<base_ptr>::const_iterator i = infinite_objects.begin(); i != infinite_objects.end(); ++i)
  {
    if( (*i)->findAllIntersections(rktRAY, rtLIST) )
    {
      hit_something = true;
    }
  }
  return hit_something;
}

int accel_grid::setAttribute (const std::string& rktNAME, NAttribute nVALUE, EAttribType eTYPE)
{
  return TObject::setAttribute(rktNAME, nVALUE, eTYPE);
}
  
int accel_grid::getAttribute (const std::string& rktNAME, NAttribute& rnVALUE)
{
  return TObject::getAttribute(rktNAME, rnVALUE);
}

void accel_grid::getAttributeList (TAttributeList& rtLIST) const
{
  TObject::getAttributeList(rtLIST);
}

TUserFunctionMap accel_grid::getUserFunctions()
{
  TUserFunctionMap ufm = TObject::getUserFunctions();
  ufm["addObject"] = create_user_function(this, &accel_grid::add_object_nr);
  
  return ufm;  
}
