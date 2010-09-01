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

#include "bctestsettingpage.hrh"
#include "bctestsettingpageview.h"
#include "bctestsettingpagecontainer.h"
#include "bctestutil.h"
#include "bctestsettingpagecase.h"
#include <bctestsettingpage.rsg>

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestSettingPageView* CBCTestSettingPageView::NewL()
    {
    CBCTestSettingPageView* self = new( ELeave ) CBCTestSettingPageView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestSettingPageView::CBCTestSettingPageView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestSettingPageView::ConstructL()
    {
    BaseConstructL( R_BCTESTSETTINGPAGE_VIEW );

    iContainer = new( ELeave ) CBCTestSettingPageContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = CBCTestUtil::NewL();

    // Add test case here.
	_LIT( KADDCASELOG1, "SettingPage test case" );
    iTestUtil->AddTestCaseL( CBCTestSettingPageCase::NewL( iContainer ),
        KADDCASELOG1 );
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestSettingPageView::~CBCTestSettingPageView()
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
TUid CBCTestSettingPageView::Id() const
    {
    return KBCTestSettingPageViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestSettingPageView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestSettingPageView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestSettingPageView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestSettingPageView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestSettingPageView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestSettingPageView::HandleCommandL( TInt aCommand )
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
