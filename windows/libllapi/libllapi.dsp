# Microsoft Developer Studio Project File - Name="libllapi" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libllapi - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libllapi.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libllapi.mak" CFG="libllapi - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libllapi - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libllapi - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libllapi - Win32 Release"

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
# ADD CPP /nologo /W3 /GX /O2 /I "../.." /I "../" /D "NDEBUG" /D STATIC_LINK=1 /D YYTEXT_POINTER=1 /D STDC_HEADERS=1 /D BROKEN_FILENO_INCLUDE=1 /D BROKEN_RETURN_SUBTYPES_ON_VIRTUAL=1 /D "WIN32" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Lib\Release\libllapi.lib"

!ELSEIF  "$(CFG)" == "libllapi - Win32 Debug"

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
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "../.." /I "../" /D _DEBUG=1 /D STATIC_LINK=1 /D YYTEXT_POINTER=1 /D STDC_HEADERS=1 /D BROKEN_FILENO_INCLUDE=1 /D BROKEN_RETURN_SUBTYPES_ON_VIRTUAL=1 /D "WIN32" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Lib\Debug\libllapi.lib"

!ENDIF 

# Begin Target

# Name "libllapi - Win32 Release"
# Name "libllapi - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\llapi\atmosphere.cpp
# End Source File
# Begin Source File

SOURCE=..\..\llapi\atmospheric_object.cpp
# End Source File
# Begin Source File

SOURCE=..\..\llapi\base_class.cpp
# End Source File
# Begin Source File

SOURCE=..\..\llapi\bounding_box.cpp
# End Source File
# Begin Source File

SOURCE=..\..\llapi\bsdf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\llapi\camera.cpp
# End Source File
# Begin Source File

SOURCE=..\..\llapi\catrom2.cpp
# End Source File
# Begin Source File

SOURCE=..\..\llapi\debug.cpp
# End Source File
# Begin Source File

SOURCE=..\..\llapi\file.cpp
# End Source File
# Begin Source File

SOURCE=..\..\llapi\gradient.cpp
# End Source File
# Begin Source File

SOURCE=..\..\llapi\heap_manager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\llapi\image.cpp
# End Source File
# Begin Source File

SOURCE=..\..\llapi\image_io.cpp
# End Source File
# Begin Source File

SOURCE=..\..\llapi\light.cpp
# End Source File
# Begin Source File

SOURCE=..\..\llapi\material.cpp
# End Source File
# Begin Source File

SOURCE=..\..\llapi\mesh.cpp
# End Source File
# Begin Source File

SOURCE=..\..\llapi\object.cpp
# End Source File
# Begin Source File

SOURCE=..\..\llapi\pattern.cpp
# End Source File
# Begin Source File

SOURCE=..\..\llapi\perlin_noise.cpp
# End Source File
# Begin Source File

SOURCE=..\..\llapi\procedural.cpp
# End Source File
# Begin Source File

SOURCE=..\..\llapi\program.cpp
# End Source File
# Begin Source File

SOURCE=..\..\llapi\ray.cpp
# End Source File
# Begin Source File

SOURCE=..\..\llapi\root_solver.cpp
# End Source File
# Begin Source File

SOURCE=..\..\llapi\sc_noise.cpp
# End Source File
# Begin Source File

SOURCE=..\..\llapi\scene.cpp
# End Source File
# Begin Source File

SOURCE=..\..\llapi\span_list.cpp
# End Source File
# Begin Source File

SOURCE=..\..\llapi\surface_data.cpp
# End Source File
# Begin Source File

SOURCE=..\..\llapi\wood.cpp
# End Source File
# Begin Source File

SOURCE=..\..\llapi\worley_basis.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\llapi\atmosphere.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\atmospheric_object.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\attribs.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\attribute.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\base_class.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\bounding_box.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\bsdf.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\camera.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\catrom2.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\checkerboard.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\color.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\debug.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\entity.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\file.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\frame.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\gradient.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\heap_manager.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\image.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\image_filter.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\image_io.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\interval.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\kdtree.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\light.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\llapi_all.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\llapi_defs.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\machine.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\mat_utils.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\material.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\math_tools.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\matrix.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\mesh.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\object.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\object_filter.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\pattern.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\perlin_noise.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\perturbation.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\priority_queue.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\procedural.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\program.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\quaternion.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\ray.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\renderer.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\root_solver.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\sc_noise.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\scene.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\solvers.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\span_list.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\surface_data.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\vector2d.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\vector3d.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\vector_tools.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\volume.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\warning_eliminator.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\wood.h
# End Source File
# Begin Source File

SOURCE=..\..\llapi\worley_basis.h
# End Source File
# End Group
# End Target
# End Project
