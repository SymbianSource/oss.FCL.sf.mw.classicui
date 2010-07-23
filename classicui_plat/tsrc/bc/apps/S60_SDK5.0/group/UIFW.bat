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

md e:\bctest

md e:\bctest\results


copy C:\BCTestLog\BCTESTBUTTON_TestLog.txt e:\bctest\results\UIFW_AVKON_BCTESTBUTTON.txt

copy C:\BCTestLog\BCTestChoicelist_TestLog.txt e:\bctest\results\UIFW_AVKON_BCTESTCHOICELIST.txt

copy C:\BCTestLog\bctestmix50_TestLog.txt e:\bctest\results\UIFW_AVKON_BCTESTMIX50.txt

copy C:\BCTestLog\bctesttoolbar_TestLog.txt e:\bctest\results\UIFW_AVKON_BCTESTTOOLBAR.txt

copy C:\BCTestLog\BCTestTouchPane_TestLog.txt e:\bctest\results\UIFW_AVKON_BCTESTTOUCHPANE.txt

copy C:\BCTestLog\bctesttreelist_TestLog.txt e:\bctest\results\UIFW_AVKON_BCTESTTREELIST.txt

copy C:\BCTestLog\bctestpane_TestLog.txt e:\bctest\results\UIFW_AVKON_BCTESTPANE.txt

