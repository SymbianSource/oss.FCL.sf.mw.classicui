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

#include "bctestlocalizer.hrh"
#include <bctestlocalizer.rsg>
#include "bctestlocalizerview.h"
#include "bctestlocalizercontainer.h"
#include "bctestutil.h"
#include "bctestlocalizercase.h"

// Constansts
_LIT( KVCardCase, "vCard test case");

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestLocalizerView* CBCTestLocalizerView::NewL()
    {
    CBCTestLocalizerView* self = new( ELeave ) CBCTestLocalizerView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestLocalizerView::CBCTestLocalizerView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestLocalizerView::ConstructL()
    {
    BaseConstructL( R_BCTESTLOCALIZER_VIEW );

    iContainer = new( ELeave ) CBCTestLocalizerContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = CBCTestUtil::NewL();

    // Add test case here.
    iTestUtil->AddTestCaseL( CBCTestLocalizerCase::NewL( iContainer ),
         KVCardCase );
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestLocalizerView::~CBCTestLocalizerView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// CBCTestLocalizerView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestLocalizerView::Id() const
    {
    return KBCTestLocalizerViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestLocalizerView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestLocalizerView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestLocalizerView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestLocalizerView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestLocalizerView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestLocalizerView::HandleCommandL( TInt aCommand )
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
