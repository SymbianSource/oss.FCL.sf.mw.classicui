/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Test queries_api
*
*/

//INCLUDE
#include "testsdkqueriescontainer.h"
#include "testsdkqueries.hrh"
#include "testsdkqueriesview.h"

// -----------------------------------------------------------------------------
// CTestSDKQueriesView::CTestSDKQueriesView
// -----------------------------------------------------------------------------
//
CTestSDKQueriesView::CTestSDKQueriesView( )
    {
    // No implementation required
    }

// -----------------------------------------------------------------------------
// CTestSDKQueriesView::~CTestSDKQueriesView
// -----------------------------------------------------------------------------
//
CTestSDKQueriesView::~CTestSDKQueriesView( )
    {
    }

// -----------------------------------------------------------------------------
// CTestSDKQueriesView::NewLC
// -----------------------------------------------------------------------------
//
CTestSDKQueriesView* CTestSDKQueriesView::NewLC( )
    {
    CTestSDKQueriesView* self = new (ELeave)CTestSDKQueriesView();
    CleanupStack::PushL( self );
    self->ConstructL( );
    return self;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueriesView::NewL
// -----------------------------------------------------------------------------
//
CTestSDKQueriesView* CTestSDKQueriesView::NewL( )
    {
    CTestSDKQueriesView* self=CTestSDKQueriesView::NewLC( );
    CleanupStack::Pop( ); // self;
    return self;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueriesView::ConstructL
// -----------------------------------------------------------------------------
//
void CTestSDKQueriesView::ConstructL( )
    {
    BaseConstructL();
    }

// -----------------------------------------------------------------------------
// CTestSDKQueriesView::Container
// -----------------------------------------------------------------------------
//
CTestSDKQueriesContainer* CTestSDKQueriesView::Container()
    {
    return iContainer;
    }

// -----------------------------------------------------------------------------
// CTestSDKQueriesView::Id
// -----------------------------------------------------------------------------
//
TUid CTestSDKQueriesView::Id() const
    {
    return TUid::Uid(ETestSDKQueryViewId);
    }

// -----------------------------------------------------------------------------
// CTestSDKQueriesView::HandldCommandL
// -----------------------------------------------------------------------------
//
void CTestSDKQueriesView::HandldCommandL(TInt /*aCommand*/)
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKQueriesView::DoActivateL
// -----------------------------------------------------------------------------
//
void CTestSDKQueriesView::DoActivateL(
    const TVwsViewId& /*aPrevViewId*/,
    TUid /*aCustomMessageId*/,
    const TDesC8& /*aCustomMessage*/ )
    {
    iContainer = CTestSDKQueriesContainer::NewL(ClientRect(), NULL);
    iContainer->SetMopParent( this );
    }

// -----------------------------------------------------------------------------
// CTestSDKQueriesView::DoDeactivate
// -----------------------------------------------------------------------------
//
void CTestSDKQueriesView::DoDeactivate()
    {
    if(iContainer)
        {
        delete iContainer;
        iContainer = NULL;
        }
    }

//End file


