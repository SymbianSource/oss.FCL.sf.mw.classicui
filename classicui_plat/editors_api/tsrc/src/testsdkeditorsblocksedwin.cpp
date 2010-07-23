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
* Description:  Test EIKEDWIN.H
*
*/



// [INCLUDE FILES]

#include <eikedwin.h>
#include <txtrich.h>
#include <aknquerycontrol.h>
#include <barsread.h>
#include <coemain.h>
#include <coeaui.h>
#include <touchfeedback.h>
#include <s32mem.h>
#include <s32file.h>
#include <f32file.h>
#include <gdi.h>
#include <s32file.h>
#include <aknsbasicbackgroundcontrolcontext.h>
#include <aknscontrolcontext.h>
#include <eikrted.h>
#include <aknextendedinputcapabilities.h>
#include <baclipb.h>

#include <testsdkeditors.rsg>

#include "testsdkeditors.h"
#include "testsdkeditorsedwin.h"
#include "testsdkeditorscontrol.h"
#include "testsdkirfactory.h"
#include "testsdkeditorsdialogfactory.h"
#include "testedwindialog.h"

const TInt KLength = 50;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEFAFormAccessorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEFAFormAccessorL( CStifItemParser& /*aItem*/ )
    {
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    CleanupStack::PopAndDestroy( edwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEFASetFormAccessorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEFASetFormAccessorL( CStifItemParser& /*aItem*/ )
    {
    //class CEikEdwinExtension is private
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEFASetScrollBarSetterL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEFASetScrollBarSetterL( CStifItemParser& /*aItem*/ )
    {
    //class CEikEdwinExtension is private
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEFAScrollBarSetterL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEFAScrollBarSetterL( CStifItemParser& /*aItem*/ )
    {
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    edwin->UpdateScrollBarsL();
    
    CleanupStack::PopAndDestroy( edwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEFATextWrapperL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEFATextWrapperL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKEditorsEdwin* edwin = new (ELeave) CTestSDKEditorsEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    edwin->ConstructL( CEikEdwin::EAvkonEditor );
    
    CParaFormatLayer* paraFormatLayer = CParaFormatLayer::NewL();
    CleanupStack::PushL( paraFormatLayer );
    CCharFormatLayer* charFormatLayer = CCharFormatLayer::NewL();
    CleanupStack::PushL( charFormatLayer );
    CRichText * richText = CRichText::NewL( paraFormatLayer, charFormatLayer );
    CleanupStack::PushL( richText );
    
    edwin->CreateLayoutL( richText );
    
    CleanupStack::Pop( richText );
    CleanupStack::Pop( charFormatLayer );
    CleanupStack::Pop( paraFormatLayer );
    
    CleanupStack::PopAndDestroy( edwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEFAFormCursorModifierL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEFAFormCursorModifierL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKEditorsEdwin* edwin = new (ELeave) CTestSDKEditorsEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    edwin->ConstructL( CEikEdwin::EAvkonEditor );
    
    CParaFormatLayer* paraFormatLayer = CParaFormatLayer::NewL();
    CleanupStack::PushL( paraFormatLayer );
    CCharFormatLayer* charFormatLayer = CCharFormatLayer::NewL();
    CleanupStack::PushL( charFormatLayer );
    CRichText * richText = CRichText::NewL( paraFormatLayer, charFormatLayer );
    CleanupStack::PushL( richText );
    
    edwin->CreateLayoutL( richText );
    edwin->CreateTextViewL();
    
    CleanupStack::Pop( richText );
    CleanupStack::Pop( charFormatLayer );
    CleanupStack::Pop( paraFormatLayer );
    
    CleanupStack::PopAndDestroy( edwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEDeconstrutorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEDeconstrutorL( CStifItemParser& /*aItem*/ )
    {
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    CleanupStack::Pop( edwin );
    delete edwin;
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECEikEdwinL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECEikEdwinL( CStifItemParser& /*aItem*/ )
    {
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    CleanupStack::PopAndDestroy( edwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECEikEdwinPL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECEikEdwinPL( CStifItemParser& /*aItem*/ )
    {
    TGulBorder gulBorder;
    CEikEdwin* edwin = new (ELeave) CEikEdwin( gulBorder );
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    CleanupStack::PopAndDestroy( edwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEConstructL( CStifItemParser& /*aItem*/ )
    {
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    edwin->ConstructL();
    
    CleanupStack::PopAndDestroy( edwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetEdwinObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetEdwinObserverL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryControl* aknQueryControl = new ( ELeave )CAknQueryControl();
    CleanupStack::PushL( aknQueryControl );
    STIF_ASSERT_NOT_NULL( aknQueryControl );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    edwin->ConstructL();
    edwin->SetEdwinObserver( aknQueryControl );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( aknQueryControl );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEAddEdwinObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEAddEdwinObserverL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryControl* aknQueryControl = new ( ELeave )CAknQueryControl();
    CleanupStack::PushL( aknQueryControl );
    STIF_ASSERT_NOT_NULL( aknQueryControl );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    edwin->ConstructL();
    edwin->AddEdwinObserverL( aknQueryControl );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( aknQueryControl );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestERemoveEdwinObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestERemoveEdwinObserverL( CStifItemParser& /*aItem*/ )
    {
    CAknQueryControl* aknQueryControl = new ( ELeave )CAknQueryControl();
    CleanupStack::PushL( aknQueryControl );
    STIF_ASSERT_NOT_NULL( aknQueryControl );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    edwin->ConstructL();
    edwin->AddEdwinObserverL( aknQueryControl );
    edwin->RemoveEdwinObserver( aknQueryControl );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( aknQueryControl );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetContainerWindowL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetContainerWindowL( CStifItemParser& /*aItem*/ )
    {
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    edwin->ConstructL( CEikEdwin::EOwnsWindow );
    edwin->SetContainerWindowL();
    
    CleanupStack::PopAndDestroy( edwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetDocumentContentL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetDocumentContentL( CStifItemParser& /*aItem*/ )
    {
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    edwin->ConstructL( CEikEdwin::EAvkonEditor );
    
    CParaFormatLayer* paraFormatLayer = CParaFormatLayer::NewL();
    CleanupStack::PushL( paraFormatLayer );
    CCharFormatLayer* charFormatLayer = CCharFormatLayer::NewL();
    CleanupStack::PushL( charFormatLayer );
    CGlobalText * globalText = CGlobalText::NewL( paraFormatLayer, charFormatLayer );
    CleanupStack::PushL( globalText );
    
    edwin->SetDocumentContentL( *globalText );
    
    CleanupStack::Pop( globalText );
    CleanupStack::Pop( charFormatLayer );
    CleanupStack::Pop( paraFormatLayer );
    
    CleanupStack::PopAndDestroy( edwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    TKeyEvent event;
    event.iCode = EKeyCBA1;
    TKeyResponse response = edwin->OfferKeyEventL( event, EEventKey );
    STIF_ASSERT_EQUALS( EKeyWasNotConsumed, response );

    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEFocusChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEFocusChangedL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    edwin->FocusChanged( EDrawNow );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEActivateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEActivateL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    edwin->ActivateL();
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    CleanupStack::PopAndDestroy( edwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    edwin->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    TSize minSize = edwin->MinimumSize();
    TPoint point = minSize.AsPoint();
    STIF_ASSERT_NOT_EQUALS( 0, point.iX );
    STIF_ASSERT_NOT_EQUALS( 0, point.iY );
    
    CleanupStack::PopAndDestroy( edwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEDrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEDrawL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CTestSDKEditorsEdwin* edwin = new (ELeave) CTestSDKEditorsEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    edwin->ActivateL();
    
    edwin->ActivateGc();
    TPoint point1( 0, 0 );
    TPoint point2( KLength, KLength );
    TRect rect( point1, point2 );
    edwin->Draw( rect );
    edwin->DeactivateGc();
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetDimmedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetDimmedL( CStifItemParser& /*aItem*/ )
    {
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetDimmed( ETrue );
    
    CleanupStack::PopAndDestroy( edwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetContainerWindowPL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetContainerWindowPL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEGetColorUseListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEGetColorUseListL( CStifItemParser& /*aItem*/ )
    {
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    CArrayFix<TCoeColorUse>* indexArray = new ( ELeave ) CArrayFixFlat<TCoeColorUse>( 1 );
    CleanupStack::PushL( indexArray );
    edwin->GetColorUseListL( *indexArray );
    STIF_ASSERT_NOT_NULL( indexArray );
    
    CleanupStack::PopAndDestroy( indexArray );
    CleanupStack::PopAndDestroy( edwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->HandleResourceChange( KEikDynamicLayoutVariantSwitch );
    
    CleanupStack::PopAndDestroy( edwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEInputCapabilitiesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEInputCapabilitiesL( CStifItemParser& /*aItem*/ )
    {
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    TCoeInputCapabilities capa;
    edwin->SetInputCapabilitiesL( capa );
    STIF_ASSERT_TRUE( capa == edwin->InputCapabilities() );
    
    CleanupStack::PopAndDestroy( edwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetInputCapabilitiesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetInputCapabilitiesL( CStifItemParser& aItem )
    {
    return TestEInputCapabilitiesL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEWriteInternalStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEWriteInternalStateL( CStifItemParser& /*aItem*/ )
    {
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    const TInt LengthC = 200;
    CBufFlat* buf = CBufFlat::NewL( LengthC );
    CleanupStack::PushL( buf );
    RBufWriteStream writeStream;
    CleanupClosePushL( writeStream );
    writeStream.Open( *buf );
        
    STIF_ASSERT_NOT_LEAVES( edwin->WriteInternalStateL( writeStream ) );
    STIF_ASSERT_NOT_NULL( buf );
    STIF_ASSERT_NOT_NULL( &writeStream );
    
    CleanupStack::PopAndDestroy( &writeStream );
    CleanupStack::PopAndDestroy( buf );
    
    CleanupStack::PopAndDestroy( edwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEHandleScrollEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEHandleScrollEventL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CTestSDKEditorsEdwin* edwin = new (ELeave) CTestSDKEditorsEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    CEikScrollBar* scrollBar = new (ELeave) CEikScrollBar;
    CleanupStack::PushL( scrollBar );
    STIF_ASSERT_NOT_NULL( scrollBar );

    scrollBar->ConstructL( static_cast<MEikScrollBarObserver*>( edwin ),
                           control,
                           CEikScrollBar::EVertical,
                           KLength,
                           CEikScrollBar::EEikScrollBarDefaultBehaviour);
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    edwin->ActivateGc();
    
    edwin->HandleScrollEventL( scrollBar, EEikScrollThumbDragHoriz );
    
    edwin->DeactivateGc();
    CleanupStack::PopAndDestroy( scrollBar );
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEOnReformatL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEOnReformatL( CStifItemParser& /*aItem*/ )
    {
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->OnReformatL( edwin->TextView() );
    
    CleanupStack::PopAndDestroy( edwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestETextLengthL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestETextLengthL( CStifItemParser& /*aItem*/ )
    {
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    _LIT( KText, "text" );
    const TInt KTextLength = 4;
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    TInt length = edwin->TextLength();
    STIF_ASSERT_TRUE( KTextLength == length );
    
    CleanupStack::PopAndDestroy( edwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECursorPosL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECursorPosL( CStifItemParser& /*aItem*/ )
    {
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->CreateTextViewL();
   
    STIF_ASSERT_EQUALS( 0, edwin->CursorPos() );
    
    CleanupStack::PopAndDestroy( edwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESelectionLengthL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESelectionLengthL( CStifItemParser& /*aItem*/ )
    {
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->CreateTextViewL();
   
    STIF_ASSERT_EQUALS( 0, edwin->SelectionLength() );
    
    CleanupStack::PopAndDestroy( edwin );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESelectionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESelectionL( CStifItemParser& aItem )
    {
    return TestESetSelectionL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEClearSelectionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEClearSelectionL( CStifItemParser& aItem )
    {
    return TestESetSelectionL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetSelectionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetSelectionL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    _LIT( KText, "text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetSelectionL( 0, 2 );
    TCursorSelection cursorSelection( 0, 2 );
    STIF_ASSERT_TRUE( cursorSelection.iCursorPos == edwin->Selection().iCursorPos );
    STIF_ASSERT_TRUE( cursorSelection.iAnchorPos == edwin->Selection().iAnchorPos );
    
    edwin->ClearSelectionL();
    STIF_ASSERT_TRUE( 0 == edwin->Selection().iCursorPos );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetCursorPosL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetCursorPosL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    _LIT( KText, "text" );
    const TInt KTextLength = 4;
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetCursorPosL( KTextLength, EFalse );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESelectAllL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESelectAllL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    _LIT( KText, "text" );
    const TInt KTextLength = 4;
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SelectAllL();
    STIF_ASSERT_TRUE( KTextLength == edwin->Selection().iCursorPos );
    STIF_ASSERT_TRUE( 0 == edwin->Selection().iAnchorPos );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECalculateWidthL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECalculateWidthL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    edwin->CalculateWidth( KLength );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEGetTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEGetTextL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    TBuf<KLength> textGet;
    edwin->GetText( textGet );
    
    STIF_ASSERT_EQUALS( 0, text.Compare( textGet ) );
    
    HBufC* bufGet = edwin->GetTextInHBufL();
    CleanupStack::PushL( bufGet );
    STIF_ASSERT_EQUALS( 0, bufGet->Compare( text ) );
    
    CleanupStack::PopAndDestroy( bufGet );
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEGetTextInHBufL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEGetTextInHBufL( CStifItemParser& aItem )
    {
    return TestEGetTextL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetTextL( CStifItemParser& aItem )
    {
    return TestEGetTextL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEClipboardL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEClipboardL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    edwin->ClipboardL( CEikEdwin::ECopy );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEInsertFieldL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEInsertFieldL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->UpdateAllFieldsL();
    
    CMyDateTimeField* field = new (ELeave) CMyDateTimeField;
    CleanupStack::PushL( field );
    
    TUid uid = field->Type();
    edwin->InsertFieldL( field, uid );
    
    CleanupStack::Pop( field );
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEUpdateAllFieldsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEUpdateAllFieldsL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    edwin->UpdateAllFieldsL();
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEUpdateCurrentFieldL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEUpdateCurrentFieldL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    edwin->UpdateCurrentFieldL();
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECountWordsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECountWordsL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    const TInt word = 2;
    TInt count = edwin->CountWords();
    STIF_ASSERT_EQUALS( word, count );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEInsertFromTextFileL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEInsertFromTextFileL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    
    _LIT( KFileName, "c:\\testsdkeditors.txt" );
    const TInt KFileLength = 50;
    TBuf<KFileLength> fileName( KFileName );
    
    RFs afs;
    CleanupClosePushL( afs );
    STIF_ASSERT_EQUALS( KErrNone, afs.Connect() );
    RFileWriteStream aFile;
    CleanupClosePushL( aFile );
    aFile.Replace( afs, fileName, EFileWrite );
    aFile.WriteL( KText );
    CleanupStack::PopAndDestroy( &aFile );
    CleanupStack::PopAndDestroy( &afs );
    
    edwin->UpdateAllFieldsL();
    edwin->SelectAllL();
    edwin->InsertFromTextFileL( fileName, CPlainText::EOrganiseByLine );
    
    TBuf<KLength> textGet;
    edwin->GetText( textGet );
    STIF_ASSERT_TRUE( 0 == textGet.Compare( KText ) );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEIdleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEIdleL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    STIF_ASSERT_FALSE( edwin->IdleL( edwin ) );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestETextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestETextL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    CPlainText* plainText = edwin->Text();
    STIF_ASSERT_NOT_NULL( plainText );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECancelFepTransactionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECancelFepTransactionL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    edwin->FocusChanged( EDrawNow );
    edwin->CancelFepTransaction();
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEHandleTextChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEHandleTextChangedL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    edwin->ActivateL();
    edwin->HandleTextChangedL();
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestELayoutWidthL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestELayoutWidthL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetWysiwygModeOff();
    CGraphicsDevice* device = CCoeEnv::Static()->ScreenDevice();
    edwin->SetWysiwygModeOn( KLength, device );
    STIF_ASSERT_TRUE( KLength == edwin->LayoutWidth() );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestENotifyNewDocumentL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestENotifyNewDocumentL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->NotifyNewDocumentL();
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestENotifyNewFormatL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestENotifyNewFormatL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->NotifyNewFormatL();
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEFindL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEFindL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    _LIT( KFindText, "text" );
    TBuf<KLength> textFind( KFindText );
    
    STIF_ASSERT_TRUE( edwin->FindL( &textFind ) );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEFindTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEFindTextL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    _LIT( KFindText, "text" );
    TBuf<KLength> textFind( KFindText );
    const TInt pos = 4;
    
    STIF_ASSERT_TRUE( pos == edwin->FindTextL( &textFind, 0, CEikEdwin::EFindCaseSensitive ) );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEReplaceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEReplaceL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "ttext" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    SEdwinFindModel findModel;
    _LIT( KFText, "t" ); 
    _LIT( KRText, "replace" );
    TBuf<KLength> findText( KFText );
    TBuf<KLength> replaceText( KRText );
    findModel.iFlags = 0;
    findModel.iText = findText;
    findModel.iReplaceText = replaceText;
    findModel.iReplaceOption = EReplaceOnce;
    edwin->ReplaceL( &findModel );
    
    _LIT( KTextGet, "replacetext" );
    TBuf<KLength> textReplace( KTextGet );
    
    TBuf<KLength> textGet;
    edwin->GetText( textGet );
    STIF_ASSERT_TRUE( 0 == textGet.Compare( textReplace ) );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEReplaceAllL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEReplaceAllL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    SEdwinFindModel findModel;
    _LIT( KFText, "t" ); 
    _LIT( KRText, "e" );
    TBuf<KLength> findText( KFText );
    TBuf<KLength> replaceText( KRText );
    findModel.iFlags = CEikEdwin::EFindCaseSensitive;
    findModel.iText = findText;
    findModel.iReplaceText = replaceText;
    findModel.iReplaceOption = EReplaceAll;
    edwin->ReplaceAllL( &findModel );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEGetFindText
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEGetFindTextL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );

    TBuf<KLength> textFindGet;
    edwin->GetFindText( &textFindGet );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEUpdateScrollBarsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEUpdateScrollBarsL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );

    edwin->UpdateScrollBarsL();
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECreateScrollBarFrameL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECreateScrollBarFrameL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );

    CEikScrollBarFrame* barFrame = edwin->CreateScrollBarFrameL();
    STIF_ASSERT_NOT_NULL( barFrame );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECreatePreAllocatedScrollBarFrameL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECreatePreAllocatedScrollBarFrameL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );

    CEikScrollBarFrame* barFrame = edwin->CreatePreAllocatedScrollBarFrameL();
    STIF_ASSERT_NOT_NULL( barFrame );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEScrollBarFrameL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEScrollBarFrameL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );

    CEikScrollBarFrame* barFrame = edwin->CreateScrollBarFrameL();
    STIF_ASSERT_TRUE( barFrame == edwin->ScrollBarFrame() );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetWordWrapL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetWordWrapL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetWordWrapL( EFalse );
    edwin->SetWordWrapL( ETrue );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestELineCursorWidthL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestELineCursorWidthL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    STIF_ASSERT_TRUE( 0 == edwin->LineCursorWidth() );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetZoomFactorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetZoomFactorL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    TZoomFactor factor;
    edwin->SetZoomFactorL( &factor );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetBackgroundColorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetBackgroundColorL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetBackgroundColorL( KRgbSymbianGreen );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetWysiwygModeOnL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetWysiwygModeOnL( CStifItemParser& aItem )
    {
    return TestELayoutWidthL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetWysiwygModeOffL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetWysiwygModeOffL( CStifItemParser& aItem )
    {
    return TestELayoutWidthL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEUpdateLayoutWidthL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEUpdateLayoutWidthL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    const TInt width = 10;
    edwin->UpdateLayoutWidth( width );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESendDataOverIrL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESendDataOverIrL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    TTestSDKIrFactory irFactory;
    ivEikonEnv->SetIrFactory( &irFactory );
    
    edwin->SendDataOverIrL();
    edwin->ReceiveDataOverIrL();
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEReceiveDataOverIrL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEReceiveDataOverIrL( CStifItemParser& aItem )
    {
    return TestESendDataOverIrL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetAmountToFormatL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetAmountToFormatL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetAmountToFormatL( ETrue );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetAmountToFormatPL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetAmountToFormatPL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetAmountToFormatL( ETrue, ETrue );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetPasteFromIrStoreL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetPasteFromIrStoreL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetPasteFromIrStore( ETrue );
    edwin->UpdateCurrentFieldL();
    edwin->ClipboardL( CEikEdwin::ECopy );
    
    CClipboard* cb = CClipboard::NewForWritingLC(CCoeEnv::Static()->FsSession());
    
    edwin->SelectAllL();
    edwin->CopyToStoreL( cb->Store(), cb->StreamDictionary() );
    edwin->ClearSelectionL();
    edwin->PasteFromStoreL( cb->Store(), cb->StreamDictionary() );
    TBuf<KLength> textGet;
    edwin->GetText( textGet );
    _LIT( KTextPaste, "one textone text" );
    STIF_ASSERT_EQUALS( 0, textGet.Compare( KTextPaste ) );
    
    CleanupStack::PopAndDestroy( cb );
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEPasteFromStoreL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEPasteFromStoreL( CStifItemParser& aItem )
    {
    return TestESetPasteFromIrStoreL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECopyToStoreL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECopyToStoreL( CStifItemParser& aItem )
    {
    return TestESetPasteFromIrStoreL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetBorderViewMarginsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetBorderViewMarginsL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    TMargins8 margin;
    margin.SetAllValuesTo( 1 );
    edwin->SetBorderViewMargins( margin );
    STIF_ASSERT_TRUE( margin.iBottom == edwin->Margins().iBottom );
    STIF_ASSERT_TRUE( margin.iLeft == edwin->Margins().iLeft );
    STIF_ASSERT_TRUE( margin.iRight == edwin->Margins().iRight );
    STIF_ASSERT_TRUE( margin.iTop == edwin->Margins().iTop );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEForceScrollBarUpdateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEForceScrollBarUpdateL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->ForceScrollBarUpdateL();
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetDocumentOwnershipL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetDocumentOwnershipL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetDocumentOwnership( CEikEdwin::EOwnsText );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetTextLimitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetTextLimitL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetTextLimit( KLength );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestERunCharMapDialogL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestERunCharMapDialogL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    CTestSDKEditorsDialogFactory* factory = new (ELeave) CTestSDKEditorsDialogFactory;
    CleanupStack::PushL( factory );
    ivEikonEnv->SetCDlgDialogFactory( factory );
    
    edwin->RunCharMapDialogL();
    
    CleanupStack::PopAndDestroy( factory );
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEMarginsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEMarginsL( CStifItemParser& aItem )
    {
    return TestESetBorderViewMarginsL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEUpperFullFormattingLengthL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEUpperFullFormattingLengthL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetUpperFullFormattingLength( KLength );
    const TInt systemMaxLength = 500;
    STIF_ASSERT_TRUE( systemMaxLength == edwin->UpperFullFormattingLength() );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestELowerPartialFormattingLengthL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestELowerPartialFormattingLengthL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetUpperFullFormattingLength( KLength );
    const TInt lowerLengthGet = 400;
    STIF_ASSERT_TRUE( lowerLengthGet == edwin->LowerPartialFormattingLength() );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetReadOnlyL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetReadOnlyL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetReadOnly( ETrue );
    STIF_ASSERT_TRUE( edwin->IsReadOnly() );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEIsReadOnlyL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEIsReadOnlyL( CStifItemParser& aItem )
    {
    return TestESetReadOnlyL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECheckNotReadOnlyL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECheckNotReadOnlyL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetReadOnly( EFalse );
    STIF_ASSERT_FALSE( edwin->IsReadOnly() );
    edwin->CheckNotReadOnlyL();
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetAllowPicturesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetAllowPicturesL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetAllowPictures( ETrue );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECheckRemovePicturesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECheckRemovePicturesL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->CheckRemovePictures( 0, edwin->TextLength() );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetRightWrapGutterL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetRightWrapGutterL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetRightWrapGutter( 1 );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEUndoL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEUndoL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetAllowUndo( ETrue );
    TCursorSelection cursorSelection;
    STIF_ASSERT_TRUE( edwin->SetUndoBufferL( cursorSelection ) );
    edwin->UndoL();
    edwin->ClearUndo();
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEClearUndoL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEClearUndoL( CStifItemParser& aItem )
    {
    return TestEUndoL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetAllowUndoL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetAllowUndoL( CStifItemParser& aItem )
    {
    return TestEUndoL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESupportsUndoL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESupportsUndoL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetAllowUndo( ETrue );
    STIF_ASSERT_TRUE( edwin->SupportsUndo() );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECanUndoL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECanUndoL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetAllowUndo( ETrue );
    TCursorSelection cursorSelection;
    STIF_ASSERT_TRUE( edwin->SetUndoBufferL( cursorSelection ) );
    STIF_ASSERT_TRUE( edwin->CanUndo() );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetWordDelimitersL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetWordDelimitersL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetWordDelimiters( ETrue, ETrue );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEGetWordInfoL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEGetWordInfoL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "onetext" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    TInt start;
    TInt length;
    edwin->GetWordInfo( 0, start, length );
    STIF_ASSERT_EQUALS( 0, start );
    STIF_ASSERT_EQUALS( 7, length );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEMoveCursorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEMoveCursorL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "onetext" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->MoveCursorL( TCursorPosition::EFRight, ETrue );
    edwin->MoveDisplayL( TCursorPosition::EFRight );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEMoveDisplayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEMoveDisplayL( CStifItemParser& aItem )
    {
    return TestEMoveCursorL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECheckValidityOfCharsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECheckValidityOfCharsL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "onetext" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->CheckValidityOfChars( 0, text.Length() );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetOnlyASCIICharsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetOnlyASCIICharsL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "onetext" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetOnlyASCIIChars( ETrue );
    STIF_ASSERT_TRUE( edwin->OnlyASCIIChars() );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEOnlyASCIICharsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEOnlyASCIICharsL( CStifItemParser& aItem )
    {
    return TestESetOnlyASCIICharsL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEAvgLinesInViewRectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEAvgLinesInViewRectL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "onetext" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    const TInt line = 2;
    edwin->SetAvgLinesInViewRect( line );
    STIF_ASSERT_EQUALS( line, edwin->AvgLinesInViewRect() );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEAvgCharsPerLineL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEAvgCharsPerLineL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "onetext" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    const TInt count = 10;
    edwin->SetAvgCharsPerLine( count );
    STIF_ASSERT_EQUALS( count, edwin->AvgCharsPerLine() );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetAvgLinesInViewRectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetAvgLinesInViewRectL( CStifItemParser& aItem )
    {
    return TestEAvgLinesInViewRectL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetAvgCharsPerLineL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetAvgCharsPerLineL( CStifItemParser& aItem )
    {
    return TestEAvgCharsPerLineL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetEdwinSizeObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetEdwinSizeObserverL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "onetext" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    CAknQueryControl* observer = new (ELeave) CAknQueryControl;
    CleanupStack::PushL( observer );
    edwin->SetEdwinSizeObserver( observer );
    
    CleanupStack::PopAndDestroy( observer );
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEMinimumHeightL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEMinimumHeightL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "onetext" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    const TInt minHeight = 5;
    edwin->SetMinimumHeight( minHeight );
    STIF_ASSERT_EQUALS( minHeight, edwin->MinimumHeight() );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEMaximumHeightL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEMaximumHeightL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "onetext" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    const TInt maxHeight = 20;
    edwin->SetMaximumHeight( maxHeight );
    STIF_ASSERT_EQUALS( maxHeight, edwin->MaximumHeight() );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetMinimumHeightL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetMinimumHeightL( CStifItemParser& aItem )
    {
    return TestEMinimumHeightL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetMaximumHeightL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetMaximumHeightL( CStifItemParser& aItem )
    {
    return TestEMaximumHeightL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEInsertDeleteCharsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEInsertDeleteCharsL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "onetext" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    _LIT( KIDText, "insert" );
    TBuf<KLength> idText( KIDText );
    
    const TInt anchorPos = 3;
    TCursorSelection cursorSelection;
    cursorSelection.iCursorPos = 0;
    cursorSelection.iAnchorPos = anchorPos;
    edwin->InsertDeleteCharsL( 0, idText, cursorSelection );
    
    TBuf<KLength> textGet;
    edwin->GetText( textGet );
    _LIT( KTextChange, "inserttext" );
    STIF_ASSERT_TRUE( 0 == textGet.Compare( KTextChange ) );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetNonPrintingCharsVisibilityL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetNonPrintingCharsVisibilityL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "onetext" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    TNonPrintingCharVisibility charVisibility;
    charVisibility.SetNoneVisible();
    edwin->SetNonPrintingCharsVisibility( charVisibility );
    STIF_ASSERT_TRUE( edwin->NonPrintingCharsVisibility().NoneVisible() );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestENonPrintingCharsVisibilityL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestENonPrintingCharsVisibilityL( CStifItemParser& aItem )
    {
    return TestESetNonPrintingCharsVisibilityL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetAvkonWrapL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetAvkonWrapL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "onetext" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetAvkonWrap( ETrue );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetAknEditorCaseL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetAknEditorCaseL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "onetext" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetAknEditorCase( EAknEditorUpperCase );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetAknEditorPermittedCaseModesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetAknEditorPermittedCaseModesL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "onetext" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetAknEditorPermittedCaseModes( EAknEditorAllCaseModes );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetAknEditorNumericKeymapL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetAknEditorNumericKeymapL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "onetext" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetAknEditorNumericKeymap( EAknEditorStandardNumberModeKeymap );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetAknEditorInputModeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetAknEditorInputModeL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "onetext" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetAknEditorInputMode( EAknEditorTextInputMode );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetAknEditorAllowedInputModesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetAknEditorAllowedInputModesL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "onetext" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetAknEditorAllowedInputModes( EAknEditorTextInputMode );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetAknEditorSpecialCharacterTableL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetAknEditorSpecialCharacterTableL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "onetext" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetAknEditorSpecialCharacterTable( 0 );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetAknEditorFlagsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetAknEditorFlagsL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "onetext" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetAknEditorFlags( EAknEditorFlagDefault );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEEnableCcpuSupportL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEEnableCcpuSupportL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "onetext" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->EnableCcpuSupportL( ETrue );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetAknEditorCurrentInputModeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetAknEditorCurrentInputModeL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "onetext" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetAknEditorCurrentInputMode( EAknEditorTextInputMode );
    STIF_ASSERT_TRUE( EAknEditorTextInputMode == edwin->AknEditorCurrentInputMode() );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEAknEditorCurrentInputModeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEAknEditorCurrentInputModeL( CStifItemParser& aItem )
    {
    return TestESetAknEditorCurrentInputModeL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetAknEditorCurrentCaseL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetAknEditorCurrentCaseL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "onetext" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetAknEditorCurrentCase( EAknEditorUpperCase );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetAknEditorLocalLanguageL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetAknEditorLocalLanguageL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "onetext" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetAknEditorLocalLanguage( ELangEnglish );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestENotifyEditorStateObserverOfStateChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestENotifyEditorStateObserverOfStateChangeL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "onetext" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->NotifyEditorStateObserverOfStateChangeL();
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetSuppressBackgroundDrawingL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetSuppressBackgroundDrawingL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "onetext" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetSuppressBackgroundDrawing( ETrue );
    STIF_ASSERT_TRUE( edwin->IsBackgroundDrawingSuppressed() );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEIsBackgroundDrawingSuppressedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEIsBackgroundDrawingSuppressedL( CStifItemParser& aItem )
    {
    return TestESetSuppressBackgroundDrawingL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetTextLinesRectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetTextLinesRectL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "onetext" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    TRect rect( 0, 0, KLength, KLength );
    edwin->SetTextLinesRect( rect );
    STIF_ASSERT_TRUE( rect == edwin->GetTextLinesRect() );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetScrollRectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetScrollRectL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "onetext" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    const TInt KScroll = 20;
    TRect rect( KLength, KLength, KScroll, KScroll );
    edwin->SetScrollRect( rect );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEGetTextLinesRectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEGetTextLinesRectL( CStifItemParser& aItem )
    {
    return TestESetTextLinesRectL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetCursorVisibleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetCursorVisibleL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "onetext" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetCursorVisible( ETrue );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetMaximumHeightInLinesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetMaximumHeightInLinesL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "onetext" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    const TInt line = 2;
    edwin->SetMaximumHeightInLines( line );
    STIF_ASSERT_TRUE( line == edwin->MaximumHeightInLines() );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEMaximumHeightInLinesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEMaximumHeightInLinesL( CStifItemParser& aItem )
    {
    return TestESetMaximumHeightInLinesL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECcpuIsFocusedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECcpuIsFocusedL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "onetext" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );

    edwin->SetFocus( ETrue, ENoDrawNow );
    STIF_ASSERT_TRUE( edwin->CcpuIsFocused() );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECcpuCanCutL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECcpuCanCutL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "onetext" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );

    edwin->SelectAllL();
    STIF_ASSERT_TRUE( edwin->CcpuCanCut() );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECcpuCutL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECcpuCutL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "onetext" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );

    edwin->SelectAllL();
    edwin->CcpuCutL();
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECcpuCanCopyL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECcpuCanCopyL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "onetext" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );

    edwin->SelectAllL();
    STIF_ASSERT_TRUE( edwin->CcpuCanCopy() );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECcpuCopyL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECcpuCopyL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "onetext" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );

    edwin->SelectAllL();
    edwin->CcpuCopyL();
    edwin->SelectAllL();
    edwin->CcpuPasteL();
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECcpuCanPasteL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECcpuCanPasteL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "onetext" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );

    edwin->SelectAllL();
    STIF_ASSERT_TRUE( edwin->CcpuCanPaste() );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECcpuPasteL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECcpuPasteL( CStifItemParser& aItem )
    {
    return TestECcpuCopyL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECcpuCanUndoL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECcpuCanUndoL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetAllowUndo( ETrue );
    TCursorSelection cursorSelection;
    STIF_ASSERT_TRUE( edwin->SetUndoBufferL( cursorSelection ) );
    STIF_ASSERT_TRUE( edwin->CcpuCanUndo() );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECcpuUndoL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECcpuUndoL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    edwin->SetAllowUndo( ETrue );
    
    _LIT( KText, "onetext" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );

    edwin->SelectAllL();
    edwin->CcpuCutL();
    edwin->CcpuUndoL();
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEAknEdwinFlagsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEAknEdwinFlagsL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    edwin->SetAllowUndo( ETrue );
    
    _LIT( KText, "onetext" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );

    STIF_ASSERT_TRUE( 0 == edwin->AknEdwinFlags() );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECreateTextViewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECreateTextViewL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    
    edwin->CreateTextViewL();
    STIF_ASSERT_NOT_NULL( edwin->TextView() );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestETextViewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestETextViewL( CStifItemParser& aItem )
    {
    return TestECreateTextViewL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestETextLayoutL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestETextLayoutL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    STIF_ASSERT_NOT_NULL( edwin->TextLayout() );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetUndoBufferL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetUndoBufferL( CStifItemParser& aItem )
    {
    return TestESetUndoableTextL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetUndoableTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetUndoableTextL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetAllowUndo( ETrue );
    TCursorSelection cursorSelection;
    STIF_ASSERT_TRUE( edwin->SetUndoBufferL( cursorSelection ) );
    edwin->SetUndoableText( cursorSelection );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetMaxLengthL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetMaxLengthL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    const TInt maxLength = 20;
    edwin->SetMaxLength( maxLength );
    STIF_ASSERT_TRUE( maxLength == edwin->MaxLength() );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEMaxLengthL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEMaxLengthL( CStifItemParser& aItem )
    {
    return TestESetMaxLengthL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEAddFlagToUserFlagsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEAddFlagToUserFlagsL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    edwin->ConstructL( EAknEditorFlagDefault );
    
    TInt flag = edwin->UserFlags();
    edwin->AddFlagToUserFlags( EAknEditorFlagEnablePictographInput );
    edwin->RemoveFlagFromUserFlags( EAknEditorFlagEnablePictographInput );
    STIF_ASSERT_TRUE( flag == edwin->UserFlags() );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestERemoveFlagFromUserFlagsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestERemoveFlagFromUserFlagsL( CStifItemParser& aItem )
    {
    return TestEAddFlagToUserFlagsL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEUserFlagsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEUserFlagsL( CStifItemParser& aItem )
    {
    return TestEAddFlagToUserFlagsL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetCharFormatLayerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetCharFormatLayerL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    CCharFormatLayer* charFormatLayer = CCharFormatLayer::NewL();
    CleanupStack::PushL( charFormatLayer );
    
    edwin->SetCharFormatLayer( charFormatLayer );
    
    CleanupStack::Pop( charFormatLayer );
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetParaFormatLayerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetParaFormatLayerL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    CParaFormatLayer* paraFormatLayer = CParaFormatLayer::NewL();
    CleanupStack::PushL( paraFormatLayer );
    
    edwin->SetParaFormatLayer( paraFormatLayer );
    
    CleanupStack::Pop( paraFormatLayer );
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetSkinBackgroundControlContextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetSkinBackgroundControlContextL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    TAknsItemID itemId;
    TRect rect( 0, 0, KLength, KLength );
    CAknsBasicBackgroundControlContext* context = CAknsBasicBackgroundControlContext::NewL( itemId, rect, ETrue );
    CleanupStack::PushL( context );
    
    edwin->SetSkinBackgroundControlContextL( context );
    
    CleanupStack::PopAndDestroy( context );
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetAlignmentL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetAlignmentL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetAlignment( EAknEditorAlignCenter );

    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetPictographAnimationCallBackL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetPictographAnimationCallBackL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    TCallBack callBack;
    edwin->SetPictographAnimationCallBack( callBack );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetUpperFullFormattingLengthL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetUpperFullFormattingLengthL( CStifItemParser& aItem )
    {
    return TestEUpperFullFormattingLengthL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetSuppressNotifyDrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetSuppressNotifyDrawL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetSuppressNotifyDraw( ETrue );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetSuppressFormattingL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetSuppressFormattingL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CEikEdwin* edwin = new (ELeave) CEikEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetSuppressFormatting( ETrue );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEEditObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEEditObserverL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CTestSDKEditorsEdwin* edwin = new (ELeave) CTestSDKEditorsEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->EditObserver( 0, text.Length() );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestETrappedDrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestETrappedDrawL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CTestSDKEditorsEdwin* edwin = new (ELeave) CTestSDKEditorsEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    edwin->ActivateL();
    
    edwin->ActivateGc();
    TRect rect( edwin->Size() );
    edwin->TrappedDraw( rect );
    edwin->DeactivateGc();
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEDrawContentsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEDrawContentsL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CTestSDKEditorsEdwin* edwin = new (ELeave) CTestSDKEditorsEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    edwin->ActivateL();
    
    edwin->DrawContents();
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEBaseConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEBaseConstructL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CTestSDKEditorsEdwin* edwin = new (ELeave) CTestSDKEditorsEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    edwin->BaseConstructL();
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEFormatTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEFormatTextL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CTestSDKEditorsEdwin* edwin = new (ELeave) CTestSDKEditorsEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->FormatTextL();
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEDeleteHighlightL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEDeleteHighlightL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CTestSDKEditorsEdwin* edwin = new (ELeave) CTestSDKEditorsEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SelectAllL();
    TBool change;
    STIF_ASSERT_TRUE( 0 == edwin->DeleteHighlightL( change ) );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEOkToDeleteSelectionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEOkToDeleteSelectionL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CTestSDKEditorsEdwin* edwin = new (ELeave) CTestSDKEditorsEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    STIF_ASSERT_TRUE( edwin->OkToDeleteSelectionL() );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEDeleteL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEDeleteL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CTestSDKEditorsEdwin* edwin = new (ELeave) CTestSDKEditorsEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    TBool change;
    TCursorSelection cursorSelection;
    cursorSelection.iCursorPos = 0;
    cursorSelection.iCursorPos = 4;
    edwin->DeleteL( change, cursorSelection );
    
    TBuf<KLength> textGet;
    edwin->GetText( textGet );
    
    _LIT( KTextChanged, "text" );
    STIF_ASSERT_TRUE( 0 == textGet.Compare( KTextChanged ) );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestETrappedSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestETrappedSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CTestSDKEditorsEdwin* edwin = new (ELeave) CTestSDKEditorsEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->TrappedSizeChanged();
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEHandleSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEHandleSizeChangedL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CTestSDKEditorsEdwin* edwin = new (ELeave) CTestSDKEditorsEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->HandleSizeChangedL();
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECancelSelectionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECancelSelectionL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CTestSDKEditorsEdwin* edwin = new (ELeave) CTestSDKEditorsEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->CancelSelectionL();
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEMoveCursorToChunkStartL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEMoveCursorToChunkStartL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CTestSDKEditorsEdwin* edwin = new (ELeave) CTestSDKEditorsEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->MoveCursorToChunkStartL( EFalse );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECancelInsertCharFormatL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECancelInsertCharFormatL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CTestSDKEditorsEdwin* edwin = new (ELeave) CTestSDKEditorsEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->CancelInsertCharFormat();
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEPlaceDataOnClipboardL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEPlaceDataOnClipboardL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CTestSDKEditorsEdwin* edwin = new (ELeave) CTestSDKEditorsEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->PlaceDataOnClipboardL();
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEReportEdwinEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEReportEdwinEventL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CTestSDKEditorsEdwin* edwin = new (ELeave) CTestSDKEditorsEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->ReportEdwinEventL( MEikEdwinObserver::EEventFormatChanged );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetLineCursorDetailsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetLineCursorDetailsL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CTestSDKEditorsEdwin* edwin = new (ELeave) CTestSDKEditorsEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetLineCursorDetailsL();
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECopyDocumentContentL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECopyDocumentContentL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CTestSDKEditorsEdwin* edwin = new (ELeave) CTestSDKEditorsEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    CParaFormatLayer* paraFormatLayer = CParaFormatLayer::NewL();
    CleanupStack::PushL( paraFormatLayer );
    CCharFormatLayer* charFormatLayer = CCharFormatLayer::NewL();
    CleanupStack::PushL( charFormatLayer );
    CGlobalText * globalText = CGlobalText::NewL( paraFormatLayer, charFormatLayer );
    CleanupStack::PushL( globalText );
    
    edwin->CopyDocumentContentL( *globalText, *globalText );
    
    CleanupStack::Pop( globalText );
    CleanupStack::Pop( charFormatLayer );
    CleanupStack::Pop( paraFormatLayer );
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEDisplayFindTextNotFoundL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEDisplayFindTextNotFoundL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CTestSDKEditorsEdwin* edwin = new (ELeave) CTestSDKEditorsEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->DisplayFindTextNotFound( text );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEHandleTextPastedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEHandleTextPastedL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CTestSDKEditorsEdwin* edwin = new (ELeave) CTestSDKEditorsEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    TInt length;
    edwin->HandleTextPastedL( 0, length );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECreateCustomDrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECreateCustomDrawL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CTestSDKEditorsEdwin* edwin = new (ELeave) CTestSDKEditorsEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    CLafEdwinCustomDrawBase* drawBase = edwin->CreateCustomDrawL();
    STIF_ASSERT_NOT_NULL( drawBase );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEReadAknResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEReadAknResourceL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CTestSDKEditorsEdwin* edwin = new (ELeave) CTestSDKEditorsEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_AKNALLEDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    TResourceReader reader1;
    CCoeEnv::Static()->CreateResourceReaderLC( reader1, R_TESTSDK_AKNEDWIN );
    edwin->ReadAknResourceL( reader1 );
    CleanupStack::PopAndDestroy();
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECreateLayoutL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECreateLayoutL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CTestSDKEditorsEdwin* edwin = new (ELeave) CTestSDKEditorsEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );

    CParaFormatLayer* paraFormatLayer = CParaFormatLayer::NewL();
    CleanupStack::PushL( paraFormatLayer );
    CCharFormatLayer* charFormatLayer = CCharFormatLayer::NewL();
    CleanupStack::PushL( charFormatLayer );
    CGlobalText * globalText = CGlobalText::NewL( paraFormatLayer, charFormatLayer );
    CleanupStack::PushL( globalText );
    
    edwin->CreateLayoutL( globalText );
    
    CleanupStack::Pop( globalText );
    CleanupStack::Pop( charFormatLayer );
    CleanupStack::Pop( paraFormatLayer );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECreateTextAndLayoutL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECreateTextAndLayoutL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CTestSDKEditorsEdwin* edwin = new (ELeave) CTestSDKEditorsEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );

    CParaFormatLayer* paraFormatLayer = CParaFormatLayer::NewL();
    CleanupStack::PushL( paraFormatLayer );
    CCharFormatLayer* charFormatLayer = CCharFormatLayer::NewL();
    CleanupStack::PushL( charFormatLayer );
    
    edwin->CreateTextAndLayoutL( paraFormatLayer, charFormatLayer );

    CleanupStack::Pop( charFormatLayer );
    CleanupStack::Pop( paraFormatLayer );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestECheckEdwinExtensionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestECheckEdwinExtensionL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CTestSDKEditorsEdwin* edwin = new (ELeave) CTestSDKEditorsEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->CheckEdwinExtensionL();
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEEdwinExtensionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEEdwinExtensionL( CStifItemParser& /*aItem*/ )
    {
    //return value is private
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEMopSupplyObjectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEMopSupplyObjectL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CTestSDKEditorsEdwin* edwin = new (ELeave) CTestSDKEditorsEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    TTypeUid::Ptr ptr = TTypeUid::Null();
    ptr = edwin->MopSupplyObject( CAknExtendedInputCapabilities::ETypeId );
    CAknExtendedInputCapabilities* point = static_cast<CAknExtendedInputCapabilities*> ( ptr.Pointer() );
    STIF_ASSERT_NOT_NULL( point );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetTextSkinColorIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetTextSkinColorIdL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CTestSDKEditorsEdwin* edwin = new (ELeave) CTestSDKEditorsEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetTextSkinColorIdL( 0 );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestESetHighlightStyleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestESetHighlightStyleL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CTestSDKEditorsEdwin* edwin = new (ELeave) CTestSDKEditorsEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    edwin->SetContainerWindowL( *control );
    edwin->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );
    
    edwin->SetHighlightStyleL( EEikEdwinHighlightNormal  );
    
    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }


// -----------------------------------------------------------------------------
// CTestSDKEditors::TestEEnableKineticScrollingL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestEEnableKineticScrollingL( CStifItemParser& /*aItem*/ )
    {
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CTestSDKEditorsEdwin* edwin = new ( ELeave ) CTestSDKEditorsEdwin;
    CleanupStack::PushL( edwin );
    STIF_ASSERT_NOT_NULL( edwin );
    // Enable kinetic scrolling
    edwin->EnableKineticScrollingL( ETrue );
    edwin->SetContainerWindowL( *control );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_EDWIN );
    edwin->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    // CreateLayoutL
    CParaFormatLayer* paraFormatLayer = CParaFormatLayer::NewL();
    CleanupStack::PushL( paraFormatLayer );
    CCharFormatLayer* charFormatLayer = CCharFormatLayer::NewL();
    CleanupStack::PushL( charFormatLayer );
    CGlobalText * globalText =
        CGlobalText::NewL( paraFormatLayer, charFormatLayer );
    CleanupStack::PushL( globalText );
    edwin->CreateLayoutL( globalText );
    CleanupStack::Pop( globalText );
    CleanupStack::Pop( charFormatLayer );
    CleanupStack::Pop( paraFormatLayer );

    edwin->CreateTextViewL();

    // SetTextL
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    edwin->SetTextL( &text );

    edwin->ForceScrollBarUpdateL();
    edwin->HandleSizeChangedL();

    // Set selection
    const TInt KSelectionPosition( 2 );
    edwin->SetSelectionL( 0, KSelectionPosition );
    TCursorSelection cursorSelection( 0, KSelectionPosition );
    STIF_ASSERT_TRUE(
            cursorSelection.iCursorPos == edwin->Selection().iCursorPos );
    STIF_ASSERT_TRUE(
            cursorSelection.iAnchorPos == edwin->Selection().iAnchorPos );
    edwin->ClearSelectionL();
    STIF_ASSERT_TRUE( 0 == edwin->Selection().iCursorPos );

    edwin->MoveCursorL( TCursorPosition::EFRight, ETrue );
    STIF_ASSERT_FALSE( edwin->IdleL( edwin ) );

    // HandlePointerEventL
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    edwin->HandlePointerEventL( event );

    // HandleScrollEventL
    CEikScrollBar* scrollBar = new ( ELeave ) CEikScrollBar;
    CleanupStack::PushL( scrollBar );
    STIF_ASSERT_NOT_NULL( scrollBar );
    scrollBar->ConstructL( static_cast<MEikScrollBarObserver*>( edwin ),
                           control,
                           CEikScrollBar::EVertical,
                           KLength,
                           CEikScrollBar::EEikScrollBarDefaultBehaviour );
    TAknDoubleSpanScrollBarModel doubleModel;
    scrollBar->SetModel( &doubleModel );
    edwin->HandleScrollEventL( scrollBar, EEikScrollThumbDragHoriz );
    CleanupStack::PopAndDestroy( scrollBar );

    CleanupStack::PopAndDestroy( edwin );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }


TInt CTestSDKEditors::TestEikEdwinSmileyInputL(CStifItemParser& /*aItem*/)
    {
    TInt err = KErrNone;
// this case is only valid when Editor Simley is enabled
#ifdef FF_AVKON_EMOTION_ICON_ENABLED
    TRAP(err, TestEdwinDialog::RunDlgLD(R_BASICGUI_EDWIN_DIALOG));
#endif
    return err;
    }

