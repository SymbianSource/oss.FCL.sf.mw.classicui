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
* Description:  Internal Publish & Subscribe keys.
 *
 *
*/


#ifndef UIKON_INTERNAL_PS_KEYS_H
#define UIKON_INTERNAL_PS_KEYS_H

const TUid KPSUidUikon = { 0x101F8773 };

/**
 * Free space level of FFS file system (drive C:)
 *
 * Possible values:
 *  0: free space OK
 * -1: free space at or below warning level
 * -2: free space at or below critical level
 */
const TUint32 KUikFFSFreeLevel       = 0x00000001;

/**
 * Free space level of FFS file system (drive MMC:)
 *
 * Possible values:
 *  0: free space OK
 * -1: free space at or below warning level
 * -2: free space at or below critical level
 */
const TUint32 KUikMmcFFSFreeLevel    = 0x00000002;

/**
 * Flip status. This key is updated by AknCapServer according to the
 * flip key events.
 *
 * Possible values:
 * 0: flip close
 * 1: flip open
 */
const TUint32 KUikFlipStatus         = 0x00000003;

/**
 * This key tells which application is topmost when there is an active video
 * call.
 */
const TUint32 KUikVideoCallTopApp    = 0x00000004;

/**
 * To be used by SysAp for notifying OOM Watcher of the MMC status.
 * SysAp initializes this key in startup and if the device supports
 * MMC Hot Swap, updates its status according to MMC mounts/dismounts.
 *
 * Possible values:
 * 0: MMC removed
 * 1: MMC inserted
 */
const TUint32 KUikMMCInserted        = 0x00000005;

/**
 * Information about whether it is allowed to show global notes on the screen
 * or not.
 *
 * No notes should be shown during boot sequence and this setting will remain
 * in the value 0 until the phone is completely booted up.
 *
 * Possible values:
 * 0: global notes are not allowed to be shown.
 * 1: global notes can be shown normally.
 */
const TUint32 KUikGlobalNotesAllowed = 0x00000006;

/**
 * This key is used to signal OOM framework to free RAM. FW will ask
 * applications to exit until amount of free memory exceeds the value given
 * or there is no more application which will exit gracefully.
 * OOM FW signals its completion by setting this value to -1.
 */
const TUint32 KUikOOMWatchdogStatus  = 0x00000007;

/**
 * This key saves the screen resolution state in the device.
 * The value is updated by eiksrvui project in Eikstd which
 * is part of Avkon ui library.
 *
 * Possible values: 0 - x where x is the biggest used layout
 * state value in aknpriv.rss. 
 * Same value in different products can mean different resolution
 * (it depends on aknpriv.rss configuration).
*/
const TUint32 KUikLayoutState  = 0x00000008;

/**
 * Preferred orientation. This key is used to store the preferred orientation
 * for the current hardware layout state.
 *
 * Possible values:
 * 0: Normal screen orientation
 * 1: Alternate screen orientation
 *
 */
const TUint32 KUikPreferredOrientation  = 0x00000009;

enum TPreferredOrientation
    {
    EPreferredOrientationNormal = 0,
    EPreferredOrientationAlternate = 1
    };

/**
 * The list of running aplications meant to be hidden from the user.
 * The list is always the size of 4*KMaxHiddenApps bytes.
 *
 * Stores maximum of KMaxHiddenApps number of application UIDs
 * to the byte array property, the value of 0x00000000 marks 
 * the end of list.
 *
 * Possible values: 
 *
 * 0-KMaxHiddenApps Application UIDs in byte array
 *
 */
const TUint32 KUikAppHiddenList  = 0x00000010;

// the maximum size of array (25 32-bit UIDs equal 100 bytes)
const TInt KMaxHiddenApps = 25;

/**
 * String value containing a space-separated list of the language
 * codes of the language variants that are installed in the device.
 *
 * The list begins and ends with space, so a language ID can be
 * searched from the list with " <LANGUAGE ID> ".
 *
 * The key is defined and set by AknCapServer during the
 * startup of the device and it shouldn't be changed afterwards.
 *
 * @type RProperty::EText
 */
const TUint32 KUikInstalledLanguages = 0x00000011;
    
#endif

// End of file
