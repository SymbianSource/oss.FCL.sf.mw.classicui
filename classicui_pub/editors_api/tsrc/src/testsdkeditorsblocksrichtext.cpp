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
* Description:  Test EIKRTED.h
*
*/



// [INCLUDE FILES]

#include <eikrted.h>
#include <eikedwin.h>
#include <fbs.h>
#include <barsread.h>
#include <coemain.h>
#include <coeaui.h>
#include <s32mem.h>
#include <gulftflg.hrh>
#include <prnsetup.h>
#include <eikenv.h>
#include <txtglobl.h>
#include <eikembal.h>
#include <eikproc.h>
#include <testsdkeditors.rsg>

#include "testsdkeditors.h"
#include "testsdkeditorscontrol.h"
#include "testsdkeditorsdialogfactory.h"
#include "testsdkeditorsrichtext.h"
#include "testsdkeditorsedstateobserver.h"

//CONST
const TInt KLimit = 20;
const TInt KLength = 20;

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKEditors::TestRETCEikRichTextEditorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestRETCEikRichTextEditorL( CStifItemParser& /*aItem*/ )
    {
    CEikRichTextEditor* richEditor = new (ELeave) CEikRichTextEditor;
    CleanupStack::PushL( richEditor );
    STIF_ASSERT_NOT_NULL( richEditor );
    
    CleanupStack::PopAndDestroy( richEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestRETCEikRichTextEditorPL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestRETCEikRichTextEditorPL( CStifItemParser& /*aItem*/ )
    {
    TGulBorder gulBorder;
    CEikRichTextEditor* richEditor = new (ELeave) CEikRichTextEditor( gulBorder );
    CleanupStack::PushL( richEditor );
    STIF_ASSERT_NOT_NULL( richEditor );
    
    CleanupStack::PopAndDestroy( richEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestRETDeconstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestRETDeconstructorL( CStifItemParser& /*aItem*/ )
    {
    CEikRichTextEditor* richEditor = new (ELeave) CEikRichTextEditor;
    CleanupStack::PushL( richEditor );
    STIF_ASSERT_NOT_NULL( richEditor );
    
    CleanupStack::Pop( richEditor );
    delete richEditor;
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestRETConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestRETConstructL( CStifItemParser& /*aItem*/ )
    {
    CEikRichTextEditor* richEditor = new (ELeave) CEikRichTextEditor;
    CleanupStack::PushL( richEditor );
    STIF_ASSERT_NOT_NULL( richEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    richEditor->ConstructL( control, 1, KLimit, CEikEdwin::ENoAutoSelection, 0, 0 );
    
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( richEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestRETRichTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestRETRichTextL( CStifItemParser& /*aItem*/ )
    {
    CEikRichTextEditor* richEditor = new (ELeave) CEikRichTextEditor;
    CleanupStack::PushL( richEditor );
    STIF_ASSERT_NOT_NULL( richEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    richEditor->ConstructL( control, 1, KLimit, CEikEdwin::ENoAutoSelection, 0, 0 );
    
    CRichText* richText = richEditor->RichText();
    STIF_ASSERT_NOT_NULL( richText );
    
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( richEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestRETInsertObjectOPL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestRETInsertObjectOPL( CStifItemParser& /*aItem*/ )
    {
    CEikRichTextEditor* richEditor = new (ELeave) CEikRichTextEditor;
    CleanupStack::PushL( richEditor );
    STIF_ASSERT_NOT_NULL( richEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_RICHTEXT );
    richEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    richEditor->SetContainerWindowL( *control );
    richEditor->ActivateL();
    
    CTestSDKEditorsDialogFactory* factory = new (ELeave) CTestSDKEditorsDialogFactory;
    CleanupStack::PushL( factory );
    ivEikonEnv->SetCDlgDialogFactory( factory );
    
    TRAP_IGNORE( richEditor->InsertObjectL( CEikRichTextEditor::EAlwaysIconic ) );
    
    CleanupStack::PopAndDestroy( factory );
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( richEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestRETInsertObjectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestRETInsertObjectL( CStifItemParser& /*aItem*/ )
    {
    CEikRichTextEditor* richEditor = new (ELeave) CEikRichTextEditor;
    CleanupStack::PushL( richEditor );
    STIF_ASSERT_NOT_NULL( richEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_RICHTEXT );
    richEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    richEditor->SetContainerWindowL( *control );
    richEditor->CreateTextViewL();
    richEditor->ActivateL();
    
    _LIT( KText, "Text" );
    TFileName text( KText );
    richEditor->SetTextL( &text );
    
    CTestSDKEditorsDialogFactory* factory = new (ELeave) CTestSDKEditorsDialogFactory;
    CleanupStack::PushL( factory );
    ivEikonEnv->SetCDlgDialogFactory( factory );
    
    TRAP_IGNORE( richEditor->InsertObjectL() );
    
    CleanupStack::PopAndDestroy( factory );
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( richEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestRETInsertObjectTPL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestRETInsertObjectTPL( CStifItemParser& /*aItem*/ )
    {
    CEikRichTextEditor* richEditor = new (ELeave) CEikRichTextEditor;
    CleanupStack::PushL( richEditor );
    STIF_ASSERT_NOT_NULL( richEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    richEditor->ConstructL( control, 1, KLimit, CEikEdwin::ENoAutoSelection, 0, 0 );
    
    richEditor->SetContainerWindowL( *control );
    richEditor->CreateTextViewL();
    
    _LIT( KText, "Text" );
    TFileName text( KText );
    richEditor->SetTextL( &text );
    
    CTestSDKEditorsDialogFactory* factory = new (ELeave) CTestSDKEditorsDialogFactory;
    CleanupStack::PushL( factory );
    ivEikonEnv->SetCDlgDialogFactory( factory );
    
    _LIT( KAppDllName, "test.dll" );
    TUid dllId = TUid::Uid( 0x20004742 );
    TRAP_IGNORE( richEditor->InsertObjectL( KAppDllName, dllId, CEikRichTextEditor::EAlwaysIconic ) );
    
    CleanupStack::PopAndDestroy( factory );
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( richEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestRETInsertObjectWPL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestRETInsertObjectWPL( CStifItemParser& /*aItem*/ )
    {
    CEikRichTextEditor* richEditor = new (ELeave) CEikRichTextEditor;
    CleanupStack::PushL( richEditor );
    STIF_ASSERT_NOT_NULL( richEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    richEditor->ConstructL( control, 1, KLimit, CEikEdwin::ENoAutoSelection, 0, 0 );
    
    richEditor->SetContainerWindowL( *control );
    richEditor->CreateTextViewL();
    
    _LIT( KText, "Text" );
    TFileName text( KText );
    richEditor->SetTextL( &text );
    
    CTestSDKEditorsDialogFactory* factory = new (ELeave) CTestSDKEditorsDialogFactory;
    CleanupStack::PushL( factory );
    ivEikonEnv->SetCDlgDialogFactory( factory );
    
    CFbsBitmap* bmp = new( ELeave ) CFbsBitmap();
    CleanupStack::PushL( bmp );
    TRAP_IGNORE( richEditor->InsertObjectL( KUidPictureTypeDoor, bmp ) );
    
    CleanupStack::PopAndDestroy( bmp );
    CleanupStack::PopAndDestroy( factory );
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( richEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestRETReEditObjectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestRETReEditObjectL( CStifItemParser& /*aItem*/ )
    {
    CEikRichTextEditor* richEditor = new (ELeave) CEikRichTextEditor;
    CleanupStack::PushL( richEditor );
    STIF_ASSERT_NOT_NULL( richEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    richEditor->ConstructL( control, 1, KLimit, CEikEdwin::ENoAutoSelection, 0, 0 );
    
    richEditor->SetContainerWindowL( *control );
    richEditor->CreateTextViewL();

    richEditor->ReEditObjectL();

    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( richEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestRETObjectCursorPosL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestRETObjectCursorPosL( CStifItemParser& /*aItem*/ )
    {
    CEikRichTextEditor* richEditor = new (ELeave) CEikRichTextEditor;
    CleanupStack::PushL( richEditor );
    STIF_ASSERT_NOT_NULL( richEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    richEditor->ConstructL( control, 1, KLimit, CEikEdwin::ENoAutoSelection, 0, 0 );
    
    richEditor->SetContainerWindowL( *control );
    richEditor->CreateTextViewL();

    STIF_ASSERT_EQUALS( KErrNotFound, richEditor->ObjectCursorPos() );

    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( richEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestRETCheckForObjectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestRETCheckForObjectL( CStifItemParser& /*aItem*/ )
    {
    CEikRichTextEditor* richEditor = new (ELeave) CEikRichTextEditor;
    CleanupStack::PushL( richEditor );
    STIF_ASSERT_NOT_NULL( richEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    richEditor->ConstructL( control, 1, KLimit, CEikEdwin::ENoAutoSelection, 0, 0 );
    
    richEditor->SetContainerWindowL( *control );
    richEditor->CreateTextViewL();

    STIF_ASSERT_FALSE( richEditor->CheckForObjectL() );

    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( richEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestRETEditPictureFormatL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestRETEditPictureFormatL( CStifItemParser& /*aItem*/ )
    {
    CEikRichTextEditor* richEditor = new (ELeave) CEikRichTextEditor;
    CleanupStack::PushL( richEditor );
    STIF_ASSERT_NOT_NULL( richEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    richEditor->ConstructL( control, 1, KLimit, CEikEdwin::ENoAutoSelection, 0, 0 );
    
    richEditor->SetContainerWindowL( *control );
    richEditor->CreateTextViewL();

    richEditor->EditPictureFormatL();

    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( richEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestRETPictureFormatChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestRETPictureFormatChangedL( CStifItemParser& /*aItem*/ )
    {
    CEikRichTextEditor* richEditor = new (ELeave) CEikRichTextEditor;
    CleanupStack::PushL( richEditor );
    STIF_ASSERT_NOT_NULL( richEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    richEditor->ConstructL( control, 1, KLimit, CEikEdwin::ENoAutoSelection, 0, 0 );
    
    richEditor->SetContainerWindowL( *control );
    richEditor->CreateTextViewL();

    richEditor->PictureFormatChangedL();

    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( richEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestRETGetEmbeddedAppL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestRETGetEmbeddedAppL( CStifItemParser& /*aItem*/ )
    {
    CEikRichTextEditor* richEditor = new (ELeave) CEikRichTextEditor;
    CleanupStack::PushL( richEditor );
    STIF_ASSERT_NOT_NULL( richEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    richEditor->ConstructL( control, 1, KLimit, CEikEdwin::ENoAutoSelection, 0, 0 );
    
    richEditor->SetContainerWindowL( *control );
    richEditor->CreateTextViewL();

    CApaDocument* document = NULL;
    CApaDoor* door = NULL;
    richEditor->GetEmbeddedAppL( door, document, 0 );

    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( richEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestRETUpdatePictureFormatL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestRETUpdatePictureFormatL( CStifItemParser& /*aItem*/ )
    {
    CEikRichTextEditor* richEditor = new (ELeave) CEikRichTextEditor;
    CleanupStack::PushL( richEditor );
    STIF_ASSERT_NOT_NULL( richEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_RICHTEXT );
    richEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    richEditor->SetContainerWindowL( *control );
    richEditor->ActivateL();

    richEditor->UpdatePictureFormatL();
    
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( richEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestRETUpdatePictureFormatPL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestRETUpdatePictureFormatPL( CStifItemParser& /*aItem*/ )
    {
    CEikRichTextEditor* richEditor = new (ELeave) CEikRichTextEditor;
    CleanupStack::PushL( richEditor );
    STIF_ASSERT_NOT_NULL( richEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_RICHTEXT );
    richEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    richEditor->SetContainerWindowL( *control );
    richEditor->ActivateL();

    richEditor->UpdatePictureFormatL( 0, 1 );
    
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( richEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestRETSetDefaultIconicDoorSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestRETSetDefaultIconicDoorSizeL( CStifItemParser& /*aItem*/ )
    {
    CEikRichTextEditor* richEditor = new (ELeave) CEikRichTextEditor;
    CleanupStack::PushL( richEditor );
    STIF_ASSERT_NOT_NULL( richEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_RICHTEXT );
    richEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    richEditor->SetContainerWindowL( *control );
    richEditor->ActivateL();
    
    TSize size( KLength, KLength );
    richEditor->SetDefaultIconicDoorSize( size );
    STIF_ASSERT_TRUE( size == richEditor->DefaultIconicDoorSize() );
    
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( richEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestRETDefaultIconicDoorSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestRETDefaultIconicDoorSizeL( CStifItemParser& aItem )
    {
    return TestRETSetDefaultIconicDoorSizeL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestRETUpdatePictureSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestRETUpdatePictureSizeL( CStifItemParser& /*aItem*/ )
    {
    CEikRichTextEditor* richEditor = new (ELeave) CEikRichTextEditor;
    CleanupStack::PushL( richEditor );
    STIF_ASSERT_NOT_NULL( richEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_RICHTEXT );
    richEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    richEditor->SetContainerWindowL( *control );
    richEditor->ActivateL();
    
    richEditor->UpdatePictureSizeL();
    
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( richEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestRETUpdatePictureSizePL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestRETUpdatePictureSizePL( CStifItemParser& /*aItem*/ )
    {
    CEikRichTextEditor* richEditor = new (ELeave) CEikRichTextEditor;
    CleanupStack::PushL( richEditor );
    STIF_ASSERT_NOT_NULL( richEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_RICHTEXT );
    richEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    richEditor->SetContainerWindowL( *control );
    richEditor->ActivateL();
    
    richEditor->UpdatePictureSizeL( 0, 1 );
    
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( richEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestRETSetParserObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestRETSetParserObserverL( CStifItemParser& /*aItem*/ )
    {
    CEikRichTextEditor* richEditor = new (ELeave) CEikRichTextEditor;
    CleanupStack::PushL( richEditor );
    STIF_ASSERT_NOT_NULL( richEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_RICHTEXT );
    richEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    richEditor->SetContainerWindowL( *control );
    richEditor->ActivateL();
    
    CTestSDKEditorsEdStateObserver* observer = CTestSDKEditorsEdStateObserver::NewL();
    CleanupStack::PushL( observer );
    
    richEditor->SetParserObserver( observer );
    
    CleanupStack::PopAndDestroy( observer );
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( richEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestRETSetPhoneNumberGroupingL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestRETSetPhoneNumberGroupingL( CStifItemParser& /*aItem*/ )
    {
    CEikRichTextEditor* richEditor = new (ELeave) CEikRichTextEditor;
    CleanupStack::PushL( richEditor );
    STIF_ASSERT_NOT_NULL( richEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_RICHTEXT );
    richEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    richEditor->SetContainerWindowL( *control );
    richEditor->ActivateL();
    
    richEditor->SetPhoneNumberGrouping( ETrue );
    
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( richEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestRETOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestRETOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {
    CEikRichTextEditor* richEditor = new (ELeave) CEikRichTextEditor;
    CleanupStack::PushL( richEditor );
    STIF_ASSERT_NOT_NULL( richEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_RICHTEXT );
    richEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    richEditor->SetContainerWindowL( *control );
    richEditor->ActivateL();
    
    TKeyEvent keyEvent;
    keyEvent.iCode = EKeyCBA1;
    STIF_ASSERT_TRUE( EKeyWasNotConsumed == richEditor->OfferKeyEventL( keyEvent, EEventKey ) );
    
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( richEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestRETHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestRETHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CEikRichTextEditor* richEditor = new (ELeave) CEikRichTextEditor;
    CleanupStack::PushL( richEditor );
    STIF_ASSERT_NOT_NULL( richEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_RICHTEXT );
    richEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    richEditor->SetContainerWindowL( *control );
    richEditor->ActivateL();
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Up;
    richEditor->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( richEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestRETConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestRETConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    CEikRichTextEditor* richEditor = new (ELeave) CEikRichTextEditor;
    CleanupStack::PushL( richEditor );
    STIF_ASSERT_NOT_NULL( richEditor );
    
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_RICHTEXT );
    richEditor->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    CleanupStack::PopAndDestroy( richEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestRETActivateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestRETActivateL( CStifItemParser& /*aItem*/ )
    {
    CEikRichTextEditor* richEditor = new (ELeave) CEikRichTextEditor;
    CleanupStack::PushL( richEditor );
    STIF_ASSERT_NOT_NULL( richEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    richEditor->ConstructL( control, 1, KLimit, CEikEdwin::ENoAutoSelection, 0, 0 );
    
    richEditor->SetContainerWindowL( *control );
    richEditor->CreateTextViewL();
    
    richEditor->ActivateL();
    
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( richEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestRETCopyDocumentContentL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestRETCopyDocumentContentL( CStifItemParser& /*aItem*/ )
    {
    CEikRichTextEditor* richEditor = new (ELeave) CEikRichTextEditor;
    CleanupStack::PushL( richEditor );
    STIF_ASSERT_NOT_NULL( richEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    richEditor->ConstructL( control, 1, KLimit, CEikEdwin::ENoAutoSelection, 0, 0 );
    
    richEditor->SetContainerWindowL( *control );
    richEditor->CreateTextViewL();
    
    _LIT( KText, "one text" );
    TBuf<KLength> text( KText );
    richEditor->SetTextL( &text );
    
    CGlobalText* globalText = richEditor->GlobalText();
    richEditor->CopyDocumentContentL( *globalText, *globalText );
    
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( richEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestRETWriteInternalStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestRETWriteInternalStateL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKEditorsRichText* richEditor = new (ELeave) CTestSDKEditorsRichText;
    CleanupStack::PushL( richEditor );
    STIF_ASSERT_NOT_NULL( richEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    richEditor->ConstructL( control, 1, KLimit, CEikEdwin::ENoAutoSelection, 0, 0 );
    
    richEditor->SetContainerWindowL( *control );
    
    const TInt LengthC = 200;
    CBufFlat* buf = CBufFlat::NewL( LengthC );
    CleanupStack::PushL( buf );
    RBufWriteStream writeStream;
    CleanupClosePushL( writeStream );
    writeStream.Open( *buf );
        
    STIF_ASSERT_NOT_LEAVES( richEditor->WriteInternalStateL( writeStream ) );
    STIF_ASSERT_NOT_NULL( buf );
    STIF_ASSERT_NOT_NULL( &writeStream );
    
    CleanupStack::PopAndDestroy( &writeStream );
    CleanupStack::PopAndDestroy( buf );

    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( richEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestRETEditObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestRETEditObserverL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKEditorsRichText* richEditor = new (ELeave) CTestSDKEditorsRichText;
    CleanupStack::PushL( richEditor );
    STIF_ASSERT_NOT_NULL( richEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    richEditor->ConstructL( control, 1, KLimit, CEikEdwin::ENoAutoSelection, 0, 0 );
    
    richEditor->SetContainerWindowL( *control );
    richEditor->CreateTextViewL();

    richEditor->EditObserver( 0, 1 );

    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( richEditor );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditors::TestRETRefreshParsersL
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditors::TestRETRefreshParsersL( CStifItemParser& /*aItem*/ )
    {
    CEikRichTextEditor* richEditor = new (ELeave) CEikRichTextEditor;
    CleanupStack::PushL( richEditor );
    STIF_ASSERT_NOT_NULL( richEditor );
    
    CTestEditorsControl* control = CTestEditorsControl::NewL();
    CleanupStack::PushL( control );
    richEditor->ConstructL( control, 1, KLimit, CEikEdwin::ENoAutoSelection, 0, 0 );
    
    richEditor->SetContainerWindowL( *control );
    richEditor->CreateTextViewL();

    richEditor->RefreshParsersL();

    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( richEditor );
    
    return KErrNone;
    
    }
