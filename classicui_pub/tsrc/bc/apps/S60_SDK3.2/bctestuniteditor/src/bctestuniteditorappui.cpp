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
* Description:         test bc for unit editor control api(s)
*
*/








#include <avkon.hrh>
#include <aknsutils.h>

#include "bctestuniteditorAppUi.h"
#include "bctestuniteditor.hrh"
#include "bctestuniteditorview.h"
#include "bctestutil.h"
#include "bctestuniteditorcase.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// ctro do nothing
// ---------------------------------------------------------------------------
//
CBCTestUnitEditorAppUi::CBCTestUnitEditorAppUi()
    {
    }

// ---------------------------------------------------------------------------
// symbian 2nd phase ctor
// ---------------------------------------------------------------------------
//
void CBCTestUnitEditorAppUi::ConstructL()
    {
    BaseConstructL();
    AknsUtils::SetAvkonSkinEnabledL( ETrue );

	// init test util
	iTestUtil = CBCTestUtil::NewL();

    // init view
    CBCTestUnitEditorView* view = CBCTestUnitEditorView::NewL(iTestUtil);
    CleanupStack::PushL( view );
    AddViewL( view );
    CleanupStack::Pop( view );    
    
    ActivateLocalViewL( view->Id() );

	// Add test case here.
    iTestUtil->AddTestCaseL( CBCTestUnitEditorCase::NewL( view->Container() ),
        _L("UnitEditor test case") );
    }

// ----------------------------------------------------------------------------
// CBCTestUnitEditorAppUi::~CBCTestUnitEditorAppUi()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestUnitEditorAppUi::~CBCTestUnitEditorAppUi()
    { 
	delete iTestUtil;
    }

// ----------------------------------------------------------------------------
// handle menu command events
// ----------------------------------------------------------------------------
//
void CBCTestUnitEditorAppUi::HandleCommandL( TInt aCommand )
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
