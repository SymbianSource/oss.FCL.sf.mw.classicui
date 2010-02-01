/*
* Copyright (c) 2005-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Internal Central Repository keys for Personalisation app.
*
*/


#ifndef PSLNINTERNALCRKEYS_H
#define PSLNINTERNALCRKEYS_H

/**
*******************************************************************************
* Themes features repository.
*******************************************************************************
*/
const TUid KCRUidThemes = { 0x102818E8 };

/**
* Specifies the user defined path and file name of the image object 
* that is shown when there is an active call.
* 
* Possible values:
*     any path and filename.
*/
const TUint32 KThemesCallImagePath        = 0x00000001;

/**
* Specifies the Call Image setting state. 
*
* Possible values: 0 - 2
*       0 - No default image. Only contact images are shown.
*       1 - User defined call image.
*       2 - Theme call image.
*/
const TUint32 KThemesCallImageSetting     = 0x00000002;

/**
* Specifies the type of wallpaper slide set.
* 
* Possible values:
*       0 - Image set is defined by the user.
*       1 - Random (images are not set by user but randomly defined).
*/
const TUint32 KThemesWallpaperSlideSetType = 0x00000004;

/**
* Specifies the interval between images in wallpaper slide set.
* 
* Possible values: 0 - 4
*       0 - 1 minute, 
*       1 - 10 minutes, 
*       2 - 30 minutes, 
*       3 - 1 hour, 
*       4 - 1 day.
*/
const TUint32 KThemesWallpaperSlideSetInterval = 0x00000005;

/**
* Specifies the type of screensaver slide set.
* 
* Possible values:
*       0 - Image set is defined by the user.
*       1 - Random (images are not set by user but randomly defined).
*/
const TUint32 KThemesScreenSaverSlideSetType = 0x00000006;

/**
* Specifies the duration of backlight in slide set screensaver.
* Value is in seconds (integer).
* 
* Possible values: 0 (off) - 30.
*/
const TUint32 KThemesScreenSaverSlideSetBacklight = 0x00000007;

/**
* Specifies the duration of slide set screensaver.
* Value is in minutes (integer).
*
* Possible values: 1 - 30.
*       
*/
const TUint32 KThemesScreenSaverSlideSetDuration = 0x00000008;

/**
* Specifies if the transition effects are turned off or not.
* Value is used as a bitmask.
* 
* Possible values:
*       zero indicates that all effects are supported.
*       KMaxTInt indicates that all effects are suppressed.
*/
const TUint32 KThemesTransitionEffects = 0x00000009;

/**
* Specifies the default configuration of which types of transition 
* effects are supported, when the effects are enabled.
* Value is used as a bitmask.
*
* Possible values:
*       Any integer value between 0 (all features on - see above) and
*       KMaxTInt (all features off - see above). 
*
*/
const TUint32 KThemesDefaultTransitionEffects = 0x0000000A;

/**
* Specifies the wait time of quick theme preview timer, arisen by touch. 
* Value is in micro seconds.
*
* Possible values: 250000 
*
*/
const TUint32 KThemesPreviewDelayTime = 0x0000000B;

/**
* Specifies the interval period of quick theme preview timer.
* Value is in micro seconds.
*
* Possible values: 200000 
*
*/
const TUint32 KThemesPreviewIntervalTime = 0x0000000C;

/**
* Specifies the wait time of quick theme preview timer, arisen by navigation key. 
* Value is in micro seconds.
*
* Possible values: 750000 
*
*/
const TUint32 KThemesPreviewDelayTimeOnHardKey = 0x0000000D;

/**
* Specifies if the animation effects are turned off or not.
* Value is used as a bitmask.
* 
* Possible values:
*       zero indicates that all effects are supported.
*       KMaxTInt indicates that all effects are suppressed.
*/
const TUint32 KThemesAnimBackgroundSupport = 0x0000000E;


#endif // PSLNINTERNALCRKEYS_H
