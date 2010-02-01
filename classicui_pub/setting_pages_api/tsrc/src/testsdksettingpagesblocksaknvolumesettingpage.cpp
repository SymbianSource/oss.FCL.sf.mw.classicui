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
* Description:  Test aknvolumesettingpage.h
*
*/

// INCLUDE FILES
#include <aknvolumesettingpage.h>
#include <testsdksettingpages.rsg>

#include "testsdksettingpages.h"
#include "testsdksettingpagesstdinclude.h"
#include "testaknvolumesettingpageprotected.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesVolumeConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesVolumeConstructorL( CStifItemParser& /*aItem*/ )
    {
    TInt volume( KTen );
    CAknVolumeSettingPage* pageDialog = new( ELeave ) CAknVolumeSettingPage( R_VOLUME_SETTING_PAGE, volume );
    CleanupStack::PushL( pageDialog );
    STIF_ASSERT_NOT_NULL( pageDialog );
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesVolumeConstructorLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesVolumeConstructorLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TInt volume( KTen );
    CAknVolumeSettingPage* pageDialog = new( ELeave ) CAknVolumeSettingPage( &buffer, KOne, 
        EAknCtVolumeControl, R_VOLUME_CONTROL, R_VOLUME_SETTING_PAGE, volume );
    CleanupStack::PushL( pageDialog );
    STIF_ASSERT_NOT_NULL( pageDialog );
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesVolumeHandlePointerEventLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesVolumeHandlePointerEventLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TInt volume( KTen );
    CTestVolumeSettingPage* pageDialog = new( ELeave ) CTestVolumeSettingPage( &buffer, KOne, 
        EAknCtVolumeControl, R_VOLUME_CONTROL, R_VOLUME_SETTING_PAGE, volume );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->DoConstructL();
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( KPointX, KPointY );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    pageDialog->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesVolumeDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesVolumeDestructorL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TInt volume( KTen );
    CTestVolumeSettingPage* pageDialog = new( ELeave ) CTestVolumeSettingPage( &buffer, KOne, 
        EAknCtVolumeControl, R_VOLUME_CONTROL, R_VOLUME_SETTING_PAGE, volume );
    CleanupStack::PushL( pageDialog );
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesVolumeConstructLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesVolumeConstructLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TInt volume( KTen );
    CTestVolumeSettingPage* pageDialog = new( ELeave ) CTestVolumeSettingPage( &buffer, KOne, 
        EAknCtVolumeControl, R_VOLUME_CONTROL, R_VOLUME_SETTING_PAGE, volume );
    CleanupStack::PushL( pageDialog );
    pageDialog->DoConstructL();
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesVolumeVolumeControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesVolumeVolumeControlL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TInt volume( KTen );
    CTestVolumeSettingPage* pageDialog = new( ELeave ) CTestVolumeSettingPage( &buffer, KOne, 
        EAknCtVolumeControl, R_VOLUME_CONTROL, R_VOLUME_SETTING_PAGE, volume );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->DoConstructL();
    CAknVolumeControl* control = pageDialog->DoVolumeControl();
    STIF_ASSERT_NOT_NULL( control );
    control = NULL;
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesVolumeSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesVolumeSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TInt volume( KTen );
    CTestVolumeSettingPage* pageDialog = new( ELeave ) CTestVolumeSettingPage( &buffer, KOne, 
        EAknCtVolumeControl, R_VOLUME_CONTROL, R_VOLUME_SETTING_PAGE, volume );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->DoConstructL();
    pageDialog->DoSizeChanged();
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesVolumeDrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesVolumeDrawL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TInt volume( KTen );
    CTestVolumeSettingPage* pageDialog = new( ELeave ) CTestVolumeSettingPage( &buffer, KOne, 
        EAknCtVolumeControl, R_VOLUME_CONTROL, R_VOLUME_SETTING_PAGE, volume );
    CleanupStack::PushL( pageDialog );
    
    pageDialog->DoConstructL();
    pageDialog->DoActivateGc();
    pageDialog->ActivateL();
    TPoint topLeftPoint( KZero, KZero );
    TPoint bottomRightPoint( KTen, KTen );
    TRect rect( topLeftPoint, bottomRightPoint );
    pageDialog->DoDraw( rect );
    pageDialog->DoDeactivateGc();
    
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesVolumeWriteInternalStateLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesVolumeWriteInternalStateLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TInt volume( KTen );
    CTestVolumeSettingPage* pageDialog = new( ELeave ) CTestVolumeSettingPage( &buffer, KOne, 
        EAknCtVolumeControl, R_VOLUME_CONTROL, R_VOLUME_SETTING_PAGE, volume );
    CleanupStack::PushL( pageDialog );
    pageDialog->DoConstructL();
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
// CTestSDKSettingPages::TestSettingPagesVolumeUpdateSettingLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesVolumeUpdateSettingLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TInt volume( KTen );
    CTestVolumeSettingPage* pageDialog = new( ELeave ) CTestVolumeSettingPage( &buffer, KOne, 
        EAknCtVolumeControl, R_VOLUME_CONTROL, R_VOLUME_SETTING_PAGE, volume );
    CleanupStack::PushL( pageDialog );
    pageDialog->DoConstructL();
    pageDialog->DoUpdateSettingL();
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesVolumeAcceptSettingLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesVolumeAcceptSettingLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TInt volume( KTen );
    CTestVolumeSettingPage* pageDialog = new( ELeave ) CTestVolumeSettingPage( &buffer, KOne, 
        EAknCtVolumeControl, R_VOLUME_CONTROL, R_VOLUME_SETTING_PAGE, volume );
    CleanupStack::PushL( pageDialog );
    pageDialog->DoConstructL();
    pageDialog->DoAcceptSettingL();
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingPagesVolumeRestoreOriginalSettingLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingPagesVolumeRestoreOriginalSettingLL( CStifItemParser& /*aItem*/ )
    {
    TBuf< KBufSize > buffer( KTestString );
    TInt volume( KTen );
    CTestVolumeSettingPage* pageDialog = new( ELeave ) CTestVolumeSettingPage( &buffer, KOne, 
        EAknCtVolumeControl, R_VOLUME_CONTROL, R_VOLUME_SETTING_PAGE, volume );
    CleanupStack::PushL( pageDialog );
    pageDialog->DoConstructL();
    pageDialog->DoRestoreOriginalSettingL();
    CleanupStack::PopAndDestroy( pageDialog );
    return KErrNone;
    }

//End file


