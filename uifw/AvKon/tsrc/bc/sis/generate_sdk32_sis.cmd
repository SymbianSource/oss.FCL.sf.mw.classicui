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

cd ../../S60_SDK3.2/bcextendedfontapi/sis
attrib *.sis* -r
makesis bcextendedfontapi.pkg
signsis bcextendedfontapi.sis bcextendedfontapi.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestbutton/sis
attrib *.sis* -r
makesis bctestbutton.pkg
signsis bctestbutton.sis bctestbutton.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestchoicelist/sis
attrib *.sis* -r
makesis bctestchoicelist.pkg
signsis bctestchoicelist.sis bctestchoicelist.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestgloballistmsgquery/sis
attrib *.sis* -r
makesis bctestgloballistmsgquery.pkg
signsis bctestgloballistmsgquery.sis bctestgloballistmsgquery.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestlocalizer/sis
attrib *.sis* -r
makesis bctestlocalizer.pkg
signsis bctestlocalizer.sis bctestlocalizer.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestmisc32/sis
attrib *.sis* -r
makesis bctestmisc32.pkg
signsis bctestmisc32.sis bctestmisc32.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestservicehandler/sis
attrib *.sis* -r
makesis bctestservicehandler.pkg
signsis bctestservicehandler.sis bctestservicehandler.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctesttouchpane/sis
attrib *.sis* -r
makesis bctesttouchpane.pkg
signsis bctesttouchpane.sis bctesttouchpane.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestuniteditor/sis
attrib *.sis* -r
makesis bctestuniteditor.pkg
signsis bctestuniteditor.sis bctestuniteditor.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestutilities/sis
attrib *.sis* -r
makesis bctestutilities.pkg
signsis bctestutilities.sis bctestutilities.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../../sis
attrib *.sis* -r
makesis bctestsdk32.pkg
signsis bctestsdk32.sis bctestsdk32.sisx /s60/rd.cer /s60/rd-key.pem