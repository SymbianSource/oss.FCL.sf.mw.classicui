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
* Description:  global_popup_priority_controller_api
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknglobalpopupprioritycontroller.h>
#include <coecntrl.h>
#include <aknpopupfader.h> 

#include "testdomgppc.h"



// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMGPPC::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDOMGPPC::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestGPPCEnablePriorityControlL", CTestDOMGPPC::TestGPPCEnablePriorityControlL ),
        ENTRY( "TestGPPCAllowGlobalPopups", CTestDOMGPPC::TestGPPCAllowGlobalPopups ),
        ENTRY( "TestGPPCSetPopupPriorityL", CTestDOMGPPC::TestGPPCSetPopupPriorityL ),
        ENTRY( "TestGPPCRemovePopupPriority", CTestDOMGPPC::TestGPPCRemovePopupPriorityL ),
        ENTRY( "TestGPPCShowPopup", CTestDOMGPPC::TestGPPCShowPopupL ),
        ENTRY( "TestGPPCSetRootWinOrdinalPosition", CTestDOMGPPC::TestGPPCSetRootWinOrdinalPosition ),
        ENTRY( "TestGPPCAddSubPopupL", CTestDOMGPPC::TestGPPCAddSubPopupL ),
        ENTRY( "TestGPPCAddPopupToControlStackL", CTestDOMGPPC::TestGPPCAddPopupToControlStackL ),
        ENTRY( "TestGPPCRouseSleepingPopup", CTestDOMGPPC::TestGPPCRouseSleepingPopupL ),
        ENTRY( "TestGPPCFadeBehindPopup", CTestDOMGPPC::TestGPPCFadeBehindPopupL ),

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestDOMGPPC::TestGPPCEnablePriorityControlL
// -----------------------------------------------------------------------------
//
TInt CTestDOMGPPC::TestGPPCEnablePriorityControlL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomgppc, "testdomgppc" );
    _LIT( KTestGPPCEnablePriorityControlL, "In TestGPPCEnablePriorityControlL" );
    TestModuleIf().Printf( 0, Ktestdomgppc, KTestGPPCEnablePriorityControlL );
    // Print to log file
    iLog->Log( KTestGPPCEnablePriorityControlL );

    TInt err = KErrNone;
    TRAP( err, AknGlobalPopupPriorityController::EnablePriorityControlL() );
    return err;

    }
// -----------------------------------------------------------------------------
// CTestDOMGPPC::TestGPPCAllowGlobalPopups
// -----------------------------------------------------------------------------
//
TInt CTestDOMGPPC::TestGPPCAllowGlobalPopups( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomgppc, "testdomgppc" );
    _LIT( KTestGPPCAllowGlobalPopups, "In TestGPPCAllowGlobalPopups" );
    TestModuleIf().Printf( 0, Ktestdomgppc, KTestGPPCAllowGlobalPopups );
    // Print to log file
    iLog->Log( KTestGPPCAllowGlobalPopups );

    AknGlobalPopupPriorityController::AllowGlobalPopups( ETrue );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMGPPC::TestGPPCSetPopupPriorityL
// -----------------------------------------------------------------------------
//
TInt CTestDOMGPPC::TestGPPCSetPopupPriorityL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomgppc, "testdomgppc" );
    _LIT( KTestGPPCSetPopupPriorityL, "In TestGPPCSetPopupPriorityL" );
    TestModuleIf().Printf( 0, Ktestdomgppc, KTestGPPCSetPopupPriorityL );
    // Print to log file
    iLog->Log( KTestGPPCSetPopupPriorityL );
    TInt err = KErrNone;
    TInt priority = 0;
    CCoeControl* control = new ( ELeave ) CCoeControl();
    CleanupStack::PushL( control );
    TRAP( err, AknGlobalPopupPriorityController::SetPopupPriorityL( *control, priority ) );
    CleanupStack::PopAndDestroy( control );
    return err;
    }
// -----------------------------------------------------------------------------
// CTestDOMGPPC::TestGPPCRemovePopupPriorityL
// -----------------------------------------------------------------------------
//
TInt CTestDOMGPPC::TestGPPCRemovePopupPriorityL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomgppc, "testdomgppc" );
    _LIT( KTestGPPCRemovePopupPriorityL, "In TestGPPCRemovePopupPriorityL" );
    TestModuleIf().Printf( 0, Ktestdomgppc, KTestGPPCRemovePopupPriorityL );
    // Print to log file
    iLog->Log( KTestGPPCRemovePopupPriorityL );
    CCoeControl* control = new ( ELeave ) CCoeControl();
    CleanupStack::PushL( control );
    AknGlobalPopupPriorityController::RemovePopupPriority( *control );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMGPPC::TestGPPCShowPopupL
// -----------------------------------------------------------------------------
//
TInt CTestDOMGPPC::TestGPPCShowPopupL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomgppc, "testdomgppc" );
    _LIT( KTestGPPCShowPopupL, "In TestGPPCShowPopupL" );
    TestModuleIf().Printf( 0, Ktestdomgppc, KTestGPPCShowPopupL );
    // Print to log file
    iLog->Log( KTestGPPCShowPopupL );
    CCoeControl* control = new ( ELeave ) CCoeControl();
    CleanupStack::PushL( control );
    AknGlobalPopupPriorityController::ShowPopup( *control, ETrue );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMGPPC::TestGPPCSetRootWinOrdinalPosition
// -----------------------------------------------------------------------------
//
TInt CTestDOMGPPC::TestGPPCSetRootWinOrdinalPosition( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomgppc, "testdomgppc" );
    _LIT( KTestGPPCSetRootWinOrdinalPosition, "In TestGPPCSetRootWinOrdinalPosition" );
    TestModuleIf().Printf( 0, Ktestdomgppc, KTestGPPCSetRootWinOrdinalPosition );
    // Print to log file
    iLog->Log( KTestGPPCSetRootWinOrdinalPosition );
    RWindowGroup & rootWinGroup = CCoeEnv::Static()->RootWin() ;       
    TInt ordinalPosition = rootWinGroup.OrdinalPosition();
    AknGlobalPopupPriorityController::SetRootWinOrdinalPosition( ordinalPosition );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMGPPC::TestGPPCAddSubPopupL
// -----------------------------------------------------------------------------
//
TInt CTestDOMGPPC::TestGPPCAddSubPopupL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomgppc, "testdomgppc" );
    _LIT( KTestGPPCAddSubPopupL, "In TestGPPCAddSubPopupL" );
    TestModuleIf().Printf( 0, Ktestdomgppc, KTestGPPCAddSubPopupL );
    // Print to log file
    iLog->Log( KTestGPPCAddSubPopupL );
    TInt err = KErrNone;
   
    CCoeControl* control = new ( ELeave ) CCoeControl();
    CleanupStack::PushL( control );
    CCoeControl* subControl = new ( ELeave ) CCoeControl();
    CleanupStack::PushL( subControl );
    TRAP( err, AknGlobalPopupPriorityController::AddSubPopupL( *control, *subControl ) );
    CleanupStack::PopAndDestroy( subControl );
    CleanupStack::PopAndDestroy( control );
    return err;
    }
// -----------------------------------------------------------------------------
// CTestDOMGPPC::TestGPPCAddPopupToControlStackL
// -----------------------------------------------------------------------------
//
TInt CTestDOMGPPC::TestGPPCAddPopupToControlStackL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomgppc, "testdomgppc" );
    _LIT( KTestGPPCAddPopupToControlStackL, "In TestGPPCAddPopupToControlStackL" );
    TestModuleIf().Printf( 0, Ktestdomgppc, KTestGPPCAddPopupToControlStackL );
    // Print to log file
    iLog->Log( KTestGPPCAddPopupToControlStackL );
    TInt err = KErrNone;
   
    CCoeControl* control = new ( ELeave ) CCoeControl();
    CleanupStack::PushL( control );
    TRAP( err, AknGlobalPopupPriorityController::AddPopupToControlStackL( *control ) );
    CleanupStack::Pop( control );
    return err;
    }
// -----------------------------------------------------------------------------
// CTestDOMGPPC::TestGPPCRouseSleepingPopupL
// -----------------------------------------------------------------------------
//
TInt CTestDOMGPPC::TestGPPCRouseSleepingPopupL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomgppc, "testdomgppc" );
    _LIT( KTestGPPCRouseSleepingPopupL, "In TestGPPCRouseSleepingPopupL" );
    TestModuleIf().Printf( 0, Ktestdomgppc, KTestGPPCRouseSleepingPopupL );
    // Print to log file
    iLog->Log( KTestGPPCRouseSleepingPopupL );
    CCoeControl* control = new ( ELeave ) CCoeControl();
    CleanupStack::PushL( control );
    CCoeEnv::Static()->AppUi()->AddToStackL( control );
    AknGlobalPopupPriorityController::RouseSleepingPopup( *control, EFalse );
    CleanupStack::Pop( control );
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestDOMGPPC::TestGPPCFadeBehindPopupL
// -----------------------------------------------------------------------------
//
TInt CTestDOMGPPC::TestGPPCFadeBehindPopupL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomgppc, "testdomgppc" );
    _LIT( KTestGPPCFadeBehindPopupL, "In TestGPPCFadeBehindPopupL" );
    TestModuleIf().Printf( 0, Ktestdomgppc, KTestGPPCFadeBehindPopupL );
    // Print to log file
    iLog->Log( KTestGPPCFadeBehindPopupL );
    CCoeControl* control = new ( ELeave ) CCoeControl();
    CleanupStack::PushL( control );
    TAknPopupFader fader;
    MAknFadedComponent fadedComponent;
    AknGlobalPopupPriorityController::FadeBehindPopup( *control, fader, fadedComponent, ETrue );
    CleanupStack::PopAndDestroy( control );
    return KErrNone;
    }
//  [End of File]
