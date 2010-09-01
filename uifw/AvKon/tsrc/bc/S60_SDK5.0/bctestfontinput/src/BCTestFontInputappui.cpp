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

#include "BCTestFontInputappui.h"
#include "BCTestFontInput.hrh"
#include "BCTestFontInputview.h"
#include "bctestutil.h"
#include "BCTestFontInputcase.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// constructor do nothing
// ---------------------------------------------------------------------------
//
CBCTestFontInputAppUi::CBCTestFontInputAppUi()
    {
    }

// ---------------------------------------------------------------------------
// symbian 2nd phase constructor
// ---------------------------------------------------------------------------
//
void CBCTestFontInputAppUi::ConstructL()
    {
    BaseConstructL();
    AknsUtils::SetAvkonSkinEnabledL( ETrue );

	// init test util
	iTestUtil = CBCTestUtil::NewL();

    // init view
    CBCTestFontInputView* view = CBCTestFontInputView::NewL( iTestUtil );
    CleanupStack::PushL( view );
    AddViewL( view );
    CleanupStack::Pop( view );    
    
    ActivateLocalViewL( view->Id() );

	// Add test case here.
//    iTestUtil->AddTestCaseL( CBCTestFontInputCase::NewL( view->Container() ),
//        _L( "Template test case" ) );
    }

// ---------------------------------------------------------------------------
// CBCTestFontInputAppUi::~CBCTestFontInputAppUi()
// Destructor.
// ---------------------------------------------------------------------------
//
CBCTestFontInputAppUi::~CBCTestFontInputAppUi()
    { 
	delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// handle menu command events
// ---------------------------------------------------------------------------
//
void CBCTestFontInputAppUi::HandleCommandL( TInt aCommand )
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
