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

#include "testsdkview.h"
#include "testsdkcontainer.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CTestSDKView* CTestSDKView::NewL()
    {
    CTestSDKView* self = new( ELeave ) CTestSDKView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CTestSDKView::CTestSDKView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CTestSDKView::ConstructL()
    {
    iContainer = new( ELeave ) CTestSDKContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CTestSDKView::~CTestSDKView()
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
TUid CTestSDKView::Id() const
    {
    return KBCTestGridsViewId;
    }

// ---------------------------------------------------------------------------
// CTestSDKCPView::DoActivateL
// ---------------------------------------------------------------------------
//
void CTestSDKView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CTestSDKCPView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CTestSDKView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CTestSDKCPView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CTestSDKView::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        default:
            break;
        }
    }

