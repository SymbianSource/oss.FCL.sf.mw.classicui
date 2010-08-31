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
* Description:  Test grids_api
*
*/

/*
 * Include files
 */
#include <aknviewappui.h>

#include "testsdkgridsview.h"
#include "testsdkgridscontainer.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CTestSDKGridsView* CTestSDKGridsView::NewL()
    {
    CTestSDKGridsView* self = new( ELeave ) CTestSDKGridsView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CTestSDKGridsView::CTestSDKGridsView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CTestSDKGridsView::ConstructL()
    { 

    iContainer = new( ELeave ) CTestSDKGridsContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CTestSDKGridsView::~CTestSDKGridsView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    }

// ---------------------------------------------------------------------------
// Ctestsdkgridsview::Id
// ---------------------------------------------------------------------------
//
TUid CTestSDKGridsView::Id() const
    {
    return KBCTestGridsViewId;
    }

// ---------------------------------------------------------------------------
// Ctestsdkgridsview::DoActivateL
// ---------------------------------------------------------------------------
//
void CTestSDKGridsView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// Ctestsdkgridsview::DoDeactivate
// ---------------------------------------------------------------------------
//
void CTestSDKGridsView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// Ctestsdkgridsview::HandleCommandL
// ---------------------------------------------------------------------------
//
void CTestSDKGridsView::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        default:
            break;
        }
    }

/*
 * End file
 */
