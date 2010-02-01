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

#include "bctestskins.hrh"
#include <bctestskins.rsg>
#include "bctestskinsview.h"
#include "bctestskinscontainer.h"
#include "bctestutil.h"
#include "bctestdrawutilscase.h"
#include "bctestutilscase.h"
#include "bctestbmpanimcase.h"
#include "bctesteffectcmdcase.h"
#include "bctesteffectqueuecase.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestSkinsView* CBCTestSkinsView::NewL()
    {
    CBCTestSkinsView* self = new( ELeave ) CBCTestSkinsView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestSkinsView::CBCTestSkinsView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestSkinsView::ConstructL()
    {
    BaseConstructL( R_BCTESTSKINS_VIEW );

    iContainer = new( ELeave ) CBCTestSkinsContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = CBCTestUtil::NewL();

    // Add test case here.
    iTestUtil->AddTestCaseL( CBCTestDrawUtilsCase::NewL( iContainer ),
        _L("Test CBCTestDrawUtilsCase") );
    iTestUtil->AddTestCaseL( CBCTestEffectQueueCase::NewL( iContainer ),
        _L("Test CBCTestEffectQueueCase") );
    iTestUtil->AddTestCaseL( CBCTestBmpAnimCase::NewL( iContainer ),
        _L("Test CBCTestBmpAnimCase") );
    iTestUtil->AddTestCaseL( CBCTestUtilsCase::NewL( iContainer ),
        _L("Test CBCTestUtilsCase") );
    iTestUtil->AddTestCaseL( CBCTestEffectCmdCase::NewL( iContainer ),
        _L("Test CBCTestEffectCmdCase") );

    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestSkinsView::~CBCTestSkinsView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// CBCTestSkinsView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestSkinsView::Id() const
    {
    return KBCTestSkinsViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestSkinsView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestSkinsView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestSkinsView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestSkinsView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestSkinsView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestSkinsView::HandleCommandL( TInt aCommand )
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
