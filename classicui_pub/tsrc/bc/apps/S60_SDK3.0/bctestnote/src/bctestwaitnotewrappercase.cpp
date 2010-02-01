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
* Description:         Implements test bc for wait note wrapper testcase.
*
*/









#include <w32std.h>
#include <coecntrl.h>
#include <aknwaitnotewrapper.h>
#include <bctestnote.rsg>

#include "bctestwaitnotewrappercase.h"
#include "bctestsubwaitnotewrapper.h"
#include "bctestnotecontainer.h"
#include "bctestnote.hrh"
#include "autotestcommands.h"

// constant
const TInt KOne = 1;
const TInt KTwo = 2;
const TInt KFive = 5;

_LIT( KWaitNoteWrapperComment, "Waitnotewrapper created" );
_LIT( KExecuteLComment, "Waitnotewrapper's ExecuteL invoked" );
_LIT( KPrompt, "Please waiting..." );
_LIT( KExecuteLOverComment, 
    "Waitnotewrapper's ExecuteL invoked(Overload)" );

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestWaitNoteWrapperCase* CBCTestWaitNoteWrapperCase::NewL(
    CBCTestNoteContainer* aContainer )
    {
    CBCTestWaitNoteWrapperCase* self = 
        new( ELeave ) CBCTestWaitNoteWrapperCase( aContainer );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestWaitNoteWrapperCase::CBCTestWaitNoteWrapperCase(
    CBCTestNoteContainer* aContainer ) : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestWaitNoteWrapperCase::~CBCTestWaitNoteWrapperCase()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestWaitNoteWrapperCase::ConstructL()
    {
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestWaitNoteWrapperCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestWaitNoteWrapperCase::BuildScriptL()
    {
    const TInt scripts[] =
        {
        //outline15
        DELAY( KOne ),// delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA,
        REP( Down, KFive ),
        KeyOK,
        KeyOK,
        WAIT( KTwo ),
        RightCBA,

        //outline16
        LeftCBA,
        REP( Down, KFive ),
        KeyOK,
        Down,
        KeyOK,
        WAIT( KTwo ),
        RightCBA      
        };
    AddTestScriptL( scripts, sizeof( scripts ) / sizeof( TInt ) );    
    }

// ---------------------------------------------------------------------------
// CBCTestWaitNoteWrapperCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestWaitNoteWrapperCase::RunL( TInt aCmd )
    {
    if ( ( aCmd < EBCTestNoteCmdOutline15 ) 
        || ( aCmd > EBCTestNoteCmdOutline16 ) )
        {
        return;
        }
    switch ( aCmd )
        {
        case EBCTestNoteCmdOutline15:
            TestWaitNoteWrapperL();
            break;
        case EBCTestNoteCmdOutline16:
            TestOtherFunctionsL();
            break;            
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestWaitNoteWrapperCase::TestWaitNoteWrapperL
// ---------------------------------------------------------------------------
//
void CBCTestWaitNoteWrapperCase::TestWaitNoteWrapperL()
    {
    iWaitNoteWrapper = CAknWaitNoteWrapper::NewL();    
    iSubWaitNoteWrapper = CBCTestSubWaitNoteWrapper::NewL();    
    AssertNotNullL( iWaitNoteWrapper, KWaitNoteWrapperComment );
    
    iWaitNoteWrapper->ExecuteL( R_BCTESTNOTE_WAIT_NOTE_WRAPPER, 
        *iSubWaitNoteWrapper, ETrue );
    AssertTrueL( ETrue, KExecuteLComment );
    
    delete iSubWaitNoteWrapper;
    iSubWaitNoteWrapper = NULL;
    delete iWaitNoteWrapper;
    iWaitNoteWrapper = NULL;
	    
    }   
    
// ---------------------------------------------------------------------------
// CBCTestWaitNoteWrapperCase::TestOtherFunctionsL
// ---------------------------------------------------------------------------
//
void CBCTestWaitNoteWrapperCase::TestOtherFunctionsL()
    {
    iWaitNoteWrapper = CAknWaitNoteWrapper::NewL();    
    iSubWaitNoteWrapper = CBCTestSubWaitNoteWrapper::NewL(); 
    
    iWaitNoteWrapper->ExecuteL( R_BCTESTNOTE_WAIT_NOTE_WRAPPER, 
        *iSubWaitNoteWrapper, KPrompt, ETrue );
    AssertTrueL( ETrue, KExecuteLOverComment );
    
    delete iSubWaitNoteWrapper;
    iSubWaitNoteWrapper = NULL;
    delete iWaitNoteWrapper;
    iWaitNoteWrapper = NULL;    
    }    

    
    





    
   

    
