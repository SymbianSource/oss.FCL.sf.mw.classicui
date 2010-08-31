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
* Description:         test case
*
*/









#include <w32std.h>
#include <coecntrl.h>

#include "bctestgridscase.h"
#include "bctestgridscontainer.h"
#include "bctestgrids.hrh"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestGridsCase* CBCTestGridsCase::NewL( 
    CBCTestGridsContainer* aContainer )
    {
    CBCTestGridsCase* self = new( ELeave ) CBCTestGridsCase( 
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
CBCTestGridsCase::CBCTestGridsCase( 
    CBCTestGridsContainer* aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestGridsCase::~CBCTestGridsCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestGridsCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestGridsCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestGridsCase::BuildScriptL()
    { 
    // Add script as your need.   
    AddTestL( LeftCBA, KeyOK, TEND );    
    }
    
// ---------------------------------------------------------------------------
// CBCTestGridsCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestGridsCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline1 || aCmd > EBCTestCmdOutline1 )
        {
        return;
        }
    // Call release before prepare to let container has time to draw the 
    // control created in PrepareCaseL.
    ReleaseCaseL();
    PrepareCaseL( aCmd );
    switch ( aCmd )  
        {
        case EBCTestCmdOutline1:
            TestFunction();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestGridsCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestGridsCase::PrepareCaseL( TInt aCmd )
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
// CBCTestGridsCase::ReleaseCaseL
// ---------------------------------------------------------------------------
//   
void CBCTestGridsCase::ReleaseCaseL()
    {
    // let container delete the component control.
    iContainer->ResetControl();
    iControl = NULL;
    }

// ---------------------------------------------------------------------------
// CBCTestGridsCase::TestLayoutDecorator
// ---------------------------------------------------------------------------
//    
void CBCTestGridsCase::TestFunction()
    {
    // Test some API here
    }
    
