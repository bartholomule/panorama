/*
*  Copyright (C) 1998, 1999 Angel Jimenez Jimenez and Carlos Jimenez Moreno
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

%{
#include <string>
using std::string;
//#define YYSTYPE string;
 
#define YYDEBUG 1
#define YYERROR_VERBOSE 

static const string newline = "\n";

 unsigned line_number;
 string file_name;
 
 static string x;
 static string y;
 static string z;
 static string image_output_type;

 static string extract_class(const string& cls, const string& def);

#include "parser_defs.h"

 
%}

%token T_BOOL
%token T_REAL
%token T_IDENTIFIER
%token T_QUOTED_STRING

/* "Reserved word" tokens.
   Modified to all act the same as identifiers (KH--07Aug2000)  */
%token  T_VERBATIM
%token  T_AGGREGATE
%token  T_ATM_OBJECT
%token  T_BLUE
%token  T_BOX
%token  T_BSDF
%token  T_CAMERA
%token  T_CIRCLE
%token  T_CLASS
%token  T_COLOR
%token  T_CONE
%token  T_CYLINDER
%token  T_DEFINE
%token  T_DIFFERENCE
%token  T_EXTENDS
%token  T_FILTER
%token  T_GREEN
%token  T_IMAGE_FILTER
%token  T_INTERSECTION
%token  T_LIGHT
%token  T_MATERIAL
%token  T_MESH
%token  T_OBJECT
%token  T_OBJECT_FILTER
%token  T_OUTPUT
%token  T_PATTERN
%token  T_PERTURBATION
%token  T_PHONG_TRIANGLE
%token  T_PLANE
%token  T_RECTANGLE
%token  T_RED
%token  T_RENDERER
%token  T_ROTATE
%token  T_SCALE
%token  T_SCENE
%token  T_SPHERE
%token  T_TORUS
%token  T_TRANSLATE
%token  T_TRIANGLE
%token  T_TYPE
%token  T_UNION
%token  T_VECTOR
%token  T_VERTEX
%token  T_X
%token  T_Y
%token  T_Z

%left '+' '-'
%left '*' '/'
%right UNARY_MINUS

%start scene_file

%%

scene_file : everything
{
  cout << "// This is a converted RT scene file.  Check for correctness." << endl;
  cout << "#include \"shapes.inc\"" << endl;
  cout << $1 << endl;
}

optional_comments:
/* empty */
{
  $$ = "";
  cout << "parser:optional_comments (empty)" << endl;
}
| T_VERBATIM
{
  cout << "parser:optional_comments (verbatim)" << endl;
  $$ = $1;
}
;

everything:
/* Nothing */
{
  $$ = "";
}
| everything optional_comments
{
  $$ = $1 + $2;
}
| everything instance optional_comments
{
  $$ = $1 + $2 + $3;
}
| everything definition optional_comments
{
  $$ = $1 + $2 + $3;
}
;

instance:
T_SCENE scene_instance
{
  $$ = string("scene") + newline + $2 + newline;
}
| T_ATM_OBJECT type_instance
{
  $$ = $1 + newline + $2 + newline;
}
| object
{
  $$ = $1;  
}
;
                        
definition		:
T_DEFINE T_COLOR color_def
{
  $$ = $3 + newline;
}
| T_DEFINE T_VECTOR vector_def
{
  $$ = $3 + newline;
}
| T_DEFINE T_OBJECT object_def
{
  $$ = $3 + newline;
}
| T_DEFINE T_SCENE scene_def
{
  $$ = $3 + newline;
}
| type_def
{
  $$ = $1;
}
;

type_def:
reserved_types name class '{' object_params '}'
{
  $$ = string("define ") + $2 + " " + extract_class($3,$1) + " { " + newline + $4 + newline + " };";  
}
;

type_instance:
class '{' any_params '}'
{
  $$ = string("define ") + $2 + " " + extract_class($1,"/* unknown instance */") + " { " + newline + $3 + newline + " }";  
}
;


object:
object_instance
{
  $$ = $1;
}
;

real_expr		:
T_REAL
{
  $$ = $1;
}
| T_IDENTIFIER '(' ')'
{
  $$ = $1 + "()";
}
| real_expr '+' real_expr
{
  $$ = $1 + "+" + $3;
}
| real_expr '-' real_expr
{
  $$ = $1 + "-" + $3;
}
| real_expr '*' real_expr
{
  $$ = $1 + "*" + $3;
}
| real_expr '/' real_expr
{
  $$ = $1 + "/" + $3;
}
| '-' real_expr %prec UNARY_MINUS
{
  $$ = "-" + $2;
}
| '(' real_expr ')'
{
  $$ = string("(") + $2 + ")";
}
;
color:
'{' T_RED real_expr T_GREEN real_expr T_BLUE real_expr '}'
{
  $$ = string("{ red ") + $3 + " green " + $5 + " blue " + $7 + " }";
}
;

vector3:
'<' real_expr ',' real_expr ',' real_expr '>'
{
  $$ = string("< ") + $2 + ", " + $4 + ", " + $6 + " >";   
}
;
vector2:
'<' real_expr ',' real_expr '>'
{
  $$ = string("< ") + $2 + ", " + $4 + " >";   
}
;

name			: /* Nothing */
{
  $$ = "";
}
| T_IDENTIFIER
{
  $$ = $1;
}
;

class:
/* Nothing */
{
  $$ = "";
}
| ':' T_EXTENDS T_IDENTIFIER
{
  $$ = $3;
}
| ':' T_CLASS T_IDENTIFIER
{
  $$ = "class " + $3;
}
;


any_params:
/* EMPTY */
{
  $$ = "";
}
| any_params any_param
{
  $$ = $1 + $2 + newline;
}
;

any_param:
object_param { $$ = $1; }
| scene_param { $$ = $1; }
| image_io_param { $$ = $1; }
| aggregate_param { $$ = $1; }
| param { $$ = $1; }
;


params:
/* Nothing */
{
  $$ = "";
}
| params param
{
  $$ = $1 + $2 + ";" + newline;
}
;

param:
T_IDENTIFIER potential_string
{
  $$ = $1 + " = " + $2;
}
| T_IDENTIFIER vector3
{
  $$ = $1 + " = " + $2;
}
| T_IDENTIFIER vector2
{
  $$ = $1 + " = " + $2;			    
}
| T_IDENTIFIER real_expr
{
  $$ = $1 + " = " + $2;			    
}
| T_IDENTIFIER T_BOOL
{
  $$ = $1 + " = " + $2;			    
}
| T_IDENTIFIER T_QUOTED_STRING
{
  $$ = $1 + " = " + $2;			    
}
| T_IDENTIFIER color
{
  $$ = $1 + " = " + $2;			    
}
| T_IDENTIFIER name
{
  $$ = $1 + " = " + $2;			    
}
| T_COLOR name
{
  $$ = "color = " + $2;			    
}
| T_COLOR real_expr
{
  $$ = "color = " + $2;			    
}
| T_COLOR color
{
  $$ = "color = " + $2;			    
}
| T_COLOR type_instance
{
  $$ = "color = " + $2;			    
}
| T_VECTOR vector_instance
{
  $$ = "vector = " + $2;			    
}
| T_CAMERA type_instance
{
  $$ = "camera = " + $2;			    
}
| T_RENDERER type_instance
{
  $$ = "renderer = " + $2;			    
}
| T_BSDF type_instance
{
  $$ = "bsdf = " + $2;			    
}
| reserved_fields type_instance { $$ = $1 + " = " + $2 }
;

object_params:
/* Nothing */
{
  $$ = "";
}
| object_params object_param
{
  $$ = $1 + $2 + newline;
}
;

scene_params:
/* Nothing */
{
  $$ = "";
}
| scene_params scene_param
{
  $$ = $1 + $2 + newline;
}
;

entity_param:
T_TRANSLATE vector3
{
  $$ = "translate( " + $2 + ");";
}
| T_ROTATE vector3
{
  $$ = "rotate( " + $2 + ");";
}
| T_ROTATE real_expr ',' vector3
{
  $$ = "quaternion_rotate(" + $2 + "," + $4 + ");";
}
| T_TRANSLATE vector_instance
{
  $$ = "translate( " + $2 + ");";
}
| T_ROTATE vector_instance
{
  $$ = "rotate( " + $2 + ");";
}
| T_ROTATE real_expr ',' vector_instance
{
  $$ = "quaternion_rotate(" + $2 + "," + $4 + ");";
}
| param
{
  $$ = $1;
}
;

volume_param:
T_SCALE vector3
{
  $$ = "scale( " + $2 + ");";
}
| entity_param
{
  $$ = $1;
}
;

object_param:
T_MATERIAL type_instance
{
  $$ = $2;
}
| T_FILTER type_instance
{
  $$ = $2;
}
| volume_param
{
  $$ = $1;
}
;


scene_param:
T_LIGHT type_instance
{
  $$ = "light = " + $2 + ";";
}
| T_FILTER type_instance
{
  $$ = "filter = " + $2 + ";";
}
| T_OUTPUT image_io_instance
{
  $$ = "output = " + $2 + ";";
}
| param
{
  $$ = $1;
}
;

image_io_param:
T_TYPE T_QUOTED_STRING
{
  image_output_type = $2.substr(1,$2.length() - 2);
  $$ = "";
}
| param
{
  $$ = $1;
}
;


image_io_instance:
'{' image_io_params '}'
{
  $$ = "class " + image_output_type + newline + "{ " + newline + $2 + newline + "}";
}
;

image_io_params:
/* Nothing */
{
  image_output_type = "tga";
}
| image_io_params image_io_param
{
  $$ = $1 + $2 + newline;
}
;

scene_def:
name class '{' scene_params '}'
{
  $$ = string("define ") + $1 + " " + extract_class($2, "class Scene") + " { " + newline + $4 + newline + " };";
}
;

scene_instance:
name
{
  $$ = $1;
}
| class '{' scene_params '}'
{
  $$ = extract_class($1, "class Scene") + " { " + newline + $3 + newline + " }";
}
;

object_def:
name class '{' object_params '}'
{
  $$ = string("define ") + $1 + " " + extract_class($2, "/* unknown class */") + " { " + newline + $4 + newline + " };";  
}
;

object_instance:
name
{
  $$ = $1;
}
| class '{' object_params '}'
{
  $$ = extract_class($1, "/* unknown class */") + " { " + newline + $3 + newline + " }";  
}
;

aggregate_param:
object
{
  $$ = $1;
}
| object_param
{
  $$ = $1;
}
;

color_def:
name class '{' color_params '}'
{
  $$ = string("define ") + $1 + "{ " + $4 + " };";
}
;

color_params:
color_param
{
  $$ = $1;
}
| color_params color_param
{
  $$ = $1 + $2 + " ";
}
;

color_param:
T_RED real_expr
{
  $$ = "red " + $2;
}
| T_GREEN real_expr
{
  $$ = "green " + $2;
}
| T_BLUE real_expr
{
  $$ = "blue " + $2;
}
;

vector_def:
name class '{' vector_params '}'
{
  $$ = string("define ") + $1 + "{ " + $4 + " };";
}
;

vector_instance:
name
{
  $$ = $1;
}
| class '{' vector_params '}'
{
  $$ = "< " + x + ", " + y + ", " + z + " >";
  x = "";
  y = "";
  z = "";
}
;

vector_params:
vector_param
{
  $$ = "vector_param (not to be used)";
}
| vector_params vector_param
{
  $$ = "vector_param (not to be used)";
}
;

vector_param:
T_X real_expr
{
  x = $2;
  $$ = "";
}
| T_Y real_expr
{
  y = $2;
  $$ = "";
}
| T_Z real_expr
{
  z = $2;
  $$ = "";
}
;

potential_string        : T_IDENTIFIER
			| reserved_words
			;


reserved_types:
T_AGGREGATE       { $$ = "class Aggregate"; }
| T_ATM_OBJECT    { $$ = "class AtmConst"; }
| T_BOX           { $$ = "class Box"; }
| T_CAMERA        { $$ = "class PinholeCamera"; }
| T_CIRCLE        { $$ = "class Circle"; }
| T_CONE          { $$ = "class Cone"; }
| T_CYLINDER      { $$ = "class Cylinder"; }
| T_DIFFERENCE    { $$ = "/* [FIXME!]  difference  */ class Csg"; }
| T_UNION         { $$ = "/* [FIXME!]    union     */ class Csg"; }
| T_INTERSECTION  { $$ = "/* [FIXME!] intersection */ class Csg"; }
| T_IMAGE_FILTER  { $$ = "/* unknown image filter */"; }
| T_OBJECT_FILTER { $$ = "/* unknown object filter */"; }
| T_LIGHT         { $$ = "class PointLight"; }
| T_MESH          { $$ = "class Mesh"; }
| T_OBJECT        { $$ = "/* uknown object class */"; }
| T_BSDF          { $$ = "class Bsdf"; }
| T_MATERIAL      { $$ = "class Material"; }
| T_PATTERN       { $$ = "class Pattern"; }
| T_PERTURBATION  { $$ = "class Perturbation"; }
| T_PHONG_TRIANGLE{ $$ = "class PhongTriangle"; }
| T_PLANE         { $$ = "class Plane"; }
| T_RECTANGLE     { $$ = "class Rectangle"; }
| T_RENDERER      { $$ = "class Raytracer"; }
| T_SCENE         { $$ = "class Scene"; }
| T_SPHERE        { $$ = "class Sphere"; }
| T_TORUS         { $$ = "class Torus"; }
| T_TRIANGLE      { $$ = "class Triangle"; }
;

reserved_fields:
T_OUTPUT   { $$ = "output"; }
| T_COLOR  { $$ = "color"; }
| T_SCALE  { $$ = "scale"; }
| T_VERTEX { $$ = "vertex"; }
| T_FILTER { $$ = "filter"; }
| T_TYPE   { $$ = "type"; }
;

reserved_words:
reserved_types { $$ = $1; }
| reserved_fields { $$ = $1; }
| T_CLASS     { $$ = "class"; }
| T_DEFINE    { $$ = "define"; }
| T_EXTENDS   { $$ = "extends"; }
| T_GREEN     { $$ = "green"; }
| T_RED       { $$ = "red"; }
| T_BLUE      { $$ = "blue"; }
| T_ROTATE    { $$ = "rotate"; }
| T_TRANSLATE { $$ = "translate"; }
| T_VECTOR    { $$ = "vector"; }
| T_X         { $$ = "x"; }
| T_Y         { $$ = "y"; }
| T_Z         { $$ = "z"; }
;

%%

void rt_conv_error (const char* pkcTEXT)
{

  cerr << endl << file_name << "(" << line_number << ") Error: " << pkcTEXT << endl;

}  /* rt_conv_error() */

void rt_conv_error (const string& rksTEXT)
{

  cerr << endl << file_name << "(" << line_number << ") Error: " << rksTEXT << endl;

}  /* rt_conv_error() */


void RT_CONV_InitParser (void)
{
  
}  /* RT_CONV_InitParser() */


void RT_CONV_CloseParser (void)
{

}  /* RT_CONV_CloseParser() */


string extract_class(const string& cls, const string& def)
{
  if( cls.length() >= 1 )
  {
    return cls;
  }
  return def;
}
