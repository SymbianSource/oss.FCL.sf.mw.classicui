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
* Description:         Implements test bc for eik info dialog testcase.
*
*/









#include <w32std.h>
#include <coecntrl.h>
#include <eikinfo.h> 
#include <bctestnote.rsg>

#include "bctesteikinfodialogcase.h"
#include "bctestnotecontainer.h"
#include "bctestnote.hrh"
#include "autotestcommands.h"

// constant
const TInt KOne = 1;
const TInt KThree = 3;

_LIT( KTitle, "EIK INFO DIALOG" );
_LIT( KMsg, "This is eik info dialog!" );
_LIT( KEikInfoDialogCreateComment, "Eikinfodialog created" );
_LIT( KHandlePointerEventLComment, 
    "Eik info's HandlePointerEventL() invoked" );
_LIT( KRunDlgLDComment, "Eik info's RunDlgLD() invoked" );

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestEikInfoDialogCase* CBCTestEikInfoDialogCase::NewL(
    CBCTestNoteContainer* aContainer )
    {
    CBCTestEikInfoDialogCase* self = new( ELeave ) CBCTestEikInfoDialogCase(
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
CBCTestEikInfoDialogCase::CBCTestEikInfoDialogCase(
    CBCTestNoteContainer* aContainer ) : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestEikInfoDialogCase::~CBCTestEikInfoDialogCase()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestEikInfoDialogCase::ConstructL()
    {
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestEikInfoDialogCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestEikInfoDialogCase::BuildScriptL()
    {
    const TInt scripts[] =
        {
        //outline12
        DELAY( KOne ),// delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA,
        REP( Down, KThree ),
        KeyOK,
        KeyOK,
        LeftCBA
        };
    AddTestScriptL( scripts, sizeof( scripts ) / sizeof( TInt ) );    
    }

// ---------------------------------------------------------------------------
// CBCTestEikInfoDialogCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestEikInfoDialogCase::RunL( TInt aCmd )
    {
    if ( aCmd != EBCTestNoteCmdOutline12 )
        {
        return;
        }
    switch ( aCmd )
        {
        case EBCTestNoteCmdOutline12:
            TestEikInfoDialogL();            
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestEikInfoDialogCase::TestEikInfoDialogL
// ---------------------------------------------------------------------------
//
void CBCTestEikInfoDialogCase::TestEikInfoDialogL()
    {
    CEikInfoDialog* eikInfoDialog = 
        new( ELeave ) CEikInfoDialog( KTitle, KMsg );
    CleanupStack::PushL( eikInfoDialog );
    AssertNotNullL( eikInfoDialog, KEikInfoDialogCreateComment );

    TPointerEvent tPointerEvent;
    tPointerEvent.iType = TPointerEvent::EButton2Up;
    eikInfoDialog->HandlePointerEventL( tPointerEvent );
    AssertTrueL( ETrue, KHandlePointerEventLComment );
    
    CleanupStack::Pop( eikInfoDialog );
    eikInfoDialog->RunDlgLD( KTitle, KMsg );
    AssertTrueL( ETrue, KRunDlgLDComment );
    delete eikInfoDialog;
    eikInfoDialog = NULL;     
   
    }
