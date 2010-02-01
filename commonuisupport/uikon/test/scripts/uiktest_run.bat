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

testexecute.exe z:\uiktest\uiktest_t_addlibrary.script
testexecute.exe z:\uiktest\uiktest_t_applicationlanguage.script
testexecute.exe z:\uiktest\uiktest_t_applicationlanguagefrench.script
testexecute.exe z:\uiktest\uiktest_t_applicationlanguagenotset.script
testexecute.exe z:\uiktest\uiktest_t_applicationlanguagesc.script
testexecute.exe z:\uiktest\uiktest_t_applicationlanguagezulu.script
testexecute.exe z:\uiktest\uiktest_t_autoLib.script
testexecute.exe z:\uiktest\uiktest_t_backup.script
testexecute.exe z:\uiktest\uiktest_t_brdrcol.script
testexecute.exe z:\uiktest\uiktest_t_capability1.script
testexecute.exe z:\uiktest\uiktest_t_capability2.script
testexecute.exe z:\uiktest\uiktest_t_colovr.script
testexecute.exe z:\uiktest\uiktest_t_colscm.script
testexecute.exe z:\uiktest\uiktest_t_disableexitchecks.script
testexecute.exe z:\uiktest\uiktest_t_eikenv.script
testexecute.exe z:\uiktest\uiktest_t_error.script
testexecute.exe z:\uiktest\uiktest_t_fileutils.script
testexecute.exe z:\uiktest\uiktest_t_focus.script
testexecute.exe z:\uiktest\uiktest_t_hlsprite.script
testexecute.exe z:\uiktest\uiktest_t_msg.script
testexecute.exe z:\uiktest\uiktest_t_nonfocus.script
testexecute.exe z:\uiktest\uiktest_t_notdial.script
testexecute.exe z:\uiktest\uiktest_t_package.script
testexecute.exe z:\uiktest\uiktest_t_parent.script
testexecute.exe z:\uiktest\uiktest_t_shutter.script
testexecute.exe z:\uiktest\uiktest_t_spane.script
testexecute.exe z:\uiktest\uiktest_t_syscolor.script

:: NOTE: Capability test cases must be run first.
:: Otherwise test execution is in alphabetical order.

:: Ignore the following if using this script for emulator testing.
:: Logs are automatically copied on hardware to MMC
:: which is assumed to be drive E:
@echo off
if not exist c:\logs\testexecute\ goto :EOF
md e:\logs
md e:\logs\testexecute
copy c:\logs\testexecute\uiktest*.htm e:\logs\testexecute\