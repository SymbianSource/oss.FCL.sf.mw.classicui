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
#include <caknmemoryselectionsettingitemmultidrive.h>
#include <AknCommonDialogsDynMem.h>

#include <bctestmixmcl.rsg>
#include <eikedwin.h>
#include <aknphysics.h>
#include <aknradiobuttonsettingpage.h>
#include <aknpopupsettingpage.h>  
#include <ItemFinder.h>
#include <finditemdialog.h>
#include <aknphysics.h>
#include <aknbutton.h>

#include "bctestmixmclgeneralcase.h"
#include "bctestmixmclcontainer.h"
#include "bctestmixmcl.hrh"

// CONSTANTS

//
// class CSettingPageTest
// Helper class for testing protected setting page methods.
//
NONSHARABLE_CLASS( CSettingPageTest ) : public CAknSettingPage
    {   
public:
    virtual void ProcessCommandL( TInt aCommandId );  
    };

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
    TestAknToolbarL();
    TestAknPopupUtilsL();
    TestAknListUtilsL(); 
    TestRadioButtonSettingPageL();
    TestPopupSettingPageL();   
    TestItemFinderL();
    TestFindItemDialogL();
    TestEditorKineticScrollingL();
    TestEnableKineticScrollingPhysicsL();
    TestAknPhysicsSuspendPhysicsL();
    TestAknPhysicsResumePhysicsL();
    TestCbaL();
	TestCommonDialogsL();
	TestAknButtonEnableFeedbackL();
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

	CEikFormattedCellListBox * listbox = new (ELeave) CEikFormattedCellListBox();
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
// CBCTestMixMCLGeneralCase::TestAknPopupUtilsL
// ---------------------------------------------------------------------------
//   
void CBCTestMixMCLGeneralCase::TestAknPopupUtilsL()
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
// CBCTestMixMCLGeneralCase::TestAknToolbarL
// ---------------------------------------------------------------------------
// 
void CBCTestMixMCLGeneralCase::TestAknToolbarL()
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


// -----------------------------------------------------------------------------
// CBCTestMixMCLGeneralCase::TestRadioButtonSettingPageL
// -----------------------------------------------------------------------------
//
void CBCTestMixMCLGeneralCase::TestRadioButtonSettingPageL()
    { 
    const TInt KBufSize = 32;
    const TInt KZero = 0;
    const TInt KOne = 1;
    const TInt KTwo = 2;
    _LIT( KTestString, "Radiobuttonsettingpage test" );
    _LIT( KTestRadioButtonSettingPage, 
        "CAknRadioButtonSettingPage::ProcessCommandL tested" );
    
    CDesCArrayFlat* array = CCoeEnv::Static()->
        ReadDesCArrayResourceL( R_BCTESTMIXMCL_LIST_ITEM_ARRAY );   
    CleanupStack::PushL( array );

    TInt optin( KZero );
    TBuf< KBufSize > buffer( KTestString );
    CAknRadioButtonSettingPage* settingPage = new (ELeave) 
        CAknRadioButtonSettingPage( &buffer, KOne, EAknCtPopupSettingList,
                                    R_BCTESTMIXMCL_RADIOBUTTON_EDITOR, 
                                    R_BCTESTMIXMCL_RADIOBUTTON_SETTING_PAGE, 
                                    optin, array );
    CleanupStack::PushL( settingPage ); 
    
    settingPage->ConstructL();

    // CSettingPageTest is used to access protected method
    // CAknRadioButtonSettingPage::ProcessCommandL
    CSettingPageTest* test = reinterpret_cast<CSettingPageTest*>( settingPage );
    
    CCoeEnv::Static()->AppUi()->AddToStackL( test );
    test->ProcessCommandL( EAknSoftkeySelect );
    CCoeEnv::Static()->AppUi()->RemoveFromStack( test );  
  
    CleanupStack::PopAndDestroy( KTwo );   
    AssertTrueL( ETrue, KTestRadioButtonSettingPage );
    }

// -----------------------------------------------------------------------------
// CBCTestMixMCLGeneralCase::TestPopupSettingPageL
// -----------------------------------------------------------------------------
//
void CBCTestMixMCLGeneralCase::TestPopupSettingPageL()
    {    
    _LIT( KTestPopupSettingPage, 
        "CAknPopupSettingPage::ProcessCommandL tested" );
    
    CDesCArrayFlat* item = CCoeEnv::Static()->
        ReadDesCArrayResourceL( R_BCTESTMIXMCL_LIST_ITEM_ARRAY );
    CleanupStack::PushL( item );
    
    CAknQueryValueTextArray* textArray = CAknQueryValueTextArray::NewL();
    CleanupStack::PushL( textArray );
    textArray->SetArray( *item );
    
    CAknQueryValueText* queryValueText = CAknQueryValueText::NewL();
    CleanupStack::PushL( queryValueText );
    queryValueText->SetArrayL( textArray );
    
    CAknPopupSettingPage* popupSettingPage  = new (ELeave) 
        CAknPopupSettingPage( R_BCTESTMIXMCL_POPUP_SETTING_PAGE, 
                              *queryValueText );
    
    CleanupStack::PushL( popupSettingPage );
    
    popupSettingPage->ConstructL();
    
    // CSettingPageTest is used to access protected method
    // CAknPopupSettingPage::ProcessCommandL
    CSettingPageTest* test = reinterpret_cast<CSettingPageTest*>( popupSettingPage );
    
    CCoeEnv::Static()->AppUi()->AddToStackL( popupSettingPage );
    test->ProcessCommandL( EAknSoftkeySelect );
    CCoeEnv::Static()->AppUi()->RemoveFromStack( popupSettingPage );     
    
    CleanupStack::PopAndDestroy( popupSettingPage );
    CleanupStack::PopAndDestroy( queryValueText );
    CleanupStack::PopAndDestroy( textArray );
    CleanupStack::PopAndDestroy( item );
    
    AssertTrueL( ETrue, KTestPopupSettingPage );
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
// CBCTestMixMCLGeneralCase::TestEnableKineticScrollingPhysicsL
// ---------------------------------------------------------------------------
//
void CBCTestMixMCLGeneralCase::TestEnableKineticScrollingPhysicsL()
    {
    CEikEdwin* editor = new ( ELeave ) CEikEdwin;
    CleanupStack::PushL( editor );

    CAknPhysics* physics ( NULL );
    AssertTrueL ( CAknPhysics::FeatureEnabled() );
    CCoeControl* control ( NULL );
    control = new (ELeave) CCoeControl;
    CleanupStack::PushL( control );

    physics = CAknPhysics::NewL( *this, control );
    CleanupStack::PushL( physics );

    editor->EnableKineticScrollingL( physics );

    CleanupStack::PopAndDestroy( physics );
    CleanupStack::PopAndDestroy( control );
    CleanupStack::PopAndDestroy( editor );

    _LIT( KEdwinEnableScrollingPhysics,
            "CEikEdwin::TestEnableKineticScrollingPhysicsL tested" );
    AssertTrueL( ETrue, KEdwinEnableScrollingPhysics );
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
// CBCTestMixMCLGeneralCase::TestCbaL
// ---------------------------------------------------------------------------
//   
void CBCTestMixMCLGeneralCase::TestCbaL()
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
// CBCTestMixMCLGeneralCase::TestCommonDialogsL()
//  common file test  
// ---------------------------------------------------------------------------
//
void CBCTestMixMCLGeneralCase::TestCommonDialogsL()
    {
    _LIT( KSetIncludedMediasL, 
          "CAknMemorySelectionSettingItemMultiDrive::SetIncludedMediasL()invoked");
    
    TInt id = 1;
    TDriveNumber selDr = EDriveC;
    
    CAknMemorySelectionSettingItemMultiDrive* settingItem = 
            new ( ELeave ) CAknMemorySelectionSettingItemMultiDrive( 
            id, selDr );
    CleanupStack::PushL( settingItem );
    
    TInt includedMedias = AknCommonDialogsDynMem:: EMemoryTypePhone |
                          AknCommonDialogsDynMem:: EMemoryTypeMMC |
                          AknCommonDialogsDynMem:: EMemoryTypeRemote;

    settingItem->SetIncludedMediasL( includedMedias );
    AssertTrueL( ETrue, KSetIncludedMediasL );
    
    includedMedias &= (~AknCommonDialogsDynMem:: EMemoryTypePhone ); 
    settingItem->SetIncludedMediasL( includedMedias );

    CleanupStack::PopAndDestroy( settingItem );
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

// -----------------------------------------------------------------------------
// CBCTestMixMCLGeneralCase::TestItemFinderL
// -----------------------------------------------------------------------------
//
void CBCTestMixMCLGeneralCase::TestItemFinderL()
    {
    _LIT( KSetItemFinderObserverL,
            "CItemFinder::SetItemFinderObserverL() tested" );

    CItemFinder* itemfinder = CItemFinder::NewL();
    CleanupStack::PushL ( itemfinder );

    itemfinder->SetItemFinderObserverL( this );
    itemfinder->SetItemFinderObserverL( 0 );
    AssertTrueL( ETrue, KSetItemFinderObserverL );

    CleanupStack::PopAndDestroy( itemfinder );
    }


// -----------------------------------------------------------------------------
// CBCTestMixMCLGeneralCase::TestFindItemDialogL
// -----------------------------------------------------------------------------
//
void CBCTestMixMCLGeneralCase::TestFindItemDialogL()
    {
    _LIT( KEnableSingleClick,
            "CFindItemDialog::EnableSingleClick() tested" );
    _LIT( KUrlDes, "http://www.symbian.com" );

    CFindItemDialog* dialog = CFindItemDialog::NewL( KUrlDes,
            CFindItemEngine::EFindItemSearchURLBin );
    CleanupStack::PushL( dialog );

    dialog->EnableSingleClick ( EFalse );
    dialog->EnableSingleClick ( ETrue );
    AssertTrueL( ETrue, KEnableSingleClick );

    CleanupStack::PopAndDestroy( dialog );
    }


// ---------------------------------------------------------------------------
// CBCTestMixMCLGeneralCase::HandleFindItemEventL
// ---------------------------------------------------------------------------
//
void CBCTestMixMCLGeneralCase::HandleFindItemEventL(
        const CItemFinder::CFindItemExt& /*aItem*/,
            MAknItemFinderObserver::TEventFlag /*aEvent*/, TUint /*aFlags*/)
    {
    // do nothing
    }


// ---------------------------------------------------------------------------
// CBCTestMixMCLGeneralCase::TestAknButtonEnableFeedbackL
// ---------------------------------------------------------------------------
//
void CBCTestMixMCLGeneralCase::TestAknButtonEnableFeedbackL()
    {
    CAknButton* button = CAknButton::NewLC();

    button->EnableFeedback( EFalse );
    button->EnableFeedback( ETrue );

    CleanupStack::PopAndDestroy ( button );

    _LIT( KEnableFeedback, "CAknButton::EnableFeedback tested" );
    AssertTrueL( ETrue, KEnableFeedback );
    }

//end of file

