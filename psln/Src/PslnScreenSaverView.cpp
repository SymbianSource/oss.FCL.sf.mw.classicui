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
* Description:  Screen saver view.
*
*/


// INCLUDE FILES

// RProperty keys.
#include <e32cmn.h>
#include <e32def.h>

// Central repository.
#include <centralrepository.h>
#include <cenrepnotifyhandler.h>

// AVKON services.
#include <AknWaitDialog.h>
#include <aknnotewrappers.h>
#include <avkon.hrh>
#include <StringLoader.h>
#include <eikmenup.h>

// Power save mode setting
#include <psmsettings.h>

// Psln specific.
#include <psln.rsg>
#include "PslnModel.h"
#include "PslnScreenSaverView.h"
#include "PslnScreenSaverContainer.h"
#include "PslnConst.h"
#include "PslnUi.h"

// CONSTANTS
// Number of default system screensavers.
const TInt KPslnSystemScreenSavers = 2;
// Value in PubSub when screensaver preview is off.
const TInt KPslnScreenSaverPreviewOff = 0;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CPslnScreenSaverView::CPslnScreenSaverView()
    {
    }

// -----------------------------------------------------------------------------
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CPslnScreenSaverView::ConstructL()
    {
    BaseConstructL( R_PSLN_SCREENSAVER_VIEW );

    iNaviPaneContext = iPslnUi->PslnTabGroup();

    iScreenSaverRepository = NULL;
    iScreenSaverNotifier = CCenRepNotifyHandler::NewL(
        *this,
        *iScreenSaverRepository,
        CCenRepNotifyHandler::EIntKey,
        NULL );

    // Load screensavers.
    iModel->LoadScreensaverArrayL();
    }

// -----------------------------------------------------------------------------
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CPslnScreenSaverView* CPslnScreenSaverView::NewLC()
    {
    CPslnScreenSaverView* self = new (ELeave) CPslnScreenSaverView();
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// Destructor
CPslnScreenSaverView::~CPslnScreenSaverView()
    {
    if ( iPreviewModeSubscriber )
        {
        iPreviewModeSubscriber->Cancel();
        }
    iPreviewModeProperty.Close();
    delete iPreviewModeSubscriber;
    if ( iPreviewStateSubscriber )
        {
        iPreviewStateSubscriber->Cancel();
        }
    iPreviewStateProperty.Close();
    delete iPreviewStateSubscriber;
    
    if(iPsmClient)
    	{
    	iPsmClient->CancelPowerSaveModeNotificationRequest();
    	delete iPsmClient;
    	}
    
    if ( iWaitDlg )
        {
        delete iWaitDlg;
        }

    if ( iScreenSaverNotifier->IsActive() )
        {
        iScreenSaverNotifier->StopListening();
        }
    delete iScreenSaverNotifier;
    delete iScreenSaverRepository;
    }

// -----------------------------------------------------------------------------
// CPslnScreenSaverView::Id
// -----------------------------------------------------------------------------
//
TUid CPslnScreenSaverView::Id() const
    {
    return KPslnScreenSaverView;
    }

// -----------------------------------------------------------------------------
// CPslnScreenSaverView::HandleCommandL
// -----------------------------------------------------------------------------
//
void CPslnScreenSaverView::HandleCommandL( TInt aCommand )
    {
    TInt currentItem = 0;
    if ( iContainer )
        {
        currentItem = iContainer->CurrentItemIndex();
        }
    switch ( aCommand )
        {
        case EPslnCmdAppChangeScreenSaver:
            if ( iModel->ScreensaverHasCapability( currentItem, EScpCapsConfigure ) )
                {
                HandleScreenSaverSettingsL( currentItem );
                }
            else
                {
                HandleScreenSaverActivationL( currentItem );
                }
            break;
        case EPslnCmdAppSetScreenSaver:
#ifdef __WINS__
            // Trap in wins => unhandled leave propagated to UI level.
            TRAP_IGNORE( HandleScreenSaverActivationL( currentItem ) );
#else
            HandleScreenSaverActivationL( currentItem );
#endif //__WINS__
            break;

        case EPslnCmdPreviewScreenSaver:
            HandleScreenSaverPreviewL( currentItem );
            break;

        case EPslnCmdAppSettings:
            HandleScreenSaverSettingsL( currentItem );
            break;

        case EAknSoftkeyExit:
            aCommand = EAknCmdExit;
            //lint -fallthrough
        default:
            iPslnUi->HandleCommandL( aCommand );
            break;
        }
    }

// -----------------------------------------------------------------------------
// When screensaver list is updated due to install/uninstall of screensaver,
// this method is called.
// -----------------------------------------------------------------------------
//
void CPslnScreenSaverView::HandlePluginListChangeL()
    {
    // Set highlight to selected item.
    if ( iContainer )
        {
        static_cast<CPslnScreenSaverContainer*> (iContainer)->UpdateListBoxL();

        TInt newDefault = iModel->CurrentPropertyIndexL( KPslnScreenSettingId );
        if ( newDefault == KErrNotFound )
            {
            // If no default found, assume that date is default.
            newDefault = 0;
            iModel->SetCurrentPropertyTypeL(
                KPslnScreenSettingId,
                newDefault );
            }
        iContainer->SetCurrentItemIndexAndDraw( newDefault );
        CheckMiddleSoftkeyLabelL();
        }
    }

// -----------------------------------------------------------------------------
// When this method is called, view checks based on highlight focus, if the MSK
// label is correct.
// -----------------------------------------------------------------------------
//
void CPslnScreenSaverView::CheckMiddleSoftkeyLabelL()
    {
    // First remove any prevous commands.
    RemoveCommandFromMSK();

    if ( IsChangeCommandVisibleL() )
        {
        // Set middle softkey as Change.
        CPslnBaseView::SetMiddleSoftKeyLabelL(
            R_PSLN_MSK_CHANGE,
            EPslnCmdAppChangeScreenSaver );
        }
    else if(IsApplyCommandVisibleL())
        {
        // For "Date" and for inactive screensavers MSK Label is Apply.
        // Apply is also used for simple installed screensavers that do not have settings.
        CPslnBaseView::SetMiddleSoftKeyLabelL(
            R_PSLN_MSK_ACTIVATE,
            EPslnCmdAppSetScreenSaver );
       
        }
    else
        {
        // when current focus and ticked item is Date.
        // Do not show MSK.
        CPslnBaseView::SetMiddleSoftKeyLabelL(
            R_PSLN_MSK_DUMMY,
            EPslnCmdAppSetScreenSaver );
        }
    }

// ---------------------------------------------------------------------------
// This is callback method for iPreviewModeSubscriber.
// This method is not allowed to leave - if it leaves, subscription is not
// activated.
// ---------------------------------------------------------------------------
//
TInt CPslnScreenSaverView::HandlePreviewModeChanged( TAny *aPtr )
    {
    CPslnScreenSaverView* self =
        static_cast<CPslnScreenSaverView*>(aPtr);
    TInt value = KErrNone;
    if ( self->iPreviewModeSubscriber )
        {
        self->iPreviewModeProperty.Get( value );
        }

    if ( value == KPslnScreenSaverPreviewOff )
        {

        // Stop listening for preview mode changes.
        if ( self->iPreviewModeSubscriber )
            {
            self->iPreviewModeSubscriber->Cancel();
            }

        // Restore the original screen saver
        self->iModel->ActivateScreenSaver(
            KErrNotFound,
            EPslnScreenSaverPreviewDeactivation );

        if ( self->iContainer )
            {
            // Update container.
            TRAP_IGNORE(
                static_cast<CPslnScreenSaverContainer*>
                    (self->iContainer)->UpdateListBoxL() );
            }
        }
    return KErrNone;
    }

// ---------------------------------------------------------------------------
// This is callback method for iPreviewStateSubscriber.
// This method is not allowed to leave - if it leaves, subscription is not
// activated.
// ---------------------------------------------------------------------------
//
TInt CPslnScreenSaverView::HandlePreviewStateChanged( TAny* aPtr )
    {
    CPslnScreenSaverView* self =
        static_cast<CPslnScreenSaverView*>(aPtr);
    TInt value = KErrNone;
    if ( self->iPreviewStateSubscriber )
        {
        self->iPreviewStateProperty.Get( value );
        }

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// Screensaver array needs to be loaded before activating the view.
// It is done from UI class.
// -----------------------------------------------------------------------------
//
void CPslnScreenSaverView::DoActivateL(
            const TVwsViewId& aPrevViewId,
            TUid aCustomMessageId,
            const TDesC8& aCustomMessage )
    {
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
            KPslnScreenSaverView.iUid,
            KPslnScreenSaverView.iUid );
        }

    // Notify model that we are ready to receive changes in screensavers.
    iModel->EnableScreenSaverNotifications( ETrue, *this );

    if ( !iScreenSaverNotifier->IsActive() )
        {
        iScreenSaverNotifier->StartListeningL();
        }

    iPsmClient = CPsmClient::NewL(*this);
    iPsmClient->RequestPowerSaveModeNotification();

    // Set highlight to selected item.
    if ( iContainer )
        {
        iContainer->SetCurrentItemIndexAndDraw(
            iModel->CurrentPropertyIndexL( KPslnScreenSettingId ) );
        }
    CheckMiddleSoftkeyLabelL();
    }

// -----------------------------------------------------------------------------
// This is called when view is deactivated (when another view has been activated),
// -----------------------------------------------------------------------------
//
void CPslnScreenSaverView::DoDeactivate()
    {
    CPslnBaseView::DoDeactivate();

    // Notify model that we are no longer active.
    // Get the pointer to model from UI class (even though base view also has it)
    // because, the model might have been deleted at this point and base class is
    // not aware of the deletion.
    if ( iPslnUi->Model() )
        {
        iPslnUi->Model()->EnableScreenSaverNotifications( EFalse, *this );
        }
        
    if(iPsmClient)
    	{
    	iPsmClient->CancelPowerSaveModeNotificationRequest();
        delete iPsmClient;
        iPsmClient = NULL;
    	}
    }

// -----------------------------------------------------------------------------
// CPslnScreenSaverView::DynInitMenuPaneL
// -----------------------------------------------------------------------------
//
void CPslnScreenSaverView::DynInitMenuPaneL(
    TInt aResourceId, CEikMenuPane* aMenuPane )
    {
    if ( aResourceId == R_PSLN_SS_VIEW_MENUPANE )
        {
        if ( iContainer )
            {
            iCurrentItem = iContainer->CurrentItemIndex();
            }

        if ( IsChangeCommandVisibleL() )
            {
            // Remove Set screensaver, if current selection is already active.
            aMenuPane->SetItemDimmed( EPslnCmdAppSetScreenSaver, ETrue );
            }
        else if ( IsApplyCommandVisibleL() )
            {
            // Remove Change screensaver if
            //  a) not active screensaver
            //  b) not of Date type
            //  c) installed screensaver is such that it does not have settings.
            aMenuPane->SetItemDimmed( EPslnCmdAppChangeScreenSaver, ETrue );
            }
        else
            {
            // when current focus and ticked item is Date.
            // a) do not show apply
            // b) do not show change
            aMenuPane->SetItemDimmed( EPslnCmdAppSetScreenSaver, ETrue );
            aMenuPane->SetItemDimmed( EPslnCmdAppChangeScreenSaver, ETrue );
            }

        // If it is System screen saver, or the plug-in doesn't allow editing
        // of settings, remove 'Settings' item.
        if ( ( iCurrentItem < KPslnSystemScreenSavers ) ||
             ( !iModel->ScreensaverHasCapability(
                   iCurrentItem, EScpCapsConfigure ) ) )
            {
            // Set Settings off.
            aMenuPane->SetItemDimmed( EPslnCmdAppSettings, ETrue );
            }
        }
    CPslnBaseView::DynInitMenuPaneL( aResourceId, aMenuPane );
    }

// -----------------------------------------------------------------------------
// CPslnScreenSaverView::HandleListBoxSelectionL
// -----------------------------------------------------------------------------
//
void CPslnScreenSaverView::HandleListBoxSelectionL()
    {
    if ( iContainer )
        {
        iCurrentItem = iContainer->CurrentItemIndex();
        }
    if ( IsChangeCommandVisibleL() )
        {
        HandleCommandL( EPslnCmdAppChangeScreenSaver );
        }
    else
        {    
        HandleCommandL( EPslnCmdAppSetScreenSaver );
        }
    }

// -----------------------------------------------------------------------------
// CPslnScreenSaverView::HandleListBoxItemHighlightL
// -----------------------------------------------------------------------------
//
void CPslnScreenSaverView::HandleListBoxItemHighlightL()
    {    
    }

// -----------------------------------------------------------------------------
// CPslnScreenSaverView::NewContainerL
// -----------------------------------------------------------------------------
//
void CPslnScreenSaverView::NewContainerL()
    {
    iContainer = new (ELeave) CPslnScreenSaverContainer();
    iContainer->SetMiddleSoftkeyObserver( this );
    }

// -----------------------------------------------------------------------------
// CPslnScreenSaverView::SetTitlePaneL
// -----------------------------------------------------------------------------
//
void CPslnScreenSaverView::SetTitlePaneL( TInt& aResourceId )
    {
#ifdef RD_CONTROL_PANEL
    aResourceId = R_PSLN_TITLE_PANE_SCREENSAVER;
#endif //RD_CONTROL_PANEL
    }

// -----------------------------------------------------------------------------
// If wallpaper image has changed, update container.
// -----------------------------------------------------------------------------
//
void CPslnScreenSaverView::HandleNotifyInt( TUint32 /*aId*/, TInt /*aNewValue*/ )
    {

    TInt value = KErrNone;
    if ( iPreviewModeSubscriber )
        {
        iPreviewModeProperty.Get( value );
        }

    if( iContainer && ( value == KPslnScreenSaverPreviewOff ) )
        {
        // Update container.
        TRAP_IGNORE(
            static_cast<CPslnScreenSaverContainer*>
                (iContainer)->UpdateListBoxL() );
        }
    }

// -----------------------------------------------------------------------------
// If the whole repository changes, update container.
// -----------------------------------------------------------------------------
//
void CPslnScreenSaverView::HandleNotifyGeneric( TUint32 aId )
    {
    if (  aId == NCentralRepositoryConstants::KInvalidNotificationId || iContainer )
        {
        // Update container.
        TRAP_IGNORE(
            static_cast<CPslnScreenSaverContainer*>
                (iContainer)->UpdateListBoxL() );
        }
    }

// -----------------------------------------------------------------------------
// In case of error, try to re-start listening.
// -----------------------------------------------------------------------------
//
void CPslnScreenSaverView::HandleNotifyError(
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
// CPslnScreenSaverView::HandleScreenSaverActivationL
// -----------------------------------------------------------------------------
//
void CPslnScreenSaverView::HandleScreenSaverActivationL( TInt aCurrentItem )
    {
    TInt PsmMode = 0; 
    iPsmClient->PsmSettings().GetCurrentMode( PsmMode );
    if ( PsmMode == EPsmsrvModePowerSave ) // PSM on, setting is protected
        {
        HBufC* buf = StringLoader::LoadLC( R_PSLN_QTN_PSM_INFONOTE );
        CAknInformationNote* note = new (ELeave) CAknInformationNote( ETrue );
        note->ExecuteLD( *buf );
        CleanupStack::PopAndDestroy( buf );
        return;
        }
    
    TRAPD( err, DoInvokeScreenSaverFunctionL(
        aCurrentItem,
        EScpCapsSelectionNotification ) );

    if ( err == KErrNone )
        {        
        TRAPD( seterr,iModel->SetCurrentPropertyTypeL(
            KPslnScreenSettingId,
            aCurrentItem ) );
        if( seterr == KErrCancel )
            {
            return;
            }
        else
            {
            User::LeaveIfError( seterr );
            }

        if ( iContainer )
            {
            // Update container.
            static_cast<CPslnScreenSaverContainer*>
                (iContainer)->UpdateListBoxL();
            }
        CheckMiddleSoftkeyLabelL();
        }
    
    return;
    }

// -----------------------------------------------------------------------------
// CPslnScreenSaverView::HandleScreenSaverPreviewL
// -----------------------------------------------------------------------------
//
void CPslnScreenSaverView::HandleScreenSaverPreviewL( TInt aCurrentItem )
    {
    TRAPD( err, DoInvokeScreenSaverFunctionL(
        aCurrentItem,
        EScpCapsPreviewNotification ) );

    if ( err == KErrNone )
        {        
        // Start listening for screensaver preview mode key changes.
        CreatePreviewModeSubscriberL();
        CreatePreviewStateSubscriberL();
        
        User::LeaveIfError(
            iModel->ActivateScreenSaver(
                aCurrentItem,
                EPslnScreenSaverPreviewActivation ) );       
        }
    
    return;
    }

// -----------------------------------------------------------------------------
// CPslnScreenSaverView::HandleScreenSaverSettingsL
// -----------------------------------------------------------------------------
//
void CPslnScreenSaverView::HandleScreenSaverSettingsL( TInt aCurrentItem )
    {
    // Indicate to the plugin that active screensaver is possibly modified.
    // Configure plugin.
    TRAP_IGNORE( DoInvokeScreenSaverFunctionL(
        aCurrentItem,
        EScpCapsConfigure ) );
    }

// -----------------------------------------------------------------------------
// Non-Leaving version of wait note launching.
// -----------------------------------------------------------------------------
//
void CPslnScreenSaverView::LaunchNote()
    {
    TRAP_IGNORE( LaunchNoteL() );
    }

// -----------------------------------------------------------------------------
// Launches wait note.
// -----------------------------------------------------------------------------
//
void CPslnScreenSaverView::LaunchNoteL()
    {
    HBufC* noteText = StringLoader::LoadLC( R_PSLN_QTN_GEN_NOTE_OPENING  );

    if ( !iWaitDlg )
        {
        // Create note and launch it.
        CAknWaitDialog* requestingNote = new(ELeave) CAknWaitDialog(
            (REINTERPRET_CAST( CEikDialog**, &iWaitDlg ) ), ETrue );
        iWaitDlg = requestingNote;
        requestingNote->PrepareLC( R_PSLN_GENERAL_WAIT_NOTE );
        if ( noteText )
            {
            requestingNote->SetTextL( noteText->Des() );
            }
        requestingNote->RunLD();
        }

    CleanupStack::PopAndDestroy( noteText );
    }

// -----------------------------------------------------------------------------
// Non-Leaving version of wait note removal.
// -----------------------------------------------------------------------------
//
void CPslnScreenSaverView::RemoveNote()
    {
    TRAP_IGNORE( RemoveNoteL() );
    }

// -----------------------------------------------------------------------------
// Removes opening note and stops listening for preview state changes.
// -----------------------------------------------------------------------------
//
void CPslnScreenSaverView::RemoveNoteL()
    {
    // Stop listening for preview mode changes.
    if ( iPreviewStateSubscriber )
        {
        iPreviewStateSubscriber->Cancel();
        }
    // Remove wait note.
    if ( iWaitDlg )
        {
        iWaitDlg->ProcessFinishedL();
        iWaitDlg = NULL;
        }
    }

// -----------------------------------------------------------------------------
// Invokes screensaver function.
// -----------------------------------------------------------------------------
//
void CPslnScreenSaverView::DoInvokeScreenSaverFunctionL(
    const TInt aCurrentItem, const TScPluginCaps aType )
    {
    // Offer selection notification, if requested by the saver
    if( iModel && iModel->ScreensaverHasCapability(
        aCurrentItem,
        aType ) )
        {
        iModel->InvokeSSPluginFunctionL(
            aCurrentItem,
            aType );
        }
    }

// -----------------------------------------------------------------------------
// Creates subscriber and starts to listen.
// -----------------------------------------------------------------------------
//
void CPslnScreenSaverView::CreatePreviewModeSubscriberL()
    {
    if ( !iPreviewModeSubscriber )
        {
        iPreviewModeSubscriber =
            new (ELeave) CPslnPropertySubscriber(
                TCallBack( HandlePreviewModeChanged, this ),
                iPreviewModeProperty );
        }
    iPreviewModeSubscriber->Subscribe();
    }

void CPslnScreenSaverView::CreatePreviewStateSubscriberL()
    {
    if ( !iPreviewStateSubscriber )
        {
        iPreviewStateSubscriber =
            new (ELeave) CPslnPropertySubscriber(
                TCallBack( HandlePreviewStateChanged, this ),
                iPreviewStateProperty );
        }
    iPreviewStateSubscriber->Subscribe();
    }

// -----------------------------------------------------------------------------
// Remove unnecessary commands from Middle softkey.
// -----------------------------------------------------------------------------
//
void CPslnScreenSaverView::RemoveCommandFromMSK()
    {
    CEikButtonGroupContainer* cbaGroup = Cba();
    if ( cbaGroup )
        {
        cbaGroup->RemoveCommandFromStack( KPslnMSKControlID, EPslnCmdAppSetScreenSaver );
        }
    }

// -----------------------------------------------------------------------------
// Is 'Change' command visible or not.
// -----------------------------------------------------------------------------
//
TBool CPslnScreenSaverView::IsChangeCommandVisibleL() const
    {
    if ( !iContainer )
        {
        return EFalse;
        }

    TInt currentItem = KErrNotFound;
    currentItem = iContainer->CurrentItemIndex();

    // Remove Change screensaver if
    //  a) not active screensaver
    //  b) not of Date type
    //  c) installed screensaver is such that it does not have settings.
    if ( currentItem == iModel->CurrentPropertyIndexL( KPslnScreenSettingId ) &&
       iModel->ScreensaverHasCapability( currentItem, EScpCapsConfigure ) )
        {
        return ETrue;
        }

    return EFalse;
    }


// -----------------------------------------------------------------------------
// Is the focus item the same as the setting
// -----------------------------------------------------------------------------
//
TBool CPslnScreenSaverView::IsApplyCommandVisibleL() const
    {
    if ( !iContainer )
        {
        return EFalse;
        }

    TInt currentItem = KErrNotFound;
    currentItem = iContainer->CurrentItemIndex();

    // Remove Apply screensaver if
    //  a) the focused item is the same as ticked 
    //  c) 

    TBool retVal = ETrue;
    if ( currentItem == iModel->CurrentPropertyIndexL( KPslnScreenSettingId ))
        {
        retVal = EFalse;
        }
    return retVal;
    }


// -----------------------------------------------------------------------------
// Called when the power save mode is changed.
// -----------------------------------------------------------------------------
//
void CPslnScreenSaverView::PowerSaveModeChanged( const TPsmsrvMode /*aMode*/ )
	{
	TRAP_IGNORE( iContainer->SetCurrentItemIndexAndDraw(
        iModel->CurrentPropertyIndexL( KPslnScreenSettingId ) ) );
	TRAP_IGNORE( CheckMiddleSoftkeyLabelL() );	
	
	if ( iPsmClient )
		{
	    iPsmClient->RequestPowerSaveModeNotification();	
		}    
	}


// -----------------------------------------------------------------------------
// Called when some wrong with the power save mode change.
// -----------------------------------------------------------------------------
//
void CPslnScreenSaverView::PowerSaveModeChangeError( const TInt /*aError*/ )
	{
	}


//  End of File
