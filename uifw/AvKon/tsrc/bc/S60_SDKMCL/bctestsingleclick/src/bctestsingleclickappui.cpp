/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  AppUI class of bctestsingleclick.
*
*/

#include <avkon.hrh>
#include <AknsUtils.h>

#include "bctestsingleclickappui.h"
#include "bctestsingleclick.hrh"
#include "bctestsingleclickview.h"
#include "bctestutil.h"
#include "bctestsingleclickcase.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// constructor do nothing
// ---------------------------------------------------------------------------
//
CBCTESTSingleClickAppUi::CBCTESTSingleClickAppUi()
    {
    }

// ---------------------------------------------------------------------------
// symbian 2nd phase constructor
// ---------------------------------------------------------------------------
//
void CBCTESTSingleClickAppUi::ConstructL()
    {
    BaseConstructL(EAknSingleClickCompatible);
    AknsUtils::SetAvkonSkinEnabledL( ETrue );

	// init test util
    iTestUtil = CBCTestUtil::NewL();

    // init view
    CBCTESTSingleClickView* view = CBCTESTSingleClickView::NewL( iTestUtil );
    CleanupStack::PushL( view );
    AddViewL( view );
    CleanupStack::Pop( view );    
    
    ActivateLocalViewL( view->Id() );

	// Add test case here.
    iTestUtil->AddTestCaseL( CBCTESTSingleClickCase::NewL( view->Container() ),
        _L( "Single Click test case" ) );        
    }

// ---------------------------------------------------------------------------
// CBCTESTSingleClickAppUi::~CBCTESTSingleClickAppUi()
// Destructor.
// ---------------------------------------------------------------------------
//
CBCTESTSingleClickAppUi::~CBCTESTSingleClickAppUi()
    { 
    delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// handle menu command events
// ---------------------------------------------------------------------------
//
void CBCTESTSingleClickAppUi::HandleCommandL( TInt aCommand )
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
