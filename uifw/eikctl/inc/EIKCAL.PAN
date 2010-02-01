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


#if !defined(__EIKCALPAN__)
#define __EIKCALPAN__

enum TEikCalendarPanic
	{
	EEikPanicCalendarDivideTestCodeFailed,
	EEikPanicCalendarBadNumMonths,
	EEikPanicCalendarNoTextSeparatingYearRange,
	EEikPanicCalendarCannotDisplayAllMonths,
	EEikPanicCalendarBadMinimumAndMaximum,
	EEikPanicCalendarBadStartMonth1,
	EEikPanicCalendarBadStartMonth2,
	EEikPanicCalendarBadSize,
	EEikPanicCalendarBadComponentControlIndex,
	EEikPanicCalendarNoControlContext,
	EEikPanicCalendarBadRowOrColumn,
	EEikPanicCalendarBadRule1,
	EEikPanicCalendarBadRule2,
	EEikPanicCalendarCannotAlterCursor1,
	EEikPanicCalendarCannotAlterCursor2,
	EEikPanicCalendarCannotAlterCursor3,
	EEikPanicCalendarNotFocused,
	EEikPanicCalendarShouldHaveCompletedDrawingDayMatrix,
	EEikPanicCalendarBadRangeOfColumns,
	EEikPanicCalendarBadDivisor,
	EEikPanicCalendarDialogBadResourceId,
	EEikPanicCalendarDialogBadButtonId
	};

GLREF_C void Panic(TEikCalendarPanic aPanic);

#endif

