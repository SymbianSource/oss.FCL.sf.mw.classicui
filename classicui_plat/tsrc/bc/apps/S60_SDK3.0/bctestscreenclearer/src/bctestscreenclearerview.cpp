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
#include <bctestscreenclearer.rsg>

#include "bctestscreenclearer.hrh"
#include "bctestscreenclearerview.h"
#include "bctestscreenclearercontainer.h"
#include "bctestutil.h"
#include "bctestscreenclearercase.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestScreenClearerView* CBCTestScreenClearerView::NewL()
    {
    CBCTestScreenClearerView* self = new( ELeave ) CBCTestScreenClearerView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestScreenClearerView::CBCTestScreenClearerView()
    {    
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestScreenClearerView::ConstructL()
    {
    BaseConstructL( R_BCTESTSCREENCLEARER_VIEW );
    
    iContainer = new( ELeave ) CBCTestScreenClearerContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );
    
    iTestUtil = CBCTestUtil::NewL();
    
    // Add test case here.
    _LIT( KTestcase, "ScreenClearer test case" );
    iTestUtil->AddTestCaseL( CBCTestScreenClearerCase::NewL( iContainer ), 
        KTestcase );
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestScreenClearerView::~CBCTestScreenClearerView()
    {    
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// CBCTestScreenClearerView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestScreenClearerView::Id() const
    {
    return KBCTestScreenClearerViewId;
    }
    
// ---------------------------------------------------------------------------
// CBCTestScreenClearerView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestScreenClearerView::DoActivateL( const TVwsViewId&, TUid, 
    const TDesC8& )
    {     
    }
    
// ---------------------------------------------------------------------------
// CBCTestScreenClearerView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestScreenClearerView::DoDeactivate()
    {    
    }
    
// ---------------------------------------------------------------------------
// CBCTestScreenClearerView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestScreenClearerView::HandleCommandL( TInt aCommand )
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




