dnl Process this file with autoconf to produce a configure script.

dnl AC_INIT(llapi/base_class.h)
AC_INIT(panorama, 0.18.01, bug-panorama@gnu.org)

AC_PREFIX_DEFAULT(/opt/panorama)

dnl Gets the host type
AC_CANONICAL_HOST

dnl Checks for programs.
AC_LIBTOOL_DLOPEN
AC_PROG_LIBTOOL
AC_SUBST(LIBTOOL_DEPS)

dnl FIXME!  I need to determine the suffix to use for a library (also for plugins).
PLUGIN_EXTENSION=.so
AC_SUBST(PLUGIN_EXTENSION)

AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LEX
AC_PROG_YACC
AC_PROG_MAKE_SET

dnl Checks for libraries.
AC_CHECK_LIB(dl, dlopen)
AC_CHECK_LIB(c,  dlopen)

dnl Checks for header files.
AC_HEADER_STDC

dnl Check for special libraries

echo -e "checking for GTK--... \c"
dnl AC_CHECK_PROG(gtkmm_val,"gtkmm-config --cflags","yes","no")
if [ `gtkmm-config --cflags >/dev/null 2>/dev/null` ]
then
  GUI_PROGRAM="gui"
  echo "yes"
else
  GUI_PROGRAM=""
  echo "no"
  AC_MSG_WARN(GTK-- not available so gui (panorama) not compiled)
fi
AC_SUBST(GUI_PROGRAM)


text_val=no
echo -e "checking for modern freetype... \c"
if [ `freetype-config --cflags >/dev/null 2>/dev/null` ]
then
  TEXT_FILTER="text"
  PLUGIN_TEXT="if_text$PLUGIN_EXTENSION"
  echo "yes"
else
  echo "no"

  dnl This is the original test, which I am leaving in here for backwards 
  dnl compatibility (if it still works).

  AC_CHECK_HEADER([freetype/ft2build.h freetype/freetype.h], [AC_CHECK_LIB(ttf,main,text_val=yes)])
  if test $text_val = "yes"
  then
    TEXT_FILTER="text"
    PLUGIN_TEXT="if_text$PLUGIN_EXTENSION"
  else
    TEXT_FILTER=""
    PLUGIN_TEXT=""
    AC_MSG_WARN(Freetype library not available so text filter not compiled)
  fi
fi
AC_SUBST(TEXT_FILTER)
AC_SUBST(PLUGIN_TEXT)

jpeg_val=no
AC_CHECK_HEADER(jpeglib.h, [AC_CHECK_LIB(jpeg,main,jpeg_val=yes)])
if test $jpeg_val = "yes"; then
	JPEG_FILTER="jpeg"
	PLUGIN_JPEG="jpeg_io$PLUGIN_EXTENSION"
else
	JPEG_FILTER=""
	PLUGIN_JPEG=""
	AC_MSG_WARN(JPEG library not available so jpeg filter not compiled)
fi
AC_SUBST(JPEG_FILTER)
AC_SUBST(PLUGIN_JPEG)

png_val=no
AC_CHECK_HEADER(png.h, [AC_CHECK_LIB(png,main,dnl
AC_CHECK_LIB(z,main,png_val=yes))])
if test $png_val = "yes"; then
	PNG_FILTER="png"
	PLUGIN_PNG="png_io$PLUGIN_EXTENSION"
else
	PNG_FILTER=""
	PLUGIN_PNG=""
	AC_MSG_WARN(Either png or zlib library not available so png filter not compiled)
fi
AC_SUBST(PNG_FILTER)
AC_SUBST(PLUGIN_PNG)

gif_val=no
AC_CHECK_HEADER(gif_lib.h, [AC_CHECK_LIB(ungif,main,gif_val=yes)])
if test $gif_val = "yes"; then
	GIF_FILTER="gif"
	PLUGIN_GIF="gif_io$PLUGIN_EXTENSION"
else
	GIF_FILTER=""
	PLUGIN_GIF=""
	AC_MSG_WARN(UNGIF library not available so gif filter not compiled)
fi
AC_SUBST(GIF_FILTER)
AC_SUBST(PLUGIN_GIF)

tiff_val=no
AC_CHECK_HEADER(tiffio.h, [AC_CHECK_LIB(tiff,TIFFGetVersion,tiff_val=yes)])
if test $tiff_val = "yes"; then
	TIFF_FILTER="tiff"
	PLUGIN_TIFF="tiff_io$PLUGIN_EXTENSION"
else
	TIFF_FILTER=""
	PLUGIN_TIFF=""
	AC_MSG_WARN(LIBTIFF library not available so tiff filter not compiled)
fi
AC_SUBST(TIFF_FILTER)
AC_SUBST(PLUGIN_TIFF)

dnl Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_BIGENDIAN
AC_TYPE_SIZE_T
dnl 
dnl Under Irix 6.5, g++ does not define fileno when stdio.h is included 
dnl by a lex generated file.
dnl
AC_CACHE_CHECK([for fileno being properly defined with C++],
  ac_cv_fileno_ok, 
[AC_TRY_COMPILE([#include <stdio.h>
], [int s = fileno(STDOUT)], ac_cv_fileno_ok=yes, ac_cv_fileno_ok=no)])
if test $ac_cv_fileno_ok = no; then
  AC_DEFINE(BROKEN_FILENO_INCLUDE)
fi


dnl Checks for static-link option.
AC_MSG_CHECKING(whether to link statically or not)
AC_ARG_ENABLE(static-link,
[  --enable-static-link    Link everything statically],
STATIC_VAL=$enableval, STATIC_VAL="no")
if test $STATIC_VAL = "yes"; then
  STATIC_LINK=1
else
  STATIC_VAL="no";
  STATIC_LINK=0
fi
AC_SUBST(STATIC_LINK)
AC_MSG_RESULT($STATIC_VAL)

dnl Checks for profile option.
AC_MSG_CHECKING(whether to add profiling information or not)
AC_ARG_ENABLE(profile,
[  --enable-profile        Add profiling information],
PROFILE_VAL=$enableval, PROFILE_VAL="no")
if test $PROFILE_VAL = "yes"; then
  PROFILE=1
else
  PROFILE_VAL="no";
  PROFILE=0
fi
AC_SUBST(PROFILE)
AC_MSG_RESULT($PROFILE_VAL)

dnl Checks for debug option.
AC_MSG_CHECKING(whether to enable debug info or not)
AC_ARG_ENABLE(debug,
[  --enable-debug          Generate debug information when compiling],
DEBUG_VAL=$enableval, DEBUG_VAL="no")
if test $DEBUG_VAL = "yes"; then
  DEBUG_INFO=1
else
  DEBUG_VAL="no";
  DEBUG_INFO=0
fi
AC_SUBST(DEBUG_INFO)
AC_MSG_RESULT($DEBUG_VAL)

dnl Checks for experimental code option.
AC_MSG_CHECKING(whether to enable experimental code or not)
AC_ARG_ENABLE(experimental,
[  --enable-experimental   Include experimental code in built],
EXPER_VAL=$enableval, EXPER_VAL="no")
if test $EXPER_VAL = "yes"; then
  EXPERIMENTAL=1
  AC_DEFINE(USE_EXPERIMENTAL)
else
  EXPER_VAL="no";
  EXPERIMENTAL=0
fi
AC_SUBST(EXPERIMENTAL)
AC_MSG_RESULT($EXPER_VAL)

dnl This is the machine specific logic which can set some features depending
dnl on the platform.
dnl XXX Check we are really gcc

dnl The following variables may be set
dnl ARCH_MAKE_SHARED_OPTS flags tacked onto the end of building a shared
dnl     library or plugin
dnl
dnl have_so_reg flags if so_locations is used by the machine.
dnl
dnl ARCH_PROG_SETLIBPATH flags to set the library path in executables
dnl      convenient so one does not need to set LD_LIBRARY_PATH
case $host in

alpha-dec-osf*)
	echo "Adding shared library rules for DEC Alpha system"
	ARCH_MAKE_SHARED_OPTS="-Wl,-expect_unresolved,\*"
	ARCH_PROG_SETLIBPATH="-Wl,-rpath,\${LIB_DIR}"
	have_so_reg=yes
	;;
mips-sgi-irix6*)
	echo "Adding shared library rules for IRIX 6.* system"
	#ARCH_MAKE_SHARED_OPTS="-Wl,-expect_unresolved,\*"
	ARCH_MAKE_SHARED_OPTS=""
	ARCH_PROG_SETLIBPATH="-Wl,-rpath,\${LIB_DIR}"
	have_so_reg=yes
	;;
*)
	ARCH_MAKE_SHARED_OPTS=""
	ARCH_PROG_SETLIBPATH=""
	have_so_reg=no
	;;
esac

if test $have_so_reg = "yes"; then
  ARCH_MAKE_SHARED_OPTS="$ARCH_MAKE_SHARED_OPTS -Wl,-update_registry,\${BUILD_TOP}/so_locations"
fi

AC_SUBST(ARCH_MAKE_SHARED_OPTS)
AC_SUBST(ARCH_PROG_SETLIBPATH)
  
AC_OUTPUT(\
	Makefile \
	Makefile.vars \
	Makefile.targets \
        version \
        data/Makefile \
        data/gradient/Makefile \
        data/include/Makefile \
        data/texture/Makefile \
        doc/Makefile \
        doc/developers/Makefile \
        doc/users/Makefile \
        doc/api/Makefile \
        doc/api/Doxyfile \
        llapi/Makefile \
        hlapi/Makefile \
        plugins/Makefile \
        plugins/atm_object/Makefile \
        plugins/atm_object/atm_const/Makefile:Makefile.plugin.in \
        plugins/bsdf/Makefile \
        plugins/bsdf/cook_torrance/Makefile:Makefile.plugin.in \
        plugins/bsdf/lambertian/Makefile:Makefile.plugin.in \
        plugins/bsdf/phong/Makefile:Makefile.plugin.in \
        plugins/bsdf/schlick/Makefile:Makefile.plugin.in \
        plugins/bsdf/schlick_double/Makefile:Makefile.plugin.in \
        plugins/bsdf/ward/Makefile:Makefile.plugin.in \
        plugins/camera/Makefile \
        plugins/camera/parallel/Makefile:Makefile.plugin.in \
        plugins/camera/pinhole/Makefile:Makefile.plugin.in \
        plugins/camera/thinlens/Makefile:Makefile.plugin.in \
        plugins/image_filter/Makefile \
        plugins/image_filter/cartoon/Makefile:Makefile.plugin.in \
        plugins/image_filter/convert_to_grey/Makefile:Makefile.plugin.in \
        plugins/image_filter/fog/Makefile:Makefile.plugin.in \
        plugins/image_filter/lens_flare/Makefile:Makefile.plugin.in \
        plugins/image_filter/text/Makefile:Makefile.plugin.in \
        plugins/image_io/Makefile \
        plugins/image_io/gif/Makefile:Makefile.plugin.in \
        plugins/image_io/jpeg/Makefile:Makefile.plugin.in \
        plugins/image_io/png/Makefile:Makefile.plugin.in \
        plugins/image_io/tga/Makefile:Makefile.plugin.in \
        plugins/image_io/tiff/Makefile:Makefile.plugin.in \
        plugins/light/Makefile \
        plugins/light/point_light/Makefile:Makefile.plugin.in \
        plugins/light/projector/Makefile:Makefile.plugin.in \
        plugins/light/warn_light/Makefile:Makefile.plugin.in \
        plugins/pattern/Makefile \
        plugins/pattern/amplifier/Makefile:Makefile.plugin.in \
        plugins/pattern/brick/Makefile:Makefile.plugin.in \
        plugins/pattern/checker/Makefile:Makefile.plugin.in \
        plugins/pattern/composite/Makefile:Makefile.plugin.in \
        plugins/pattern/crackle/Makefile:Makefile.plugin.in \
        plugins/pattern/cylgrad/Makefile:Makefile.plugin.in \
        plugins/pattern/leopard/Makefile:Makefile.plugin.in \
        plugins/pattern/marble/Makefile:Makefile.plugin.in \
        plugins/pattern/noise/Makefile:Makefile.plugin.in \
        plugins/pattern/parquet/Makefile:Makefile.plugin.in \
        plugins/pattern/texture/Makefile:Makefile.plugin.in \
        plugins/pattern/wood/Makefile:Makefile.plugin.in \
        plugins/pattern/worley/Makefile:Makefile.plugin.in \
        plugins/perturbation/Makefile \
        plugins/perturbation/brick/Makefile:Makefile.plugin.in \
        plugins/perturbation/bump/Makefile:Makefile.plugin.in \
        plugins/perturbation/crackle/Makefile:Makefile.plugin.in \
        plugins/perturbation/leopard/Makefile:Makefile.plugin.in \
        plugins/perturbation/marble/Makefile:Makefile.plugin.in \
        plugins/perturbation/noise/Makefile:Makefile.plugin.in \
        plugins/perturbation/wave/Makefile:Makefile.plugin.in \
        plugins/perturbation/worley/Makefile:Makefile.plugin.in \
        plugins/object/Makefile \
        plugins/object/abvh/Makefile:Makefile.plugin.in \
        plugins/object/aggregate_uniform_grid/Makefile:Makefile.plugin.in \
        plugins/object/bezier/Makefile:Makefile.plugin.in \
        plugins/object/subdiv/Makefile:Makefile.plugin.in \
        plugins/object/height_field/Makefile:Makefile.plugin.in \
        plugins/object/lwo/Makefile:Makefile.plugin.in \
        plugins/object/polyhedron/Makefile:Makefile.plugin.in \
        plugins/object_filter/Makefile \
        plugins/object_filter/cartoon/Makefile:Makefile.plugin.in \
        plugins/object_filter/convert_to_grey/Makefile:Makefile.plugin.in \
        plugins/renderer/Makefile \
        plugins/renderer/raytracer/Makefile:Makefile.plugin.in \
        plugins/renderer/zbuffer/Makefile:Makefile.plugin.in \
        plugins/scene_io/Makefile \
        plugins/scene_io/rt/Makefile:Makefile.plugin.in \
        plugins/scene_io/psl/Makefile:Makefile.plugin.in \
        programs/Makefile \
        programs/render/Makefile \
        programs/gui/Makefile \
        scenes/Makefile \
        scenes/atmospheric/Makefile \
        scenes/lights/Makefile \
        scenes/materials/Makefile \
        scenes/misc/Makefile \
        scenes/objects/Makefile
)

dnl AC_CONFIG_LINKS(Makefile.deps:Makefile.deps)
ln -s $ac_aux_dir/Makefile.deps . 2>/dev/null
ln -s $ac_aux_dir/install-sh . 2>/dev/null
exit 0
