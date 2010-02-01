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
#include <bctesttouchpane.rsg>

#include "bctesttouchpane.hrh"
#include "bctesttouchpaneview.h"
#include "bctesttouchpanecontainer.h"
#include "bctestutil.h"
#include "bctesttouchpanecase.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestTouchPaneView* CBCTestTouchPaneView::NewL(CBCTestUtil* aUtil)
    {
    CBCTestTouchPaneView* self = new( ELeave ) CBCTestTouchPaneView();
    CleanupStack::PushL( self );
    self->ConstructL(aUtil);
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestTouchPaneView::CBCTestTouchPaneView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestTouchPaneView::ConstructL(CBCTestUtil* aUtil)
    {
    BaseConstructL( R_BCTESTTOUCHPANE_VIEW );

    iContainer = new( ELeave ) CBCTestTouchPaneContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = aUtil;
    
	_LIT( KTestCase, "TouchPane test case" );
    iTestUtil->AddTestCaseL( CBCTestTouchPaneCase::NewL( iContainer ),
        KTestCase );    
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestTouchPaneView::~CBCTestTouchPaneView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    }

// ---------------------------------------------------------------------------
// CBCTestTouchPaneView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestTouchPaneView::Id() const
    {
    return KBCTestTouchPaneViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestTouchPaneView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestTouchPaneView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestTouchPaneView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestTouchPaneView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestTouchPaneView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestTouchPaneView::HandleCommandL( TInt aCommand )
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
