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
* Description:         view class
*
*/









#include <aknviewappui.h>

#include "bctesteikfrm.hrh"
#include <bctesteikfrm.rsg>
#include "bctesteikfrmview.h"
#include "bctesteikfrmcontainer.h"
#include "bctestutil.h"
#include "bctesteikfrmcase.h"
#include "bctesteikdoc.h"
#include "bctesteikproc.h"
#include "bctestapplist.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestEikFrmView* CBCTestEikFrmView::NewL()
    {
    CBCTestEikFrmView* self = new( ELeave ) CBCTestEikFrmView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestEikFrmView::CBCTestEikFrmView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestEikFrmView::ConstructL()
    {
    BaseConstructL( R_BCTESTEIKFRM_VIEW );

    iContainer = new( ELeave ) CBCTestEikFrmContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = CBCTestUtil::NewL();

    // Add test case here.
    iTestUtil->AddTestCaseL( CBCTestEikFrmCase::NewL( iContainer ),
        _L("EikFrm test case") );

	iTestUtil->AddTestCaseL( CBCTestEikDoc::NewL(), _L("EikDoc test case") );
	iTestUtil->AddTestCaseL( CBCTestEikProc::NewL(), _L("EikProcess test case") );
	iTestUtil->AddTestCaseL( CBCTestAppList::NewL(), _L("AppList test case") );
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestEikFrmView::~CBCTestEikFrmView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// CBCTestEikFrmView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestEikFrmView::Id() const
    {
    return KBCTestEikFrmViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestEikFrmView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestEikFrmView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestEikFrmView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestEikFrmView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestEikFrmView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestEikFrmView::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EProgCmdAutoTest:
            iTestUtil->RunL();
            break;
        default:
            if ( aCommand > EBCTestCmdEmptyOutline &&
                 aCommand < EBCTestCmdMaxOutline )
                {
                iTestUtil->RunL( aCommand );
                }
            break;
        }
    }
