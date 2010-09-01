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
* Description:  Personalisation constants.
*
*/

#ifndef PSLNCONST_H
#define PSLNCONST_H

#include <e32std.h>

#include <AknsSkinUID.h>
#include <AknsItemID.h>
#include <AknsUtils.h>

#include "psln.hrh"
#include "PslnVariant.hrh"

// CONSTANTS

// UID of Personlisation application
const TUid KUidPsln = { 0x10005A32 };

// Screen saver none type.
_LIT( KPslnScreenSaverTypeNone, "None" );
// Screen saver date type.
_LIT( KPslnScreenSaverTypeDateTime, "DateTime" );
// Screen saver text type.
_LIT( KPslnScreenSaverTypeText, "Text" );

// View ID's - STATIC ONES
// General theme view Id.
const TUid KPslnGeneralView     = {0};
// Wallpaper view Id.
const TUid KPslnWallpaperView   = {3};
// Screen saver view Id.
const TUid KPslnScreenSaverView = {4};
// Main view Id.
const TUid KPslnMainView2       = { 0x102750AA };

// Properties view setting ID's
// Wallpaper setting id.
const TInt KPslnBgIdleSettingId = 0;
// Screen saver id.
const TInt KPslnScreenSettingId = 1;

// Default skin index.
const TInt KPslnSeries60SkinIndex = 0;

// Maximum number of characters in Screen saver txt.
const TInt KPslnMaxNumberOfScreenSaverText = 15;

// No resource specified. 
const TInt KPslnNoResource = 0;

// Middle Softkey control ID.
const TInt KPslnMSKControlID = 3;

// Tags for ini-file.
// Screen saver tag for ini-file.
_LIT( KPslnSSaver, "ScreenSaver" );
// Wallpaper tag for ini-file.
_LIT( KPslnIdleBgImage, "IdleImg" );
// Wallpaper path tag for ini-file.
_LIT( KPslnIdleBgImagePath, "IdlePath" );
// Screen saver text tag for ini-file.
_LIT( KPslnScreenSaverText, "ScreenText" );

// Path separator.
_LIT( KPslnPathSeparator, "\\" );

// Memory card drive letter.
#ifndef RD_MULTIPLE_DRIVE
_LIT( KPslnMMCDriveLetter, "E" );
#endif // RD_MULTIPLE_DRIVE

// Default Plugin UIDs.
// Application Shell Plugin UID.
#ifdef FF_HITCHCOCK_APP_SHELL
const TUid KPslnASPluginUid = { 0x10283151 };
#else
const TUid KPslnASPluginUid = { 0x102750A5 };
#endif // FF_HITCHCOCK_APP_SHELL
// Active Idle Plugin UID.
const TUid KPslnAIPluginUid = { 0x102750A7 };

// Max lenght of container setting text.
const TInt KPslnItemLength = 128;

// Space for icon.
const TInt KPslnIconSize = 4; 

// Sound file types.
static const TAknsItemID KPslnSoundItems[] =
    {
        // Ringing tone.
        { EAknsMajorSound, EAknsMinorSoundRingingTone },
        // Message alert tone.
        { EAknsMajorSound, EAknsMinorSoundMessageAlert },
        // None.
        { EAknsMajorNone, EAknsMinorNone } // End of list
    };

// Entry point for dynamically loaded dlls.
const TInt KPslnDllEntryPoint = 1;

// Transition Effects setting values.
enum TPslnTransitionEffects
    {
    // All effects are enabled.
    EPslnEnableAllEffects = 0,
    // All effects are disabled.
    EPslnDisableAllEffects = KMaxTInt
    };

// Minimum memary size for change skin
const TInt KPslnMinMemSize = 2000000;

// Delay time for updateing skin
const TInt KPslnUpdateSkinDelay = 10000;//10ms

#endif // PSLNCONST_H

// End of File
