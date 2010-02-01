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

#include "bctestimage.hrh"
#include <bctestimage.rsg>
#include "bctestimageview.h"
#include "bctestimagecontainer.h"
#include "bctestutil.h"
#include "bctestimagecase.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestImageView* CBCTestImageView::NewL()
    {
    CBCTestImageView* self = new( ELeave ) CBCTestImageView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestImageView::CBCTestImageView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestImageView::ConstructL()
    {
    BaseConstructL( R_BCTESTIMAGE_VIEW );

    iContainer = new( ELeave ) CBCTestImageContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = CBCTestUtil::NewL();

    _LIT(Ktest, "Template test case");
    
    // Add test case here.
    iTestUtil->AddTestCaseL( CBCTestImageCase::NewL( iContainer ),
        Ktest );
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestImageView::~CBCTestImageView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// CBCTestImageView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestImageView::Id() const
    {
    return KBCTestImageViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestImageView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestImageView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestImageView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestImageView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestImageView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestImageView::HandleCommandL( TInt aCommand )
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
