/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test AknToolbar.h
*
*/


// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <akntoolbar.h>
#include <akndef.h>
#include <aknbutton.h>
#include <akntoolbarextension.h>

#include <testsdktoolbar.rsg>
#include "testsdktoolbar.h"
#include "testsdktoolbarcontrol.h"
#include "testsdktoolbar.hrh"


// CONSTANTS
const TInt KEventPointX = 5;
const TInt KEventPointY = 5;
const TInt KToolbarWidth = 20;
const TInt KToolbarHeight = 10;

_LIT( KButtonText, "Button" );
_LIT( KButtonHelpText, "Help");

// ============================= MEMBER FUNCTIONS ==============================

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarNewL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarNewL, "in NewL" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarNewL );
    // Print to log file
    iLog->Log( KTestToolbarNewL );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );
    STIF_ASSERT_NOT_NULL( toolbar );

    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarNewLCL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarNewLCL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarNewLC, "in NewLC" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarNewLC );
    // Print to log file
    iLog->Log( KTestToolbarNewLC );

    CAknToolbar* toolbar = CAknToolbar::NewLC( R_TOOLBAR );
    
    STIF_ASSERT_NOT_NULL( toolbar );

    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarCountComponentControlsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarCountComponentControlsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarCountComponentControls, "in CountComponentControls" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarCountComponentControls );
    // Print to log file
    iLog->Log( KTestToolbarCountComponentControls );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    TInt num = toolbar->CountComponentControls();
    STIF_ASSERT_EQUALS( 0, num );
    
    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarComponentControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarComponentControlL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarComponentControl, "in ComponentControl" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarComponentControl );
    // Print to log file
    iLog->Log( KTestToolbarComponentControl );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    TInt index = 0;
    CCoeControl* control = toolbar->ComponentControl( index );
    STIF_ASSERT_NULL( control );
    
    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarHandlePointerEventL, "in HandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarHandlePointerEventL );
    // Print to log file
    iLog->Log( KTestToolbarHandlePointerEventL );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( KEventPointX, KEventPointY );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    
    toolbar->HandlePointerEventL( event );
    CleanupStack::PopAndDestroy( toolbar );
    
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarHandleResourceChange, "in HandleResourceChange" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarHandleResourceChange );
    // Print to log file
    iLog->Log( KTestToolbarHandleResourceChange );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    TInt type = KEikDynamicLayoutVariantSwitch;
    toolbar->HandleResourceChange( type );
    
    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarHandleControlEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarHandleControlEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarHandleControlEventL, "in HandleControlEventL" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarHandleControlEventL );
    // Print to log file
    iLog->Log( KTestToolbarHandleControlEventL );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    CTestToolbarControl* control = CTestToolbarControl::NewL();
    CleanupStack::PushL( control );
    MCoeControlObserver::TCoeEvent eventType = MCoeControlObserver::EEventStateChanged;
    toolbar->HandleControlEventL( control, eventType );
    
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarPositionChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarPositionChangedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarPositionChanged, "in PositionChanged" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarPositionChanged );
    // Print to log file
    iLog->Log( KTestToolbarPositionChanged );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    toolbar->PositionChanged();
    
    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarProcessCommandL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarProcessCommandL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarProcessCommandL, "in ProcessCommandL" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarProcessCommandL );
    // Print to log file
    iLog->Log( KTestToolbarProcessCommandL );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    CAknButton *button = CAknButton::NewLC( NULL, NULL, NULL,
                             NULL, KButtonText, KButtonHelpText, 
                             KAknButtonNoFrame, 0 );
    toolbar->AddItemL( 
            button, EAknCtButton, ETestToolBarCbaCmdBtn, 1 );
    CleanupStack::Pop( button );
    
    toolbar->SetFocusing( ETrue );
    toolbar->SetFocusedItemL( ETestToolBarCbaCmdBtn );
    
    TInt commandId = EAknSoftkeySelect;
    toolbar->ProcessCommandL( commandId );
    
    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarSetDimmedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarSetDimmedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarSetDimmed, "in SetDimmed" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarSetDimmed );
    // Print to log file
    iLog->Log( KTestToolbarSetDimmed );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    toolbar->SetDimmed( ETrue );
    
    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarOfferKeyEventL, "in OfferKeyEventL" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarOfferKeyEventL );
    // Print to log file
    iLog->Log( KTestToolbarOfferKeyEventL );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    TKeyEvent keyEvent;
    keyEvent.iScanCode = EStdKeyEnter;
    TKeyResponse keyResponse = toolbar->OfferKeyEventL( keyEvent, EEventKey );
    STIF_ASSERT_TRUE( ( keyResponse == EKeyWasNotConsumed )
            || ( keyResponse == EKeyWasConsumed ) );

    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarInputCapabilitiesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarInputCapabilitiesL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarInputCapabilities, "in InputCapabilities" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarInputCapabilities );
    // Print to log file
    iLog->Log( KTestToolbarInputCapabilities );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    TCoeInputCapabilities inputCapabilities = toolbar->InputCapabilities();
    STIF_ASSERT_TRUE( inputCapabilities == TCoeInputCapabilities::EAllText );

    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarDrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarDrawL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarDraw, "in Draw" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarDraw );
    // Print to log file
    iLog->Log( KTestToolbarDraw );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    CTestToolbarControl* control = CTestToolbarControl::NewL();
    CleanupStack::PushL( control );
    TRect rect( 0, 0, KToolbarWidth, KToolbarHeight );
    control->DoActivateGc();
    CWindowGc& gc = control->SystemGc();
    toolbar->Draw( gc, *control, rect );

    control->DoDeactivateGc();
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarControlOrNullL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarControlOrNullL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarControlOrNull, "in ControlOrNull" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarControlOrNull );
    // Print to log file
    iLog->Log( KTestToolbarControlOrNull );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    CCoeControl* control = toolbar->ControlOrNull( EtCmdToolbarTextEditor );
    STIF_ASSERT_NULL( control );

    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarSetToolbarVisibilityL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarSetToolbarVisibilityL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarSetToolbarVisibility, "in SetToolbarVisibility" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarSetToolbarVisibility );
    // Print to log file
    iLog->Log( KTestToolbarSetToolbarVisibility );

    TInt num = 0;
    TInt err = aItem.GetNextInt( num );
    if ( err != KErrNone )
        {
        return err;
        }

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    switch( num )
        {
        case 1:
            toolbar->SetToolbarVisibility( ETrue );
            break;
            
        case 2:
            toolbar->SetToolbarVisibility( ETrue, ETrue );
            break;
            
        default:
            CleanupStack::PopAndDestroy( toolbar );
            return KErrNotSupported;
        }

    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarSetItemDimmedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarSetItemDimmedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarSetItemDimmed, "in SetItemDimmed" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarSetItemDimmed );
    // Print to log file
    iLog->Log( KTestToolbarSetItemDimmed );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    toolbar->SetItemDimmed( EtCmdToolbarTextEditor, ETrue, ETrue );

    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarHideItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarHideItemL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarHideItem, "in HideItem" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarHideItem );
    // Print to log file
    iLog->Log( KTestToolbarHideItem );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    toolbar->HideItem( EtCmdToolbarTextEditor, ETrue, ETrue );

    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarSetToolbarObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarSetToolbarObserverL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarSetToolbarObserver, "in SetToolbarObserver" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarSetToolbarObserver );
    // Print to log file
    iLog->Log( KTestToolbarSetToolbarObserver );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );
    CTestToolbarControl* control = new ( ELeave ) CTestToolbarControl;
    CleanupStack::PushL( control );

    toolbar->SetToolbarObserver( control );

    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarToolbarObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarToolbarObserverL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarToolbarObserver, "in ToolbarObserver" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarToolbarObserver );
    // Print to log file
    iLog->Log( KTestToolbarToolbarObserver );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );
    CTestToolbarControl* control = new ( ELeave ) CTestToolbarControl;
    CleanupStack::PushL( control );

    toolbar->SetToolbarObserver( control );
    
    MAknToolbarObserver* observer = toolbar->ToolbarObserver();
    STIF_ASSERT_NOT_NULL( observer );

    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarAddItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarAddItemL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarAddItemL, "in AddItemL" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarAddItemL );
    // Print to log file
    iLog->Log( KTestToolbarAddItemL );

    TInt num = 0;
    TInt err = aItem.GetNextInt( num );
    if ( err != KErrNone )
        {
        return err;
        }

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    CAknButton *button = CAknButton::NewLC( NULL, NULL, NULL,
                             NULL, KButtonText, KButtonHelpText, 
                             KAknButtonNoFrame, 0 );

    switch( num )
        {
        case 1:
            toolbar->AddItemL( 
                    button, EAknCtButton, ETestToolBarCbaCmdBtn, 1 );
            break;

        case 2:
            {
            TInt index = 0;
            toolbar->AddItemL( 
                    button, EAknCtButton, ETestToolBarCbaCmdBtn, 1, index );
            }
            break;

        default:
            CleanupStack::Pop( button );
            CleanupStack::PopAndDestroy( toolbar );
            return KErrNotSupported;
        }

    CleanupStack::Pop( button );
    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarRemoveItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarRemoveItemL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarRemoveItem, "in RemoveItem" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarRemoveItem );
    // Print to log file
    iLog->Log( KTestToolbarRemoveItem );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    toolbar->RemoveItem( EtCmdToolbarTextEditor );

    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarIsSupportedItemTypeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarIsSupportedItemTypeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarIsSupportedItemType, "in IsSupportedItemType" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarIsSupportedItemType );
    // Print to log file
    iLog->Log( KTestToolbarIsSupportedItemType );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    TInt type = EAknCtButton;
    TBool isSupported = toolbar->IsSupportedItemType( type );
    STIF_ASSERT_TRUE( isSupported );

    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarSetInitialFocusedItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarSetInitialFocusedItemL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarSetInitialFocusedItem, "in SetInitialFocusedItem" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarSetInitialFocusedItem );
    // Print to log file
    iLog->Log( KTestToolbarSetInitialFocusedItem );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    toolbar->SetInitialFocusedItem( EtCmdToolbarTextEditor );

    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarSetEmphasisL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarSetEmphasisL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarSetEmphasis, "in SetEmphasis" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarSetEmphasis );
    // Print to log file
    iLog->Log( KTestToolbarSetEmphasis );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    toolbar->SetEmphasis( ETrue );

    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarIsShownL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarIsShownL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarIsShown, "in IsShown" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarIsShown );
    // Print to log file
    iLog->Log( KTestToolbarIsShown );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    toolbar->SetToolbarVisibility( EFalse );
    TBool isShown = toolbar->IsShown();
    STIF_ASSERT_FALSE( isShown );

    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarSetWithSlidingL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarSetWithSlidingL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarSetWithSliding, "in SetWithSliding" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarSetWithSliding );
    // Print to log file
    iLog->Log( KTestToolbarSetWithSliding );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    toolbar->SetWithSliding( ETrue );

    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarSetCloseOnCommandL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarSetCloseOnCommandL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarSetCloseOnCommand, "in SetCloseOnCommand" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarSetCloseOnCommand );
    // Print to log file
    iLog->Log( KTestToolbarSetCloseOnCommand );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    toolbar->SetCloseOnCommand( EtCmdToolbarTextEditor,ETrue );

    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarSetCloseOnAllCommandsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarSetCloseOnAllCommandsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarSetCloseOnAllCommands, "in SetCloseOnAllCommands" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarSetCloseOnAllCommands );
    // Print to log file
    iLog->Log( KTestToolbarSetCloseOnAllCommands );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    toolbar->SetCloseOnAllCommands( ETrue );

    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarSetOrientationL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarSetOrientationL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarSetOrientation, "in SetOrientation" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarSetOrientation );
    // Print to log file
    iLog->Log( KTestToolbarSetOrientation );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    TAknOrientation orientation = EAknOrientationVertical;
    toolbar->SetOrientation( orientation );

    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarUpdateBackgroundL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarUpdateBackgroundL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarUpdateBackground, "in UpdateBackground" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarUpdateBackground );
    // Print to log file
    iLog->Log( KTestToolbarUpdateBackground );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    toolbar->UpdateBackground();

    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarDisableToolbarL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarDisableToolbarL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarDisableToolbarL, "in DisableToolbarL" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarDisableToolbarL );
    // Print to log file
    iLog->Log( KTestToolbarDisableToolbarL );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    toolbar->DisableToolbarL( ETrue );

    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarIsToolbarDisabledL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarIsToolbarDisabledL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarIsToolbarDisabled, "in IsToolbarDisabled" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarIsToolbarDisabled );
    // Print to log file
    iLog->Log( KTestToolbarIsToolbarDisabled );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    toolbar->DisableToolbarL( ETrue );
    TBool disabled = toolbar->IsToolbarDisabled();
    STIF_ASSERT_TRUE( disabled );

    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarSetFocusedItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarSetFocusedItemL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarSetFocusedItemL, "in SetFocusedItemL" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarSetFocusedItemL );
    // Print to log file
    iLog->Log( KTestToolbarSetFocusedItemL );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    CAknButton *button = CAknButton::NewLC( NULL, NULL, NULL,
                             NULL, KButtonText, KButtonHelpText, 
                             KAknButtonNoFrame, 0 );
    toolbar->AddItemL( 
            button, EAknCtButton, ETestToolBarCbaCmdBtn, 1 );
    CleanupStack::Pop( button );
    
    toolbar->SetFocusing( ETrue );
    toolbar->SetFocusedItemL( ETestToolBarCbaCmdBtn );

    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarFocusedItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarFocusedItemL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarFocusedItem, "in FocusedItem" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarFocusedItem );
    // Print to log file
    iLog->Log( KTestToolbarFocusedItem );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    CAknButton *button = CAknButton::NewLC( NULL, NULL, NULL,
                             NULL, KButtonText, KButtonHelpText, 
                             KAknButtonNoFrame, 0 );
    toolbar->AddItemL( 
            button, EAknCtButton, ETestToolBarCbaCmdBtn, 1 );
    CleanupStack::Pop( button );

    toolbar->SetFocusing( ETrue );
    TInt commandId = ETestToolBarCbaCmdBtn;
    toolbar->SetFocusedItemL( commandId );
    
    TInt focusedItem = toolbar->FocusedItem();
    STIF_ASSERT_EQUALS( commandId, focusedItem );

    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarEventModifiersL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarEventModifiersL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarEventModifiers, "in EventModifiers" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarEventModifiers );
    // Print to log file
    iLog->Log( KTestToolbarEventModifiers );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    CTestToolbarControl* control = CTestToolbarControl::NewL();
    CleanupStack::PushL( control );
    MCoeControlObserver::TCoeEvent eventType = MCoeControlObserver::EEventStateChanged;
    toolbar->HandleControlEventL( control, eventType );
    CleanupStack::PopAndDestroy( control );

    TInt modifiers = toolbar->EventModifiers(); 
    STIF_ASSERT_TRUE( modifiers == 0 );

    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarToolbarFlagsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarToolbarFlagsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarToolbarFlags, "in ToolbarFlags" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarToolbarFlags );
    // Print to log file
    iLog->Log( KTestToolbarToolbarFlags );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    TInt flags = toolbar->ToolbarFlags();
    STIF_ASSERT_TRUE( flags >= 0 );

    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarSetSoftkeyResourceIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarSetSoftkeyResourceIdL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarSetSoftkeyResourceIdL, "in SetSoftkeyResourceIdL" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarSetSoftkeyResourceIdL );
    // Print to log file
    iLog->Log( KTestToolbarSetSoftkeyResourceIdL );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    toolbar->SetSoftkeyResourceIdL( R_AVKON_SOFTKEYS_CLOSE );

    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarToolbarExtensionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarToolbarExtensionL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarToolbarExtension, "in ToolbarExtension" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarToolbarExtension );
    // Print to log file
    iLog->Log( KTestToolbarToolbarExtension );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    CAknToolbarExtension* toolbarExt = toolbar->ToolbarExtension();
    STIF_ASSERT_NULL( toolbarExt );

    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarHideItemsAndDrawOnlyBackgroundL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarHideItemsAndDrawOnlyBackgroundL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarHideItemsAndDrawOnlyBackground, "in HideItemsAndDrawOnlyBackground" );
    TestModuleIf().Printf( 0, KTestSDKToolbar,
            KTestToolbarHideItemsAndDrawOnlyBackground );
    // Print to log file
    iLog->Log( KTestToolbarHideItemsAndDrawOnlyBackground );

    TInt num = 0;
    TInt err = aItem.GetNextInt( num );
    if ( err != KErrNone )
        {
        return err;
        }

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    CAknButton *button = CAknButton::NewLC( NULL, NULL, NULL,
                             NULL, KButtonText, KButtonHelpText, 
                             KAknButtonNoFrame, 0 );
    toolbar->AddItemL( 
            button, EAknCtButton, ETestToolBarCbaCmdBtn, 1 );
    CleanupStack::Pop( button );

    
    
    switch( num )
        {
        case 1:
            toolbar->HideItemsAndDrawOnlyBackground( ETrue );
            break;

        case 2:
            toolbar->HideItemsAndDrawOnlyBackground( ETrue, ECoeWinPriorityHigh );
            break;

        default:
            CleanupStack::PopAndDestroy( toolbar );
            return KErrNotSupported;
        }

    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarSizeChangedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarSizeChanged, "in SizeChanged" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarSizeChanged );
    // Print to log file
    iLog->Log( KTestToolbarSizeChanged );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    TSize size( KToolbarWidth, KToolbarHeight );
    toolbar->SetSize( size );

    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarFocusChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarFocusChangedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarFocusChanged, "in FocusChanged" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarFocusChanged );
    // Print to log file
    iLog->Log( KTestToolbarFocusChanged );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    toolbar->SetFocus( EFalse, EDrawNow );
    toolbar->SetFocus( ETrue, EDrawNow );

    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarExtensionInterfaceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarExtensionInterfaceL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarExtensionInterface, "in ExtensionInterface" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarExtensionInterface );
    // Print to log file
    iLog->Log( KTestToolbarExtensionInterface );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    CTestToolBar* toolBar = static_cast<CTestToolBar*>( toolbar );
    TUid uid = TUid::Null();
    STIF_ASSERT_NULL( toolBar->ExtensionInterface( uid ) );
    
    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarMopSupplyObjectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarMopSupplyObjectL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbar" );
    _LIT( KTestToolbarMopSupplyObject, "in MopSupplyObject" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarMopSupplyObject );
    // Print to log file
    iLog->Log( KTestToolbarMopSupplyObject );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    CTestToolBar* toolBar = static_cast<CTestToolBar*>( toolbar );
    TTypeUid::Ptr ptr = TTypeUid::Null();
    ptr = toolBar->MopSupplyObject( CEikCba::ETypeId );
    STIF_ASSERT_NULL( ptr.Pointer() );
    
    CleanupStack::PopAndDestroy( toolbar );
    return KErrNone;

    }

