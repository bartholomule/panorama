# Microsoft Developer Studio Project File - Name="libhlapi" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libhlapi - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libhlapi.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libhlapi.mak" CFG="libhlapi - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libhlapi - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libhlapi - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libhlapi - Win32 Release"

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
# ADD CPP /nologo /W3 /GX /O2 /I "../.." /I "../" /D "NDEBUG" /D "_LIB" /D STATIC_LINK=1 /D YYTEXT_POINTER=1 /D STDC_HEADERS=1 /D BROKEN_FILENO_INCLUDE=1 /D BROKEN_RETURN_SUBTYPES_ON_VIRTUAL=1 /D "WIN32" /D "_MBCS" /D TOPDIR=\"../..\" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Lib\Release\libhlapi.lib"

!ELSEIF  "$(CFG)" == "libhlapi - Win32 Debug"

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
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "../.." /I "../" /D "_DEBUG" /D "_LIB" /D STATIC_LINK=1 /D YYTEXT_POINTER=1 /D STDC_HEADERS=1 /D BROKEN_FILENO_INCLUDE=1 /D BROKEN_RETURN_SUBTYPES_ON_VIRTUAL=1 /D "WIN32" /D "_MBCS" /D TOPDIR=\"../..\" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Lib\Debug\libhlapi.lib"

!ENDIF 

# Begin Target

# Name "libhlapi - Win32 Release"
# Name "libhlapi - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\hlapi\aggregate.cpp
# End Source File
# Begin Source File

SOURCE=..\..\hlapi\box.cpp
# End Source File
# Begin Source File

SOURCE=..\..\hlapi\circle.cpp
# End Source File
# Begin Source File

SOURCE=..\..\hlapi\class_manager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\hlapi\cone.cpp
# End Source File
# Begin Source File

SOURCE=..\..\hlapi\csg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\hlapi\cylinder.cpp
# End Source File
# Begin Source File

SOURCE=..\..\hlapi\image_manager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\hlapi\mesh_object.cpp
# End Source File
# Begin Source File

SOURCE=..\..\hlapi\phong_triangle.cpp
# End Source File
# Begin Source File

SOURCE=..\..\hlapi\plane.cpp
# End Source File
# Begin Source File

SOURCE=..\..\hlapi\plugin_manager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\hlapi\rectangle.cpp
# End Source File
# Begin Source File

SOURCE=..\..\hlapi\scene_manager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\hlapi\sphere.cpp
# End Source File
# Begin Source File

SOURCE=..\..\hlapi\torus.cpp
# End Source File
# Begin Source File

SOURCE=..\..\hlapi\triangle.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\hlapi\aggregate.h
# End Source File
# Begin Source File

SOURCE=..\..\hlapi\box.h
# End Source File
# Begin Source File

SOURCE=..\..\hlapi\circle.h
# End Source File
# Begin Source File

SOURCE=..\..\hlapi\class_manager.h
# End Source File
# Begin Source File

SOURCE=..\..\hlapi\cone.h
# End Source File
# Begin Source File

SOURCE=..\..\hlapi\csg.h
# End Source File
# Begin Source File

SOURCE=..\..\hlapi\cylinder.h
# End Source File
# Begin Source File

SOURCE=..\..\hlapi\hlapi_all.h
# End Source File
# Begin Source File

SOURCE=..\..\hlapi\image_manager.h
# End Source File
# Begin Source File

SOURCE=..\..\hlapi\mesh_object.h
# End Source File
# Begin Source File

SOURCE=..\..\hlapi\phong_triangle.h
# End Source File
# Begin Source File

SOURCE=..\..\hlapi\plane.h
# End Source File
# Begin Source File

SOURCE=..\..\hlapi\plugin_manager.h
# End Source File
# Begin Source File

SOURCE=..\..\hlapi\plugins_all.h
# End Source File
# Begin Source File

SOURCE=..\..\hlapi\rectangle.h
# End Source File
# Begin Source File

SOURCE=..\..\hlapi\scene_manager.h
# End Source File
# Begin Source File

SOURCE=..\..\hlapi\sphere.h
# End Source File
# Begin Source File

SOURCE=..\..\hlapi\torus.h
# End Source File
# Begin Source File

SOURCE=..\..\hlapi\triangle.h
# End Source File
# End Group
# End Target
# End Project
