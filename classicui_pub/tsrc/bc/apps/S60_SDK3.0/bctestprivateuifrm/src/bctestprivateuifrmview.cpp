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

#include "bctestprivateuifrm.hrh"
#include <bctestprivateuifrm.rsg>
#include "bctestPrivateUIFrmview.h"
#include "bctestPrivateUIFrmcontainer.h"
#include "bctestutil.h"
#include "bctestPrivateUIFrmcase.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestPrivateUIFrmView* CBCTestPrivateUIFrmView::NewL()
    {
    CBCTestPrivateUIFrmView* self = new( ELeave ) CBCTestPrivateUIFrmView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestPrivateUIFrmView::CBCTestPrivateUIFrmView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestPrivateUIFrmView::ConstructL()
    {
    BaseConstructL( R_BCTESTPRIVATEUIFRM_VIEW );

    iContainer = new( ELeave ) CBCTestPrivateUIFrmContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = CBCTestUtil::NewL();

    // Add test case here.
    iTestUtil->AddTestCaseL( CBCTestPrivateUIFrmCase::NewL( iContainer ),
        _L("PrivateUIFrm test case") );
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestPrivateUIFrmView::~CBCTestPrivateUIFrmView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// CBCTestPrivateUIFrmView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestPrivateUIFrmView::Id() const
    {
    return KBCTestPrivateUIFrmViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestPrivateUIFrmView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestPrivateUIFrmView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestPrivateUIFrmView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestPrivateUIFrmView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestPrivateUIFrmView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestPrivateUIFrmView::HandleCommandL( TInt aCommand )
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
