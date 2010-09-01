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
#include <eikenv.h>

#include <bctestmixmcl.rsg>

#include "bctestmixmclhapticscase.h"
#include "bctestmixmclcontainer.h"
#include "bctestmixmcl.hrh"
#include "bctestmixmclhelper.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CBCTestMixMCLCase::NewL()
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestMixMCLCase* CBCTestMixMCLCase::NewL( CBCTestMixMCLContainer* aContainer )
    {
    CBCTestMixMCLCase* self = new( ELeave ) CBCTestMixMCLCase( aContainer );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// CBCTestMixMCLCase::CBCTestMixMCLCase()
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestMixMCLCase::CBCTestMixMCLCase( CBCTestMixMCLContainer* aContainer )
    : iContainer( aContainer )
    {
    }


// ---------------------------------------------------------------------------
// CBCTestMixMCLCase::~CBCTestMixMCLCase()
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestMixMCLCase::~CBCTestMixMCLCase()
    {
    delete iHapticsHelper;
    }


// ---------------------------------------------------------------------------
// CBCTestMixMCLCase::ConstructL()
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestMixMCLCase::ConstructL()
    {
    BuildScriptL();
    iEnv = CEikonEnv::Static(); 
    }


// ---------------------------------------------------------------------------
// CBCTestMixMCLCase::BuildScriptL()
//
// ---------------------------------------------------------------------------
//
void CBCTestMixMCLCase::BuildScriptL()
    {
    // Add script
    const TInt scripts[] =
        {
        DELAY(1),
        LeftCBA, LeftCBA,                 // Outline 1
        TEND
        };

    AddTestScriptL( scripts, sizeof( scripts ) / sizeof( TInt ) );
    }


// ---------------------------------------------------------------------------
// CBCTestMixMCLCase::RunL()
//
// ---------------------------------------------------------------------------
//
void CBCTestMixMCLCase::RunL( TInt aCmd )
    {

    switch ( aCmd )
        {
        case EBCTestCmdOutline1:
            {
            TestHapticsL();
            }

            break;
        default:
            break;
        }
    }


// ---------------------------------------------------------------------------
// CBCTestMixMCLCase::TestHapticsL()
// ( menu item -1- )
// ---------------------------------------------------------------------------
//
void CBCTestMixMCLCase::TestHapticsL()
    {
	_LIT( KNewL1, "CHWRMHaptics::NewL() 2 parameters" );
	
	CHWRMHaptics* haptics = CHWRMHaptics::NewL( NULL, NULL );
	CleanupStack::PushL(haptics);
	AssertNotNullL( haptics, KNewL1 );
	CleanupStack::PopAndDestroy(haptics);
	
	iHapticsHelper = CBCTestHWRMHapticsHelperActiveObject::NewL( this );
	iHapticsHelper->StartTestL();
    }
