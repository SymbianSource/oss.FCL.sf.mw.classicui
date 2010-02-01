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
* Description:  view
*
*/


#include <aknviewappui.h>
#include <bctestdomnotifier.rsg>

#include "bctestdomnotifier.hrh"
#include "bctestdomnotifierview.h"
#include "bctestdomnotifiercontainer.h"
#include "bctestutil.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCDomainTestNotifierView* CBCDomainTestNotifierView::NewL( CBCTestUtil* aUtil )
    {
    CBCDomainTestNotifierView* self = new( ELeave ) CBCDomainTestNotifierView();
    CleanupStack::PushL( self );
    self->ConstructL( aUtil );
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCDomainTestNotifierView::CBCDomainTestNotifierView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCDomainTestNotifierView::ConstructL( CBCTestUtil* aUtil )
    {
    BaseConstructL( R_BCTESTDOMNOTIFIER_VIEW );

    iContainer = new( ELeave ) CBCDomainTestNotifierContainer();
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
CBCDomainTestNotifierView::~CBCDomainTestNotifierView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    }

// ---------------------------------------------------------------------------
// CBCDomainTestNotifierView::Id
// ---------------------------------------------------------------------------
//
TUid CBCDomainTestNotifierView::Id() const
    {
    return KBCDomainTestNotifierViewId;
    }

// ---------------------------------------------------------------------------
// CBCDomainTestNotifierView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCDomainTestNotifierView::DoActivateL( const TVwsViewId&, TUid, 
    const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCDomainTestNotifierView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCDomainTestNotifierView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCDomainTestNotifierView::Container
// ---------------------------------------------------------------------------
//
CBCDomainTestNotifierContainer* CBCDomainTestNotifierView::Container()
    {
	return iContainer;
    }

// ---------------------------------------------------------------------------
// CBCDomainTestNotifierView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCDomainTestNotifierView::HandleCommandL( TInt aCommand )
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
