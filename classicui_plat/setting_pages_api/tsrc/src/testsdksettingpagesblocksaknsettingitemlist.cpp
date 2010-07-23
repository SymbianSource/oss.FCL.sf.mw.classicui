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
* Description:  Test aknsettingitemlist.h
*
*/

// INCLUDE FILES
#include <aknsettingitemlist.h>
#include <testsdksettingpages.rsg>
#include <akniconarray.h>
#include <eikmsg.h>
#include <eikapp.h>
#include <avkon.mbg>
#include <gulicon.h>
#include <akniconutils.h>
#include <in_sock.h>
#include <e32cmn.h>
#include <barsread.h>
#include <coemain.h>
#include <eiklbo.h>
#include <eiklbi.h>
#include <eiktxlbx.h>
#include <aknpopup.h> 

#include "testsdksettingpagesstdinclude.h"
#include "testsdksettingpages.h"
#include "testaknsettingitemlistprotected.h"
#include "testparentcontrol.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListConstructorL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItem* settingItem = new( ELeave ) CAknSettingItem( KOne );
    CleanupStack::PushL( settingItem );
    STIF_ASSERT_NOT_NULL( settingItem );
    CleanupStack::PopAndDestroy( settingItem );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListDestructorL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItem* settingItem = new( ELeave ) CAknSettingItem( KOne );
    CleanupStack::PushL( settingItem );
    STIF_ASSERT_NOT_NULL( settingItem );
    CleanupStack::PopAndDestroy( settingItem );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListConstructL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItem* settingItem = new( ELeave ) CAknSettingItem( KOne );
    CleanupStack::PushL( settingItem );
    
    TBuf< KBufSize > buffer( KTestString );
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( mIcon );
    CleanupStack::Pop( mask );
    CleanupStack::Pop( bitmap );
    
    TBuf< KBufSize > buf( KTestString );
    settingItem->SetEmptyItemTextL( buf );
    settingItem->ConstructL( ETrue, KOne, buffer, mIcons, R_EXAMPLE_SETTING_PAGE,
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL );
    
    CleanupStack::PopAndDestroy( mIcons );
    CleanupStack::PopAndDestroy( settingItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListStoreLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListStoreLL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItem* settingItem = new( ELeave ) CAknSettingItem( KOne );
    CleanupStack::PushL( settingItem );
    settingItem->StoreL();
    CleanupStack::PopAndDestroy( settingItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListLoadLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListLoadLL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItem* settingItem = new( ELeave ) CAknSettingItem( KOne );
    CleanupStack::PushL( settingItem );
    settingItem->LoadL();
    CleanupStack::PopAndDestroy( settingItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEditItemLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEditItemLL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItem* settingItem = new( ELeave ) CAknSettingItem( KOne );
    CleanupStack::PushL( settingItem );
    settingItem->EditItemL( ETrue );
    CleanupStack::PopAndDestroy( settingItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListUpdateListBoxTextLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListUpdateListBoxTextLL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItem* settingItem = new( ELeave ) CAknSettingItem( KOne );
    CleanupStack::PushL( settingItem );
    
    TBuf< KBufSize > buffer( KTestString );
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( mIcon );
    CleanupStack::Pop( mask );
    CleanupStack::Pop( bitmap );
    
    TBuf< KBufSize > buf( KTestString );
    settingItem->SetEmptyItemTextL( buf );
    settingItem->ConstructL( ETrue, KOne, buffer, mIcons, R_EXAMPLE_SETTING_PAGE,
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL );
    
    settingItem->UpdateListBoxTextL();
    
    CleanupStack::PopAndDestroy( mIcons );
    CleanupStack::PopAndDestroy( settingItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListSettingNameL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListSettingNameL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItem* settingItem = new( ELeave ) CAknSettingItem( KOne );
    CleanupStack::PushL( settingItem );
    
    TBuf< KBufSize > buffer( KTestString );
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( mIcon );
    CleanupStack::Pop( mask );
    CleanupStack::Pop( bitmap );
    
    TBuf< KBufSize > buf( KTestString );
    settingItem->SetEmptyItemTextL( buf );
    settingItem->ConstructL( ETrue, KOne, buffer, mIcons, R_EXAMPLE_SETTING_PAGE,
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL );
    
    TPtrC returnname = settingItem->SettingName();
    STIF_ASSERT_TRUE( buf == returnname );
    
    CleanupStack::PopAndDestroy( mIcons );
    CleanupStack::PopAndDestroy( settingItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListSettingNumberL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListSettingNumberL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItem* settingItem = new( ELeave ) CAknSettingItem( KOne );
    CleanupStack::PushL( settingItem );
    
    TInt number = settingItem->SettingNumber();
    STIF_ASSERT_EQUALS( EAknSettingPageNoOrdinalDisplayed, number );
    
    TBuf< KBufSize > buffer( KTestString );
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( mIcon );
    CleanupStack::Pop( mask );
    CleanupStack::Pop( bitmap );
    
    TBuf< KBufSize > buf( KTestString );
    settingItem->SetEmptyItemTextL( buf );
    settingItem->ConstructL( ETrue, KOne, buffer, mIcons, R_EXAMPLE_SETTING_PAGE,
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL );
    
    number = settingItem->SettingNumber();
    STIF_ASSERT_EQUALS( KOne, number );
    
    CleanupStack::PopAndDestroy( mIcons );
    CleanupStack::PopAndDestroy( settingItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListIsHiddenL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListIsHiddenL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItem* settingItem = new( ELeave ) CAknSettingItem( KOne );
    CleanupStack::PushL( settingItem );
    
    TBool hidden = settingItem->IsHidden();
    STIF_ASSERT_FALSE( hidden );
    
    settingItem->SetHidden( ETrue );
    hidden = settingItem->IsHidden();
    STIF_ASSERT_TRUE( hidden );
    
    CleanupStack::PopAndDestroy( hidden );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListIsNumberedStyleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListIsNumberedStyleL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItem* settingItem = new( ELeave ) CAknSettingItem( KOne );
    CleanupStack::PushL( settingItem );
    
    TBool numberstyle = settingItem->IsNumberedStyle();
    STIF_ASSERT_FALSE( numberstyle );
    
    TBuf< KBufSize > buffer( KTestString );
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( mIcon );
    CleanupStack::Pop( mask );
    CleanupStack::Pop( bitmap );
    
    TBuf< KBufSize > buf( KTestString );
    settingItem->SetEmptyItemTextL( buf );
    settingItem->ConstructL( ETrue, KOne, buffer, mIcons, R_EXAMPLE_SETTING_PAGE,
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL );
    
    numberstyle = settingItem->IsNumberedStyle();
    STIF_ASSERT_TRUE( numberstyle );
    
    CleanupStack::PopAndDestroy( mIcons );
    CleanupStack::PopAndDestroy( settingItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListSetHiddenL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListSetHiddenL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItem* settingItem = new( ELeave ) CAknSettingItem( KOne );
    CleanupStack::PushL( settingItem );
    
    settingItem->SetHidden( ETrue );
    settingItem->SetHidden( EFalse );
    
    CleanupStack::PopAndDestroy( settingItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListSettingTextLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListSettingTextLL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItem* settingItem = new( ELeave ) CAknSettingItem( KOne );
    CleanupStack::PushL( settingItem );

    TBuf< KBufSize > buffer( KTestString );
    settingItem->SetEmptyItemTextL( buffer );
    
    TBuf< KBufSize > text = settingItem->SettingTextL();
    STIF_ASSERT_EQUALS( buffer, text );
    
    CleanupStack::PopAndDestroy( settingItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListListBoxTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListListBoxTextL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItem* settingItem = new( ELeave ) CAknSettingItem( KOne );
    CleanupStack::PushL( settingItem );
    
    HBufC* listboxtext = settingItem->ListBoxText();
    STIF_ASSERT_NULL( listboxtext );
    
    TBuf< KBufSize > buffer( KTestString );
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( mIcon );
    CleanupStack::Pop( mask );
    CleanupStack::Pop( bitmap );
    
    TBuf< KBufSize > buf( KTestString );
    settingItem->SetEmptyItemTextL( buf );
    settingItem->ConstructL( ETrue, KOne, buffer, mIcons, R_EXAMPLE_SETTING_PAGE,
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL );
    
    listboxtext = settingItem->ListBoxText();
    STIF_ASSERT_NOT_NULL( listboxtext );
    
    CleanupStack::PopAndDestroy( mIcons );
    CleanupStack::PopAndDestroy( settingItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListIdentifierL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListIdentifierL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItem* settingItem = new( ELeave ) CAknSettingItem( KOne );
    CleanupStack::PushL( settingItem );
    
    TInt listidentifier = settingItem->Identifier();
    STIF_ASSERT_EQUALS( KOne, listidentifier );
    
    CleanupStack::PopAndDestroy( settingItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListHasIconL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListHasIconL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItem* settingItem = new( ELeave ) CAknSettingItem( KOne );
    CleanupStack::PushL( settingItem );
    
    TBool hasicon = settingItem->HasIcon();
    STIF_ASSERT_FALSE( hasicon );

    CleanupStack::PopAndDestroy( settingItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListSetEmptyItemTextLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListSetEmptyItemTextLL( CStifItemParser& /*aItem*/ )
    {
    CTestSettingItem* settingItem = new( ELeave ) CTestSettingItem( KOne );
    CleanupStack::PushL( settingItem );
    
    TBuf< KBufSize > buffer( KTestString );
    settingItem->SetEmptyItemTextL( buffer );
    
    TBuf< KBufSize > returntext = settingItem->DoEmptyItemText();
    STIF_ASSERT_EQUALS( buffer, returntext );
    
    CleanupStack::PopAndDestroy( settingItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListSetCompulsoryIndTextLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListSetCompulsoryIndTextLL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItem* settingItem = new( ELeave ) CAknSettingItem( KOne );
    CleanupStack::PushL( settingItem );
    
    TBuf< KBufSize > buffer( KTestString );
    settingItem->SetCompulsoryIndTextL( buffer );
    
    CleanupStack::PopAndDestroy( settingItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListHandleSettingPageEventLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListHandleSettingPageEventLL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItem* settingItem = new( ELeave ) CAknSettingItem( KOne );
    CleanupStack::PushL( settingItem );
    
    HBufC* listboxtext = settingItem->ListBoxText();
    STIF_ASSERT_NULL( listboxtext );
    
    TBuf< KBufSize > buffer( KTestString );
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( KThree );
    
    TBuf< KBufSize > buf( KTestString );
    settingItem->SetEmptyItemTextL( buf );
    settingItem->ConstructL( ETrue, KOne, buffer, mIcons, R_EXAMPLE_SETTING_PAGE,
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL );
    
    CAknSettingPage* page = new( ELeave ) CAknSettingPage( R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( page );
    
    settingItem->HandleSettingPageEventL( page, MAknSettingPageObserver::EEventSettingChanged );
    settingItem->HandleSettingPageEventL( page, MAknSettingPageObserver::EEventSettingCancelled );
    settingItem->HandleSettingPageEventL( page, MAknSettingPageObserver::EEventSettingOked );
    
    CleanupStack::PopAndDestroy( page );
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListVisibleIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListVisibleIndexL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItem* settingItem = new( ELeave ) CAknSettingItem( KOne );
    CleanupStack::PushL( settingItem );
    
    TInt visibleindex = settingItem->VisibleIndex();
    STIF_ASSERT_EQUALS( KZero, visibleindex );
    
    CleanupStack::PopAndDestroy( settingItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListSetSettingPageFlagsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListSetSettingPageFlagsL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItem* settingItem = new( ELeave ) CAknSettingItem( KOne );
    CleanupStack::PushL( settingItem );
    
    settingItem->SetSettingPageFlags( KOne );
    TInt pageflags = settingItem->SettingPageFlags();
    STIF_ASSERT_EQUALS( KOne, pageflags );
    
    settingItem->SetSettingPageFlags( KTwo );
    pageflags = settingItem->SettingPageFlags();
    STIF_ASSERT_EQUALS( KTwo, pageflags );
    
    CleanupStack::PopAndDestroy( settingItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListSettingPageFlagsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListSettingPageFlagsL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesItemListSetSettingPageFlagsL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListSetProtectionStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListSetProtectionStateL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItem* settingItem = new( ELeave ) CAknSettingItem( KOne );
    CleanupStack::PushL( settingItem );
    
    CAknSettingItem::TSettingItemProtection protection = settingItem->ProtectionState();
    STIF_ASSERT_EQUALS( CAknSettingItem::ENoSettingItemProtection, protection );
    
    settingItem->SetProtectionState( CAknSettingItem::ENoSettingItemProtection );
    protection = settingItem->ProtectionState();
    STIF_ASSERT_EQUALS( CAknSettingItem::ENoSettingItemProtection, protection );
    
    settingItem->SetProtectionState( CAknSettingItem::ESettingItemViewOnly );
    protection = settingItem->ProtectionState();
    STIF_ASSERT_EQUALS( CAknSettingItem::ESettingItemViewOnly, protection );
    
    settingItem->SetProtectionState( CAknSettingItem::ESettingItemProtected );
    protection = settingItem->ProtectionState();
    STIF_ASSERT_EQUALS( CAknSettingItem::ESettingItemProtected, protection );
    
    CleanupStack::PopAndDestroy( settingItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListProtectionStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListProtectionStateL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesItemListSetProtectionStateL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListCompleteConstructionLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListCompleteConstructionLL( CStifItemParser& /*aItem*/ )
    {
    CTestSettingItem* settingItem = new( ELeave ) CTestSettingItem( KOne );
    CleanupStack::PushL( settingItem );
    
    settingItem->DoCompleteConstructionL();
    
    CleanupStack::PopAndDestroy( settingItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListCreateBitmapLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListCreateBitmapLL( CStifItemParser& /*aItem*/ )
    {
    CTestSettingItem* settingItem = new( ELeave ) CTestSettingItem( KOne );
    CleanupStack::PushL( settingItem );
    
    CFbsBitmap* returnbitmap = settingItem->DoCreateBitmapL();
    STIF_ASSERT_NULL( returnbitmap );
    
    CleanupStack::PopAndDestroy( settingItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListSetSettingPageL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListSetSettingPageL( CStifItemParser& /*aItem*/ )
    {
    CTestSettingItem* settingItem = new( ELeave ) CTestSettingItem( KOne );
    CleanupStack::PushL( settingItem );
    
    CAknSettingPage* settingpage = settingItem->DoSettingPage();
    STIF_ASSERT_NULL( settingpage );
    
    CAknSettingPage* page = new( ELeave ) CAknSettingPage( R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( page );
    
    settingItem->DoSetSettingPage( page );
    settingpage = settingItem->DoSettingPage();
    STIF_ASSERT_EQUALS( page, settingpage );
    
    CleanupStack::PopAndDestroy( page );
    CleanupStack::PopAndDestroy( settingItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListSettingPageL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListSettingPageL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesItemListSetSettingPageL( aItem );
    return err;
    }


// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListSetUpStandardSettingPageLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListSetUpStandardSettingPageLL( CStifItemParser& /*aItem*/ )
    {
    CTestSettingItem* settingItem = new( ELeave ) CTestSettingItem( KOne );
    CleanupStack::PushL( settingItem );
    
    CAknSettingPage* page = new( ELeave ) CAknSettingPage( R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( page );
    settingItem->DoSetSettingPage( page );
    
    TBuf< KBufSize > buffer( KTestString );
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( KThree );
    
    TBuf< KBufSize > buf( KTestString );
    settingItem->SetEmptyItemTextL( buf );
    settingItem->ConstructL( ETrue, KOne, buffer, mIcons, R_EXAMPLE_SETTING_PAGE,
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL );
    
    settingItem->DoSetUpStandardSettingPageL();
    TBool flag = settingItem->DoSettingPage()->IsNumbered();
    STIF_ASSERT_TRUE( flag );
    
    CleanupStack::PopAndDestroy( KThree );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEmptyItemTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEmptyItemTextL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesItemListSetEmptyItemTextLL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListSettingPageResourceIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListSettingPageResourceIdL( CStifItemParser& /*aItem*/ )
    {
    CTestSettingItem* settingItem = new( ELeave ) CTestSettingItem( KOne );
    CleanupStack::PushL( settingItem );
    
    TBuf< KBufSize > buffer( KTestString );
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( KThree );
    
    TBuf< KBufSize > buf( KTestString );
    settingItem->SetEmptyItemTextL( buf );
    settingItem->ConstructL( ETrue, KOne, buffer, mIcons, R_EXAMPLE_SETTING_PAGE,
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL );
    
    TInt settingpageId = settingItem->DoSettingPageResourceId();
    STIF_ASSERT_EQUALS( R_EXAMPLE_SETTING_PAGE, settingpageId );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListSettingEditorResourceIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListSettingEditorResourceIdL( CStifItemParser& /*aItem*/ )
    {
    CTestSettingItem* settingItem = new( ELeave ) CTestSettingItem( KOne );
    CleanupStack::PushL( settingItem );
    
    TBuf< KBufSize > buffer( KTestString );
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( KThree );
    
    TBuf< KBufSize > buf( KTestString );
    settingItem->SetEmptyItemTextL( buf );
    settingItem->ConstructL( ETrue, KOne, buffer, mIcons, R_EXAMPLE_SETTING_PAGE,
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL );
    
    TInt editorId = settingItem->DoSettingEditorResourceId();
    STIF_ASSERT_EQUALS( R_EXAMPLE_EDITOR_CONTROL, editorId );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListAssociatedResourceIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListAssociatedResourceIdL( CStifItemParser& /*aItem*/ )
    {
    CTestSettingItem* settingItem = new( ELeave ) CTestSettingItem( KOne );
    CleanupStack::PushL( settingItem );
    
    TBuf< KBufSize > buffer( KTestString );
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( KThree );
    
    TBuf< KBufSize > buf( KTestString );
    settingItem->SetEmptyItemTextL( buf );
    settingItem->ConstructL( ETrue, KOne, buffer, mIcons, R_EXAMPLE_SETTING_PAGE,
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL );
    
    TInt mAssociatedId = settingItem->DoAssociatedResourceId();
    STIF_ASSERT_EQUALS( KZero, mAssociatedId );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListSetIconMaskL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListSetIconMaskL( CStifItemParser& /*aItem*/ )
    {
    CTestSettingItem* settingItem = new( ELeave ) CTestSettingItem( KOne );
    CleanupStack::PushL( settingItem );
    
    TBool flag = settingItem->DoSetIconMask( NULL );
    STIF_ASSERT_FALSE( flag );
    
    TBuf< KBufSize > buffer( KTestString );
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( KThree );
    
    TBuf< KBufSize > buf( KTestString );
    settingItem->SetEmptyItemTextL( buf );
    settingItem->ConstructL( ETrue, KOne, buffer, mIcons, R_EXAMPLE_SETTING_PAGE,
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL );
    
    CFbsBitmap* setbitmap = NULL;
    CFbsBitmap* setmask = NULL;
    AknIconUtils::CreateIconLC( setbitmap, setmask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );

    flag = settingItem->DoSetIconMask( setmask );
    STIF_ASSERT_FALSE( flag );
    
    CleanupStack::PopAndDestroy( setmask );
    CleanupStack::PopAndDestroy( setbitmap );
    CleanupStack::PopAndDestroy( mIcons );
    CleanupStack::PopAndDestroy( settingItem );
    return KErrNone;
    }

//CAknTextSettingItem
// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListTextSetItemConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListTextSetItemConstructorL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CAknTextSettingItem* textSettingItem = new( ELeave ) CAknTextSettingItem( KOne, buffer );
    CleanupStack::PushL( textSettingItem);
    STIF_ASSERT_NOT_NULL( textSettingItem );
    CleanupStack::PopAndDestroy( textSettingItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListTextSetItemDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListTextSetItemDestructorL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CAknTextSettingItem* textSettingItem = new( ELeave ) CAknTextSettingItem( KOne, buffer );
    CleanupStack::PushL( textSettingItem);
    CleanupStack::PopAndDestroy( textSettingItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListTextSetItemStoreLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListTextSetItemStoreLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestTextSettingItem* textSettingItem = new( ELeave ) CTestTextSettingItem( KOne, buffer );
    CleanupStack::PushL( textSettingItem);
    
    TPtrC externaltext = textSettingItem->DoExternalText();
    STIF_ASSERT_TRUE( buffer == externaltext );
    
    TBuf< KBufSize > buf( KTestStringReplace );
    textSettingItem->DoSetExternalText( buf );
    
    textSettingItem->LoadL();
    textSettingItem->StoreL();
    
    TPtrC externaltexttwo = textSettingItem->DoExternalText();
    STIF_ASSERT_TRUE( buf == externaltexttwo );
    
    CleanupStack::PopAndDestroy( textSettingItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListTextSetItemLoadLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListTextSetItemLoadLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestTextSettingItem* textSettingItem = new( ELeave ) CTestTextSettingItem( KOne, buffer );
    CleanupStack::PushL( textSettingItem);
    
    
    textSettingItem->LoadL();
    TPtrC mInternaltext = textSettingItem->DoInternalTextPtr();
    STIF_ASSERT_TRUE( buffer == mInternaltext );
    
    TBuf< KBufSize > buf( KTestStringReplace );
    textSettingItem->DoSetExternalText( buf );
    
    textSettingItem->LoadL();
    TPtrC mInternaltexttwo = textSettingItem->DoInternalTextPtr();
    STIF_ASSERT_TRUE( buf == mInternaltexttwo );
    
    CleanupStack::PopAndDestroy( textSettingItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListTextSetItemSettingTextLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListTextSetItemSettingTextLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CAknTextSettingItem* textSettingItem = new( ELeave ) CAknTextSettingItem( KOne, buffer );
    CleanupStack::PushL( textSettingItem);
    
    TBuf< KBufSize > buf( KTestStringReplace );
    textSettingItem->SetEmptyItemTextL( buf );
    textSettingItem->LoadL();
    TBuf< KBufSize > returntext = textSettingItem->SettingTextL();
    STIF_ASSERT_EQUALS( buffer, returntext );
    
    textSettingItem->LoadL();
    returntext = textSettingItem->SettingTextL();
    STIF_ASSERT_EQUALS( buffer, returntext );
    
    CleanupStack::PopAndDestroy( textSettingItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListTextSetItemEditItemLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListTextSetItemEditItemLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CAknTextSettingItem* textSettingItem = new( ELeave ) CAknTextSettingItem( KOne, buffer );
    CleanupStack::PushL( textSettingItem);
    textSettingItem->LoadL();
    
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( KThree );
    
    textSettingItem->SetEmptyItemTextL( buffer );
    textSettingItem->ConstructL( ETrue, KOne, buffer, mIcons, R_TEXT_SETTING_PAGE,
        EEikCtEdwin, R_TEXT_CONTROL );
    
    textSettingItem->EditItemL( ETrue );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListTextSetItemInternalTextPtrL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListTextSetItemInternalTextPtrL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesItemListTextSetItemLoadLL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListTextSetItemExternalTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListTextSetItemExternalTextL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesItemListTextSetItemStoreLL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListTextSetItemSetExternalTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListTextSetItemSetExternalTextL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesItemListTextSetItemStoreLL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListIntegerSetItemConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListIntegerSetItemConstructorL( CStifItemParser& /*aItem*/ )
    {
    TInt value( KZero );
    CTestIntegerSettingItem* mIntegerItem = new( ELeave ) CTestIntegerSettingItem( KOne, value );
    CleanupStack::PushL( mIntegerItem );
    STIF_ASSERT_NOT_NULL( mIntegerItem );
    CleanupStack::PopAndDestroy( mIntegerItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListIntegerSetItemDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListIntegerSetItemDestructorL( CStifItemParser& /*aItem*/ )
    {
    TInt value( KZero );
    CTestIntegerSettingItem* mIntegerItem = new( ELeave ) CTestIntegerSettingItem( KOne, value );
    CleanupStack::PushL( mIntegerItem );
    CleanupStack::PopAndDestroy( mIntegerItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListIntegerSetItemStoreLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListIntegerSetItemStoreLL( CStifItemParser& /*aItem*/ )
    {
    TInt value( KOne );
    CTestIntegerSettingItem* mIntegerItem = new( ELeave ) CTestIntegerSettingItem( KOne, value );
    CleanupStack::PushL( mIntegerItem );
    
    TInt externvalue = mIntegerItem->DoExternalValueRef();
    STIF_ASSERT_EQUALS( KOne, externvalue );
    
    mIntegerItem->StoreL();
    externvalue = mIntegerItem->DoExternalValueRef();
    STIF_ASSERT_EQUALS( KZero, externvalue );
    
    CleanupStack::PopAndDestroy( mIntegerItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListIntegerSetItemLoadLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListIntegerSetItemLoadLL( CStifItemParser& /*aItem*/ )
    {
    TInt value( KOne );
    CTestIntegerSettingItem* mIntegerItem = new( ELeave ) CTestIntegerSettingItem( KOne, value );
    CleanupStack::PushL( mIntegerItem );
    
    TInt mInternalvalue = mIntegerItem->DoInternalValueRef();
    STIF_ASSERT_EQUALS( KZero, mInternalvalue );
    
    value = KThree;
    mIntegerItem->DoSetExternalValue( value );
    mIntegerItem->LoadL();
    mInternalvalue = mIntegerItem->DoInternalValueRef();
    STIF_ASSERT_EQUALS( KThree, mInternalvalue );
    
    CleanupStack::PopAndDestroy( mIntegerItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListIntegerSetItemSettingTextLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListIntegerSetItemSettingTextLL( CStifItemParser& /*aItem*/ )
    {
    TInt value( KOne );
    CTestIntegerSettingItem* mIntegerItem = new( ELeave ) CTestIntegerSettingItem( KOne, value );
    CleanupStack::PushL( mIntegerItem );
    
    mIntegerItem->DoCompleteConstructionL();
    mIntegerItem->LoadL();
    TBuf< KBufSize > text = mIntegerItem->SettingTextL();
    STIF_ASSERT_NOT_NULL( &text );
    
    CleanupStack::PopAndDestroy( mIntegerItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListIntegerSetItemCompleteConstructionLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListIntegerSetItemCompleteConstructionLL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesItemListIntegerSetItemSettingTextLL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListIntegerSetItemInternalValueRefL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListIntegerSetItemInternalValueRefL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesItemListIntegerSetItemLoadLL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListIntegerSetItemExternalValueRefL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListIntegerSetItemExternalValueRefL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesItemListIntegerSetItemStoreLL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListIntegerSetItemSetExternalValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListIntegerSetItemSetExternalValueL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesItemListIntegerSetItemLoadLL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListIntegerEdwinConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListIntegerEdwinConstructorL( CStifItemParser& /*aItem*/ )
    {
    TInt value( KOne );
    CAknIntegerEdwinSettingItem* mIntegerItem = new( ELeave ) CAknIntegerEdwinSettingItem( KOne, value );
    CleanupStack::PushL( mIntegerItem );
    STIF_ASSERT_NOT_NULL( mIntegerItem );
    CleanupStack::PopAndDestroy( mIntegerItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListIntegerEdwinEditItemLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListIntegerEdwinEditItemLL( CStifItemParser& /*aItem*/ )
    {
    TInt value( KOne );
    CAknIntegerEdwinSettingItem* mIntegerEdwin = new( ELeave ) CAknIntegerEdwinSettingItem( KOne, value );
    CleanupStack::PushL( mIntegerEdwin);
    mIntegerEdwin->LoadL();
    
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( KThree );
    
    TBuf< KBufSize > buffer( KTestString );
    mIntegerEdwin->SetEmptyItemTextL( buffer );
    mIntegerEdwin->ConstructL( ETrue, KOne, buffer, mIcons, R_INTEGER_SETTING_PAGE,
        EAknCtIntegerEdwin, R_INTEGER_CONTROL );
    
    mIntegerEdwin->EditItemL( ETrue );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListPasswordConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListPasswordConstructorL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > password( KOldPassword );
    CAknPasswordSettingItem* passwordItem = new( ELeave ) CAknPasswordSettingItem( KOne, CAknPasswordSettingItem::ENumeric, password );
    CleanupStack::PushL( passwordItem );
    STIF_ASSERT_NOT_NULL( passwordItem );
    CleanupStack::PopAndDestroy( passwordItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListPasswordSettingTextLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListPasswordSettingTextLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > password( KOldPassword );
    CTestPasswordSettingItem* passwordItem = new( ELeave ) CTestPasswordSettingItem( KOne, CAknPasswordSettingItem::ENumeric, password );
    CleanupStack::PushL( passwordItem );
    
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( KThree );
    
    TBuf< KBufSize > buffer( KTestString );
    passwordItem->SetEmptyItemTextL( buffer );
    passwordItem->ConstructL( ETrue, KOne, buffer, mIcons, R_NUMERIC_PASSWORD_SETTING_PAGE,
        EAknCtNumericSecretEditor, R_NUMERIC_PASSWORD_CONTROL );
    
    TBuf< KBufSize > returntext = passwordItem->SettingTextL();
    STIF_ASSERT_NOT_NULL( &returntext );
    
    passwordItem->EditItemL( ETrue );
    
    returntext = passwordItem->SettingTextL();
    STIF_ASSERT_NOT_NULL( &returntext );
    
    passwordItem->DoCompleteConstructionL();
    
    returntext = passwordItem->SettingTextL();
    STIF_ASSERT_NOT_NULL( &returntext );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListPasswordEditItemLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListPasswordEditItemLL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesItemListPasswordSettingTextLL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListPasswordCompleteConstructionLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListPasswordCompleteConstructionLL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesItemListPasswordSettingTextLL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListVolumeConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListVolumeConstructorL( CStifItemParser& /*aItem*/ )
    {
    TInt extralvolume( KZero );
    CAknVolumeSettingItem* volumeItem = new( ELeave )CAknVolumeSettingItem( KOne, extralvolume );
    CleanupStack::PushL( volumeItem );
    STIF_ASSERT_NOT_NULL( volumeItem );
    CleanupStack::PopAndDestroy( volumeItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListVolumeStoreLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListVolumeStoreLL( CStifItemParser& /*aItem*/ )
    {
    TInt extralvolume( KThree );
    CTestVolumeSettingItem* volumeItem = new( ELeave )CTestVolumeSettingItem( KOne, extralvolume );
    CleanupStack::PushL( volumeItem );
    
    volumeItem->StoreL();
    volumeItem->LoadL();
    
    TInt mInternalVolume = volumeItem->DoInternalVolumeValue();
    STIF_ASSERT_EQUALS( KZero, mInternalVolume );
    
    CleanupStack::PopAndDestroy( volumeItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListVolumeLoadLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListVolumeLoadLL( CStifItemParser& /*aItem*/ )
    {
    TInt extralvolume( KThree );
    CTestVolumeSettingItem* volumeItem = new( ELeave )CTestVolumeSettingItem( KOne, extralvolume );
    CleanupStack::PushL( volumeItem );
    
    volumeItem->LoadL();
    
    TInt mInternalVolume = volumeItem->DoInternalVolumeValue();
    STIF_ASSERT_EQUALS( KThree, mInternalVolume );
    
    CleanupStack::PopAndDestroy( volumeItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListVolumeSettingTextLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListVolumeSettingTextLL( CStifItemParser& /*aItem*/ )
    {
    TInt extralvolume( KThree );
    CAknVolumeSettingItem* volumeItem = new( ELeave )CAknVolumeSettingItem( KOne, extralvolume );
    CleanupStack::PushL( volumeItem );
    
    TBuf< KBufSize > returnText = volumeItem->SettingTextL();
    TBuf< KBufSize > comparetext( KSpace );
    STIF_ASSERT_EQUALS( comparetext, returnText );
    
    CleanupStack::PopAndDestroy( volumeItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListVolumeEditItemLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListVolumeEditItemLL( CStifItemParser& /*aItem*/ )
    {
    TInt extralvolume( KThree );
    CAknVolumeSettingItem* volumeItem = new( ELeave )CAknVolumeSettingItem( KOne, extralvolume );
    CleanupStack::PushL( volumeItem );
    
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( KThree );
    
    TBuf< KBufSize > buffer( KTestString );
    volumeItem->SetEmptyItemTextL( buffer );
    volumeItem->ConstructL( ETrue, KOne, buffer, mIcons, R_VOLUME_SETTING_PAGE,
        EAknCtVolumeControl, R_VOLUME_CONTROL );
    
    volumeItem->EditItemL( ETrue );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListVolumeInternalVolumeValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListVolumeInternalVolumeValueL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesItemListVolumeLoadLL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListVolumeCreateBitmapLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListVolumeCreateBitmapLL( CStifItemParser& /*aItem*/ )
    {
    TInt extralvolume( KThree );
    CTestVolumeSettingItem* volumeItem = new( ELeave )CTestVolumeSettingItem( KOne, extralvolume );
    CleanupStack::PushL( volumeItem );
    
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( KThree );
    
    TBuf< KBufSize > buffer( KTestString );
    volumeItem->SetEmptyItemTextL( buffer );
    volumeItem->ConstructL( ETrue, KOne, buffer, mIcons, R_EXAMPLE_SETTING_PAGE,
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL );
    
    CFbsBitmap* returnBitmap = volumeItem->DoCreateBitmapL();
    STIF_ASSERT_NOT_NULL( returnBitmap );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpaegsItemListSliderConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpaegsItemListSliderConstructL( CStifItemParser& /*aItem*/ )
    {
    TInt sliderValue = KTen;
    CAknSliderSettingItem* sliderItem = new( ELeave ) CAknSliderSettingItem( KOne, sliderValue );
    CleanupStack::PushL( sliderItem );
    STIF_ASSERT_NOT_NULL( sliderItem );
    CleanupStack::PopAndDestroy( sliderItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListSliderStoreLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListSliderStoreLL( CStifItemParser& /*aItem*/ )
    {
    TInt sliderValue = KTen;
    CTestSliderSettingItem* sliderItem = new( ELeave ) CTestSliderSettingItem( KOne, sliderValue );
    CleanupStack::PushL( sliderItem );
    
    TInt mInternalSliderValue = sliderItem->DoInternalSliderValue();
    STIF_ASSERT_EQUALS( KZero, mInternalSliderValue );
    
    sliderItem->LoadL();
    mInternalSliderValue = sliderItem->DoInternalSliderValue();
    STIF_ASSERT_EQUALS( KTen, mInternalSliderValue );
    
    sliderItem->StoreL();
    sliderItem->LoadL();
    mInternalSliderValue = sliderItem->DoInternalSliderValue();
    STIF_ASSERT_EQUALS( KTen, mInternalSliderValue );
    
    CleanupStack::PopAndDestroy( sliderItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListSliderLoadLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListSliderLoadLL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesItemListSliderStoreLL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListSliderSettingTextLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListSliderSettingTextLL( CStifItemParser& /*aItem*/ )
    {
    TInt sliderValue = KTen;
    CAknSliderSettingItem* sliderItem = new( ELeave ) CAknSliderSettingItem( KOne, sliderValue );
    CleanupStack::PushL( sliderItem );
    
    TBuf< KBufSize > buffer( KSpace );
    TBuf< KBufSize > text = sliderItem->SettingTextL();
    STIF_ASSERT_EQUALS( buffer, text );
    
    CleanupStack::PopAndDestroy( sliderItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListSliderEditItemLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListSliderEditItemLL( CStifItemParser& /*aItem*/ )
    {
    TInt sliderValue = KTen;
    CAknSliderSettingItem* sliderItem = new( ELeave ) CAknSliderSettingItem( KOne, sliderValue );
    CleanupStack::PushL( sliderItem );
    
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( KThree );
    
    TBuf< KBufSize > buffer( KTestString );
    sliderItem->SetEmptyItemTextL( buffer );
    sliderItem->ConstructL( ETrue, KOne, buffer, mIcons, R_SLIDER_SETTING_PAGE,
        EAknCtSlider, R_SLIDER_CONTROL );
    
    sliderItem->EditItemL( ETrue );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListSliderCreateSettingPageLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListSliderCreateSettingPageLL( CStifItemParser& /*aItem*/ )
    {
    TInt sliderValue = KTen;
    CTestSliderSettingItem* sliderItem = new( ELeave ) CTestSliderSettingItem( KOne, sliderValue );
    CleanupStack::PushL( sliderItem );
    
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( KThree );
    
    TBuf< KBufSize > buffer( KTestString );
    sliderItem->SetEmptyItemTextL( buffer );
    sliderItem->ConstructL( ETrue, KOne, buffer, mIcons, R_SLIDER_SETTING_PAGE,
        EAknCtSlider, R_SLIDER_CONTROL );
    
    CAknSettingPage* dialog = sliderItem->DoCreateSettingPageL();
    STIF_ASSERT_NOT_NULL( dialog );
    dialog = NULL;
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListSliderCreateAndExecuteSettingPageLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListSliderCreateAndExecuteSettingPageLL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesItemListSliderEditItemLL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListSliderInternalSliderValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListSliderInternalSliderValueL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesItemListSliderStoreLL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListSliderCreateBitmapLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListSliderCreateBitmapLL( CStifItemParser& /*aItem*/ )
    {
    TInt sliderValue = KTen;
    CTestSliderSettingItem* sliderItem = new( ELeave ) CTestSliderSettingItem( KOne, sliderValue );
    CleanupStack::PushL( sliderItem );
    
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( KThree );
    
    TBuf< KBufSize > buffer( KTestString );
    sliderItem->SetEmptyItemTextL( buffer );
    sliderItem->ConstructL( ETrue, KOne, buffer, mIcons, R_SLIDER_SETTING_PAGE,
        EAknCtSlider, R_SLIDER_CONTROL );
    
    CFbsBitmap* returnBitmap = sliderItem->DoCreateBitmapL();
    STIF_ASSERT_NOT_NULL( returnBitmap );
    returnBitmap = NULL;
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListTimeOrDateConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListTimeOrDateConstructorL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KTimeSize > timevalue( KTime );
    TTime time( timevalue );
    CAknTimeOrDateSettingItem* timeOrDateItem = new( ELeave ) CAknTimeOrDateSettingItem( KOne,
            CAknTimeOrDateSettingItem::EDate, time );
    CleanupStack::PushL( timeOrDateItem );
    STIF_ASSERT_NOT_NULL( timeOrDateItem );
    CleanupStack::PopAndDestroy( timeOrDateItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListTimeOrDateDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListTimeOrDateDestructorL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KTimeSize > timevalue( KTime );
    TTime time( timevalue );
    CAknTimeOrDateSettingItem* timeOrDateItem = new( ELeave ) CAknTimeOrDateSettingItem( KOne,
            CAknTimeOrDateSettingItem::EDate, time );
    CleanupStack::PushL( timeOrDateItem );
    CleanupStack::PopAndDestroy( timeOrDateItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListTimeOrDateCompleteConstructionLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListTimeOrDateCompleteConstructionLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KTimeSize > timevalue( KTime );
    TTime time( timevalue );
    CAknTimeOrDateSettingItem* dateItem = new( ELeave ) CAknTimeOrDateSettingItem( KOne,
            CAknTimeOrDateSettingItem::EDate, time );
    CleanupStack::PushL( dateItem );
    
    dateItem->CompleteConstructionL();
    
    CAknTimeOrDateSettingItem* timeItem = new( ELeave ) CAknTimeOrDateSettingItem( KOne,
            CAknTimeOrDateSettingItem::ETime, time );
    CleanupStack::PushL( timeItem );
    
    timeItem->CompleteConstructionL();
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListTimeOrDateStoreLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListTimeOrDateStoreLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KTimeSize > timevalue( KTime );
    TTime time( timevalue );
    CAknTimeOrDateSettingItem* timeOrDateItem = new( ELeave ) CAknTimeOrDateSettingItem( KOne,
            CAknTimeOrDateSettingItem::EDate, time );
    CleanupStack::PushL( timeOrDateItem );
    
    timeOrDateItem->CompleteConstructionL();
    
    timeOrDateItem->LoadL();
    TBuf< KBufSize > value = timeOrDateItem->SettingTextL();
    STIF_ASSERT_NOT_NULL( &value );
    
    timeOrDateItem->StoreL();
    timeOrDateItem->LoadL();
    value = timeOrDateItem->SettingTextL();
    STIF_ASSERT_NOT_NULL( &value );
    
    CleanupStack::PopAndDestroy( timeOrDateItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListTimeOrDateLoadLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListTimeOrDateLoadLL( CStifItemParser& aItem )
    {
    TInt err =  TestSettingPagesItemListTimeOrDateStoreLL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListTimeOrDateSettingTextLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListTimeOrDateSettingTextLL( CStifItemParser& aItem )
    {
    TInt err =  TestSettingPagesItemListTimeOrDateStoreLL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListTimeOrDateEditItemLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListTimeOrDateEditItemLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KTimeSize > timevalue( KTime );
    TTime time( timevalue );
    CAknTimeOrDateSettingItem* dateItem = new( ELeave ) CAknTimeOrDateSettingItem( KOne,
            CAknTimeOrDateSettingItem::EDate, time );
    CleanupStack::PushL( dateItem );
    
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( KThree );
    
    TBuf< KBufSize > buffer( KTestString );
    dateItem->SetEmptyItemTextL( buffer );
    dateItem->ConstructL( ETrue, KOne, buffer, mIcons, R_DATE_SETTING_PAGE,
        EEikCtDateEditor, R_DATE_CONTROL );
    dateItem->CompleteConstructionL();
    
    dateItem->EditItemL( ETrue );
    
    CleanupStack::PopAndDestroy( KTwo );
    
    CAknTimeOrDateSettingItem* timeItem = new( ELeave ) CAknTimeOrDateSettingItem( KOne,
            CAknTimeOrDateSettingItem::ETime, time );
    CleanupStack::PushL( timeItem );

    CArrayPtr<CGulIcon>* mIconstwo = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIconstwo); 
    
    CFbsBitmap* bitmaptwo = NULL;
    CFbsBitmap* masktwo = NULL;

    AknIconUtils::CreateIconLC( bitmaptwo, masktwo, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcontwo = CGulIcon::NewL( bitmaptwo, masktwo );
    CleanupStack::PushL( mIcontwo );
    mIconstwo->AppendL( mIcontwo );
    CleanupStack::Pop( KThree );
    timeItem->SetEmptyItemTextL( buffer );
    timeItem->ConstructL( ETrue, KOne, buffer, mIcons, R_TIME_SETTING_PAGE,
        EEikCtTimeEditor, R_TIME_CONTROL );
    timeItem->CompleteConstructionL();
    
    timeItem->EditItemL( ETrue );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListTimeOrDateSetTimeFormatStringLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListTimeOrDateSetTimeFormatStringLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KTimeSize > timevalue( KTime );
    TTime time( timevalue );
    CAknTimeOrDateSettingItem* dateItem = new( ELeave ) CAknTimeOrDateSettingItem( KOne,
            CAknTimeOrDateSettingItem::EDate, time );
    CleanupStack::PushL( dateItem );
    dateItem->CompleteConstructionL();
    TPtrC returnTime = dateItem->TimeFormatString();
    STIF_ASSERT_NOT_NULL( &returnTime );

    TBuf< KTimeSize > secondTime( KSecondTime );
    dateItem->SetTimeFormatStringL( secondTime );
    dateItem->TimeFormatString();
    
    CleanupStack::PopAndDestroy( dateItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListTimeOrDateTimeFormatStringL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListTimeOrDateTimeFormatStringL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesItemListTimeOrDateSetTimeFormatStringLL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListOffSetConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListOffSetConstructorL( CStifItemParser& /*aItem*/ )
    {
    TTimeIntervalSeconds timeInterValue = KTimeIntervalue;
    CAknTimeOffsetSettingItem* offSetItem = new( ELeave ) CAknTimeOffsetSettingItem( KOne, timeInterValue );
    CleanupStack::PushL( offSetItem );
    STIF_ASSERT_NOT_NULL( offSetItem );
    CleanupStack::PopAndDestroy( offSetItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListOffSetDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListOffSetDestructorL( CStifItemParser& /*aItem*/ )
    {
    TTimeIntervalSeconds timeInterValue = KTimeIntervalue;
    CAknTimeOffsetSettingItem* offSetItem = new( ELeave ) CAknTimeOffsetSettingItem( KOne, timeInterValue );
    CleanupStack::PushL( offSetItem );
    CleanupStack::PopAndDestroy( offSetItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListOffSetCompleteConstructionLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListOffSetCompleteConstructionLL( CStifItemParser& /*aItem*/ )
    {
    TTimeIntervalSeconds timeInterValue = KTimeIntervalue;
    CAknTimeOffsetSettingItem* offSetItem = new( ELeave ) CAknTimeOffsetSettingItem( KOne, timeInterValue );
    CleanupStack::PushL( offSetItem );
    offSetItem->CompleteConstructionL();
    CleanupStack::PopAndDestroy( offSetItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListOffSetStoreLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListOffSetStoreLL( CStifItemParser& /*aItem*/ )
    {
    TTimeIntervalSeconds timeInterValue = KTimeIntervalue;
    CAknTimeOffsetSettingItem* offSetItem = new( ELeave ) CAknTimeOffsetSettingItem( KOne, timeInterValue );
    CleanupStack::PushL( offSetItem );
    offSetItem->StoreL();
    CleanupStack::PopAndDestroy( offSetItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListOffSetLoadLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListOffSetLoadLL( CStifItemParser& /*aItem*/ )
    {
    TTimeIntervalSeconds timeInterValue = KTimeIntervalue;
    CAknTimeOffsetSettingItem* offSetItem = new( ELeave ) CAknTimeOffsetSettingItem( KOne, timeInterValue );
    CleanupStack::PushL( offSetItem );
    offSetItem->LoadL();
    CleanupStack::PopAndDestroy( offSetItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListOffSetSettingTextLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListOffSetSettingTextLL( CStifItemParser& /*aItem*/ )
    {
    TTimeIntervalSeconds timeInterValue = KTimeIntervalue;
    CAknTimeOffsetSettingItem* offSetItem = new( ELeave ) CAknTimeOffsetSettingItem( KOne, timeInterValue );
    CleanupStack::PushL( offSetItem );
    offSetItem->CompleteConstructionL();
    offSetItem->SettingTextL();
    CleanupStack::PopAndDestroy( offSetItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListOffSetEditItemLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListOffSetEditItemLL( CStifItemParser& /*aItem*/ )
    {
    TTimeIntervalSeconds timeInterValue = KTimeIntervalue;
    CAknTimeOffsetSettingItem* offSetItem = new( ELeave ) CAknTimeOffsetSettingItem( KOne, timeInterValue );
    CleanupStack::PushL( offSetItem );
    offSetItem->CompleteConstructionL();
        
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( KThree );
    
    TBuf< KBufSize > buffer( KTestString );
    offSetItem->SetEmptyItemTextL( buffer );
    offSetItem->ConstructL( ETrue, KOne, buffer, mIcons, R_TIMEOFFSET_SETTING_PAGE,
        EEikCtTimeOffsetEditor, R_TIMEOFFSET_CONTROL );
    
    offSetItem->EditItemL( ETrue );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListOffSetSetTimeFormatStringLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListOffSetSetTimeFormatStringLL( CStifItemParser& /*aItem*/ )
    {
    TTimeIntervalSeconds timeInterValue = KTimeIntervalue;
    CAknTimeOffsetSettingItem* offSetItem = new( ELeave ) CAknTimeOffsetSettingItem( KOne, timeInterValue );
    CleanupStack::PushL( offSetItem );
    offSetItem->CompleteConstructionL();
    
    TBuf< KTimeSize > timeValue( KTime );
    offSetItem->SetTimeFormatStringL( timeValue );
    offSetItem->TimeFormatString();
    
    CleanupStack::PopAndDestroy( offSetItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListOffSetTimeFormatStringL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListOffSetTimeFormatStringL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesItemListOffSetSetTimeFormatStringLL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListIpFieldConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListIpFieldConstructorL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress;
    mAddress.SetAddress( INET_ADDR( KTen, KTen, KTen, KTen ));
    CAknIpFieldSettingItem* mIpFieldItem = new( ELeave ) CAknIpFieldSettingItem( KOne, mAddress );
    CleanupStack::PushL( mIpFieldItem );
    STIF_ASSERT_NOT_NULL( mIpFieldItem );
    CleanupStack::PopAndDestroy( mIpFieldItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListIpFieldDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListIpFieldDestructorL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress;
    mAddress.SetAddress( INET_ADDR( KTen, KTen, KTen, KTen ));
    CAknIpFieldSettingItem* mIpFieldItem = new( ELeave ) CAknIpFieldSettingItem( KOne, mAddress );
    CleanupStack::PushL( mIpFieldItem );
    CleanupStack::PopAndDestroy( mIpFieldItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListIpFieldCompleteConstructionLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListIpFieldCompleteConstructionLL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress;
    mAddress.SetAddress( INET_ADDR( KTen, KTen, KTen, KTen ));
    CAknIpFieldSettingItem* mIpFieldItem = new( ELeave ) CAknIpFieldSettingItem( KOne, mAddress );
    CleanupStack::PushL( mIpFieldItem );
    mIpFieldItem->CompleteConstructionL();
    CleanupStack::PopAndDestroy( mIpFieldItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListIpFieldStoreLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListIpFieldStoreLL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress;
    mAddress.SetAddress( INET_ADDR( KTen, KTen, KTen, KTen ));
    CAknIpFieldSettingItem* mIpFieldItem = new( ELeave ) CAknIpFieldSettingItem( KOne, mAddress );
    CleanupStack::PushL( mIpFieldItem );
    
    mIpFieldItem->CompleteConstructionL();
    
    TBuf< KBufSize > compareIpAdd( KNullIpAddress );
    TBuf< KBufSize > mIpAddText = mIpFieldItem->SettingTextL();
    STIF_ASSERT_EQUALS( compareIpAdd, mIpAddText );
    
    mIpFieldItem->LoadL();
    mIpFieldItem->StoreL();
    mAddress.Output( compareIpAdd );
    mIpAddText = mIpFieldItem->SettingTextL();
    STIF_ASSERT_EQUALS( compareIpAdd, mIpAddText );
    
    CleanupStack::PopAndDestroy( mIpFieldItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListIpFieldLoadLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListIpFieldLoadLL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesItemListIpFieldStoreLL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListIpFieldSettingTextLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListIpFieldSettingTextLL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesItemListIpFieldStoreLL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListIpFieldEditItemLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListIpFieldEditItemLL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress;
    mAddress.SetAddress( INET_ADDR( KIpAddFirstNumber, KIpAddSecondNumber, KZero, KOne ));
    CAknIpFieldSettingItem* mIpFieldItem = new( ELeave ) CAknIpFieldSettingItem( KOne, mAddress );
    CleanupStack::PushL( mIpFieldItem );
    mIpFieldItem->CompleteConstructionL();
    
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( KThree );
    
    TBuf< KBufSize > buffer( KTestString );
    mIpFieldItem->SetEmptyItemTextL( buffer );
    mIpFieldItem->ConstructL( ETrue, KOne, buffer, mIcons, R_IP_ADDRESS_SETTING_PAGE,
        EAknCtIpFieldEditor, R_IP_CONTROL );
    
    mIpFieldItem->EditItemL( ETrue );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEnumeratedIBConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEnumeratedIBConstructorL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CAknEnumeratedItemBase* Enumerate = new( ELeave ) CAknEnumeratedItemBase( KOne, &buffer );
    CleanupStack::PushL( Enumerate );
    STIF_ASSERT_NOT_NULL( Enumerate );
    CleanupStack::PopAndDestroy( Enumerate );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEnumeratedIBDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEnumeratedIBDestructorL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CAknEnumeratedItemBase* Enumerate = new( ELeave ) CAknEnumeratedItemBase( KOne, &buffer );
    CleanupStack::PushL( Enumerate );
    CleanupStack::PopAndDestroy( Enumerate );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEnumeratedIBEnumerationValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEnumeratedIBEnumerationValueL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CAknEnumeratedItemBase* Enumerate = new( ELeave ) CAknEnumeratedItemBase( KOne, &buffer );
    CleanupStack::PushL( Enumerate );
    
    TInt value = Enumerate->EnumerationValue();
    STIF_ASSERT_EQUALS( KOne, value );
    
    Enumerate->SetEnumerationValue( KThree );
    value = Enumerate->EnumerationValue();
    STIF_ASSERT_EQUALS( KThree, value );
    
    CleanupStack::PopAndDestroy( Enumerate );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEnumeratedIBSetEnumerationValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEnumeratedIBSetEnumerationValueL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesItemListEnumeratedIBEnumerationValueL( aItem );
    return err;
    }


// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEnumeratedIBValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEnumeratedIBValueL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CAknEnumeratedItemBase* Enumerate = new( ELeave ) CAknEnumeratedItemBase( KOne, &buffer );
    CleanupStack::PushL( Enumerate );
    
    Enumerate->Value();
    Enumerate->SetValue( &buffer );
    
    CleanupStack::PopAndDestroy( Enumerate );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEnumeratedIBSetValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEnumeratedIBSetValueL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesItemListEnumeratedIBValueL( aItem );
    return err;
    }
    

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEMTDItemConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEMTDItemConstructorL( CStifItemParser& /*aItem*/ )
    {
    typedef CAknEnumeratedItem<HBufC> CAknEnumeratedTextExt;
    TBuf< KBufSize > buffer( KTestString );
    HBufC* hbuf = buffer.AllocL();
    CleanupStack::PushL( hbuf );
    CAknEnumeratedTextExt* enumerate = new( ELeave ) CAknEnumeratedTextExt( KOne, hbuf );
    CleanupStack::PushL( enumerate );
    STIF_ASSERT_NOT_NULL( enumerate );
    CleanupStack::PopAndDestroy( enumerate );
    CleanupStack::Pop( hbuf );
    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEMTDItemDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEMTDItemDestructorL( CStifItemParser& /*aItem*/ )
    {
    typedef CAknEnumeratedItem<HBufC> CAknEnumeratedTextExt;
    TBuf< KBufSize > buffer( KTestString );
    HBufC* hbuf = buffer.AllocL();
    CleanupStack::PushL( hbuf );
    CAknEnumeratedTextExt* enumerate = new( ELeave ) CAknEnumeratedTextExt( KOne, hbuf );
    CleanupStack::PushL( enumerate );
    CleanupStack::PopAndDestroy( enumerate );
    CleanupStack::Pop( hbuf );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEMTDItemValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEMTDItemValueL( CStifItemParser& /*aItem*/ )
    {
    typedef CAknEnumeratedItem<HBufC> CAknEnumeratedTextExt;
    TBuf< KBufSize > buffer( KTestString );
    HBufC* hbuf = buffer.AllocL();
    CleanupStack::PushL( hbuf );
    CAknEnumeratedTextExt* Enumerate = new( ELeave ) CAknEnumeratedTextExt( KOne, hbuf );
    CleanupStack::PushL( Enumerate );
    
    Enumerate->Value();
    Enumerate->SetValue( hbuf );
    CleanupStack::PopAndDestroy( Enumerate );
    CleanupStack::Pop( hbuf );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEMTDItemSetValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEMTDItemSetValueL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesItemListEMTDItemValueL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEnuredTxtConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEnuredTxtConstructorL( CStifItemParser& /*aItem*/ )
    {
    CAknEnumeratedTextSettingItem* textItem = 
        new( ELeave ) CAknEnumeratedTextSettingItem( R_ENUMTEXT_SETTING_PAGE );
    CleanupStack::PushL( textItem );
    STIF_ASSERT_NOT_NULL( textItem );
    CleanupStack::PopAndDestroy( textItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEnuredTxtDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEnuredTxtDestructorL( CStifItemParser& /*aItem*/ )
    {
    CAknEnumeratedTextSettingItem* textItem = 
        new( ELeave ) CAknEnumeratedTextSettingItem( R_ENUMTEXT_SETTING_PAGE );
    CleanupStack::PushL( textItem );
    CleanupStack::PopAndDestroy( textItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEnuredTxtCompleteConstructionLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEnuredTxtCompleteConstructionLL( CStifItemParser& /*aItem*/ )
    {
    CTestEnumeratedTextSettingItem* textItem = 
        new( ELeave ) CTestEnumeratedTextSettingItem( R_ENUMTEXT_SETTING_PAGE );
    CleanupStack::PushL( textItem );

    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( KThree );
    
    TBuf< KBufSize > buffer( KTestString );
    textItem->SetEmptyItemTextL( buffer );
    textItem->ConstructL( ETrue, KOne, buffer, mIcons, R_ENUMTEXT_SETTING_PAGE,
        EAknCtPopupSettingList, R_POPUP_SETTING_LIST_CONTROL, R_POPUP_SETTING_LIST );
        
    textItem->DoCompleteConstructionL();
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEnuredTxtEnuredTxtArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEnuredTxtEnuredTxtArrayL( CStifItemParser& /*aItem*/ )
    {
    CTestEnumeratedTextSettingItem* textItem = 
        new( ELeave ) CTestEnumeratedTextSettingItem( R_ENUMTEXT_SETTING_PAGE );
    CleanupStack::PushL( textItem );
    
    CArrayPtr<CAknEnumeratedText>* array = textItem->EnumeratedTextArray();
    STIF_ASSERT_NULL( array );
    
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( KThree );
    
    TBuf< KBufSize > buffer( KTestString );
    textItem->SetEmptyItemTextL( buffer );
    textItem->ConstructL( ETrue, KOne, buffer, mIcons, R_ENUMTEXT_SETTING_PAGE,
        EAknCtPopupSettingList, R_POPUP_SETTING_LIST_CONTROL, R_POPUP_SETTING_LIST );
        
    array = textItem->EnumeratedTextArray();
    STIF_ASSERT_NOT_NULL( array );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEnuredTxtPoppedUpTextArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEnuredTxtPoppedUpTextArrayL( CStifItemParser& /*aItem*/ )
    {
    CTestEnumeratedTextSettingItem* textItem = 
        new( ELeave ) CTestEnumeratedTextSettingItem( R_ENUMTEXT_SETTING_PAGE );
    CleanupStack::PushL( textItem );
    
    CArrayPtr<HBufC>* array = textItem->PoppedUpTextArray();
    STIF_ASSERT_NULL( array );
    
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( KThree );
    
    TBuf< KBufSize > buffer( KTestString );
    textItem->SetEmptyItemTextL( buffer );
    textItem->ConstructL( ETrue, KOne, buffer, mIcons, R_ENUMTEXT_SETTING_PAGE,
        EAknCtPopupSettingList, R_POPUP_SETTING_LIST_CONTROL, R_POPUP_SETTING_LIST );
        
    array = textItem->PoppedUpTextArray();
    STIF_ASSERT_NOT_NULL( array );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEnuredTxtSetEnuredTxtArraysL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEnuredTxtSetEnuredTxtArraysL( CStifItemParser& /*aItem*/ )
    {
    CTestEnumeratedTextSettingItem* textItem = 
        new( ELeave ) CTestEnumeratedTextSettingItem( R_ENUMTEXT_SETTING_PAGE );
    CleanupStack::PushL( textItem );
    
    CArrayPtr<CAknEnumeratedText>* enuArray = textItem->EnumeratedTextArray();
    STIF_ASSERT_NULL( enuArray );
    
    CArrayPtr<HBufC>* popArray = textItem->PoppedUpTextArray();
    STIF_ASSERT_NULL( popArray );
    
    TBuf< KBufSize > buffer( KTestString );
    HBufC* buf = buffer.AllocL();
    CleanupStack::PushL( buf );
    HBufC* buf1 = buffer.AllocL();
    CleanupStack::PushL( buf1 );
    CAknEnumeratedText* txt = new( ELeave ) CAknEnumeratedText( KOne, buf );
    CleanupStack::PushL( txt );
    
    CArrayPtr<CAknEnumeratedText>* enumeratedText = new (ELeave) CArrayPtrFlat<CAknEnumeratedText>( KFive );
    CleanupStack::PushL( enumeratedText );
    CArrayPtr<HBufC>* popTxt = new (ELeave) CArrayPtrFlat<HBufC>( KFive );
    CleanupStack::PushL( popTxt );
    
    enumeratedText->AppendL( txt );
    popTxt->AppendL( buf1 );
    
    textItem->SetEnumeratedTextArrays( enumeratedText, popTxt );
    
    enuArray = textItem->EnumeratedTextArray();
    STIF_ASSERT_NOT_NULL( enuArray );
    
    popArray = textItem->PoppedUpTextArray();
    STIF_ASSERT_NOT_NULL( popArray );
    
    CleanupStack::Pop( KFive );
    CleanupStack::PopAndDestroy( textItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEnuredTxtHandleTextArrayUpdateLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEnuredTxtHandleTextArrayUpdateLL( CStifItemParser& /*aItem*/ )
    {
    CTestEnumeratedTextSettingItem* textItem = 
        new( ELeave ) CTestEnumeratedTextSettingItem( R_ENUMTEXT_SETTING_PAGE );
    CleanupStack::PushL( textItem );
    
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( KThree );
    
    TBuf< KBufSize > buffer( KTestString );
    textItem->SetEmptyItemTextL( buffer );
    textItem->ConstructL( ETrue, KOne, buffer, mIcons, R_ENUMTEXT_SETTING_PAGE,
        EAknCtPopupSettingList, R_POPUP_SETTING_LIST_CONTROL, R_POPUP_SETTING_LIST );
    
    textItem->HandleTextArrayUpdateL();
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEnuredTxtNumberOfItemsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEnuredTxtNumberOfItemsL( CStifItemParser& /*aItem*/ )
    {
    CTestEnumeratedTextSettingItem* textItem = 
        new( ELeave ) CTestEnumeratedTextSettingItem( R_ENUMTEXT_SETTING_PAGE );
    CleanupStack::PushL( textItem );
    
    TInt number = textItem->NumberOfItems();
    STIF_ASSERT_EQUALS( KZero, number );
    
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( KThree );
    
    TBuf< KBufSize > buffer( KTestString );
    textItem->SetEmptyItemTextL( buffer );
    textItem->ConstructL( ETrue, KOne, buffer, mIcons, R_ENUMTEXT_SETTING_PAGE,
        EAknCtPopupSettingList, R_POPUP_SETTING_LIST_CONTROL, R_POPUP_SETTING_LIST );
    
    number = textItem->NumberOfItems();
    STIF_ASSERT_EQUALS( KThree, number );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEnuredTxtIndexFromValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEnuredTxtIndexFromValueL( CStifItemParser& /*aItem*/ )
    {
    CTestEnumeratedTextSettingItem* textItem = 
        new( ELeave ) CTestEnumeratedTextSettingItem( R_ENUMTEXT_SETTING_PAGE );
    CleanupStack::PushL( textItem );
    
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( KThree );
    
    TBuf< KBufSize > buffer( KTestString );
    textItem->SetEmptyItemTextL( buffer );
    textItem->ConstructL( ETrue, KOne, buffer, mIcons, R_ENUMTEXT_SETTING_PAGE,
        EAknCtPopupSettingList, R_POPUP_SETTING_LIST_CONTROL, R_POPUP_SETTING_LIST );
    
    TInt number = textItem->IndexFromValue( KOne );
    STIF_ASSERT_NOT_EQUALS( KMinusOne, number );
    
    number = textItem->IndexFromValue( KTwo );
    STIF_ASSERT_NOT_EQUALS( KMinusOne, number );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEnuredTxtSetSettingPageTextLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEnuredTxtSetSettingPageTextLL( CStifItemParser& /*aItem*/ )
    {
    CTestEnumeratedTextSettingItem* textItem = 
        new( ELeave ) CTestEnumeratedTextSettingItem( R_ENUMTEXT_SETTING_PAGE );
    CleanupStack::PushL( textItem );
    
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( KThree );
    
    TBuf< KBufSize > buffer( KTestString );
    textItem->SetEmptyItemTextL( buffer );
    textItem->ConstructL( ETrue, KOne, buffer, mIcons, R_ENUMTEXT_SETTING_PAGE,
        EAknCtPopupSettingList, R_POPUP_SETTING_LIST_CONTROL, R_POPUP_SETTING_LIST );
    
    textItem->DoSetSettingPageTextL();
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEnuredTxtSettingPageTextArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEnuredTxtSettingPageTextArrayL( CStifItemParser& /*aItem*/ )
    {
    CTestEnumeratedTextSettingItem* textItem = 
        new( ELeave ) CTestEnumeratedTextSettingItem( R_ENUMTEXT_SETTING_PAGE );
    CleanupStack::PushL( textItem );
    
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( KThree );
    
    TBuf< KBufSize > buffer( KTestString );
    textItem->SetEmptyItemTextL( buffer );
    textItem->ConstructL( ETrue, KOne, buffer, mIcons, R_ENUMTEXT_SETTING_PAGE,
        EAknCtPopupSettingList, R_POPUP_SETTING_LIST_CONTROL, R_POPUP_SETTING_LIST );
    
    CDesCArray* settingArray = textItem->DoSettingPageTextArray();
    STIF_ASSERT_NULL( settingArray );
    
    textItem->DoSetSettingPageTextL();
    settingArray = textItem->DoSettingPageTextArray();
    STIF_ASSERT_NOT_NULL( settingArray );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEnurtdTxtPopConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEnurtdTxtPopConstructorL( CStifItemParser& /*aItem*/ )
    {
    TInt value = KZero;
    CAknEnumeratedTextPopupSettingItem* popupItem = new( ELeave ) CAknEnumeratedTextPopupSettingItem( R_ENUMTEXT_SETTING_PAGE, value );
    CleanupStack::PushL( popupItem );
    STIF_ASSERT_NOT_NULL( popupItem );
    CleanupStack::PopAndDestroy( popupItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEnurtdTxtPopDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEnurtdTxtPopDestructorL( CStifItemParser& /*aItem*/ )
    {
    TInt value = KZero;
    CAknEnumeratedTextPopupSettingItem* popupItem = new( ELeave ) CAknEnumeratedTextPopupSettingItem( R_ENUMTEXT_SETTING_PAGE, value );
    CleanupStack::PushL( popupItem );
    CleanupStack::PopAndDestroy( popupItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEnurtdTxtPopStoreLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEnurtdTxtPopStoreLL( CStifItemParser& /*aItem*/ )
    {
    TInt value = KZero;
    CAknEnumeratedTextPopupSettingItem* popupItem = new( ELeave ) CAknEnumeratedTextPopupSettingItem( R_ENUMTEXT_SETTING_PAGE, value );
    CleanupStack::PushL( popupItem );
    
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( KThree );
    
    TBuf< KBufSize > buffer( KTestString );
    popupItem->SetEmptyItemTextL( buffer );
    popupItem->ConstructL( ETrue, KOne, buffer, mIcons, R_ENUMTEXT_SETTING_PAGE,
        EAknCtPopupSettingList, R_POPUP_SETTING_LIST_CONTROL, R_POPUP_SETTING_LIST );
        
    popupItem->LoadL();
    popupItem->StoreL();
    popupItem->SettingTextL();
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEnurtdTxtPopLoadLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEnurtdTxtPopLoadLL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesItemListEnurtdTxtPopStoreLL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEnurtdTxtPopSettingTextLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEnurtdTxtPopSettingTextLL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesItemListEnurtdTxtPopStoreLL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEnurtdTxtPopEditItemLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEnurtdTxtPopEditItemLL( CStifItemParser& /*aItem*/ )
    {
    TInt value = KZero;
    CAknEnumeratedTextPopupSettingItem* popupItem = new( ELeave ) CAknEnumeratedTextPopupSettingItem( R_ENUMTEXT_SETTING_PAGE, value );
    CleanupStack::PushL( popupItem );
    
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( KThree );
    
    TBuf< KBufSize > buffer( KTestString );
    popupItem->SetEmptyItemTextL( buffer );
    popupItem->ConstructL( ETrue, KOne, buffer, mIcons, R_ENUMTEXT_SETTING_PAGE,
        EAknCtPopupSettingList, R_POPUP_SETTING_LIST_CONTROL, R_POPUP_SETTING_LIST );
    
    popupItem->EditItemL( ETrue );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEnurtdTxtPopEnumeratedTextArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEnurtdTxtPopEnumeratedTextArrayL( CStifItemParser& /*aItem*/ )
    {
    TInt value = KZero;
    CAknEnumeratedTextPopupSettingItem* popupItem = new( ELeave ) CAknEnumeratedTextPopupSettingItem( R_ENUMTEXT_SETTING_PAGE, value );
    CleanupStack::PushL( popupItem );
    
    CArrayPtr<CAknEnumeratedText>* enuArray = popupItem->EnumeratedTextArray();
    STIF_ASSERT_NULL( enuArray );
    
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( KThree );
    
    TBuf< KBufSize > buffer( KTestString );
    popupItem->SetEmptyItemTextL( buffer );
    popupItem->ConstructL( ETrue, KOne, buffer, mIcons, R_ENUMTEXT_SETTING_PAGE,
        EAknCtPopupSettingList, R_POPUP_SETTING_LIST_CONTROL, R_POPUP_SETTING_LIST );
    
    enuArray = popupItem->EnumeratedTextArray();
    STIF_ASSERT_NOT_NULL( enuArray );
    enuArray = NULL;
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEnurtdTxtPopPoppedUpTextArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEnurtdTxtPopPoppedUpTextArrayL( CStifItemParser& /*aItem*/ )
    {
    TInt value = KZero;
    CAknEnumeratedTextPopupSettingItem* popupItem = new( ELeave ) CAknEnumeratedTextPopupSettingItem( R_ENUMTEXT_SETTING_PAGE, value );
    CleanupStack::PushL( popupItem );
    
    CArrayPtr<HBufC>* popupArray = popupItem->PoppedUpTextArray();
    STIF_ASSERT_NULL( popupArray );
    
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( KThree );
    
    TBuf< KBufSize > buffer( KTestString );
    popupItem->SetEmptyItemTextL( buffer );
    popupItem->ConstructL( ETrue, KOne, buffer, mIcons, R_ENUMTEXT_SETTING_PAGE,
        EAknCtPopupSettingList, R_POPUP_SETTING_LIST_CONTROL, R_POPUP_SETTING_LIST );
    
    popupArray = popupItem->PoppedUpTextArray();
    STIF_ASSERT_NOT_NULL( popupArray );
    popupArray = NULL;
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEnurtdTxtPopCreateSettingPageLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEnurtdTxtPopCreateSettingPageLL( CStifItemParser& /*aItem*/ )
    {
    TInt value = KZero;
    CTestEnumeratedTextPopupSettingItem* popupItem = new( ELeave ) CTestEnumeratedTextPopupSettingItem( R_ENUMTEXT_SETTING_PAGE, value );
    CleanupStack::PushL( popupItem );
    
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( KThree );
    
    TBuf< KBufSize > buffer( KTestString );
    popupItem->SetEmptyItemTextL( buffer );
    popupItem->ConstructL( ETrue, KOne, buffer, mIcons, R_ENUMTEXT_SETTING_PAGE,
        EAknCtPopupSettingList, R_POPUP_SETTING_LIST_CONTROL, R_POPUP_SETTING_LIST );

    CAknSettingPage* dlg = popupItem->DoCreateSettingPageL();
    STIF_ASSERT_NOT_NULL( dlg );
    dlg = NULL;
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEnurtdTxtPopCreateAndExecuteSettingPageLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEnurtdTxtPopCreateAndExecuteSettingPageLL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesItemListEnurtdTxtPopEditItemLL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEnurtdTxtPopCompleteConstructionLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEnurtdTxtPopCompleteConstructionLL( CStifItemParser& /*aItem*/ )
    {
    TInt value = KZero;
    CTestEnumeratedTextPopupSettingItem* popupItem = new( ELeave ) CTestEnumeratedTextPopupSettingItem( R_ENUMTEXT_SETTING_PAGE, value );
    CleanupStack::PushL( popupItem );
    
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( KThree );
    
    TBuf< KBufSize > buffer( KTestString );
    popupItem->SetEmptyItemTextL( buffer );
    popupItem->ConstructL( ETrue, KOne, buffer, mIcons, R_ENUMTEXT_SETTING_PAGE,
        EAknCtPopupSettingList, R_POPUP_SETTING_LIST_CONTROL, R_POPUP_SETTING_LIST );
    
    popupItem->DoCompleteConstructionL();
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEnurtdTxtPopSetExternalValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEnurtdTxtPopSetExternalValueL( CStifItemParser& /*aItem*/ )
    {
    TInt value = KZero;
    CTestEnumeratedTextPopupSettingItem* popupItem = new( ELeave ) CTestEnumeratedTextPopupSettingItem( R_ENUMTEXT_SETTING_PAGE, value );
    CleanupStack::PushL( popupItem );
    
    TInt externalValue = popupItem->DoExternalValue();
    STIF_ASSERT_EQUALS( KZero, externalValue );
    
    popupItem->DoSetExternalValue( KThree );
    externalValue = popupItem->DoExternalValue();
    STIF_ASSERT_EQUALS( KThree, externalValue );
    
    CleanupStack::PopAndDestroy( popupItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEnurtdTxtPopSetInternalValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEnurtdTxtPopSetInternalValueL( CStifItemParser& /*aItem*/ )
    {
    TInt value = KZero;
    CTestEnumeratedTextPopupSettingItem* popupItem = new( ELeave ) CTestEnumeratedTextPopupSettingItem( R_ENUMTEXT_SETTING_PAGE, value );
    CleanupStack::PushL( popupItem );
    
    TInt mInternalValue = popupItem->DoInternalValue();
    STIF_ASSERT_EQUALS( KZero, mInternalValue );
    
    popupItem->DoSetInternalValue( KThree );
    mInternalValue = popupItem->DoInternalValue();
    STIF_ASSERT_EQUALS( KThree, mInternalValue );
    
    CleanupStack::PopAndDestroy( popupItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEnurtdTxtPopSetSelectedIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEnurtdTxtPopSetSelectedIndexL( CStifItemParser& /*aItem*/ )
    {
    TInt value = KZero;
    CTestEnumeratedTextPopupSettingItem* popupItem = new( ELeave ) CTestEnumeratedTextPopupSettingItem( R_ENUMTEXT_SETTING_PAGE, value );
    CleanupStack::PushL( popupItem );
    popupItem->DoSetSelectedIndex( KThree );
    CleanupStack::PopAndDestroy( popupItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEnurtdTxtPopIndexFromValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEnurtdTxtPopIndexFromValueL( CStifItemParser& /*aItem*/ )
    {
    TInt value = KZero;
    CTestEnumeratedTextPopupSettingItem* popupItem = new( ELeave ) CTestEnumeratedTextPopupSettingItem( R_ENUMTEXT_SETTING_PAGE, value );
    CleanupStack::PushL( popupItem );
        
    TFileName file( KTestMbmFile );
    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( KThree );
    
    TBuf< KBufSize > buffer( KTestString );
    popupItem->SetEmptyItemTextL( buffer );
    popupItem->ConstructL( ETrue, KOne, buffer, mIcons, R_ENUMTEXT_SETTING_PAGE,
        EAknCtPopupSettingList, R_POPUP_SETTING_LIST_CONTROL, R_POPUP_SETTING_LIST );
    
    TInt number = popupItem->DoIndexFromValue( KOne );
    STIF_ASSERT_NOT_EQUALS( KMinusOne, number );
    
    number = popupItem->DoIndexFromValue( KTwo );
    STIF_ASSERT_NOT_EQUALS( KMinusOne, number );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEnurtdTxtPopExternalValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEnurtdTxtPopExternalValueL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesItemListEnurtdTxtPopSetExternalValueL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEnurtdTxtPopInternalValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEnurtdTxtPopInternalValueL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesItemListEnurtdTxtPopSetInternalValueL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListEnurtdTxtPopQueryValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListEnurtdTxtPopQueryValueL( CStifItemParser& /*aItem*/ )
    {
    TInt value = KZero;
    CTestEnumeratedTextPopupSettingItem* popupItem = new( ELeave ) CTestEnumeratedTextPopupSettingItem( R_ENUMTEXT_SETTING_PAGE, value );
    CleanupStack::PushL( popupItem );
    
    MAknQueryValue* returnValue = popupItem->DoQueryValue();
    STIF_ASSERT_NULL( returnValue );
    
    CleanupStack::PopAndDestroy( popupItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListBinaryPopConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListBinaryPopConstructorL( CStifItemParser& /*aItem*/ )
    {
    TBool binaryValue = ETrue;
    CAknBinaryPopupSettingItem* binarydlg = new( ELeave ) CAknBinaryPopupSettingItem( KOne, binaryValue );
    CleanupStack::PushL( binarydlg );
    STIF_ASSERT_NOT_NULL( binarydlg );
    CleanupStack::PopAndDestroy( binarydlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListBinaryPopStoreLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListBinaryPopStoreLL( CStifItemParser& /*aItem*/ )
    {
    TBool binaryValue = ETrue;
    CTestBinaryPopupSettingItem* binarydlg = new( ELeave ) CTestBinaryPopupSettingItem( KOne, binaryValue );
    CleanupStack::PushL( binarydlg );
    
    TInt externalValue = binarydlg->DoExternalValue();
    STIF_ASSERT_EQUALS( KOne, externalValue );
    
    binarydlg->StoreL();
    externalValue = binarydlg->DoExternalValue();
    STIF_ASSERT_EQUALS( KZero, externalValue );
    
    CleanupStack::PopAndDestroy( binarydlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListBinaryPopLoadLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListBinaryPopLoadLL( CStifItemParser& /*aItem*/ )
    {
    TBool binaryValue = ETrue;
    CTestBinaryPopupSettingItem* binarydlg = new( ELeave ) CTestBinaryPopupSettingItem( KOne, binaryValue );
    CleanupStack::PushL( binarydlg );
    
    TInt externalValue = binarydlg->DoExternalValue();
    STIF_ASSERT_EQUALS( KOne, externalValue );
    
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( KThree );
    
    TBuf< KBufSize > buffer( KTestString );
    binarydlg->SetEmptyItemTextL( buffer );
    binarydlg->ConstructL( ETrue, KOne, buffer, mIcons, R_BINARY_SETTING_PAGE,
        EAknCtPopupSettingList, R_BINARY_POPUP_CONTROL, R_POPUP_SETTING_BINARY_TEXTS );
        
    binarydlg->LoadL();
    externalValue = binarydlg->DoExternalValue();
    STIF_ASSERT_EQUALS( KOne, externalValue );
    
    binarydlg->DoSetInternalValue( KZero );
    binarydlg->StoreL();
    binarydlg->LoadL();
    
    externalValue = binarydlg->DoExternalValue();
    STIF_ASSERT_EQUALS( KZero, externalValue );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListBinaryPopEditItemLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListBinaryPopEditItemLL( CStifItemParser& /*aItem*/ )
    {
    TBool binaryValue = ETrue;
    CTestBinaryPopupSettingItem* binarydlg = new( ELeave ) CTestBinaryPopupSettingItem( KOne, binaryValue );
    CleanupStack::PushL( binarydlg );
    
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( KThree );
    
    TBuf< KBufSize > buffer( KTestString );
    binarydlg->SetEmptyItemTextL( buffer );
    binarydlg->ConstructL( ETrue, KOne, buffer, mIcons, R_BINARY_SETTING_PAGE,
        EAknCtPopupSettingList, R_BINARY_POPUP_CONTROL, R_POPUP_SETTING_BINARY_TEXTS );
    
    binarydlg->EditItemL( ETrue );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListBinaryPopCompleteConstructionLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListBinaryPopCompleteConstructionLL( CStifItemParser& /*aItem*/ )
    {
    TBool binaryValue = ETrue;
    CTestBinaryPopupSettingItem* binarydlg = new( ELeave ) CTestBinaryPopupSettingItem( KOne, binaryValue );
    CleanupStack::PushL( binarydlg );
    
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( KThree );
    
    TBuf< KBufSize > buffer( KTestString );
    binarydlg->SetEmptyItemTextL( buffer );
    binarydlg->ConstructL( ETrue, KOne, buffer, mIcons, R_BINARY_SETTING_PAGE,
        EAknCtPopupSettingList, R_BINARY_POPUP_CONTROL, R_POPUP_SETTING_BINARY_TEXTS );
    
    binarydlg->DoCompleteConstructionL();
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListBigSIBConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListBigSIBConstructorL( CStifItemParser& /*aItem*/ )
    {
    CAknBigSettingItemBase* bigItem = new( ELeave ) CAknBigSettingItemBase( KOne );
    CleanupStack::PushL( bigItem );
    STIF_ASSERT_NOT_NULL( bigItem );
    CleanupStack::PopAndDestroy( bigItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListBigSIBSettingTextLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListBigSIBSettingTextLL( CStifItemParser& /*aItem*/ )
    {
    CTestBigSettingItemBase* bigItem = new( ELeave ) CTestBigSettingItemBase( KOne );
    CleanupStack::PushL( bigItem );
    
    TDesC nullDesc = KNullDesC;
    TDesC buffer = bigItem->DoSettingTextL();
    STIF_ASSERT_EQUALS( nullDesc, buffer );
    
    CleanupStack::PopAndDestroy( bigItem );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListItemArrayConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListItemArrayConstructorL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItemArray* mItemArray = new( ELeave ) CAknSettingItemArray( KFive, EFalse, KZero );
    mItemArray->Reset();
    delete mItemArray;
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListItemArrayDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListItemArrayDestructorL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItemArray* mItemArray = new( ELeave ) CAknSettingItemArray( KFive, EFalse, KZero );
    CleanupStack::PushL( mItemArray );
    CleanupStack::PopAndDestroy( mItemArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListItemArrayMdcaCountL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListItemArrayMdcaCountL( CStifItemParser& /*aItem*/ )
    {
    CTestSettingItemArray* mItemArray = new( ELeave ) CTestSettingItemArray( KFive, EFalse, KZero );
    CleanupStack::PushL( mItemArray );
    
    TInt number = mItemArray->MdcaCount();
    STIF_ASSERT_EQUALS( KZero, number );
    
    CAknSettingItem* settingItem = new( ELeave ) CAknSettingItem( KOne );
    CleanupStack::PushL( settingItem );
    mItemArray->AppendL( settingItem );
    mItemArray->DoSetVisibleCount( KOne );
    
    number = mItemArray->MdcaCount();
    STIF_ASSERT_EQUALS( KOne, number );
    mItemArray->ResetAndDestroy();
    CleanupStack::Pop( settingItem );
    CleanupStack::PopAndDestroy( mItemArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListItemArrayMdcaPointL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListItemArrayMdcaPointL( CStifItemParser& /*aItem*/ )
    {
    CTestSettingItemArray* mItemArray = new( ELeave ) CTestSettingItemArray( KFive, EFalse, KZero );
    CleanupStack::PushL( mItemArray );
    
    TBool binaryValue = ETrue;
    CTestBinaryPopupSettingItem* binarydlg = new( ELeave ) CTestBinaryPopupSettingItem( KOne, binaryValue );
    CleanupStack::PushL( binarydlg );
    
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( KThree );
    
    TBuf< KBufSize > buffer( KTestString );
    binarydlg->SetEmptyItemTextL( buffer );
    binarydlg->ConstructL( ETrue, KOne, buffer, mIcons, R_BINARY_SETTING_PAGE,
        EAknCtPopupSettingList, R_BINARY_POPUP_CONTROL, R_POPUP_SETTING_BINARY_TEXTS );
    
    
    mItemArray->AppendL( binarydlg );
    mItemArray->DoSetVisibleCount( KOne );
    
    TPtrC16 text = mItemArray->MdcaPoint( KZero );
    STIF_ASSERT_NOT_NULL( &text );
    
    CleanupStack::PopAndDestroy( mIcons );
    mItemArray->ResetAndDestroy();
    CleanupStack::Pop( binarydlg );
    CleanupStack::PopAndDestroy( mItemArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListItemArrayItemIndexFromVisibleIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListItemArrayItemIndexFromVisibleIndexL( CStifItemParser& /*aItem*/ )
    {
    CTestSettingItemArray* mItemArray = new( ELeave ) CTestSettingItemArray( KFive, EFalse, KZero );
    CleanupStack::PushL( mItemArray );
    
    TInt number = mItemArray->MdcaCount();
    STIF_ASSERT_EQUALS( KZero, number );
    
    CAknSettingItem* settingItem = new( ELeave ) CAknSettingItem( KOne );
    CleanupStack::PushL( settingItem );
    mItemArray->AppendL( settingItem );
    mItemArray->DoSetVisibleCount( KZero );
    
    TInt trueIndex = mItemArray->ItemIndexFromVisibleIndex( KZero );
    STIF_ASSERT_EQUALS( KZero, trueIndex );
    mItemArray->ResetAndDestroy();
    CleanupStack::Pop( KOne );
    CleanupStack::PopAndDestroy( mItemArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListItemArrayRecalculateVisibleIndicesLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListItemArrayRecalculateVisibleIndicesLL( CStifItemParser& /*aItem*/ )
    {
    CTestSettingItemArray* mItemArray = new( ELeave ) CTestSettingItemArray( KFive, EFalse, KZero );
    CleanupStack::PushL( mItemArray );
    
    mItemArray->RecalculateVisibleIndicesL();
    
    TBool binaryValue = ETrue;
    CTestBinaryPopupSettingItem* binarydlg = new( ELeave ) CTestBinaryPopupSettingItem( KOne, binaryValue );
    CleanupStack::PushL( binarydlg );
    
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 

    CArrayPtr<CGulIcon>* mIcons = new(ELeave) CAknIconArray( KNumberOfIcons ); 
    CleanupStack::PushL(mIcons); 
    
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    AknIconUtils::CreateIconLC( bitmap, mask, file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CGulIcon* mIcon = CGulIcon::NewL( bitmap, mask );
    CleanupStack::PushL( mIcon );
    mIcons->AppendL( mIcon );
    CleanupStack::Pop( KThree );
    
    TBuf< KBufSize > buffer( KTestString );
    binarydlg->SetEmptyItemTextL( buffer );
    binarydlg->ConstructL( ETrue, KOne, buffer, mIcons, R_BINARY_SETTING_PAGE,
        EAknCtPopupSettingList, R_BINARY_POPUP_CONTROL, R_POPUP_SETTING_BINARY_TEXTS );
        
    mItemArray->AppendL( binarydlg );
    mItemArray->DoSetVisibleCount( KZero );
    
    mItemArray->RecalculateVisibleIndicesL();
    
    CleanupStack::PopAndDestroy( KOne );
    mItemArray->ResetAndDestroy();
    CleanupStack::Pop( KOne );
    CleanupStack::PopAndDestroy( KOne );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListItemArraySetInitialOrdinalL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListItemArraySetInitialOrdinalL( CStifItemParser& /*aItem*/ )
    {
    CTestSettingItemArray* mItemArray = new( ELeave ) CTestSettingItemArray( KFive, EFalse, KZero );
    CleanupStack::PushL( mItemArray );
    mItemArray->SetInitialOrdinal( KOne );
    CleanupStack::PopAndDestroy( mItemArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListItemArraySetFlagsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListItemArraySetFlagsL( CStifItemParser& /*aItem*/ )
    {
    CTestSettingItemArray* mItemArray = new( ELeave ) CTestSettingItemArray( KFive, EFalse, KZero );
    CleanupStack::PushL( mItemArray );
    mItemArray->SetFlags( KOne );
    CleanupStack::PopAndDestroy( mItemArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListItemArraySetVisibleCountL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListItemArraySetVisibleCountL( CStifItemParser& /*aItem*/ )
    {
    CTestSettingItemArray* mItemArray = new( ELeave ) CTestSettingItemArray( KFive, EFalse, KZero );
    CleanupStack::PushL( mItemArray );
    
    TInt visible = mItemArray->DoVisibleCount();
    STIF_ASSERT_EQUALS( KZero, visible );
    
    mItemArray->DoSetVisibleCount( KThree );
    visible = mItemArray->DoVisibleCount();
    STIF_ASSERT_EQUALS( KThree, visible );
    
    CleanupStack::PopAndDestroy( mItemArray );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListItemArrayVisibleCountL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListItemArrayVisibleCountL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesItemListItemArraySetVisibleCountL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListItemListConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListItemListConstructorL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItemList* list = new( ELeave ) CAknSettingItemList();
    CleanupStack::PushL( list );
    STIF_ASSERT_NOT_NULL( list );
    CleanupStack::PopAndDestroy( list );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListItemListDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListItemListDestructorL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItemList* list = new( ELeave ) CAknSettingItemList();
    CleanupStack::PushL( list );
    CleanupStack::PopAndDestroy( list );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListItemListConstructFromResourceLIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListItemListConstructFromResourceLIdL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItemList* list = new( ELeave ) CAknSettingItemList();
    CleanupStack::PushL( list );
    
    list->ConstructFromResourceL( R_SETTING_LIST_SETTING_BINARY );
    
    CleanupStack::PopAndDestroy( list );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListItemListConstructFromResourceLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListItemListConstructFromResourceLL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItemList* list = new( ELeave ) CAknSettingItemList();
    CleanupStack::PushL( list );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_SETTING_LIST_SETTING_BINARY );
    list->ConstructFromResourceL( reader );
    
    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( list );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListItemListCountComponentControlsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListItemListCountComponentControlsL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItemList* list = new( ELeave ) CAknSettingItemList();
    CleanupStack::PushL( list );
    
    list->CountComponentControls();
    
    CleanupStack::PopAndDestroy( list );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestTextSettingPage::~CTestTextSettingPage
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListItemListComponentControlL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItemList* list = new( ELeave ) CAknSettingItemList();
    CleanupStack::PushL( list );
    
    CCoeControl* control = list->ComponentControl( KOne );
    STIF_ASSERT_NULL( control );
    
    list->ConstructFromResourceL( R_SETTING_LIST_SETTING_BINARY );
    control = list->ComponentControl( KOne );
    STIF_ASSERT_NOT_NULL( control );
    control = NULL;
    CleanupStack::PopAndDestroy( list );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestTextSettingPage::~CTestTextSettingPage
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListItemListOfferKeyEventLL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItemList* list = new( ELeave ) CAknSettingItemList();
    CleanupStack::PushL( list );
    
    TKeyEvent event;
    event.iCode = EKeyOK;
    
    list->ConstructFromResourceL( R_SETTING_LIST_SETTING_BINARY );
    list->OfferKeyEventL( event, EEventKey );
    
    CleanupStack::PopAndDestroy( list );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestTextSettingPage::~CTestTextSettingPage
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListItemListFocusChangedL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItemList* list = new( ELeave ) CAknSettingItemList();
    CleanupStack::PushL( list );
    
    list->ConstructFromResourceL( R_SETTING_LIST_SETTING_BINARY );
    list->FocusChanged( EDrawNow );
    
    CleanupStack::PopAndDestroy( list );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListItemListHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListItemListHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItemList* list = new( ELeave ) CAknSettingItemList();
    CleanupStack::PushL( list );
        
    list->ConstructFromResourceL( R_SETTING_LIST_SETTING_BINARY );
    list->HandleResourceChange( KEikDynamicLayoutVariantSwitch );
    list->HandleResourceChange( KAknsMessageSkinChange );
    
    CleanupStack::PopAndDestroy( list );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListItemListHandleListBoxEventLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListItemListHandleListBoxEventLL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItemList* list = new( ELeave ) CAknSettingItemList();
    CleanupStack::PushL( list );
        
    list->ConstructFromResourceL( R_SETTING_LIST_SETTING_BINARY );
    CEikTextListBox* listBox = new(ELeave) CEikTextListBox; 
    CleanupStack::PushL( listBox ); 
    CAknPopupList* popupList = CAknPopupList::NewL( listBox, R_AVKON_SOFTKEYS_OK_BACK );
    CleanupStack::PushL( popupList ); 
    listBox->ConstructL( popupList, CEikListBox::ELeftDownInViewRect ); 
    list->HandleListBoxEventL( listBox, MEikListBoxObserver::EEventItemDoubleClicked );
    
    CleanupStack::PopAndDestroy( popupList );
    CleanupStack::PopAndDestroy( listBox );
    CleanupStack::PopAndDestroy( list );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListItemListEditItemLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListItemListEditItemLL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItemList* list = new( ELeave ) CAknSettingItemList();
    CleanupStack::PushL( list );
        
    list->ConstructFromResourceL( R_SETTING_LIST_SETTING_BINARY );
    list->EditItemL( KZero, ETrue );
    
    CleanupStack::PopAndDestroy( list );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListItemListLoadSettingsLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListItemListLoadSettingsLL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItemList* list = new( ELeave ) CAknSettingItemList();
    CleanupStack::PushL( list );
            
    list->ConstructFromResourceL( R_SETTING_LIST_SETTING_BINARY );
    list->LoadSettingsL();
    
    CleanupStack::PopAndDestroy( list );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListItemListStoreSettingsLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListItemListStoreSettingsLL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItemList* list = new( ELeave ) CAknSettingItemList();
    CleanupStack::PushL( list );
            
    list->ConstructFromResourceL( R_SETTING_LIST_SETTING_BINARY );
    list->StoreSettingsL();
    
    CleanupStack::PopAndDestroy( list );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListItemListSetIncludeHiddenInOrdinalL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListItemListSetIncludeHiddenInOrdinalL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItemList* list = new( ELeave ) CAknSettingItemList();
    CleanupStack::PushL( list );
            
    list->ConstructFromResourceL( R_SETTING_LIST_SETTING_BINARY );
    list->SetIncludeHiddenInOrdinal( ETrue );
    list->SetIncludeHiddenInOrdinal( EFalse );
    
    CleanupStack::PopAndDestroy( list );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
//CTestSDKSettingPages::TestSettingPagesItemListItemListIsNumberedStyleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListItemListIsNumberedStyleL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItemList* list = new( ELeave ) CAknSettingItemList();
    CleanupStack::PushL( list );
    
    list->ConstructFromResourceL( R_SETTING_LIST_SETTING_BINARY );
    list->IsNumberedStyle();
    CleanupStack::PopAndDestroy( list );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListItemListListBoxL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListItemListListBoxL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItemList* list = new( ELeave ) CAknSettingItemList();
    CleanupStack::PushL( list );
    
    CEikFormattedCellListBox* listBox = list->ListBox();
    STIF_ASSERT_NULL( listBox );
    
    list->ConstructFromResourceL( R_SETTING_LIST_SETTING_BINARY );
    listBox = list->ListBox();
    STIF_ASSERT_NOT_NULL( listBox );
    listBox = NULL;
    
    CleanupStack::PopAndDestroy( list );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListItemListSettingItemArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListItemListSettingItemArrayL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItemList* list = new( ELeave ) CAknSettingItemList();
    CleanupStack::PushL( list );
    
    CAknSettingItemArray* mArray = list->SettingItemArray();
    STIF_ASSERT_NULL( mArray );
    
    list->ConstructFromResourceL( R_SETTING_LIST_SETTING_BINARY );
    mArray = list->SettingItemArray();
    STIF_ASSERT_NOT_NULL( mArray );
    mArray = NULL;
    CleanupStack::PopAndDestroy( list );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListItemListHandleChangeInItemArrayOrVisibilityLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListItemListHandleChangeInItemArrayOrVisibilityLL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItemList* list = new( ELeave ) CAknSettingItemList();
    CleanupStack::PushL( list );
    
    list->ConstructFromResourceL( R_SETTING_LIST_SETTING_BINARY );
    list->HandleChangeInItemArrayOrVisibilityL();
    
    CleanupStack::PopAndDestroy( list );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListItemListHandlePointerEventLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListItemListHandlePointerEventLL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingItemList* list = new( ELeave ) CAknSettingItemList();
    CleanupStack::PushL( list );
    
    list->ConstructFromResourceL( R_SETTING_LIST_SETTING_BINARY );
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    list->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( list );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesItemListItemListCreateSettingItemLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesItemListItemListCreateSettingItemLL( CStifItemParser& /*aItem*/ )
    {
    CTestSettingItemList* list = new( ELeave ) CTestSettingItemList();
    CleanupStack::PushL( list );
    
    list->ConstructFromResourceL( R_SETTING_LIST_SETTING_BINARY );
    CAknSettingItem* mItemdlg = list->DoCreateSettingItemL( KZero );
    STIF_ASSERT_NOT_NULL( mItemdlg );
    mItemdlg = NULL;
    CleanupStack::PopAndDestroy( list );
    return KErrNone;
    }

//End file


