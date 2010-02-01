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

#include "bctesttemplate.hrh"
#include <bctesttemplate.rsg>
#include "bctesttemplateview.h"
#include "bctesttemplatecontainer.h"
#include "bctestutil.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestTemplateView* CBCTestTemplateView::NewL(CBCTestUtil* aUtil)
    {
    CBCTestTemplateView* self = new( ELeave ) CBCTestTemplateView();
    CleanupStack::PushL( self );
    self->ConstructL(aUtil);
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestTemplateView::CBCTestTemplateView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestTemplateView::ConstructL(CBCTestUtil* aUtil)
    {
    BaseConstructL( R_BCTESTTEMPLATE_VIEW );

    iContainer = new( ELeave ) CBCTestTemplateContainer();
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
CBCTestTemplateView::~CBCTestTemplateView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    }

// ---------------------------------------------------------------------------
// CBCTestTemplateView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestTemplateView::Id() const
    {
    return KBCTestTemplateViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestTemplateView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestTemplateView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestTemplateView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestTemplateView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestTemplateView::Container
// ---------------------------------------------------------------------------
//
CBCTestTemplateContainer* CBCTestTemplateView::Container()
    {
	return iContainer;
    }

// ---------------------------------------------------------------------------
// CBCTestTemplateView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestTemplateView::HandleCommandL( TInt aCommand )
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
