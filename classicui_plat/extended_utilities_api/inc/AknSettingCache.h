/*
* Copyright (c) 2002-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Interface for fetching certain system settings in UI controls.
*
*/


#ifndef AKN_SETTING_CACHE_H
#define AKN_SETTING_CACHE_H

// INCLUDES
#include <e32base.h>
#include <AknLayoutDef.h> // for TAknLayoutId
#include <AknDef.h> // for TAknUiZoom

// CONSTANTS

// FORWARD DECLARATIONS

// CLASS DECLARATIONS

/**
* Interface for implementing setting cache plugins, provided by AppUi clients. 
* The plugin mechanism offers clients the ability to register themselves with 
* the AppUi, so that client specific settings can be updated when necessary, 
* and so that the plugin can report that a change has occurred to those settings. 
* The plugin can also cache the value of the setting, and report it when requested,
* although in practice the AppUi would have to know about the setting in order to 
* know what to do with it.
*
* The idea is that there may be a single setting whose current value can in principle 
* be controlled by a number of clients. At any one time, one of those clients has the 
* right to control the actual value of the setting, but each of the other clients may
* need to listen to other events in order to keep their values up to date. The clients 
* are arranged in a stack, so that the most recently added client overrides the values
* that are managed by the previously added clients.
*
* The plugins can handle specific event IDs, for example @c KAknLocalZoomLayoutSwitch. 
* When the setting cache is updated, for example during a layout switch event, 
* the plugins are asked to update their own cached values (in the order of the stack). 
*
* The first plugin that claims to handle the event id, and successfully updates, 
* is then asked for its value; however all other plugins will still get a chance to update. 
*
* It is possible to de-register from the middle of the stack (although in 
* practice clients should ensure that the stacking corresponds logically to 
* their own application context). 
*
* Consult the document S60 AVKON Zoom Design Document for a description of how 
* this API can be used to implement local zoom functionality by handling the 
* @c KAknLocalZoomLayoutSwitch event id.
*
* @lib avkon.lib
* @since 3.1
* @internal to S60
*/
class MAknSettingCacheUpdatePlugin
    {
    public:
        /**
        * Report whether the plugin handles a given event id. Resgistered 
        * plugins are queried in order of most recent registration. @c Update is 
        * only called on the plugin if it claims to handle the event id.
        * @param aEventId event id to be queried
        * @return ETrue if the event id is handled
        */
        virtual TBool HandlesEvent(TInt aEventId) const = 0;

        /**
        * Update the setting cache plugin's cached values,
        * and report whether any values were changed. If this plugin is not 
        * the most recently registered plugin (that handles a given event id) 
        * the return value will be ignored.
        * @param aEventId event id to be processed
        * @return ETrue if the event has caused an update, EFalse otherwise
        */
        virtual TBool Update(TInt aEventId) = 0;
        
        /**
        * Return the value that is being managed by this plugin for the 
        * specified event. 
        * @param aEventId the event id
        * @param aValue output the value
        * @return KErrNone if there was no error.
        */
        virtual TInt GetValue(TInt aEventId, TInt& aValue) const = 0;
    };

/**
* Interface for fetching certain system settings in UI controls.
* AknEnv owns an instance of this.
*
* @lib avkon.dll
* @since 2.0
* @internal to S60
*/
NONSHARABLE_CLASS(CAknSettingCache) : public CBase
    {
    public:     // Public c'tor and d'tor

        static CAknSettingCache* NewL();
        ~CAknSettingCache();

    public: // New methods

        /**
        * Returns the current input language (Symbian OS language code).
        *
        * @since 2.0
        *
        * @return Current input language.
        */
        IMPORT_C TLanguage InputLanguage();

        /**
        * Returns the current layout ID.
        *
        * @since 2.0
        *
        * @return Current layout ID.
        */
        IMPORT_C TAknLayoutId LayoutId();

        /**
        * Returns the current hardware layout state.
        *
        * @since 2.8
        *
        * @return Current hardware layout state.
        */
        IMPORT_C TInt HardwareLayoutState();

        /**
        * Returns the preferred orientation for the current hardware layout state.
        *
        * @since 3.1
        *
        * @return Preferred orientation for current hardware layout state.
        */
        IMPORT_C TInt PreferredOrientation();

        /**
        * Returns the current hardware layout state.
        *
        * @since 3.1
        *
        * @return Current Global UI Zoom level
        */
        IMPORT_C TAknUiZoom GlobalUiZoom();

    public: // New methods

        /**
        * Updates the cache.
        * Called by CEikAppUi before forwarding events to application controls.
        * Others should not call this method.
        *
        * @internal
        *
        * @param aEventId UID of the event that causes cache update.
        *
        * @return ETrue if value was changed, EFalse if not.
        */
        IMPORT_C TBool Update( TInt aEventId );

        /**
        * Register a new plugin. This plugin may be queried during update
        * if internal settings or previously registered plugins have not already 
        * reported an update. Leaves if there was an error.
        * 
        * @internal
        * @since 3.1
        * @param aPlugin plugin being registered, ownership is not passed
        */
        IMPORT_C void RegisterPluginL(MAknSettingCacheUpdatePlugin* aPlugin);
        
        /**
        * De-register and destroy a plugin. If the plugin has been previously registered, then
        * it will be removed from the internal data structure. If the plugin cannot be found, 
        * no action is taken.
        * 
        * @internal
        * @since 3.1
        * @param aPlugin plugin being de-registered
        *
        */
        IMPORT_C void DeRegisterPlugin(MAknSettingCacheUpdatePlugin* aPlugin);
        
        /**
        * Request the value from the most recently registered plugin for a given
        * channel. There should be a registered plugin that is listening to the 
        * specified channel id, otherwise an error will be reported
        *
        * @internal
        * @since 3.1
        * @param aEventId the event id 
        * @param aValue the output value, will be invalid if return value is KErrNotFound
        * @return KErrNone if plugin found that supports this channel, otherwise KErrNotFound
        */
        IMPORT_C TInt PluginValue(TInt aEventId, TInt& aValue);
        
        /**
        * Return if Transparency is Enabled .
        *
        * @since 5.0
        *
        * @return if Transparency is Enabled.
        */
        IMPORT_C TBool TransparencyEnabled();
                
    private:    // Private constructors

        CAknSettingCache();

    private:    // New methods

        enum TCacheFlag
            {
            EInputLanguage  = 0x00000001,
            ELayoutId       = 0x00000002,
            EHardwareLayout = 0x00000004,
            EGlobalUiZoom = 0x00000008,
            EPreferredOrientation = 0x00000010,
            ETransparencyEnabled = 0x00000020
            };

        TBool UpdateFromPubSub(
            const TUid aUid, TUint32 aKey, TInt& aValue, TCacheFlag aFlag);

        TBool UpdateFromCenRep(
            const TUid aUid, TUint32 aKey, TInt& aValue, TCacheFlag aFlag);

    private:    // Data

        TInt iFlags;

        // cached settings
        TLanguage iInputLanguage;
        TAknLayoutId iLayoutId;
        TInt iHardwareLayout;
        TAknUiZoom iGlobalUiZoom;
        TInt iPreferredOrientation;
        TInt iTransparencyEnabled;
               
        // plugins
        RPointerArray<MAknSettingCacheUpdatePlugin> iPlugins; // plugins are not owned
    };

#endif // AKN_SETTING_CACHE_H

// End of File
