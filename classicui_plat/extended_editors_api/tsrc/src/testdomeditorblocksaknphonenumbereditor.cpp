/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test aknphonenumbereditor.h
*
*/



#include <aknphonenumbereditor.h>
#include <barsread.h>
#include <eiksbfrm.h>
#include <frmtlay.h>
#include <testdomeditor.rsg>

#include "testdomeditor.h"
#include "testdomeditorcontainer.h"

// CONSTANTS
const TInt KMaxChars = 30;
const TInt KMaxLines = 3;
const TInt KMaxFormats = 3;
_LIT( KTruncation, "..." );
const TInt KOuterRectAx = 10;
const TInt KOuterRectAy = 10;
const TInt KOuterRectBx = 70;
const TInt KOuterRectBy = 55;
const TInt KBorderType = 0;
const TInt KNumLines = 3;
const TInt KBottomBaselineOffset = 3;
const TInt KBaselineSeparation = 15;
const TInt KBufSize = 32;


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestTForamtDefConsWithNoParam
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestTForamtDefConsWithNoParam( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestTForamtDefConsWithNoParam, "In TForamtDefConsWithNoParam" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestTForamtDefConsWithNoParam );
    // Print to log file
    iLog->Log( KTestTForamtDefConsWithNoParam );

    CAknPhoneNumberEditor::TFormat format( CAknPhoneNumberEditor::TFormat() );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestTForamtDefConsWithRes
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestTForamtDefConsWithResL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestTForamtDefConsWithRes, "In TForamtDefConsWithRes" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestTForamtDefConsWithRes );
    // Print to log file
    iLog->Log( KTestTForamtDefConsWithRes );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    CAknPhoneNumberEditor::TFormat format( CAknPhoneNumberEditor::TFormat( reader ) );

    CleanupStack::PopAndDestroy();
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestTForamtDefConsWithFont
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestTForamtDefConsWithFont( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestTForamtDefConsWithFont, "In TForamtDefConsWithFont" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestTForamtDefConsWithFont );
    // Print to log file
    iLog->Log( KTestTForamtDefConsWithFont );

    TRect outerRect( KOuterRectAx, KOuterRectAy, KOuterRectBx, KOuterRectBy );
    const CFont* font = CCoeEnv::Static()->NormalFont();
    CAknPhoneNumberEditor::TFormat format( CAknPhoneNumberEditor::TFormat(
            outerRect, KBorderType, KNumLines, KBottomBaselineOffset,
            KBaselineSeparation, font ) );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorDefConsL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorDefConsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorDefCons, "In EditorDefCons" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorDefCons );
    // Print to log file
    iLog->Log( KTestEditorDefCons );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    STIF_ASSERT_NOT_NULL( phoneNumEditor );

    CleanupStack::Pop( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorConstructL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorConstructL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorConstructL, "In EditorConstructL" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorConstructL );
    // Print to log file
    iLog->Log( KTestEditorConstructL );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    phoneNumEditor->ConstructL( KMaxChars, KMaxLines, KMaxFormats, KTruncation );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorConstructFromResourceL, "In EditorConstructFromResourceL" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorConstructFromResourceL );
    // Print to log file
    iLog->Log( KTestEditorConstructFromResourceL );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );

    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorAddFormatL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorAddFormatL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorAddFormat, "In EditorAddFormat" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorAddFormat );
    // Print to log file
    iLog->Log( KTestEditorAddFormat );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );
    phoneNumEditor->ConstructL( KMaxChars, KMaxLines, KMaxFormats, KTruncation );

    TRect outerRect( KOuterRectAx, KOuterRectAy, KOuterRectBx, KOuterRectBy );
    const CFont* font = CCoeEnv::Static()->NormalFont();
    CAknPhoneNumberEditor::TFormat format( CAknPhoneNumberEditor::TFormat(
            outerRect, KBorderType, KNumLines, KBottomBaselineOffset,
            KBaselineSeparation, font ) );
    phoneNumEditor->AddFormat( format );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorCountFormatsL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorCountFormatsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorCountFormats, "In EditorCountFormats" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorCountFormats );
    // Print to log file
    iLog->Log( KTestEditorCountFormats );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    TInt formats = phoneNumEditor->CountFormats();
    STIF_ASSERT_EQUALS( 1, formats );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorFormatL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorFormatL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorFormat, "In EditorFormat" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorFormat );
    // Print to log file
    iLog->Log( KTestEditorFormat );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );
    phoneNumEditor->ConstructL( KMaxChars, KMaxLines, KMaxFormats, KTruncation );

    TRect outerRect( KOuterRectAx, KOuterRectAy, KOuterRectBx, KOuterRectBy );
    const CFont* font = CCoeEnv::Static()->NormalFont();
    CAknPhoneNumberEditor::TFormat format( CAknPhoneNumberEditor::TFormat(
            outerRect, KBorderType, KNumLines, KBottomBaselineOffset,
            KBaselineSeparation, font ) );
    phoneNumEditor->AddFormat( format );

    CAknPhoneNumberEditor::TFormat editorFormat = phoneNumEditor->Format( 0 );
    STIF_ASSERT_EQUALS( format.iOuterRect, editorFormat.iOuterRect );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorCurrentFormatIndexL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorCurrentFormatIndexL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorCurrentFormatIndex, "In EditorCurrentFormatIndex" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorCurrentFormatIndex );
    // Print to log file
    iLog->Log( KTestEditorCurrentFormatIndex );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    TInt currentIndex = phoneNumEditor->CurrentFormatIndex();
    STIF_ASSERT_EQUALS( 0, currentIndex );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorWouldTextFitInFormatL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorWouldTextFitInFormatL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorWouldTextFitInFormat, "In EditorWouldTextFitInFormat" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorWouldTextFitInFormat );
    // Print to log file
    iLog->Log( KTestEditorWouldTextFitInFormat );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    TBool testFit = phoneNumEditor->WouldTextFitInFormat( 0 );
    STIF_ASSERT_TRUE( testFit );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorSetFormatL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorSetFormatL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorSetFormat, "In EditorSetFormat" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorSetFormat );
    // Print to log file
    iLog->Log( KTestEditorSetFormat );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    phoneNumEditor->SetFormat( 0 );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorTextL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorTextL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorText, "In EditorText" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorText );
    // Print to log file
    iLog->Log( KTestEditorText );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    TPtrC text = phoneNumEditor->Text();
    TInt len = text.Length();
    STIF_ASSERT_EQUALS( 0, len );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorSetTextL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorSetTextL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorSetText, "In EditorSetText" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorSetText );
    // Print to log file
    iLog->Log( KTestEditorSetText );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    _LIT( KText, "text" );
    phoneNumEditor->SetText( KText );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorSizeChangedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorSizeChanged, "In EditorSizeChanged" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorSizeChanged );
    // Print to log file
    iLog->Log( KTestEditorSizeChanged );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    phoneNumEditor->SizeChanged();

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorOfferKeyEventL, "In EditorOfferKeyEventL" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorOfferKeyEventL );
    // Print to log file
    iLog->Log( KTestEditorOfferKeyEventL );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    TKeyEvent keyEvent;
    keyEvent.iScanCode = EStdKeyEnter;
    TKeyResponse keyResponse = phoneNumEditor->OfferKeyEventL( keyEvent, EEventKey );
    STIF_ASSERT_TRUE( keyResponse == EKeyWasNotConsumed );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorMinimumSizeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorMinimumSize, "In EditorMinimumSize" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorMinimumSize );
    // Print to log file
    iLog->Log( KTestEditorMinimumSize );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    TSize size( phoneNumEditor->MinimumSize() );
    STIF_ASSERT_TRUE( ( size.iWidth >= 0 ) && ( size.iHeight >= 0 ) );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorFocusChangedL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorFocusChangedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorFocusChanged, "In EditorFocusChanged" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorFocusChanged );
    // Print to log file
    iLog->Log( KTestEditorFocusChanged );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    phoneNumEditor->FocusChanged( EDrawNow );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorDrawL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorDrawL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorDraw, "In EditorDraw" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorDraw );
    // Print to log file
    iLog->Log( KTestEditorDraw );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    // Draw() function will be called.
    phoneNumEditor->FocusChanged( EDrawNow );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorInputCapabilitiesL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorInputCapabilitiesL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorInputCapabilities, "In EditorInputCapabilities" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorInputCapabilities );
    // Print to log file
    iLog->Log( KTestEditorInputCapabilities );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    TCoeInputCapabilities inputCapabilities ( phoneNumEditor->InputCapabilities() );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorTextLengthL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorTextLengthL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorTextLength, "In EditorTextLength" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorTextLength );
    // Print to log file
    iLog->Log( KTestEditorTextLength );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    TInt textLength = phoneNumEditor->TextLength();
    STIF_ASSERT_EQUALS( 0, textLength );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorCursorPosL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorCursorPosL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorCursorPos, "In EditorCursorPos" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorCursorPos );
    // Print to log file
    iLog->Log( KTestEditorCursorPos );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    TInt cursorPos = phoneNumEditor->CursorPos();
    STIF_ASSERT_EQUALS( 0, cursorPos );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorSelectionLengthL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorSelectionLengthL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorSelectionLength, "In EditorSelectionLength" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorSelectionLength );
    // Print to log file
    iLog->Log( KTestEditorSelectionLength );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    TInt selectionLength = phoneNumEditor->SelectionLength();
    STIF_ASSERT_EQUALS( 0, selectionLength );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorSelectionL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorSelectionL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorSelection, "In EditorSelection" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorSelection );
    // Print to log file
    iLog->Log( KTestEditorSelection );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    TCursorSelection selection ( phoneNumEditor->Selection() );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorClearSelectionL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorClearSelectionL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorClearSelectionL, "In EditorClearSelectionL" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorClearSelectionL );
    // Print to log file
    iLog->Log( KTestEditorClearSelectionL );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    phoneNumEditor->ClearSelectionL();

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorSetSelectionL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorSetSelectionL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorSetSelectionL, "In EditorSetSelectionL" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorSetSelectionL );
    // Print to log file
    iLog->Log( KTestEditorSetSelectionL );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    phoneNumEditor->SetSelectionL( 0, 0 );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorSetCursorPosL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorSetCursorPosL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorSetCursorPosL, "In EditorSetCursorPosL" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorSetCursorPosL );
    // Print to log file
    iLog->Log( KTestEditorSetCursorPosL );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    phoneNumEditor->SetCursorPosL( 0, ETrue );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorSelectAllL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorSelectAllL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorSelectAllL, "In EditorSelectAllL" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorSelectAllL );
    // Print to log file
    iLog->Log( KTestEditorSelectAllL );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    phoneNumEditor->SelectAllL();

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorGetTextL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorGetTextL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorGetText, "In EditorGetText" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorGetText );
    // Print to log file
    iLog->Log( KTestEditorGetText );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    TBuf<KBufSize> text;
    phoneNumEditor->GetText( text );
    TInt length = text.Length();
    STIF_ASSERT_EQUALS( 0, length );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorGetTextInHBufL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorGetTextInHBufL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorGetTextInHBufL, "In EditorGetTextInHBufL" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorGetTextInHBufL );
    // Print to log file
    iLog->Log( KTestEditorGetTextInHBufL );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    HBufC* text = phoneNumEditor->GetTextInHBufL();
    CleanupStack::PushL( text );
    TInt length = text->Length();
    STIF_ASSERT_EQUALS( 0, length );

    CleanupStack::PopAndDestroy( text );
    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorSetTextWithPoiL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorSetTextWithPoiL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorSetTextL, "In EditorSetTextL" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorSetTextL );
    // Print to log file
    iLog->Log( KTestEditorSetTextL );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    _LIT( KText, "text" );
    TBuf<KBufSize> text( KText );
    phoneNumEditor->SetTextL( &text );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorCancelFepTransactionL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorCancelFepTransactionL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorCancelFepTransaction, "In EditorCancelFepTransaction" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorCancelFepTransaction );
    // Print to log file
    iLog->Log( KTestEditorCancelFepTransaction );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    phoneNumEditor->CancelFepTransaction();

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorUpdateScrollBarsL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorUpdateScrollBarsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorUpdateScrollBarsL, "In EditorUpdateScrollBarsL" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorUpdateScrollBarsL );
    // Print to log file
    iLog->Log( KTestEditorUpdateScrollBarsL );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    phoneNumEditor->UpdateScrollBarsL();

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorCreateScrollBarFrameL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorCreateScrollBarFrameL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorCreateScrollBarFrameL, "In EditorCreateScrollBarFrameL" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorCreateScrollBarFrameL );
    // Print to log file
    iLog->Log( KTestEditorCreateScrollBarFrameL );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    CEikScrollBarFrame* sbFrame = phoneNumEditor->CreateScrollBarFrameL();
    CleanupStack::PushL( sbFrame );
    STIF_ASSERT_NULL( sbFrame );

    CleanupStack::PopAndDestroy( sbFrame );
    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorScrollBarFrameL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorScrollBarFrameL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorScrollBarFrame, "In EditorScrollBarFrame" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorScrollBarFrame );
    // Print to log file
    iLog->Log( KTestEditorScrollBarFrame );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    CEikScrollBarFrame* sbFrame = phoneNumEditor->ScrollBarFrame();
    STIF_ASSERT_NULL( sbFrame );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorLineCursorWidthL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorLineCursorWidthL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorLineCursorWidth, "In EditorLineCursorWidth" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorLineCursorWidth );
    // Print to log file
    iLog->Log( KTestEditorLineCursorWidth );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    TInt lineCursorWidth = phoneNumEditor->LineCursorWidth();
    STIF_ASSERT_EQUALS( 0, lineCursorWidth );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorMarginsL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorMarginsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorMargins, "In EditorMargins" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorMargins );
    // Print to log file
    iLog->Log( KTestEditorMargins );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    TMargins8 margins = phoneNumEditor->Margins();
    TInt left = margins.iLeft;
    STIF_ASSERT_EQUALS( 0, left );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorChangeEditorModeL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorChangeEditorModeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorChangeEditorMode, "In EditorChangeEditorMode" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorChangeEditorMode );
    // Print to log file
    iLog->Log( KTestEditorChangeEditorMode );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    TInt code = 1;
    TInt mode = phoneNumEditor->ChangeEditorMode();
    STIF_ASSERT_EQUALS( code, mode );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorGetEditorModeL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorGetEditorModeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorGetEditorMode, "In EditorGetEditorMode" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorGetEditorMode );
    // Print to log file
    iLog->Log( KTestEditorGetEditorMode );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    TInt mode = phoneNumEditor->GetEditorMode();
    STIF_ASSERT_EQUALS( 2, mode );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorResetEditorToDefaultValuesL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorResetEditorToDefaultValuesL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorResetEditorToDefaultValues, "In EditorResetEditorToDefaultValues" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorResetEditorToDefaultValues );
    // Print to log file
    iLog->Log( KTestEditorResetEditorToDefaultValues );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    phoneNumEditor->ResetEditorToDefaultValues();

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorHandlePointerEventL, "In EditorHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorHandlePointerEventL );
    // Print to log file
    iLog->Log( KTestEditorHandlePointerEventL );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( KOuterRectAx, KOuterRectAy );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;

    phoneNumEditor->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorCcpuIsFocusedL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorCcpuIsFocusedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorCcpuIsFocused, "In EditorCcpuIsFocused" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorCcpuIsFocused );
    // Print to log file
    iLog->Log( KTestEditorCcpuIsFocused );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    TBool isFocused = phoneNumEditor->CcpuIsFocused();
    STIF_ASSERT_FALSE( isFocused );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorCcpuCanCutL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorCcpuCanCutL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorCcpuCanCut, "In EditorCcpuCanCut" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorCcpuCanCut );
    // Print to log file
    iLog->Log( KTestEditorCcpuCanCut );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    TBool canCut = phoneNumEditor->CcpuCanCut();
    STIF_ASSERT_FALSE( canCut );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorCcpuCutL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorCcpuCutL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorCcpuCutL, "In EditorCcpuCutL" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorCcpuCutL );
    // Print to log file
    iLog->Log( KTestEditorCcpuCutL );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    phoneNumEditor->CcpuCutL();

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorCcpuCanCopyL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorCcpuCanCopyL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorCcpuCanCopy, "In EditorCcpuCanCopy" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorCcpuCanCopy );
    // Print to log file
    iLog->Log( KTestEditorCcpuCanCopy );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    TBool canCopy = phoneNumEditor->CcpuCanCopy();
    STIF_ASSERT_FALSE( canCopy );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorCcpuCopyL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorCcpuCopyL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorCcpuCopyL, "In EditorCcpuCopyL" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorCcpuCopyL );
    // Print to log file
    iLog->Log( KTestEditorCcpuCopyL );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    phoneNumEditor->CcpuCopyL();

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorCcpuCanPasteL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorCcpuCanPasteL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorCcpuCanPaste, "In EditorCcpuCanPaste" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorCcpuCanPaste );
    // Print to log file
    iLog->Log( KTestEditorCcpuCanPaste );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    TBool canPaste = phoneNumEditor->CcpuCanPaste();
    STIF_ASSERT_FALSE( canPaste );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorCcpuPasteL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorCcpuPasteL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorCcpuPasteL, "In EditorCcpuPasteL" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorCcpuPasteL );
    // Print to log file
    iLog->Log( KTestEditorCcpuPasteL );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    phoneNumEditor->CcpuPasteL();

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorCcpuCanUndoL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorCcpuCanUndoL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorCcpuCanUndo, "In EditorCcpuCanUndo" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorCcpuCanUndo );
    // Print to log file
    iLog->Log( KTestEditorCcpuCanUndo );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    TBool canUndo = phoneNumEditor->CcpuCanUndo();
    STIF_ASSERT_FALSE( canUndo );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorCcpuUndoL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorCcpuUndoL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorCcpuUndoL, "In EditorCcpuUndoL" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorCcpuUndoL );
    // Print to log file
    iLog->Log( KTestEditorCcpuUndoL );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    phoneNumEditor->CcpuUndoL();

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMEditor::TestEditorOpenVKBL
// -----------------------------------------------------------------------------
//
TInt CTestDOMEditor::TestEditorOpenVKBL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMEditor, "testdomeditor" );
    _LIT( KTestEditorOpenVKB, "In EditorOpenVKB" );
    TestModuleIf().Printf( 0, KTestDOMEditor, KTestEditorOpenVKB );
    // Print to log file
    iLog->Log( KTestEditorOpenVKB );

    CAknPhoneNumberEditor* phoneNumEditor = new ( ELeave ) CAknPhoneNumberEditor;
    CleanupStack::PushL( phoneNumEditor );
    CTestDOMEditorContainer* container = CTestDOMEditorContainer::NewL();
    CleanupStack::PushL( container );
    phoneNumEditor->SetContainerWindowL( *container );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader , R_PHONENUM_EDITOR );
    phoneNumEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    phoneNumEditor->OpenVKB();

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( phoneNumEditor );
    return KErrNone;

    }


