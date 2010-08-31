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

#include "bctestserverapp.hrh"
#include <bctestserverapp.rsg>
#include "bctestserverappview.h"
#include "bctestserverappcontainer.h"
#include "bctestutil.h"
#include "bctestserverappcase.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestServerappView* CBCTestServerappView::NewL()
    {
    CBCTestServerappView* self = new( ELeave ) CBCTestServerappView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestServerappView::CBCTestServerappView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestServerappView::ConstructL()
    {
    BaseConstructL( R_BCTESTSERVERAPP_VIEW );

    iContainer = new( ELeave ) CBCTestServerappContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = CBCTestUtil::NewL();

    _LIT(Ktest, "Template test case");
    
    // Add test case here.
    iTestUtil->AddTestCaseL( CBCTestServerappCase::NewL( iContainer ),
        Ktest );
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestServerappView::~CBCTestServerappView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// CBCTestServerappView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestServerappView::Id() const
    {
    return KBCTestServerappViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestServerappView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestServerappView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestServerappView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestServerappView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestServerappView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestServerappView::HandleCommandL( TInt aCommand )
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
