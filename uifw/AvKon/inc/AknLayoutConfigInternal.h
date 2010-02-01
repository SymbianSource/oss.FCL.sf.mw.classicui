/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Structures used by AknScreenMode and AknLayoutConfig
*               
*
*/


#ifndef AKNLAYOUTCONFIGINTERNAL_H
#define AKNLAYOUTCONFIGINTERNAL_H

#include <w32std.h>
#include <AknPriv.hrh>

struct SAknScreenModeInfo
	{
	TInt iModeNumber;
	TPixelsTwipsAndRotation iPixelsTwipsAndRotation;
	TAknPrivSoftkeyLocation iSoftkeyLocation;
	TInt iScreenStyleHash;
	TDisplayMode iDisplayMode;
	};

struct SHardwareStateInfo
	{
	TInt iStateNum;
	TInt iKeyCode;
	TInt iScreenMode;
	TInt iAltScreenMode;
	};

struct SAknLayoutConfig
	{
	TInt iNumScreenModes;
	SAknScreenModeInfo* iScreenModes;
	TInt iNumHardwareStates;
	SHardwareStateInfo* iHardwareStates;
	};



#endif