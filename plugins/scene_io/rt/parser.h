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
#define	T_IDENTIFIER	259
#define	T_QUOTED_STRING	260
#define	T_AGGREGATE	261
#define	T_ATM_OBJECT	262
#define	T_BLUE	263
#define	T_BOX	264
#define	T_BSDF	265
#define	T_CAMERA	266
#define	T_CIRCLE	267
#define	T_CLASS	268
#define	T_COLOR	269
#define	T_CONE	270
#define	T_CYLINDER	271
#define	T_DEFINE	272
#define	T_DIFFERENCE	273
#define	T_EXTENDS	274
#define	T_FILTER	275
#define	T_GREEN	276
#define	T_IMAGE_FILTER	277
#define	T_INTERSECTION	278
#define	T_LIGHT	279
#define	T_MATERIAL	280
#define	T_MESH	281
#define	T_OBJECT	282
#define	T_OBJECT_FILTER	283
#define	T_OUTPUT	284
#define	T_PATTERN	285
#define	T_PERTURBATION	286
#define	T_PHONG_TRIANGLE	287
#define	T_PLANE	288
#define	T_RECTANGLE	289
#define	T_RED	290
#define	T_RENDERER	291
#define	T_ROTATE	292
#define	T_SCALE	293
#define	T_SCENE	294
#define	T_SPHERE	295
#define	T_TORUS	296
#define	T_TRANSLATE	297
#define	T_TRIANGLE	298
#define	T_TYPE	299
#define	T_UNION	300
#define	T_VECTOR	301
#define	T_VERTEX	302
#define	T_X	303
#define	T_Y	304
#define	T_Z	305
#define	T_ATTR_LIST	306
#define	T_ATTR_TYPE	307
#define	UNARY_MINUS	308


extern YYSTYPE rt_lval;
