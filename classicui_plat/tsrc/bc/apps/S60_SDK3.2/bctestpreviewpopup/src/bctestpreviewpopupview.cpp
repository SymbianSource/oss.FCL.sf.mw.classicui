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

#include "bctestpreviewpopup.hrh"
#include <bctestpreviewpopup.rsg>
#include "bctestpreviewpopupview.h"
#include "bctestpreviewpopupcontainer.h"
#include "bctestutil.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestPreviewPopupView* CBCTestPreviewPopupView::NewL(CBCTestUtil* aUtil)
    {
    CBCTestPreviewPopupView* self = new( ELeave ) CBCTestPreviewPopupView();
    CleanupStack::PushL( self );
    self->ConstructL(aUtil);
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestPreviewPopupView::CBCTestPreviewPopupView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestPreviewPopupView::ConstructL(CBCTestUtil* aUtil)
    {
    BaseConstructL( R_BCTESTPREVIEWPOPUP_VIEW );

    iContainer = new( ELeave ) CBCTestPreviewPopupContainer();
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
CBCTestPreviewPopupView::~CBCTestPreviewPopupView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    }

// ---------------------------------------------------------------------------
// CBCTestPreviewPopupView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestPreviewPopupView::Id() const
    {
    return KBCTestPreviewPopupViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestPreviewPopupView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestPreviewPopupView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestPreviewPopupView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestPreviewPopupView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestPreviewPopupView::Container
// ---------------------------------------------------------------------------
//
CBCTestPreviewPopupContainer* CBCTestPreviewPopupView::Container()
    {
	return iContainer;
    }

// ---------------------------------------------------------------------------
// CBCTestPreviewPopupView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestPreviewPopupView::HandleCommandL( TInt aCommand )
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
