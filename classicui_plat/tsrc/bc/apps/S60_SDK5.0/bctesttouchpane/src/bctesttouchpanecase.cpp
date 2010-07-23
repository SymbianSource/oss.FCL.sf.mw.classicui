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
* Description:         test case
*
*/









#include <w32std.h>
#include <coecntrl.h>
#include <aknscreenmode.h>
#include <aknappui.h>
#include <akntouchpane.h>
#include <bctesttouchpane.rsg>
#include <aknsconstants.h>
#include <aknutils.h> 

#include "bctesttouchpanecase.h"
#include "bctesttouchpanecontainer.h"
#include "bctesttouchpane.hrh"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestTouchPaneCase* CBCTestTouchPaneCase::NewL( 
    CBCTestTouchPaneContainer* aContainer )
    {
    CBCTestTouchPaneCase* self = new( ELeave ) CBCTestTouchPaneCase( 
        aContainer );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestTouchPaneCase::CBCTestTouchPaneCase( 
    CBCTestTouchPaneContainer* aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestTouchPaneCase::~CBCTestTouchPaneCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestTouchPaneCase::ConstructL()
    {    
    BuildScriptL();
    iEnv = CEikonEnv::Static();     
    }
    
// ---------------------------------------------------------------------------
// CBCTestTouchPaneCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestTouchPaneCase::BuildScriptL()
    { 
    // Add script as your need.   
    AddTestL( DELAY(1), LeftCBA, KeyOK, TEND );    
    }
    
// ---------------------------------------------------------------------------
// CBCTestTouchPaneCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestTouchPaneCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline1 || aCmd > EBCTestCmdOutline1 )
        {
        return;
        }
        
    switch ( aCmd )  
        {
        case EBCTestCmdOutline1:
            TestFunctionL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestTouchPaneCase::TestAknTouchPaneL
// ---------------------------------------------------------------------------
// 
void CBCTestTouchPaneCase::TestAknTouchPaneL()
    {
    
    if ( ! AknLayoutUtils::PenEnabled() )
        {
        return;
        }
    
    CAknTouchPane* touchPane1 = CAknTouchPane::NewL();
    delete touchPane1;
    _LIT( KNewL1, "NewL test" );
    AssertTrueL( ETrue, KNewL1 );
    
    CAknTouchPane* touchPane2 = CAknTouchPane::NewL( 
        R_BCTESTTOUCHPANE_TOUCHPANE );
    
    CleanupStack::PushL( touchPane2 );    
    _LIT( KNewL2, "NewL with resourceId test" );
    AssertTrueL( ETrue, KNewL2 );
    
    TRect rect = iContainer->Rect(); 
    touchPane2->ReduceRect( rect );
    _LIT( KReduceRect, "ReduceRect test" );
    AssertTrueL( ETrue, KReduceRect );
    
    CBCTestObserver* observer = new( ELeave ) CBCTestObserver();
    CleanupStack::PushL( observer );
    touchPane2->SetObserver( observer );    
    _LIT( KSetObserver, "SetObserver test" );
    AssertTrueL( ETrue, KSetObserver );
    
    CAknTouchPane::TVisibilityMode vmode;
    touchPane2->SetVisibilityMode(vmode);
    _LIT(KSetVisibilityMode, "SetVisibility test");
    AssertTrueL( ETrue, KSetVisibilityMode );
    
    touchPane2->AllowInputMethodActivation( ETrue );
    _LIT( KAllowInputMethodActivation, 
        "AllowInputMethodActivation test" );
    AssertTrueL( ETrue, KAllowInputMethodActivation );
    
    touchPane2->SetInputMethodIconActivated( ETrue );
    _LIT( KSetInputMethodIconActivated, 
        "SetInputMethodIconActivated test" );
    AssertTrueL( ETrue, KSetInputMethodIconActivated );
    
    touchPane2->RefreshL();
    _LIT( KRefreshL, "RefreshL test" );
    AssertTrueL( ETrue, KRefreshL );

#if 0 //SDK API using Domain API Class
    //komala    
    CBCTestFepPen* interface = new( ELeave ) CBCTestFepPen();
    CleanupStack::PushL( interface );
    touchPane2->SetFepPenSupportInterface( interface );
    _LIT( KSetFepPenSupportInterface, "SetFepPenSupportInterface test" );
    AssertTrueL( ETrue, KSetFepPenSupportInterface );
    CleanupStack::PopAndDestroy( interface );
#endif     
           
    TInt countControls = touchPane2->CountComponentControls();
    _LIT( KCountComponentControls, "CountComponentControls test" );
    AssertTrueL( ETrue, KCountComponentControls );
            
    CCoeControl* componentControl = 
        touchPane2->ComponentControl( 0 );
    _LIT( KComponentControl, "ComponentControl test" );
    AssertTrueL( ETrue, KComponentControl );
    
    iContainer->ActivateGc();
    touchPane2->Draw( iContainer->SystemGc(), *iContainer, rect );
    iContainer->DeactivateGc();
    _LIT( KDraw, "Draw test" );
    AssertTrueL( ETrue, KDraw );    
    
    touchPane2->HandleControlEventL( iContainer, 
    	CAknTouchPane::EEventRequestExit );
    _LIT( KHandleControlEventL, "HandleControlEventL test" );
    AssertTrueL( ETrue, KHandleControlEventL );
    
    //TKeyEvent evt = { EKeyPause, EStdKeySpace, 0, 0  };
    TWsEvent evt;
    touchPane2->HandleWsEventL( evt, iContainer );
    _LIT( KHandleWsEventL, "HandleWsEventL test" );
    AssertTrueL( ETrue, KHandleWsEventL );
    
    touchPane2->HandleResourceChange( KAknsMessageSkinChange );
    touchPane2->HandleResourceChange( KEikDynamicLayoutVariantSwitch );
    _LIT( KHandleResourceChange, "HandleResourceChange test" );
    AssertTrueL( ETrue, KHandleResourceChange );
    
    touchPane2->MakeVisible( ETrue );
    _LIT( KMakeVisible, "MakeVisible test" );
    AssertTrueL( ETrue, KMakeVisible );
    
    TKeyEvent keyEvent = { EKeyPause, EStdKeySpace, 0, 0  };
    TKeyResponse response = touchPane2->OfferKeyEventL( keyEvent,EEventNull );
    _LIT( KOfferKeyEventL, "OfferKeyEventL test" );
    AssertTrueL( ETrue, KOfferKeyEventL );   
    
    CleanupStack::PopAndDestroy( observer );
    CleanupStack::PopAndDestroy( touchPane2 );
    }
// ---------------------------------------------------------------------------
// CBCTestTouchPaneCase::TestLayoutDecorator
// ---------------------------------------------------------------------------
//    
void CBCTestTouchPaneCase::TestFunctionL()
    {
    TestAknTouchPaneL();
    }

// ---------------------------------------------------------------------------
// CBCTestObserver::HandleTouchPaneSizeChange
// ---------------------------------------------------------------------------
//    
void CBCTestObserver::HandleTouchPaneSizeChange()
    {
    
    }


#if 0 //SDK API using Domain API Class
// ---------------------------------------------------------------------------
// CBCTestFepPen::ActivatePenInputL
// ---------------------------------------------------------------------------
// 
//komala
void CBCTestFepPen::ActivatePenInputL()
    {
    
    }

// ---------------------------------------------------------------------------
// CBCTestFepPen::DeactivatePenInput
// ---------------------------------------------------------------------------
// 
void CBCTestFepPen::DeactivatePenInputL()
    {
    
    }
#endif
