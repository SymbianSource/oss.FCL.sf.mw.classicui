/*
* Copyright (c) 2005-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  General theme view.
*
*/



// INCLUDE FILES

// General - services
#include <StringLoader.h>
#include <AknGlobalNote.h>
#include <aknnotewrappers.h>
#include <akntitle.h>
#include <barsread.h>
#include <eikbtgpc.h>
#include <eikmenup.h>

// Feature manager.
#include <featmgr.h>
#include <features.hrh>

// Power save mode setting
#include <psmsettings.h>

// Resources
#include <psln.rsg>
#include <pslncommon.rsg>
#include <data_caging_path_literals.hrh>

// Psln specific.
#include "PslnGeneralThemeView.h"
#include "PslnConst.h"
#include "PslnUi.h"
#include "PslnModel.h"
#include "PslnFeatures.h"
#include "PslnDebug.h"


// Path to common personalization resources. This resource file is meant for
// shared resources between application and plugins.
_LIT( KPslnCommonResourceFileName, "z:pslncommon.rsc" );

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// C++ constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CPslnGeneralThemeView::CPslnGeneralThemeView()
    : iResourceLoaderCommon( *iCoeEnv )
    {
    }

// -----------------------------------------------------------------------------
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CPslnGeneralThemeView::ConstructL()
    {
    BaseConstructL( R_PSLN_GENERAL_VIEW );

    iNaviPaneContext = iPslnUi->PslnTabGroup();

    // Find the common resource file:
    TParse* parse = new (ELeave) TParse;
    CleanupStack::PushL( parse );
    parse->Set( KPslnCommonResourceFileName, &KDC_APP_RESOURCE_DIR, NULL );
    TFileName* fileName = new (ELeave) TFileName( parse->FullName() );
    CleanupStack::PushL( fileName );

    // Open resource file:
    iResourceLoaderCommon.OpenL( *fileName );

    CleanupStack::PopAndDestroy( 2, parse ); // fileName, parse

    // Normally download item is the first one.
    iDownloadItemIndex = 0;

    // If enchanted embedded links are not supported, then there shouldn't be
    // 'Download' item at all.
    if ( !PslnFeatures::IsEnhancedEmbeddedLinksSupported() )
        {
        iDownloadItemIndex = KErrNotFound;
        }
    }

// -----------------------------------------------------------------------------
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CPslnGeneralThemeView* CPslnGeneralThemeView::NewLC()
    {
    CPslnGeneralThemeView* self = new (ELeave) CPslnGeneralThemeView();
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// Destructor
CPslnGeneralThemeView::~CPslnGeneralThemeView()
    {
    iResourceLoaderCommon.Close();
    }

// -----------------------------------------------------------------------------
// CPslnGeneralThemeView::Id
// -----------------------------------------------------------------------------
//
TUid CPslnGeneralThemeView::Id() const
    {
    return KPslnGeneralView;
    }

// -----------------------------------------------------------------------------
// CPslnGeneralThemeView::HandleCommandL
// -----------------------------------------------------------------------------
//
void CPslnGeneralThemeView::HandleCommandL( TInt aCommand )
    {
    // First set active item and active skin.
    if ( iContainer )
        {
        iCurrentItem = iContainer->CurrentItemIndex();
        }
    TInt activeSkinIndex = iCurrentItem;
    if ( iDownloadItemIndex != KErrNotFound )
        {
        activeSkinIndex--;
        }
    switch ( aCommand )
        {
        case EPslnCmdTransitionEffectsActivate:
            {
            TInt PsmMode = 0;
            CPsmSettings *PsmSettings = CPsmSettings::NewL();
            PsmSettings->GetCurrentMode( PsmMode );
            delete PsmSettings;

            if ( PsmMode == EPsmsrvModePowerSave ) // PSM on, setting is protected
                {
                HBufC* buf = StringLoader::LoadLC( R_PSLN_QTN_PSM_INFONOTE );
                CAknInformationNote* note = new (ELeave) CAknInformationNote( ETrue );
                note->ExecuteLD( *buf );
                CleanupStack::PopAndDestroy( buf );
                return;
                }

            TInt error = iModel->SetTransitionEffectsL( EPslnEnableAllEffects );
            
            if ( error == KErrNoMemory )
                {
                HBufC* errorBuf = StringLoader::LoadLC(
                    R_PSLN_NOT_ENOUGH_MEMORY );
                // Display global note.
                CAknGlobalNote* errorNote = CAknGlobalNote::NewLC();
                errorNote->ShowNoteL( EAknGlobalErrorNote, *errorBuf );
                CleanupStack::PopAndDestroy( 2, errorBuf ); // errorNote also
                }
            else
                {
                User::LeaveIfError( error );
                }
            }
            break;
        case EPslnCmdTransitionEffectsDeactivate:
            iModel->SetTransitionEffectsL( EPslnDisableAllEffects );
            break;
        
        case EPslnCmdAnimBackgroundActivate:
            {
            TInt PsmMode = 0;
            CPsmSettings *PsmSettings = CPsmSettings::NewL();
            PsmSettings->GetCurrentMode( PsmMode );
            delete PsmSettings;

            if ( PsmMode == EPsmsrvModePowerSave ) // PSM on, setting is protected
                {
                HBufC* buf = StringLoader::LoadLC( R_PSLN_QTN_PSM_INFONOTE );
                CAknInformationNote* note = new (ELeave) CAknInformationNote( ETrue );
                note->ExecuteLD( *buf );
                CleanupStack::PopAndDestroy( buf );
                return;
                }

            TInt error = iModel->SetAnimBackground( EPslnEnableAllEffects );
            if ( error == KErrNoMemory )
                {
                HBufC* errorBuf = StringLoader::LoadLC(
                        R_PSLN_NOT_ENOUGH_MEMORY );

                CAknGlobalNote* errorNote = CAknGlobalNote::NewLC();
                errorNote->ShowNoteL( EAknGlobalErrorNote, *errorBuf );
                CleanupStack::PopAndDestroy( 2, errorBuf ); // errorNote also
                }
            }
            break;
        case EPslnCmdAnimBackgroundDeactivate:
            iModel->SetAnimBackground( EPslnDisableAllEffects );
            break;        
        case EPslnCmdEmptyCommand: // Fallthrough
        case EPslnCmdAppActivate: // Fallthrough
            {
            if ( iContainer )
                {
                if ( iToBeActivatedSkinIndex != KErrNotFound )
                    {
                    activeSkinIndex = iToBeActivatedSkinIndex;
                    iToBeActivatedSkinIndex = -1;
                    }
                // Do nothing if active theme is selected.
                if ( iModel->IsActiveSkinSelected( activeSkinIndex  ) )
                    {
                    break;
                    }
                // Check is the theme corrupted.
                if ( !iModel->IsValidForActivation( activeSkinIndex ) )
                    {
                    HBufC* errorBuf = StringLoader::LoadLC(
                        R_PSLN_QTN_SKINS_ERROR_CORRUPTED );
                    // Display global note.
                    CAknGlobalNote* errorNote = CAknGlobalNote::NewLC();
                    errorNote->ShowNoteL( EAknGlobalErrorNote, *errorBuf );
                    CleanupStack::PopAndDestroy( 2, errorBuf ); // errorNote also
                    return;
                    }
                else
                    {
                    iModel->SetCurrentSelectedSkinIndex( activeSkinIndex );
                    }
                }
            }
        case EPslnCmdAppDownload: // Fallthrough
        default:
            iPslnUi->HandleCommandL( aCommand );
            break;
        }
    }

// ---------------------------------------------------------------------------
// CPslnGeneralThemeView::UpdateSkinListItemsL()
// ---------------------------------------------------------------------------
//
void CPslnGeneralThemeView::UpdateSkinListItemsL( TInt aCurrentIndex )
    {
    PSLN_TRACE_DEBUG("CPslnGeneralThemeView::UpdateSkinListItemsL");
    if ( iContainer )
        {
        if ( aCurrentIndex == KErrNotFound )
            {
            aCurrentIndex = iContainer->CurrentItemIndex();
            }
        static_cast<CPslnGeneralThemeContainer*>(iContainer)->
            UpdateSkinListItemsL( aCurrentIndex );
        }
    CheckMiddleSoftkeyLabelL();
    }

// -----------------------------------------------------------------------------
// CPslnGeneralThemeView::DoActivateL
// -----------------------------------------------------------------------------
//
void CPslnGeneralThemeView::DoActivateL(
            const TVwsViewId& aPrevViewId,
            TUid aCustomMessageId,
            const TDesC8& aCustomMessage )
    {
    PSLN_TRACE_DEBUG("CPslnGeneralThemeView::DoActivateL");

    CPslnBaseView::DoActivateL(
        aPrevViewId,
        aCustomMessageId,
        aCustomMessage );

    // If view is directly activated (not through main view), update
    // tab group (and main view's active folder). The static views
    // have same UID as their tab index.
    if ( aPrevViewId.iAppUid != KUidPsln )
        {
        iPslnUi->UpdateTabIndex(
            KPslnGeneralView.iUid,
            KPslnGeneralView.iUid );
        }

    // Update skin list.
    // Set active index and update container.
    TInt currentlySelected  = iModel->ActiveSkinIndex();
    iModel->SetCurrentSelectedSkinIndex( currentlySelected );

    CheckMiddleSoftkeyLabelL();

    iToBeActivatedSkinIndex = -1;
    }

// -----------------------------------------------------------------------------
// CPslnGeneralThemeView::DoDeactivate
// -----------------------------------------------------------------------------
//
void CPslnGeneralThemeView::DoDeactivate()
    {
    PSLN_TRACE_DEBUG("CPslnGeneralThemeView::DoDeactivate");
    RemoveCommandFromMSK();
    CPslnBaseView::DoDeactivate();
    }

// -----------------------------------------------------------------------------
// CPslnGeneralThemeView::DynInitMenuPaneL
//
// -----------------------------------------------------------------------------
//
void CPslnGeneralThemeView::DynInitMenuPaneL(
    TInt aResourceId, CEikMenuPane* aMenuPane )
    {
    PSLN_TRACE_DEBUG("CPslnGeneralThemeView::DynInitMenuPaneL");
    if( aResourceId == R_PSLN_GEN_VIEW_MENUPANE )
        {
        if ( iContainer )
            {
            if ( iContainer->iListBox->IsHighlightEnabled() )
                {
                iCurrentItem = iContainer->CurrentItemIndex();
                }
            else
                {
                iCurrentItem = iModel->ActiveSkinIndex();
                if ( iDownloadItemIndex != KErrNotFound )
                    {
                    iCurrentItem++;
                    }
                }
            }

        TBool downloadExists = ETrue;
        // Download theme is not selected, or it is not supported.
        if ( iDownloadItemIndex == KErrNotFound )
            {
            // Download item is not supported.
            aMenuPane->SetItemDimmed( EPslnCmdAppDownload, ETrue );
            downloadExists = EFalse;
            }
        else if ( iCurrentItem != iDownloadItemIndex )
            {
            // Download is supported, but is not selected.
            aMenuPane->SetItemDimmed( EPslnCmdAppDownload, ETrue );
            downloadExists = ETrue;
            }
        else
            {
            aMenuPane->SetItemDimmed( EPslnCmdAppActivate, ETrue );
            }

        // Update current item index in model.
        // Possibly reduce by one, since UI might show Download item.
        TInt skinIndex = iCurrentItem - (TInt) downloadExists;
        iModel->SetCurrentSelectedSkinIndex( skinIndex );

        if( iModel->IsActiveSkinSelected() ||
           !iModel->IsValidForActivation( skinIndex ) )
            {
            aMenuPane->SetItemDimmed( EPslnCmdAppActivate, ETrue );
            }
        }
    else if ( aResourceId == R_PSLN_TRANSITION_EFFECTS_MENU_PANE )
        {
        if ( ( iCurrentItem == iDownloadItemIndex &&
             iDownloadItemIndex != KErrNotFound ) ||
            !FeatureManager::FeatureSupported(KFeatureIdUiTransitionEffects) )
            {
            // Remove Transition Effects when Download is highlighted.
            aMenuPane->SetItemDimmed( EPslnCmdTransitionEffectsSubMenuOpen, ETrue );
            }
        }
    else if ( aResourceId == R_PSLN_TRANSITION_EFFECTS_CASCADE_MENU )
        {
        // Do nothing with cascade menu values, if Download is highlighted.
        if ( iCurrentItem != iDownloadItemIndex ||
             iDownloadItemIndex != KErrNotFound )
            {
            TInt transitionEffectsValue = iModel->GetTransitionEffectStateL();
            // Effects are enabled if value is NOT KMaxTInt.
            if( transitionEffectsValue != KMaxTInt )
                {
                aMenuPane->SetItemButtonState(
                    EPslnCmdTransitionEffectsActivate,
                    EEikMenuItemSymbolOn );
                aMenuPane->SetItemButtonState(
                    EPslnCmdTransitionEffectsDeactivate,
                    EEikMenuItemSymbolIndeterminate );
                }
            else
                {
                aMenuPane->SetItemButtonState(
                    EPslnCmdTransitionEffectsActivate,
                    EEikMenuItemSymbolIndeterminate );
                aMenuPane->SetItemButtonState(
                    EPslnCmdTransitionEffectsDeactivate,
                    EEikMenuItemSymbolOn );
                }
            }
        }
    else if ( aResourceId == R_PSLN_ANIM_BACKGROUND_MENU_PANE )
        {
        TBool downloadExists = ETrue;
        if ( iDownloadItemIndex == KErrNotFound )
            {
            downloadExists = EFalse;
            }
        TInt skinIndex = iCurrentItem - (TInt) downloadExists;
		
        if ( ( iCurrentItem == iDownloadItemIndex &&
             iDownloadItemIndex != KErrNotFound )||
             !iModel->IsActiveSkinSelected() ||
             !PslnFeatures::IsSupported( KPslnSupportAnimBackground ) ||
             !iModel->IsSupportAnimBg(skinIndex))
            {
            aMenuPane->SetItemDimmed( EPslnCmdAnimBackgroundSubMenuOpen, ETrue );
            }
        }
    else if ( aResourceId == R_PSLN_ANIM_BACKGROUND_CASCADE_MENU )
        {
        // Do nothing with cascade menu values, if Download is highlighted.
        if ( iCurrentItem != iDownloadItemIndex ||
             iDownloadItemIndex != KErrNotFound )
            {
            TInt animEffectsValue = iModel->AnimBackgroundState();
            // Animation background are enabled if value is NOT KMaxTInt.
            if( animEffectsValue != KMaxTInt )
                {
                aMenuPane->SetItemButtonState(
                    EPslnCmdAnimBackgroundActivate,
                    EEikMenuItemSymbolOn );
                aMenuPane->SetItemButtonState(
                    EPslnCmdAnimBackgroundDeactivate,
                    EEikMenuItemSymbolIndeterminate );
                }
            else
                {
                aMenuPane->SetItemButtonState(
                    EPslnCmdAnimBackgroundActivate,
                    EEikMenuItemSymbolIndeterminate );
                aMenuPane->SetItemButtonState(
                    EPslnCmdAnimBackgroundDeactivate,
                    EEikMenuItemSymbolOn );
                }
            }
        }
    else
        {
        PSLN_TRACE_DEBUG("CPslnGeneralThemeView::DynInitMenuPaneL empty else");
        }
    CPslnBaseView::DynInitMenuPaneL( aResourceId, aMenuPane );
    }

// -----------------------------------------------------------------------------
// Handle listbox selection.
//
// -----------------------------------------------------------------------------
//
void CPslnGeneralThemeView::HandleListBoxSelectionL()
    {
    PSLN_TRACE_DEBUG("CPslnGeneralThemeView::HandleListBoxSelectionL");
    if ( iContainer )
        {
        iCurrentItem = iContainer->CurrentItemIndex();
        }

    if ( iCurrentItem == iDownloadItemIndex )
        {
        HandleCommandL( EPslnCmdAppDownload );
        }
    else
        {
        HandleCommandL( EPslnCmdAppActivate );
        }
    }

// -----------------------------------------------------------------------------
// Create container.
//
// -----------------------------------------------------------------------------
//
void CPslnGeneralThemeView::NewContainerL()
    {
    iContainer = new(ELeave) CPslnGeneralThemeContainer();
    iContainer->SetMiddleSoftkeyObserver( this );
    }

// -----------------------------------------------------------------------------
// Sets view specific title pane text.
//
// -----------------------------------------------------------------------------
//
void CPslnGeneralThemeView::SetTitlePaneL( TInt& aResourceId )
    {
    aResourceId = R_PSLN_TITLE_PANE_GENERAL;
    }

// -----------------------------------------------------------------------------
// Checks is there a need to update the middle softkey label.
// This method should do nothing but MSK issues, since it is still called
// if the framework does not support MSK.
// -----------------------------------------------------------------------------
//
void CPslnGeneralThemeView::CheckMiddleSoftkeyLabelL()
    {
    PSLN_TRACE_DEBUG("CPslnGeneralThemeView::CheckMiddleSoftkeyLabelL");
    TInt currentItem = KErrNotFound;
    if ( iContainer )
        {
        currentItem = iContainer->CurrentItemIndex();
        }

    TInt activeSkinIndex = 0;
    if ( iModel )
        {
        activeSkinIndex = iModel->ActiveSkinIndex();
        }
    if ( iDownloadItemIndex != KErrNotFound )
        {
        // If download item is present, increment current index,
        // so that skin index maps directly to listbox indexes.
        activeSkinIndex++;
        }

    // First remove any prevous commands.
    RemoveCommandFromMSK();
    if ( currentItem == iDownloadItemIndex && currentItem != KErrNotFound )
        {
        // Set middle softkey as Download.
        CPslnBaseView::SetMiddleSoftKeyLabelL(
            R_PSLN_MSK_SELECT,
            EPslnCmdAppDownload );
        }
    else if ( currentItem != activeSkinIndex )
        {
        // Set middle softkey as Apply.
        CPslnBaseView::SetMiddleSoftKeyLabelL(
            R_PSLN_MSK_ACTIVATE,
            EPslnCmdAppActivate );
        }
    else
        {
        // Set middle softkey as dummy.
        CPslnBaseView::SetMiddleSoftKeyLabelL(
            R_PSLN_MSK_DUMMY,
            EPslnCmdEmptyCommand );
        }
    }

// -----------------------------------------------------------------------------
// Requests container to update skin data for D column.
// -----------------------------------------------------------------------------
//
void CPslnGeneralThemeView::UpdateSkinListItemsDColumnOnlyL()
    {
    PSLN_TRACE_DEBUG("CPslnGeneralThemeView::UpdateSkinListItemsL");
    if ( iContainer )
        {
        static_cast<CPslnGeneralThemeContainer*>(iContainer)->
            UpdateSkinListItemsDColumnOnlyL();
        }
    CheckMiddleSoftkeyLabelL();
    }

// -----------------------------------------------------------------------------
// Remove MSK command mappings.
// This method should do nothing but MSK issues.
// -----------------------------------------------------------------------------
//
void CPslnGeneralThemeView::RemoveCommandFromMSK()
    {
    PSLN_TRACE_DEBUG("CPslnGeneralThemeView::RemoveCommandFromMSK");
    CEikButtonGroupContainer* cbaGroup = Cba();
    // Check if model exists => indicates that UI is not exiting.
    if ( cbaGroup && iPslnUi->Model() )
        {
        cbaGroup->RemoveCommandFromStack( KPslnMSKControlID, EPslnCmdAppDownload );
        cbaGroup->RemoveCommandFromStack( KPslnMSKControlID, EPslnCmdAppActivate );
        }
    }

// -----------------------------------------------------------------------------
// Hightligt Default skin
// -----------------------------------------------------------------------------
//
void CPslnGeneralThemeView::HightlightDefaultSkin()
    {
    CPslnGeneralThemeContainer* container = static_cast<CPslnGeneralThemeContainer*>(iContainer);
    TInt modifier = container->IsEmbeddedLinkVisible( );
    container->SetCurrentItemIndex( modifier );
    }
//  End of File
