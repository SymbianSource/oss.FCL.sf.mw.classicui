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
* Description:  Test aknpasswordsettingpage.h
*
*/



// INCLUDE FILES
#include <aknpasswordsettingpage.h>
#include <testsdksettingpages.rsg>
#include <bautils.h>

#include "testsdksettingpages.h"
#include "testaknpasswordsettingpageprotected.h"
#include "testparentcontrol.h"
#include "testsdksettingpagesstdinclude.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesPasswordConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesPasswordConstructorL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KNewPassword );
    TBuf< KBufSize > buffertwo( KOldPassword );
    CTestPasswordSettingPage* passwordsettingpage = new( ELeave ) CTestPasswordSettingPage( R_NUMERIC_PASSWORD_SETTING_PAGE, buffer, buffertwo );
    CleanupStack::PushL( passwordsettingpage );
    STIF_ASSERT_NOT_NULL( passwordsettingpage );
    
    CleanupStack::PopAndDestroy( passwordsettingpage );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesPasswordConstructorLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesPasswordConstructorLL( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> buffer( KTestString );
    TBuf< KBufSize > newpassword( KNewPassword );
    TBuf< KBufSize > oldpassword( KOldPassword );
    CTestPasswordSettingPage* pageDialog = new( ELeave ) CTestPasswordSettingPage( &buffer, KOne, 
        EAknCtNumericSecretEditor, R_NUMERIC_PASSWORD_CONTROL, 
        R_NUMERIC_PASSWORD_SETTING_PAGE, newpassword, oldpassword );
    CleanupStack::PushL( pageDialog );
    STIF_ASSERT_NOT_NULL( pageDialog );
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordSetOldPasswordConfirmationResourceIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordSetOldPasswordConfirmationResourceIdL( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> buffer( KTestString );
    TBuf< KBufSize > newpassword( KNewPassword );
    TBuf< KBufSize > oldpassword( KOldPassword );
    CTestPasswordSettingPage* pageDialog = new( ELeave ) CTestPasswordSettingPage( &buffer, KOne, KZero, KZero, R_NUMERIC_PASSWORD_SETTING_PAGE, newpassword, oldpassword );
    CleanupStack::PushL( pageDialog );
    pageDialog->SetOldPasswordConfirmationResourceId( R_PASSWORD_CONFIRMATION );
    TInt oldpasswordId = pageDialog->GetOldPasswordConfirmationResourceId();
    STIF_ASSERT_EQUALS( R_PASSWORD_CONFIRMATION, oldpasswordId );
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordSetNewPasswordConfirmationResourceIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordSetNewPasswordConfirmationResourceIdL( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> buffer( KTestString );
    TBuf< KBufSize > newpassword( KNewPassword );
    TBuf< KBufSize > oldpassword( KOldPassword );
    CTestPasswordSettingPage* pageDialog = new( ELeave ) CTestPasswordSettingPage( &buffer, KOne, KZero, KZero, R_NUMERIC_PASSWORD_SETTING_PAGE, newpassword, oldpassword );
    CleanupStack::PushL( pageDialog );
    pageDialog->SetNewPasswordConfirmationResourceId( R_PASSWORD_CONFIRMATION );
    TInt oldpasswordId = pageDialog->GetNewPasswordConfirmationResourceId();
    STIF_ASSERT_EQUALS( R_PASSWORD_CONFIRMATION, oldpasswordId );
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordSetMatchingModeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordSetMatchingModeL( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> buffer( KTestString );
    TBuf< KBufSize > newpassword( KNewPassword );
    TBuf< KBufSize > oldpassword( KOldPassword );
    CTestPasswordSettingPage* pageDialog = new( ELeave ) CTestPasswordSettingPage( &buffer, KOne, KZero, KZero, R_NUMERIC_PASSWORD_SETTING_PAGE, newpassword, oldpassword );
    CleanupStack::PushL( pageDialog );
    pageDialog->SetMatchingMode( CAknPasswordSettingPage::ECaseSensitive );
    CAknPasswordSettingPage::TAknPasswordMatchingMode mode = pageDialog->MatchingMode();
    STIF_ASSERT_EQUALS( CAknPasswordSettingPage::ECaseSensitive, mode );
    
    pageDialog->SetMatchingMode( CAknPasswordSettingPage::ECaseInsensitive );
    mode = pageDialog->MatchingMode();
    STIF_ASSERT_EQUALS( CAknPasswordSettingPage::ECaseInsensitive, mode );
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordMatchingModeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordMatchingModeL( CStifItemParser& aItem )
    {
    TInt err = TestSettingpagesPasswordSetMatchingModeL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordSetMaxPasswordLengthL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordSetMaxPasswordLengthL( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> buffer( KTestString );
    TBuf< KBufSize > newpassword( KNewPassword );
    TBuf< KBufSize > oldpassword( KOldPassword );
    CTestPasswordSettingPage* pageDialog = new( ELeave ) CTestPasswordSettingPage( &buffer, KOne, KZero, KZero, R_NUMERIC_PASSWORD_SETTING_PAGE, newpassword, oldpassword );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->SetMaxPasswordLength( KOne );
    TInt passwordlength = pageDialog->MaxPasswordLength();
    STIF_ASSERT_EQUALS( KOne, passwordlength );
    
    pageDialog->SetMaxPasswordLength( KTen );
    passwordlength = pageDialog->MaxPasswordLength();
    STIF_ASSERT_EQUALS( KTen, passwordlength );
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordMaxPasswordLengthL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordMaxPasswordLengthL( CStifItemParser& aItem )
    {
    TInt err = TestSettingpagesPasswordSetMaxPasswordLengthL( aItem );
    return err;
    }
//new
// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordHandlePointerEventLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordHandlePointerEventLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KBufSize > newpassword( KNewPassword );
    TBuf< KBufSize > oldpassword( KOldPassword );
    CTestPasswordSettingPage* pageDialog = new( ELeave ) CTestPasswordSettingPage( &buffer, KOne, 
        EAknCtNumericSecretEditor, R_NUMERIC_PASSWORD_CONTROL, 
        R_NUMERIC_PASSWORD_SETTING_PAGE, newpassword, oldpassword );
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
// CTestSDKSettingPages::TestSettingpagesPasswordUpdateSettingLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordUpdateSettingLL( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> buffer( KTestString );
    TBuf< KBufSize > newpassword( KNewPassword );
    TBuf< KBufSize > oldpassword( KOldPassword );
    CTestPasswordSettingPage* pageDialog = new( ELeave ) CTestPasswordSettingPage( &buffer, KOne, KZero, KZero, R_NUMERIC_PASSWORD_SETTING_PAGE, newpassword, oldpassword );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->DoUpdateSettingL();
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordAcceptSettingLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordAcceptSettingLL( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> buffer( KTestString );
    TBuf< KBufSize > newpassword( KNewPassword );
    TBuf< KBufSize > oldpassword( KOldPassword );
    CTestPasswordSettingPage* pageDialog = new( ELeave ) CTestPasswordSettingPage( &buffer, KOne, KZero, KZero, R_NUMERIC_PASSWORD_SETTING_PAGE, newpassword, oldpassword );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->DoAcceptSettingL();
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordHandleControlEventLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordHandleControlEventLL( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> buffer( KTestString );
    TBuf< KBufSize > newpassword( KNewPassword );
    TBuf< KBufSize > oldpassword( KOldPassword );
    CTestPasswordSettingPage* pageDialog = new( ELeave ) CTestPasswordSettingPage( &buffer, KOne, KZero, KZero, R_NUMERIC_PASSWORD_SETTING_PAGE, newpassword, oldpassword );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->SetUpdateMode( CAknSettingPage::EUpdateWhenChanged );
    pageDialog->DoHandleControlEventL( NULL, MCoeControlObserver::EEventStateChanged );
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordPostDisplayInitLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordPostDisplayInitLL( CStifItemParser& /*aItem*/ )
    {
    TBuf<KBufSize> buffer( KTestString );
    TBuf< KBufSize > newpassword( KNewPassword );
    TBuf< KBufSize > oldpassword( KOldPassword );
    CTestPasswordSettingPage* pageDialog = new( ELeave ) CTestPasswordSettingPage( &buffer, KOne, KZero, KZero, R_NUMERIC_PASSWORD_SETTING_PAGE, newpassword, oldpassword );
    CleanupStack::PushL( pageDialog );
    pageDialog->DoPostDisplayInitL();
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordPostDisplayCheckLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordPostDisplayCheckLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KBufSize > newpassword( KNewPassword );
    TBuf< KBufSize > oldpassword( KOldPassword );
    CTestPasswordSettingPage* pageDialog = new( ELeave ) CTestPasswordSettingPage( &buffer, KOne, 
        EAknCtNumericSecretEditor, R_NUMERIC_PASSWORD_CONTROL, 
        R_NUMERIC_PASSWORD_SETTING_PAGE, newpassword, oldpassword );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    pageDialog->GetPostDisplayCheckL();
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordOkToExitLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordOkToExitLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KBufSize > newpassword( KNewPassword );
    TBuf< KBufSize > oldpassword( KOldPassword );
    CTestPasswordSettingPage* pageDialog = new( ELeave ) CTestPasswordSettingPage( &buffer, KOne, 
        EAknCtNumericSecretEditor, R_NUMERIC_PASSWORD_CONTROL, 
        R_NUMERIC_PASSWORD_SETTING_PAGE, newpassword, oldpassword );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    TBool flag = pageDialog->DoOkToExitL( EFalse );
    STIF_ASSERT_TRUE( flag );
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KBufSize > newpassword( KNewPassword );
    TBuf< KBufSize > oldpassword( KOldPassword );
    CTestPasswordSettingPage* pageDialog = new( ELeave ) CTestPasswordSettingPage( &buffer, KOne, 
        EAknCtNumericSecretEditor, R_NUMERIC_PASSWORD_CONTROL, 
        R_NUMERIC_PASSWORD_SETTING_PAGE, newpassword, oldpassword );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    pageDialog->DoSizeChanged();

    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordDrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordDrawL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KBufSize > newpassword( KNewPassword );
    TBuf< KBufSize > oldpassword( KOldPassword );
    CTestPasswordSettingPage* pageDialog = new( ELeave ) CTestPasswordSettingPage( &buffer, KOne, 
        EAknCtNumericSecretEditor, R_NUMERIC_PASSWORD_CONTROL, 
        R_NUMERIC_PASSWORD_SETTING_PAGE, newpassword, oldpassword );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    TRect rect( 0, 0, 1, 1 );
    pageDialog->DoActivateGc();
    pageDialog->DoDraw( rect );
    pageDialog->DoDeactivateGc();

    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordUpdateTextLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordUpdateTextLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KBufSize > newpassword( KNewPassword );
    TBuf< KBufSize > oldpassword( KOldPassword );
    CTestPasswordSettingPage* pageDialog = new( ELeave ) CTestPasswordSettingPage( &buffer, KOne, 
        EAknCtNumericSecretEditor, R_NUMERIC_PASSWORD_CONTROL, 
        R_NUMERIC_PASSWORD_SETTING_PAGE, newpassword, oldpassword );
    CleanupStack::PushL( pageDialog );
    pageDialog->ConstructL();
    pageDialog->UpdateTextL();
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordExecuteOldPasswordConfirmationLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordExecuteOldPasswordConfirmationLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KBufSize > newpassword( KNewPassword );
    TBuf< KBufSize > oldpassword( KOldPassword );
    CTestPasswordSettingPage* pageDialog = new( ELeave ) CTestPasswordSettingPage( &buffer, KOne, 
        EAknCtNumericSecretEditor, R_NUMERIC_PASSWORD_CONTROL, 
        R_NUMERIC_PASSWORD_SETTING_PAGE, newpassword, oldpassword );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    pageDialog->DoExecuteOldPasswordConfirmationL( oldpassword, KZero );
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordExecuteNewPasswordConfirmationLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordExecuteNewPasswordConfirmationLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KBufSize > newpassword( KNewPassword );
    TBuf< KBufSize > oldpassword( KOldPassword );
    CTestPasswordSettingPage* pageDlg = new( ELeave ) CTestPasswordSettingPage( &buffer, KOne, 
        EAknCtNumericSecretEditor, R_NUMERIC_PASSWORD_CONTROL, 
        R_NUMERIC_PASSWORD_SETTING_PAGE, newpassword, oldpassword );
    CleanupStack::PushL( pageDlg );
    
    pageDlg->ConstructL();
    pageDlg->DoExecuteNewPasswordConfirmationL( newpassword, KZero );
    
    CleanupStack::PopAndDestroy( pageDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordComparePasswordsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordComparePasswordsL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KBufSize > newpassword( KNewPassword );
    TBuf< KBufSize > oldpassword( KOldPassword );
    CTestPasswordSettingPage* pageDialog = new( ELeave ) CTestPasswordSettingPage( &buffer, KOne, 
        EAknCtNumericSecretEditor, R_NUMERIC_PASSWORD_CONTROL, 
        R_NUMERIC_PASSWORD_SETTING_PAGE, newpassword, oldpassword );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    TInt result = pageDialog->DoComparePasswords( oldpassword, newpassword, CAknPasswordSettingPage::ECaseSensitive );
    STIF_ASSERT_NOT_EQUALS( KZero, result );
    
    result = pageDialog->DoComparePasswords( oldpassword, oldpassword, CAknPasswordSettingPage::ECaseSensitive );
    STIF_ASSERT_EQUALS( KZero, result );
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordOldPasswordConfirmationResourceIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordOldPasswordConfirmationResourceIdL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KBufSize > newpassword( KNewPassword );
    TBuf< KBufSize > oldpassword( KOldPassword );
    CTestPasswordSettingPage* pageDialog = new( ELeave ) CTestPasswordSettingPage( &buffer, KOne, 
        EAknCtNumericSecretEditor, R_NUMERIC_PASSWORD_CONTROL, 
        R_NUMERIC_PASSWORD_SETTING_PAGE, newpassword, oldpassword );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    TInt oldPasswordId = pageDialog->DoOldPasswordConfirmationResourceId();
    STIF_ASSERT_EQUALS( KZero, oldPasswordId );
    
    pageDialog->SetOldPasswordConfirmationResourceId( R_PASSWORD_CONFIRMATION );
    oldPasswordId = pageDialog->DoOldPasswordConfirmationResourceId();
    STIF_ASSERT_EQUALS( R_PASSWORD_CONFIRMATION, oldPasswordId );
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordNewPasswordConfirmationResourceIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordNewPasswordConfirmationResourceIdL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KBufSize > newpassword( KNewPassword );
    TBuf< KBufSize > oldpassword( KOldPassword );
    CTestPasswordSettingPage* pageDialog = new( ELeave ) CTestPasswordSettingPage( &buffer, KOne, 
        EAknCtNumericSecretEditor, R_NUMERIC_PASSWORD_CONTROL, 
        R_NUMERIC_PASSWORD_SETTING_PAGE, newpassword, oldpassword );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    TInt newPasswordId = pageDialog->DoNewPasswordConfirmationResourceId();
    STIF_ASSERT_EQUALS( KZero, newPasswordId );
    
    pageDialog->SetNewPasswordConfirmationResourceId( R_PASSWORD_CONFIRMATION );
    newPasswordId = pageDialog->DoNewPasswordConfirmationResourceId();
    STIF_ASSERT_EQUALS( R_PASSWORD_CONFIRMATION, newPasswordId );
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordReadConfirmationResourceLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordReadConfirmationResourceLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KBufSize > newpassword( KNewPassword );
    TBuf< KBufSize > oldpassword( KOldPassword );
    CTestPasswordSettingPage* pageDialog = new( ELeave ) CTestPasswordSettingPage( &buffer, KOne, 
        EAknCtNumericSecretEditor, R_NUMERIC_PASSWORD_CONTROL, 
        R_NUMERIC_PASSWORD_SETTING_PAGE, newpassword, oldpassword );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    SAknConfirmationResource confResources;
    pageDialog->DoReadConfirmationResourceL( R_PASSWORD_CONFIRMATION, confResources );
    STIF_ASSERT_EQUALS( R_TEXT_QUERY_DIALOG, confResources.iEntryQueryResourceId );
    STIF_ASSERT_EQUALS( R_SUCCESSFUL_NOTE, confResources.iSuccessNoteResourceId );
    STIF_ASSERT_EQUALS( R_FAIL_NOTE, confResources.iFailureNoteResourceId );
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordDoPasswordConfirmationLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordDoPasswordConfirmationLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KBufSize > newpassword( KNewPassword );
    TBuf< KBufSize > oldpassword( KOldPassword );
    CTestPasswordSettingPage* pageDlg = new( ELeave ) CTestPasswordSettingPage( &buffer, KOne, 
        EAknCtNumericSecretEditor, R_NUMERIC_PASSWORD_CONTROL, 
        R_NUMERIC_PASSWORD_SETTING_PAGE, newpassword, oldpassword );
    CleanupStack::PushL( pageDlg );
    
    pageDlg->ConstructL();
    TInt tries(0);
    pageDlg->DoDoPasswordConfirmationL( newpassword, R_PASSWORD_CONFIRMATION,
        CAknPasswordSettingPage::ECaseInsensitive, tries );
    
    CleanupStack::PopAndDestroy( pageDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordNewPasswordL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordNewPasswordL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KBufSize > newpassword( KNewPassword );
    TBuf< KBufSize > oldpassword( KOldPassword );
    CTestPasswordSettingPage* pageDialog = new( ELeave ) CTestPasswordSettingPage( &buffer, KOne, 
        EAknCtNumericSecretEditor, R_NUMERIC_PASSWORD_CONTROL, 
        R_NUMERIC_PASSWORD_SETTING_PAGE, newpassword, oldpassword );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    TBuf< KBufSize > returnNewPassword = pageDialog->DoNewPassword();
    STIF_ASSERT_EQUALS( newpassword, returnNewPassword );
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordOldPasswordL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordOldPasswordL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KBufSize > newpassword( KNewPassword );
    TBuf< KBufSize > oldpassword( KOldPassword );
    CTestPasswordSettingPage* pageDialog = new( ELeave ) CTestPasswordSettingPage( &buffer, KOne, 
        EAknCtNumericSecretEditor, R_NUMERIC_PASSWORD_CONTROL, 
        R_NUMERIC_PASSWORD_SETTING_PAGE, newpassword, oldpassword );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    TBuf< KBufSize > returnOldPassword = pageDialog->DoOldPassword();
    STIF_ASSERT_EQUALS( oldpassword, returnOldPassword );
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordWriteInternalStateLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordWriteInternalStateLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KBufSize > newpassword( KNewPassword );
    TBuf< KBufSize > oldpassword( KOldPassword );
    CTestPasswordSettingPage* pageDialog = new( ELeave ) CTestPasswordSettingPage( &buffer, KOne, 
        EAknCtNumericSecretEditor, R_NUMERIC_PASSWORD_CONTROL, 
        R_NUMERIC_PASSWORD_SETTING_PAGE, newpassword, oldpassword );
    CleanupStack::PushL( pageDialog );
    pageDialog->ConstructL();
    
    RDesWriteStream stream;
    CleanupClosePushL( stream );
    HBufC8* hbuf = HBufC8::NewL( KHBufSize );
    CleanupStack::PushL( hbuf );
    TPtr8 ptr = hbuf->Des();
    stream.Open( ptr );
    pageDialog->DoWriteInternalStateL( stream );
    stream.CommitL();
    stream.Close();
    
    CleanupStack::PopAndDestroy( KThree );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordAlphaConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordAlphaConstructorL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > newPassword( KNewPassword );
    TBuf< KBufSize > oldPassword( KOldPassword );
    CAknAlphaPasswordSettingPage* pageDlg = new( ELeave ) CAknAlphaPasswordSettingPage( R_ALPHA_PASSWORD_SETTING_PAGE,
        newPassword, oldPassword );
    CleanupStack::PushL( pageDlg );
    STIF_ASSERT_NOT_NULL( pageDlg );
    CleanupStack::PopAndDestroy( pageDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordAlphaConstructorLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordAlphaConstructorLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KBufSize > newPassword( KNewPassword );
    TBuf< KBufSize > oldPassword( KOldPassword );
    CAknAlphaPasswordSettingPage* pageDlg = new( ELeave ) CAknAlphaPasswordSettingPage( &buffer, KOne, 
        EEikCtSecretEd, R_SETTINGLIST_ALPHA_PASSWORD_CONTROL, R_ALPHA_PASSWORD_SETTING_PAGE,
        newPassword, oldPassword );
    CleanupStack::PushL( pageDlg );
    STIF_ASSERT_NOT_NULL( pageDlg );
    CleanupStack::PopAndDestroy( pageDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordAlphaConstructLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordAlphaConstructLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KBufSize > newPassword( KNewPassword );
    TBuf< KBufSize > oldPassword( KOldPassword );
    CAknAlphaPasswordSettingPage* pageDlg = new( ELeave ) CAknAlphaPasswordSettingPage( &buffer, KOne, 
        EEikCtSecretEd, R_SETTINGLIST_ALPHA_PASSWORD_CONTROL, R_ALPHA_PASSWORD_SETTING_PAGE,
        newPassword, oldPassword );
    CleanupStack::PushL( pageDlg );
    pageDlg->ConstructL();
    CleanupStack::PopAndDestroy( pageDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordAlphaAlphaPasswordEditorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordAlphaAlphaPasswordEditorL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KBufSize > newPassword( KNewPassword );
    TBuf< KBufSize > oldPassword( KOldPassword );
    CAknAlphaPasswordSettingPage* pageDlg = new( ELeave ) CAknAlphaPasswordSettingPage( &buffer, KOne, 
        EEikCtSecretEd, R_SETTINGLIST_ALPHA_PASSWORD_CONTROL, R_ALPHA_PASSWORD_SETTING_PAGE,
        newPassword, oldPassword );
    CleanupStack::PushL( pageDlg );
    
    pageDlg->ConstructL();
    CEikSecretEditor* editorControl = pageDlg->AlphaPasswordEditor();
    STIF_ASSERT_NOT_NULL( editorControl );
    
    CleanupStack::PopAndDestroy( pageDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordAlphaHandlePointerEventLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordAlphaHandlePointerEventLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KBufSize > newPassword( KNewPassword );
    TBuf< KBufSize > oldPassword( KOldPassword );
    CAknAlphaPasswordSettingPage* pageDlg = new( ELeave ) CAknAlphaPasswordSettingPage( &buffer, KOne, 
        EEikCtSecretEd, R_SETTINGLIST_ALPHA_PASSWORD_CONTROL, R_ALPHA_PASSWORD_SETTING_PAGE,
        newPassword, oldPassword );
    CleanupStack::PushL( pageDlg );
    
    pageDlg->ConstructL();
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    pageDlg->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( pageDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordAlphaDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordAlphaDestructorL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KBufSize > newPassword( KNewPassword );
    TBuf< KBufSize > oldPassword( KOldPassword );
    CAknAlphaPasswordSettingPage* pageDlg = new( ELeave ) CAknAlphaPasswordSettingPage( &buffer, KOne, 
        EEikCtSecretEd, R_SETTINGLIST_ALPHA_PASSWORD_CONTROL, R_ALPHA_PASSWORD_SETTING_PAGE,
        newPassword, oldPassword );
    CleanupStack::PushL( pageDlg );
    CleanupStack::PopAndDestroy( pageDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordAlphaUpdateTextLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordAlphaUpdateTextLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KBufSize > newPassword( KNewPassword );
    TBuf< KBufSize > oldPassword( KOldPassword );
    CTestAlphaPasswordSettingPage* pageDlg = new( ELeave ) CTestAlphaPasswordSettingPage( &buffer, KOne, 
        EEikCtSecretEd, R_SETTINGLIST_ALPHA_PASSWORD_CONTROL, R_ALPHA_PASSWORD_SETTING_PAGE,
        newPassword, oldPassword );
    CleanupStack::PushL( pageDlg );
    
    pageDlg->ConstructL();
    pageDlg->DoUpdateTextL();
    
    CleanupStack::PopAndDestroy( pageDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordAlphaComparePasswordsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordAlphaComparePasswordsL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KBufSize > newPassword( KNewPassword );
    TBuf< KBufSize > oldPassword( KOldPassword );
    CTestAlphaPasswordSettingPage* pageDlg = new( ELeave ) CTestAlphaPasswordSettingPage( &buffer, KOne, 
        EEikCtSecretEd, R_SETTINGLIST_ALPHA_PASSWORD_CONTROL, R_ALPHA_PASSWORD_SETTING_PAGE,
        newPassword, oldPassword );
    CleanupStack::PushL( pageDlg );
    
    pageDlg->ConstructL();
    TInt result = pageDlg->DoComparePasswords( oldPassword, newPassword, CAknPasswordSettingPage::ECaseSensitive );
    STIF_ASSERT_NOT_EQUALS( KZero, result );
    result = pageDlg->DoComparePasswords( oldPassword, oldPassword, CAknPasswordSettingPage::ECaseSensitive );
    STIF_ASSERT_EQUALS( KZero, result );
    
    result = pageDlg->DoComparePasswords( oldPassword, newPassword, CAknPasswordSettingPage::ECaseInsensitive );
    STIF_ASSERT_NOT_EQUALS( KZero, result );
    result = pageDlg->DoComparePasswords( oldPassword, oldPassword, CAknPasswordSettingPage::ECaseInsensitive );
    STIF_ASSERT_EQUALS( KZero, result );
    
    CleanupStack::PopAndDestroy( pageDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordAlphaWriteInternalStateLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordAlphaWriteInternalStateLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KBufSize > newPassword( KNewPassword );
    TBuf< KBufSize > oldPassword( KOldPassword );
    CTestAlphaPasswordSettingPage* pageDlg = new ( ELeave ) CTestAlphaPasswordSettingPage( &buffer, KOne, 
        EEikCtSecretEd, R_SETTINGLIST_ALPHA_PASSWORD_CONTROL, R_ALPHA_PASSWORD_SETTING_PAGE,
        newPassword, oldPassword );
    CleanupStack::PushL( pageDlg );
    pageDlg->ConstructL();
    
    RDesWriteStream stream;
    CleanupClosePushL( stream );
    HBufC8* hbuf = HBufC8::NewL( KHBufSize );
    CleanupStack::PushL( hbuf );
    TPtr8 ptr = hbuf->Des();
    stream.Open( ptr );
    pageDlg->DoWriteInternalStateL( stream );
    stream.CommitL();
    stream.Close();
    
    CleanupStack::PopAndDestroy( KThree );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordNumericConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordNumericConstructorL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > newPassword( KNewPassword );
    TBuf< KBufSize > oldPassword( KOldPassword );
    CAknNumericPasswordSettingPage* pageDlg = new( ELeave ) CAknNumericPasswordSettingPage( 
        R_NUMERIC_PASSWORD_SETTING_PAGE, newPassword, oldPassword );
    CleanupStack::PushL( pageDlg );
    STIF_ASSERT_NOT_NULL( pageDlg );
    CleanupStack::PopAndDestroy( pageDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordNumericConstructorLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordNumericConstructorLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KBufSize > newPassword( KNewPassword );
    TBuf< KBufSize > oldPassword( KOldPassword );
    CAknNumericPasswordSettingPage* pageDlg = new( ELeave ) CAknNumericPasswordSettingPage( &buffer, KOne, 
        EAknCtNumericSecretEditor, R_NUMERIC_PASSWORD_CONTROL, R_NUMERIC_PASSWORD_SETTING_PAGE,
        newPassword, oldPassword );
    CleanupStack::PushL( pageDlg );
    STIF_ASSERT_NOT_NULL( pageDlg );
    CleanupStack::PopAndDestroy( pageDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordNumericConstructLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordNumericConstructLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KBufSize > newPassword( KNewPassword );
    TBuf< KBufSize > oldPassword( KOldPassword );
    CAknNumericPasswordSettingPage* pageDlg = new( ELeave ) CAknNumericPasswordSettingPage( &buffer, KOne, 
        EAknCtNumericSecretEditor, R_NUMERIC_PASSWORD_CONTROL, R_NUMERIC_PASSWORD_SETTING_PAGE,
        newPassword, oldPassword );
    CleanupStack::PushL( pageDlg );
    pageDlg->ConstructL();
    CleanupStack::PopAndDestroy( pageDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordNumericNumericPasswordEditorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordNumericNumericPasswordEditorL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KBufSize > newPassword( KNewPassword );
    TBuf< KBufSize > oldPassword( KOldPassword );
    CAknNumericPasswordSettingPage* pageDlg = new( ELeave ) CAknNumericPasswordSettingPage( &buffer, KOne, 
        EAknCtNumericSecretEditor, R_NUMERIC_PASSWORD_CONTROL, R_NUMERIC_PASSWORD_SETTING_PAGE,
        newPassword, oldPassword );
    CleanupStack::PushL( pageDlg );
    pageDlg->ConstructL();
    
    CAknNumericSecretEditor* editorControl = pageDlg->NumericPasswordEditor();
    STIF_ASSERT_NOT_NULL( editorControl );
    
    CleanupStack::PopAndDestroy( pageDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordNumericHandlePointerEventLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordNumericHandlePointerEventLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KBufSize > newPassword( KNewPassword );
    TBuf< KBufSize > oldPassword( KOldPassword );
    CAknNumericPasswordSettingPage* pageDlg = new( ELeave ) CAknNumericPasswordSettingPage( &buffer, KOne, 
        EAknCtNumericSecretEditor, R_NUMERIC_PASSWORD_CONTROL, R_NUMERIC_PASSWORD_SETTING_PAGE,
        newPassword, oldPassword );
    CleanupStack::PushL( pageDlg );
    
    pageDlg->ConstructL();
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    pageDlg->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( pageDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordNumericDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordNumericDestructorL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KBufSize > newPassword( KNewPassword );
    TBuf< KBufSize > oldPassword( KOldPassword );
    CAknNumericPasswordSettingPage* pageDlg = new( ELeave ) CAknNumericPasswordSettingPage( &buffer, KOne, 
        EAknCtNumericSecretEditor, R_NUMERIC_PASSWORD_CONTROL, R_NUMERIC_PASSWORD_SETTING_PAGE,
        newPassword, oldPassword );
    CleanupStack::PushL( pageDlg );
    CleanupStack::PopAndDestroy( pageDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordNumericUpdateTextLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordNumericUpdateTextLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KBufSize > newPassword( KNewPassword );
    TBuf< KBufSize > oldPassword( KOldPassword );
    CTestNumbericPasswordSettingPage* pageDlg = new( ELeave ) CTestNumbericPasswordSettingPage( &buffer, KOne, 
        EAknCtNumericSecretEditor, R_NUMERIC_PASSWORD_CONTROL, R_NUMERIC_PASSWORD_SETTING_PAGE,
        newPassword, oldPassword );
    CleanupStack::PushL( pageDlg );
    
    pageDlg->ConstructL();
    pageDlg->DoUpdateTextL();
    
    CleanupStack::PopAndDestroy( pageDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesPasswordNumericWriteInternalStateLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesPasswordNumericWriteInternalStateLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KBufSize > newPassword( KNewPassword );
    TBuf< KBufSize > oldPassword( KOldPassword );
    CTestNumbericPasswordSettingPage* pageDlg = new( ELeave ) CTestNumbericPasswordSettingPage( &buffer, KOne, 
        EAknCtNumericSecretEditor, R_NUMERIC_PASSWORD_CONTROL, R_NUMERIC_PASSWORD_SETTING_PAGE,
        newPassword, oldPassword );
    CleanupStack::PushL( pageDlg );
    pageDlg->ConstructL();
    
    RDesWriteStream stream;
    CleanupClosePushL( stream );
    HBufC8* hbuf = HBufC8::NewL( KHBufSize );
    CleanupStack::PushL( hbuf );
    TPtr8 ptr = hbuf->Des();
    stream.Open( ptr );
    pageDlg->DoWriteInternalStateL( stream );
    stream.CommitL();
    stream.Close();
        
    CleanupStack::PopAndDestroy( KThree );
    return KErrNone;
    }

//End file


