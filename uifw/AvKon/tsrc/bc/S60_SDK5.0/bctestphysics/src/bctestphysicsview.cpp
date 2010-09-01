/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  container
*
*/

#include <aknviewappui.h>
#include <bctestphysics.rsg>

#include "bctestphysics.hrh"
#include "bctestphysicsview.h"
#include "bctestphysicscontainer.h"
#include "bctestutil.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestPhysicsView* CBCTestPhysicsView::NewL( CBCTestUtil* aUtil )
    {
    CBCTestPhysicsView* self = new( ELeave ) CBCTestPhysicsView();
    CleanupStack::PushL( self );
    self->ConstructL( aUtil );
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestPhysicsView::CBCTestPhysicsView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestPhysicsView::ConstructL( CBCTestUtil* aUtil )
    {
    BaseConstructL( R_BCTESTPHYSICS_VIEW );

    iContainer = new( ELeave ) CBCTestPhysicsContainer();
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
CBCTestPhysicsView::~CBCTestPhysicsView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    }

// ---------------------------------------------------------------------------
// CBCTestPhysicsView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestPhysicsView::Id() const
    {
    return KBCTestPhysicsViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestPhysicsView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestPhysicsView::DoActivateL( const TVwsViewId&, TUid, 
    const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestPhysicsView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestPhysicsView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestPhysicsView::Container
// ---------------------------------------------------------------------------
//
CBCTestPhysicsContainer* CBCTestPhysicsView::Container()
    {
	return iContainer;
    }

// ---------------------------------------------------------------------------
// CBCTestPhysicsView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestPhysicsView::HandleCommandL( TInt aCommand )
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
