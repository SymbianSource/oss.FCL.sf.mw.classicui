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

#include "bmpansrv.h"	// for the structures definition used for the packaging
#include "bmpanpan.h"	// for panics


const TInt KFrameDataArrayGranularity = 5;
const TInt KDefaultFrameIntervalInMilliSeconds = 0;


/**
 class CBitmapFrameData
*/

CBitmapFrameData::CBitmapFrameData() 
	: iBitmapsOwnedExternally(EFalse)
	{
	}


/**
 Destructor.

It deletes the bitmap and mask objects owned by the frame unless the "owned 
externally" (SetBitmapsOwnedExternally()) flag is set. 
*/
EXPORT_C CBitmapFrameData::~CBitmapFrameData()

	{
	if(!iBitmapsOwnedExternally)
		{
		if(iMaskBitmap != iBitmap)
			{
			delete iMaskBitmap;
			}

		delete iBitmap;
		}
	}



/**
 Creates a new empty frame object.

@return New CBitmapFrameData object 
*/
EXPORT_C CBitmapFrameData* CBitmapFrameData::NewL()
	{
	CBitmapFrameData* self = new (ELeave) CBitmapFrameData();
	return self;
	}



/**
 Creates a new frame object with a specified bitmap and (optionally) a mask. 

The object takes ownership of the specified bitmap and mask.

@param aBitmap A pointer to the bitmap to use in the new frame
@param aMask If non-NULL, a pointer to the mask to use in the new frame
@return New CBitmapFrameData object 
*/
EXPORT_C CBitmapFrameData* CBitmapFrameData::NewL(CFbsBitmap* aBitmap,CFbsBitmap* aMask)
	{
	__ASSERT_DEBUG(aBitmap, Panic(EAnimationClientPanicNullPointer));

	CBitmapFrameData* self = NewL();
	CleanupStack::PushL(self);	// 
	self->SetBitmap(aBitmap);
	self->SetMask(aMask);
	CleanupStack::Pop();	// self

	return self;
	}



/**
 Creates a new frame object.

It takes ownership of the specified bitmap and mask (if specified), and 
is assigned the frame duration and position.

@param aBitmap A pointer to the bitmap to use in the frame. 
@param aMask If non-NULL, a pointer to the mask to use in the frame. 
@param aIntervalInMilliSeconds The frame's duration in milliseconds. 
@param aPosition The frame's position relative to the animation window. 
@return New CBitmapFrameData object 
*/
EXPORT_C CBitmapFrameData* CBitmapFrameData::NewL(CFbsBitmap* aBitmap,CFbsBitmap* aMask, TInt aIntervalInMilliSeconds, TPoint aPosition)
	{
	__ASSERT_DEBUG(aBitmap, Panic(EAnimationClientPanicNullPointer));

	CBitmapFrameData* self = NewL();
	CleanupStack::PushL(self);	// 
	self->SetBitmap(aBitmap);
	self->SetMask(aMask);
	self->SetPosition(aPosition);
	self->SetInterval(aIntervalInMilliSeconds);
	CleanupStack::Pop();	// self

	return self;
	}


/**
 Sets the frame bitmap.

Unless the "owned externally" (SetBitmapsOwnedExternally()) flag is set, it 
deletes any existing frame bitmap and takes ownership of the new bitmap.

@param aBitmap The frame bitmap 
*/
EXPORT_C void CBitmapFrameData::SetBitmap(CFbsBitmap* aBitmap)
	{
	__ASSERT_DEBUG(aBitmap, Panic(EAnimationClientPanicNullPointer));

	if(!iBitmapsOwnedExternally && iBitmap != iMaskBitmap)
		{
		delete iBitmap;
		}

	iBitmap = aBitmap;
	}



/**
 Gets the frame's bitmap. 

This does not affect ownership of the bitmap.

@return The frame's bitmap 
*/
EXPORT_C CFbsBitmap* CBitmapFrameData::Bitmap() const
	{
	return iBitmap;
	}



/**
 Sets the frame mask.

Unless the "owned externally" (SetBitmapsOwnedExternally()) flag is set, it 
deletes any existing mask bitmap and takes ownership of the new bitmap.

@param aMask Mask to use in the frame 
*/
EXPORT_C void CBitmapFrameData::SetMask(CFbsBitmap* aMask)
	{
	if(!iBitmapsOwnedExternally && iBitmap != iMaskBitmap)
		{
		delete iMaskBitmap;
		}

	iMaskBitmap = aMask;
	}



/**
 Gets the frame's mask. 

This does not affect ownership of the bitmap.

@return The frame's mask 
*/
EXPORT_C CFbsBitmap* CBitmapFrameData::Mask() const
	{
	return iMaskBitmap;
	}



/**
 Sets the frame's duration in milliseconds. 

You can alternatively set the interval for a complete animation using CBitmapAnimClientData::SetFrameInterval(). 
However, an interval set for an individual frame overrides any interval set 
at the animation level.

@param aIntervalInMilliSeconds The number of milliseconds to display the frame 
*/
EXPORT_C void CBitmapFrameData::SetInterval(TInt aIntervalInMilliSeconds)
	{
	iIntervalInMilliSeconds = aIntervalInMilliSeconds;
	}



/**
 Gets the frame's duration in milliseconds.

@return The number of milliseconds for which the frame is displayed 
*/
EXPORT_C TInt CBitmapFrameData::IntervalInMilliSeconds() const
	{
	return iIntervalInMilliSeconds;
	}



/**
 Sets the frame's position relative to the animation window.

@param aPosition The frame's position relative to the animation window 
*/
EXPORT_C void CBitmapFrameData::SetPosition(TPoint aPosition)
	{
	iPosition = aPosition;
	}



/**
 Gets the frame's position, relative to the animation window.

@return The frame's position, relative to the animation window. 
*/
EXPORT_C TPoint CBitmapFrameData::Position() const
	{
	return iPosition;
	}



/**
 Sets whether the bitmap and mask are owned by the frame.

@param aOwnedExternally If ETrue, the bitmap and mask are specified as being 
owned externally and the CBitmapFrameData destructor is NOT responsible for destroying the bitmap.
If EFalse, the CBitmapFrameData destructor is responsible for destroying the bitmap.
*/
EXPORT_C void CBitmapFrameData::SetBitmapsOwnedExternally(TBool aOwnedExternally)
	{
	iBitmapsOwnedExternally = aOwnedExternally ? ETrue : EFalse;
	}



/**
 Tests whether the frame owns the bitmap and mask.

@return ETrue if the bitmap is owned externally, EFalse  otherwise. 
*/
EXPORT_C TBool CBitmapFrameData::BitmapsOwnedExternally() const
	{
	return iBitmapsOwnedExternally;
	}




/**
 class CBitmapAnimClientData
*/
CBitmapAnimClientData::CBitmapAnimClientData() :
	iFlash(EFalse),
	iPlayMode(EPlay),
	iFrameIntervalInMilliSeconds(KDefaultFrameIntervalInMilliSeconds),
	iFrameArray(KFrameDataArrayGranularity)
	{
	}



/**
 Destructor.

 It deletes the background frame and destroys the contents of the frame array. 
*/
EXPORT_C CBitmapAnimClientData::~CBitmapAnimClientData()
	{
	delete iBackgroundFrame;
	iFrameArray.ResetAndDestroy();
	}



/**
 Allocates and constructs a new CBitmapAnimClientData object.

@return New CBitmapAnimClientData object 
*/
EXPORT_C CBitmapAnimClientData* CBitmapAnimClientData::NewL()
	{
	CBitmapAnimClientData* self = new (ELeave) CBitmapAnimClientData;
	return self;
	}



/**
 Appends a new frame to the array of frames. 

The array takes ownership of the new frame.

@param aFrame A pointer to the frame to add to the array of frames 
*/
EXPORT_C void CBitmapAnimClientData::AppendFrameL(CBitmapFrameData* aFrame)
	{
	iFrameArray.AppendL(aFrame);
	}



/**
 Gets the animation frame array.

@return Animation frame array 
*/
EXPORT_C const CArrayPtrFlat<CBitmapFrameData>& CBitmapAnimClientData::FrameArray() const
	{

	return iFrameArray;
	}



/**
 Resets and destroys the frame array's contents. 
*/
EXPORT_C void CBitmapAnimClientData::ResetFrameArray()
	{
	iFrameArray.ResetAndDestroy();
	}



/**
 Sets the background frame and takes ownership of it.

Any previous background frame, and mask if one is included, is deleted from 
memory. The frame is redrawn in the animation window in order to clear the 
current frame before drawing the next one.

@param aBackgroundFrame The bitmap to use as the background frame 
*/
EXPORT_C void CBitmapAnimClientData::SetBackgroundFrame(CBitmapFrameData* aBackgroundFrame)
	{

	if(iBackgroundFrame)
		{
		delete iBackgroundFrame;
		}

	iBackgroundFrame = aBackgroundFrame;
	}



/**
 Gets the background frame bitmap.

@return Background frame bitmap 
*/
EXPORT_C CBitmapFrameData* CBitmapAnimClientData::BackgroundFrame() const
	{
	return iBackgroundFrame;
	}



/**
 Sets or unsets the animation's flash state.

@param aFlash ETrue for the animation to flash, otherwise EFalse 
*/
EXPORT_C void CBitmapAnimClientData::SetFlash(TBool aFlash)
	{
	iFlash = aFlash;
	}



/**
 Gets the animation's flash setting.

@return ETrue if the animation is flashing, otherwise EFalse 
*/
EXPORT_C TBool CBitmapAnimClientData::Flash() const
	{
	return iFlash;
	}



/**
 Specifies for how many milliseconds each frame in the animation is displayed. 

This is not used for any frames in the animation that specify their own interval.

@param aFrameIntervalInMilliSeconds The number of milliseconds for which each 
frame in the animation is displayed 
*/
EXPORT_C void CBitmapAnimClientData::SetFrameInterval(TInt aFrameIntervalInMilliSeconds)
	{
	__ASSERT_DEBUG(aFrameIntervalInMilliSeconds >= 0, Panic(EAnimationClientPanicFrameIntervalNegative));
	iFrameIntervalInMilliSeconds = aFrameIntervalInMilliSeconds;
	}



/**
 Gets the default animation frame interval in milliseconds.

@return Default animation frame interval in milliseconds 
*/
EXPORT_C TInt CBitmapAnimClientData::FrameIntervalInMilliSeconds() const
	{
	return iFrameIntervalInMilliSeconds;
	}



/**
 Sets the play mode so that the animation plays once or continuously.

@param aPlayMode The animation play mode 
*/
EXPORT_C void CBitmapAnimClientData::SetPlayMode(TPlayMode aPlayMode)
	{
	iPlayMode = aPlayMode;
	}



/**
 Gets the animation's play mode.

@return Animation's play mode 
*/
EXPORT_C CBitmapAnimClientData::TPlayMode CBitmapAnimClientData::PlayMode() const
	{
	return iPlayMode;
	}



/**
 Gets the display size required to show the entire animation.

@return Display size 
*/
EXPORT_C TSize CBitmapAnimClientData::Size() const
	{
	TSize size;
	TSize frameSize;
	const TInt count = iFrameArray.Count();
	CBitmapFrameData* frame;
	CFbsBitmap* bitmap;

	TInt index = 0;

	for (index=0; index < count; index++)
		{
		frame = iFrameArray.At(index);
		bitmap = frame->Bitmap();
		if (bitmap)
			{
			frameSize = frame->Bitmap()->SizeInPixels() + frame->Position().AsSize();
			}

		size.iHeight = Max(size.iHeight, frameSize.iHeight);
		size.iWidth = Max(size.iWidth, frameSize.iWidth);
		}
	// for the background frame
	if (iBackgroundFrame && iBackgroundFrame->Bitmap())
		{
		frameSize = iBackgroundFrame->Bitmap()->SizeInPixels() + iBackgroundFrame->Position().AsSize();
		size.iHeight = Max(size.iHeight, frameSize.iHeight);
		size.iWidth = Max(size.iWidth, frameSize.iWidth);
		}

	return size;
	}




/**
 Gets the time required to display the entire sequence of frames that comprise 
the animation. 

This time is expressed in milliseconds.

@return Animation duration 
*/
EXPORT_C TInt CBitmapAnimClientData::DurationInMilliSeconds() const
	{
	TInt time = 0;
	TInt frameInterval;
	const TInt count = iFrameArray.Count();

	TInt index = 0;

	for (index = 0; index < count; index++)
		{
		frameInterval = iFrameArray.At(index)->IntervalInMilliSeconds();

		if (frameInterval < 0)
			{
			frameInterval = ((iFrameIntervalInMilliSeconds > 0) ? iFrameIntervalInMilliSeconds : KDefaultFrameIntervalInMilliSeconds);
			}

		time += frameInterval;
		}

	return time;
	}



/**
 class RBitmapAnim
*/

/**
 Constructor.

@param aAnimDll A reference to the DLL that runs the animation 
*/
EXPORT_C RBitmapAnim::RBitmapAnim(RAnimDll& aAnimDll)
	:RAnim(aAnimDll)
	{
	}



/**
 Completes construction of an animation object. 

This must be done after calling RBitmapAnim(), and before an application attempts 
any other communication with the server.

@param aWindow A reference to the container control window that will hold 
the animation. 
*/
EXPORT_C void RBitmapAnim::ConstructL(const RWindowBase& aDevice)
	{
	TPtrC8 des(NULL,0);
	User::LeaveIfError(RAnim::Construct(aDevice, 0, des));
	}



/**
 Sets the animation frame to display.

How it appears depends on whether the animation is already running. If the 
animation is running, the animation jumps to the specified frame, then 
continues playing. If the animation is not running, the animation is played, 
starting with the specified frame

@param aIndex The frame to display. 
*/
EXPORT_C void RBitmapAnim::DisplayFrameL(TInt aIndex)
	{
	TPckgBuf<SBitmapAnimIndexFrame> bitmapAnimIndexFrame;
	bitmapAnimIndexFrame().iIndex = aIndex;
	User::LeaveIfError(CommandReply(EBitmapAnimCommandSetFrameIndex, bitmapAnimIndexFrame));
	}




/**
 Specifies the animation object to play and sends it to the animation server.

To start the animation, you must subsequently call StartL().
Calling this method while an animation is running will stop the animation.

@param aBitmapAnimData The animation object to play 
*/
EXPORT_C void RBitmapAnim::SetBitmapAnimDataL(const CBitmapAnimClientData& aBitmapAnimData)
	{
	SetAttributesL(aBitmapAnimData);

	const CArrayPtrFlat<CBitmapFrameData>& frameArray = aBitmapAnimData.FrameArray();
	SetFrameArrayL(frameArray);

	CBitmapFrameData* frameData = aBitmapAnimData.BackgroundFrame();
	
	if (frameData)
		{
		SetBackgroundFrameL(*frameData);
		}
	}



/**
 Sets or unsets the animation to be drawn flashing.

@param aFlash ETrue to draw the animation flashing, otherwise EFalse. 
*/
EXPORT_C void RBitmapAnim::SetFlashL(TBool aFlash)
	{
	TPckgBuf<TBmpAnimAttributes> bitmapAnimFlash;
	bitmapAnimFlash().iFlash = aFlash;
	User::LeaveIfError(CommandReply(EBitmapAnimCommandSetFlash, bitmapAnimFlash));
	}



/**
 Specifies the number of milliseconds for which each frame in the animation 
is displayed. 

This is not used for any frames in the animation that specify their own interval.

@param aFrameIntervalInMilliSeconds The number of milliseconds for which each 
frame in the animation is displayed 
*/
EXPORT_C void RBitmapAnim::SetFrameIntervalL(TInt aFrameIntervalInMilliSeconds)
	{
	__ASSERT_DEBUG(aFrameIntervalInMilliSeconds >= 0, Panic(EAnimationClientPanicFrameIntervalNegative));
	TPckgBuf<TBmpAnimAttributes> bitmapAnimFrameInterval;
	bitmapAnimFrameInterval().iFrameIntervalInMilliSeconds = aFrameIntervalInMilliSeconds;
	User::LeaveIfError(CommandReply(EBitmapAnimCommandSetFrameInterval, bitmapAnimFrameInterval));
	}



/**
 Sets how many times the animation is played. 

If the play mode is CBitmapAnimClientData::EBounce, the number of cycles must 
be at least two to ensure a complete animation routine is played.

@param aNumberOfCycles The number of times to play the animation. 
*/
EXPORT_C void RBitmapAnim::SetNumberOfCyclesL(TInt aNumberOfCycles)
	{
	TPckgBuf<SBitmapAnimNumberOfCycles> bitmapAnimNumberOfCycles;
	bitmapAnimNumberOfCycles().iCycles = aNumberOfCycles;
	User::LeaveIfError(CommandReply(EBitmapAnimCommandSetNumberOfCycles, bitmapAnimNumberOfCycles));
	}



/**
 Sets the current animation's play mode.

@param aPlayMode The animation's play mode. 
*/
EXPORT_C void RBitmapAnim::SetPlayModeL(CBitmapAnimClientData::TPlayMode aPlayMode)
	{
	TPckgBuf<TBmpAnimAttributes> bitmapAnimPlayMode;
	bitmapAnimPlayMode().iPlayMode = aPlayMode;
	User::LeaveIfError(CommandReply(EBitmapAnimCommandSetPlayMode, bitmapAnimPlayMode));
	}



/**
 Sets the animation's position relative to the animation window.

@param aPosition The animation's position relative to the animation window 
*/
EXPORT_C void RBitmapAnim::SetPositionL(const TPoint aPosition)
	{
	TPckgBuf<SBitmapAnimNewPosition> bitmapAnimNewPosition;
	bitmapAnimNewPosition().iPosition = aPosition;
	User::LeaveIfError(CommandReply(EBitmapAnimCommandSetPosition, bitmapAnimNewPosition));
	}



/** 
 Starts the animation. 

You must first specify an animation with SetBitmapAnimDataL().

If you have specified CBitmapAnimClientData::ECycle or CBitmapAnimClientData::EBounce 
as the animation's play mode, but have not specified the number of cycles 
using SetNumberOfCyclesL(), you must call StopL() to stop the animation. 
*/
EXPORT_C void RBitmapAnim::StartL()
	{
	User::LeaveIfError(CommandReply(EBitmapAnimCommandStartAnimation));
	}



/** 
 Stops the animation. 
*/
EXPORT_C void RBitmapAnim::StopL()
	{
	User::LeaveIfError(CommandReply(EBitmapAnimCommandStopAnimation));
	}



/** 
 Sets the general attributes of the animation. 
*/
void RBitmapAnim::SetAttributesL(const CBitmapAnimClientData& aBitmapAnimData)
	{
	SetFlashL(aBitmapAnimData.Flash());
	SetFrameIntervalL(aBitmapAnimData.FrameIntervalInMilliSeconds());
	SetPlayModeL(aBitmapAnimData.PlayMode());
	}


/**
 Sets the animation frames to the player.
*/
void RBitmapAnim::SetFrameArrayL(const CArrayPtrFlat<CBitmapFrameData>& aFrameArray)
	{
	const TInt count = aFrameArray.Count();

	if (count > 0)
		{
		User::LeaveIfError(CommandReply(EBitmapAnimCommandResetFrameArray));
		CBitmapFrameData* frameData;
		User::LeaveIfError(CommandReply(EBitmapAnimCommandClearDataFrames));

		TInt index = 0;

		for (index = 0; index < count; index++)
			{
			frameData = aFrameArray.At(index);
			SetFrameL(*frameData, EBitmapAnimCommandSetDataFrame);
			}
		}
	}



/**
 Sets the background frame, aFrameData, to the player.
*/
void RBitmapAnim::SetBackgroundFrameL(const CBitmapFrameData& aFrameData)
	{
	SetFrameL(aFrameData, EBitmapAnimCommandSetBackgroundFrame);
	}


/**
 Extracts data from aFrameData, packs them and then it sends this package to the player
*/
void RBitmapAnim::SetFrameL(const CBitmapFrameData& aFrameData, TInt aOpCode)
	{
	TPckgBuf<TFrameData> dataFrameArg;
	CFbsBitmap* bitmap = aFrameData.Bitmap();
	dataFrameArg().iBitmapHandle=( (bitmap) ? bitmap->Handle() : 0 );
	CFbsBitmap* mask = aFrameData.Mask();
	dataFrameArg().iMaskBitmapHandle=( (mask) ? mask->Handle() : 0 );
	dataFrameArg().iIntervalInMilliSeconds=aFrameData.IntervalInMilliSeconds();
	dataFrameArg().iPosition=aFrameData.Position();
	User::LeaveIfError(CommandReply(aOpCode, dataFrameArg));
	}
