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
* Description:         Implements test bc for note control testcase.
*
*/









#include <w32std.h>
#include <coecntrl.h>
#include <aknnotecontrol.h>
#include <aknnotedialog.h>
#include <bctestnote.rsg>

#include "bctestnotecontrolcase.h"
#include "bctestnotecontainer.h"
#include "bctestnote.hrh"
#include "autotestcommands.h" 

// constant
const TInt KBCTestTextNumber = 100;
const TInt KOne = 1;
const TInt KTwo = 2;
const TInt KFour = 4;
const TInt KSeven = 7;
const TInt KTen = 10;

_LIT( KNoteControlCreateComment, "NoteControl created" );
_LIT( KSetTextNumberLComment, 
    "NoteControl's SetTextNumberL() invoked" );
_LIT( KSetImageLComment, "NoteControl's SetImageL() invoked" );
_LIT( KSetIconLComment, "NoteControl's SetIconL() invoked" );
_LIT( KSetTextPluralityLComment, 
    "NoteControl's SetTextPluralityL() invoked" );
_LIT( KResetTextComment, "NoteControl's ResetText() invoked" );
_LIT( KText, "Hello" );
_LIT( KSetDynamicTextLComment, 
    "NoteControl's SetDynamicTextL() invoked" );
_LIT( KTextAgain, "This is note control" );
_LIT( KSetTextLComment, "NoteControl's SetTextL() invoked" );
_LIT( KSetLabelReserveLengthLComment, 
    "NoteControl's SetLabelReserveLengthL() invoked" );
_LIT( KNoteHeightComment, "NoteControl's NoteHeight() invoked" );
_LIT( KNoteWidthComment, "NoteControl's NoteWidth() invoked" );
_LIT( KSetAnimationLComment, "NoteControl's SetAnimationL() invoked" );
_LIT( KHandlePointerEventLComment, 
    "NoteControl's HandlePointerEventL() invoked" );
_LIT( KGetProgressInfoComment, 
    "NoteControl's GetProgressInfo() invoked" );
_LIT( KLabel1, "Label1" );
_LIT( KLabel2, "Label2" );
_LIT( KLabel3, "Label3" );
_LIT( KUpdateLabelsComment, 
    "NoteControl's UpdateLabels() invoked" );
_LIT( KLabel, "This is update text!" );
_LIT( KUpdateAndFormatLabelsLComment, 
    "NoteControl's UpdateAndFormatLabelsL() invoked" );

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestNoteControlCase* CBCTestNoteControlCase::NewL(
    CBCTestNoteContainer* aContainer )
    {
    CBCTestNoteControlCase* self = new( ELeave ) CBCTestNoteControlCase(
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
CBCTestNoteControlCase::CBCTestNoteControlCase(
    CBCTestNoteContainer* aContainer ) : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestNoteControlCase::~CBCTestNoteControlCase()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestNoteControlCase::ConstructL()
    {
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestNoteControlCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestNoteControlCase::BuildScriptL()
    {
    const TInt scripts[] =
        {
        //outline20
        DELAY( KOne ),// delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA,
        REP( Down, KSeven ),
        KeyOK,
        KeyOK,
        WAIT( KFour ),

        //outline21
        LeftCBA,
        REP( Down, KSeven ),
        KeyOK,
        Down,
        KeyOK
        };
    AddTestScriptL( scripts, sizeof( scripts ) / sizeof( TInt ) );    
    }

// ---------------------------------------------------------------------------
// CBCTestNoteControlCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestNoteControlCase::RunL( TInt aCmd )
    {
    if ( ( aCmd < EBCTestNoteCmdOutline20 ) 
        || ( aCmd > EBCTestNoteCmdOutline21 ) )
        {
        return;
        }
    switch ( aCmd )
        {
        case EBCTestNoteCmdOutline20:
            TestNoteControlL();
            break;
        case EBCTestNoteCmdOutline21:
     
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestNoteControlCase::TestNoteControlL
// ---------------------------------------------------------------------------
//
void CBCTestNoteControlCase::TestNoteControlL()
    {
    CAknNoteDialog* noteDialog = new( ELeave ) CAknNoteDialog( 
        CAknNoteDialog::EWarningTone, CAknNoteDialog::EShortTimeout );    
    CleanupStack::PushL( noteDialog );
    
    noteDialog->PrepareLC( R_BCTESTNOTE_NO_ICON );
    
    iNoteControl = STATIC_CAST ( CAknNoteControl*, 
        noteDialog->Control( EBCTestNoteCtrlIdNoImageNote ) );     
    AssertNotNullL( iNoteControl, KNoteControlCreateComment );  
    
    iNoteControl->SetTextNumberL( KBCTestTextNumber );
    AssertTrueL( ETrue, KSetTextNumberLComment );
    
    iNoteControl->SetImageL( NULL );
    AssertTrueL( ETrue, KSetImageLComment );
        
    iNoteControl->SetIconL( NULL );
    AssertTrueL( ETrue, KSetIconLComment );
    
    iNoteControl->SetTextPluralityL( ETrue );
    AssertTrueL( ETrue, KSetTextPluralityLComment );
    
    iNoteControl->ResetText();
    AssertTrueL( ETrue, KResetTextComment );  
    
    iNoteControl->SetDynamicTextL( KText );
    AssertTrueL( ETrue, KSetDynamicTextLComment );

    iNoteControl->SetTextL( KTextAgain, KTwo );
    AssertTrueL( ETrue, KSetTextLComment );    
    
    iNoteControl->SetLabelReserveLengthL( KTen, KTen, KTen );
    AssertTrueL( ETrue, KSetLabelReserveLengthLComment ); 
    
    iNoteControl->NoteHeight();
    AssertTrueL( ETrue, KNoteHeightComment );    
    
    iNoteControl->NoteWidth();
    AssertTrueL( ETrue, KNoteWidthComment );  
    
    iNoteControl->SetAnimationL( R_BCTESTNOTE_BITMAP_ANIMATION );
    AssertTrueL( ETrue, KSetAnimationLComment );
    
    TPointerEvent tPointerEvent;
    tPointerEvent.iType = TPointerEvent::EButton2Up;
    iNoteControl->HandlePointerEventL( tPointerEvent );
    AssertTrueL( ETrue, KHandlePointerEventLComment ); 
    
    iNoteControl->GetProgressInfo();
    AssertTrueL( ETrue, KGetProgressInfoComment ); 
    
    iNoteControl->UpdateLabels( KLabel1, KLabel2, KLabel3 );
    AssertTrueL( ETrue, KUpdateLabelsComment ); 

    iNoteControl->UpdateAndFormatLabelsL( KLabel );
    AssertTrueL( ETrue, KUpdateAndFormatLabelsLComment );     
        
    CleanupStack::Pop( noteDialog );
    noteDialog->RunLD();
    }
    
  
    
    





    
   

    
