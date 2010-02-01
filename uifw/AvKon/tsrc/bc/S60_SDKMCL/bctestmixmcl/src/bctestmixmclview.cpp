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
#include <bctestmixmcl.rsg>

#include "bctestmixmcl.hrh"
#include "bctestmixmclview.h"
#include "bctestmixmclcontainer.h"
#include "bctestutil.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CBCTestMixMCLView::NewL()
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestMixMCLView* CBCTestMixMCLView::NewL( CBCTestUtil* aUtil )
    {
    CBCTestMixMCLView* self = new( ELeave ) CBCTestMixMCLView();
    CleanupStack::PushL( self );
    self->ConstructL( aUtil );
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// CBCTestMixMCLView::CBCTestMixMCLView()
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestMixMCLView::CBCTestMixMCLView()
    {
    }


// ---------------------------------------------------------------------------
// CBCTestMixMCLView::ConstructL()
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestMixMCLView::ConstructL( CBCTestUtil* aUtil )
    {
    BaseConstructL( R_BCTESTMIXMCL_VIEW );

    iContainer = new( ELeave ) CBCTestMixMCLContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = aUtil;
    }


// ---------------------------------------------------------------------------
// CBCTestMixMCLView::~CBCTestMixMCLView()
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestMixMCLView::~CBCTestMixMCLView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    }


// ---------------------------------------------------------------------------
// CBCTestMixMCLView::Container
//
// ---------------------------------------------------------------------------
//
CBCTestMixMCLContainer* CBCTestMixMCLView::Container()
    {
    return iContainer;
    }


// ---------------------------------------------------------------------------
// CBCTestMixMCLView::Id
//
// ---------------------------------------------------------------------------
//
TUid CBCTestMixMCLView::Id() const
    {
    return KBCTestMixMCLViewId;
    }


// ---------------------------------------------------------------------------
// CBCTestMixMCLView::DoActivateL
//
// ---------------------------------------------------------------------------
//
void CBCTestMixMCLView::DoActivateL( const TVwsViewId&, TUid,
                                    const TDesC8& )
    {
    }


// ---------------------------------------------------------------------------
// CBCTestMixMCLView::DoDeactivate
//
// ---------------------------------------------------------------------------
//
void CBCTestMixMCLView::DoDeactivate()
    {
    }


// ---------------------------------------------------------------------------
// CBCTestMixMCLView::HandleCommandL
//
// ---------------------------------------------------------------------------
//
void CBCTestMixMCLView::HandleCommandL( TInt aCommand )
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
