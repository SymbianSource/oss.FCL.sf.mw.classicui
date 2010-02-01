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

#include "bctestsearchfield.hrh"
#include <bctestsearchfield.rsg>
#include "bctestsearchfieldview.h"
#include "bctestsearchfieldcontainer.h"
#include "bctestutil.h"
#include "bctestsearchfieldcase.h"

_LIT( KTestCaseComment, "CBCTestSearchField" );
    
// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestSearchFieldView* CBCTestSearchFieldView::NewL(CBCTestUtil* aUtil)
    {
    CBCTestSearchFieldView* self = new( ELeave ) CBCTestSearchFieldView();
    CleanupStack::PushL( self );
    self->ConstructL(aUtil);
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestSearchFieldView::CBCTestSearchFieldView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestSearchFieldView::ConstructL( CBCTestUtil* aUtil )
    {
    BaseConstructL( R_BCTESTSEARCHFIELD_VIEW );

    iContainer = new( ELeave ) CBCTestSearchFieldContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = aUtil;
    iTestUtil->AddTestCaseL( CBCTestSearchFieldCase::NewL( iContainer ),
        KTestCaseComment );
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestSearchFieldView::~CBCTestSearchFieldView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;    
    }

// ---------------------------------------------------------------------------
// CBCTestSearchFieldView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestSearchFieldView::Id() const
    {
    return KBCTestSearchFieldViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestSearchFieldView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestSearchFieldView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestSearchFieldView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestSearchFieldView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestSearchFieldView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestSearchFieldView::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EBCTestCmdAutoTest:
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
