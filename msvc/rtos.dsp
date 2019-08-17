# Microsoft Developer Studio Project File - Name="rtos" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=rtos - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "rtos.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "rtos.mak" CFG="rtos - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "rtos - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "rtos - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "rtos - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Cmd_Line "NMAKE /f rtos.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "rtos.exe"
# PROP BASE Bsc_Name "rtos.bsc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Cmd_Line "nmake /f "rtos.mak""
# PROP Rebuild_Opt "/a"
# PROP Target_File "rtos.exe"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "rtos - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Cmd_Line "NMAKE /f rtos.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "rtos.exe"
# PROP BASE Bsc_Name "rtos.bsc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Cmd_Line "nmake /f "rtos.mak""
# PROP Rebuild_Opt "/a"
# PROP Target_File "rtos.exe"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "rtos - Win32 Release"
# Name "rtos - Win32 Debug"

!IF  "$(CFG)" == "rtos - Win32 Release"

!ELSEIF  "$(CFG)" == "rtos - Win32 Debug"

!ENDIF 

# Begin Group "arch"

# PROP Default_Filter ""
# Begin Group "m128"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\arch\m128\arch.c
# End Source File
# End Group
# Begin Group "c128"

# PROP Default_Filter ""
# End Group
# End Group
# Begin Group "etc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\etc\system.conf
# End Source File
# End Group
# Begin Group "include"

# PROP Default_Filter ""
# Begin Group " m128"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\include\m128\processor.h
# End Source File
# End Group
# Begin Group " c128"

# PROP Default_Filter ""
# End Group
# Begin Source File

SOURCE=..\include\kernel.h
# End Source File
# End Group
# Begin Group "init"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\init\main.c
# End Source File
# End Group
# Begin Group "kernel"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\kernel\kernel.c
# End Source File
# End Group
# Begin Group "lib"

# PROP Default_Filter ""
# End Group
# Begin Group "drivers"

# PROP Default_Filter ""
# End Group
# Begin Source File

SOURCE=..\out\Makefile
# End Source File
# End Target
# End Project
