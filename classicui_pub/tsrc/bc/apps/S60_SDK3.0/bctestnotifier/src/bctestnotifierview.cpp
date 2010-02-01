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

#include "bctestnotifier.hrh"
#include "bctestnotifierview.h"
#include "bctestnotifiercontainer.h"
#include "bctestutil.h"
#include "bctestnotifiercase.h"
#include <bctestnotifier.rsg>

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestNotifierView* CBCTestNotifierView::NewL()
    {
    CBCTestNotifierView* self = new( ELeave ) CBCTestNotifierView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestNotifierView::CBCTestNotifierView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestNotifierView::ConstructL()
    {
    BaseConstructL( R_BCTESTNOTIFIER_VIEW );

    iContainer = new( ELeave ) CBCTestNotifierContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = CBCTestUtil::NewL();

    // Add test case here.
    iTestUtil->AddTestCaseL( CBCTestNotifierCase::NewL( iContainer ),
        _L("Notifier test case") );
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestNotifierView::~CBCTestNotifierView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// CBCTestSettingPageView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestNotifierView::Id() const
    {
    return KBCTestNotifierViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestSettingPageView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestNotifierView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestSettingPageView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestNotifierView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestNotifierView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestNotifierView::HandleCommandL( TInt aCommand )
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
