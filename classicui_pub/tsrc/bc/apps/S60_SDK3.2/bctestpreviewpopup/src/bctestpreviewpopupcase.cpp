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

#include <eiklabel.h>
#include <aknpreviewpopupcontroller.h>

#include "bctestpreviewpopupcase.h"
#include "bctestpreviewpopupcontainer.h"
#include "bctestpreviewpopup.hrh"

_LIT( KContent1, "Content" );


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestPreviewPopupCase* CBCTestPreviewPopupCase::NewL( 
    CBCTestPreviewPopupContainer* aContainer )
    {
    CBCTestPreviewPopupCase* self = new( ELeave ) CBCTestPreviewPopupCase( 
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
CBCTestPreviewPopupCase::CBCTestPreviewPopupCase( 
    CBCTestPreviewPopupContainer* aContainer )
    : iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestPreviewPopupCase::~CBCTestPreviewPopupCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestPreviewPopupCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestPreviewPopupCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestPreviewPopupCase::BuildScriptL()
    { 
    // Add script as your need.   
    AddTestL( DELAY(1), LeftCBA, KeyOK, TEND );    
    }
    
// ---------------------------------------------------------------------------
// CBCTestPreviewPopupCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestPreviewPopupCase::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline1 || aCmd > EBCTestCmdOutline1 )
        {
        return;
        }
    // Call release before prepare to let container has time to draw the 
    // control created in PrepareCaseL.
    ReleaseCaseL();
    PrepareCaseL( aCmd );
    switch ( aCmd )  
        {
        case EBCTestCmdOutline1:
            TestFunction();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestPreviewPopupCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestPreviewPopupCase::PrepareCaseL( TInt aCmd )
    {        
    switch ( aCmd )
        {
        case EBCTestCmdOutline1:
            // Here is a simple demo. You should create your control 
            // instead of this.
            iControl = new( ELeave ) CCoeControl();            
            iControl->SetContainerWindowL( *iContainer );
            iControl->MakeVisible( ETrue );
            break;
        default:
            break;
        }
    // Pass the owner of iControl to iContainer.
    iContainer->SetControl( iControl );
    }

// ---------------------------------------------------------------------------
// CBCTestPreviewPopupCase::ReleaseCaseL
// ---------------------------------------------------------------------------
//   
void CBCTestPreviewPopupCase::ReleaseCaseL()
    {
    // let container delete the component control.
    iContainer->ResetControl();
    iControl = NULL;
    }

// ---------------------------------------------------------------------------
// CBCTestPreviewPopupCase::TestFunction
// ---------------------------------------------------------------------------
//    
void CBCTestPreviewPopupCase::TestFunction()
    {
    
    TRect rect ( 120,100,200,150 );
    
    CEikLabel* label = new ( ELeave ) CEikLabel;    
    label->SetTextL( KContent1 );
    label->SetRect( rect );

    CAknPreviewPopUpController* popup = NULL;
    popup = CAknPreviewPopUpController::NewL( *label, 
                CAknPreviewPopUpController::EPermanentMode );
    _LIT( KNew, "CAknPreviewPopUpController::NewL() called" );
    AssertNotNullL( popup, KNew );

    delete popup;
    popup = NULL;
    popup = CAknPreviewPopUpController::NewL( *label, *this );
    AssertNotNullL( popup, KNew );
    
    delete popup;
    popup = NULL;
    popup = CAknPreviewPopUpController::NewL( *label, *this, 
                CAknPreviewPopUpController::EPermanentMode);
    AssertNotNullL( popup, KNew );
    
    delete popup;
    popup = NULL;
    popup = CAknPreviewPopUpController::NewL( *label );
    AssertNotNullL( popup, KNew );
    
    popup->SetPopUpShowDelay( 1000 );
    _LIT( KSetShowDelay, "CAknPreviewPopUpController::SetPopUpShowDelay() called ");
    AssertTrueL( ETrue, KSetShowDelay  );
    
    popup->SetPopUpHideDelay( 500 );
    _LIT( KSetHideDelay, "CAknPreviewPopUpController::SetPopupHideDelay() called ");
    AssertTrueL( ETrue, KSetHideDelay );

    popup->ShowPopUp();
    _LIT( KShowPopUp, "CAknPreviewPopUpController::ShowPopUp() called ");
    AssertTrueL( ETrue, KShowPopUp );
   
    popup->SetPosition( TPoint (120,100) );
    _LIT( KSetPosition, "CAknPreviewPopUpController::SetPosition() called " );
    AssertTrueL( ETrue, KSetPosition );

    popup->SetPositionByHighlight( rect );
    _LIT( KSetPositionByHighlight, "CAknPreviewPopUpController::SetPositionByHighlight() called " );
    AssertTrueL( ETrue, KSetPositionByHighlight );
    
    popup->AddObserverL( *this );
    _LIT( KAddObserver, "CAknPreviewPopUpController::AddObserverL() called " );
    AssertTrueL( ETrue, KAddObserver );
    
    popup->RemoveObserver( *this );
    _LIT( KRemoveObserver, "CAknPreviewPopUpController::RemoveObserver() called " );
    AssertTrueL( ETrue, KRemoveObserver );
    
    popup->UpdateContentSize();
    _LIT( KUpdateContentSize, "CAknPreviewPopUpController::UpdateContentSize() called " );
    AssertTrueL( ETrue, KUpdateContentSize );
    
    popup->SetHeadingTextL( _L("Text"));
    _LIT( KSetHeadingText, "CAknPreviewPopUpController::SetHeadingTextL() called " );
    AssertTrueL( ETrue, KSetHeadingText );
    
    TSize size = popup->Size();
    _LIT( KSize, "CAknPreviewPopUpController::Size() called " );
    AssertTrueL( size != TSize(0,0), KSize );
    
    CAknPreviewPopUpController::TAknPreviewPopUpContentSize contentSize = popup->ContentSizeInLayout();
    _LIT( KContentSize,"CAknPreviewPopUpController::ContentSizeInLayout() called " );
    AssertTrueL( ETrue, KContentSize );
    
    popup->HidePopUp();
    _LIT( KHidePopup,"CAknPreviewPopUpController::HidePopUp() called " );
    AssertTrueL( ETrue, KHidePopup );

    delete label;
    label = NULL;
                
    delete popup;
    popup=NULL;        
    }
    
// ---------------------------------------------------------------------------
// CBCTestPreviewPopupCase::HandlePreviewPopUpEventL
// ---------------------------------------------------------------------------
//        
void CBCTestPreviewPopupCase::HandlePreviewPopUpEventL(
            CAknPreviewPopUpController* aController,
            TPreviewPopUpEvent aEvent)
    {
    
    }
// ---------------------------------------------------------------------------
// CBCTestPreviewPopupCase::StartContentBuildingL
// ---------------------------------------------------------------------------
//    
void CBCTestPreviewPopupCase::StartContentBuildingL()
    {
    }
// ---------------------------------------------------------------------------
// CBCTestPreviewPopupCase::CancelContentBuilding
// ---------------------------------------------------------------------------
//        
void CBCTestPreviewPopupCase::CancelContentBuilding()
    {
    
    }
    
               