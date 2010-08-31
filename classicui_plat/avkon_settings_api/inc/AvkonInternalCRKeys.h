/*
* Copyright (c) 2004 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Internal Central Repository keys.
 *
 *
*/


#ifndef AVKON_INTERNAL_CR_KEYS_H
#define AVKON_INTERNAL_CR_KEYS_H

const TUid KCRUidAvkon = { 0x101F876E };

/**
 * Id of the currently active UI layout, integer value.
 * In first boot this key does not exist - will be set during boot.
 *
 * Possible values:
 *
 * Any value of TAknLayoutId
 */
const TUint32 KAknLayoutId              = 0x00000001;

/**
 * This flag indicates if new contacts note is active. Integer value.
 *
 * Value 0 or KErrNotFound return value means that NCN is not active.
 * Other values mean that NCN is active.
 */
const TUint32 KAknNewContactsNoteActive = 0x00000002;

/**
 * Products must configure this value depending in which orientation
 * applications are started and run when the application does not want
 * to specify any orientation.
 *
 * Possible orientations are:
 *
 * EAppUiOrientationAutomatic = 0
 * EAppUiOrientationPortrait = 1
 * EAppUiOrientationLandscape = 2
 *
 * EAppUiOrientationAutomatic is default in the platform. Follows the
 * device orientation.
 */
const TUint32 KAknDefaultAppOrientation = 0x00000003;

/**
 * Qwerty mode status. This key is updated by Avkon according to the
 * EKeyQwertyOn (=EKeyApplication7) & EKeyQwertyOff (=EKeyApplication8) key events. 
 * The events are sent by keyboard driver when qwerty mode is
 * activated and deactivated.
 *
 * Possible values:
 * 0: Qwerty input mode is not active.
 * 1: Qwerty input mode is active.
 */
const TUint32 KAknQwertyInputModeActive = 0x00000004;

/**
 * String the recently used characters
 * Total size of this data is 80 byte (40 unicode characters).
 *
 * Possible values:
 *
 *  1-10 length 
 * 11-20 length 
 * 21-30 length 
 * 31-40 length 
 *
 */
const TUint32 KAknRecentSctData         = 0x00000005;

/**
 * Id of the currently active UI zoom level, integer value.
 * In first boot this key does not exist - will be set during boot.
 *
 * Possible values:
 *
 * Any value of TAknUiZoom
 */
const TUint32 KAknGlobalUiZoom              = 0x00000006;

/**
 * Value indicates if the extended status pane is the default status pane 
 * type in portrait mode.
 *
 * Possible values are:
 *
 * 0: Extended status pane is not default status pane
 * 1: Extended status pane is default status pane
 *
 */
const TUint32 KAknExtendedPortraitStatusPane = 0x00000007;

/**
 * Value indicates if list stretching is used by default or not.
 *
 * Possible values are:
 *
 * 0: List stretching is not used by default.
 * 1: List stretching is used by default.
 *
 */
const TUint32 KAknAutomaticListStretching = 0x00000008;

/**
 * Value chooses location editor data format
 *
 * Possible values are:
 * 
 * 0: Degrees and Decimal degrees
 * 1: degrees, minutes and decimal minutes
 * 2: degrees, minutes, seconds, decimal seconds
 *
 */
const TUint32 KAknLocationEditorCoordinateDataFormat = 0x00000009;

/**
 * Value indicates if MiddleSoftKey is enabled or not.
 *
 * Possible values are:
 *
 * 0: MSK is not used by default.
 * 1: MSK is used by default.
 *
 */
const TUint32 KAknMiddleSoftkeyEnabled = 0x0000000A;

/**
 * The QWERTY keyboard layout for generic QWERTY framework.
 *
 * Possible values:
 * 0: No Keyboard
 * 1: Keyboard with 12 key
 * 2: QWERTY 4x12 layout
 * 3: QWERTY 4x10 layout
 * 4: QWERTY 3 x 11 layout
 * 5: Half QWERTY
 * 6: Custom QWERTY
 */

const TUint32 KAknKeyBoardLayout = 0x0000000B;

/**
 * Touch compatibility mode settings flags
 *
 * Possible values are:
 *
 * Bit0: Applications may be started in compa-mode
 *
 */
const TUint32 KAknCompaModeSettings = 0x0000000C;

/**
 * Value indicates if Avkon components support transparency.
 * Changing this key needs device restart.
 *
 * Using this key needs WSINI.ini configuration with keyword TRANSPARENCY
 *
 * Possible values are:
 *
 * 0: Transparency code is not executed in Avkon code
 * 1: Avkon components utilize transparency
 *
 */
const TUint32 KAknAvkonTransparencyEnabled = 0x0000000D;

/**
 * The value indicates if adaptive search can be utilized with find pane
 *
 * The applications itself decide if they will support the feature, if available.
 *
 * Possible values are:
 *
 * 0: The adaptive search is disabled from the applications
 * 1: The adaptive search is enabled for the applications
 *
 */
const TUint32 KAknAvkonAdaptiveSearchEnabled = 0x0000000E;

/**
 * Touch compatibility mode saved transition effects state
 *
 * Possible values are:
 *
 * Bit0..30: Saved effects state (KThemesTransitionEffects key value)
 * Bit31: Effects are disabled
 *
 */
const TUint32 KAknCompaModeEffects = 0x0000000F;

/**
 * The value indicates the input method for adaptive search in 
 * Simplified Chinese language
 *
 * Key is created when user selects the language for the first time.
 *
 * Possible values are:
 *
 * 0: Pinyin
 * 1: Stroke
 *
 */
const TUint32 KAknAdaptiveSearchChinesePRC = 0x00000010;

/**
 * The value indicates the input method for adaptive search in 
 * Taiwan traditional Chinese language
 *
 * Key is created when user selects the language for the first time.
 *
 * Possible values are:
 *
 * 0: Zhuyin
 * 1: Stroke
 *
 */
const TUint32 KAknAdaptiveSearchChineseTW = 0x00000011;

/**
 * The value indicates the input method for adaptive search in 
 * Hongkong traditional Chinese language
 *
 * Key is created when user selects the language for the first time.
 *
 * Possible values are:
 *
 * 0: Stroke
 * 1: Cangjie
 *
 */
const TUint32 KAknAdaptiveSearchChineseHongkong  = 0x00000012;

/**
 * Touch compatibility mode local variation flags
 *
 * Possible values are:
 *
 * Bit0: Compa-mode is enabled in device
 *
 */
const TUint32 KAknCompaModeFeatures = 0x00000013;

/**
 * The value indicates the last used input method for 
 * adaptive search in any Chinese language variant.
 * 
 * Value is the CenRep key id of the input methdod. 
 * One of the following: 
 * KAknAdaptiveSearchChinesePRC
 * KAknAdaptiveSearchChineseTW
 * KAknAdaptiveSearchChineseHongkong
 *
 * Key is created when user sets one of the setting items for the first time.
 *
 */
const TUint32 KAknAdaptiveSearchLastChinese = 0x00000014;

/**
 * The resource file name used by editor to enable emotion icon.
 *
 * The key should be enabled in device before used by editor.
 *
 * Initial value should be "smiley"
 *
 */
const TUint32 KAknEmotionResourceFileName = 0x00000015;

const TUid KCRUidLeaveAppsInMemory = { 0x102858F2 };

/**
 * Key range for the LeaveAppsInMemory apps list. 
 * To be used with KLeaveAppsInMemoryAppListKeyMask, meaning that listed
 * app UIDs should have keys of the form 0x0000????
 */
const TUint32 KLeaveAppsInMemoryAppListKeyRange = 0x00000000;

/**
 * Key mask for the LeaveAppsInMemory apps list.
 * To be used with KLeaveAppsInMemoryAppListKeyRange, meaning that listed
 * app UIDs should have keys of the form 0x0000????
 */
const TUint32 KLeaveAppsInMemoryAppListKeyMask = 0xFFFF0000;


#endif

// End of file
