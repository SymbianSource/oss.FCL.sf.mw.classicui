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
* Description:  appui
*
*/


#include <avkon.hrh>
#include <aknsutils.h>

#include "bctestdommix50appui.h"
#include "bctestdommix50.hrh"
#include "bctestdommix50view.h"
#include "bctestutil.h"
#include "bctestdommix50case.h"

_LIT( KTestCaseTitle, "dom mix test case" );


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CBCTestDomMix50AppUi::CBCTestDomMix50AppUi()
// constructor do nothing
// ---------------------------------------------------------------------------
//
CBCTestDomMix50AppUi::CBCTestDomMix50AppUi()
    {
    }


// ---------------------------------------------------------------------------
// CBCTestDomMix50AppUi::ConstructL()
// symbian 2nd phase constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomMix50AppUi::ConstructL()
    {
    BaseConstructL();
    AknsUtils::SetAvkonSkinEnabledL( ETrue );

    // init test util
    iTestUtil = CBCTestUtil::NewL();

    // init view
    CBCTestDomMix50View* view = CBCTestDomMix50View::NewL( iTestUtil );
    CleanupStack::PushL( view );
    AddViewL( view );
    CleanupStack::Pop( view );

    ActivateLocalViewL( view->Id() );

    // Add test case here.
    iTestUtil->AddTestCaseL( CBCTestDomMix50Case::NewL( view->Container() ),
                             KTestCaseTitle );

    }


// ---------------------------------------------------------------------------
// CBCTestDomMix50AppUi::~CBCTestDomMix50AppUi()
// Destructor.
// ---------------------------------------------------------------------------
//
CBCTestDomMix50AppUi::~CBCTestDomMix50AppUi()
    {
    delete iTestUtil;
    }


// ---------------------------------------------------------------------------
// CBCTestDomMix50AppUi::HandleCommandL()
// handle menu command events
// ---------------------------------------------------------------------------
//
void CBCTestDomMix50AppUi::HandleCommandL( TInt aCommand )
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
