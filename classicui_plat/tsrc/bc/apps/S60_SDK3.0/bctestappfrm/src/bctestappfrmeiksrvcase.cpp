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
#include <eiksrv.h>
#include <w32std.h>
#include "bctestappfrmeiksrvcase.h"
#include "bctestappfrmcontainer.h"
#include "bctestappfrm.hrh"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestAppFrmEikSrvCase* CBCTestAppFrmEikSrvCase::NewL( 
    CBCTestAppFrmContainer* aContainer )
    {
    CBCTestAppFrmEikSrvCase* self = new( ELeave ) CBCTestAppFrmEikSrvCase( 
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
CBCTestAppFrmEikSrvCase::CBCTestAppFrmEikSrvCase( 
    CBCTestAppFrmContainer* aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestAppFrmEikSrvCase::~CBCTestAppFrmEikSrvCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestAppFrmEikSrvCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestAppFrmEikSrvCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestAppFrmEikSrvCase::BuildScriptL()
    { 
    // Add script as your need.   
        const TInt scripts[] =
        {
        DELAY(1),        // delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA, 
        REP(Down, 9),
        LeftCBA
        };
    AddTestScriptL(scripts, sizeof(scripts)/sizeof(TInt));   
    }
    
// ---------------------------------------------------------------------------
// CBCTestAppFrmEikSrvCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestAppFrmEikSrvCase::RunL( TInt aCmd )
    {
    if ( aCmd !=EBCTestEikSrv)
        {
        return;
        }
    // Call release before prepare to let container has time to draw the 
    // control created in PrepareCaseL.
    ReleaseCaseL();
    PrepareCaseL( aCmd );
    TestFunction();
    }

// ---------------------------------------------------------------------------
// CBCTestAppFrmEikSrvCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestAppFrmEikSrvCase::PrepareCaseL( TInt aCmd )
    {        
    switch ( aCmd )
        {
        case EBCTestEikSrv:
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
// CBCTestAppFrmEikSrvCase::ReleaseCaseL
// ---------------------------------------------------------------------------
//   
void CBCTestAppFrmEikSrvCase::ReleaseCaseL()
    {
    // let container delete the component control.
    iContainer->ResetControl();
    iControl = NULL;
    }

// ---------------------------------------------------------------------------
// CBCTestAppFrmEikSrvCase::TestLayoutDecorator
// ---------------------------------------------------------------------------
//    
void CBCTestAppFrmEikSrvCase::TestFunction()
    {
    // Test some API here
        TestPublicFunction();
        TestProtectedFunction();  
    }
void CBCTestAppFrmEikSrvCase::TestProtectedFunction()
{
         
}
    
void CBCTestAppFrmEikSrvCase::TestPublicFunction()
{

}

