# Microsoft Developer Studio Project File - Name="PktLib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=PktLib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PktLib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PktLib.mak" CFG="PktLib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PktLib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "PktLib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PktLib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Libs"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "_USE_PACKETLIB" /D "WIN32" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "PktLib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Libs"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MTd /W3 /GX /Z7 /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_USE_PACKETLIB" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Libs\PktLibD.lib"

!ENDIF 

# Begin Target

# Name "PktLib - Win32 Release"
# Name "PktLib - Win32 Debug"
# Begin Source File

SOURCE=..\Counter64Varbind.cpp
# End Source File
# Begin Source File

SOURCE=..\CounterVarbind.cpp
# End Source File
# Begin Source File

SOURCE=..\GaugeVarbind.cpp
# End Source File
# Begin Source File

SOURCE=..\GenericPacket.cpp
# End Source File
# Begin Source File

SOURCE=..\InformPdu.cpp
# End Source File
# Begin Source File

SOURCE=..\IntVarbind.cpp
# End Source File
# Begin Source File

SOURCE=..\IpAddrVarbind.cpp
# End Source File
# Begin Source File

SOURCE=..\OidVarbind.cpp
# End Source File
# Begin Source File

SOURCE=..\OpaqueVarbind.cpp
# End Source File
# Begin Source File

SOURCE=..\Packet.cpp
# End Source File
# Begin Source File

SOURCE=..\Poller.cpp
# End Source File
# Begin Source File

SOURCE=..\Scalar64Varbind.cpp
# End Source File
# Begin Source File

SOURCE=..\ScalarVarbind.cpp
# End Source File
# Begin Source File

SOURCE=..\security.cpp
# End Source File
# Begin Source File

SOURCE=..\SnmpException.cpp
# End Source File
# Begin Source File

SOURCE=..\SnmpParser.cpp
# End Source File
# Begin Source File

SOURCE=..\StringVarbind.cpp
# End Source File
# Begin Source File

SOURCE=..\Thread.cpp
# End Source File
# Begin Source File

SOURCE=..\TimeTickVarbind.cpp
# End Source File
# Begin Source File

SOURCE=..\Udp.cpp
# End Source File
# Begin Source File

SOURCE=..\UdpClient.cpp
# End Source File
# Begin Source File

SOURCE=..\UdpServer.cpp
# End Source File
# Begin Source File

SOURCE=..\V1GetNextPdu.cpp
# End Source File
# Begin Source File

SOURCE=..\V1GetPdu.cpp
# End Source File
# Begin Source File

SOURCE=..\V1Pdu.cpp
# End Source File
# Begin Source File

SOURCE=..\V1ResponsePdu.cpp
# End Source File
# Begin Source File

SOURCE=..\V1SetPdu.cpp
# End Source File
# Begin Source File

SOURCE=..\V1TrapPdu.cpp
# End Source File
# Begin Source File

SOURCE=..\V2GetBulkPdu.cpp
# End Source File
# Begin Source File

SOURCE=..\V2Notification.cpp
# End Source File
# Begin Source File

SOURCE=..\V2TrapPdu.cpp
# End Source File
# Begin Source File

SOURCE=..\Varbind.cpp
# End Source File
# Begin Source File

SOURCE=..\VarbindList.cpp
# End Source File
# Begin Source File

SOURCE=..\VbPair.cpp
# End Source File
# End Target
# End Project
