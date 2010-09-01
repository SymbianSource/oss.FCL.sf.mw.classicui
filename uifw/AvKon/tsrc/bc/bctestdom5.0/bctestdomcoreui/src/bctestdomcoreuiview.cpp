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
#include <bctestdomcoreui.rsg>

#include "bctestdomcoreui.hrh"
#include "bctestdomcoreuiview.h"
#include "bctestdomcoreuicontainer.h"
#include "bctestutil.h"
#include "bctestdomcoreuicase.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomCoreUiView* CBCTestDomCoreUiView::NewL()
    {
    CBCTestDomCoreUiView* self = new( ELeave ) CBCTestDomCoreUiView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomCoreUiView::CBCTestDomCoreUiView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomCoreUiView::ConstructL()
    {
    BaseConstructL( R_BCTESTDOMCOREUI_VIEW );

    iContainer = new( ELeave ) CBCTestDomCoreUiContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = CBCTestUtil::NewL();

    // Add test case here.
    _LIT( KADDCASELOG1, "DomCoreUi test case" );
    iTestUtil->AddTestCaseL( CBCTestDomCoreUiCase::NewL( iContainer ), KADDCASELOG1 );
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDomCoreUiView::~CBCTestDomCoreUiView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// CBCTestDomCoreUiView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestDomCoreUiView::Id() const
    {
    return KBCTestDomCoreUiViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestDomCoreUiView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestDomCoreUiView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestDomCoreUiView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestDomCoreUiView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestDomCoreUiView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestDomCoreUiView::HandleCommandL( TInt aCommand )
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


