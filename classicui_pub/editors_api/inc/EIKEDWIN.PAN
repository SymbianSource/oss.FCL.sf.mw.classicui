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


#if !defined(__EIKEDWIN_PAN__)
#define __EIKEDWIN_PAN__

enum TEikEdwinPanic
	{
	EEikPanicEdwinNoWidth,
	EEikPanicEdwinNoHeight,
	EEikPanicEdwinNotRichText,
	EEikPanicEdwinNotOwnCharFormat,
	EEikPanicEdwinNotOwnParaFormat,
	EEikPanicEdwinNoView,
	EEikPanicEdwinBadAttribute,
	EEikPanicEdwinBadClipboardFunc,
	EEikPanicEdwinNoText,
	EEikPanicEdwinNoLayout,
	EEikPanicEdwinNoWindow,
	EEikPanicEdwinInvalidTextLimit,
	EEikPanicEdwinInvalidInsertPos,
	EEikPanicEdwinInvalidFlagCombination,
	EEikPanicEdwinHeightGreaterThanMaximum,
	EEikPanicEdwinMaxHeightWithoutBaseline
	};

GLREF_C void Panic(TEikEdwinPanic aPanic);

#endif
