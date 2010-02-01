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
* Description:  Avkon Internal Publish & Subscribe keys.
*
*/

#ifndef AVKONINTERNALPSKEYS_H
#define AVKONINTERNALPSKEYS_H

const TUid KPSUidAvkonInternal = { 0x10207218 }; // Same as KPSUidAvkonDomain

//
// Note that KPSUidAvkonInternal key range starts from 0x10000000 to avoid 
// conflicts with KPSUidAvkonDomain keys that are using same Uid.
//

/**
 * Indicates the system controlled signal-, battery- and universal indicator data 
 * status. 
 *
 * See AknStatusPaneData.h for data structure details. 
 *
 */
const TUint32 KAknStatusPaneSystemData = 0x10000000;

/**
 * The window group ID of the Idle application.
 */
const TUint32 KAknIdleAppWindowGroupId = 0x10000001;

/**
 * Turn off task swapper option in menu option
 */
const TUint32 KAknMenuOptionNoTaskSwapper = 0x10000002;

/**
 * Bitmap handle for fade plugin
 */
const TUint32 KAknFadeBitmapHandle = 0x10000003;

/**
 * Mask handle for fade plugin
 */
const TUint32 KAknFadeMaskHandle = 0x10000004;

/**
 * Color for fade plugin
 */
const TUint32 KAknFadeColorHandle = 0x10000005;

/**
 * BlackMap for fade plugin
 */
const TUint32 KAknFadeBlackMapHandle = 0x10000006;

/**
 * WhiteMap for fade plugin
 */
const TUint32 KAknFadeWhiteMapHandle = 0x10000007;

#endif

// End of file
