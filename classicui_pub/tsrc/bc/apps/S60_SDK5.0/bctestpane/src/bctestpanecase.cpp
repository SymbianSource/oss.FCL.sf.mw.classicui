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
#include <barsread.h>
#include <eikenv.h>
#include <akniconutils.h>
#include <avkon.rsg>
#include <akndef.h>
#include <eikspane.h>
#include <akncontext.h>
#include <eikimage.h>
#include <akntabgrp.h>
#include <aknnavide.h>
#include <aknnavilabel.h>
#include <akndlgshut.h>
#include <aknpictographinterface.h>

#include "bctestpanecase.h"
#include "bctestpanecontainer.h"
#include "bctestpane.hrh"
#include <bctestpane.rsg>

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestPaneCase* CBCTestPaneCase::NewL(
    CBCTestPaneContainer* aContainer )
    {
    CBCTestPaneCase* self = new( ELeave ) CBCTestPaneCase(
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
CBCTestPaneCase::CBCTestPaneCase(
    CBCTestPaneContainer* aContainer )
    : iContainer( aContainer )
    {
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestPaneCase::~CBCTestPaneCase()
    {
    delete iTitle;
    delete iNaviDe;
	delete iTab;
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestPaneCase::ConstructL()
    {
    BuildScriptL();

    iEnv = CEikonEnv::Static();
    }

// ---------------------------------------------------------------------------
// CBCTestPaneCase::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestPaneCase::BuildScriptL()
    {
    // Add script as your need.
    AddTestL( DELAY( 3 ), TEND );
    TInt loop = EBCTestCmdMaxOutline - EBCTestCmdTitlePane;
    for ( TInt i = 0; i < loop; i++ )
        {
        AddTestL( LeftCBA, REP( Down, i ), KeyOK, TEND );
        }
    }

// ---------------------------------------------------------------------------
// CBCTestPaneCase::RunL
// ---------------------------------------------------------------------------
//
void CBCTestPaneCase::RunL( TInt aCmd )
    {
    iCommand = aCmd;
    ReleaseCase();
    switch ( aCmd )
        {
        case EBCTestCmdTitlePane:
            TestTitlePaneL();
            break;
        case EBCTestCmdStatusPane:
            TestStatusPaneL();
            break;
        case EBCTestCmdContextPane:
            TestContextPaneL();
            break;
        case EBCTestCmdTabGroup:
            TestTabGroupL();
            break;
        case EBCTestCmdNaviPane:
            TestNaviPaneL();
            break;
        case EBCTestCmdDlgShutAndPicto:
            TestDlgShutAndPictoL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestPaneCase::ReleaseCase
// ---------------------------------------------------------------------------
//
void CBCTestPaneCase::ReleaseCase()
    {
    iContainer->ResetControl();
    iContainer->SetPaneCase( NULL );
    }

// ---------------------------------------------------------------------------
// Test CAknTitlePane
// ---------------------------------------------------------------------------
//
void CBCTestPaneCase::TestTitlePaneL()
    {
    iTitle = new( ELeave ) CBCTestPaneTitle();
    _LIT( KTitle1, "CAknTitlePane::CAknTitlePane" );
    AssertNotNullL( iTitle, KTitle1 );

    iTitle->ConstructL();
    _LIT( KTitle2, "CAknTitlePane::ConstructL" );
    AssertTrueL( ETrue, KTitle2 );

    TBCTestTitleObserver titleObserver;
    iTitle->SetTitlePaneObserver( &titleObserver );
    _LIT( KTitle22, "CAknTitlePane::SetTitlePaneObserver" );
    AssertTrueL( ETrue, KTitle22 );

    MAknTitlePaneObserver* mobs = &titleObserver;
    TInt eve=100;
    mobs->HandleTitlePaneEventL(eve);
    _LIT( KHandleTitlePaneEventL, "MAknTitlePaneObserver::HandleTitlePaneEventL()!");
    AssertTrueL( ETrue, KHandleTitlePaneEventL );
    
    delete iTitle;
    iTitle = NULL;

    iTitle= new( ELeave ) CBCTestPaneTitle();
    
    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_BCTESTPANE_TITLE_PANE );
    iTitle->SetFromResourceL( reader );
    _LIT( KTitle21, "CAknTitlePane::SetFromResorceL" );
    AssertTrueL( ETrue, KTitle21 );
    CleanupStack::PopAndDestroy(); // reader
    delete iTitle;
    iTitle = NULL;

    iTitle = new( ELeave ) CBCTestPaneTitle();
    iTitle->SetContainerWindowL( *iContainer );

    iEnv->CreateResourceReaderLC( reader, R_BCTESTPANE_TITLE_PANE );
    iTitle->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy(); // reader
    _LIT( KTitle3, "CAknTitlePane::ConstructFromResourceL" );
    AssertTrueL( ETrue, KTitle3 );

    _LIT( KTitleText, "iTitle text" );
    TPtrC titlePtr( KTitleText );

    HBufC* buf = HBufC::NewLC( titlePtr.Length() );
    *buf = KTitleText;

    iTitle->SetText( buf, ETrue );
    _LIT( KTitle5, "CAknTitlePane::SetText( HBufC*, TBool )" );
    AssertTrueL( ETrue, KTitle5 );
    CleanupStack::Pop( buf );

    HBufC* buf2 = HBufC::NewLC( titlePtr.Length() );
    *buf = KTitleText;

    iTitle->SetText( buf2 );
    _LIT( KTitle4, "CAknTitlePane::SetText" );
    AssertTrueL( ETrue, KTitle4 );
    CleanupStack::Pop( buf2 );

    _LIT( KTitleText1, "Another iTitle" );
    TPtrC anotherText( KTitleText1 );
    iTitle->SetTextL( anotherText );
    _LIT( KTitle6, "CAknTitlePane::SetTextL" );
    AssertTrueL( ETrue, KTitle6 );

    iTitle->SetTextL( anotherText, ETrue );
    _LIT( KTitle7, "CAknTitlePane::SetTextL( const TDesC&, TBool )" );
    AssertTrueL( ETrue, KTitle7 );

    const TDesC* text = iTitle->Text();
    _LIT( KTitle8, "CAknTitlePane::Text" );
    AssertTrueL( ETrue, KTitle8 );

    CFbsBitmap* bmp = new( ELeave ) CFbsBitmap();
    CleanupStack::PushL( bmp );
    TSize size( 100, 80 );
    bmp->Create( size, ERgb );
    iTitle->SetPicture( bmp );
    _LIT( KTitle9, "CAknTitlePane::SetPicture" );
    AssertTrueL( ETrue, KTitle9 );
    CleanupStack::Pop( bmp );

    iTitle->SetPictureFromFileL( AknIconUtils::AvkonIconFileName(),
        EMbmAvkonQgn_indi_signal_strength,
        EMbmAvkonQgn_indi_signal_strength_mask );
    _LIT( KTitle10, "CAknTitlePane::SetPictureFromFileL" );
    AssertTrueL( ETrue, KTitle10 );

    CFbsBitmap* smallBmp = new( ELeave ) CFbsBitmap();
    CleanupStack::PushL( smallBmp );
    smallBmp->Create( size, ERgb );
    CFbsBitmap* smallMask = new( ELeave ) CFbsBitmap();
    CleanupStack::PushL( smallMask );
    smallMask->Create( size, ERgb );
    iTitle->SetSmallPicture( smallBmp, smallMask, ETrue );
    _LIT( KTitle11, "CAknTitlePane::SetSmallPicture" );
    AssertTrueL( ETrue, KTitle11 );
    CleanupStack::Pop( smallMask );
    CleanupStack::Pop( smallBmp );

    iTitle->SetTextToDefaultL();
    _LIT( KTitle12, "CAknTitlePane::SetTextToDefaultL" );
    AssertTrueL( ETrue, KTitle12 );

    iTitle->HandleResourceChange( KEikDynamicLayoutVariantSwitch );
    _LIT( KTitle15, "CAknTitlePane::HandleResourceChange" );
    AssertTrueL( ETrue, KTitle15 );

    iTitle->PositionChanged();
    _LIT( KTitle16, "CAknTitlePane::PositionChanged" );
    AssertTrueL( ETrue, KTitle16 );

    TInt count = iTitle->CountComponentControls();
    _LIT( KTitle17, "CAknTitlePane::PositionChanged" );
    AssertTrueL( ETrue, KTitle17 );

    CCoeControl* ctrl = iTitle->ComponentControl( count - 1 );
    _LIT( KTitle18, "CAknTitlePane::ComponentControl" );
    AssertNotNullL( ctrl, KTitle18 );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    iTitle->HandlePointerEventL( event );
    _LIT( KTitle19, "CAknTitlePane::HandlePointerEventL" );
    AssertTrueL( ETrue, KTitle19 );

    iContainer->SetPaneCase( this );
    }

// ---------------------------------------------------------------------------
// Test status pane
// ---------------------------------------------------------------------------
//
void CBCTestPaneCase::TestStatusPaneL()
    {
    RWindowGroup& win = iEnv->RootWin();
    CEikStatusPane* status = CEikStatusPane::NewL( *iEnv,
        &win, R_AVKON_STATUS_PANE );
    CleanupStack::PushL( status );
    _LIT( KStatusPane1, "CEikStatusPane::NewL" );
    AssertNotNullL( status, KStatusPane1 );

    status->SwitchLayoutL( R_AVKON_STATUS_PANE_LAYOUT_IDLE );
    status->SwitchLayoutL( R_AVKON_STATUS_PANE_LAYOUT_POWER_OFF_RECHARGE );
    status->SwitchLayoutL( R_AVKON_STATUS_PANE_LAYOUT_EMPTY );
    status->SwitchLayoutL( R_AVKON_STATUS_PANE_LAYOUT_SMALL );
    status->SwitchLayoutL( R_AVKON_STATUS_PANE_LAYOUT_SMALL_WITH_SIGNAL_PANE );
    status->SwitchLayoutL( R_AVKON_STATUS_PANE_LAYOUT_VT );
    status->SwitchLayoutL( R_AVKON_STATUS_PANE_LAYOUT_USUAL_MIRRORED );
    status->SwitchLayoutL( R_AVKON_STATUS_PANE_LAYOUT_IDLE_MIRRORED );
    status->SwitchLayoutL( R_AVKON_STATUS_PANE_LAYOUT_POWER_OFF_RECHARGE_MIRRORED );
    status->SwitchLayoutL( R_AVKON_STATUS_PANE_LAYOUT_SMALL_WITH_SIGNAL_PANE_MIRRORED );
    status->SwitchLayoutL( R_AVKON_STATUS_PANE_LAYOUT_VT_MIRRORED );
    status->SwitchLayoutL( R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_RIGHT );
    status->SwitchLayoutL( R_AVKON_STACON_PANE_LAYOUT_USUAL_SOFTKEYS_LEFT );
    status->SwitchLayoutL( R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_RIGHT );
    status->SwitchLayoutL( R_AVKON_STACON_PANE_LAYOUT_IDLE_SOFTKEYS_LEFT );
    status->SwitchLayoutL( R_AVKON_STACON_PANE_LAYOUT_EMPTY_SOFTKEYS_RIGHT );
    status->SwitchLayoutL( R_AVKON_STACON_PANE_LAYOUT_EMPTY_SOFTKEYS_LEFT );
    status->SwitchLayoutL( R_AVKON_STATUS_PANE_LAYOUT_IDLE_FLAT );
    status->SwitchLayoutL( R_AVKON_STATUS_PANE_LAYOUT_USUAL_FLAT );
    status->SwitchLayoutL( R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL );
    status->SwitchLayoutL( R_AVKON_STATUS_PANE_LAYOUT_USUAL );
    _LIT( KStatusPane16,
        "Use CEikStatusPaneBase::SwitchLayoutL to test different layouts" );
    AssertTrueL( ETrue, KStatusPane16 );

    status->MakeVisible( ETrue );
    _LIT( KStatusPane2, "CEikStatusPane::MakeVisible" );
    AssertTrueL( ETrue, KStatusPane2 );

    status->SetDimmed( ETrue );
    status->SetDimmed( EFalse );
    _LIT( KStatusPane3, "CEikStatusPane::SetDimmed" );
    AssertTrueL( ETrue, KStatusPane3 );

    status->SetFaded( ETrue );
    status->SetFaded( EFalse );
    _LIT( KStatusPane4, "CEikStatusPane::SetFaded" );
    AssertTrueL( ETrue, KStatusPane4 );

    status->ApplyCurrentSettingsL();
    _LIT( KStatusPane5, "CEikStatusPane::ApplyCurrentSettingsL" );
    AssertTrueL( ETrue, KStatusPane5 );

    status->HandleResourceChange( KEikDynamicLayoutVariantSwitch );
    status->HandleResourceChange( KEikMessageEmbedLevelChange );
    _LIT( KStatusPane6, "CEikStatusPane::HandleResourceChange" );
    AssertTrueL( ETrue, KStatusPane6 );

    TBool changeNow = status->OkToChangeStatusPaneNow();
    _LIT( KStatusPane7, "CEikStatusPane::HandleResourceChange" );
    AssertTrueL( ETrue, KStatusPane7 );

    status->PrepareForAppExit();
    _LIT( KStatusPane8, "CEikStatusPane::PrepareForAppExit" );
    AssertTrueL( ETrue, KStatusPane8 );

    status->DrawNow();
    _LIT( KStatusPane9, "CEikStatusPaneBase::DrawNow" );
    AssertTrueL( ETrue, KStatusPane9 );

    status->CEikStatusPaneBase::SetFaded( ETrue );
    _LIT( KStatusPane10, "CEikStatusPaneBase::SetFaded" );
    AssertTrueL( ETrue, KStatusPane10 );

    status->IsFaded();
    _LIT( KStatusPane11, "CEikStatusPaneBase::IsFaded" );
    AssertTrueL( ETrue, KStatusPane11 );

    const TInt KPaneCtrlUid = 0;
    TPaneId paneId = TPaneId::Uid( KPaneCtrlUid );
    TRect rect = status->PaneRectL( paneId );
    _LIT( KStatusPane12, "CEikStatusPaneBase::PaneRectL" );
    AssertTrueL( ETrue, KStatusPane12 );

    CEikStatusPaneBase::TPaneCapabilities capabilities =
        status->PaneCapabilities( paneId );
    _LIT( KStatusPane13, "CEikStatusPaneBase::PaneCapabilities" );
    AssertTrueL( ETrue, KStatusPane13 );

    TInt flags = 2; // KEikStatusPaneBaseVisibleBit
    status->SetFlags( flags );
    _LIT( KStatusPane14, "CEikStatusPaneBase::SetFlags" );
    AssertTrueL( ETrue, KStatusPane14 );

    CCoeControl* control = status->SwapControlL( paneId, iContainer );
    _LIT( KStatusPane15, "CEikStatusPaneBase::SwapControlL" );
    AssertTrueL( ETrue, KStatusPane15 );
    status->SwapControlL( paneId, control );

    CleanupStack::PopAndDestroy( status );
    }

// ---------------------------------------------------------------------------
// Test context pane
// ---------------------------------------------------------------------------
//
void CBCTestPaneCase::TestContextPaneL()
    {
    iContext = new( ELeave ) CBCTestContextPane();
    _LIT( KContextPane1, "CAknContextPane::CAknContextPane" );
    AssertNotNullL( iContext, KContextPane1 );

    iContext->SetContainerWindowL( *iContainer );
    iContext->ConstructL();
    _LIT( KContextPane2, "CAknContextPane::ConstructL" );
    AssertTrueL( ETrue, KContextPane2 );

    delete iContext;
    iContext = NULL;

    iContext = new( ELeave ) CBCTestContextPane();
    iContext->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_BCTESTPANE_CONTEXT_PANE );
    iContext->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy(); // reader;

    CFbsBitmap* bmp = new( ELeave ) CFbsBitmap();
    CleanupStack::PushL( bmp );
    TSize size( 100, 80 );
    bmp->Create( size, ERgb );
    iContext->SetPicture( bmp );
    _LIT( KContextPane3, "CAknContextPane::SetPicture with CFbsBitmap" );
    AssertTrueL( ETrue, KContextPane3 );
    CleanupStack::Pop( bmp );
    CEikImage* tempImage = iContext->SwapPicture( NULL );
    delete tempImage;
    bmp = new( ELeave ) CFbsBitmap();
    CleanupStack::PushL( bmp );
    bmp->Create( size, ERgb );
    iContext->SetPicture( bmp );
    CleanupStack::Pop( bmp );

    CEikImage* image = new( ELeave ) CEikImage();
    CleanupStack::PushL( image );
    image->CreatePictureFromFileL( AknIconUtils::AvkonIconFileName(),
        EMbmAvkonQgn_indi_signal_strength,
        EMbmAvkonQgn_indi_signal_strength_mask );
    iContext->SetPicture( image );
    _LIT( KContextPane4, "CAknContextPane::SetPicture with CEikImage" );
    AssertTrueL( ETrue, KContextPane4 );
    CleanupStack::Pop( image );

    const CEikImage& eikImage = iContext->Picture();
    _LIT( KContextPane5, "CAknContextPane::Picture" );
    AssertTrueL( ETrue, KContextPane5 );

    iContext->SetPictureFromFileL( AknIconUtils::AvkonIconFileName(),
        EMbmAvkonQgn_indi_signal_strength,
        EMbmAvkonQgn_indi_signal_strength_mask );
    _LIT( KContextPane6, "CAknContextPane::SetPictureFromFileL" );
    AssertTrueL( ETrue, KContextPane6 );

    iEnv->CreateResourceReaderLC( reader, R_BCTESTPANE_CONTEXT_PANE );
    iContext->SetFromResourceL( reader );
    CleanupStack::PopAndDestroy(); // reader
    _LIT( KContextPane7, "CAknContextPane::SetFromResourceL" );
    AssertTrueL( ETrue, KContextPane7 );

    iContext->SetPictureToDefaultL();
    _LIT( KContextPane8, "CAknContextPane::SetPictureToDefaultL" );
    AssertTrueL( ETrue, KContextPane8 );

    CEikImage* newImage = new( ELeave ) CEikImage();
    CleanupStack::PushL( newImage );
    newImage->CreatePictureFromFileL( AknIconUtils::AvkonIconFileName(),
        EMbmAvkonQgn_indi_battery_strength,
        EMbmAvkonQgn_indi_battery_strength_mask );
    CleanupStack::Pop( newImage );
    CEikImage* oldImage = iContext->SwapPicture( newImage );
    delete oldImage;
    _LIT( KContextPane9, "CAknContextPane::SwapPicture" );
    AssertTrueL( ETrue, KContextPane9 );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    iContext->HandlePointerEventL( event );
    _LIT( KContextPane10, "CAknContextPane::HandlePointerEventL" );
    AssertTrueL( ETrue, KContextPane10 );

    iContext->HandleResourceChange( KEikColorResourceChange );
    iContext->HandleResourceChange( KAknsMessageSkinChange );
    _LIT( KContextPane11, "CAknContextPane::HandleResourceChange" );
    AssertTrueL( ETrue, KContextPane11 );

    iContext->SetPictureToDefaultL();
    iContainer->SetControl( iContext );
    }

// ---------------------------------------------------------------------------
// Test CAknTabGroup
// ---------------------------------------------------------------------------
//
void CBCTestPaneCase::TestTabGroupL()
    {
    iTab = CAknTabGroup::NewL( *iContainer );
    _LIT( KTab1, "CAknTabGroup::NewL" );
    AssertNotNullL( iTab, KTab1 );

    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_BCTESTPANE_TAB );
    TInt tabId = iTab->AddTabL( reader );
    CleanupStack::PopAndDestroy(); // reader
    _LIT( KTab2, "CAknTabGroup::AddTabL with resource reader" );
    AssertTrueL( ETrue, KTab2 );

    tabId++;	//defined in HRH?
    _LIT( KTabText, "Tab" );
    iTab->AddTabL( EBCTestTab2, KTabText );
    _LIT( KTab3, "CAknTabGroup::AddTabL with text" );
    AssertTrueL( ETrue, KTab3 );

    tabId++;
    CFbsBitmap* bmp = new( ELeave ) CFbsBitmap();
    CleanupStack::PushL( bmp );
    TSize size( 100, 80 );
    bmp->Create( size, ERgb );
    iTab->AddTabL( EBCTestTab3, KTabText, bmp );
    CleanupStack::Pop( bmp );
    _LIT( KTab4, "CAknTabGroup::AddTabL with text and CFbsBitmap" );
    AssertTrueL( ETrue, KTab4 );

    tabId++;
    CFbsBitmap* bmp1 = new( ELeave ) CFbsBitmap();
    CleanupStack::PushL( bmp1 );
    bmp1->Create( size, ERgb );
    iTab->AddTabL( EBCTestTab4, bmp1 );
    CleanupStack::Pop( bmp1 );
    _LIT( KTab5, "CAknTabGroup::AddTabL with CFbsBitmap" );
    AssertTrueL( ETrue, KTab5 );

    TBCTestTabObserver observer;
    iTab->SetObserver( NULL );
    iTab->SetObserver( &observer );
    _LIT( KTab22, "CAknTabGroup::TabCount" );
    AssertTrueL( ETrue, KTab22 );

    iEnv->CreateResourceReaderLC( reader, R_BCTESTPANE_TAB1 );
    iTab->ReplaceTabL( reader );
    CleanupStack::PopAndDestroy(); // reader
    _LIT( KTab6, "CAknTabGroup::ReplaceTabL with resource reader" );
    AssertTrueL( ETrue, KTab6 );

    iTab->ReplaceTabL( EBCTestTab1, KTabText );
    _LIT( KTab7, "CAknTabGroup::ReplaceTabL with text" );
    AssertTrueL( ETrue, KTab7 );

    CFbsBitmap* bmp2 = new( ELeave ) CFbsBitmap();
    CleanupStack::PushL( bmp2 );
    bmp2->Create( size, ERgb );
    iTab->ReplaceTabL( EBCTestTab1, KTabText, bmp2 );
    CleanupStack::Pop( bmp2 );
    _LIT( KTab8, "CAknTabGroup::ReplaceTabL with text and CFbsBitmap" );
    AssertTrueL( ETrue, KTab8 );

    CFbsBitmap* bmp3 = new( ELeave ) CFbsBitmap();
    CleanupStack::PushL( bmp3 );
    bmp3->Create( size, ERgb );
    iTab->ReplaceTabL( EBCTestTab1, bmp3 );
    CleanupStack::Pop( bmp3 );
    _LIT( KTab9, "CAknTabGroup::ReplaceTabL with CFbsBitmap" );
    AssertTrueL( ETrue, KTab9 );

    _LIT( KTabText1, "Replace Tab text" );
    iTab->ReplaceTabTextL( EBCTestTab2, KTabText1 );
    _LIT( KTab10, "CAknTabGroup::ReplaceTabTextL" );
    AssertTrueL( ETrue, KTab10 );

    iTab->SetActiveTabById( EBCTestTab2 );
    _LIT( KTab12, "CAknTabGroup::SetActiveTabById" );
    AssertTrueL( ETrue, KTab12 );

    iTab->DeleteTabL( EBCTestTab1 );
    _LIT( KTab11, "CAknTabGroup::DeleteTabL" );
    AssertTrueL( ETrue, KTab11 );

    iTab->SetActiveTabByIndex( 0 );
    _LIT( KTab13, "CAknTabGroup::SetActiveTabByIndex" );
    AssertTrueL( ETrue, KTab13 );

    tabId = iTab->ActiveTabId();
    _LIT( KTab14, "CAknTabGroup::ActiveTabId" );
    AssertTrueL( ETrue, KTab14 );

    TInt tabIndex = iTab->ActiveTabIndex();
    _LIT( KTab15, "CAknTabGroup::ActiveTabId" );
    AssertTrueL( ETrue, KTab15 );

    iTab->SetTabFixedWidthL( KTabWidthWithFourTabs );
    iTab->SetTabFixedWidthL( KTabWidthWithThreeLongTabs );
    iTab->SetTabFixedWidthL( KTabWidthWithTwoLongTabs );
    iTab->SetTabFixedWidthL( KTabWidthWithTwoLongTabs + 40 );
    iTab->SetTabFixedWidthL( 20 );
    _LIT( KTab16, "CAknTabGroup::SetTabFixedWidthL" );
    AssertTrueL( ETrue, KTab16 );

    iTab->DimTab( tabId, ETrue );
    _LIT( KTab17, "CAknTabGroup::DimTab" );
    AssertTrueL( ETrue, KTab17 );

    TBool isTabDimmed = iTab->IsTabDimmed( tabId );
    _LIT( KTab18, "CAknTabGroup::IsTabDimmed" );
    AssertTrueL( ETrue, KTab18 );

    tabIndex = iTab->TabIndexFromId( tabId );
    _LIT( KTab19, "CAknTabGroup::TabIndexFromId" );
    AssertTrueL( ETrue, KTab19 );

    tabId = iTab->TabIdFromIndex( tabIndex );
    _LIT( KTab20, "CAknTabGroup::TabIndexFromId" );
    AssertTrueL( ETrue, KTab20 );

    TInt tabCount = iTab->TabCount();
    _LIT( KTab21, "CAknTabGroup::TabCount" );
    AssertTrueL( ETrue, KTab21 );

    TSize minimumSize = iTab->MinimumSize();
    _LIT( KTab23, "CAknTabGroup::MinimumSize" );
    AssertTrueL( ETrue, KTab23 );

    TKeyEvent leftArrow = { EKeyLeftArrow, EKeyLeftArrow, 0, 0 };
    TKeyEvent rightArrow = { EKeyRightArrow, EKeyRightArrow, 0, 0 };
    iTab->OfferKeyEventL( leftArrow, EEventKey );
    iTab->OfferKeyEventL( rightArrow, EEventKey );
    _LIT( KTab24, "CAknTabGroup::OfferKeyEventL" );
    AssertTrueL( ETrue, KTab24 );

    CArrayFixFlat<TCoeColorUse>* colorList = new( ELeave )
        CArrayFixFlat<TCoeColorUse>( 4 );
    CleanupStack::PushL( colorList );
    iTab->GetColorUseListL( *colorList );
    CleanupStack::PopAndDestroy( colorList );
    _LIT( KTab25, "CAknTabGroup::GetColorUseListL" );
    AssertTrueL( ETrue, KTab25 );

    iTab->HandleResourceChange( KAknsMessageSkinChange );
    iTab->HandleResourceChange( KEikDynamicLayoutVariantSwitch );
    _LIT( KTab26, "CAknTabGroup::HandleResourceChange" );
    AssertTrueL( ETrue, KTab26 );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    iTab->HandlePointerEventL( event );
    _LIT( KTab27, "CAknTabGroup::HandlePointerEventL" );
    AssertTrueL( ETrue, KTab27 );

    iTab->HandleControlEventL( iContainer,
        MCoeControlObserver::EEventRequestFocus );
    _LIT( KTab28, "CAknTabGroup::HandleControlEventL" );
    AssertTrueL( ETrue, KTab28 );

    iTab->HandleNaviDecoratorEventL(
        MAknNaviDecoratorObserver::EAknNaviDecoratorEventLeftTabArrow);
    iTab->HandleNaviDecoratorEventL(
        MAknNaviDecoratorObserver::EAknNaviDecoratorEventRightTabArrow);
    _LIT( KTab29, "CAknTabGroup::HandleNaviDecoratorEventL" );
    AssertTrueL( ETrue, KTab29 );

    iTab->SetFocus( EFalse );
    _LIT( KTab30, "CAknTabGroup::FocusChanged" );
    AssertTrueL( ETrue, KTab30 );

    tabCount = iTab->TabCount();
    iTab->SetActiveTabById( tabCount );
    //iTab->DeleteTabL( tabCount );

    iContainer->SetControl( iTab );	//give owner ship to container
	iTab=NULL;

    }

// ---------------------------------------------------------------------------
// Test navigation pane API
// ---------------------------------------------------------------------------
//
void CBCTestPaneCase::TestNaviPaneL()
    {
    iNavi = new( ELeave ) CAknNavigationControlContainer();
    _LIT( KNavi1, "CAknNavigationControlContainer::CAknNavigationControlContainer" );
    AssertNotNullL( iNavi, KNavi1 );

    iNavi->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    iEnv->CreateResourceReaderLC( reader, R_BCTESTPANE_NAVIDECORATOR );
    iNavi->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy(); // reader
    _LIT( KNavi2, "CAknNavigationControlContainer::ConstructFromResourceL" );
    AssertTrueL( ETrue, KNavi2 );

    CAknNavigationDecorator* naviDe = iNavi->CreateTabGroupL();
    delete naviDe;
    naviDe = NULL;
    _LIT( KNavi3, "CAknNavigationControlContainer::CreateTabGroupL" );
    AssertTrueL( ETrue, KNavi3 );

    TBCTestTabObserver observer;
    naviDe = iNavi->CreateTabGroupL( &observer );
    delete naviDe;
    naviDe = NULL;
    _LIT( KNavi4, "CAknNavigationControlContainer::CreateTabGroupL with observer" );
    AssertTrueL( ETrue, KNavi4 );

    iEnv->CreateResourceReaderLC( reader, R_BCTESTPANE_TABGROUP );
    naviDe = iNavi->CreateTabGroupL( reader );
    CleanupStack::PopAndDestroy(); // reader
    delete naviDe;
    naviDe = NULL;
    _LIT( KNavi5, "CAknNavigationControlContainer::CreateTabGroupL with resource reader" );
    AssertTrueL( ETrue, KNavi5 );

    iEnv->CreateResourceReaderLC( reader, R_BCTESTPANE_TABGROUP );
    naviDe = iNavi->CreateTabGroupL( reader, &observer );
    CleanupStack::PopAndDestroy(); // reader
    delete naviDe;
    naviDe = NULL;
    _LIT( KNavi6, "CAknNavigationControlContainer::CreateTabGroupL with resource reader and observer" );
    AssertTrueL( ETrue, KNavi6 );

    _LIT( KNaviLabel, "Navigation Label" );
    naviDe = iNavi->CreateNavigationLabelL( KNaviLabel );
    delete naviDe;
    naviDe = NULL;
    _LIT( KNavi7, "CAknNavigationControlContainer::CreateNavigationLabelL with text" );
    AssertTrueL( ETrue, KNavi7 );

    TSize size( 100, 80 );
    CFbsBitmap* bmp = new( ELeave ) CFbsBitmap();
    CleanupStack::PushL( bmp );
    bmp->Create( size, ERgb );
    naviDe = iNavi->CreateNavigationImageL( bmp );
    delete naviDe;
    naviDe = NULL;
    CleanupStack::Pop( bmp );
    _LIT( KNavi8, "CAknNavigationControlContainer::CreateNavigationImageL with CFbsBitmap" );
    AssertTrueL( ETrue, KNavi8 );

    iEnv->CreateResourceReaderLC( reader, R_BCTESTPANE_NAVIIMAGE );
    naviDe = iNavi->CreateNavigationImageL( reader );
    delete naviDe;
    naviDe = NULL;
    CleanupStack::PopAndDestroy(); // reader
    _LIT( KNavi9, "CAknNavigationControlContainer::CreateNavigationImageL with resource reader" );
    AssertTrueL( ETrue, KNavi9 );

    _LIT( KNaviMsgLabel, "Navigation message" );
    naviDe = iNavi->CreateMessageLabelL( KNaviMsgLabel );
    delete naviDe;
    naviDe = NULL;
    _LIT( KNavi10, "CAknNavigationControlContainer::CreateMessageLabelL with text" );
    AssertTrueL( ETrue, KNavi10 );

    iEnv->CreateResourceReaderLC( reader, R_BCTESTPANE_NAVILABEL );
    naviDe = iNavi->CreateMessageLabelL( reader );
    delete naviDe;
    naviDe = NULL;
    CleanupStack::PopAndDestroy(); // reader
    _LIT( KNavi11, "CAknNavigationControlContainer::CreateMessageLabelL with resource reader" );
    AssertTrueL( ETrue, KNavi11 );

    naviDe = iNavi->CreateVolumeIndicatorL( R_BCTESTPANE_VOLUME_INDICATOR );
    delete naviDe;
    naviDe = NULL;
    _LIT( KNavi12, "CAknNavigationControlContainer::CreateVolumeIndicatorL" );
    AssertTrueL( ETrue, KNavi12 );

    naviDe = iNavi->CreateEditorIndicatorContainerL();
    delete naviDe;
    naviDe = NULL;
    _LIT( KNavi13, "CAknNavigationControlContainer::CreateEditorIndicatorContainerL" );
    AssertTrueL( ETrue, KNavi13 );

    iNavi->PushDefaultL();
    _LIT( KNavi14, "CAknNavigationControlContainer::PushDefaultL" );
    AssertTrueL( ETrue, KNavi14 );

    iNavi->Pop();
    _LIT( KNavi15, "CAknNavigationControlContainer::Pop" );
    AssertTrueL( ETrue, KNavi15 );

    CAknNavigationDecorator* oldNaviDe = iNavi->Top();
    _LIT( KNavi16, "CAknNavigationControlContainer::Top" );
    AssertTrueL( ETrue, KNavi16 );

    CAknNavigationDecorator* newNaviDe =
        iNavi->CreateMessageLabelL( KNaviLabel );
    CleanupStack::PushL( newNaviDe );
    iNavi->ReplaceL( *oldNaviDe, *newNaviDe );
    _LIT( KNavi17, "CAknNavigationControlContainer::Top" );
    AssertTrueL( ETrue, KNavi17 );
    CleanupStack::PopAndDestroy( newNaviDe );

    iNaviDe = iNavi->ResourceDecorator();
    iNavi->PushL( *iNaviDe );
    _LIT( KNavi18, "CAknNavigationControlContainer::ResourceDecorator" );
    AssertTrueL( ETrue, KNavi18 );

    TInt colorScheme = CAknNavigationControlContainer::ColorScheme();
    _LIT( KNavi19, "CAknNavigationControlContainer::ColorScheme" );
    AssertTrueL( ETrue, KNavi19 );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( 10, 30 );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;

    iNavi->HandlePointerEventL( event );
    _LIT( KNavi20, "CAknNavigationControlContainer::HandlePointerEventL" );
    AssertTrueL( ETrue, KNavi20 );

    CAknNaviLabel* naviLabel = new( ELeave ) CAknNaviLabel();
    CleanupStack::PushL( naviLabel );
    naviLabel->HandlePointerEventL( event );
    _LIT( KNaviLabel1, "CAknNaviLabel::HandlePointerEventL" );
    AssertTrueL( ETrue, KNaviLabel1 );

    CAknNaviLabel::TNaviLabelType labelType = naviLabel->NaviLabelType();
    _LIT( KNaviLabel2, "CAknNaviLabel::NaviLabelType" );
    AssertTrueL( ETrue, KNaviLabel2 );
    CleanupStack::PopAndDestroy( naviLabel );

    iNaviDe->CAknNavigationDecorator::HandlePointerEventL( event );
    _LIT( KNaviDe1, "CAknNavigationDecorator::HandlePointerEventL" );
    AssertTrueL( ETrue, KNaviDe1 );

    TBool dimmed = iNaviDe->IsScrollButtonDimmed(
        CAknNavigationDecorator::ELeftButton );
    _LIT( KNaviDe2, "CAknNavigationDecorator::IsScrollButtonDimmed" );
    AssertTrueL( ETrue, KNaviDe2 );

    iNaviDe->SetNaviControlLayoutMode(
        CAknNavigationDecorator::ENaviControlLayoutModeAutomatic);
    _LIT( KNaviDe3, "CAknNavigationDecorator::SetNaviControlLayoutMode" );
    AssertTrueL( ETrue, KNaviDe3 );

    CAknNavigationDecorator::TAknNaviControlLayoutMode mode =
        iNaviDe->NaviControlLayoutMode();
    _LIT( KNaviDe4, "CAknNavigationDecorator::NaviControlLayoutMode" );
    AssertTrueL( ETrue, KNaviDe4 );

    iNaviDe->SetNaviControlLayoutStyle(
        CAknNavigationDecorator::ENaviControlLayoutNormal );
    _LIT( KNaviDe5, "CAknNavigationDecorator::SetNaviControlLayoutStyle" );
    AssertTrueL( ETrue, KNaviDe5 );

    TBool supported = iNaviDe->NaviControlLayoutStyleSupported(
        CAknNavigationDecorator::ENaviControlLayoutNarrow);
    _LIT( KNaviDe6, "CAknNavigationDecorator::NaviControlLayoutStyleSupported" );
    AssertTrueL( ETrue, KNaviDe6 );

    iNaviDe->SetNaviDecoratorObserver( &iNaviObserver );
    _LIT( KNaviDe7, "CAknNavigationDecorator::SetNaviDecoratorObserver" );
    AssertTrueL( ETrue, KNaviDe7 );

    iContainer->SetControl( iNavi );
    }

// ---------------------------------------------------------------------------
// Test DialogShutter and Pictograph
// ---------------------------------------------------------------------------
//
void CBCTestPaneCase::TestDlgShutAndPictoL()
    {
    AknDialogShutter::ShutDialogsL( *iEnv );
    _LIT( KDlgShut, "AknDialogShutter::ShutDialogsL" );
    AssertTrueL( ETrue, KDlgShut );

    TBCTestPictoAnimCallBack animCallback;
    CAknPictographInterface* picto = CAknPictographInterface::NewL(
        *iContainer, animCallback );
    delete picto;
    _LIT( KPictograph, "CAknPictographInterface::NewL" );
    AssertTrueL( ETrue, KPictograph );
    }

// ---------------------------------------------------------------------------
// Test API related with CWindowGc
// ---------------------------------------------------------------------------
//
void CBCTestPaneCase::DrawCaseL( CWindowGc& aGc )
    {
    if ( ( iCommand == EBCTestCmdTitlePane ) && iTitle )
        {
        iTitle->PrepareContext( aGc );
        _LIT( KTitle21, "CAknTitlePane::PrepareContext" );
        AssertTrueL( ETrue, KTitle21 );
        }
    }

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Implementation of MAknTabObserver
// ---------------------------------------------------------------------------
//
void TBCTestNaviDeObserver::HandleNaviDecoratorEventL( TInt )
    {
    }

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Implementation of MAknTabObserver
// ---------------------------------------------------------------------------
//
void TBCTestTabObserver::TabChangedL( TInt )
    {
    }

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Implementation of MAknPictographAnimatorCallBack
// ---------------------------------------------------------------------------
//
void TBCTestPictoAnimCallBack::DrawPictographArea()
    {
    }

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Implementation of MAknTitlePaneObserver
// ---------------------------------------------------------------------------
//
void TBCTestTitleObserver::HandleTitlePaneEventL( TInt )
    {
    }

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CBCTestContextPane::MopSupplyObject
// ---------------------------------------------------------------------------
//
TTypeUid::Ptr CBCTestContextPane::MopSupplyObject( TTypeUid )
    {
    return TTypeUid::Null();
    }
