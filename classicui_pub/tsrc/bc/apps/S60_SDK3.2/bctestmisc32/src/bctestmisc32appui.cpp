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

#include "bctestmisc32appui.h"
#include "bctestmisc32.hrh"
#include "bctestmisc32view.h"
#include "bctestutil.h"
#include "bctestmisc32case.h"
#include "bctestlistdatacase.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// ctro do nothing
// ---------------------------------------------------------------------------
//
CBCTestmisc32AppUi::CBCTestmisc32AppUi()
    {
    }

// ---------------------------------------------------------------------------
// symbian 2nd phase ctor
// ---------------------------------------------------------------------------
//
void CBCTestmisc32AppUi::ConstructL()
    {
    BaseConstructL();
    AknsUtils::SetAvkonSkinEnabledL( ETrue );

	// init test util
	iTestUtil = CBCTestUtil::NewL();

    // init view
    CBCTestmisc32View* view = CBCTestmisc32View::NewL(iTestUtil);
    CleanupStack::PushL( view );
    AddViewL( view );
    CleanupStack::Pop( view );    
    
    ActivateLocalViewL( view->Id() );

	// Add test case here.
    iTestUtil->AddTestCaseL( CBCTestmisc32Case::NewL( view->Container() ),
        _L("misc test case") );
    iTestUtil->AddTestCaseL( CBCTestListDataCase::NewL( view->Container() ),
        _L("list data test case") );
    }

// ----------------------------------------------------------------------------
// CBCTestmisc32AppUi::~CBCTestmisc32AppUi()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestmisc32AppUi::~CBCTestmisc32AppUi()
    { 
	delete iTestUtil;
    }

// ----------------------------------------------------------------------------
// handle menu command events
// ----------------------------------------------------------------------------
//
void CBCTestmisc32AppUi::HandleCommandL( TInt aCommand )
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
