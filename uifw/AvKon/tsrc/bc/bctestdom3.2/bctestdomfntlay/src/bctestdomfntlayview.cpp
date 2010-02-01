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
#include <bctestdomfntlay.rsg>

#include "bctestdomfntlay.hrh"
#include "bctestdomfntlayview.h"
#include "bctestdomfntlaycontainer.h"
#include "bctestutil.h"
#include "bctestdomfntlaycase.h"
#include "bctestdomskincase.h"
#include "bctestdomlayoutdatacase.h"
#include "bctestdomlayoutsystemcase.h"
#include "bctestdomgraphiccase.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomFntlayView* CBCTestDomFntlayView::NewL()
    {
    CBCTestDomFntlayView* self = new( ELeave ) CBCTestDomFntlayView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomFntlayView::CBCTestDomFntlayView()
    {


    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomFntlayView::ConstructL()
    {
    BaseConstructL( R_BCTESTDOMFNTLAY_VIEW );

    iContainer = new( ELeave ) CBCTestDomFntlayContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = CBCTestUtil::NewL();

    // Add test case here.
    _LIT( KTxtFntlay, "Fntlay test case" );
    iTestUtil->AddTestCaseL( CBCTestDomFntlayCase::NewL( iContainer ),
                             KTxtFntlay );

    _LIT( KTxtSkin, "Skin test case" );
    iTestUtil->AddTestCaseL(CBCTestDomSkinCase::NewL(),
                            KTxtSkin );

    _LIT( KTxtLayoutData, "LayoutData test case" );
    iTestUtil->AddTestCaseL(CBCTestDomLayoutDataCase::NewL(),
                            KTxtLayoutData );

    _LIT( KTxtLayoutSystem, "LayoutSystem test case" );
    iTestUtil->AddTestCaseL(CBCTestDomLayoutSystemCase::NewL(),
                            KTxtLayoutSystem );

    _LIT( KTxtGraphic, "Graphic test case" );
    iTestUtil->AddTestCaseL(CBCTestDomGraphicCase::NewL(),
                            KTxtGraphic );
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDomFntlayView::~CBCTestDomFntlayView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// CBCTestDomFntlayView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestDomFntlayView::Id() const
    {
    return KBCTestDomFntlayViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestDomFntlayView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestDomFntlayView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestDomFntlayView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestDomFntlayView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestDomFntlayView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestDomFntlayView::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EProgCmdAutoTest:
            iTestUtil->RunL();
            break;
        default:
            if ( aCommand > EBCTestDomCmdEmptyOutline &&
                 aCommand < EBCTestDomCmdMaxOutline )
                {
                iTestUtil->RunL( aCommand );
                }
            break;
        }
    }
