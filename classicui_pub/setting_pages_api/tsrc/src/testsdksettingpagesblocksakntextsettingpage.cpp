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
* Description:  Test akntextsettingpage.h
*
*/


// INCLUDE FILES
#include <akntextsettingpage.h>

#include <testsdksettingpages.rsg>

#include "testsdksettingpages.h"
#include "testsdksettingpagesstdinclude.h"
#include "testakntextsettingpageprotected.h"
#include "testparentcontrol.h"

// ============================ MEMBER FUNCTIONS ===============================

//CAknEdwinSettingPage
// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesTextEdwinTextControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesTextEdwinTextControlL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestEdwinSettingPage* pageDialog = new( ELeave ) CTestEdwinSettingPage( &buffer, KOne, 
        EEikCtEdwin, R_TEXT_CONTROL, R_TEXT_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    CEikEdwin* edwinControl = pageDialog->TextControl();
    STIF_ASSERT_NOT_NULL( edwinControl );
    edwinControl = NULL;
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesTextEdwinHandlePointerEventLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesTextEdwinHandlePointerEventLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestEdwinSettingPage* pageDialog = new( ELeave ) CTestEdwinSettingPage( &buffer, KOne, 
        EEikCtEdwin, R_TEXT_CONTROL, R_TEXT_SETTING_PAGE );
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
// CTestSDKSettingPages::TestSettingPagesTextEdwinConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesTextEdwinConstructorL( CStifItemParser& /*aItem*/ )
    {
    CTestEdwinSettingPage* pageDialog = new( ELeave ) CTestEdwinSettingPage( R_TEXT_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    STIF_ASSERT_NOT_NULL( pageDialog );
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesTextEdwinConstructorLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesTextEdwinConstructorLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestEdwinSettingPage* pageDialog = new( ELeave ) CTestEdwinSettingPage( &buffer, KOne, 
        EEikCtEdwin, R_TEXT_CONTROL, R_TEXT_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    STIF_ASSERT_NOT_NULL( pageDialog );
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesTextEdwinSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesTextEdwinSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestEdwinSettingPage* pageDialog = new( ELeave ) CTestEdwinSettingPage( &buffer, KOne, 
        EEikCtEdwin, R_TEXT_CONTROL, R_TEXT_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    pageDialog->SizeChanged();
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesTextEdwinDrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesTextEdwinDrawL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestEdwinSettingPage* pageDialog = new( ELeave ) CTestEdwinSettingPage( &buffer, KOne, 
        EEikCtEdwin, R_TEXT_CONTROL, R_TEXT_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    pageDialog->DoActivateGc();
    TPoint topLeftPoint( KZero, KZero );
    TPoint bottomRightPoint( KTen, KTen );
    TRect rect( topLeftPoint, bottomRightPoint );
    pageDialog->ActivateL();
    pageDialog->DoLayoutRect();
    pageDialog->DoDraw( rect );
    pageDialog->DoDeactivateGc();
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

//CAknTextSettingPage
// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesTextTextConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesTextTextConstructorL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CAknTextSettingPage* pageDialog = new( ELeave ) CAknTextSettingPage( R_TEXT_SETTING_PAGE, buffer );
    CleanupStack::PushL( pageDialog );
    pageDialog->ConstructL();
    STIF_ASSERT_NOT_NULL( pageDialog );
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesTextTextConstructorLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesTextTextConstructorLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CAknTextSettingPage* pageDialog = new( ELeave ) CAknTextSettingPage( &buffer, KOne, 
        EEikCtEdwin, R_TEXT_CONTROL, R_TEXT_SETTING_PAGE, buffer );
    CleanupStack::PushL( pageDialog );
    pageDialog->ConstructL();
    STIF_ASSERT_NOT_NULL( pageDialog );
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesTextTextConstructLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesTextTextConstructLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CAknTextSettingPage* pageDialog = new( ELeave ) CAknTextSettingPage( &buffer, KOne, 
        EEikCtEdwin, R_TEXT_CONTROL, R_TEXT_SETTING_PAGE, buffer );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesTextTextHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesTextTextHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CAknTextSettingPage* pageDialog = new( ELeave ) CAknTextSettingPage( &buffer, KOne, 
        EEikCtEdwin, R_TEXT_CONTROL, R_TEXT_SETTING_PAGE, buffer );
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
// CTestSDKSettingPages::TestSettingPagesTextTextDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesTextTextDestructorL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CAknTextSettingPage* pageDialog = new( ELeave ) CAknTextSettingPage( &buffer, KOne, 
        EEikCtEdwin, R_TEXT_CONTROL, R_TEXT_SETTING_PAGE, buffer );
    CleanupStack::PushL( pageDialog );
    pageDialog->ConstructL();
    STIF_ASSERT_NOT_NULL( pageDialog );
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesTextTextDynamicInitLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesTextTextDynamicInitLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestTextSettingPage* pageDialog = new( ELeave ) CTestTextSettingPage( &buffer, KOne, 
        EEikCtEdwin, R_TEXT_CONTROL, R_TEXT_SETTING_PAGE, buffer );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    pageDialog->DoDynamicInitL();
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesTextTextUpdateSettingLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesTextTextUpdateSettingLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestTextSettingPage* pageDialog = new( ELeave ) CTestTextSettingPage( &buffer, KOne, 
        EEikCtEdwin, R_TEXT_CONTROL, R_TEXT_SETTING_PAGE, buffer );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    pageDialog->DoUpdateSettingL();
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesTextTextAcceptSettingLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesTextTextAcceptSettingLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestTextSettingPage* pageDialog = new( ELeave ) CTestTextSettingPage( &buffer, KOne, 
        EEikCtEdwin, R_TEXT_CONTROL, R_TEXT_SETTING_PAGE, buffer );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    pageDialog->DoAcceptSettingL();
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesTextTextRestoreOriginalSettingLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesTextTextRestoreOriginalSettingLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestTextSettingPage* pageDialog = new( ELeave ) CTestTextSettingPage( &buffer, KOne, 
        EEikCtEdwin, R_TEXT_CONTROL, R_TEXT_SETTING_PAGE, buffer );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    pageDialog->DoRestoreOriginalSettingL();
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesTextTextHandleControlEventLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesTextTextHandleControlEventLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestTextSettingPage* pageDialog = new( ELeave ) CTestTextSettingPage( &buffer, KOne, 
        EEikCtEdwin, R_TEXT_CONTROL, R_TEXT_SETTING_PAGE, buffer );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    pageDialog->DoHandleControlEventL( pageDialog->TextControl(),
        MCoeControlObserver::EEventStateChanged );
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesTextTextCheckAndSetDataValidityL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesTextTextCheckAndSetDataValidityL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestTextSettingPage* pageDialog = new( ELeave ) CTestTextSettingPage( &buffer, KOne, 
        EEikCtEdwin, R_TEXT_CONTROL, R_TEXT_SETTING_PAGE, buffer );
    CleanupStack::PushL( pageDialog );

    pageDialog->ConstructL();
    pageDialog->DoCheckAndSetDataValidity();
    
    CleanupStack::PopAndDestroy( pageDialog  );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesTextTextUpdateTextLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesTextTextUpdateTextLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestTextSettingPage* pageDialog = new( ELeave ) CTestTextSettingPage( &buffer, KOne, 
        EEikCtEdwin, R_TEXT_CONTROL, R_TEXT_SETTING_PAGE, buffer );
    CleanupStack::PushL( pageDialog );

    pageDialog->ConstructL();
    pageDialog->DoUpdateTextL();
    
    CleanupStack::PopAndDestroy( pageDialog  );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesTextTextUpdateCbaLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesTextTextUpdateCbaLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestTextSettingPage* pageDialog = new( ELeave ) CTestTextSettingPage( &buffer, KOne, 
        EEikCtEdwin, R_TEXT_CONTROL, R_TEXT_SETTING_PAGE, buffer );
    CleanupStack::PushL( pageDialog );

    pageDialog->ConstructL();
    pageDialog->DoUpdateCbaL();
    
    CleanupStack::PopAndDestroy( pageDialog  );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesTextTextOkToExitLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesTextTextOkToExitLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestTextSettingPage* pageDialog = new( ELeave ) CTestTextSettingPage( &buffer, KOne, 
        EEikCtEdwin, R_TEXT_CONTROL, R_TEXT_SETTING_PAGE, buffer );
    CleanupStack::PushL( pageDialog );

    pageDialog->ConstructL();
    pageDialog->DoOkToExitL( ETrue );
    pageDialog->DoOkToExitL( EFalse );
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesTextTextOfferKeyEventLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesTextTextOfferKeyEventLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestTextSettingPage* pageDialog = new( ELeave ) CTestTextSettingPage( &buffer, KOne, 
        EEikCtEdwin, R_TEXT_CONTROL, R_TEXT_SETTING_PAGE, buffer );
    CleanupStack::PushL( pageDialog );

    pageDialog->ConstructL();
    TKeyEvent event;
    event.iCode = EKeyEnter;
    pageDialog->DoOfferKeyEventL( event, EEventKey );
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesTextTextSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesTextTextSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestTextSettingPage* pageDialog = new( ELeave ) CTestTextSettingPage( &buffer, KOne, 
        EEikCtEdwin, R_TEXT_CONTROL, R_TEXT_SETTING_PAGE, buffer );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    pageDialog->DoSizeChanged();
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesTextTextWriteInternalStateLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesTextTextWriteInternalStateLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestTextSettingPage* pageDialog = new( ELeave ) CTestTextSettingPage( &buffer, KOne, 
        EEikCtEdwin, R_TEXT_CONTROL, R_TEXT_SETTING_PAGE, buffer );
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

//CAknIntegerSettingPage
// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesTextIntegerConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesTextIntegerConstructorL( CStifItemParser& /*aItem*/ )
    {
    TInt returnInteger( KZero );
    CAknIntegerSettingPage* pageDialog = new( ELeave ) CAknIntegerSettingPage( R_INTEGER_SETTING_PAGE, returnInteger );
    CleanupStack::PushL( pageDialog );
    STIF_ASSERT_NOT_NULL( pageDialog );
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesTextIntegerConstructorLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesTextIntegerConstructorLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TInt returnInteger( KZero );
    CAknIntegerSettingPage* pageDialog = new( ELeave ) CAknIntegerSettingPage( &buffer, KOne, 
        EAknCtIntegerEdwin, R_INTEGER_CONTROL, R_INTEGER_SETTING_PAGE, returnInteger );
    CleanupStack::PushL( pageDialog );
    STIF_ASSERT_NOT_NULL( pageDialog );
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesTextIntegerConstructLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesTextIntegerConstructLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TInt returnInteger( KZero );
    CAknIntegerSettingPage* pageDialog = new( ELeave ) CAknIntegerSettingPage( &buffer, KOne, 
        EAknCtIntegerEdwin, R_INTEGER_CONTROL, R_INTEGER_SETTING_PAGE, returnInteger );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesTextIntegerIntegerEditorControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesTextIntegerIntegerEditorControlL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TInt returnInteger( KZero );
    CAknIntegerSettingPage* pageDialog = new( ELeave ) CAknIntegerSettingPage( &buffer, KOne, 
        EAknCtIntegerEdwin, R_INTEGER_CONTROL, R_INTEGER_SETTING_PAGE, returnInteger );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    CAknIntegerEdwin* control = pageDialog->IntegerEditorControl();
    STIF_ASSERT_NOT_NULL( control );
    control = NULL;
    
    CleanupStack::PopAndDestroy(  pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesTextIntegerHandlePointerEventLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesTextIntegerHandlePointerEventLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TInt returnInteger( KZero );
    CAknIntegerSettingPage* pageDialog = new( ELeave ) CAknIntegerSettingPage( &buffer, KOne, 
        EAknCtIntegerEdwin, R_INTEGER_CONTROL, R_INTEGER_SETTING_PAGE, returnInteger );
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
// CTestSDKSettingPages::TestSettingPagesTextIntegerDynamicInitLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesTextIntegerDynamicInitLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TInt returnInteger( KZero );
    CTestIntegerSettingPage* pageDialog = new( ELeave ) CTestIntegerSettingPage( &buffer, KOne, 
        EAknCtIntegerEdwin, R_INTEGER_CONTROL, R_INTEGER_SETTING_PAGE, returnInteger );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    pageDialog->DoDynamicInitL();
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesTextIntegerUpdateSettingLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesTextIntegerUpdateSettingLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TInt returnInteger( KZero );
    CTestIntegerSettingPage* pageDialog = new( ELeave ) CTestIntegerSettingPage( &buffer, KOne, 
        EAknCtIntegerEdwin, R_INTEGER_CONTROL, R_INTEGER_SETTING_PAGE, returnInteger );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    pageDialog->DoUpdateSettingL();
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesTextIntegerRestoreOriginalSettingLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesTextIntegerRestoreOriginalSettingLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TInt returnInteger( KZero );
    CTestIntegerSettingPage* pageDialog = new( ELeave ) CTestIntegerSettingPage( &buffer, KOne, 
        EAknCtIntegerEdwin, R_INTEGER_CONTROL, R_INTEGER_SETTING_PAGE, returnInteger );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    pageDialog->DoRestoreOriginalSettingL();
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesTextIntegerCheckAndSetDataValidityL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesTextIntegerCheckAndSetDataValidityL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TInt returnInteger( KZero );
    CTestIntegerSettingPage* pageDialog = new( ELeave ) CTestIntegerSettingPage( &buffer, KOne, 
        EAknCtIntegerEdwin, R_INTEGER_CONTROL, R_INTEGER_SETTING_PAGE, returnInteger );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    pageDialog->DoCheckAndSetDataValidity();
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesTextIntegerUpdateCbaLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesTextIntegerUpdateCbaLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TInt returnInteger( KZero );
    CTestIntegerSettingPage* pageDialog = new( ELeave ) CTestIntegerSettingPage( &buffer, KOne, 
        EAknCtIntegerEdwin, R_INTEGER_CONTROL, R_INTEGER_SETTING_PAGE, returnInteger );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    pageDialog->DoUpdateCbaL();
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesTextIntegerHandleControlEventLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesTextIntegerHandleControlEventLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TInt returnInteger( KZero );
    CTestIntegerSettingPage* pageDialog = new( ELeave ) CTestIntegerSettingPage( &buffer, KOne, 
        EAknCtIntegerEdwin, R_INTEGER_CONTROL, R_INTEGER_SETTING_PAGE, returnInteger );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    pageDialog->DoHandleControlEventL( pageDialog->IntegerEditorControl(),
        MCoeControlObserver::EEventStateChanged );
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesTextIntegerSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesTextIntegerSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TInt returnInteger( KZero );
    CTestIntegerSettingPage* pageDialog = new( ELeave ) CTestIntegerSettingPage( &buffer, KOne, 
        EAknCtIntegerEdwin, R_INTEGER_CONTROL, R_INTEGER_SETTING_PAGE, returnInteger );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    pageDialog->DoSizeChanged();
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesTextIntegerWriteInternalStateLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesTextIntegerWriteInternalStateLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TInt returnInteger( KZero );
    CTestIntegerSettingPage* pageDialog = new( ELeave ) CTestIntegerSettingPage( &buffer, KOne, 
        EAknCtIntegerEdwin, R_INTEGER_CONTROL, R_INTEGER_SETTING_PAGE, returnInteger );
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

//End file


