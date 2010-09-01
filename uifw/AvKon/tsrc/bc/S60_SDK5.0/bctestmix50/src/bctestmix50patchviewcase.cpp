/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test case
*
*/


#include <w32std.h>
#include <coecntrl.h>
#include <barsread.h>
#include <aknviewappui.h>
#include <eikenv.h>
#include <vwsdef.h>
#include <aknview.h>
#include <akntoolbar.h>
#include <eikappui.h> //test
#include <eikcolib.h> // test

#include <bctestmix50.rsg>
#include "bctestmix50app.h"
#include "bctestmix50patchviewcase.h"
#include "bctestmix50container.h"
#include "bctestmix50patchmisc.h"
#include "bctestmix50view.h"
#include "bctestmix50.hrh"

// CONSTATNS


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestMix50PatchViewCase* CBCTestMix50PatchViewCase::NewL( CBCTestMix50Container* 
    aContainer, CBCTestMix50View* aView )
    {
    CBCTestMix50PatchViewCase* self = new( ELeave ) CBCTestMix50PatchViewCase( 
        aContainer, aView );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestMix50PatchViewCase::CBCTestMix50PatchViewCase( CBCTestMix50Container* 
    aContainer, CBCTestMix50View* aView )
    : iView( aView ), iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestMix50PatchViewCase::~CBCTestMix50PatchViewCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchViewCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestMix50PatchViewCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchViewCase::BuildScriptL()
    { 
    // Add script as your need.   
    AddTestL( DELAY(1), LeftCBA, Down, Down, Down, KeyOK, TEND );
    }
    
// ---------------------------------------------------------------------------
// CBCTestMix50PatchViewCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchViewCase::RunL( TInt aCmd )
    {
    if ( aCmd != EBCTestCmdOutline4 )
        {
        return;
        }
    // Call release before prepare to let container has time to draw the 
    // control created in PrepareCaseL.
    ReleaseCaseL();
    PrepareCaseL( aCmd ); 
    
    TestAknViewL();
    TestAknAppUiL();
    TestAknAppUiBaseL();
    TestAknAppServiceBaseL();
    }

// ---------------------------------------------------------------------------
// CBCTestMix50PatchViewCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestMix50PatchViewCase::PrepareCaseL( TInt aCmd )
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
    iContainer->SetControlL( iControl );
    }

// ---------------------------------------------------------------------------
// CBCTestMix50PatchViewCase::ReleaseCaseL
// ---------------------------------------------------------------------------
//   
void CBCTestMix50PatchViewCase::ReleaseCaseL()
    {
    // let container delete the component control.
    iContainer->ResetControl();
    iControl = NULL;
    }


// -----------------------------------------------------------------------------
// CTestAknVolumeControl::TestAknViewL() 
// CAknView test
// -----------------------------------------------------------------------------
//
void CBCTestMix50PatchViewCase::TestAknViewL()
	{
    CAknViewAppUi* viewAppUi = static_cast<CAknViewAppUi*>
                               ( CEikonEnv::Static()->EikAppUi() );
    viewAppUi->EnableLocalScreenClearer( EFalse);
    _LIT( KEnableLocalScreenClearer, 
    	"CAknViewAppUi::EnableLocalScreenClearer() invoked" );
    AssertTrueL( ETrue, KEnableLocalScreenClearer );
	
	iView->ToolbarShownOnViewActivation();
    _LIT( KViewForToolbarShownOnViewActivation, "CAknView::ToolbarShownOnViewActivation" );
    AssertTrueL( ETrue, KViewForToolbarShownOnViewActivation );
    
    iView->ShowToolbarOnViewActivation( EFalse );
    iView->ShowToolbarOnViewActivation( ETrue );
    _LIT( KViewForShowToolbarOnViewActivation, "CAknView::ShowToolbarOnViewActivation" );
    AssertTrueL( ETrue, KViewForShowToolbarOnViewActivation );
    

    CAknToolbar *toolBar = iView->Toolbar();
    iView->SetToolbar( toolBar );
    _LIT( KViewForSetToolbar, "CAknView::SetToolbar" );
    AssertTrueL( ETrue, KViewForSetToolbar );
    
    iView->CreateAndSetToolbarL( R_BCTESTMIX50PATCH_TOOLBAR );
    _LIT( KViewForSCreateAndSetToolbarL, "CAknView::CreateAndSetToolbarL" );
    AssertTrueL( ETrue, KViewForSCreateAndSetToolbarL );
    iView->Toolbar()->SetToolbarVisibility( EFalse );
	}

    

// -----------------------------------------------------------------------------
// CTestAknVolumeControl::TestAknAppUiL() 
// CAknView test
// -----------------------------------------------------------------------------
//
void CBCTestMix50PatchViewCase::TestAknAppUiL()
	{
    CAknAppUiEx* uiex = static_cast<CAknAppUiEx*>( 
            CEikonEnv::Static()->EikAppUi() );
    uiex->Reserved_MtsmObject();
    _LIT( KMtsmObject, "CAknAppUi::Reserved_MtsmObject" );
    AssertTrueL( ETrue, KMtsmObject );
    
    uiex->Reserved_MtsmPosition();
    _LIT( KMtsmPosition, "CAknAppUi::Reserved_MtsmPosition" );
    AssertTrueL( ETrue, KMtsmPosition );
    
    CAknAppUi* AknAppUI = static_cast<CAknAppUi*>
                           ( CEikonEnv::Static()->EikAppUi() );
    AknAppUI->SetAliasKeyCodeResolverL( this );
    _LIT( KSetAliasKeyCodeResolver, "CAknAppUi::SetAliasKeyCodeResolverL" );
    AssertTrueL( ETrue, KSetAliasKeyCodeResolver );
    
    AknAppUI->KeySounds();
    _LIT( KKeySounds, "CAknAppUi::KeySounds() tested");
    AssertTrueL( ETrue, KKeySounds );
    TInt32  KeyHandle1;
    TInt32  KeyHandle2;
    KeyHandle1 = AknAppUI->CaptureKey( EKeyDevice8,0,0 );
    _LIT( KCaptureKey, "CAknAppUi::CaptureKey" );
    AssertTrueL( ETrue, KCaptureKey );
    
    AknAppUI->CaptureKeyL( EKeyDevice9 ,0,0,KeyHandle2 );
    _LIT( KCaptureKeyL, "CAknAppUi::CaptureKeyL" );
    AssertTrueL( ETrue, KCaptureKeyL );
    
    RWindowGroup& windowGroup = CCoeEnv::Static()->RootWin();
    windowGroup.CancelCaptureKey( KeyHandle1 );
    windowGroup.CancelCaptureKey( KeyHandle2 );
    
    AknAppUI->HideInBackground();
    _LIT( KHideInBackground, "CAknAppUi::HideInBackground" );
    AssertTrueL( ETrue, KHideInBackground );
    TApaTaskList taskList( CEikonEnv::Static()->WsSession() );
    TApaTask task = taskList.FindApp( KUidBCTestMix50 );
    task.BringToForeground();
	}

// -----------------------------------------------------------------------------
// CTestAknVolumeControl::TestAknAppUiBaseL() 
// CAknAppUiBase test
// -----------------------------------------------------------------------------
//
void CBCTestMix50PatchViewCase::TestAknAppUiBaseL()
	{
    CAknAppUiBase* AknAppUIBase = static_cast<CAknAppUiBase*>
                                 ( CEikonEnv::Static()->EikAppUi() );
    AknAppUIBase->OrientationCanBeChanged();
    _LIT( KOrientationCanBeChanged, "CAknAppUiBase::OrientationCanBeChanged" );
    AssertTrueL( ETrue, KOrientationCanBeChanged );
    
    AknAppUIBase->SetKeyEventFlags( CAknAppUiBase::EDisableSendKeyShort );
    _LIT( KSetKeyEventFlags, "CAknAppUiBase::SetKeyEventFlags" );
    AssertTrueL( ETrue, KSetKeyEventFlags );
	}

// -----------------------------------------------------------------------------
// CTestAknVolumeControl::TestAknAppServiceBaseL()
// CAknAppService test
// -----------------------------------------------------------------------------
//
void CBCTestMix50PatchViewCase::TestAknAppServiceBaseL()
	{
	CBCTestAppServiceBase* appserver = new ( ELeave ) CBCTestAppServiceBase();
	CleanupStack::PushL( appserver );
	
	RMessage2 rmessage;
    appserver->ServiceError( rmessage, 0 );
    _LIT( KServiceError, "CAknAppServiceBase::ServiceError" );
    AssertTrueL( ETrue, KServiceError );
	
	appserver->HandleServerAppExit( -1 );
    _LIT( KHandleServerAppExit, "MAknServerAppExitObserver::HandleServerAppExit" );
    AssertTrueL( ETrue, KHandleServerAppExit );
    
    //exit the application,so place the function the last of test case
    //CAknEnv::ExitForegroundAppL();
    //_LIT( KAknEnvExitForegroundAppL, "CAknEnv::ExitForegroundAppL" );
    //AssertTrueL( ETrue, KAknEnvExitForegroundAppL );
	
	CleanupStack::PopAndDestroy( appserver );
	}
