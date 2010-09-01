/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
#include <gdi.h>
#include <eikenv.h>
#include <avkon.hrh>

// test header of Api
#include <aknfontspecification.h>

#include "BCTestFontInputcase.h"
#include "BCTestFontInputcontainer.h"
#include "BCTestFontInput.hrh"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestFontInputCase* CBCTestFontInputCase::NewL( CBCTestFontInputContainer* 
    aContainer )
    {
    CBCTestFontInputCase* self = new( ELeave ) CBCTestFontInputCase( 
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
CBCTestFontInputCase::CBCTestFontInputCase( CBCTestFontInputContainer* 
    aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestFontInputCase::~CBCTestFontInputCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestFontInputCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestFontInputCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestFontInputCase::BuildScriptL()
    { 
    // Add script as your need.   
    AddTestL( DELAY( 2 ), LeftCBA, LeftCBA, TEND );
    }
    
// ---------------------------------------------------------------------------
// CBCTestFontInputCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestFontInputCase::RunL( TInt aCmd )
    {
    // Call release before prepare to let container has time to draw the 
    // control created in PrepareCaseL.
    ReleaseCaseL();
    PrepareCaseL( aCmd );
    switch ( aCmd )  
        {
        case EBCTestFontSpec:
            TestFontSpecL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestFontInputCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestFontInputCase::PrepareCaseL( TInt aCmd )
    {        
    switch ( aCmd )
        {
        case EBCTestCmdOutline1:
            // Here is a simple demo. You should create your control 
            // instead of this.
            iControl = new( ELeave ) CCoeControl();            
            iControl->SetContainerWindowL( *iContainer );
            iControl->MakeVisible( ETrue );
            break;
        default:
            break;
        }
    // Pass the owner of iControl to iContainer.
    iContainer->SetControl( iControl );
    }

// ---------------------------------------------------------------------------
// CBCTestFontInputCase::ReleaseCaseL
// ---------------------------------------------------------------------------
//   
void CBCTestFontInputCase::ReleaseCaseL()
    {
    // let container delete the component control.
    iContainer->ResetControl();
    iControl = NULL;
    }


// ---------------------------------------------------------------------------
// CBCTestFontInputCase::TestFontSpecL
// ---------------------------------------------------------------------------
//

void CBCTestFontInputCase::TestFontSpecL()
    {
    // Test some API here
    TAknFontSpecification fontSpec( 3 );
    
    fontSpec.IsOutlineEffectOn();
    _LIT( stIsOutline, " Test IsOutlineEffectOn() " );
    AssertTrueL( ETrue, stIsOutline );
    }

void CBCTestFontInputCase::TestLafEnvL()
    {

    }
