// Copyright (c) 2004-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include <fbs.h>

#include "AnimationFrame.h"

/** Destructor.*/
EXPORT_C CAnimationFrame::~CAnimationFrame()
	{
	delete iBitmap;
	delete iMask;
	}

/**
Two stage constructor.

After construction, the frame contains empty bitmaps.

@return The new object
*/
EXPORT_C CAnimationFrame* CAnimationFrame::NewL()
	{
	CAnimationFrame * self = new (ELeave) CAnimationFrame();
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}
	
/**
Two stage constructor.

After construction, the frame contains the bitmaps specified in the handles
argument.

@see GetHandles()
@param aHandles An internal data type used for transferring the contents
@return The new object
*/
EXPORT_C CAnimationFrame* CAnimationFrame::NewL(const THandles& aHandles)
	{
	CAnimationFrame * self = NewL();
	CleanupStack::PushL(self);
	self->SetHandlesL(aHandles);
	CleanupStack::Pop(self);
	return self;
	}

void CAnimationFrame::ConstructL()
	{
	iBitmap = new (ELeave) CFbsBitmap;
	iMask = new (ELeave) CFbsBitmap;
	}

/**
Initialises the internal bitmaps to the correct sizes for the frame.
@param aFrameInfo A TFrameInfo object indicating the required size
of the bitmaps.
*/
EXPORT_C void CAnimationFrame::CreateL(const TFrameInfo& aFrameInfo)
	{
	iFrameInfo = aFrameInfo;
	iBitmap->Reset();
	iMask->Reset();
	User::LeaveIfError(iBitmap->Create(iFrameInfo.iFrameCoordsInPixels.Size(), iFrameInfo.iFrameDisplayMode));
	User::LeaveIfError(iMask->Create(iFrameInfo.iFrameCoordsInPixels.Size(), EGray256));
	}
	
/**
Obtains an alternative representation of the frame suitable for transferring
over most interfaces (a THandle uses handles instead of pointers).

@see SetHandlesL()
@param aHandles A handles object to populate
*/
EXPORT_C void CAnimationFrame::GetHandles(THandles & aHandles) const
	{
	aHandles.iBitmapHandle = iBitmap->Handle();
	aHandles.iMaskHandle = iMask->Handle();
	aHandles.iFrameInfo = iFrameInfo;
	}
	
/**
Sets the contents of the internal bitmaps to those represented by the handles.

@see GetHandles()
@param aHandles A handles object obtained from a call to GetHandles
*/
EXPORT_C void CAnimationFrame::SetHandlesL(const THandles & aHandles)
	{
	iBitmap->Duplicate(aHandles.iBitmapHandle);
	iMask->Duplicate(aHandles.iMaskHandle);
	iFrameInfo = aHandles.iFrameInfo;
	}

/** Reserved for future use */
EXPORT_C void CAnimationFrame::CAnimationFrame_Reserved1() { }

/** Reserved for future use */
EXPORT_C void CAnimationFrame::CAnimationFrame_Reserved2() { }

