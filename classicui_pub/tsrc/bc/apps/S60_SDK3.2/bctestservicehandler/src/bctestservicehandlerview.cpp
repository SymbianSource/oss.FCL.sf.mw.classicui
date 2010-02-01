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

#include "bctestservicehandler.hrh"
#include <bctestservicehandler.rsg>
#include "bctestservicehandlerview.h"
#include "bctestservicehandlercontainer.h"
#include "bctestutil.h"
#include "bctestservicehandlercase.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestServiceHandlerView* CBCTestServiceHandlerView::NewL()
    {
    CBCTestServiceHandlerView* self = new( ELeave ) CBCTestServiceHandlerView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestServiceHandlerView::CBCTestServiceHandlerView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestServiceHandlerView::ConstructL()
    {
    BaseConstructL( R_BCTESTSERVICEHANDLER_VIEW );

    iContainer = new( ELeave ) CBCTestServiceHandlerContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    // init test util
	iTestUtil = CBCTestUtil::NewL();
    
    // Add test case here.
    iTestUtil->AddTestCaseL( CBCTestServiceHandlerCase::NewL( iContainer ),
        _L("ServiceHandler test case") );
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestServiceHandlerView::~CBCTestServiceHandlerView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// CBCTestServiceHandlerView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestServiceHandlerView::Id() const
    {
    return KBCTestServiceHandlerViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestServiceHandlerView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestServiceHandlerView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestServiceHandlerView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestServiceHandlerView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestServiceHandlerView::Container
// ---------------------------------------------------------------------------
//
CBCTestServiceHandlerContainer* CBCTestServiceHandlerView::Container()
    {
	return iContainer;
    }

// ---------------------------------------------------------------------------
// CBCTestServiceHandlerView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestServiceHandlerView::HandleCommandL( TInt aCommand )
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
