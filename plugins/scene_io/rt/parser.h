typedef union {
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
       } YYSTYPE;
#define	T_BOOL	257
#define	T_REAL	258
#define	T_INTEGER	259
#define	T_IDENTIFIER	260
#define	T_QUOTED_STRING	261
#define	T_AGGREGATE	262
#define	T_ATM_OBJECT	263
#define	T_BLUE	264
#define	T_BOX	265
#define	T_BSDF	266
#define	T_CAMERA	267
#define	T_CIRCLE	268
#define	T_CLASS	269
#define	T_COLOR	270
#define	T_CONE	271
#define	T_CYLINDER	272
#define	T_DEFINE	273
#define	T_DIFFERENCE	274
#define	T_EXTENDS	275
#define	T_FILTER	276
#define	T_GREEN	277
#define	T_IMAGE_FILTER	278
#define	T_INTERSECTION	279
#define	T_LIGHT	280
#define	T_MATERIAL	281
#define	T_MESH	282
#define	T_OBJECT	283
#define	T_OBJECT_FILTER	284
#define	T_OUTPUT	285
#define	T_PATTERN	286
#define	T_PERTURBATION	287
#define	T_PHONG_TRIANGLE	288
#define	T_PLANE	289
#define	T_RECTANGLE	290
#define	T_RED	291
#define	T_RENDERER	292
#define	T_ROTATE	293
#define	T_SCALE	294
#define	T_SCENE	295
#define	T_SPHERE	296
#define	T_TORUS	297
#define	T_TRANSLATE	298
#define	T_TRIANGLE	299
#define	T_TYPE	300
#define	T_UNION	301
#define	T_VECTOR	302
#define	T_VERTEX	303
#define	T_X	304
#define	T_Y	305
#define	T_Z	306
#define	T_ATTR_LIST	307
#define	T_ATTR_TYPE	308
#define	UNARY_MINUS	309


extern YYSTYPE rt_lval;
