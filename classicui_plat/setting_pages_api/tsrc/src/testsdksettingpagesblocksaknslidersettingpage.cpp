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
* Description:  Test aknslidersettingpage.h
*
*/



// INCLUDE FILES
#include <aknslidersettingpage.h>
#include <testsdksettingpages.rsg>
#include "testsdksettingpagesstdinclude.h"
#include "testsdksettingpages.h"
#include "testaknslidersettingpageprotected.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSliderConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSliderConstructorL( CStifItemParser& /*aItem*/ )
    {
    TInt number( KZero );
    CAknSliderSettingPage* pageDialog = new( ELeave ) CAknSliderSettingPage( R_SLIDER_SETTING_PAGE, number );
    CleanupStack::PushL( pageDialog );
    STIF_ASSERT_NOT_NULL( pageDialog );
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSliderConstructorLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSliderConstructorLL( CStifItemParser& /*aItem*/ )
    {
    TInt number( KZero );
    TBuf< KBufSize > buffer( KTestString );
    CAknSliderSettingPage* pageDialog = new( ELeave ) CAknSliderSettingPage( &buffer, KOne, 
        EAknCtSlider, R_SLIDER_CONTROL, R_SLIDER_SETTING_PAGE, number );
    CleanupStack::PushL( pageDialog );
    STIF_ASSERT_NOT_NULL( pageDialog );
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSliderSliderControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSliderSliderControlL( CStifItemParser& /*aItem*/ )
    {
    TInt number( KZero );
    TBuf< KBufSize > buffer( KTestString );
    CAknSliderSettingPage* pageDialog = new( ELeave ) CAknSliderSettingPage( &buffer, KOne, 
        EAknCtSlider, R_SLIDER_CONTROL, R_SLIDER_SETTING_PAGE, number );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    CAknSlider* sliderControl = pageDialog->SliderControl();
    STIF_ASSERT_NOT_NULL( sliderControl );
    sliderControl = NULL;
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSliderConstructLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSliderConstructLL( CStifItemParser& /*aItem*/ )
    {
    TInt number( KZero );
    TBuf< KBufSize > buffer( KTestString );
    CAknSliderSettingPage* pageDialog = new( ELeave ) CAknSliderSettingPage( &buffer, KOne, 
        EAknCtSlider, R_SLIDER_CONTROL, R_SLIDER_SETTING_PAGE, number );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSliderHandlePointerEventLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSliderHandlePointerEventLL( CStifItemParser& /*aItem*/ )
    {
    TInt number( KZero );
    TBuf< KBufSize > buffer( KTestString );
    CAknSliderSettingPage* pageDialog = new( ELeave ) CAknSliderSettingPage( &buffer, KOne, 
        EAknCtSlider, R_SLIDER_CONTROL, R_SLIDER_SETTING_PAGE, number );
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
// CTestSDKSettingPages::TestSettingPagesSliderSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSliderSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    TInt number( KZero );
    TBuf< KBufSize > buffer( KTestString );
    CTestSliderSettingPage* pageDialog = new( ELeave ) CTestSliderSettingPage( &buffer, KOne, 
        EAknCtSlider, R_SLIDER_CONTROL, R_SLIDER_SETTING_PAGE, number );
    CleanupStack::PushL( pageDialog );
    pageDialog->ConstructL();
    pageDialog->DoSizeChanged();
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSliderDrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSliderDrawL( CStifItemParser& /*aItem*/ )
    {
    TInt number( KZero );
    TBuf< KBufSize > buffer( KTestString );
    CTestSliderSettingPage* pageDialog = new( ELeave ) CTestSliderSettingPage( &buffer, KOne, 
        EAknCtSlider, R_SLIDER_CONTROL, R_SLIDER_SETTING_PAGE, number );
    CleanupStack::PushL( pageDialog );
    pageDialog->ConstructL();
    pageDialog->DoActivateGc();
    TPoint topLeftPoint( KZero, KZero );
    TPoint bottomRightPoint( KTen, KTen );
    TRect rect( topLeftPoint, bottomRightPoint );
    pageDialog->DoDraw( rect );
    pageDialog->DoDeactivateGc();
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSliderWriteInternalStateLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSliderWriteInternalStateLL( CStifItemParser& /*aItem*/ )
    {
    TInt number( KZero );
    TBuf< KBufSize > buffer( KTestString );
    CTestSliderSettingPage* pageDialog = new( ELeave ) CTestSliderSettingPage( &buffer, KOne, 
        EAknCtSlider, R_SLIDER_CONTROL, R_SLIDER_SETTING_PAGE, number );
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
// CTestSDKSettingPages::TestSettingPagesSliderDestructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSliderDestructL( CStifItemParser& /*aItem*/ )
    {
    TInt number( KZero );
    CAknSliderSettingPage* pageDialog = new( ELeave ) CAknSliderSettingPage( R_SLIDER_SETTING_PAGE, number );
    CleanupStack::PushL( pageDialog );
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSliderUpdateSettingLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSliderUpdateSettingLL( CStifItemParser& /*aItem*/ )
    {
    TInt number( KZero );
    TBuf< KBufSize > buffer( KTestString );
    CTestSliderSettingPage* pageDialog = new( ELeave ) CTestSliderSettingPage( &buffer, KOne, 
        EAknCtSlider, R_SLIDER_CONTROL, R_SLIDER_SETTING_PAGE, number );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    pageDialog->DoUpdateSettingL();
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSliderAcceptSettingLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSliderAcceptSettingLL( CStifItemParser& /*aItem*/ )
    {
    TInt number( KZero );
    TBuf< KBufSize > buffer( KTestString );
    CTestSliderSettingPage* pageDialog = new( ELeave ) CTestSliderSettingPage( &buffer, KOne, 
        EAknCtSlider, R_SLIDER_CONTROL, R_SLIDER_SETTING_PAGE, number );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    pageDialog->DoAcceptSettingL();
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesSliderRestoreOriginalSettingLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesSliderRestoreOriginalSettingLL( CStifItemParser& /*aItem*/ )
    {
    TInt number( KZero );
    TBuf< KBufSize > buffer( KTestString );
    CTestSliderSettingPage* pageDialog = new( ELeave ) CTestSliderSettingPage( &buffer, KOne, 
        EAknCtSlider, R_SLIDER_CONTROL, R_SLIDER_SETTING_PAGE, number );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->ConstructL();
    pageDialog->DoRestoreOriginalSettingL();
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

//Endfile


