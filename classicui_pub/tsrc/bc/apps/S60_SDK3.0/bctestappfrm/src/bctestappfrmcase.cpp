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
#include <s32strm.h> 
#include "bctestappfrmcase.h"
#include "bctestappfrmcontainer.h"
#include "bctestappfrm.hrh"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestAppFrmCase* CBCTestAppFrmCase::NewL( 
    CBCTestAppFrmContainer* aContainer )
    {
    CBCTestAppFrmCase* self = new( ELeave ) CBCTestAppFrmCase( 
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
CBCTestAppFrmCase::CBCTestAppFrmCase( 
    CBCTestAppFrmContainer* aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestAppFrmCase::~CBCTestAppFrmCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestAppFrmCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestAppFrmCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestAppFrmCase::BuildScriptL()
    { 
    // Add script as your need.   
    //AddTestL( LeftCBA, KeyOK, TEND );    
    }
    
// ---------------------------------------------------------------------------
// CBCTestAppFrmCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestAppFrmCase::RunL( TInt aCmd )
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
// CBCTestAppFrmCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestAppFrmCase::PrepareCaseL( TInt aCmd )
    {        
    switch ( aCmd )
        {
        case EBCTestCmdOutline1:
            // Here is a simple demo. You should create your control 
            // instead of this.
            //iControl = new( ELeave ) CCoeControl();            
            //iControl->SetContainerWindowL( *iContainer );
            //iControl->MakeVisible( ETrue );
            break;
        default:
            break;
        }
    // Pass the owner of iControl to iContainer.
    //iContainer->SetControl( iControl );
    }

// ---------------------------------------------------------------------------
// CBCTestAppFrmCase::ReleaseCaseL
// ---------------------------------------------------------------------------
//   
void CBCTestAppFrmCase::ReleaseCaseL()
    {
    // let container delete the component control.
    iContainer->ResetControl();
    iControl = NULL;
    }

// ---------------------------------------------------------------------------
// CBCTestAppFrmCase::TestLayoutDecorator
// ---------------------------------------------------------------------------
//    
void CBCTestAppFrmCase::TestFunction()
    {
    // Test some API here
    }
    
