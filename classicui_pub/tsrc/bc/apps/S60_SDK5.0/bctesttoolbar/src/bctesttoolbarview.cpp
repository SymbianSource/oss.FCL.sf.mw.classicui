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

#include "bctesttoolbar.hrh"
#include <bctesttoolbar.rsg>
#include "bctesttoolbarview.h"
#include "bctesttoolbarcontainer.h"
#include "bctestutil.h"
#include "bctesttoolbarcase.h"

// Constansts
_LIT( KBCTestToolBarCase, "AknToolBar test case");

// ======== MEMBER FUNCTIONS ========

// --------------------------------------------------------------------------
// Symbian 2nd static Constructor
// --------------------------------------------------------------------------
//
CBCTestToolBarView* CBCTestToolBarView::NewL()
    {
    CBCTestToolBarView* self = new( ELeave ) CBCTestToolBarView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// --------------------------------------------------------------------------
// C++ default Constructor
// --------------------------------------------------------------------------
//
CBCTestToolBarView::CBCTestToolBarView()
    {
    }

// --------------------------------------------------------------------------
// Symbian 2nd Constructor
// --------------------------------------------------------------------------
//
void CBCTestToolBarView::ConstructL()
    {
    BaseConstructL( R_BCTESTTOOLBAR_VIEW );

    iContainer = new( ELeave ) CBCTestToolBarContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = CBCTestUtil::NewL();

    // Add test case here.
    iTestUtil->AddTestCaseL( CBCTestToolBarCase::NewL( iContainer ),
         KBCTestToolBarCase );
    }

// --------------------------------------------------------------------------
// Destructor
// --------------------------------------------------------------------------
//
CBCTestToolBarView::~CBCTestToolBarView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    delete iTestUtil;
    }

// --------------------------------------------------------------------------
// CBCTestToolBarView::Id
// --------------------------------------------------------------------------
//
TUid CBCTestToolBarView::Id() const
    {
    return KBCTestToolBarViewId;
    }

// --------------------------------------------------------------------------
// CBCTestToolBarView::DoActivateL
// --------------------------------------------------------------------------
//
void CBCTestToolBarView::DoActivateL( 
    const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// --------------------------------------------------------------------------
// CBCTestToolBarView::DoDeactivate
// --------------------------------------------------------------------------
//
void CBCTestToolBarView::DoDeactivate()
    {
    }

// --------------------------------------------------------------------------
// CBCTestToolBarView::HandleCommandL
// --------------------------------------------------------------------------
//
void CBCTestToolBarView::HandleCommandL( TInt aCommand )
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
