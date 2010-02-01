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
#include <bctestbuttons.rsg>

#include "bctestbuttons.hrh"
#include "bctestbuttonsview.h"
#include "bctestbuttonscontainer.h"
#include "bctestutil.h"
#include "bctestbuttonscase.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestButtonsView* CBCTestButtonsView::NewL()
    {
    CBCTestButtonsView* self = new( ELeave ) CBCTestButtonsView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestButtonsView::CBCTestButtonsView()
    {    
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestButtonsView::ConstructL()
    {
    BaseConstructL( R_BCTESTBUTTONS_VIEW );
    
    iContainer = new( ELeave ) CBCTestButtonsContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );
    
    iTestUtil = CBCTestUtil::NewL();
    // Add test case here.
    _LIT( KEikBgftyCase , " eikbgfty Test for Buttons case" );
    iTestUtil->AddTestCaseL( CBCTestButtonsCase::NewL( iContainer ), 
        KEikBgftyCase );
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestButtonsView::~CBCTestButtonsView()
    {    
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// CBCTestButtonsView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestButtonsView::Id() const
    {
    return KBCTestButtonsViewId;
    }
    
// ---------------------------------------------------------------------------
// CBCTestButtonsView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestButtonsView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {    
    }
    
// ---------------------------------------------------------------------------
// CBCTestButtonsView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestButtonsView::DoDeactivate()
    {    
    }
    
// ---------------------------------------------------------------------------
// CBCTestButtonsView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestButtonsView::HandleCommandL( TInt aCommand )
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


