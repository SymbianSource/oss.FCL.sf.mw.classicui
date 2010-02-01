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
* Description:         Implements test bc for labelinfoindicators view.
*
*/









#include <aknviewappui.h>
#include <bctestlabelinfoindicators.rsg>

#include "bctestlabelinfoindicators.hrh"
#include "bctestlabelinfoindicatorsview.h"
#include "bctestlabelinfoindicatorscontainer.h"
#include "bctestutil.h"
#include "bctestlabelinfoindicatorscase.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestLabelInfoIndicatorsView* CBCTestLabelInfoIndicatorsView::NewL()
    {
    CBCTestLabelInfoIndicatorsView* self = 
        new ( ELeave ) CBCTestLabelInfoIndicatorsView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestLabelInfoIndicatorsView::CBCTestLabelInfoIndicatorsView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestLabelInfoIndicatorsView::ConstructL()
    {
    BaseConstructL( R_BCTESTLABELINFOINDICATORS_VIEW );

    iContainer = new( ELeave ) CBCTestLabelInfoIndicatorsContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = CBCTestUtil::NewL();

    // Add test case here.
    _LIT( KLabelInfoIndicatorsCaseComment, "LabelInfoIndicators case" );
    iTestUtil->AddTestCaseL( 
        CBCTestLabelInfoIndicatorsCase::NewL( iContainer ),
        KLabelInfoIndicatorsCaseComment );        
                   
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestLabelInfoIndicatorsView::~CBCTestLabelInfoIndicatorsView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// CBCTestLabelInfoIndicatorsView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestLabelInfoIndicatorsView::Id() const
    {
    return KBCTestLabelInfoIndicatorsViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestLabelInfoIndicatorsView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestLabelInfoIndicatorsView::
    DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestLabelInfoIndicatorsView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestLabelInfoIndicatorsView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestLabelInfoIndicatorsView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestLabelInfoIndicatorsView::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EBCTestLabelInfoIndicatorsCmdAutotest:
            iTestUtil->RunL();
            break;
        default:
            if ( aCommand > EBCTestLabelInfoIndicatorsCmdEmptyOutline &&
                 aCommand < EBCTestLabelInfoIndicatorsCmdMaxOutline )
                {
                iTestUtil->RunL( aCommand );
                }
            break;
        }
    }
