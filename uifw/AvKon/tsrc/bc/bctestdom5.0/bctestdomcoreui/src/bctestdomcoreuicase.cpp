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

#include <bctestdomcoreui.rsg>

#include "bctestdomcoreuicase.h" 
#include "bctestdomcoreuicontainer.h"
#include "bctestdomcoreui.hrh"
#include "bctestdommenusatinterface.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomCoreUiCase* CBCTestDomCoreUiCase::NewL( 
    CBCTestDomCoreUiContainer* aContainer )
    {
    CBCTestDomCoreUiCase* self = new( ELeave ) CBCTestDomCoreUiCase( 
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
CBCTestDomCoreUiCase::CBCTestDomCoreUiCase( 
    CBCTestDomCoreUiContainer* aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDomCoreUiCase::~CBCTestDomCoreUiCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomCoreUiCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomCoreUiCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestDomCoreUiCase::BuildScriptL()
    { 
    // Add script as your need.   
    AddTestL(DELAY(1), LeftCBA, KeyOK, WAIT(4), RightCBA,WAIT(10),TEND );    
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomCoreUiCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestDomCoreUiCase::RunL( TInt aCmd )
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
            TestFunctionL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestDomCoreUiCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestDomCoreUiCase::PrepareCaseL( TInt aCmd )
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
// CBCTestDomCoreUiCase::ReleaseCaseL
// ---------------------------------------------------------------------------
//   
void CBCTestDomCoreUiCase::ReleaseCaseL()
    {
    // let container delete the component control.
    iContainer->ResetControl();
    iControl = NULL;
    } 
 
// ---------------------------------------------------------------------------
// CBCTestDomCoreUiCase::TestLayoutDecorator
// ---------------------------------------------------------------------------
//    
void CBCTestDomCoreUiCase::TestFunctionL()
    {
    TestMenuSATInterfaceL();
    TestVoiceRecogL();
    TestVoiceRecognitionDialogL();
        
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomCoreUiCase::TestMenuSATInterfaceL
// ---------------------------------------------------------------------------
//    
void CBCTestDomCoreUiCase::TestMenuSATInterfaceL()
    
    {
    CBCTestDomMenuSATInterface *menuSI = 
                        new( ELeave ) CBCTestDomMenuSATInterface();
    CleanupStack::PushL( menuSI );//push
    _LIT( msiLogInit, "CMenuSATInterface::CMenuSATInterface()" );
    AssertNotNullL( menuSI, msiLogInit );

    _LIT( testValue, "MenuSATI" );
    menuSI->MakeSatUiVisible( EFalse, testValue );
    _LIT( msiLogSatUi, "CMenuSATInterface::MakeSatUiVisible( , )" );
    AssertNotNullL( menuSI, msiLogSatUi );

    menuSI->MakeSatUiVisible( ETrue, testValue, 6 );
    _LIT( msiLogSatUi2, "CMenuSATInterface::MakeSatUiVisible( , , )" );
    AssertNotNullL( menuSI, msiLogSatUi2 );
        
    CleanupStack::PopAndDestroy( menuSI );
    }
    
// ---------------------------------------------------------------------------
// CBCTestDomCoreUiCase::TestVoiceRecogL
// ---------------------------------------------------------------------------
//    
void CBCTestDomCoreUiCase::TestVoiceRecogL()
    {
    
    }

// ---------------------------------------------------------------------------
// CBCTestDomCoreUiCase::TestVoiceRecognitionDialogL
// ---------------------------------------------------------------------------
//    
void CBCTestDomCoreUiCase::TestVoiceRecognitionDialogL()
    {

    
    }

