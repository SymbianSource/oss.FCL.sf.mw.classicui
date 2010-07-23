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

#include "testsdksfview.h"
#include "testsdksearchfieldcontainer.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CTestSDKSFView* CTestSDKSFView::NewL()
    {
    CTestSDKSFView* self = new( ELeave ) CTestSDKSFView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CTestSDKSFView::CTestSDKSFView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CTestSDKSFView::ConstructL()
    {
    iContainer = new( ELeave ) CTestSDKSearchFieldContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CTestSDKSFView::~CTestSDKSFView()
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
TUid CTestSDKSFView::Id() const
    {
    return KBCTestGridsViewId;
    }

// ---------------------------------------------------------------------------
// CTestSDKCPView::DoActivateL
// ---------------------------------------------------------------------------
//
void CTestSDKSFView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CTestSDKCPView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CTestSDKSFView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CTestSDKCPView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CTestSDKSFView::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        default:
            break;
        }
    }
