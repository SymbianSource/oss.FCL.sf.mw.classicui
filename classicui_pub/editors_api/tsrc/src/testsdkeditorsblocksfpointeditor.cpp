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
* Description:  Test EIKFPNE.h
*
*/



// [INCLUDE FILES]

#include <eikfpne.h>
#include <barsread.h>
#include <coemain.h>
#include <coeaui.h>
#include <akndef.h>
#include <testsdkeditors.rsg>

#include "testsdkeditors.h"
#include "testsdkeditorscontrol.h"

const TReal KMin = 0.0;
const TReal KMax = 100.0;
const TInt KLimit = 5;
const TInt KLength = 10;
const TInt KMinValue = 0;
const TInt KMaxValue = 100;

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKEditors::TestFPECEikFloatingPointEditorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestFPECEikFloatingPointEditorL( CStifItemParser& /*aItem*/ )
    {
    CEikFloatingPointEditor* pointEditor = new (ELeave) CEikFloatingPointEditor;
    CleanupStack::PushL( pointEditor );
    STIF_ASSERT_NOT_NULL( pointEditor );
    
    CleanupStack::PopAndDestroy( pointEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestFPEConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestFPEConstructL( CStifItemParser& /*aItem*/ )
    {
    CEikFloatingPointEditor* pointEditor = new (ELeave) CEikFloatingPointEditor;
    CleanupStack::PushL( pointEditor );
    STIF_ASSERT_NOT_NULL( pointEditor );
    
    pointEditor->ConstructL( KMin, KMax, KLimit );
    
    CleanupStack::PopAndDestroy( pointEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestFPEValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestFPEValueL( CStifItemParser& /*aItem*/ )
    {
    CEikFloatingPointEditor* pointEditor = new (ELeave) CEikFloatingPointEditor;
    CleanupStack::PushL( pointEditor );
    STIF_ASSERT_NOT_NULL( pointEditor );
    
    pointEditor->ConstructL( KMin, KMax, KLimit );
    pointEditor->SetValueL( &KMax );
    STIF_ASSERT_TRUE( KMax == pointEditor->Value() );
    
    CleanupStack::PopAndDestroy( pointEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestFPEGetValueAsRealL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestFPEGetValueAsRealL( CStifItemParser& /*aItem*/ )
    {
    CEikFloatingPointEditor* pointEditor = new (ELeave) CEikFloatingPointEditor;
    CleanupStack::PushL( pointEditor );
    STIF_ASSERT_NOT_NULL( pointEditor );
    
    pointEditor->ConstructL( KMin, KMax, KLimit );
    pointEditor->SetValueL( &KMax );
    
    TReal valueGet;
    pointEditor->GetValueAsReal( valueGet );
    STIF_ASSERT_TRUE( KMax == valueGet );
    
    CleanupStack::PopAndDestroy( pointEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestFPESetValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestFPESetValueL( CStifItemParser& aItem )
    {
    return TestFPEValueL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestFPESetMinMaxL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestFPESetMinMaxL( CStifItemParser& /*aItem*/ )
    {
    CEikFloatingPointEditor* pointEditor = new (ELeave) CEikFloatingPointEditor;
    CleanupStack::PushL( pointEditor );
    STIF_ASSERT_NOT_NULL( pointEditor );
    
    pointEditor->ConstructL( KMin, KMax, KLimit );
    pointEditor->SetMinMax( KMin, KMax );
    
    TReal minGet;
    TReal maxGet;
    pointEditor->GetMinMax( minGet, maxGet );
    STIF_ASSERT_TRUE( KMin == minGet );
    STIF_ASSERT_TRUE( KMax == maxGet );
    
    CleanupStack::PopAndDestroy( pointEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestFPEGetMinMaxL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestFPEGetMinMaxL( CStifItemParser& aItem )
    {
    return TestFPESetMinMaxL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestFPEConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestFPEConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    CEikFloatingPointEditor* pointEditor = new (ELeave) CEikFloatingPointEditor;
    CleanupStack::PushL( pointEditor );
    STIF_ASSERT_NOT_NULL( pointEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_FPEEDITOR );
    pointEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    CleanupStack::PopAndDestroy( pointEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestFPEPrepareForFocusLossL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestFPEPrepareForFocusLossL( CStifItemParser& /*aItem*/ )
    {
    CEikFloatingPointEditor* pointEditor = new (ELeave) CEikFloatingPointEditor;
    CleanupStack::PushL( pointEditor );
    STIF_ASSERT_NOT_NULL( pointEditor );
    
    pointEditor->ConstructL( KMin, KMax, KLimit );
    _LIT( KText, "100" );
    TBuf<KLength> text( KText );
    pointEditor->SetTextL( &text );
    pointEditor->PrepareForFocusLossL();
    
    CleanupStack::PopAndDestroy( pointEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestFPEInputCapabilitiesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestFPEInputCapabilitiesL( CStifItemParser& /*aItem*/ )
    {
    CEikFloatingPointEditor* pointEditor = new (ELeave) CEikFloatingPointEditor;
    CleanupStack::PushL( pointEditor );
    STIF_ASSERT_NOT_NULL( pointEditor );
    
    pointEditor->ConstructL( KMin, KMax, KLimit );
    TCoeInputCapabilities capa = pointEditor->InputCapabilities();
    
    CleanupStack::PopAndDestroy( pointEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestFPEOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestFPEOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {
    CEikFloatingPointEditor* pointEditor = new (ELeave) CEikFloatingPointEditor;
    CleanupStack::PushL( pointEditor );
    STIF_ASSERT_NOT_NULL( pointEditor );
    
    pointEditor->ConstructL( KMin, KMax, KLimit );
    TKeyEvent keyEvent;
    keyEvent.iCode = EKeyCBA1;
    STIF_ASSERT_TRUE( EKeyWasNotConsumed == pointEditor->OfferKeyEventL( keyEvent, EEventKeyDown ) );
    
    CleanupStack::PopAndDestroy( pointEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestFPEHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestFPEHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    CEikFloatingPointEditor* pointEditor = new (ELeave) CEikFloatingPointEditor;
    CleanupStack::PushL( pointEditor );
    STIF_ASSERT_NOT_NULL( pointEditor );
    
    pointEditor->ConstructL( KMin, KMax, KLimit );

    pointEditor->HandleResourceChange( KEikInputLanguageChange );
    
    CleanupStack::PopAndDestroy( pointEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestFPEHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestFPEHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikFloatingPointEditor* pointEditor = new (ELeave) CEikFloatingPointEditor;
    CleanupStack::PushL( pointEditor );
    STIF_ASSERT_NOT_NULL( pointEditor );
    
    pointEditor->ConstructL( KMin, KMax, KLimit );
    pointEditor->SetContainerWindowL( *control );
    pointEditor->CreateTextViewL();

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Up;
    pointEditor->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( pointEditor );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestXPECEikFixedPointEditorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestXPECEikFixedPointEditorL( CStifItemParser& /*aItem*/ )
    {
    CEikFixedPointEditor* pointEditor = new (ELeave) CEikFixedPointEditor;
    CleanupStack::PushL( pointEditor );
    STIF_ASSERT_NOT_NULL( pointEditor );
    
    CleanupStack::PopAndDestroy( pointEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestXPEConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestXPEConstructL( CStifItemParser& /*aItem*/ )
    {
    CEikFixedPointEditor* pointEditor = new (ELeave) CEikFixedPointEditor;
    CleanupStack::PushL( pointEditor );
    STIF_ASSERT_NOT_NULL( pointEditor );
    
    pointEditor->ConstructL( KMinValue, KMaxValue );
    
    CleanupStack::PopAndDestroy( pointEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestXPEValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestXPEValueL( CStifItemParser& /*aItem*/ )
    {
    CEikFixedPointEditor* pointEditor = new (ELeave) CEikFixedPointEditor;
    CleanupStack::PushL( pointEditor );
    STIF_ASSERT_NOT_NULL( pointEditor );
    
    pointEditor->ConstructL( KMinValue, KMaxValue );
    pointEditor->SetValueL( &KMaxValue );
    STIF_ASSERT_TRUE( KMaxValue == pointEditor->Value() );
    
    CleanupStack::PopAndDestroy( pointEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestXPEGetValueAsIntegerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestXPEGetValueAsIntegerL( CStifItemParser& /*aItem*/ )
    {
    CEikFixedPointEditor* pointEditor = new (ELeave) CEikFixedPointEditor;
    CleanupStack::PushL( pointEditor );
    STIF_ASSERT_NOT_NULL( pointEditor );
    
    pointEditor->ConstructL( KMinValue, KMaxValue );
    pointEditor->SetValueL( &KMaxValue );
    TInt valueGet;
    
    STIF_ASSERT_TRUE( CAknNumericEdwin::EValueValid == pointEditor->GetValueAsInteger( valueGet ) );
    STIF_ASSERT_TRUE( valueGet == KMaxValue );
    
    CleanupStack::PopAndDestroy( pointEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestXPESetValueL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestXPESetValueL( CStifItemParser& aItem )
    {
    return TestXPEValueL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestXPESetMinMaxrL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestXPESetMinMaxrL( CStifItemParser& /*aItem*/ )
    {
    CEikFixedPointEditor* pointEditor = new (ELeave) CEikFixedPointEditor;
    CleanupStack::PushL( pointEditor );
    STIF_ASSERT_NOT_NULL( pointEditor );
    
    pointEditor->ConstructL( KMinValue, KMaxValue );
    pointEditor->SetMinMax( KMinValue, KMaxValue );
    TInt minGet;
    TInt maxGet;
    pointEditor->GetMinMax( minGet, maxGet );
    
    STIF_ASSERT_TRUE( minGet == KMinValue );
    STIF_ASSERT_TRUE( maxGet == KMaxValue );
    
    CleanupStack::PopAndDestroy( pointEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestXPEGetMinMaxL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestXPEGetMinMaxL( CStifItemParser& aItem )
    {
    return TestXPESetMinMaxrL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestXPESetDecimalPlacesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestXPESetDecimalPlacesL( CStifItemParser& /*aItem*/ )
    {
    CEikFixedPointEditor* pointEditor = new (ELeave) CEikFixedPointEditor;
    CleanupStack::PushL( pointEditor );
    STIF_ASSERT_NOT_NULL( pointEditor );
    
    pointEditor->ConstructL( KMinValue, KMaxValue );
    const TInt KDecimalPlace = 3;
    pointEditor->SetDecimalPlaces( KDecimalPlace );
    STIF_ASSERT_TRUE( KDecimalPlace == pointEditor->DecimalPlaces() );
    
    CleanupStack::PopAndDestroy( pointEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestXPEDecimalPlacesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestXPEDecimalPlacesL( CStifItemParser& aItem )
    {
    return TestXPESetDecimalPlacesL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestXPEConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestXPEConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    CEikFixedPointEditor* pointEditor = new (ELeave) CEikFixedPointEditor;
    CleanupStack::PushL( pointEditor );
    STIF_ASSERT_NOT_NULL( pointEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_XPEEDITOR );
    pointEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    CleanupStack::PopAndDestroy( pointEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestXPEPrepareForFocusLossL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestXPEPrepareForFocusLossL( CStifItemParser& /*aItem*/ )
    {
    CEikFixedPointEditor* pointEditor = new (ELeave) CEikFixedPointEditor;
    CleanupStack::PushL( pointEditor );
    STIF_ASSERT_NOT_NULL( pointEditor );
    
    pointEditor->ConstructL( KMinValue, KMaxValue );
    
    _LIT( KText, "100" );
    TBuf<KLength> text( KText );
    pointEditor->SetTextL( &text );
    pointEditor->PrepareForFocusLossL();
    
    CleanupStack::PopAndDestroy( pointEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestXPEInputCapabilitiesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestXPEInputCapabilitiesL( CStifItemParser& /*aItem*/ )
    {
    CEikFixedPointEditor* pointEditor = new (ELeave) CEikFixedPointEditor;
    CleanupStack::PushL( pointEditor );
    STIF_ASSERT_NOT_NULL( pointEditor );
    
    pointEditor->ConstructL( KMinValue, KMaxValue );
    
    TCoeInputCapabilities capa = pointEditor->InputCapabilities();
    
    CleanupStack::PopAndDestroy( pointEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestXPEOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestXPEOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {
    CEikFixedPointEditor* pointEditor = new (ELeave) CEikFixedPointEditor;
    CleanupStack::PushL( pointEditor );
    STIF_ASSERT_NOT_NULL( pointEditor );
    
    pointEditor->ConstructL( KMinValue, KMaxValue );
    TKeyEvent keyEvent;
    keyEvent.iCode = EKeyCBA1;
    STIF_ASSERT_TRUE( EKeyWasNotConsumed == pointEditor->OfferKeyEventL( keyEvent, EEventKeyDown ) );
    
    CleanupStack::PopAndDestroy( pointEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestXPEHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestXPEHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    CEikFixedPointEditor* pointEditor = new (ELeave) CEikFixedPointEditor;
    CleanupStack::PushL( pointEditor );
    STIF_ASSERT_NOT_NULL( pointEditor );
    
    pointEditor->ConstructL( KMinValue, KMaxValue );

    _LIT( KText, "100" );
    TBuf<KLength> text( KText );
    pointEditor->SetTextL( &text );
    
    pointEditor->HandleResourceChange( KEikInputLanguageChange );
    
    CleanupStack::PopAndDestroy( pointEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestXPEHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestXPEHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikFixedPointEditor* pointEditor = new (ELeave) CEikFixedPointEditor;
    CleanupStack::PushL( pointEditor );
    STIF_ASSERT_NOT_NULL( pointEditor );
    
    pointEditor->ConstructL( KMinValue, KMaxValue );
    pointEditor->SetContainerWindowL( *control );
    pointEditor->CreateTextViewL();
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    pointEditor->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( pointEditor );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }
