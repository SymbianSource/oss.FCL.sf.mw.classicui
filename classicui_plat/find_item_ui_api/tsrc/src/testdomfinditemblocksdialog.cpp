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
* Description:  test finditemdialog.h and finditemmenu.h
*
*/

#include <finditemdialog.h>
#include <coemain.h>
#include <coeaui.h>
#include <eikmenup.h>
#include <testdomfinditem.rsg>

#include "testdomfinditem.h"
#include "testdomfinditemcontainer.h"

// CONSTANTS
_LIT( KUrlDes, "http://www.symbian.com" );

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestdomfinditem::TestDialogNewL
// -----------------------------------------------------------------------------
//
TInt Ctestdomfinditem::TestDialogNewL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomfinditem, "testdomfinditem" );
    _LIT( KTestDialogNewL, "In DialogNewL" );
    TestModuleIf().Printf( 0, Ktestdomfinditem, KTestDialogNewL );
    // Print to log file
    iLog->Log( KTestDialogNewL );

    CFindItemDialog* dialog = CFindItemDialog::NewL( KUrlDes,
            CFindItemEngine::EFindItemSearchURLBin );
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );

    CleanupStack::PopAndDestroy( dialog );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// Ctestdomfinditem::TestDialogExecuteLDL
// -----------------------------------------------------------------------------
//
TInt Ctestdomfinditem::TestDialogExecuteLDL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomfinditem, "testdomfinditem" );
    _LIT( KTestDialogExecuteLD, "In DialogExecuteLD" );
    TestModuleIf().Printf( 0, Ktestdomfinditem, KTestDialogExecuteLD );
    // Print to log file
    iLog->Log( KTestDialogExecuteLD );

    CFindItemDialog* dialog = CFindItemDialog::NewL( KUrlDes,
            CFindItemEngine::EFindItemSearchURLBin );

    TInt err = dialog->ExecuteLD();

    return err;

    }

// -----------------------------------------------------------------------------
// Ctestdomfinditem::TestDialogProcessCommandL
// -----------------------------------------------------------------------------
//
TInt Ctestdomfinditem::TestDialogProcessCommandL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomfinditem, "testdomfinditem" );
    _LIT( KTestDialogProcessCommandL, "In DialogProcessCommandL" );
    TestModuleIf().Printf( 0, Ktestdomfinditem, KTestDialogProcessCommandL );
    // Print to log file
    iLog->Log( KTestDialogProcessCommandL );

    CFindItemDialog* dialog = CFindItemDialog::NewL( KUrlDes,
            CFindItemEngine::EFindItemSearchURLBin );
    CleanupStack::PushL( dialog );

    CCoeEnv::Static()->AppUi()->AddToStackL( dialog );
    dialog->ProcessCommandL( EAknSoftkeyHide );
    CCoeEnv::Static()->AppUi()->RemoveFromStack( dialog );

    CleanupStack::PopAndDestroy( dialog );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// Ctestdomfinditem::TestDialogOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt Ctestdomfinditem::TestDialogOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomfinditem, "testdomfinditem" );
    _LIT( KTestDialogOfferKeyEventL, "In DialogOfferKeyEventL" );
    TestModuleIf().Printf( 0, Ktestdomfinditem, KTestDialogOfferKeyEventL );
    // Print to log file
    iLog->Log( KTestDialogOfferKeyEventL );

    CFindItemDialog* dialog = CFindItemDialog::NewL( KUrlDes,
            CFindItemEngine::EFindItemSearchURLBin );
    CleanupStack::PushL( dialog );

    TKeyEvent keyEvent;
    keyEvent.iScanCode = EStdKeyEnter;
    TKeyResponse keyResponse = dialog->OfferKeyEventL( keyEvent, EEventKey );
    STIF_ASSERT_EQUALS( EKeyWasNotConsumed, keyResponse );

    CleanupStack::PopAndDestroy( dialog );
    return KErrNone;

    }

