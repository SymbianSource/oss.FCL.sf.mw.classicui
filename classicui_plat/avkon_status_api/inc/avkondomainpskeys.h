/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Avkon Domain Publish & Subscribe keys.
*
*/

#ifndef AVKONDOMAINPSKEYS_H
#define AVKONDOMAINPSKEYS_H

const TUid KPSUidAvkonDomain = { 0x10207218 }; // Same as KPSUidAvkonInternal

/**
 * Indicates the status of Keyguard
 *
 * Possible values are:
 *
 * 0: Keyguard is not active
 * 1: Keys are locked
 * 2: Autolock emulation enabled
 *
 */
const TUint32 KAknKeyguardStatus = 0x00000001;

enum TAknKeyguardStatus
    {
    EKeyguardNotActive,
    EKeyguardLocked,
    EKeyguardAutolockEmulation
    };
    
    
/**
* TFX Server Status P&S key
* Indicates transition server state
* 0x1: True if TFXServer is running
*/ 
const TUint32 KAknTfxServerStatus = 0x00000002;
enum TAknTfxServerStatus
	{
	ETfxSrvRunning = 0x1,
	};

/**
* TFX Server redirection status P&S key 
* Indicates whether TFXServer is using redirected drawing
* 0x1: True if drawing is redirected
*/
const TUint32 KAknTfxServerRedirectionStatus = 0x00000003;
enum TAknTfxServerRedirectionStatus 
	{
    ETfxScreenRedirected = 0x1,
	};

/**
 * Indicates the power menu status.
 * Possible values are:
 * 0: Power menu is not open
 * 1: Power menu is open
 */ 
const TUint32 KAknPowerMenuStatus = 0x00000004;
enum TAknPowerMenuStatus
	{
	EPowerMenuNotOpen,
	EPowerMenuOpen
	};	
	
/**
 * Indicates that the combined end key / power key has been pressed. An event is sent only when 
 * the device is in the idle state. "Pure event distribution" pattern is used, therefore the 
 * actual value is meaningless.
 */ 
const TUint32 KAknEndKeyEvent = 0x00000005;
    
/**
 * Contains positive integer in following cases:
 * 1) Idle application is on foreground.
 * 2) Screensaver is on foreground, but idle application is beneath it.
 * Possible global notifiers between those applications are ignored. 
 * Otherwise the value is zero.
 */
const TUint32 KAknNotificationsInIdleAllowed = 0x00000006;

/**
 * Indicates that the number of running global discreet popup changed.
 * This is a pure event distribution, property value is meaningless.
 */
const TUint32 KAknGlobalDiscreetPopupNumChanged = 0x00000007;

#endif

// End of file
