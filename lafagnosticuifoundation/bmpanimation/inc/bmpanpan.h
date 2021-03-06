// Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
//

#if !defined(__BMPANPAN_H__)
#define __BMPANPAN_H__

#include <e32std.h>

enum TBitmapAnimClientPanic
	{
	EAnimationClientPanicNullPointer,
	EAnimationClientPanicStartAnimation,
	EAnimationClientPanicStopAnimation,
	EAnimationClientPanicSettingBackground,
	EAnimationClientPanicSettingPreference,
	EAnimationClientPanicSettingFrame,
	EAnimationClientPanic,
	EAnimationClientPanicFrameIntervalNegative
	};

GLREF_C void Panic(TBitmapAnimClientPanic aPanic);

#endif
