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
#include <akntouchpane.h>
#include <akndef.h>
#include <testsdktouchpane.rsg>
#include <w32std.h>
#include <coemain.h>
#include <coeaui.h> 

#include "testsdktouchpane.h"
#include "testsdktptouchpaneobserver.h"
#include "testsdktptouchpanefeppen.h"
#include "testsdktpcontainer.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestsdktouchpane::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestSDKTouchPane::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctestsdktouchpane::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKTouchPane::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestTPNewL", CTestSDKTouchPane::TestTPNewL ),
        ENTRY( "TestTPNewLWithResourceL", CTestSDKTouchPane::TestTPNewLWithResourceL ),
        ENTRY( "TestTPReduceRectL", CTestSDKTouchPane::TestTPReduceRectL ),
        ENTRY( "TestTPSetObserverL", CTestSDKTouchPane::TestTPSetObserverL ),
        ENTRY( "TestTPSetVisibilityModeL", CTestSDKTouchPane::TestTPSetVisibilityModeL ),
        ENTRY( "TestTPAllowInputMethodActivationL", CTestSDKTouchPane::TestTPAllowInputMethodActivationL ),
        ENTRY( "TestTPSetInputMethodIconActivatedL", CTestSDKTouchPane::TestTPSetInputMethodIconActivatedL ),
        ENTRY( "TestTPRefreshL", CTestSDKTouchPane::TestTPRefreshL ),
        ENTRY( "TestTPSetFepPenSupportInterfaceL", CTestSDKTouchPane::TestTPSetFepPenSupportInterfaceL ),
        ENTRY( "TestTPCountComponentControlsL", CTestSDKTouchPane::TestTPCountComponentControlsL ),
        ENTRY( "TestTPComponentControlL", CTestSDKTouchPane::TestTPComponentControlL ),
        ENTRY( "TestTPDrawL", CTestSDKTouchPane::TestTPDrawL ),
        ENTRY( "TestTPHandleControlEventL", CTestSDKTouchPane::TestTPHandleControlEventL ),
        ENTRY( "TestTPHandleResourceChangeL", CTestSDKTouchPane::TestTPHandleResourceChangeL ),
        ENTRY( "TestTPMakeVisibleL", CTestSDKTouchPane::TestTPMakeVisibleL ),
        ENTRY( "TestTPOfferKeyEventL", CTestSDKTouchPane::TestTPOfferKeyEventL ),
        ENTRY( "TestTPHandlePointerEventL", CTestSDKTouchPane::TestTPHandlePointerEventL ),
        ENTRY( "TestTPPositionChangedL", CTestSDKTouchPane::TestTPPositionChangedL ),
        ENTRY( "TestTPSizeChangedL", CTestSDKTouchPane::TestTPSizeChangedL ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestSDKTouchPane::TestTPNewL
// NewL test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKTouchPane::TestTPNewL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdktouchpane" );
    _LIT( KTestSFSetSkinEnabledL, "In TestTPNewL" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFSetSkinEnabledL );
    // Print to log file
    iLog->Log( KTestSFSetSkinEnabledL );

    CAknTouchPane* touchPane = CAknTouchPane::NewL();
    delete touchPane;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTouchPane::TestTPNewLWithResourceL
// NewL test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKTouchPane::TestTPNewLWithResourceL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdktouchpane" );
    _LIT( KTestSFSetSkinEnabledL, "In TestTPNewLWithResourceL" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFSetSkinEnabledL );
    // Print to log file
    iLog->Log( KTestSFSetSkinEnabledL );

    CAknTouchPane* touchPane = CAknTouchPane::NewL( R_TOUCHPANE );
    delete touchPane;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTouchPane::TestTPReduceRectL
// ReduceRect test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKTouchPane::TestTPReduceRectL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdktouchpane" );
    _LIT( KTestSFSetSkinEnabledL, "In TestTPReduceRectL" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFSetSkinEnabledL );
    // Print to log file
    iLog->Log( KTestSFSetSkinEnabledL );

    CAknTouchPane* touchPane = CAknTouchPane::NewL( R_TOUCHPANE );
    CleanupStack::PushL( touchPane );
    
    CCoeControl* container = new( ELeave ) CCoeControl();
    CleanupStack::PushL( container );
    TRect rect = container->Rect();
    touchPane->ReduceRect( rect );
    
    CleanupStack::Pop( container );
    CleanupStack::PopAndDestroy( touchPane );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTouchPane::TestTPSetObserverL
// SetObserver test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKTouchPane::TestTPSetObserverL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdktouchpane" );
    _LIT( KTestSFSetSkinEnabledL, "In TestTPSetObserverL" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFSetSkinEnabledL );
    // Print to log file
    iLog->Log( KTestSFSetSkinEnabledL );

    CAknTouchPane* touchPane = CAknTouchPane::NewL( R_TOUCHPANE );
    CleanupStack::PushL( touchPane );
    
    CTestSDKTPTouchPaneObserver* observer = new( ELeave ) CTestSDKTPTouchPaneObserver();
    CleanupStack::PushL( observer );
    touchPane->SetObserver( observer );
    CleanupStack::Pop( observer );
    
    CleanupStack::PopAndDestroy( touchPane );


    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTouchPane::TestTPSetVisibilityModeL
// SetVisibilityMode test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKTouchPane::TestTPSetVisibilityModeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdktouchpane" );
    _LIT( KTestSFSetSkinEnabledL, "In TestTPSetVisibilityModeL" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFSetSkinEnabledL );
    // Print to log file
    iLog->Log( KTestSFSetSkinEnabledL );

    CAknTouchPane* touchPane = CAknTouchPane::NewL( R_TOUCHPANE );
    CleanupStack::PushL( touchPane );
    
    touchPane->SetVisibilityMode( CAknTouchPane::EAutomaticVisibilityChanges );
    touchPane->SetVisibilityMode( CAknTouchPane::EManualVisibilityChanges );
    
    CleanupStack::PopAndDestroy( touchPane );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTouchPane::TestTPAllowInputMethodActivationL
// AllowInputMethodActivation test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKTouchPane::TestTPAllowInputMethodActivationL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdktouchpane" );
    _LIT( KTestSFSetSkinEnabledL, "In TestTPAllowInputMethodActivationL" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFSetSkinEnabledL );
    // Print to log file
    iLog->Log( KTestSFSetSkinEnabledL );

    CAknTouchPane* touchPane = CAknTouchPane::NewL( R_TOUCHPANE );
    CleanupStack::PushL( touchPane );
    
    touchPane->AllowInputMethodActivation( ETrue );
    
    CleanupStack::PopAndDestroy( touchPane );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTouchPane::TestTPSetInputMethodIconActivatedL
// SetInputMethodIconActivated test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKTouchPane::TestTPSetInputMethodIconActivatedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdktouchpane" );
    _LIT( KTestSFSetSkinEnabledL, "In TestTPSetInputMethodIconActivatedL" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFSetSkinEnabledL );
    // Print to log file
    iLog->Log( KTestSFSetSkinEnabledL );

    CAknTouchPane* touchPane = CAknTouchPane::NewL( R_TOUCHPANE );
    CleanupStack::PushL( touchPane );
    
    touchPane->SetInputMethodIconActivated( ETrue );
    
    CleanupStack::PopAndDestroy( touchPane );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTouchPane::TestTPRefreshL
// RefreshL test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKTouchPane::TestTPRefreshL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdktouchpane" );
    _LIT( KTestSFSetSkinEnabledL, "In TestTPRefreshL" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFSetSkinEnabledL );
    // Print to log file
    iLog->Log( KTestSFSetSkinEnabledL );

    CAknTouchPane* touchPane = CAknTouchPane::NewL( R_TOUCHPANE );
    CleanupStack::PushL( touchPane );
    
    touchPane->RefreshL();
    
    CleanupStack::PopAndDestroy( touchPane );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTouchPane::TestTPSetFepPenSupportInterfaceL
// SetFepPenSupportInterface test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKTouchPane::TestTPSetFepPenSupportInterfaceL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdktouchpane" );
    _LIT( KTestSFSetSkinEnabledL, "In TestTPSetFepPenSupportInterfaceL" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFSetSkinEnabledL );
    // Print to log file
    iLog->Log( KTestSFSetSkinEnabledL );

    CAknTouchPane* touchPane = CAknTouchPane::NewL( R_TOUCHPANE );
    CleanupStack::PushL( touchPane );
    
    CTestSDKTPTouchPaneFepPen* interface = new( ELeave ) CTestSDKTPTouchPaneFepPen();
    CleanupStack::PushL( interface );
    touchPane->SetFepPenSupportInterface( interface );
    CleanupStack::Pop( interface );
    CleanupStack::PopAndDestroy( touchPane );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTouchPane::TestTPCountComponentControlsL
// CountComponentControls test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKTouchPane::TestTPCountComponentControlsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdktouchpane" );
    _LIT( KTestSFSetSkinEnabledL, "In TestTPCountComponentControlsL" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFSetSkinEnabledL );
    // Print to log file
    iLog->Log( KTestSFSetSkinEnabledL );

    CAknTouchPane* touchPane = CAknTouchPane::NewL( R_TOUCHPANE );
    CleanupStack::PushL( touchPane );

    const TInt unexpected = 0;
    TInt count = touchPane->CountComponentControls();
    STIF_ASSERT_NOT_EQUALS( unexpected, count );
    
    CleanupStack::PopAndDestroy( touchPane );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTouchPane::TestTPComponentControlL
// ComponentControl test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKTouchPane::TestTPComponentControlL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdktouchpane" );
    _LIT( KTestSFSetSkinEnabledL, "In TestTPComponentControlL" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFSetSkinEnabledL );
    // Print to log file
    iLog->Log( KTestSFSetSkinEnabledL );

    CAknTouchPane* touchPane = CAknTouchPane::NewL( R_TOUCHPANE );
    CleanupStack::PushL( touchPane );

    CCoeControl* componentControl = touchPane->ComponentControl( 0 );
    STIF_ASSERT_NOT_NULL( componentControl );
    
    CleanupStack::PopAndDestroy( touchPane );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTouchPane::TestTPDrawL
// Draw test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKTouchPane::TestTPDrawL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdktouchpane" );
    _LIT( KTestSFSetSkinEnabledL, "In TestTPDrawL" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFSetSkinEnabledL );
    // Print to log file
    iLog->Log( KTestSFSetSkinEnabledL );

    CAknTouchPane* touchPane = CAknTouchPane::NewL( R_TOUCHPANE );
    CleanupStack::PushL( touchPane );

    CCoeControl* container = new( ELeave ) CCoeControl();
    CleanupStack::PushL( container );
    
    TRect rect = iContainer->Rect();
    
    iContainer->ActivateGc();
    touchPane->Draw( iContainer->SystemGc(), *iContainer, rect );
    iContainer->DeactivateGc();
    
    CleanupStack::Pop( container );
    CleanupStack::PopAndDestroy( touchPane );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTouchPane::TestTPHandleControlEventL
// HandleControlEventL test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKTouchPane::TestTPHandleControlEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdktouchpane" );
    _LIT( KTestSFSetSkinEnabledL, "In TestTPHandleControlEventL" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFSetSkinEnabledL );
    // Print to log file
    iLog->Log( KTestSFSetSkinEnabledL );

    CAknTouchPane* touchPane = CAknTouchPane::NewL( R_TOUCHPANE );
    CleanupStack::PushL( touchPane );

    CCoeControl* container = new( ELeave ) CCoeControl();
    CleanupStack::PushL( container );
    
    touchPane->HandleControlEventL( container, CAknTouchPane::EEventRequestExit );
    
    CleanupStack::Pop( container );
    CleanupStack::PopAndDestroy( touchPane );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTouchPane::TestTPHandleResourceChangeL
// HandleResourceChange test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKTouchPane::TestTPHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdktouchpane" );
    _LIT( KTestSFSetSkinEnabledL, "In TestTPHandleResourceChangeL" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFSetSkinEnabledL );
    // Print to log file
    iLog->Log( KTestSFSetSkinEnabledL );

    CAknTouchPane* touchPane = CAknTouchPane::NewL( R_TOUCHPANE );
    CleanupStack::PushL( touchPane );

    touchPane->HandleResourceChange( KEikDynamicLayoutVariantSwitch );
    
    CleanupStack::PopAndDestroy( touchPane );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTouchPane::TestTPMakeVisibleL
// MakeVisible test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKTouchPane::TestTPMakeVisibleL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdktouchpane" );
    _LIT( KTestSFSetSkinEnabledL, "In TestTPMakeVisibleL" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFSetSkinEnabledL );
    // Print to log file
    iLog->Log( KTestSFSetSkinEnabledL );

    CAknTouchPane* touchPane = CAknTouchPane::NewL( R_TOUCHPANE );
    CleanupStack::PushL( touchPane );

    touchPane->MakeVisible( ETrue );
    
    CleanupStack::PopAndDestroy( touchPane );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTouchPane::TestTPOfferKeyEventL
// OfferKeyEventL test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKTouchPane::TestTPOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdktouchpane" );
    _LIT( KTestSFSetSkinEnabledL, "In TestTPOfferKeyEventL" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFSetSkinEnabledL );
    // Print to log file
    iLog->Log( KTestSFSetSkinEnabledL );

    CAknTouchPane* touchPane = CAknTouchPane::NewL( R_TOUCHPANE );
    CleanupStack::PushL( touchPane );

    TKeyEvent keyEvent = { EKeyPause, EStdKeySpace, 0, 0  };
    TKeyResponse response = touchPane->OfferKeyEventL( keyEvent, EEventNull );
    
    CleanupStack::PopAndDestroy( touchPane );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTouchPane::TestTPHandlePointerEventL
// HandlePointerEventL test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKTouchPane::TestTPHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdktouchpane" );
    _LIT( KTestSFSetSkinEnabledL, "In TestTPHandlePointerEventL" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFSetSkinEnabledL );
    // Print to log file
    iLog->Log( KTestSFSetSkinEnabledL );

    CAknTouchPane* touchPane = CAknTouchPane::NewL( R_TOUCHPANE );
    CleanupStack::PushL( touchPane );
    CCoeEnv::Static()->AppUi()->AddToStackL( touchPane );

    TPoint point( ( touchPane->Rect().iBr.iX + touchPane->Rect().iTl.iX ) / 2,
        ( touchPane->Rect().iBr.iY + touchPane->Rect().iTl.iY ) / 2 );
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iPosition = point;
    iContainer->TransferEventL( event );
    CCoeEnv::Static()->AppUi()->RemoveFromStack( touchPane );
    CleanupStack::PopAndDestroy( touchPane );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTouchPane::TestTPPositionChangedL
// PositionChanged test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKTouchPane::TestTPPositionChangedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdktouchpane" );
    _LIT( KTestTPPositionChangedL, "In TestTPPositionChangedL" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestTPPositionChangedL );
    // Print to log file
    iLog->Log( KTestTPPositionChangedL );

    CAknTouchPane* touchPane = CAknTouchPane::NewL( R_TOUCHPANE );
    CleanupStack::PushL( touchPane );

    TPoint point( 1, 1 );
    touchPane->SetPosition( point );

    CleanupStack::PopAndDestroy( touchPane );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKTouchPane::TestTPSizeChangedL
// SizeChanged test method function.
// -----------------------------------------------------------------------------
//
TInt CTestSDKTouchPane::TestTPSizeChangedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestsdksearchfield, "testsdktouchpane" );
    _LIT( KTestSFSetSkinEnabledL, "In TestTPSizeChangedL" );
    TestModuleIf().Printf( 0, Ktestsdksearchfield, KTestSFSetSkinEnabledL );
    // Print to log file
    iLog->Log( KTestSFSetSkinEnabledL );

    CAknTouchPane* touchPane = CAknTouchPane::NewL( R_TOUCHPANE );
    CleanupStack::PushL( touchPane );

    TSize size( 20, 20 );
    touchPane->SetSize( size );

    CleanupStack::PopAndDestroy( touchPane );

    return KErrNone;
    }

//  [End of File]
