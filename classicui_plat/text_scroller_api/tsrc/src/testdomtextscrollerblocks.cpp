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
* Description:  text aknmarqueecontrol.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknmarqueecontrol.h>
#include <eikenv.h>
#include <aknlayoutscalable_avkon.cdl.h>

#include "testdomtextscroller.h"
#include "testdomtextscrollercontainer.h"

class TAknTextComponentLayout;
// CONSTANTS
const TInt KBaselineoffset = 8;
const TInt KRectBx = 99;
const TInt KRectBy = 99;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMTextScroller::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDOMTextScroller::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestNewL", CTestDOMTextScroller::TestNewL ),
        ENTRY( "TestNewLC", CTestDOMTextScroller::TestNewLCL ),
        ENTRY( "TestSetRedrawCallBack",
                CTestDOMTextScroller::TestSetRedrawCallBackL ),
        ENTRY( "TestDrawText", CTestDOMTextScroller::TestDrawTextL ),
        ENTRY( "TestUseLogicalToVisualConversion",
                CTestDOMTextScroller::TestUseLogicalToVisualConversionL ),
        ENTRY( "TestStart", CTestDOMTextScroller::TestStartL ),
        ENTRY( "TestStop", CTestDOMTextScroller::TestStopL ),
        ENTRY( "TestReset", CTestDOMTextScroller::TestResetL ),
        ENTRY( "TestIsMarqueeOn", CTestDOMTextScroller::TestIsMarqueeOnL ),
        ENTRY( "TestSetSpeedInPixels",
                CTestDOMTextScroller::TestSetSpeedInPixelsL ),
        ENTRY( "TestSetDelay", CTestDOMTextScroller::TestSetDelayL ),
        ENTRY( "TestSetInterval", CTestDOMTextScroller::TestSetIntervalL ),
        ENTRY( "TestSetLoops", CTestDOMTextScroller::TestSetLoopsL ),
        ENTRY( "TestEnableMarquee", CTestDOMTextScroller::TestEnableMarqueeL ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestDOMTextScroller::TestNewL
// -----------------------------------------------------------------------------
//
TInt CTestDOMTextScroller::TestNewL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMTextScroller, "testdomtextscroller" );
    _LIT( KTestNewL, "In NewL" );
    TestModuleIf().Printf( 0, KTestDOMTextScroller, KTestNewL );
    // Print to log file
    iLog->Log( KTestNewL );

    CAknMarqueeControl* marControl = CAknMarqueeControl::NewL();
    CleanupStack::PushL( marControl );
    STIF_ASSERT_NOT_NULL( marControl );

    CleanupStack::PopAndDestroy( marControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMTextScroller::TestNewLCL
// -----------------------------------------------------------------------------
//
TInt CTestDOMTextScroller::TestNewLCL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMTextScroller, "testdomtextscroller" );
    _LIT( KTestNewLC, "In NewLC" );
    TestModuleIf().Printf( 0, KTestDOMTextScroller, KTestNewLC );
    // Print to log file
    iLog->Log( KTestNewLC );

    CAknMarqueeControl* marControl = CAknMarqueeControl::NewLC();
    STIF_ASSERT_NOT_NULL( marControl );

    CleanupStack::PopAndDestroy( marControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMTextScroller::TestSetRedrawCallBackL
// -----------------------------------------------------------------------------
//
TInt CTestDOMTextScroller::TestSetRedrawCallBackL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMTextScroller, "testdomtextscroller" );
    _LIT( KTestSetRedrawCallBack, "In SetRedrawCallBack" );
    TestModuleIf().Printf( 0, KTestDOMTextScroller, KTestSetRedrawCallBack );
    // Print to log file
    iLog->Log( KTestSetRedrawCallBack );

    CAknMarqueeControl* marControl = CAknMarqueeControl::NewLC();

    TCallBack callBack;
    marControl->SetRedrawCallBack( callBack );

    CleanupStack::PopAndDestroy( marControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMTextScroller::TestDrawTextL
// -----------------------------------------------------------------------------
//
TInt CTestDOMTextScroller::TestDrawTextL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KTestDOMTextScroller, "testdomtextscroller" );
    _LIT( KTestDrawText, "In DrawText" );
    TestModuleIf().Printf( 0, KTestDOMTextScroller, KTestDrawText );
    // Print to log file
    iLog->Log( KTestDrawText );

    TInt num = 0;
    TInt err = aItem.GetNextInt( num );
    if ( err != KErrNone )
        {
        return err;
        }

    CAknMarqueeControl* marControl = CAknMarqueeControl::NewLC();
    _LIT( KText, "text" );
    const TBuf<32>  txt( KText );
    const CGraphicsContext::TTextAlign align( CGraphicsContext::ELeft );
    TRect rect( TRect( 1, 1, KRectBx,KRectBy ) );
    const CFont* font = CEikonEnv::Static()->NormalFont();
    TAknTextComponentLayout textlayout;

    CTestTextScrollerContainer* container = CTestTextScrollerContainer::NewL();
    CleanupStack::PushL( container );
    marControl->SetContainerWindowL( *container );
    container->DoActivateGc();
    CWindowGc& gc = marControl->SystemGc();

    TBool drawText;
    switch( num )
        {
        case 1:
            drawText = marControl->DrawText( gc, rect, txt, KBaselineoffset,
                    align, *font );
            STIF_ASSERT_FALSE( drawText );
            break;
        case 2:
            drawText = marControl->DrawText( gc, rect, textlayout, txt, font );
            STIF_ASSERT_FALSE( drawText );
            break;
        case 3:
            drawText = marControl->DrawText( gc, rect, textlayout, txt,
                    font, KRgbBlack );
            STIF_ASSERT_FALSE( drawText );
            break;
        default:
            return KErrNotSupported;
        }

    container->DoDeactivateGc();
    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( marControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMTextScroller::TestUseLogicalToVisualConversionL
// -----------------------------------------------------------------------------
//
TInt CTestDOMTextScroller::TestUseLogicalToVisualConversionL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMTextScroller, "testdomtextscroller" );
    _LIT( KTestUseLogicalToVisualConversion, "In UseLogicalToVisualConversion" );
    TestModuleIf().Printf( 0, KTestDOMTextScroller, KTestUseLogicalToVisualConversion );
    // Print to log file
    iLog->Log( KTestUseLogicalToVisualConversion );

    CAknMarqueeControl* marControl = CAknMarqueeControl::NewLC();

    marControl->UseLogicalToVisualConversion( EFalse );

    CleanupStack::PopAndDestroy( marControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMTextScroller::TestStartL
// -----------------------------------------------------------------------------
//
TInt CTestDOMTextScroller::TestStartL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMTextScroller, "testdomtextscroller" );
    _LIT( KTestStart, "In Start" );
    TestModuleIf().Printf( 0, KTestDOMTextScroller, KTestStart );
    // Print to log file
    iLog->Log( KTestStart );

    CAknMarqueeControl* marControl = CAknMarqueeControl::NewLC();

    marControl->Start();

    CleanupStack::PopAndDestroy( marControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMTextScroller::TestStopL
// -----------------------------------------------------------------------------
//
TInt CTestDOMTextScroller::TestStopL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMTextScroller, "testdomtextscroller" );
    _LIT( KTestStop, "In Stop" );
    TestModuleIf().Printf( 0, KTestDOMTextScroller, KTestStop );
    // Print to log file
    iLog->Log( KTestStop );

    CAknMarqueeControl* marControl = CAknMarqueeControl::NewLC();

    marControl->Stop();

    CleanupStack::PopAndDestroy( marControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMTextScroller::TestResetL
// -----------------------------------------------------------------------------
//
TInt CTestDOMTextScroller::TestResetL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMTextScroller, "testdomtextscroller" );
    _LIT( KTestReset, "In Reset" );
    TestModuleIf().Printf( 0, KTestDOMTextScroller, KTestReset );
    // Print to log file
    iLog->Log( KTestReset );

    CAknMarqueeControl* marControl = CAknMarqueeControl::NewLC();

    marControl->Reset();

    CleanupStack::PopAndDestroy( marControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMTextScroller::TestIsMarqueeOnL
// -----------------------------------------------------------------------------
//
TInt CTestDOMTextScroller::TestIsMarqueeOnL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMTextScroller, "testdomtextscroller" );
    _LIT( KTestIsMarqueeOn, "In IsMarqueeOn" );
    TestModuleIf().Printf( 0, KTestDOMTextScroller, KTestIsMarqueeOn );
    // Print to log file
    iLog->Log( KTestIsMarqueeOn );

    CAknMarqueeControl* marControl = CAknMarqueeControl::NewLC();

    TBool isMarqueeOn = marControl->IsMarqueeOn();
    STIF_ASSERT_FALSE( isMarqueeOn );

    CleanupStack::PopAndDestroy( marControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMTextScroller::TestSetSpeedInPixelsL
// -----------------------------------------------------------------------------
//
TInt CTestDOMTextScroller::TestSetSpeedInPixelsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMTextScroller, "testdomtextscroller" );
    _LIT( KTestSetSpeedInPixels, "In SetSpeedInPixels" );
    TestModuleIf().Printf( 0, KTestDOMTextScroller, KTestSetSpeedInPixels );
    // Print to log file
    iLog->Log( KTestSetSpeedInPixels );

    CAknMarqueeControl* marControl = CAknMarqueeControl::NewLC();

    marControl->SetSpeedInPixels( 1 );

    CleanupStack::PopAndDestroy( marControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMTextScroller::TestSetDelayL
// -----------------------------------------------------------------------------
//
TInt CTestDOMTextScroller::TestSetDelayL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMTextScroller, "testdomtextscroller" );
    _LIT( KTestSetDelay, "In SetDelay" );
    TestModuleIf().Printf( 0, KTestDOMTextScroller, KTestSetDelay );
    // Print to log file
    iLog->Log( KTestSetDelay );

    CAknMarqueeControl* marControl = CAknMarqueeControl::NewLC();

    marControl->SetDelay( 1 );

    CleanupStack::PopAndDestroy( marControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMTextScroller::TestSetIntervalL
// -----------------------------------------------------------------------------
//
TInt CTestDOMTextScroller::TestSetIntervalL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMTextScroller, "testdomtextscroller" );
    _LIT( KTestSetInterval, "In SetInterval" );
    TestModuleIf().Printf( 0, KTestDOMTextScroller, KTestSetInterval );
    // Print to log file
    iLog->Log( KTestSetInterval );

    CAknMarqueeControl* marControl = CAknMarqueeControl::NewLC();

    marControl->SetInterval( 1 );

    CleanupStack::PopAndDestroy( marControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMTextScroller::TestSetLoopsL
// -----------------------------------------------------------------------------
//
TInt CTestDOMTextScroller::TestSetLoopsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMTextScroller, "testdomtextscroller" );
    _LIT( KTestSetLoops, "In SetLoops" );
    TestModuleIf().Printf( 0, KTestDOMTextScroller, KTestSetLoops );
    // Print to log file
    iLog->Log( KTestSetLoops );

    CAknMarqueeControl* marControl = CAknMarqueeControl::NewLC();

    marControl->SetLoops( 1 );

    CleanupStack::PopAndDestroy( marControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMTextScroller::TestEnableMarqueeL
// -----------------------------------------------------------------------------
//
TInt CTestDOMTextScroller::TestEnableMarqueeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMTextScroller, "testdomtextscroller" );
    _LIT( KTestEnableMarquee, "In EnableMarquee" );
    TestModuleIf().Printf( 0, KTestDOMTextScroller, KTestEnableMarquee );
    // Print to log file
    iLog->Log( KTestEnableMarquee );

    CAknMarqueeControl* marControl = CAknMarqueeControl::NewLC();

    marControl->EnableMarquee( EFalse );

    CleanupStack::PopAndDestroy( marControl );
    return KErrNone;

    }


//  [End of File]
