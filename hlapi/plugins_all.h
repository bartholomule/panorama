/*
*  Copyright (C) 1998, 1999 Angel Jimenez Jimenez and Carlos Jimenez Moreno
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

#include "plugins/atm_object/atm_const/atm_const.h"
#include "plugins/bsdf/lambertian/bsdf_lambertian.h"
#include "plugins/bsdf/phong/bsdf_phong.h"
#include "plugins/camera/pinhole/pinhole.h"
#include "plugins/image_filter/cartoon/if_cartoon.h"
#include "plugins/image_filter/convert_to_grey/if_convert_to_grey.h"
#include "plugins/image_filter/fog/if_fog.h"
#include "plugins/image_filter/text/if_text.h"
#include "plugins/light/point_light/point_light.h"
#include "plugins/light/projector/projector.h"
#include "plugins/light/warn_light/warn_light.h"
#include "plugins/material/brick/mat_brick.h"
#include "plugins/material/checker/mat_checker.h"
#include "plugins/material/crackle/mat_crackle.h"
#include "plugins/material/leopard/mat_leopard.h"
#include "plugins/material/marble/mat_marble.h"
#include "plugins/material/noise/mat_noise.h"
#include "plugins/material/parquet/mat_parquet.h"
#include "plugins/material/wood/mat_wood.h"
#include "plugins/material/worley/mat_worley.h"
#include "plugins/object/abvh/abvh.h"
#include "plugins/object/bezier/bezier.h"
#include "plugins/object/subdiv/subdiv.h"
#include "plugins/object/height_field/height_field.h"
#include "plugins/object/lwo/lwo.h"
#include "plugins/object/polyhedron/polyhedron.h"
#include "plugins/object_filter/cartoon/of_cartoon.h"
#include "plugins/renderer/raytracer/raytracer.h"
#include "plugins/renderer/zbuffer/zbuffer.h"
