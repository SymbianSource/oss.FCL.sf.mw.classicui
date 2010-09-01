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

#include "bctestbutton.hrh"
#include <bctestbutton.rsg>
#include "bctestbuttonview.h"
#include "bctestbuttoncontainer.h"
#include "bctestutil.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestButtonView* CBCTestButtonView::NewL(CBCTestUtil* aUtil)
    {
    CBCTestButtonView* self = new( ELeave ) CBCTestButtonView();
    CleanupStack::PushL( self );
    self->ConstructL(aUtil);
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestButtonView::CBCTestButtonView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestButtonView::ConstructL(CBCTestUtil* aUtil)
    {
    BaseConstructL( R_BCTESTBUTTON_VIEW );

    iContainer = new( ELeave ) CBCTestButtonContainer();
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
CBCTestButtonView::~CBCTestButtonView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    }

// ---------------------------------------------------------------------------
// CBCTestButtonView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestButtonView::Id() const
    {
    return KBCTestButtonViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestButtonView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestButtonView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestButtonView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestButtonView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestButtonView::Container
// ---------------------------------------------------------------------------
//
CBCTestButtonContainer* CBCTestButtonView::Container()
    {
	return iContainer;
    }

// ---------------------------------------------------------------------------
// CBCTestButtonView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestButtonView::HandleCommandL( TInt aCommand )
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
