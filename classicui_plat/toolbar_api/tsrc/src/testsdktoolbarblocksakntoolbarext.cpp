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
* Description:  test akntoolbarextension.h
*
*/


// [INCLUDE FILES]
#include <akntoolbarextension.h>

#include <testsdktoolbar.rsg>
#include "testsdktoolbar.h"
#include "testsdktoolbar.hrh"
#include "testsdktoolbarcontrol.h"


// CONSTANTS
_LIT( KButtonText, "Button" );
_LIT( KButtonHelpText, "Help");

// ============================= MEMBER FUNCTIONS ==============================

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarExtNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarExtNewL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbarextension" );
    _LIT( KTestToolbarExtNewL, "in NewL" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarExtNewL );
    // Print to log file
    iLog->Log( KTestToolbarExtNewL );

    CAknToolbarExtension* toolbarExt = CAknToolbarExtension::NewL( R_TOOLBAR_EXTENSION );
    CleanupStack::PushL( toolbarExt );
    STIF_ASSERT_NOT_NULL( toolbarExt );

    CleanupStack::PopAndDestroy( toolbarExt );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarExtNewLCL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarExtNewLCL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbarextension" );
    _LIT( KTestToolbarExtNewLC, "in NewLC" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarExtNewLC );
    // Print to log file
    iLog->Log( KTestToolbarExtNewLC );

    CAknToolbarExtension* toolbarExt = CAknToolbarExtension::NewLC( R_TOOLBAR_EXTENSION );
    STIF_ASSERT_NOT_NULL( toolbarExt );

    CleanupStack::PopAndDestroy( toolbarExt );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarExtAddItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarExtAddItemL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbarextension" );
    _LIT( KTestToolbarExtAddItemL, "in AddItemL" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarExtAddItemL );
    // Print to log file
    iLog->Log( KTestToolbarExtAddItemL );

    CAknToolbarExtension* toolbarExt = CAknToolbarExtension::NewL( R_TOOLBAR_EXTENSION );
    CleanupStack::PushL( toolbarExt );

    CAknButton* button = CAknButton::NewLC( NULL, NULL, NULL,
                             NULL, KButtonText, KButtonHelpText, 
                             KAknButtonNoFrame, 0 );

    TInt index = 0;
    toolbarExt->AddItemL( 
            button, EAknCtButton, ETestToolBarCbaCmdBtn, 1, index );

    CleanupStack::Pop( button );
    CleanupStack::PopAndDestroy( toolbarExt );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarExtControlOrNullL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarExtControlOrNullL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbarextension" );
    _LIT( KTestToolbarExtControlOrNull, "in ControlOrNull" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarExtControlOrNull );
    // Print to log file
    iLog->Log( KTestToolbarExtControlOrNull );

    CAknToolbarExtension* toolbarExt = CAknToolbarExtension::NewL( R_TOOLBAR_EXTENSION );
    CleanupStack::PushL( toolbarExt );

    CAknButton* button = CAknButton::NewLC( NULL, NULL, NULL,
                             NULL, KButtonText, KButtonHelpText, 
                             KAknButtonNoFrame, 0 );
    TInt index = 0;
    toolbarExt->AddItemL( 
            button, EAknCtButton, ETestToolBarCbaCmdBtn, 1, index );
    CleanupStack::Pop( button );

    CCoeControl* control = toolbarExt->ControlOrNull( ETestToolBarCbaCmdBtn );
    STIF_ASSERT_NOT_NULL( control );

    CleanupStack::PopAndDestroy( toolbarExt );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarExtRemoveItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarExtRemoveItemL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbarextension" );
    _LIT( KTestToolbarExtRemoveItemL, "in RemoveItemL" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarExtRemoveItemL );
    // Print to log file
    iLog->Log( KTestToolbarExtRemoveItemL );

    CAknToolbarExtension* toolbarExt = CAknToolbarExtension::NewL( R_TOOLBAR_EXTENSION );
    CleanupStack::PushL( toolbarExt );

    CAknButton* button = CAknButton::NewLC( NULL, NULL, NULL,
                             NULL, KButtonText, KButtonHelpText, 
                             KAknButtonNoFrame, 0 );
    TInt index = 0;
    toolbarExt->AddItemL( 
            button, EAknCtButton, ETestToolBarCbaCmdBtn, 1, index );
    CleanupStack::Pop( button );

    toolbarExt->RemoveItemL( ETestToolBarCbaCmdBtn );

    CleanupStack::PopAndDestroy( toolbarExt );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarExtSetShownL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarExtSetShownL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbarextension" );
    _LIT( KTestToolbarExtSetShown, "SetShown" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarExtSetShown );
    // Print to log file
    iLog->Log( KTestToolbarExtSetShown );

    CAknToolbar* toolbar = CAknToolbar::NewL( R_TOOLBAR );
    CleanupStack::PushL( toolbar );

    CAknToolbarExtension* toolbarExtension = 
        CAknToolbarExtension::NewL( R_TOOLBAR_EXTENSION );
    toolbar->AddItemL( toolbarExtension, EAknCtToolbarExtension, 0, 0 );

    toolbarExtension->SetShown( ETrue );

    CleanupStack::PopAndDestroy( toolbar );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarExtIsShownL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarExtIsShownL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbarextension" );
    _LIT( KTestToolbarExtIsShown, "in IsShown" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarExtIsShown );
    // Print to log file
    iLog->Log( KTestToolbarExtIsShown );

    CAknToolbarExtension* toolbarExt = CAknToolbarExtension::NewL( R_TOOLBAR_EXTENSION );
    CleanupStack::PushL( toolbarExt );

    TBool isShown = toolbarExt->IsShown();
    STIF_ASSERT_FALSE( isShown );

    CleanupStack::PopAndDestroy( toolbarExt );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarExtSetItemDimmedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarExtSetItemDimmedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbarextension" );
    _LIT( KTestToolbarExtSetItemDimmed, "in SetItemDimmed" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarExtSetItemDimmed );
    // Print to log file
    iLog->Log( KTestToolbarExtSetItemDimmed );

    CAknToolbarExtension* toolbarExt = CAknToolbarExtension::NewL( R_TOOLBAR_EXTENSION );
    CleanupStack::PushL( toolbarExt );

    CAknButton* button = CAknButton::NewLC( NULL, NULL, NULL,
                             NULL, KButtonText, KButtonHelpText, 
                             KAknButtonNoFrame, 0 );
    TInt index = 0;
    toolbarExt->AddItemL( 
            button, EAknCtButton, ETestToolBarCbaCmdBtn, 1, index );
    CleanupStack::Pop( button );

    toolbarExt->SetItemDimmed( ETestToolBarCbaCmdBtn, ETrue );

    CleanupStack::PopAndDestroy( toolbarExt );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKToolbar::TestToolbarExtHideItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKToolbar::TestToolbarExtHideItemL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKToolbar, "testsdktoolbarextension" );
    _LIT( KTestToolbarExtHideItemL, "in HideItemL" );
    TestModuleIf().Printf( 0, KTestSDKToolbar, KTestToolbarExtHideItemL );
    // Print to log file
    iLog->Log( KTestToolbarExtHideItemL );

    CAknToolbarExtension* toolbarExt = CAknToolbarExtension::NewL( R_TOOLBAR_EXTENSION );
    CleanupStack::PushL( toolbarExt );

    CAknButton* button = CAknButton::NewLC( NULL, NULL, NULL,
                             NULL, KButtonText, KButtonHelpText, 
                             KAknButtonNoFrame, 0 );
    TInt index = 0;
    toolbarExt->AddItemL( 
            button, EAknCtButton, ETestToolBarCbaCmdBtn, 1, index );
    CleanupStack::Pop( button );

    toolbarExt->HideItemL( ETestToolBarCbaCmdBtn, ETrue );

    CleanupStack::PopAndDestroy( toolbarExt );
    return KErrNone;

    }

