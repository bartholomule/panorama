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
#include "plugins/bsdf/cook_torrance/bsdf_cook_torrance.h"
#include "plugins/bsdf/lambertian/bsdf_lambertian.h"
#include "plugins/bsdf/phong/bsdf_phong.h"
#include "plugins/bsdf/schlick/bsdf_schlick.h"
#include "plugins/bsdf/schlick_double/bsdf_schlick_double.h"
#include "plugins/bsdf/ward/bsdf_ward.h"
#include "plugins/camera/parallel/parallel.h"
#include "plugins/camera/pinhole/pinhole.h"
#include "plugins/image_filter/cartoon/if_cartoon.h"
#include "plugins/image_filter/convert_to_grey/if_convert_to_grey.h"
#include "plugins/image_filter/fog/if_fog.h"
#include "plugins/image_filter/lens_flare/if_lens_flare.h"
#include "plugins/image_filter/text/if_text.h"
#include "plugins/light/point_light/point_light.h"
#include "plugins/light/projector/projector.h"
#include "plugins/light/warn_light/warn_light.h"
#include "plugins/pattern/amplifier/pat_amplifier.h"
#include "plugins/pattern/brick/pat_brick.h"
#include "plugins/pattern/checker/pat_checker.h"
#include "plugins/pattern/composite/pat_composite.h"
#include "plugins/pattern/crackle/pat_crackle.h"
#include "plugins/pattern/cylgrad/pat_cylgrad.h"
#include "plugins/pattern/leopard/pat_leopard.h"
#include "plugins/pattern/marble/pat_marble.h"
#include "plugins/pattern/noise/pat_noise.h"
#include "plugins/pattern/parquet/pat_parquet.h"
#include "plugins/pattern/texture/pat_texture.h"
#include "plugins/pattern/wood/pat_wood.h"
#include "plugins/pattern/worley/pat_worley.h"
#include "plugins/perturbation/brick/per_brick.h"
#include "plugins/perturbation/bump/per_bump.h"
#include "plugins/perturbation/crackle/per_crackle.h"
#include "plugins/perturbation/leopard/per_leopard.h"
#include "plugins/perturbation/marble/per_marble.h"
#include "plugins/perturbation/noise/per_noise.h"
#include "plugins/perturbation/wave/per_wave.h"
#include "plugins/perturbation/worley/per_worley.h"
#include "plugins/object/aggregate_uniform_grid/aggregate_uniform_grid.h"
#include "plugins/object/bezier/bezier.h"
#include "plugins/object_filter/cartoon/of_cartoon.h"
#include "plugins/object_filter/convert_to_grey/of_convert_to_grey.h"
#include "plugins/renderer/raytracer/raytracer.h"

#if       defined(USE_EXPERIMENTAL)
#include "plugins/object/abvh/abvh.h"
#include "plugins/object/height_field/height_field.h"
#include "plugins/object/lwo/lwo.h"
#include "plugins/object/polyhedron/polyhedron.h"
#include "plugins/object/subdiv/subdiv.h"
#include "plugins/renderer/zbuffer/zbuffer.h"
#endif /* defined(USE_EXPERIMENTAL) */
