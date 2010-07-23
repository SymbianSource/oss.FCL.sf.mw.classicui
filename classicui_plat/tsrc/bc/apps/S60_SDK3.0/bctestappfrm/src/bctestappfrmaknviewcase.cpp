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
#include <s32strm.h> 
#include <vwsdef.h>

#include "bctestappfrmaknviewcase.h"
#include "bctestappfrmcontainer.h"
#include "bctestappfrm.hrh"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestAppFrmAknViewCase* CBCTestAppFrmAknViewCase::NewL( 
    CBCTestAppFrmContainer* aContainer ,CAknView* aView)
    {
    CBCTestAppFrmAknViewCase* self = new( ELeave ) CBCTestAppFrmAknViewCase( 
        aContainer ,aView);
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestAppFrmAknViewCase::CBCTestAppFrmAknViewCase( 
    CBCTestAppFrmContainer* aContainer ,CAknView* aView)
    : iContainer( aContainer ) , iView ( aView )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestAppFrmAknViewCase::~CBCTestAppFrmAknViewCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestAppFrmAknViewCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestAppFrmAknViewCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestAppFrmAknViewCase::BuildScriptL()
    { 
    // Add script as your need.   
        const TInt scripts[] =
        {
        DELAY(1),        // delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA, 
        REP(Down, 7),
        LeftCBA
        };
    AddTestScriptL(scripts, sizeof(scripts)/sizeof(TInt));  
    }
    
// ---------------------------------------------------------------------------
// CBCTestAppFrmAknViewCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestAppFrmAknViewCase::RunL( TInt aCmd )
    {
    if ( aCmd !=EBCTestAknView)
        {
        return;
        }
    // Call release before prepare to let container has time to draw the 
    // control created in PrepareCaseL.
    ReleaseCaseL();
    PrepareCaseL( aCmd );
    TestFunction();
    }

// ---------------------------------------------------------------------------
// CBCTestAppFrmAknViewCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestAppFrmAknViewCase::PrepareCaseL( TInt aCmd )
    {        
    switch ( aCmd )
        {
        case EBCTestAknView:
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
// CBCTestAppFrmAknViewCase::ReleaseCaseL
// ---------------------------------------------------------------------------
//   
void CBCTestAppFrmAknViewCase::ReleaseCaseL()
    {
    // let container delete the component control.
    iContainer->ResetControl();
    iControl = NULL;
    }

// ---------------------------------------------------------------------------
// CBCTestAppFrmAknViewCase::TestLayoutDecorator
// ---------------------------------------------------------------------------
//    
void CBCTestAppFrmAknViewCase::TestFunction()
    {
    // Test some API here
        TestPublicFunction();
        TestProtectedFunction();  
    }
    
// ---------------------------------------------------------------------------
// CBCTestAppFrmAknViewCase::TestPublicFunction  (Test class CAknView)
// ---------------------------------------------------------------------------
//     
void CBCTestAppFrmAknViewCase::TestPublicFunction()
    {
    TVwsViewId iVwsViewId = iView->ViewId();
    iView->ActivateViewL( iVwsViewId ); 
    _LIT( KActivateViewL1 , "CAknView::ActivateViewL() invoked" );
    AssertTrueL( ETrue, KActivateViewL1 );
    
    iView->ActivateViewL( iVwsViewId, KNullUid, KNullDesC8 );
    _LIT( KActivateViewL2, 
    "CAknView::ActivateViewL(const TVwsViewId&) invoked" );
    AssertTrueL( ETrue, KActivateViewL2 );
    
    iView->AknViewActivatedL( iVwsViewId, KNullUid, KNullDesC8 );
    _LIT( KAknViewActivatedL,
    "CAknView::AknViewActivatedL(TVwsViewId&,TUid,TDesC8&) invoked" );
    AssertTrueL( ETrue, KAknViewActivatedL );

    iView->ClientRect();
     _LIT( KClientRect , "CAknView::ClientRect() invoked" );
    AssertTrueL( ETrue, KClientRect);
    
    iView->ConstructMenuAndCbaEarlyL();
    _LIT( KConstructMenuAndCbaEarlyL, 
    "CAknView::ConstructMenuAndCbaEarlyL() invoked" );
    AssertTrueL( ETrue, KConstructMenuAndCbaEarlyL );

    iView->HandleStatusPaneSizeChange();
    _LIT( KHandleStatusPaneSizeChange,
    "CAknView::HandleStatusPaneSizeChange() invoked" );
    AssertTrueL( ETrue, KHandleStatusPaneSizeChange );
    
    iView->HandleViewRectChange();
    _LIT( KHandleViewRectChange, "CAknView::HandleViewRectChange() invoked" );
    AssertTrueL( ETrue, KHandleViewRectChange );

    iView->Id();
    _LIT( KId, "CAknView::Id() invoked" );
    AssertTrueL( ETrue, KId);    
    
    iView->IsForeground();
    _LIT( KIsForeground, "CAknView::IsForeground() invoked" );
    AssertTrueL( ETrue, KIsForeground );    
    
    iView->Redraw();
    _LIT( KRedraw, "CAknView::Redraw() invoked" );
    AssertTrueL( ETrue, KRedraw );    
    
    iView->StopDisplayingToolbar();
    _LIT( KStopDisplayingToolbar, 
    "CAknView::StopDisplayingToolbar() invoked" );
    AssertTrueL( ETrue, KStopDisplayingToolbar );    
    
    iView->Toolbar();
    _LIT( KToolbar , "CAknView::Toolbar() invoked" );
    AssertTrueL( ETrue, KToolbar );    
    
    }

// ---------------------------------------------------------------------------
// CBCTestAppFrmAknViewCase::TestProtectedFunction  (Test class CAknView)
// ---------------------------------------------------------------------------
//   
void CBCTestAppFrmAknViewCase::TestProtectedFunction()
    {
    CBCTestAppFrmView* iTestView = static_cast<CBCTestAppFrmView*>( iView );
    iTestView->AppFrmView_cba();
    _LIT( Kcba , "CAknView::cba() invoked" );
    AssertTrueL( ETrue, Kcba);  
      
    iTestView->AppFrmView_HandleCommandL(1);
    _LIT( KHandleCommandL , "CAknView::HandleCommandL(TInt) invoked" );
    AssertTrueL( ETrue, KHandleCommandL); 
    
    iTestView->AppFrmView_StatusPane();
    _LIT( KStatusPane, "CAknView::StatusPane() invoked" );
    AssertTrueL( ETrue, KStatusPane );    

    iTestView->AppFrmView_ViewScreenDeviceChangedL();
    _LIT( KViewScreenDeviceChangedL,
    "CAknView::ViewScreenDeviceChangedL() invoked" );
    AssertTrueL( ETrue, KViewScreenDeviceChangedL );    
    
    iTestView->AppFrmView_DoActivateL( iView->ViewId(), KNullUid, KNullDesC8 );
    _LIT( KDoActivateL,
    "CAknView::DoActivateL() invoked" );
    AssertTrueL( ETrue, KDoActivateL );    

    iTestView->AppFrmView_MopNext();
    _LIT( KMopNext , "CAknView::MopNext() invoked" );
    AssertTrueL( ETrue, KMopNext );    
 
    iTestView->AppFrmView_MopSupplyObject( 0 );
    _LIT( KMopSupplyObject ,"CAknView::MopSupplyObject(TTypeUid) invoked" );
    AssertTrueL( ETrue, KMopSupplyObject );    
    
    }
