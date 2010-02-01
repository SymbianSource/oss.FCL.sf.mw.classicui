/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:  Description
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknscreenmode.h>
#include <e32err.h>
#include <gdi.h>
#include <coemain.h>
#include <aknappui.h> 

#include "testsdkscreenmode.h"

TInt const KExpected = 0;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestsdkscreenmode::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestSDKScreenMode::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctestsdkscreenmode::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKScreenMode::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestSMSizeInPixels", CTestSDKScreenMode::TestSMSizeInPixels ),
        ENTRY( "TestSMDisplayMode", CTestSDKScreenMode::TestSMDisplayMode ),
        ENTRY( "TestSMModeNumber", CTestSDKScreenMode::TestSMModeNumber ),
        ENTRY( "TestSModesGetModes", CTestSDKScreenMode::TestSModesGetModes ),
        ENTRY( "TestSModesCount", CTestSDKScreenMode::TestSModesCount ),
        ENTRY( "TestSModesoperator", CTestSDKScreenMode::TestSModesoperator ),
        ENTRY( "TestSModesSetAppUiScreenModeL", CTestSDKScreenMode::TestSModesSetAppUiScreenModeL ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

//-----------------------------------------------------------------------------
// Ctestsdkscreenmode::TestSMSizeInPixels
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
TInt CTestSDKScreenMode::TestSMSizeInPixels(CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KSMTestModule, "SSTestModule" );
    _LIT( KSMSizeInPixels, "In SPIDNewL" );
    TestModuleIf().Printf( 0, KSMTestModule, KSMSizeInPixels );
    // Print to log file
    iLog->Log( KSMSizeInPixels );
    
    TAknScreenModes screenModes = TAknScreenModes::GetModes(); 
    TAknScreenMode screenMode = screenModes[0]; 
    TSize iSize = screenMode.SizeInPixels();
    
    return KErrNone;
    }

//-----------------------------------------------------------------------------
// Ctestsdkscreenmode::TestSMDisplayMode
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
TInt CTestSDKScreenMode::TestSMDisplayMode(CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KSMTestModule, "SSTestModule" );
    _LIT( KSMDisplayMode, "In SPIDNewL" );
    TestModuleIf().Printf( 0, KSMTestModule, KSMDisplayMode );
    // Print to log file
    iLog->Log( KSMDisplayMode );
    
    TAknScreenModes screenModes = TAknScreenModes::GetModes(); 
    TAknScreenMode screenMode = screenModes[0];
    TDisplayMode actual = screenMode.DisplayMode();
    
    return KErrNone;
    }

//-----------------------------------------------------------------------------
// Ctestsdkscreenmode::TestSMModeNumber
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
TInt CTestSDKScreenMode::TestSMModeNumber(CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KSMTestModule, "SSTestModule" );
    _LIT( KSMModeNumber, "In SPIDNewL" );
    TestModuleIf().Printf( 0, KSMTestModule, KSMModeNumber );
    // Print to log file
    iLog->Log( KSMModeNumber );
    
    TAknScreenModes screenModes = TAknScreenModes::GetModes(); 
    TAknScreenMode screenMode = screenModes[0];
    TInt actual = screenMode.ModeNumber();
    STIF_ASSERT_EQUALS( KExpected, actual );
    
    return KErrNone;
    }

//===============================class TAknScreenModes=========================
//-----------------------------------------------------------------------------
// Ctestsdkscreenmode::TestSModeSGetModes
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
TInt CTestSDKScreenMode::TestSModesGetModes(CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KSMTestModule, "SSTestModule" );
    _LIT( KSMModeNumber, "In SPIDNewL" );
    TestModuleIf().Printf( 0, KSMTestModule, KSMModeNumber );
    // Print to log file
    iLog->Log( KSMModeNumber );
    
    TAknScreenModes screenModes = TAknScreenModes::GetModes(); 
    
    return KErrNone;
    }

//-----------------------------------------------------------------------------
// Ctestsdkscreenmode::TestSModeSCount
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
TInt CTestSDKScreenMode::TestSModesCount(CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KSMTestModule, "SSTestModule" );
    _LIT( KSMModeNumber, "In SPIDNewL" );
    TestModuleIf().Printf( 0, KSMTestModule, KSMModeNumber );
    // Print to log file
    iLog->Log( KSMModeNumber );
    
    TAknScreenModes screenModes = TAknScreenModes::GetModes(); 
    TInt actual = screenModes.Count();
    STIF_ASSERT_NOT_EQUALS( KExpected, actual );
    
    return KErrNone;
    }

//-----------------------------------------------------------------------------
// Ctestsdkscreenmode::TestSModeSoperator
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
TInt CTestSDKScreenMode::TestSModesoperator(CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KSMTestModule, "SSTestModule" );
    _LIT( KSMModeNumber, "In SPIDNewL" );
    TestModuleIf().Printf( 0, KSMTestModule, KSMModeNumber );
    // Print to log file
    iLog->Log( KSMModeNumber );
    
    TAknScreenModes screenModes = TAknScreenModes::GetModes(); 
    TAknScreenMode screenMode = screenModes.operator []( 0 );
    
    return KErrNone;
    }

//-----------------------------------------------------------------------------
// Ctestsdkscreenmode::TestSModesSetAppUiScreenModeL
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
TInt CTestSDKScreenMode::TestSModesSetAppUiScreenModeL(CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KSMTestModule, "SSTestModule" );
    _LIT( KSMModeNumber, "In SPIDNewL" );
    TestModuleIf().Printf( 0, KSMTestModule, KSMModeNumber );
    // Print to log file
    iLog->Log( KSMModeNumber );
    
    TAknScreenModes screenModes = TAknScreenModes::GetModes(); 
    TAknScreenMode screenMode = screenModes.operator []( 0 );
    
    TInt err = KErrNone;
    CAknAppUiBase* appUiBase = new ( ELeave ) CAknAppUiBase();
    TRAP( err, TAknScreenModes::SetAppUiScreenModeL( appUiBase, screenMode ) );
    
    return err;
    }
//  [End of File]
