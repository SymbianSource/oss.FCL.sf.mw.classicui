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

#include <aknfontprovider.h>

#include "BCExtendedFontApicase.h"
#include "BCExtendedFontApicontainer.h"
#include "BCExtendedFontApi.hrh"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCExtendedFontApiCase* CBCExtendedFontApiCase::NewL( CBCExtendedFontApiContainer* 
    aContainer )
    {
    CBCExtendedFontApiCase* self = new( ELeave ) CBCExtendedFontApiCase( 
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
CBCExtendedFontApiCase::CBCExtendedFontApiCase( CBCExtendedFontApiContainer* 
    aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCExtendedFontApiCase::~CBCExtendedFontApiCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCExtendedFontApiCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCExtendedFontApiCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCExtendedFontApiCase::BuildScriptL()
    { 
    // Add script as your need.   
    AddTestL( DELAY(1), LeftCBA, KeyOK, TEND );    
    }
    
// ---------------------------------------------------------------------------
// CBCExtendedFontApiCase::RunL
// ---------------------------------------------------------------------------
//
void CBCExtendedFontApiCase::RunL( TInt aCmd )
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
// CBCExtendedFontApiCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCExtendedFontApiCase::PrepareCaseL( TInt aCmd )
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
// CBCExtendedFontApiCase::ReleaseCaseL
// ---------------------------------------------------------------------------
//   
void CBCExtendedFontApiCase::ReleaseCaseL()
    {
    // let container delete the component control.
    iContainer->ResetControl();
    iControl = NULL;
    }

// ---------------------------------------------------------------------------
// CBCExtendedFontApiCase::TestLayoutDecorator
// ---------------------------------------------------------------------------
//    
void CBCExtendedFontApiCase::TestFunction()
    {
    CWsScreenDevice* screenDev = CCoeEnv::Static()->ScreenDevice();
    TAknFontSpecification aknFs(0);
    TFontSpec newFontSpec;
    TInt foundIndex(KErrNotFound);
    TInt err = AknFontProvider::GetFontSpecFromMetrics(*screenDev, 0, aknFs, newFontSpec, foundIndex);
    _LIT( getFontSpecFromMetrics, " GetFontSpecFromMetrics() " );
    AssertTrueL( err == KErrNone, getFontSpecFromMetrics );    
    }
    
