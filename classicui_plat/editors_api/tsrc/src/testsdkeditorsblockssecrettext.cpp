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
* Description:  Test EIKSECED.h
*
*/



// [INCLUDE FILES]

#include <eikseced.h>
#include <eikedwin.h>
#include <fbs.h>
#include <barsread.h>
#include <coemain.h>
#include <coeaui.h>
#include <s32mem.h>
#include <gulftflg.hrh>
#include <prnsetup.h>
#include <eikenv.h>
#include <aknsconstants.h>
#include <aknutils.h>
#include <gdi.h>
#include <aknsbasicbackgroundcontrolcontext.h>
#include <testsdkeditors.rsg>

#include "testsdkeditors.h"
#include "testsdkeditorssecrettext.h"

//COSNT
const TInt KLength = 10;

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKEditors::TestSECEikSecretEditorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestSECEikSecretEditorL( CStifItemParser& /*aItem*/ )
    {
    CEikSecretEditor* secretEditor = new (ELeave) CEikSecretEditor;
    CleanupStack::PushL( secretEditor );
    STIF_ASSERT_NOT_NULL( secretEditor );
    
    CleanupStack::PopAndDestroy( secretEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestSEDeconstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestSEDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    CEikSecretEditor* secretEditor = new (ELeave) CEikSecretEditor;
    CleanupStack::PushL( secretEditor );
    STIF_ASSERT_NOT_NULL( secretEditor );
    
    CleanupStack::Pop( secretEditor );
    delete secretEditor;
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestSEConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestSEConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    CEikSecretEditor* secretEditor = new (ELeave) CEikSecretEditor;
    CleanupStack::PushL( secretEditor );
    STIF_ASSERT_NOT_NULL( secretEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_SECRETTEXT );
    secretEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    CleanupStack::PopAndDestroy( secretEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestSEMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestSEMinimumSizeL( CStifItemParser& /*aItem*/ )
    {
    CEikSecretEditor* secretEditor = new (ELeave) CEikSecretEditor;
    CleanupStack::PushL( secretEditor );
    STIF_ASSERT_NOT_NULL( secretEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_SECRETTEXT );
    secretEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    TSize size = secretEditor->MinimumSize();
    STIF_ASSERT_NOT_EQUALS( 0, size.AsPoint().iX );
    STIF_ASSERT_NOT_EQUALS( 0, size.AsPoint().iY );
    
    CleanupStack::PopAndDestroy( secretEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestSEOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestSEOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {
    CEikSecretEditor* secretEditor = new (ELeave) CEikSecretEditor;
    CleanupStack::PushL( secretEditor );
    STIF_ASSERT_NOT_NULL( secretEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_SECRETTEXT );
    secretEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    TKeyEvent keyEvent;
    keyEvent.iCode = EKeyCBA1;
    STIF_ASSERT_TRUE( EKeyWasConsumed == secretEditor->OfferKeyEventL( keyEvent, EEventKey ) );
    
    CleanupStack::PopAndDestroy( secretEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestSEGetColorUseListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestSEGetColorUseListL( CStifItemParser& /*aItem*/ )
    {
    CEikSecretEditor* secretEditor = new (ELeave) CEikSecretEditor;
    CleanupStack::PushL( secretEditor );
    STIF_ASSERT_NOT_NULL( secretEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_SECRETTEXT );
    secretEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    CArrayFix<TCoeColorUse>* colorList = new (ELeave) CArrayFixFlat<TCoeColorUse>(1);
    CleanupStack::PushL(colorList);
    secretEditor->GetColorUseListL( *colorList ); 
    STIF_ASSERT_NOT_NULL( colorList );
    CleanupStack::PopAndDestroy( colorList );
    
    CleanupStack::PopAndDestroy( secretEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestSEHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestSEHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    CEikSecretEditor* secretEditor = new (ELeave) CEikSecretEditor;
    CleanupStack::PushL( secretEditor );
    STIF_ASSERT_NOT_NULL( secretEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_SECRETTEXT );
    secretEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    secretEditor->HandleResourceChange( KAknsMessageSkinChange ); 
    
    CleanupStack::PopAndDestroy( secretEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestSEInputCapabilitiesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestSEInputCapabilitiesL( CStifItemParser& /*aItem*/ )
    {
    CEikSecretEditor* secretEditor = new (ELeave) CEikSecretEditor;
    CleanupStack::PushL( secretEditor );
    STIF_ASSERT_NOT_NULL( secretEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_SECRETTEXT );
    secretEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    TCoeInputCapabilities capa = secretEditor->InputCapabilities(); 
    
    CleanupStack::PopAndDestroy( secretEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestSEHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestSEHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CEikSecretEditor* secretEditor = new (ELeave) CEikSecretEditor;
    CleanupStack::PushL( secretEditor );
    STIF_ASSERT_NOT_NULL( secretEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_SECRETTEXT );
    secretEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    secretEditor->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( secretEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestSEGetTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestSEGetTextL( CStifItemParser& /*aItem*/ )
    {
    CEikSecretEditor* secretEditor = new (ELeave) CEikSecretEditor;
    CleanupStack::PushL( secretEditor );
    STIF_ASSERT_NOT_NULL( secretEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_SECRETTEXT );
    secretEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    _LIT( KText, "Text" );
    TFileName text( KText );
    secretEditor->SetText( text );
    
    TFileName textGet;
    secretEditor->GetText( textGet );
    
    STIF_ASSERT_EQUALS( 0, textGet.Compare( text ) );
    
    CleanupStack::PopAndDestroy( secretEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestSESetTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestSESetTextL( CStifItemParser& aItem )
    {
    return TestSEGetTextL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestSEInitializeDisplayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestSEInitializeDisplayL( CStifItemParser& /*aItem*/ )
    {
    CEikSecretEditor* secretEditor = new (ELeave) CEikSecretEditor;
    CleanupStack::PushL( secretEditor );
    STIF_ASSERT_NOT_NULL( secretEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_SECRETTEXT );
    secretEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    _LIT( KText, "Text" );
    TFileName text( KText );
    secretEditor->SetText( text );
    
    secretEditor->InitializeDisplay( 1 );
    
    CleanupStack::PopAndDestroy( secretEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestSEResetL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestSEResetL( CStifItemParser& /*aItem*/ )
    {
    CEikSecretEditor* secretEditor = new (ELeave) CEikSecretEditor;
    CleanupStack::PushL( secretEditor );
    STIF_ASSERT_NOT_NULL( secretEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_SECRETTEXT );
    secretEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    _LIT( KText, "Text" );
    TFileName text( KText );
    secretEditor->SetText( text );
    
    secretEditor->Reset();
    
    TFileName textGet;
    secretEditor->GetText( textGet );
    
    STIF_ASSERT_EQUALS( 0, textGet.Length() );
    
    CleanupStack::PopAndDestroy( secretEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestSESetMaxLengthL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestSESetMaxLengthL( CStifItemParser& /*aItem*/ )
    {
    CEikSecretEditor* secretEditor = new (ELeave) CEikSecretEditor;
    CleanupStack::PushL( secretEditor );
    STIF_ASSERT_NOT_NULL( secretEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_SECRETTEXT );
    secretEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    secretEditor->SetMaxLength( KLength );
    STIF_ASSERT_EQUALS( KLength, secretEditor->MaxLength() );
    
    CleanupStack::PopAndDestroy( secretEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestSEAknSetFontL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestSEAknSetFontL( CStifItemParser& /*aItem*/ )
    {
    CEikSecretEditor* secretEditor = new (ELeave) CEikSecretEditor;
    CleanupStack::PushL( secretEditor );
    STIF_ASSERT_NOT_NULL( secretEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_SECRETTEXT );
    secretEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    const CFont* font = ivEikonEnv->LegendFont();
    secretEditor->AknSetFont( *font );
    
    CleanupStack::PopAndDestroy( secretEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestSEAknSetAlignmentL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestSEAknSetAlignmentL( CStifItemParser& /*aItem*/ )
    {
    CEikSecretEditor* secretEditor = new (ELeave) CEikSecretEditor;
    CleanupStack::PushL( secretEditor );
    STIF_ASSERT_NOT_NULL( secretEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_SECRETTEXT );
    secretEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    secretEditor->AknSetAlignment( CGraphicsContext::ELeft );
    
    CleanupStack::PopAndDestroy( secretEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestSESetDefaultInputModeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestSESetDefaultInputModeL( CStifItemParser& /*aItem*/ )
    {
    CEikSecretEditor* secretEditor = new (ELeave) CEikSecretEditor;
    CleanupStack::PushL( secretEditor );
    STIF_ASSERT_NOT_NULL( secretEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_SECRETTEXT );
    secretEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    secretEditor->SetDefaultInputMode( EAknEditorNumericInputMode );
    
    CleanupStack::PopAndDestroy( secretEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestSEMaxLengthL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestSEMaxLengthL( CStifItemParser& aItem )
    {
    return TestSESetMaxLengthL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestSEBufferL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestSEBufferL( CStifItemParser& /*aItem*/ )
    {
    CEikSecretEditor* secretEditor = new (ELeave) CEikSecretEditor;
    CleanupStack::PushL( secretEditor );
    STIF_ASSERT_NOT_NULL( secretEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_SECRETTEXT );
    secretEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    TBufC<KLength> buffer = secretEditor->Buffer();
    STIF_ASSERT_EQUALS( 0, buffer.Length() );
    
    CleanupStack::PopAndDestroy( secretEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestSERevealSecretTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestSERevealSecretTextL( CStifItemParser& /*aItem*/ )
    {
    CEikSecretEditor* secretEditor = new (ELeave) CEikSecretEditor;
    CleanupStack::PushL( secretEditor );
    STIF_ASSERT_NOT_NULL( secretEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_SECRETTEXT );
    secretEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    secretEditor->RevealSecretText( ETrue );
    
    CleanupStack::PopAndDestroy( secretEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestSEEnableSCTL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestSEEnableSCTL( CStifItemParser& /*aItem*/ )
    {
    CEikSecretEditor* secretEditor = new (ELeave) CEikSecretEditor;
    CleanupStack::PushL( secretEditor );
    STIF_ASSERT_NOT_NULL( secretEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_SECRETTEXT );
    secretEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    secretEditor->EnableSCT();
    
    CleanupStack::PopAndDestroy( secretEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestSESetSkinBackgroundControlContextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestSESetSkinBackgroundControlContextL( CStifItemParser& /*aItem*/ )
    {
    CEikSecretEditor* secretEditor = new (ELeave) CEikSecretEditor;
    CleanupStack::PushL( secretEditor );
    STIF_ASSERT_NOT_NULL( secretEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_SECRETTEXT );
    secretEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    TAknsItemID itemId;
    TRect rect( 0, 0, KLength, KLength );
    CAknsBasicBackgroundControlContext* context = CAknsBasicBackgroundControlContext::NewL( itemId, rect, ETrue );
    CleanupStack::PushL( context );
    
    secretEditor->SetSkinBackgroundControlContextL( context );
    
    CleanupStack::PopAndDestroy( context );
    CleanupStack::PopAndDestroy( secretEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestSEAppendCharacterL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestSEAppendCharacterL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKEditorsSecretText* secretEditor = new (ELeave) CTestSDKEditorsSecretText;
    CleanupStack::PushL( secretEditor );
    STIF_ASSERT_NOT_NULL( secretEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_SECRETTEXT );
    secretEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    secretEditor->AppendCharacterL( 'TEXT' );
    
    CleanupStack::PopAndDestroy( secretEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestSEUpdateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestSEUpdateL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKEditorsSecretText* secretEditor = new (ELeave) CTestSDKEditorsSecretText;
    CleanupStack::PushL( secretEditor );
    STIF_ASSERT_NOT_NULL( secretEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_SECRETTEXT );
    secretEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    secretEditor->Update();
    
    CleanupStack::PopAndDestroy( secretEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestSESizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestSESizeChangedL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKEditorsSecretText* secretEditor = new (ELeave) CTestSDKEditorsSecretText;
    CleanupStack::PushL( secretEditor );
    STIF_ASSERT_NOT_NULL( secretEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_SECRETTEXT );
    secretEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    secretEditor->SizeChanged();
    
    CleanupStack::PopAndDestroy( secretEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestSESetSkinTextColorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestSESetSkinTextColorL( CStifItemParser& /*aItem*/ )
    {
    CEikSecretEditor* secretEditor = new (ELeave) CEikSecretEditor;
    CleanupStack::PushL( secretEditor );
    STIF_ASSERT_NOT_NULL( secretEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_SECRETTEXT );
    secretEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    secretEditor->SetSkinTextColorL( 1 );

    CleanupStack::PopAndDestroy( secretEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestSESetFeatureL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestSESetFeatureL( CStifItemParser& /*aItem*/ )
    {
    CEikSecretEditor* secretEditor = new (ELeave) CEikSecretEditor;
    CleanupStack::PushL( secretEditor );
    STIF_ASSERT_NOT_NULL( secretEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_SECRETTEXT );
    secretEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    secretEditor->SetFeature( CEikSecretEditor::EDisablePenInput, CEikSecretEditor::EDisablePenInput );
    TInt para;
    secretEditor->GetFeature( CEikSecretEditor::EDisablePenInput, para );
    STIF_ASSERT_TRUE( para == CEikSecretEditor::EDisablePenInput );

    CleanupStack::PopAndDestroy( secretEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestSEGetFeatureL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestSEGetFeatureL( CStifItemParser& aItem )
    {
    return TestSESetFeatureL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestSESupportsFeatureL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestSESupportsFeatureL( CStifItemParser& /*aItem*/ )
    {
    CEikSecretEditor* secretEditor = new (ELeave) CEikSecretEditor;
    CleanupStack::PushL( secretEditor );
    STIF_ASSERT_NOT_NULL( secretEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_SECRETTEXT );
    secretEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    STIF_ASSERT_TRUE( secretEditor->SupportsFeature( CEikSecretEditor::EDisablePenInput ) );

    CleanupStack::PopAndDestroy( secretEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestSEFocusChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestSEFocusChangedL( CStifItemParser& /*aItem*/ )
    {
    CEikSecretEditor* secretEditor = new ( ELeave ) CEikSecretEditor;
    CleanupStack::PushL( secretEditor );
    STIF_ASSERT_NOT_NULL( secretEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_SECRETTEXT );
    secretEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    secretEditor->FocusChanged( ENoDrawNow );

    CleanupStack::PopAndDestroy( secretEditor );
    
    return KErrNone;
    }

// [End of file]
