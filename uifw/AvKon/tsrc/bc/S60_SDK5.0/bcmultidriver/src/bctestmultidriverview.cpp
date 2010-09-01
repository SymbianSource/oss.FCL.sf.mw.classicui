/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  view class
*
*/


#include <aknviewappui.h>

#include "BCTestMultiDriver.hrh"
#include <bctestmultidriver.rsg>
#include "BCTestMultiDriverview.h"
#include "BCTestMultiDrivercontainer.h"
#include "bctestutil.h"
#include "BCTestMultiDrivercase.h"

// Constansts
_LIT( KVCardCase, "vCard test case");

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CMultiDriverView* CMultiDriverView::NewL()
    {
    CMultiDriverView* self = new( ELeave ) CMultiDriverView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CMultiDriverView::CMultiDriverView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CMultiDriverView::ConstructL()
    {
    BaseConstructL( R_BCTESTMULTIDRIVER_VIEW );

    iContainer = new( ELeave ) CMultiDriverContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = CBCTestUtil::NewL();

    // Add test case here.
    iTestUtil->AddTestCaseL( CMultiDriverCase::NewL( iContainer ),
         KVCardCase );
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CMultiDriverView::~CMultiDriverView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// CMultiDriverView::Id
// ---------------------------------------------------------------------------
//
TUid CMultiDriverView::Id() const
    {
    return KMultiDriverViewId;
    }

// ---------------------------------------------------------------------------
// CMultiDriverView::DoActivateL
// ---------------------------------------------------------------------------
//
void CMultiDriverView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CMultiDriverView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CMultiDriverView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CMultiDriverView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CMultiDriverView::HandleCommandL( TInt aCommand )
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
