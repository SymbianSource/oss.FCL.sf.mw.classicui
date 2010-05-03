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

cd ../../bctestdom3.2/bctestdomaiwakn/sis
attrib *.sis* -r
makesis bctestdomaiwakn.pkg
signsis bctestdomaiwakn.sis bctestdomaiwakn.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestdomcdl/sis
attrib *.sis* -r
makesis bctestdomcdl.pkg
signsis bctestdomcdl.sis bctestdomcdl.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestdomcoreui/sis
attrib *.sis* -r
makesis bctestdomcoreui.pkg
signsis bctestdomcoreui.sis bctestdomcoreui.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestdomfntlay/sis
attrib *.sis* -r
makesis bctestdomfntlay.pkg
signsis bctestdomfntlay.sis bctestdomfntlay.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestdominputmethods/sis
attrib *.sis* -r
makesis bctestdominputmethods.pkg
signsis bctestdominputmethods.sis bctestdominputmethods.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestdomnotifier/sis
attrib *.sis* -r
makesis bctestdomnotifier.pkg
signsis bctestdomnotifier.sis bctestdomnotifier.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestdompopup/sis
attrib *.sis* -r
makesis bctestdompopup.pkg
signsis bctestdompopup.sis bctestdompopup.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../../sis
attrib *.sis* -r
makesis bctestdom32.pkg
signsis bctestdom32.sis bctestdom32.sisx /s60/rd.cer /s60/rd-key.pem