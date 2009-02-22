AC_DEFUN([PANORAMA_CHECK_COMPILER_FLAG],
[
AC_MSG_CHECKING(whether $CXX supports -$1)
panorama_cache=`echo $1 | sed 'y% .=/+-%____p_%'`
AC_CACHE_VAL(panorama_cv_prog_cxx_$panorama_cache,
[
  AC_LANG_SAVE
  AC_LANG_CPLUSPLUS
  save_CXXFLAGS="$CXXFLAGS"
  CXXFLAGS="$CXXFLAGS -$1"
  AC_TRY_LINK([],[ return 0; ], [eval "panorama_cv_prog_cxx_$panorama_cache=yes"], [])
  CXXFLAGS="$save_CXXFLAGS"
  AC_LANG_RESTORE
])
if eval "test \"`echo '$panorama_cv_prog_cxx_'$panorama_cache`\" = yes"; then
 AC_MSG_RESULT(yes)
 :
 $2
else
 AC_MSG_RESULT(no)
 :
 $3
fi
])