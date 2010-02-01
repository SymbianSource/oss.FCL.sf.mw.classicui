/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Variation flags in central repository
*
*/


#ifndef __AKNCOMPAFLAGS_H__
#define __AKNCOMPAFLAGS_H__

// Flags for KAknCompaModeFeatures
const TInt KAknCompaFeatureEnaCompaMode = 1; // Enable compa-mode in device

// Flags for KAknCompaModeSettings
// Enable applications to start in compa-mode
const TInt KAknCompaSettingEnaApps = 1;

// Start rom applications in compa-mode
const TInt KAknCompaSettingEnaRomApps = 2;

// Flags for KAknCompaModeEffects
const TInt KAknCompaModeEffectsSaved = (1 << 31);
const TInt KAknCompaModeEffectsDisabled = 0x7fffffff;


#endif // __AKNCOMPAFLAGS_H__
