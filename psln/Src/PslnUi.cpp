/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  UI class of Psln.
*
*/


// INCLUDE FILES

#include "PslnUi.h"

#include <barsread.h>
#include <StringLoader.h>

// Navi pane, Title Pane & Tab groups
#include <aknnavi.h>
#include <aknnavide.h>
#include <akntitle.h>

// Notes & Dialogs
#include <AknGlobalNote.h>
#include <aknnotewrappers.h>
#include <AknWaitDialog.h> 

// DRM.
#include <DRMHelper.h>
#include <DRMRights.h>

// Psln specific.
#include <psln.rsg>
#include "PslnModel.h"
#include "PslnSkinEntry.h"
#include "PslnFeatures.h"
#include "PslnSoundActivator.h"
#include "pslntaskactivatesounds.h"
#include "pslntaskgenericupdate.h"
#include "pslnidletaskcreateviews.h"
#include "PslnConst.h"
#include "PslnDebug.h"
#include "PslnModel.h"
#include "PslnPropertySubscriber.h"

// Views
#include "PslnMainView.h"
#include "PslnGeneralThemeView.h"
#include "PslnScreenSaverView.h"
#include "PslnWallpaperView.h"

// Framework
#include "PslnPluginHandler.h"
#include <pslnfwplugininterface.h>
#include <pslnfwbaseview.h>

// Help texts
#include <hlplch.h>
#include <csxhelp/skins.hlp.hrh>
#include <UsbWatcherInternalPSKeys.h>           // KPSUidUsbWatcher
#include <usbpersonalityids.h>                  // Usb Personality Ids

// Sets internal state correctly when leave occurs in skin changing.

// Handles application exit correctly when leave occurs in exiting.
void HandleExitLeave( TAny* aPtr )
    {
    CPslnUi* psln = static_cast<CPslnUi*>(aPtr);
    psln->HandleCmdExitLeave();
    }

// ========================= MEMBER FUNCTIONS ================================
// ---------------------------------------------------------------------------
// C++ constructor can NOT contain any code, that might leave.
// ---------------------------------------------------------------------------
//
CPslnUi::CPslnUi() : iPslnUiStatus ( EPslnCreated )
    {
    }

// ---------------------------------------------------------------------------
// Symbian two-phased constructor.
// ---------------------------------------------------------------------------
//
void CPslnUi::ConstructL()
    {
    PSLN_TRACE_DEBUG1("CPslnUi::ConstructL, Start:%d", User::NTickCount() );

    BaseConstructL( EAknEnableSkin | EAknEnableMSK | EAknSingleClickCompatible );
    EnableExternalViewSwitches(ETrue);

    // Create ECOM plugin loader.
    PSLN_TRACE_DEBUG("CPslnUi::ConstructL PluginHandler");
    iPluginHandler = CPslnPluginHandler::NewL( this );

    PSLN_TRACE_DEBUG("CPslnUi::ConstructL Model");
    // Force creation of model, since it is anyway created when ANY view is
    // activated.
    CreateModelL();

    PSLN_TRACE_DEBUG("CPslnUi::ConstructL StatusPane");
    // Show tabs for main views from resources
    CEikStatusPane* sp = StatusPane();
    if ( sp )
        {
        // Fetch pointer to the default navi pane control
        iNaviPane = (CAknNavigationControlContainer*)sp->ControlL(
            TUid::Uid(EEikStatusPaneUidNavi));
        }

    // New main view
    PSLN_TRACE_DEBUG("CPslnUi::ConstructL View-Main");
    CPslnMainView* view = CPslnMainView::NewLC();
    AddViewL( view );          // transfer ownership to CAknViewAppUi
    CleanupStack::Pop( view ); // the view has to be popped from cleanupstack here
    iMainView = view;
    SetDefaultViewL( *view );

    iIdleActivateSkin = CIdle::NewL( CActive::EPriorityIdle );
    iIdleUpdateSkin = CIdle::NewL( CActive::EPriorityIdle );
    
    PSLN_TRACE_DEBUG("CPslnUi::ConstructL OK");
    User::LeaveIfError( iEnableUSBWatchProperty.Attach(
          KPSUidUsbWatcher, KUsbWatcherSelectedPersonality) );
    iUSBWatchSubscriber = new (ELeave) CPslnPropertySubscriber(
        TCallBack(USBCallBackL, this), iEnableUSBWatchProperty );
    iUSBWatchSubscriber->Subscribe();
    
    
    TInt value = KErrNone;
    iEnableUSBWatchProperty.Get(value);
    if (value == KUsbPersonalityIdMS)
        {
        iUSBAttached = ETrue;
        }
    else
        {
        iUSBAttached = EFalse;
        }
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CPslnUi::~CPslnUi()
    {
    PSLN_TRACE_DEBUG("CPslnUi::Destructor");

    HideProgressBar();
    // Reset skin info when exiting normally. This prevents model class
    // from trying to revert back to previous skin.
    if ( iView && iView->Id().iUid == KPslnMainView2.iUid )
        {
        // It is possible that Model is not created, if exiting immediately after
        // application launch. So first check that Model is created.
        if ( iModel )
            {
            TInt currentlySelected = iModel->ActiveSkinIndex();
            iModel->SetCurrentSelectedSkinIndex( currentlySelected );
            }
        }
    delete iModel;
    // This nullification is needed, since external DLL's may try to access
    // model through view framework and it might succeed even if model and UI
    // classes are already deleted, but external DLLs aren't.
    // This is due to that model reference is passed as a pointer due to delayed
    // construction - it is not available at the time when view is constructed.
    iModel = NULL;
    delete iDecoratedTabGroup;

    if ( iPluginHandler )
        {
        delete iPluginHandler;
        }

    delete iIdleTask;
    delete iIdleActivateSkin;
    delete iIdleUpdateSkin;
    
    
    if( iUSBWatchSubscriber )
        {
        iUSBWatchSubscriber->Cancel();
        }
    iEnableUSBWatchProperty.Close();
    delete iUSBWatchSubscriber;
    }

// ---------------------------------------------------------------------------
// Handles event when focus loss or gain.
// ---------------------------------------------------------------------------
//
void CPslnUi::HandleWsEventL( const TWsEvent& aEvent, CCoeControl* aDestination )
    {
    PSLN_TRACE_DEBUG("CPslnUi::HandlwWSEvent");
    if ( iView )
        {
        TInt eventType = aEvent.Type();
        TUid currentView = iView->Id();

        // do this everytime when foreground gained.
        if ( ( currentView.iUid == KPslnGeneralView.iUid ) &&
             ( eventType == EEventFocusGained ) &&
             ( GetStatus( EPslnListUpdateNeeded )  ||
               GetStatus( EPslnProtectedSkinInList ) ) && IsForeground() )
            {
            PSLN_TRACE_DEBUG("CPslnUi::HandlwWSEvent Update list");
            SetStateOff( EPslnListUpdateNeeded );
            DoCreateWaitNoteL();
            }
        }
    CAknViewAppUi::HandleWsEventL( aEvent, aDestination );
    }

// ---------------------------------------------------------------------------
// Handles commands directed to this class.
// ---------------------------------------------------------------------------
//
void CPslnUi::HandleCommandL( TInt aCommand )
    {
    PSLN_TRACE_DEBUG1("CPslnUi::HandleCommand %d", aCommand );
    switch ( aCommand )
        {
        //both exit commands should do the same thing
        case EEikCmdExit:
        case EAknCmdExit:
        case EAknSoftkeyExit:
            HandleCmdExitL();
            break;

        case EPslnCmdAppActivate:
            {
            if (!iIdleActivateSkin->IsActive())
                {
                iIdleActivateSkin->Start(TCallBack( DoActivateSkinL, this ));
                }
            }
            break;
        case EPslnCmdAppDownload:
            DownloadSkinL();
            break;
        case EAknCmdHelp:
        case EPslnCmdAppHelp:
            {
            HlpLauncher::LaunchHelpApplicationL(
                iEikonEnv->WsSession(), AppHelpContextL());
            }
            break;
        case EAknSoftkeyBack:
            // If General view is active and Back key is
            // pressed and there is skin activation ongoing
            // set internal state off.
            if ( iView && GetStatus( EPslnSkinChangeRequested ) &&
                   ( iView->Id().iUid == KPslnGeneralView.iUid )  )
                {
                SetStateOff( EPslnSkinChangeRequested );
                }
            ActivateLocalViewL( KPslnMainView2 );
            break;
        default:
            CAknViewAppUi::HandleCommandL( aCommand );
            break;
        }
    }

// ---------------------------------------------------------------------------
// CPslnUi::HandleResourceChangeL
// ---------------------------------------------------------------------------
//
void CPslnUi::HandleResourceChangeL( TInt aType )
    {
    PSLN_TRACE_DEBUG("CPslnUi::HandleResourceChangeL");
    if (  iView && !GetStatus( EPslnSkinChangeRequested ) &&
          iView->Id().iUid == KPslnGeneralView.iUid &&
          aType == KAknsMessageSkinChange )
        {
        iGeneralThemeView->UpdateSkinListItemsDColumnOnlyL();
        }
    CAknViewAppUi::HandleResourceChangeL( aType );
    }

// ---------------------------------------------------------------------------
// CPslnUi::ActivateLocalViewL
// ---------------------------------------------------------------------------
//
void CPslnUi::ActivateLocalViewL( TUid aViewId )
    {
    if ( GetStatus( EPslnListUpdateNeeded ) &&
         ( aViewId.iUid == KPslnGeneralView.iUid ) )
        {
        PSLN_TRACE_DEBUG("CPslnUi::ActivateLocalViewL update list");
        SetStateOff( EPslnListUpdateNeeded );
        DoCreateWaitNoteL();
        }
    CAknViewAppUi::ActivateLocalViewL( aViewId );
    }

// ---------------------------------------------------------------------------
// CPslnUi::SkinContentChanged
// ---------------------------------------------------------------------------
//
void CPslnUi::SkinContentChanged()
    {
    PSLN_TRACE_DEBUG("CPslnUi::SkinContentChanged");
    if ( !iView || iView->Id().iUid != KPslnGeneralView.iUid  )
        {
        SetStateOn( EPslnListUpdateNeeded );
        }
    }

// ---------------------------------------------------------------------------
// CPslnUi::SkinConfigurationChanged
// ---------------------------------------------------------------------------
//
void CPslnUi::SkinConfigurationChanged(
    const TAknsSkinStatusConfigurationChangeReason aReason )
    {
    PSLN_TRACE_DEBUG("CPslnUi::SkinConfigurationChanged");
    TRAPD( err, SkinConfigurationChangedL( aReason ) );
    if ( err != KErrNone )
        {
        TRAP_IGNORE( iGeneralThemeView->UpdateSkinListItemsL() );
        }
    }

// ---------------------------------------------------------------------------
// CPslnUi::SkinPackageChanged
// ---------------------------------------------------------------------------
//
void CPslnUi::SkinPackageChanged(
    const TAknsSkinStatusPackageChangeReason aReason )
    {
    PSLN_TRACE_DEBUG("CPslnUi::SkinPackageChanged");
    if ( aReason == EAknsSkinStatusPackageListUpdate )
        {
        if ( !iView || iView->Id().iUid != KPslnGeneralView.iUid )
            {
            SetStateOn( EPslnListUpdateNeeded );
            }
        else
            {
            PSLN_TRACE_DEBUG("CPslnUi::SkinPackageChanged update list");
            //To Fix Defect:ESNN-7CXCT2:Themes: Layout is incorrect 
            //when removing memory card which the active theme is installed in.
            //DoCreateWaitNoteL take too much time and stop the skin refresh.
            //Need to wait for the Skin Server finish its work,so we use CIdle.
            //Also we need User::After to delay some time to make sure 
            //iIdleUpdateSkin start late enough.
            User::After(KPslnUpdateSkinDelay);
            if (!iIdleUpdateSkin->IsActive())
                {
                iIdleUpdateSkin->Start(TCallBack( DoCreateWaitNoteL, this ));
                }
            SetStateOff( EPslnListUpdateNeeded );
            }
        }
    }

// ---------------------------------------------------------------------------
// Return model pointer.
// ---------------------------------------------------------------------------
//
CPslnModel* CPslnUi::Model() const
    {
    return iModel;
    }

// ---------------------------------------------------------------------------
// Updates tab group to current tab index
// The parameters are optional.
// ---------------------------------------------------------------------------
//
#ifdef RD_CONTROL_PANEL
void CPslnUi::UpdateTabIndex( const TInt aMyId, const TInt /*aMyTabIndex*/ )
#else
void CPslnUi::UpdateTabIndex( const TInt /*aMyId*/, const TInt aMyTabIndex )
#endif // RD_CONTROL_PANEL
    {
#ifdef RD_CONTROL_PANEL
    if ( aMyId != KErrNotFound )
        {
        if ( iMainView )
            {
            iMainView->SetActiveFolder( TUid::Uid( aMyId ) );
            }
        }
#else
    if ( aMyTabIndex != KErrNotFound )
        {
        if ( iTabGroup )
            {
            iTabGroup->SetActiveTabById( aMyTabIndex );
            }
        }
    if ( ( iView == iMainView ) && iTabGroup && iMainView )
        {
        iTabGroup->SetActiveTabByIndex( iMainView->ActiveView() );
        }
#endif //RD_CONTROL_PANEL
    }

// ---------------------------------------------------------------------------
// Creates given view.
// ---------------------------------------------------------------------------
//
void CPslnUi::CreateViewL( TUid aViewUid )
    {
    PSLN_TRACE_DEBUG1("CPslnUi::CreateViewL, Start:%d", User::NTickCount() );
    TBitFlags views = ViewSupport();

if ( aViewUid == KPslnWallpaperView &&
              !GetStatus( EPslnWallpaperViewCreated ) )
        {

        if ( views.IsSet( EPslnWallpaperView ) )
            {
            CAknView* view = CPslnWallpaperView::NewLC();
            AddViewL( view );          // transfer ownership to CAknViewAppUi
            CleanupStack::Pop( view );

            SetStateOn( EPslnWallpaperViewCreated );

            PSLN_TRACE_DEBUG("CPslnUi::CreateViewL - Wallpaper");
            PSLN_TRACE_DEBUG1("CPslnUi::CreateViewL, End:%d", User::NTickCount() );
            }
        }
    // Screensaver view.
    else if ( aViewUid == KPslnScreenSaverView &&
              !GetStatus( EPslnScreenSaverViewCreated ) )
        {
        if ( views.IsSet( EPslnScreensaverView ) )
            {
            CAknView* view = CPslnScreenSaverView::NewLC();
            AddViewL( view );          // transfer ownership to CAknViewAppUi
            CleanupStack::Pop( view );

            SetStateOn( EPslnScreenSaverViewCreated );

            PSLN_TRACE_DEBUG("CPslnUi::CreateViewL - ScreenSaver");
            PSLN_TRACE_DEBUG1("CPslnUi::CreateViewL, End:%d", User::NTickCount() );
            }
        }
    // General view.
    else if ( aViewUid.iUid == KPslnGeneralView.iUid &&
              !GetStatus( EPslnGeneralViewCreated ) )
        {
        CAknView* view = CPslnGeneralThemeView::NewLC();
        AddViewL( view );          // transfer ownership to CAknViewAppUi
        iGeneralThemeView = static_cast< CPslnGeneralThemeView* >( view );
        CleanupStack::Pop( view );

        SetStateOn( EPslnGeneralViewCreated );

        PSLN_TRACE_DEBUG("CPslnUi::CreateViewL - General");
        PSLN_TRACE_DEBUG1("CPslnUi::CreateViewL, End:%d", User::NTickCount() );
        }
    }

// ---------------------------------------------------------------------------
// Return navi control container pointer.
// ---------------------------------------------------------------------------
//
CAknNavigationControlContainer* CPslnUi::NaviContainer() const
    {
    return iNaviPane;
    }

// ---------------------------------------------------------------------------
// Return tab group pointer.
// ---------------------------------------------------------------------------
//
CAknNavigationDecorator* CPslnUi::PslnTabGroup()
    {
     if ( !GetStatus( EPslnTabGroupCreated ) )
         {
         TRAP_IGNORE( ConstructTabGroupL() );
         }
    return iDecoratedTabGroup;
    }

// ---------------------------------------------------------------------------
// Return plugin handler pointer.
// ---------------------------------------------------------------------------
//
CPslnPluginHandler* CPslnUi::PluginHandler() const
    {
    return iPluginHandler;
    }

// ---------------------------------------------------------------------------
// Adds new view to UI class, if the UI class is not already completed.
// ---------------------------------------------------------------------------
//
void CPslnUi::AddNewViewL( CAknView* aNewView )
    {
    if ( GetStatus( EPslnCreated ) )
        {
        if ( aNewView && !View( aNewView->Id() ) )
            {
            AddViewL( aNewView );
            }
        }
    }

// ---------------------------------------------------------------------------
// When this method is called, UI class considers itself to be complete.
// ---------------------------------------------------------------------------
//
void CPslnUi::AllViewsDone()
    {
    SetStateOff( EPslnCreated );
    }

// ---------------------------------------------------------------------------
// Handles errors that occur when handling images.
// ---------------------------------------------------------------------------
//
void CPslnUi::HandleImageErrorsL( TInt aError )
    {
    PSLN_TRACE_DEBUG1("CPslnUi::HandleImageError %d", aError );
    if ( aError == KErrNoMemory || aError == KErrTooBig )
        {
        // Show information note
        HBufC* prompt = iCoeEnv->AllocReadResourceLC( R_PSLN_IMAGE_TOO_LARGE );
        CAknInformationNote* note = new (ELeave) CAknInformationNote( ETrue );
        note->ExecuteLD( *prompt );
        CleanupStack::PopAndDestroy( prompt );
        }
    else if ( aError == KErrCancel || aError == KErrCouldNotConnect )
        {
        // Other error codes are ignored; as not real errors (i.e. KErrCancel),
        // or such errors that Psln cannot react to them (KErrCouldNotConnect)
        }
    else
        {
        // Show information note
        HBufC* prompt = iCoeEnv->AllocReadResourceLC( R_PSLN_IMAGE_CORRUPTED );
        CAknInformationNote* note = new (ELeave) CAknInformationNote( ETrue );
        note->ExecuteLD( *prompt );
        CleanupStack::PopAndDestroy( prompt );
        }
    }

// ---------------------------------------------------------------------------
// Indicate that tab group has been changed.
// ---------------------------------------------------------------------------
//
#ifndef RD_CONTROL_PANEL
void CPslnUi::TabChangedL( TInt aIndex )
    {
    PSLN_TRACE_DEBUG("CPslnUi::TabChangedL 1" );
    // If it is one of the dynamically created views, check if the view is
    // already created. If view is not created, create it.
    if ( aIndex == KPslnGeneralView.iUid )
        {
        if ( !GetStatus( EPslnGeneralViewCreated ) )
            {
            CreateViewL( KPslnGeneralView );
            }
        }
    else if ( aIndex == KPslnWallpaperView.iUid )
        {
        if ( !GetStatus( EPslnWallpaperViewCreated ) )
            {
            CreateViewL( KPslnWallpaperView );
            }
        }
    else if ( aIndex == KPslnScreenSaverView.iUid )
        {
        if ( !GetStatus( EPslnScreenSaverViewCreated ) )
            {
            CreateViewL( KPslnScreenSaverView );
            }
        }
    if ( iMainView )
        {
        iMainView->SetActiveFolder( aIndex );
        ActivateLocalViewL( TUid::Uid( iMainView->ActiveFolderUid() ) );
        }
    }
#endif //RD_CONTROL_PANEL

// ---------------------------------------------------------------------------
// Loads views when application is idle.
// ---------------------------------------------------------------------------
//
void CPslnUi::LoadViewsWhenIdleL()
    {
    if ( !iIdleTask )
        {
        iIdleTask = CPslnIdleTaskCreateViews::NewL( this );
        }
    }

// ---------------------------------------------------------------------------
// Constructs the Tab group.
// ---------------------------------------------------------------------------
void CPslnUi::ConstructTabGroupL()
    {
#ifdef RD_CONTROL_PANEL
    return;
#else
    if ( GetStatus( EPslnTabGroupCreated ) )
        {
        // Tabgroup has already been created.
        return;
        }
    // Tabgroup has been read from resource and it were pushed to the navi pane.
    // Get pointer to the navigation decorator
    // and set this to be a MAknTabObserver.
    if ( iNaviPane )
        {
        iDecoratedTabGroup = iNaviPane->ResourceDecorator();
        }
    if ( iDecoratedTabGroup )
        {
        PSLN_TRACE_DEBUG("CPslnUi::ConstructTabGroupL DecoTabGrp");
        iTabGroup = static_cast <CAknTabGroup*>
            ( iDecoratedTabGroup->DecoratedControl() );
        iTabGroup->SetObserver( this );
        }
    TInt tabCount = 1; // index 0 = general view
    TBitFlags views = ViewSupport();

    // Update Tab group to contain default plugins.
    if ( iPluginHandler )
        {
        CPslnFWPluginInterface* plugin =
            iPluginHandler->GetPlugin( KPslnASPluginUid );
        if ( plugin )
            {
            AddPluginToTab( *plugin );
            static_cast <CPslnFWBaseView*>
                (plugin)->SetNaviPaneDecorator( iDecoratedTabGroup );
            tabCount++; // index 1 = AS plugin
            }
        plugin = iPluginHandler->GetPlugin( KPslnAIPluginUid );
        if ( plugin )
            {
            AddPluginToTab( *plugin );
            static_cast <CPslnFWBaseView*>
                (plugin)->SetNaviPaneDecorator( iDecoratedTabGroup );
            tabCount++; // index 2 = AI plugin
            }
        }

    // Add tabs for screen saver and wallpaper.
    if ( iTabGroup )
        {
        if ( views.IsSet( EPslnWallpaperView ) )
            {
            TResourceReader reader;
            iCoeEnv->CreateResourceReaderLC( reader, R_PSLN_WALLPAPER_TAB );
            iTabGroup->AddTabL( reader );
            CleanupStack::PopAndDestroy(); // reader - AppUi now owns this tab,
            tabCount++; // index 3 = Wallpaper view
            }

        if ( views.IsSet( EPslnScreensaverView ) )
            {
            TResourceReader reader2;
            iCoeEnv->CreateResourceReaderLC( reader2, R_PSLN_SCREENSAVER_TAB );
            iTabGroup->AddTabL( reader2 );
            CleanupStack::PopAndDestroy(); // reader2  - AppUi now owns this tab,
            tabCount++; // index 4 = Screensaver view
            }
        PSLN_TRACE_DEBUG("CPslnUi::ConstructTabGroupL Default Tabs added to TabGrp");
        }

    // Add rest of the plugins to tabs.
    if ( iPluginHandler )
        {
        // Fetch the plugin array.
        CArrayPtrFlat<CPslnFWPluginInterface>* pluginArray =
            iPluginHandler->GetPluginArray();
        CleanupStack::PushL( pluginArray );
        TInt pluginCount = pluginArray->Count();
        PSLN_TRACE_DEBUG1("CPslnUi::ConstructTabGroupL Plugin count=%d", pluginCount );

        // Go through all the plugins and add plugins to tab group.
        for ( TInt i = 0; i < pluginCount; i++ )
            {
            CPslnFWPluginInterface* plugin = pluginArray->operator[]( i );

            if ( !plugin )
                {
                PSLN_TRACE_DEBUG("CPslnUi::ConstructTabGroupL Plugin fails");
                }
            // Default plugins can be skipped.
            else if ( plugin->Id().iUid == KPslnASPluginUid.iUid ||
                      plugin->Id().iUid == KPslnAIPluginUid.iUid )
                {
                PSLN_TRACE_DEBUG("CPslnUi::ConstructTabGroupL Plugin skipped");
                }
            else
                {
                PSLN_TRACE_DEBUG1("CPslnUi::ConstructTabGroupL Plugin Id=%d", plugin->Id().iUid );
                AddPluginToTab( *plugin );
                static_cast <CPslnFWBaseView*>
                    (plugin)->SetNaviPaneDecorator( iDecoratedTabGroup );
                // Inform to the plugin which tab index it is using.
                static_cast <CPslnFWBaseView*>
                    (plugin)->SetTabIndex( tabCount++ );
                PSLN_TRACE_DEBUG("CPslnUi::ConstructTabGroupL Plugin added to tab");
                }
            }
        CleanupStack::Pop( pluginArray ); // plugin handler owns plugin array
        }
    // Push empty navi pane, so that tab group is not shown with default item (first),
    // if other than main view is activated externally.
    iNaviPane->PushDefaultL();
    SetStateOn( EPslnTabGroupCreated );
#endif //RD_CONTROL_PANEL
    }


// ---------------------------------------------------------------------------
// Is this class able to handle a new skin activation related command.
// ---------------------------------------------------------------------------
TBool CPslnUi::IsReadyToHandleCommands()
    {
    return !GetStatus( EPslnSkinChangeRequested );
    }

// ---------------------------------------------------------------------------
// Ensure that Exit() is called when trying to exit and leave occurs.
// ---------------------------------------------------------------------------
void CPslnUi::HandleCmdExitLeave()
    {
    Exit();
    }

// ---------------------------------------------------------------------------
// Sets title pane back to default text.
// ---------------------------------------------------------------------------
void CPslnUi::SetTitleToDefaultL()
    {
    // Set default title back. But do not change title when application is about
    // to die.
    if ( iCoeEnv && Model() )
        {
        TResourceReader rReader;
        iCoeEnv->CreateResourceReaderLC( rReader, R_PSLN_SKIN_LIST_VIEW_TITLE );
        if ( iAvkonAppUi )
            {
            CEikStatusPane* sp = iAvkonAppUi->StatusPane();
            if ( sp )
                {
                CAknTitlePane* title = static_cast<CAknTitlePane*>(
                    sp->ControlL( TUid::Uid( EEikStatusPaneUidTitle ) ) );

                if ( title )
                    {
                    title->SetFromResourceL( rReader );
                    }
                }
            }
        CleanupStack::PopAndDestroy(); // rReader
        }
    }

// ---------------------------------------------------------------------------
// Checks if a view has been created.
// ---------------------------------------------------------------------------
TBitFlags CPslnUi::ViewSupport()
    {
    // Initially all views are 'on'.
    TBitFlags viewFlags;
    viewFlags.SetAll();
    if ( GetStatus( EPslnViewSupportChecked ) )
        {
        if ( GetStatus( EPslnNoScreenSaverView ) )
            {
            viewFlags.Clear( EPslnScreensaverView );
            }
        if ( GetStatus( EPslnNoWallpaperView ) )
            {
            viewFlags.Clear( EPslnWallpaperView );
            }
        }
    else
        {
        TBool noWallpaperView = PslnFeatures::IsSupported( KPslnRemoveWallpaper );
        TBool noScreenSaverView = PslnFeatures::IsSupported( KPslnRemoveScreensaver );
        if ( noWallpaperView )
            {
            SetStateOn( EPslnNoWallpaperView );
            viewFlags.Clear( EPslnWallpaperView );
            }
        if ( noScreenSaverView )
            {
            SetStateOn( EPslnNoScreenSaverView );
            viewFlags.Clear( EPslnScreensaverView );
            }
        SetStateOn( EPslnViewSupportChecked );
        }
    return viewFlags;
    }

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
void CPslnUi::SetDRMProtectedSkinInSkinList(
    const TBool& aProtectedSkinInList )
    {
    if ( aProtectedSkinInList )
        {
        SetStateOn( EPslnProtectedSkinInList );
        }
    else
        {
        SetStateOff( EPslnProtectedSkinInList );
        }
    }


// -----------------------------------------------------------------------------
// Callback - USB status change.
// -----------------------------------------------------------------------------
//
TInt CPslnUi::USBCallBackL(TAny* aPtr)
    {
    CPslnUi* self = static_cast<CPslnUi*>(aPtr);
    if ( self )
        {
        self->HandleUSBCallBackL();
        }
    return KErrNone;
    }
    
    
    /**
    * USB Attach State.
    * @return ETrue when USB already attached, otherwise EFalse,
    */
// ---------------------------------------------------------------------------
// USB Attach State.
// ---------------------------------------------------------------------------
TBool CPslnUi::USBAttachState()
    {
    return iUSBAttached;
    }

// ---------------------------------------------------------------------------
// Called when a key is pressed and no other class has catched the event.
// Handles only key events that are meant to control the tab group.
// ---------------------------------------------------------------------------
#ifdef RD_CONTROL_PANEL
TKeyResponse CPslnUi::HandleKeyEventL(
    const TKeyEvent& /*aKeyEvent*/, TEventCode /*aType*/ )
#else
TKeyResponse CPslnUi::HandleKeyEventL(
    const TKeyEvent& aKeyEvent, TEventCode aType )
#endif // RD_CONTROL_PANEL
    {
    PSLN_TRACE_DEBUG("CPslnUi::HandleKeyEventL");

#ifndef RD_CONTROL_PANEL
    // If tab group is not yet created, create it.
    if ( !GetStatus( EPslnTabGroupCreated ) )
        {
        ConstructTabGroupL();
        }
    iTabGroup = static_cast<CAknTabGroup*>
        ( iDecoratedTabGroup->DecoratedControl() );

    // Only forward key events to tabgroup when:
    //     1) TabGroup has been created (and is not NULL)
    //     2) Active view is not MainView (there is no tab group in Main)
    //     3) key event is either left key or right key
    if ( iTabGroup && iView && iView->Id().iUid != KPslnMainView2.iUid &&
         ( aKeyEvent.iScanCode == EStdKeyLeftArrow ||
           aKeyEvent.iScanCode == EStdKeyRightArrow ) )
        {
        PSLN_TRACE_DEBUG("CPslnUi::HandleKeyEventL forward event to Tab");
        // If preview is about to activate, cancel it.
        if ( GetStatus( EPslnSkinChangeRequested ) &&
             iView->Id().iUid == KPslnGeneralView.iUid )
            {
            SetStateOff( EPslnSkinChangeRequested );
            }

        return iTabGroup->OfferKeyEventL( aKeyEvent, aType );
        }
#endif // !RD_CONTROL_PANEL
    return EKeyWasNotConsumed;
    }

// ---------------------------------------------------------------------------
// CPslnUi::SkinConfigurationChangedL
// ---------------------------------------------------------------------------
//
void CPslnUi::SkinConfigurationChangedL(
    const TAknsSkinStatusConfigurationChangeReason aReason )
    {
    PSLN_TRACE_DEBUG1("CPslnUi::SkinConfigurationChangedL internal state before: %d", iPslnUiStatus );
    HBufC* errorBuf = NULL;

    switch( aReason )
        {
        // Skin activation failed due to OOM.
        // Set skin activation user activity off, so that subsequent attempts can be made.
        // Also, set error note text.
        // Finally, set skin activation attempt off and update skin list.
        case EAknsSkinStatusConfigurationFailedOOM:
            SetStateOff( EPslnSkinChangeRequested );
            errorBuf = StringLoader::LoadLC( R_PSLN_QTN_MEMLO_RAM_OUT_OF_MEM );
            if ( GetStatus( EPslnSkinActivated ) )
                {
                SetStateOff( EPslnSkinActivated );
                HideProgressBar();
                DoCreateWaitNoteL();
                }
            break;
        // Skin activation failed due to skin being corrupted.
        // Set skin activation user activity off, so that subsequent attempts can be made.
        // Also, set error note text.
        // Then set skin activation attempt off and update skin list.
        // Finally, activate default skin.
        case EAknsSkinStatusConfigurationFailedCorrupt:
            SetStateOff( EPslnSkinChangeRequested );
            iGeneralThemeView->HightlightDefaultSkin();
            errorBuf = StringLoader::LoadLC( R_PSLN_QTN_SKINS_ERROR_CORRUPTED );
            if ( GetStatus( EPslnSkinActivated ) )
                {
                SetStateOff( EPslnSkinActivated );
                HideProgressBar();
                DoCreateWaitNoteL();
                }
            SetStateOn( EPslnListUpdateNeeded );
            break;
        // Skin activation was success.
        // Set skin activation user activity off.
        // Show confirmation note about the skin change and set activation
        // request state off. Finally, check if there are sounds in the skin.
        case EAknsSkinStatusConfigurationDeployed:
            SetStateOff( EPslnSkinChangeRequested );
            if ( GetStatus( EPslnSkinActivated ) )
                {
                SetStateOff( EPslnSkinActivated );
                HideProgressBar();
                SkinDeployedL();
                }
            else // Theme changed by other app, update view.
                {
                iModel->PerformCompleteUpdateL();             
                iGeneralThemeView->UpdateSkinListItemsL( iModel->ActiveSkinIndex() + 
                                PslnFeatures::IsEnhancedEmbeddedLinksSupported() );
                }
            
            if ( GetStatus( EPslnSoundActivationPending ) )
                {
                SetStateOff( EPslnSoundActivationPending );
                ActivateSoundsL();
                }
            break;
        default:
            break;
        }

    if( errorBuf )
        {
        ShowErrorNoteL( *errorBuf );
        CleanupStack::PopAndDestroy( errorBuf );
        }
    PSLN_TRACE_DEBUG1("CPslnUi::SkinConfigurationChangedL internal state after: %d", iPslnUiStatus );
    }

// ---------------------------------------------------------------------------
// Activate a Skin.
// ---------------------------------------------------------------------------
//
void CPslnUi::ActivateSkinL()
    {
    PSLN_TRACE_DEBUG("CPslnUi::ActivateSkinL");
    TInt skinIndex = iModel->CurrentSelectedSkinIndex();

    CPslnSkinEntry* entry = iModel->VisibleSkin( skinIndex );
    if( !entry )
        {
        SetStateOff( EPslnSkinChangeRequested );
        return;
        }

    TBool showWaitNote = EFalse;
    TInt drmError = KErrNone;
    HBufC* errorBuf = NULL;

    PSLN_TRACE_DEBUG1("CPslnUi::ActivateSkinL entry->Protection: %d", entry->Protection() );
    switch ( entry->Protection() )
        {
        case EAknsSrvNoRights:
            drmError = CDRMRights::ENoRights;
            showWaitNote = ETrue;
            break;
        case EAknsSrvFutureRights:
            drmError = CDRMRights::ERightsExpired;
            break;
        case EAknsSrvExpiredRights:
            drmError = CDRMRights::ERightsExpired;
            showWaitNote = ETrue;
            break;
        default :
            break;
        }

    // DRMHelper handles the error.
    if ( drmError )
        {
        RAknsSrvSession skinsrv;
        User::LeaveIfError( skinsrv.Connect() );
        CleanupClosePushL( skinsrv );

        TInt fileserverhandle;
        TInt filehandle;
        fileserverhandle = skinsrv.OpenBitmapFile( entry->FullName(), filehandle );
        RFile file;
        User::LeaveIfError( file.AdoptFromServer( fileserverhandle, filehandle ) );
        CleanupClosePushL( file );

        TInt returnCode = KErrNone;
        PSLN_TRACE_DEBUG("CPslnUi::ActivateSkinL use DRMHelper to show the error note");
        CDRMHelper* drmhelper = CDRMHelper::NewLC( *CCoeEnv::Static() );
        returnCode = drmhelper->HandleErrorL(
            drmError,
            file );

        PSLN_TRACE_DEBUG1("CPslnUi::ActivateSkinL DRMHelper returns: %d", returnCode );
        if ( returnCode && showWaitNote )
            {
            if ( GetStatus( EPslnListUpdateNeeded ) )
                {
                SetStateOff( EPslnListUpdateNeeded );
                DoCreateWaitNoteL();
                }
            }
        SetStateOff( EPslnSkinChangeRequested );
        CleanupStack::PopAndDestroy( 3 ); // drmHelper, skinsrv, file
        }
    else
        {
        if ( entry->Protection() == EAknsSrvCountBased )
            {
            errorBuf = StringLoader::LoadLC( R_PSLN_QTN_DRM_PREV_RIGHTS_SET );
            }
        // Check for corruption.
        if ( entry->IsCorrupted() )
            {
            PSLN_TRACE_DEBUG("CPslnUi::ActivateSkinL corrupt skin!");
            errorBuf = StringLoader::LoadLC( R_PSLN_QTN_SKINS_ERROR_CORRUPTED );
            }

        // Non-DRMHelper error handling.
        if ( errorBuf )
            {
            SetStateOff( EPslnSkinChangeRequested );
            ShowErrorNoteL( *errorBuf );
            CleanupStack::PopAndDestroy( errorBuf );
            }
        // No errors, activate the skin.
        else
            {
            PSLN_TRACE_DEBUG("CPslnUi::ActivateSkinL 2");
            // Start changing active skin.
            iModel->GuardActivationLC();
            TBool shownote = EFalse;

            PSLN_TRACE_DEBUG("CPslnUi::ActivateSkinL directly");
            shownote = iModel->ActivateSkinL( skinIndex );
            ShowProgressBarL();

            if ( shownote )
                {
                PSLN_TRACE_DEBUG("CPslnUi::ActivateSkinL skin activated");
                SetStateOn( EPslnSkinActivated );
                }
            else
                {
                // If user declined to activate protected skin, re-initialize status
                // flag.
                if ( GetStatus( EPslnSkinChangeRequested ) )
                    {
                    PSLN_TRACE_DEBUG("CPslnUi::ActivateSkinL decline DRM activation");
                    SetStateOff( EPslnSkinChangeRequested );
                    }
                }
            CleanupStack::PopAndDestroy(); // activation guard
            }
        }
    }

// ---------------------------------------------------------------------------
// CPslnUi::ActivateSoundsL
// ---------------------------------------------------------------------------
//
void CPslnUi::ActivateSoundsL()
    {
    PSLN_TRACE_DEBUG("CPslnUi::ActivateSoundsL");

    // Is sounds are not supperted, ignore.
    if ( !PslnFeatures::IsSoundsInSkinsSupported()

    // If sounds are supported, but general view is not active, ignore.
        || iView && iView->Id().iUid != KPslnGeneralView.iUid  )
        {
        return;
        }

    TPath skinPath;
    CPslnSkinEntry* entry = iModel->VisibleSkin( iModel->ActiveSkinIndex() );
    if( entry )
        {
        entry->GetSkinPath( skinPath );
        skinPath.Append( KPslnPathSeparator );
        }
    else
        {
        User::Leave( KErrUnknown );
        }

    // Find sound files.
    CPslnSoundActivator* activator = CPslnSoundActivator::NewLC();
    TInt numberOfSounds = 0;
    activator->CollectSoundsL( skinPath, numberOfSounds );

    PSLN_TRACE_DEBUG1("CPslnUi::ActivateSoundsL num of tunes %d", numberOfSounds );

    if ( numberOfSounds <= 0 )
        {
        CleanupStack::PopAndDestroy( activator );
        return;
        }

    // Launch profile settings loader.
    CPslnTaskActivateSounds* activateTask = new (ELeave)
        CPslnTaskActivateSounds( *activator );
    CleanupStack::PushL( activateTask );

    CreateAndShowWaitWrapperL(
        *activateTask,
        R_PSLN_QTN_GEN_NOTE_OPENING,
        KNullDesC() );

    HBufC* noteText = NULL;

    PSLN_TRACE_DEBUG1("CPslnUi::ActivateSoundsL error %d", activateTask->iActivationErr );

    if( activateTask->iActivationErr == KErrNone )
        {
        if ( numberOfSounds == 1 )
            {
            noteText = StringLoader::LoadLC(
                R_PSLN_QTN_SKINS_NOTE_TONE_ACTIVATED );
            }
        else
            {
            noteText = StringLoader::LoadLC(
                R_PSLN_QTN_SKINS_NOTE_TONES_ACTIVATED );
            }

        CAknConfirmationNote* note =
            new (ELeave) CAknConfirmationNote( ETrue );
        note->ExecuteLD( *noteText );
        }
    else
        {
        if( activateTask->iActivationErr == KErrPermissionDenied )
            {
            noteText = StringLoader::LoadLC(
                R_PSLN_QTN_PROFILES_INFO_TONE_NO_DRM );
            }
        else
            {
            noteText = StringLoader::LoadLC(
                R_PSLN_QTN_FILE_FORMAT_ERROR );
            }
        CAknErrorNote* note =
            new (ELeave) CAknErrorNote( ETrue );
        note->ExecuteLD( *noteText );
        }
    
    CleanupStack::PopAndDestroy( 3, activator );
    }

// ---------------------------------------------------------------------------
// CPslnUi::DownloadSkinL
// ---------------------------------------------------------------------------
//
void CPslnUi::DownloadSkinL()
    {
    PSLN_TRACE_DEBUG("CPslnUi::DownloadSkinL");
    iModel->DownloadSkinL();
    }

// ---------------------------------------------------------------------------
// CPslnUi::CreateAndShowWaitWrapperL
// ---------------------------------------------------------------------------
//
void CPslnUi::CreateAndShowWaitWrapperL( MAknBackgroundProcess& aTask,
    const TInt aResourceID, const TDesC& aString,
    const TBool aShowImmediately )
    {
    HBufC* noteText = NULL;
    if ( aString.Length() == 0 )
        {
        noteText = StringLoader::LoadLC( aResourceID, iEikonEnv );
        }
    else
        {
        noteText = StringLoader::LoadLC( aResourceID, aString, iEikonEnv );
        }

    CAknWaitNoteWrapper* wrapper = CAknWaitNoteWrapper::NewL();
    CleanupDeletePushL( wrapper );
    if ( wrapper )
        {
        wrapper->ExecuteL(
            R_PSLN_GENERAL_WAIT_NOTE, aTask, *noteText, aShowImmediately );
        }

    CleanupStack::PopAndDestroy( 2, noteText ); // noteText, wrapper
    }

// ---------------------------------------------------------------------------
// CPslnUi::AddPluginToTabL
// ---------------------------------------------------------------------------
//
#ifndef RD_CONTROL_PANEL
void CPslnUi::AddPluginToTabL( CPslnFWPluginInterface& aPlugin )
    {
    PSLN_TRACE_DEBUG("CPslnUi::AddPluginToTabL Start");
    HBufC* buf = HBufC::NewLC( KPslnItemLength );
    TPtr ptrBuf = buf->Des();
    aPlugin.GetTabTextL( ptrBuf );
    TInt pluginUid = aPlugin.Id().iUid;
    if ( iTabGroup )
        {
        iTabGroup->AddTabL( pluginUid, ptrBuf );
        }
    PSLN_TRACE_DEBUG("CPslnUi::AddPluginToTabL Default Plugin added to tab");
    CleanupStack::PopAndDestroy( buf );
    }
#endif //!RD_CONTROL_PANEL

// ---------------------------------------------------------------------------
// Handles Exit command.
// ---------------------------------------------------------------------------
//
void CPslnUi::HandleCmdExitL()
    {
    Exit();
    }

// ---------------------------------------------------------------------------
// Shows error note.
// ---------------------------------------------------------------------------
//
void CPslnUi::ShowErrorNoteL( HBufC& aErrorBuf ) const
    {
    // Display global note.
    CAknGlobalNote* errorNote = CAknGlobalNote::NewLC();
    errorNote->ShowNoteL( EAknGlobalErrorNote, aErrorBuf );
    CleanupStack::PopAndDestroy( errorNote );
    }
// ---------------------------------------------------------------------------
// Callback when idle time occurs for skin update.
// ---------------------------------------------------------------------------
//
TInt CPslnUi::DoCreateWaitNoteL( TAny* aAny )
    {
    static_cast< CPslnUi* >( aAny )->DoCreateWaitNoteL();
    return EFalse;
    }
// ---------------------------------------------------------------------------
// CPslnUi::DoCreateWaitNoteL
// ---------------------------------------------------------------------------
//
void CPslnUi::DoCreateWaitNoteL()
    {
    CPslnTaskGenericUpdate* updateTask =
        new (ELeave) CPslnTaskGenericUpdate(
        *this, &CPslnModel::PerformCompleteUpdateL, ETrue );
    CleanupStack::PushL( updateTask );

    CreateAndShowWaitWrapperL( *updateTask,
        R_PSLN_QTN_GEN_NOTE_OPENING, KNullDesC(), EFalse );

    User::LeaveIfError( updateTask->iCallErr );

    CleanupStack::PopAndDestroy( updateTask );
    }

// ---------------------------------------------------------------------------
// This operation needs to be atomic. If it leaves, set state back to previous.
// ---------------------------------------------------------------------------
//
TInt CPslnUi::ActivateSkin( const TInt aPslnStatus )
    {
    TInt error = KErrNone;
    if ( !GetStatus( aPslnStatus ) )
        {
        SetStateOn( aPslnStatus );
        TRAPD( err, ActivateSkinL() );
        if ( err != KErrNone )
            {
            SetStateOff( aPslnStatus );
            error = err;
            }
        }
    return error;
    }

// ---------------------------------------------------------------------------
// Non-leaving version of AddPluginToTabL.
// ---------------------------------------------------------------------------
//
#ifndef RD_CONTROL_PANEL
TInt CPslnUi::AddPluginToTab( CPslnFWPluginInterface& aPlugin )
    {
    TRAPD( err, AddPluginToTabL( aPlugin ) );
    if ( err )
        {
        PSLN_TRACE_DEBUG1("CPslnUi::AddPluginToTab plugin fails: ", aPlugin.Id().iUid );
        }
    return err;
    }
#endif //!RD_CONTROL_PANEL

// ---------------------------------------------------------------------------
// Show skin activated note.
// ---------------------------------------------------------------------------
//
void CPslnUi::SkinDeployedL()
    {
#ifdef RD_UI_TRANSITION_EFFECTS_PHASE2
    // Only set sound state - no conf note anymore.
    SetStateOn( EPslnSoundActivationPending );
#else
    HBufC* skinName = HBufC::NewLC( KMaxName );
    TPtr skinNamePtr = skinName->Des();
    TInt skinIndex = iModel->ActiveSkinIndex();

    iModel->GetSkinNameByIndex(
        skinIndex,
        skinNamePtr,
        EPslnSkinNameTypeTitle );

    // Show confirmation note about skin change.
    HBufC* noteTxt = StringLoader::LoadL(
        R_PSLN_CONFIRM_ACTIVE_SKIN_STRING,
        skinNamePtr,
        iEikonEnv );
    CleanupStack::PushL( noteTxt );

    SetStateOn( EPslnSoundActivationPending );
    CAknConfirmationNote* note =
        new (ELeave) CAknConfirmationNote( ETrue );
    note->ExecuteLD( *noteTxt );
    CleanupStack::PopAndDestroy( 2, skinName ); // skinName, noteTxt

#endif
    iGeneralThemeView->UpdateSkinListItemsL();
    }

// ---------------------------------------------------------------------------
// Creates model class.
// ---------------------------------------------------------------------------
//
void CPslnUi::CreateModelL()
    {
    if ( !GetStatus( EPslnModelCreated ) )
        {
        iModel = CPslnModel::NewL( this );
        SetStateOn( EPslnModelCreated );
        }
    }

// ---------------------------------------------------------------------------
// Callback when idle time occurs for skin activation.
// ---------------------------------------------------------------------------
//
TInt CPslnUi::DoActivateSkinL( TAny* aAny )
    {
    static_cast< CPslnUi* >( aAny )->DoActivateSkinL();
    return EFalse;
    }

// ---------------------------------------------------------------------------
// Callback when idle time occurs for skin activation.
// ---------------------------------------------------------------------------
//
void CPslnUi::DoActivateSkinL()
    {
    TInt error = ActivateSkin( EPslnSkinChangeRequested );
    if ( error == KErrNoMemory )
        {
        HBufC* errorBuf = StringLoader::LoadLC(
            R_PSLN_QTN_MEMLO_RAM_OUT_OF_MEM );
        // Display global note.
        CAknGlobalNote* errorNote = CAknGlobalNote::NewLC();
        errorNote->ShowNoteL( EAknGlobalErrorNote, *errorBuf );
        CleanupStack::PopAndDestroy( 2 ); // errorNote & errorBuf
        }
    }


/**
* Handle USB Callback.
*/
void CPslnUi::HandleUSBCallBackL()
    {
    if ( iView && iView->Id().iUid == KPslnGeneralView.iUid )
        {
        TInt value = KErrNone;
        iEnableUSBWatchProperty.Get(value);
        
        if (value == KUsbPersonalityIdMS )
            {
            iUSBAttached = ETrue;
            }
        else
            {
            iUSBAttached = EFalse;
            }
        }
    }

// ---------------------------------------------------------------------------
// CPslnUi::ShowProgressBarL
// ---------------------------------------------------------------------------
//
void CPslnUi::ShowProgressBarL()
    {
    if ( iWaitDialog == NULL )
        {
        iWaitDialog = new (ELeave) CAknWaitDialog(
                    ( REINTERPRET_CAST( CEikDialog**, &iWaitDialog ) ), ETrue );
        iWaitDialog->PrepareLC( R_PSLN_GENERAL_WAIT_NOTE );

        HBufC* noteText = NULL;
        noteText = StringLoader::LoadLC( R_PSLN_QTN_GEN_NOTE_PROCESSING, iEikonEnv );
        iWaitDialog->SetTextL( *noteText );
        CleanupStack::PopAndDestroy( noteText );

        iWaitDialog->RunLD();
        }
    }

// ---------------------------------------------------------------------------
// CPslnUi::HideProgressBar
// ---------------------------------------------------------------------------
//
void CPslnUi::HideProgressBar()
    {
    if( iWaitDialog )
        {
        TRAP_IGNORE( iWaitDialog->ProcessFinishedL() )
        delete iWaitDialog;
        iWaitDialog = NULL;
        }
    }

// End of File

