typedef union {
         char          acString [200];
         double        dValue;
         bool          gValue;
         TScene*       ptScene;
         TObject*      ptObject;
         EAttribType   eType;
         struct
         {
           EAttribType   eType;
           NAttribute    nValue;
         } tExpressionData;
       } YYSTYPE;
#define	T_REAL	257
#define	T_BOOL	258
#define	T_COMPLEX_TYPE	259
#define	T_IDENTIFIER	260
#define	T_QUOTED_STRING	261
#define	T_DEFINE	262
#define	T_CLASS	263
#define	T_EXTENDS	264
#define	T_NEW	265
#define	T_BOX	266
#define	T_CIRCLE	267
#define	T_CONE	268
#define	T_CYLINDER	269
#define	T_DIFFERENCE	270
#define	T_FILTER	271
#define	T_INTERSECTION	272
#define	T_MESH	273
#define	T_PHONG_TRIANGLE	274
#define	T_PLANE	275
#define	T_RECTANGLE	276
#define	T_SPHERE	277
#define	T_TRIANGLE	278
#define	T_UNION	279
#define	T_TYPE_REAL	280
#define	T_TYPE_BOOL	281
#define	T_TYPE_STRING	282
#define	T_TYPE_COLOR	283
#define	T_TYPE_VECTOR	284
#define	T_TYPE_VECTOR2	285
#define	T_TYPE_IMAGE	286
#define	T_TYPE_SCENE	287
#define	T_TYPE_BSDF	288
#define	T_TYPE_CAMERA	289
#define	T_TYPE_LIGHT	290
#define	T_TYPE_MATERIAL	291
#define	T_TYPE_RENDERER	292
#define	T_TYPE_OBJECT	293
#define	T_TYPE_AGGREGATE	294
#define	T_TYPE_OBJECT_FILTER	295
#define	T_TYPE_IMAGE_FILTER	296
#define	UNARY_MINUS	297


extern YYSTYPE psl_lval;
