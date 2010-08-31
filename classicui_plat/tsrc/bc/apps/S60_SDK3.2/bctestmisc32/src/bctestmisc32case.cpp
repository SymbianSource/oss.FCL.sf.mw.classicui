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
#include <eikmfne.h>

#include "bctestmisc32case.h"
#include "bctestmisc32container.h"
#include "bctestmisc32.hrh"
#include "bctestmisc32appui.h"

// ======== ASSERTION COMMENTS ========

_LIT ( KEikMfneSetFeature, "CEikMfne::SetFeature" );
_LIT ( KEikMfneGetFeature, "CEikMfne::GetFeature" );
_LIT ( KEikMfneSupportsFeature, "CEikMfne::SupportsFeature" );

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestmisc32Case* CBCTestmisc32Case::NewL( 
    CBCTestmisc32Container* aContainer )
    {
    CBCTestmisc32Case* self = new( ELeave ) CBCTestmisc32Case( 
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
CBCTestmisc32Case::CBCTestmisc32Case( 
    CBCTestmisc32Container* aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestmisc32Case::~CBCTestmisc32Case()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestmisc32Case::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestmisc32Case::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestmisc32Case::BuildScriptL()
    { 
    // Add script as your need.   
    AddTestL( DELAY(1), LeftCBA, KeyOK, TEND );    
    AddTestL( LeftCBA, REP( Down, 2 ), KeyOK, TEND );    
    }
    
// ---------------------------------------------------------------------------
// CBCTestmisc32Case::RunL
// ---------------------------------------------------------------------------
//
void CBCTestmisc32Case::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline1 || aCmd > EBCTestCmdOutline6 )
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
            TestAknViewAppUiL();
            break;
        case EBCTestCmdOutline6:
            TestEikMfneL();
            break;            
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestmisc32Case::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestmisc32Case::PrepareCaseL( TInt aCmd )
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
// CBCTestmisc32Case::ReleaseCaseL
// ---------------------------------------------------------------------------
//   
void CBCTestmisc32Case::ReleaseCaseL()
    {
    // let container delete the component control.
    iContainer->ResetControl();
    iControl = NULL;
    }

// ---------------------------------------------------------------------------
// CBCTestmisc32Case::TestLayoutDecorator
// ---------------------------------------------------------------------------
//    
void CBCTestmisc32Case::TestAknViewAppUiL()
    {
    CBCTestmisc32AppUi *iTestAppUi = static_cast<CBCTestmisc32AppUi*>
                                     ( CEikonEnv::Static()->EikAppUi() );
    
    //iTestAppUi->EnableLocalScreenClearer( EFalse);
    _LIT( KEnableLocalScreenClearer, "CAknViewAppUi::EnableLocalScreenClearer() invoked" );
    AssertTrueL( ETrue, KEnableLocalScreenClearer );
    }
    
// ---------------------------------------------------------------------------
// CBCTestmisc32Case::TestEikMfneL
// ---------------------------------------------------------------------------
//    
void CBCTestmisc32Case::TestEikMfneL()
    {
    CEikMfne* mfne = new ( ELeave ) CEikMfne;
    CleanupStack::PushL( mfne );
    
    // To create the extension
    mfne->CreateFieldArrayL( 1 );
    
    mfne->SetFeature( 0, 0 );
    AssertTrueL( ETrue, KEikMfneSetFeature );
    
    TInt tmpFeature;
    mfne->GetFeature( 0, tmpFeature );
    AssertTrueL( ETrue, KEikMfneGetFeature );
    
    mfne->SupportsFeature( 0 );
    AssertTrueL( ETrue, KEikMfneSupportsFeature );
    
    CleanupStack::PopAndDestroy(); // mfne
    }
    
