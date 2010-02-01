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
#include <eikalign.h>

#include "bctesteikaligncase.h"
#include "bctesteikbctrlcontainer.h"
#include "bctesteikbctrl.hrh"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTesteikalignCase* CBCTesteikalignCase::NewL(
    CBCTesteikbctrlContainer* aContainer )
    {
    CBCTesteikalignCase* self = new( ELeave ) CBCTesteikalignCase(
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
CBCTesteikalignCase::CBCTesteikalignCase(
    CBCTesteikbctrlContainer* aContainer )
    : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//

CBCTesteikalignCase::~CBCTesteikalignCase()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------

void CBCTesteikalignCase::ConstructL()
    {
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTesteikalignCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTesteikalignCase::BuildScriptL()
    {
    // Add script as your need.
    AddTestL( DELAY( 1 ), LeftCBA, Down, KeyOK, TEND );
    }

// ---------------------------------------------------------------------------
// CBCTesteikalignCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTesteikalignCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestAlignApi || aCmd > EBCTestAlignApi )
       {
        return;
       }

    switch ( aCmd )
        {
        case EBCTestAlignApi:
            TestFunctionL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTesteikalignCase::TestLayoutDecorator
// ---------------------------------------------------------------------------
//
void CBCTesteikalignCase::TestFunctionL()
    {
    // Test some API here
    _LIT(creatAlign," create alignCtrol ");
    _LIT(setMargin," invoke SetAllMarginsto() " );
    _LIT(setAlign," call SetAlignment()" );

    CEikAlignedControl *alignCtrl = new ( ELeave )  CEikAlignedControl();
    AssertNotNullL( alignCtrl, creatAlign);

    //invoke SetAllMarginsTo
    alignCtrl->SetAllMarginsTo( TInt(2) );
    AssertTrueL( ETrue,setMargin );

    //invoke SetAlignment()
    alignCtrl->SetAlignment(EHLeftVBottom);
    AssertTrueL( ETrue,setAlign );

    TPointerEvent pEvnt;
     pEvnt.iType = TPointerEvent::EButton1Down;
     alignCtrl->HandlePointerEventL( pEvnt );
     _LIT( ptEvnt," Test HandlePointerEventL()" );
     AssertTrueL( ETrue, ptEvnt);

    delete alignCtrl;
    }

