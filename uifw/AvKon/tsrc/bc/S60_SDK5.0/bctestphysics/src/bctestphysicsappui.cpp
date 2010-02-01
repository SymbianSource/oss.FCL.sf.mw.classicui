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
* Description:  container
*
*/

#include <avkon.hrh>
#include <aknsutils.h>

#include "bctestphysicsappui.h"
#include "bctestphysics.hrh"
#include "bctestphysicsview.h"
#include "bctestutil.h"
#include "bctestphysicscase.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// constructor do nothing
// ---------------------------------------------------------------------------
//
CBCTestPhysicsAppUi::CBCTestPhysicsAppUi()
    {
    }

// ---------------------------------------------------------------------------
// symbian 2nd phase constructor
// ---------------------------------------------------------------------------
//
void CBCTestPhysicsAppUi::ConstructL()
    {
    BaseConstructL();
    AknsUtils::SetAvkonSkinEnabledL( ETrue );

	// init test util
	iTestUtil = CBCTestUtil::NewL();

    // init view
    CBCTestPhysicsView* view = CBCTestPhysicsView::NewL( iTestUtil );
    CleanupStack::PushL( view );
    AddViewL( view );
    CleanupStack::Pop( view );    
    
    ActivateLocalViewL( view->Id() );

	// Add test case here.
    iTestUtil->AddTestCaseL( CBCTestPhysicsCase::NewL( view->Container() ),
        _L( "Physics test case" ) );
    }

// ---------------------------------------------------------------------------
// CBCTestPhysicsAppUi::~CBCTestPhysicsAppUi()
// Destructor.
// ---------------------------------------------------------------------------
//
CBCTestPhysicsAppUi::~CBCTestPhysicsAppUi()
    { 
	delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// handle menu command events
// ---------------------------------------------------------------------------
//
void CBCTestPhysicsAppUi::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EAknSoftkeyBack:
        case EEikCmdExit:
            {
            Exit();
            return;
            }
        default:
            break;
        }    
    }

// End of File
