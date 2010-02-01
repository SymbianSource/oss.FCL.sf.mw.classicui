/*
* Copyright (c) 2004-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Internal Publish & Subscribe keys.
 *
 *
*/


#ifndef SCREENSAVER_INTERNAL_PS_KEYS_H
#define SCREENSAVER_INTERNAL_PS_KEYS_H

#include <e32def.h>
#include <e32cmn.h>

const TUid KPSUidScreenSaver = { 0x101F8771 };

/**
 * Screen saver preview mode. This integer value triggers screen saver
 * preview mode. Value is normally 0 but when set to 1 screen saver
 * application goes to preview mode (ie. turns screensaver on for 10 seconds
 * and then terminates it). If screensaver is already on when value is set
 * to 1 then nothing happens.
 *
 * Possible values:
 * 0: default value
 * 1: triggers screensaver preview mode
 */
const TUint32 KScreenSaverPreviewMode      = 0x00000001;

/**
 * Indication of allowing screen saver to be activated.
 *
 * Possible values:
 *  0: screen saver is allowed to be activated.
 * >0: screen saver is not allowed to be activated.
 */
const TUint32 KScreenSaverAllowScreenSaver = 0x00000002;

/**
 * Indication of whether screen saver is on (active) or not.
 *
 * Possible values:
 *  0: screen saver is not active.
 * >0: screen saver is displaying.
 */
const TUint32 KScreenSaverOn               = 0x00000003;

/**
 * Indication of the state of screensaver preview
 */
const TUint32 KScreenSaverPreviewState     = 0x00000004;
enum TScreenSaverPreviewState
    {
    EScreenSaverPreviewNone,      // Initial state, no preview in progress
    EScreenSaverPreviewLoading,   // Preview is loading
    EScreenSaverPreviewInvalid,   // Invalid file for preview
    EScreenSaverPreviewLoaded,    // Preview has been loaded, about to start
    EScreenSaverPreviewStart,     // Start of preview displaying
    EScreenSaverPreviewEnd,       // Preview displaying ended
    EScreenSaverPreviewCancel,    // Preview cancelled (e.g. by user)
    EScreenSaverPreviewError      // An error occurred during preview
    };

/**
 * Indicates whether Idle was in front when screensaver was started.
 * Keyguard uses this indication to decide if it can be automatically
 * activated.
 * 
 * Possible values:
 * 0: Screensaver not active, or not started from Idle
 * 1: Screensaver was started from Idle
 */
const TUint32 KScreenSaverActivatedFromIdle     = 0x00000005;

/**
 * Indicates that currently selected screensaver plugin settings (that can
 * not be otherwise watched through CR & P&S notifications) are being
 * changed. Written by Themes, listened to by plugins interested in knowing
 * whether their settings have changed "on the fly". The plugin does not 
 * write the value, as not all plugins will even listen to this key. 
 * 
 * Possible values:
 * 0: Configured plugin is not the currently selected one,
 *     or settings were left unchanged
 * 1: Current plugin is being configured. This lets the configuration
 *     dialog know the active plugin settings are being changed in Themes, so
 *     it can notify the plugin loaded in Screensaver context that its
 *     settings have changed through this key.
 * 2: Current plugin was configured, and its settings were changed. The
 *     plugin running in Screensaver process should notice this, and reload
 *     its settings. After this the plugin should write the value back to 0.
 */
const TUint32 KScreenSaverPluginSettingsChanged = 0x00000006;
enum TScreenSaverPluginSettingsState
    {
    // Configured plugin not current, or settings did not change
    EScreenSaverPluginSettingsNoChange,
    // Current plugin is being configured
    EScreenSaverPluginSettingsChanging,
    // Current plugin settings have changed
    EScreenSaverPluginSettingsChanged
    };


/**
 * Indicates that Screensaver should not attempt to use display power save mode
 * 
 * Possible values:
 * 0: Power save mode is used normally
 * 1: Power save mode is not used
 */
const TUint32 KScreenSaverNoPowerSaveMode = 0x00000007;

#endif // SCREENSAVER_INTERNAL_PS_KEYS_H

// End of file
