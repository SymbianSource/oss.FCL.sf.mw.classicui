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

cd ../../S60_SDK5.0/bctestappfrm/sis
attrib *.sis* -r
makesis bctestappfrm.pkg
signsis bctestappfrm.sis bctestappfrm.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestdocandinit/sis
attrib *.sis* -r
makesis bctestdocandinit.pkg
signsis bctestdocandinit.sis bctestdocandinit.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestfontinput/sis
attrib *.sis* -r
makesis bctestfontinput.pkg
signsis bctestfontinput.sis bctestfontinput.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestmix50/sis
attrib *.sis* -r
makesis bctestmix50.pkg
signsis bctestmix50.sis bctestmix50.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestmultidriver/sis
attrib *.sis* -r
makesis bctestmultidriver.pkg
signsis bctestmultidriver.sis bctestmultidriver.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestsettingpage/sis
attrib *.sis* -r
makesis bctestsettingpage.pkg
signsis bctestsettingpage.sis bctestsettingpage.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestsliderandicons/sis
attrib *.sis* -r
makesis bctestsliderandicons.pkg
signsis bctestsliderandicons.sis bctestsliderandicons.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../../sis
attrib *.sis* -r
makesis bctestsdk50.pkg
signsis bctestsdk50.sis bctestsdk50.sisx /s60/rd.cer /s60/rd-key.pem