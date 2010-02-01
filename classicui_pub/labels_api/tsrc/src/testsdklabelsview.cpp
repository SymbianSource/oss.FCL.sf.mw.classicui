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
* Description:  Test labels_api
*
*/

/*
 * Include files
 */
#include <aknviewappui.h>

#include "testsdklabelsview.h"
#include "testsdklabelscontainer.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CTestSDKLabelsView* CTestSDKLabelsView::NewL()
    {
    CTestSDKLabelsView* self = new( ELeave ) CTestSDKLabelsView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CTestSDKLabelsView::CTestSDKLabelsView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CTestSDKLabelsView::ConstructL()
    { 

    iContainer = new( ELeave ) CTestSDKLabelsContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CTestSDKLabelsView::~CTestSDKLabelsView()
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
TUid CTestSDKLabelsView::Id() const
    {
    return KBCTestGridsViewId;
    }

// ---------------------------------------------------------------------------
// Ctestsdkgridsview::DoActivateL
// ---------------------------------------------------------------------------
//
void CTestSDKLabelsView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// Ctestsdkgridsview::DoDeactivate
// ---------------------------------------------------------------------------
//
void CTestSDKLabelsView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// Ctestsdkgridsview::HandleCommandL
// ---------------------------------------------------------------------------
//
void CTestSDKLabelsView::HandleCommandL( TInt aCommand )
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
