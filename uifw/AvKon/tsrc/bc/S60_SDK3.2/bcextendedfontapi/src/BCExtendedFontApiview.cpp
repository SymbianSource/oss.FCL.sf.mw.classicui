/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  view
*
*/


#include <aknviewappui.h>
#include <bcextendedfontapi.rsg>

#include "BCExtendedFontApi.hrh"
#include "BCExtendedFontApiview.h"
#include "BCExtendedFontApicontainer.h"
#include "bctestutil.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCExtendedFontApiView* CBCExtendedFontApiView::NewL( CBCTestUtil* aUtil )
    {
    CBCExtendedFontApiView* self = new( ELeave ) CBCExtendedFontApiView();
    CleanupStack::PushL( self );
    self->ConstructL( aUtil );
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCExtendedFontApiView::CBCExtendedFontApiView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCExtendedFontApiView::ConstructL( CBCTestUtil* aUtil )
    {
    BaseConstructL( R_BCEXTENDEDFONTAPI_VIEW );

    iContainer = new( ELeave ) CBCExtendedFontApiContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = aUtil;
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCExtendedFontApiView::~CBCExtendedFontApiView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    }

// ---------------------------------------------------------------------------
// CBCExtendedFontApiView::Id
// ---------------------------------------------------------------------------
//
TUid CBCExtendedFontApiView::Id() const
    {
    return KBCExtendedFontApiViewId;
    }

// ---------------------------------------------------------------------------
// CBCExtendedFontApiView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCExtendedFontApiView::DoActivateL( const TVwsViewId&, TUid, 
    const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCExtendedFontApiView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCExtendedFontApiView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCExtendedFontApiView::Container
// ---------------------------------------------------------------------------
//
CBCExtendedFontApiContainer* CBCExtendedFontApiView::Container()
    {
	return iContainer;
    }

// ---------------------------------------------------------------------------
// CBCExtendedFontApiView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCExtendedFontApiView::HandleCommandL( TInt aCommand )
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
