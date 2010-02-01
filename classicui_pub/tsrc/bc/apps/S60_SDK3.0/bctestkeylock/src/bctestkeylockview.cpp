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

#include "bctestKeyLock.hrh"
#include <bctestKeyLock.rsg>
#include "bctestKeyLockview.h"
#include "bctestKeyLockcontainer.h"
#include "bctestutil.h"
#include "bctestKeyLockcase.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestKeyLockView* CBCTestKeyLockView::NewL()
    {
    CBCTestKeyLockView* self = new( ELeave ) CBCTestKeyLockView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestKeyLockView::CBCTestKeyLockView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestKeyLockView::ConstructL()
    {
    BaseConstructL( R_BCTESTKEYLOCK_VIEW );

    iContainer = new( ELeave ) CBCTestKeyLockContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = CBCTestUtil::NewL();

    // Add test case here.
    iTestUtil->AddTestCaseL( CBCTestKeyLockCase::NewL( iContainer ),
        _L("KeyLock test case") );
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestKeyLockView::~CBCTestKeyLockView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// CBCTestKeyLockView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestKeyLockView::Id() const
    {
    return KBCTestKeyLockViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestKeyLockView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestKeyLockView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestKeyLockView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestKeyLockView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestKeyLockView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestKeyLockView::HandleCommandL( TInt aCommand )
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
