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
* Description: 
*
*/

#ifndef __AKNAPPUI_H__
#define __AKNAPPUI_H__

//  INCLUDES
#include <eikappui.h>
#include <eikspane.h>
#include <eikcba.h>
#include <avkon.hrh>
#include <AknDef.h>
#include <akntouchpaneobserver.h>

// FORWARD DECLARATIONS
class CEikButtonGroupContainer;
class CAknAppShutter;
class CAknAppUiExtension;
class CAknWsEventMonitor;
class CAknKeySoundSystem;
class CAknAppUiBaseExtension;
class CAknTouchPane;
class CAknToolbar;
class CAknPointerEventModifier;

// MACROS
#define iAvkonAppUi ((CAknAppUi*)CEikonEnv::Static()->EikAppUi())
#define iAvkonAppUiBase ((CAknAppUiBase*)CEikonEnv::Static()->EikAppUi())

/**
*  Avkon key resolver interface
*
*  @since S60 3.1
*/
class MAknAliasKeyCodeResolver
    {
public:
    /**
    * Resolves keyboard layout dependent keycode for the given event 
    *
    * @since S60 3.1
    * @param aCode reference to variable to contain new keycode 
    * @param aKeyEvent reference to original, complete, event
    * @param aType indicating original event type
    * @return KErrNone on success, otherwise system wide error codes
    */
    virtual TInt GetAliasKeyCode(TUint& aCode, const TKeyEvent& aKeyEvent,TEventCode aType)=0;        
    };

// CLASS DECLARATION

/**
*  Abstract Avkon application UI base class
*
*  @since S60 3.0
*/
class CAknAppUiBase : public CEikAppUi
    {
private:
    friend class CAknAppUi;
    enum
        {
        EAppOrientationSpecifiedFlag            = 0x00010000, // In area reserved for System Guis
        EAppOrientationLandscapeFlag            = 0x00020000,
        EAppOrientationAutomaticFlag            = 0x00040000,
        EAknEnableSkinFlag                      = 0x00080000,
        // Since 3.0
        EAknDisableHighlightAnimationFlag       = 0x00100000,
        EAknEnableMSKflag                       = 0x00200000,
        /**
         * When enabled, avkon does not complete startup effect
         * application has to do it by itself.
         *
         * @since S60 3.2
         *
         */
        EAknExplicitStartupEffectCompletionFlag     = 0x00400000,

        /**
         * Application supports touch (doesn't need keyboard). If the flag
         * is missing and compatibility mode is enabled in a device,
         * application is run in a compatibility mode (QVGA window with a
         * virtual keypad.
         *
         * @since S60 5.0
         */
        EAknTouchCompatibleFlag                 = 0x00800000,

        /**
         * Application supports single click.
         *
         * @since S60 5.2
         */
        EAknSingleClickCompatibleFlag           = 0x01000000
        };

    public:

    enum TAppUiOrientation
        {
        /**
        * Use the default device screen rotation of the product for this 
        * application. This is the default rotation setting for an 
        * application, and it should be used by nearly all applications. 
        */
        EAppUiOrientationUnspecified,
        /**
        * Use a portrait screen rotation for this application.
        * This should only be used when an application specifically wants
        * portrait rotation. The device will select an appropriate portrait
        * rotation, if one is available.
        */
        EAppUiOrientationPortrait,
        /**
        * Use a landscape screen rotation for this application.
        * This should only be used when an application specifically wants
        * landscape rotation. The device will select an appropriate landscape
        * rotation, if one is available.
        */
        EAppUiOrientationLandscape,
        /**
        * Use the normal device screen rotation for this application.
        * Both portrait and landscape screen rotations are possible. The 
        * application rotation follows device screen rotation.
        */
        EAppUiOrientationAutomatic
        };
    enum
        {
        /**
        * Flag indicating that default skin parameters should be provided by
        * UI controls created within the scope of this AppUi instance.
        * This value (or binary combination with some other values) should
        * be given as a parameter to <code>BaseConstructL</code> in case
        * the application wants to enable default skin parameters for all
        * the Avkon controls supporting them.
        *
        * Note: The value can be queried by using 
        * <code>AknsUtils::AvkonSkinEnabled()</code> from AknSkins.lib.
        *
        * @since S60 2.0
        */
        EAknEnableSkin = EAknEnableSkinFlag,
        EAppOrientationPortrait     = EAppOrientationSpecifiedFlag,
        EAppOrientationLandscape    = EAppOrientationSpecifiedFlag 
                                      | EAppOrientationLandscapeFlag,
        EAppOrientationAutomatic    = EAppOrientationSpecifiedFlag
                                      | EAppOrientationAutomaticFlag,
        // Since 3.0
        EAknDisableHighlightAnimation = EAknDisableHighlightAnimationFlag,
        // Since 3.1
        EAknEnableMSK = EAknEnableMSKflag,
        // Since 3.2
        EAknExplicitStartupEffectCompletion = EAknExplicitStartupEffectCompletionFlag,
        // Since 5.0
        EAknTouchCompatible = EAknTouchCompatibleFlag,
        // Since 5.2
        EAknSingleClickCompatible = EAknSingleClickCompatibleFlag
        };
    enum TKeyEventFlag
        {
        EDisableSendKeyShort = 0x01, // Short press of send key
        EDisableSendKeyLong  = 0x02  // Long press of send key
        };    

public:
    /**
    * Destructor.
    */    
    IMPORT_C ~CAknAppUiBase();
    
    /**
    * C++ Default constructor.
    */
    IMPORT_C CAknAppUiBase();
public: 
    
    /**
    * Initialises this Avkon base app UI with standard values. 
    * @c aAppUiFlags values are common with 
    * @c CEikAppUi::BaseConstructL(aAppUiFlags).
    * @param aAppUiFlags Application user interface flags.
    */
    IMPORT_C void BaseConstructL( TInt aAppUiFlags );
    
    /**
    * Handles changes in keyboard focus when an application switches to,
    * or from, the foreground. This function calls 
    * @c CEikAppUi::HandleForegroundEventL.
    * @param aForeground @c ETrue if the application is in the foreground, 
    * otherwise @c EFalse.
    */ 
    IMPORT_C void HandleForegroundEventL(TBool aForeground);

public: // From CEikAppUi
    
    /**
    * From @c CEikAppUi. Completes construction. The implementation of 
    * @c ConstructL() in @c CAknAppUiBase simply calls @c BaseConstructL().
    */
    IMPORT_C void ConstructL();  // virtual
    
    /** 
    * From @c CEikAppUi. Closes the app UI.
    */
    IMPORT_C void Exit(); //virtual
    
    /**
    * From @c CEikAppUi. Sets whether the windows are faded.
    * @param aFaded @c ETrue if windows are faded, otherwise windows are 
    * unfaded.
    */
    IMPORT_C void SetFadedL(TBool aFaded); // virtual
    
    /**
    * From @c CEikAppUi. Handles a change to the application's resources which
    * are shared across the environment. This function calls 
    * @c CEikAppUi::HandleResourceChangeL except when @c aType is 
    * @c KEikDynamicLayoutVariantSwitch.
    * @param aType The type of resources that have changed. 
    */
    IMPORT_C void HandleResourceChangeL(TInt aType); // virtual
    
    /**
    * From @c CEikAppUi. Gets the total area of the screen available to the
    * application. This includes the space that is available for a toolbar, 
    * toolband or title band, if the application requires them.
    * @return The total area of the screen available to the application.
    */
    IMPORT_C TRect ApplicationRect() const; //virtual

public: // from CCoeAppUiBase
    
    /** 
    * From @c CCoeAppUiBase. Performs pre-exit processing by calling 
    * @c CEikAppUi::PrepareToExit() to ensure the application will exit
    * cleanly.
    */
    IMPORT_C void PrepareToExit();
public: // New Functions
    /**
    * Determines whether the system is faded.
    * @return @c ETrue if system is faded 
    */
    IMPORT_C TBool IsFaded() const;

    /**
    * Returns the object which allows events to be spyed upon in addition to
    * normal event handling.
    * @return Pointer to window server event monitor object.
    */
    IMPORT_C CAknWsEventMonitor* EventMonitor() const;
    
    /**
    * Gets a pointer to KeySound API object.
    * @return Pointer to KeySound API object. 
    */
    IMPORT_C CAknKeySoundSystem* KeySounds() const;

    /**
    * Determines whether the application is full screen application.
    * @return @c ETrue if the application is full screen application.
    */
    IMPORT_C TBool IsFullScreenApp() const;
    
    /**
    * Determines whether the application is layout aware.
    * @return @c ETrue if the application is layout aware.
    */
    IMPORT_C TBool IsLayoutAwareApp() const;
    
    /**
    * Determines whether the application has MSK enabled.
    * @return @c ETrue if the application has MSK enabled.
    *
    * @since 3.1 
    */
    TBool IsMSKEnabledApp() const;

    /**
    * Determines whether the application is closing.
    * In practice this means that CEikonEnv has been destroyed.
    * @return @c ETrue if the application is closing.
    *
    * @since 3.2
    */
    TBool IsAppClosing() const;
    
    /**
    * Set application layout aware.
    * @param aLayoutAwareApp @c ETrue if the application is layout aware, 
    * @c EFlase otherwise.
    */
    IMPORT_C void SetLayoutAwareApp(TBool aLayoutAwareApp);
    
    /**
    * Determines whether the application is foreground.
    * @return @c ETrue if the application is foreground.
    */
    IMPORT_C TBool IsForeground() const;
    
    /**
    * Determines whether the application is partially foreground.
    * @return @c ETrue if the application is partially foreground.
    */
    IMPORT_C TBool IsPartialForeground() const;

    /**
    * Gets the application screen orientation.
    * @return Application screen orientation.
    */
    IMPORT_C TAppUiOrientation Orientation() const;
    
    /**
    * Tests whether it is possible for this app to have a
    * practical effect on the screen orientation, through
    * SetOrientationL().
    * @since S60 3.2
    * @return ETrue if SetOrientationL can change the orientation, EFalse otherwise.
    */
    IMPORT_C TBool OrientationCanBeChanged() const;
    
    /**
    * Sets the application screen orientation.
    * Note: this API has no effect on non-full-screen app UIs.
    * @param aOrientation application screen orientation.
    */
    IMPORT_C void SetOrientationL(TAppUiOrientation aOrientation);

    /**
    * Find the window group ID of the application below this application.
    * @return the window group ID of the application below this application.
    */
    TInt FindAppWgIdBelowMeL();
    
    /**
    * Simply return @c KEikPartialForeground if @c aPartialFg == @c ETrue, 
    * otherwise if @c aForeground == @c ETrue then return @c EEventFocusGained
    * else return @c EEventFocusLost.  
    * @return if @c aPartialFg then return KEikPartialForeground.
    */
    TInt EventForForegroundState(TBool aPartialFg, TBool aForeground);
    
    /**
    * Determines whether the thread owning this application window group is
    * foreground.    
    * @return @c ETrue if the thread owning this application window group is
    * foreground, @c EFlase otherwise.
    */
    TBool ThreadIsForeground() const;

    /**
    * Simulates an event being received from wserv
    * @param aEvent the event id being simulated.
    */
    void SimulateWsEventL(TInt aEvent);

    /** 
     * Gets the application local zoom
     * @return Application local zoom
     * @since 3.1 
     */
    IMPORT_C TAknUiZoom LocalUiZoom() const;

    /**
    * Sets the application local zoom. However, in order to have any 
    * effect, it may be necessary to make a subsequent call to  
    * @c ApplyLayoutChangeL.
    *
    * @param aZoom application local zoom
    * @since 3.1 
    */
    IMPORT_C void SetLocalUiZoom(TAknUiZoom aZoom);

    /*
    * Can be used to apply changes to settings that affect the current layout,
    * such as changes to the local zoom. Optionally reports the change
    * to the layout to all controls in the application. There are a number of 
    * different possible usages of this API:
    * <ul>
    * <li> Can be used to immediately change the local zoom, by passing in 
    * ETrue for the reporting parameter.</li>
    * <li> Can be called before BaseConstructL without leaving, the effect
    * is the same as passing EFalse for the reporting parameter, as 
    * the correct layout data is picked up later on during control layout.</li>
    * <li>Can be used by implementors of the 
    * @c MAknSettingCacheUpdatePlugin interface, in order to set the local 
    * zoom whilst updating the settings cache. By passing in EFalse for the 
    * reporting parameter, the layout switch is deferred to the usual 
    * processing in @c UpdateSettingCacheAndForwardEventL.</li>
    * <li> Can be used by controls that require a different local zoom to 
    * the underlying application, such as a dialog. By not 
    * reporting the change during construction, the dialog will lay itself out 
    * correctly. However, the dialog must then report the change back to the 
    * app zoom level when it closes, ignoring the resulting resource changed 
    * layout switch event.</li>
    * </ul>
    *
    * @param aReportChange if this is true, then the layout event will be 
    *               reported to controls on the control stack
    * @since 3.1 
    */    
    IMPORT_C void ApplyLayoutChangeL(TBool aReportChange);
    
    /**
    * Checks if application UI has full or partial foreground status.
    * @since 3.2
    * @return ETrue if application UI has full or partial foreground status.
    *         Otherwise EFalse.
    */
    TBool HasFullOrPartialForeground() const;    

    /**
    * Sets the flags for default key event handling
    * @since 5.0
    * @param aFlags which can be a combination of flags 
    *        declared in enumeration TKeyEventFlag 
    */
    IMPORT_C void SetKeyEventFlags( const TInt aFlags );
    
    /**
    * Returns a pointer to appui's pointer event modifier. This method is
    * intended for internal usage only.
    *
    * @since S60 v5.0
    * @return pointer event modifier
    */
    IMPORT_C CAknPointerEventModifier* PointerEventModifier();
    
    /**
    * Checks if the application is touch compatible i.e. it has been
    * constructed with the flag EAknTouchCompatible.
    *
    * @since S60 v5.0
    * @return ETrue if the application is touch compatible
    */
    IMPORT_C TBool IsTouchCompatible() const;

    /**
     * Checks if the application is single click compatible i.e.
     * it has been constructed with the flag EAknSingleClickCompatible.
     *
     * @since S60 v5.0
     * @return ETrue if the application is single click compatible
     */
    IMPORT_C TBool IsSingleClickCompatible() const;

protected: // From CCoeAppUiBase
    /**
    * From @c CCoeAppUiBase.   
    * Calls CCoeAppUi::HandleScreenDeviceChangedL().
    */
    IMPORT_C virtual void HandleScreenDeviceChangedL(); // was Reserved_1()

protected: // From CCoeAppUi
     
    /**
    * From @c CCoeAppUi. Handles an application specific event.
    * @param aType The type of the event that occurred. This should be a 
    * unique identifier constant.
    * @param aEvent The window server event that occurred. 
    */
    IMPORT_C virtual void HandleApplicationSpecificEventL(TInt aType,
        const TWsEvent& aEvent);

protected: // New functions
    /**
    * Set the application to be a full screen application.
    * @param aIsFullScreen is @c ETrue if the application is a full screen
    * application, @c EFlase otherwise.
    */
    IMPORT_C void SetFullScreenApp(TBool aIsFullScreen);
    
    /**
    * Replace current key sound server with new one.
    * @param aUid ID of the new key sound server.
    */
    IMPORT_C void ReplaceKeySoundsL( TInt aUid );

protected: // from MObjectProvider
    IMPORT_C virtual TTypeUid::Ptr MopSupplyObject(TTypeUid aId);

public: // not exported
    void SetScreenModeL(TInt aModeNumber);
    TInt ScreenMode() const;

private:
    void UpdateSettingCacheAndForwardEventL( TInt aEventId );
    // Method tests on aError. If < KErrNone, it calls CCoeEnv::SetAppUi in order to pass
    // ownership to the environment. CCoeEnv then will delete the AppUi at the usual point in the destruct order
    void SetAppUiAndLeaveIfErrorL( TInt aError );
    TBool AlwaysForwardEvent( TInt aEventId );
    void RelinquishPriorityToForegroundAppLC();

private:
    // Avkon app ui class flags
    TBitFlags iAknFlags;

    // Added for Avkon. Monitor events for emergency call support
    CAknWsEventMonitor* iEventMonitor;

    // Added for Avkon. Provides access to keysound server.
    // Moved from CAknAppUi, because CEikSrvUi needs it as well
    CAknKeySoundSystem* iKeySounds; 
    
    CAknAppUiBaseExtension* iAppUiBaseExtension;
    };

/**
*  Abstract Avkon application UI class
*
*  @since S60 0.9
*/

class CAknAppUi : public CAknAppUiBase, MEikStatusPaneObserver,
            public MCoeViewDeactivationObserver,
            public MAknTouchPaneObserver
    {
public:
    
    /**
    * Initialises this Avkon app UI with standard values. @c aAppUiFlags
    * values are common with @c CEikAppUi::BaseConstructL(aAppUiFlags). 
    * Additionally those @c aAppUiFlags values can be bitwise ORed with
    * @c EAknEnableSkin flag to provide default skin parameters for this AppUi
    * instance.
    * @param aAppUiFlags Application user interface flags.
    */
    IMPORT_C void BaseConstructL(TInt aAppUiFlags=EStandardApp);
    
    /**
    * Destructor.
    */
    IMPORT_C ~CAknAppUi();

public: // From CEikAppUi
     /**
     * From @c CEikAppUi. Completes construction. The implementation of
     * @c ConstructL() in @c CAknAppUi simply calls @c BaseConstructL().
     */
    IMPORT_C void ConstructL();  // virtual

public:
    /**
    * Gets a pointer to the status pane.
    * @return Pointer to the status pane 
    */
    IMPORT_C CEikStatusPane* StatusPane();
    /**
    * Gets a pointer to the Command Button Area.
    * @return Pointer to the CBA 
    */
    IMPORT_C CEikButtonGroupContainer* Cba();

    /**
    * Gets a pointer to the touch pane.
    * @return Pointer to the the touch pane
    * @since S60 5.0
    */
    IMPORT_C CAknTouchPane* TouchPane();

    /**
    * Gets a pointer to the application toolbar.
    * @return Pointer to the applicaton toolbar or NULL
    * @since S60 3.1
    */
    IMPORT_C CAknToolbar* PopupToolbar() const; 
    
    /**
    * Gets a pointer to the current toolbar( view toolbar is priority ).
    * @return Pointer to the current toolbar or NULL
    * @since S60 3.1
    */
    IMPORT_C CAknToolbar* CurrentPopupToolbar() const;
    
    /**
    * Gets a pointer to the current fixed toolbar( view toolbar is priority ).
    * @return Pointer to the current fixed toolbar or NULL
    * @since S60 5.0
    */
    IMPORT_C CAknToolbar* CurrentFixedToolbar() const; 

    
    /**
    * Hides popup toolbar if it is visible
    * @since S60 3.1
    */
    void StopDisplayingPopupToolbar(); 
        
      
    /**
    * Processes user commands.
    * This function passes @c aCommand (except values @c EAknSoftkeyOptions,
    * @c EAknCmdExit, @c EEikCmdCanceled) to user derived @c HandleCommandL.
    * @param aCommand A command ID.
    */
    IMPORT_C void ProcessCommandL(TInt aCommand);

    
    /**
    * Handles errors.
    * @param aError The error code.
    * @param aExtErr For extended error messages. Not used.
    * @param aErrorText Error text. Not used.
    * @param aContextText Text describing the context of the error. Not used.
    * @return @c ENoDisplay if Error handled proper way, else 
    * @c EErrorNotHandled
    */
    IMPORT_C TErrorHandlerResponse HandleError (TInt aError,
        const SExtendedError& aExtErr, TDes& aErrorText, TDes& aContextText); 

    /**
    * Run the application shutter if it exists.
    */
    IMPORT_C void RunAppShutter();
    
    /**
    * Determines whether the application shutter is active.
    * @return @c ETrue if application shutter is active.
    */
    IMPORT_C TBool IsAppShutterRunning() const;

    /**
    * Determines whether the application is hidden in background.
    * (i.e. HideInBackground has been called and application has not
    *       yet been activated)
    * @return @c ETrue if application is hidden in background.
    */
    TBool IsAppHiddenInBackground() const;
    
public: // MCoeViewDeactivationObserver

    /**
    * From @c MCoeViewDeactivationObserver.
    * Handles the deactivation of the view identified by
    * @c aViewIdToBeDeactivated before the newly activated view with id
    * @c aNewlyActivatedViewId is marked as current.
    * Default implementation calls @c iAvkonEnv->CloseAllIntermediateStates()
    * without using @c aViewIdToBeDeactivated and @c aNewlyActivatedViewId.
    * @param aViewIdToBeDeactivated
    * @param aNewlyActivatedViewId  
    */
    IMPORT_C virtual void HandleViewDeactivation(
        const TVwsViewId& aViewIdToBeDeactivated,
        const TVwsViewId &aNewlyActivatedViewId);

public: // from CCoeAppUiBase
    
    /**
    * From @c CCoeAppUiBase. Performs pre-exit processing to ensure the
    * application will exit cleanly.
    */
    IMPORT_C void PrepareToExit();

public: // from MAknTouchPaneObserver

    /**
    * From @MAknTouchPaneObserver.
    * Handles a change in the size or position of touch pane.
    */
    IMPORT_C void HandleTouchPaneSizeChange();

protected:
    // from MEikStatusPaneObserver
    /**
    * From @c MEikStatusPaneObserver. Handles a change in the position or size
    * of the screen area occupied by the status pane.
    */  
    IMPORT_C void HandleStatusPaneSizeChange();

    // from CCoeAppUi
    /**
    * From @c CCoeAppUi. Handles system events generated by the window server.
    * @param aEvent The window server event that occurred.
    */
    IMPORT_C void HandleSystemEventL(const TWsEvent& aEvent);

protected: // formerly from MTopSetMember<CEikMenuBar>, now reserved
    IMPORT_C virtual void Reserved_MtsmPosition();
    IMPORT_C virtual void Reserved_MtsmObject();
protected:
    
    /**
    * Handles changes in keyboard focus when an application switches to, 
    * or from, the foreground.
    * @param aForeground @c ETrue if the application is in the foreground,
    * otherwise @c EFalse.
    */
    IMPORT_C void HandleForegroundEventL(TBool aForeground);
    
    /**
    * Handles window server events.
    * @param aEvent The window server event that occurred.
    * @param aDestination The control associated with the event.
    */
    IMPORT_C void HandleWsEventL(const TWsEvent& aEvent,
        CCoeControl* aDestination);

    /**
    * Set key block mode.
    * In default mode, the S60 Developer Platform blocks simultaneous key
    * presses.
    * @param aMode @c ENoKeyBlock if no key block, otherwise
    * @c EDefaultBlockMode
    */
    IMPORT_C void SetKeyBlockMode(TAknKeyBlockMode aMode);
    IMPORT_C void HandleErrorL(TInt aError, HBufC** aErrorDesc, TBool aShowNote = ETrue );

#ifdef _DEBUG
    
    /**
    * Prints out information about the control and all its subcontrols to
    * RDebug console.
    * @param aControl object to be printed.
    * @param aLevel  positioning constant.
    * @param aDebug stream for printing.
    */
    void DumpControl(CCoeControl* aControl, TInt aLevel, RDebug& aDebug);
#endif
    /**
    * Try to set window server buffer size to @c KAknDefaultWsBufferSize.
    */
    void DecideWsClientBufferSizesL();

private:
    void UpdateKeyBlockMode();
    TBool SimulateHashKeyMarkingEvent(const TWsEvent& aEvent);

private:
    TBool iDumpNextControl;
    CAknAppShutter* iAppShutter;// May be set to NULL by the app shutter itself
    TAknKeyBlockMode iBlockMode;
    CAknAppUiExtension * iExtension;

public:
    /**
    * Hide application from Fast-swap window.
    * @since S60 2.6
    * @param aHide @c ETrue if application is hided from Fast-swap window, otherwise
    * @c EFalse
    */
    IMPORT_C void HideApplicationFromFSW(TBool aHide=ETrue);

    /**
    * Gets keyboard layout specific keycode. Uses given resolver
    * SetAliasKeyCodeResolverL() if set, by default
    * fetches alternative code from avkon server.
    *
    * @since S60 3.1
    * @param aCode reference to variable to contain new keycode 
    * @param aKeyEvent reference to original, complete, event
    * @param aType indicating original event type
    */
    IMPORT_C void GetAliasKeyCodeL(TUint& aCode, const TKeyEvent& aKeyEvent,TEventCode aType);

    /**
    * Sets custom resolver for keycode aliases
    * Creates iExtension if it doesn't exist
    * @since S60 3.1
    * @param aHandler instance implementing MAknAliasKeyCodeResolver 
    */
    IMPORT_C void SetAliasKeyCodeResolverL(MAknAliasKeyCodeResolver* aResolver);
    
    /**
    * This is same as RWindowGroup::CaptureKey, except that this version takes
    * S60 keymappings into account and captures the key that produces requested
    * aKeyCode according to S60 keymappings. Standard RWindowgroup::CaptureKey
    * functionality takes place before S60 AppUi framework and has no knowledge
    * of S60 keymappings.
    * Note: This method requires same capabilites as RWindowGroup::CaptureKey()     
    *
    * @since S60 V3.2
    * @param aKeycode The key code for the key to be captured. Key codes for
    *                 special keys are defined in TKeyCode. 
    * @param aModifier Mask Only the modifier keys in this mask are tested against
    *                      the states specified in aModifier. 
    * @param aModifier The key is captured only when the modifier keys specified in
    *                  aModifierMask match these states, where 1=modifier set,
    *                  and 0=modifier not set. Modifier key states are defined
    *                  in TEventModifier. 
    * @return A handle identifying the capture key, or one of the system-wide error
    *                  codes (if <0). Handles should be kept in order to be passed to
    *                  CancelCaptureKey() later. 
    */
    IMPORT_C TInt32 CaptureKey(TUint aKeycode, TUint aModifierMask, TUint aModifier);         
    
    /**
    * This is same as RWindowGroup::CaptureKey, except that this version takes
    * S60 keymappings into account and captures the key that produces requested
    * aKeyCode according to S60 keymappings. This version leaves instead of returning
    * an error code. Standard RWindowgroup::CaptureKey functionality takes place
    * before S60 AppUi framework and has no knowledge of S60 keymappings.
    * Note: This method requires same capabilites as RWindowGroup::CaptureKey() 
    *
    * @since S60 V3.2
    * @param aKeycode The key code for the key to be captured. Key codes for
    *                 special keys are defined in TKeyCode. 
    * @param aModifier Mask Only the modifier keys in this mask are tested against
    *                      the states specified in aModifier. 
    * @param aModifier The key is captured only when the modifier keys specified in
    *                  aModifierMask match these states, where 1=modifier set,
    *                  and 0=modifier not set. Modifier key states are defined
    *                  in TEventModifier. 
    * @param aHandle   identifying the capture key. Handles should be kept in order
    *                  to be passed to CancelCaptureKey() later. 
    */    
    IMPORT_C void CaptureKeyL(TUint aKeycode, TUint aModifierMask, TUint aModifier, TInt32& aHandle);
    
    /**
    * This tells the application if it is allowed to hide itself in the
    * background in response to a user (menu or softkey) exit command, 
    * instead of actually exiting.
    * If the application appears to exit, but actually leaves itself in
    * memory, it may appear to start faster next time the user activates it.
    *
    * @since S60 V5.0
    * @return ETrue if the application can hide itself in the background, 
    *		  EFalse if it must exit properly by calling Exit().
    */    
    IMPORT_C TBool ExitHidesInBackground() const;
    
    /**
    * Hide the running instance of this application from the user, which
    * makes it appear as if the application has exited.
    * This is done by placing the application in the background, behind 
    * all other apps, and removing the application from the Fast Swap Window.
    * When the application comes to the foreground again, it will be
    * restored to the Fast Swap Window (in HandleForegroundEventL). If the
    * application is not supposed to be in the Fast Swap Window, it will have
    * to remove itself again.
    * @since S60 V5.0
    */    
    IMPORT_C void HideInBackground();
    
    /**
    * Disables next key sound (and repeated key sounds until pointer up event).
    *
    * @since S60 V5.0
    * @param aScanCode Scan code of disabled key.
    */
    IMPORT_C void DisableNextKeySound( TInt aScanCode ); 
    
private:
    TBool ExitHidesInBackgroundL() const;
    };



#endif







