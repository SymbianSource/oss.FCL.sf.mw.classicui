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
* Description:  Test AknNumEdwin.h
*
*/



// [INCLUDE FILES]

#include <aknnumedwin.h>
#include <barsread.h>
#include <coemain.h>
#include <coeaui.h>
#include <aknsconstants.h>
#include <akndef.h>
#include <testsdkeditors.rsg>

#include "testsdkeditors.h"
#include "testsdkeditorscontrol.h"

const TInt KMaxInteger = 100;
const TInt KMaxChar = 5;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestIENewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestIENewL( CStifItemParser& /*aItem*/ )
    {
    CAknIntegerEdwin* integerEdwin = CAknIntegerEdwin::NewL( 0, KMaxInteger, KMaxChar );
    CleanupStack::PushL( integerEdwin );
    STIF_ASSERT_NOT_NULL( integerEdwin );
    
    CleanupStack::PopAndDestroy( integerEdwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestIEConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestIEConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    CAknIntegerEdwin* integerEdwin = CAknIntegerEdwin::NewL( 0, KMaxInteger, KMaxChar );
    CleanupStack::PushL( integerEdwin );
    STIF_ASSERT_NOT_NULL( integerEdwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_IEEDITOR );
    integerEdwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    CleanupStack::PopAndDestroy( integerEdwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestIEConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestIEConstructL( CStifItemParser& /*aItem*/ )
    {
    CAknIntegerEdwin* integerEdwin = CAknIntegerEdwin::NewL( 0, KMaxInteger, KMaxChar );
    CleanupStack::PushL( integerEdwin );
    STIF_ASSERT_NOT_NULL( integerEdwin );
    
    integerEdwin->ConstructL( 0, KMaxInteger, KMaxChar );
    
    CleanupStack::PopAndDestroy( integerEdwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestIESetValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestIESetValueL( CStifItemParser& /*aItem*/ )
    {
    CAknIntegerEdwin* integerEdwin = CAknIntegerEdwin::NewL( 0, KMaxInteger, KMaxChar );
    CleanupStack::PushL( integerEdwin );
    STIF_ASSERT_NOT_NULL( integerEdwin );
    
    integerEdwin->SetValueL( KMaxInteger );
    
    CleanupStack::PopAndDestroy( integerEdwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestIESetUnsetValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestIESetUnsetValueL( CStifItemParser& /*aItem*/ )
    {
    CAknIntegerEdwin* integerEdwin = CAknIntegerEdwin::NewL( 0, KMaxInteger, KMaxChar );
    CleanupStack::PushL( integerEdwin );
    STIF_ASSERT_NOT_NULL( integerEdwin );
    
    integerEdwin->SetUnsetValue( 0 );
    
    CleanupStack::PopAndDestroy( integerEdwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestIEGetTextAsIntegerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestIEGetTextAsIntegerL( CStifItemParser& /*aItem*/ )
    {
    CAknIntegerEdwin* integerEdwin = CAknIntegerEdwin::NewL( 0, KMaxInteger, KMaxChar );
    CleanupStack::PushL( integerEdwin );
    STIF_ASSERT_NOT_NULL( integerEdwin );
    
    integerEdwin->SetValueL( KMaxInteger );
    TInt valueGet;
    STIF_ASSERT_TRUE( CAknNumericEdwin ::EValueValid == integerEdwin->GetTextAsInteger( valueGet ) );
    STIF_ASSERT_TRUE( valueGet == KMaxInteger );
    
    CleanupStack::PopAndDestroy( integerEdwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestIESetMinimumIntegerValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestIESetMinimumIntegerValueL( CStifItemParser& /*aItem*/ )
    {
    CAknIntegerEdwin* integerEdwin = CAknIntegerEdwin::NewL( 0, KMaxInteger, KMaxChar );
    CleanupStack::PushL( integerEdwin );
    STIF_ASSERT_NOT_NULL( integerEdwin );
    
    integerEdwin->SetMinimumIntegerValue( 0 );
    
    CleanupStack::PopAndDestroy( integerEdwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestIESetMaximumIntegerValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestIESetMaximumIntegerValueL( CStifItemParser& /*aItem*/ )
    {
    CAknIntegerEdwin* integerEdwin = CAknIntegerEdwin::NewL( 0, KMaxInteger, KMaxChar );
    CleanupStack::PushL( integerEdwin );
    STIF_ASSERT_NOT_NULL( integerEdwin );
    
    integerEdwin->SetMaximumIntegerValue( KMaxInteger );
    
    CleanupStack::PopAndDestroy( integerEdwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestIEPrepareForFocusLossL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestIEPrepareForFocusLossL( CStifItemParser& /*aItem*/ )
    {
    CAknIntegerEdwin* integerEdwin = CAknIntegerEdwin::NewL( 0, KMaxInteger, KMaxChar );
    CleanupStack::PushL( integerEdwin );
    STIF_ASSERT_NOT_NULL( integerEdwin );
    
    integerEdwin->PrepareForFocusLossL();
    
    CleanupStack::PopAndDestroy( integerEdwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestIEHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestIEHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    CAknIntegerEdwin* integerEdwin = CAknIntegerEdwin::NewL( 0, KMaxInteger, KMaxChar );
    CleanupStack::PushL( integerEdwin );
    STIF_ASSERT_NOT_NULL( integerEdwin );
    
    integerEdwin->HandleResourceChange( KEikInputLanguageChange );
    
    CleanupStack::PopAndDestroy( integerEdwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestIEOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestIEOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {
    CAknIntegerEdwin* integerEdwin = CAknIntegerEdwin::NewL( 0, KMaxInteger, KMaxChar );
    CleanupStack::PushL( integerEdwin );
    STIF_ASSERT_NOT_NULL( integerEdwin );
    
    TKeyEvent keyEvent;
    keyEvent.iCode = EKeyCBA1;
    STIF_ASSERT_TRUE( EKeyWasNotConsumed == integerEdwin->OfferKeyEventL( keyEvent, EEventKeyDown ) );
    
    CleanupStack::PopAndDestroy( integerEdwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestIEHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestIEHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CAknIntegerEdwin* integerEdwin = CAknIntegerEdwin::NewL( 0, KMaxInteger, KMaxChar );
    CleanupStack::PushL( integerEdwin );
    STIF_ASSERT_NOT_NULL( integerEdwin );
    
    integerEdwin->ConstructL( 0, KMaxInteger, KMaxChar );
    integerEdwin->SetContainerWindowL( *control );
    integerEdwin->CreateTextViewL();
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    integerEdwin->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( integerEdwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestIECheckNumberL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestIECheckNumberL( CStifItemParser& /*aItem*/ )
    {
    CAknIntegerEdwin* integerEdwin = CAknIntegerEdwin::NewL( 0, KMaxInteger, KMaxChar );
    CleanupStack::PushL( integerEdwin );
    STIF_ASSERT_NOT_NULL( integerEdwin );
    
    integerEdwin->SetValueL( KMaxInteger );
    STIF_ASSERT_TRUE( integerEdwin->CheckNumber() );
    
    CleanupStack::PopAndDestroy( integerEdwin );
    
    return KErrNone;
    
    }
