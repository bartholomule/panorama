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

%{

#include <map>
#include <stack>
#include <string>
#include <iostream>
#include "llapi/llapi_all.h"
#include "hlapi/hlapi_all.h"
#include "hlapi/class_manager.h"
#include "parser_defs.h"
#include "rt_io.h"

static map<string, TProcedural*, less<string> >       _tObjectMap;
static map<string, TColor, less<string> >             _tColorMap;
static map<string, double(*)(void), less<string> >    _tFunctionMap;
static stack<TProcedural*>                            _tDataStack;

static TProcedural*   _ptData;
static TProcedural*   _ptParent;
static Byte           _bVertices;
static TVector        _tVector;
static TVector2       _tVector2;
static TColor         _tColor;
static TAggregate*    _ptWorld;
static NAttribute     _nAttrib;
static TImageIO*      _ptImageIO;

static double (*_pfFunction)(void);

#define POP()           top(); _tDataStack.pop()            // Fix to STL's pop()

#define DATA		(_tDataStack.top())
#define ENTITY		((TEntity*) _tDataStack.top())
#define VOLUME		((TVolume*) _tDataStack.top())
#define COLOR		((TColor*) _tDataStack.top())
#define SCENE		(TSceneRT::_ptParsedScene)
#define MATERIAL	((TMaterial*) _tDataStack.top())
#define OBJECT		((TObject*) _tDataStack.top())
#define AGGREGATE	((TAggregate*) _tDataStack.top())
#define TRIANGLE	((TTriangle*) _tDataStack.top())
#define RECTANGLE	((TRectangle*) _tDataStack.top())
#define MESH		((TMeshObject*) _tDataStack.top())

#define YYDEBUG 1

static TProcedural* NewObject (const string& rktCLASS, const TProcedural* pktPARENT);
static void* InstanceObject (const string& rktNAME);
static void* UpdateObject (const string& rktNAME);
static void DefineObject (const string& rktNAME, const string& rktCLASS, const string& rktDEF_CLASS);
static void CreateObject (const string& rktCLASS, const string& rktDEF_CLASS);
static void SetParameter (const string& rktATTRIB, EAttribType eTYPE);

static void InitObjects (void);
static void InitFunctions (void);

%}

%union {
         char                  acIdent [200];
         double                dValue;
         bool                  gValue;
         TColor*               ptColor;
         TVector*              ptVector;
         TVector2*             ptVector2;
         TScene*               ptScene;
         TRenderer*            ptRenderer;
         TCamera*              ptCamera;
         TLight*               ptLight;
         TBsdf*                ptBsdf;
         TMaterial*            ptMaterial;
         TObject*              ptObject;
         TImageFilter*         ptIFilter;
         TObjectFilter*        ptOFilter;
         TAtmosphericObject*   ptAtmObject;
         TImageIO*             ptImageIO;
       }

%token <gValue> T_BOOL
%token <dValue> T_REAL
%token <acIdent> T_IDENTIFIER
%token <acIdent> T_QUOTED_STRING

%token T_AGGREGATE
%token T_ATM_OBJECT
%token T_BLUE
%token T_BOX
%token T_BSDF
%token T_CAMERA
%token T_CIRCLE
%token T_CLASS
%token T_COLOR
%token T_CONE
%token T_CYLINDER
%token T_DEFINE
%token T_DIFFERENCE
%token T_EXTENDS
%token T_FILTER
%token T_GREEN
%token T_IMAGE_FILTER
%token T_INTERSECTION
%token T_LIGHT
%token T_MATERIAL
%token T_MESH
%token T_OBJECT
%token T_OBJECT_FILTER
%token T_OUTPUT
%token T_PHONG_TRIANGLE
%token T_PLANE
%token T_RECTANGLE
%token T_RED
%token T_RENDERER
%token T_ROTATE
%token T_SCALE
%token T_SCENE
%token T_SPHERE
%token T_TORUS
%token T_TRANSLATE
%token T_TRIANGLE
%token T_TYPE
%token T_UNION
%token T_VERTEX

%type <dValue> real_expr
%type <acIdent> name
%type <acIdent> class
%type <ptVector> vector3
%type <ptVector2> vector2
%type <ptVector> vertex_instance
%type <ptColor> color_def
%type <ptColor> color_instance
%type <ptScene> scene_def
%type <ptScene> scene_instance
%type <ptCamera> camera_def
%type <ptCamera> camera_instance
%type <ptBsdf> bsdf_def
%type <ptBsdf> bsdf_instance
%type <ptRenderer> renderer_def
%type <ptRenderer> renderer_instance
%type <ptLight> light_def
%type <ptLight> light_instance
%type <ptMaterial> material_def
%type <ptMaterial> material_instance
%type <ptIFilter> ifilter_def
%type <ptIFilter> ifilter_instance
%type <ptOFilter> ofilter_def
%type <ptOFilter> ofilter_instance
%type <ptObject> object
%type <ptObject> object_def
%type <ptObject> object_instance
%type <ptObject> plane_def
%type <ptObject> plane_instance
%type <ptObject> sphere_def
%type <ptObject> sphere_instance
%type <ptObject> triangle_def
%type <ptObject> triangle_instance
%type <ptObject> phong_triangle_def
%type <ptObject> phong_triangle_instance
%type <ptObject> rectangle_def
%type <ptObject> rectangle_instance
%type <ptObject> circle_def
%type <ptObject> circle_instance
%type <ptObject> aggregate_def
%type <ptObject> aggregate_instance
%type <ptObject> box_def
%type <ptObject> box_instance
%type <ptObject> cylinder_def
%type <ptObject> cylinder_instance
%type <ptObject> cone_def
%type <ptObject> cone_instance
%type <ptObject> torus_def
%type <ptObject> torus_instance
%type <ptObject> mesh_def
%type <ptObject> mesh_instance
%type <ptAtmObject> atm_object_def
%type <ptAtmObject> atm_object_instance
%type <ptImageIO> image_io_instance

%left '+' '-'
%left '*' '/'
%right UNARY_MINUS

%start everything

%%

everything		: /* Nothing */
			| everything instance
			| everything definition
			;

instance		: T_SCENE scene_instance
                          {}
                        | T_ATM_OBJECT atm_object_instance
                          {
                            SCENE->atmosphere()->addObject ($2);
                          }
			| object
                          {
                            _ptWorld->add ($1);
                          }
			;
                        
definition		: T_DEFINE T_COLOR color_def
			  {}
			| T_DEFINE T_OBJECT object_def
			  {}
			| T_DEFINE T_SCENE scene_def
			  {}
			| T_DEFINE T_CAMERA camera_def
			  {}
			| T_DEFINE T_LIGHT light_def
			  {}
			| T_DEFINE T_BSDF bsdf_def
			  {}
			| T_DEFINE T_IMAGE_FILTER ifilter_def
			  {}
			| T_DEFINE T_OBJECT_FILTER ofilter_def
			  {}
			| T_DEFINE T_RENDERER renderer_def
			  {}
			| T_DEFINE T_MATERIAL material_def
			  {}
			| T_DEFINE T_PLANE plane_def
			  {}
			| T_DEFINE T_SPHERE sphere_def
			  {}
			| T_DEFINE T_TRIANGLE triangle_def
			  {}
			| T_DEFINE T_PHONG_TRIANGLE phong_triangle_def
			  {}
			| T_DEFINE T_RECTANGLE rectangle_def
			  {}
			| T_DEFINE T_CIRCLE circle_def
			  {}
			| T_DEFINE T_AGGREGATE aggregate_def
			  {}
			| T_DEFINE T_BOX box_def
			  {}
			| T_DEFINE T_CYLINDER cylinder_def
			  {}
			| T_DEFINE T_CONE cone_def
			  {}
			| T_DEFINE T_TORUS torus_def
			  {}
			| T_DEFINE T_MESH mesh_def
			  {}
			| T_DEFINE T_ATM_OBJECT atm_object_def
			  {}
			;

object                  : T_OBJECT object_instance
                          {
                            $$ = $2;
                          }
			| T_PLANE plane_instance
			  {
                            $$ = $2;
                          }
			| T_SPHERE sphere_instance
			  {
			    $$ = $2;
			  }
			| T_TRIANGLE triangle_instance
			  {
			    $$ = $2;
                          }
			| T_PHONG_TRIANGLE phong_triangle_instance
			  {
			    $$ = $2;
                          }
			| T_RECTANGLE rectangle_instance
			  {
			    $$ = $2;
                          }
			| T_CIRCLE circle_instance
			  {
			    $$ = $2;
                          }
                        | T_AGGREGATE aggregate_instance
                          {
                            $$ = $2;
                          }
			| T_BOX box_instance
			  {
			    $$ = $2;
                          }
			| T_CYLINDER cylinder_instance
			  {
			    $$ = $2;
                          }
			| T_CONE cone_instance
			  {
			    $$ = $2;
                          }
                        | T_TORUS torus_instance
                          {
                            $$ = $2;
                          }
                        | T_MESH mesh_instance
                          {
                            $$ = $2;
                          }
			;

real_expr		: T_REAL
			  {
			    $$ = $1;
			  }
			| T_IDENTIFIER '(' ')'
			  {
                            if ( _tFunctionMap.find ($1) == _tFunctionMap.end() )
                            {
			      yyerror ("function does not exist");
			      exit (1);
                            }
			    _pfFunction = _tFunctionMap [$1];
			    $$ = (*_pfFunction)();
			  }
			| real_expr '+' real_expr
			  {
			    $$ = $1 + $3;
			  }
			| real_expr '-' real_expr
			  {
			    $$ = $1 - $3;
			  }
			| real_expr '*' real_expr
			  {
			    $$ = $1 * $3;
			  }
			| real_expr '/' real_expr
			  {
			    $$ = $1 / $3;
			  }
			| '-' real_expr %prec UNARY_MINUS
			  {
			    $$ = -$2;
			  }
			| '(' real_expr ')'
			  {
			    $$ = $2;
			  }
			;

vector3			: '<' real_expr ',' real_expr ',' real_expr '>'
			  {
			    _tVector.set ($2, $4, $6);
			    $$ = &_tVector;
			  }
			;

vector2			: '<' real_expr ',' real_expr '>'
			  {
			    _tVector2.set ($2, $4);
			    $$ = &_tVector2;
			  }
			;

vertex_instance		: vector3
			  {
			    $$ = $1;
			  }
			| T_VERTEX vector3
			  {
			    $$ = $2;
			  }
			;

name			: /* Nothing */
			  {
			    strcpy ($$, "");
			  }
			| T_IDENTIFIER
			  {
			    strcpy ($$, $1);
			  }
			;

class			: /* Nothing */
			  {
			    strcpy ($$, "");
			  }
			| ':' T_EXTENDS T_IDENTIFIER
			  {
                            if ( _tObjectMap.find ($3) == _tObjectMap.end() )
                            {
			      yyerror ("trying to extend from non existing object");
			      exit (1);
                            }
                            _ptParent = _tObjectMap [$3];
			    strcpy ($$, _ptParent->className().c_str());
			  }
			| ':' T_CLASS T_IDENTIFIER
			  {
			    _ptParent = NULL;
			    strcpy ($$, $3);
			  }
			;

params			: /* Nothing */
			| params param
			;

param			: T_IDENTIFIER vector3
			  {
			    _nAttrib.pvValue = $2;
			    SetParameter ($1, FX_VECTOR);
			  }
			| T_IDENTIFIER vector2
			  {
			    _nAttrib.pvValue = $2;
			    SetParameter ($1, FX_VECTOR2);
			  }
			| T_IDENTIFIER real_expr
			  {
			    _nAttrib.dValue = $2;
			    SetParameter ($1, FX_REAL);
			  }
			| T_IDENTIFIER T_BOOL
			  {
			    _nAttrib.gValue = $2;
			    SetParameter ($1, FX_BOOL);
			  }
			| T_IDENTIFIER T_QUOTED_STRING
			  {
			    _nAttrib.pvValue = $2;
			    SetParameter ($1, FX_STRING);
			  }
			| T_IDENTIFIER color_instance
			  {
			    _nAttrib.pvValue = $2;
			    SetParameter ($1, FX_COLOR);
			  }
			| T_COLOR color_instance
			  {
			    _nAttrib.pvValue = $2;
			    SetParameter ("color", FX_COLOR);
			  }
			| T_IDENTIFIER camera_instance
			  {
			    _nAttrib.pvValue = $2;
			    SetParameter ($1, FX_CAMERA);
			  }
			| T_CAMERA camera_instance
			  {
			    _nAttrib.pvValue = $2;
			    SetParameter ("camera", FX_CAMERA);
			  }
			| T_IDENTIFIER renderer_instance
			  {
			    _nAttrib.pvValue = $2;
			    SetParameter ($1, FX_RENDERER);
			  }
			| T_RENDERER renderer_instance
			  {
			    _nAttrib.pvValue = $2;
			    SetParameter ("renderer", FX_RENDERER);
			  }
			| T_IDENTIFIER bsdf_instance
			  {
			    _nAttrib.pvValue = $2;
			    SetParameter ($1, FX_BSDF);
			  }
			| T_BSDF bsdf_instance
			  {
			    _nAttrib.pvValue = $2;
			    SetParameter ("bsdf", FX_BSDF);
			  }
			;

entity_params		: /* Nothing */
			| entity_params entity_param
			;

entity_param		: T_TRANSLATE vector3
			  {
			    ENTITY->translate (*$2);
			  }
			| T_ROTATE vector3
			  {
			    ENTITY->rotate (*$2);
			  }
			| param
			;

volume_param		: T_SCALE vector3
			  {
			    VOLUME->scale (*$2, TVector (0, 0, 0));
			  }
			| entity_param
			;

object_params		: /* Nothing */
			| object_params object_param
			;

object_param		: T_MATERIAL material_instance
			  {
			    OBJECT->setMaterial ($2);
			  }
			| T_FILTER ofilter_instance
			  {
			    OBJECT->addFilter ($2);
			  }
			| volume_param
			;

color_def		: name class
			  {
                            if ( $1 == "" )
                            {
                              yyerror ("cannot define unnamed color");
                              exit (1);
                            }

                            if ( _tColorMap.find ($1) != _tColorMap.end() )
                            {
                              yyerror ("cannot redefine an existing color");
                              exit (1);
                            }

                            _tColor = TColor::_black();

                            _ptParent = NULL;
			  }
			  '{' color_params '}'
			  {
                            _tColorMap [$1] = _tColor;
                            
                            $$ = &_tColor;
			  }
			;

color_instance		: name
			  {
                            if ( $1 == "" )
                            {
                              yyerror ("instanced object cannot be unnamed");
                              exit (1);
                            }

                            if ( _tColorMap.find ($1) == _tObjectMap.end() )
                            {
                              yyerror ("color does not exist");
                              exit (1);
                            }

                            $$ = (TColor*) &(_tColorMap [$1]);
			  }
			| class
			  {
                            _tColor = TColor::_black();
			  }
			  '{' color_params '}'
			  {
			    $$ = (TColor*) &_tColor;
			  }
			;

color_params		: /* Nothing */
			| color_params color_param
			;

color_param		: T_RED real_expr
			  {
			    _tColor.setRed ($2);
			  }
			| T_GREEN real_expr
			  {
			    _tColor.setGreen ($2);
			  }
			| T_BLUE real_expr
			  {
			    _tColor.setBlue ($2);
			  }
			;

image_io_instance      	: '{'
                          {
                            _tDataStack.push (TImageManager::_getImageIO ("tga"));
                          }
			  image_io_params '}'
			  {
			    $$ = (TImageIO*) _tDataStack.POP();
			  }
			;

image_io_params		: /* Nothing */
			| image_io_params image_io_param
			;

image_io_param		: T_TYPE T_QUOTED_STRING
			  {
                            _ptImageIO = (TImageIO*) _tDataStack.POP();
                            delete _ptImageIO;
                            
                            _ptImageIO = TImageManager::_getImageIO ($2);
                            if ( !_ptImageIO )
                            {
                              yyerror ("Image output type not available");
                              exit (1);
                            }
                            _tDataStack.push (_ptImageIO);
			  }
			| param
			;

scene_def		: name class
			  {
			    DefineObject ($1, $2, "Scene");
			  }
			  '{' scene_params '}'
			  {
			    $$ = (TScene*) UpdateObject ($1);
			  }
			;

scene_instance		: name
			  {
			    $$ = (TScene*) InstanceObject ($1);
			    TSceneRT::_ptParsedScene = $$;
			  }
			| class
			  {
//			    CreateObject ($1, "Scene");
			    _ptData = TSceneRT::_ptParsedScene;
			    _tDataStack.push (_ptData);
			  }
			  '{' scene_params '}'
			  {
			    $$ = (TScene*) _tDataStack.POP();
//			    $$ = &tScene;
			  }
			;

scene_params		: /* Nothing */
			| scene_params scene_param
			;

scene_param		: T_LIGHT light_instance
			  {
			    SCENE->addLight ($2);
			  }
			| T_FILTER ifilter_instance
			  {
			    SCENE->addImageFilter ($2);
			  }
			| T_OUTPUT image_io_instance
			  {
			    SCENE->setImageOutput ($2);
			  }
			| param
			;

camera_def		: name class
			  {
			    DefineObject ($1, $2, "PinholeCamera");
			  }
			  '{' entity_params '}'
			  {
			    $$ = (TCamera*) UpdateObject ($1);
			  }
			;

camera_instance		: name
			  {
			    $$ = (TCamera*) InstanceObject ($1);
			  }
			| class
			  {
			    CreateObject ($1, "PinholeCamera");
			  }
			  '{' entity_params '}'
			  {
			    $$ = (TCamera*) _tDataStack.POP();
			  }
			;

light_def		: name class
			  {
			    DefineObject ($1, $2, "PointLight");
			  }
			  '{' entity_params '}'
			  {
			    $$ = (TLight*) UpdateObject ($1);
			  }
			;

light_instance		: name
			  {
			    $$ = (TLight*) InstanceObject ($1);
			  }
			| class
			  {
			    CreateObject ($1, "PointLight");
			  }
			  '{' entity_params '}'
			  {
			    $$ = (TLight*) _tDataStack.POP();
			  }
			;

bsdf_def		: name class
			  {
			    DefineObject ($1, $2, "BsdfPhong");
			  }
			  '{' params '}'
			  {
			    $$ = (TBsdf*) UpdateObject ($1);
			  }
			;

bsdf_instance		: name
			  {
			    $$ = (TBsdf*) InstanceObject ($1);
			  }
			| class
			  {
                            CreateObject ($1, "BsdfPhong");
			  }
			  '{' params '}'
			  {
                            $$ = (TBsdf*) _tDataStack.POP();
			  }
			;

renderer_def		: name class
			  {
			    DefineObject ($1, $2, "Raytracer");
			  }
			  '{' params '}'
			  {
			    $$ = (TRenderer*) UpdateObject ($1);
			  }
			;

renderer_instance	: name
			  {
			    $$ = (TRenderer*) InstanceObject ($1);
			  }
			| class
			  {
			    CreateObject ($1, "Raytracer");
			  }
			  '{' params '}'
			  {
			    $$ = (TRenderer*) _tDataStack.POP();
			  }
			;

material_def		: name class
			  {
			    DefineObject ($1, $2, "Material");
			  }
			  '{' params '}'
			  {
                            $$ = (TMaterial*) UpdateObject ($1);
			  }
			;

material_instance	: name
			  {
			    $$ = (TMaterial*) InstanceObject ($1);
			  }
			| class
			  {
			    CreateObject ($1, "Material");
			  }
			  '{' params '}'
			  {
			    $$ = (TMaterial*) _tDataStack.POP();

			  }
			;

ifilter_def		: name class
			  {
			    DefineObject ($1, $2, "");
			  }
			  '{' params '}'
			  {
			    $$ = (TImageFilter*) UpdateObject ($1);
			  }
			;

ifilter_instance	: name
			  {
			    $$ = (TImageFilter*) InstanceObject ($1);
			  }
			| class
			  {
			    CreateObject ($1, "");
			  }
			  '{' params '}'
			  {
			    $$ = (TImageFilter*) _tDataStack.POP();
			  }
			;

ofilter_def		: name class
			  {
			    DefineObject ($1, $2, "");
			  }
			  '{' params '}'
			  {
			    $$ = (TObjectFilter*) UpdateObject ($1);
			  }
			;

ofilter_instance	: name
			  {
			    $$ = (TObjectFilter*) InstanceObject ($1);
			  }
			| class
			  {
			    CreateObject ($1, "");
			  }
			  '{' params '}'
			  {
			    $$ = (TObjectFilter*) _tDataStack.POP();
			  }
			;

object_def		: name class
			  {
			    DefineObject ($1, $2, "");
			  }
			  '{' object_params '}'
			  {
			    $$ = (TObject*) UpdateObject ($1);
			  }
			;

object_instance		: name
			  {
			    $$ = (TObject*) InstanceObject ($1);
			  }
			| class
			  {
			    CreateObject ($1, "");
			  }
			  '{' object_params '}'
			  {
			    $$ = (TObject*) _tDataStack.POP();
			  }
			;

plane_def		: name class
			  {
			    DefineObject ($1, $2, "Plane");
			  }
			  '{' object_params '}'
			  {
			    $$ = (TPlane*) UpdateObject ($1);
			  }
			;

plane_instance		: name
			  {
			    $$ = (TPlane*) InstanceObject ($1);
			  }
			| class
			  {
			    CreateObject ($1, "Plane");
			  }
			  '{' object_params '}'
			  {
			    $$ = (TPlane*) _tDataStack.POP();
			  }
			;

sphere_def		: name class
			  {
			    DefineObject ($1, $2, "Sphere");
			  }
			  '{' object_params '}'
			  {
			    $$ = (TSphere*) UpdateObject ($1);
			  }
			;

sphere_instance		: name
			  {
			    $$ = (TSphere*) InstanceObject ($1);
			  }
			| class
			  {
			    CreateObject ($1, "Sphere");
			  }
			  '{' object_params '}'
			  {
			    $$ = (TSphere*) _tDataStack.POP();
			  }
			;

triangle_def		: name class
			  {
			    DefineObject ($1, $2, "Triangle");
			    _bVertices = 0;
			  }
			  '{' triangle_params '}'
			  {
			    if ( _bVertices != 3 )
			    {
			      yyerror ("wrong number of vertices in triangle");
			      exit (1);
			    }
			    $$ = (TTriangle*) UpdateObject ($1);
			  }
			;

triangle_instance	: name
			  {
			    $$ = (TTriangle*) InstanceObject ($1);
			  }
			| class
			  {
			    CreateObject ($1, "Triangle");
			    _bVertices = 0;
			  }
			  '{' triangle_params '}'
			  {
			    if ( _bVertices != 3 )
			    {
			      yyerror ("wrong number of vertices in triangle");
			      exit (1);
			    }
			    $$ = (TTriangle*) _tDataStack.POP();
			  }
			;

triangle_params		: /* Nothing */
			| triangle_params triangle_param
			;

triangle_param		: vertex_instance
			  {
			    TRIANGLE->setVertex (*$1);
			    _bVertices++;
			  }
			| object_param
			;

phong_triangle_def	: name class
			  {
			    DefineObject ($1, $2, "PhongTriangle");
			    _bVertices = 0;
			  }
			  '{' phong_triangle_params '}'
			  {
			    if ( _bVertices != 3 )
			    {
			      yyerror ("wrong number of vertices in phong_triangle");
			      exit (1);
			    }
			    $$ = (TPhongTriangle*) UpdateObject ($1);
			  }
			;

phong_triangle_instance	: name
			  {
			    $$ = (TPhongTriangle*) InstanceObject ($1);
			  }
			| class
			  {
			    CreateObject ($1, "PhongTriangle");
			    _bVertices = 0;
			  }
			  '{' phong_triangle_params '}'
			  {
			    if ( _bVertices != 3 )
			    {
			      yyerror ("wrong number of vertices in phong_triangle");
			      exit (1);
			    }
			    $$ = (TPhongTriangle*) _tDataStack.POP();
			  }
			;

phong_triangle_params	: /* Nothing */
			| phong_triangle_params phong_triangle_param
			;

phong_triangle_param	: vertex_instance
			  {
			    TRIANGLE->setVertex (*$1);
			    _bVertices++;
			  }
			| object_param
			;

rectangle_def		: name class
			  {
			    DefineObject ($1, $2, "Rectangle");
			    _bVertices = 0;
			  }
			  '{' rectangle_params '}'
			  {
			    if ( _bVertices != 4 )
			    {
			      yyerror ("wrong number of vertices in rectangle");
			      exit (1);
			    }
			    $$ = (TRectangle*) UpdateObject ($1);
			  }
			;

rectangle_instance	: name
			  {
			    $$ = (TRectangle*) InstanceObject ($1);
			  }
			| class
			  {
			    CreateObject ($1, "Rectangle");
			    _bVertices = 0;
			  }
			  '{' rectangle_params '}'
			  {
			    if ( _bVertices != 4 )
			    {
			      yyerror ("wrong number of vertices in rectangle");
			      exit (1);
			    }
			    $$ = (TRectangle*) _tDataStack.POP();
			  }
			;

rectangle_params	: /* Nothing */
			| rectangle_params rectangle_param
			;

rectangle_param		: vertex_instance
			  {
			    RECTANGLE->setVertex (*$1);
			    _bVertices++;
			  }
			| object_param
			;

circle_def		: name class
			  {
			    DefineObject ($1, $2, "Circle");
			  }
			  '{' object_params '}'
			  {
			    $$ = (TCircle*) UpdateObject ($1);
			  }
			;

circle_instance		: name
			  {
			    $$ = (TCircle*) InstanceObject ($1);
			  }
			| class
			  {
			    CreateObject ($1, "Circle");
			  }
			  '{' object_params '}'
			  {
			    $$ = (TCircle*) _tDataStack.POP();
			  }
			;

aggregate_params       	: /* Nothing */
			| aggregate_params aggregate_param
			;

aggregate_param		: object
			  {
			    AGGREGATE->add ($1);
			  }
			| object_param
			;

aggregate_def		: name class
			  {
			    DefineObject ($1, $2, "Aggregate");
			  }
			  '{' aggregate_params '}'
			  {
			    $$ = (TAggregate*) UpdateObject ($1);
			  }
			;

aggregate_instance     	: name
			  {
			    $$ = (TAggregate*) InstanceObject ($1);
			  }
			| class
			  {
			    CreateObject ($1, "Aggregate");
			  }
			  '{' aggregate_params '}'
			  {
			    $$ = (TAggregate*) _tDataStack.POP();
			  }
			;

atm_object_def		: name class
			  {
			    DefineObject ($1, $2, "AtmConst");
			  }
			  '{' params '}'
			  {
			    $$ = (TAtmosphericObject*) UpdateObject ($1);
			  }
			;

atm_object_instance	: name
			  {
			    $$ = (TAtmosphericObject*) InstanceObject ($1);
			  }
			| class
			  {
			    CreateObject ($1, "AtmConst");
			  }
			  '{' params '}'
			  {
			    $$ = (TAtmosphericObject*) _tDataStack.POP();
			  }
			;

box_def			: name class
			  {
			    DefineObject ($1, $2, "Box");
			  }
			  '{' object_params '}'
			  {
			    $$ = (TBox*) UpdateObject ($1);
			  }
			;

box_instance		: name
			  {
			    $$ = (TBox*) InstanceObject ($1);
			  }
			| class
			  {
			    CreateObject ($1, "Box");
			  }
			  '{' object_params '}'
			  {
			    $$ = (TBox*) _tDataStack.POP();
			  }
			;

cylinder_def		: name class
			  {
			    DefineObject ($1, $2, "Cylinder");
			  }
			  '{' object_params '}'
			  {
			    $$ = (TCylinder*) UpdateObject ($1);
			  }
			;

cylinder_instance	: name
			  {
			    $$ = (TCylinder*) InstanceObject ($1);
			  }
			| class
			  {
			    CreateObject ($1, "Cylinder");
			  }
			  '{' object_params '}'
			  {
			    $$ = (TCylinder*) _tDataStack.POP();
			  }
			;

cone_def		: name class
			  {
			    DefineObject ($1, $2, "Cone");
			  }
			  '{' object_params '}'
			  {
			    $$ = (TCone*) UpdateObject ($1);
			  }
			;

cone_instance		: name
			  {
			    $$ = (TCone*) InstanceObject ($1);
			  }
			| class
			  {
			    CreateObject ($1, "Cone");
			  }
			  '{' object_params '}'
			  {
			    $$ = (TCone*) _tDataStack.POP();
	       		  }
			;

torus_def   		: name class
			  {
			    DefineObject ($1, $2, "Torus");
			  }
			  '{' object_params '}'
			  {
			    $$ = (TTorus*) UpdateObject ($1);
			  }
			;

torus_instance      	: name
			  {
			    $$ = (TTorus*) InstanceObject ($1);
			  }
			| class
			  {
			    CreateObject ($1, "Torus");
			  }
			  '{' object_params '}'
			  {
			    $$ = (TTorus*) _tDataStack.POP();
			  }
			;

mesh_def   		: name class
			  {
			    DefineObject ($1, $2, "Mesh");
			  }
			  '{' mesh_params '}'
			  {
			    $$ = (TMeshObject*) UpdateObject ($1);
			  }
			;

mesh_instance      	: name
			  {
			    $$ = (TMeshObject*) InstanceObject ($1);
			  }
			| class
			  {
			    CreateObject ($1, "Mesh");
			  }
			  '{' mesh_params '}'
			  {
			    $$ = (TMeshObject*) _tDataStack.POP();
			  }
			;

mesh_params		: /* Nothing */
			| mesh_params mesh_param
			;

mesh_param		: T_TRIANGLE triangle_instance
			  {
			    MESH->addTriangle ((TTriangle*) $2);
                            delete $2;
			  }
			| object_param
			;

%%

void rt_error (const char* pkcTEXT)
{

  cerr << endl << TSceneRT::_tInputFileName << "(" << TSceneRT::_dwLineNumber << ") Error: " << pkcTEXT << endl;

}  /* rt_error() */


void RT_InitParser (void)
{

  InitObjects();
  InitFunctions();

  _ptWorld = new TAggregate();
  
  TSceneRT::_ptParsedScene->setWorld (_ptWorld);
  
}  /* RT_InitParser() */


void RT_CloseParser (void)
{

  _tObjectMap.clear();

}  /* RT_CloseParser() */


void InitFunctions (void)
{

  _tFunctionMap ["rand"] = (double(*)(void)) &frand;

}  /* InitFunctions() */


void InitObjects (void)
{
}  /* InitObjects() */


TProcedural* NewObject (const string& rktCLASS, const TProcedural* pktPARENT)
{

  TProcedural*   ptChild;

//  cout << "New object : \"" << rktCLASS << "\"" << endl;

  ptChild = (TProcedural*) TClassManager::_newObject (rktCLASS, pktPARENT);
  if ( !ptChild )
  {
    string   tMessage = string ("class ") + rktCLASS + " does not exist";
    yyerror (tMessage.c_str());
    exit (1);
  }

  return ptChild;

}  /* NewObject() */


void* InstanceObject (const string& rktNAME)
{

  void*   pvObject;

  if ( rktNAME == "" )
  {
    yyerror ("instanced object cannot be unnamed");
    exit (1);
  }

  if ( _tObjectMap.find (rktNAME) == _tObjectMap.end() )
  {
    yyerror ("object does not exist");
    exit (1);
  }

  pvObject = _tObjectMap [rktNAME];

  return pvObject;

}  /* InstanceObject() */


void* UpdateObject (const string& rktNAME)
{

  TProcedural*   ptObject;

//  cout << "Updating object : \"" << rktNAME << "\"" << endl;

  ptObject = _tDataStack.POP();

  _tObjectMap [rktNAME] = ptObject;

  return ptObject;

}  /* UpdateObject() */


void DefineObject (const string& rktNAME, const string& rktCLASS, const string& rktDEF_CLASS)
{

//  cout << "Defining object : \"" << rktNAME << "\", \"" << rktCLASS << "\", \"" << rktDEF_CLASS << "\"" << endl;

  if ( rktNAME == "" )
  {
    yyerror ("defined object cannot be unnamed");
    exit (1);
  }

  if ( _tObjectMap.find (rktNAME) != _tObjectMap.end() )
  {
    yyerror ("cannot redefine an existing object");
    exit (1);
  }

  if ( rktCLASS == "" )
  {
    _ptData = NewObject (rktDEF_CLASS, _ptParent);
  }
  else
  {
    _ptData = NewObject (rktCLASS, _ptParent);
  }

  _tDataStack.push (_ptData);
  _ptParent = NULL;

}  /* DefineObject() */


void CreateObject (const string& rktCLASS, const string& rktDEF_CLASS)
{

//  cout << "Creating object : \"" << rktCLASS << "\", \"" << rktDEF_CLASS << "\"" << endl;
  
  if ( rktCLASS == "" )
  {
    _ptData = NewObject (rktDEF_CLASS, _ptParent);
  }
  else
  {
    _ptData = NewObject (rktCLASS, _ptParent);
  }

  _tDataStack.push (_ptData);
  _ptParent = NULL;

}  /* CreateObject() */


void SetParameter (const string& rktATTRIB, EAttribType eTYPE)
{

  int   iResult;

  iResult = DATA->setAttribute (rktATTRIB, _nAttrib, eTYPE);

  if ( iResult == FX_ATTRIB_WRONG_PARAM )
  {
    yyerror ("object does not have such parameter");
    exit (1);
  }
  else if ( iResult == FX_ATTRIB_WRONG_TYPE )
  {
    yyerror ("incorrect type in parameter value");
    exit (1);
  }
  else if ( iResult == FX_ATTRIB_USER_ERROR )
  {
    yyerror (TProcedural::_tUserErrorMessage.c_str());
    exit (1);
  }

}  /* SetParameter() */
