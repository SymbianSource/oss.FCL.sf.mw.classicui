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

#include "BCTestChoicelist.hrh"
#include <bctestchoicelist.rsg>
#include "BCTestChoicelistview.h"
#include "BCTestChoicelistcontainer.h"
#include "bctestutil.h"
#include "BCTestChoicelistcase.h"

// Constansts
_LIT( KPopupChoicelistCase, "PopupChoicelist test case");

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCPopupChoicelistView* CBCPopupChoicelistView::NewL()
    {
    CBCPopupChoicelistView* self = new( ELeave ) CBCPopupChoicelistView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCPopupChoicelistView::CBCPopupChoicelistView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCPopupChoicelistView::ConstructL()
    {
    BaseConstructL( R_BCPOPUPCHOICELIST_VIEW );

    iContainer = new( ELeave ) CBCPopupChoicelistContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = CBCTestUtil::NewL();

    // Add test case here.
    iTestUtil->AddTestCaseL( CBCPopupChoicelistCase::NewL( iContainer ),
         KPopupChoicelistCase );
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCPopupChoicelistView::~CBCPopupChoicelistView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// CBCPopupChoicelistView::Id
// ---------------------------------------------------------------------------

TUid CBCPopupChoicelistView::Id() const
    {
    return KBCPopupChoicelistViewId;
    }

// ---------------------------------------------------------------------------
// CBCPopupChoicelistView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCPopupChoicelistView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCPopupChoicelistView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCPopupChoicelistView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCPopupChoicelistView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCPopupChoicelistView::HandleCommandL( TInt aCommand )
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
