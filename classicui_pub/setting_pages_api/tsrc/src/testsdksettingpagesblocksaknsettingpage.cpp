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
* Description:  Test aknsettingpage.h
*
*/



// INCLUDE FILES
#include <aknsettingpage.h>
#include <akninputblock.h>
#include <testsdksettingpages.rsg>
#include <aknsettingitemlist.h>
#include <gulicon.h>
#include <avkon.mbg>
#include <akniconarray.h>
#include <akniconutils.h> 
#include <w32std.h>
#include <coemop.h>
#include <bautils.h>
#include <aknscontrolcontext.h> 

#include "testsdksettingpages.h"
#include "testsdksettingpagesstdinclude.h"
#include "testparentcontrol.h"
#include "testsettingpageobserver.h"
#include "testaknsettingpageprotected.h"
#include "testsettingpagemenuobserver.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageConstructorL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingPage* pageDialog = new( ELeave ) CAknSettingPage( R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    STIF_ASSERT_NOT_NULL( pageDialog );
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageConstructorLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageConstructorLL( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> buffer( KTestString );
    CAknSettingPage* pageDialog = new( ELeave ) CAknSettingPage( &buffer, KOne, KZero, KZero, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    STIF_ASSERT_NOT_NULL( pageDialog );
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageDestructorL( CStifItemParser& /*aItem*/ )
    {
    CAknSettingPage* pageDialog = new( ELeave ) CAknSettingPage( R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    STIF_ASSERT_NOT_NULL( pageDialog );
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageExecuteLDL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageExecuteLDL( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    pageDialog->ConstructL();
    pageDialog->ExecuteLD( CAknSettingPage::EUpdateWhenChanged );
    CleanupStack::Pop( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageConstructL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesSetPageExecuteLDL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageEditorControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageEditorControlL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CAknSettingPage* pageDialog = new( ELeave ) CAknSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    CCoeControl* editorControl = pageDialog->EditorControl();
    STIF_ASSERT_NULL( editorControl );
    
    pageDialog->ConstructL();
    editorControl = pageDialog->EditorControl();
    STIF_ASSERT_NOT_NULL( editorControl );
    editorControl = NULL;
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageSettingIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageSettingIdL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CAknSettingPage* pageDialog = new( ELeave ) CAknSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    
    TInt settingId = pageDialog->SettingId();
    STIF_ASSERT_EQUALS( KAknSettingPageNoIdSet, settingId );
    
    pageDialog->SetSettingId( KOne );
    settingId = pageDialog->SettingId();
    STIF_ASSERT_EQUALS( KOne, settingId );
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageSetSettingIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageSetSettingIdL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesSetPageSettingIdL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageSetSettingNumberLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageSetSettingNumberLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CAknSettingPage* pageDialog = new( ELeave ) CAknSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    
    TInt settingNumber = pageDialog->SettingNumber();
    STIF_ASSERT_EQUALS( KOne, settingNumber );
    
    pageDialog->SetSettingNumberL( KThree );
    settingNumber = pageDialog->SettingNumber();
    STIF_ASSERT_EQUALS( KThree, settingNumber );
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageSetSettingTextLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageSetSettingTextLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CAknSettingPage* pageDialog = new( ELeave ) CAknSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    pageDialog->ConstructL();
    pageDialog->SetSettingTextL( buffer );
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageSetSettingPageObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageSetSettingPageObserverL( CStifItemParser& /*aItem*/ )
    {
    CSettingItemObserver* observer = new( ELeave ) CSettingItemObserver( KOne );
    CleanupStack::PushL( observer );
    TBuf< KBufSize > buffer( KTestString );
    CAknSettingPage* pageDialog = new( ELeave ) CAknSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    pageDialog->SetSettingPageObserver( observer );
    CleanupStack::PopAndDestroy( pageDialog );
    CleanupStack::PopAndDestroy( observer );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageSettingNumberL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageSettingNumberL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesSetPageSetSettingNumberLL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageIsNumberedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageIsNumberedL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CAknSettingPage* pageDialog = new( ELeave ) CAknSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    
    TBool numbered = pageDialog->IsNumbered();
    STIF_ASSERT_FALSE( numbered );
    
    pageDialog->SetNumbered( ETrue );
    numbered = pageDialog->IsNumbered();
    STIF_ASSERT_TRUE( numbered );
    
    pageDialog->SetNumbered( EFalse );
    numbered = pageDialog->IsNumbered();
    STIF_ASSERT_FALSE( numbered );
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageSetNumberedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageSetNumberedL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesSetPageIsNumberedL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageGetEditorResourceInfoLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageGetEditorResourceInfoLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CAknSettingPage* pageDialog = new( ELeave ) CAknSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    
    TInt controlType( KMinusOne );
    TInt editorResourceId( KMinusOne );
    
    pageDialog->ConstructL();
    pageDialog->GetEditorResourceInfoL( R_EXAMPLE_EDITOR_CONTROL, controlType, editorResourceId );

    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageSetEditStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageSetEditStateL( CStifItemParser& /*aItem*/)
    {
    TBuf< KBufSize > buffer( KTestString );
    CAknSettingPage* pageDialog = new( ELeave ) CAknSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    TBool editable = pageDialog->IsEditable();
    STIF_ASSERT_TRUE( editable );
    
    pageDialog->SetEditState( EFalse );
    editable = pageDialog->IsEditable();
    STIF_ASSERT_FALSE( editable );
    
    pageDialog->SetEditState( ETrue );
    editable = pageDialog->IsEditable();
    STIF_ASSERT_TRUE( editable );
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageIsEditableL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageIsEditableL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesSetPageSetEditStateL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    pageDialog->ConstructL();
    pageDialog->TestSizeChanged();
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageFocusChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageFocusChangedL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    pageDialog->ConstructL();
    pageDialog->SetFocus( ETrue, EDrawNow );
    pageDialog->TestFocusChanged( EDrawNow );
    CCoeControl* control = pageDialog->EditorControl();
    TBool focus = control->IsFocused();
    STIF_ASSERT_TRUE( focus );
    pageDialog->SetFocus( EFalse, EDrawNow );
    pageDialog->TestFocusChanged( ENoDrawNow );
    focus = control->IsFocused();
    STIF_ASSERT_FALSE( focus );
    control = NULL;
    pageDialog->TestSetFocusToEditor();// it has not any code, debug macro will crash, add for coverage
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageProcessCommandLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageProcessCommandLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    pageDialog->ConstructL();
    pageDialog->ExecuteLD( CAknSettingPage::EUpdateWhenChanged );
    CleanupStack::Pop( pageDialog );
    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageHandleControlEventLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageHandleControlEventLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    pageDialog->ConstructL();
    pageDialog->SetiUpdateMode( CAknSettingPage::EUpdateWhenChanged );
    pageDialog->TestHandleControlEventL( NULL, MCoeControlObserver::EEventStateChanged );
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetpageOkToExitLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetpageOkToExitLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    
    TBool exitif = pageDialog->TestOkToExitL( ETrue );
    STIF_ASSERT_TRUE( exitif );
    
    exitif = pageDialog->TestOkToExitL( EFalse );
    STIF_ASSERT_TRUE( exitif );
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageDynamicInitLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageDynamicInitLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    pageDialog->TestDynamicInitL();
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageUpdateSettingLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageUpdateSettingLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    pageDialog->TestUpdateSettingL();
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageAcceptSettingLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageAcceptSettingLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    pageDialog->TestAcceptSettingL();
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageRestoreOriginalSettingLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageRestoreOriginalSettingLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    pageDialog->TestRestoreOriginalSettingL();
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageDisplayMenuLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageDisplayMenuLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    pageDialog->ConstructL();
    CCoeEnv::Static()->AppUi()->AddToStackL( pageDialog );
    pageDialog->TestDisplayMenuL();
    CCoeEnv::Static()->AppUi()->RemoveFromStack( pageDialog );
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageHideMenuL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageHideMenuL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    pageDialog->ConstructL();
    CCoeEnv::Static()->AppUi()->AddToStackL( pageDialog );
    pageDialog->TestHideMenu();
    CCoeEnv::Static()->AppUi()->RemoveFromStack( pageDialog );
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageSelectCurrentItemLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageSelectCurrentItemLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    pageDialog->TestSelectCurrentItemL();
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageBaseConstructLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageBaseConstructLL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesSetPageConstructL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageDismissLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageDismissLL( CStifItemParser& /*aItem*/ )
    {
    CSettingItemObserver* observer = new( ELeave ) CSettingItemObserver( KOne );
    CleanupStack::PushL( observer );
    TBuf< KBufSize > buf( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buf, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    pageDialog->ConstructL();
    
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
    
    observer->SetEmptyItemTextL( buf );
    observer->ConstructL( ETrue, KOne, buffer, mIcons, R_EXAMPLE_SETTING_PAGE,
        EEikCtEdwin, R_EXAMPLE_EDITOR_CONTROL );

    pageDialog->SetSettingPageObserver( observer );
    pageDialog->TestDismissL( ETrue );
    pageDialog->TestDismissL( EFalse );
    
    CleanupStack::PopAndDestroy( mIcons );
    CleanupStack::PopAndDestroy( pageDialog );
    CleanupStack::PopAndDestroy( observer );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageMenuShowingL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageMenuShowingL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    pageDialog->ConstructL();
    pageDialog->TestMenuShowing();
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageConstructFromResourceLIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageConstructFromResourceLIdL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesSetPageExecuteLDL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageConstructFromResourceLReaderL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageConstructFromResourceLReaderL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesSetPageExecuteLDL( aItem );
    return err;
    }


// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetpageAttemptExitLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetpageAttemptExitLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    pageDialog->ConstructL();
    pageDialog->ExecuteLD( CAknSettingPage::EUpdateWhenChanged );
    CleanupStack::Pop( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageWaitingL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageWaitingL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    pageDialog->TestWaiting();
    pageDialog->ExecuteLD( CAknSettingPage::EUpdateWhenChanged );
    
    CleanupStack::Pop( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageCbaL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageCbaL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    
    CEikButtonGroupContainer* cba = pageDialog->TestCba();
    STIF_ASSERT_NULL( cba );
    
    pageDialog->ConstructL();
    cba = pageDialog->TestCba();
    STIF_ASSERT_NOT_NULL( cba );
    cba = NULL;
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageDefaultCbaResourceIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageDefaultCbaResourceIdL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    
    TInt cbaId = pageDialog->TestDefaultCbaResourceId();
    STIF_ASSERT_EQUALS( KZero, cbaId );
    
    pageDialog->ConstructL();
    cbaId = pageDialog->TestDefaultCbaResourceId();
    STIF_ASSERT_EQUALS( R_AVKON_SOFTKEYS_OK_CANCEL__OK, cbaId );
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageOfferKeyEventLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageOfferKeyEventLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    pageDialog->ConstructL();
    
    TKeyEvent event1;
    event1.iCode = EKeyOK;
    pageDialog->TestOfferKeyEventL( event1, EEventKey );

    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageStandardSettingPageLayoutL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageStandardSettingPageLayoutL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    pageDialog->ConstructL();
    pageDialog->TestStandardSettingPageLayout();
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageIsBaseConstructedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageIsBaseConstructedL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    
    TBool baseConstructed = pageDialog->TestIsBaseConstructed();
    STIF_ASSERT_FALSE( baseConstructed );
    
    pageDialog->ConstructL();
    baseConstructed = pageDialog->TestIsBaseConstructed();
    STIF_ASSERT_TRUE( baseConstructed );
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageSettingPageResourceIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageSettingPageResourceIdL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    
    TInt resourceId = pageDialog->TestSettingPageResourceId();
    STIF_ASSERT_EQUALS( R_EXAMPLE_SETTING_PAGE, resourceId );
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageBaseDrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageBaseDrawL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    CAknInputBlock* inputBlock = CAknInputBlock::NewLC( );
    if ( !pageDialog->TestIsBaseConstructed() )
        ConstructL();
    pageDialog->DoActivateGc();
    pageDialog->TestDynamicInitL();
    pageDialog->ActivateL();

    TPoint point1( KZero, KZero );
    TPoint point2( KPointX, KPointY );
    TRect rect( point1, point2 );
    pageDialog->GetWindow().Invalidate( rect ); 
    pageDialog->GetWindow().BeginRedraw( rect ); 
    
    pageDialog->TestBaseDraw( rect );
    pageDialog->DoDeactivateGc();
    
    CleanupStack::PopAndDestroy( inputBlock );
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageResetFlagsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageResetFlagsL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->SetSettingId( KThree );
    TInt settingId = pageDialog->SettingId();
    STIF_ASSERT_EQUALS( KThree, settingId );
    
    pageDialog->TestResetFlags();
    settingId = pageDialog->SettingId();
    STIF_ASSERT_EQUALS( KMinusOne, settingId );
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPagePostDisplayCheckLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPagePostDisplayCheckLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    
    TBool displayChecked = pageDialog->TestPostDisplayCheckL();
    STIF_ASSERT_TRUE( displayChecked );
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageUpdateCbaLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageUpdateCbaLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, 
            EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    pageDialog->TestUpdateCbaL();
    
    pageDialog->SetEditState( EFalse );
    pageDialog->TestUpdateCbaL();
    
    pageDialog->SetEditState( ETrue );
    pageDialog->TestSetDataValidity( EFalse );
    pageDialog->TestUpdateCbaL();
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageDataValidityL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageDataValidityL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, 
            EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    
    TBool dataValidity = pageDialog->TestDataValidity();
    STIF_ASSERT_TRUE( dataValidity );
    
    pageDialog->TestSetDataValidity( EFalse );
    dataValidity = pageDialog->TestDataValidity();
    STIF_ASSERT_FALSE( dataValidity );
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageSetDataValidityL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageSetDataValidityL( CStifItemParser& aItem )
    {
    TInt err = TestSettingPagesSetPageDataValidityL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageCheckAndSetDataValidityL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageCheckAndSetDataValidityL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, 
            EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    
    TBool dataValidity = pageDialog->TestDataValidity();
    STIF_ASSERT_TRUE( dataValidity );
    
    pageDialog->TestSetDataValidity( EFalse );
    pageDialog->TestCheckAndSetDataValidity();
    dataValidity = pageDialog->TestDataValidity();
    STIF_ASSERT_TRUE( dataValidity );
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageSetEmphasisL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageSetEmphasisL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    pageDialog->ConstructL();
    CCoeEnv::Static()->AppUi()->AddToStackL( pageDialog );
    pageDialog->TestSetEmphasis( pageDialog->EditorControl(), ETrue );
    CCoeEnv::Static()->AppUi()->RemoveFromStack( pageDialog );
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageDynInitMenuPaneLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageDynInitMenuPaneLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    CTestMenuObserver* observer = new( ELeave ) CTestMenuObserver;
    CleanupStack::PushL( observer );
    CEikMenuPane* menuPane = new( ELeave ) CEikMenuPane( observer );
    CleanupStack::PushL( menuPane );
    
    pageDialog->TestDynInitMenuPaneL( R_AVKON_FORM_MENUPANE, menuPane );
    
    CleanupStack::PopAndDestroy( KThree );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    pageDialog->ConstructL();
    pageDialog->HandleResourceChange( KEikDynamicLayoutVariantSwitch );
    pageDialog->HandleResourceChange( KAknsMessageSkinChange );
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageCountComponentControlsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageCountComponentControlsL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    pageDialog->ConstructL();
    TInt controlNumber = pageDialog->CountComponentControls();
    STIF_ASSERT_NOT_EQUALS( KZero, controlNumber );
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageComponentControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageComponentControlL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    pageDialog->ConstructL();
    
    pageDialog->EditorControl();
    pageDialog->ComponentControl( KOne );
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageHandlePointerEventLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageHandlePointerEventLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
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
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageInputCapabilitiesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageInputCapabilitiesL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    pageDialog->InputCapabilities();
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageInvalidDataCbaResourceIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageInvalidDataCbaResourceIdL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog ); 
    
    pageDialog->ConstructL();
    TInt cbaId = pageDialog->TestInvalidDataCbaResourceId();
    STIF_ASSERT_EQUALS( R_AVKON_SOFTKEYS_CANCEL, cbaId );
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageMopSupplyObjectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageMopSupplyObjectL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    pageDialog->ConstructL();
    
    TTypeUid uId( MAknsControlContext::ETypeId );
    pageDialog->TestMopSupplyObject( uId );
    
    TTypeUid uIdTwo( CEikScrollBarFrame::ETypeId );
    pageDialog->TestMopSupplyObject( uIdTwo );
    
    TTypeUid uIdThree = 0x11111111;
    pageDialog->TestMopSupplyObject( uIdThree );
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageWriteInternalStateLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageWriteInternalStateLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
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
    
    
    CleanupStack::PopAndDestroy( KThree );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageTextLabelL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageTextLabelL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    
    CEikLabel* textLable = pageDialog->TestTextLabel();
    STIF_ASSERT_NULL( textLable );
    
    pageDialog->ConstructL();
    textLable = pageDialog->TestTextLabel();
    STIF_ASSERT_NOT_NULL( textLable );
    textLable = NULL;
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSetPageShadowTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSetPageShadowTextL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestSettingPage* pageDialog = new( ELeave ) CTestSettingPage( &buffer, KOne, 
        EAknCtPopupSettingList, R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );

    pageDialog->ConstructL();
    CEikLabel* textLable = pageDialog->TestShadowText();
    STIF_ASSERT_NOT_NULL( textLable );
    textLable = NULL;
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

//End file


