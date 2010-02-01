@echo off
rem
rem Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
rem Description: Build script for MCL BC test drivers.
rem
@echo on

del \epoc32\winscw\c\BCTestLog\config.xml

del bctestlauncher\group\config.xml
copy bctestlauncher\group\config_3x.xml bctestlauncher\group\config.xml

call cd S60_SDKMCL\group
call bldmake bldfiles
call abld build winscw udeb
call abld build armv5 urel

cd ..\..
