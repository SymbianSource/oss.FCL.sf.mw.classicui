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


#ifndef SCREENSAVER_INTERNAL_CR_KEYS_H
#define SCREENSAVER_INTERNAL_CR_KEYS_H

const TUid KCRUidScreenSaver = { 0x101F8770 };

/**
 * Specifies name of screen saver plugin module currently in use.
 * The string doesn't contain path information, only the name of plugin module
 * dll. This value applies only if "KScreenSaverObject" is set to value 3,
 * otherwise it has no effect.
 *
 * Default value: "" (empty string)
 */
const TUint32 KScreenSaverPluginName = 0x00000001;

/**
 * Screen saver object.
 *
 * Possible values:
 * 0: text
 * 1: time and date (default value)
 * 3: plugin
 */
const TUint32 KScreenSaverObject     = 0x00000002;
enum TScreensaverObjectType
    {
    EScreensaverTypeText = 0,
    EScreensaverTypeDate,
    EScreensaverTypeBitmap,  // Not used
    EScreensaverTypePlugin
    };

/**
 * Screen saver text.
 * The value is a string (max length 15).
 *
 * Default value: "" (empty string)
 */
const TUint32 KScreenSaverText       = 0x00000003;

/**
 * Screen saver using inverted color.
 * This is to be used for product variation, especially
 * for those products with OLED display.
 * Possible Values -
 *  
 * 0 : Normal screensaver colors 
 * 		(white and blue backgrounds with black letters/indicators)
 * 
 * 1 : Black background with white letters/indicators)
 * 		(this provides for more power saving in OLED displays)
 * 
 * Default value: 0 
 */
const TUint32 KScreenSaverInvertedColors    = 0x00000004;

#endif

// End of file
