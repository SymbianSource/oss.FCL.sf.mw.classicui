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

#include "bctestpane.hrh"
#include <bctestpane.rsg>
#include "bctestpaneview.h"
#include "bctestpanecontainer.h"
#include "bctestutil.h"
#include "bctestpanecase.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestPaneView* CBCTestPaneView::NewL( CBCTestUtil* aUtil )
    {
    CBCTestPaneView* self = new( ELeave ) CBCTestPaneView( aUtil );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestPaneView::CBCTestPaneView( CBCTestUtil* aUtil ):
    iTestUtil( aUtil )
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestPaneView::ConstructL()
    {
    BaseConstructL( R_BCTESTPANE_VIEW );

    iContainer = new( ELeave ) CBCTestPaneContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    // Add test case here.
    _LIT( KPaneCase, "Pane case" );
    iTestUtil->AddTestCaseL( CBCTestPaneCase::NewL( iContainer ), 
        KPaneCase );        
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestPaneView::~CBCTestPaneView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    }

// ---------------------------------------------------------------------------
// CBCTestPaneView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestPaneView::Id() const
    {
    return KBCTestTemplateViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestPaneView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestPaneView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestPaneView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestPaneView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestPaneView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestPaneView::HandleCommandL( TInt aCommand )
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
