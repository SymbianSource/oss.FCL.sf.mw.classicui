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

#include "bctestutilities.hrh"
#include <bctestutilities.rsg>
#include "bctestutilitiesview.h"
#include "bctestutilitiescontainer.h"
#include "bctestutil.h"
#include "bctestutilitiescase.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestUtilitiesView* CBCTestUtilitiesView::NewL()
    {
    CBCTestUtilitiesView* self = new( ELeave ) CBCTestUtilitiesView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestUtilitiesView::CBCTestUtilitiesView()
    {    
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestUtilitiesView::ConstructL()
    {
    BaseConstructL( R_BCTESTUTILITIES_VIEW );
    
    iContainer = new( ELeave ) CBCTestUtilitiesContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );
    
    iTestUtil = CBCTestUtil::NewL();
    _LIT( KUtilitiesCase, "Utilities-AknTextUtils test case" );
    iTestUtil->AddTestCaseL( CBCTestUtilitiesCase::NewL( iContainer ), 
        KUtilitiesCase );
     
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestUtilitiesView::~CBCTestUtilitiesView()
    {    
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// CBCTestUtilitiesView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestUtilitiesView::Id() const
    {
    return KBCTestUtilitiesViewId;
    }
    
// ---------------------------------------------------------------------------
// CBCTestUtilitiesView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestUtilitiesView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {    
    }
    
// ---------------------------------------------------------------------------
// CBCTestUtilitiesView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestUtilitiesView::DoDeactivate()
    {    
    }
    
// ---------------------------------------------------------------------------
// CBCTestUtilitiesView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestUtilitiesView::HandleCommandL( TInt aCommand )
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
