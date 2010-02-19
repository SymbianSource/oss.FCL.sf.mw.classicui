/*
* Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Contains the test cases.
*
*/

#include <avkon.hrh>
#include <eikfrlb.h>
#include <aknappui.h>
#include <aknpointereventmodifier.h>
#include <akntashook.h>
#include <aknpreviewpopupcontroller.h>
#include <eikmenub.h>
#include <eikenv.h>
#include <aknutils.h>
#include <akntoolbar.h>

#include <bctestmixmcl.rsg>
#include <eikedwin.h>
#include <aknphysics.h>

#include "bctestmixmclgeneralcase.h"
#include "bctestmixmclcontainer.h"
#include "bctestmixmcl.hrh"

// CONSTATNS


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestMixMCLGeneralCase* CBCTestMixMCLGeneralCase::NewL( CBCTestMixMCLContainer* 
    aContainer, CBCTestMixMCLView* aView )
    {
    CBCTestMixMCLGeneralCase* self = new( ELeave ) CBCTestMixMCLGeneralCase( 
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
CBCTestMixMCLGeneralCase::CBCTestMixMCLGeneralCase( CBCTestMixMCLContainer* 
    aContainer, CBCTestMixMCLView* aView )
    : iView( aView ), iContainer( aContainer )
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestMixMCLGeneralCase::~CBCTestMixMCLGeneralCase()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestMixMCLGeneralCase::ConstructL()
    {    
    BuildScriptL();    
    }
    
// ---------------------------------------------------------------------------
// CBCTestMixMCLGeneralCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestMixMCLGeneralCase::BuildScriptL()
    { 
    // Add script as your need.   
    AddTestL( DELAY(1), LeftCBA, Down, KeyOK, TEND ); // outline02
    }
    
// ---------------------------------------------------------------------------
// CBCTestMixMCLGeneralCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestMixMCLGeneralCase::RunL( TInt aCmd )
    {
    if ( aCmd != EBCTestCmdOutline2 )
        {
        return;
        }
    // Call release before prepare to let container has time to draw the 
    // control created in PrepareCaseL.
    ReleaseCaseL();
    PrepareCaseL( aCmd ); 
    
    TestListBoxL();
    TestOptionsMenuL();
    TestTasObjectInfoAndTasHookL();
    TestMiscApisFuncOneL();
    TestAknToolbar();
    TestAknPopupUtils();
    TestAknListUtilsL(); 
    TestEditorKineticScrollingL();
    TestAknPhysicsSuspendPhysicsL();
    TestAknPhysicsResumePhysicsL();
    TestCba();
    }

// ---------------------------------------------------------------------------
// CBCTestMixMCLGeneralCase::PrepareCaseL
// ---------------------------------------------------------------------------
//
void CBCTestMixMCLGeneralCase::PrepareCaseL( TInt aCmd )
    {        
    switch ( aCmd )
        {
        case EBCTestCmdOutline2:
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
// CBCTestMixMCLGeneralCase::ReleaseCaseL
// ---------------------------------------------------------------------------
//   
void CBCTestMixMCLGeneralCase::ReleaseCaseL()
    {
    // let container delete the component control.
    iContainer->ResetControl();
    iControl = NULL;
    }

// ---------------------------------------------------------------------------
// CBCTestMixMCLGeneralCase::HandleLongTapEventL
// ---------------------------------------------------------------------------
//   
void CBCTestMixMCLGeneralCase::HandleLongTapEventL( 
		const TPoint& /*aPenEventLocation*/, 
		const TPoint& /*aPenEventScreenLocation*/ )
	{
	
	}

// ---------------------------------------------------------------------------
// CBCTestMixMCLGeneralCase::TestListBoxL
// ---------------------------------------------------------------------------
//   
void CBCTestMixMCLGeneralCase::TestListBoxL()
	{
	_LIT( KDisableScrolling, "CEikListBox::DisableScrolling() invoked" );
	_LIT( KSetItemsInSingleLine, 
	    "CEikListBox::SetItemsInSingleLine() invoked" );
	_LIT( KBackgroundDrawingSuppressed, 
	    "CEikListBox::BackgroundDrawingSuppressed() invoked" );
	_LIT( KHandlePhysicsScrollEventL, 
	    "CEikListBox::HandlePhysicsScrollEventL() invoked" );
	_LIT( KSuspendEffectsL, "CEikListBox::SuspendEffects() invoked" );
	_LIT( KScrollingDisabledL, "CEikListBox::ScrollingDisabled() invoked" );
	_LIT( KItemIsPartiallyVisibleL, 
	    "CListBoxView::ItemIsPartiallyVisible() invoked" );	
	_LIT( KItemOffsetInPixels, 
	    "CListBoxView::ItemOffsetInPixels() invoked" );
	_LIT( KDisableItemSpecificMenu, 
	    "CListBoxView::DisableItemSpecificMenu() invoked" );
	_LIT( KMakeVisible,
	    "CEikListBox::MakeVisible() invoked" );
    _LIT( KItemsInSingleLine, 
        "CEikListBox::ItemsInSingleLine() invoked" );

	CEikFormattedCellListBox * listbox = new CEikFormattedCellListBox();
	CleanupStack::PushL( listbox );
	
	listbox->ConstructL( iContainer, EAknListBoxSelectionList );
	CDesCArrayFlat* text = new (ELeave) CDesCArrayFlat(1);
	CleanupStack::PushL( text );
	
	text->AppendL( _L( "\tTextItem1\t" ) );
	text->AppendL( _L( "\tTextItem2\t" ) );
	text->AppendL( _L( "\tTextItem3\t" ) );
	
	listbox->Model()->SetItemTextArray( text );
	listbox->Model()->SetOwnershipType( ELbmDoesNotOwnItemArray );
	
	listbox->DisableScrolling( ETrue );
	AssertTrueL( ETrue, KDisableScrolling );
	
	listbox->SetItemsInSingleLine( 1 );
	AssertTrueL( ETrue, KSetItemsInSingleLine );
	
	listbox->BackgroundDrawingSuppressed();
	AssertTrueL( ETrue, KBackgroundDrawingSuppressed );
	
	listbox->HandlePhysicsScrollEventL( listbox->ItemHeight() );
	AssertTrueL( ETrue, KHandlePhysicsScrollEventL );
	
	listbox->SuspendEffects( ETrue );
    AssertTrueL( ETrue, KSuspendEffectsL );	
    
	listbox->ScrollingDisabled();
    AssertTrueL( ETrue, KScrollingDisabledL );
    
	listbox->View()->ItemIsPartiallyVisible( 1 );
    AssertTrueL( ETrue, KItemIsPartiallyVisibleL );
	
	listbox->View()->ItemOffsetInPixels();
	AssertTrueL( ETrue, KItemOffsetInPixels );
	
	listbox->DisableItemSpecificMenu();
	AssertTrueL( ETrue, KDisableItemSpecificMenu );
    listbox->MakeVisible( ETrue );
    AssertTrueL( ETrue, KMakeVisible );

	listbox->ItemsInSingleLine();
	AssertTrueL( ETrue, KItemsInSingleLine );
	
	CleanupStack::PopAndDestroy( text );
	CleanupStack::PopAndDestroy( listbox );
	}
	
// ---------------------------------------------------------------------------
// CBCTestMixMCLGeneralCase::TestOptionsMenuL
// ---------------------------------------------------------------------------
//   
void CBCTestMixMCLGeneralCase::TestOptionsMenuL()
    {
    _LIT( KGetMenuType, "CEikMenuBar::GetMenuType invoked" );
    CEikMenuBar* menuBar = CEikonEnv::Static()->AppUiFactory()->MenuBar();            
    if( menuBar )
        {        
        menuBar->GetMenuType();
        AssertTrueL( ETrue, KGetMenuType );  
        }
    }	

// ---------------------------------------------------------------------------
// CBCTestMixMCLGeneralCase::TestTasObjectInfoAndTasHookL
// ---------------------------------------------------------------------------
//   
void CBCTestMixMCLGeneralCase::TestTasObjectInfoAndTasHookL()
	{
	_LIT( KClassName, "CBCTestMixMCLGeneralCase" );
	_LIT( KAddL, "CAknTasHook::AddL() tested" );
	_LIT( KGet, "CAknTasHook::Get() tested" );
	_LIT( KRemove, "CAknTasHook::Remove() tested" );
	_LIT( KIsA, "CAknTasObjectInfo::IsA() tested" );
	_LIT( KType, "CAknTasObjectInfo::Type() tested" );
	_LIT( KGetClassNames, "CAknTasObjectInfo::GetClassNames() tested" );
	_LIT( KGetControl, "CAknTasObjectInfo::GetControl() tested" );
	
	CAknTasHook::AddL( this, KClassName() );
	AssertTrueL( ETrue, KAddL );
	
	CAknTasObjectInfo* info = CAknTasHook::Get( this );
	AssertTrueL( ETrue, KGet );
	
	// info would be NULL if KTasHooking is not enabled.
	if ( info )
		{
	    info->IsA( KClassName() );
	    AssertTrueL( ETrue, KIsA );
	    
	    info->Type();
	    AssertTrueL( ETrue, KType );
	    
	    info->GetClassNames();
	    AssertTrueL( ETrue, KGetClassNames );
	    
	    info->GetControl();
	    AssertTrueL( ETrue, KGetControl );
		}
	
	CAknTasHook::Remove( this );
	AssertTrueL( ETrue, KRemove );
	}

// ---------------------------------------------------------------------------
// CBCTestMixMCLGeneralCase::TestMiscApisFuncOneL
// ---------------------------------------------------------------------------
//   
void CBCTestMixMCLGeneralCase::TestMiscApisFuncOneL()
	{
	_LIT( KCancelAnimationL, 
	    "CAknLongTapDetector::CancelAnimationL() invoked" );
	_LIT( KHandlePointerEvent, 
	    "CAknPointerEventModifier::CAknPointerEventModifier() tested");
	_LIT( KResetTimer, "CAknPreviewPopUpController::ResetTimer() teseted");
	
	CAknLongTapDetector* detector = CAknLongTapDetector::NewL( this );
	CleanupStack::PushL( detector );
	
	detector->After( TTimeIntervalMicroSeconds32( 1000000 ) );
	detector->CancelAnimationL();
	AssertTrueL( ETrue, KCancelAnimationL );
	
	CleanupStack::PopAndDestroy( detector );
	
	CAknPreviewPopUpController* popupController = 
	        CAknPreviewPopUpController::NewL( *iControl );
	CleanupStack::PushL( popupController );
	
	popupController->ResetTimer();
	AssertTrueL( ETrue, KResetTimer );
	
	CleanupStack::PopAndDestroy( popupController );
	
	// simulate a pointer event for forcing the CAknAppUi::HandleWsEventL
	// to call CAknPointerEventModifier::HandlePointerEventL().
	TRawEvent eventDown;
	eventDown.Set( TRawEvent::EButton1Down, 0, 0 );
	UserSvr::AddEvent( eventDown );
	
	User::After( 1000000 );

	TRawEvent eventUp;
	eventUp.Set( TRawEvent::EButton1Up, 0, 0 );
	UserSvr::AddEvent( eventUp );

	AssertTrueL( ETrue, KHandlePointerEvent );
	}

// ---------------------------------------------------------------------------
// CBCTestMixMCLGeneralCase::TestAknPopupUtils
// ---------------------------------------------------------------------------
//   
void CBCTestMixMCLGeneralCase::TestAknPopupUtils()
    {
    TSize size( 10, 10 );
    TPoint point( AknPopupUtils::Position( size, ETrue ) );
    point = AknPopupUtils::Position( size, EFalse );
    point = AknPopupUtils::Position( size, NULL );
    _LIT( KAknPopupUtilsPosition, "AknPopupUtils::Position funcs are tested" );
    AssertTrueL( ETrue, KAknPopupUtilsPosition );
    }

	
// ---------------------------------------------------------------------------
// CBCTestMixMCLGeneralCase::TestAknListUtils
// ---------------------------------------------------------------------------
//   
void CBCTestMixMCLGeneralCase::TestAknListUtilsL()
    {
    CFbsBitmap *bitmap = new ( ELeave ) CFbsBitmap();
    CleanupStack::PushL( bitmap );
    bitmap->Create( TSize( 20, 20 ), EColor16MA );
    CFbsBitmapDevice *bitmapDevice = CFbsBitmapDevice::NewL( bitmap );
    CleanupStack::PushL( bitmapDevice );
    CFbsBitGc *gc = CFbsBitGc::NewL();
    CleanupStack::PushL( gc );
    gc->Activate( bitmapDevice );
    
    TRect rect( 10,100,20,120 );
    TRgb color( KRgbRed );
    AknListUtils::DrawSeparator( *gc, rect, color );
    
    CleanupStack::PopAndDestroy( gc );
    CleanupStack::PopAndDestroy( bitmapDevice );
    CleanupStack::PopAndDestroy( bitmap );
    
    _LIT( KAknListUtilsDrawSeparator, "AknListUtils::DrawSeparator tested" );
    AssertTrueL( ETrue, KAknListUtilsDrawSeparator );
    }

	
// ---------------------------------------------------------------------------
// CBCTestMixMCLGeneralCase::TestAknToolbar
// ---------------------------------------------------------------------------
// 
void CBCTestMixMCLGeneralCase::TestAknToolbar()
	{
	_LIT( KAknToolbarNew, "CAknToolbar::New toolbar is constructed" );
	_LIT( KAknToolbarSetBgId, "CAknToolbar::New background skin theme ID is set" );
	
	CAknToolbar* toolbar = CAknToolbar::NewL( R_BCTESTMIXMCL_TOOLBAR_FIXED );
	CleanupStack::PushL( toolbar );
	AssertTrueL( ETrue, KAknToolbarNew );
	
	toolbar->SetSkinBackgroundId( KAknsIIDQsnBgAreaControlMp );
	AssertTrueL( ETrue, KAknToolbarSetBgId );
	CleanupStack::PopAndDestroy( toolbar );
	}


// ---------------------------------------------------------------------------
// CBCTestMixMCLGeneralCase::TestEditorKineticScrollingL
// ---------------------------------------------------------------------------
//   
void CBCTestMixMCLGeneralCase::TestEditorKineticScrollingL()
    {
    CEikEdwin* editor = new ( ELeave ) CEikEdwin;
    CleanupStack::PushL( editor );
    editor->EnableKineticScrollingL( ETrue );
    CleanupStack::PopAndDestroy( editor );
    _LIT( KEdwinEnableScrolling, "CEikEdwin::EnableKineticScrollingL tested" );
    AssertTrueL( ETrue, KEdwinEnableScrolling );
    }

// ---------------------------------------------------------------------------
// CBCTestMixMCLGeneralCase::TestAknPhysicsSuspendPhysicsL
// ---------------------------------------------------------------------------
//   
void CBCTestMixMCLGeneralCase::TestAknPhysicsSuspendPhysicsL()
    {
    CCoeControl* testControl = new (ELeave) CCoeControl();
    CleanupStack::PushL( testControl );
    CAknPhysics* physics = CAknPhysics::NewL( *this, testControl );
    CleanupStack::PushL( physics );
    physics->SuspendPhysics();
    CleanupStack::PopAndDestroy( physics );
    CleanupStack::PopAndDestroy( testControl );
    _LIT( KSuspendPhysics, "CAknPhysics::SuspendPhysics tested" );
    AssertTrueL( ETrue, KSuspendPhysics );
    }
	
// ---------------------------------------------------------------------------
// CBCTestMixMCLGeneralCase::TestAknPhysicsResumePhysicsL
// ---------------------------------------------------------------------------
//   
void CBCTestMixMCLGeneralCase::TestAknPhysicsResumePhysicsL()
    {
    CCoeControl* testControl = new (ELeave) CCoeControl();
    CleanupStack::PushL( testControl );
    CAknPhysics* physics = CAknPhysics::NewL( *this, testControl );
    CleanupStack::PushL( physics );
    physics->ResumePhysics();
    CleanupStack::PopAndDestroy( physics );
    CleanupStack::PopAndDestroy( testControl );
    _LIT( KResumePhysics, "CAknPhysics::ResumePhysics tested" );
    AssertTrueL( ETrue, KResumePhysics );
    }

// ---------------------------------------------------------------------------
// CBCTestMixMCLGeneralCase::TestCba
// ---------------------------------------------------------------------------
//   
void CBCTestMixMCLGeneralCase::TestCba()
    {
    CEikCba* cba = static_cast<CEikCba*>( 
        iAvkonAppUi->Cba()->ButtonGroup()->AsControl() );
    cba->EnableItemSpecificSoftkey( EFalse );
    cba->EnableItemSpecificSoftkey( ETrue );
    _LIT( CEikCbaEnableItemSpecificSoftkey, 
        "CEikCba::EnableItemSpecificSoftkey tested" );
    AssertTrueL( ETrue, CEikCbaEnableItemSpecificSoftkey );
    }    

// ---------------------------------------------------------------------------
// CBCTestMixMCLGeneralCase::ViewPositionChanged
// ---------------------------------------------------------------------------
// 
void CBCTestMixMCLGeneralCase::ViewPositionChanged(
    const TPoint& /*aNewPosition*/,
    TBool /*aDrawNow*/,
    TUint /*aFlags*/ )
    {
    }

// ---------------------------------------------------------------------------
// CBCTestMixMCLGeneralCase::PhysicEmulationEnded
// ---------------------------------------------------------------------------
// 
void CBCTestMixMCLGeneralCase::PhysicEmulationEnded()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestMixMCLGeneralCase::ViewPosition
// ---------------------------------------------------------------------------
// 
TPoint CBCTestMixMCLGeneralCase::ViewPosition() const
    {
    return TPoint( 0, 0 );
    }

//end of file

