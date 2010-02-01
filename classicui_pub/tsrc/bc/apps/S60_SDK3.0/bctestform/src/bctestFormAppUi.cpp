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
* Description:         For bctestform application
*
*/








// INCLUDE FILES
#include <avkon.hrh>

#include <aknsutils.h>

#include "BCTestFormAppUi.h"
#include "BCTestFormView.h"
#include "BCTestForm.hrh"

#include "bctestutil.h"
#include "bctestsuite.h"
#include "bctestformcase.h"
// ============================ MEMBER FUNCTIONS ===============================

// ----------------------------------------------------------------------------
// CBCTestFormAppUi::CBCTestFormAppUi()
// C++ default constructor can NOT contain any code, that
// might leave.
// ----------------------------------------------------------------------------
//
CBCTestFormAppUi::CBCTestFormAppUi()
    {
    }

// ----------------------------------------------------------------------------
// void CBCTestFormAppUi::ConstructL()
// Symbian 2nd phase constructor can leave.
// ----------------------------------------------------------------------------
//
void CBCTestFormAppUi::ConstructL()
    {
    _LIT( strClassName,"CTestForm" );
    BaseConstructL();
    AknsUtils::SetAvkonSkinEnabledL( ETrue );

    // Creates CBCTestFormView class object.
    CBCTestFormView* view = CBCTestFormView::NewL();
    CleanupStack::PushL( view );
    AddViewL( view ); // transfer ownership
    CleanupStack::Pop();
   
    ActivateLocalViewL( view->Id() );
    
    iTestUtil = CBCTestUtil::NewL();
    
    iTestUtil->AddTestCaseL( CBCTestFormCase::NewL( view ),strClassName );
    }
// ----------------------------------------------------------------------------
// CBCTestFormAppUi::~CBCTestFormAppUi()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestFormAppUi::~CBCTestFormAppUi()
    {
    delete iTestUtil;
    }

// ----------------------------------------------------------------------------
// void CBCTestFormAppUi::HandleCommandL( TInt )
// Handles the commands.
// ----------------------------------------------------------------------------
//
void CBCTestFormAppUi::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EBCTestFormCmdAutotest:
            if ( iTestUtil )
                {                
                iTestUtil->RunL(); 
                }
            return;
        case EEikCmdExit:
            {
            Exit();
            return;
            }
        default:
            break;
        }
    //
    // map the UI event to test cases in test suite.
    //    
    if(aCommand > EBCTestFormCmdEmptyOutline && aCommand <= EBCTestFormCmdMaxOutline)
        {
        iTestUtil->RunL( aCommand );
        }
    }
