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
* Description:  Test aknmessagequerydialog.h
*
*/

//INCLUDE
#include <aknmessagequerydialog.h>
#include <testsdkqueries.rsg>
#include <e32std.h>
#include <eikimage.h>

#include "testsdkqueries.h"
#include "testsdkqueriescontainer.h"
#include "testsdkaknmessagequerydialogprotected.h"

const TInt KZero = 0;
const TInt KTwo = 2;
const TInt KThree = 3;
const TInt KBufSize = 32;
_LIT( KTestString, "It is a test!");

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMqdlgNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMqdlgNewL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > message( KTestString );
    CAknMessageQueryDialog* dlg = CAknMessageQueryDialog::NewL( message,
        CAknQueryDialog::EConfirmationTone );
    CleanupStack::PushL( dlg );
    STIF_ASSERT_NOT_NULL( dlg );
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMqdlgDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMqdlgDestructorL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > message( KTestString );
    CAknMessageQueryDialog* dlg = CAknMessageQueryDialog::NewL( message,
        CAknQueryDialog::EConfirmationTone );
    CleanupStack::PushL( dlg );
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMqdlgConstructorOneL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMqdlgConstructorOneL( CStifItemParser& /*aItem*/ )
    {
    CAknMessageQueryDialog* dlg = new( ELeave ) CAknMessageQueryDialog( CAknQueryDialog::EConfirmationTone );
    CleanupStack::PushL( dlg );
    STIF_ASSERT_NOT_NULL( dlg );
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMqdlgSetMessageTextOneL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMqdlgSetMessageTextOneL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > message( KTestString );
    CAknMessageQueryDialog* dlg = CAknMessageQueryDialog::NewL( message,
        CAknQueryDialog::EConfirmationTone );
    CleanupStack::PushL( dlg );
    
    dlg->SetMessageTextL( message );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMqdlgSetHeaderTextOneL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMqdlgSetHeaderTextOneL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > message( KTestString );
    CAknMessageQueryDialog* dlg = CAknMessageQueryDialog::NewL( message,
        CAknQueryDialog::EConfirmationTone );
    CleanupStack::PushL( dlg );
    
    dlg->SetHeaderTextL( message );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMqdlgSetLinkTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMqdlgSetLinkTextL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > message( KTestString );
    CAknMessageQueryDialog* dlg = CAknMessageQueryDialog::NewL( message,
        CAknQueryDialog::EConfirmationTone );
    CleanupStack::PushL( dlg );
    
    dlg->SetLinkTextL( message );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMqdlgSetLinkL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMqdlgSetLinkL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > message( KTestString );
    CAknMessageQueryDialog* dlg = CAknMessageQueryDialog::NewL( message,
        CAknQueryDialog::EConfirmationTone );
    CleanupStack::PushL( dlg );
    
    TCallBack callBack;
    dlg->SetLink( callBack );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMqdlgOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMqdlgOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > message( KTestString );
    CAknMessageQueryDialog* dlg = CAknMessageQueryDialog::NewL( message,
        CAknQueryDialog::EConfirmationTone );
    
    dlg->PrepareLC( R_MESSAGE_DIALOG );

    TKeyEvent event;
    event.iCode = EKeyDownArrow;
    TKeyResponse response = dlg->OfferKeyEventL( event, EEventKey );
    STIF_ASSERT_EQUALS( EKeyWasConsumed, response );
    
    event.iCode = EKeyOK;
    response = dlg->OfferKeyEventL( event, EEventKey );
    STIF_ASSERT_EQUALS( EKeyWasConsumed, response );
    
    CleanupStack::Pop( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMqdlgHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMqdlgHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > message( KTestString );
    CAknMessageQueryDialog* dlg = CAknMessageQueryDialog::NewL( message,
        CAknQueryDialog::EConfirmationTone );
    
    dlg->PrepareLC( R_MESSAGE_DIALOG );
    
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
// CTestSDKQueries::TestMqdlgPreLayoutDynInitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMqdlgPreLayoutDynInitL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > message( KTestString );
    CAknMessageQueryDialog* dlg = CAknMessageQueryDialog::NewL( message,
        CAknQueryDialog::EConfirmationTone );
    
    dlg->PrepareLC( R_MESSAGE_DIALOG );
    CTestCAknMessageQueryDialog* dlgProtected = static_cast<CTestCAknMessageQueryDialog*>( dlg );
    
    TInt err = KErrNone;
    TRAP( err, dlgProtected->PreLayoutDynInitL() );
    
    CleanupStack::PopAndDestroy( dlg );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMqdlgSetSizeAndPositionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMqdlgSetSizeAndPositionL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > message( KTestString );
    CAknMessageQueryDialog* dlg = CAknMessageQueryDialog::NewL( message,
        CAknQueryDialog::EConfirmationTone );
    
    dlg->PrepareLC( R_MESSAGE_DIALOG );
    CTestCAknMessageQueryDialog* dlgProtected = static_cast<CTestCAknMessageQueryDialog*>( dlg );
    
    dlgProtected->PreLayoutDynInitL();
    TSize size = iContainer->Rect().Size();
    dlgProtected->SetSizeAndPosition( size );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMqdlgPostLayoutDynInitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMqdlgPostLayoutDynInitL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > message( KTestString );
    CAknMessageQueryDialog* dlg = CAknMessageQueryDialog::NewL( message,
        CAknQueryDialog::EConfirmationTone );
    
    dlg->PrepareLC( R_MESSAGE_DIALOG );
    CTestCAknMessageQueryDialog* dlgProtected = static_cast<CTestCAknMessageQueryDialog*>( dlg );
    
    dlgProtected->PostLayoutDynInitL();
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMqdlgProcessCommandL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMqdlgProcessCommandL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > message( KTestString );
    CAknMessageQueryDialog* dlg = CAknMessageQueryDialog::NewL( message,
        CAknQueryDialog::EConfirmationTone );
    
    dlg->PrepareLC( R_MESSAGE_DIALOG );
    CTestCAknMessageQueryDialog* dlgProtected = static_cast<CTestCAknMessageQueryDialog*>( dlg );
    
    TInt commandId = EAknSoftkeyView;
    dlgProtected->ProcessCommandL( commandId );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMqdlgConstructorTwoL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMqdlgConstructorTwoL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > message( KTestString );
    
    HBufC* buf = message.AllocL();
    CleanupStack::PushL( buf );
    HBufC* buffer = message.AllocL();
    CleanupStack::PushL( buffer );
    
    CAknMessageQueryDialog* dlg = new( ELeave ) CAknMessageQueryDialog( buf, buffer );
    CleanupStack::PushL( dlg );
    
    STIF_ASSERT_NOT_NULL( dlg );
    
    CleanupStack::PopAndDestroy( dlg );
    CleanupStack::Pop( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMqdlgConstructorThreeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMqdlgConstructorThreeL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > message( KTestString );
    
    CEikImage* mImage = new( ELeave ) CEikImage;
    CleanupStack::PushL( mImage );
    
    CAknMessageQueryDialog* dlg = new( ELeave ) CAknMessageQueryDialog( &message, &message,
        mImage );
    CleanupStack::PushL( dlg );
    
    STIF_ASSERT_NOT_NULL( dlg );
    
    CleanupStack::Pop( dlg );
    CleanupStack::PopAndDestroy( mImage );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMqdlgConstructorFourL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMqdlgConstructorFourL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > message( KTestString );
    
    HBufC* buf = message.AllocL();
    CleanupStack::PushL( buf );
    HBufC* buffer = message.AllocL();
    CleanupStack::PushL( buffer );
    
    CAknMessageQueryDialog* dlg = new( ELeave ) CAknMessageQueryDialog( buf, buffer, 
        CAknQueryDialog::EConfirmationTone );
    CleanupStack::PushL( dlg );
    
    STIF_ASSERT_NOT_NULL( dlg );
    
    CleanupStack::PopAndDestroy( dlg );
    CleanupStack::Pop( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMqdlgConstructorFiveL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMqdlgConstructorFiveL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > message( KTestString );
    
    HBufC* buf = message.AllocL();
    CleanupStack::PushL( buf );
    HBufC* buffer = message.AllocL();
    CleanupStack::PushL( buffer );
    
    CEikImage* mImage = new( ELeave ) CEikImage;
    CleanupStack::PushL( mImage );
    
    CAknMessageQueryDialog* dlg = new( ELeave ) CAknMessageQueryDialog( buf, buffer,
        mImage, CAknQueryDialog::EConfirmationTone );
    CleanupStack::PushL( dlg );
    
    STIF_ASSERT_NOT_NULL( dlg );
    
    CleanupStack::PopAndDestroy( dlg );
    CleanupStack::Pop( KThree );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMqdlgSetMessageTextTwoL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMqdlgSetMessageTextTwoL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > message( KTestString );
    CAknMessageQueryDialog* dlg = CAknMessageQueryDialog::NewL( message,
        CAknQueryDialog::EConfirmationTone );
    
    dlg->PrepareLC( R_MESSAGE_DIALOG );
    
    dlg->SetMessageText( &message );
    
    CleanupStack::Pop( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMqdlgSetMessageTextThreeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMqdlgSetMessageTextThreeL( CStifItemParser& /*aItem*/ )
    {
    TBuf16< KBufSize > msg( KTestString );
    const TBuf16< KBufSize > message( KTestString );
    CAknMessageQueryDialog* dlg = CAknMessageQueryDialog::NewL( msg,
        CAknQueryDialog::EConfirmationTone );
    
    dlg->PrepareLC( R_MESSAGE_DIALOG );
    
    dlg->SetMessageText( message );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMqdlgSetHeaderTextTwoL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMqdlgSetHeaderTextTwoL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > message( KTestString );
    HBufC* buffer = message.AllocL();
    CleanupStack::PushL( buffer );
    CAknMessageQueryDialog* dlg = CAknMessageQueryDialog::NewL( *buffer,
        CAknQueryDialog::EConfirmationTone );
    
    dlg->PrepareLC( R_MESSAGE_DIALOG );
    
    dlg->SetHeaderText( &message );
    
    CleanupStack::Pop( dlg );
    CleanupStack::PopAndDestroy( buffer );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMqdlgSetHeaderTextThreeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMqdlgSetHeaderTextThreeL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > message( KTestString );
    const TBuf< KBufSize > msg( KTestString );
    CAknMessageQueryDialog* dlg = CAknMessageQueryDialog::NewL( message,
        CAknQueryDialog::EConfirmationTone );
    
    dlg->PrepareLC( R_MESSAGE_DIALOG );
    
    dlg->SetHeaderText( msg );
    
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueries::TestMqcConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKQueries::TestMqdlgConstructorSixL( CStifItemParser& /*aItem*/ )
    {
    CAknMessageQueryDialog* dlg = new( ELeave ) CAknMessageQueryDialog;
    CleanupStack::PushL( dlg );
    STIF_ASSERT_NOT_NULL( dlg );
    CleanupStack::PopAndDestroy( dlg );
    return KErrNone;
    }

//End file


