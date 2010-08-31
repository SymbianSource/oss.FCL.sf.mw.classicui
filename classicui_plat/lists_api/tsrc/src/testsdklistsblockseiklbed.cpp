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
* Description:  Test eiklbed.h
*
*/

// [INCLUDE FILES]
#include <e32base.h>
#include <eiklbed.h>
#include <testsdklists.rsg>
#include <coemain.h>
#include <coeaui.h>
#include <eiklbi.h>
#include <eiktxlbm.h>
#include <s32file.h>

#include "testsdklists.h"
#include "testsdkcontainer.h"
#include "testsdklistslbtexteditor.h"

const TInt KTen = 10;
const TInt KThirty = 30;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBTEConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBTEConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLBTEConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();
    CleanupStack::PushL( model );
    model->ConstructL( NULL );

    CEikListBoxTextEditor* editor = new( ELeave ) CEikListBoxTextEditor( model );
    CleanupStack::PushL( editor );
    STIF_ASSERT_NOT_NULL( editor );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBTEDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBTEDestructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLBTEDestructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();
    CleanupStack::PushL( model );
    model->ConstructL( NULL );

    CEikListBoxTextEditor* editor = new( ELeave ) CEikListBoxTextEditor( model );
    CleanupStack::PushL( editor );
    STIF_ASSERT_NOT_NULL( editor );
    CleanupStack::Pop( editor );
    CleanupStack::PopAndDestroy( model );
    delete editor;
    editor = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBTESetFontL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBTESetFontL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLBTESetFontL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();
    CleanupStack::PushL( model );
    model->ConstructL( NULL );

    CEikListBoxTextEditor* editor = new( ELeave ) CEikListBoxTextEditor( model );
    CleanupStack::PushL( editor );
    STIF_ASSERT_NOT_NULL( editor );

    const CFont* font = iEikonEnvPointer->NormalFont();
    editor->SetFont( font );
    CleanupStack::Pop( editor );
    CleanupStack::PopAndDestroy( model );
    delete editor;
    editor = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBTEEditorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBTEEditorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLBTEEditorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();
    CleanupStack::PushL( model );
    model->ConstructL( NULL );

    CEikListBoxTextEditor* editor = new( ELeave ) CEikListBoxTextEditor( model );
    CleanupStack::PushL( editor );
    STIF_ASSERT_NOT_NULL( editor );

    CEikEdwin* edwin = editor->Editor();
    STIF_ASSERT_NULL( edwin );
    CleanupStack::Pop( editor );
    CleanupStack::PopAndDestroy( model );
    delete editor;
    editor = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBTESetListBoxEditorObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBTESetListBoxEditorObserverL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLBTESetListBoxEditorObserverL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();
    CleanupStack::PushL( model );
    model->ConstructL( NULL );

    CEikListBoxTextEditor* editor = new( ELeave ) CEikListBoxTextEditor( model );
    CleanupStack::PushL( editor );
    STIF_ASSERT_NOT_NULL( editor );

    MListBoxEditorObserver* observer = NULL;
    editor->SetListBoxEditorObserver( observer );
    CleanupStack::Pop( editor );
    CleanupStack::PopAndDestroy( model );
    delete editor;
    editor = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBTEItemTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBTEItemTextL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLBTEItemTextL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY_AGAIN );
    CleanupStack::PushL( textArray );
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();
    CleanupStack::PushL( model );
    model->ConstructL( textArray );

    CEikListBoxTextEditor* editor = new( ELeave ) CEikListBoxTextEditor( model );
    CleanupStack::PushL( editor );
    STIF_ASSERT_NOT_NULL( editor );
    editor->ItemText();
    CleanupStack::Pop( editor );
    CleanupStack::PopAndDestroy( model );
    CleanupStack::Pop( textArray );
    delete editor;
    editor = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBTEStartEditingL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBTEStartEditingL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLBTEStartEditingL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY_AGAIN );
    CleanupStack::PushL( textArray );
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();
    CleanupStack::PushL( model );
    model->ConstructL( textArray );

    CEikListBoxTextEditor* editor = new( ELeave ) CEikListBoxTextEditor( model );
    CleanupStack::PushL( editor );
    STIF_ASSERT_NOT_NULL( editor );

    TRect rect = iContainer->Rect();
    rect.iBr.iY = rect.iTl.iY + rect.Size().iHeight / 2;
    editor->StartEditingL( *iContainer, rect, 0, KThirty );

    CEikEdwin* edwin = editor->Editor();
    STIF_ASSERT_NOT_NULL( edwin );
    CleanupStack::Pop( editor );
    CleanupStack::PopAndDestroy( model );
    CleanupStack::Pop( textArray );
    delete editor;
    editor = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBTEStopEditingL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBTEStopEditingL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLBTEStopEditingL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY_AGAIN );
    CleanupStack::PushL( textArray );
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();
    CleanupStack::PushL( model );
    model->ConstructL( textArray );

    CEikListBoxTextEditor* editor = new( ELeave ) CEikListBoxTextEditor( model );
    CleanupStack::PushL( editor );
    STIF_ASSERT_NOT_NULL( editor );

    TRect rect = iContainer->Rect();
    rect.iBr.iY = rect.iTl.iY + rect.Size().iHeight / 2;
    editor->StartEditingL( *iContainer, rect, 0, KThirty );
    CEikEdwin* edwin = editor->Editor();
    STIF_ASSERT_NOT_NULL( edwin );

    editor->StopEditingL();
    edwin = editor->Editor();
    STIF_ASSERT_NULL( edwin );
    CleanupStack::Pop( editor );
    CleanupStack::PopAndDestroy( model );
    CleanupStack::Pop( textArray );
    delete editor;
    editor = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBTEUpdateModelL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBTEUpdateModelL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLBTEUpdateModelL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY_AGAIN );
    CleanupStack::PushL( textArray );
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();
    CleanupStack::PushL( model );
    model->ConstructL( textArray );

    CEikListBoxTextEditor* editor = new( ELeave ) CEikListBoxTextEditor( model );
    CleanupStack::PushL( editor );
    STIF_ASSERT_NOT_NULL( editor );

    TBool flag = editor->UpdateModelL();
    STIF_ASSERT_FALSE( flag );
    CleanupStack::Pop( editor );
    CleanupStack::PopAndDestroy( model );
    CleanupStack::Pop( textArray );
    delete editor;
    editor = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBTEOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBTEOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLBTEOfferKeyEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY_AGAIN );
    CleanupStack::PushL( textArray );
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();
    CleanupStack::PushL( model );
    model->ConstructL( textArray );

    CEikListBoxTextEditor* editor = new( ELeave ) CEikListBoxTextEditor( model );
    CleanupStack::PushL( editor );
    STIF_ASSERT_NOT_NULL( editor );

    TKeyEvent eventEnter = { EKeyEnter, EKeyEnter, 0, 0 };
    TKeyEvent eventShift = { '1', '1', EModifierCtrl | EModifierShift, 0 };
    TKeyEvent eventT = { 'T', 'T', 0, 0 };
    TKeyEvent evente = { 'e', 'e', 0, 0 };
    TKeyEvent events = { 's', 's', 0, 0 };
    TKeyEvent eventt = { 't', 't', 0, 0 };
    editor->OfferKeyEventL( eventEnter, EEventKey );
    editor->SetListBoxEditorObserver( NULL );
    editor->OfferKeyEventL( eventT, EEventKey );
    editor->OfferKeyEventL( evente, EEventKey );
    editor->OfferKeyEventL( events, EEventKey );
    editor->OfferKeyEventL( eventt, EEventKey );    
    editor->OfferKeyEventL( eventShift, EEventKey );    
    CleanupStack::Pop( editor );
    CleanupStack::PopAndDestroy( model );
    CleanupStack::Pop( textArray );
    delete editor;
    editor = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBTEHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBTEHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLBTEHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY_AGAIN );
    CleanupStack::PushL( textArray );
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();
    CleanupStack::PushL( model );
    model->ConstructL( textArray );

    CEikListBoxTextEditor* editor = new( ELeave ) CEikListBoxTextEditor( model );
    CleanupStack::PushL( editor );
    STIF_ASSERT_NOT_NULL( editor );

    TInt err = KErrNone;
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( KTen, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    TRAP( err, editor->HandlePointerEventL( event ) );
    CleanupStack::Pop( editor );
    CleanupStack::PopAndDestroy( model );
    CleanupStack::Pop( textArray );
    delete editor;
    editor = NULL;

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBTEReleaseL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBTEReleaseL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLBTEReleaseL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY_AGAIN );
    CleanupStack::PushL( textArray );
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();
    CleanupStack::PushL( model );
    model->ConstructL( textArray );

    CTestSDKListsLBTextEditor* editor = new( ELeave ) CTestSDKListsLBTextEditor( model );
    CleanupStack::PushL( editor );
    STIF_ASSERT_NOT_NULL( editor );

    editor->Release();
    CleanupStack::Pop( editor );
    CleanupStack::PopAndDestroy( model );
    CleanupStack::Pop( textArray );
    editor = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBTEListBoxModelL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBTEListBoxModelL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLBTEListBoxModelL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY_AGAIN );
    CleanupStack::PushL( textArray );
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();
    CleanupStack::PushL( model );
    model->ConstructL( textArray );

    CTestSDKListsLBTextEditor* editor = new( ELeave ) CTestSDKListsLBTextEditor( model );
    CleanupStack::PushL( editor );
    STIF_ASSERT_NOT_NULL( editor );

    CTextListBoxModel* getModel = static_cast<CTextListBoxModel*>( editor->ListBoxModel() );
    STIF_ASSERT_NOT_NULL( getModel );
    CleanupStack::Pop( editor );
    CleanupStack::PopAndDestroy( model );
    CleanupStack::Pop( textArray );
    delete editor;
    editor = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBTEItemIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBTEItemIndexL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLBTEItemIndexL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY_AGAIN );
    CleanupStack::PushL( textArray );
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();
    CleanupStack::PushL( model );
    model->ConstructL( textArray );

    CTestSDKListsLBTextEditor* editor = new( ELeave ) CTestSDKListsLBTextEditor( model );
    CleanupStack::PushL( editor );
    STIF_ASSERT_NOT_NULL( editor );

    TInt index = editor->ItemIndex();
    CleanupStack::Pop( editor );
    CleanupStack::PopAndDestroy( model );
    CleanupStack::Pop( textArray );
    delete editor;
    editor = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLBTEWriteInternalStateL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLBTEWriteInternalStateL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLBTEWriteInternalStateL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY_AGAIN );
    CleanupStack::PushL( textArray );
    CTextListBoxModel* model = new( ELeave ) CTextListBoxModel();
    CleanupStack::PushL( model );
    model->ConstructL( textArray );

    CTestSDKListsLBTextEditor* editor = new( ELeave ) CTestSDKListsLBTextEditor( model );
    CleanupStack::PushL( editor );
    STIF_ASSERT_NOT_NULL( editor );

    TRect rect = iContainer->Rect();
    rect.iBr.iY = rect.iTl.iY + rect.Size().iHeight / 2;
    editor->StartEditingL( *iContainer, rect, 0, KThirty );

    RFs& tempServer = iEikonEnvPointer->FsSession();
    tempServer.Delete( KStreamName );

    RFileWriteStream fWrite;
    User::LeaveIfError( fWrite.Create( tempServer, 
        KStreamName, EFileWrite ) );
    CleanupClosePushL( fWrite );
    editor->WriteInternalStateL( fWrite );

    editor->StopEditingL();
    CleanupStack::PopAndDestroy( &fWrite );
    CleanupStack::Pop( editor );
    CleanupStack::PopAndDestroy( model );
    CleanupStack::Pop( textArray );
    delete editor;
    editor = NULL;

    return KErrNone;
    }
