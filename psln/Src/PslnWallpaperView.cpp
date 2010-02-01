/*
* Copyright (c) 2005-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Wallpaper view.
*
*/


// INCLUDE FILES
// Psln specific
#include <psln.rsg>
#include "PslnModel.h"
#include "PslnWallpaperView.h"
#include "PslnWallpaperContainer.h"
#include "PslnConst.h"
#include "PslnUi.h"
#include "PslnDRMImplementation.h"
#include "PslnDebug.h"

// General services
#include <MGFetch.h>
#include <AknSkinsInternalCRKeys.h>
#include <centralrepository.h>
#include <StringLoader.h>
#include <AknGlobalNote.h>

#ifdef RD_SLIDESHOW_WALLPAPER
// Slide set wallpaper.
#include <pslnslidesetwallpaperdialog.h>
#include <mmf/common/mmfcontrollerpluginresolver.h>
#include <ecom/resolver.h>
#endif // RD_SLIDESHOW_WALLPAPER

// CONSTANTS
// Granularity for wallpaper items.
const TInt KPslnFileArrayGranularity = 4;
// Index of selected file item from MGFetch.
const TInt KPslnSelectedFile = 0;

// Index of current wallpaper item selection.
enum TPslnWallpaperSelection
    {
    EPslnNoneWP = 0,
    EPslnUserDefinedWP,
    EPslnSlideSetWP
    };

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CPslnWallpaperView::CPslnWallpaperView()
    {
    }

// -----------------------------------------------------------------------------
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CPslnWallpaperView::ConstructL()
    {
    PSLN_TRACE_DEBUG("CPslnWallpaperView::ConstructL BEGIN");
    BaseConstructL( R_PSLN_WALLPAPER_VIEW );

    iNaviPaneContext = iPslnUi->PslnTabGroup();

    iWallpaperRepository = CRepository::NewL( KCRUidPersonalisation );
    iWallpaperNotifier = CCenRepNotifyHandler::NewL(
        *this,
        *iWallpaperRepository,
        CCenRepNotifyHandler::EIntKey,
        KPslnWallpaperType );
    iWpDlgRunnig = EFalse;
    PSLN_TRACE_DEBUG("CPslnWallpaperView::ConstructL END");
    }

// -----------------------------------------------------------------------------
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CPslnWallpaperView* CPslnWallpaperView::NewLC()
    {
    CPslnWallpaperView* self = new (ELeave) CPslnWallpaperView();
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// Destructor
CPslnWallpaperView::~CPslnWallpaperView()
    {
    if ( iWallpaperNotifier )
        {
        iWallpaperNotifier->StopListening();
        }
    delete iWallpaperNotifier;
    delete iWallpaperRepository;
    }

// -----------------------------------------------------------------------------
// CPslnWallpaperView::Id
// -----------------------------------------------------------------------------
//
TUid CPslnWallpaperView::Id() const
    {
    return KPslnWallpaperView;
    }

// -----------------------------------------------------------------------------
// CPslnWallpaperView::HandleCommandL
// -----------------------------------------------------------------------------
//
void CPslnWallpaperView::HandleCommandL( TInt aCommand )
    {
    if ( aCommand == EAknSoftkeyOk ||
         aCommand == EPslnCmdAppSetWallpaper ||
         aCommand == EPslnCmdAppChangeWallpaper ||
         aCommand == EPslnCmdWallpaperConfigure )
        {
        if ( iContainer )
            {
            TInt setBgImage = KErrNone;
            // If User specified is selected.
            switch ( iContainer->CurrentItemIndex() )
                {
                case EPslnUserDefinedWP:
                    {
                    if ( iWpDlgRunnig )
                        {
                        return;
                        }
                    if ( !ShowBackgroundImageListL() )
                        {
                        return;
                        }
                    iModel->SetCurrentPropertyTypeL(
                        KPslnBgIdleSettingId,
                        EPslnUserDefinedWP );
                    }
                    break;
                case EPslnNoneWP:
                    if ( iActiveWallpaper != EPslnNoneWP )
                        {
                        iModel->SetCurrentPropertyTypeL(
                            KPslnBgIdleSettingId,
                            EPslnNoneWP );
                        setBgImage = iModel->SetBackgroundImagePath( KNullDesC );
                        if ( setBgImage != KErrNone )
                            {
                            iPslnUi->HandleImageErrorsL( setBgImage );
                            }
                        }
                    else
                        {
                        // No need to do anything.
                        return;
                        }
                    break;
                case EPslnSlideSetWP:
                    {
#ifdef RD_SLIDESHOW_WALLPAPER
                    if ( iWpDlgRunnig )
                        {
                        //Try not run slideset dialog more than once.
                        return;
                        }
                    RImplInfoPtrArray array;
                    const TUid wallpaperUid = { 0x102823AD };
                    const TEComResolverParams emptyParams;
                    REComSession::ListImplementationsL(
                        wallpaperUid,
                        emptyParams,
                        KRomOnlyResolverUid,
                        array );
                    CleanupResetAndDestroyPushL( array );

                    CImplementationInformation* info = array[ KPslnWallpaperSlideSettingDialog ];
                    TUid implUid = info->ImplementationUid();

                    CPslnSlidesetDialogInterface* plugin =
                        CPslnSlidesetDialogInterface::NewL( implUid );
                    if ( aCommand == EPslnCmdWallpaperConfigure )
                        {
                        plugin->SetDialogFlag(
                            CPslnSlidesetDialogInterface::EPslnLaunchMode,
                            CPslnSlidesetDialogInterface::EPslnConfigureOnly );
                        }
                    if ( aCommand == EPslnCmdAppSetWallpaper &&
                         plugin->GetDialogFlag(
                            CPslnSlidesetDialogInterface::EPslnConfigurability ) ==
                                CPslnSlidesetDialogInterface::EPslnDirectActivationPossible )
                        {
                        delete plugin; // just delete the plugin as it is not needed.
                        iWallpaperRepository->Set( KPslnWallpaperType, EPslnSlideSetWP );
                        UpdateCurrentItem();
                        }
                    else
                        {
                        iWpDlgRunnig = ETrue;
                        plugin->ExecuteDialogLD();
                        iWpDlgRunnig = EFalse;
                        }

                    plugin = NULL;
                    CleanupStack::PopAndDestroy(); // array

                    // Plugin stores wallpaper type, if it deems that the user selection is valid.

#endif // RD_SLIDESHOW_WALLPAPER
                    }
                    break;
                default:
                    break;
                }

            // Update container.
            static_cast<CPslnWallpaperContainer*>
                (iContainer)->UpdateListBoxL();
            CheckMiddleSoftkeyLabelL();
            }
        }
    else
        {
    	if ( ( aCommand == EAknSoftkeyBack ) && iWpDlgRunnig )
    		{
    		return;
    		}
        iPslnUi->HandleCommandL( aCommand );
        }
    }

// -----------------------------------------------------------------------------
// When this method is called, view checks based on highlight focus, if the MSK
// label is correct.
// -----------------------------------------------------------------------------
//
void CPslnWallpaperView::CheckMiddleSoftkeyLabelL()
    {
    // First remove any prevous commands.
    RemoveCommandFromMSK();

    if ( iContainer )
        {
        iCurrentItem = iContainer->CurrentItemIndex();
        }

    // Set MSK label.
    if ( iActiveWallpaper != iCurrentItem )
        {
        // Set middle softkey as Apply, if:
        // a) 'None' is selected
        // b) highlight is on inactive selection
        CPslnBaseView::SetMiddleSoftKeyLabelL(
            R_PSLN_MSK_ACTIVATE,
            EPslnCmdAppSetWallpaper );
        }
     else if (  iActiveWallpaper == 0 )
        {
        CPslnBaseView::SetMiddleSoftKeyLabelL(
                R_PSLN_MSK_DUMMY,
                EPslnCmdEmptyCommand );
        }
    else
        {
        // Otherwise set middle softkey as Change.
        CPslnBaseView::SetMiddleSoftKeyLabelL(
            R_PSLN_MSK_CHANGE,
            EPslnCmdAppChangeWallpaper );
        }
    }

// -----------------------------------------------------------------------------
// If wallpaper image has changed, update container.
// -----------------------------------------------------------------------------
//
void CPslnWallpaperView::HandleNotifyInt( TUint32 aId, TInt /*aNewValue*/ )
    {
    if ( ( aId == KPslnWallpaperType ) && iContainer )
        {
        TInt previousValue = UpdateCurrentItem();
        if ( iActiveWallpaper != previousValue )
            {
            UpdateContainer();
            }
        }
    }

// -----------------------------------------------------------------------------
// If the whole repository changes, update container.
// -----------------------------------------------------------------------------
//
void CPslnWallpaperView::HandleNotifyGeneric( TUint32 aId )
    {
    if ( ( aId == NCentralRepositoryConstants::KInvalidNotificationId ||
           aId == KPslnWallpaperType ) && iContainer )
        {
        TInt previousValue = UpdateCurrentItem();
        if ( iActiveWallpaper != previousValue )
            {
            UpdateContainer();
            }
        }
    }

// -----------------------------------------------------------------------------
// In case of error, try to re-start listening.
// -----------------------------------------------------------------------------
//
void CPslnWallpaperView::HandleNotifyError(
    TUint32 /*aId*/,
    TInt aError,
    CCenRepNotifyHandler* aHandler )
    {
    if ( ( aError != KErrNone ) && aHandler )
        {
        TRAP_IGNORE( aHandler->StartListeningL() );
        }
    }

// -----------------------------------------------------------------------------
// CPslnWallpaperView::DoActivateL
// -----------------------------------------------------------------------------
//
void CPslnWallpaperView::DoActivateL(
            const TVwsViewId& aPrevViewId,
            TUid aCustomMessageId,
            const TDesC8& aCustomMessage )
    {
    PSLN_TRACE_DEBUG("CPslnWallpaperView::DoActivateL START");
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
            KPslnWallpaperView.iUid,
            KPslnWallpaperView.iUid );
        }

    if ( iContainer )
        {
        UpdateCurrentItem();
        // Set highlight to selected item.
        iContainer->SetCurrentItemIndexAndDraw( iActiveWallpaper );
        }
    if ( iWallpaperNotifier )
        {
        iWallpaperNotifier->StartListeningL();
        }
    CheckMiddleSoftkeyLabelL();
    iWpDlgRunnig = EFalse;
    PSLN_TRACE_DEBUG("CPslnWallpaperView::DoActivateL END");
    }

// -----------------------------------------------------------------------------
// CPslnWallpaperView::DynInitMenuPaneL
// -----------------------------------------------------------------------------
//
void CPslnWallpaperView::DynInitMenuPaneL(
    TInt aResourceId, CEikMenuPane* aMenuPane )
    {
    if ( aResourceId == R_PSLN_WALLPAPER_MENUPANE )
        {
        if ( iContainer )
            {
            iCurrentItem = iContainer->CurrentItemIndex();
            }
        // Remove change if none is selected, or highlight is not in active item.
        if ( iActiveWallpaper != iCurrentItem )
            {
            aMenuPane->SetItemDimmed( EPslnCmdAppChangeWallpaper, ETrue );
            }
        else if ( iActiveWallpaper == 0 )
            {
                aMenuPane->SetItemDimmed( EPslnCmdAppSetWallpaper, ETrue );
                aMenuPane->SetItemDimmed( EPslnCmdAppChangeWallpaper, ETrue );
            }
        else
            {
            aMenuPane->SetItemDimmed( EPslnCmdAppSetWallpaper, ETrue );
            }
          
#ifdef RD_SLIDESHOW_WALLPAPER

        if ( iCurrentItem != EPslnSlideSetWP )
            {
            aMenuPane->SetItemDimmed( EPslnCmdWallpaperConfigure, ETrue );
            }
#endif // RD_SLIDESET_WALLPAPER
        }
    CPslnBaseView::DynInitMenuPaneL( aResourceId, aMenuPane );
    }

// -----------------------------------------------------------------------------
// CPslnWallpaperView::HandleListBoxSelectionL
// -----------------------------------------------------------------------------
//
void CPslnWallpaperView::HandleListBoxSelectionL()
    {
    if ( iContainer )
        {
        iCurrentItem = iContainer->CurrentItemIndex();
        }
    HandleCommandL( EAknSoftkeyOk );
    }
    
// -----------------------------------------------------------------------------
// CPslnWallpaperView::HandleListBoxItemHighlightL
// -----------------------------------------------------------------------------
//
void CPslnWallpaperView::HandleListBoxItemHighlightL()
    {    
    }    

// -----------------------------------------------------------------------------
// CPslnWallpaperView::NewContainerL
// -----------------------------------------------------------------------------
//
void CPslnWallpaperView::NewContainerL()
    {
    iContainer = new(ELeave) CPslnWallpaperContainer();
    iContainer->SetMiddleSoftkeyObserver( this );
    }

// -----------------------------------------------------------------------------
// CPslnWallpaperView::SetTitlePaneL
// -----------------------------------------------------------------------------
//
void CPslnWallpaperView::SetTitlePaneL( TInt& aResourceId )
    {
#ifdef RD_CONTROL_PANEL
    aResourceId = R_PSLN_TITLE_PANE_WALLPAPER;
#endif //RD_CONTROL_PANEL
    }

// ---------------------------------------------------------------------------
// CPslnWallpaperView::CbaExitEnabled
// ---------------------------------------------------------------------------
//
TInt CPslnWallpaperView::CbaResourceId( const TVwsViewId& /*aPrevViewId*/,TUid aCustomMessageId )
    {
    return aCustomMessageId.iUid ?
        R_AVKON_SOFTKEYS_OPTIONS_EXIT : R_AVKON_SOFTKEYS_OPTIONS_BACK;
    }
    
// ---------------------------------------------------------------------------
// CPslnWallpaperView::ShowBackgroundImageListL
// ---------------------------------------------------------------------------
//
TBool CPslnWallpaperView::ShowBackgroundImageListL()
    {
    PSLN_TRACE_DEBUG("CPslnWallpaperView::ShowBackgroundImageListL");
    TBool retVal = EFalse;
    CDesCArrayFlat* files =
        new (ELeave) CDesCArrayFlat( KPslnFileArrayGranularity );
    CleanupStack::PushL( files );
    CPslnDRMImplementation* verifier = NULL;
    verifier = CPslnDRMImplementation::NewL();
    CleanupStack::PushL( verifier );

    PSLN_TRACE_DEBUG("CPslnWallpaperView::ShowBackgroundImageListL MGFetch");
    iWpDlgRunnig = ETrue;
    TBool selected = EFalse;
    TRAPD( err,selected = MGFetch::RunL( *files, EImageFile, EFalse, verifier ) );
    iWpDlgRunnig = EFalse;
    User::LeaveIfError( err );
    if ( !verifier )
        {
        PSLN_TRACE_DEBUG("CPslnWallpaperView::ShowBackgroundImageListL DRM Error");
        }

    else if( selected && ( files->MdcaCount() > 0 ) )
        {
        PSLN_TRACE_DEBUG("CPslnWallpaperView::ShowBackgroundImageListL Fetch successful");
        TInt setBgImage = iModel->SetBackgroundImagePath(
                files->MdcaPoint( KPslnSelectedFile ) );
        if ( setBgImage != KErrNone )
            {
            if ( setBgImage == KLeaveExit )
                {
                User::Leave( KLeaveExit );
                }
            else
                {    
                iPslnUi->HandleImageErrorsL( setBgImage );
                }
            }
        else
            {
            // Image selected, no DRM issues.
            retVal = ETrue;
            }
        CheckMiddleSoftkeyLabelL();
        }
    else
        {
        PSLN_TRACE_DEBUG("CPslnWallpaperView::ShowBackgroundImageListL Fetch cancelled");
        }

    CleanupStack::PopAndDestroy( 2, files ); // verifier, files

    PSLN_TRACE_DEBUG("CPslnWallpaperView::ShowBackgroundImageListL METHOD COMPLETED");
    return retVal;
    }

// ---------------------------------------------------------------------------
// Updates the container.
// ---------------------------------------------------------------------------
//
void CPslnWallpaperView::UpdateContainer()
    {
    PSLN_TRACE_DEBUG("CPslnWallpaperView::UpdateContainer START");
    if ( iContainer )
        {
        TRAP_IGNORE( static_cast<CPslnWallpaperContainer*>
                (iContainer)->UpdateListBoxL();
            CheckMiddleSoftkeyLabelL();
            );
        }
    PSLN_TRACE_DEBUG("CPslnWallpaperView::UpdateContainer END");
    }

// ---------------------------------------------------------------------------
// Removes unnecessary commands from Middle softkey.
// ---------------------------------------------------------------------------
//
void CPslnWallpaperView::RemoveCommandFromMSK()
    {
    CEikButtonGroupContainer* cbaGroup = Cba();
    if ( cbaGroup )
        {
        cbaGroup->RemoveCommandFromStack( KPslnMSKControlID, EPslnCmdAppSetWallpaper );
        cbaGroup->RemoveCommandFromStack( KPslnMSKControlID, EPslnCmdAppChangeWallpaper );
        }
    }

// ---------------------------------------------------------------------------
// Updates current item.
// ---------------------------------------------------------------------------
//
TInt CPslnWallpaperView::UpdateCurrentItem()
    {
    TInt previousValue = iActiveWallpaper;
    iActiveWallpaper = iModel->CurrentPropertyIndex( KPslnBgIdleSettingId );
    return previousValue;
    }

//  End of File
