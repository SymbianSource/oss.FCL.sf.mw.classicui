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

#include "bctesteh.hrh"
#include <bctesteh.rsg>
#include "bctestehview.h"
#include "bctestehcontainer.h"
#include "bctestutil.h"
#include "bctestehcase.h"

// constant
_LIT( KBctestCase, "BCTest Error UI and Hotkeys case" );


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestEHView* CBCTestEHView::NewL()
    {
    CBCTestEHView* self = new( ELeave ) CBCTestEHView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestEHView::CBCTestEHView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestEHView::ConstructL()
    {
    BaseConstructL( R_BCTESTEH_VIEW );

    iContainer = new( ELeave ) CBCTestEHContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = CBCTestUtil::NewL();

    // Add test case here.
    iTestUtil->AddTestCaseL( CBCTestEHCase::NewL( iContainer ),
        KBctestCase );
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestEHView::~CBCTestEHView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// CBCTestEHView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestEHView::Id() const
    {
    return KBCTestEHViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestEHView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestEHView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestEHView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestEHView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestEHView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestEHView::HandleCommandL( TInt aCommand )
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
