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
#include <aknappui.h>
#include <eikenv.h>
#include <eikappui.h>
#include <akndef.h> // for TAknUiZoom
#include <AknAppUi.h>
#include <e32err.h>
#include <bctestappfrm.rsg>

#include "bctestappfrm.hrh"
#include "bctestappfrmaknappuicase.h"
#include "bctestappfrmcontainer.h"
#include "bctestappfrmappui.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestAppFrmAknAppUICase* CBCTestAppFrmAknAppUICase::NewL(
    CBCTestAppFrmContainer* aContainer )
    {
    CBCTestAppFrmAknAppUICase* self = new( ELeave ) CBCTestAppFrmAknAppUICase(
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
CBCTestAppFrmAknAppUICase::CBCTestAppFrmAknAppUICase(
    CBCTestAppFrmContainer* aContainer )
    : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestAppFrmAknAppUICase::~CBCTestAppFrmAknAppUICase()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestAppFrmAknAppUICase::ConstructL()
    {
    BuildScriptL();
    }

// ---------------------------------------------------------------------------
// CBCTestAppFrmAknAppUICase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestAppFrmAknAppUICase::BuildScriptL()
    {
       const TInt scripts[] =
        {
        DELAY(1),        // delay between commands is 1*0.1 seconds = 0.1 seconds
        LeftCBA,
        REP(Down, 6),
        LeftCBA
        };
    AddTestScriptL(scripts, sizeof(scripts)/sizeof(TInt));
    }

// ---------------------------------------------------------------------------
// CBCTestAppFrmAknAppUICase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestAppFrmAknAppUICase::RunL( TInt aCmd )
    {
    if ( aCmd !=EBCTestAknAppUi)
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
// CBCTestAppFrmAknAppUICase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestAppFrmAknAppUICase::PrepareCaseL( TInt aCmd )
    {
    switch ( aCmd )
        {
        case EBCTestAknAppUi:
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
// CBCTestAppFrmAknAppUICase::ReleaseCaseL
// ---------------------------------------------------------------------------
//
void CBCTestAppFrmAknAppUICase::ReleaseCaseL()
    {
    // let container delete the component control.
    iContainer->ResetControl();
    iControl = NULL;
    }

// ---------------------------------------------------------------------------
// CBCTestAppFrmAknAppUICase::TestLayoutDecorator
// ---------------------------------------------------------------------------
//
void CBCTestAppFrmAknAppUICase::TestFunction()
    {
    // Test some API here

    TestPublicFunction();
    TestProtectedAknAppUi();
    }

void CBCTestAppFrmAknAppUICase::TestProtectedAknAppUi()
    {
    CBCTestAppFrmAppUi *iTestAppUi = static_cast<CBCTestAppFrmAppUi*>
                                     ( CEikonEnv::Static()->EikAppUi() );
    iTestAppUi->AppFrm_SetKeyBlockMode();
    _LIT( KSetKeyBlockMode, "CAknAppUi::SetKeyBlockMode() invoked" );
    AssertTrueL( ETrue, KSetKeyBlockMode );

    iTestAppUi->AppFrm_HandleStatusPaneSizeChange();
    _LIT(KHandleStatusPaneSizeChange ,
        "CAknAppUiBase::HandleStatusPaneSizeChange() invoked" );
    AssertTrueL( ETrue, KHandleStatusPaneSizeChange );

    TWsEvent iEvent ;
    iTestAppUi->AppFrm_HandleApplicationSpecificEventL(
                                           KEikPartialForeground, iEvent );
    _LIT( KHandleApplicationSpecificEventL,
    "CAknAppUiBase::HandleApplicationSpecificEventL() invoked" );
    AssertTrueL( ETrue, KHandleApplicationSpecificEventL);

    iTestAppUi->AppFrm_HandleScreenDeviceChangedL();
    _LIT( KHandleScreenDeviceChangedL ,
    "CAknAppUiBase::HandleScreenDeviceChangedL() invoked" );
    AssertTrueL( ETrue, KHandleScreenDeviceChangedL );

    TInt uid = KErrNotFound;
    iTestAppUi->AppFrm_ReplaceKeySoundsL( uid );
    _LIT( KReplaceKeySoundsL ,
     "CAknAppUiBase::ReplaceKeySoundsL(TInt aUid) invoked" );
    AssertTrueL( ETrue, KReplaceKeySoundsL );

    }

void CBCTestAppFrmAknAppUICase::TestPublicFunction()
    {
    /*********************************************************/
    /*CAknAppUi*/
    /*********************************************************/

    CAknAppUi* iAknAppUI = static_cast<CAknAppUi*>
                           ( CEikonEnv::Static()->EikAppUi() );
    iAknAppUI->Cba();
    _LIT( KCAknAppUiCba, "CAknAppUi::Cba() invoked" );
    AssertTrueL( ETrue, KCAknAppUiCba );

    iAknAppUI->CurrentPopupToolbar();
    _LIT( KCurrentPopupToolbar, "CAknAppUi::CurrentPopupToolbar() invoked" );
    AssertTrueL( ETrue, KCurrentPopupToolbar );

    TInt iErrCode = KErrNone;
    SExtendedError iExtErr;
    TBuf<16> iErrorText;
    TBuf<16> iContextText;
    iAknAppUI->HandleError( iErrCode, iExtErr, iErrorText, iContextText );
    _LIT( KCAknAppUiHandleError , "CAknAppUi::HandleError() invoked" );
    AssertTrueL( ETrue, KCAknAppUiHandleError);

    iAknAppUI->TouchPane();
    _LIT( KTouchPane ,"CAknAppUi::TouchPane() invoked" );
    AssertTrueL( ETrue, KTouchPane );

    iAknAppUI->PopupToolbar();
    _LIT( KPopupToolbar , "CAknAppUi::PopupToolbar() invoked" );
    AssertTrueL( ETrue, KPopupToolbar );

    iAknAppUI->HandleTouchPaneSizeChange();
    _LIT( KHandleTouchPaneSizeChange ,
    "CAknAppUi::HandleTouchPaneSizeChange() invoked" );
    AssertTrueL( ETrue, KHandleTouchPaneSizeChange );

    TBool iHide = ETrue;
    iAknAppUI->HideApplicationFromFSW( iHide );
    _LIT( KHideApplicationFromFSW ,
    "CAknAppUi::HideApplicationFromFSW() invoked" );
    AssertTrueL( ETrue, KHideApplicationFromFSW );

    iAknAppUI->IsAppShutterRunning();
    _LIT( KIsAppShutterRunning ,
    "CAknAppUi::IsAppShutterRunning() invoked" );
    AssertTrueL( ETrue, KIsAppShutterRunning);

    iAknAppUI->ProcessCommandL( 100 );
    _LIT( KProcessCommandL,"CAknAppUi::ProcessCommandL() invoked" );
    AssertTrueL( ETrue, KProcessCommandL);

    /*********************************************************/
    /*CAknAppUiBase*/
    /*********************************************************/

    CAknAppUiBase* iAknAppUIBase = static_cast<CAknAppUiBase*>
                                 ( CEikonEnv::Static()->EikAppUi() );

    iAknAppUIBase->IsFullScreenApp();
    _LIT( KIsFullScreenApp , "CAknAppUIBase::IsFullScreenApp() invoked" );
    AssertTrueL( ETrue, KIsFullScreenApp );

    iAknAppUIBase->IsPartialForeground();
    _LIT( KIsPartialForeground,
    "CAknAppUIBase::IsPartialForeground() invoked" );
    AssertTrueL( ETrue, KIsPartialForeground );

    iAknAppUIBase->LocalUiZoom();
    _LIT( KLocalUiZoom ,"CAknAppUIBase::LocalUiZoom() invoked" );
    AssertTrueL( ETrue, KLocalUiZoom );

    iAknAppUIBase->Orientation();
    _LIT( KOrientation , "CAknAppUIBase::Orientation() invoked" );
    AssertTrueL( ETrue, KOrientation );

    iAknAppUIBase->SetLayoutAwareApp( ETrue );
    _LIT( KSetLayoutAwareApp , "CAknAppUIBase::SetLayoutAwareApp() invoked" );
    AssertTrueL( ETrue, KSetLayoutAwareApp );

    iAknAppUIBase->SetLocalUiZoomL( EAknUiZoomNormal );
    _LIT( KSetLocalUiZoomL , "CAknAppUIBase::SetLocalUiZoomL() invoked" );
    AssertTrueL( ETrue, KSetLocalUiZoomL );

    iAknAppUIBase->HandleForegroundEventL( ETrue );
    _LIT( KHandleForegroundEventL,
    "CAknAppUIBase::HandleForegroundEventL() invoked" );
    AssertTrueL( ETrue, KHandleForegroundEventL );

    iAknAppUIBase->SetOrientationL( iAknAppUIBase->Orientation() );
    _LIT( KSetOrientationL, "CAknAppUIBase::SetOrientationL() invoked" );
    AssertTrueL( ETrue, KSetOrientationL);

    }


























