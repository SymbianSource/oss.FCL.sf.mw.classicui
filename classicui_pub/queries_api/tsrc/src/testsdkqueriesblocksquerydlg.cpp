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
* Description:  Test aknquerydialog.h
*
*/

//INCLUDE
#include <aknquerydialog.h>
#include <testsdkqueries.rsg>
#include <in_sock.h>
#include <aknquerycontrol.h>
#include <avkon.mbg>

#include "testsdkqueries.h"
#include "testsdkaknquerydialogprotected.h"
#include "testsdkqueriescontainer.h"
#include "testsdkaknquerycontrolprotected.h"

const TInt KZero = 0;
const TInt KOne = 1;
const TInt KFive = 5;
const TInt KTen = 10;
const TInt KBufSize = 32;
const TReal KRealvalue = 2.12345; 
const TReal KMaxRealvalue = 1000.3233;
const TUint32 KAddrValue = 0x11111111;
const TInt KHundred = 100;
const TUint32 KMaxAddrValue = 0xffffffff;

_LIT( KTestString, "It is a test!" );
_LIT( KTestStringReplace, "It is a test too!" );
_LIT( KTestTime, "20000111:200600.000000" );
_LIT( KTestMinTime, "10000111:100100.000000" );
_LIT( KTestMbmFile,"\\resource\\apps\\avkon2.mbm" );

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgNewLOneL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgNewLOneL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryDialog* dlg = CAknQueryDialog::NewL();
    CleanupStack::PushL( dlg );
    
    STIF_ASSERT_NOT_NULL( dlg );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgNewLTwoL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgNewLTwoL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > message( KTestString );
    
    CAknQueryDialog* dlg = CAknQueryDialog::NewL( message );
    CleanupStack::PushL( dlg );
    
    STIF_ASSERT_NOT_NULL( dlg );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgNewLThreeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgNewLThreeL( CStifItemParser& /*aItem*/ )
    {
    TInt number = KTen;
    
    CAknQueryDialog* dlg = CAknQueryDialog::NewL( number );
    CleanupStack::PushL( dlg );
    
    STIF_ASSERT_NOT_NULL( dlg );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgNewLFourL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgNewLFourL( CStifItemParser& /*aItem*/ )
    {
    TTime time( KTestTime );
    
    CAknQueryDialog* dlg = CAknQueryDialog::NewL( time );
    CleanupStack::PushL( dlg );
    
    STIF_ASSERT_NOT_NULL( dlg );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgNewLFiveL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgNewLFiveL( CStifItemParser& /*aItem*/ )
    {
    TTimeIntervalSeconds time = KTen;
    
    CAknQueryDialog* dlg = CAknQueryDialog::NewL( time );
    CleanupStack::PushL( dlg );
    
    STIF_ASSERT_NOT_NULL( dlg );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgNewLSixL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgNewLSixL( CStifItemParser& /*aItem*/ )
    {
    TReal number( KRealvalue );
    
    CAknQueryDialog* dlg = CAknQueryDialog::NewL( number );
    CleanupStack::PushL( dlg );
    
    STIF_ASSERT_NOT_NULL( dlg );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgNewLSevenL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgNewLSevenL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddr( KAddrValue );
    
    CAknQueryDialog* dlg = CAknQueryDialog::NewL( mAddr );
    CleanupStack::PushL( dlg );
    
    STIF_ASSERT_NOT_NULL( dlg );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgNewLEightL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgNewLEightL( CStifItemParser& /*aItem*/ )
    {
    TTime time( KTestTime );
    TCoordinate coord( 01.00, 01.0 );
    TLocality loc( coord, 0.1 );
    TPosition position( loc, time );
    
    CAknQueryDialog* dlg = CAknQueryDialog::NewL( position );
    CleanupStack::PushL( dlg );
    
    STIF_ASSERT_NULL( dlg );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgDestructorL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddr( KAddrValue );
    CAknQueryDialog* dlg = CAknQueryDialog::NewL( mAddr );
    CleanupStack::PushL( dlg );
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgConstructorOneL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgConstructorOneL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryDialog* dlg = new( ELeave ) CAknQueryDialog( CAknQueryDialog ::ENoTone );
    CleanupStack::PushL( dlg );
    STIF_ASSERT_NOT_NULL( dlg );
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgQueryHeadingL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgQueryHeadingL( CStifItemParser& /*aItem*/ )
    {
    TInt number = KTen;
    
    CAknQueryDialog* dlg = CAknQueryDialog::NewL( number );
    CleanupStack::PushL( dlg );
    
    CAknPopupHeadingPane* heading = dlg->QueryHeading();
    STIF_ASSERT_NULL( heading );
    
    dlg->PrepareLC( R_MESSAGE_DIALOG );
    
    heading = dlg->QueryHeading();
    dlg->Heading();
    
    STIF_ASSERT_NOT_NULL( heading );
    
    CleanupStack::PopAndDestroy( dlg );
    CleanupStack::Pop( KOne );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgHeadingL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgHeadingL( CStifItemParser& aItem )
    {
    TInt err = TestQdlgQueryHeadingL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgSetPromptL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgSetPromptL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryDialog* dlg = new( ELeave ) CAknQueryDialog( CAknQueryDialog ::ENoTone );    
    dlg->PrepareLC( R_AKNEXQUERY_NUMBER_LAYOUT );
    
    CTestCAknQueryDialog* testDlg = static_cast<CTestCAknQueryDialog*>( dlg );
    
    TBuf< KBufSize > text( KTestString );
    
    TPtrC returnPromptOne = testDlg->Prompt();
    STIF_ASSERT_NOT_NULL( &returnPromptOne );
    
    dlg->SetPromptL( text );
    
    TPtrC returnPromptTwo = testDlg->Prompt();
    STIF_ASSERT_NOT_NULL( &returnPromptTwo );
    STIF_ASSERT_EQUALS( returnPromptTwo, ( TPtrC )( text ));
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgMakeLeftSoftkeyVisibleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgMakeLeftSoftkeyVisibleL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryDialog* dlg = CAknQueryDialog::NewL();    
    dlg->PrepareLC( R_AKNEXQUERY_CONFIRMATION_QUERY );
    
    dlg->MakeLeftSoftkeyVisible( ETrue );
    dlg->MakeLeftSoftkeyVisible( EFalse );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgSetEmergencyCallSupportL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgSetEmergencyCallSupportL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryDialog* dlg = CAknQueryDialog::NewL();
    
    dlg->PrepareLC( R_AKNEXQUERY_CONFIRMATION_QUERY );
    
    dlg->SetEmergencyCallSupport( ETrue );
    dlg->SetEmergencyCallSupport( EFalse );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgRemoveEditorIndicatorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgRemoveEditorIndicatorL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryDialog* dlg = CAknQueryDialog::NewL(); 
    dlg->PrepareLC( R_AKNEXQUERY_CONFIRMATION_QUERY );
    
    dlg->RemoveEditorIndicator();
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgSetPredictiveTextInputPermittedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgSetPredictiveTextInputPermittedL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryDialog* dlg = CAknQueryDialog::NewL();    
    dlg->PrepareLC( R_AKNEXQUERY_CONFIRMATION_QUERY );
    TBool temp = ETrue;
    dlg->SetPredictiveTextInputPermitted( temp );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgRunLDL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgRunLDL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryDialog* dlg = CAknQueryDialog::NewL();    
    dlg->PrepareLC( R_AKNEXQUERY_CONFIRMATION_QUERY );
    
    dlg->RunLD();
    
        return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgExecuteLDOneL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgExecuteLDOneL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryDialog* dlg = CAknQueryDialog::NewL();
    CleanupStack::PushL( dlg );
    
    dlg->ExecuteLD( R_AKNEXQUERY_CONFIRMATION_QUERY );
    
    CleanupStack::Pop( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgExecuteLDTwoL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgExecuteLDTwoL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryDialog* dlg = CAknQueryDialog::NewL();
    CleanupStack::PushL( dlg );
    
    TBuf< KBufSize > message( KTestString );
    
    dlg->ExecuteLD( R_AKNEXQUERY_CONFIRMATION_QUERY, message );
    
    CleanupStack::Pop( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {
    TInt number = KTen;
    
    CAknQueryDialog* dlg = CAknQueryDialog::NewL( number );
    
    dlg->PrepareLC( R_MESSAGE_DIALOG );
    
    TKeyEvent event;
    event.iCode = EKeyOK;
    
    TKeyResponse reponse = dlg->OfferKeyEventL( event, EEventKey );
    STIF_ASSERT_EQUALS( EKeyWasConsumed, reponse );
    
    event.iCode = EKeyEnter;
    
    dlg->OfferKeyEventL( event, EEventKey );
    STIF_ASSERT_EQUALS( EKeyWasConsumed, reponse );
    
    event.iScanCode = EStdKeyHash;
    
    dlg->OfferKeyEventL( event, EEventKey );
    STIF_ASSERT_EQUALS( EKeyWasConsumed, reponse );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryDialog* dlg = CAknQueryDialog::NewL();
    dlg->PrepareLC( R_AKNEXQUERY_CONFIRMATION_QUERY );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = KZero;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    TInt err = KErrNone;
    TRAP( err, dlg->HandlePointerEventL( event ) );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgMaxTextLengthOneL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgMaxTextLengthOneL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryDialog* dlg = CAknQueryDialog::NewL();    
    dlg->PrepareLC( R_AKNEXQUERY_NUMBER_LAYOUT );
    
    CTestCAknQueryDialog* testDlg = static_cast<CTestCAknQueryDialog*>( dlg );
    CAknQueryControl* control = testDlg->QueryControl();
    
    control->SetTextEntryLength( KFive );
    
    TBuf< KBufSize > buffer( KTestString );
    
    TInt length = dlg->MaxTextLength( control, buffer, KTen );
    STIF_ASSERT_EQUALS( KTen, length );
    
    length = dlg->MaxTextLength( control, buffer, KHundred );
    STIF_ASSERT_EQUALS( KFive, length );
    
    control->SetTextEntryLength( KZero );
    
    length = dlg->MaxTextLength( control, buffer, KHundred );
    STIF_ASSERT_EQUALS( KBufSize, length );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgSetSizeAndPositionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgSetSizeAndPositionL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryDialog* dlg = CAknQueryDialog::NewL();   
    dlg->PrepareLC( R_AKNEXQUERY_CONFIRMATION_QUERY );
    
    CTestCAknQueryDialog* testDlg = static_cast<CTestCAknQueryDialog*>( dlg );
    
    testDlg->SetSizeAndPosition( iContainer->Rect().Size() );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgPreLayoutDynInitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgPreLayoutDynInitL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryDialog* dlg = CAknQueryDialog::NewL();    
    dlg->PrepareLC( R_AKNEXQUERY_CONFIRMATION_QUERY );
    
    CTestCAknQueryDialog* testDlg = static_cast<CTestCAknQueryDialog*>( dlg );
    
    testDlg->PreLayoutDynInitL();
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgPostLayoutDynInitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgPostLayoutDynInitL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryDialog* dlg = CAknQueryDialog::NewL();    
    dlg->PrepareLC( R_AKNEXQUERY_CONFIRMATION_QUERY );
    
    CTestCAknQueryDialog* testDlg = static_cast<CTestCAknQueryDialog*>( dlg );
    
    testDlg->PostLayoutDynInitL();
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgOkToExitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgOkToExitL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryDialog* dlg = CAknQueryDialog::NewL();    
    dlg->PrepareLC( R_AKNEXQUERY_NUMBER_LAYOUT );
    
    CTestCAknQueryDialog* testDlg = static_cast<CTestCAknQueryDialog*>( dlg );
    
    TBool flag = testDlg->OkToExitL( EAknSoftkeyEmergencyCall );
    STIF_ASSERT_TRUE( flag );
    
    flag = testDlg->OkToExitL( EEikBidOk );
    STIF_ASSERT_TRUE( flag );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgHandleQueryEditorSizeEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgHandleQueryEditorSizeEventL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryDialog* dlg = CAknQueryDialog::NewL();
    CleanupStack::PushL( dlg );
    
    dlg->PrepareLC( R_AKNEXQUERY_NUMBER_LAYOUT );
    
    CTestCAknQueryDialog* testDlg = static_cast<CTestCAknQueryDialog*>( dlg );
    CAknQueryControl* control = testDlg->QueryControl();
    
    TBool flag = dlg->HandleQueryEditorSizeEventL( control,
        MAknQueryControlObserver::EQueryControltSizeChanging );
    STIF_ASSERT_FALSE( flag );
    
    CleanupStack::PopAndDestroy( dlg );
    CleanupStack::Pop( KOne );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgHandleQueryEditorStateEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgHandleQueryEditorStateEventL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryDialog* dlg = CAknQueryDialog::NewL();
    dlg->PrepareLC( R_AKNEXQUERY_NUMBER_LAYOUT );
    
    CTestCAknQueryDialog* testDlg = static_cast<CTestCAknQueryDialog*>( dlg );
    CAknQueryControl* control = testDlg->QueryControl();
    
    dlg->SetContainerWindowL( *iContainer );
    
    TBool flag = dlg->HandleQueryEditorStateEventL( control, 
        MAknQueryControlObserver::EEmergencyCallAttempted, 
        MAknQueryControlObserver::EEditorValueValid );
    STIF_ASSERT_FALSE( flag );
    
    CleanupStack::Pop( dlg );
    
    CAknQueryDialog* dlgTwo = CAknQueryDialog::NewL();    
    dlgTwo->PrepareLC( R_AKNEXQUERY_NUMBER_LAYOUT );
    
    CTestCAknQueryDialog* testDlgTwo = static_cast<CTestCAknQueryDialog*>( dlgTwo );
    control = testDlgTwo->QueryControl();
    
    dlgTwo->SetContainerWindowL( *iContainer );
    
    flag = dlgTwo->HandleQueryEditorStateEventL( control, 
        MAknQueryControlObserver::EQueryControlEditorStateChanging, 
        MAknQueryControlObserver::EEditorValueValid );
    STIF_ASSERT_FALSE( flag );
    
    CleanupStack::PopAndDestroy( dlgTwo );
    
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgNeedToDismissQueryL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgNeedToDismissQueryL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryDialog* dlg = CAknQueryDialog::NewL();
    dlg->PrepareLC( R_DEMO_DATA_PIN_QUERY );
    
    TKeyEvent event;
    event.iScanCode = EStdKeySquareBracketLeft;
    
    TBool flag = dlg->NeedToDismissQueryL( event );
    STIF_ASSERT_FALSE( flag );
    
    event.iScanCode = EStdKeyHash;
    
    flag = dlg->NeedToDismissQueryL( event );
    STIF_ASSERT_TRUE( flag );
    
    CleanupStack::Pop( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgDismissQueryL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgDismissQueryL( CStifItemParser& aItem )
    {
    TInt err = TestQdlgNeedToDismissQueryL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgUpdateLeftSoftKeyL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgUpdateLeftSoftKeyL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryDialog* dlg = CAknQueryDialog::NewL();
    
    dlg->PrepareLC( R_AKNEXQUERY_NUMBER_LAYOUT );
    
    CTestCAknQueryDialog* testDlg = static_cast<CTestCAknQueryDialog*>( dlg );
    
    testDlg->UpdateLeftSoftKeyL();
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgDoSetPromptL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgDoSetPromptL( CStifItemParser& aItem )
    {
    TInt err = TestQdlgSetPromptL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgQueryControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgQueryControlL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryDialog* dlg = CAknQueryDialog::NewL();
    CleanupStack::PushL( dlg );
    
    CTestCAknQueryDialog* testDlg = static_cast<CTestCAknQueryDialog*>( dlg );
    
    CAknQueryControl* control = testDlg->QueryControl();
    STIF_ASSERT_NULL( control );
    
    dlg->PrepareLC( R_AKNEXQUERY_NUMBER_LAYOUT );
    
    control = testDlg->QueryControl();
    STIF_ASSERT_NOT_NULL( control );
    
    CleanupStack::PopAndDestroy( dlg );
    CleanupStack::Pop( KOne );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgPromptL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgPromptL( CStifItemParser& aItem )
    {
    TInt err = TestQdlgSetPromptL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgConstructorTwoL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgConstructorTwoL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryDialog* dlg = new( ELeave ) CAknQueryDialog();
    CleanupStack::PushL( dlg );
    STIF_ASSERT_NOT_NULL( dlg );
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgConstructorThreeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgConstructorThreeL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > message( KTestString );
    
    CAknQueryDialog* dlg = new( ELeave ) CAknQueryDialog( message );
    CleanupStack::PushL( dlg );
    STIF_ASSERT_NOT_NULL( dlg );
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgSetHeaderTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgSetHeaderTextL( CStifItemParser& /*aItem*/ )
    {
    TInt number = KTen;
    
    CAknQueryDialog* dlg = CAknQueryDialog::NewL( number );
    CleanupStack::PushL( dlg );
    
    dlg->PrepareLC( R_MESSAGE_DIALOG );
    
    TBuf< KBufSize > heading( KTestString );
    
    dlg->SetHeaderTextL( heading );
    
    CleanupStack::PopAndDestroy( dlg );
    CleanupStack::Pop( KOne );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgSetHeaderImageL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgSetHeaderImageL( CStifItemParser& /*aItem*/ )
    {
    TInt number = KTen;
    
    CAknQueryDialog* dlg = CAknQueryDialog::NewL( number );
    CleanupStack::PushL( dlg );
    
    dlg->PrepareLC( R_MESSAGE_DIALOG );
    
    CEikImage* mImage = new( ELeave ) CEikImage();
    CleanupStack::PushL( mImage );
    
    TFileName file( KTestMbmFile );
    User::LeaveIfError( CompleteWithAppPath( file ) ); 
    
    mImage->CreatePictureFromFileL( file, EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    
    dlg->SetHeaderImageL( mImage );
    
    CleanupStack::Pop( mImage );
    CleanupStack::PopAndDestroy( dlg );
    CleanupStack::Pop( KOne );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgRunDlgLDL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgRunDlgLDL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryDialog* dlg = CAknQueryDialog::NewL();
    CleanupStack::PushL( dlg );
    
    dlg->RunDlgLD( R_AKNEXQUERY_CONFIRMATION_QUERY );
    
    CleanupStack::Pop( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgMaxTextLengthTwoL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgMaxTextLengthTwoL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryDialog* dlg = CAknQueryDialog::NewL();
    dlg->PrepareLC( R_AKNEXQUERY_NUMBER_LAYOUT );
    
    CTestCAknQueryDialog* testDlg = static_cast<CTestCAknQueryDialog*>( dlg );
    CAknQueryControl* control = testDlg->QueryControl();
    
    control->SetTextEntryLength( KFive );
    
    TBuf< KBufSize > buffer( KTestString );
    
    TInt length = dlg->MaxTextLength( control, &buffer, KTen );
    STIF_ASSERT_EQUALS( KTen, length );
    
    length = dlg->MaxTextLength( control, &buffer, KHundred );
    STIF_ASSERT_EQUALS( KFive, length );
    
    control->SetTextEntryLength( KZero );
    
    length = dlg->MaxTextLength( control, &buffer, KHundred );
    STIF_ASSERT_EQUALS( KBufSize, length );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgInputCapabilitiesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgInputCapabilitiesL( CStifItemParser& /*aItem*/ )
    {
    TInt number = KTen;
    
    CAknQueryDialog* dlg = CAknQueryDialog::NewL( number );
    dlg->PrepareLC( R_MESSAGE_DIALOG );
    
    TCoeInputCapabilities capabilities = dlg->InputCapabilities();
    STIF_ASSERT_NOT_NULL( &capabilities );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestQdlgSetEmergencyCallSupportForCBAL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestQdlgSetEmergencyCallSupportForCBAL( CStifItemParser& /*aItem*/ )
    {
    TInt number = KTen;
    
    CAknQueryDialog* dlg = CAknQueryDialog::NewL( number );
    dlg->PrepareLC( R_MESSAGE_DIALOG );
    
    dlg->SetEmergencyCallSupportForCBA( ETrue );
    dlg->SetEmergencyCallSupportForCBA( EFalse );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTextQdlgNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTextQdlgNewL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > dateText( KTestTime );
    
    CAknTextQueryDialog* dlg = CAknTextQueryDialog::NewL( dateText );
    CleanupStack::PushL( dlg );
    STIF_ASSERT_NOT_NULL( dlg );
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTextQdlgConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTextQdlgConstructorL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > dateText( KTestTime );
    
    CAknTextQueryDialog* dlg = new( ELeave ) CAknTextQueryDialog( dateText );
    CleanupStack::PushL( dlg );
    STIF_ASSERT_NOT_NULL( dlg );
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTextQdlgDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTextQdlgDestructorL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > dateText( KTestTime );
    TBuf< KBufSize > datePromt( KTestTime );
    
    CAknTextQueryDialog* dlg = new( ELeave ) CAknTextQueryDialog( dateText, datePromt );
    CleanupStack::PushL( dlg );
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTextQdlgSetMaxLengthL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTextQdlgSetMaxLengthL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > dateText( KTestTime );
    
    CAknTextQueryDialog* dlg = CAknTextQueryDialog::NewL( dateText );
    CleanupStack::PushL( dlg );
    dlg->SetMaxLength( KTen );
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTextQdlgCheckIfEntryTextOkL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTextQdlgCheckIfEntryTextOkL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > dateText( KTestTime );
    
    CAknTextQueryDialog* dlg = CAknTextQueryDialog::NewL( dateText );
    CleanupStack::PushL( dlg );
    
    TBool flag = dlg->CheckIfEntryTextOk();
    STIF_ASSERT_FALSE( flag );
    
    CleanupStack::Pop( dlg );
    dlg->PrepareLC( R_DEMO_DATA_QUERY );
    
    flag = dlg->CheckIfEntryTextOk();
    STIF_ASSERT_FALSE( flag );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTextQdlgSetDefaultInputModeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTextQdlgSetDefaultInputModeL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > dateText( KTestTime );
        
    CAknTextQueryDialog* dlg = CAknTextQueryDialog::NewL( dateText );
    
    dlg->PrepareLC( R_DEMO_DATA_QUERY );
    
    dlg->SetDefaultInputMode( KTen );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTextQdlgPreLayoutDynInitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTextQdlgPreLayoutDynInitL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > dateText( KTestTime );
        
    CAknTextQueryDialog* dlg = CAknTextQueryDialog::NewL( dateText );
    CTestCAknTextQueryDialog* testDlg = static_cast<CTestCAknTextQueryDialog*>( dlg );
    
    testDlg->PrepareLC( R_DEMO_DATA_QUERY );
    
    CTestCAknQueryControl* control = static_cast<CTestCAknQueryControl*>( testDlg->QueryControl() );
    control->iEdwin->SetMaxLength( KHundred );
    
    testDlg->PreLayoutDynInitL();
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTextQdlgOkToExitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTextQdlgOkToExitL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > dateText( KTestTime );
        
    CAknTextQueryDialog* dlg = CAknTextQueryDialog::NewL( dateText );
    CTestCAknTextQueryDialog* testDlg = static_cast<CTestCAknTextQueryDialog*>( dlg );
    
    testDlg->PrepareLC( R_DEMO_DATA_QUERY );
    
    TBool flag = testDlg->OkToExitL( EAknSoftkeyEmergencyCall );
    STIF_ASSERT_TRUE( flag );
    
    flag = testDlg->OkToExitL( EEikBidOk );
    STIF_ASSERT_TRUE( flag );
    
    flag = testDlg->OkToExitL( KHundred );
    STIF_ASSERT_FALSE( flag );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTextQdlgHandleQueryEditorSizeEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTextQdlgHandleQueryEditorSizeEventL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > dateText( KTestTime );
        
    CAknTextQueryDialog* dlg = CAknTextQueryDialog::NewL( dateText );
    CTestCAknTextQueryDialog* testDlg = static_cast<CTestCAknTextQueryDialog*>( dlg );
    
    testDlg->PrepareLC( R_DEMO_DATA_QUERY );
    
    CAknQueryControl* control = testDlg->QueryControl();
    
    TBool flag = dlg->HandleQueryEditorSizeEventL( control,
        MAknQueryControlObserver::EQueryControltSizeChanging );
    STIF_ASSERT_FALSE( flag );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTextQdlgHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTextQdlgHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > dateText( KTestTime );
        
    CAknTextQueryDialog* dlg = CAknTextQueryDialog::NewL( dateText );
    
    dlg->PrepareLC( R_DEMO_DATA_QUERY );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = KZero;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    TInt err = KErrNone;
    TRAP( err, dlg->HandlePointerEventL( event ) );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTextQdlgConstructorLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTextQdlgConstructorLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > dataText( KTestTime );
    TBuf< KBufSize > promptText( KTestString );
    
    CAknTextQueryDialog* dlg = new( ELeave ) CAknTextQueryDialog( dataText, promptText );
    CleanupStack::PushL( dlg );
    STIF_ASSERT_NOT_NULL( dlg );
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestNumberQdlgNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestNumberQdlgNewL( CStifItemParser& /*aItem*/ )
    {
    TInt number = KTen;
    
    CAknNumberQueryDialog* dlg = CAknNumberQueryDialog::NewL( number );
    CleanupStack::PushL( dlg );
    
    STIF_ASSERT_NOT_NULL( dlg );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestNumberQdlgConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestNumberQdlgConstructorL( CStifItemParser& /*aItem*/ )
    {
    TInt number = KTen;
    
    CAknNumberQueryDialog* dlg = new( ELeave ) CAknNumberQueryDialog( number );
    CleanupStack::PushL( dlg );
    
    STIF_ASSERT_NOT_NULL( dlg );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestNumberQdlgDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestNumberQdlgDestructorL( CStifItemParser& /*aItem*/ )
    {
    TInt number = KTen;
    
    CAknNumberQueryDialog* dlg = CAknNumberQueryDialog::NewL( number );
    CleanupStack::PushL( dlg );
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestNumberQdlgSetMinimumAndMaximumL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestNumberQdlgSetMinimumAndMaximumL( CStifItemParser& /*aItem*/ )
    {
    TInt number = KTen;
    
    CAknNumberQueryDialog* dlg = CAknNumberQueryDialog::NewL( number );
    
    dlg->PrepareLC( R_AKNEXQUERY_NUMBER_LAYOUT );
    
    dlg->SetMinimumAndMaximum( KZero, KHundred );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestNumberQdlgHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestNumberQdlgHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    TInt number = KTen;
    
    CAknNumberQueryDialog* dlg = CAknNumberQueryDialog::NewL( number );
    
    dlg->PrepareLC( R_AKNEXQUERY_NUMBER_LAYOUT );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = KZero;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    TInt err = KErrNone;
    TRAP( err, dlg->HandlePointerEventL( event ) );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestNumberQdlgPreLayoutDynInitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestNumberQdlgPreLayoutDynInitL( CStifItemParser& /*aItem*/ )
    {
    TInt number = KTen;
    
    CAknNumberQueryDialog* dlg = CAknNumberQueryDialog::NewL( number );
    
    dlg->PrepareLC( R_AKNEXQUERY_NUMBER_LAYOUT );
    
    CTestCAknNumberQueryDialog* testDlg = static_cast<CTestCAknNumberQueryDialog*>( dlg );
    
    testDlg->PreLayoutDynInitL();
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestNumberQdlgOkToExitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestNumberQdlgOkToExitL( CStifItemParser& /*aItem*/ )
    {
    TInt number = KTen;
    
    CAknNumberQueryDialog* dlg = CAknNumberQueryDialog::NewL( number );
    dlg->PrepareLC( R_AKNEXQUERY_NUMBER_LAYOUT );
    
    CTestCAknNumberQueryDialog* testDlg = static_cast<CTestCAknNumberQueryDialog*>( dlg );
    
    TBool flag = testDlg->OkToExitL( EAknSoftkeyEmergencyCall );
    STIF_ASSERT_TRUE( flag );
    
    flag = testDlg->OkToExitL( EEikBidOk );
    STIF_ASSERT_TRUE( flag );
    
    flag = testDlg->OkToExitL( KHundred );
    STIF_ASSERT_FALSE( flag );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestNumberQdlgNumberL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestNumberQdlgNumberOneL( CStifItemParser& /*aItem*/ )
    {
    TInt number = KTen;
    
    CAknNumberQueryDialog* dlg = CAknNumberQueryDialog::NewL( number );
    dlg->PrepareLC( R_AKNEXQUERY_NUMBER_LAYOUT );
    
    CTestCAknNumberQueryDialog* testDlg = static_cast<CTestCAknNumberQueryDialog*>( dlg );
    
    TInt returnNumber = testDlg->Number();
    STIF_ASSERT_EQUALS( KTen, returnNumber );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestNumberQdlgNumberL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestNumberQdlgNumberTwoL( CStifItemParser& /*aItem*/ )
    {
    TInt number = KTen;
    
    CAknNumberQueryDialog* dlg = CAknNumberQueryDialog::NewL( number );
    dlg->PrepareLC( R_AKNEXQUERY_NUMBER_LAYOUT );
    
    CTestCAknNumberQueryDialog* testDlg = static_cast<CTestCAknNumberQueryDialog*>( dlg );
    
    const TInt returnNumber = testDlg->Number();
    STIF_ASSERT_EQUALS( KTen, returnNumber );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTimeQdlgNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTimeQdlgNewL( CStifItemParser& /*aItem*/ )
    {
    TTime time( KTestTime );
    
    CAknTimeQueryDialog* dlg = CAknTimeQueryDialog::NewL( time );
    CleanupStack::PushL( dlg );
    
    STIF_ASSERT_NOT_NULL( dlg );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTimeQdlgConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTimeQdlgConstructorL( CStifItemParser& /*aItem*/ )
    {
    TTime time( KTestTime );
    
    CAknTimeQueryDialog* dlg = new( ELeave ) CAknTimeQueryDialog( time );
    CleanupStack::PushL( dlg );
    
    STIF_ASSERT_NOT_NULL( dlg );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTimeQdlgDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTimeQdlgDestructorL( CStifItemParser& /*aItem*/ )
    {
    TTime time( KTestTime );
    TBuf< KBufSize > text( KTestString );
    
    CAknTimeQueryDialog* dlg = new( ELeave ) CAknTimeQueryDialog( time, text );
    delete dlg;
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTimeQdlgSetMinimumAndMaximumL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTimeQdlgSetMinimumAndMaximumL( CStifItemParser& /*aItem*/ )
    {
    TTime time( KTestTime );
    
    CAknTimeQueryDialog* dlg = CAknTimeQueryDialog::NewL( time );
    dlg->PrepareLC( R_AKNEXQUERY_TIME_QUERY );
    
    TTime minTime( KZero );
    
    dlg->SetMinimumAndMaximum( minTime, time );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTimeQdlgHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTimeQdlgHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    TTime time( KTestTime );
    
    CAknTimeQueryDialog* dlg = CAknTimeQueryDialog::NewL( time );
    dlg->PrepareLC( R_AKNEXQUERY_TIME_QUERY );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = KZero;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    TInt err = KErrNone;
    TRAP( err, dlg->HandlePointerEventL( event ) );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTimeQdlgPreLayoutDynInitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTimeQdlgPreLayoutDynInitL( CStifItemParser& /*aItem*/ )
    {
    TTime time( KTestTime );
    
    CAknTimeQueryDialog* dlg = CAknTimeQueryDialog::NewL( time );
    dlg->PrepareLC( R_AKNEXQUERY_TIME_QUERY );
    
    CTestCAknTimeQueryDialog* testDlg = static_cast<CTestCAknTimeQueryDialog*>( dlg );
    
    testDlg->PreLayoutDynInitL();
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTimeQdlgOkToExitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTimeQdlgOkToExitL( CStifItemParser& /*aItem*/ )
    {
    TTime time( KTestTime );
    
    CAknTimeQueryDialog* dlg = CAknTimeQueryDialog::NewL( time );
    dlg->PrepareLC( R_AKNEXQUERY_TIME_QUERY );
    
    CTestCAknTimeQueryDialog* testDlg = static_cast<CTestCAknTimeQueryDialog*>( dlg );
    
    TBool flag = testDlg->OkToExitL( EEikBidOk );
    STIF_ASSERT_TRUE( flag );

    flag = testDlg->OkToExitL( KHundred );
    STIF_ASSERT_FALSE( flag );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTimeQdlgTimeOneL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTimeQdlgTimeOneL( CStifItemParser& /*aItem*/ )
    {
    TTime time( KTestTime );
    
    CAknTimeQueryDialog* dlg = CAknTimeQueryDialog::NewL( time );
    dlg->PrepareLC( R_AKNEXQUERY_TIME_QUERY );
    
    CTestCAknTimeQueryDialog* testDlg = static_cast<CTestCAknTimeQueryDialog*>( dlg );
    
    TTime returnTime = testDlg->Time();
    STIF_ASSERT_EQUALS( time, returnTime );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTimeQdlgTimeTwoL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTimeQdlgTimeTwoL( CStifItemParser& /*aItem*/ )
    {
    TTime time( KTestTime );
    
    CAknTimeQueryDialog* dlg = CAknTimeQueryDialog::NewL( time );
    dlg->PrepareLC( R_AKNEXQUERY_TIME_QUERY );
    
    CTestCAknTimeQueryDialog* testDlg = static_cast<CTestCAknTimeQueryDialog*>( dlg );
    
    const TTime returnTime = testDlg->Time();
    STIF_ASSERT_EQUALS( time, returnTime );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestTimeQdlgConstructorLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestTimeQdlgConstructorLL( CStifItemParser& /*aItem*/ )
    {
    TTime time( KTestTime );
    TBuf< KBufSize > prompt( KTestString );
    
    CAknTimeQueryDialog* dlg = new( ELeave ) CAknTimeQueryDialog( time, prompt );
    CleanupStack::PushL( dlg );
    
    STIF_ASSERT_NOT_NULL( dlg );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestDurationNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestDurationNewL( CStifItemParser& /*aItem*/ )
    {
    TTimeIntervalSeconds duration;
    
    CAknDurationQueryDialog* durationDlg = CAknDurationQueryDialog::NewL( duration );
    CleanupStack::PushL( durationDlg );
    
    STIF_ASSERT_NOT_NULL( durationDlg );
    
    CleanupStack::PopAndDestroy( durationDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestDurationConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestDurationConstructorL( CStifItemParser& /*aItem*/ )
    {
    TTimeIntervalSeconds duration;
    
    CAknDurationQueryDialog* durationDlg = new( ELeave ) CAknDurationQueryDialog( duration );
    CleanupStack::PushL( durationDlg );
    
    STIF_ASSERT_NOT_NULL( durationDlg );
    
    CleanupStack::PopAndDestroy( durationDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestDurationDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestDurationDestructorL( CStifItemParser& /*aItem*/ )
    {
    TTimeIntervalSeconds duration;
    
    CAknDurationQueryDialog* durationDlg = CAknDurationQueryDialog::NewL( duration );
    delete durationDlg;
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestDurationSetMinimumAndMaximumL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestDurationSetMinimumAndMaximumL( CStifItemParser& /*aItem*/ )
    {
    TTimeIntervalSeconds duration;
    
    CAknDurationQueryDialog* durationDlg = new( ELeave ) CAknDurationQueryDialog( duration );
    durationDlg->PrepareLC( R_AKNEXQUERY_DURATION_LAYOUT );
    
    TTimeIntervalSeconds minDuration( KZero );
    TTimeIntervalSeconds maxDuration( KHundred );
    
    durationDlg->SetMinimumAndMaximum( minDuration, maxDuration );
    
    CleanupStack::PopAndDestroy( durationDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestDurationHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestDurationHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    TTimeIntervalSeconds duration;
    
    CAknDurationQueryDialog* dlg = new( ELeave ) CAknDurationQueryDialog( duration );
    dlg->PrepareLC( R_AKNEXQUERY_DURATION_LAYOUT );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = KZero;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    TInt err = KErrNone;
    TRAP( err, dlg->HandlePointerEventL( event ) );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestDurationPreLayoutDynInitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestDurationPreLayoutDynInitL( CStifItemParser& /*aItem*/ )
    {
    TTimeIntervalSeconds duration( KOne );
        
    CAknDurationQueryDialog* dlg = new( ELeave ) CAknDurationQueryDialog( duration );
    dlg->PrepareLC( R_AKNEXQUERY_DURATION_LAYOUT );
    
    CTestCAknDurationQueryDialog* testDlg = static_cast<CTestCAknDurationQueryDialog*>( dlg );
    
    testDlg->PreLayoutDynInitL();
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestDurationOkToExitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestDurationOkToExitL( CStifItemParser& /*aItem*/ )
    {
    TTimeIntervalSeconds duration;
        
    CAknDurationQueryDialog* dlg = new( ELeave ) CAknDurationQueryDialog( duration );
    dlg->PrepareLC( R_AKNEXQUERY_DURATION_LAYOUT );
    
    CTestCAknDurationQueryDialog* testDlg = static_cast<CTestCAknDurationQueryDialog*>( dlg );
    
    TBool flag = testDlg->OkToExitL( EEikBidOk );
    STIF_ASSERT_TRUE( flag );
    
    flag = testDlg->OkToExitL( KHundred );
    STIF_ASSERT_FALSE( flag );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestDurationDurationOneL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestDurationDurationOneL( CStifItemParser& /*aItem*/ )
    {
    TTimeIntervalSeconds duration( KOne );
        
    CAknDurationQueryDialog* dlg = new( ELeave ) CAknDurationQueryDialog( duration );
    dlg->PrepareLC( R_AKNEXQUERY_DURATION_LAYOUT );
    
    CTestCAknDurationQueryDialog* testDlg = static_cast<CTestCAknDurationQueryDialog*>( dlg );
    
    TTimeIntervalSeconds& returnDuration = testDlg->Duration();
    STIF_ASSERT_EQUALS( duration, returnDuration );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestDurationDurationTwoL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestDurationDurationTwoL( CStifItemParser& /*aItem*/ )
    {
    TTimeIntervalSeconds duration( KOne );
        
    CAknDurationQueryDialog* dlg = new( ELeave ) CAknDurationQueryDialog( duration );
    dlg->PrepareLC( R_AKNEXQUERY_DURATION_LAYOUT );
    
    CTestCAknDurationQueryDialog* testDlg = static_cast<CTestCAknDurationQueryDialog*>( dlg );
    
    const TTimeIntervalSeconds& returnDuration = testDlg->Duration();
    STIF_ASSERT_EQUALS( duration, returnDuration );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestFloatingQdlgNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestFloatingQdlgNewL( CStifItemParser& /*aItem*/ )
    {
    TReal value = KRealvalue;
    
    CAknFloatingPointQueryDialog* dlg = CAknFloatingPointQueryDialog::NewL( value );
    CleanupStack::PushL( dlg );
    
    STIF_ASSERT_NOT_NULL( dlg );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestFloatingQdlgConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestFloatingQdlgConstructorL( CStifItemParser& /*aItem*/ )
    {
    TReal value = KRealvalue;
    
    CAknFloatingPointQueryDialog* dlg = new( ELeave ) CAknFloatingPointQueryDialog( value );
    CleanupStack::PushL( dlg );
    
    STIF_ASSERT_NOT_NULL( dlg );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestFloatingQdlgDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestFloatingQdlgDestructorL( CStifItemParser& /*aItem*/ )
    {
    TReal value = KRealvalue;
    
    CAknFloatingPointQueryDialog* dlg = new( ELeave ) CAknFloatingPointQueryDialog( value );
    delete dlg;
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestFloatingQdlgSetMinimumAndMaximumL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestFloatingQdlgSetMinimumAndMaximumL( CStifItemParser& /*aItem*/ )
    {
    TReal value = KRealvalue;
    
    CAknFloatingPointQueryDialog* dlg = CAknFloatingPointQueryDialog::NewL( value );
    dlg->PrepareLC( R_DEMO_FLOATING_QUERY );
    
    TReal maxValue = KMaxRealvalue;
    
    dlg->SetMinimumAndMaximum( value, maxValue );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestFloatingQdlgHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestFloatingQdlgHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    TReal value = KRealvalue;
    
    CAknFloatingPointQueryDialog* dlg = CAknFloatingPointQueryDialog::NewL( value );
    dlg->PrepareLC( R_DEMO_FLOATING_QUERY );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = KZero;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    TInt err = KErrNone;
    TRAP( err, dlg->HandlePointerEventL( event ) );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestFloatingQdlgPreLayoutDynInitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestFloatingQdlgPreLayoutDynInitL( CStifItemParser& /*aItem*/ )
    {
    TReal value = KRealvalue;
    
    CAknFloatingPointQueryDialog* dlg = CAknFloatingPointQueryDialog::NewL( value );
    dlg->PrepareLC( R_DEMO_FLOATING_QUERY );
    
    CTestCAknFloatingPointQueryDialog* testDlg = static_cast<CTestCAknFloatingPointQueryDialog*>( dlg );
    
    testDlg->PreLayoutDynInitL();
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestFloatingQdlgOkToExitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestFloatingQdlgOkToExitL( CStifItemParser& /*aItem*/ )
    {
    TReal value = KRealvalue;
    
    CAknFloatingPointQueryDialog* dlg = CAknFloatingPointQueryDialog::NewL( value );
    dlg->PrepareLC( R_DEMO_FLOATING_QUERY );
    
    CTestCAknFloatingPointQueryDialog* testDlg = static_cast<CTestCAknFloatingPointQueryDialog*>( dlg );
    
    TBool flag = testDlg->OkToExitL( EEikBidOk );
    STIF_ASSERT_TRUE( flag );
    
    flag = testDlg->OkToExitL( KHundred );
    STIF_ASSERT_FALSE( flag );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestFloatingQdlgNumberOneL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestFloatingQdlgNumberOneL( CStifItemParser& /*aItem*/ )
    {
    TReal value = KRealvalue;
    
    CAknFloatingPointQueryDialog* dlg = CAknFloatingPointQueryDialog::NewL( value );
    dlg->PrepareLC( R_DEMO_FLOATING_QUERY );
    
    CTestCAknFloatingPointQueryDialog* testDlg = static_cast<CTestCAknFloatingPointQueryDialog*>( dlg );
    
    TReal returnValue = testDlg->Number();
    STIF_ASSERT_EQUALS( value, returnValue );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestFloatingQdlgNumberTwoL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestFloatingQdlgNumberTwoL( CStifItemParser& /*aItem*/ )
    {
    TReal value = KRealvalue;
    
    CAknFloatingPointQueryDialog* dlg = CAknFloatingPointQueryDialog::NewL( value );
    dlg->PrepareLC( R_DEMO_FLOATING_QUERY );
    
    CTestCAknFloatingPointQueryDialog* testDlg = static_cast<CTestCAknFloatingPointQueryDialog*>( dlg );
    
    const TReal returnValue = testDlg->Number();
    STIF_ASSERT_EQUALS( value, returnValue );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineDataQdlgNewLOneL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineDataQdlgNewLOneL( CStifItemParser& /*aItem*/ )
    {
    TTime time1( KTestTime );
    TTime time2( KTestMinTime );
    
    CAknMultiLineDataQueryDialog* dlg = 
        CAknMultiLineDataQueryDialog::NewL( time1, time2 );
    CleanupStack::PushL( dlg );
    
    STIF_ASSERT_NOT_NULL( dlg );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineDataQdlgNewLTwoL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineDataQdlgNewLTwoL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > text1( KTestString );
    TBuf< KBufSize > text2( KTestStringReplace );
    
    CAknMultiLineDataQueryDialog* dlg = 
        CAknMultiLineDataQueryDialog::NewL( text1, text2 );
    CleanupStack::PushL( dlg );
    
    STIF_ASSERT_NOT_NULL( dlg );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineDataQdlgNewLThreeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineDataQdlgNewLThreeL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > text( KTestString );
    TTime time( KTestTime );
    
    CAknMultiLineDataQueryDialog* dlg = 
        CAknMultiLineDataQueryDialog::NewL( text, time );
    CleanupStack::PushL( dlg );
    
    STIF_ASSERT_NOT_NULL( dlg );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineDataQdlgNewLFourL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineDataQdlgNewLFourL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > text( KTestString );
    TInt number = KTen;
    
    CAknMultiLineDataQueryDialog* dlg = 
        CAknMultiLineDataQueryDialog::NewL( text, number );
    CleanupStack::PushL( dlg );
    
    STIF_ASSERT_NOT_NULL( dlg );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineDataQdlgNewLFiveL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineDataQdlgNewLFiveL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > text( KTestString );
    TTimeIntervalSeconds duration( KOne );
    
    CAknMultiLineDataQueryDialog* dlg = 
        CAknMultiLineDataQueryDialog::NewL( text, duration );
    CleanupStack::PushL( dlg );
    
    STIF_ASSERT_NOT_NULL( dlg );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineDataQdlgNewLSixL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineDataQdlgNewLSixL( CStifItemParser& /*aItem*/ )
    {
    TTime time( KTestTime );
    TTimeIntervalSeconds duration( KOne );
    
    CAknMultiLineDataQueryDialog* dlg = 
        CAknMultiLineDataQueryDialog::NewL( time, duration );
    CleanupStack::PushL( dlg );
    
    STIF_ASSERT_NOT_NULL( dlg );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineDataQdlgNewLSevenL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineDataQdlgNewLSevenL( CStifItemParser& /*aItem*/ )
    {
    TInt number1 = KZero;
    TInt number2 = KTen;
    
    CAknMultiLineDataQueryDialog* dlg = 
        CAknMultiLineDataQueryDialog::NewL( number1, number2 );
    CleanupStack::PushL( dlg );
    
    STIF_ASSERT_NOT_NULL( dlg );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineDataQdlgNewLEightL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineDataQdlgNewLEightL( CStifItemParser& /*aItem*/ )
    {
    TTime time( KTestTime );
    TCoordinate coord( 01.00, 01.0 );
    TLocality loc( coord, 0.1 );
    TPosition position( loc, time );
    
    CAknMultiLineDataQueryDialog* dlg = 
        CAknMultiLineDataQueryDialog::NewL( position );
    CleanupStack::PushL( dlg );
    
    STIF_ASSERT_NOT_NULL( dlg );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineDataQdlgDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineDataQdlgDestructorL( CStifItemParser& /*aItem*/ )
    {
    TTime time( KTestTime );
    TCoordinate coord( 01.00, 01.0 );
    TLocality loc( coord, 0.1 );
    TPosition position( loc, time );
    
    CAknMultiLineDataQueryDialog* dlg = 
        CAknMultiLineDataQueryDialog::NewL( position );
    delete dlg;
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineDataQdlgConstructorOneL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineDataQdlgConstructorOneL( CStifItemParser& /*aItem*/ )
    {
    CTestCAknMultiLineDataQueryDialog* dlg = 
        new( ELeave ) CTestCAknMultiLineDataQueryDialog( CAknQueryDialog::ENoTone );
    CleanupStack::PushL( dlg );
    
    STIF_ASSERT_NOT_NULL( dlg );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineDataQdlgSetPromptL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineDataQdlgSetPromptL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > message( KTestString );
    TTime topDateTime;
    topDateTime.Set( message );
    topDateTime.HomeTime();
    TTimeIntervalSeconds bottomDuration = KHundred;
    
    CAknMultiLineDataQueryDialog* dlg = 
        CAknMultiLineDataQueryDialog::NewL(topDateTime,bottomDuration);
    dlg->PrepareLC( R_AKNEXQUERY_MULTI_LINE_DATE_AND_DURATION_LAYOUT );
    
    TBuf< KBufSize > secondPrompt( KTestStringReplace );
    
    dlg->SetPromptL( message, secondPrompt );
    
    CTestCAknMultiLineDataQueryDialog* testDlg = 
        static_cast<CTestCAknMultiLineDataQueryDialog*>( dlg );
        
    TPtrC returnPrompt = testDlg->SecondPrompt();
    STIF_ASSERT_EQUALS( ( TPtrC )secondPrompt, returnPrompt );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineDataQdlgSetMaxLengthOfFirstEditorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineDataQdlgSetMaxLengthOfFirstEditorL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > message( KTestString );
    TTime topDateTime;
    topDateTime.Set( message );
    topDateTime.HomeTime();
    TTimeIntervalSeconds bottomDuration = KHundred;
    
    CAknMultiLineDataQueryDialog* dlg = 
        CAknMultiLineDataQueryDialog::NewL(topDateTime,bottomDuration);
    dlg->PrepareLC( R_AKNEXQUERY_MULTI_LINE_DATE_AND_DURATION_LAYOUT );
    
    dlg->SetMaxLengthOfFirstEditor( KHundred );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineDataQdlgSetMaxLengthOfSecondEditorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineDataQdlgSetMaxLengthOfSecondEditorL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > message( KTestString );
    TTime topDateTime;
    topDateTime.Set( message );
    topDateTime.HomeTime();
    TTimeIntervalSeconds bottomDuration = KHundred;
    
    CAknMultiLineDataQueryDialog* dlg = 
        CAknMultiLineDataQueryDialog::NewL(topDateTime,bottomDuration);
    dlg->PrepareLC( R_AKNEXQUERY_MULTI_LINE_DATE_AND_DURATION_LAYOUT );
    
    dlg->SetMaxLengthOfSecondEditor( KHundred );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineDataQdlgHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineDataQdlgHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > message( KTestString );
    TTime topDateTime;
    topDateTime.Set( message );
    topDateTime.HomeTime();
    TTimeIntervalSeconds bottomDuration = KHundred;
    
    CAknMultiLineDataQueryDialog* dlg = 
        CAknMultiLineDataQueryDialog::NewL(topDateTime,bottomDuration);
    dlg->PrepareLC( R_AKNEXQUERY_MULTI_LINE_DATE_AND_DURATION_LAYOUT );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = KZero;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    TInt err = KErrNone;
    TRAP( err, dlg->HandlePointerEventL( event ) );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineDataQdlgOkToExitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineDataQdlgOkToExitL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > message( KTestString );
    TTime topDateTime;
    topDateTime.Set( message );
    topDateTime.HomeTime();
    TTimeIntervalSeconds bottomDuration = KHundred;
    
    CAknMultiLineDataQueryDialog* dlg = 
        CAknMultiLineDataQueryDialog::NewL(topDateTime,bottomDuration);
    dlg->PrepareLC( R_AKNEXQUERY_MULTI_LINE_DATE_AND_DURATION_LAYOUT );
    
    CTestCAknMultiLineDataQueryDialog* testDlg = 
        static_cast<CTestCAknMultiLineDataQueryDialog*>( dlg );
        
    TBool flag = testDlg->OkToExitL( EEikBidOk );
    STIF_ASSERT_TRUE( flag );
    
    flag = testDlg->OkToExitL( KHundred );
    STIF_ASSERT_FALSE( flag );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineDataQdlgPreLayoutDynInitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineDataQdlgPreLayoutDynInitL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > message( KTestString );
    TTime topDateTime;
    topDateTime.Set( message );
    topDateTime.HomeTime();
    TTimeIntervalSeconds bottomDuration = KHundred;
    
    CAknMultiLineDataQueryDialog* dlg = 
        CAknMultiLineDataQueryDialog::NewL(topDateTime,bottomDuration);
    dlg->PrepareLC( R_AKNEXQUERY_MULTI_LINE_DATE_AND_DURATION_LAYOUT );
    
    CTestCAknMultiLineDataQueryDialog* testDlg = 
        static_cast<CTestCAknMultiLineDataQueryDialog*>( dlg );
        
    testDlg->PreLayoutDynInitL();
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineDataQdlgHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineDataQdlgHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > message( KTestString );
    TTime topDateTime;
    topDateTime.Set( message );
    topDateTime.HomeTime();
    TTimeIntervalSeconds bottomDuration = KHundred;
    
    CAknMultiLineDataQueryDialog* dlg = 
        CAknMultiLineDataQueryDialog::NewL(topDateTime,bottomDuration);
    dlg->PrepareLC( R_AKNEXQUERY_MULTI_LINE_DATE_AND_DURATION_LAYOUT );
    
    CTestCAknMultiLineDataQueryDialog* testDlg = 
        static_cast<CTestCAknMultiLineDataQueryDialog*>( dlg );
        
    testDlg->HandleResourceChange( KEikDynamicLayoutVariantSwitch );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineDataQdlgUpdateLeftSoftKeyL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineDataQdlgUpdateLeftSoftKeyL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > message( KTestString );
    TTime topDateTime;
    topDateTime.Set( message );
    topDateTime.HomeTime();
    TTimeIntervalSeconds bottomDuration = KHundred;
    
    CAknMultiLineDataQueryDialog* dlg = 
        CAknMultiLineDataQueryDialog::NewL(topDateTime,bottomDuration);
    dlg->PrepareLC( R_AKNEXQUERY_MULTI_LINE_DATE_AND_DURATION_LAYOUT );
    
    CTestCAknMultiLineDataQueryDialog* testDlg = 
        static_cast<CTestCAknMultiLineDataQueryDialog*>( dlg );
        
    testDlg->UpdateLeftSoftKeyL();
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineDataQdlgDoSetPromptL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineDataQdlgDoSetPromptL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > message( KTestString );
    TTime topDateTime;
    topDateTime.Set( message );
    topDateTime.HomeTime();
    TTimeIntervalSeconds bottomDuration = KHundred;
    
    CAknMultiLineDataQueryDialog* dlg = 
        CAknMultiLineDataQueryDialog::NewL(topDateTime,bottomDuration);
    dlg->PrepareLC( R_AKNEXQUERY_MULTI_LINE_DATE_AND_DURATION_LAYOUT );
    
    CTestCAknMultiLineDataQueryDialog* testDlg = 
        static_cast<CTestCAknMultiLineDataQueryDialog*>( dlg );
        
    testDlg->DoSetPromptL();
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineDataQdlgNeedToDismissQueryL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineDataQdlgNeedToDismissQueryL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > message( KTestString );
    TTime topDateTime;
    topDateTime.Set( message );
    topDateTime.HomeTime();
    TTimeIntervalSeconds bottomDuration = KHundred;
    
    CAknMultiLineDataQueryDialog* dlg = 
        CAknMultiLineDataQueryDialog::NewL(topDateTime,bottomDuration);
    dlg->PrepareLC( R_AKNEXQUERY_MULTI_LINE_DATE_AND_DURATION_LAYOUT );
    
    CTestCAknMultiLineDataQueryDialog* testDlg = 
        static_cast<CTestCAknMultiLineDataQueryDialog*>( dlg );
        
    TKeyEvent event;
    event.iScanCode = EStdKeyHash;
    event.iCode = EKeyTab;
    
    TBool flag = testDlg->NeedToDismissQueryL( event );
    STIF_ASSERT_FALSE( flag );
    
    event.iScanCode = EStdKeySquareBracketLeft;
    
    flag = testDlg->NeedToDismissQueryL( event );
    STIF_ASSERT_FALSE( flag );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineDataQdlgFirstControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineDataQdlgFirstControlL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > message( KTestString );
    TTime topDateTime;
    topDateTime.Set( message );
    topDateTime.HomeTime();
    TTimeIntervalSeconds bottomDuration = KHundred;
    
    CAknMultiLineDataQueryDialog* dlg = 
        CAknMultiLineDataQueryDialog::NewL(topDateTime,bottomDuration);
    dlg->PrepareLC( R_AKNEXQUERY_MULTI_LINE_DATE_AND_DURATION_LAYOUT );
    
    CTestCAknMultiLineDataQueryDialog* testDlg = 
        static_cast<CTestCAknMultiLineDataQueryDialog*>( dlg );
    
    CAknMultilineQueryControl* firstControl = testDlg->FirstControl();
    STIF_ASSERT_NOT_NULL( firstControl );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineDataQdlgSecondControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineDataQdlgSecondControlL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > message( KTestString );
    TTime topDateTime;
    topDateTime.Set( message );
    topDateTime.HomeTime();
    TTimeIntervalSeconds bottomDuration = KHundred;
    
    CAknMultiLineDataQueryDialog* dlg = 
        CAknMultiLineDataQueryDialog::NewL(topDateTime,bottomDuration);
    dlg->PrepareLC( R_AKNEXQUERY_MULTI_LINE_DATE_AND_DURATION_LAYOUT );
    
    CTestCAknMultiLineDataQueryDialog* testDlg = 
        static_cast<CTestCAknMultiLineDataQueryDialog*>( dlg );
    
    CAknMultilineQueryControl* secondControl = testDlg->SecondControl();
    STIF_ASSERT_NOT_NULL( secondControl );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineDataQdlgQueryControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineDataQdlgQueryControlL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > message( KTestString );
    TTime topDateTime;
    topDateTime.Set( message );
    topDateTime.HomeTime();
    TTimeIntervalSeconds bottomDuration = KHundred;
    
    CAknMultiLineDataQueryDialog* dlg = 
        CAknMultiLineDataQueryDialog::NewL(topDateTime,bottomDuration);
    dlg->PrepareLC( R_AKNEXQUERY_MULTI_LINE_DATE_AND_DURATION_LAYOUT );
    
    CTestCAknMultiLineDataQueryDialog* testDlg = 
        static_cast<CTestCAknMultiLineDataQueryDialog*>( dlg );
    
    CAknQueryControl* control = testDlg->QueryControl();
    STIF_ASSERT_NOT_NULL( control );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineDataQdlgQueryHeadingL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineDataQdlgQueryHeadingL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > message( KTestString );
    TTime topDateTime;
    topDateTime.Set( message );
    topDateTime.HomeTime();
    TTimeIntervalSeconds bottomDuration = KHundred;
    
    CAknMultiLineDataQueryDialog* dlg = 
        CAknMultiLineDataQueryDialog::NewL(topDateTime,bottomDuration);
    dlg->PrepareLC( R_AKNEXQUERY_MULTI_LINE_DATE_AND_DURATION_LAYOUT );
    
    CTestCAknMultiLineDataQueryDialog* testDlg = 
        static_cast<CTestCAknMultiLineDataQueryDialog*>( dlg );
    
    CAknPopupHeadingPane* heading = testDlg->QueryHeading();
    STIF_ASSERT_NULL( heading );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineDataSecondPromptL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineDataSecondPromptL( CStifItemParser& aItem )
    {
    TInt err = TestMultiLineDataQdlgSetPromptL( aItem );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineDataQdlgConstructorTwoL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineDataQdlgConstructorTwoL( CStifItemParser& /*aItem*/ )
    {
    TTime time1( KTestTime );
    TTime time2( KTestMinTime );
    
    CAknMultiLineDataQueryDialog* dlg = new( ELeave ) CAknMultiLineDataQueryDialog( &time1, &time2 );
    CleanupStack::PushL( dlg );
    
    STIF_ASSERT_NOT_NULL( dlg );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineDataQdlgConstructorThreeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineDataQdlgConstructorThreeL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > text1( KTestString );
    TBuf< KBufSize > text2( KTestStringReplace );
    
    CAknMultiLineDataQueryDialog* dlg = new( ELeave ) CAknMultiLineDataQueryDialog( &text1, &text2 );
    CleanupStack::PushL( dlg );
    
    STIF_ASSERT_NOT_NULL( dlg );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineDataQdlgConstructorFourL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineDataQdlgConstructorFourL( CStifItemParser& /*aItem*/ )
    {
    TTime time( KTestTime );
    TBuf< KBufSize > text( KTestString );
    
    CAknMultiLineDataQueryDialog* dlg = new( ELeave ) CAknMultiLineDataQueryDialog( &text, &time );
    CleanupStack::PushL( dlg );
    
    STIF_ASSERT_NOT_NULL( dlg );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineDataQdlgConstructorFiveL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineDataQdlgConstructorFiveL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > text( KTestString );
    TInt number = KTen;
    
    CAknMultiLineDataQueryDialog* dlg = new( ELeave ) CAknMultiLineDataQueryDialog( &text, &number );
    CleanupStack::PushL( dlg );
    
    STIF_ASSERT_NOT_NULL( dlg );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineDataQdlgConstructorSixL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineDataQdlgConstructorSixL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > text( KTestString );
    TTimeIntervalSeconds duration( KOne );
    
    CAknMultiLineDataQueryDialog* dlg = new( ELeave ) CAknMultiLineDataQueryDialog( &text, &duration );
    CleanupStack::PushL( dlg );
    
    STIF_ASSERT_NOT_NULL( dlg );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineDataQdlgConstructorSevenL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineDataQdlgConstructorSevenL( CStifItemParser& /*aItem*/ )
    {
    TTime time( KTestTime );
    TTimeIntervalSeconds duration( KOne );
    
    CAknMultiLineDataQueryDialog* dlg = new( ELeave ) CAknMultiLineDataQueryDialog( &time, &duration );
    CleanupStack::PushL( dlg );
    
    STIF_ASSERT_NOT_NULL( dlg );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineDataQdlgConstructorEightL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineDataQdlgConstructorEightL( CStifItemParser& /*aItem*/ )
    {
    TInt number1 = KZero;
    TInt number2 = KTen;
    
    CAknMultiLineDataQueryDialog* dlg = new( ELeave ) CAknMultiLineDataQueryDialog( &number1, &number2 );
    CleanupStack::PushL( dlg );
    
    STIF_ASSERT_NOT_NULL( dlg );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestIpAddressQdlgNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestIpAddressQdlgNewL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress;
    mAddress.SetAddress( INET_ADDR( KTen, KTen, KTen, KTen ));
    
    CAknIpAddressQueryDialog* dlg = CAknIpAddressQueryDialog::NewL( mAddress, 
        CAknIpAddressQueryDialog::ENoTone );
    CleanupStack::PushL( dlg );
    
    STIF_ASSERT_NOT_NULL( dlg );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestIpAddressQdlgDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestIpAddressQdlgDestructorL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress;
    mAddress.SetAddress( INET_ADDR( KTen, KTen, KTen, KTen ));
    
    CAknIpAddressQueryDialog* dlg = CAknIpAddressQueryDialog::NewL( mAddress, 
        CAknIpAddressQueryDialog::ENoTone );
    delete dlg;
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestIpAddressQdlgSetMinimumAndMaximumL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestIpAddressQdlgSetMinimumAndMaximumL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress;
    mAddress.SetAddress( INET_ADDR( KTen, KTen, KTen, KTen ));
    
    CAknIpAddressQueryDialog* dlg = CAknIpAddressQueryDialog::NewL( mAddress, 
        CAknIpAddressQueryDialog::ENoTone );
    dlg->PrepareLC( R_TESTQUERY_IP_ADDRESS );
    
    TInetAddr minAddr( KZero, KZero );
    TInetAddr maxAddr( KMaxAddrValue );
    
    dlg->SetMinimumAndMaximum( minAddr, maxAddr );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestIpAddressQdlgNeedToDismissQueryL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestIpAddressQdlgNeedToDismissQueryL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress;
    mAddress.SetAddress( INET_ADDR( KTen, KTen, KTen, KTen ));
    
    CAknIpAddressQueryDialog* dlg = CAknIpAddressQueryDialog::NewL( mAddress, 
        CAknIpAddressQueryDialog::ENoTone );
    dlg->PrepareLC( R_TESTQUERY_IP_ADDRESS );
    
    TKeyEvent event;
    event.iScanCode = EStdKeySquareBracketLeft;
    
    TBool flag = dlg->NeedToDismissQueryL( event );
    
    STIF_ASSERT_FALSE( flag );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestIpAddressQdlgQueryControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestIpAddressQdlgQueryControlL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress;
    mAddress.SetAddress( INET_ADDR( KTen, KTen, KTen, KTen ));
    
    CAknIpAddressQueryDialog* dlg = CAknIpAddressQueryDialog::NewL( mAddress, 
        CAknIpAddressQueryDialog::ENoTone );
    dlg->PrepareLC( R_TESTQUERY_IP_ADDRESS );
    
    CTestCAknIpAddressQueryDialog* testDlg = static_cast<CTestCAknIpAddressQueryDialog*>( dlg );
    
    CAknQueryControl* control = testDlg->QueryControl();
    STIF_ASSERT_NOT_NULL( control );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestIpAddressQdlgSetSizeAndPositionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestIpAddressQdlgSetSizeAndPositionL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress;
    mAddress.SetAddress( INET_ADDR( KTen, KTen, KTen, KTen ));
    
    CAknIpAddressQueryDialog* dlg = CAknIpAddressQueryDialog::NewL( mAddress, 
        CAknIpAddressQueryDialog::ENoTone );
    dlg->PrepareLC( R_TESTQUERY_IP_ADDRESS );
    
    CTestCAknIpAddressQueryDialog* testDlg = static_cast<CTestCAknIpAddressQueryDialog*>( dlg );
    
    testDlg->SetSizeAndPosition( iContainer->Rect().Size() );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestIpAddressQdlgPreLayoutDynInitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestIpAddressQdlgPreLayoutDynInitL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress;
    mAddress.SetAddress( INET_ADDR( KTen, KTen, KTen, KTen ));
    
    CAknIpAddressQueryDialog* dlg = CAknIpAddressQueryDialog::NewL( mAddress, 
        CAknIpAddressQueryDialog::ENoTone );
    dlg->PrepareLC( R_TESTQUERY_IP_ADDRESS );
    
    CTestCAknIpAddressQueryDialog* testDlg = static_cast<CTestCAknIpAddressQueryDialog*>( dlg );
    
    testDlg->PreLayoutDynInitL();
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestIpAddressQdlgPostLayoutDynInitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestIpAddressQdlgPostLayoutDynInitL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress;
    mAddress.SetAddress( INET_ADDR( KTen, KTen, KTen, KTen ));
    
    CAknIpAddressQueryDialog* dlg = CAknIpAddressQueryDialog::NewL( mAddress, 
        CAknIpAddressQueryDialog::ENoTone );
    dlg->PrepareLC( R_TESTQUERY_IP_ADDRESS );
    
    CTestCAknIpAddressQueryDialog* testDlg = static_cast<CTestCAknIpAddressQueryDialog*>( dlg );
    
    testDlg->PostLayoutDynInitL();
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestIpAddressQdlgDoSetPromptL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestIpAddressQdlgDoSetPromptL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress;
    mAddress.SetAddress( INET_ADDR( KTen, KTen, KTen, KTen ));
    
    CAknIpAddressQueryDialog* dlg = CAknIpAddressQueryDialog::NewL( mAddress, 
        CAknIpAddressQueryDialog::ENoTone );
    dlg->PrepareLC( R_TESTQUERY_IP_ADDRESS );
    
    CTestCAknIpAddressQueryDialog* testDlg = static_cast<CTestCAknIpAddressQueryDialog*>( dlg );
    
    testDlg->DoSetPromptL();
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestIpAddressQdlgOkToExitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestIpAddressQdlgOkToExitL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress;
    mAddress.SetAddress( INET_ADDR( KTen, KTen, KTen, KTen ));
    
    CAknIpAddressQueryDialog* dlg = CAknIpAddressQueryDialog::NewL( mAddress, 
        CAknIpAddressQueryDialog::ENoTone );
    dlg->PrepareLC( R_TESTQUERY_IP_ADDRESS );
    
    CTestCAknIpAddressQueryDialog* testDlg = static_cast<CTestCAknIpAddressQueryDialog*>( dlg );
    
    TBool flag = testDlg->OkToExitL( EEikBidOk );
    STIF_ASSERT_TRUE( flag );
    
    flag = testDlg->OkToExitL( KHundred );
    STIF_ASSERT_FALSE( flag );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestIpAddressQdlgUpdateLeftSoftKeyL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestIpAddressQdlgUpdateLeftSoftKeyL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress;
    mAddress.SetAddress( INET_ADDR( KTen, KTen, KTen, KTen ));
    
    CAknIpAddressQueryDialog* dlg = CAknIpAddressQueryDialog::NewL( mAddress, 
        CAknIpAddressQueryDialog::ENoTone );
    dlg->PrepareLC( R_TESTQUERY_IP_ADDRESS );
    
    CTestCAknIpAddressQueryDialog* testDlg = static_cast<CTestCAknIpAddressQueryDialog*>( dlg );
    
    testDlg->UpdateLeftSoftKeyL();
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestIpAddressQdlgInetAddrOneL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestIpAddressQdlgInetAddrOneL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress;
    mAddress.SetAddress( INET_ADDR( KTen, KTen, KTen, KTen ));
    
    CAknIpAddressQueryDialog* dlg = CAknIpAddressQueryDialog::NewL( mAddress, 
        CAknIpAddressQueryDialog::ENoTone );
    dlg->PrepareLC( R_TESTQUERY_IP_ADDRESS );
    
    CTestCAknIpAddressQueryDialog* testDlg = static_cast<CTestCAknIpAddressQueryDialog*>( dlg );
    
    TInetAddr returnAddr = testDlg->InetAddr();
    STIF_ASSERT_EQUALS( mAddress, returnAddr );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestIpAddressQdlgInetAddrTwoL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestIpAddressQdlgInetAddrTwoL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress;
    mAddress.SetAddress( INET_ADDR( KTen, KTen, KTen, KTen ));
    
    CAknIpAddressQueryDialog* dlg = CAknIpAddressQueryDialog::NewL( mAddress, 
        CAknIpAddressQueryDialog::ENoTone );
    dlg->PrepareLC( R_TESTQUERY_IP_ADDRESS );
    
    CTestCAknIpAddressQueryDialog* testDlg = static_cast<CTestCAknIpAddressQueryDialog*>( dlg );
    
    const TInetAddr returnAddr = testDlg->InetAddr();
    STIF_ASSERT_EQUALS( mAddress, returnAddr );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestFixedPointQdlgNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestFixedPointQdlgNewL( CStifItemParser& /*aItem*/ )
    {
    TInt number = KTen;
    
    CAknFixedPointQueryDialog* dlg = CAknFixedPointQueryDialog::NewL( number, 
        CAknFixedPointQueryDialog::ENoTone );
    CleanupStack::PushL( dlg );
    
    STIF_ASSERT_NOT_NULL( dlg );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestFixedPointQdlgDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestFixedPointQdlgDestructorL( CStifItemParser& /*aItem*/ )
    {
    TInt number = KTen;
    
    CAknFixedPointQueryDialog* dlg = CAknFixedPointQueryDialog::NewL( number, 
        CAknFixedPointQueryDialog::ENoTone );
    delete dlg;
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestFixedPointQdlgSetMinimumAndMaximumL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestFixedPointQdlgSetMinimumAndMaximumL( CStifItemParser& /*aItem*/ )
    {
    TInt number = KTen;
        
    CAknFixedPointQueryDialog* dlg = CAknFixedPointQueryDialog::NewL( number, 
        CAknFixedPointQueryDialog::ENoTone );
    
    dlg->PrepareLC( R_TESTQUERY_FIXED_POINT );
    
    dlg->SetMinimumAndMaximum( KZero, KHundred );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestFixedPointQdlgNeedToDismissQueryL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestFixedPointQdlgNeedToDismissQueryL( CStifItemParser& /*aItem*/ )
    {
    TInt number = KTen;
        
    CAknFixedPointQueryDialog* dlg = CAknFixedPointQueryDialog::NewL( number, 
        CAknFixedPointQueryDialog::ENoTone );
    
    dlg->PrepareLC( R_TESTQUERY_FIXED_POINT );
    
    TKeyEvent event;
    event.iScanCode = EStdKeyHash;
    event.iCode = EKeyTab;
    
    TBool flag = dlg->NeedToDismissQueryL( event );
    STIF_ASSERT_FALSE( flag );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestFixedPointQdlgQueryControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestFixedPointQdlgQueryControlL( CStifItemParser& /*aItem*/ )
    {
    TInt number = KTen;
        
    CAknFixedPointQueryDialog* dlg = CAknFixedPointQueryDialog::NewL( number, 
        CAknFixedPointQueryDialog::ENoTone );
    
    dlg->PrepareLC( R_TESTQUERY_FIXED_POINT );
    
    CTestCAknFixedPointQueryDialog* testDlg = static_cast<CTestCAknFixedPointQueryDialog*>( dlg );
    
    CAknQueryControl* control = testDlg->QueryControl();
    
    STIF_ASSERT_NOT_NULL( control );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestFixedPointQdlgSetSizeAndPositionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestFixedPointQdlgSetSizeAndPositionL( CStifItemParser& /*aItem*/ )
    {
    TInt number = KTen;
        
    CAknFixedPointQueryDialog* dlg = CAknFixedPointQueryDialog::NewL( number, 
        CAknFixedPointQueryDialog::ENoTone );
    
    dlg->PrepareLC( R_TESTQUERY_FIXED_POINT );
    
    CTestCAknFixedPointQueryDialog* testDlg = static_cast<CTestCAknFixedPointQueryDialog*>( dlg );
    
    testDlg->SetSizeAndPosition( iContainer->Rect().Size() );

    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestFixedPointQdlgPreLayoutDynInitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestFixedPointQdlgPreLayoutDynInitL( CStifItemParser& /*aItem*/ )
    {
    TInt number = KTen;
        
    CAknFixedPointQueryDialog* dlg = CAknFixedPointQueryDialog::NewL( number, 
        CAknFixedPointQueryDialog::ENoTone );
    
    dlg->PrepareLC( R_TESTQUERY_FIXED_POINT );
    
    CTestCAknFixedPointQueryDialog* testDlg = static_cast<CTestCAknFixedPointQueryDialog*>( dlg );
    
    testDlg->PreLayoutDynInitL();

    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestFixedPointQdlgPostLayoutDynInitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestFixedPointQdlgPostLayoutDynInitL( CStifItemParser& /*aItem*/ )
    {
    TInt number = KTen;
        
    CAknFixedPointQueryDialog* dlg = CAknFixedPointQueryDialog::NewL( number, 
        CAknFixedPointQueryDialog::ENoTone );
    
    dlg->PrepareLC( R_TESTQUERY_FIXED_POINT );
    
    CTestCAknFixedPointQueryDialog* testDlg = static_cast<CTestCAknFixedPointQueryDialog*>( dlg );
    
    testDlg->PostLayoutDynInitL();

    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestFixedPointQdlgDoSetPromptL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestFixedPointQdlgDoSetPromptL( CStifItemParser& /*aItem*/ )
    {
    TInt number = KTen;
        
    CAknFixedPointQueryDialog* dlg = CAknFixedPointQueryDialog::NewL( number, 
        CAknFixedPointQueryDialog::ENoTone );
    
    dlg->PrepareLC( R_TESTQUERY_FIXED_POINT );
    
    CTestCAknFixedPointQueryDialog* testDlg = static_cast<CTestCAknFixedPointQueryDialog*>( dlg );
    
    testDlg->DoSetPromptL();

    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestFixedPointQdlgOkToExitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestFixedPointQdlgOkToExitL( CStifItemParser& /*aItem*/ )
    {
    TInt number = KTen;
        
    CAknFixedPointQueryDialog* dlg = CAknFixedPointQueryDialog::NewL( number, 
        CAknFixedPointQueryDialog::ENoTone );
    
    dlg->PrepareLC( R_TESTQUERY_FIXED_POINT );
    
    CTestCAknFixedPointQueryDialog* testDlg = static_cast<CTestCAknFixedPointQueryDialog*>( dlg );
    
    TBool flag = testDlg->OkToExitL( EEikBidOk );
    STIF_ASSERT_TRUE( flag );
    
    flag = testDlg->OkToExitL( KHundred );
    STIF_ASSERT_FALSE( flag );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestFixedPointQdlgUpdateLeftSoftKeyL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestFixedPointQdlgUpdateLeftSoftKeyL( CStifItemParser& /*aItem*/ )
    {
    TInt number = KTen;
        
    CAknFixedPointQueryDialog* dlg = CAknFixedPointQueryDialog::NewL( number, 
        CAknFixedPointQueryDialog::ENoTone );
    
    dlg->PrepareLC( R_TESTQUERY_FIXED_POINT );
    
    CTestCAknFixedPointQueryDialog* testDlg = static_cast<CTestCAknFixedPointQueryDialog*>( dlg );
    
    testDlg->UpdateLeftSoftKeyL();

    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestFixedPointQdlgNumberOneL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestFixedPointQdlgNumberOneL( CStifItemParser& /*aItem*/ )
    {
    TInt number = KTen;
        
    CAknFixedPointQueryDialog* dlg = CAknFixedPointQueryDialog::NewL( number, 
        CAknFixedPointQueryDialog::ENoTone );
    
    dlg->PrepareLC( R_TESTQUERY_FIXED_POINT );
    
    CTestCAknFixedPointQueryDialog* testDlg = static_cast<CTestCAknFixedPointQueryDialog*>( dlg );
    
    TInt returnNumber = testDlg->Number();
    STIF_ASSERT_EQUALS( KTen, returnNumber );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestFixedPointQdlgNumberTwoL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestFixedPointQdlgNumberTwoL( CStifItemParser& /*aItem*/ )
    {
    TInt number = KTen;
        
    CAknFixedPointQueryDialog* dlg = CAknFixedPointQueryDialog::NewL( number, 
        CAknFixedPointQueryDialog::ENoTone );
    
    dlg->PrepareLC( R_TESTQUERY_FIXED_POINT );
    
    CTestCAknFixedPointQueryDialog* testDlg = static_cast<CTestCAknFixedPointQueryDialog*>( dlg );
    
    const TInt returnNumber = testDlg->Number();
    STIF_ASSERT_EQUALS( KTen, returnNumber );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineIpQdlgNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineIpQdlgNewL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress1;
    mAddress1.SetAddress( INET_ADDR( KTen, KTen, KTen, KTen ));
    
    TInetAddr mAddress2;
    mAddress2.SetAddress( INET_ADDR( KTen, KZero, KTen, KOne ));
    
    CAknMultiLineIpQueryDialog* dlg = CAknMultiLineIpQueryDialog::NewL( mAddress1, 
        mAddress1, CAknMultiLineIpQueryDialog::ENoTone );
    CleanupStack::PushL( dlg );
    
    STIF_ASSERT_NOT_NULL( dlg );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineIpQdlgDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineIpQdlgDestructorL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress1;
    mAddress1.SetAddress( INET_ADDR( KTen, KTen, KTen, KTen ));
    
    TInetAddr mAddress2;
    mAddress2.SetAddress( INET_ADDR( KTen, KZero, KTen, KOne ));
    
    CAknMultiLineIpQueryDialog* dlg = CAknMultiLineIpQueryDialog::NewL( mAddress1, 
        mAddress1, CAknMultiLineIpQueryDialog::ENoTone );
    delete dlg;
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineIpQdlgSetPromptL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineIpQdlgSetPromptL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress1;
    mAddress1.SetAddress( INET_ADDR( KTen, KTen, KTen, KTen ));
    
    TInetAddr mAddress2;
    mAddress2.SetAddress( INET_ADDR( KTen, KZero, KTen, KOne ));
    
    CAknMultiLineIpQueryDialog* dlg = CAknMultiLineIpQueryDialog::NewL( mAddress1, 
        mAddress1, CAknMultiLineIpQueryDialog::ENoTone );
    
    dlg->PrepareLC( R_TESTQUERY_MULTI_LINE_IP_ADDRESS );
    
    TBuf< KBufSize > firstPrompt( KTestString );
    TBuf< KBufSize > secondPrompt( KTestStringReplace );
    
    dlg->SetPromptL( firstPrompt, secondPrompt );
    
    CTestCAknMultiLineIpQueryDialog* testDlg = static_cast<CTestCAknMultiLineIpQueryDialog*>( dlg );
    
    TPtrC returnPrompt = testDlg->SecondPrompt();
    STIF_ASSERT_EQUALS( ( TPtrC )secondPrompt, returnPrompt );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineIpQdlgSetMaxLengthOfFirstEditorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineIpQdlgSetMaxLengthOfFirstEditorL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress1;
    mAddress1.SetAddress( INET_ADDR( KTen, KTen, KTen, KTen ));
    
    TInetAddr mAddress2;
    mAddress2.SetAddress( INET_ADDR( KTen, KZero, KTen, KOne ));
    
    CAknMultiLineIpQueryDialog* dlg = CAknMultiLineIpQueryDialog::NewL( mAddress1, 
        mAddress1, CAknMultiLineIpQueryDialog::ENoTone );
    
    dlg->PrepareLC( R_TESTQUERY_MULTI_LINE_IP_ADDRESS );
    
    dlg->SetMaxLengthOfFirstEditor( KHundred );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineIpQdlgSetMaxLengthOfSecondEditorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineIpQdlgSetMaxLengthOfSecondEditorL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress1;
    mAddress1.SetAddress( INET_ADDR( KTen, KTen, KTen, KTen ));
    
    TInetAddr mAddress2;
    mAddress2.SetAddress( INET_ADDR( KTen, KZero, KTen, KOne ));
    
    CAknMultiLineIpQueryDialog* dlg = CAknMultiLineIpQueryDialog::NewL( mAddress1, 
        mAddress1, CAknMultiLineIpQueryDialog::ENoTone );
    
    dlg->PrepareLC( R_TESTQUERY_MULTI_LINE_IP_ADDRESS );
    
    dlg->SetMaxLengthOfSecondEditor( KHundred );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineIpQdlgOkToExitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineIpQdlgOkToExitL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress1;
    mAddress1.SetAddress( INET_ADDR( KTen, KTen, KTen, KTen ));
    
    TInetAddr mAddress2;
    mAddress2.SetAddress( INET_ADDR( KTen, KZero, KTen, KOne ));
    
    CAknMultiLineIpQueryDialog* dlg = CAknMultiLineIpQueryDialog::NewL( mAddress1, 
        mAddress1, CAknMultiLineIpQueryDialog::ENoTone );
    
    dlg->PrepareLC( R_TESTQUERY_MULTI_LINE_IP_ADDRESS );
    
    CTestCAknMultiLineIpQueryDialog* testDlg = static_cast<CTestCAknMultiLineIpQueryDialog*>( dlg );
    
    TBool flag = testDlg->OkToExitL( EEikBidOk );
    STIF_ASSERT_TRUE( flag );
    
    flag = testDlg->OkToExitL( KHundred );
    STIF_ASSERT_FALSE( flag );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineIpQdlgPreLayoutDynInitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineIpQdlgPreLayoutDynInitL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress1;
    mAddress1.SetAddress( INET_ADDR( KTen, KTen, KTen, KTen ));
    
    TInetAddr mAddress2;
    mAddress2.SetAddress( INET_ADDR( KTen, KZero, KTen, KOne ));
    
    CAknMultiLineIpQueryDialog* dlg = CAknMultiLineIpQueryDialog::NewL( mAddress1, 
        mAddress1, CAknMultiLineIpQueryDialog::ENoTone );
    
    dlg->PrepareLC( R_TESTQUERY_MULTI_LINE_IP_ADDRESS );
    
    CTestCAknMultiLineIpQueryDialog* testDlg = static_cast<CTestCAknMultiLineIpQueryDialog*>( dlg );
    
    testDlg->PreLayoutDynInitL();
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineIpQdlgHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineIpQdlgHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress1;
    mAddress1.SetAddress( INET_ADDR( KTen, KTen, KTen, KTen ));
    
    TInetAddr mAddress2;
    mAddress2.SetAddress( INET_ADDR( KTen, KZero, KTen, KOne ));
    
    CAknMultiLineIpQueryDialog* dlg = CAknMultiLineIpQueryDialog::NewL( mAddress1, 
        mAddress1, CAknMultiLineIpQueryDialog::ENoTone );
    
    dlg->PrepareLC( R_TESTQUERY_MULTI_LINE_IP_ADDRESS );
    
    CTestCAknMultiLineIpQueryDialog* testDlg = static_cast<CTestCAknMultiLineIpQueryDialog*>( dlg );
    
    testDlg->HandleResourceChange( KEikDynamicLayoutVariantSwitch );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineIpQdlgUpdateLeftSoftKeyL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineIpQdlgUpdateLeftSoftKeyL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress1;
    mAddress1.SetAddress( INET_ADDR( KTen, KTen, KTen, KTen ));
    
    TInetAddr mAddress2;
    mAddress2.SetAddress( INET_ADDR( KTen, KZero, KTen, KOne ));
    
    CAknMultiLineIpQueryDialog* dlg = CAknMultiLineIpQueryDialog::NewL( mAddress1, 
        mAddress1, CAknMultiLineIpQueryDialog::ENoTone );
    
    dlg->PrepareLC( R_TESTQUERY_MULTI_LINE_IP_ADDRESS );
    
    CTestCAknMultiLineIpQueryDialog* testDlg = static_cast<CTestCAknMultiLineIpQueryDialog*>( dlg );
    
    testDlg->UpdateLeftSoftKeyL();
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineIpQdlgDoSetPromptL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineIpQdlgDoSetPromptL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress1;
    mAddress1.SetAddress( INET_ADDR( KTen, KTen, KTen, KTen ));
    
    TInetAddr mAddress2;
    mAddress2.SetAddress( INET_ADDR( KTen, KZero, KTen, KOne ));
    
    CAknMultiLineIpQueryDialog* dlg = CAknMultiLineIpQueryDialog::NewL( mAddress1, 
        mAddress1, CAknMultiLineIpQueryDialog::ENoTone );
    
    dlg->PrepareLC( R_TESTQUERY_MULTI_LINE_IP_ADDRESS );
    
    CTestCAknMultiLineIpQueryDialog* testDlg = static_cast<CTestCAknMultiLineIpQueryDialog*>( dlg );
    
    testDlg->DoSetPromptL();
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineIpQdlgNeedToDismissQueryL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineIpQdlgNeedToDismissQueryL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress1;
    mAddress1.SetAddress( INET_ADDR( KTen, KTen, KTen, KTen ));
    
    TInetAddr mAddress2;
    mAddress2.SetAddress( INET_ADDR( KTen, KZero, KTen, KOne ));
    
    CAknMultiLineIpQueryDialog* dlg = CAknMultiLineIpQueryDialog::NewL( mAddress1, 
        mAddress1, CAknMultiLineIpQueryDialog::ENoTone );
    
    dlg->PrepareLC( R_TESTQUERY_MULTI_LINE_IP_ADDRESS );
    
    CTestCAknMultiLineIpQueryDialog* testDlg = static_cast<CTestCAknMultiLineIpQueryDialog*>( dlg );
    
    TKeyEvent event;
    event.iScanCode = EStdKeyHash;
    event.iCode = EKeyTab;
    
    TBool flag = testDlg->NeedToDismissQueryL( event );
    STIF_ASSERT_FALSE( flag );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineIpQdlgFirstControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineIpQdlgFirstControlL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress1;
    mAddress1.SetAddress( INET_ADDR( KTen, KTen, KTen, KTen ));
    
    TInetAddr mAddress2;
    mAddress2.SetAddress( INET_ADDR( KTen, KZero, KTen, KOne ));
    
    CAknMultiLineIpQueryDialog* dlg = CAknMultiLineIpQueryDialog::NewL( mAddress1, 
        mAddress1, CAknMultiLineIpQueryDialog::ENoTone );
    
    dlg->PrepareLC( R_TESTQUERY_MULTI_LINE_IP_ADDRESS );
    
    CTestCAknMultiLineIpQueryDialog* testDlg = static_cast<CTestCAknMultiLineIpQueryDialog*>( dlg );
    
    CAknExtMultilineQueryControl* firstControl = testDlg->FirstControl();
    STIF_ASSERT_NOT_NULL( firstControl );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineIpQdlgSecondControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineIpQdlgSecondControlL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress1;
    mAddress1.SetAddress( INET_ADDR( KTen, KTen, KTen, KTen ));
    
    TInetAddr mAddress2;
    mAddress2.SetAddress( INET_ADDR( KTen, KZero, KTen, KOne ));
    
    CAknMultiLineIpQueryDialog* dlg = CAknMultiLineIpQueryDialog::NewL( mAddress1, 
        mAddress1, CAknMultiLineIpQueryDialog::ENoTone );
    
    dlg->PrepareLC( R_TESTQUERY_MULTI_LINE_IP_ADDRESS );
    
    CTestCAknMultiLineIpQueryDialog* testDlg = static_cast<CTestCAknMultiLineIpQueryDialog*>( dlg );
    
    CAknExtMultilineQueryControl* secondControl = testDlg->SecondControl();
    STIF_ASSERT_NOT_NULL( secondControl );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineIpQdlgQueryControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineIpQdlgQueryControlL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress1;
    mAddress1.SetAddress( INET_ADDR( KTen, KTen, KTen, KTen ));
    
    TInetAddr mAddress2;
    mAddress2.SetAddress( INET_ADDR( KTen, KZero, KTen, KOne ));
    
    CAknMultiLineIpQueryDialog* dlg = CAknMultiLineIpQueryDialog::NewL( mAddress1, 
        mAddress1, CAknMultiLineIpQueryDialog::ENoTone );
    
    dlg->PrepareLC( R_TESTQUERY_MULTI_LINE_IP_ADDRESS );
    
    CTestCAknMultiLineIpQueryDialog* testDlg = static_cast<CTestCAknMultiLineIpQueryDialog*>( dlg );
    
    CAknQueryControl* control = testDlg->QueryControl();
    STIF_ASSERT_NOT_NULL( control );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMultiLineIpQdlgSecondPromptL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMultiLineIpQdlgSecondPromptL( CStifItemParser& aItem )
    {
    TInt err = TestMultiLineIpQdlgSetPromptL( aItem );
    return err;
    }

//End file



