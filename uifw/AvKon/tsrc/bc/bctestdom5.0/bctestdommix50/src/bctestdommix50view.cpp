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
* Description:  view
*
*/


#include <aknviewappui.h>
#include <bctestdommix50.rsg>

#include "bctestdommix50.hrh"
#include "bctestdommix50view.h"
#include "bctestdommix50container.h"
#include "bctestutil.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CBCTestDomMix50View::NewL()
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomMix50View* CBCTestDomMix50View::NewL( CBCTestUtil* aUtil )
    {
    CBCTestDomMix50View* self = new( ELeave ) CBCTestDomMix50View();
    CleanupStack::PushL( self );
    self->ConstructL( aUtil );
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// CBCTestDomMix50View::CBCTestDomMix50View()
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomMix50View::CBCTestDomMix50View()
    {
    }


// ---------------------------------------------------------------------------
// CBCTestDomMix50View::ConstructL()
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomMix50View::ConstructL( CBCTestUtil* aUtil )
    {
    BaseConstructL( R_BCTESTDOMMIX50_VIEW );

    iContainer = new( ELeave ) CBCTestDomMix50Container();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = aUtil;
    }


// ---------------------------------------------------------------------------
// CBCTestDomMix50View::~CBCTestDomMix50View()
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDomMix50View::~CBCTestDomMix50View()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    }


// ---------------------------------------------------------------------------
// CBCTestDomMix50View::Container
//
// ---------------------------------------------------------------------------
//
CBCTestDomMix50Container* CBCTestDomMix50View::Container()
    {
    return iContainer;
    }


// ---------------------------------------------------------------------------
// CBCTestDomMix50View::Id
//
// ---------------------------------------------------------------------------
//
TUid CBCTestDomMix50View::Id() const
    {
    return KBCTestDomMix50ViewId;
    }


// ---------------------------------------------------------------------------
// CBCTestDomMix50View::DoActivateL
//
// ---------------------------------------------------------------------------
//
void CBCTestDomMix50View::DoActivateL( const TVwsViewId&, TUid,
                                       const TDesC8& )
    {
    }


// ---------------------------------------------------------------------------
// CBCTestDomMix50View::DoDeactivate
//
// ---------------------------------------------------------------------------
//
void CBCTestDomMix50View::DoDeactivate()
    {
    }


// ---------------------------------------------------------------------------
// CBCTestDomMix50View::HandleCommandL
//
// ---------------------------------------------------------------------------
//
void CBCTestDomMix50View::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EProgCmdAutoTest:
            iTestUtil->RunL();
            break;
        case EAknSoftkeyExit:
            AppUi()->HandleCommandL( EEikCmdExit );
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
