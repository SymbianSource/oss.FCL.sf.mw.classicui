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
* Description:         test case
*
*/









#include <w32std.h>
#include <coecntrl.h>

#include <fbs.h>
#include <aknslider.h>
#include <aknsfld.h>
#include <eikdialg.h>
#include <aknedsts.h>
#include <eikfrlbd.h>
#include <aknsfld.h>
#include <eiklabel.h>
#include <barsread.h>
#include <eiklbx.h>
#include <eikclbd.h>
#include <eikcmobs.h> 
#include <eikbtgpc.h>
//#include <akncharmap.h>
//#include <aknjavalists.h>
//#include <aknsctdialog.h>
#include <akniconutils.h> 
#include <aknLocationed.h>
#include <aknuniteditor.h>
//#include <aknvolumepopup.h>
#include <aknvolumecontrol.h>
#include <aknmessagequerydialog.h>
#include <aknmessagequerycontrol.h>
#include <aknchoicelist.h>
#include <AknButton.h>
#include <bctestmix50.rsg>
#include <touchfeedback.h>
#include <akntitlepaneobserver.h>


#include "bctestmix50case.h"
#include "bctestmix50container.h"
#include "bctestmix50.hrh"
#include "bctestmix50extendclasses.h"

const TInt KMinVal = 1;
const TInt KMaxVal = 100;
const TInt KDefaultVolumeLevel = 5;

const TInt KXLeftPos = 0;
const TInt KYUpPos   = 0;
const TInt KXRightPos = 100;
const TInt KYDownPos  = 100;

const TInt KBuffSmallSize = 32;
const TInt KBuffLargeSize = 256;
const TInt KSearchFieldMaxLength = 256;

const TInt KIconWidth = 20;
const TInt KIconHeight = 20;

_LIT( KTitle, "Title" );


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CBCTestMix50Case::NewL()
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestMix50Case* CBCTestMix50Case::NewL( CBCTestMix50Container* aContainer )
    {
    CBCTestMix50Case* self = new( ELeave ) CBCTestMix50Case( aContainer );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// CBCTestMix50Case::CBCTestMix50Case()
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestMix50Case::CBCTestMix50Case( CBCTestMix50Container* aContainer )
    : iContainer( aContainer )
    {
    }


// ---------------------------------------------------------------------------
// CBCTestMix50Case::~CBCTestMix50Case()
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestMix50Case::~CBCTestMix50Case()
    {
    }


// ---------------------------------------------------------------------------
// CBCTestMix50Case::ConstructL()
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestMix50Case::ConstructL()
    {
    BuildScriptL();
    iEnv = CEikonEnv::Static(); 
    }


// ---------------------------------------------------------------------------
// CBCTestMix50Case::BuildScriptL()
//
// ---------------------------------------------------------------------------
//
void CBCTestMix50Case::BuildScriptL()
    {
    // Add script
    const TInt scripts[] =
        {

        DELAY(1),
        LeftCBA, KeyOK                 // Outline 1
        
        };

    AddTestScriptL( scripts, sizeof( scripts ) / sizeof( TInt ) );
    }


// ---------------------------------------------------------------------------
// CBCTestMix50Case::RunL()
//
// ---------------------------------------------------------------------------
//
void CBCTestMix50Case::RunL( TInt aCmd )
    {

    switch ( aCmd )
        {
        case EBCTestCmdOutline1:
            {
            
            TestCFormattedCellListBoxDataCaseL();
            TestCAknSearchFieldCaseL();
            TestCAknPopupListCaseL();
            TestCAknMessageQueryControlCaseL();
            TestCAknPopupHeadingPaneCaseL();
            TestCEikButtonGroupContainerCaseL();
            TestCEikCbaCaseL();
            TestCEikEdwinCaseL();
            TestCAknSliderCaseL();
            TestCEikDialogCaseL();
            TestCEikCaptionedControlCaseL();
            TestCAknVolumeControlCaseL();
            TestCAknSettingPageCaseL();
            TestCEikListBoxCaseL();
            TestCAknEdwinStateCaseL();
            TestCEikMenuPaneCaseL();
            TestCAknGridCaseL();
            //TestCColumnListBoxItemDrawerCaseL();
            TestCAknLocationEditorCaseL();
            TestCEikMfneCaseL();
            TestCAknUnitEditorCaseL();
            TestCColumnListBoxDataCaseL();
            TestTouchFeedback() ;           
            TestCAknchoicelist();
            //TestCAknButton();
            }

            break;
        default:
            break;
        }
    }


// ---------------------------------------------------------------------------
// CBCTestMix50Case::TestCFormattedCellListBoxDataCaseL()
// ( menu item -1- )
// ---------------------------------------------------------------------------
//
void CBCTestMix50Case::TestCFormattedCellListBoxDataCaseL()
    {
    CFormattedCellListBoxData* formatCellListBoxData = 
                                            CFormattedCellListBoxData::NewL();
    CleanupStack::PushL( formatCellListBoxData );
    _LIT( KTxtNewL, "CFormattedCellListBoxData::NewL" );
    AssertNotNullL( formatCellListBoxData, KTxtNewL );

    formatCellListBoxData->CurrentItemTextWasClipped();
    _LIT( KTxtCurrentItemTextWasClipped,
         "CFormattedCellListBoxData::CurrentItemTextWasClipped" );
    AssertTrueL( ETrue, KTxtCurrentItemTextWasClipped );

    CleanupStack::PopAndDestroy( formatCellListBoxData );
    }


// ---------------------------------------------------------------------------
// CBCTestMix50Case::TestCAknSearchFieldCaseL()
// ( menu item -2- )
// ---------------------------------------------------------------------------
//
void CBCTestMix50Case::TestCAknSearchFieldCaseL()
    {
    CAknSearchField* search = CAknSearchField::NewL( *iContainer,
                                         CAknSearchField::ESearch,
                                         NULL, KSearchFieldMaxLength );
    CleanupStack::PushL( search );
    _LIT( KTxtNewL, "CAknSearchField::NewL" );
    AssertNotNullL( search, KTxtNewL );

    search->MakeVisible( ETrue );
    search->MakeVisible( EFalse );
    _LIT( KTxtMakeVisible, "CAknSearchField::MakeVisible" );
    AssertTrueL( ETrue, KTxtMakeVisible );

    CleanupStack::PopAndDestroy( search );
    }


// ---------------------------------------------------------------------------
// CBCTestMix50Case::TestCAknPopupListCaseL()
// ( menu item -3- )
// ---------------------------------------------------------------------------
//
void CBCTestMix50Case::TestCAknPopupListCaseL()
    {
    CEikListBox* listBox = new( ELeave ) CEikListBox;
    CleanupStack::PushL( listBox );

    CBCTestCAknPopupList* popupList = CBCTestCAknPopupList::NewL( listBox );
    CleanupStack::PushL( popupList );
    _LIT( KTxtNewL, "CBCTestCAknPopupList::NewL" );
    AssertNotNullL( popupList, KTxtNewL );

    popupList->FadeBehindPopup( ETrue );
    popupList->FadeBehindPopup( EFalse );
    _LIT( KTxtFadeBehindPopup, "CAknPopupList::FadeBehindPopup" );
    AssertTrueL( ETrue, KTxtFadeBehindPopup );

    CleanupStack::PopAndDestroy( popupList );
    CleanupStack::PopAndDestroy( listBox );
    }


// ---------------------------------------------------------------------------
// CBCTestMix50Case::TestCAknMessageQueryControlCaseL()
// ( menu item -4- )
// ---------------------------------------------------------------------------
//
void CBCTestMix50Case::TestCAknMessageQueryControlCaseL()
    {
    CAknMessageQueryDialog* msgQueryDlg =
    CAknMessageQueryDialog::NewL( ( TDesC& )KTitle, CAknQueryDialog::ENoTone );
    CleanupStack::PushL( msgQueryDlg );
    _LIT( KTxtCAknMessageQueryDialog, "CAknMessageQueryDialog::NewL" );
    AssertNotNullL( msgQueryDlg, KTxtCAknMessageQueryDialog );

    msgQueryDlg->PrepareLC( R_BCTESTMIX50_EIKDIALOG );
    _LIT( KTxtPrepareLC, "CAknMessageQueryDialog::PrepareLC" );
    AssertTrueL( ETrue, KTxtPrepareLC );

    CAknMessageQueryControl* msgCtrl = static_cast< CAknMessageQueryControl* >
                        ( msgQueryDlg->Control( EAknMessageQueryContentId ) );
    _LIT( KTxtCAknMessageQueryControl,
          "CAknMessageQueryControl static_cast< CAknMessageQueryControl* >" );
    AssertNotNullL( msgCtrl, KTxtCAknMessageQueryControl );

    msgCtrl->LinkHighLighted();
    _LIT( KTxtLinkHighLighted, "CAknMessageQueryControl::LinkHighLighted" );
    AssertTrueL( ETrue, KTxtLinkHighLighted );

    CleanupStack::Pop( );   // PrepareLC
    CleanupStack::PopAndDestroy( msgQueryDlg );
    }


// ---------------------------------------------------------------------------
// CBCTestMix50Case::TestCAknPopupHeadingPaneCaseL()
// ( menu item -5- )
// ---------------------------------------------------------------------------
//
void CBCTestMix50Case::TestCAknPopupHeadingPaneCaseL()
    {
    CAknPopupHeadingPane* head = new( ELeave ) CAknPopupHeadingPane();
    CleanupStack::PushL( head );
    _LIT( KTxtCAknPopupHeadingPane,
          "CAknPopupHeadingPane::CAknPopupHeadingPane" );
    AssertNotNullL( head, KTxtCAknPopupHeadingPane );

    CEikImage* image = new( ELeave ) CEikImage;
    CleanupStack::PushL( image ); 

    CFbsBitmap* bmpImg = new( ELeave ) CFbsBitmap;
    CleanupStack::PushL( bmpImg ); 

    CFbsBitmap* maskImg = new( ELeave ) CFbsBitmap;
    CleanupStack::PushL( maskImg ); 

    TSize iconSize( KIconWidth, KIconHeight );
    User::LeaveIfError( AknIconUtils::SetSize( bmpImg,
                                       iconSize, EAspectRatioNotPreserved ) );
    User::LeaveIfError( AknIconUtils::SetSize( maskImg,
                                       iconSize, EAspectRatioNotPreserved ) );
    image->SetPicture( bmpImg, maskImg );

    TBuf< KBuffLargeSize > buff;
    head->ConstructL( buff );
    _LIT( KTxtConstructL,
          "CAknPopupHeadingPane::ConstructL" );
    AssertTrueL( ETrue, KTxtConstructL );

    head->SetHeaderImageOwnedL( image );
    _LIT( KTxtSetHeaderImageOwnedL,
          "CAknPopupHeadingPane::SetHeaderImageOwnedL" );
    AssertTrueL( ETrue, KTxtSetHeaderImageOwnedL );

    CleanupStack::Pop( maskImg );
    CleanupStack::Pop( bmpImg );
    CleanupStack::Pop( image );
    CleanupStack::PopAndDestroy( head );
    }


// ---------------------------------------------------------------------------
// CBCTestMix50Case::TestCEikButtonGroupContainerCaseL()
// ( menu item -6- )
// ---------------------------------------------------------------------------
//
void CBCTestMix50Case::TestCEikButtonGroupContainerCaseL()
    {
    TInt pos = 0;
    TBCTestCommandObserver cmdObserver;
    CEikButtonGroupContainer* btnGroupContainer =
                                 CEikButtonGroupContainer::Current();

    btnGroupContainer->UpdateCommandObserverL( pos, cmdObserver );
    _LIT( KTxtUpdateCommandObserverL,
         "CEikButtonGroupContainer::UpdateCommandObserverL" );
    AssertTrueL( ETrue,  KTxtUpdateCommandObserverL );

    btnGroupContainer->UpdatedCommandObserverExists(
                           CEikButtonGroupContainer::ELeftSoftkeyPosition );
    _LIT( KTxtUpdatedCommandObserverExists,
         "CEikButtonGroupContainer::UpdatedCommandObserverExists" );
    AssertTrueL( ETrue, KTxtUpdatedCommandObserverExists );

    btnGroupContainer->RemoveCommandObserver( pos );
    _LIT( KTxtRemoveCommandObserver,
         "CEikButtonGroupContainer::RemoveCommandObserver" );
    AssertTrueL( ETrue, KTxtRemoveCommandObserver );
    
    }

// ---------------------------------------------------------------------------
// CBCTestMix50Case::TestCEikCbaCaseL()
// ( menu item -6.1- )
// ---------------------------------------------------------------------------
//
void CBCTestMix50Case::TestCEikCbaCaseL()
{
    CEikButtonGroupContainer* btnGroupContainer =
                                 CEikButtonGroupContainer::Current();
    

    CEikCba *eikcba = static_cast<CEikCba*>( btnGroupContainer->ButtonGroup() );
    eikcba->HandleControlEventL(eikcba, MCoeControlObserver::EEventStateChanged);
    _LIT(KHandleControlEvent, "CCoeControl::HandleControlEventL");
    AssertTrueL(ETrue, KHandleControlEvent);

}

// ---------------------------------------------------------------------------
// CBCTestMix50Case::TestCEikEdwinCaseL()
// ( menu item -7- )
// ---------------------------------------------------------------------------
//
void CBCTestMix50Case::TestCEikEdwinCaseL()
    {
    CEikEdwin* eikEdwin = new( ELeave ) CEikEdwin;
    CleanupStack::PushL( eikEdwin );
    _LIT( KTxtCEikEdwin, "CEikEdwin::CEikEdwin" );
    AssertNotNullL( eikEdwin, KTxtCEikEdwin );

    TRect rect( KXLeftPos, KYUpPos, KXRightPos, KYDownPos );
    eikEdwin->SetScrollRect( rect );
    _LIT( KTxtSetScrollRect, "CEikEdwin::SetScrollRect" );
    AssertTrueL( ETrue, KTxtSetScrollRect );

    CleanupStack::PopAndDestroy( eikEdwin );
    }


// ---------------------------------------------------------------------------
// CBCTestMix50Case::TestCAknSliderCaseL()
// ( menu item -8- )
// ---------------------------------------------------------------------------
//
void CBCTestMix50Case::TestCAknSliderCaseL()
    {
    CAknSlider* aknSlider = new( ELeave ) CAknSlider;
    CleanupStack::PushL( aknSlider );
    _LIT( KTxtCAknSlider, "CAknSlider::CAknSlider" );
    AssertNotNullL( aknSlider, KTxtCAknSlider );

    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_BCTESTMIX50_SLIDER );
    aknSlider->ConstructFromResourceL( reader ); 
    _LIT( KTxtConstructFromResourceL, "CAknSlider::ConstructFromResourceL" );
    AssertTrueL( ETrue, KTxtConstructFromResourceL );
    CleanupStack::PopAndDestroy(); // reader

    aknSlider->SetContainerWindowL( *iContainer );
    _LIT( KTxtSetContainerWindowLg, "CAknSlider::SetContainerWindowL" );
    AssertTrueL( ETrue, KTxtSetContainerWindowLg );

    TInt nMin = 0;
    TInt nMax = 0;
    aknSlider->SetRange( KMinVal, KMaxVal );
    _LIT( KTxtSetRange, "CAknSlider::SetRange" );
    AssertTrueL( ETrue, KTxtSetRange );

    aknSlider->GetRange( nMin, nMax );
    _LIT( KTxtGetRange, "CAknSlider::GetRange" );
    AssertTrueL( (KMinVal == nMin)&&(KMaxVal == nMax), KTxtGetRange );

    aknSlider->EnableDrag();
    _LIT( KTxtEnableDrag, "CAknSlider::EnableDrag" );
    AssertTrueL( ETrue, KTxtEnableDrag );

    CleanupStack::PopAndDestroy( aknSlider );
    }


// ---------------------------------------------------------------------------
// CBCTestMix50Case::TestCEikDialogCaseL()
// ( menu item -9- )
// ---------------------------------------------------------------------------
//
void CBCTestMix50Case::TestCEikDialogCaseL()
    {
    CEikDialog* dialog = new( ELeave ) CEikDialog;
    CleanupStack::PushL( dialog );
    _LIT( KTxtCEikDialog, "CEikDialog::CEikDialog" );
    AssertNotNullL( dialog, KTxtCEikDialog );

    dialog->ReadResourceLC( R_BCTESTMIX50_EIKDIALOG );
    _LIT( KTxtReadResourceLC, "CEikDialog::ReadResourceLC" );
    AssertTrueL( ETrue, KTxtReadResourceLC );
    CleanupStack::Pop();
    
    dialog->SetMultilineQuery( EFalse );
    dialog->SetMultilineQuery( ETrue );
    _LIT( KTxtSetMultilineQuery, "CEikDialog::SetMultilineQuery" );
    AssertTrueL( ETrue, KTxtSetMultilineQuery );

    CleanupStack::PopAndDestroy( dialog );
    }


// ---------------------------------------------------------------------------
// CBCTestMix50Case::TestCEikCaptionedControlCaseL()
// ( menu item -10- )
// ---------------------------------------------------------------------------
//
void CBCTestMix50Case::TestCEikCaptionedControlCaseL()
    {
    CEikCaptionedControl* captionCtrl = new( ELeave ) CEikCaptionedControl;
    CleanupStack::PushL( captionCtrl );
    _LIT( KTxtCEikCaptionedControl,
          "CEikCaptionedControl::CEikCaptionedControl" );
    AssertNotNullL( captionCtrl, KTxtCEikCaptionedControl );

    TBCTestPointerObserver pointerObserver;
    captionCtrl->SetPointerEventObserver( &pointerObserver );
    _LIT( KTxtSetPointerEventObserver,
          "CEikCaptionedControl::SetPointerEventObserver" );
    AssertTrueL( ETrue, KTxtSetPointerEventObserver );

    TInt nFlag = 0;
    captionCtrl->SetFormFlags( nFlag );
    _LIT( KTxtSetFormFlags,
          "CEikCaptionedControl::SetFormFlags" );
    AssertTrueL( ETrue, KTxtSetFormFlags );

    TInt nIcon = 0;
    CFbsBitmap* bitmap = new ( ELeave ) CFbsBitmap();
    CleanupStack::PushL( bitmap );

    CFbsBitmap* maskBmp = new ( ELeave ) CFbsBitmap();
    CleanupStack::PushL( maskBmp );

    captionCtrl->SetCaptionL( KTitle );
    _LIT( KTxtSetCaptionL,
          "CEikCaptionedControl::SetCaptionL" );
    AssertTrueL( ETrue, KTxtSetCaptionL );

    captionCtrl->SetIndicatorIconL( nIcon, bitmap, maskBmp );
    _LIT( KTxtSetIndicatorIconL,
          "CEikCaptionedControl::SetIndicatorIconL" );
    AssertTrueL( ETrue, KTxtSetIndicatorIconL );

    CleanupStack::Pop( maskBmp );
    CleanupStack::Pop( bitmap );
    CleanupStack::PopAndDestroy( captionCtrl );
    }


// ---------------------------------------------------------------------------
// CBCTestMix50Case::TestCAknVolumeControlCaseL()
// ( menu item -11- )
// ---------------------------------------------------------------------------
//
void CBCTestMix50Case::TestCAknVolumeControlCaseL()
    {
    CAknVolumeControl* volumeCtrl = new( ELeave ) CAknVolumeControl;
    CleanupStack::PushL( volumeCtrl );
    _LIT( KTxtCAknVolumeControl, "CAknVolumeControl::CAknVolumeControl" );
    AssertNotNullL( volumeCtrl, KTxtCAknVolumeControl );
    
    volumeCtrl->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_BCTESTMIX50_VOLUMECONTROL );
    volumeCtrl->ConstructFromResourceL( reader );
    _LIT( KTxtConstructFromResourceL,
          "CAknVolumeControl::ConstructFromResourceL" );
    AssertTrueL( ETrue, KTxtConstructFromResourceL );
    CleanupStack::PopAndDestroy(); // reader

    volumeCtrl->SetRange( KMinVal , KMaxVal );
    _LIT( KTxtSetRange, "CAknVolumeControl::SetRange" );
    AssertTrueL( ETrue, KTxtSetRange );

    TInt nMin = 0;
    TInt nMax = 0;
    volumeCtrl->GetRange( nMin , nMax );
    _LIT( KTxtGetRange, "CAknVolumeControl::GetRange" );
    AssertTrueL( ( KMinVal == nMin )&&( KMaxVal == nMax ), KTxtGetRange );

    CleanupStack::PopAndDestroy( volumeCtrl );
    volumeCtrl = NULL;

    CGulIcon* icon = CAknVolumeControl::CreateSetDynRangeStyleListBoxIconL(
    KDefaultVolumeLevel, KMinVal, KMaxVal );
    CleanupStack::PushL( icon );
    _LIT( KTxtCreateSetDynRangeStyleListBoxIconL,
          "CAknVolumeControl::CreateSetDynRangeStyleListBoxIconL" );
    AssertNotNullL( icon, KTxtCreateSetDynRangeStyleListBoxIconL );
    CleanupStack::PopAndDestroy( icon );
    }


// ---------------------------------------------------------------------------
// CBCTestMix50Case::TestCAknSettingPageCaseL()
// ( menu item -12- )
// ---------------------------------------------------------------------------
//
void CBCTestMix50Case::TestCAknSettingPageCaseL()
    {
    CBCTestCAknSettingPage* settingPage = new( ELeave )
            CBCTestCAknSettingPage( R_BCTESTMIX50SETPAGE_TEXT_SETTING_PAGE );
    CleanupStack::PushL( settingPage );
    _LIT( KTxtCBCTestCAknSettingPage,
          "CBCTestCAknSettingPage::CBCTestCAknSettingPage" );
    AssertNotNullL( settingPage, KTxtCBCTestCAknSettingPage );

    settingPage->ConstructL();
    _LIT( KTxtConstructL, "CAknSettingPage::ConstructL" );
    AssertTrueL( ETrue, KTxtConstructL );

    settingPage->TextLabel();
    _LIT( KTxtTextLabel, "CAknSettingPage::TextLabel" );
    AssertTrueL( ETrue, KTxtTextLabel );

    settingPage->ShadowText();
    _LIT( KTxtShadowText, "CAknSettingPage::ShadowText" );
    AssertTrueL( ETrue, KTxtShadowText );

    CleanupStack::PopAndDestroy( settingPage );
    }


// ---------------------------------------------------------------------------
// CBCTestMix50Case::TestCEikListBoxCaseL()
// ( menu item -13- )
// ---------------------------------------------------------------------------
//
void CBCTestMix50Case::TestCEikListBoxCaseL()
    {
    CEikListBox* listBox = new( ELeave ) CEikListBox();
    CleanupStack::PushL( listBox );
    _LIT( KTxtCEikListBox, "CEikListBox::CEikListBox" );
    AssertNotNullL( listBox, KTxtCEikListBox );

    listBox->RedrawItem( 0 );
    _LIT( KTxtRedrawItem, "CEikListBox::RedrawItem" );
    AssertTrueL( ETrue, KTxtRedrawItem );

    TBCTestSelectionObserver selectionObserver;
    listBox->AddSelectionObserverL( &selectionObserver );
    _LIT( KTxtAddSelectionObserverL,
          "CEikListBox::AddSelectionObserverL" );
    AssertTrueL( ETrue, KTxtAddSelectionObserverL );

    listBox->RemoveSelectionObserver( &selectionObserver );
    _LIT( KTxtRemoveSelectionObserver,
          "CEikListBox::RemoveSelectionObserver" );
    AssertTrueL( ETrue, KTxtRemoveSelectionObserver );

    CleanupStack::PopAndDestroy( listBox );
    }


// ---------------------------------------------------------------------------
// CBCTestMix50Case::TestCAknEdwinStateCaseL()
// ( menu item -14- )
// ---------------------------------------------------------------------------
//
void CBCTestMix50Case::TestCAknEdwinStateCaseL()
    {
    CAknEdwinState* edwinState = new( ELeave ) CAknEdwinState;
    CleanupStack::PushL( edwinState );
    _LIT( KTxtCAknEdwinState, "CAknEdwinState::CAknEdwinState" );
    AssertNotNullL( edwinState, KTxtCAknEdwinState );

    TInt nCmdID = 5;
    TInt nRetID = 0;
    edwinState->SetMiddleSoftkeyCommandId( nCmdID );
    _LIT( KTxtSetMiddleSoftkeyCommandId,
          "CAknEdwinState::SetMiddleSoftkeyCommandId" );
    AssertTrueL( ETrue, KTxtSetMiddleSoftkeyCommandId );

    nRetID = edwinState->MiddleSoftkeyCommandId();
    _LIT( KTxtMiddleSoftkeyCommandId, "CAknEdwinState::MiddleSoftkeyCommandId" );
    AssertTrueL( nCmdID == nRetID, KTxtMiddleSoftkeyCommandId );

    TBCTestCcpuEditor cpuEditor;
    edwinState->SetCcpuState( &cpuEditor );
    _LIT( KTxtSetCcpuState,
          "CAknEdwinState::SetCcpuState" );
    AssertTrueL( ETrue, KTxtSetCcpuState );

    CleanupStack::PopAndDestroy( edwinState );
    }


// ---------------------------------------------------------------------------
// CBCTestMix50Case::TestCEikMenuPaneCaseL()
// ( menu item -15- )
// ---------------------------------------------------------------------------
//
void CBCTestMix50Case::TestCEikMenuPaneCaseL()
    {
    CAknDialog* dlg = new( ELeave ) CAknDialog();
    CleanupStack::PushL( dlg );

    CEikMenuPane* menuPane = new( ELeave ) CEikMenuPane( dlg );
    CleanupStack::PushL( menuPane );

    TBuf< KBuffLargeSize > buff;
    menuPane->ConstructMenuSctRowFromDialogL( buff,
                          R_AVKON_EMAIL_ADDR_SPECIAL_CHARACTER_TABLE_DIALOG );
    _LIT( KTxtConstructMenuSctRowFromDialogL,
          "CAknEdwinState::ConstructMenuSctRowFromDialogL" );
    AssertTrueL( ETrue, KTxtConstructMenuSctRowFromDialogL );

    menuPane->ConstructMenuSctRowFromDialogL( EAknSCTLowerCase , buff,
                          R_AVKON_EMAIL_ADDR_SPECIAL_CHARACTER_TABLE_DIALOG );
    AssertTrueL( ETrue, KTxtConstructMenuSctRowFromDialogL );

    CleanupStack::PopAndDestroy( menuPane );
    CleanupStack::PopAndDestroy( dlg );
    }


// ---------------------------------------------------------------------------
// CBCTestMix50Case::TestCAknGridCaseL()
// ( menu item -16- )
// ---------------------------------------------------------------------------
//
void CBCTestMix50Case::TestCAknGridCaseL()
    {
    CBCTestCAknGrid* grid = new( ELeave) CBCTestCAknGrid();
    CleanupStack::PushL( grid );
    _LIT( KCAknGrid, "CAknGrid::CAknGrid" );
    AssertNotNullL( grid, KCAknGrid );

    TTypeUid tUid( 0 );
    grid->MopSupplyObject( tUid );
    _LIT( KTxtMopSupplyObject, "CAknGrid::MopSupplyObject" );
    AssertTrueL( ETrue, KTxtMopSupplyObject );

    CleanupStack::PopAndDestroy( grid );
    }


// ---------------------------------------------------------------------------
// CBCTestMix50Case::TestCColumnListBoxItemDrawerCaseL()
// ( menu item -( 17 )- )
// ---------------------------------------------------------------------------
//
/*void CBCTestMix50Case::TestCColumnListBoxItemDrawerCaseL()
    {
    CColumnListBoxItemDrawer* columnListBoxItemDrawer =
    new( ELeave )CColumnListBoxItemDrawer();
    CleanupStack::PushL( columnListBoxItemDrawer );

    _LIT( KCColumnListBoxItemDrawer,
          "CColumnListBoxItemDrawer::CColumnListBoxItemDrawer()" );
    AssertTrueL( ETrue, KCColumnListBoxItemDrawer );

    CleanupStack::PopAndDestroy( columnListBoxItemDrawer );
    }

*/
// ---------------------------------------------------------------------------
// CBCTestMix50Case::TestCAknLocationEditorCaseL()
// ( menu item -18- )
// ---------------------------------------------------------------------------
//
void CBCTestMix50Case::TestCAknLocationEditorCaseL()
    {
    CBCTestCAknLocationEditor* testEditor =
        new( ELeave )CBCTestCAknLocationEditor;
    CleanupStack::PushL( testEditor );

    TKeyEvent keyEvent;
    keyEvent.iCode = 0;
    testEditor->OfferKeyEventL( keyEvent, EEventKey );
    _LIT( KOfferKeyEventL, "CAknLocationEditor::OfferKeyEventL()" );
    AssertTrueL( ETrue, KOfferKeyEventL );

    TUid uid = { 0xA00040AB };
    testEditor->CAknLocationEditor_ExtensionInterface( uid );
    _LIT( KExtensionInterface,
          "CAknLocationEditor::CAknLocationEditor_ExtensionInterface()" );
    AssertTrueL( ETrue, KExtensionInterface );

    CleanupStack::PopAndDestroy( testEditor );
    }


// ---------------------------------------------------------------------------
// CBCTestMix50Case::TestCEikMfneCaseL()
// ( menu item -19- )
// ---------------------------------------------------------------------------
//
void CBCTestMix50Case::TestCEikMfneCaseL()
    {
    CEikMfne* eikMfne = new( ELeave )CEikMfne;
    CleanupStack::PushL( eikMfne );

    TInt result(0);
    eikMfne->GetFeature( 0, result );
    _LIT( KGetFeature, "CEikMfne::GetFeature" );
    AssertTrueL( ETrue, KGetFeature );

    result = eikMfne->SetFeature( 0, 0 );
    _LIT( KSetFeature, "CEikMfne::SetFeature" );
    AssertTrueL( ETrue, KSetFeature );

    result = eikMfne->SupportsFeature( 0 );
    _LIT( KSupportsFeature, "CEikMfne::SupportsFeature" );
    AssertTrueL( ETrue, KSupportsFeature );

    eikMfne->SetUseOverrideColors( ETrue );
    _LIT( KSetUseOverrideColors, "CEikMfne::SetUseOverrideColors" );
    AssertTrueL( ETrue, KSetUseOverrideColors );

    //TC indirectly calling overridden CEikMfne::SizeChanged
    eikMfne->CreateFieldArrayL(3);
    CEikMfneNumber *mfnenum = CEikMfneNumber::NewL(*LatinPlain12(), 0, 99, 55, 0);
    eikMfne->AddField(mfnenum);

    CEikMfneSeparator *mfnesep = CEikMfneSeparator::NewL(_L("xbdf0\x00C1\x00C7:").AllocL());
    eikMfne->AddField(mfnesep);
    
    CEikMfneSeparator *mfnesep1 = CEikMfneSeparator::NewL(_L("FOOBAR").AllocL());
    eikMfne->AddField(mfnesep1);
    
    TSize sizeCtrl = eikMfne->Size();
    sizeCtrl.iHeight +=1;
    sizeCtrl.iWidth +=1;
    eikMfne->SetSize(sizeCtrl);
    _LIT( KSizeChanged, "CEikMfne::SizeChanged()" );
    AssertTrueL( ETrue, KSizeChanged );


    eikMfne->ResetFieldArray();
    _LIT( KResetFieldArray, "CEikMfne::ResetFieldArray()" );
    AssertTrueL( ETrue, KResetFieldArray );
    


    CleanupStack::PopAndDestroy( eikMfne );
    }


// ---------------------------------------------------------------------------
// CBCTestMix50Case::TestCAknUnitEditorCaseL()
// ( menu item -20- )
// ---------------------------------------------------------------------------
//
void CBCTestMix50Case::TestCAknUnitEditorCaseL()
    {
    CAknUnitEditor* aknUnitEditor = CAknUnitEditor::NewL();
    CleanupStack::PushL( aknUnitEditor );

    _LIT( KTxtNewL, "CAknUnitEditor::NewL()" );
    AssertNotNullL( aknUnitEditor, KTxtNewL );

    TResourceReader resourceReader;
    iEnv->CreateResourceReaderLC( resourceReader, R_BCTESTMIX50_EDITOR_EDWIN );

    aknUnitEditor->ConstructFromResourceL( resourceReader );
    _LIT( KConstructFromResourceL,
          "CAknUnitEditor::ConstructFromResourceL()" );
    AssertTrueL( ETrue, KConstructFromResourceL );

    CleanupStack::PopAndDestroy();  // resourceReader
    CleanupStack::PopAndDestroy( aknUnitEditor );
    _LIT( KTxtDestrutctor, "CAknUnitEditor::~CAknUnitEditor()" );
    AssertTrueL( ETrue, KTxtDestrutctor );
    aknUnitEditor = NULL;

    aknUnitEditor = CAknUnitEditor::NewLC();
    _LIT( KTxtNewLC, "CAknUnitEditor::NewLC()" );
    AssertNotNullL( aknUnitEditor, KTxtNewLC );

    aknUnitEditor->ConstructL( 1, 1, 1, 1, 1, 1 );
    _LIT( KConstructL, "CAknUnitEditor::ConstructL()" );
    AssertTrueL( ETrue, KConstructL );

    aknUnitEditor->SetContainerWindowL( *iContainer );
    _LIT( KSetContainerWindowL, "CAknUnitEditor::SetContainerWindowL()" );
    AssertTrueL( ETrue, KSetContainerWindowL );

    aknUnitEditor->Flags();
    _LIT( KFlags, "CAknUnitEditor::Flags()" );
    AssertTrueL( ETrue, KFlags );

    TReal min, max;
    aknUnitEditor->GetMinimumAndMaximum( min, max );
    _LIT( KGetMinimumAndMaximum, "CAknUnitEditor::GetMinimumAndMaximum()" );
    AssertTrueL( ETrue, KGetMinimumAndMaximum );

    TBuf< KBuffSmallSize > uEditData;
    aknUnitEditor->GetUnit( uEditData );
    _LIT( KGetUnit, "CAknUnitEditor::GetUnit()" );
    AssertTrueL( ETrue, KGetUnit );

    aknUnitEditor->MaxFractionalDigits();
    _LIT( KMaxFractionalDigits, "CAknUnitEditor::MaxFractionalDigits()" );
    AssertTrueL( ETrue, KMaxFractionalDigits );

    aknUnitEditor->PrepareForFocusLossL();
    _LIT( KPrepareForFocusLossL, "CAknUnitEditor::PrepareForFocusLossL()" );
    AssertTrueL( ETrue, KPrepareForFocusLossL );

    aknUnitEditor->SetFlags( 0 );
    _LIT( KSetFlags, "CAknUnitEditor::SetFlags()" );
    AssertTrueL( ETrue, KSetFlags );

    aknUnitEditor->SetMaxFractionalDigits( 1 );
    _LIT( KSetMaxFractionalDigits, "CAknUnitEditor::SetMaxFractionalDigits()" );
    AssertTrueL( ETrue, KSetMaxFractionalDigits );

    aknUnitEditor->SetMinimumAndMaximum( 0, 1 );
    _LIT( KSetMinimumAndMaximum, "CAknUnitEditor::SetMinimumAndMaximum()" );
    AssertTrueL( ETrue, KSetMinimumAndMaximum );

    aknUnitEditor->SetUnitL( uEditData );
    _LIT( KSetUnitL, "CAknUnitEditor::SetUnitL()" );
    AssertTrueL( ETrue, KSetUnitL );

    aknUnitEditor->SetUnitL( 0 );
    _LIT( KSetUnitLInt, "CAknUnitEditor::SetUnitL()" );
    AssertTrueL( ETrue, KSetUnitLInt );

    aknUnitEditor->SetValue( 0.0 );
    _LIT( KSetValueDouble, "CAknUnitEditor::SetValue()" );
    AssertTrueL( ETrue, KSetValueDouble );

    aknUnitEditor->Unit();
    _LIT( KUnit, "CAknUnitEditor::Unit()" );
    AssertTrueL( ETrue, KUnit );
    
    aknUnitEditor->Value();
    _LIT( KValue, "CAknUnitEditor::Value()" );
    AssertTrueL( ETrue, KValue );

    aknUnitEditor->SupportsUnit( 0 );
    _LIT( KSupportsUnit, "CAknUnitEditor::SupportsUnit()" );
    AssertTrueL( ETrue, KSupportsUnit );

    CleanupStack::PopAndDestroy( aknUnitEditor );
    }


// ---------------------------------------------------------------------------
// CBCTestMix50Case::TestCColumnListBoxDataCaseL()
// ( menu item -21- )
// ---------------------------------------------------------------------------
//
void CBCTestMix50Case::TestCColumnListBoxDataCaseL()
    {
    CColumnListBoxData* columnListBoxData = CColumnListBoxData::NewL();
    CleanupStack::PushL( columnListBoxData );

    columnListBoxData->CurrentItemTextWasClipped();
    _LIT( KCurrentItemTextWasClipped,
          "CColumnListBoxData::CurrentItemTextWasClipped()" );
    AssertTrueL( ETrue, KCurrentItemTextWasClipped );

    CleanupStack::PopAndDestroy( columnListBoxData );
    }

// ---------------------------------------------------------------------------
// CBCTestMix50Case::TestCAknchoicelist()
// ( menu item -22- )
// ---------------------------------------------------------------------------
//
void CBCTestMix50Case::TestCAknchoicelist()
    {
    
   CAknButton* btn = CAknButton::NewLC( NULL, NULL, NULL,
                          NULL, _L("LeftButton"), KNullDesC,
                          KAknButtonNoFrame, 0 );
    
    CleanupStack::PopAndDestroy();
    btn = NULL;    
    
    btn = CAknButton::NewL( NULL, NULL, NULL,
                          NULL, _L("LeftButton"), KNullDesC,
                          KAknButtonNoFrame, 0 );

    CDesCArrayFlat* itemArray = new ( ELeave ) CDesCArrayFlat( 8 );
    CleanupStack::PushL( itemArray );
    itemArray->AppendL( _L("orking") );
    itemArray->AppendL( _L("ll") );
    itemArray->AppendL( _L("sti") );
    itemArray->AppendL( _L("w") );


    CAknChoiceList *choList = CAknChoiceList::NewL( iContainer, itemArray,
                                                    CAknChoiceList::EAknChoiceListWithCurrentSelection, btn );

    CleanupStack::PushL( choList );
    _LIT( aknChoiceList, " ChoiceList create successfully " );
    AssertNotNullL(  choList, aknChoiceList );

    CleanupStack::Pop( choList );
    CleanupStack::Pop( itemArray );
    delete btn;

    choList->ShowChoiceListL();
    _LIT( showList, " ShowChoiceList! " );
    AssertTrueL( ETrue, showList);

    choList->SetSelectedIndex( TInt( 1 ) );
    _LIT( setIndex, " SetSelectedIndex()!" );
    AssertTrueL( ETrue, setIndex );

    choList->SelectedIndex();
    _LIT( selectedIndex, " SelectedIndex() " );
    AssertTrueL( ETrue, selectedIndex );

    //choList->SetItemsL( R_MYCHOICELIST_ITEMS );
    _LIT( setItemsL, " SetItemsL( TInt aResourceId ) " );
    AssertTrueL( ETrue, setItemsL );
    
    _LIT( setItems, " SetItems( CDesCArray* aArray ) " );
    CDesCArray* array = new ( ELeave ) CDesCArrayFlat( 1 );
    array->AppendL( setItems );	
    choList->SetItems( array ); 
    AssertTrueL( ETrue, setItems );

    TBuf<20> *bf = new ( ELeave ) TBuf<20>;
    choList->AddItemL( bf );
    _LIT( addItemL, " AddItemL() " );
    AssertTrueL( ETrue, addItemL );

    choList->RemoveItem( TInt( 1 ) );
    _LIT( removeItem, " RemoveItem() " );
    AssertTrueL( ETrue, removeItem );

    choList->SetFlags( TInt( 1 ) );
    _LIT( setFlags, " SetFlags() " );
    AssertTrueL( ETrue, setFlags );

    choList->Flags();
    _LIT( flg, " Flags() " );
    AssertTrueL( ETrue, flg );

    choList->SetButtonL( CAknButton::NewL() );
    _LIT( setButtonL, " SetButtonL() " );
    AssertTrueL( ETrue, setButtonL );

    choList->HideChoiceList();
    _LIT( hideChoiceList, " HideChoiceList() " );
    AssertTrueL( ETrue, hideChoiceList );

    _LIT( setTooltipTextL, " SetTooltipTextL() " );
    choList->SetTooltipTextL( setTooltipTextL );
    AssertTrueL( ETrue, setTooltipTextL );
    
    choList->SetTooltipTimeouts( 150, 3000 ); // 150 and 3000 are the defaults
    _LIT( setTooltipTimeouts, " SetTooltipTimeouts() " );
    AssertTrueL( ETrue, setTooltipTimeouts );
    
    choList->SetTooltipPosition( CAknChoiceList::EPositionTop );
    _LIT( setTooltipPosition, " SetTooltipPosition() " );
    AssertTrueL( ETrue, setTooltipPosition );    
    
    choList->ComponentControl( TInt( 1 ) );
    _LIT( componentControl, " componentControl() " );
    AssertTrueL( ETrue, componentControl );

    choList->CountComponentControls();
    _LIT( countComponentControls, " CountComponentControls() " );
    AssertTrueL( ETrue, countComponentControls );

    choList->MinimumSize();
    _LIT( minimumSize, " MinimumSize() " );
    AssertTrueL( ETrue, minimumSize );

/*komala    choList->PositionChanged();//test PositionChanged    
    _LIT( KCAknChoiceList,
        "CColumnListBoxData::TestCAknchoicelist()" );
    AssertTrueL( ETrue, KCAknChoiceList );
*/
    choList->HandleResourceChange( TInt( 1 ) );
    _LIT( handleResourceChange, " HandleResourceChange() " );
    AssertTrueL( ETrue, handleResourceChange );

    TKeyEvent keyEvent;
    choList->OfferKeyEventL( keyEvent, EEventNull );
     _LIT( offerKeyEventL, " OfferKeyEventL() " );
    AssertTrueL( ETrue, offerKeyEventL );

    choList->Draw( TRect() );
    _LIT( draw, " Draw() " );
    AssertTrueL( ETrue, draw );

    choList->HandleControlEventL( iContainer, 
    	MCoeControlObserver::EEventRequestFocus );
    _LIT( handleControlEventL, " HandleControlEventL() " );
    AssertTrueL( ETrue, handleControlEventL );

    choList->InsertItemL( TInt( 2 ), *bf );
    _LIT( insertItemL, " InsertItemL() " );
    AssertTrueL( ETrue, insertItemL );

    delete bf;
    delete choList;
    
    }
    
// ---------------------------------------------------------------------------
// CBCTestMix50Case::TestCAknButton()
// ( menu item -23- )
// ---------------------------------------------------------------------------
//
/*komala void CBCTestMix50Case::TestCAknButton()
    {
    CAknButton* aknCAknButton = CAknButton::NewL(); 
    CleanupStack::PushL( aknCAknButton );
    aknCAknButton->PositionChanged();
    _LIT( KCAknButton,
        "CColumnListBoxData::TestCAknButton()" );
    AssertTrueL( ETrue, KCAknButton );
    CleanupStack::PopAndDestroy( aknCAknButton );
    }
*/
// ---------------------------------------------------------------------------
// CBCTestMix50Case::TestTouchFeedback()
// ( menu item -21- )
// ---------------------------------------------------------------------------
//
void CBCTestMix50Case::TestTouchFeedback()   
    {
    MTouchFeedback* feedback = MTouchFeedback::Instance();
    _LIT( KMTouchFeedbackInstance,
          "MTouchFeedback::Instance" );
    AssertTrueL( ETrue, KMTouchFeedbackInstance );   
    
    feedback->TouchFeedbackSupported();
    _LIT(KMTouchFBSupported, "TouchFeedbackSuppoted()!");
    AssertTrueL( ETrue, KMTouchFBSupported );  
    
    feedback->SetFeedbackEnabledForThisApp( ETrue );
    _LIT(KMSetFeedbackEnabledForThisApp, "SetFeedbackEnabledForThisApp()!");
    AssertTrueL( ETrue, KMSetFeedbackEnabledForThisApp );  
    
    TBool fb;
    fb = feedback->FeedbackEnabledForThisApp();
    _LIT(KMFeedbackEnabledForThisApp, "FeedbackEnabledForThisApp()!");
    AssertTrueL( ETrue, KMFeedbackEnabledForThisApp );  
    //AssertTrueL( ETrue, fb );
    
    feedback->FlushRegistryUpdates();
    _LIT(KMFlushRegUpdates, "FlushRegistryUpdates()!");
    AssertTrueL(ETrue, KMFlushRegUpdates);
    
 
    TTouchLogicalFeedback type;
    feedback->InstantFeedback(type);
    _LIT(KMInstantFeedback, "InstantFeedback()!");
    AssertTrueL(ETrue, KMInstantFeedback);
    
    CAknButton* aknCAknButton = CAknButton::NewL(); 
    CleanupStack::PushL( aknCAknButton );
    
    TUint32 index;
    TRect rect;
    TTouchEventType etype;
    feedback->SetFeedbackArea( aknCAknButton, index, rect, type, etype);
    _LIT(KMSetFeedbackArea, "SetFeedbackArea()!");
    AssertTrueL(ETrue, KMSetFeedbackArea);
    
    feedback->RemoveFeedbackArea(aknCAknButton, index);
    _LIT(KMRemoveFeedbackArea, "RemoveFeedbackArea()!");
    AssertTrueL( ETrue, KMRemoveFeedbackArea );
    
    feedback->RemoveFeedbackForControl(aknCAknButton);
    _LIT(KMRemoveFeedbackForControl, "RemoveFeedbackForControl()!");
    AssertTrueL( ETrue, KMRemoveFeedbackForControl );
    
    feedback->ChangeFeedbackArea(aknCAknButton, index, rect);
    _LIT(KMChangeFeedbackArea, "ChangeFeedbackArea()!");
    AssertTrueL( ETrue, KMChangeFeedbackArea );
    
    feedback->ChangeFeedbackType(aknCAknButton, index, type);
    _LIT(KMChangeFeedbackType, "ChangeFeedbackType()!");
    AssertTrueL( ETrue, KMChangeFeedbackType );
    
    feedback->MoveFeedbackAreaToFirstPriority(aknCAknButton, index);
    _LIT(KMMoveFeedbackAreaToFirstPriority, "MoveFeedbackAreaToFirstPriority()!");
    AssertTrueL(ETrue, KMMoveFeedbackAreaToFirstPriority);
    
    feedback->InstantFeedback(aknCAknButton, type);
    _LIT(KMInstantFeedback2, "InstantFeedback(aknCAknButton, type)!");
    AssertTrueL(ETrue, KMInstantFeedback2);
    
    feedback->ControlHasFeedback(aknCAknButton);
    _LIT(KMControlHasFeedback, "ControlHasFeedback()!");
    AssertTrueL(ETrue, KMControlHasFeedback);
    
    feedback->ControlHasFeedback(aknCAknButton, index);
    _LIT(KMControlHasFeedback2, "ControlHasFeedback(index)!");
    AssertTrueL(ETrue, KMControlHasFeedback2);
    
    feedback->EnableFeedbackForControl( aknCAknButton, fb );
    _LIT(KMEnableFeedbackForControl, "EnableFeedbackForControl()!");
    AssertTrueL(ETrue, KMEnableFeedbackForControl);
    
    
    
    
    CleanupStack::PopAndDestroy( aknCAknButton );
    
    if( !feedback )
        {
        MTouchFeedback*  feedbackCreated = MTouchFeedback::CreateInstanceL();
        _LIT( KMTouchFeedbackCreateInstanceL,
              "MTouchFeedback::CreateInstanceL" );
        AssertTrueL( ETrue, KMTouchFeedbackCreateInstanceL );     
        
        
        MTouchFeedback::DestroyInstance();
        _LIT( KMTouchFeedbackDestroyInstance,
              "MTouchFeedback::DestroyInstance" );
        AssertTrueL( ETrue, KMTouchFeedbackDestroyInstance );     
                
        }

		
    }
        