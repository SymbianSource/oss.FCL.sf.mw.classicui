/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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


// INCLUDE FILES
#include <aknviewappui.h>
#include <bctestdominputmethods.rsg>

#include "bctestdominputmethods.hrh"
#include "bctestdominputmethodsview.h"
#include "bctestdominputmethodscontainer.h"
#include "bctestutil.h"
#include "bctestdominputmethodscase.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomInputMethodsView* CBCTestDomInputMethodsView::NewL()
    {
    CBCTestDomInputMethodsView* self = new( ELeave ) CBCTestDomInputMethodsView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomInputMethodsView::CBCTestDomInputMethodsView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomInputMethodsView::ConstructL()
    {
    BaseConstructL( R_BCTESTDOMINPUTMETHODS_VIEW );

    iContainer = new( ELeave ) CBCTestDomInputMethodsContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = CBCTestUtil::NewL();

    // Add test case here.
    _LIT( KADDCASELOG1, "DomInputMethods test case" );
    iTestUtil->AddTestCaseL( CBCTestDomInputMethodsCase::NewL( iContainer ),
        KADDCASELOG1 );
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDomInputMethodsView::~CBCTestDomInputMethodsView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// CBCTestDomInputMethodsView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestDomInputMethodsView::Id() const
    {
    return KBCTestDomInputMethodsViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestDomInputMethodsView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestDomInputMethodsView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestDomInputMethodsView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestDomInputMethodsView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestDomInputMethodsView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestDomInputMethodsView::HandleCommandL( TInt aCommand )
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
