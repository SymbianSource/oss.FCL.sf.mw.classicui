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
* Description:  Test EIKGTED.h
*
*/



// [INCLUDE FILES]

#include <eikgted.h>
#include <eikedwin.h>
#include <fbs.h>
#include <barsread.h>
#include <coemain.h>
#include <coeaui.h>
#include <s32mem.h>
#include <gulftflg.hrh>
#include <prnsetup.h>
#include <eikenv.h>
#include <testsdkeditors.rsg>

#include "testsdkeditors.h"
#include "testsdkeditorscontrol.h"
#include "testsdkeditorsglobaltext.h"
#include "testsdkeditorsdialogfactory.h"

const TInt KLimit = 20;

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKEditors::TestGETCEikGlobalTextEditorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestGETCEikGlobalTextEditorL( CStifItemParser& /*aItem*/ )
    {
    CEikGlobalTextEditor* globalEditor = new (ELeave) CEikGlobalTextEditor;
    CleanupStack::PushL( globalEditor );
    STIF_ASSERT_NOT_NULL( globalEditor );
    
    CleanupStack::PopAndDestroy( globalEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestGETCEikGlobalTextEditorPL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestGETCEikGlobalTextEditorPL( CStifItemParser& /*aItem*/ )
    {
    TGulBorder gulBorder;
    CEikGlobalTextEditor* globalEditor = new (ELeave) CEikGlobalTextEditor( gulBorder );
    CleanupStack::PushL( globalEditor );
    STIF_ASSERT_NOT_NULL( globalEditor );
    
    CleanupStack::PopAndDestroy( globalEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestGETDeconstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestGETDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    CEikGlobalTextEditor* globalEditor = new (ELeave) CEikGlobalTextEditor;
    CleanupStack::PushL( globalEditor );
    STIF_ASSERT_NOT_NULL( globalEditor );
    
    CleanupStack::Pop( globalEditor );
    delete globalEditor;
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestGETConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestGETConstructL( CStifItemParser& /*aItem*/ )
    {
    CEikGlobalTextEditor* globalEditor = new (ELeave) CEikGlobalTextEditor;
    CleanupStack::PushL( globalEditor );
    STIF_ASSERT_NOT_NULL( globalEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    globalEditor->ConstructL( control, 1, KLimit, CEikEdwin::ENoAutoSelection, 0, 0 );
    
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( globalEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestGETSetButtonGroupL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestGETSetButtonGroupL( CStifItemParser& /*aItem*/ )
    {
    CEikGlobalTextEditor* globalEditor = new (ELeave) CEikGlobalTextEditor;
    CleanupStack::PushL( globalEditor );
    STIF_ASSERT_NOT_NULL( globalEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    globalEditor->ConstructL( control, 1, KLimit, CEikEdwin::EZeroEnumValue, 
                              EGulFontControlAll, EGulAllFonts );
    
    globalEditor->SetButtonGroup( control );
    
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( globalEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestGETSetLineCursorBitmapL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestGETSetLineCursorBitmapL( CStifItemParser& /*aItem*/ )
    {
    CEikGlobalTextEditor* globalEditor = new (ELeave) CEikGlobalTextEditor;
    CleanupStack::PushL( globalEditor );
    STIF_ASSERT_NOT_NULL( globalEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    globalEditor->ConstructL( control, 1, KLimit, CEikEdwin::EZeroEnumValue, 
                              EGulFontControlAll, EGulAllFonts );
    
    CFbsBitmap* bitmap = new (ELeave) CFbsBitmap;
    CleanupStack::PushL( bitmap );
    globalEditor->SetLineCursorBitmapL( bitmap );
    
    CleanupStack::PopAndDestroy( bitmap );
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( globalEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestGETRunFontDialogL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestGETRunFontDialogL( CStifItemParser& /*aItem*/ )
    {
    CEikGlobalTextEditor* globalEditor = new (ELeave) CEikGlobalTextEditor;
    CleanupStack::PushL( globalEditor );
    STIF_ASSERT_NOT_NULL( globalEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    globalEditor->ConstructL( control, 1, KLimit, CEikEdwin::ENoAutoSelection, 0, 0 );
    
    globalEditor->SetContainerWindowL( *control );
    globalEditor->CreateTextViewL();
    
    _LIT( KText, "Text" );
    TFileName text( KText );
    globalEditor->SetTextL( &text );
    
    CTestSDKEditorsDialogFactory* factory = new (ELeave) CTestSDKEditorsDialogFactory;
    CleanupStack::PushL( factory );
    ivEikonEnv->SetCDlgDialogFactory( factory );
    ivEikonEnv->SetPrintDialogFactory( factory );
    
    globalEditor->RunFontDialogL( 0x10, 0, 0x001 );
    
    CleanupStack::PopAndDestroy( factory );
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( globalEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestGETRunTabsDialogL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestGETRunTabsDialogL( CStifItemParser& /*aItem*/ )
    {
    CEikGlobalTextEditor* globalEditor = new (ELeave) CEikGlobalTextEditor;
    CleanupStack::PushL( globalEditor );
    STIF_ASSERT_NOT_NULL( globalEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    globalEditor->ConstructL( control, 1, KLimit, CEikEdwin::ENoAutoSelection, 0, 0 );
    
    globalEditor->SetContainerWindowL( *control );
    globalEditor->CreateTextViewL();
    
    _LIT( KText, "Text" );
    TFileName text( KText );
    globalEditor->SetTextL( &text );
    
    CTestSDKEditorsDialogFactory* factory = new (ELeave) CTestSDKEditorsDialogFactory;
    CleanupStack::PushL( factory );
    ivEikonEnv->SetCDlgDialogFactory( factory );
    ivEikonEnv->SetPrintDialogFactory( factory );
    
    const TInt pageWidth = 100;
    globalEditor->RunTabsDialogL( pageWidth );
    
    CleanupStack::PopAndDestroy( factory );
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( globalEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestGETRunIndentsDialogL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestGETRunIndentsDialogL( CStifItemParser& /*aItem*/ )
    {
    CEikGlobalTextEditor* globalEditor = new (ELeave) CEikGlobalTextEditor;
    CleanupStack::PushL( globalEditor );
    STIF_ASSERT_NOT_NULL( globalEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    globalEditor->ConstructL( control, 1, KLimit, CEikEdwin::ENoAutoSelection, 0, 0 );
    
    globalEditor->SetContainerWindowL( *control );
    globalEditor->CreateTextViewL();
    
    _LIT( KText, "Text" );
    TFileName text( KText );
    globalEditor->SetTextL( &text );
    
    CTestSDKEditorsDialogFactory* factory = new (ELeave) CTestSDKEditorsDialogFactory;
    CleanupStack::PushL( factory );
    ivEikonEnv->SetCDlgDialogFactory( factory );
    ivEikonEnv->SetPrintDialogFactory( factory );
    
    const TInt pageWidth = 100;
    globalEditor->RunIndentsDialogL( pageWidth );
    
    CleanupStack::PopAndDestroy( factory );
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( globalEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestGETSetGraphicsDeviceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestGETSetGraphicsDeviceL( CStifItemParser& /*aItem*/ )
    {
    CEikGlobalTextEditor* globalEditor = new (ELeave) CEikGlobalTextEditor;
    CleanupStack::PushL( globalEditor );
    STIF_ASSERT_NOT_NULL( globalEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    globalEditor->ConstructL( control, 1, KLimit, CEikEdwin::EZeroEnumValue, 
                              EGulFontControlAll, EGulAllFonts );
    
    CGraphicsDevice* device = CCoeEnv::Static()->ScreenDevice();
    globalEditor->SetGraphicsDevice( device );

    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( globalEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestGETRunFindDialogL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestGETRunFindDialogL( CStifItemParser& /*aItem*/ )
    {
    CEikGlobalTextEditor* globalEditor = new (ELeave) CEikGlobalTextEditor;
    CleanupStack::PushL( globalEditor );
    STIF_ASSERT_NOT_NULL( globalEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    globalEditor->ConstructL( control, 1, KLimit, CEikEdwin::ENoAutoSelection, 0, 0 );
    
    globalEditor->SetContainerWindowL( *control );
    globalEditor->CreateTextViewL();
    
    _LIT( KText, "Text" );
    TFileName text( KText );
    globalEditor->SetTextL( &text );
    
    CTestSDKEditorsDialogFactory* factory = new (ELeave) CTestSDKEditorsDialogFactory;
    CleanupStack::PushL( factory );
    ivEikonEnv->SetCDlgDialogFactory( factory );
    ivEikonEnv->SetPrintDialogFactory( factory );
    
    globalEditor->RunFindDialogL();
    
    CleanupStack::PopAndDestroy( factory );
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( globalEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestGETRunFindAgainDialogL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestGETRunFindAgainDialogL( CStifItemParser& /*aItem*/ )
    {
    CEikGlobalTextEditor* globalEditor = new (ELeave) CEikGlobalTextEditor;
    CleanupStack::PushL( globalEditor );
    STIF_ASSERT_NOT_NULL( globalEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    globalEditor->ConstructL( control, 1, KLimit, CEikEdwin::ENoAutoSelection, 0, 0 );
    
    globalEditor->SetContainerWindowL( *control );
    globalEditor->CreateTextViewL();
    
    _LIT( KText, "Text" );
    TFileName text( KText );
    globalEditor->SetTextL( &text );
    
    CTestSDKEditorsDialogFactory* factory = new (ELeave) CTestSDKEditorsDialogFactory;
    CleanupStack::PushL( factory );
    ivEikonEnv->SetCDlgDialogFactory( factory );
    ivEikonEnv->SetPrintDialogFactory( factory );
    
    globalEditor->RunFindAgainDialogL();
    
    CleanupStack::PopAndDestroy( factory );
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( globalEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestGETRunReplaceDialogL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestGETRunReplaceDialogL( CStifItemParser& /*aItem*/ )
    {
    CEikGlobalTextEditor* globalEditor = new (ELeave) CEikGlobalTextEditor;
    CleanupStack::PushL( globalEditor );
    STIF_ASSERT_NOT_NULL( globalEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    globalEditor->ConstructL( control, 1, KLimit, CEikEdwin::ENoAutoSelection, 0, 0 );
    
    globalEditor->SetContainerWindowL( *control );
    globalEditor->CreateTextViewL();
    
    _LIT( KText, "Text" );
    TFileName text( KText );
    globalEditor->SetTextL( &text );
    
    CTestSDKEditorsDialogFactory* factory = new (ELeave) CTestSDKEditorsDialogFactory;
    CleanupStack::PushL( factory );
    ivEikonEnv->SetCDlgDialogFactory( factory );
    ivEikonEnv->SetPrintDialogFactory( factory );
    
    globalEditor->RunReplaceDialogL();
    
    CleanupStack::PopAndDestroy( factory );
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( globalEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestGETInitFindL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestGETInitFindL( CStifItemParser& aItem )
    {
    return TestGETDoFindL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestGETDoFindL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestGETDoFindL( CStifItemParser& /*aItem*/ )
    {
    CEikGlobalTextEditor* globalEditor = new (ELeave) CEikGlobalTextEditor;
    CleanupStack::PushL( globalEditor );
    STIF_ASSERT_NOT_NULL( globalEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_GLOBALTEXT );
    globalEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    globalEditor->SetContainerWindowL( *control );
    globalEditor->CreateTextViewL();
    
    _LIT( KText, "Text" );
    TFileName text( KText );
    globalEditor->SetTextL( &text );
    
    SEdwinFindModel* findModel = NULL;
    CDesCArray* findList = NULL;
    CDesCArray* replaceList = NULL;
    
    globalEditor->InitFindL( findModel, findList, replaceList );
    
    globalEditor->DoFindL();
    
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( globalEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestGETRunParaDialogsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestGETRunParaDialogsL( CStifItemParser& /*aItem*/ )
    {
    CEikGlobalTextEditor* globalEditor = new (ELeave) CEikGlobalTextEditor;
    CleanupStack::PushL( globalEditor );
    STIF_ASSERT_NOT_NULL( globalEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_GLOBALTEXT );
    globalEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    globalEditor->SetContainerWindowL( *control );
    globalEditor->CreateTextViewL();

    CTestSDKEditorsDialogFactory* factory = new (ELeave) CTestSDKEditorsDialogFactory;
    CleanupStack::PushL( factory );
    ivEikonEnv->SetCDlgDialogFactory( factory );
    
    globalEditor->RunParaDialogsL( EEikCmdParaAlign );
    
    CleanupStack::PopAndDestroy( factory );
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( globalEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestGETRunPaginateDialogL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestGETRunPaginateDialogL( CStifItemParser& /*aItem*/ )
    {
    CEikGlobalTextEditor* globalEditor = new (ELeave) CEikGlobalTextEditor;
    CleanupStack::PushL( globalEditor );
    STIF_ASSERT_NOT_NULL( globalEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_GLOBALTEXT );
    globalEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    globalEditor->SetContainerWindowL( *control );
    globalEditor->CreateTextViewL();

    CPrintSetup* setup = CPrintSetup::NewL();
    CleanupStack::PushL( setup );
    CArrayFix<TInt>* array = new (ELeave) CArrayFixFlat<TInt>( 1 );
    CleanupStack::PushL( array );
    
    CTestSDKEditorsDialogFactory* factory = new (ELeave) CTestSDKEditorsDialogFactory;
    CleanupStack::PushL( factory );
    ivEikonEnv->SetPrintDialogFactory( factory );
    globalEditor->RunPaginateDialogL( setup, array );
    
    CleanupStack::PopAndDestroy( factory );
    CleanupStack::PopAndDestroy( array );
    CleanupStack::PopAndDestroy( setup );
    
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( globalEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestGETGlobalTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestGETGlobalTextL( CStifItemParser& /*aItem*/ )
    {
    CEikGlobalTextEditor* globalEditor = new (ELeave) CEikGlobalTextEditor;
    CleanupStack::PushL( globalEditor );
    STIF_ASSERT_NOT_NULL( globalEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_GLOBALTEXT );
    globalEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    globalEditor->SetContainerWindowL( *control );
    globalEditor->CreateTextViewL();

    CGlobalText* globaltext = globalEditor->GlobalText();
    STIF_ASSERT_NOT_NULL( globaltext );
    
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( globalEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestGETApplyParaFormatL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestGETApplyParaFormatL( CStifItemParser& /*aItem*/ )
    {
    CEikGlobalTextEditor* globalEditor = new (ELeave) CEikGlobalTextEditor;
    CleanupStack::PushL( globalEditor );
    STIF_ASSERT_NOT_NULL( globalEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_GLOBALTEXT );
    globalEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    globalEditor->SetContainerWindowL( *control );
    globalEditor->CreateTextViewL();
    
    CParaFormat* paraFormat = new (ELeave) CParaFormat;
    CleanupStack::PushL( paraFormat );
    TParaFormatMask paraFormatMask;
    globalEditor->ApplyParaFormatL( paraFormat, paraFormatMask );
    
    CleanupStack::PopAndDestroy( paraFormat );
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( globalEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestGETApplyCharFormatL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestGETApplyCharFormatL( CStifItemParser& /*aItem*/ )
    {
    CEikGlobalTextEditor* globalEditor = new (ELeave) CEikGlobalTextEditor;
    CleanupStack::PushL( globalEditor );
    STIF_ASSERT_NOT_NULL( globalEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_GLOBALTEXT );
    globalEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    globalEditor->SetContainerWindowL( *control );
    globalEditor->CreateTextViewL();
    
    TCharFormat charFormat;
    TCharFormatMask charFormatMask;
    globalEditor->ApplyCharFormatL( charFormat, charFormatMask );
    
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( globalEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestGETBoldItalicUnderlineEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestGETBoldItalicUnderlineEventL( CStifItemParser& /*aItem*/ )
    {
    CEikGlobalTextEditor* globalEditor = new (ELeave) CEikGlobalTextEditor;
    CleanupStack::PushL( globalEditor );
    STIF_ASSERT_NOT_NULL( globalEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_GLOBALTEXT );
    globalEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    globalEditor->SetContainerWindowL( *control );
    globalEditor->CreateTextViewL();
    
    globalEditor->BoldItalicUnderlineEventL( CEikGlobalTextEditor::EStandard );
    
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( globalEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestGETUpdateButtonGroupL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestGETUpdateButtonGroupL( CStifItemParser& /*aItem*/ )
    {
    CEikGlobalTextEditor* globalEditor = new (ELeave) CEikGlobalTextEditor;
    CleanupStack::PushL( globalEditor );
    STIF_ASSERT_NOT_NULL( globalEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_GLOBALTEXT );
    globalEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    globalEditor->SetContainerWindowL( *control );
    globalEditor->CreateTextViewL();
    
    globalEditor->UpdateButtonGroup();
    
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( globalEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestGETConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestGETConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    CEikGlobalTextEditor* globalEditor = new (ELeave) CEikGlobalTextEditor;
    CleanupStack::PushL( globalEditor );
    STIF_ASSERT_NOT_NULL( globalEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_GLOBALTEXT );
    globalEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( globalEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestGETOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestGETOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {
    CEikGlobalTextEditor* globalEditor = new (ELeave) CEikGlobalTextEditor;
    CleanupStack::PushL( globalEditor );
    STIF_ASSERT_NOT_NULL( globalEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    globalEditor->ConstructL( control, 1, KLimit, CEikEdwin::EZeroEnumValue, 
                              EGulFontControlAll, EGulAllFonts );
    globalEditor->SetContainerWindowL( *control );

    TKeyEvent keyEvent;
    keyEvent.iCode = EKeyCBA1;
    STIF_ASSERT_TRUE( EKeyWasNotConsumed == globalEditor->OfferKeyEventL( keyEvent, EEventKeyDown ) );
    
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( globalEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestGETActivateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestGETActivateL( CStifItemParser& /*aItem*/ )
    {
    CEikGlobalTextEditor* globalEditor = new (ELeave) CEikGlobalTextEditor;
    CleanupStack::PushL( globalEditor );
    STIF_ASSERT_NOT_NULL( globalEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    globalEditor->ConstructL( control, 1, KLimit, CEikEdwin::EZeroEnumValue, 
                              EGulFontControlAll, EGulAllFonts );
    globalEditor->SetContainerWindowL( *control );
    globalEditor->ActivateL();
    
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( globalEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestGETHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestGETHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CEikGlobalTextEditor* globalEditor = new (ELeave) CEikGlobalTextEditor;
    CleanupStack::PushL( globalEditor );
    STIF_ASSERT_NOT_NULL( globalEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_GLOBALTEXT );
    globalEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    globalEditor->SetContainerWindowL( *control );
    globalEditor->CreateTextViewL();
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Up;
    globalEditor->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( globalEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestGETLineCursorWidthL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestGETLineCursorWidthL( CStifItemParser& /*aItem*/ )
    {
    CEikGlobalTextEditor* globalEditor = new (ELeave) CEikGlobalTextEditor;
    CleanupStack::PushL( globalEditor );
    STIF_ASSERT_NOT_NULL( globalEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    globalEditor->ConstructL( control, 1, KLimit, CEikEdwin::EZeroEnumValue, 
                              EGulFontControlAll, EGulAllFonts );
    
    STIF_ASSERT_EQUALS( 0, globalEditor->LineCursorWidth() );
    
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( globalEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestGETBaseConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestGETBaseConstructL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKEditorsGloablText* globalEditor = new (ELeave) CTestSDKEditorsGloablText;
    CleanupStack::PushL( globalEditor );
    STIF_ASSERT_NOT_NULL( globalEditor );
    
    globalEditor->BaseConstructL();
    
    CleanupStack::PopAndDestroy( globalEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestGETWriteInternalStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestGETWriteInternalStateL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKEditorsGloablText* globalEditor = new (ELeave) CTestSDKEditorsGloablText;
    CleanupStack::PushL( globalEditor );
    STIF_ASSERT_NOT_NULL( globalEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    globalEditor->ConstructL( control, 1, KLimit, CEikEdwin::EZeroEnumValue, 
                              EGulFontControlAll, EGulAllFonts );
    
    const TInt LengthC = 200;
    CBufFlat* buf = CBufFlat::NewL( LengthC );
    CleanupStack::PushL( buf );
    RBufWriteStream writeStream;
    CleanupClosePushL( writeStream );
    writeStream.Open( *buf );
        
    STIF_ASSERT_NOT_LEAVES( globalEditor->WriteInternalStateL( writeStream ) );
    STIF_ASSERT_NOT_NULL( buf );
    STIF_ASSERT_NOT_NULL( &writeStream );
    
    CleanupStack::PopAndDestroy( &writeStream );
    CleanupStack::PopAndDestroy( buf );
    
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( globalEditor );
    
    return KErrNone;
    
    }
