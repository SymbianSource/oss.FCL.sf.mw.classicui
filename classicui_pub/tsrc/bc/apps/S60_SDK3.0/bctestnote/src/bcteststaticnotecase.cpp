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
* Description:         Implements test bc for static note testcase.
*
*/









#include <w32std.h>
#include <coecntrl.h>
#include <aknstaticnotedialog.h>
#include <bctestnote.rsg>

#include "bcteststaticnotecase.h"
#include "bctestnotecontainer.h"
#include "bctestnote.hrh"
#include "autotestcommands.h"
#include "bctestsubstaticnote.h"

// constant
const TInt KOne = 1;
const TInt KTwo = 2;
const TInt KFive = 5;

_LIT( KEikDialogCreateComment, "eikdialog created" );
_LIT( KStaticNoteDialogCreateComment, "StaticNote created" );
_LIT( KSetNumberOfBordersComment, 
    "StaticNote's SetNumberOfBorders() invoked" );
_LIT( KHandlePointerEventLComment, 
    "StaticNote's HandlePointerEventL() invoked" );
_LIT( KSubStaticNoteComment, "SubStaticNote created" );
_LIT( KOfferKeyEventLComment, "StaticNote's OfferKeyEventL() invoked" );

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestStaticNoteCase* CBCTestStaticNoteCase::NewL(
    CBCTestNoteContainer* aContainer )
    {
    CBCTestStaticNoteCase* self = new( ELeave ) CBCTestStaticNoteCase(
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
CBCTestStaticNoteCase::CBCTestStaticNoteCase(
    CBCTestNoteContainer* aContainer ) : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestStaticNoteCase::~CBCTestStaticNoteCase()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestStaticNoteCase::ConstructL()
    {
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestStaticNoteCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestStaticNoteCase::BuildScriptL()
    {
    const TInt scripts[] =
        {
        //outline10
        DELAY( KOne ),// delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA,
        REP( Down, KTwo ),
        KeyOK,
        KeyOK,

        //outline11
        LeftCBA,
        REP( Down, KTwo ),
        KeyOK,
        REP( Down, KOne ),
        KeyOK,
        };
    AddTestScriptL( scripts, sizeof( scripts ) / sizeof( TInt ) );    
    }

// ---------------------------------------------------------------------------
// CBCTestStaticNoteCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestStaticNoteCase::RunL( TInt aCmd )
    {
    if ( ( aCmd < EBCTestNoteCmdOutline10 ) 
        || ( aCmd > EBCTestNoteCmdOutline11 ) )
        {
        return;
        }
    switch ( aCmd )
        {
        case EBCTestNoteCmdOutline10:
            TestStaticNoteL();
            break;
        case EBCTestNoteCmdOutline11:
            TestProtectedFunctionsL();      
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestStaticNoteCase::TestStaticNoteL
// ---------------------------------------------------------------------------
//
void CBCTestStaticNoteCase::TestStaticNoteL()
    {
    iEikDialog = new( ELeave ) CEikDialog();
    AssertNotNullL( iEikDialog, KEikDialogCreateComment );
    iStaticNote = new( ELeave ) CAknStaticNoteDialog ( &iEikDialog );
    AssertNotNullL( iStaticNote, KStaticNoteDialogCreateComment );  
    
    iStaticNote->SetNumberOfBorders( KFive );    
    AssertTrueL( ETrue, KSetNumberOfBordersComment );

    TPointerEvent tPointerEvent;
    tPointerEvent.iType = TPointerEvent::EButton2Up;
    iStaticNote->HandlePointerEventL( tPointerEvent );    
    AssertTrueL( ETrue, KHandlePointerEventLComment ); 
    
    delete iEikDialog;
    iEikDialog = NULL;
    delete iStaticNote;
    iStaticNote = NULL;
    
    }   
    
// ---------------------------------------------------------------------------
// CBCTestStaticNoteCase::TestProtectedFunctionsL
//
//
void CBCTestStaticNoteCase::TestProtectedFunctionsL()
    {
    CBCTestSubStaticNote* subStaticNote = CBCTestSubStaticNote::NewL();
    AssertNotNullL( subStaticNote, KSubStaticNoteComment );

	subStaticNote->PrepareLC(R_BCTEST_STATIC_TEXT_NOTE);
    TKeyEvent keyEvent;
    keyEvent.iCode = EKeyOK;
    subStaticNote->OfferKeyEventL( keyEvent, EEventKey );    
    AssertTrueL( ETrue, KOfferKeyEventLComment );

	CleanupStack::PopAndDestroy();	//PrepareLC
    }




    
   

    
