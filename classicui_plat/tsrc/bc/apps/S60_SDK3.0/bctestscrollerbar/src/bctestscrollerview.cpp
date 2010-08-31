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
#include <bctestscroller.rsg>

#include "bctestscroller.hrh"
#include "bctestscrollerview.h"
#include "bctestscrollercontainer.h"
#include "bctestutil.h"
#include "bctestscrollercase.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestScrollerView* CBCTestScrollerView::NewL()
    {
    CBCTestScrollerView* self = new( ELeave ) CBCTestScrollerView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestScrollerView::CBCTestScrollerView()
    {    
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestScrollerView::ConstructL()
    {
    BaseConstructL( R_BCTESTSCROLLER_VIEW );
    
    iContainer = new( ELeave ) CBCTestScrollerContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );
    
    iTestUtil = CBCTestUtil::NewL();
    
    // Add test case here.
    _LIT(addCase,"Scroller test case " );
    iTestUtil->AddTestCaseL( CBCTestScrollerCase::NewL( iContainer,this ), 
        addCase );    
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestScrollerView::~CBCTestScrollerView()
    {    
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// CBCTestScrollerView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestScrollerView::Id() const
    {
    return KBCTestScrollerViewId;
    }
    
// ---------------------------------------------------------------------------
// CBCTestScrollerView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestScrollerView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {    
    }
    
// ---------------------------------------------------------------------------
// CBCTestScrollerView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestScrollerView::DoDeactivate()
    {    
    }
    
// ---------------------------------------------------------------------------
// CBCTestScrollerView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestScrollerView::HandleCommandL( TInt aCommand )
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
