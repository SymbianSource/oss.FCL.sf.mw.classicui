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
* Description:         Implements test bc for note dialog testcase.
*
*/









#include <w32std.h>
#include <coecntrl.h>
#include <aknnotecontrol.h>
#include <aknnotedialog.h>
#include <eikdialg.h>
#include <bctestnote.rsg>

#include "bctestnotedialogcase.h"
#include "bctestsubnotedialog.h"
#include "bctestnotecontainer.h"
#include "bctestnote.hrh"
#include "autotestcommands.h"

// constant
const TInt KBCTestTextNumber = 100;
const TInt KOne = 1;
const TInt KTwo = 2;
const TInt KSix = 6;

_LIT( KNoteDialogCreateComment, "NoteDialog created" );
_LIT( KSetTimeoutComment, "NoteDialog's SetTimeout() invoked" );
_LIT( KSetToneComment, "NoteDialog's SetTone() invoked" );
_LIT( KSetTextWrappingComment, "NoteDialog's SetTextWrapping() invoked" );
_LIT( KSetTextProcessingComment, 
    "NoteDialog's SetTextProcessing() invoked" );
_LIT( KSetTextNumberLComment, "NoteDialog's SetTextNumberL() invoked" );
_LIT( KSetImageLComment, "NoteDialog's SetImageL() invoked" );
_LIT( KSetIconLComment, "NoteDialog's SetIconL() invoked" );
_LIT( KSetTextPluralityLComment, 
    "NoteDialog's SetTextPluralityL() invoked" );
_LIT( KCurrentLabel, "This is note dialog" );
_LIT( KSetCurrentLabelLComment, 
    "NoteDialog's SetCurrentLabelL() invoked" );
_LIT( KRunDlgLDTTComment, "NoteDialog's RunDlgLD() invoked" );
_LIT( KRunDlgLDTComment, "NoteDialog's RunDlgLD() invoked(OverLoad)" );
_LIT( KRunDlgLDComment, 
    "NoteDialog's RunDlgLD() invoked(OverLoad again)" );
_LIT( KRunDlgLDLastComment, 
    "NoteDialog's RunDlgLD() invoked last time" );
_LIT( KOfferKeyEventLComment, 
    "NoteDialog's OfferKeyEventL() invoked" );
_LIT( KHandlePointerEventLComment, 
    "NoteDialog's HandlePointerEventL() invoked" );
_LIT( KExecuteDlgLDComment, "NoteDialog's ExecuteDlgLD() invoked" );
_LIT( KExecuteDlgLDOverComment, 
    "NoteDialog's ExecuteDlgLD() invoked(OverLoad)" );
_LIT( KExecuteDlgLDOverLoadComment, 
    "NoteDialog's ExecuteDlgLD() invoked(OverLoad again)" );
_LIT( KSetNoMemoryAllocationComment, 
    "NoteDialog's SetNoMemoryAllocation() invoked" );

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestNoteDialogCase* CBCTestNoteDialogCase::NewL(
    CBCTestNoteContainer* aContainer )
    {
    CBCTestNoteDialogCase* self = new( ELeave ) CBCTestNoteDialogCase(
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
CBCTestNoteDialogCase::CBCTestNoteDialogCase(
    CBCTestNoteContainer* aContainer ) : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestNoteDialogCase::~CBCTestNoteDialogCase()
    {
    if ( iNoteDialog )
        {
        delete iNoteDialog;
        iNoteDialog = NULL;
        }
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestNoteDialogCase::ConstructL()
    {
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestNoteDialogCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestNoteDialogCase::BuildScriptL()
    {
    const TInt scripts[] =
        {
        //outline17
        DELAY( KOne ),// delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA,
        REP( Down, KSix ),
        KeyOK,
        KeyOK,     //Invoke RunDlgLD() four times
        KeyOK,
        KeyOK,
        KeyOK,
        WAIT( 15 ),  

        //outline18
        LeftCBA,
        REP( Down, KSix ),
        KeyOK,
        REP( Down, KOne ),
        KeyOK,      //Invoke RunDlgLD() three times
        DELAY( KOne ),
                
        //outline19
        LeftCBA,
        REP( Down, KSix ),
        KeyOK,
        REP( Down, KTwo ),
        KeyOK
        };
    AddTestScriptL( scripts, sizeof( scripts ) / sizeof( TInt ) );    
    }

// ---------------------------------------------------------------------------
// CBCTestNoteDialogCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestNoteDialogCase::RunL( TInt aCmd )
    {
    if ( ( aCmd < EBCTestNoteCmdOutline17 ) 
        || ( aCmd > EBCTestNoteCmdOutline19 ) )
        {
        return;
        }
    switch ( aCmd )
        {
        case EBCTestNoteCmdOutline17:
            TestSetFunctionsL();
            break;
        case EBCTestNoteCmdOutline18:
            TestOtherPublicFunctionsL();
            break;
        case EBCTestNoteCmdOutline19:
            TestProtectedFunctionsL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestNoteDialogCase::TestSetFunctionsL
// ---------------------------------------------------------------------------
//
void CBCTestNoteDialogCase::TestSetFunctionsL()
    {
    iNoteDialog = new( ELeave ) CAknNoteDialog();      
    AssertNotNullL( iNoteDialog, KNoteDialogCreateComment );
    
    iNoteDialog->SetTimeout( CAknNoteDialog::EShortTimeout );
    AssertTrueL( ETrue, KSetTimeoutComment );
        
    iNoteDialog->SetTone( CAknNoteDialog::EConfirmationTone );
    AssertTrueL( ETrue, KSetToneComment );
    
    iNoteDialog->SetTextWrapping( ETrue );
    AssertTrueL( ETrue, KSetTextWrappingComment );
    
    iNoteDialog->SetTextProcessing( ETrue );
    AssertTrueL( ETrue, KSetTextProcessingComment );
    
    iNoteDialog->SetTextNumberL( KBCTestTextNumber );
    AssertTrueL( ETrue, KSetTextNumberLComment );
    
    iNoteDialog->SetImageL( NULL );
    AssertTrueL( ETrue, KSetImageLComment );
        
    iNoteDialog->SetIconL( NULL );
    AssertTrueL( ETrue, KSetIconLComment );

    iNoteDialog->SetTextPluralityL( ETrue );
    AssertTrueL( ETrue, KSetTextPluralityLComment );
    
    iNoteDialog->SetCurrentLabelL( R_BCTESTNOTE_NO_ICON, KCurrentLabel );
    AssertTrueL( ETrue, KSetCurrentLabelLComment );    

    delete iNoteDialog;
    iNoteDialog = NULL; 
    
    CAknNoteDialog* tmpNoteDialog = new( ELeave ) CAknNoteDialog();
    tmpNoteDialog->PrepareLC( R_BCTESTNOTE_IMAGE_NOTE );
    tmpNoteDialog->RunDlgLD( CAknNoteDialog::EShortTimeout,
         CAknNoteDialog::EConfirmationTone );
    AssertTrueL( ETrue, KRunDlgLDTTComment );
    tmpNoteDialog = NULL; 
    
    tmpNoteDialog = new( ELeave ) CAknNoteDialog();
    tmpNoteDialog->PrepareLC( R_BCTESTNOTE_IMAGE_NOTE );
    tmpNoteDialog->RunDlgLD( CAknNoteDialog::EWarningTone );          
    AssertTrueL( ETrue, KRunDlgLDTComment );
    tmpNoteDialog = NULL;
    
    tmpNoteDialog = new( ELeave ) CAknNoteDialog();
    tmpNoteDialog->PrepareLC( R_BCTESTNOTE_IMAGE_NOTE );
    tmpNoteDialog->RunDlgLD(); 
    AssertTrueL( ETrue, KRunDlgLDComment ); 
    tmpNoteDialog = NULL;
    
    tmpNoteDialog = new( ELeave ) CAknNoteDialog();
    tmpNoteDialog->PrepareLC( R_BCTESTNOTE_IMAGE_NOTE );    
    tmpNoteDialog->RunDlgLD( KTwo ); 
    AssertTrueL( ETrue, KRunDlgLDLastComment );            
    }
    
// ---------------------------------------------------------------------------
// CBCTestNoteDialogCase::TestOtherPublicFunctionsL
// ---------------------------------------------------------------------------
//
void CBCTestNoteDialogCase::TestOtherPublicFunctionsL()
    {
    CAknNoteDialog* tNoteDialog = new( ELeave ) CAknNoteDialog();      
    
    CleanupStack::PushL( tNoteDialog );
    
    TKeyEvent keyEvent;
    keyEvent.iCode = EKeyCBA1;
    tNoteDialog->OfferKeyEventL( keyEvent, EEventKey ); 
    AssertTrueL( ETrue, KOfferKeyEventLComment );

    TPointerEvent tPointerEvent;
    tPointerEvent.iType = TPointerEvent::EButton2Up;
    tNoteDialog->HandlePointerEventL( tPointerEvent );
    AssertTrueL( ETrue, KHandlePointerEventLComment );    

    CleanupStack::Pop( tNoteDialog );

    tNoteDialog->ExecuteDlgLD( R_BCTESTNOTE_NO_ICON, KTwo );
    AssertTrueL( ETrue, KExecuteDlgLDComment ); 
    tNoteDialog = NULL;
    
    tNoteDialog = new( ELeave ) CAknNoteDialog();
    tNoteDialog->ExecuteDlgLD( CAknNoteDialog::EConfirmationTone,
        R_BCTESTNOTE_NO_ICON );
    AssertTrueL( ETrue, KExecuteDlgLDOverComment ); 
    tNoteDialog = NULL;
    
    tNoteDialog = new( ELeave ) CAknNoteDialog();
    tNoteDialog->ExecuteDlgLD( CAknNoteDialog::EShortTimeout, 
        CAknNoteDialog::EConfirmationTone, R_BCTESTNOTE_NO_ICON );
    AssertTrueL( ETrue, KExecuteDlgLDOverLoadComment ); 
    tNoteDialog = NULL;      
        
    }
    
// ---------------------------------------------------------------------------
// CBCTestNoteDialogCase::TestProtectedFunctionsL
// ---------------------------------------------------------------------------
//
void CBCTestNoteDialogCase::TestProtectedFunctionsL()
    {        
    CAknNoteDialog* tmpNoteDialog = new( ELeave ) CAknNoteDialog();
    tmpNoteDialog->PrepareLC( R_BCTESTNOTE_IMAGE_NOTE );
    
    CBCTestSubNoteDialog* subNoteDialog = 
        static_cast<CBCTestSubNoteDialog*> ( tmpNoteDialog );
    
    subNoteDialog->SetNoMemoryAllocation();
    AssertTrueL( ETrue, KSetNoMemoryAllocationComment );

    CleanupStack::PopAndDestroy( tmpNoteDialog );  
    }
