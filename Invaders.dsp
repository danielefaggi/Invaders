# Microsoft Developer Studio Project File - Name="Invaders" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Invaders - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Invaders.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Invaders.mak" CFG="Invaders - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Invaders - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Invaders - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Invaders - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 msimg32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Invaders - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 msimg32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Invaders - Win32 Release"
# Name "Invaders - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Bitmaps.cpp
# End Source File
# Begin Source File

SOURCE=.\Invaders.cpp
# End Source File
# Begin Source File

SOURCE=.\Invaders.rc
# End Source File
# Begin Source File

SOURCE=.\Logic.cpp
# End Source File
# Begin Source File

SOURCE=.\Renderer.cpp
# End Source File
# Begin Source File

SOURCE=.\Sounds.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Bitmaps.h
# End Source File
# Begin Source File

SOURCE=.\Invaders.h
# End Source File
# Begin Source File

SOURCE=.\Logic.h
# End Source File
# Begin Source File

SOURCE=.\Renderer.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\Sounds.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\alien1_1.bmp
# End Source File
# Begin Source File

SOURCE=.\alien1_2.bmp
# End Source File
# Begin Source File

SOURCE=.\alien2_1.bmp
# End Source File
# Begin Source File

SOURCE=.\alien2_2.bmp
# End Source File
# Begin Source File

SOURCE=.\alien3_1.bmp
# End Source File
# Begin Source File

SOURCE=.\alien3_2.bmp
# End Source File
# Begin Source File

SOURCE=.\aliens21.bmp
# End Source File
# Begin Source File

SOURCE=.\aliens22.bmp
# End Source File
# Begin Source File

SOURCE=.\aliensh1.bmp
# End Source File
# Begin Source File

SOURCE=.\backg2.bmp
# End Source File
# Begin Source File

SOURCE=.\backgound.bmp
# End Source File
# Begin Source File

SOURCE=.\background22.bmp
# End Source File
# Begin Source File

SOURCE=.\background23.BMP
# End Source File
# Begin Source File

SOURCE=.\defence1.bmp
# End Source File
# Begin Source File

SOURCE=.\defence2.bmp
# End Source File
# Begin Source File

SOURCE=.\defence3.bmp
# End Source File
# Begin Source File

SOURCE=.\defref1.bmp
# End Source File
# Begin Source File

SOURCE=.\defref2.bmp
# End Source File
# Begin Source File

SOURCE=.\defref3.bmp
# End Source File
# Begin Source File

SOURCE=.\expl1_1.bmp
# End Source File
# Begin Source File

SOURCE=.\expl1_2.bmp
# End Source File
# Begin Source File

SOURCE=.\expl1_3.bmp
# End Source File
# Begin Source File

SOURCE=.\Invaders.ico
# End Source File
# Begin Source File

SOURCE=.\live.bmp
# End Source File
# Begin Source File

SOURCE=.\mship.bmp
# End Source File
# Begin Source File

SOURCE=.\small.ico
# End Source File
# Begin Source File

SOURCE=.\tank.bmp
# End Source File
# Begin Source File

SOURCE=.\tank_sho.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\big_explosion.wav
# End Source File
# Begin Source File

SOURCE=.\chop.wav
# End Source File
# Begin Source File

SOURCE=.\explosion.wav
# End Source File
# Begin Source File

SOURCE=.\laser.wav
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
