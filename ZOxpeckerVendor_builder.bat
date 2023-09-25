::  ===========================================================================
::   Main build script for Oxpecker - Canopy Template firmware package
::
::   Pre-requisites:
::           - IAR Workbench is installed in C:\Program Files\IAR Systems.
::
::   Execution-Instructions:
::           - Run this script from within the DCS-Oxpecker folder.
::             The DCS-Oxpecker folder is the folder created when
::             the git project repository is cloned.
::
::            - On successful execution, the build results appear in
::              DCS-Oxpecker/Release
::
::   Arguments: None
::
::   Returns %ERRORLEVEL%
::           : 0 on success
::           : 1 on error
::  ===========================================================================

@ECHO off
SET LOCAL_PATH=%cd%

SET VENDOR_PROJECT_PATH="%LOCAL_PATH%\EWARM\STM32L4R7I_OCB.ewp"


SET THIS_SCRIPT=ZOxpeckerTemplate_builder.bat

ECHO LOCAL_PATH=%LOCAL_PATH%

call :build_vendor_fw %VENDOR_PROJECT_PATH%
exit /B %errorlevel%

:ERROR_BADEXECDIR
ECHO Execution from wrong directory. Script should be run from DCS-Oxpecker folder.
GOTO EEXIT


:build_vendor_fw
   ZBuilder_Library.bat %*

:EEXIT
exit /B 1

