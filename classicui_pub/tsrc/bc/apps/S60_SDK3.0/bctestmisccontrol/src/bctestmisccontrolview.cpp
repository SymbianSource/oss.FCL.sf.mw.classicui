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
* Description:         Implements test bc for misc control view.
*
*/









#include <aknviewappui.h>
#include <bctestmisccontrol.rsg>

#include "bctestmisccontrol.hrh"
#include "bctestmisccontrolview.h"
#include "bctestmisccontrolcontainer.h"
#include "bctestutil.h"
#include "bctesteikcaptionedcontrolcase.h"
#include "bctesteikconsolecontrolcase.h"
#include "bctesteikcontrolgroupcase.h"

//Constant
_LIT( KEikCaptionedControlCaseComment, "Eik captioned control case" );
_LIT( KEikConsoleControlCaseComment, "Eik console control case" );
_LIT( KEikControlGroupCaseComment, "Eik control group case" );

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestMiscControlView* CBCTestMiscControlView::NewL()
    {
    CBCTestMiscControlView* self = new ( ELeave ) CBCTestMiscControlView();
    CleanupStack::PushL( self );
    self->ConstructL(); 
    CleanupStack::Pop( self ); 
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CBCTestMiscControlView::CBCTestMiscControlView()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestMiscControlView::ConstructL()
    {
    BaseConstructL( R_BCTESTMISCCONTROL_VIEW );

    iContainer = new( ELeave ) CBCTestMiscControlContainer();
    iContainer->SetMopParent( this );
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );

    iTestUtil = CBCTestUtil::NewL();

    // Add test case here.
    iTestUtil->AddTestCaseL( 
        CBCTestEikCaptionedControlCase::NewL( iContainer ),
        KEikCaptionedControlCaseComment );  

    iTestUtil->AddTestCaseL( 
        CBCTestEikConsoleControlCase::NewL( iContainer ),
        KEikConsoleControlCaseComment ); 

    iTestUtil->AddTestCaseL(  
        CBCTestEikControlGroupCase::NewL( iContainer ),
        KEikControlGroupCaseComment );                      
                   
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestMiscControlView::~CBCTestMiscControlView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    delete iTestUtil;
    }

// ---------------------------------------------------------------------------
// CBCTestMiscControlView::Id
// ---------------------------------------------------------------------------
//
TUid CBCTestMiscControlView::Id() const
    {
    return KBCTestMiscControlViewId;
    }

// ---------------------------------------------------------------------------
// CBCTestMiscControlView::DoActivateL
// ---------------------------------------------------------------------------
//
void CBCTestMiscControlView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestMiscControlView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CBCTestMiscControlView::DoDeactivate()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestMiscControlView::HandleCommandL
// ---------------------------------------------------------------------------
//
void CBCTestMiscControlView::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EBCTestMiscControlCmdAutotest:
            iTestUtil->RunL();
            break;
        default:
            if ( aCommand > EBCTestMiscControlCmdEmptyOutline &&
                 aCommand < EBCTestMiscControlCmdMaxOutline )
                {
                iTestUtil->RunL( aCommand );
                }
            break;
        }
    }
