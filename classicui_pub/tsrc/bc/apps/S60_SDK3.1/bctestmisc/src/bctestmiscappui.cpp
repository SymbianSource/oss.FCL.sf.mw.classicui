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
* Description:         test bc for misc control api(s)
*
*/









#include <avkon.hrh>
#include <aknsutils.h>

#include "bctestmiscappui.h"
#include "bctestmisc.hrh"
#include "bctestmiscview.h"
#include "bctestutil.h"
#include "bctestmisccase.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// ctro do nothing
// ---------------------------------------------------------------------------
//
CBCTestMiscAppUi::CBCTestMiscAppUi()
    {
    }

// ---------------------------------------------------------------------------
// symbian 2nd phase ctor
// ---------------------------------------------------------------------------
//
void CBCTestMiscAppUi::ConstructL()
    {
    BaseConstructL();
    AknsUtils::SetAvkonSkinEnabledL( ETrue );

	// init test util
	iTestUtil = CBCTestUtil::NewL();

    // init view
    CBCTestMiscView* view = CBCTestMiscView::NewL(iTestUtil);
    CleanupStack::PushL( view );
    AddViewL( view );
    CleanupStack::Pop( view );    
    
    ActivateLocalViewL( view->Id() );

	// Add test case here.
	_LIT( KTestCase, "Misc test case" );
    iTestUtil->AddTestCaseL( CBCTestMiscCase::NewL( view->Container() ),
        KTestCase );
    }

// ----------------------------------------------------------------------------
// CBCTestMiscAppUi::~CBCTestMiscAppUi()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestMiscAppUi::~CBCTestMiscAppUi()
    { 
	delete iTestUtil;
    }

// ----------------------------------------------------------------------------
// handle menu command events
// ----------------------------------------------------------------------------
//
void CBCTestMiscAppUi::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EAknSoftkeyBack:
        case EEikCmdExit:
            {
            Exit();            
            }
            break;
        default:
            break;
        }    
    }
