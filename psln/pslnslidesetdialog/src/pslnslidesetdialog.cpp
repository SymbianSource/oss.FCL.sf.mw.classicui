/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Slide set dialog base class.
*
*/


// General.
#include <e32std.h>
#include <barsread.h>
#include <data_caging_path_literals.hrh>
#include <hlplch.h>

// UI components.
#include <avkon.hrh>
#include <AknUtils.h>
#include <aknappui.h>
#include <aknnavi.h>
#include <akntitle.h>
#include <aknlists.h>
#include <aknradiobuttonsettingpage.h>
#include <aknslidersettingpage.h>
#include <AknsSrvClient.h>

#include <AknsWallpaperUtils.h>
#include <centralrepository.h>
#include <AknSkinsInternalCRKeys.h>

// Other services.
#include <MGFetch.h>
#include <StringLoader.h>
#include <featmgr.h>

// Psln slide set specific.
#include "pslnslidesetdialog.h"
#include "pslnslidesetmodel.h"
#include "pslnslidesetdrmverifier.h"
#include "pslnslidesetconst.h"

// Local resources and definitions.
#include "pslnslidesetdialog.hrh"
#include <pslnslidesetdialogrsc.rsg>
#include <bautils.h>

// CONSTANTS
// Image fetch granularity.
const TInt KPslnSlideSetImagesGranualarity = 6;
// Middle softkey command ID
const TInt KPslnMSKControlID = 3;
// Size of ending '\t' in string.
const TInt KPslnStringEndMarkSize = 2;
// Length of setting item value.
const TInt KPslnSettingItemLength = 64;

// Path to compiled resource file.
_LIT( KPslnSlideSetDialogResourceFileName,
     "z:pslnslidesetdialogrsc.rsc" );

// ============================ MEMBER FUNCTIONS ===============================

void CPslnSlidesetDialog::BaseConstructL( const TInt aType )
    {
    FeatureManager::InitializeLibL();

    // Validate type parameter.
    if ( aType != EPslnScreensaverDialog &&
         aType != EPslnWallpaperDialog )
        {
        User::Leave( KErrArgument );
        }
    iType = aType;

    iModel = CPslnSlideSetModel::NewL();
    // Feature support should only be read once. It should not change run-time.
    iModel->GetFeatureSupportL( iFeaturesSupport );

    // Find the resource file:
    TParse* parse = new (ELeave) TParse;
    CleanupStack::PushL( parse );
    parse->Set(
        KPslnSlideSetDialogResourceFileName,
        &KDC_RESOURCE_FILES_DIR, NULL );

    TFileName* fileName = new (ELeave) TFileName( parse->FullName() );
    CleanupStack::PushL( fileName );

    // Open resource file:
    RFs& fs = iEikonEnv->FsSession();
    BaflUtils::NearestLanguageFile( fs, *fileName );
    iResourceOffset = iEikonEnv->AddResourceFileL( *fileName );

    CleanupStack::PopAndDestroy( 2, parse );

    CAknDialog::ConstructL( R_PSLN_SLIDE_DIALOG_MENUBAR );

    // Remove tab group (if applicable).
    ToggleDefaultNaviPaneL( ETrue );

    // Retrieve previous title so that we can set it back when
    // dialog exits.
    if ( iAvkonAppUi )
        {
        CEikStatusPane* sp = iAvkonAppUi->StatusPane();
        if ( sp )
            {
            CAknTitlePane* title = static_cast<CAknTitlePane*>(
                sp->ControlL( TUid::Uid( EEikStatusPaneUidTitle ) ) );

            if ( title )
                {
                const TDesC* prevTitle = title->Text();
                iPreviousTitleTxt = prevTitle->AllocL();
                }
            }
        }
    iMGFetchRunning = EFalse;
    }

// -----------------------------------------------------------------------------
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CPslnSlidesetDialog::CPslnSlidesetDialog()
    {
    }

// Destructor
CPslnSlidesetDialog::~CPslnSlidesetDialog()
    {
    if ( this->IsFocused() )
        {
        CEikDialog::ButtonGroupContainer().RemoveCommandObserver( KPslnMSKControlID );
        }

    // Remove empty navi pane.
    TRAP_IGNORE( ToggleDefaultNaviPaneL( EFalse ) );

    iEikonEnv->EikAppUi()->RemoveFromStack( this );

    delete iListBox;
    delete iItems;
    delete iModel;
    delete iPreviousTitleTxt;
    delete iSlideSetTypeItems;

    if ( iResourceOffset != 0 )
        {
        iEikonEnv->DeleteResourceFile( iResourceOffset );
        }

    FeatureManager::UnInitializeLib();
    }

// ---------------------------------------------------------------------------
// Gets current item.
// ---------------------------------------------------------------------------
//
TInt CPslnSlidesetDialog::CurrentItemIndex() const
    {
    return iListBox->CurrentItemIndex();
    }

// ---------------------------------------------------------------------------
// Sets current item and re-draws the listbox.
// ---------------------------------------------------------------------------
//
void CPslnSlidesetDialog::SetCurrentItemIndexAndDraw( TInt aNewIndex )
    {
    if( ( aNewIndex >= 0 ) &&
        ( aNewIndex < iListBox->Model()->NumberOfItems() ) )
        {
        iListBox->SetCurrentItemIndexAndDraw( aNewIndex );
        }
    }

// ---------------------------------------------------------------------------
// Checks if feature is supported.
// ---------------------------------------------------------------------------
//
TBool CPslnSlidesetDialog::IsFeatureSupported( TInt aFeatureID )
    {
    if ( ( aFeatureID >= 0 ) && ( aFeatureID < KPslnMaxFeatureID ) )
        {
        return iFeaturesSupport.IsSet( aFeatureID );
        }
    else
        {
        // invalid feature value.
        return EFalse;
        }
    }

// ---------------------------------------------------------------------------
// Sets title pane text.
// ---------------------------------------------------------------------------
//
void CPslnSlidesetDialog::SetTitlePaneL( const TInt aResourceId )
    {
    CEikStatusPane* sp = iAvkonAppUi->StatusPane();
    CAknTitlePane* titlePane =
        static_cast<CAknTitlePane*> (
        sp->ControlL( TUid::Uid( EEikStatusPaneUidTitle ) ) );
    if ( titlePane )
        {
        HBufC* titleBuf = StringLoader::LoadLC( aResourceId );
        titlePane->SetTextL( *titleBuf );
        CleanupStack::PopAndDestroy( titleBuf );
        }
    }

// ---------------------------------------------------------------------------
// Creates a specific setting item.
// ---------------------------------------------------------------------------
//
void CPslnSlidesetDialog::MakeItemL( const TInt aIndex )
    {
    // Check that parameter is valid.
    if ( aIndex > iItems->Count() || aIndex < 0 )
        {
        User::Leave( KErrArgument );
        }
    TInt currentValue = KErrNotFound;
    switch( aIndex )
        {
        case EPslnSlideSetImagesId:
            {
            if ( IsFeatureSupported( EPslnSlideSetFeatureRandom ) &&
                 ( iType == EPslnScreensaverDialog ) )
                {
                currentValue = iModel->GetSlideSetType( iType );
                SetSettingPageValueToListL(
                    *iSlideSetTypeItems,
                    aIndex,
                    currentValue,
                    EFalse );
                }
            else
                {
                // Get number of images.
                HBufC* item = (*iItems)[aIndex].AllocL();
                TInt slideSetFileType = EAknsSrvInifileSSWP;
                if ( iType == EPslnScreensaverDialog )
                    {
                    slideSetFileType = EAknsSrvInifileSSSS;
                    }
                currentValue =
                    iModel->GetImageCountInSlideSetL( slideSetFileType );

                // If there are images already selected, the number of images
                // needs to be shown in the setting page.
                if ( currentValue > 0 )
                    {
                    TInt resourceId =
                        SelectResourceStringForImages( currentValue );
                    HBufC* valueStr = NULL;
                // Use singular form, if only one image.
                    if ( currentValue == 1 )
                        {
                        valueStr = StringLoader::LoadLC( resourceId );
                        }
                // Otherwise plural.
                    else
                        {
                        valueStr = StringLoader::LoadLC(
                            resourceId,
                            currentValue );
                        }
                    // for A&H number conversion
                    TPtr bufPtr = valueStr->Des();
                    if( AknTextUtils::DigitModeQuery(
                        AknTextUtils::EDigitModeShownToUser ) )
                        {
                        AknTextUtils::LanguageSpecificNumberConversion( bufPtr );
                        }
                    // make room for value and end mark.
                    item = item->ReAllocL(
                        item->Length() +
                        bufPtr.Length() +
                        KPslnStringEndMarkSize );
                    TPtr expandedPtr = item->Des();
                    expandedPtr.Insert( item->Length(), bufPtr );
                    CleanupStack::PopAndDestroy( valueStr );
                    }
                else
                	{
                	if ( iType == EPslnWallpaperDialog )
                		{
                		TInt type = KErrNone;
						CRepository* rep = CRepository::NewL( KCRUidPersonalisation );
						rep->Get( KPslnWallpaperType,type );
						const TInt SlideSetWPType = 2;
						if ( type == SlideSetWPType )
							{
							AknsWallpaperUtils::SetIdleWallpaper( KNullDesC, NULL );
							}
						delete rep;
                		}
                	}
                CleanupStack::PushL( item );
                TPtr ptr = item->Des();
                iItemArray->InsertL( aIndex, ptr );
                CleanupStack::PopAndDestroy( item );
                }
            }
            break;
        case EPslnSlideSetDurationId:
            {
            if ( iType == EPslnScreensaverDialog )
                {
                currentValue = iModel->GetSlideSetDuration();

                SetSliderValueToListL(
                    aIndex,
                    currentValue,
                    R_PSLN_DURATION_SLIDER );
                }
            else
                {
                currentValue = iModel->GetSlideSetInterval();

                // Last parameter is whether or not A&H numeric conversion should be done.
                SetSettingPageValueToListL(
                    *iIntervalItems,
                    aIndex,
                    currentValue,
                    ETrue );
                }
            }
            break;
        case EPslnSlideSetBacklightId:
            {
            currentValue = iModel->GetSlideSetBacklight();

            SetSliderValueToListL(
                aIndex,
                currentValue,
                R_PSLN_BACKLIGHT_SLIDER );
            }
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// Sets middle softkey label.
// ---------------------------------------------------------------------------
//
void CPslnSlidesetDialog::SetMiddleSoftKeyLabelL(
    const TInt aResourceId, const TInt aCommandId )
    {
    HBufC* middleSKText = StringLoader::LoadLC( aResourceId );
    TPtr mskPtr = middleSKText->Des();
    CEikDialog::ButtonGroupContainer().AddCommandToStackL(
        KPslnMSKControlID,
        aCommandId,
        mskPtr );
    CEikDialog::ButtonGroupContainer().UpdateCommandObserverL(
        KPslnMSKControlID,
        *this );
    CleanupStack::PopAndDestroy( middleSKText );
    }

// -----------------------------------------------------------------------------
// Layouts dialog before it is visible.
// -----------------------------------------------------------------------------
//
void CPslnSlidesetDialog::PreLayoutDynInitL()
    {
    iEikonEnv->EikAppUi()->AddToStackL( this, ECoeStackPriorityDialog );
    CreateSettingsListL();
    CEikDialog::PreLayoutDynInitL();
    }

// -----------------------------------------------------------------------------
// Reimplements CAknDialog::ProcessCommandL inorder to handle dialog menu
// commands.
// -----------------------------------------------------------------------------
//
void CPslnSlidesetDialog::ProcessCommandL( TInt aCommandId )
    {
    CAknDialog::ProcessCommandL( aCommandId );
    switch ( aCommandId )
        {
        case EPslnCmdAppSetWallpaper: // Fallthrough
        case EPslnCmdAppSetScreenSaver: // Fallthrough
        case EPslnSlideSetCmdChange:
            if ( iListBox )
                {
                HandleListBoxSelectionL();
                }
            break;
        case EAknCmdHelp:
            HlpLauncher::LaunchHelpApplicationL( iEikonEnv->WsSession(),
                iAvkonAppUi->AppHelpContextL() );
            break;
        case EAknSoftkeyBack: // -Fallthrough
            // Remove empty navi pane.
            ToggleDefaultNaviPaneL( EFalse );
        case EEikCmdExit: // -Fallthrough
        case EAknCmdExit:
            // Close this dialog
            TryExitL( aCommandId );
            iAvkonAppUi->ProcessCommandL( aCommandId );
            break;
        default:
            break;
        }
    }

// -----------------------------------------------------------------------------
// Reimplements CAknDialog::OkToExitL.
// -----------------------------------------------------------------------------
//
TBool CPslnSlidesetDialog::OkToExitL( TInt aButtonId )
    {
    //Check if MGFetch is running.
    if( iMGFetchRunning )
        {
        return EFalse;
        }

    if ( iPreviousTitleTxt &&
         iPreviousTitleTxt->Length() > 0 &&
         aButtonId != EAknSoftkeyOptions )
        {
        if ( iAvkonAppUi )
            {
            CEikStatusPane* sp = iAvkonAppUi->StatusPane();
            if ( sp )
                {
                CAknTitlePane* title = static_cast<CAknTitlePane*>(
                    sp->ControlL( TUid::Uid( EEikStatusPaneUidTitle ) ) );

                if ( title )
                    {
                    title->SetTextL( *iPreviousTitleTxt );
                    }
                }
            }
        }
    return CAknDialog::OkToExitL( aButtonId );
    }

// -----------------------------------------------------------------------------
// Reimplements CAknDialog::DynInitMenuPaneL inorder to support dynamic hiding
// of menu items based on current state of the viewer.
// -----------------------------------------------------------------------------
//
void CPslnSlidesetDialog::DynInitMenuPaneL(
    TInt aResourceId, CEikMenuPane* aMenuPane )
    {
    if ( aResourceId == R_PSLN_SLIDE_DIALOG_MENU &&
         !FeatureManager::FeatureSupported( KFeatureIdHelp ) )
        {
        // Disable help if not supported
        aMenuPane->SetItemDimmed( EAknCmdHelp, ETrue );
        }
    }

// -----------------------------------------------------------------------------
// Reimplements CAknDialog::SizeChanged inorder to support the resize of the
// dialog when functions such as SetRect, SetExtent are called on the dialog.
// -----------------------------------------------------------------------------
//
void CPslnSlidesetDialog::SizeChanged()
    {
    CAknDialog::SizeChanged();
    if ( iListBox )
        {
        // Get size from main pane, place from this rect
        TRect mainPaneRect;
        AknLayoutUtils::LayoutMetricsRect(
            AknLayoutUtils::EMainPane,
            mainPaneRect );

        iListBox->SetExtent( Rect().iTl, mainPaneRect.Size() );
        }
    }

// -----------------------------------------------------------------------------
// Handles Key events by reimplementing CCoeControl::OfferKeyEventL.
// -----------------------------------------------------------------------------
//
TKeyResponse CPslnSlidesetDialog::OfferKeyEventL( const TKeyEvent& aKeyEvent,
    TEventCode aType )
    {
    switch ( aKeyEvent.iCode )
        {
        case EKeyLeftArrow: // -Fallthrough
        case EKeyRightArrow:
            // Listbox takes all event even if it doesn't use them
            if ( !iMGFetchRunning )
                {
                return EKeyWasConsumed;
                }
            break;
        default:
            break;
        }
    // If MGFetch is running, do not give key events to listbox.
    if ( iListBox && !iMGFetchRunning )
        {
        iListBox->OfferKeyEventL( aKeyEvent, aType );
        }
    return CAknDialog::OfferKeyEventL( aKeyEvent, aType );
    }

// -----------------------------------------------------------------------------
// Handles setting page events.
// -----------------------------------------------------------------------------
//
void CPslnSlidesetDialog::HandleSettingPageEventL(
        CAknSettingPage* aSettingPage,
        TAknSettingPageEvent aEventType )
    {
    TInt settingPageId = aSettingPage->SettingId();
    TInt current = KErrNotFound;
    if ( aEventType == EEventSettingOked )
        {
        switch( settingPageId )
            {
            case EPslnSlideSetImagesId:
                if ( IsFeatureSupported( EPslnSlideSetFeatureRandom ) )
                    {
                    current = static_cast<CAknRadioButtonSettingPage*>(
                        aSettingPage)->ListBoxControl()->CurrentItemIndex();
                    // If images is selected, start MGFetch.
                    if ( current != KPslnSlideSetRandomIndex )
                        {
                        HandleLaunchMGFetchL();
                        }
                    else
                        {
                        iModel->SetSlideSetType( iType, current );
                        }
                    }
                break;

            case EPslnSlideSetDurationId:
                current = static_cast<CAknSliderSettingPage*>
                    (aSettingPage)->SliderControl()->Value();
                iModel->SetSlideSetDuration( current );
                break;
            case EPslnSlideSetBacklightId:
                current = static_cast<CAknSliderSettingPage*>
                    (aSettingPage)->SliderControl()->Value();
                iModel->SetSlideSetBacklight( current );
                break;
            case EPslnSlideSetIntervalId:
                current = static_cast<CAknRadioButtonSettingPage*>(
                    aSettingPage)->ListBoxControl()->CurrentItemIndex();
                iModel->SetSlideSetInterval( current );
                // interval is regarded as duration
                settingPageId = EPslnSlideSetDurationId;
                break;
            default:
                break;
            }
        UpdateDialogL( settingPageId );
        }
    }

// -----------------------------------------------------------------------------
// Handles change of skin/Layout
// -----------------------------------------------------------------------------
//
void CPslnSlidesetDialog::HandleResourceChange( TInt aType )
    {
    CAknDialog::HandleResourceChange( aType );
    if ( iListBox )
        {
        iListBox->HandleResourceChange( aType );
        }
    }

// ---------------------------------------------------------------------------
// Handles list animation events.
// ---------------------------------------------------------------------------
//
void CPslnSlidesetDialog::FocusChanged( TDrawNow aDrawNow )
    {
    CAknDialog::FocusChanged( aDrawNow );
    if( iListBox )
        {
        iListBox->SetFocus( IsFocused(), aDrawNow );
        }
    }

// ---------------------------------------------------------------------------
// Count components.
// ---------------------------------------------------------------------------
//
TInt CPslnSlidesetDialog::CountComponentControls() const
    {
    return iListBox ? 1 : 0;
    }

// ---------------------------------------------------------------------------
// Give pointer to component matching to the index.
// ---------------------------------------------------------------------------
//
CCoeControl* CPslnSlidesetDialog::ComponentControl( TInt aIndex ) const
    {
    return ( aIndex == 0 ) ? iListBox : NULL;
    }

// ---------------------------------------------------------------------------
// Handle listbox event.
// ---------------------------------------------------------------------------
//
void CPslnSlidesetDialog::HandleListBoxEventL(
    CEikListBox* /*aListBox*/, TListBoxEvent aEventType )
    {
    switch ( aEventType )
        {
        case EEventEnterKeyPressed: // Fallthrough
        case EEventItemDoubleClicked:
        case EEventItemSingleClicked:
            HandleListBoxSelectionL();
            break;
        default:
           break;
        }
    }

// -----------------------------------------------------------------------------
// Create setting items.
// -----------------------------------------------------------------------------
//
void CPslnSlidesetDialog::CreateSettingsListL()
    {
    // Create settings listbox.
    iListBox = new (ELeave) CAknSettingStyleListBox;
    iListBox->ConstructL( this, EAknListBoxSelectionList );

    // Create listbox items.
    iItemArray = static_cast<CDesCArray*>
        ( iListBox->Model()->ItemTextArray() );
    iListBox->SetContainerWindowL( *this );
    iListBox->Model()->SetOwnershipType( ELbmOwnsItemArray );

    iListBox->CreateScrollBarFrameL( ETrue );
    iListBox->ScrollBarFrame()->SetScrollBarVisibilityL(
        CEikScrollBarFrame::EOff,
        CEikScrollBarFrame::EAuto );
    iListBox->SetListBoxObserver( this );
    iListBox->SetMopParent( this );
    iListBox->MakeVisible( ETrue );

    CreateListBoxItemsL();
    iListBox->HandleItemAdditionL();

    SetRect( iAvkonAppUi->ClientRect() );
    ActivateL();
    }

// ---------------------------------------------------------------------------
// CPslnSlidesetDialog::HandleListBoxSelectionL()
// ---------------------------------------------------------------------------
//
void CPslnSlidesetDialog::HandleListBoxSelectionL()
    {
     TInt index = iListBox->CurrentItemIndex();

     switch ( index )
        {
        case EPslnSlideSetImagesId:
            if( iMGFetchRunning )
                {
                return;
                }
            if ( IsFeatureSupported( EPslnSlideSetFeatureRandom ) 
                && ( iType == EPslnScreensaverDialog ) )
                {
                ShowSlideSetTypeSelectionL();
                }
            else
                {
                ShowSlideSetImageListL();
                }
            break;
        case EPslnSlideSetDurationId:
            if ( iType == EPslnScreensaverDialog )
                {
                ShowDurationSliderL();
                }
            else
                {
                ShowIntervalListL();
                }
            break;
        case EPslnSlideSetBacklightId:
            ShowBacklightSliderL();
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// Show slide set type setting page. Since it is used by both slide sets
// (wallpaper and screen saver), the default implementation is in the base
// class.
// ---------------------------------------------------------------------------
//
void CPslnSlidesetDialog::ShowSlideSetTypeSelectionL()
    {
    // Retrieve title txt.
    TInt titleResourceID = R_PSLN_IMAGES_SLIDE_SS_PAGE_TITLE;
    if ( iType != EPslnScreensaverDialog )
        {
        titleResourceID = R_PSLN_IMAGES_SLIDE_WP_PAGE_TITLE;
        }
    HBufC* titleText = StringLoader::LoadLC( titleResourceID );

    // Retrieve current setting page value.
    TInt currentValue = iModel->GetSlideSetType( iType );

    // Create & show the setting page.
    CAknRadioButtonSettingPage* dlg =
        new( ELeave ) CAknRadioButtonSettingPage(
            titleText,
            EAknSettingPageNoOrdinalDisplayed,
            EAknCtSettingPage,
            0,
            R_PSLN_IMAGE_SELECTION_SETTING_PAGE,
            currentValue,
            iSlideSetTypeItems );
    dlg->SetSettingId( EPslnSlideSetImagesId );
    dlg->SetSettingPageObserver( this );
    dlg->ExecuteLD( CAknSettingPage::EUpdateWhenAccepted );

    CleanupStack::PopAndDestroy( titleText );
    }

// ---------------------------------------------------------------------------
// Shows backlight slider setting page.
// ---------------------------------------------------------------------------
//
void CPslnSlidesetDialog::ShowBacklightSliderL()
    {
    // Empty implementation to be overloaded.
    }

// ---------------------------------------------------------------------------
// Shows duration slider setting page.
// ---------------------------------------------------------------------------
//
void CPslnSlidesetDialog::ShowDurationSliderL()
    {
    // Empty implementation to be overloaded.
    }

// ---------------------------------------------------------------------------
// Show wallpaper slide set's interval selection.
// ---------------------------------------------------------------------------
//
void CPslnSlidesetDialog::ShowIntervalListL()
    {
    // Empty implementation to be overloaded.
    }

// ---------------------------------------------------------------------------
// Starts image fetch.
// ---------------------------------------------------------------------------
//
TBool CPslnSlidesetDialog::ShowSlideSetImageListL()
    {
    CDesCArrayFlat* files =
        new (ELeave) CDesCArrayFlat( KPslnSlideSetImagesGranualarity );
    CleanupStack::PushL( files );

    CPslnSlideSetDRMVerifier* verifier = CPslnSlideSetDRMVerifier::NewL( iType );
    CleanupStack::PushL( verifier );

    iMGFetchRunning = ETrue;
    TBool selected = EFalse;
    TRAPD( err,selected = MGFetch::RunL( *files, EImageFile, ETrue, verifier ) );
    iMGFetchRunning = EFalse;
    User::LeaveIfError( err );
    CleanupStack::PopAndDestroy( verifier );

    // Handle selection
    if ( selected && ( files->MdcaCount() > 0 ) )
        {
        iModel->SetImageListL( iType, *files, iLaunchMode );
        iModel->SetSlideSetType( iType, 0 );
        UpdateDialogL( EPslnSlideSetImagesId );
        }
    // else - either: User made a selection, but all the images had issues with DRM.
    // or: MGFetch was cancelled
    else
        {
        selected = EFalse;
        }

    CleanupStack::PopAndDestroy( files );
    return selected;
    }

// ---------------------------------------------------------------------------
// Toggles navi pane to default and back.
// ---------------------------------------------------------------------------
//
#ifdef RD_CONTROL_PANEL
void CPslnSlidesetDialog::ToggleDefaultNaviPaneL( const TBool /*aNaviPaneToggle*/ )
#else
void CPslnSlidesetDialog::ToggleDefaultNaviPaneL( const TBool aNaviPaneToggle )
#endif // RD_CONTROL_PANEL
    {
    // Remove tab group (if applicable).
    CEikStatusPane* sp = iAvkonAppUi->StatusPane();
    // Fetch pointer to the default navi pane control
    CAknNavigationControlContainer* naviPane =
        (CAknNavigationControlContainer*)sp->ControlL(
            TUid::Uid(EEikStatusPaneUidNavi));
    // Show again previous navipane
    if ( naviPane )
        {
#ifndef RD_CONTROL_PANEL
        if ( !aNaviPaneToggle )
            {
            naviPane->Pop();
            }
        // Show default navi pane.
        else
#endif // !RD_CONTROL_PANEL
            {
            naviPane->PushDefaultL();
            }
        }
    }

// -----------------------------------------------------------------------------
// Updates dialog based on new value of setting item.
// -----------------------------------------------------------------------------
//
void CPslnSlidesetDialog::UpdateDialogL( const TInt aSettingId )
    {
    if ( aSettingId >= 0 &&
         aSettingId < iItemArray->Count() )
        {
        iItemArray->Delete( aSettingId );
        MakeItemL( aSettingId );
        iListBox->HandleItemAdditionL();
        }
    }

// -----------------------------------------------------------------------------
// Updates dialog based on new value of setting item.
// -----------------------------------------------------------------------------
//
void CPslnSlidesetDialog::SetSettingPageValueToListL(
        const CDesCArrayFlat& aArray,
        const TInt aCurrentIndex,
        const TInt aCurrentValue,
        const TBool aNumericConversionNeeded )
    {
    if ( aCurrentIndex >= iItems->Count() )
        {
        User::Leave( KErrArgument );
        }
    HBufC* item = (*iItems)[aCurrentIndex].AllocL();
    HBufC* settingItemValue = HBufC::NewLC( KPslnSettingItemLength );
    TPtr valuePtr ( settingItemValue->Des() );
    valuePtr = aArray[ aCurrentValue ];

    // A&H conversion.
    if( aNumericConversionNeeded &&
        AknTextUtils::DigitModeQuery( AknTextUtils::EDigitModeShownToUser ) )
        {
        AknTextUtils::LanguageSpecificNumberConversion( valuePtr );
        }

    // Re-allocate string, so that setting item name and current value fit.
    item = item->ReAllocL(
        item->Length() + valuePtr.Length() + KPslnStringEndMarkSize );
    TPtr expandedPtr = item->Des();

    expandedPtr.Insert( item->Length(), valuePtr );
    CleanupStack::PopAndDestroy( settingItemValue );
    CleanupStack::PushL( item );

    TPtr ptr = item->Des();
    iItemArray->InsertL( aCurrentIndex, ptr );
    CleanupStack::PopAndDestroy( item );
    }

// -----------------------------------------------------------------------------
// Updates dialog based on new value of setting item.
// -----------------------------------------------------------------------------
//
void CPslnSlidesetDialog::SetSliderValueToListL(
        const TInt aCurrentIndex,
        const TInt aCurrentValue,
        const TInt aResourceID )
    {
    if ( aCurrentIndex >= iItems->Count() )
        {
        User::Leave( KErrArgument );
        }

    HBufC* item = (*iItems)[aCurrentIndex].AllocL();
    // If minimum value for backlight, use "Off".
    if ( aResourceID == R_PSLN_BACKLIGHT_SLIDER && aCurrentValue == 0 )
        {
        HBufC* settingItem = StringLoader::LoadLC( R_PSLN_SANIM_SLIDER_OFF );
        TPtr bufPtr = settingItem->Des();
        item = item->ReAllocL(
            item->Length() + bufPtr.Length() + KPslnStringEndMarkSize );
        TPtr expandedPtr = item->Des();

        expandedPtr.Insert( item->Length(), bufPtr );
        CleanupStack::PopAndDestroy( settingItem );

        }
    else
        {
        HBufC* settingItem = CAknSlider::CreateValueTextInHBufCL(
                      aCurrentValue,
                      aResourceID );
        CleanupStack::PushL( settingItem );

        // for A&H number conversion
        TPtr bufPtr = settingItem->Des();
        if( AknTextUtils::DigitModeQuery( AknTextUtils::EDigitModeShownToUser ) )
            {
            AknTextUtils::LanguageSpecificNumberConversion( bufPtr );
            }
        item = item->ReAllocL(
            item->Length() + bufPtr.Length() + KPslnStringEndMarkSize );
        TPtr expandedPtr = item->Des();

        expandedPtr.Insert( item->Length(), bufPtr );
        CleanupStack::PopAndDestroy( settingItem );
        }
    CleanupStack::PushL( item );
    TPtr ptr = item->Des();
    iItemArray->InsertL( aCurrentIndex, ptr );
    CleanupStack::PopAndDestroy( item );
    }

// -----------------------------------------------------------------------------
// Select appropriate resource text for setting item value.
// -----------------------------------------------------------------------------
//
TInt CPslnSlidesetDialog::SelectResourceStringForImages( TInt aCurrentValue )
    {
    TInt resourceId = R_PSLN_SLIDE_SET_WP_IMAGES;
    if ( aCurrentValue == 1 )
        {
        if ( iType == EPslnScreensaverDialog )
            {
            resourceId = R_PSLN_SLIDE_SET_SS_IMAGE;
            }
        else
            {
            resourceId = R_PSLN_SLIDE_SET_WP_IMAGE;
            }
        }
    else
        {
        if ( iType == EPslnScreensaverDialog )
            {
            resourceId = R_PSLN_SLIDE_SET_SS_IMAGES;
            }
        }
    return resourceId;
    }

// -----------------------------------------------------------------------------
// Handles idle time. Starts MGFetch.
// -----------------------------------------------------------------------------
//
void CPslnSlidesetDialog::HandleLaunchMGFetchL()
    {
    TBool selected = ShowSlideSetImageListL();
    if ( !selected )
        {
        ShowSlideSetTypeSelectionL();
        }
    }

// End of File
