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


#if !defined(__BMPANCONSTS_H__)
#define __BMPANCONSTS_H__

/**
TBitmapAnimCommand

@internalComponent
*/
enum TBitmapAnimCommand
	{
	EBitmapAnimCommandSetBackgroundFrame,
	EBitmapAnimCommandSetDataFrame,
	EBitmapAnimCommandSetFlash,
	EBitmapAnimCommandSetFrameIndex,
	EBitmapAnimCommandSetFrameInterval,
	EBitmapAnimCommandSetNumberOfCycles,
	EBitmapAnimCommandSetPlayMode,
	EBitmapAnimCommandSetPosition,
	EBitmapAnimCommandStartAnimation,
	EBitmapAnimCommandStopAnimation,	
	EBitmapAnimCommandStartAnimationAndKeepLastFrame,
	EBitmapAnimCommandResetFrameArray,
	EBitmapAnimCommandClearDataFrames
	};

#endif

