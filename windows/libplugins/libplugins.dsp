# Microsoft Developer Studio Project File - Name="libplugins" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libplugins - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libplugins.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libplugins.mak" CFG="libplugins - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libplugins - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libplugins - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libplugins - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "../.." /I "../" /D "NDEBUG" /D YY_NEVER_INTERACTIVE=1 /D STATIC_LINK=1 /D YYTEXT_POINTER=1 /D STDC_HEADERS=1 /D BROKEN_FILENO_INCLUDE=1 /D BROKEN_RETURN_SUBTYPES_ON_VIRTUAL=1 /D "WIN32" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Lib\Release\libplugins.lib"

!ELSEIF  "$(CFG)" == "libplugins - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "../.." /I "../" /D "_DEBUG" /D YY_NEVER_INTERACTIVE=1 /D STATIC_LINK=1 /D YYTEXT_POINTER=1 /D STDC_HEADERS=1 /D BROKEN_FILENO_INCLUDE=1 /D BROKEN_RETURN_SUBTYPES_ON_VIRTUAL=1 /D "WIN32" /D "_MBCS" /D "_LIB" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\Debug\libplugins.lib"

!ENDIF 

# Begin Target

# Name "libplugins - Win32 Release"
# Name "libplugins - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\plugins\object\abvh\abvh.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\object\aggregate_uniform_grid\aggregate_uniform_grid.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\atm_object\atm_const\atm_const.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\object\bezier\bezier.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\object\bezier\beziersub.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\bsdf\cook_torrance\bsdf_cook_torrance.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\bsdf\lambertian\bsdf_lambertian.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\bsdf\phong\bsdf_phong.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\bsdf\schlick\bsdf_schlick.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\bsdf\schlick_double\bsdf_schlick_double.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\bsdf\ward\bsdf_ward.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\object\lwo\chunks.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\image_filter\lens_flare\flare.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\object\height_field\height_field.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\image_filter\cartoon\if_cartoon.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\image_filter\convert_to_grey\if_convert_to_grey.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\image_filter\fog\if_fog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\image_filter\lens_flare\if_lens_flare.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\object\lwo\lwo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\object_filter\cartoon\of_cartoon.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\object_filter\convert_to_grey\of_convert_to_grey.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\camera\parallel\parallel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\pattern\amplifier\pat_amplifier.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\pattern\brick\pat_brick.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\pattern\checker\pat_checker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\pattern\composite\pat_composite.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\pattern\crackle\pat_crackle.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\pattern\cylgrad\pat_cylgrad.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\pattern\leopard\pat_leopard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\pattern\marble\pat_marble.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\pattern\noise\pat_noise.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\pattern\parquet\pat_parquet.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\pattern\texture\pat_texture.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\pattern\wood\pat_wood.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\pattern\worley\pat_worley.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\perturbation\brick\per_brick.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\perturbation\bump\per_bump.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\perturbation\crackle\per_crackle.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\perturbation\leopard\per_leopard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\perturbation\marble\per_marble.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\perturbation\noise\per_noise.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\perturbation\wave\per_wave.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\perturbation\worley\per_worley.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\camera\pinhole\pinhole.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\light\point_light\point_light.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\object\polyhedron\polyhedron.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\light\projector\projector.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\renderer\raytracer\raytracer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\scene_io\rt\rt_io.cpp
# End Source File
# Begin Source File

SOURCE=.\rt_parser.cpp
# End Source File
# Begin Source File

SOURCE=.\rt_scanner.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\object\subdiv\subdiv.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\object\subdiv\subdivedge.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\object\subdiv\subdivface.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\object\subdiv\subdivvert.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\image_io\tga\tga_io.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\camera\thinlens\thinlens.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\object\aggregate_uniform_grid\uniform_grid.cpp
# End Source File
# Begin Source File

SOURCE=..\..\plugins\light\warn_light\warn_light.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\plugins\object\abvh\abvh.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\object\aggregate_uniform_grid\aggregate_uniform_grid.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\atm_object\atm_const\atm_const.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\object\bezier\bezier.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\bsdf\cook_torrance\bsdf_cook_torrance.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\bsdf\lambertian\bsdf_lambertian.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\bsdf\phong\bsdf_phong.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\bsdf\schlick\bsdf_schlick.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\bsdf\schlick_double\bsdf_schlick_double.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\bsdf\ward\bsdf_ward.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\object\height_field\height_field.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\image_filter\cartoon\if_cartoon.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\image_filter\convert_to_grey\if_convert_to_grey.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\image_filter\fog\if_fog.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\image_filter\lens_flare\if_lens_flare.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\object\lwo\lwo.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\object_filter\cartoon\of_cartoon.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\object_filter\convert_to_grey\of_convert_to_grey.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\camera\parallel\parallel.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\scene_io\rt\parser.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\scene_io\rt\parser_defs.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\pattern\amplifier\pat_amplifier.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\pattern\brick\pat_brick.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\pattern\checker\pat_checker.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\pattern\composite\pat_composite.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\pattern\crackle\pat_crackle.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\pattern\cylgrad\pat_cylgrad.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\pattern\leopard\pat_leopard.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\pattern\marble\pat_marble.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\pattern\noise\pat_noise.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\pattern\parquet\pat_parquet.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\pattern\texture\pat_texture.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\pattern\wood\pat_wood.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\pattern\worley\pat_worley.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\perturbation\brick\per_brick.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\perturbation\bump\per_bump.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\perturbation\crackle\per_crackle.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\perturbation\leopard\per_leopard.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\perturbation\marble\per_marble.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\perturbation\noise\per_noise.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\perturbation\wave\per_wave.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\perturbation\worley\per_worley.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\camera\pinhole\pinhole.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\light\point_light\point_light.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\object\polyhedron\polyhedron.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\light\projector\projector.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\renderer\raytracer\raytracer.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\scene_io\rt\rt_io.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\object\subdiv\subdiv.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\image_io\tga\tga_io.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\camera\thinlens\thinlens.h
# End Source File
# Begin Source File

SOURCE=..\..\plugins\light\warn_light\warn_light.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\plugins\scene_io\rt\parser.y
# End Source File
# Begin Source File

SOURCE=..\..\plugins\scene_io\rt\scanner.l
# End Source File
# Begin Source File

SOURCE=.\TODO.TXT
# End Source File
# End Target
# End Project
