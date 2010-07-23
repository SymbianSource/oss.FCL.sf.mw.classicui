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
* Description:  Test aknradiobuttonsettingpage.h
*
*/



// INCLUDE FILES
#include <aknradiobuttonsettingpage.h>
#include <testsdksettingpages.rsg>
#include <bautils.h>

#include "testaknradiobuttonsettingpageprotected.h"
#include "testsdksettingpagesstdinclude.h"
#include "testsdksettingpagesstdinclude.h"
#include "testsdksettingpages.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesRadioButtonConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesRadioButtonConstructorL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* mArr = new( ELeave ) CDesCArrayFlat( KSize );
    CleanupStack::PushL( mArr );

    TBuf<KBufSize> tom( KTom );
    TBuf<KBufSize> jack( KJack );
    TBuf<KBufSize> mary( KMary );
    mArr->AppendL( tom );
    mArr->AppendL( jack );
    mArr->AppendL( mary );
    
    TInt optin( KZero );
    CAknRadioButtonSettingPage* dialog =
        new (ELeave) CAknRadioButtonSettingPage( R_EXAMPLE_SETTING_PAGE,
        optin, mArr );
    CleanupStack::PushL( dialog );
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesRadioButtonConstructorLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesRadioButtonConstructorLL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* mArr = new( ELeave ) CDesCArrayFlat( KSize );
    CleanupStack::PushL( mArr );

    TBuf<KBufSize> tom( KTom );
    TBuf<KBufSize> jack( KJack );
    TBuf<KBufSize> mary( KMary );
    mArr->AppendL( tom );
    mArr->AppendL( jack );
    mArr->AppendL( mary );
    
    TInt optin( KZero );
    TBuf< KBufSize > buffer( KTestString );
    CAknRadioButtonSettingPage* dialog =
    new (ELeave) CAknRadioButtonSettingPage( &buffer, KOne, EAknCtPopupSettingList,
        R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE, optin, mArr );
    CleanupStack::PushL( dialog );
    STIF_ASSERT_NOT_NULL( dialog );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesRadioButtonConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesRadioButtonConstructL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* mArr = new( ELeave ) CDesCArrayFlat( KSize );
    CleanupStack::PushL( mArr );

    TBuf<KBufSize> tom( KTom );
    TBuf<KBufSize> jack( KJack );
    TBuf<KBufSize> mary( KMary );
    mArr->AppendL( tom );
    mArr->AppendL( jack );
    mArr->AppendL( mary );
    
    TInt optin( KZero );
    CAknRadioButtonSettingPage* dialog =
    new (ELeave) CAknRadioButtonSettingPage( R_EXAMPLE_SETTING_PAGE,
            optin, mArr );
    CleanupStack::PushL( dialog );
    dialog->ConstructL();
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesRadioButtonListBoxControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesRadioButtonListBoxControlL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* mArr = new( ELeave ) CDesCArrayFlat( KSize );
    CleanupStack::PushL( mArr );

    TBuf<KBufSize> tom( KTom );
    TBuf<KBufSize> jack( KJack );
    TBuf<KBufSize> mary( KMary );
    mArr->AppendL( tom );
    mArr->AppendL( jack );
    mArr->AppendL( mary );
    
    TInt optin( KZero );
    CAknRadioButtonSettingPage* dialog =
    new (ELeave) CAknRadioButtonSettingPage( R_EXAMPLE_SETTING_PAGE,
        optin, mArr );
    CleanupStack::PushL( dialog );
    
    CAknSetStyleListBox* editorControl = dialog->ListBoxControl();
    STIF_ASSERT_NULL( editorControl );
    
    dialog->ConstructL();
    
    editorControl = dialog->ListBoxControl();
    STIF_ASSERT_NOT_NULL( editorControl );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesRadioButtonHandleListBoxEventLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesRadioButtonHandleListBoxEventLL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* mArr = new( ELeave ) CDesCArrayFlat( KSize );
    CleanupStack::PushL( mArr );

    TBuf<KBufSize> tom( KTom );
    TBuf<KBufSize> jack( KJack );
    TBuf<KBufSize> mary( KMary );
    mArr->AppendL( tom );
    mArr->AppendL( jack );
    mArr->AppendL( mary );
    
    TInt optin( KZero );
    TBuf< KBufSize > buffer( KTestString );
    CAknRadioButtonSettingPage* dialog =
    new (ELeave) CAknRadioButtonSettingPage( &buffer, KOne, EAknCtPopupSettingList,
        R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE, optin, mArr );
    CleanupStack::PushL( dialog );
    
    dialog->ConstructL();
    dialog->HandleListBoxEventL( dialog->ListBoxControl(), MEikListBoxObserver::EEventItemActioned );
    dialog->HandleListBoxEventL( dialog->ListBoxControl(), MEikListBoxObserver::EEventItemClicked );
    dialog->HandleListBoxEventL( dialog->ListBoxControl(), MEikListBoxObserver::EEventPenDownOnItem );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesRadioButtonSetItemArrayAndSelectionLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesRadioButtonSetItemArrayAndSelectionLL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* mArray = new( ELeave ) CDesCArrayFlat( KSize );
    CleanupStack::PushL( mArray );
    
    TBuf<KBufSize> tom( KTom );
    TBuf<KBufSize> jack( KJack );
    TBuf<KBufSize> mary( KMary );
    mArray->AppendL( tom );
    mArray->AppendL( jack );
    mArray->AppendL( mary );
    TInt optin( KZero );
    TBuf< KBufSize > buffer( KTestString );
    CAknRadioButtonSettingPage* dialog =
    new (ELeave) CAknRadioButtonSettingPage( &buffer, KOne, EAknCtPopupSettingList,
        R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE, optin, mArray );
    CleanupStack::PushL( dialog );
    
    dialog->ConstructL();
    CDesCArrayFlat* mArr = new( ELeave ) CDesCArrayFlat( KSize );
    CleanupStack::PushL( mArr );

    mArr->AppendL( tom );
    mArr->AppendL( jack );
    mArr->AppendL( mary );
    
    dialog->SetItemArrayAndSelectionL( mArr, KOne );
    
    CleanupStack::PopAndDestroy( KThree );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesRadioButtonHandlePointerEventLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesRadioButtonHandlePointerEventLL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* mArr = new( ELeave ) CDesCArrayFlat( KSize );
    CleanupStack::PushL( mArr );

    TBuf<KBufSize> tom( KTom );
    TBuf<KBufSize> jack( KJack );
    TBuf<KBufSize> mary( KMary );
    mArr->AppendL( tom );
    mArr->AppendL( jack );
    mArr->AppendL( mary );
    
    TInt optin( KZero );
    TBuf< KBufSize > buffer( KTestString );
    CAknRadioButtonSettingPage* dialog =
    new (ELeave) CAknRadioButtonSettingPage( &buffer, KOne, EAknCtPopupSettingList,
        R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE, optin, mArr );
    CleanupStack::PushL( dialog );
    
    dialog->ConstructL();
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    dialog->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesRadioButtonHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesRadioButtonHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* mArr = new( ELeave ) CDesCArrayFlat( KSize );
    CleanupStack::PushL( mArr );

    TBuf<KBufSize> tom( KTom );
    TBuf<KBufSize> jack( KJack );
    TBuf<KBufSize> mary( KMary );
    mArr->AppendL( tom );
    mArr->AppendL( jack );
    mArr->AppendL( mary );
    
    TInt optin( KZero );
    TBuf< KBufSize > buffer( KTestString );
    CAknRadioButtonSettingPage* dialog =
    new (ELeave) CAknRadioButtonSettingPage( &buffer, KOne, EAknCtPopupSettingList,
        R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE, optin, mArr );
    CleanupStack::PushL( dialog );
    
    dialog->ConstructL();
    dialog->HandleResourceChange( KAknsMessageSkinChange );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesRadioButtonDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesRadioButtonDestructorL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* mArr = new( ELeave ) CDesCArrayFlat( KSize );
    CleanupStack::PushL( mArr );
    TBuf<KBufSize> tom( KTom );
    TBuf<KBufSize> jack( KJack );
    TBuf<KBufSize> mary( KMary );
    mArr->AppendL( tom );
    mArr->AppendL( jack );
    mArr->AppendL( mary );
    
    TInt optin( KZero );
    CAknRadioButtonSettingPage* dialog =
    new (ELeave) CAknRadioButtonSettingPage( R_EXAMPLE_SETTING_PAGE,
            optin, mArr );
    CleanupStack::PushL( dialog );
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesRadioButtonUpdateSettingLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesRadioButtonUpdateSettingLL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* mArr = new( ELeave ) CDesCArrayFlat( KSize );
    CleanupStack::PushL( mArr );
    TBuf<KBufSize> tom( KTom );
    TBuf<KBufSize> jack( KJack );
    TBuf<KBufSize> mary( KMary );
    mArr->AppendL( tom );
    mArr->AppendL( jack );
    mArr->AppendL( mary );
    
    TInt optin( KZero );
    TBuf< KBufSize > buffer( KTestString );
    CTestRadioButtonSettingPage* dialog =
    new (ELeave) CTestRadioButtonSettingPage( &buffer, KOne, EAknCtPopupSettingList,
        R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE, optin, mArr );
    CleanupStack::PushL( dialog );
    
    dialog->ConstructL();
    dialog->DoUpdateSettingL();
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesRadioButtonDynamicInitLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesRadioButtonDynamicInitLL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* mArr = new( ELeave ) CDesCArrayFlat( KSize );
    CleanupStack::PushL( mArr );

    TBuf<KBufSize> tom( KTom );
    TBuf<KBufSize> jack( KJack );
    TBuf<KBufSize> mary( KMary );
    mArr->AppendL( tom );
    mArr->AppendL( jack );
    mArr->AppendL( mary );
    
    TInt optin( KZero );
    TBuf< KBufSize > buffer( KTestString );
    CTestRadioButtonSettingPage* dialog =
    new (ELeave) CTestRadioButtonSettingPage( &buffer, KOne, EAknCtPopupSettingList,
        R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE, optin, mArr );
    CleanupStack::PushL( dialog );
    
    dialog->ConstructL();
    dialog->DoDynamicInitL();
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesRadioButtonSelectCurrentItemLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesRadioButtonSelectCurrentItemLL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* mArr = new( ELeave ) CDesCArrayFlat( KSize );
    CleanupStack::PushL( mArr );

    TBuf<KBufSize> tom( KTom );
    TBuf<KBufSize> jack( KJack );
    TBuf<KBufSize> mary( KMary );
    mArr->AppendL( tom );
    mArr->AppendL( jack );
    mArr->AppendL( mary );
    
    TInt optin( KZero );
    TBuf< KBufSize > buffer( KTestString );
    CTestRadioButtonSettingPage* dialog =
    new (ELeave) CTestRadioButtonSettingPage( &buffer, KOne, EAknCtPopupSettingList,
        R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE, optin, mArr );
    CleanupStack::PushL( dialog );
    
    dialog->ConstructL();
    dialog->DoSelectCurrentItemL();
    
    CleanupStack::PopAndDestroy( KTwo );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKSettingPages::TestSettingpagesRadioButtonWriteInternalStateLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKSettingPages::TestSettingpagesRadioButtonWriteInternalStateLL( CStifItemParser& /*aItem*/ )
    {
    CDesCArrayFlat* mArr = new( ELeave ) CDesCArrayFlat( KSize );
    CleanupStack::PushL( mArr );

    TBuf<KBufSize> tom( KTom );
    TBuf<KBufSize> jack( KJack );
    TBuf<KBufSize> mary( KMary );
    mArr->AppendL( tom );
    mArr->AppendL( jack );
    mArr->AppendL( mary );
    TInt optin( KZero );
    TBuf< KBufSize > buffer( KTestString );
    CTestRadioButtonSettingPage* dialog =
    new (ELeave) CTestRadioButtonSettingPage( &buffer, KOne, EAknCtPopupSettingList,
        R_EXAMPLE_EDITOR_CONTROL, R_EXAMPLE_SETTING_PAGE, optin, mArr );
    CleanupStack::PushL( dialog );
    dialog->ConstructL();
    
    RDesWriteStream stream;
    CleanupClosePushL( stream );
    HBufC8* hbuf = HBufC8::NewL( KHBufSize );
    CleanupStack::PushL( hbuf );
    TPtr8 ptr = hbuf->Des();
    stream.Open( ptr );
    dialog->DoWriteInternalStateL( stream );
    stream.CommitL();
    stream.Close();  
    CleanupStack::PopAndDestroy( KFour );
    return KErrNone;
    }

//End file


