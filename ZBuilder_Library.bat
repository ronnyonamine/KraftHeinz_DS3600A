::  ===========================================================================
::   Function Library for Oxpecker - Canopy firmware building
:: 
::   Pre-requisites:
::           - IAR Workbench is installed in C:\Program Files(x86)\IAR Systems.
::
::   Execution-Instructions:
::             Call these functions from a script that runs within the DCS-Oxpecker folder.
::             The DCS-Oxpecker folder is the folder created when
::             the git project repository is cloned.
::  
::   Arguments: Full Path to the Project ewp file
::  
::   Returns %ERRORLEVEL%
::           : 0 on success
::           : 1 on error
::  ===========================================================================  
@echo off

:build_vendor_fw
   SET TEMPLATE_BUILD="3"
   SET PROJECT_PATH=%~1
   SET LOCAL_PATH=%cd%
   SET TEMPLATE_BOOTLOADER1_BIN_PATH="%LOCAL_PATH%\Platform\bootloader1.bin"
   SET TEMPLATE_BOOTLOADER2_BIN_PATH="%LOCAL_PATH%\Platform\bootloader2.bin"
   SET PROJECT_BIN_PATH="%LOCAL_PATH%\EWARM\Oxpecker\Exe\STM32L4RI_OCB-0x8010000.bin"
   SET PROJECT_VENDOR_CONFIGURATION="Oxpecker"
   SET PACKTOOL_CONFIGURATION="%LOCAL_PATH%\OxpeckerTemplateConfig.xml"
   GOTO MAINBUILD

:build_template_fw
   SET TEMPLATE_BUILD="2"
   SET PROJECT_PATH=%~1
   SET LOCAL_PATH=%cd%
   SET TEMPLATE_BOOTLOADER1_BIN_PATH="%LOCAL_PATH%\Platform\bootloader1.bin"
   SET TEMPLATE_BOOTLOADER2_BIN_PATH="%LOCAL_PATH%\Platform\bootloader2.bin"
   SET PROJECT_BIN_PATH="%LOCAL_PATH%\EWARM_Deployable\Oxpecker\Exe\STM32L4R7I_OCB-0x8010000.bin"
   SET PROJECT_STATICLIB_CONFIGURATION="Full_Lib"
   SET PROJECT_DEPLOYABLE_CONFIGURATION="Oxpecker"
   SET PACKTOOL_CONFIGURATION="%LOCAL_PATH%\OxpeckerTemplateConfig.xml"
   GOTO MAINBUILD

:build_canopy_fw
   SET TEMPLATE_BUILD="1"
   SET PROJECT_PATH=%~1
   SET LOCAL_PATH=%cd%
   SET BOOTLOADER1_BIN_PATH="%LOCAL_PATH%\Bootloader\Oxpecker_bootloader_1\EWARM\STM32L4R7I_OCB.1stBootloader\Exe\STM32L4R7I_OCB.1stBootloader.bin"
   SET BOOTLOADER2_BIN_PATH="%LOCAL_PATH%\Bootloader\Oxpecker_bootloader_2\EWARM\STM32L4R7I_OCB\Exe\STM32L4R7I_OCB.bin"
   SET PROJECT_BIN_PATH="%LOCAL_PATH%\EWARM_Oxpecker\STM32L4R7I_OCB\Exe\STM32L4R7I_OCB-0x8010000.bin"
   SET BOOTLOADER1_CONFIGURATION=STM32L4R7I_OCB.1stBootloader
   SET BOOTLOADER2_CONFIGURATION=STM32L4R7I_OCB
   SET PROJECT_CONFIGURATION=STM32L4R7I_OCB
   SET PACKTOOL_CONFIGURATION="%LOCAL_PATH%\OxpeckerTemplateConfig.xml"

   :MAINBUILD
   SET BOOTLOADER1_PATH="%LOCAL_PATH%\Bootloader\Oxpecker_bootloader_1\EWARM\STM32L4R7I_OCB.1stBootloader.ewp"
   SET BOOTLOADER2_PATH="%LOCAL_PATH%\Bootloader\Oxpecker_bootloader_2\EWARM\STM32L4R7I_OCB.ewp"
   SET TOOLKIT_COMMON_DIR="C:\Program Files\IAR Systems\Embedded Workbench 9.0\common\bin\"
   SET TOOLKIT_ARM_DIR="C:\Program Files\IAR Systems\Embedded Workbench 9.0\arm\bin\"
   SET TARGET_UI=Oxpecker
   SET BUILD_LOG="%LOCAL_PATH%"\Release\Oxpecker_build_log.txt

   :: Alter Bootloader bin paths if template build
   IF %TEMPLATE_BUILD%=="2" (
      SET BOOTLOADER1_BIN_PATH="%TEMPLATE_BOOTLOADER1_BIN_PATH%"
      SET BOOTLOADER2_BIN_PATH="%TEMPLATE_BOOTLOADER2_BIN_PATH%"
   )

   IF %TEMPLATE_BUILD%=="3" (
      SET BOOTLOADER1_BIN_PATH="%TEMPLATE_BOOTLOADER1_BIN_PATH%"
      SET BOOTLOADER2_BIN_PATH="%TEMPLATE_BOOTLOADER2_BIN_PATH%"
   )


   ECHO SET operations completed...
   ECHO =====================================
   IF %TEMPLATE_BUILD%=="1" (
      ECHO Build type: Complete build.
   )
   IF %TEMPLATE_BUILD%=="2" (
      ECHO Build type: Template build.
   )
   IF %TEMPLATE_BUILD%=="3" (
      ECHO Build type: Vendor build.
   )
   ECHO =====================================
 
   :: check build tool
   IF NOT EXIST %TOOLKIT_COMMON_DIR%IarBuild.exe (GOTO ERROR_NO_IARINSTALL)
   IF NOT EXIST %TOOLKIT_ARM_DIR%ielftool.exe (GOTO ERROR_NO_IARIARINSTALL)

   ECHO check build tool completed...

   :: make and populate folders
   IF NOT EXIST "%LOCAL_PATH%\Release" ( 
      MKDIR "%LOCAL_PATH%\Release" 
      ECHO mkdir %LOCAL_PATH%\Release
   )
   IF NOT EXIST "%LOCAL_PATH%\Release\bin" ( 
      MKDIR "%LOCAL_PATH%\Release\bin"
      ECHO mkdir %LOCAL_PATH%\Release\bin
   )
   IF NOT EXIST "%LOCAL_PATH%\Release\hex" ( 
      MKDIR "%LOCAL_PATH%\Release\hex"
      ECHO mkdir %LOCAL_PATH%\Release\hex
   )


   :: delete build log if it exists
   IF EXIST %BUILD_LOG% ( del %BUILD_LOG% )

   ECHO make folder completed...

   :: dump environment 
   ECHO ===============================>>%BUILD_LOG%
   ECHO Environment dump>>%BUILD_LOG%
   SET >>%BUILD_LOG%
   ECHO ===============================>>%BUILD_LOG% 

   
   :: check package tool for vendor build
   IF %TEMPLATE_BUILD%=="1" (
      GOTO PACKINFONONCHECK
   )
   IF %TEMPLATE_BUILD%=="2" (
      GOTO PACKCONFIGCHECK
   )
   IF %TEMPLATE_BUILD%=="3" (
      GOTO PACKCONFIGCHECK
   )

   :: Should never get here.
   ECHO +++Error Internal error
   GOTO EEXIT

   :PACKINFONONCHECK

   IF EXIST %PACKTOOL_CONFIGURATION% (
      ECHO +++Error Package tool configuration file not allowed for this build
      ECHO %PACKTOOL_CONFIGURATION%
      GOTO EEXIT
   )

   GOTO PACKINFOCHECKDONE

   :PACKCONFIGCHECK
   IF NOT EXIST %PACKTOOL_CONFIGURATION% (
      ECHO +++Error Package tool configuration not found
      ECHO %PACKTOOL_CONFIGURATION%
      GOTO EEXIT
   )

   :PACKINFOCHECKDONE

   :: build bootloader1
   IF  %TEMPLATE_BUILD%=="1" (
   ECHO ===============================>>%BUILD_LOG%
   IF EXIST %BOOTLOADER1_BIN_PATH% ( del %BOOTLOADER1_BIN_PATH% )
   ECHO Build bootloader1... 
   ECHO START to build bootloader1>>%BUILD_LOG%

   ECHO "invoking..." -log all>>%BUILD_LOG%

   %TOOLKIT_COMMON_DIR%IarBuild.exe %BOOTLOADER1_PATH% -build %BOOTLOADER1_CONFIGURATION% -log all>>%BUILD_LOG%
   ECHO Build bootloader1 finished>>%BUILD_LOG%
   )

   IF %TEMPLATE_BUILD%=="2" ( 
   ECHO bootloader1 build skipped
   )
   IF %TEMPLATE_BUILD%=="3" ( 
   ECHO bootloader1 build skipped
   )

   :: build bootloader2
   if %TEMPLATE_BUILD%=="1" (
   ECHO ===============================>>%BUILD_LOG%
   if EXIST %BOOTLOADER2_BIN_PATH% ( del %BOOTLOADER2_BIN_PATH% )
   ECHO Build bootloader2... 
   ECHO START to build bootloader2>>%BUILD_LOG%
   %TOOLKIT_COMMON_DIR%IarBuild.exe %BOOTLOADER2_PATH% -build %BOOTLOADER2_CONFIGURATION% -log all>>%BUILD_LOG%
   ECHO Build bootloader2 finished>>%BUILD_LOG%
   )
   IF %TEMPLATE_BUILD%=="2" ( 
      ECHO bootloader2 build skipped
   )
   IF %TEMPLATE_BUILD%=="3" ( 
      ECHO bootloader2 build skipped
   )

   :: bootloader binary check
   IF NOT EXIST %BOOTLOADER1_BIN_PATH% (
      ECHO +++Error: bootloader 1 binary not found
      ECHO %BOOTLOADER1_BIN_PATH%
      GOTO EEXIT
   )
   IF NOT EXIST %BOOTLOADER2_BIN_PATH% (
      ECHO +++Error: bootloader 2 binary not found
      ECHO %BOOTLOADER2_BIN_PATH%
      GOTO EEXIT
   )

   

   :: build project
   ECHO ===============================>>%BUILD_LOG%
   ECHO Build project... 
   ECHO START to build project>>%BUILD_LOG%

   IF EXIST %PROJECT_BIN_PATH% ( del %PROJECT_BIN_PATH% )

   IF %TEMPLATE_BUILD%=="1" (
      ECHO %TOOLKIT_COMMON_DIR%IarBuild.exe "%PROJECT_PATH%" -build %PROJECT_CONFIGURATION%
      %TOOLKIT_COMMON_DIR%IarBuild.exe "%PROJECT_PATH%" -build %PROJECT_CONFIGURATION% -log all>>%BUILD_LOG%
      ECHO %TOOLKIT_ARM_DIR%ielftool.exe --bin-multi --verbose "%LOCAL_PATH%\EWARM_Oxpecker\STM32L4R7I_OCB\Exe\STM32L4R7I_OCB.out" "%LOCAL_PATH%\EWARM_Oxpecker\STM32L4R7I_OCB\Exe\STM32L4R7I_OCB.bin"
      %TOOLKIT_ARM_DIR%ielftool.exe --bin-multi --verbose "%LOCAL_PATH%\EWARM_Oxpecker\STM32L4R7I_OCB\Exe\STM32L4R7I_OCB.out" "%LOCAL_PATH%\EWARM_Oxpecker\STM32L4R7I_OCB\Exe\STM32L4R7I_OCB.bin"
   )
   IF %TEMPLATE_BUILD%=="2" (
      ECHO building template_static_lib>>%BUILD_LOG%
      ECHO building template static lib...  
      %TOOLKIT_COMMON_DIR%IarBuild.exe "%TEMPLATE_STATIC_LIB_CONFIG%" -build %PROJECT_STATICLIB_CONFIGURATION% -log all>>%BUILD_LOG%
   )
   IF %TEMPLATE_BUILD%=="2" (
      ECHO building Deployable Oxpecker>>%BUILD_LOG%
      ECHO building Deployable Oxpecker...
      %TOOLKIT_COMMON_DIR%IarBuild.exe "%TEMPLATE_DEPLOY_PROJ_CONFIG%"  -build "%PROJECT_DEPLOYABLE_CONFIGURATION%" -log all>>%BUILD_LOG%
      %TOOLKIT_ARM_DIR%ielftool.exe --bin-multi --verbose "%LOCAL_PATH%\EWARM_Deployable\Oxpecker\Exe\STM32L4R7I_OCB.out" "%LOCAL_PATH%\EWARM_Deployable\Oxpecker\Exe\STM32L4R7I_OCB.bin"
   )
   IF %TEMPLATE_BUILD%=="3" (
      ECHO building Vendor Oxpecker>>%BUILD_LOG%
      ECHO building Vendor Oxpecker...
      %TOOLKIT_COMMON_DIR%IarBuild.exe "%VENDOR_PROJECT_PATH%"  -build "%PROJECT_VENDOR_CONFIGURATION%" -log all>%BUILD_LOG%
      %TOOLKIT_ARM_DIR%ielftool.exe --bin-multi --verbose "%LOCAL_PATH%\EWARM\Oxpecker\Exe\STM32L4R7I_OCB.out" "%LOCAL_PATH%\EWARM\Oxpecker\Exe\STM32L4RI_OCB.bin"
   )

   ECHO Build project finished>>%BUILD_LOG%

   :: check Project Bin 
   IF NOT EXIST %PROJECT_BIN_PATH% (
         ECHO +++Error: project bin file not found
         ECHO %PROJECT_BIN_PATH%
         GOTO EEXIT
   ) 


   :: copy bin file
   ECHO ===============================>>%BUILD_LOG%
   ECHO Do File Copy...
   ECHO Copying binary Files to release folder>>%BUILD_LOG% 

   copy "%BOOTLOADER1_BIN_PATH%" "%LOCAL_PATH%\Release\bin\bootloader1.bin"
   copy "%BOOTLOADER2_BIN_PATH%" "%LOCAL_PATH%\Release\bin\bootloader2.bin"
   copy /b "%LOCAL_PATH%\Release\bin\bootloader1.bin"+"%LOCAL_PATH%\Release\bin\bootloader2.bin" "%LOCAL_PATH%\Release\bin\bootloader.bin"
   copy "%PROJECT_BIN_PATH%" "%LOCAL_PATH%\Release\bin\project.bin"
   ECHO binary file copy finished>>%BUILD_LOG%
   ECHO ===============================>>%BUILD_LOG%



   ECHO ===============================>>%BUILD_LOG%
   ECHO Build package...
   ECHO START building Package>>%BUILD_LOG%
   Oxpecker_Package_Tool.exe .\

   ECHO package finished>>%BUILD_LOG%
   ECHO ===============================>>%BUILD_LOG%

   GOTO PASS

   :ERROR_NO_IARINSTALL
   CD "%LOCAL_PATH%"
   ECHO IAR Workbench not installed.
   GOTO EEXIT

   :EEXIT
   exit /B 1

   :PASS
   exit /B 0




