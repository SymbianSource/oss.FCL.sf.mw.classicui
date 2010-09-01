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
* Description:  Wallpaper slide set setting dialog.
*
*/


// General
#include <e32std.h>
#include <StringLoader.h>
#include <csxhelp/skins.hlp.hrh>

// Central repository.
#include <centralrepository.h>
#include <AknSkinsInternalCRKeys.h>
#include <pslninternalcrkeys.h>

// From AVKON
#include <avkon.hrh>
#include <aknappui.h>
#include <aknradiobuttonsettingpage.h>
#include <AknsSrvClient.h>

// Psln Slide set specific.
#include "pslnslidesetwallpaperdialog.h"
#include "pslnslidesetdialog.hrh"
#include "pslnslidesetmodel.h"
#include "pslnslidesetconst.h"

// Resources
#include <pslnslidesetdialogrsc.rsg>

const TInt KPslnSsSettingsItemArray = 6;
const TInt KPslnSsSlideSetType = 2;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CPslnWallpaperSlidesetDialog::CPslnWallpaperSlidesetDialog()
    {
    }

// -----------------------------------------------------------------------------
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CPslnWallpaperSlidesetDialog::ConstructL()
    {
#ifndef RD_SLIDESHOW_WALLPAPER
    User::Leave( KErrNotSupported );
#endif // RD_SLIDESHOW_WALLPAPER
    BaseConstructL(
        GetDialogFlag( CPslnSlidesetDialogInterface::EPslnDialogType ) );

    iSlideSetTypeItems = iCoeEnv->ReadDesC16ArrayResourceL(
        R_PSLN_SLIDESET_TYPE_WP_SETTING_PAGE_LBX );

    // Add each line separately, since it needs language-dependant conversion.
    iIntervalItems = new( ELeave ) CDesCArrayFlat( KPslnSsSettingsItemArray );
    AppendIntervalItemL( R_PSLN_SLIDESET_INTERVAL_1_MINUTE );
    AppendIntervalItemL( R_PSLN_SLIDESET_INTERVAL_10_MINUTE );
    AppendIntervalItemL( R_PSLN_SLIDESET_INTERVAL_30_MINUTE );
    AppendIntervalItemL( R_PSLN_SLIDESET_INTERVAL_1_HOUR );
    AppendIntervalItemL( R_PSLN_SLIDESET_INTERVAL_1_DAY );
    }

// -----------------------------------------------------------------------------
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CPslnWallpaperSlidesetDialog* CPslnWallpaperSlidesetDialog::NewL()
    {
    CPslnWallpaperSlidesetDialog* self = NewLC();
    CleanupStack::Pop(); // Self
    return self;
    }

// -----------------------------------------------------------------------------
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CPslnWallpaperSlidesetDialog* CPslnWallpaperSlidesetDialog::NewLC()
    {
    CPslnWallpaperSlidesetDialog* self =
        new ( ELeave ) CPslnWallpaperSlidesetDialog();
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// Destructor
CPslnWallpaperSlidesetDialog::~CPslnWallpaperSlidesetDialog()
    {
    // base class destroys iSlideSetTypeItems.
    delete iIntervalItems;
    }

// -----------------------------------------------------------------------------
// Executes dialog.
// -----------------------------------------------------------------------------
//
TInt CPslnWallpaperSlidesetDialog::ExecuteDialogLD()
    {
    return CAknDialog::ExecuteLD( R_PSLN_SETTINGS_DIALOG );
    }

// -----------------------------------------------------------------------------
// Configures dialog.
// -----------------------------------------------------------------------------
//
void CPslnWallpaperSlidesetDialog::SetDialogFlag(
    const TInt aFlag, const TInt aValue )
    {
    switch( aFlag )
        {
        case CPslnSlidesetDialogInterface::EPslnDialogType:
            // Cannot be changed.
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
// Queries for dialog parameters.
// -----------------------------------------------------------------------------
//
TInt CPslnWallpaperSlidesetDialog::GetDialogFlag( const TInt aFlag )
    {
    TInt flagValue = KErrNotFound;
    switch( aFlag )
        {
        case CPslnSlidesetDialogInterface::EPslnDialogType:
            flagValue = EPslnWallpaperDialog;
            break;
        case CPslnSlidesetDialogInterface::EPslnLaunchMode:
            flagValue = iLaunchMode;
            break;
        case CPslnSlidesetDialogInterface::EPslnConfigurability:
            TRAP_IGNORE( flagValue = DeduceActivationModeL() );
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
void CPslnWallpaperSlidesetDialog::PreLayoutDynInitL()
    {
    // Set title pane text.
    SetTitlePaneL( R_PSLN_SLIDESET_WALLPAPER_DIALOG_TITLE );
    // Set middle softkey as Change.
    CPslnSlidesetDialog::SetMiddleSoftKeyLabelL(
        R_PSLN_MSK_CHANGE,
        EPslnCmdAppSetWallpaper );
    CPslnSlidesetDialog::PreLayoutDynInitL();
    }

// -----------------------------------------------------------------------------
// Process command.
// -----------------------------------------------------------------------------
//
void CPslnWallpaperSlidesetDialog::ProcessCommandL( TInt aCommandId )
    {
    CPslnSlidesetDialog::ProcessCommandL( aCommandId );
    }

// -----------------------------------------------------------------------------
// Reimplements CAknDialog::OkToExitL.
// Possibly stores wallpaper type to cenrep.
// -----------------------------------------------------------------------------
//
TBool CPslnWallpaperSlidesetDialog::OkToExitL( TInt aButtonId )
    {
    if ( CPslnSlidesetDialog::IsFeatureSupported( EPslnSlideSetFeatureRandom ) )
        {
        CRepository* repository = CRepository::NewL( KCRUidThemes );
        TInt slideSetType = KErrNotFound;
        repository->Get( KThemesWallpaperSlideSetType, slideSetType );
        delete repository;
        // If Random is selected, then set slide type wallpaper active.
        if ( ( slideSetType == KPslnSlideSetRandomIndex ) &&
             ( iLaunchMode == CPslnSlidesetDialogInterface::EPslnNormal ) )
            {
            CRepository* repository2 =
                CRepository::NewL( KCRUidPersonalisation );
            repository2->Set(
                KPslnWallpaperType,
                KPslnSsSlideSetType );
            delete repository2;
            }
        }
    return CPslnSlidesetDialog::OkToExitL( aButtonId );
    }


// -----------------------------------------------------------------------------
// Adds setting list items to listbox.
// -----------------------------------------------------------------------------
//
void CPslnWallpaperSlidesetDialog::CreateListBoxItemsL()
    {
    iItems = iCoeEnv->ReadDesC16ArrayResourceL(
        R_PSLN_WALLPAPER_SLIDE_SETTING_LBX_ITEMS );
    CPslnSlidesetDialog::MakeItemL( EPslnSlideSetImagesId );
    CPslnSlidesetDialog::MakeItemL( EPslnSlideSetDurationId ); // regard as interval
    }

// ---------------------------------------------------------------------------
// Gets help context for Help application.
// ---------------------------------------------------------------------------
//
void CPslnWallpaperSlidesetDialog::GetHelpContext(
    TCoeHelpContext& aContext ) const
    {
    aContext.iMajor = KUidPsln;
    aContext.iContext = KSCREENSAVER_HLP_WP_SETTINGS;
    }

// -----------------------------------------------------------------------------
// Show slide set image interval peridod setting page.
// -----------------------------------------------------------------------------
//
void CPslnWallpaperSlidesetDialog::ShowIntervalListL()
    {
    // Retrieve title txt.
    TInt titleResourceID = R_PSLN_INTERVAL_SLIDE_PAGE_TITLE;
    HBufC* titleText = StringLoader::LoadLC( titleResourceID );

    // Retrieve current setting page value.
    TInt currentValue = iModel->GetSlideSetInterval();

    // Create & show the setting page.
    CAknRadioButtonSettingPage* dlg =
        new( ELeave ) CAknRadioButtonSettingPage(
            titleText,
            EAknSettingPageNoOrdinalDisplayed,
            EAknCtSettingPage,
            0,
            R_PSLN_IMAGE_SELECTION_SETTING_PAGE,
            currentValue,
            iIntervalItems );
    dlg->SetSettingId( EPslnSlideSetIntervalId );
    dlg->SetSettingPageObserver( this );
    dlg->ExecuteLD( CAknSettingPage::EUpdateWhenAccepted );
    // Base class stores new value to CenRep.

    CleanupStack::PopAndDestroy( titleText );
    }

// -----------------------------------------------------------------------------
// Deduce if the slide set can be activated without showing the dialog.
// -----------------------------------------------------------------------------
//
TInt CPslnWallpaperSlidesetDialog::DeduceActivationModeL()
    {
    TInt retValue = CPslnSlidesetDialogInterface::EPslnNeedsToBeConfigured;
    if ( CPslnSlidesetDialog::IsFeatureSupported( EPslnSlideSetFeatureRandom ) )
        {
        CRepository* repository = CRepository::NewL( KCRUidThemes );
        TInt slideSetType = KErrNotFound;
        repository->Get( KThemesWallpaperSlideSetType, slideSetType );
        delete repository;
        // If selection type is set to random, then direct activation
        // is possible.
        if ( slideSetType == KPslnSlideSetRandomIndex )
            {
            return CPslnSlidesetDialogInterface::EPslnDirectActivationPossible;
            }
        }
    // If slide set image list file exists, direct activation is allowed.
    if ( iModel->SlideSetImageFileExistsL( EAknsSrvInifileSSWP ) &&
         iModel->GetImageCountInSlideSetL( EAknsSrvInifileSSWP ) > 1 )
        {
        retValue = CPslnSlidesetDialogInterface::EPslnDirectActivationPossible;
        }
    return retValue;
    }

// -----------------------------------------------------------------------------
// Append one line to interval setting list - make language dependant conversion.
// -----------------------------------------------------------------------------
//
void CPslnWallpaperSlidesetDialog::AppendIntervalItemL( TInt aResourceText )
    {
    HBufC* text = iCoeEnv->AllocReadResourceLC( aResourceText );
    TPtr ptr = text->Des();
    AknTextUtils::LanguageSpecificNumberConversion( ptr );
    iIntervalItems->AppendL( ptr  );
    CleanupStack::PopAndDestroy();  // textFromResourceFile
    }

// End of File
