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

#include "BCTestTreeList.hrh"
#include <bctesttreelist.rsg>
#include "BCTestTreeListview.h"
#include "BCTestTreeListcontainer.h"
#include "bctestutil.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestTreeListView* CBCTestTreeListView::NewL(CBCTestUtil* aUtil)
    {
    CBCTestTreeListView* self = new( ELeave ) CBCTestTreeListView();
    CleanupStack::PushL( self );
    self->ConstructL(aUtil);
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestTreeListView::CBCTestTreeListView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestTreeListView::ConstructL(CBCTestUtil* aUtil)
    {
    BaseConstructL( R_BCTESTTREELIST_VIEW );

    iContainer = new( ELeave ) CBCTestTreeListContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = aUtil;
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestTreeListView::~CBCTestTreeListView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    }

// ---------------------------------------------------------------------------
// CBCTestTreeListView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestTreeListView::Id() const
    {
    return KBCTestTreeListViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestTreeListView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestTreeListView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestTreeListView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestTreeListView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestTreeListView::Container
// ---------------------------------------------------------------------------
//
CBCTestTreeListContainer* CBCTestTreeListView::Container()
    {
	return iContainer;
    }

// ---------------------------------------------------------------------------
// CBCTestTreeListView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestTreeListView::HandleCommandL( TInt aCommand )
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
