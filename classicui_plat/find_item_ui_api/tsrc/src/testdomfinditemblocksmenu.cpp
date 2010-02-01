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



#include <finditemmenu.h>
#include <aknform.h>
#include <eikmenup.h>
#include <finditem.hrh>

#include <testdomfinditem.rsg>
#include "testdomfinditem.h"


// CONSTANTS
_LIT( KNumberDes, "callback");


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestdomfinditem::TestMenuNewL
// -----------------------------------------------------------------------------
//
TInt Ctestdomfinditem::TestMenuNewL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomfinditem, "testdomfinditem" );
    _LIT( KTestMenuNewL, "In MenuNewL" );
    TestModuleIf().Printf( 0, Ktestdomfinditem, KTestMenuNewL );
    // Print to log file
    iLog->Log( KTestMenuNewL );

    CFindItemMenu* menu = CFindItemMenu::NewL( R_FIND_ITEM_MENU );
    CleanupStack::PushL( menu );
    STIF_ASSERT_NOT_NULL( menu );

    CleanupStack::PopAndDestroy( menu );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// Ctestdomfinditem::TestMenuNewLCL
// -----------------------------------------------------------------------------
//
TInt Ctestdomfinditem::TestMenuNewLCL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomfinditem, "testdomfinditem" );
    _LIT( KTestMenuNewLC, "In MenuNewLC" );
    TestModuleIf().Printf( 0, Ktestdomfinditem, KTestMenuNewLC );
    // Print to log file
    iLog->Log( KTestMenuNewLC );

    CFindItemMenu* menu = CFindItemMenu::NewLC( R_FIND_ITEM_MENU );
    STIF_ASSERT_NOT_NULL( menu );

    CleanupStack::PopAndDestroy( menu );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// Ctestdomfinditem::TestMenuDisplayFindItemMenuItemL
// -----------------------------------------------------------------------------
//
TInt Ctestdomfinditem::TestMenuDisplayFindItemMenuItemL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomfinditem, "testdomfinditem" );
    _LIT( KTestMenuDisplayFindItemMenuItemL, "In MenuDisplayFindItemMenuItemL" );
    TestModuleIf().Printf( 0, Ktestdomfinditem, KTestMenuDisplayFindItemMenuItemL );
    // Print to log file
    iLog->Log( KTestMenuDisplayFindItemMenuItemL );

    CFindItemMenu* menu = CFindItemMenu::NewLC( R_FIND_ITEM_MENU );

    CAknForm* frm = new ( ELeave ) CAknForm;
    CleanupStack::PushL( frm );
    frm->ConstructL();

    CEikMenuPane* pane = new ( ELeave ) CEikMenuPane( frm );
    CleanupStack::PushL( pane );
    pane->ConstructL( pane, NULL );

    menu->DisplayFindItemMenuItemL( *pane, 0 );

    CleanupStack::PopAndDestroy( pane );
    CleanupStack::PopAndDestroy( frm );
    CleanupStack::PopAndDestroy( menu );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// Ctestdomfinditem::TestMenuDisplayFindItemCascadeMenuL
// -----------------------------------------------------------------------------
//
TInt Ctestdomfinditem::TestMenuDisplayFindItemCascadeMenuL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomfinditem, "testdomfinditem" );
    _LIT( KTestMenuDisplayFindItemCascadeMenuL, "In MenuDisplayFindItemCascadeMenuL" );
    TestModuleIf().Printf( 0, Ktestdomfinditem, KTestMenuDisplayFindItemCascadeMenuL );
    // Print to log file
    iLog->Log( KTestMenuDisplayFindItemCascadeMenuL );

    CFindItemMenu* menu = CFindItemMenu::NewLC( R_FIND_ITEM_MENU );

    CAknForm* frm = new ( ELeave ) CAknForm;
    CleanupStack::PushL( frm );
    frm->ConstructL();

    CEikMenuPane* pane = new ( ELeave ) CEikMenuPane( frm );
    CleanupStack::PushL( pane );
    pane->ConstructL( pane, NULL );

    menu->DisplayFindItemCascadeMenuL( *pane );

    CleanupStack::PopAndDestroy( pane );
    CleanupStack::PopAndDestroy( frm );
    CleanupStack::PopAndDestroy( menu );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// Ctestdomfinditem::TestMenuCommandIsValidL
// -----------------------------------------------------------------------------
//
TInt Ctestdomfinditem::TestMenuCommandIsValidL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomfinditem, "testdomfinditem" );
    _LIT( KTestMenuCommandIsValidL, "In MenuCommandIsValidL" );
    TestModuleIf().Printf( 0, Ktestdomfinditem, KTestMenuCommandIsValidL );
    // Print to log file
    iLog->Log( KTestMenuCommandIsValidL );

    CFindItemMenu* menu = CFindItemMenu::NewLC( R_FIND_ITEM_MENU );

    TBool valid = menu->CommandIsValidL( R_FIND_ITEM_MENU );
    STIF_ASSERT_FALSE( valid );

    CleanupStack::PopAndDestroy( menu );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// Ctestdomfinditem::TestMenuSearchCaseL
// -----------------------------------------------------------------------------
//
TInt Ctestdomfinditem::TestMenuSearchCaseL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomfinditem, "testdomfinditem" );
    _LIT( KTestMenuSearchCase, "In MenuSearchCase" );
    TestModuleIf().Printf( 0, Ktestdomfinditem, KTestMenuSearchCase );
    // Print to log file
    iLog->Log( KTestMenuSearchCase );

    CFindItemMenu* menu = CFindItemMenu::NewLC( R_FIND_ITEM_MENU );

    CFindItemEngine::TFindItemSearchCase searchCase = menu->SearchCase(
            R_FIND_ITEM_MENU + 1 );
    STIF_ASSERT_EQUALS( CFindItemEngine::
            EFindItemSearchPhoneNumberBin, searchCase );

    CleanupStack::PopAndDestroy( menu );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// Ctestdomfinditem::TestMenuUpdateItemFinderMenuL
// -----------------------------------------------------------------------------
//
TInt Ctestdomfinditem::TestMenuUpdateItemFinderMenuL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomfinditem, "testdomfinditem" );
    _LIT( KTestMenuUpdateItemFinderMenuL, "In MenuUpdateItemFinderMenuL" );
    TestModuleIf().Printf( 0, Ktestdomfinditem, KTestMenuUpdateItemFinderMenuL );
    // Print to log file
    iLog->Log( KTestMenuUpdateItemFinderMenuL );

    CFindItemMenu* menu = CFindItemMenu::NewLC( R_FIND_ITEM_MENU );

    CAknForm* frm = new ( ELeave ) CAknForm;
    CleanupStack::PushL( frm );
    frm->ConstructL();

    CEikMenuPane* pane = new ( ELeave ) CEikMenuPane( frm );
    CleanupStack::PushL( pane );
    pane->ConstructL( pane, NULL );

    menu->UpdateItemFinderMenuL( R_FIND_ITEM_MENU, pane );

    CleanupStack::PopAndDestroy( pane );
    CleanupStack::PopAndDestroy( frm );
    CleanupStack::PopAndDestroy( menu );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// Ctestdomfinditem::TestMenuHandleItemFinderCommandL
// -----------------------------------------------------------------------------
//
TInt Ctestdomfinditem::TestMenuHandleItemFinderCommandL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomfinditem, "testdomfinditem" );
    _LIT( KTestMenuHandleItemFinderCommandL, "In MenuHandleItemFinderCommandL" );
    TestModuleIf().Printf( 0, Ktestdomfinditem, KTestMenuHandleItemFinderCommandL );
    // Print to log file
    iLog->Log( KTestMenuHandleItemFinderCommandL );

    CFindItemMenu* menu = CFindItemMenu::NewLC( R_FIND_ITEM_MENU );
    menu->AttachItemFinderMenuL( R_FIND_ITEM_MENU );

    menu->HandleItemFinderCommandL( 0 );

    CleanupStack::PopAndDestroy( menu );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// Ctestdomfinditem::TestMenuAttachItemFinderMenuL
// -----------------------------------------------------------------------------
//
TInt Ctestdomfinditem::TestMenuAttachItemFinderMenuL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomfinditem, "testdomfinditem" );
    _LIT( KTestMenuAttachItemFinderMenuL, "In MenuAttachItemFinderMenuL" );
    TestModuleIf().Printf( 0, Ktestdomfinditem, KTestMenuAttachItemFinderMenuL );
    // Print to log file
    iLog->Log( KTestMenuAttachItemFinderMenuL );

    CFindItemMenu* menu = CFindItemMenu::NewLC( R_FIND_ITEM_MENU );

    menu->AttachItemFinderMenuL( R_FIND_ITEM_MENU );

    CleanupStack::PopAndDestroy( menu );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// Ctestdomfinditem::TestMenuSetCallbackNumberL
// -----------------------------------------------------------------------------
//
TInt Ctestdomfinditem::TestMenuSetCallbackNumberL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomfinditem, "testdomfinditem" );
    _LIT( KTestMenuSetCallbackNumber, "In MenuSetCallbackNumber" );
    TestModuleIf().Printf( 0, Ktestdomfinditem, KTestMenuSetCallbackNumber );
    // Print to log file
    iLog->Log( KTestMenuSetCallbackNumber );

    CFindItemMenu* menu = CFindItemMenu::NewLC( R_FIND_ITEM_MENU );

    menu->SetCallbackNumber( KNumberDes );

    CleanupStack::PopAndDestroy( menu );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// Ctestdomfinditem::TestMenuHandleCallL
// -----------------------------------------------------------------------------
//
TInt Ctestdomfinditem::TestMenuHandleCallL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomfinditem, "testdomfinditem" );
    _LIT( KTestMenuHandleCallL, "In MenuHandleCallL" );
    TestModuleIf().Printf( 0, Ktestdomfinditem, KTestMenuHandleCallL );
    // Print to log file
    iLog->Log( KTestMenuHandleCallL );

    CFindItemMenu* menu = CFindItemMenu::NewLC( R_FIND_ITEM_MENU );

    _LIT( KUrlDes, "http://www.symbian.com" );
    menu->HandleCallL( KUrlDes );

    CleanupStack::PopAndDestroy( menu );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// Ctestdomfinditem::TestMenuHandleVoIPCallL
// -----------------------------------------------------------------------------
//
TInt Ctestdomfinditem::TestMenuHandleVoIPCallL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomfinditem, "testdomfinditem" );
    _LIT( KTestMenuHandleVoIPCallL, "In MenuHandleVoIPCallL" );
    TestModuleIf().Printf( 0, Ktestdomfinditem, KTestMenuHandleVoIPCallL );
    // Print to log file
    iLog->Log( KTestMenuHandleVoIPCallL );

    CFindItemMenu* menu = CFindItemMenu::NewLC( R_FIND_ITEM_MENU );

    menu->HandleVoIPCallL( KNumberDes );

    CleanupStack::PopAndDestroy( menu );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// Ctestdomfinditem::TestMenuSetSenderHighlightStatusL
// -----------------------------------------------------------------------------
//
TInt Ctestdomfinditem::TestMenuSetSenderHighlightStatusL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomfinditem, "testdomfinditem" );
    _LIT( KTestMenuSetSenderHighlightStatus, "In MenuSetSenderHighlightStatus" );
    TestModuleIf().Printf( 0, Ktestdomfinditem, KTestMenuSetSenderHighlightStatus );
    // Print to log file
    iLog->Log( KTestMenuSetSenderHighlightStatus );

    CFindItemMenu* menu = CFindItemMenu::NewLC( R_FIND_ITEM_MENU );

    menu->SetSenderHighlightStatus( ETrue );

    CleanupStack::PopAndDestroy( menu );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// Ctestdomfinditem::TestMenuSetSenderDisplayTextL
// -----------------------------------------------------------------------------
//
TInt Ctestdomfinditem::TestMenuSetSenderDisplayTextL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomfinditem, "testdomfinditem" );
    _LIT( KTestMenuSetSenderDisplayText, "In MenuSetSenderDisplayText" );
    TestModuleIf().Printf( 0, Ktestdomfinditem, KTestMenuSetSenderDisplayText );
    // Print to log file
    iLog->Log( KTestMenuSetSenderDisplayText );

    CFindItemMenu* menu = CFindItemMenu::NewLC( R_FIND_ITEM_MENU );

    menu->SetSenderDisplayText( KNumberDes );

    CleanupStack::PopAndDestroy( menu );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// Ctestdomfinditem::TestMenuAddItemFindMenuL
// -----------------------------------------------------------------------------
//
TInt Ctestdomfinditem::TestMenuAddItemFindMenuL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomfinditem, "testdomfinditem" );
    _LIT( KTestMenuAddItemFindMenuL, "In MenuAddItemFindMenuL" );
    TestModuleIf().Printf( 0, Ktestdomfinditem, KTestMenuAddItemFindMenuL );
    // Print to log file
    iLog->Log( KTestMenuAddItemFindMenuL );

    CFindItemMenu* menu = CFindItemMenu::NewLC( R_FIND_ITEM_MENU );

    CAknForm* frm = new ( ELeave ) CAknForm;
    CleanupStack::PushL( frm );
    frm->ConstructL();

    CEikMenuPane* pane = new ( ELeave ) CEikMenuPane( frm );
    CleanupStack::PushL( pane );
    pane->ConstructL( pane, NULL );

    CItemFinder* finder = CItemFinder::NewL();
    CleanupStack::PushL( finder );

    menu->AddItemFindMenuL( finder, pane, 0, KNumberDes );

    CleanupStack::PopAndDestroy( finder );
    CleanupStack::PopAndDestroy( pane );
    CleanupStack::PopAndDestroy( frm );
    CleanupStack::PopAndDestroy( menu );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// Ctestdomfinditem::TestMenuSetMenuItemVisibilityL
// -----------------------------------------------------------------------------
//
TInt Ctestdomfinditem::TestMenuSetMenuItemVisibilityL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomfinditem, "testdomfinditem" );
    _LIT( KTestMenuSetMenuItemVisibilityL, "In TestMenuSetMenuItemVisibilityL" );
    TestModuleIf().Printf( 0, Ktestdomfinditem, KTestMenuSetMenuItemVisibilityL );
    // Print to log file
    iLog->Log( KTestMenuSetMenuItemVisibilityL );

    CFindItemMenu* menu = CFindItemMenu::NewLC( R_FIND_ITEM_MENU );

    CAknForm* frm = new ( ELeave ) CAknForm;
    CleanupStack::PushL( frm );
    frm->ConstructL();

    CEikMenuPane* pane = new ( ELeave ) CEikMenuPane( frm );
    CleanupStack::PushL( pane );
    pane->ConstructL( pane, NULL );

    CItemFinder* finder = CItemFinder::NewL();
    CleanupStack::PushL( finder );
    
    menu->SetMenuItemVisibility( CFindItemMenu::ECallItem, ETrue );
    menu->AddItemFindMenuL( finder, pane, 0, KNumberDes );

    CleanupStack::PopAndDestroy( finder );
    CleanupStack::PopAndDestroy( pane );
    CleanupStack::PopAndDestroy( frm );
    CleanupStack::PopAndDestroy( menu );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// Ctestdomfinditem::TestMenuSetSenderDescriptorTypeL
// -----------------------------------------------------------------------------
//
TInt Ctestdomfinditem::TestMenuSetSenderDescriptorTypeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomfinditem, "testdomfinditem" );
    _LIT( KTestMenuSetSenderDescriptorType, "In MenuSetSenderDescriptorType" );
    TestModuleIf().Printf( 0, Ktestdomfinditem, KTestMenuSetSenderDescriptorType );
    // Print to log file
    iLog->Log( KTestMenuSetSenderDescriptorType );

    CFindItemMenu* menu = CFindItemMenu::NewLC( R_FIND_ITEM_MENU );

    menu->SetSenderDescriptorType( CItemFinder::EUrlAddress );

    CleanupStack::PopAndDestroy( menu );
    return KErrNone;

    }

