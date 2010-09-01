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
* Description:  view class
*
*/


#include <aknviewappui.h>
#include <bctestdomcdl.rsg>

#include "bctestdomcdl.hrh"
#include "bctestdomcdlview.h"
#include "bctestdomcdlcontainer.h"
#include "bctestutil.h"
#include "bctestdomcdlcase.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomCdlView* CBCTestDomCdlView::NewL()
    {
    CBCTestDomCdlView* self = new( ELeave ) CBCTestDomCdlView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomCdlView::CBCTestDomCdlView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomCdlView::ConstructL()
    {
    BaseConstructL( R_BCTESTCDL_VIEW );

    iContainer = new( ELeave ) CBCTestDomCdlContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = CBCTestUtil::NewL();

    // Add test case here.
    _LIT( KADDCASELOG1, "Cdl api test case" );
    iTestUtil->AddTestCaseL( CBCTestDomCdlCase::NewL( iContainer ),KADDCASELOG1 );
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDomCdlView::~CBCTestDomCdlView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// CBCTestDomCdlView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestDomCdlView::Id() const
    {
    return KBCTestCdlViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestDomCdlView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestDomCdlView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestDomCdlView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestDomCdlView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestDomCdlView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestDomCdlView::HandleCommandL( TInt aCommand )
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

