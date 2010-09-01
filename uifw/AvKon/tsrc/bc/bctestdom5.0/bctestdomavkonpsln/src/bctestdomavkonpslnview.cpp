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
* Description:  ?Description
*
*/


#include <aknviewappui.h>
#include <bctestdomavkonpsln.rsg>

#include "bctestdomavkonpsln.hrh"
#include "bctestdomavkonpslnview.h"
#include "bctestdomavkonpslncontainer.h"
#include "bctestutil.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomAvkonPslnView* CBCTestDomAvkonPslnView::NewL( CBCTestUtil* aUtil )
    {
    CBCTestDomAvkonPslnView* self = new( ELeave ) CBCTestDomAvkonPslnView();
    CleanupStack::PushL( self );
    self->ConstructL( aUtil );
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomAvkonPslnView::CBCTestDomAvkonPslnView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomAvkonPslnView::ConstructL( CBCTestUtil* aUtil )
    {
    BaseConstructL( R_BCTESTDOMAVKONPSLN_VIEW );

    iContainer = new( ELeave ) CBCTestDomAvkonPslnContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = aUtil;
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDomAvkonPslnView::~CBCTestDomAvkonPslnView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    }

// ---------------------------------------------------------------------------
// CBCTestDomAvkonPslnView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestDomAvkonPslnView::Id() const
    {
    return KBCTestDomainViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestDomAvkonPslnView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestDomAvkonPslnView::DoActivateL( const TVwsViewId&, TUid, 
    const TDesC8& )
    {
    
    }

// ---------------------------------------------------------------------------
// CBCTestDomAvkonPslnView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestDomAvkonPslnView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestDomAvkonPslnView::Container
// ---------------------------------------------------------------------------
//
CBCTestDomAvkonPslnContainer* CBCTestDomAvkonPslnView::Container()
    {
    return iContainer;
    }

// ---------------------------------------------------------------------------
// CBCTestDomAvkonPslnView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestDomAvkonPslnView::HandleCommandL( TInt aCommand )
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
//end of file
