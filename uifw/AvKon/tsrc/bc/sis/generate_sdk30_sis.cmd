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
signsis bctestutil.sis bctestutil3.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestlauncher/sis
attrib *.sis* -r
makesis bctestlauncher.pkg
signsis bctestlauncher.sis bctestlauncher3.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../S60_SDK3.0/bctestaknsound/sis
attrib *.sis* -r
makesis bctestaknsound.pkg
signsis bctestaknsound.sis bctestaknsound3.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestappfrm/sis
attrib *.sis* -r
makesis bctestappfrm.pkg
signsis bctestappfrm.sis bctestappfrm3.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestbuttons/sis
attrib *.sis* -r
makesis bctestbuttons.pkg
signsis bctestbuttons.sis bctestbuttons3.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestcmdlg/sis
attrib *.sis* -r
makesis bctestcmdlg.pkg
signsis bctestcmdlg.sis bctestcmdlg3.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestdocandinit/sis
attrib *.sis* -r
makesis bctestdocandinit.pkg
signsis bctestdocandinit.sis bctestdocandinit3.sisx /s60/rd.cer /s60/rd-key.pem


cd ../../bctesteditor/sis
attrib *.sis* -r
makesis bctesteditor.pkg
signsis bctesteditor.sis bctesteditor3.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctesteh/sis
attrib *.sis* -r
makesis bctesteh.pkg
signsis bctesteh.sis bctesteh3.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctesteikbctrl/sis
attrib *.sis* -r
makesis bctesteikbctrl.pkg
signsis bctesteikbctrl.sis bctesteikbctrl3.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctesteikfrm/sis
attrib *.sis* -r
makesis bctesteikfrm.pkg
signsis bctesteikfrm.sis bctesteikfrm3.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestfontinput/sis
attrib *.sis* -r
makesis bctestfontinput.pkg
signsis bctestfontinput.sis bctestfontinput3.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestform/sis
attrib *.sis* -r
makesis bctestform.pkg
signsis bctestform.sis bctestform3.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestgrids/sis
attrib *.sis* -r
makesis bctestgrids.pkg
signsis bctestgrids.sis bctestgrids3.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestimage/sis
attrib *.sis* -r
makesis bctestimage.pkg
signsis bctestimage.sis bctestimage3.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestkeylock/sis
attrib *.sis* -r
makesis bctestkeylock.pkg
signsis bctestkeylock.sis bctestkeylock3.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestlabelinfoindicators/sis
attrib *.sis* -r
makesis bctestlabelinfoindicators.pkg
signsis bctestlabelinfoindicators.sis bctestlabelinfoindicators3.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestlist/sis
attrib *.sis* -r
makesis bctestlist.pkg
signsis bctestlist.sis bctestlist3.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestmenu/sis
attrib *.sis* -r
makesis bctestmenu.pkg
signsis bctestmenu.sis bctestmenu3.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestmisccontrol/sis
attrib *.sis* -r
makesis bctestmisccontrol.pkg
signsis bctestmisccontrol.sis bctestmisccontrol3.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestnote/sis
attrib *.sis* -r
makesis bctestnote.pkg
signsis bctestnote.sis bctestnote3.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestnotifier/sis
attrib *.sis* -r
makesis bctestnotifier.pkg
signsis bctestnotifier.sis bctestnotifier3.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestpane/sis
attrib *.sis* -r
makesis bctestpane.pkg
signsis bctestpane.sis bctestpane3.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestpopups/sis
attrib *.sis* -r
makesis bctestpopups.pkg
signsis bctestpopups.sis bctestpopups3.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestprivateuifrm/sis
attrib *.sis* -r
makesis bctestprivateuifrm.pkg
signsis bctestprivateuifrm.sis bctestprivateuifrm3.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestptieng/sis
attrib *.sis* -r
makesis bctestptieng.pkg
signsis bctestptieng.sis bctestptieng3.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestquery/sis
attrib *.sis* -r
makesis bctestquery.pkg
signsis bctestquery.sis bctestquery3.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestscreenclearer/sis
attrib *.sis* -r
makesis bctestscreenclearer.pkg
signsis bctestscreenclearer.sis bctestscreenclearer3.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestscrollerbar/sis
attrib *.sis* -r
makesis bctestscrollerbar.pkg
signsis bctestscrollerbar.sis bctestscrollerbar3.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestsearchfield/sis
attrib *.sis* -r
makesis bctestsearchfield.pkg
signsis bctestsearchfield.sis bctestsearchfield3.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestserverapp/sis
attrib *.sis* -r
makesis bctestserverapp.pkg
signsis bctestserverapp.sis bctestserverapp3.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestsettingpage/sis
attrib *.sis* -r
makesis bctestsettingpage.pkg
signsis bctestsettingpage.sis bctestsettingpage3.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestskins/sis
attrib *.sis* -r
makesis bctestskins.pkg
signsis bctestskins.sis bctestskins3.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestsliderandicons/sis
attrib *.sis* -r
makesis bctestsliderandicons.pkg
signsis bctestsliderandicons.sis bctestsliderandicons3.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestutilities/sis
attrib *.sis* -r
makesis bctestutilities.pkg
signsis bctestutilities.sis bctestutilities3.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../bctestvolume/sis
attrib *.sis* -r
makesis bctestvolume.pkg
signsis bctestvolume.sis bctestvolume3.sisx /s60/rd.cer /s60/rd-key.pem

cd ../../../sis
attrib *.sis* -r
makesis bctestsdk30.pkg
signsis bctestsdk30.sis bctestsdk30.sisx /s60/rd.cer /s60/rd-key.pem