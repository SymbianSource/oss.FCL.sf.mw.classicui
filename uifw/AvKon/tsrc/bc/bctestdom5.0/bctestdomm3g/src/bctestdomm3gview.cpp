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
* Description:  Implement view class
*
*/


#include <aknviewappui.h>

#include "bctestdomm3g.hrh"
#include <bctestdomm3g.rsg>
#include "bctestdomm3gview.h"
#include "bctestdomm3gcontainer.h"
#include "bctestutil.h"
#include "bctestdomm3gcase.h"
#include "bctestdomm3gnodecase.h"

_LIT( KObjectTestCaseComment, "CBCTestDomM3gObjectTestCase" );
_LIT( KNodeTestCaseComment, "CBCTestDomM3gNodeTestCase" );
    
// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomM3gView* CBCTestDomM3gView::NewL(CBCTestUtil* aUtil)
    {
    CBCTestDomM3gView* self = new( ELeave ) CBCTestDomM3gView();
    CleanupStack::PushL( self );
    self->ConstructL(aUtil);
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomM3gView::CBCTestDomM3gView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gView::ConstructL( CBCTestUtil* aUtil )
    {
    BaseConstructL( R_BCTESTDOMM3G_VIEW );

    iContainer = new( ELeave ) CBCTestDomM3gContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = aUtil;
    iTestUtil->AddTestCaseL( CBCTestDomM3gCase::NewL( iContainer ),
        KObjectTestCaseComment );
        
    iTestUtil->AddTestCaseL( CBCTestDomM3gNodeCase::NewL( iContainer ),
        KNodeTestCaseComment );        
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDomM3gView::~CBCTestDomM3gView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;    
    }

// ---------------------------------------------------------------------------
// CBCTestDomM3gView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestDomM3gView::Id() const
    {
    return KBCTestM3gViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestDomM3gView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestDomM3gView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestDomM3gView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestDomM3gView::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EBCTestCmdAutoTest:
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
