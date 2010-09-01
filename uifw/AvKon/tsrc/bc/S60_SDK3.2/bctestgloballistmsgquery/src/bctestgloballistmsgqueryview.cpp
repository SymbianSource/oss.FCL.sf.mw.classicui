/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  View class implementation for BCTestGlobalListMsgQuery.
*
*/

#include <aknviewappui.h>

#include "bctestgloballistmsgquery.hrh"
#include "bctestgloballistmsgqueryview.h"
#include "bctestgloballistmsgquerycontainer.h"
#include "bctestutil.h"
#include "bctestgloballistmsgquerycase.h"
#include <bctestgloballistmsgquery.rsg>

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CBCTestGlobalListMsgQueryView::NewL()
// ---------------------------------------------------------------------------
//
CBCTestGlobalListMsgQueryView* CBCTestGlobalListMsgQueryView::NewL()
    {
    CBCTestGlobalListMsgQueryView* self = new( ELeave ) CBCTestGlobalListMsgQueryView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// CBCTestGlobalListMsgQueryView::CBCTestGlobalListMsgQueryView()
// ---------------------------------------------------------------------------
//
CBCTestGlobalListMsgQueryView::CBCTestGlobalListMsgQueryView()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestGlobalListMsgQueryView::ConstructL()
// ---------------------------------------------------------------------------
//
void CBCTestGlobalListMsgQueryView::ConstructL()
    {
    BaseConstructL( R_BCTESTGLOBALLISTMSGQUERY_VIEW );

    iContainer = new( ELeave ) CBCTestGlobalListMsgQueryContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = CBCTestUtil::NewL();

    // Add test case here.
    iTestUtil->AddTestCaseL( CBCTestGlobalListMsgQueryCase::NewL( iContainer ),
        _L("GlobalListMsgQuery test case") );
    }

// ---------------------------------------------------------------------------
// CBCTestGlobalListMsgQueryView::~CBCTestGlobalListMsgQueryView()
// ---------------------------------------------------------------------------
//
CBCTestGlobalListMsgQueryView::~CBCTestGlobalListMsgQueryView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// CBCTestGlobalListMsgQueryView::Id()
// ---------------------------------------------------------------------------
//
TUid CBCTestGlobalListMsgQueryView::Id() const
    {
    return KBCTestGlobalListMsgQueryViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestGlobalListMsgQueryView::DoActivateL()
// ---------------------------------------------------------------------------
//
void CBCTestGlobalListMsgQueryView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestGlobalListMsgQueryView::DoDeactivate()
// ---------------------------------------------------------------------------
//
void CBCTestGlobalListMsgQueryView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestGlobalListMsgQueryView::HandleCommandL()
// ---------------------------------------------------------------------------
//
void CBCTestGlobalListMsgQueryView::HandleCommandL( TInt aCommand )
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

// End of file
