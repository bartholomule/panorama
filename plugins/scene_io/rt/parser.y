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
#include <cstring>
#include <iostream>
#include "llapi/llapi_all.h"
#include "hlapi/hlapi_all.h"
#include "hlapi/class_manager.h"
#include "hlapi/plugins_all.h"
#include "parser_defs.h"
#include "rt_io.h"

static map<string, TProcedural*, less<string> >       _tObjectMap;
static map<string, TColor, less<string> >             _tColorMap;
static map<string, TVector, less<string> >            _tVectorMap;
static map<string, double(*)(void), less<string> >    _tFunctionMap;
static map<string, EClass, less<string> >             _tTypeMap;
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
#define VECTOR		((TVector*) _tDataStack.top())
#define COLOR		((TColor*) _tDataStack.top())
#define SCENE		(TSceneRT::_ptParsedScene)
#define MATERIAL	((TMaterial*) _tDataStack.top())
#define OBJECT		((TObject*) _tDataStack.top())
#define AGGREGATE	((TAggregate*) _tDataStack.top())
#define TRIANGLE	((TTriangle*) _tDataStack.top())
#define RECTANGLE	((TRectangle*) _tDataStack.top())
#define MESH		((TMeshObject*) _tDataStack.top())

#define YYDEBUG 1
#define YYERROR_VERBOSE 

static TProcedural* NewObject (const string& rktCLASS, const TProcedural* pktPARENT);
static void* InstanceObject (const string& rktNAME);
static void* UpdateObject (const string& rktNAME);
static void DefineObject (const string& rktNAME, const string& rktCLASS, const string& rktDEF_CLASS);
static void CreateObject (const string& rktCLASS, const string& rktDEF_CLASS);
static void SetParameter (const string& rktATTRIB, EAttribType eTYPE);

static void DefineColor (const string& rktNAME);
static TColor* InstanceColor (const string& rktNAME);

static void DefineVector (const string& rktNAME);
static TVector* InstanceVector (const string& rktNAME);

static void UpdateAttribute (const string& rktATTRIBUTE, const string& rktIDENT);

static void InitObjects (void);
static void InitFunctions (void);

static EAttribType MapClassToAttribute (const TBaseClass* pktClass);

static string EAttribType_to_str (EAttribType eat);
 
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
         TPattern*             ptPattern;
         TPerturbation*        ptPerturbation; 
         TObject*              ptObject;
         TImageFilter*         ptIFilter;
         TObjectFilter*        ptOFilter;
         TAtmosphericObject*   ptAtmObject;
         TImageIO*             ptImageIO;
       }

%token <gValue> T_BOOL
%token <dValue> T_REAL
%token <iValue> T_INTEGER
%token <acIdent> T_IDENTIFIER
%token <acIdent> T_QUOTED_STRING

/* "Reserved word" tokens.
   Modified to all act the same as identifiers (KH--07Aug2000)  */
%token <acIdent> T_AGGREGATE
%token <acIdent> T_ATM_OBJECT
%token <acIdent> T_BLUE
%token <acIdent> T_BOX
%token <acIdent> T_BSDF
%token <acIdent> T_CAMERA
%token <acIdent> T_CIRCLE
%token <acIdent> T_CLASS
%token <acIdent> T_COLOR
%token <acIdent> T_CONE
%token <acIdent> T_CYLINDER
%token <acIdent> T_DEFINE
%token <acIdent> T_DIFFERENCE
%token <acIdent> T_EXTENDS
%token <acIdent> T_FILTER
%token <acIdent> T_GREEN
%token <acIdent> T_IMAGE_FILTER
%token <acIdent> T_INTERSECTION
%token <acIdent> T_LIGHT
%token <acIdent> T_MATERIAL
%token <acIdent> T_MESH
%token <acIdent> T_OBJECT
%token <acIdent> T_OBJECT_FILTER
%token <acIdent> T_OUTPUT
%token <acIdent> T_PATTERN
%token <acIdent> T_PERTURBATION
%token <acIdent> T_PHONG_TRIANGLE
%token <acIdent> T_PLANE
%token <acIdent> T_RECTANGLE
%token <acIdent> T_RED
%token <acIdent> T_RENDERER
%token <acIdent> T_ROTATE
%token <acIdent> T_SCALE
%token <acIdent> T_SCENE
%token <acIdent> T_SPHERE
%token <acIdent> T_TORUS
%token <acIdent> T_TRANSLATE
%token <acIdent> T_TRIANGLE
%token <acIdent> T_TYPE
%token <acIdent> T_UNION
%token <acIdent> T_VECTOR
%token <acIdent> T_VERTEX
%token <acIdent> T_X
%token <acIdent> T_Y
%token <acIdent> T_Z
/* Tokens to allow user requested information about types/attribute lists.
   Added 06/Aug/2000 */ 
%token <acIdent> T_ATTR_LIST
%token <acIdent> T_ATTR_TYPE
%type <acIdent> reserved_words
%type <acIdent> potential_string

%type <dValue> real_expr
%type <acIdent> name
%type <acIdent> class
%type <ptColor> color
%type <ptVector> vector3
%type <ptVector2> vector2
%type <ptVector> vertex_instance
%type <ptVector> vector_def
%type <ptVector> vector_instance
%type <ptColor> color_def
//%type <ptColor> color_instance
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
%type <ptPattern> pattern_def
%type <ptPattern> pattern_instance
%type <ptPerturbation> perturbation_def
%type <ptPerturbation> perturbation_instance
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
%type <ptObject> csg_def
%type <ptObject> csg_instance
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
			    // Sanity check to avoid adding an object more than
			    // once. 
			    if( !_ptWorld->containsObject( $1 ) )
			    {
			      _ptWorld->add ($1);
			    }
			    else
			    {
			      // Somehow, the object was added more than
			      // once... 
			      string s = "This object is already in the scene: ";
			      rt_error(s + $1->className());
			    }
                          }
			;
                        
definition		: T_DEFINE T_COLOR color_def
			  {}
			| T_DEFINE T_VECTOR vector_def
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
			| T_DEFINE T_PATTERN pattern_def
			  {}
                        | T_DEFINE T_PERTURBATION perturbation_def
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
			| T_DEFINE T_UNION csg_def
			  {}
			| T_DEFINE T_INTERSECTION csg_def
			  {}
			| T_DEFINE T_DIFFERENCE csg_def
			  {}
			;

object                  : T_OBJECT object_instance
                          {
                            $$ = $2;
                          }
			| T_LIGHT light_instance
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
                        | T_UNION csg_instance
			  {
                            ((TCsg*) $2)->setOperation (FX_CSG_UNION);
                            $$ = $2;
                          }
                        | T_INTERSECTION csg_instance
			  {
                            ((TCsg*) $2)->setOperation (FX_CSG_INTERSECTION);
                            $$ = $2;
                          }
                        | T_DIFFERENCE csg_instance
			  {
                            ((TCsg*) $2)->setOperation (FX_CSG_DIFFERENCE);
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
color                   : '{' T_RED real_expr T_GREEN real_expr T_BLUE real_expr '}'
                          {
			    _tColor.setRed ($3);
			    _tColor.setGreen ($5);
			    _tColor.setBlue ($7);
			    $$ = (TColor*) &_tColor;
			  }
                       ;

vector3                 : '<' real_expr ',' real_expr ',' real_expr '>'
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

param			: T_ATTR_LIST '(' ')' 
                          {
			    /* Print out an attribute list [names w/types] for
			       the current object */ 
			    TAttributeList   tal;
			  
			    DATA->getAttributeList (tal);
			    
			    cout << "Requested attribute list for \""
				 << DATA->className() << "\"" << endl;
			    
			    for(TAttributeList::const_iterator i = tal.begin();
				i != tal.end();
				++i)
			    {
			      cout << "  ("
				   << EAttribType_to_str (i->second)
				   << ") "
				   << i->first << endl;
			    }
			  }
                        | T_ATTR_TYPE '(' potential_string ')' 
                          {
			    /* Print out the type of the given attribute */
			    TAttributeList                   tal;
			    TAttributeList::const_iterator   loc;
			    
			    DATA->getAttributeList (tal);
			    
			    loc = tal.find (string($3)); 
			    
			    cout << "Requested attribute type for \"" << $3
				 << "\" in \"" << DATA->className() << "\": ";
			    
			    if ( loc != tal.end() )
			    {
			      cout << EAttribType_to_str (loc->second) << endl;
			    }
			    else
			    {
			      cout << "no such attribute" << endl;
			    }
			  }
                        | T_IDENTIFIER vector3
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
			| T_IDENTIFIER pattern_instance
			  {
			    _nAttrib.pvValue = $2;
			    SetParameter ($1, MapClassToAttribute ((TBaseClass*) $2));
                          }
			| T_IDENTIFIER perturbation_instance
			  {
			    _nAttrib.pvValue = $2;
			    SetParameter ($1, MapClassToAttribute ((TBaseClass*) $2));
                          }
			| T_IDENTIFIER color
			  {
			    _nAttrib.pvValue = $2;
			    SetParameter ($1, FX_COLOR);
			  }
			| T_IDENTIFIER name
			  {
			    UpdateAttribute ($1, $2);
			  }
			| T_COLOR name
			  {
			    UpdateAttribute ("color", $2);
			  }
			| T_COLOR real_expr
			  {
			    _nAttrib.dValue = $2;
			    SetParameter ("color", FX_REAL);
			  }
			| T_COLOR color
			  {
			    _nAttrib.pvValue = $2;
			    SetParameter ("color", FX_COLOR);
			  }
			| T_COLOR pattern_instance
			  {
			    _nAttrib.pvValue = $2;
			    SetParameter ("color", FX_PATTERN);
                          }
			| T_VECTOR vector_instance
			  {
			    _nAttrib.pvValue = $2;
			    SetParameter ("vector", FX_VECTOR);
			  }
			| T_CAMERA camera_instance
			  {
			    _nAttrib.pvValue = $2;
			    SetParameter ("camera", FX_CAMERA);
			  }
			| T_RENDERER renderer_instance
			  {
			    _nAttrib.pvValue = $2;
			    SetParameter ("renderer", FX_RENDERER);
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
			| T_ROTATE real_expr ',' vector3
                          {
			    ENTITY->rotate (makeUnitQuaternion ($2, *$4));
                          }
			| T_TRANSLATE vector_instance
			  {
			    ENTITY->translate (*$2);
			  }
			| T_ROTATE vector_instance
			  {
			    ENTITY->rotate (*$2);
			  }
			| T_ROTATE real_expr ',' vector_instance
                          {
			    ENTITY->rotate (makeUnitQuaternion ($2, *$4));
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
			    DefineColor ($1);
			  }
			  '{' color_params '}'
			  {
                            _tColorMap [$1] = _tColor;
			    _tTypeMap  [$1] = FX_COLOR_CLASS;
                            
                            $$ = &_tColor;
			  }
			;


/*
color_instance		: name
			  {
			    $$ = InstanceColor ($1);
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
*/

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

vector_def		: name class
			  {
			    DefineVector ($1);
			  }
                          '{' vector_params '}'
			  {
                            _tVectorMap [$1] = _tVector;
			    _tTypeMap   [$1] = FX_VECTOR_CLASS;
                            
                            $$ = &_tVector;
			  }
			;

vector_instance		: name
			  {
			    $$ = InstanceVector ($1);
			  }
			| class
			  {
                            _tVector = TVector (0, 0, 0);
			  }
			  '{' vector_params '}'
			  {
			    $$ = (TVector*) &_tVector;
			  }
			;

vector_params		: /* Nothing */
			| vector_params vector_param
			;

vector_param		: T_X real_expr
			  {
			    _tVector.setX ($2);
			  }
			| T_Y real_expr
			  {
			    _tVector.setY ($2);
			  }
			| T_Z real_expr
			  {
			    _tVector.setZ ($2);
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
			    // This is no longer needed, as there are speial
			    // cases for this in the light_instance rule.
			    if( $2 )
			    {
			      static bool gave_warning = false;

			      if(!gave_warning)
			      {
                                cerr << "Note for light instance on line "
				     << TSceneRT::_dwLineNumber
				     << endl;
				cerr << "  Usage of lights in the 'scene' section is no longer required" << endl;
				cerr << "  They may now be added to aggregates, csg, etc., or used "
				     << endl
				     << "  external to the scene section (same syntax)." 
				     << endl;
				gave_warning = true;
			      }
			      SCENE->addLight ($2);
			    }
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
			    // This one is passed back to the scene instance...
			  }
			;

bsdf_def		: name class
			  {
			    DefineObject ($1, $2, "Bsdf");
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
                            CreateObject ($1, "Bsdf");
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

pattern_def		: name class
			  {
			    DefineObject ($1, $2, "Pattern");
			  }
			  '{' params '}'
			  {
                            $$ = (TPattern*) UpdateObject ($1);
			  }
			;

pattern_instance	: name
			  {
			    $$ = (TPattern*) InstanceObject ($1);
			  }
			| class
			  {
			    CreateObject ($1, "Pattern");
			  }
			  '{' params '}'
			  {
			    $$ = (TPattern*) _tDataStack.POP();
			  }
			;

perturbation_def       	: name class
			  {
			    DefineObject ($1, $2, "Perturbation");
			  }
			  '{' params '}'
			  {
                            $$ = (TPerturbation*) UpdateObject ($1);
			  }
			;

perturbation_instance	: name
			  {
			    $$ = (TPerturbation*) InstanceObject ($1);
			  }
			| class
			  {
			    CreateObject ($1, "Perturbation");
			  }
			  '{' params '}'
			  {
			    $$ = (TPerturbation*) _tDataStack.POP();
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

csg_def	  		: name class
			  {
			    DefineObject ($1, $2, "Csg");
			  }
			  '{' aggregate_params '}'
			  {
			    $$ = (TCsg*) UpdateObject ($1);
			  }
			;

csg_instance     	: name
			  {
			    $$ = (TCsg*) InstanceObject ($1);
			  }
			| class
			  {
			    CreateObject ($1, "Csg");
			  }
			  '{' aggregate_params '}'
			  {
			    $$ = (TCsg*) _tDataStack.POP();
			  }
			;

potential_string        : T_IDENTIFIER
			| reserved_words
			;


reserved_words          : T_AGGREGATE 
			| T_ATM_OBJECT
			| T_BLUE
			| T_BOX
			| T_BSDF
			| T_CAMERA
			| T_CIRCLE
			| T_CLASS
			| T_COLOR
			| T_CONE
			| T_CYLINDER
			| T_DEFINE
			| T_DIFFERENCE
			| T_EXTENDS
			| T_FILTER
			| T_GREEN
			| T_IMAGE_FILTER
			| T_INTERSECTION
			| T_LIGHT
			| T_MATERIAL
			| T_MESH
			| T_OBJECT
			| T_OBJECT_FILTER
			| T_OUTPUT
			| T_PATTERN
			| T_PERTURBATION
			| T_PHONG_TRIANGLE
			| T_PLANE
			| T_RECTANGLE
			| T_RED
			| T_RENDERER
			| T_ROTATE
			| T_SCALE
			| T_SCENE
			| T_SPHERE
			| T_TORUS
			| T_TRANSLATE
			| T_TRIANGLE
			| T_TYPE
			| T_UNION
			| T_VECTOR
			| T_VERTEX
			| T_X
			| T_Y
		        | T_Z
			| T_ATTR_LIST
			| T_ATTR_TYPE
			;

%%

void rt_error (const char* pkcTEXT)
{

  cerr << endl << TSceneRT::_tInputFileName << "(" << TSceneRT::_dwLineNumber << ") Error: " << pkcTEXT << endl;

}  /* rt_error() */

void rt_error (const string& rksTEXT)
{

  cerr << endl << TSceneRT::_tInputFileName << "(" << TSceneRT::_dwLineNumber << ") Error: " << rksTEXT << endl;

}  /* rt_error() */


void RT_InitParser (void)
{

  InitObjects();
  InitFunctions();

  _tColorMap.clear();
  _tVectorMap.clear();
  _tTypeMap.clear();  
  while(!_tDataStack.empty()) _tDataStack.pop();

  _ptWorld = new TAggregate();
  
  TSceneRT::_ptParsedScene->setWorld (_ptWorld);
  
}  /* RT_InitParser() */


void RT_CloseParser (void)
{

  _tObjectMap.clear();

}  /* RT_CloseParser() */


void InitFunctions (void)
{
  _tFunctionMap.clear();
  _tFunctionMap ["rand"] = (double(*)(void)) &frand;
}  /* InitFunctions() */


void InitObjects (void)
{
  _tObjectMap.clear();
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

  // cout << "Updating object : \"" << rktNAME << "\"" << endl;

  ptObject = _tDataStack.POP();

  _tObjectMap [rktNAME] = ptObject;
  _tTypeMap   [rktNAME] = ptObject->classType();

  return ptObject;

}  /* UpdateObject() */


void DefineObject (const string& rktNAME, const string& rktCLASS, const string& rktDEF_CLASS)
{

  // cout << "Defining object : \"" << rktNAME << "\", \"" << rktCLASS << "\", \"" << rktDEF_CLASS << "\"" << endl;

  if ( rktNAME == "" )
  {
    yyerror ("defined object cannot be unnamed");
    exit (1);
  }

  if ( _tTypeMap.find (rktNAME) != _tTypeMap.end() )
  {
    yyerror ("cannot redefine an existing object");
    exit (1);
  }

  if ( ( _tObjectMap.find (rktNAME) != _tObjectMap.end() ) ||
       ( _tTypeMap  .find (rktNAME) != _tTypeMap.  end() ) )
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

  // cout << "Creating object : \"" << rktCLASS << "\", \"" << rktDEF_CLASS << "\"" << endl;
  
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


void DefineColor (const string& rktNAME)
{

  if ( rktNAME == "" )
  {
    yyerror ("cannot define unnamed color");
    exit (1);
  }

  if ( _tColorMap.find (rktNAME) != _tColorMap.end() )
  {
    yyerror ("cannot redefine an existing color");
    exit (1);
  }

  if ( _tTypeMap.find (rktNAME) != _tTypeMap.end() )
  {
    yyerror ("cannot redefine an existing object");
    exit (1);
  }

  _tColor = TColor::_black();
  
  _ptParent = NULL;

}  /* DefineColor() */


TColor* InstanceColor (const string& rktNAME)
{

  TColor*   ptColor;

  if ( rktNAME == "" )
  {
    yyerror ("instanced object cannot be unnamed");
    exit (1);
  }
  
  if ( _tColorMap.find (rktNAME) == _tColorMap.end() )
  {
    yyerror ("pattern/color does not exist");
    exit (1);
  }
  
  ptColor = (TColor*) &(_tColorMap [rktNAME]);
  
  return ptColor;

}  /* InstanceColor() */


void DefineVector (const string& rktNAME)
{

  if ( rktNAME == "" )
  {
    yyerror ("cannot define unnamed vector");
    exit (1);
  }
  
  if ( _tVectorMap.find (rktNAME) != _tVectorMap.end() )
  {
    yyerror ("cannot redefine an existing vector");
    exit (1);
  }

  if ( _tTypeMap.find (rktNAME) != _tTypeMap.end() )
  {
    yyerror ("cannot redefine an existing object");
    exit (1);
  }
  
  _tVector = TVector (0, 0, 0);
  
  _ptParent = NULL;

}  /* DefineVector() */


TVector* InstanceVector (const string& rktNAME)
{

  TVector*   ptVector;

  if ( rktNAME == "" )
  {
    yyerror ("instanced object cannot be unnamed");
    exit (1);
  }
  
  if ( _tVectorMap.find (rktNAME) == _tVectorMap.end() )
  {
    yyerror ("vector does not exist");
    exit (1);
  }
  
  ptVector = (TVector*) &(_tVectorMap [rktNAME]);
  
  return ptVector;

}  /* InstanceVector() */


EAttribType MapClassToAttribute (const TBaseClass* pktClass)
{

  EClass   eIdentifierClass = pktClass->classType();

  switch (eIdentifierClass) 
  {
    case FX_PATTERN_CLASS:
      return FX_PATTERN;

    case FX_PERTURBATION_CLASS:
      return FX_PERTURBATION;

    default:
      return FX_NONE;
  }

}  /* MapClassToAttribute() */


void UpdateAttribute (const string& rktATTRIBUTE, const string& rktIDENT)
{

  EClass        eIdentifierClass = _tTypeMap [rktIDENT];
  EAttribType   eAttribute;
  void*         vpInstance;
  
  switch (eIdentifierClass) 
  {
    case FX_COLOR_CLASS:
      vpInstance = InstanceColor (rktIDENT);
      eAttribute = FX_COLOR;
      break;

    case FX_VECTOR_CLASS:
      vpInstance = InstanceVector (rktIDENT);
      eAttribute = FX_VECTOR;
      break;
      
    case FX_BSDF_CLASS:
      vpInstance = InstanceObject (rktIDENT);
      eAttribute = FX_BSDF;
      break;

    case FX_PATTERN_CLASS:
      vpInstance = InstanceObject (rktIDENT);
      eAttribute = FX_PATTERN;
      break;

    case FX_PERTURBATION_CLASS:
      vpInstance = InstanceObject (rktIDENT);
      eAttribute = FX_PERTURBATION;
      break;

    default:
      vpInstance = NULL;
      eAttribute = FX_NONE;

      cerr << "Warning: identifier class not recognized." << endl;
  }
  
  _nAttrib.pvValue = vpInstance;
  SetParameter (rktATTRIBUTE, eAttribute);
  
}  /* UpdateAttribute() */


void SetParameter (const string& rktATTRIB, EAttribType eTYPE)
{

  int   iResult;

  iResult = DATA->setAttribute (rktATTRIB, _nAttrib, eTYPE);

  if ( iResult == FX_ATTRIB_WRONG_PARAM )
  {
    yyerror ("object does not have such attribute");
    exit (1);
  }
  else if ( iResult == FX_ATTRIB_WRONG_TYPE )
  {
    yyerror ("incorrect type in attribute value");
    exit (1);
  }
  else if ( iResult == FX_ATTRIB_WRONG_VALUE )
  {
    yyerror ("value not accepted for this attribute");
    exit (1);
  }
  else if ( iResult == FX_ATTRIB_USER_ERROR )
  {
    yyerror (TProcedural::_tUserErrorMessage.c_str());
    exit (1);
  }

}  /* SetParameter() */


string EAttribType_to_str (EAttribType eTYPE)
{

  /* This function is pretty dumb, but I (KH) couldn't find another one
     anywhere else.  Added on 07Aug2000  */ 

  switch ( eTYPE )
  {
    case FX_NONE: 
      return "none";

    case FX_REAL: 
      return "real";

    case FX_BOOL: 
      return "bool";

    case FX_STRING: 
      return "string";

    case FX_COLOR: 
      return "color";

    case FX_VECTOR: 
      return "vector";

    case FX_VECTOR2: 
      return "2d_vector";

    case FX_IMAGE: 
      return "image";

    case FX_BSDF: 
      return "bsdf";

    case FX_CAMERA: 
      return "camera";

    case FX_LIGHT: 
      return "light";

    case FX_MATERIAL: 
      return "material";

    case FX_PATTERN: 
      return "pattern";

    case FX_PERTURBATION: 
      return "perturbation";

    case FX_RENDERER: 
      return "renderer";

    case FX_OBJECT: 
      return "object";

    case FX_OBJECT_FILTER: 
      return "object_filter";

    case FX_IMAGE_FILTER: 
      return "image_filter";

    default: 
      return "unknown";
  }

}  /* EAttribType_to_str() */
