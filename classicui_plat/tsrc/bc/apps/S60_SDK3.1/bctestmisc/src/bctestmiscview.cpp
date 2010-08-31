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
#include <bctestmisc.rsg>

#include "bctestmisc.hrh"
#include "bctestmiscview.h"
#include "bctestmisccontainer.h"
#include "bctestutil.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestMiscView* CBCTestMiscView::NewL(CBCTestUtil* aUtil)
    {
    CBCTestMiscView* self = new( ELeave ) CBCTestMiscView();
    CleanupStack::PushL( self );
    self->ConstructL(aUtil);
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestMiscView::CBCTestMiscView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestMiscView::ConstructL(CBCTestUtil* aUtil)
    {
    BaseConstructL( R_BCTESTMISC_VIEW );

    iContainer = new( ELeave ) CBCTestMiscContainer();
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
CBCTestMiscView::~CBCTestMiscView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    }

// ---------------------------------------------------------------------------
// CBCTestMiscView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestMiscView::Id() const
    {
    return KBCTestMiscViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestMiscView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestMiscView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestMiscView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestMiscView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestMiscView::Container
// ---------------------------------------------------------------------------
//
CBCTestMiscContainer* CBCTestMiscView::Container()
    {
	return iContainer;
    }

// ---------------------------------------------------------------------------
// CBCTestMiscView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestMiscView::HandleCommandL( TInt aCommand )
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
