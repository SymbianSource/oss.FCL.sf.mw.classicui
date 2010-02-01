/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Implements test bc for wait dialog testcase.
*
*/









#include <w32std.h>
#include <coecntrl.h>
#include <aknwaitdialog.h>
#include <eikdialg.h>
#include <aknprogresstimer.h>
#include <eikprogi.h> 
#include <bctestnote.rsg>

#include "bctestwaitdialogcase.h"
#include "bctestnotecontainer.h"
#include "bctestnote.hrh"
#include "autotestcommands.h"

// constant
const TInt KBCTestNoteProgressbarFinalValue = 200;
const TInt KBCTestNoteProgressbarIncrement = 5;
const TInt KBCTestNoteProgressbarInterval = 20;
const TInt KOne = 1;
const TInt KTwo = 2;
const TInt KThree = 3;

_LIT( KEikDialogCreateComment, "eikdialog created" );
_LIT( KWaitDialogCreateComment, "WaitDialog created" );
_LIT( KWHandlePointerEventLComment, 
    "WaitDialog's HandlePointerEventL() invoked" );
_LIT( KPRunLDComment, "ProgressDialog's RunLD() invoked" );
_LIT( KWaitDialogCreateOverLoadComment, "WaitDialog created(overload)" );
_LIT( KProgressDialogCreateComment, "progressdialog created" );
_LIT( KPOfferKeyEventLComment, 
    "ProgressDialog's OfferKeyEventL() invoked" );
_LIT( KSetCallbackComment, "ProgressDialog SetCallback() invoked" );
_LIT( KTProgressDialogCreateComment, "tprogressdialog created" );
_LIT( KTExecuteLDComment, "ProgressDialog ExecuteLD() invoked" );
_LIT( KGetProgressInfoLComment, 
    "ProgressDialog GetProgressInfoL() invoked" );
_LIT( KTProcessFinishedLComment, 
    "ProgressDialog ProcessFinishedL() invoked" );

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestWaitDialogCase* CBCTestWaitDialogCase::NewL(
    CBCTestNoteContainer* aContainer )
    {
    CBCTestWaitDialogCase* self = new( ELeave ) CBCTestWaitDialogCase(
        aContainer );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestWaitDialogCase::CBCTestWaitDialogCase(
    CBCTestNoteContainer* aContainer ) : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestWaitDialogCase::~CBCTestWaitDialogCase()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestWaitDialogCase::ConstructL()
    {
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestWaitDialogCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestWaitDialogCase::BuildScriptL()
    {
    const TInt scripts[] =
        {
        //outline7
        DELAY( KOne ),// delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA,
        Down,
        KeyOK,
        KeyOK,
        WAIT( KThree ),
        RightCBA,

        //outline8
        LeftCBA,
        Down,
        KeyOK,
        REP( Down, KOne ),
        KeyOK,
        WAIT( KTwo ),
        KeyOK,
        
        //outline9
        LeftCBA,
        Down,
        KeyOK,
        REP( Down, KTwo ),
        KeyOK
        };
    AddTestScriptL( scripts, sizeof( scripts ) / sizeof( TInt ) );    
    }

// ---------------------------------------------------------------------------
// CBCTestWaitDialogCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestWaitDialogCase::RunL( TInt aCmd )
    {
    if ( ( aCmd < EBCTestNoteCmdOutline07 ) 
        || ( aCmd > EBCTestNoteCmdOutline09 ) )
        {
        return;
        }
    switch ( aCmd )
        {
        case EBCTestNoteCmdOutline07:
            TestWaitDialogL();
            break;
        case EBCTestNoteCmdOutline08:
            TestProgressDialogL();        
            break;
        case EBCTestNoteCmdOutline09:
            TestProgressOtherFunctionsL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestWaitDialogCase::TestWaitDialogL
// ---------------------------------------------------------------------------
//
void CBCTestWaitDialogCase::TestWaitDialogL()
    {
    iEikDialog = new( ELeave ) CEikDialog();
    AssertNotNullL( iEikDialog, KEikDialogCreateComment );
    CAknWaitDialog* tmpWaitDialog = new( ELeave ) CAknWaitDialog ( NULL );
    CleanupStack::PushL( tmpWaitDialog );
    AssertNotNullL( tmpWaitDialog, KWaitDialogCreateComment );
    
    TPointerEvent tPointerEvent;
    tPointerEvent.iType = TPointerEvent::EButton2Up;
    tmpWaitDialog->HandlePointerEventL( tPointerEvent );
    AssertTrueL( ETrue, KWHandlePointerEventLComment );
        
    CleanupStack::Pop( tmpWaitDialog );
    tmpWaitDialog->PrepareLC( R_BCTESTNOTE_WAIT_NOTE_FOR_AKNWAITDIALOG );
    tmpWaitDialog->RunLD();
    AssertTrueL( ETrue, KPRunLDComment );
        
    CAknWaitDialog* tWaitDialog = new( ELeave ) CAknWaitDialog ( 
        &iEikDialog, ETrue );
    CleanupStack::PushL( tWaitDialog );
    AssertNotNullL( tWaitDialog, KWaitDialogCreateOverLoadComment );
    CleanupStack::Pop( tWaitDialog );
    
    delete iEikDialog;
    iEikDialog = NULL;    
    delete tWaitDialog;    
    }
    
// ---------------------------------------------------------------------------
// CBCTestWaitDialogCase::TestProgressDialogL
// ---------------------------------------------------------------------------
//
void CBCTestWaitDialogCase::TestProgressDialogL()
    {
    CAknProgressDialog* progressDialog = new( ELeave ) CAknProgressDialog( 
        KBCTestNoteProgressbarFinalValue, 
        KBCTestNoteProgressbarIncrement, 
        KBCTestNoteProgressbarInterval, NULL );
    CleanupStack::PushL( progressDialog );
    AssertNotNullL( progressDialog, KProgressDialogCreateComment ); 
        
    progressDialog->PrepareLC( R_BCTESTNOTE_PROGRESS_NOTE );
    progressDialog->RunLD();
    
    TKeyEvent keyEvent;
    keyEvent.iCode = EKeyCBA1;
    progressDialog->OfferKeyEventL( keyEvent, EEventKeyUp ); 
    AssertTrueL( ETrue, KPOfferKeyEventLComment );
    
    progressDialog->SetCallback( NULL );
    AssertTrueL( ETrue, KSetCallbackComment );
    
    CleanupStack::Pop( progressDialog );
       
    }
    
// ---------------------------------------------------------------------------
// CBCTestWaitDialogCase::TestProgressOtherFunctionsL
// ---------------------------------------------------------------------------
//
void CBCTestWaitDialogCase::TestProgressOtherFunctionsL()
    {
    iEikDialog = new( ELeave ) CEikDialog();
    CAknProgressDialog* tProgressDialog = new( ELeave ) 
        CAknProgressDialog( &iEikDialog );
    CleanupStack::PushL( tProgressDialog );    
    AssertNotNullL( tProgressDialog, KTProgressDialogCreateComment ); 

    CleanupStack::Pop( tProgressDialog );
    delete iEikDialog;
    iEikDialog = NULL; 
    tProgressDialog->ExecuteLD( R_BCTESTNOTE_PROGRESS_NOTE );     
    AssertTrueL( ETrue, KTExecuteLDComment );
    
    tProgressDialog->GetProgressInfoL();
    AssertTrueL( ETrue, KGetProgressInfoLComment ); 

    tProgressDialog->ProcessFinishedL();
    AssertTrueL( ETrue, KTProcessFinishedLComment );    
    }    
    
    





    
   

    
