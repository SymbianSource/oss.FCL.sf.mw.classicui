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

#include "bctestdocandinit.hrh"
#include <bctestdocandinit.rsg>
#include "bctestdocandinitview.h"
#include "bctestdocandinitcontainer.h"
#include "bctestutil.h"
#include "bctestdocandinitcase.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestDocAndInitView* CBCTestDocAndInitView::NewL()
    {
    CBCTestDocAndInitView* self = new( ELeave ) CBCTestDocAndInitView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestDocAndInitView::CBCTestDocAndInitView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDocAndInitView::ConstructL()
    {
    BaseConstructL( R_BCTESTDOCANDINIT_VIEW );

    iContainer = new( ELeave ) CBCTestDocAndInitContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = CBCTestUtil::NewL();

    // Add test case here.
    iTestUtil->AddTestCaseL( CBCTestDocAndInitCase::NewL( iContainer ),
        _L("DocAndInit test case") );
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDocAndInitView::~CBCTestDocAndInitView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// CBCTestDocAndInitView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestDocAndInitView::Id() const
    {
    return KBCTestDocAndInitViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestDocAndInitView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestDocAndInitView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestDocAndInitView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestDocAndInitView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestDocAndInitView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestDocAndInitView::HandleCommandL( TInt aCommand )
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
