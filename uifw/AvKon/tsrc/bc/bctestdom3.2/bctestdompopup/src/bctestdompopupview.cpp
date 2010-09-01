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
#include <bctestdompopup.rsg>

#include "bctestdompopup.hrh"
#include "bctestdompopupview.h"
#include "bctestdompopupcontainer.h"
#include "bctestutil.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCDomainTestPopupView* CBCDomainTestPopupView::NewL( CBCTestUtil* aUtil )
    {
    CBCDomainTestPopupView* self = new( ELeave ) CBCDomainTestPopupView();
    CleanupStack::PushL( self );
    self->ConstructL( aUtil );
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCDomainTestPopupView::CBCDomainTestPopupView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCDomainTestPopupView::ConstructL( CBCTestUtil* aUtil )
    {
    BaseConstructL( R_BCTESTDOMPOPUP_VIEW );

    iContainer = new( ELeave ) CBCDomainTestPopupContainer();
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
CBCDomainTestPopupView::~CBCDomainTestPopupView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    }

// ---------------------------------------------------------------------------
// CBCDomainTestPopupView::Id
// ---------------------------------------------------------------------------
//
TUid CBCDomainTestPopupView::Id() const
    {
    return KBCDomainTestPopupViewId;
    }

// ---------------------------------------------------------------------------
// CBCDomainTestPopupView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCDomainTestPopupView::DoActivateL( const TVwsViewId&, TUid, 
    const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCDomainTestPopupView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCDomainTestPopupView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCDomainTestPopupView::Container
// ---------------------------------------------------------------------------
//
CBCDomainTestPopupContainer* CBCDomainTestPopupView::Container()
    {
	return iContainer;
    }

// ---------------------------------------------------------------------------
// CBCDomainTestPopupView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCDomainTestPopupView::HandleCommandL( TInt aCommand )
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
