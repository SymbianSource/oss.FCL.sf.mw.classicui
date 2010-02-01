@echo off
rem Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
rem All rights reserved.
rem This component and the accompanying materials are made available
rem under the terms of "Eclipse Public License v1.0"
rem which accompanies this distribution, and is available
rem at the URL "http://www.eclipse.org/legal/epl-v10.html".
rem
rem Initial Contributors:
rem Nokia Corporation - initial contribution.
rem
rem Contributors:
rem
rem Description:
rem This batch file allows multiplealarm tests to run in textshell mode (WINSCW only!)
rem 
rem

setlocal
if not defined EPOC_INI set EPOC_INI=%EPOCROOT%epoc32\data\epoc.ini

if "%1"=="?" goto help
if "%1"=="" goto help
goto %1
goto help

rem ================ Install ==============
:install

@echo.
@echo ---------------------------------------------------------------------------------------------------------------------
@echo Backing up EPOC.INI, and adding line to EPOC.INI so that the system starter will start the emulator in textshell mode
@echo ---------------------------------------------------------------------------------------------------------------------
@echo.
if not exist %EPOCROOT%epoc32\data\epoc.bak copy %EPOC_INI% %EPOCROOT%epoc32\data\epoc.bak >nul
echo. >> %EPOC_INI%
echo StartupMode 1 >> %EPOC_INI%
goto :done


rem ================ Uninstall ==============
:uninstall
@echo.
@echo ------------------
@echo Restoring EPOC.INI
@echo ------------------
@echo.
if exist %EPOCROOT%epoc32\data\epoc.bak xcopy /r /y %EPOCROOT%epoc32\data\epoc.bak %EPOC_INI% >nul
if exist %EPOCROOT%epoc32\data\epoc.bak del %EPOCROOT%epoc32\data\epoc.bak
goto :done


rem ================ HELP! =================
:help
@echo.
@echo ----------------------------------------------
@echo The usage of this setup file is the following
@echo.
@echo    install    to set up textshell environment.
@echo    unistall   to restore previous environment.
@echo ----------------------------------------------
@echo.

:done
endlocal
