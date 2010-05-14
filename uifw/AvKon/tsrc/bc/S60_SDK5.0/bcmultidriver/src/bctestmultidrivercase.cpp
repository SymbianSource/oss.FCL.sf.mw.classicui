/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test case
*
*/


#include <w32std.h>
#include <coecntrl.h>

#include "BCTestMultiDrivercase.h"
#include "BCTestMultiDrivercontainer.h"
#include "BCTestMultiDriver.hrh"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CMultiDriverCase* CMultiDriverCase::NewL( 
    CMultiDriverContainer* aContainer )
    {
    CMultiDriverCase* self = new( ELeave ) CMultiDriverCase( 
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
CMultiDriverCase::CMultiDriverCase( 
    CMultiDriverContainer* aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CMultiDriverCase::~CMultiDriverCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CMultiDriverCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CMultiDriverCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CMultiDriverCase::BuildScriptL()
    { 
    // Add script as your need.   
    AddTestL( DELAY(1), LeftCBA, LeftCBA, TEND );  
    AddTestL( LeftCBA, Down, LeftCBA, TEND );  
    }
    
// ---------------------------------------------------------------------------
// CMultiDriverCase::RunL
// ---------------------------------------------------------------------------
//
void CMultiDriverCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline1 || aCmd > EBCTestCmdOutline1 )
        {
        return;
        }

    switch ( aCmd )  
        {
        case EBCTestCmdOutline1:
            TestFunctionL();
            break;
        case EBCTestCmdOutline2:
            TestFunction2L();
            break;    
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CMultiDriverCase::TestFunctionL
// ---------------------------------------------------------------------------
//    
void CMultiDriverCase::TestFunctionL()
    {
    }
    
void CMultiDriverCase::TestFunction2L()
    {
    }
    