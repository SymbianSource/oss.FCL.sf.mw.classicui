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
* Description:  ?Description
*
*/


#include <avkon.hrh>
#include <aknsutils.h>

#include "bctestdomavkonpslnappui.h"
#include "bctestdomavkonpsln.hrh"
#include "bctestdomavkonpslnview.h"
#include "bctestutil.h"
#include "bctestdomakncase.h"
#include "bctestdomeikcase.h"
#include "bctestdomfindcase.h"
#include "bctestdomjplangcase.h"
#include "bctestdompslncase.h"


// ============================= MEMBER FUNCTIONS ============================

// ---------------------------------------------------------------------------
// constructor do nothing
// ---------------------------------------------------------------------------
//
CBCTestDomAvkonPslnAppUi::CBCTestDomAvkonPslnAppUi()
    {
    }

// ---------------------------------------------------------------------------
// symbian 2nd phase constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomAvkonPslnAppUi::ConstructL()
    {
    BaseConstructL();
    AknsUtils::SetAvkonSkinEnabledL( ETrue );

    // init test util
    iTestUtil = CBCTestUtil::NewL();

    // init view
    CBCTestDomAvkonPslnView* view = CBCTestDomAvkonPslnView::NewL( iTestUtil );
    CleanupStack::PushL( view );
    AddViewL( view );
    CleanupStack::Pop( view );    
    
    ActivateLocalViewL( view->Id() );

    // Add test case here.
    iTestUtil->AddTestCaseL( CBCTestDomAknCase::NewL( view->Container() ),
        _L( "domakn test case" ) );
        
    iTestUtil->AddTestCaseL( CBCTestDomEikCase::NewL( view->Container() ),
        _L( "domeik test case" ) );
    
    iTestUtil->AddTestCaseL( CBCTestDomFindCase::NewL( view->Container() ),
        _L( "domfind test case" ) );
    
    iTestUtil->AddTestCaseL( CBCTestDomJPLangCase::NewL( view->Container() ),
        _L( "domjplang test case" ) );
        
    iTestUtil->AddTestCaseL( CBCTestDomPslnCase::NewL( view->Container() ),
        _L( "dompsln test case" ) );
    }
    

// ---------------------------------------------------------------------------
// CBCTestDomAvkonPslnAppUi::~CBCTestDomAvkonPslnAppUi()
// Destructor.
// ---------------------------------------------------------------------------
//
CBCTestDomAvkonPslnAppUi::~CBCTestDomAvkonPslnAppUi()
    { 
    delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// handle menu command events
// ---------------------------------------------------------------------------
//
void CBCTestDomAvkonPslnAppUi::HandleCommandL( TInt aCommand )
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
