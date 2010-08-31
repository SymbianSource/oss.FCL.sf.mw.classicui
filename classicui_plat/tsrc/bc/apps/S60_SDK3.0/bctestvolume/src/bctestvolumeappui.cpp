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
* Description:         test bc for volume control api(s)
*
*/








#include <avkon.hrh>
#include <aknsutils.h>

#include "BCTestVolumeAppUi.h"
#include "BCTestVolumeView.h"
#include "BCTestvolume.hrh"

//
// TO DO:
// include the bc test framework header files here
//
#include "bctestutil.h"     
#include "bctestsuite.h"

//
// TO DO: 
// add all your concrete test case headers here:
//
#include "testVolumeSettingPage.h"
#include "testVolumeNaviPane.h"
#include "bctestothers.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// ctro do nothing
// ---------------------------------------------------------------------------
//
CBCTestVolumeAppUi::CBCTestVolumeAppUi()
    {
    }

// ---------------------------------------------------------------------------
// symbian 2nd phase ctor
// ---------------------------------------------------------------------------
//
void CBCTestVolumeAppUi::ConstructL()
    {
    BaseConstructL();
    AknsUtils::SetAvkonSkinEnabledL( ETrue );

    // Creates CBCTestVolumeView class object.
    CBCTestVolumeView* view = CBCTestVolumeView::NewL();
    CleanupStack::PushL( view );
    AddViewL( view ); // transfer ownership to CAknViewAppUi.
    CleanupStack::Pop(); // view

    ActivateLocalViewL( view->Id() );

    // init bc test framework    
    iTestUtil = CBCTestUtil::NewL();

    // add all test cases....
    iTestUtil->AddTestCaseL( CTestVolumeSettingPage::NewL(view), _L("CTestVolumeSettingPage") );
    iTestUtil->AddTestCaseL( CTestVolumeNaviPane::NewL(view), _L("CTestVolumeNaviPane") );
	iTestUtil->AddTestCaseL( CTestOthers::NewL(view), _L("CTestOthers") );
    }

// ----------------------------------------------------------------------------
// CBCTestVolumeAppUi::~CBCTestVolumeAppUi()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestVolumeAppUi::~CBCTestVolumeAppUi()
    {
    delete iTestUtil;
    }

// ----------------------------------------------------------------------------
// handle menu command events
// ----------------------------------------------------------------------------
//
void CBCTestVolumeAppUi::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EProgCmdAutoTest:
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
    if(aCommand > EBCTestVolumeCmdEmptyOutline && aCommand <= EBCTestVolumeCmdMaxOutline)
        {
        iTestUtil->RunL(aCommand);
        }
    }

// End of File
