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
#include <eikenv.h>
#include <aknsdrawutils.h> 
#include <aknsframebackgroundcontrolcontext.h> 

#include "bctestdrawutilscase.h"
#include "bctestskinscontainer.h"
#include "bctestskins.hrh"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestDrawUtilsCase* CBCTestDrawUtilsCase::NewL( 
    CBCTestSkinsContainer* aContainer )
    {
    CBCTestDrawUtilsCase* self = new( ELeave ) CBCTestDrawUtilsCase( 
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
CBCTestDrawUtilsCase::CBCTestDrawUtilsCase( 
    CBCTestSkinsContainer* aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDrawUtilsCase::~CBCTestDrawUtilsCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDrawUtilsCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestDrawUtilsCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestDrawUtilsCase::BuildScriptL()
    { 
    // Add script as your need.   
    AddTestL( DELAY( 1 ), LeftCBA, KeyOK, TEND );    
    }
    
// ---------------------------------------------------------------------------
// CBCTestDrawUtilsCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestDrawUtilsCase::RunL( TInt aCmd )
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
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestDrawUtilsCase::TestFunctionL
// ---------------------------------------------------------------------------
//   
void CBCTestDrawUtilsCase::TestFunctionL()
    {
    iContainer->DrawTest();
    _LIT( KMsg, "Test AknsDrawUtils API");
    AssertNotNullL( iContainer, KMsg );
    
    // Test CAknsFrameBackgroundControlContext API
    TAknsItemID frameId;
    TRect outerRect( 0, 0, 100, 100 );
    TRect innerRect( 10, 10, 90, 90 );
    TBool absolute = ETrue;
    CAknsFrameBackgroundControlContext* ctrlContext = 
        CAknsFrameBackgroundControlContext::NewL ( frameId, outerRect, 
        innerRect, absolute );
    CleanupStack::PushL( ctrlContext );
    ctrlContext->SetFramePartRect( outerRect, EAknsFrameIndexTl );     
    _LIT( KSetFramePartRect, "CAknsFrameBackgroundControlContext::SetFramePartRect" );
    AssertNotNullL( ctrlContext, KSetFramePartRect );
    CleanupStack::PopAndDestroy( ctrlContext );    
    }
    
