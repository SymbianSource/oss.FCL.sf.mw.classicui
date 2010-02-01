/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  View class of bctestsingleclick.
*
*/

#include <aknViewAppUi.h>
#include <bctestsingleclick.rsg>

#include "bctestsingleclick.hrh"
#include "bctestsingleclickview.h"
#include "bctestsingleclickcontainer.h"
#include "bctestutil.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTESTSingleClickView* CBCTESTSingleClickView::NewL( CBCTestUtil* aUtil )
    {
    CBCTESTSingleClickView* self = new( ELeave ) CBCTESTSingleClickView();
    CleanupStack::PushL( self );
    self->ConstructL( aUtil );
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTESTSingleClickView::CBCTESTSingleClickView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTESTSingleClickView::ConstructL( CBCTestUtil* aUtil )
    {
    BaseConstructL( R_BCTESTSINGLECLICK_VIEW );

    iContainer = new( ELeave ) CBCTESTSingleClickContainer();
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
CBCTESTSingleClickView::~CBCTESTSingleClickView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    }

// ---------------------------------------------------------------------------
// CBCTESTSingleClickView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTESTSingleClickView::Id() const
    {
    return KCBCTESTSingleClickViewId;
    }

// ---------------------------------------------------------------------------
// CBCTESTSingleClickView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTESTSingleClickView::DoActivateL( const TVwsViewId&, TUid, 
    const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTESTSingleClickView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTESTSingleClickView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTESTSingleClickView::Container
// ---------------------------------------------------------------------------
//
CBCTESTSingleClickContainer* CBCTESTSingleClickView::Container()
    {
    return iContainer;
    }

// ---------------------------------------------------------------------------
// CBCTESTSingleClickView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTESTSingleClickView::HandleCommandL( TInt aCommand )
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
