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
* Description:  Screensaver slide set settings dialog.
*
*/


// General
#include <e32std.h>
#include <StringLoader.h>
#include <e32property.h>
#include <csxhelp/skins.hlp.hrh>

// From AVKON
#include <avkon.hrh>
#include <aknappui.h>
#include <aknslidersettingpage.h>
#include <AknsSrvClient.h>

// Screensaver PS keys.
#include <ScreensaverInternalPSKeys.h>

// Psln Slide set specific.
#include "pslnslidesetscreensaverdialog.h"
#include "pslnslidesetdialog.hrh"
#include "pslnslidesetmodel.h"
#include "pslnslidesetconst.h"

// Resources
#include <pslnslidesetdialogrsc.rsg>

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CPslnSlidesetScreensaverDialog::CPslnSlidesetScreensaverDialog()
    {
    }

// -----------------------------------------------------------------------------
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CPslnSlidesetScreensaverDialog::ConstructL()
    {
#ifndef RD_SLIDESHOW_SCREENSAVER
    User::Leave( KErrNotSupported );
#endif // RD_SLIDESHOW_SCREENSAVER
    BaseConstructL(
        GetDialogFlag( CPslnSlidesetDialogInterface::EPslnDialogType ) );

    iSlideSetTypeItems = iCoeEnv->ReadDesC16ArrayResourceL(
        R_PSLN_SLIDESET_TYPE_SS_SETTING_PAGE_LBX );
    }

// -----------------------------------------------------------------------------
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CPslnSlidesetScreensaverDialog* CPslnSlidesetScreensaverDialog::NewL()
    {
    CPslnSlidesetScreensaverDialog* self = NewLC();
    CleanupStack::Pop(); // Self
    return self;
    }

// -----------------------------------------------------------------------------
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CPslnSlidesetScreensaverDialog* CPslnSlidesetScreensaverDialog::NewLC()
    {
    CPslnSlidesetScreensaverDialog* self =
        new ( ELeave ) CPslnSlidesetScreensaverDialog();
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// Destructor
CPslnSlidesetScreensaverDialog::~CPslnSlidesetScreensaverDialog()
    {
    }

// -----------------------------------------------------------------------------
// Executes dialog.
// -----------------------------------------------------------------------------
//
TInt CPslnSlidesetScreensaverDialog::ExecuteDialogLD()
    {
    return CAknDialog::ExecuteLD( R_PSLN_SETTINGS_DIALOG );
    }

// -----------------------------------------------------------------------------
// Configures dialog.
// -----------------------------------------------------------------------------
//
void CPslnSlidesetScreensaverDialog::SetDialogFlag(
    const TInt aFlag, const TInt aValue )
    {
    switch( aFlag )
        {
        case CPslnSlidesetDialogInterface::EPslnConfigurability:
        case CPslnSlidesetDialogInterface::EPslnDialogType:
            // Cannot be changed dynamically.
            break;
        case CPslnSlidesetDialogInterface::EPslnLaunchMode:
            if ( aValue == CPslnSlidesetDialogInterface::EPslnNormal ||
                 aValue == CPslnSlidesetDialogInterface::EPslnConfigureOnly )
                {
                iLaunchMode = aValue;
                }
            break;
        default:
            break;
        }
    }

// -----------------------------------------------------------------------------
// Queries for dialog parameter.
// -----------------------------------------------------------------------------
//
TInt CPslnSlidesetScreensaverDialog::GetDialogFlag( const TInt aFlag )
    {
    TInt flagValue = KErrNotFound;
    switch( aFlag )
        {
        case CPslnSlidesetDialogInterface::EPslnDialogType:
            flagValue = EPslnScreensaverDialog;
            break;
        case CPslnSlidesetDialogInterface::EPslnLaunchMode:
            // Configuring Screensaver is handled using screensaver framework.
            flagValue = iLaunchMode;
            break;
        case CPslnSlidesetDialogInterface::EPslnConfigurability:
            // Activation is handled by screensaver framework and Psln application.
            flagValue = CPslnSlidesetDialogInterface::EPslnUnknown;
            break;
        default:
            break;
        }
    return flagValue;
    }

// -----------------------------------------------------------------------------
// Layouts dialog before showing it.
// -----------------------------------------------------------------------------
//
void CPslnSlidesetScreensaverDialog::PreLayoutDynInitL()
    {
    // Set title pane text.
    SetTitlePaneL( R_PSLN_SLIDESET_SCREENSAVER_DIALOG_TITLE );
    // Set middle softkey as Change.
    CPslnSlidesetDialog::SetMiddleSoftKeyLabelL(
        R_PSLN_MSK_CHANGE,
        EPslnCmdAppSetScreenSaver );
    CPslnSlidesetDialog::PreLayoutDynInitL();
    }

// -----------------------------------------------------------------------------
// Reimplements CAknDialog::OkToExitL inorder to indicate to the
// screensaver that new settings have been defined.
// -----------------------------------------------------------------------------
//
TBool CPslnSlidesetScreensaverDialog::OkToExitL( TInt aButtonId )
    {
    // Check if model indicates that setting values have been updated.
    if ( iModel->HasDialogUpdatedValues() )
        {
        TInt psValue = KErrNotFound;
        User::LeaveIfError(
            RProperty::Get(
                KPSUidScreenSaver,
                KScreenSaverPluginSettingsChanged,
                psValue ) );

        // If so, check P&S key.
        if ( psValue == EScreenSaverPluginSettingsChanging )
            {
            // If P&S key indicates that setting changes need to be
            // informed, do so.
            User::LeaveIfError(
                RProperty::Set(
                    KPSUidScreenSaver,
                    KScreenSaverPluginSettingsChanged,
                    EScreenSaverPluginSettingsChanged ) );
            }
        }
    return CPslnSlidesetDialog::OkToExitL( aButtonId );
    }

// -----------------------------------------------------------------------------
// Adds setting list items to listbox.
// -----------------------------------------------------------------------------
//
void CPslnSlidesetScreensaverDialog::CreateListBoxItemsL()
    {
    iItems = iCoeEnv->ReadDesC16ArrayResourceL(
        R_PSLN_SCREENSAVER_SLIDE_SETTING_LBX_ITEMS );
    CPslnSlidesetDialog::MakeItemL( EPslnSlideSetImagesId );
    CPslnSlidesetDialog::MakeItemL( EPslnSlideSetDurationId );
    
    if ( !IsFeatureSupported( EPslnSlideSetBacklightRemoved ) )
        {        
        CPslnSlidesetDialog::MakeItemL( EPslnSlideSetBacklightId );
        }
    }

// ---------------------------------------------------------------------------
// Gets help context for Help application.
// ---------------------------------------------------------------------------
//
void CPslnSlidesetScreensaverDialog::GetHelpContext(
    TCoeHelpContext& aContext ) const
    {
    aContext.iMajor = KUidPsln;
    aContext.iContext = KSKINS_HLP_SCREENS_SETTINGS;
    }

// ---------------------------------------------------------------------------
// Shows duration slider setting page.
// ---------------------------------------------------------------------------
//
void CPslnSlidesetScreensaverDialog::ShowDurationSliderL()
    {
    TInt currentValue = iModel->GetSlideSetDuration();

    // Retrieve title txt.
    HBufC* sliderTitle = StringLoader::LoadLC( R_PSLN_DURATION_SLIDE_PAGE_TITLE );

    // Instantiate setting page.
    CAknSliderSettingPage* dlg = new( ELeave ) CAknSliderSettingPage(
        sliderTitle,
        EAknSettingPageNoOrdinalDisplayed,
        EAknCtSlider,
        R_PSLN_DURATION_SLIDER,
        R_PSLN_IMAGE_SELECTION_SETTING_PAGE,
        currentValue );

    dlg->SetSettingId( EPslnSlideSetDurationId );
    dlg->SetSettingPageObserver( this );
    dlg->ExecuteLD( CAknSettingPage::EUpdateWhenChanged );
    // New value is stored in base class to CenRep.

    CleanupStack::PopAndDestroy( sliderTitle );
    }

// ---------------------------------------------------------------------------
// Shows backlight slider setting page.
// ---------------------------------------------------------------------------
//
void CPslnSlidesetScreensaverDialog::ShowBacklightSliderL()
    {
    // Empty implementation to be overloaded.
    TInt currentValue = iModel->GetSlideSetBacklight();

    // Retrieve title txt.
    HBufC* sliderTitle = StringLoader::LoadLC( R_PSLN_BACKLIGHT_SLIDE_PAGE_TITLE );

    CAknSliderSettingPage* dlg = new( ELeave ) CAknSliderSettingPage(
        sliderTitle,
        EAknSettingPageNoOrdinalDisplayed,
        EAknCtSlider,
        R_PSLN_BACKLIGHT_SLIDER,
        R_PSLN_IMAGE_SELECTION_SETTING_PAGE,
        currentValue );

    dlg->SetSettingId( EPslnSlideSetBacklightId );
    dlg->SetSettingPageObserver( this );
    dlg->ExecuteLD( CAknSettingPage::EUpdateWhenChanged );
    // New value is stored in base class to CenRep.

    CleanupStack::PopAndDestroy( sliderTitle );
    }

// End of File
