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
* Description:  test AknForm.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknform.h>
#include <eikmenup.h> 
#include <avkon.rsg>
#include <avkon.hrh>
#include <akndef.hrh>
#include <akndef.h>
#include <eikedwin.h> 
#include <eikcapc.h> 
#include <testsdkform.rsg>

#include "testsdkform.hrh"
#include "testsdkformcontrol.h"
#include "testsdkform.h"

//CONST
const TInt KLength = 10;
// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKForm::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestSDKForm::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTestSDKForm::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKForm::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestFCAknFormL", CTestSDKForm::TestFCAknFormL ),
        ENTRY( "TestFConstructL", CTestSDKForm::TestFConstructL ),
        ENTRY( "TestFDecontructorL", CTestSDKForm::TestFDecontructorL ),
        ENTRY( "TestFDynInitMenuPaneL", CTestSDKForm::TestFDynInitMenuPaneL ),
        ENTRY( "TestFProcessCommandL", CTestSDKForm::TestFProcessCommandL ),
        ENTRY( "TestFOkToExitL", CTestSDKForm::TestFOkToExitL ),
        ENTRY( "TestFPrepareForFocusTransitionL", CTestSDKForm::TestFPrepareForFocusTransitionL ),
        ENTRY( "TestFHandleResourceChangeL", CTestSDKForm::TestFHandleResourceChangeL ),
        ENTRY( "TestFHandlePointerEventL", CTestSDKForm::TestFHandlePointerEventL ),
        ENTRY( "TestFSaveFormDataL", CTestSDKForm::TestFSaveFormDataL ),
        ENTRY( "TestFDoNotSaveFormDataL", CTestSDKForm::TestFDoNotSaveFormDataL ),
        ENTRY( "TestFQuerySaveChangesL", CTestSDKForm::TestFQuerySaveChangesL ),
        ENTRY( "TestFEditCurrentLabelL", CTestSDKForm::TestFEditCurrentLabelL ),
        ENTRY( "TestFDeleteCurrentItemL", CTestSDKForm::TestFDeleteCurrentItemL ),
        ENTRY( "TestFAddItemL", CTestSDKForm::TestFAddItemL ),
        ENTRY( "TestFSetChangesPendingL", CTestSDKForm::TestFSetChangesPendingL ),
        ENTRY( "TestFPostLayoutDynInitL", CTestSDKForm::TestFPostLayoutDynInitL ),
        ENTRY( "TestFHandleControlStateChangeL", CTestSDKForm::TestFHandleControlStateChangeL ),
        ENTRY( "TestFSetInitialCurrentLineL", CTestSDKForm::TestFSetInitialCurrentLineL ),
        ENTRY( "TestFUnsavedEditL", CTestSDKForm::TestFUnsavedEditL ),
        ENTRY( "TestFDeletingL", CTestSDKForm::TestFDeletingL ),
        ENTRY( "TestFSetFormFlagL", CTestSDKForm::TestFSetFormFlagL ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKForm::TestFCAknFormL
// -----------------------------------------------------------------------------
TInt CTestSDKForm::TestFCAknFormL( CStifItemParser& /*aItem*/ )
    {
    CAknForm* form = new (ELeave) CAknForm;
    CleanupStack::PushL( form );
    STIF_ASSERT_NOT_NULL( form );
    
    CleanupStack::PopAndDestroy( form );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKForm::TestFConstructL
// -----------------------------------------------------------------------------
TInt CTestSDKForm::TestFConstructL( CStifItemParser& /*aItem*/ )
    {
    CAknForm* form = new (ELeave) CAknForm;
    CleanupStack::PushL( form );
    STIF_ASSERT_NOT_NULL( form );
    
    form->ConstructL();
    
    CleanupStack::PopAndDestroy( form );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKForm::TestFDecontructorL
// -----------------------------------------------------------------------------
TInt CTestSDKForm::TestFDecontructorL( CStifItemParser& /*aItem*/ )
    {
    CAknForm* form = new (ELeave) CAknForm;
    CleanupStack::PushL( form );
    STIF_ASSERT_NOT_NULL( form );
    
    CleanupStack::Pop( form );
    delete form;
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKForm::TestFDynInitMenuPaneL
// -----------------------------------------------------------------------------
TInt CTestSDKForm::TestFDynInitMenuPaneL( CStifItemParser& /*aItem*/ )
    {
    CAknForm* form = new (ELeave) CAknForm;
    CleanupStack::PushL( form );
    STIF_ASSERT_NOT_NULL( form );
    
    form->ConstructL();
    form->PrepareLC( R_TESTSDK_FORM_DIALOG );
    CleanupStack::Pop( form );
    
    CEikMenuPane* menuPane = new (ELeave) CEikMenuPane( form );
    CleanupStack::PushL( menuPane );
    STIF_ASSERT_NOT_NULL( menuPane );
    
    form->DynInitMenuPaneL( R_TESTSDK_FORM_DIALOG, menuPane );
    
    CleanupStack::PopAndDestroy( menuPane );
    CleanupStack::PopAndDestroy( form );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKForm::TestFProcessCommandL
// -----------------------------------------------------------------------------
TInt CTestSDKForm::TestFProcessCommandL( CStifItemParser& /*aItem*/ )
    {
    CAknForm* form = new (ELeave) CAknForm;
    CleanupStack::PushL( form );
    STIF_ASSERT_NOT_NULL( form );
    
    form->ConstructL();
    form->PrepareLC( R_TESTSDK_FORM_DIALOG );
    CleanupStack::Pop( form );
    
    CEikMenuPane* menuPane = new (ELeave) CEikMenuPane( form );
    CleanupStack::PushL( menuPane );
    STIF_ASSERT_NOT_NULL( menuPane );
    
    form->DynInitMenuPaneL( R_TESTSDK_FORM_DIALOG, menuPane );
    form->ProcessCommandL( EAknFormCmdEdit );
    form->ProcessCommandL( EAknFormCmdAdd );
    form->ProcessCommandL( EAknFormCmdSave );
    form->ProcessCommandL( EAknFormCmdLabel );
    form->ProcessCommandL( EAknFormCmdDelete );
    
    CleanupStack::PopAndDestroy( menuPane );
    CleanupStack::PopAndDestroy( form );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKForm::TestFOkToExitL
// -----------------------------------------------------------------------------
TInt CTestSDKForm::TestFOkToExitL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKFormControl* form = new (ELeave) CTestSDKFormControl;
    CleanupStack::PushL( form );
    STIF_ASSERT_NOT_NULL( form );
    
    form->ConstructL();
    form->PrepareLC( R_TESTSDK_FORM_DIALOG );
    CleanupStack::Pop( form );
    
    form->SetEditableL( ETrue );
    TBool flag = form->OkToExitL( EAknSoftkeyBack );
    STIF_ASSERT_TRUE( flag );
    
    CleanupStack::PopAndDestroy( form );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKForm::TestFPrepareForFocusTransitionL
// -----------------------------------------------------------------------------
TInt CTestSDKForm::TestFPrepareForFocusTransitionL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKFormControl* form = new (ELeave) CTestSDKFormControl;
    CleanupStack::PushL( form );
    STIF_ASSERT_NOT_NULL( form );
    
    form->ConstructL();
    form->PrepareLC( R_TESTSDK_FORM_DIALOG );
    CleanupStack::Pop( form );
    
    form->Deleting();
    form->PrepareForFocusTransitionL();
    
    CleanupStack::PopAndDestroy( form );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKForm::TestFHandleResourceChangeL
// -----------------------------------------------------------------------------
TInt CTestSDKForm::TestFHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    CAknForm* form = new (ELeave) CAknForm;
    CleanupStack::PushL( form );
    STIF_ASSERT_NOT_NULL( form );
    
    form->ConstructL();
    form->PrepareLC( R_TESTSDK_FORM_DIALOG );
    CleanupStack::Pop( form );
    
    form->HandleResourceChange( KEikColorResourceChange );
    
    CleanupStack::PopAndDestroy( form );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKForm::TestFHandlePointerEventL
// -----------------------------------------------------------------------------
TInt CTestSDKForm::TestFHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    CAknForm* form = new (ELeave) CAknForm;
    CleanupStack::PushL( form );
    STIF_ASSERT_NOT_NULL( form );
    
    form->ConstructL();
    form->PrepareLC( R_TESTSDK_FORM_DIALOG );
    CleanupStack::Pop( form );
    
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;

    form->HandlePointerEventL( event );
    
    CleanupStack::PopAndDestroy( form );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKForm::TestFSaveFormDataL
// -----------------------------------------------------------------------------
TInt CTestSDKForm::TestFSaveFormDataL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKFormControl* form = new (ELeave) CTestSDKFormControl;
    CleanupStack::PushL( form );
    STIF_ASSERT_NOT_NULL( form );
    
    form->ConstructL();
    form->PrepareLC( R_TESTSDK_FORM_DIALOG );
    CleanupStack::Pop( form );
    
    CEikEdwin* edwin = static_cast<CEikEdwin*>( form->ControlOrNull( ETestSDKEdwin ) );
    _LIT( KEdwin, "edwin" );
    TBuf<KLength> tedwin( KEdwin );
    edwin->SetTextL( &tedwin );
    
    TBool save = form->SaveFormDataL();
    STIF_ASSERT_TRUE( save );
    
    CleanupStack::PopAndDestroy( form );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKForm::TestFDoNotSaveFormDataL
// -----------------------------------------------------------------------------
TInt CTestSDKForm::TestFDoNotSaveFormDataL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKFormControl* form = new (ELeave) CTestSDKFormControl;
    CleanupStack::PushL( form );
    STIF_ASSERT_NOT_NULL( form );
    
    form->ConstructL();
    form->PrepareLC( R_TESTSDK_FORM_DIALOG );
    CleanupStack::Pop( form );
    
    form->DoNotSaveFormDataL();
    
    CleanupStack::PopAndDestroy( form );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKForm::TestFQuerySaveChangesL
// -----------------------------------------------------------------------------
TInt CTestSDKForm::TestFQuerySaveChangesL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKFormControl* form = new (ELeave) CTestSDKFormControl;
    CleanupStack::PushL( form );
    STIF_ASSERT_NOT_NULL( form );
    
    form->ConstructL();
    form->PrepareLC( R_TESTSDK_FORM_DIALOG );
    CleanupStack::Pop( form );
    
    TBool query = form->QuerySaveChangesL();
    STIF_ASSERT_FALSE( query );
    
    CleanupStack::PopAndDestroy( form );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKForm::TestFEditCurrentLabelL
// -----------------------------------------------------------------------------
TInt CTestSDKForm::TestFEditCurrentLabelL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKFormControl* form = new (ELeave) CTestSDKFormControl;
    CleanupStack::PushL( form );
    STIF_ASSERT_NOT_NULL( form );
    
    form->ConstructL();
    form->PrepareLC( R_TESTSDK_FORM_DIALOG );
    CleanupStack::Pop( form );
    
    form->SetInitialCurrentLine();
    CEikCaptionedControl* curLine = form->CurrentLine();
    if (curLine)
        {
        form->TryChangeFocusToL(curLine->iId);
        }
    form->EditCurrentLabelL();
    
    CleanupStack::PopAndDestroy( form );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKForm::TestFDeleteCurrentItemL
// -----------------------------------------------------------------------------
TInt CTestSDKForm::TestFDeleteCurrentItemL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKFormControl* form = new (ELeave) CTestSDKFormControl;
    CleanupStack::PushL( form );
    STIF_ASSERT_NOT_NULL( form );
    
    form->ConstructL();
    form->PrepareLC( R_TESTSDK_FORM_DIALOG );
    CleanupStack::Pop( form );
    
    form->SetInitialCurrentLine();
    CEikCaptionedControl* curLine = form->CurrentLine();
    if (curLine)
        {
        form->TryChangeFocusToL(curLine->iId);
        }
    form->DeleteCurrentItemL();
    
    CleanupStack::PopAndDestroy( form );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKForm::TestFAddItemL
// -----------------------------------------------------------------------------
TInt CTestSDKForm::TestFAddItemL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKFormControl* form = new (ELeave) CTestSDKFormControl;
    CleanupStack::PushL( form );
    STIF_ASSERT_NOT_NULL( form );
    
    form->ConstructL();
    form->PrepareLC( R_TESTSDK_FORM_DIALOG );
    CleanupStack::Pop( form );
    
    form->AddItemL();
    
    CleanupStack::PopAndDestroy( form );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKForm::TestFSetChangesPendingL
// -----------------------------------------------------------------------------
TInt CTestSDKForm::TestFSetChangesPendingL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKFormControl* form = new (ELeave) CTestSDKFormControl;
    CleanupStack::PushL( form );
    STIF_ASSERT_NOT_NULL( form );
    
    form->ConstructL();
    form->PrepareLC( R_TESTSDK_FORM_DIALOG );
    CleanupStack::Pop( form );
    
    form->SetChangesPending( EFalse );
    form->SetChangesPending( ETrue );
    
    CleanupStack::PopAndDestroy( form );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKForm::TestFPostLayoutDynInitL
// -----------------------------------------------------------------------------
TInt CTestSDKForm::TestFPostLayoutDynInitL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKFormControl* form = new (ELeave) CTestSDKFormControl;
    CleanupStack::PushL( form );
    STIF_ASSERT_NOT_NULL( form );
    
    form->ConstructL();
    form->PrepareLC( R_TESTSDK_FORM_DIALOG );
    CleanupStack::Pop( form );
    
    form->PostLayoutDynInitL();
    STIF_ASSERT_TRUE( form->IsEditable() );
    CleanupStack::PopAndDestroy( form );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKForm::TestFHandleControlStateChangeL
// -----------------------------------------------------------------------------
TInt CTestSDKForm::TestFHandleControlStateChangeL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKFormControl* form = new (ELeave) CTestSDKFormControl;
    CleanupStack::PushL( form );
    STIF_ASSERT_NOT_NULL( form );
    
    form->ConstructL();
    form->PrepareLC( R_TESTSDK_FORM_DIALOG );
    CleanupStack::Pop( form );
    
    form->HandleControlStateChangeL( ETestSDKEdwin );

    CleanupStack::PopAndDestroy( form );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKForm::TestFSetInitialCurrentLineL
// -----------------------------------------------------------------------------
TInt CTestSDKForm::TestFSetInitialCurrentLineL( CStifItemParser& aItem )
    {
    return TestFDeleteCurrentItemL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKForm::TestFUnsavedEditL
// -----------------------------------------------------------------------------
TInt CTestSDKForm::TestFUnsavedEditL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKFormControl* form = new (ELeave) CTestSDKFormControl;
    CleanupStack::PushL( form );
    STIF_ASSERT_NOT_NULL( form );
    
    form->ConstructL();
    form->PrepareLC( R_TESTSDK_FORM_DIALOG );
    CleanupStack::Pop( form );
    
    TBool save = form->UnsavedEdit();
    STIF_ASSERT_FALSE( save );

    CleanupStack::PopAndDestroy( form );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKForm::TestFDeletingL
// -----------------------------------------------------------------------------
TInt CTestSDKForm::TestFDeletingL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKFormControl* form = new (ELeave) CTestSDKFormControl;
    CleanupStack::PushL( form );
    STIF_ASSERT_NOT_NULL( form );
    
    form->ConstructL();
    form->PrepareLC( R_TESTSDK_FORM_DIALOG );
    CleanupStack::Pop( form );
    
    form->SetFormFlag();
    TBool save = form->Deleting();
    STIF_ASSERT_TRUE( save );

    CleanupStack::PopAndDestroy( form );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKForm::TestFSetFormFlagL
// -----------------------------------------------------------------------------
TInt CTestSDKForm::TestFSetFormFlagL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKFormControl* form = new (ELeave) CTestSDKFormControl;
    CleanupStack::PushL( form );
    STIF_ASSERT_NOT_NULL( form );
    
    form->ConstructL();
    form->PrepareLC( R_TESTSDK_FORM_DIALOG );
    CleanupStack::Pop( form );
    
    form->SetFormFlag();

    CleanupStack::PopAndDestroy( form );
    
    return KErrNone;
    
    }

//  [End of File]
