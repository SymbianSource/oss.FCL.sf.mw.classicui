@rem
@rem Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
@rem All rights reserved.
@rem This component and the accompanying materials are made available
@rem under the terms of "Eclipse Public License v1.0"
@rem which accompanies this distribution, and is available
@rem at the URL "http://www.eclipse.org/legal/epl-v10.html".
@rem
@rem Initial Contributors:
@rem Nokia Corporation - initial contribution.
@rem
@rem Contributors:
@rem
@rem Description: 
@rem

testexecute.exe z:\conetest\conetest_t_background.script
testexecute.exe z:\conetest\conetest_t_conecoecntss.script
testexecute.exe z:\conetest\conetest_t_cone0.script
testexecute.exe z:\conetest\conetest_t_cone1.script
testexecute.exe z:\conetest\conetest_t_cone2.script
testexecute.exe z:\conetest\conetest_t_cone3.script
testexecute.exe z:\conetest\conetest_t_cone4exe.script
testexecute.exe z:\conetest\conetest_t_cone5.script
testexecute.exe z:\conetest\conetest_t_cone6.script
testexecute.exe z:\conetest\conetest_t_cone7.script
testexecute.exe z:\conetest\conetest_t_coneerrormsg.script
testexecute.exe z:\conetest\conetest_t_conehelptext.script
testexecute.exe z:\conetest\conetest_t_coneinvalidate.script
testexecute.exe z:\conetest\conetest_t_conetransition.script
testexecute.exe z:\conetest\conetest_t_conevisibility.script
testexecute.exe z:\conetest\conetest_t_conetransparency.script
testexecute.exe z:\conetest\conetest_t_conezoomfont.script
testexecute.exe z:\conetest\conetest_t_coedatastorage.script
testexecute.exe z:\conetest\conetest_t_coneresourceloader.script
testexecute.exe z:\conetest\conetest_t_conestateobs.script
testexecute.exe z:\conetest\conetest_t_conemultiptr.script
testexecute.exe z:\conetest\conetest_t_conemultiptrcompound.script
testexecute.exe z:\conetest\conetest_t_coneevents.script

:: Ignore the following if using this script for emulator testing.
:: Logs are automatically copied on hardware to MMC
:: which is assumed to be drive E:
@echo off
if not exist c:\logs\testexecute\ goto :EOF
md e:\logs
md e:\logs\testexecute
copy c:\logs\testexecute\conetest*.htm e:\logs\testexecute\
