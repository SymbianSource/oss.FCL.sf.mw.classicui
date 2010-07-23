/*
* Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         view
*
*/









#include <aknviewappui.h>
#include <bctestmix50.rsg>

#include "bctestmix50.hrh"
#include "bctestmix50view.h"
#include "bctestmix50container.h"
#include "bctestutil.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CBCTestMix50View::NewL()
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestMix50View* CBCTestMix50View::NewL( CBCTestUtil* aUtil )
    {
    CBCTestMix50View* self = new( ELeave ) CBCTestMix50View();
    CleanupStack::PushL( self );
    self->ConstructL( aUtil );
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// CBCTestMix50View::CBCTestMix50View()
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestMix50View::CBCTestMix50View()
    {
    }


// ---------------------------------------------------------------------------
// CBCTestMix50View::ConstructL()
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestMix50View::ConstructL( CBCTestUtil* aUtil )
    {
    BaseConstructL( R_BCTESTMIX50_VIEW );

    iContainer = new( ELeave ) CBCTestMix50Container();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = aUtil;
    }


// ---------------------------------------------------------------------------
// CBCTestMix50View::~CBCTestMix50View()
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestMix50View::~CBCTestMix50View()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    }


// ---------------------------------------------------------------------------
// CBCTestMix50View::Container
//
// ---------------------------------------------------------------------------
//
CBCTestMix50Container* CBCTestMix50View::Container()
    {
    return iContainer;
    }


// ---------------------------------------------------------------------------
// CBCTestMix50View::Id
//
// ---------------------------------------------------------------------------
//
TUid CBCTestMix50View::Id() const
    {
    return KBCTestMix50ViewId;
    }


// ---------------------------------------------------------------------------
// CBCTestMix50View::DoActivateL
//
// ---------------------------------------------------------------------------
//
void CBCTestMix50View::DoActivateL( const TVwsViewId&, TUid,
                                    const TDesC8& )
    {
    }


// ---------------------------------------------------------------------------
// CBCTestMix50View::DoDeactivate
//
// ---------------------------------------------------------------------------
//
void CBCTestMix50View::DoDeactivate()
    {
    }


// ---------------------------------------------------------------------------
// CBCTestMix50View::HandleCommandL
//
// ---------------------------------------------------------------------------
//
void CBCTestMix50View::HandleCommandL( TInt aCommand )
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
