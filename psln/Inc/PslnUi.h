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
* Description:  Personalisation application UI class.
*
*/


#ifndef C_PSLNUI_H
#define C_PSLNUI_H

#include <aknViewAppUi.h>
#ifndef RD_CONTROL_PANEL
#include <akntabgrp.h>
#include <akntabobserver.h>
#endif //RD_CONTROL_PANEL
#include <AknsSrvClient.h>
#include <e32property.h>

class CAknNavigationControlContainer;
class CAknNavigationDecorator;
class MAknBackgroundProcess;
#ifndef RD_CONTROL_PANEL
class CAknTabGroup;
#endif //RD_CONTROL_PANEL
class CPslnMainView;
class CPslnPluginHandler;
class CPslnFWPluginInterface;
class CPslnIdleTaskCreateViews;
class CPslnModel;
class CPslnPropertySubscriber;
class CPslnGeneralThemeView;


/**
 *  'AppUi' class.
 *
 *  @since S60 v2.0
 */
class CPslnUi : public CAknViewAppUi,
                public MAknsSkinChangeObserver
#ifndef RD_CONTROL_PANEL
                ,public MAknTabObserver
#endif //RD_CONTROL_PANEL
    {

public:

    /**
    * C++ default constructor
    */
    CPslnUi();

    /**
    * Symbian default constructor.
    */
    void ConstructL();

    /**
    * Destructor.
    */
    ~CPslnUi();

    /**
    * From CEikAppUi.
    * Takes care of command handling.
    * @param aCommand command to be handled
    */
    void HandleCommandL( TInt aCommand );

    /**
    * From CEikAppUi.
    * Handles a change to the application's resources
    * which are shared across the environment.
    * @param aType type of resources that have changed. 
    */
    void HandleResourceChangeL( TInt aType );

    /**
    * From CAknViewAppUi.
    * Activates a specified application view, without passing any message.
    * The function leaves if activation of the view fails.
    * @param aViewId Identifier of the view to activate.
    */
    void ActivateLocalViewL( TUid aViewId );

    /**
    * From MAknsSkinChangeObserver.
    * Called by the skin server when skin content is changed and the
    * connected client wants to be informed.
    *
    * @since 2.0
    */
    void SkinContentChanged();

    /**
    * From MAknsSkinChangeObserver.
    * Called by the skin server to indicate that the current skin
    * configuration has changed.
    *
    * @param aReason Reason code.
    *
    * @since 2.5
    */
    void SkinConfigurationChanged(
        const TAknsSkinStatusConfigurationChangeReason aReason );

    /**
    * From MAknsSkinChangeObserver.
    * Called by the skin server to indicate that the available
    * skin packages have changed.
    *
    * @param aReason Reason code.
    *
    * @since 2.5
    */
    void SkinPackageChanged(
        const TAknsSkinStatusPackageChangeReason aReason );

    /**
    * Returns pointer to Psln model which is owned by the AppUi.
    *
    * @return Psln model.
    */
    CPslnModel* Model() const;

    /**
    * Updates Tab index. If the parameters are not given, tab is set 
    * according to active selection in Main View.
    *
    * @param aMyId Uid of the active view.
    * @param aMyTabIndex Index of the active tab.
    * @since 3.1
    */
    void UpdateTabIndex( const TInt aMyId = KErrNotFound,
        const TInt aMyTabIndex = KErrNotFound );

    /**
    * Creates the given view.
    * @since 3.1
    * @param aViewUid Uid of view to be created.
    */
    void CreateViewL( TUid aViewUid );

    /**
    * Returns application's CAknNavigationControlContainer.
    * @since 3.1
    * @return CAknNavigationControlContainer.
    */
    CAknNavigationControlContainer* NaviContainer() const;

    /**
    * Returns tab group.
    * @since 3.1
    * @return CAknNavigationDecorator.
    */
    CAknNavigationDecorator* PslnTabGroup();

    /**
    * Returns pointer to ECOM plugin handler which is owned by the AppUi.
    * @since 3.1
    * @return ECOM plugin handler.
    */
    CPslnPluginHandler* PluginHandler() const;

    /**
    * Add new view to Ui Class.
    * @since 3.1
    * @param aNewView new view to add to Ui class.
    */
    void AddNewViewL( CAknView* aNewView );

    /**
    * Indicate from caller class that Ui-class has now all the applicable views.
    * @since 3.1
    */
    void AllViewsDone();

    /**
    * Handles errors when settings wallpapers.
    * @param aError error code received from WallpaperUtils API.
    */
    void HandleImageErrorsL( TInt aError );

#ifndef RD_CONTROL_PANEL
    /**
    * From MAknTabObserver.
    * Takes care of tab handling.
    * @since 3.1
    * @param aIndex tab to be handled
    */
    void TabChangedL( TInt aIndex );
#endif //RD_CONTROL_PANEL

    /**
    * Create views when application is idle. 
    * @since 3.1
    */
    void LoadViewsWhenIdleL();

    /**
    * Constructs tab group, containing all static views and 
    * ECOM plugin views.
    * @since 3.1
    */
    void ConstructTabGroupL();

    /**
    * Toggles screen blanker on/off. 
    * @param aToggleValue ETrue activates screen blanker; EFalse removes it.
    * @param aStatusPaneVisible indicates if the blanker should cover the 
    *        statuspane as well. This is irrelevant, when removing the blanker.
    * @since 3.1
    */
    void ToggleScreenBlankerL(
        const TBool& aToggleValue,
        const TBool& aStatusPaneVisible,
        const TBool& aRealAct = ETrue );

    /**
    * Indicates if the UI class has deployed the skin already and is ready to 
    * receive further skin activation related commands.
    * @return ETrue when UI class can handle a new skin activation related 
    *         command, otherwise EFalse,
    */
    TBool IsReadyToHandleCommands();

    /**
    * Handles exit command correctly when leave occurs in application exit.
    */
    void HandleCmdExitLeave();

    /**
    * Sets title back to default (application name).
    */
    void SetTitleToDefaultL();

    /**
    * Binary flags to indicate if view is going to be created.
    * Statuses are valid irregardless if view has, or has not 
    * been already created. These values cannot change dynamically.
    * 
    */
    enum TPslnViewSupport
        {
        EPslnScreensaverView = 0x00000001,
        EPslnWallpaperView   = 0x00000002
        };

    /**
    * Gets view creation statuses as a bitmask.
    * See TPslnViewSupport for optional views whose statuses
    * can be inquiried.
    * To check if a view is supported, check flag value.
    * E.g. TBitflags views = ViewSupport();
    *      if ( views.IsSet( EPslnScreensaverView ) )
    *          {
    *          // Screensaver view is supported
    *          ...
    * 
    * @return bitmask containing view support status.
    */
    TBitFlags ViewSupport();

    void SetDRMProtectedSkinInSkinList( 
        const TBool& aProtectedSkinInList );

    /**
    * USB Callback.
    */
    static TInt USBCallBackL(TAny* aPtr);

    /**
    * USB Attach State.
    * @return ETrue when USB already attached, otherwise EFalse,
    */
    TBool USBAttachState();

private:

    /**
    * From CCoeAppUi.
    * Handles events sent to the application by the window server.
    * @param The event that occurred.
    * @param The control that the event occurred in. 
    *        (For key events this is the applications window group.)
    */
    void HandleWsEventL(
        const TWsEvent& aEvent,
        CCoeControl* aDestination );

    /**
    * From CEikAppUi.
    * Key event handler.
    */
    virtual TKeyResponse HandleKeyEventL(
        const TKeyEvent& aKeyEvent,
        TEventCode aType );

    /**
    * @see SkinConfigurationChanged, same functionality, but 
    * leaving internal method.
    */
    void SkinConfigurationChangedL(
        const TAknsSkinStatusConfigurationChangeReason aReason );

    /* Activates skin. */
    void ActivateSkinL();

    /* Activates sounds in skin. */
    void ActivateSoundsL();

    /* Downloads skin. */
    void DownloadSkinL();

    /* Creates wait dialog and shows it */
    void CreateAndShowWaitWrapperL(
        MAknBackgroundProcess& aTask,
        const TInt aResourceID, const TDesC& aString,
        const TBool aShowImmediately = ETrue );

#ifndef RD_CONTROL_PANEL
    /* Adds given view plugin to TabGrp */
    void AddPluginToTabL( CPslnFWPluginInterface& aPlugin );
#endif //!RD_CONTROL_PANEL

    /* Handles exit command. */
    void HandleCmdExitL();

    /* Shows error note. */
    void ShowErrorNoteL( HBufC& aErrorBuf ) const;

    /**
    * Callback when idle time occurs.
    */
    static TInt DoCreateWaitNoteL( TAny* aAny );
    
    /* Creates and shows wait note. */
    void DoCreateWaitNoteL();

    /* Activates skin, cannot leave. */
    TInt ActivateSkin( const TInt aPslnStatus );

#ifndef RD_CONTROL_PANEL
    /* Non-leaving version of AddPluginToTabL. */
    TInt AddPluginToTab( CPslnFWPluginInterface& aPlugin );
#endif //!RD_CONTROL_PANEL

    /* Set internal state to post-skin-deployment.*/
    void SkinDeployedL();

    /** 
    * Creates model instance.
    * @since 3.1
    */
    void CreateModelL();
    
    /**
    * Callback when idle time occurs for skin activation.
    */
    static TInt DoActivateSkinL( TAny* aAny );
    
    /**
    * Activates skin
    */
    void DoActivateSkinL();

// INLINE METHODS

    /* Checks if internal state is on or off. */
    inline TBool GetStatus( TInt aInternalState ) const;

    /* Sets internal state on. Includes check that state is now off. */
    inline void SetStateOn( TInt aInternalState );

    /* Sets internal state off. Includes check that state is now on. */
    inline void SetStateOff( TInt aInternalState );
    
    /**
    * Handle USB Callback.
    */
    void HandleUSBCallBackL();

private: // data

    /**
    * Psln Model.
    * Own.
    */
    CPslnModel* iModel;

    /**
    * Navigation Pane.
    * Not own.
    */
    CAknNavigationControlContainer* iNaviPane;

    /**
    * Frame for tabgroup.
    * Own.
    */
    CAknNavigationDecorator* iDecoratedTabGroup;

    /**
    * Main view.
    * Not own (application framework 'owns' this).
    */
    CPslnMainView* iMainView;

    /**
    * ECOM view plugin handler.
    * Own.
    */
    CPslnPluginHandler* iPluginHandler;

    /**
    * Internal status of Psln. The specific states are:
    * 
    * EPslnCreated 
    *     Psln has this status when default constructor 
    *     has been called. It's set off, once all views 
    *     have been added.
    * EPslnSoundActivationPending
    *     Psln has this status when skin server about to activate
    *     sounds included in skin package. It is set off when 
    *     activation is finished.
    * EPslnListUpdateNeeded
    *     Psln has this status when skin list needs updating.
    * EPslnWallpaperViewCreated
    *     This state is active when wallpaper view has been created.
    *     It is initially off and set on when either view is loaded
    *     due to idle activity, or when needed.
    * EPslnScreenSaverViewCreated
    *     This state is active when screensaver view has been created.
    *     It is initially off and set on when either view is loaded
    *     due to idle activity, or when needed.
    * EPslnGeneralViewCreated
    *     This state is active when general theme view has been created.
    *     It is initially off and set on when either view is loaded
    *     due to idle activity, or when needed.    
    * EPslnSkinActivated
    *     User has opted to activate a skin. This state prevails until
    *     skin server indicates that skin changes has been deployed.
    * EPslnTabGroupCreated
    *     This state is active when tab group has been created.
    *     It is initially off and set on when either any other view is
    *     activated (other than main) or with time due to idle activity.
    * EPslnModelCreated
    *     This state is active when model has been created.
    *     It is initially off and set on when either any other view is
    *     activated (other than main) or with time due to idle activity.    
    * EPslnSkinChangeRequested
    *     This state is active when user has indicated that he/she would
    *     would like to change the active skin (i.e. preview or actual
    *     activation). It is initially off and is set on when user selects
    *     Apply for the skin from General Theme view.
    *     It is again set off when skin server indicates that skin was 
    *     either activated, or there was an error. 
    *     This differs from EPslnSkinActivated in that this is purely tied
    *     to user activity.
    * EPslnViewSupportChecked
    *     This state indicates that the view support has been checked.
    *     It is set active once, the view support status has been checked
    *     for the first time.
    * EPslnNoScreenSaverView
    *     This state indicates that there is no Screensaver view in the
    *     application. View statuses are set when ViewSupport is called.
    * EPslnNoWallpaperView
    *     This state indicates that there is no Wallpaper view in the
    *     application. View statuses are set when ViewSupport is called.
    */
    enum TPslnStatus {
        EPslnCreated                = 0x00000001,
        EPslnProtectedSkinInList    = 0x00000002,
        //Not used    = 0x00000004,
        EPslnSoundActivationPending = 0x00000008,
        EPslnListUpdateNeeded       = 0x00000010,
        EPslnWallpaperViewCreated   = 0x00000020,
        EPslnScreenSaverViewCreated = 0x00000040,
        EPslnGeneralViewCreated     = 0x00000080,
        EPslnSkinActivated          = 0x00000200,
        EPslnTabGroupCreated        = 0x00000400,
        EPslnModelCreated           = 0x00000800,
        EPslnSkinChangeRequested    = 0x00001000,
        EPslnViewSupportChecked     = 0x00002000,
        EPslnNoScreenSaverView      = 0x00004000,
        EPslnNoWallpaperView        = 0x00008000
        };
    TInt iPslnUiStatus;

#ifndef RD_CONTROL_PANEL
    /**
    * Tab group.
    * Not own - owned by iDecoratedTabGroup.
    */
    CAknTabGroup* iTabGroup;
#endif //RD_CONTROL_PANEL

    /**
    * Creates views when application is idle.
    * Own.
    */
    CPslnIdleTaskCreateViews* iIdleTask;   
    /**    
    * 
    */
    CIdle* iIdleActivateSkin;
    
    /**    
    * 
    */
    CIdle* iIdleUpdateSkin;
    
    /**
    * USB Watch Property.
    */
    RProperty iEnableUSBWatchProperty;
    
    
    /**
    * USB Watch Property Subscriber.
    * Own.
    */
    CPslnPropertySubscriber* iUSBWatchSubscriber;
    
    /**
    * USB Attached.
    */
    TBool iUSBAttached;

    /**
    * General Theme view.
    * Not own (application framework 'owns' this).
    */
    CPslnGeneralThemeView* iGeneralThemeView;

    };

// Inline methods.
#include "pslnui.inl"

#endif // C_PSLNUI_H

// End of File

