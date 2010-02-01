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

#include "bctestlocation.hrh"
#include <bctestlocation.rsg>
#include "bctestlocationview.h"
#include "bctestlocationcontainer.h"
#include "bctestutil.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestLocationView* CBCTestLocationView::NewL(CBCTestUtil* aUtil)
    {
    CBCTestLocationView* self = new( ELeave ) CBCTestLocationView();
    CleanupStack::PushL( self );
    self->ConstructL(aUtil);
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestLocationView::CBCTestLocationView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestLocationView::ConstructL(CBCTestUtil* aUtil)
    {
    BaseConstructL( R_BCTESTLOCATION_VIEW );

    iContainer = new( ELeave ) CBCTestLocationContainer();
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
CBCTestLocationView::~CBCTestLocationView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    }

// ---------------------------------------------------------------------------
// CBCTestLocationView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestLocationView::Id() const
    {
    return KBCTestLocationViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestLocationView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestLocationView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestLocationView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestLocationView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestLocationView::Container
// ---------------------------------------------------------------------------
//
CBCTestLocationContainer* CBCTestLocationView::Container()
    {
	return iContainer;
    }

// ---------------------------------------------------------------------------
// CBCTestLocationView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestLocationView::HandleCommandL( TInt aCommand )
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
