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
* Description:         test bc for template control api(s)
*
*/








#include <avkon.hrh>
#include <aknsutils.h>

#include "bctesttemplateAppUi.h"
#include "bctesttemplate.hrh"
#include "bctesttemplateview.h"
#include "bctestutil.h"
#include "bctesttemplatecase.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// ctro do nothing
// ---------------------------------------------------------------------------
//
CBCTestTemplateAppUi::CBCTestTemplateAppUi()
    {
    }

// ---------------------------------------------------------------------------
// symbian 2nd phase ctor
// ---------------------------------------------------------------------------
//
void CBCTestTemplateAppUi::ConstructL()
    {
    BaseConstructL();
    AknsUtils::SetAvkonSkinEnabledL( ETrue );

	// init test util
	iTestUtil = CBCTestUtil::NewL();

    // init view
    CBCTestTemplateView* view = CBCTestTemplateView::NewL(iTestUtil);
    CleanupStack::PushL( view );
    AddViewL( view );
    CleanupStack::Pop( view );    
    
    ActivateLocalViewL( view->Id() );

	// Add test case here.
    iTestUtil->AddTestCaseL( CBCTestTemplateCase::NewL( view->Container() ),
        _L("Template test case") );
    }

// ----------------------------------------------------------------------------
// CBCTestTemplateAppUi::~CBCTestTemplateAppUi()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestTemplateAppUi::~CBCTestTemplateAppUi()
    { 
	delete iTestUtil;
    }

// ----------------------------------------------------------------------------
// handle menu command events
// ----------------------------------------------------------------------------
//
void CBCTestTemplateAppUi::HandleCommandL( TInt aCommand )
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
