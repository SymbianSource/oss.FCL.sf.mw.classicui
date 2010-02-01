/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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


#if !defined(__EIKCLOCK_PAN__)
#define __EIKCLOCK_PAN__

enum TEikClockPanic
	{
	EEikPanicClockTypeMustBeAllowedToChange,
	EEikPanicClockBadFormat1,
	EEikPanicClockBadFormat2,
	EEikPanicClockBadFormat3,
	EEikPanicClockBadFormat4,
	EEikPanicClockHasAlreadyBeenConstructed,
	EEikPanicClockBadChangeFormatCall,
	EEikPanicClockBadChangeUniversalTimeOffsetAndDaylightSavingZoneCall,
	EEikPanicClockNoNeedToSetFormat,
	EEikPanicClockInconsistentHorizontalTextAlignmentValues,
	EEikPanicClockInconsistentVerticalTextAlignmentValues,
	EEikPanicClockInconsistentHandTypeValues,
	EEikPanicClockBadHandFeatureType,
	EEikPanicClockClockAlreadyExists,
	EEikPanicClockNoControlContext,
	};

GLREF_C void Panic(TEikClockPanic aPanic);

#endif

