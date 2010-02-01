/*
* Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         appui
*
*/









#include <avkon.hrh>
#include <aknsutils.h>

#include "bctestmix50appui.h"
#include "bctestmix50.hrh"
#include "bctestmix50view.h"
#include "bctestutil.h"
#include "bctestmix50case.h"

_LIT( KTestCaseTitle, "mix test case" );


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CBCTestMix50AppUi::CBCTestMix50AppUi()
// constructor do nothing
// ---------------------------------------------------------------------------
//
CBCTestMix50AppUi::CBCTestMix50AppUi()
    {
    }


// ---------------------------------------------------------------------------
// CBCTestMix50AppUi::ConstructL()
// symbian 2nd phase constructor
// ---------------------------------------------------------------------------
//
void CBCTestMix50AppUi::ConstructL()
    {
    BaseConstructL();
    AknsUtils::SetAvkonSkinEnabledL( ETrue );

    // init test util
    iTestUtil = CBCTestUtil::NewL();

    // init view
    CBCTestMix50View* view = CBCTestMix50View::NewL( iTestUtil );
    CleanupStack::PushL( view );
    AddViewL( view );
    CleanupStack::Pop( view );

    ActivateLocalViewL( view->Id() );

    // Add test case here.
    iTestUtil->AddTestCaseL( CBCTestMix50Case::NewL( view->Container() ),
                             KTestCaseTitle );

    }


// ---------------------------------------------------------------------------
// CBCTestMix50AppUi::~CBCTestMix50AppUi()
// Destructor.
// ---------------------------------------------------------------------------
//
CBCTestMix50AppUi::~CBCTestMix50AppUi()
    {
    delete iTestUtil;
    }


// ---------------------------------------------------------------------------
// CBCTestMix50AppUi::HandleCommandL()
// handle menu command events
// ---------------------------------------------------------------------------
//
void CBCTestMix50AppUi::HandleCommandL( TInt aCommand )
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
