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

#include "bctestmixmclappui.h"
#include "bctestmixmcl.hrh"
#include "bctestmixmclview.h"
#include "bctestutil.h"
#include "bctestmixmclhapticscase.h"
#include "bctestmixmclgeneralcase.h"

_LIT( KTestCaseTitle, "mix mcl test case" );
_LIT( KGeneralCaseTestTitle, "general case test");


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CBCTestMixMCLAppUiUi::CBCTestMixMCLAppUiUi()
// constructor do nothing
// ---------------------------------------------------------------------------
//
CBCTestMixMCLAppUi::CBCTestMixMCLAppUi()
    {
    }


// ---------------------------------------------------------------------------
// CBCTestMixMCLAppUi::ConstructL()
// symbian 2nd phase constructor
// ---------------------------------------------------------------------------
//
void CBCTestMixMCLAppUi::ConstructL()
    {
    BaseConstructL();
    AknsUtils::SetAvkonSkinEnabledL( ETrue );

    // init test util
    iTestUtil = CBCTestUtil::NewL();

    // init view
    CBCTestMixMCLView* view = CBCTestMixMCLView::NewL( iTestUtil );
    CleanupStack::PushL( view );
    AddViewL( view );
    CleanupStack::Pop( view );

    ActivateLocalViewL( view->Id() );

    // Add test case here.
    iTestUtil->AddTestCaseL( CBCTestMixMCLCase::NewL( view->Container() ),
                             KTestCaseTitle );
    iTestUtil->AddTestCaseL( CBCTestMixMCLGeneralCase::NewL( view->Container(),
    		                 view), KGeneralCaseTestTitle );
    }


// ---------------------------------------------------------------------------
// CBCTestMixMCLAppUi::~CBCTestMixMCLAppUi()
// Destructor.
// ---------------------------------------------------------------------------
//
CBCTestMixMCLAppUi::~CBCTestMixMCLAppUi()
    {
    delete iTestUtil;
    }


// ---------------------------------------------------------------------------
// CBCTestMixMCLAppUi::HandleCommandL()
// handle menu command events
// ---------------------------------------------------------------------------
//
void CBCTestMixMCLAppUi::HandleCommandL( TInt aCommand )
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
