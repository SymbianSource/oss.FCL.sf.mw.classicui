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
* Description:  Test CAknListBoxLayoutDecorator.H
*
*/



// [INCLUDE FILES]
#include <e32base.h>
#include <aknlistboxsettingpage.h>
#include <testsdklists.rsg>

#include "testsdklists.h"
#include "testsdkcontainer.h"
#include "testsdklistslistboxsettingpageext.h"

const TInt KLength = 20;
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBSPHandleListBoxEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBSPHandleListBoxEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknListBoxLayoutDecoratorTestModule" );
    _LIT( KTestLBSPHandleListBoxEventL, "In TestLBSPHandleListBoxEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestLBSPHandleListBoxEventL );
    // Print to log file
    iLog->Log( KTestLBSPHandleListBoxEventL );

    _LIT( KItemText, "Item1" );
    TBuf<KLength> temp( KItemText );

    CSelectableItem* item = new( ELeave ) CSelectableItem( temp, EFalse );
    CleanupStack::PushL( item );            
    item->ConstructL();

    CSelectionItemList* itemList = new( ELeave ) CSelectionItemList( 1 );
    CleanupStack::PushL( itemList );            
    itemList->AppendL( item );

    CAknListBoxSettingPageExt* settingPage = 
        new ( ELeave ) CAknListBoxSettingPageExt( R_TESTLIST_SETTING_PAGE, itemList );
    CleanupStack::PushL( settingPage );
    settingPage->ConstructL();

    TInt err = KErrNone;
    TRAP( err, settingPage->CAknListBoxSettingPage::HandleListBoxEventL(
                    settingPage->ListBoxControl(), 
                    MEikListBoxObserver::EEventItemClicked ) );

    CleanupStack::PopAndDestroy( settingPage );
    CleanupStack::PopAndDestroy( itemList );
    CleanupStack::PopAndDestroy( item );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBSPCheckAndSetDataValidityL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBSPCheckAndSetDataValidityL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknListBoxLayoutDecoratorTestModule" );
    _LIT( KTestLBSPCheckAndSetDataValidityL, "In TestLBSPCheckAndSetDataValidityL" );
    TestModuleIf().Printf( 0, KTestModule, KTestLBSPCheckAndSetDataValidityL );
    // Print to log file
    iLog->Log( KTestLBSPCheckAndSetDataValidityL );

    _LIT( KItemText, "Item1" );
    TBuf<KLength> temp( KItemText );

    CSelectableItem* item = new( ELeave ) CSelectableItem( temp, EFalse );
    CleanupStack::PushL( item );            
    item->ConstructL();

    CSelectionItemList* itemList = new( ELeave ) CSelectionItemList( 1 );
    CleanupStack::PushL( itemList );            
    itemList->AppendL( item );

    CAknListBoxSettingPageExt* settingPage = 
        new ( ELeave ) CAknListBoxSettingPageExt( R_TESTLIST_SETTING_PAGE, itemList );
    CleanupStack::PushL( settingPage );
    settingPage->ConstructL();

    settingPage->CAknListBoxSettingPage::CheckAndSetDataValidity();

    CleanupStack::PopAndDestroy( settingPage );
    CleanupStack::PopAndDestroy( itemList );
    CleanupStack::PopAndDestroy( item );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBSPUpdateCbaL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBSPUpdateCbaL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknListBoxLayoutDecoratorTestModule" );
    _LIT( KTestLBSPCheckAndSetDataValidityL, "In TestLBSPCheckAndSetDataValidityL" );
    TestModuleIf().Printf( 0, KTestModule, KTestLBSPCheckAndSetDataValidityL );
    // Print to log file
    iLog->Log( KTestLBSPCheckAndSetDataValidityL );

    _LIT( KItemText, "Item1" );
    TBuf<KLength> temp( KItemText );

    CSelectableItem* item = new( ELeave ) CSelectableItem( temp, EFalse );
    CleanupStack::PushL( item );            
    item->ConstructL();

    CSelectionItemList* itemList = new( ELeave ) CSelectionItemList( 1 );
    CleanupStack::PushL( itemList );            
    itemList->AppendL( item );

    CAknListBoxSettingPageExt* settingPage = 
        new ( ELeave ) CAknListBoxSettingPageExt( R_TESTLIST_SETTING_PAGE, itemList );
    CleanupStack::PushL( settingPage );
    settingPage->ConstructL();

    settingPage->CAknListBoxSettingPage::UpdateCbaL();

    CleanupStack::PopAndDestroy( settingPage );
    CleanupStack::PopAndDestroy( itemList );
    CleanupStack::PopAndDestroy( item );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBSPSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBSPSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknListBoxLayoutDecoratorTestModule" );
    _LIT( KTestLBSPSizeChangedL, "In TestLBSPSizeChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestLBSPSizeChangedL );
    // Print to log file
    iLog->Log( KTestLBSPSizeChangedL );

    _LIT( KItemText, "Item1" );
    TBuf<KLength> temp( KItemText );

    CSelectableItem* item = new( ELeave ) CSelectableItem( temp, EFalse );
    CleanupStack::PushL( item );            
    item->ConstructL();

    CSelectionItemList* itemList = new( ELeave ) CSelectionItemList( 1 );
    CleanupStack::PushL( itemList );            
    itemList->AppendL( item );

    CAknListBoxSettingPageExt* settingPage = 
        new ( ELeave ) CAknListBoxSettingPageExt( R_TESTLIST_SETTING_PAGE, itemList );
    CleanupStack::PushL( settingPage );
    settingPage->ConstructL();

    settingPage->CAknListBoxSettingPage::SizeChanged();

    CleanupStack::PopAndDestroy( settingPage );
    CleanupStack::PopAndDestroy( itemList );
    CleanupStack::PopAndDestroy( item );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBSPDrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBSPDrawL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "AknListBoxLayoutDecoratorTestModule" );
    _LIT( KTestLBSPDrawL, "In TestLBSPDrawL" );
    TestModuleIf().Printf( 0, KTestModule, KTestLBSPDrawL );
    // Print to log file
    iLog->Log( KTestLBSPDrawL );

    _LIT( KItemText, "Item1" );
    TBuf<KLength> temp( KItemText );

    CSelectableItem* item = new( ELeave ) CSelectableItem( temp, EFalse );
    CleanupStack::PushL( item );            
    item->ConstructL();

    CSelectionItemList* itemList = new( ELeave ) CSelectionItemList( 1 );
    CleanupStack::PushL( itemList );            
    itemList->AppendL( item );

    CAknListBoxSettingPageExt* settingPage = 
        new ( ELeave ) CAknListBoxSettingPageExt( R_TESTLIST_SETTING_PAGE, itemList );
    CleanupStack::PushL( settingPage );
    settingPage->ConstructL();

    iContainer->ActivateGc();
    settingPage->CAknListBoxSettingPage::Draw( iContainer->Rect() );
    iContainer->DeactivateGc();

    CleanupStack::PopAndDestroy( settingPage );
    CleanupStack::PopAndDestroy( itemList );
    CleanupStack::PopAndDestroy( item );

    return KErrNone;
    }

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// C++ constructor
// ---------------------------------------------------------------------------
//
CAknListBoxSettingPageExt::CAknListBoxSettingPageExt( TInt aResourceId, 
    CSelectionItemList* aItemArray ) : 
    CAknCheckBoxSettingPage( aResourceId, aItemArray )
    {    
    }
