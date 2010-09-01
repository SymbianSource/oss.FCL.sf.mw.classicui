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

cd ../../S60_SDK3.2ed/bctestpreviewpopup/sis
attrib *.sis* -r
makesis bctestpreviewpopup.pkg
signsis bctestpreviewpopup.sis bctestpreviewpopup.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctesttoolbar/sis
attrib *.sis* -r
makesis bctesttoolbar.pkg
signsis bctesttoolbar.sis bctesttoolbar.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctesttreelist/sis
attrib *.sis* -r
makesis bctesttreelist.pkg
signsis bctesttreelist.sis bctesttreelist.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../../sis
attrib *.sis* -r
makesis bctestsdk32ed.pkg
signsis bctestsdk32ed.sis bctestsdk32ed.sisx /s60/rd.cer /s60/rd-key.pem