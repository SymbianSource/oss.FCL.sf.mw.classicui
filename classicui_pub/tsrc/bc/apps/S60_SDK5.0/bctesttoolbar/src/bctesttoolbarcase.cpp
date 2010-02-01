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
#include <aknnotewrappers.h>
#include <akntoolbar.h>
#include <akntoolbarobserver.h>
#include <akntoolbarextension.h>
#include <bctesttoolbar.rsg>
#include <eikcmbut.h>
#include <barsread.h>
#include <aknbutton.h>
#include <avkon.rsg>

#include "bctesttoolbarapp.h"
#include "bctesttoolbarcase.h"
#include "bctesttoolbarcontainer.h"
#include "bctesttoolbar.hrh"
#include "bctesttoolbarderived.h"

// ======== MEMBER FUNCTIONS ========

// --------------------------------------------------------------------------
// Symbian 2nd static Constructor
// --------------------------------------------------------------------------
//
CBCTestToolBarCase* CBCTestToolBarCase::NewL( 
    CBCTestToolBarContainer* aContainer )
    {
    CBCTestToolBarCase* self = new( ELeave ) CBCTestToolBarCase( 
        aContainer );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// --------------------------------------------------------------------------
// C++ default constructor
// --------------------------------------------------------------------------
//
CBCTestToolBarCase::CBCTestToolBarCase( 
    CBCTestToolBarContainer* aContainer )
    : iContainer( aContainer )
    {    
    }
    
// --------------------------------------------------------------------------
// Destructor
// --------------------------------------------------------------------------
//
CBCTestToolBarCase::~CBCTestToolBarCase()
    {  
    }
    
// --------------------------------------------------------------------------
// Symbian 2nd Constructor
// --------------------------------------------------------------------------
//
void CBCTestToolBarCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// --------------------------------------------------------------------------
// CBCTestToolBarCase::BuildScriptL
// --------------------------------------------------------------------------
//
void CBCTestToolBarCase::BuildScriptL()
    { 
    // Add script as your need.
    const TInt scripts[] =
        {
        DELAY( 5 ), // delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA,
        LeftCBA
        };
    AddTestScriptL( scripts, sizeof( scripts )/sizeof( TInt ) );
    }
    
// --------------------------------------------------------------------------
// CBCTestToolBarCase::RunL
// --------------------------------------------------------------------------
//
void CBCTestToolBarCase::RunL( TInt aCmd )
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

// --------------------------------------------------------------------------
// CBCTestToolBarCase::DynInitToolbarL
// --------------------------------------------------------------------------
//
void CBCTestToolBarCase::DynInitToolbarL( TInt /*aResourceId*/, 
	CAknToolbar* /*aToolbar*/ )
	{
	
	}
	
// --------------------------------------------------------------------------
// CBCTestToolBarCase::OfferToolbarEventL
// --------------------------------------------------------------------------
//
void CBCTestToolBarCase::OfferToolbarEventL( TInt /*aCommand*/ )
	{
	
	}

// --------------------------------------------------------------------------
// CBCTestToolBarCase::TestFunctionL
// --------------------------------------------------------------------------
//   
void CBCTestToolBarCase::TestFunctionL()
    {
    // Test some API here
    CAknToolbar *toolBar = 
        CAknToolbar::NewL( R_BCTESTTOOLBAR_CBA_OPTIONS_NEXT );
    CleanupStack::PushL( toolBar );

	CAknButton *leftButton = 
	    CAknButton::NewLC( NULL, NULL, NULL,
                          NULL, _L( "LeftButton" ), KNullDesC, 
                          KAknButtonNoFrame, 0 );    
    toolBar->AddItemL( 
    	leftButton, EAknCtButton, EBCTestToolBarCbaCmdLeftBtn, 1 );
    _LIT( KAddItem, "CAknToolbar::AddItemL() called" );
    AssertTrueL( ETrue, KAddItem );
    CleanupStack::Pop( leftButton );

    _LIT( KRightButton, "RightButton" );
    CAknButton *rightButton = 
	    CAknButton::NewLC( NULL, NULL, NULL,
                          NULL, KRightButton, KNullDesC, 
                          KAknButtonNoFrame, 0 );  
        
    toolBar->AddItemL( 
        rightButton, EAknCtButton, EBCTestToolBarCbaCmdRightBtn, 1, 1 );
    _LIT( KAddItem2, "CAknToolbar::AddItemL() with index called" );
    AssertTrueL( ETrue, KAddItem2 );

    CleanupStack::Pop( rightButton );

                               
	TInt count = toolBar->CountComponentControls();
	_LIT( KCount, "CAknToolbar::CountComponentControls() called" );
	AssertIntL( 2, count, KCount );

	CCoeControl* control = toolBar->ComponentControl( 1 );
	_LIT( KComponentControl, "CAknToolbar::ComponentControl() called" );
	AssertNotNullL( control, KComponentControl );
	
	CCoeControl* rightControl = 
	    toolBar->ControlOrNull( EBCTestToolBarCbaCmdRightBtn );
	_LIT( KControlOrNull, "CAknToolbar::ControlOrNull() called" );
	AssertNotNullL( control, KControlOrNull );

	toolBar->SetToolbarVisibility( ETrue );
	_LIT( KSetVisible, "CAknToolbar::SetToolbarVisibility() called" );
	AssertTrueL( ETrue, KSetVisible );

	TBool isShown = toolBar->IsShown();
	_LIT( KIsShown, "CAknToolbar::IsShown() called" );
	AssertTrueL( isShown, KIsShown );

    toolBar->SetInitialFocusedItem( EBCTestToolBarCbaCmdRightBtn );
	_LIT( KSetInitial, "CAknToolbar::SetInitialFocusedItem() called" );
	AssertTrueL( ETrue, KSetInitial );
    
	toolBar->ProcessCommandL( EBCTestToolBarCbaCmdRightBtn ); 
	_LIT( KProcessCommand, "CAknToolbar::ProcessCommandL() called" );
	AssertTrueL( ETrue, KProcessCommand );

	toolBar->PositionChanged();
	_LIT( KPositionChanged, "CAknToolbar::PositionChanged() called" );
	AssertTrueL( ETrue, KPositionChanged );

    toolBar->SetFocusedItemL( EBCTestToolBarCbaCmdRightBtn );
    _LIT( KSetFocusedItem, "CAknToolbar::SetFocusedItemL() called" );
    AssertTrueL( ETrue, KSetFocusedItem );

    TInt focusedItem = toolBar->FocusedItem();
    _LIT( KFocusedItem, "CAknToolbar::FocusedItem() called" );
    AssertIntL( EBCTestToolBarCbaCmdRightBtn, focusedItem , KFocusedItem );


	toolBar->SetDimmed( ETrue );
	_LIT( KSetDimmed, "CAknToolbar::SetDimmed() called" );
	AssertTrueL( ETrue, KSetDimmed );
	
	toolBar->UpdateBackground();
	_LIT( KUpdateBackground, "CAknToolbar::UpdateBackground() called" );
	AssertTrueL( ETrue, KUpdateBackground );
	
	toolBar->SetWithSliding( ETrue );
	_LIT( KSetWithSliding, "CAknToolbar::SetWithSliding() called" );
	AssertTrueL( ETrue, KSetWithSliding );
	
	toolBar->SetEmphasis( ETrue );
	_LIT( KSetEmphasis, "CAknToolbar::SetEmphasis() called" );
	AssertTrueL( ETrue, KSetEmphasis );

	toolBar->SetItemDimmed( EBCTestToolBarCbaCmdRightBtn, ETrue, ETrue );
	_LIT( KSetItemDimmed, "CAknToolbar::SetItemDimmed() called" );
	AssertTrueL( ETrue, KSetItemDimmed );

	toolBar->HideItem( EBCTestToolBarCbaCmdRightBtn, ETrue, ETrue );
	_LIT( KHideItem, "CAknToolbar::HideItem() called" );
	AssertTrueL( ETrue, KHideItem );

	toolBar->RemoveItem( EBCTestToolBarCbaCmdRightBtn );
	_LIT( KRemoveItem, "CAknToolbar::RemoveItem() called" );
	AssertTrueL( ETrue, KRemoveItem );
	

	toolBar->SetCloseOnCommand( EBCTestToolBarCbaCmdRightBtn, ETrue );
	_LIT( KSetCloseOnCommand, "CAknToolbar::SetCloseOnCommand() called" );
	AssertTrueL( ETrue, KSetCloseOnCommand );

	toolBar->SetCloseOnAllCommands( ETrue );
	_LIT( KSetCloseOnAllCmds, "CAknToolbar::SetCloseOnAllCommands() called" );
	AssertTrueL( ETrue, KSetCloseOnAllCmds );

	toolBar->SetOrientation( EAknOrientationVertical );
	_LIT( KSetOrientation, "CAknToolbar::SetOrientation() called" );
	AssertTrueL( ETrue, KSetOrientation );
	
	TBool isSupported = toolBar->IsSupportedItemType ( EAknCtButton );
	_LIT( KIsSupported, "CAknToolbar::IsSupportedItemType() called" );
	AssertTrueL( isSupported, KIsSupported );
    
	TRect rect = iContainer->Rect(); 
	iContainer->ActivateGc();
    toolBar->Draw( iContainer->SystemGc(), *iContainer, rect );
    iContainer->DeactivateGc();
    _LIT( KDraw, "CAknToolbar::Draw() called" );
    AssertTrueL( ETrue, KDraw );    
 
    TPointerEvent pointerEvent;
    TPoint point;
    point.iX = 5;
    point.iY = 5;
    pointerEvent.iModifiers = 0;
    pointerEvent.iParentPosition =  point;
    pointerEvent.iPosition = point;
    pointerEvent.iType = TPointerEvent::EButton1Up; 
    
    toolBar->HandlePointerEventL( pointerEvent );
	_LIT( KHandlePointerEventL, "CAknToolbar::HandlePointerEventL() called" );
	AssertTrueL( ETrue, KHandlePointerEventL );
 
    TKeyEvent keyEvent;
    toolBar->OfferKeyEventL( keyEvent,EEventKey );    
	_LIT( KOfferKeyEventL, "CAknToolbar::OfferKeyEventL() called" );
	AssertTrueL( ETrue, KOfferKeyEventL );
    
    toolBar->HandleResourceChange( KEikDynamicLayoutVariantSwitch );
	_LIT( KHandleResChange, "CAknToolbar::HandleResourceChange() called" );
	AssertTrueL( ETrue, KHandleResChange );

    toolBar->HandleControlEventL( 
        iContainer, CAknToolbar::EEventRequestExit );
    _LIT( KHandleControlEventL, 
        "CAknToolbar::HandleControlEventL() called" );
    AssertTrueL( ETrue, KHandleControlEventL );
     
    TCoeInputCapabilities inputCapabilities = toolBar->InputCapabilities();
    _LIT( KInputCapabilities, "CAknToolbar::InputCapabilities() called" );
    AssertTrueL( ( inputCapabilities == TCoeInputCapabilities::EAllText ), 
        KInputCapabilities );
    
    toolBar->SetToolbarObserver( this );
    _LIT( KSetToolbarObserver, "CAknToolbar::SetToolbarObserver() called" );
    AssertTrueL( ETrue, KSetToolbarObserver );
    
    MAknToolbarObserver* observer = toolBar->ToolbarObserver();
    _LIT( KToolbarObserver, "CAknToolbar::ToolbarObserver() called" );
    AssertNotNullL( observer, KToolbarObserver );
    
     TInt modifiers = toolBar->EventModifiers(); 
    _LIT( KEventModifiers, "CAknToolbar::EventModifiers() called" );
    AssertTrueL( ETrue, KEventModifiers );

    CAknToolbarExtension* extn = toolBar->ToolbarExtension();
    _LIT( KToolBarExtension, "CAknToolbar::ToolBarExtension() called" );
    AssertTrueL( ETrue, KToolBarExtension );

    toolBar->SetToolbarVisibility( EFalse, ETrue );
    _LIT( KSetToolbarVisibility2, "CAknToolbar::SetToolbarVisibility(TBool,TBool) called" );
    AssertTrueL( ETrue, KSetToolbarVisibility2 );

    // Leaves if toolbar is shown
    toolBar->DisableToolbarL( ETrue );
    _LIT( KDisableToolbar, "CAknToolbar::DisableToolbarL() called" );
    AssertTrueL( ETrue, KDisableToolbar );

    TBool disabled = toolBar->IsToolbarDisabled();
    _LIT( KIsToolbarDisabled, "CAknToolbar::IsToolbarDisabled() called" );
    AssertTrueL( disabled, KIsToolbarDisabled );

    TInt flags = toolBar->ToolbarFlags(); 
    _LIT( KToolbarFlags, "CAknToolbar::ToolbarFlags() called" );
    AssertTrueL( flags >= 0, KToolbarFlags );

    toolBar->SetSoftkeyResourceIdL( R_AVKON_SOFTKEYS_CLOSE ); 
    _LIT( KSoftkeyResource, "CAknToolbar::SetSoftkeyResourceIdL() called" );
    AssertTrueL( ETrue, KSoftkeyResource );

       
    CBCTestToolBarDerived* toolBarDerived = static_cast<CBCTestToolBarDerived*> 
        (CAknToolbar::NewL( R_BCTESTTOOLBAR_CBA_OPTIONS_NEXT ) );
    CleanupStack::PushL( toolBarDerived );
    toolBarDerived->SizeChanged();
    _LIT( KSizeChanged, "CAknToolbar::SizeChanged() called" );
    AssertTrueL( ETrue, KSizeChanged );
   
    toolBarDerived->FocusChanged( EDrawNow );
    _LIT( KFocusChanged, "CAknToolbar::FocusChanged() called" );
    AssertTrueL( ETrue, KFocusChanged );
    
    _LIT( KExtInterface, "CAknToolbar::ExtensionInterface");
    AssertTrueL( 
        toolBarDerived->ExtensionInterface( KUidBCTestToolBar ) == NULL, 
        KExtInterface );
    
    TTypeUid::Ptr ptr = toolBarDerived->MopSupplyObject( CEikCba::ETypeId );
    ptr = toolBarDerived->MopSupplyObject( 
        CEikButtonGroupContainer::ETypeId );
    _LIT( KMopSupplyObject, "CAknToolbar::MopSupplyObject() called" );
    AssertTrueL( ETrue, KMopSupplyObject );
    
   
    CBCTestToolBarObserver tool;
    MAknToolbarObserver* toolBarCase = &tool;
    
    TInt resId=100;
    toolBarCase->DynInitToolbarL( resId, toolBar );
    _LIT( KDynInitToolBarL, "MAknToolBarObserver::DynInitToolBarL() tested");
    AssertTrueL( ETrue, KDynInitToolBarL ); 

    TInt aCmd = 1;
    toolBarCase->OfferToolbarEventL( aCmd );
    _LIT( KOfferToolbarEventL, "MAknToolBarObserver::OfferToolbarEventL() tested");
    AssertTrueL( ETrue, KOfferToolbarEventL ); 

    CleanupStack::PopAndDestroy( toolBarDerived );
    
    CleanupStack::PopAndDestroy( toolBar );
    }
    
/*void CBCTestToolBarObserver::DynInitToolbarL(TInt resId, CAknToolbar* aToolbar )
{
	
}*/

void CBCTestToolBarObserver::OfferToolbarEventL( TInt )
{
	
}
/*
void CBCTestToolBarObserver::Call()
{
	TInt a = MAknToolbarObserver_Reserved_1();
	TInt b = MAknToolbarObserver_Reserved_2();
}*/