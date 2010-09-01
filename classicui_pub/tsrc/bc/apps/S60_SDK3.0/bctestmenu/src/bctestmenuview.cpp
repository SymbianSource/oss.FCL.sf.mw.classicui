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

#include "bctestmenu.hrh"
#include <bctestmenu.rsg>
#include "bctestmenuview.h"
#include "bctestmenucontainer.h"
#include "bctestutil.h"
#include "bctestmenucase.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestMenuView* CBCTestMenuView::NewL()
    {
    CBCTestMenuView* self = new( ELeave ) CBCTestMenuView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestMenuView::CBCTestMenuView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestMenuView::ConstructL()
    {
    BaseConstructL( R_BCTESTMENU_VIEW );

    iContainer = new( ELeave ) CBCTestMenuContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = CBCTestUtil::NewL();
    _LIT( KMenuTestCase, "Menu test case");
    // Add test case here.
    iTestUtil->AddTestCaseL( CBCTestMenuCase::NewL( iContainer ),
        KMenuTestCase );
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestMenuView::~CBCTestMenuView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// CBCTestMenuView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestMenuView::Id() const
    {
    return KBCTestMenuViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestMenuView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestMenuView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestMenuView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestMenuView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestMenuView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestMenuView::HandleCommandL( TInt aCommand )
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
