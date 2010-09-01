/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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

#include <fbs.h>
#include <akncharmap.h>
#include <aknjavalists.h>
#include <aknsctdialog.h>
#include <aknvolumepopup.h>
#include <aknextendedinputcapabilities.h>
#include <bctestdommix50.rsg>

#include "bctestdommix50case.h"
#include "bctestdommix50container.h"
#include "bctestdommix50.hrh"
#include "bctestdommix50extendclasses.h"


const TInt KMinVal = 0;
const TInt KMaxVal = 100;

const TInt KStepSize = 2;
const TInt KCurrMark = 5;

const TInt KTimeOutSec = 40;
const TInt KBuffSmallSize = 32;

const TInt KXRightPos = 100;
const TInt KYDownPos  = 100;

const TInt KDefaultVolumeLevel = 5;

_LIT( KTitle, "Title" );


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CBCTestDomMix50Case::NewL()
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestDomMix50Case* CBCTestDomMix50Case::NewL(
    CBCTestDomMix50Container* aContainer )
    {
    CBCTestDomMix50Case* self = new( ELeave ) CBCTestDomMix50Case( aContainer );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// CBCTestDomMix50Case::CBCTestDomMix50Case()
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestDomMix50Case::CBCTestDomMix50Case(
    CBCTestDomMix50Container* aContainer )
    : iContainer( aContainer )
    {
    }


// ---------------------------------------------------------------------------
// CBCTestDomMix50Case::~CBCTestDomMix50Case()
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestDomMix50Case::~CBCTestDomMix50Case()
    {
    }


// ---------------------------------------------------------------------------
// CBCTestDomMix50Case::ConstructL()
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestDomMix50Case::ConstructL()
    {
    BuildScriptL();
    iEnv = CEikonEnv::Static(); 
    }


// ---------------------------------------------------------------------------
// CBCTestDomMix50Case::BuildScriptL()
//
// ---------------------------------------------------------------------------
//
void CBCTestDomMix50Case::BuildScriptL()
    {
    // Add script
    const TInt scripts[] =
        {
        DELAY(1),
        LeftCBA, KeyOK,                   // menuitem1
        LeftCBA, REP( Down, 1 ), KeyOK,   // menuitem2
        LeftCBA, REP( Down, 2 ), KeyOK,   // menuitem3
        LeftCBA, REP( Down, 3 ), KeyOK,   // menuitem4
        LeftCBA, REP( Down, 4 ), KeyOK, Right, REP( KeyOK, 2 ), RightCBA, 
        LeftCBA, REP( Down, 5 ), KeyOK,   // menuitem6
        LeftCBA, REP( Down, 6 ), KeyOK   // menuitem7
        };

    AddTestScriptL( scripts, sizeof( scripts ) / sizeof( TInt ) );
    }


// ---------------------------------------------------------------------------
// CBCTestDomMix50Case::RunL()
//
// ---------------------------------------------------------------------------
//
void CBCTestDomMix50Case::RunL( TInt aCmd )
    {
    if ( aCmd < EBCTestCmdOutline1 || aCmd > EBCTestCmdOutline7 )
        {
        return;
        }

    switch ( aCmd )
        {
        case EBCTestCmdOutline1:
            TestCAknPopupFormCaseL();
            break;
        case EBCTestCmdOutline2:
            TestCAknCharMapCaseL();
            break;
        case EBCTestCmdOutline3:
            TestCAknCharMapDialogCaseL();
            break;
        case EBCTestCmdOutline4:
            TestCAknVolumePopupCaseL();
            break;
        case EBCTestCmdOutline5:
            TestCAknTransparentCameraSettingPageCaseL();
            break;
        case EBCTestCmdOutline6:
            TestCAknSingle2GraphicStyleListBoxCaseL();
            break;
        case EBCTestCmdOutline7:
            TestCAknExtendedInputCapabilitiesCaseL();
            break;

        default:
            break;
        }
    }


// ---------------------------------------------------------------------------
// CBCTestDomMix50Case::TestCAknPopupFormCaseL()
// ( menu item -1- )
// ---------------------------------------------------------------------------
//
void CBCTestDomMix50Case::TestCAknPopupFormCaseL()
    {
    CBCTestCAknPopupForm* popupForm = CBCTestCAknPopupForm::NewL();
    CleanupStack::PushL( popupForm );
    _LIT( KTxtCBCTestCAknPopupForm, "CBCTestCAknPopupForm::NewL" );
    AssertNotNullL( popupForm, KTxtCBCTestCAknPopupForm );
    
    TPointerEvent pointerEvent;
    pointerEvent.iType = TPointerEvent::EMove;
    //TPoint eventPos( KXRightPos , KYDownPos );
    //pointerEvent.iPosition = eventPos;
    //pointerEvent.iParentPosition = eventPos;
    popupForm->HandlePointerEventL( pointerEvent );
    _LIT( KHandlePointerEventL, "CAknPopupForm::HandlePointerEventL" );
    AssertTrueL( ETrue, KHandlePointerEventL );   

    CleanupStack::PopAndDestroy( popupForm );
    }


// ---------------------------------------------------------------------------
// CBCTestDomMix50Case::TestCAknCharMapCaseL()
// ( menu item -2- )
// ---------------------------------------------------------------------------
//
void CBCTestDomMix50Case::TestCAknCharMapCaseL()
    {
    CAknCharMap* charMap = new( ELeave ) CAknCharMap();
    CleanupStack::PushL( charMap ) ;
    _LIT( KCAknCharMap, "CAknCharMap::CAknCharMap()" );
    AssertNotNullL( charMap, KCAknCharMap );

    charMap->ConstructMenuSctRowFromDialogL(
                        R_AVKON_EMAIL_ADDR_SPECIAL_CHARACTER_TABLE_DIALOG );
    _LIT( KConstructMenuSctRowFromDialogL,
          "CAknCharMap::ConstructMenuSctRowFromDialogL()" );
    AssertTrueL( ETrue, KConstructMenuSctRowFromDialogL );    

    CleanupStack::PopAndDestroy( charMap );
    }


// ---------------------------------------------------------------------------
// CBCTestDomMix50Case::TestCAknCharMapDialogCaseL()
// ( menu item -3- )
// ---------------------------------------------------------------------------
//
void CBCTestDomMix50Case::TestCAknCharMapDialogCaseL()
    {
     TInt charcase = 1; 
    _LIT( tmp,"specialchars" );
    TBuf< KBuffSmallSize > specialchars( tmp );
    CAknCharMapDialog* mapDlg = new ( ELeave )
                                CAknCharMapDialog( charcase, specialchars );
    CleanupStack::PushL( mapDlg );
    _LIT( KTxtCAknCharMapDialog, "CAknCharMapDialog::CAknCharMapDialog" );
    AssertNotNullL( mapDlg, KTxtCAknCharMapDialog );

    mapDlg->DisableRecentCharsRow();
    _LIT( KTxtDisableRecentCharsRow,
          "CAknCharMapDialog::DisableRecentCharsRow" );
    AssertTrueL( ETrue, KTxtDisableRecentCharsRow );

    CleanupStack::PopAndDestroy( mapDlg );
    }


// ---------------------------------------------------------------------------
// CBCTestDomMix50Case::TestCAknVolumePopupCaseL()
// ( menu item -4- )
// ---------------------------------------------------------------------------
//
void CBCTestDomMix50Case::TestCAknVolumePopupCaseL()
    {
    CAknVolumePopup* volumePopup = CAknVolumePopup::NewL( iContainer, EFalse );
    CleanupStack::PushL( volumePopup );
    _LIT( KTxtCAknVolumePopup, "CAknVolumePopup::NewL( CCoeControl )" );
    AssertNotNullL( volumePopup, KTxtCAknVolumePopup );

    volumePopup->SetRange( KMinVal, KMaxVal );
    _LIT( KTxtSetRange, "CAknVolumePopup::SetRange" );
    AssertTrueL( ETrue, KTxtSetRange );

    TInt nMinVol = 0;
    TInt nMaxVol = 0;
    volumePopup->GetRange( nMinVol , nMaxVol );
    _LIT( KTxtGetRange, "CAknVolumePopup::GetRange" );
    AssertTrueL( ( KMinVal == nMinVol )&&( KMaxVal == nMaxVol )
               , KTxtGetRange );

    volumePopup->SetStepSize( KStepSize );
    _LIT( KTxtSetStepSize, "CAknVolumePopup::SetStepSize" );
    AssertTrueL( ETrue, KTxtSetStepSize );

    volumePopup->SetValueType( EAknSliderValueDecimal );
    _LIT( KTxtSetValueType, "CAknVolumePopup::SetValueType" );
    AssertTrueL( ETrue, KTxtSetValueType );

    volumePopup->SetDecimalPlaces( KCurrMark );
    _LIT( KTxtSetDecimalPlaces, "CAknVolumePopup::SetDecimalPlaces" );
    AssertTrueL( ETrue, KTxtSetDecimalPlaces );
    
    volumePopup->CloseVolumePopup();
    _LIT( KTxtCloseVolumePopup, "CAknVolumePopup::CloseVolumePopup" );
    AssertTrueL( ETrue, KTxtCloseVolumePopup );

    CleanupStack::PopAndDestroy( volumePopup );
    volumePopup = NULL;

    volumePopup = CAknVolumePopup::ConstructFromResourceL(
                                           R_BCTESTDOMMIX50_VOLUMECONTROL );
    CleanupStack::PushL( volumePopup );
    _LIT( KTxtConstructFromResourceL,
          "CAknVolumePopup::ConstructFromResourceL" );
    AssertNotNullL( volumePopup, KTxtConstructFromResourceL );

    volumePopup->SetTimeOutAsSecond( KTimeOutSec );
    _LIT( KTxtSetTimeOutAsSecond, "CAknVolumePopup::SetTimeOutAsSecond" );
    AssertTrueL( ETrue, KTxtSetTimeOutAsSecond );

    volumePopup->SetAdjustmentIndicatorDisplay( EFalse );
    volumePopup->SetAdjustmentIndicatorDisplay( ETrue );
    _LIT( KTxtSetAdjustmentIndicatorDisplay,
          "CAknVolumePopup::SetAdjustmentIndicatorDisplay" );
    AssertTrueL( ETrue, KTxtSetAdjustmentIndicatorDisplay );

    volumePopup->SetValue( KDefaultVolumeLevel );
    _LIT( KTxtSetValue, "CAknVolumePopup::SetValue" );
    AssertTrueL( ETrue, KTxtSetValue );

    volumePopup->CloseVolumePopup();
    AssertTrueL( ETrue, KTxtCloseVolumePopup );

    CleanupStack::PopAndDestroy( volumePopup );
    }


// ---------------------------------------------------------------------------
// CBCTestDomMix50Case::TestCAknSettingPageCaseL()
// ( menu item -5- )
// ---------------------------------------------------------------------------
//
void CBCTestDomMix50Case::TestCAknTransparentCameraSettingPageCaseL()
    {
    CDesCArrayFlat* array =
    iEnv->ReadDesCArrayResourceL( R_BCTESTDOMMIX50_TRANSPARENTCAMERA_ITEM_ARRAY );
    CleanupStack::PushL( array );

    TInt currentItem( 0 );
    CBCTestCAknTransparentCameraSettingPage* transCameraSettingPage =
    new( ELeave ) CBCTestCAknTransparentCameraSettingPage(
          R_BCTESTDOMMIX50_TRANSPARENTCAMERA_SETTING_PAGE, currentItem, array );
    CleanupStack::PushL( transCameraSettingPage );
    _LIT( KTxtCAknTransparentCameraSettingPage,
          "CAknTransparentCameraSettingPage::\
           CAknTransparentCameraSettingPage" );
    AssertNotNullL( transCameraSettingPage,
                    KTxtCAknTransparentCameraSettingPage );

    transCameraSettingPage->ConstructL();
    _LIT( KTxtConstructL, "CAknTransparentCameraSettingPage::ConstructL" );
    AssertTrueL( ETrue, KTxtConstructL );

    transCameraSettingPage->HandleControlEventL( iContainer,
                                    MCoeControlObserver::EEventStateChanged );
    _LIT( KTxtHandleControlEventL,
          "CAknTransparentCameraSettingPage::HandleControlEventL" );
    AssertTrueL( ETrue, KTxtHandleControlEventL );

    CleanupStack::Pop( transCameraSettingPage );
    transCameraSettingPage->ExecuteLD( CAknSettingPage::EUpdateWhenChanged, 
                                       ETrue );
    _LIT( KTxtExecuteLD, "CAknTransparentCameraSettingPage::ExecuteLD" );
    AssertTrueL( ETrue, KTxtExecuteLD );
    transCameraSettingPage = NULL;

    currentItem = 0;
    TInt setNum( 1 );
    transCameraSettingPage =
                     new( ELeave ) CBCTestCAknTransparentCameraSettingPage(
                                &KTitle,
                                setNum,
                                EAknSetListBox,
                                R_BCTESTDOMMIX50_TRANSPARENTCAMERA_LISTBOX,
                                R_BCTESTDOMMIX50_TRANSPARENTCAMERA_SETTING_PAGE,
                                currentItem,
                                array );

    CleanupStack::PushL( transCameraSettingPage );
    AssertNotNullL( transCameraSettingPage,
                    KTxtCAknTransparentCameraSettingPage );

    transCameraSettingPage->ConstructL();
    AssertTrueL( ETrue, KTxtConstructL );

    TKeyEvent keyEvent;
    keyEvent.iCode = 0;
    transCameraSettingPage->OfferKeyEventL( keyEvent, EEventKey );
    _LIT( KTxtOfferKeyEventL,
          "CAknTransparentCameraSettingPage::OfferKeyEventL" );
    AssertTrueL( ETrue, KTxtOfferKeyEventL );

    iEnv->EikAppUi()->AddToStackL( transCameraSettingPage );
    transCameraSettingPage->ProcessCommandL( EAknSoftkeyOptions );
    _LIT( KTxtProcessCommandL,
          "CAknTransparentCameraSettingPage::ProcessCommandL" );
    AssertTrueL( ETrue, KTxtProcessCommandL );
    iEnv->EikAppUi()->RemoveFromStack( transCameraSettingPage );

    CleanupStack::PopAndDestroy( transCameraSettingPage );
    CleanupStack::PopAndDestroy( array );
    }


// ---------------------------------------------------------------------------
// CBCTestDomMix50Case::TestCAknSingle2GraphicStyleListBoxCaseL()
// test for CAknSingle2GraphicStyleListBox/CAknSingle2GraphicListBoxItemDrawer
// ( menu item -6- )
// ---------------------------------------------------------------------------
//
void CBCTestDomMix50Case::TestCAknSingle2GraphicStyleListBoxCaseL()
    {
    CAknSingle2GraphicStyleListBox* single2GraphListBox =
                              new( ELeave ) CAknSingle2GraphicStyleListBox() ;
    CleanupStack::PushL( single2GraphListBox );
    _LIT( KTxtCAknSingle2GraphicStyleListBox, 
      "CAknDouble2GraphicLargeStyleListBox::CAknSingle2GraphicStyleListBox" );
    AssertNotNullL( single2GraphListBox, KTxtCAknSingle2GraphicStyleListBox );

    single2GraphListBox->CreateItemDrawerL();
    _LIT( KTxtCAknSingle2GraphicListBoxItemDrawer,
          "CAknSingle2GraphicListBoxItemDrawer::\
           CAknSingle2GraphicListBoxItemDrawer" );
    AssertTrueL( ETrue,
                 KTxtCAknSingle2GraphicListBoxItemDrawer );
    _LIT( KTxtCreateItemDrawerL, 
          "CAknDouble2GraphicLargeStyleListBox::CreateItemDrawerL" );
    AssertTrueL( ETrue, KTxtCreateItemDrawerL );

    single2GraphListBox->UseEmptyIconSpace( ETrue );
    single2GraphListBox->UseEmptyIconSpace( EFalse );
    _LIT( KTxtDrawerUseEmptyIconSpace, 
          "CAknSingle2GraphicListBoxItemDrawer::UseEmptyIconSpace" );
    AssertTrueL( ETrue, KTxtDrawerUseEmptyIconSpace );
    _LIT( KTxtUseEmptyIconSpace, 
          "CAknDouble2GraphicLargeStyleListBox::UseEmptyIconSpace" );
    AssertTrueL( ETrue, KTxtUseEmptyIconSpace );

    CleanupStack::PopAndDestroy( single2GraphListBox );
    }


// ---------------------------------------------------------------------------
// CBCTestDomMix50Case::TestCAknExtendedInputCapabilitiesCaseL()
// ( menu item -( 7 )- )
// ---------------------------------------------------------------------------
//
void CBCTestDomMix50Case::TestCAknExtendedInputCapabilitiesCaseL()
    {
    CAknExtendedInputCapabilities* extendedInputCapabilities =
        CAknExtendedInputCapabilities::NewLC();

    TBCTestAknEventObserver aknEventObserver;
    extendedInputCapabilities->RegisterObserver( &aknEventObserver );
    _LIT( KRegisterObserver, 
          "CAknExtendedInputCapabilities::RegisterObserver()" );
    AssertTrueL( ETrue, KRegisterObserver );

    extendedInputCapabilities->ReportEventL( 0, NULL );
    _LIT( KReportEventL, "CAknExtendedInputCapabilities::ReportEventL()" );
    AssertTrueL( ETrue, KReportEventL );

    extendedInputCapabilities->UnregisterObserver( &aknEventObserver );
    _LIT( KUnregisterObserver, 
          "CAknExtendedInputCapabilities::UnregisterObserver()" );
    AssertTrueL( ETrue, KUnregisterObserver );

    CAknExtendedInputCapabilities::\
    CAknExtendedInputCapabilitiesProvider* provider =
    new( ELeave )CAknExtendedInputCapabilities::\
        CAknExtendedInputCapabilitiesProvider;
    CleanupStack::PushL( provider );

    _LIT( KCAknExtendedInputCapabilitiesProvider, 
          "CAknExtendedInputCapabilities::\
           CAknExtendedInputCapabilitiesProvider()" );
    AssertTrueL( ETrue, KCAknExtendedInputCapabilitiesProvider );

    provider->ExtendedInputCapabilities();
    _LIT( KExtendedInputCapabilities, 
          "CAknExtendedInputCapabilitiesProvider::\
           ExtendedInputCapabilities()" );
    AssertTrueL( ETrue, KExtendedInputCapabilities );

    provider->SetExtendedInputCapabilities( extendedInputCapabilities );
    _LIT( KSetExtendedInputCapabilities, 
          "CAknExtendedInputCapabilitiesProvider::\
           SetExtendedInputCapabilities()" );
    AssertTrueL( ETrue, KSetExtendedInputCapabilities );

    provider->SetMopParent( NULL );
    _LIT( KSetMopParent,
          "CAknExtendedInputCapabilitiesProvider::SetMopParent()" );
    AssertTrueL( ETrue, KSetMopParent );

    CleanupStack::PopAndDestroy( provider );
    _LIT( KCAknExtendedInputCapabilitiesProviderDestruct, 
          "CAknExtendedInputCapabilitiesProvider::\
           ~CAknExtendedInputCapabilitiesProvider()" );
    AssertTrueL( ETrue, KCAknExtendedInputCapabilitiesProviderDestruct );

    CleanupStack::PopAndDestroy( extendedInputCapabilities );
    }
