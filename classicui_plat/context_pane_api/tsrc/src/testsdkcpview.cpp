/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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

#include "testsdkcpview.h"
#include "testsdkcpcontainer.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CTestSDKCPView* CTestSDKCPView::NewL()
    {
    CTestSDKCPView* self = new( ELeave ) CTestSDKCPView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CTestSDKCPView::CTestSDKCPView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CTestSDKCPView::ConstructL()
    {
    iContainer = new( ELeave ) CTestSDKCPContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CTestSDKCPView::~CTestSDKCPView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    }

// ---------------------------------------------------------------------------
// CTestSDKCPView::Id
// ---------------------------------------------------------------------------
//
TUid CTestSDKCPView::Id() const
    {
    return KBCTestGridsViewId;
    }

// ---------------------------------------------------------------------------
// CTestSDKCPView::DoActivateL
// ---------------------------------------------------------------------------
//
void CTestSDKCPView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CTestSDKCPView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CTestSDKCPView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CTestSDKCPView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CTestSDKCPView::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        default:
            break;
        }
    }
