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
* Description:         test bc for previewpopup control api(s)
*
*/








#include <avkon.hrh>
#include <aknsutils.h>

#include "bctestpreviewpopupAppUi.h"
#include "bctestpreviewpopup.hrh"
#include "bctestpreviewpopupview.h"
#include "bctestutil.h"
#include "bctestpreviewpopupcase.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// ctro do nothing
// ---------------------------------------------------------------------------
//
CBCTestPreviewPopupAppUi::CBCTestPreviewPopupAppUi()
    {
    }

// ---------------------------------------------------------------------------
// symbian 2nd phase ctor
// ---------------------------------------------------------------------------
//
void CBCTestPreviewPopupAppUi::ConstructL()
    {
    BaseConstructL();
    AknsUtils::SetAvkonSkinEnabledL( ETrue );

	// init test util
	iTestUtil = CBCTestUtil::NewL();

    // init view
    CBCTestPreviewPopupView* view = CBCTestPreviewPopupView::NewL(iTestUtil);
    CleanupStack::PushL( view );
    AddViewL( view );
    CleanupStack::Pop( view );    
    
    ActivateLocalViewL( view->Id() );

	// Add test case here.
    iTestUtil->AddTestCaseL( CBCTestPreviewPopupCase::NewL( view->Container() ),
        _L("PreviewPopup test case") );
    }

// ----------------------------------------------------------------------------
// CBCTestPreviewPopupAppUi::~CBCTestPreviewPopupAppUi()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestPreviewPopupAppUi::~CBCTestPreviewPopupAppUi()
    { 
	delete iTestUtil;
    }

// ----------------------------------------------------------------------------
// handle menu command events
// ----------------------------------------------------------------------------
//
void CBCTestPreviewPopupAppUi::HandleCommandL( TInt aCommand )
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
