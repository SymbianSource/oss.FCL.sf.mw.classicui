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
rem Description:
rem
@echo on

@echo -this command generates sis files to bctest-
@echo -remember first to build all tests to armv5-

@echo on

cd ../bctestutil/sis
attrib *.sis* -r
makesis bctestutil.pkg
signsis bctestutil.sis bctestutil.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestlauncher/sis
attrib *.sis* -r
makesis bctestlauncher.pkg
signsis bctestlauncher.sis bctestlauncher.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../S60_SDK3.1/bctestlocation/sis
attrib *.sis* -r
makesis bctestlocation.pkg
signsis bctestlocation.sis bctestlocation.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestmisc/sis
attrib *.sis* -r
makesis bctestmisc.pkg
signsis bctestmisc.sis bctestmisc.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestocr/sis
attrib *.sis* -r
makesis bctestocr.pkg
signsis bctestocr.sis bctestocr.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../../sis
attrib *.sis* -r
makesis bctestsdk31.pkg
signsis bctestsdk31.sis bctestsdk31.sisx /s60/rd.cer /s60/rd-key.pem