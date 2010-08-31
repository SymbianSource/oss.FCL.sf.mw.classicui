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
* Description:  Test akncheckboxsettingpage.h
*
*/

// INCLUDE FILES
#include <akncheckboxsettingpage.h>
#include <testsdksettingpages.rsg>
#include <bautils.h>

#include "testsdksettingpages.h"
#include "testsdksettingpagesstdinclude.h"
#include "testakncheckboxsettingpageprotected.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesCheckBoxCSelectableItemConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesCheckBoxCSelectableItemConstructorL( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> buffer( KTestString );
    CSelectableItem* selecttableitem = new( ELeave ) CSelectableItem( buffer, ETrue );
    CleanupStack::PushL( selecttableitem );
    STIF_ASSERT_NOT_NULL( selecttableitem );
    CleanupStack::PopAndDestroy( selecttableitem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesCheckBoxCSelectableItemConstructLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesCheckBoxCSelectableItemConstructLL( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> buffer( KTestString );
    CSelectableItem* selecttableitem = new( ELeave ) CSelectableItem( buffer, ETrue );
    CleanupStack::PushL( selecttableitem );
    selecttableitem->ConstructL();
    CleanupStack::PopAndDestroy( selecttableitem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesCheckBoxCSelectableItemSetSelectionStatusL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesCheckBoxCSelectableItemSetSelectionStatusL( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> buffer( KTestString );
    CSelectableItem* selecttableitem = new( ELeave ) CSelectableItem( buffer, ETrue );
    CleanupStack::PushL( selecttableitem );
    selecttableitem->ConstructL();
    selecttableitem->SetSelectionStatus( ETrue );
    TBool status = selecttableitem->SelectionStatus();
    STIF_ASSERT_TRUE( status );
    
    selecttableitem->SetSelectionStatus( EFalse );
    status = selecttableitem->SelectionStatus();
    STIF_ASSERT_FALSE( status );
    
    CleanupStack::PopAndDestroy( selecttableitem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesCheckBoxCSelectableItemSelectionStatusL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesCheckBoxCSelectableItemSelectionStatusL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesCheckBoxCSelectableItemSetSelectionStatusL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesCheckBoxCSelectableItemItemTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesCheckBoxCSelectableItemItemTextL( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> buffer( KTestString );
    CSelectableItem* selecttableitem = new( ELeave ) CSelectableItem( buffer, ETrue );
    CleanupStack::PushL( selecttableitem );
    
    selecttableitem->ConstructL();
    TPtrC valueofitem = selecttableitem->ItemText();
    
    STIF_ASSERT_TRUE( valueofitem == buffer );
    
    CleanupStack::PopAndDestroy( selecttableitem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesCheckBoxCSelectionItemListConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesCheckBoxCSelectionItemListConstructorL( CStifItemParser& /*aItem*/ )
    {
    CSelectionItemList* selectionitemlist = new( ELeave ) CSelectionItemList( KTen );
    CleanupStack::PushL( selectionitemlist );
    STIF_ASSERT_NOT_NULL( selectionitemlist );
    CleanupStack::PopAndDestroy( selectionitemlist );
    return KErrNone;
    }
    

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesCheckBoxCSelectionItemListMdcaCountL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesCheckBoxCSelectionItemListMdcaCountL( CStifItemParser& /*aItem*/ )
    {
    CSelectionItemList* selectionitemlist = new( ELeave ) CSelectionItemList( KTen );
    CleanupStack::PushL( selectionitemlist );
    
    TInt count = selectionitemlist->MdcaCount();
    STIF_ASSERT_EQUALS( KZero, count );
    
    TBuf<KBufSize> buffer( KTestString );
    CSelectableItem* selecttableitem = new( ELeave ) CSelectableItem( buffer, ETrue );
    CleanupStack::PushL( selecttableitem );
    selecttableitem->ConstructL();
    selectionitemlist->AppendL( selecttableitem );
    
    count = selectionitemlist->MdcaCount();
    STIF_ASSERT_EQUALS( KOne, count );
    selectionitemlist->ResetAndDestroy();
    CleanupStack::Pop( selecttableitem );
    CleanupStack::PopAndDestroy( selectionitemlist );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesCheckBoxCSelectionItemListMdcaPointL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesCheckBoxCSelectionItemListMdcaPointL( CStifItemParser& /*aItem*/ )
    {
    CSelectionItemList* selectionitemlist = new( ELeave ) CSelectionItemList( KTen );
    CleanupStack::PushL( selectionitemlist );
    
    TBuf<KBufSize> buffer( KTestString );
    CSelectableItem* selecttableitem = new( ELeave ) CSelectableItem( buffer, ETrue );
    CleanupStack::PushL( selecttableitem );
    selecttableitem->ConstructL();
    selectionitemlist->AppendL( selecttableitem );
    
    
    TPtrC mdcapointvalue = selectionitemlist->MdcaPoint( KZero );
    STIF_ASSERT_TRUE( mdcapointvalue == buffer );
    
    selectionitemlist->ResetAndDestroy();
    CleanupStack::Pop( selecttableitem );
    CleanupStack::PopAndDestroy( selectionitemlist );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesCheckBoxChkBoxSetPgConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesCheckBoxChkBoxSetPgConstructorL( CStifItemParser& /*aItem*/ )
    {
    CSelectionItemList* selectionitemlist = new( ELeave ) CSelectionItemList( KTen );
    CleanupStack::PushL( selectionitemlist );
    CAknCheckBoxSettingPage* pageDialog = new( ELeave ) CAknCheckBoxSettingPage( R_EXAMPLE_SETTING_PAGE, selectionitemlist );
    CleanupStack::PushL( pageDialog );
    STIF_ASSERT_NOT_NULL( pageDialog );
    CleanupStack::PopAndDestroy( pageDialog );
    CleanupStack::PopAndDestroy( selectionitemlist );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesCheckBoxChkBoxSetPgConstructorLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesCheckBoxChkBoxSetPgConstructorLL( CStifItemParser& /*aItem*/ )
    {
    CSelectionItemList* selectionitemlist = new( ELeave ) CSelectionItemList( KTen );
    CleanupStack::PushL( selectionitemlist );
    TBuf< KBufSize > buffer( KTestString );
    CAknCheckBoxSettingPage* pageDialog = new( ELeave ) CAknCheckBoxSettingPage( &buffer, KOne, KZero, KZero, R_EXAMPLE_SETTING_PAGE, selectionitemlist );
    CleanupStack::PushL( pageDialog );
    STIF_ASSERT_NOT_NULL( pageDialog );
    CleanupStack::PopAndDestroy( pageDialog );
    CleanupStack::PopAndDestroy( selectionitemlist );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesCheckBoxChkBoxSetPgConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesCheckBoxChkBoxSetPgConstructL( CStifItemParser& /*aItem*/ )
    {
    CSelectionItemList* selectionitemlist = new( ELeave ) CSelectionItemList( KTen );
    CleanupStack::PushL( selectionitemlist );
    TBuf< KBufSize > buffer( KTestString );
    CAknCheckBoxSettingPage* pageDialog = new( ELeave ) CAknCheckBoxSettingPage( &buffer, KOne, KZero, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE, selectionitemlist );
    CleanupStack::PushL( pageDialog );
    pageDialog->ConstructL();
    CleanupStack::PopAndDestroy( pageDialog );
    CleanupStack::PopAndDestroy( selectionitemlist );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesCheckBoxChkBoxSetPgListBoxControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesCheckBoxChkBoxSetPgListBoxControlL( CStifItemParser& /*aItem*/ )
    {
    CSelectionItemList* selectionitemlist = new( ELeave ) CSelectionItemList( KTen );
    CleanupStack::PushL( selectionitemlist );
    TBuf< KBufSize > buffer( KTestString );
    CAknCheckBoxSettingPage* pageDialog = new( ELeave ) CAknCheckBoxSettingPage( &buffer, KOne, KZero, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE, selectionitemlist );
    CleanupStack::PushL( pageDialog );
    pageDialog->ConstructL();
    CAknSetStyleListBox* styleListBox = pageDialog->ListBoxControl();
    STIF_ASSERT_NOT_NULL( styleListBox );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesCheckBoxChkBoxSetPgSetSelectionItemArrayLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesCheckBoxChkBoxSetPgSetSelectionItemArrayLL( CStifItemParser& /*aItem*/ )
    {
    CSelectionItemList* selectionItemList = new( ELeave ) CSelectionItemList( KTen );
    CleanupStack::PushL( selectionItemList );
    TBuf< KBufSize > buffer( KTestString );
    CSelectableItem* selectTableItem = new( ELeave ) CSelectableItem( buffer, ETrue );
    CleanupStack::PushL( selectTableItem );
    selectTableItem->ConstructL();
    selectionItemList->AppendL( selectTableItem );
    CAknCheckBoxSettingPage* pageDialog = new( ELeave ) CAknCheckBoxSettingPage( &buffer, KOne, KZero, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE, selectionItemList );
    CleanupStack::PushL( pageDialog );
    pageDialog->ConstructL();
    pageDialog->SetSelectionItemArrayL( selectionItemList );
    
    CleanupStack::PopAndDestroy( pageDialog );
    selectionItemList->ResetAndDestroy();
    CleanupStack::Pop( selectTableItem );
    CleanupStack::PopAndDestroy( selectionItemList );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesCheckBoxChkBoxSetPgHandleListBoxEventLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesCheckBoxChkBoxSetPgHandleListBoxEventLL( CStifItemParser& /*aItem*/ )
    {
    CSelectionItemList* selectionItemList = new( ELeave ) CSelectionItemList( KTen );
    CleanupStack::PushL( selectionItemList );
    TBuf< KBufSize > buffer( KTestString );
    CAknCheckBoxSettingPage* pageDialog = new( ELeave ) CAknCheckBoxSettingPage( &buffer, KOne, KZero, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE, selectionItemList );
    CleanupStack::PushL( pageDialog );
    pageDialog->ConstructL();
    pageDialog->HandleListBoxEventL( pageDialog->ListBoxControl(), MEikListBoxObserver::EEventPenDownOnItem );
    
    CleanupStack::PopAndDestroy( pageDialog );
    CleanupStack::PopAndDestroy( selectionItemList );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesCheckBoxChkBoxSetPgHandlePointerEventLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesCheckBoxChkBoxSetPgHandlePointerEventLL( CStifItemParser& /*aItem*/ )
    {
    CSelectionItemList* selectionItemList = new( ELeave ) CSelectionItemList( KTen );
    CleanupStack::PushL( selectionItemList );
    TBuf< KBufSize > buffer( KTestString );
    CAknCheckBoxSettingPage* pageDialog = new( ELeave ) CAknCheckBoxSettingPage( &buffer, KOne, KZero, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE, selectionItemList );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    
    pageDialog->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( pageDialog );
    CleanupStack::PopAndDestroy( selectionItemList );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesCheckBoxChkBoxSetPgHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesCheckBoxChkBoxSetPgHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    CSelectionItemList* selectionItemList = new( ELeave ) CSelectionItemList( KTen );
    CleanupStack::PushL( selectionItemList );
    TBuf< KBufSize > buffer( KTestString );
    CAknCheckBoxSettingPage* pageDialog = new( ELeave ) CAknCheckBoxSettingPage( &buffer, 
        KOne, KZero, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE, selectionItemList );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    pageDialog->HandleResourceChange( KAknsMessageSkinChange );

    CleanupStack::PopAndDestroy( pageDialog );
    CleanupStack::PopAndDestroy( selectionItemList );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesCheckBoxChkBoxSetPgDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesCheckBoxChkBoxSetPgDestructorL( CStifItemParser& /*aItem*/ )
    {
    CSelectionItemList* selectionItemList = new( ELeave ) CSelectionItemList( KTen );
    CleanupStack::PushL( selectionItemList );
    TBuf< KBufSize > buffer( KTestString );
    CTestCheckBoxSettingPage* pageDialog = new( ELeave ) CTestCheckBoxSettingPage( &buffer, 
        KOne, KZero, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE, selectionItemList );
    delete pageDialog;
    CleanupStack::PopAndDestroy( selectionItemList );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesCheckBoxChkBoxSetPgUpdateSettingLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesCheckBoxChkBoxSetPgUpdateSettingLL( CStifItemParser& /*aItem*/ )
    {
    CSelectionItemList* selectionItemList = new( ELeave ) CSelectionItemList( KTen );
    CleanupStack::PushL( selectionItemList );
    TBuf< KBufSize > buffer( KTestString );
    CTestCheckBoxSettingPage* pageDialog = new( ELeave ) CTestCheckBoxSettingPage( &buffer, 
        KOne, KZero, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE, selectionItemList );
    CleanupStack::PushL( pageDialog );
    pageDialog->TestUpdateSettingL();
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesCheckBoxChkBoxSetPgDynamicInitLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesCheckBoxChkBoxSetPgDynamicInitLL( CStifItemParser& /*aItem*/ )
    {
    CSelectionItemList* selectionItemList = new( ELeave ) CSelectionItemList( KTen );
    CleanupStack::PushL( selectionItemList );
    TBuf< KBufSize > buffer( KTestString );
    CTestCheckBoxSettingPage* pageDialog = new( ELeave ) CTestCheckBoxSettingPage( &buffer, 
        KOne, KZero, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE, selectionItemList );
    CleanupStack::PushL( pageDialog );
    pageDialog->TestDynamicInitL();
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesCheckBoxChkBoxSetPgProcessCommandLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesCheckBoxChkBoxSetPgProcessCommandLL( CStifItemParser& /*aItem*/ )
    {
    CSelectionItemList* selectionItemList = new( ELeave ) CSelectionItemList( KTen );
    CleanupStack::PushL( selectionItemList );
    TBuf< KBufSize > buffer( KTestString );
    CTestCheckBoxSettingPage* pageDialog = new( ELeave ) CTestCheckBoxSettingPage( &buffer, 
        KOne, KZero, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE, selectionItemList );
    CleanupStack::PushL( pageDialog );
    pageDialog->ConstructL();
    CCoeEnv::Static()->AppUi()->AddToStackL( pageDialog );
    pageDialog->TestProcessCommandL( EAknSoftkeySelect );
    CCoeEnv::Static()->AppUi()->RemoveFromStack( pageDialog );
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesCheckBoxChkBoxSetPgSelectCurrentItemLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesCheckBoxChkBoxSetPgSelectCurrentItemLL( CStifItemParser& /*aItem*/ )
    {
    CSelectionItemList* selectionItemList = new( ELeave ) CSelectionItemList( KTen );
    CleanupStack::PushL( selectionItemList );
    TBuf< KBufSize > buffer( KTestString );
    CTestCheckBoxSettingPage* pageDialog = new( ELeave ) CTestCheckBoxSettingPage( &buffer, 
        KOne, KZero, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE, selectionItemList );
    CleanupStack::PushL( pageDialog );
    pageDialog->ConstructL();
    pageDialog->TestSelectCurrentItemL();
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesCheckBoxChkBoxSetPgWriteInternalStateLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesCheckBoxChkBoxSetPgWriteInternalStateLL( CStifItemParser& /*aItem*/ )
    {
    CSelectionItemList* selectionItemList = new( ELeave ) CSelectionItemList( KTen );
    CleanupStack::PushL( selectionItemList );
    TBuf< KBufSize > buffer( KTestString );
    CTestCheckBoxSettingPage* pageDialog = new( ELeave ) CTestCheckBoxSettingPage( &buffer, 
        KOne, KZero, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE, selectionItemList );
    CleanupStack::PushL( pageDialog );
    pageDialog->ConstructL();
    
    RDesWriteStream stream;
    CleanupClosePushL( stream );
    HBufC8* hbuf = HBufC8::NewL( KHBufSize );
    CleanupStack::PushL( hbuf );
    TPtr8 ptr = hbuf->Des();
    stream.Open( ptr );
    pageDialog->TestWriteInternalStateL( stream );
    stream.CommitL();
    stream.Close();
    
    CleanupStack::PopAndDestroy( KFour );
    return KErrNone;
    }

//End file

