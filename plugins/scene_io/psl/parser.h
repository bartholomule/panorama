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
#define	T_REAL	258
#define	T_BOOL	259
#define	T_COMPLEX_TYPE	260
#define	T_IDENTIFIER	261
#define	T_QUOTED_STRING	262
#define	T_DEFINE	263
#define	T_CLASS	264
#define	T_EXTENDS	265
#define	T_NEW	266
#define	T_BOX	267
#define	T_CIRCLE	268
#define	T_CONE	269
#define	T_CYLINDER	270
#define	T_DIFFERENCE	271
#define	T_FILTER	272
#define	T_INTERSECTION	273
#define	T_MESH	274
#define	T_PHONG_TRIANGLE	275
#define	T_PLANE	276
#define	T_RECTANGLE	277
#define	T_SPHERE	278
#define	T_TRIANGLE	279
#define	T_UNION	280
#define	T_TYPE_REAL	281
#define	T_TYPE_BOOL	282
#define	T_TYPE_STRING	283
#define	T_TYPE_COLOR	284
#define	T_TYPE_VECTOR	285
#define	T_TYPE_VECTOR2	286
#define	T_TYPE_IMAGE	287
#define	T_TYPE_SCENE	288
#define	T_TYPE_BSDF	289
#define	T_TYPE_CAMERA	290
#define	T_TYPE_LIGHT	291
#define	T_TYPE_MATERIAL	292
#define	T_TYPE_RENDERER	293
#define	T_TYPE_OBJECT	294
#define	T_TYPE_AGGREGATE	295
#define	T_TYPE_OBJECT_FILTER	296
#define	T_TYPE_IMAGE_FILTER	297
#define	UNARY_MINUS	298


extern YYSTYPE yylval;
