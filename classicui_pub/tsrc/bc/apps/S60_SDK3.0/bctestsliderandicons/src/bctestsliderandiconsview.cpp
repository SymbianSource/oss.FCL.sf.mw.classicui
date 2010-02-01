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

#include "bctestsliderandicons.hrh"
#include <bctestsliderandicons.rsg>
#include "bctestsliderandiconsview.h"
#include "bctestsliderandiconscontainer.h"
#include "bctestutil.h"
#include "bctestforslider.h"
#include "bctestforicons.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestSliderAndIconsView* CBCTestSliderAndIconsView::NewL()
    {
    CBCTestSliderAndIconsView* self = new( ELeave ) CBCTestSliderAndIconsView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestSliderAndIconsView::CBCTestSliderAndIconsView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestSliderAndIconsView::ConstructL()
    {
    BaseConstructL( R_BCTESTSLIDERANDICONS_VIEW );

    iContainer = new( ELeave ) CBCTestSliderAndIconsContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = CBCTestUtil::NewL();

    // Add test case here.
    iTestUtil->AddTestCaseL( CBCTestForSlider::NewL( iContainer ),
        _L("Slider test case") );
    iTestUtil->AddTestCaseL( CBCTestForIcons::NewL( iContainer ),
        _L("Icons test case") );
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestSliderAndIconsView::~CBCTestSliderAndIconsView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// CBCTestSliderAndIconsView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestSliderAndIconsView::Id() const
    {
    return KBCTestSliderAndIconsViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestSliderAndIconsView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestSliderAndIconsView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestSliderAndIconsView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestSliderAndIconsView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestSliderAndIconsView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestSliderAndIconsView::HandleCommandL( TInt aCommand )
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
