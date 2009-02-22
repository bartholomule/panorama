/*
*  Copyright (C) 2002 Kevin Harris
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
#if       !defined(PARSED_TYPES_H)
#define            PARSED_TYPES_H

#include <string>
#include "llapi/llapi_all.h"
#include "hlapi/hlapi_all.h"
#include "generic/magic_pointer.h"

#if defined(NEW_ATTRIBUTES)
#include <llapi/attribs.h>
#endif

#define YYSTYPE yy_data_type
#define YYLEX_PARAM &yylval

struct yy_data_type
{
  std::string           sIdent;
  double                dValue;
  int                   iValue;
  bool                  gValue;
  magic_pointer<TColor>               ptColor;
  magic_pointer<TVector>              ptVector;
  magic_pointer<TVector2>             ptVector2;
  magic_pointer<TScene>               ptScene;
  magic_pointer<TRenderer>            ptRenderer;
  magic_pointer<TCamera>              ptCamera;
  magic_pointer<TLight>               ptLight;
  magic_pointer<TBsdf>                ptBsdf;
  magic_pointer<TMaterial>            ptMaterial;
  magic_pointer<TPattern>             ptPattern;
  magic_pointer<TPerturbation>        ptPerturbation; 
  magic_pointer<TObject>              ptObject;
  magic_pointer<TImageFilter>         ptIFilter;
  magic_pointer<TObjectFilter>        ptOFilter;
  magic_pointer<TAtmosphericObject>   ptAtmObject;
  magic_pointer<TImageIO>             ptImageIO;
#if defined(NEW_ATTRIBUTES)
  magic_pointer<TAttribute>           ptAttribute;
#endif

};

typedef YYSTYPE yystype;

#endif /* !defined(PARSED_TYPES_H) */
