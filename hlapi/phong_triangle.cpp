/*
*  Copyright (C) 1998 Angel Jimenez Jimenez and Carlos Jimenez Moreno
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

#include "llapi/surface_data.h"
#include "hlapi/phong_triangle.h"

void TPhongTriangle::update (void)
{

  TVector   tV2V0 = atVertex[0] - atVertex[2];

  TTriangle::update();
  
  tV2V1     = atVertex[1] - atVertex[2];
  tV2V1norm = tV2V1.norm();

  tV2V1.normalize();

  tProyV2V0overV2V1 = dotProduct (tV2V0, tV2V1);
  tMinDisV0overV2V1 = sqrt (dotProduct (tV2V0, tV2V0) - (tProyV2V0overV2V1 * tProyV2V0overV2V1));

}  /* update() */


void TPhongTriangle::setNormal (const TVector& rktNORMAL)
{

  if ( bNormal <= 2 )
  {
    atNormal [bNormal++] = rktNORMAL;
  }

}  /* setNormal() */


TVector TPhongTriangle::normal (const TSurfaceData& rktDATA) const
{

  TScalar   tProyVIV0overV2V1;
  TScalar   d, x, lambda;
  TVector   tNormal;
  TVector   tVIV0 = atVertex[0] - rktDATA.point();

  tProyVIV0overV2V1 = dotProduct (tVIV0, tV2V1);
  d                 = sqrt (dotProduct (tVIV0, tVIV0) - (tProyVIV0overV2V1 * tProyVIV0overV2V1));

  x      = (tProyVIV0overV2V1 * tMinDisV0overV2V1) / d;
  lambda = tProyV2V0overV2V1 - x;

  lambda = lambda / tV2V1norm;
  d      = d / tMinDisV0overV2V1;

  tNormal = lerp (atNormal[2], atNormal[1], lambda);
  tNormal = lerp (atNormal[0], tNormal, d);
  tNormal.normalize();

  if ( gOneSided )
  {
    return tNormal;
  }

  if ( dotProduct (tNormal, rktDATA.ray().direction()) > 0 )
  {
    tNormal = -tNormal;
  }

  return tNormal;

}  /* normal() */


void TPhongTriangle::printDebug (const std::string& indent) const
{

  GOM.debug() << indent << "[_PhongTriangle_]" << std::endl;

  std::string new_indent = TDebug::Indent(indent);
  
  GOM.debug() << new_indent << "Vertex 1 : "; atVertex[0].printDebug(new_indent); GOM.debug() << std::endl;
  GOM.debug() << new_indent << "Vertex 2 : "; atVertex[1].printDebug(new_indent); GOM.debug() << std::endl;
  GOM.debug() << new_indent << "Vertex 3 : "; atVertex[2].printDebug(new_indent); GOM.debug() << std::endl;
  GOM.debug() << new_indent << "Normal 1 : "; atNormal[0].printDebug(new_indent); GOM.debug() << std::endl;
  GOM.debug() << new_indent << "Normal 2 : "; atNormal[1].printDebug(new_indent); GOM.debug() << std::endl;
  GOM.debug() << new_indent << "Normal 3 : "; atNormal[2].printDebug(new_indent); GOM.debug() << std::endl;

}  /* printDebug() */

void TPhongTriangle::addVertex (const TVector& rktVERTEX, const TVector& rktNORMAL )
{
  setVertex(rktVERTEX);
  setNormal(rktNORMAL);
}

TUserFunctionMap TPhongTriangle::getUserFunctions()
{
  TUserFunctionMap ufm = TTriangle::getUserFunctions();

  ufm["addVertex"] = create_user_function(this,&TPhongTriangle::addVertex);

  return ufm;
}
