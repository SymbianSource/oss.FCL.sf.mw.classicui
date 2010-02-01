/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:
*
*/

#include "AknScreenMode.h"
#include "AknLayoutConfig.h"
#include "AknSgcc.h"
#include "AknLayoutConfigInternal.h"
#include "AknPanic.h"
#include "aknappui.h"

EXPORT_C TSize TAknScreenMode::SizeInPixels() const
    {
    return iInfo.iPixelsTwipsAndRotation.iPixelSize;
    }

EXPORT_C TDisplayMode TAknScreenMode::DisplayMode() const
    {
    return iInfo.iDisplayMode;
    }

EXPORT_C TInt TAknScreenMode::ModeNumber() const
	{
	return iInfo.iModeNumber;
	}

TAknScreenMode::TAknScreenMode(const SAknScreenModeInfo& aInfo)
: iInfo(aInfo)
	{
	}


EXPORT_C TAknScreenModes TAknScreenModes::GetModes()
    {
    return CAknSgcClient::LayoutConfig().ScreenModes();
    }

EXPORT_C TInt TAknScreenModes::Count() const
    {
    return iInfo.iNumScreenModes;
    }

EXPORT_C TAknScreenMode TAknScreenModes::operator[](TInt aIndex) const
    {
	__ASSERT_ALWAYS(0 <= aIndex && aIndex < iInfo.iNumScreenModes, Panic(EAknPanicLayoutConfigBadScreenModeIndex));
	return TAknScreenMode(iInfo.iScreenModes[aIndex]);
    }

EXPORT_C void TAknScreenModes::SetAppUiScreenModeL(CAknAppUiBase* aAppUi, const TAknScreenMode& aMode)
    {
    aAppUi->SetScreenModeL(aMode.ModeNumber());
    }

TAknScreenModes::TAknScreenModes(const SAknLayoutConfig& aInfo)
: iInfo(aInfo)
    {
    }


