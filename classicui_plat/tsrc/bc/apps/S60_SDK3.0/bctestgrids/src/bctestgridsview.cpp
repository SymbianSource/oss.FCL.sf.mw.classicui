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
#include <bctestgrids.rsg>

#include "bctestgrids.hrh"
#include "bctestgridsview.h"
#include "bctestgridscontainer.h"
#include "bctestutil.h"
#include "bctestforcolourandgms.h"
#include "bctestforakngrid.h"
#include "bctestformandview.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestGridsView* CBCTestGridsView::NewL()
    {
    CBCTestGridsView* self = new( ELeave ) CBCTestGridsView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestGridsView::CBCTestGridsView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestGridsView::ConstructL()
    {    BaseConstructL( R_BCTESTGRIDS_VIEW );

    iContainer = new( ELeave ) CBCTestGridsContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = CBCTestUtil::NewL();

    // Add test case here.
    _LIT( KColourAndGms, "ColourAndGms test case" );
    iTestUtil->AddTestCaseL( CBCTestForColourAndGms::NewL( iContainer ),
        KColourAndGms );
    _LIT( KAknGrid,"AknGrid test case" );
    iTestUtil->AddTestCaseL( CBCTestForAknGrid::NewL( iContainer ),
         KAknGrid );
    _LIT( KAknMAndView,"AknMAndView test case" );
    iTestUtil->AddTestCaseL( CBCTestForMAndView::NewL( iContainer ),
         KAknMAndView );
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestGridsView::~CBCTestGridsView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// CBCTestGridsView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestGridsView::Id() const
    {
    return KBCTestGridsViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestGridsView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestGridsView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestGridsView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestGridsView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestGridsView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestGridsView::HandleCommandL( TInt aCommand )
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
