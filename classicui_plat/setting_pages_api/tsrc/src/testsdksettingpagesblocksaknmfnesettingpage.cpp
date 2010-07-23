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
* Description:  Test aknmfnesettingpage.h
*
*/

// INCLUDE FILES
#include <aknmfnesettingpage.h>
#include <testsdksettingpages.rsg>
#include <bautils.h>
#include <in_sock.h>

#include "testsdksettingpagesstdinclude.h"
#include "testsdksettingpages.h"
#include "testparentcontrol.h"
#include "testaknmfnesettingpageprotected.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneHandlePointerEventLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneHandlePointerEventLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestMfneSettingPage* pageDialog = new( ELeave ) CTestMfneSettingPage( &buffer, KOne, 
        EEikCtDateEditor, R_DATE_CONTROL, R_DATE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    pageDialog->DoBaseConstructL();
    pageDialog->DoConstructL();
    
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
// CTestSDKSettingPages::TestSettingPagesMfneDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneDestructorL( CStifItemParser& /*aItem*/ )
    {
    CTestMfneSettingPage* pageDialog = new( ELeave ) CTestMfneSettingPage( R_DATE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    STIF_ASSERT_NOT_NULL( pageDialog );
    CleanupStack::PopAndDestroy( pageDialog );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneConstructorL( CStifItemParser& /*aItem*/ )
    {
    CTestMfneSettingPage* pageDialog = new( ELeave ) CTestMfneSettingPage( R_DATE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    STIF_ASSERT_NOT_NULL( pageDialog );
    CleanupStack::PopAndDestroy( pageDialog );
        
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneConstructorLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneConstructorLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestMfneSettingPage* pageDialog = new( ELeave ) CTestMfneSettingPage( &buffer, KOne, 
        EEikCtDateEditor, R_DATE_CONTROL, R_DATE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    STIF_ASSERT_NOT_NULL( pageDialog );
    CleanupStack::PopAndDestroy( pageDialog );
        
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestMfneSettingPage* pageDialog = new( ELeave ) CTestMfneSettingPage( &buffer, KOne, 
        EEikCtDateEditor, R_DATE_CONTROL, R_DATE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->DoBaseConstructL();
    pageDialog->DoConstructL();
    pageDialog->DoSizeChanged();
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneDrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneDrawL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestMfneSettingPage* pageDialog = new( ELeave ) CTestMfneSettingPage( &buffer, KOne, 
        EEikCtDateEditor, R_DATE_CONTROL, R_DATE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->DoBaseConstructL();
    pageDialog->DoConstructL();
    pageDialog->ActivateL();
    TRect rect( 0, 0, 1, 1 );
    pageDialog->DoActivateGc();
    pageDialog->DoDraw( rect );
    pageDialog->DoDeactivateGc();
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneMfneL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneMfneL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestMfneSettingPage* pageDialog = new( ELeave ) CTestMfneSettingPage( &buffer, KOne, 
        EEikCtDateEditor, R_DATE_CONTROL, R_DATE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->DoBaseConstructL();
    pageDialog->DoConstructL();
    CEikMfne* mfne = pageDialog->DoMfne();
    STIF_ASSERT_NOT_NULL( mfne );
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneCheckAndSetDataValidityL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneCheckAndSetDataValidityL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestMfneSettingPage* pageDialog = new( ELeave ) CTestMfneSettingPage( &buffer, KOne, 
        EEikCtDateEditor, R_DATE_CONTROL, R_DATE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->DoBaseConstructL();
    pageDialog->DoConstructL();
    pageDialog->DoCheckAndSetDataValidity();
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneHandleControlEventLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneHandleControlEventLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestMfneSettingPage* pageDialog = new( ELeave ) CTestMfneSettingPage( &buffer, KOne, 
        EEikCtDateEditor, R_DATE_CONTROL, R_DATE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->DoBaseConstructL();
    pageDialog->DoConstructL();
    pageDialog->DoHandleControlEventL( pageDialog->DoMfne(),
        MCoeControlObserver::EEventStateChanged );
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneConstructLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneConstructLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestMfneSettingPage* pageDialog = new( ELeave ) CTestMfneSettingPage( &buffer, KOne, 
        EEikCtDateEditor, R_DATE_CONTROL, R_DATE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->DoBaseConstructL();
    pageDialog->DoConstructL();
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneCountComponentControlsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneCountComponentControlsL( CStifItemParser& /*aItem*/ ) 
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestMfneSettingPage* pageDialog = new( ELeave ) CTestMfneSettingPage( &buffer, KOne, 
        EEikCtDateEditor, R_DATE_CONTROL, R_DATE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->DoBaseConstructL();
    pageDialog->DoConstructL();
    TInt controlNumber = pageDialog->DoCountComponentControls();
    STIF_ASSERT_NOT_EQUALS( KZero, controlNumber );
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneComponentControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneComponentControlL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    CTestMfneSettingPage* pageDialog = new( ELeave ) CTestMfneSettingPage( &buffer, KZero, 
        EEikCtDateEditor, R_DATE_CONTROL, R_DATE_SETTING_PAGE );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->DoBaseConstructL();
    pageDialog->DoConstructL();
    CCoeControl* control = pageDialog->DoComponentControl( KOne );
    CEikMfne* editorControl = pageDialog->DoMfne();
    STIF_ASSERT_EQUALS( static_cast<CCoeControl*>( editorControl ), control );
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneDateConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneDateConstructorL( CStifItemParser /*aItem*/ ) 
    {
    TBuf< KTimeSize > timeValue( KTime );
    TTime time( timeValue );
    CAknDateSettingPage* dateDlg = new( ELeave ) CAknDateSettingPage( R_DATE_SETTING_PAGE, time );
    CleanupStack::PushL( dateDlg );
    STIF_ASSERT_NOT_NULL( dateDlg );
    CleanupStack::PopAndDestroy( dateDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneDateConstructorLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneDateConstructorLL( CStifItemParser /*aItem*/ ) 
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KTimeSize > timeValue( KTime );
    TTime time( timeValue );
    CAknDateSettingPage* dateDlg = new( ELeave ) CAknDateSettingPage( &buffer, KOne, 
            EEikCtDateEditor, R_DATE_CONTROL, R_DATE_SETTING_PAGE, time );
    CleanupStack::PushL( dateDlg );
    STIF_ASSERT_NOT_NULL( dateDlg );
    CleanupStack::PopAndDestroy( dateDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneDateConstructLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneDateConstructLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KTimeSize > timeValue( KTime );
    TTime time( timeValue );
    CAknDateSettingPage* dateDlg = new( ELeave ) CAknDateSettingPage( &buffer, KOne, 
            EEikCtDateEditor, R_DATE_CONTROL, R_DATE_SETTING_PAGE, time );
    CleanupStack::PushL( dateDlg );
    dateDlg->ConstructL();
    
    CleanupStack::PopAndDestroy( dateDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneDateEditorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneDateEditorL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KTimeSize > timeValue( KTime );
    TTime time( timeValue );
    CAknDateSettingPage* dateDlg = new( ELeave ) CAknDateSettingPage( &buffer, KOne, 
            EEikCtDateEditor, R_DATE_CONTROL, R_DATE_SETTING_PAGE, time );
    CleanupStack::PushL( dateDlg );
    dateDlg->ConstructL();
    
    CEikDateEditor* dateControl = dateDlg->DateEditor();
    STIF_ASSERT_NOT_NULL( dateControl );
    
    CleanupStack::PopAndDestroy( dateDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneDateHandlePointerEventLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneDateHandlePointerEventLL( CStifItemParser& /*aItem*/ ) 
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KTimeSize > timeValue( KTime );
    TTime time( timeValue );
    CAknDateSettingPage* dateDlg = new( ELeave ) CAknDateSettingPage( &buffer, KOne, 
            EEikCtDateEditor, R_DATE_CONTROL, R_DATE_SETTING_PAGE, time );
    CleanupStack::PushL( dateDlg );
    dateDlg->ConstructL();
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    dateDlg->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( dateDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneDateDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneDateDestructorL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KTimeSize > timeValue( KTime );
    TTime time( timeValue );
    CAknDateSettingPage* dateDlg = new( ELeave ) CAknDateSettingPage( &buffer, KOne, 
            EEikCtDateEditor, R_DATE_CONTROL, R_DATE_SETTING_PAGE, time );
    CleanupStack::PushL( dateDlg );
    CleanupStack::PopAndDestroy( dateDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneDateUpdateSettingLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneDateUpdateSettingLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KTimeSize > timeValue( KTime );
    TTime time( timeValue );
    CTestDateSettingPage* dateDlg = new( ELeave ) CTestDateSettingPage( &buffer, KOne, 
            EEikCtDateEditor, R_DATE_CONTROL, R_DATE_SETTING_PAGE, time );
    CleanupStack::PushL( dateDlg );
    dateDlg->ConstructL();
    dateDlg->DoUpdateSettingL();
    CleanupStack::PopAndDestroy( dateDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneDateAcceptSettingLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneDateAcceptSettingLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KTimeSize > timeValue( KTime );
    TTime time( timeValue );
    CTestDateSettingPage* dateDlg = new( ELeave ) CTestDateSettingPage( &buffer, KOne, 
            EEikCtDateEditor, R_DATE_CONTROL, R_DATE_SETTING_PAGE, time );
    CleanupStack::PushL( dateDlg );
    dateDlg->ConstructL();
    dateDlg->DoAcceptSettingL();
    CleanupStack::PopAndDestroy( dateDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneDateRestoreOriginalSettingLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneDateRestoreOriginalSettingLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KTimeSize > timeValue( KTime );
    TTime time( timeValue );
    CTestDateSettingPage* dateDlg = new( ELeave ) CTestDateSettingPage( &buffer, KOne, 
            EEikCtDateEditor, R_DATE_CONTROL, R_DATE_SETTING_PAGE, time );
    CleanupStack::PushL( dateDlg );
    dateDlg->ConstructL();
    dateDlg->DoRestoreOriginalSettingL();
    CleanupStack::PopAndDestroy( dateDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneDateWriteInternalStateLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneDateWriteInternalStateLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KTimeSize > timeValue( KTime );
    TTime time( timeValue );
    CTestDateSettingPage* dateDlg = new( ELeave ) CTestDateSettingPage( &buffer, KOne, 
            EEikCtDateEditor, R_DATE_CONTROL, R_DATE_SETTING_PAGE, time );
    CleanupStack::PushL( dateDlg );
    dateDlg->ConstructL();
    
    RDesWriteStream stream;
    CleanupClosePushL( stream );
    HBufC8* hbuf = HBufC8::NewL( KHBufSize );
    CleanupStack::PushL( hbuf );
    TPtr8 ptr = hbuf->Des();
    stream.Open( ptr );
    dateDlg->DoWriteInternalStateL( stream );
    stream.CommitL();
    stream.Close();
    
    CleanupStack::PopAndDestroy( KThree );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneTimeConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneTimeConstructorL( CStifItemParser /*aItem*/ )
    {
    TBuf< KTimeSize > timeValue( KTime );
    TTime time( timeValue );
    CAknTimeSettingPage* timeDlg = new( ELeave ) CAknTimeSettingPage( R_TIME_SETTING_PAGE, time );
    CleanupStack::PushL( timeDlg );
    STIF_ASSERT_NOT_NULL( timeDlg );
    CleanupStack::PopAndDestroy( timeDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneTimeConstructorLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneTimeConstructorLL( CStifItemParser /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KTimeSize > timeValue( KTime );
    TTime time( timeValue );
    CAknTimeSettingPage* timeDlg = new( ELeave ) CAknTimeSettingPage( &buffer, KOne, 
        EEikCtTimeEditor, R_TIME_CONTROL, R_TIME_SETTING_PAGE, time );
    CleanupStack::PushL( timeDlg );
    STIF_ASSERT_NOT_NULL( timeDlg );
    CleanupStack::PopAndDestroy( timeDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneTimeConstructLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneTimeConstructLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KTimeSize > timeValue( KTime );
    TTime time( timeValue );
    CAknTimeSettingPage* timeDlg = new( ELeave ) CAknTimeSettingPage( &buffer, KOne, 
        EEikCtTimeEditor, R_TIME_CONTROL, R_TIME_SETTING_PAGE, time );
    CleanupStack::PushL( timeDlg );
    timeDlg->ConstructL();
    CleanupStack::PopAndDestroy( timeDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneTimeEditorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneTimeEditorL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KTimeSize > timeValue( KTime );
    TTime time( timeValue );
    CAknTimeSettingPage* timeDlg = new( ELeave ) CAknTimeSettingPage( &buffer, KOne, 
        EEikCtTimeEditor, R_TIME_CONTROL, R_TIME_SETTING_PAGE, time );
    CleanupStack::PushL( timeDlg );
    timeDlg->ConstructL();
    
    CEikTimeEditor* timeControl = timeDlg->TimeEditor();
    STIF_ASSERT_NOT_NULL( timeControl );
    
    CleanupStack::PopAndDestroy( timeDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneTimeHandlePointerEventLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneTimeHandlePointerEventLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KTimeSize > timeValue( KTime );
    TTime time( timeValue );
    CAknTimeSettingPage* timeDlg = new( ELeave ) CAknTimeSettingPage( &buffer, KOne, 
        EEikCtTimeEditor, R_TIME_CONTROL, R_TIME_SETTING_PAGE, time );
    CleanupStack::PushL( timeDlg );
    timeDlg->ConstructL();
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    timeDlg->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( timeDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneTimeDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneTimeDestructorL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KTimeSize > timeValue( KTime );
    TTime time( timeValue );
    CAknTimeSettingPage* timeDlg = new( ELeave ) CAknTimeSettingPage( &buffer, KOne, 
        EEikCtTimeEditor, R_TIME_CONTROL, R_TIME_SETTING_PAGE, time );
    CleanupStack::PushL( timeDlg );
    CleanupStack::PopAndDestroy( timeDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneTimeUpdateSettingLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneTimeUpdateSettingLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KTimeSize > timeValue( KTime );
    TTime time( timeValue );
    CTestTimeSettingPage* timeDlg = new( ELeave ) CTestTimeSettingPage( &buffer, KOne, 
        EEikCtTimeEditor, R_TIME_CONTROL, R_TIME_SETTING_PAGE, time );
    CleanupStack::PushL( timeDlg );
    timeDlg->ConstructL();
    timeDlg->DoUpdateSettingL();
    CleanupStack::PopAndDestroy( timeDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneTimeAcceptSettingLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneTimeAcceptSettingLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KTimeSize > timeValue( KTime );
    TTime time( timeValue );
    CTestTimeSettingPage* timeDlg = new( ELeave ) CTestTimeSettingPage( &buffer, KOne, 
        EEikCtTimeEditor, R_TIME_CONTROL, R_TIME_SETTING_PAGE, time );
    CleanupStack::PushL( timeDlg );
    timeDlg->ConstructL();
    timeDlg->DoAcceptSettingL();
    CleanupStack::PopAndDestroy( timeDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneTimeRestoreOriginalSettingLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneTimeRestoreOriginalSettingLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KTimeSize > timeValue( KTime );
    TTime time( timeValue );
    CTestTimeSettingPage* timeDlg = new( ELeave ) CTestTimeSettingPage( &buffer, KOne, 
        EEikCtTimeEditor, R_TIME_CONTROL, R_TIME_SETTING_PAGE, time );
    CleanupStack::PushL( timeDlg );
    timeDlg->ConstructL();
    timeDlg->DoRestoreOriginalSettingL();
    CleanupStack::PopAndDestroy( timeDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneTimeWriteInternalStateLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneTimeWriteInternalStateLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TBuf< KTimeSize > timeValue( KTime );
    TTime time( timeValue );
    CTestTimeSettingPage* timeDlg = new( ELeave ) CTestTimeSettingPage( &buffer, KOne, 
        EEikCtTimeEditor, R_TIME_CONTROL, R_TIME_SETTING_PAGE, time );
    CleanupStack::PushL( timeDlg );
    timeDlg->ConstructL();
    
    RDesWriteStream stream;
    CleanupClosePushL( stream );
    HBufC8* hbuf = HBufC8::NewL( KHBufSize );
    CleanupStack::PushL( hbuf );
    TPtr8 ptr = hbuf->Des();
    stream.Open( ptr );
    timeDlg->DoWriteInternalStateL( stream );
    stream.CommitL();
    stream.Close();
    
    CleanupStack::PopAndDestroy( KThree );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneDurationConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneDurationConstructorL( CStifItemParser /*aItem*/ )
    {
    TTimeIntervalSeconds mIntervalue = KTimeIntervalue;
    CAknDurationSettingPage* DurationDlg = new( ELeave ) CAknDurationSettingPage( R_TIME_SETTING_PAGE, mIntervalue );
    CleanupStack::PushL( DurationDlg );
    STIF_ASSERT_NOT_NULL( DurationDlg );
    CleanupStack::PopAndDestroy( DurationDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneDurationConstructorLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneDurationConstructorLL( CStifItemParser /*aItem*/ )
    {
    TTimeIntervalSeconds mIntervalue = KTimeIntervalue;
    TBuf< KBufSize > buffer( KTestString );
    CAknDurationSettingPage* DurationDlg = new( ELeave ) CAknDurationSettingPage( &buffer, KOne, 
        EEikCtTimeEditor, R_TIME_CONTROL, R_TIME_SETTING_PAGE, mIntervalue );
    CleanupStack::PushL( DurationDlg );
    STIF_ASSERT_NOT_NULL( DurationDlg );
    CleanupStack::PopAndDestroy( DurationDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneDurationConstructLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneDurationConstructLL( CStifItemParser& /*aItem*/ )
    {
    TTimeIntervalSeconds mIntervalue = KTimeIntervalue;
    TBuf< KBufSize > buffer( KTestString );
    CAknDurationSettingPage* DurationDlg = new( ELeave ) CAknDurationSettingPage( &buffer, KOne, 
        EEikCtTimeEditor, R_TIME_CONTROL, R_TIME_SETTING_PAGE, mIntervalue );
    CleanupStack::PushL( DurationDlg );
    DurationDlg->ConstructL();
    CleanupStack::PopAndDestroy( DurationDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneDurationDurationEditorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneDurationDurationEditorL( CStifItemParser& /*aItem*/ )
    {
    TTimeIntervalSeconds mIntervalue = KTimeIntervalue;
    TBuf< KBufSize > buffer( KTestString );
    CAknDurationSettingPage* DurationDlg = new( ELeave ) CAknDurationSettingPage( &buffer, KOne, 
        EEikCtTimeEditor, R_TIME_CONTROL, R_TIME_SETTING_PAGE, mIntervalue );
    CleanupStack::PushL( DurationDlg );
    DurationDlg->ConstructL();
    
    CEikDurationEditor* timeControl = DurationDlg->DurationEditor();
    STIF_ASSERT_NOT_NULL( timeControl );
    
    CleanupStack::PopAndDestroy( DurationDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneDurationHandlePointerEventLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneDurationHandlePointerEventLL( CStifItemParser& /*aItem*/ )
    {
    TTimeIntervalSeconds mIntervalue = KTimeIntervalue;
    TBuf< KBufSize > buffer( KTestString );
    CAknDurationSettingPage* DurationDlg = new( ELeave ) CAknDurationSettingPage( &buffer, KOne, 
        EEikCtTimeEditor, R_TIME_CONTROL, R_TIME_SETTING_PAGE, mIntervalue );
    CleanupStack::PushL( DurationDlg );
    DurationDlg->ConstructL();
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    DurationDlg->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( DurationDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneDurationDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneDurationDestructorL( CStifItemParser& /*aItem*/ )
    {
    TTimeIntervalSeconds mIntervalue = KTimeIntervalue;
    TBuf< KBufSize > buffer( KTestString );
    CTestDurationSettingPage* DurationDlg = new( ELeave ) CTestDurationSettingPage( &buffer, KOne, 
        EEikCtTimeEditor, R_TIME_CONTROL, R_TIME_SETTING_PAGE, mIntervalue );
    CleanupStack::PushL( DurationDlg );
    CleanupStack::PopAndDestroy( DurationDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneDurationUpdateSettingLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneDurationUpdateSettingLL( CStifItemParser& /*aItem*/ )
    {
    TTimeIntervalSeconds mIntervalue = KTimeIntervalue;
    TBuf< KBufSize > buffer( KTestString );
    CTestDurationSettingPage* DurationDlg = new( ELeave ) CTestDurationSettingPage( &buffer, KOne, 
        EEikCtTimeEditor, R_TIME_CONTROL, R_TIME_SETTING_PAGE, mIntervalue );
    CleanupStack::PushL( DurationDlg );
    DurationDlg->ConstructL();
    DurationDlg->DoUpdateSettingL();
    CleanupStack::PopAndDestroy( DurationDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneDurationAcceptSettingLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneDurationAcceptSettingLL( CStifItemParser& /*aItem*/ )
    {
    TTimeIntervalSeconds mIntervalue = KTimeIntervalue;
    TBuf< KBufSize > buffer( KTestString );
    CTestDurationSettingPage* DurationDlg = new( ELeave ) CTestDurationSettingPage( &buffer, KOne, 
        EEikCtTimeEditor, R_TIME_CONTROL, R_TIME_SETTING_PAGE, mIntervalue );
    CleanupStack::PushL( DurationDlg );
    DurationDlg->ConstructL();
    DurationDlg->DoAcceptSettingL();
    CleanupStack::PopAndDestroy( DurationDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneDurationRestoreOriginalSettingLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneDurationRestoreOriginalSettingLL( CStifItemParser& /*aItem*/ )
    {
    TTimeIntervalSeconds mIntervalue = KTimeIntervalue;
    TBuf< KBufSize > buffer( KTestString );
    CTestDurationSettingPage* DurationDlg = new( ELeave ) CTestDurationSettingPage( &buffer, KOne, 
        EEikCtTimeEditor, R_TIME_CONTROL, R_TIME_SETTING_PAGE, mIntervalue );
    CleanupStack::PushL( DurationDlg );
    DurationDlg->ConstructL();
    DurationDlg->DoRestoreOriginalSettingL();
    CleanupStack::PopAndDestroy( DurationDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneDurationWriteInternalStateLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneDurationWriteInternalStateLL( CStifItemParser& /*aItem*/ )
    {
    TTimeIntervalSeconds mIntervalue = KTimeIntervalue;
    TBuf< KBufSize > buffer( KTestString );
    CTestDurationSettingPage* DurationDlg = new( ELeave ) CTestDurationSettingPage( &buffer, KOne, 
        EEikCtTimeEditor, R_TIME_CONTROL, R_TIME_SETTING_PAGE, mIntervalue );
    CleanupStack::PushL( DurationDlg );
    DurationDlg->ConstructL();
    
    RDesWriteStream stream;
    CleanupClosePushL( stream );
    HBufC8* hbuf = HBufC8::NewL( KHBufSize );
    CleanupStack::PushL( hbuf );
    TPtr8 ptr = hbuf->Des();
    stream.Open( ptr );
    DurationDlg->DoWriteInternalStateL( stream );
    stream.CommitL();
    stream.Close();
    
    CleanupStack::PopAndDestroy( KThree );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneTimeOffSetConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneTimeOffSetConstructorL( CStifItemParser /*aItem*/ )
    {
    TTimeIntervalSeconds mIntervalue = KTimeIntervalue;
    CAknTimeOffsetSettingPage* TimeOffsetDlg = new( ELeave ) CAknTimeOffsetSettingPage( R_TIMEOFFSET_SETTING_PAGE, mIntervalue );
    CleanupStack::PushL( TimeOffsetDlg );
    STIF_ASSERT_NOT_NULL( TimeOffsetDlg );
    CleanupStack::PopAndDestroy( TimeOffsetDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneTimeOffSetConstructorLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneTimeOffSetConstructorLL( CStifItemParser /*aItem*/ )
    {
    TTimeIntervalSeconds mIntervalue = KTimeIntervalue;
    TBuf< KBufSize > buffer( KTestString );
    CAknTimeOffsetSettingPage* TimeOffsetDlg = new( ELeave ) CAknTimeOffsetSettingPage( &buffer, KOne, 
        EEikCtTimeOffsetEditor, R_TIMEOFFSET_CONTROL, R_TIMEOFFSET_SETTING_PAGE, mIntervalue );
    CleanupStack::PushL( TimeOffsetDlg );
    STIF_ASSERT_NOT_NULL( TimeOffsetDlg );
    CleanupStack::PopAndDestroy( TimeOffsetDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneTimeOffSetConstructLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneTimeOffSetConstructLL( CStifItemParser& /*aItem*/ )
    {
    TTimeIntervalSeconds mIntervalue = KTimeIntervalue;
    TBuf< KBufSize > buffer( KTestString );
    CAknTimeOffsetSettingPage* TimeOffsetDlg = new( ELeave ) CAknTimeOffsetSettingPage( &buffer, KOne, 
        EEikCtTimeOffsetEditor, R_TIMEOFFSET_CONTROL, R_TIMEOFFSET_SETTING_PAGE, mIntervalue );
    CleanupStack::PushL( TimeOffsetDlg );
    TimeOffsetDlg->ConstructL();
    CleanupStack::PopAndDestroy( TimeOffsetDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneTimeOffSetTimeOffsetEditorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneTimeOffSetTimeOffsetEditorL( CStifItemParser& /*aItem*/ )
    {
    TTimeIntervalSeconds mIntervalue = KTimeIntervalue;
    TBuf< KBufSize > buffer( KTestString );
    CAknTimeOffsetSettingPage* TimeOffsetDlg = new( ELeave ) CAknTimeOffsetSettingPage( &buffer, KOne, 
        EEikCtTimeOffsetEditor, R_TIMEOFFSET_CONTROL, R_TIMEOFFSET_SETTING_PAGE, mIntervalue );
    CleanupStack::PushL( TimeOffsetDlg );
    TimeOffsetDlg->ConstructL();
    
    CEikTimeOffsetEditor* timeOffsetControl = TimeOffsetDlg->TimeOffsetEditor();
    STIF_ASSERT_NOT_NULL( timeOffsetControl );
    
    CleanupStack::PopAndDestroy( TimeOffsetDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneTimeOffSetHandlePointerEventLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneTimeOffSetHandlePointerEventLL( CStifItemParser& /*aItem*/ )
    {
    TTimeIntervalSeconds mIntervalue = KTimeIntervalue;
    TBuf< KBufSize > buffer( KTestString );
    CAknTimeOffsetSettingPage* TimeOffsetDlg = new( ELeave ) CAknTimeOffsetSettingPage( &buffer, KOne, 
        EEikCtTimeOffsetEditor, R_TIMEOFFSET_CONTROL, R_TIMEOFFSET_SETTING_PAGE, mIntervalue );
    CleanupStack::PushL( TimeOffsetDlg );
    TimeOffsetDlg->ConstructL();
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    TimeOffsetDlg->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( TimeOffsetDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneTimeOffSetDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneTimeOffSetDestructorL( CStifItemParser& /*aItem*/ )
    {
    TTimeIntervalSeconds mIntervalue = KTimeIntervalue;
    TBuf< KBufSize > buffer( KTestString );
    CTestTimeOffsetSettingPage* TimeOffsetDlg = new( ELeave ) CTestTimeOffsetSettingPage( &buffer, KOne, 
        EEikCtTimeOffsetEditor, R_TIMEOFFSET_CONTROL, R_TIMEOFFSET_SETTING_PAGE, mIntervalue );
    CleanupStack::PushL( TimeOffsetDlg );
    CleanupStack::PopAndDestroy( TimeOffsetDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneTimeOffSetUpdateSettingLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneTimeOffSetUpdateSettingLL( CStifItemParser& /*aItem*/ )
    {
    TTimeIntervalSeconds mIntervalue = KTimeIntervalue;
    TBuf< KBufSize > buffer( KTestString );
    CTestTimeOffsetSettingPage* TimeOffsetDlg = new( ELeave ) CTestTimeOffsetSettingPage( &buffer, KOne, 
        EEikCtTimeOffsetEditor, R_TIMEOFFSET_CONTROL, R_TIMEOFFSET_SETTING_PAGE, mIntervalue );
    CleanupStack::PushL( TimeOffsetDlg );
    TimeOffsetDlg->ConstructL();
    TimeOffsetDlg->DoUpdateSettingL();
    CleanupStack::PopAndDestroy( TimeOffsetDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneTimeOffSetAcceptSettingLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneTimeOffSetAcceptSettingLL( CStifItemParser& /*aItem*/ )
    {
    TTimeIntervalSeconds mIntervalue = KTimeIntervalue;
    TBuf< KBufSize > buffer( KTestString );
    CTestTimeOffsetSettingPage* TimeOffsetDlg = new( ELeave ) CTestTimeOffsetSettingPage( &buffer, KOne, 
        EEikCtTimeOffsetEditor, R_TIMEOFFSET_CONTROL, R_TIMEOFFSET_SETTING_PAGE, mIntervalue );
    CleanupStack::PushL( TimeOffsetDlg );
    TimeOffsetDlg->ConstructL();
    TimeOffsetDlg->DoAcceptSettingL();
    CleanupStack::PopAndDestroy( TimeOffsetDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneTimeOffSetRestoreOriginalSettingLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneTimeOffSetRestoreOriginalSettingLL( CStifItemParser& /*aItem*/ )
    {
    TTimeIntervalSeconds mIntervalue = KTimeIntervalue;
    TBuf< KBufSize > buffer( KTestString );
    CTestTimeOffsetSettingPage* TimeOffsetDlg = new( ELeave ) CTestTimeOffsetSettingPage( &buffer, KOne, 
        EEikCtTimeOffsetEditor, R_TIMEOFFSET_CONTROL, R_TIMEOFFSET_SETTING_PAGE, mIntervalue );
    CleanupStack::PushL( TimeOffsetDlg );
    TimeOffsetDlg->ConstructL();
    TimeOffsetDlg->DoRestoreOriginalSettingL();
    CleanupStack::PopAndDestroy( TimeOffsetDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneTimeOffSetWriteInternalStateLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneTimeOffSetWriteInternalStateLL( CStifItemParser& /*aItem*/ )
    {
    TTimeIntervalSeconds mIntervalue = KTimeIntervalue;
    TBuf< KBufSize > buffer( KTestString );
    CTestTimeOffsetSettingPage* TimeOffsetDlg = new( ELeave ) CTestTimeOffsetSettingPage( &buffer, KOne, 
        EEikCtTimeOffsetEditor, R_TIMEOFFSET_CONTROL, R_TIMEOFFSET_SETTING_PAGE, mIntervalue );
    CleanupStack::PushL( TimeOffsetDlg );
    TimeOffsetDlg->ConstructL();
    
    RDesWriteStream stream;
    CleanupClosePushL( stream );
    HBufC8* hbuf = HBufC8::NewL( KHBufSize );
    CleanupStack::PushL( hbuf );
    TPtr8 ptr = hbuf->Des();
    stream.Open( ptr );
    TimeOffsetDlg->DoWriteInternalStateL( stream );
    stream.CommitL();
    stream.Close();
    
    CleanupStack::PopAndDestroy( KThree );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneIpFieldConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneIpFieldConstructorL( CStifItemParser /*aItem*/ )
    {
    TInetAddr mAddress;
    mAddress.SetAddress( INET_ADDR( KIpAddFirstNumber, KIpAddSecondNumber, KZero, KOne ));
    CAknIpFieldSettingPage* IpFieldDlg = new( ELeave ) CAknIpFieldSettingPage( R_IP_ADDRESS_SETTING_PAGE, mAddress );
    CleanupStack::PushL( IpFieldDlg );
    STIF_ASSERT_NOT_NULL( IpFieldDlg );
    CleanupStack::PopAndDestroy( IpFieldDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneIpFieldConstructorLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneIpFieldConstructorLL( CStifItemParser /*aItem*/ )
    {
    TInetAddr mAddress;
    mAddress.SetAddress( INET_ADDR( KIpAddFirstNumber, KIpAddSecondNumber, KZero, KOne ));
    TBuf< KBufSize > buffer( KTestString );
    CAknIpFieldSettingPage* IpFieldDlg = new( ELeave ) CAknIpFieldSettingPage( &buffer, KOne, 
        EAknCtIpFieldEditor, R_IP_CONTROL, R_IP_ADDRESS_SETTING_PAGE, mAddress );
    CleanupStack::PushL( IpFieldDlg );
    STIF_ASSERT_NOT_NULL( IpFieldDlg );
    CleanupStack::PopAndDestroy( IpFieldDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneIpFieldConstructLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneIpFieldConstructLL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress;
    mAddress.SetAddress( INET_ADDR( KIpAddFirstNumber, KIpAddSecondNumber, KZero, KOne ));
    TBuf< KBufSize > buffer( KTestString );
    CAknIpFieldSettingPage* IpFieldDlg = new( ELeave ) CAknIpFieldSettingPage( &buffer, KOne, 
        EAknCtIpFieldEditor, R_IP_CONTROL, R_IP_ADDRESS_SETTING_PAGE, mAddress );
    CleanupStack::PushL( IpFieldDlg );
    IpFieldDlg->ConstructL();
    CleanupStack::PopAndDestroy( IpFieldDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneIpFieldTimeOffsetEditorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneIpFieldTimeOffsetEditorL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress;
    mAddress.SetAddress( INET_ADDR( KIpAddFirstNumber, KIpAddSecondNumber, KZero, KOne ));
    TBuf< KBufSize > buffer( KTestString );
    CAknIpFieldSettingPage* IpFieldDlg = new( ELeave ) CAknIpFieldSettingPage( &buffer, KOne, 
        EAknCtIpFieldEditor, R_IP_CONTROL, R_IP_ADDRESS_SETTING_PAGE, mAddress );
    CleanupStack::PushL( IpFieldDlg );
    IpFieldDlg->ConstructL();
    
    CAknIpFieldEditor* IpControl = IpFieldDlg->IpFieldEditor();
    STIF_ASSERT_NOT_NULL( IpControl );
    
    CleanupStack::PopAndDestroy( IpFieldDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneIpFieldHandlePointerEventLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneIpFieldHandlePointerEventLL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress;
    mAddress.SetAddress( INET_ADDR( KIpAddFirstNumber, KIpAddSecondNumber, KZero, KOne ));
    TBuf< KBufSize > buffer( KTestString );
    CAknIpFieldSettingPage* IpFieldDlg = new( ELeave ) CAknIpFieldSettingPage( &buffer, KOne, 
        EAknCtIpFieldEditor, R_IP_CONTROL, R_IP_ADDRESS_SETTING_PAGE, mAddress );
    CleanupStack::PushL( IpFieldDlg );
    IpFieldDlg->ConstructL();
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    IpFieldDlg->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( IpFieldDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneIpFieldDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneIpFieldDestructorL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress;
    mAddress.SetAddress( INET_ADDR( KIpAddFirstNumber, KIpAddSecondNumber, KZero, KOne ));
    TBuf< KBufSize > buffer( KTestString );
    CTestIpFieldSettingPage* IpFieldDlg = new( ELeave ) CTestIpFieldSettingPage( &buffer, KOne, 
        EAknCtIpFieldEditor, R_IP_CONTROL, R_IP_ADDRESS_SETTING_PAGE, mAddress );
    CleanupStack::PushL( IpFieldDlg );
    CleanupStack::PopAndDestroy( IpFieldDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneIpFieldUpdateSettingLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneIpFieldUpdateSettingLL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress;
    mAddress.SetAddress( INET_ADDR( KIpAddFirstNumber, KIpAddSecondNumber, KZero, KOne ));
    TBuf< KBufSize > buffer( KTestString );
    CTestIpFieldSettingPage* IpFieldDlg = new( ELeave ) CTestIpFieldSettingPage( &buffer, KOne, 
        EAknCtIpFieldEditor, R_IP_CONTROL, R_IP_ADDRESS_SETTING_PAGE, mAddress );
    CleanupStack::PushL( IpFieldDlg );
    IpFieldDlg->ConstructL();
    IpFieldDlg->DoUpdateSettingL();
    CleanupStack::PopAndDestroy( IpFieldDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneIpFieldAcceptSettingLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneIpFieldAcceptSettingLL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress;
    mAddress.SetAddress( INET_ADDR( KIpAddFirstNumber, KIpAddSecondNumber, KZero, KOne ));
    TBuf< KBufSize > buffer( KTestString );
    CTestIpFieldSettingPage* IpFieldDlg = new( ELeave ) CTestIpFieldSettingPage( &buffer, KOne, 
        EAknCtIpFieldEditor, R_IP_CONTROL, R_IP_ADDRESS_SETTING_PAGE, mAddress );
    CleanupStack::PushL( IpFieldDlg );
    IpFieldDlg->ConstructL();
    IpFieldDlg->DoAcceptSettingL();
    CleanupStack::PopAndDestroy( IpFieldDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneIpFieldRestoreOriginalSettingLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneIpFieldRestoreOriginalSettingLL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress;
    mAddress.SetAddress( INET_ADDR( KIpAddFirstNumber, KIpAddSecondNumber, KZero, KOne ));
    TBuf< KBufSize > buffer( KTestString );
    CTestIpFieldSettingPage* IpFieldDlg = new( ELeave ) CTestIpFieldSettingPage( &buffer, KOne, 
        EAknCtIpFieldEditor, R_IP_CONTROL, R_IP_ADDRESS_SETTING_PAGE, mAddress );
    CleanupStack::PushL( IpFieldDlg );
    IpFieldDlg->ConstructL();
    IpFieldDlg->DoRestoreOriginalSettingL();
    CleanupStack::PopAndDestroy( IpFieldDlg );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesMfneIpFieldWriteInternalStateLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesMfneIpFieldWriteInternalStateLL( CStifItemParser& /*aItem*/ )
    {
    TInetAddr mAddress;
    mAddress.SetAddress( INET_ADDR( KIpAddFirstNumber, KIpAddSecondNumber, KZero, KOne ));
    TBuf< KBufSize > buffer( KTestString );
    CTestIpFieldSettingPage* IpFieldDlg = new( ELeave ) CTestIpFieldSettingPage( &buffer, KOne, 
        EAknCtIpFieldEditor, R_IP_CONTROL, R_IP_ADDRESS_SETTING_PAGE, mAddress );
    CleanupStack::PushL( IpFieldDlg );
    IpFieldDlg->ConstructL();
    
    RDesWriteStream stream;
    CleanupClosePushL( stream );
    HBufC8* hbuf = HBufC8::NewL( KHBufSize );
    CleanupStack::PushL( hbuf );
    TPtr8 ptr = hbuf->Des();
    stream.Open( ptr );
    IpFieldDlg->DoWriteInternalStateL( stream );
    stream.CommitL();
    stream.Close();
    
    CleanupStack::PopAndDestroy( KThree );
    return KErrNone;
    }

//End file


