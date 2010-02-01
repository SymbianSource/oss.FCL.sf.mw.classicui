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

#include <gdi.h>
#include <fbs.h>

#include "BitmapAnimator.h"
#include "AnimationFrame.h"
#include "AnimationConfig.h"
#include "AnimationEvents.h"
#include "AnimationTicker.h"

/**
Two stage constructor.

Animators should not be constructed directly.  They are loaded as required
by the ECOM plugin framework, using this interface.

@see CAnimator
@param aRenderer A pointer to an MAnimationDrawer
@return The newly constructed animator
*/
CBitmapAnimator* CBitmapAnimator::NewL(TAny* aRenderer)
	{
	MAnimationDrawer* renderer = static_cast<MAnimationDrawer*>(aRenderer);
	CBitmapAnimator* self = new (ELeave) CBitmapAnimator(renderer);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	
	return self;
	}

/** Destructor.*/
CBitmapAnimator::~CBitmapAnimator()
	{
	Stop();
	iFrameArray.ResetAndDestroy();
	iFrameArray.Close();
	}

void CBitmapAnimator::Start(const TAnimationConfig& aConfig)
/**
Implements CAnimator::Start.

This function ignores the EStartImmediately flag in the config argument, and
always delays starting untill all frames of the animation have been loaded.
*/
	{
	Stop();
	
	if (aConfig.iFlags & TAnimationConfig::ECountFrames)
		iFlags |= ECountFrames;
	else
		iFlags &= ~ECountFrames;
		
	if (aConfig.iFlags & TAnimationConfig::EEndOnLastFrame)
		iFlags |= EEndOnLastFrame;
	else
		iFlags &= ~EEndOnLastFrame;
	
	if (aConfig.iFlags & TAnimationConfig::ELoop)
		iLoop = aConfig.iData;
	else
		iLoop = 1;
	
	iFlags &= ~ERunMask;

	if (iFrameArray.Count() > 0 && (iFlags & ECompleteData || aConfig.iFlags & TAnimationConfig::EStartImmediately))
		{
		iFlags |= ERunning;
		iTicksLeft = 0;
		// Add can fail, but if it does there isn't much we can do about it, we just won't animate.
		iRenderer->AnimatorTicker().Add(this);
		}
	else
		{
		iFlags |= EPending;
		}
	}
	
/** Implements CAnimator::Stop.*/
void CBitmapAnimator::Stop()
	{
	if (iFlags & ERunning)
		{
		if (!(iFlags & EPaused))
			iRenderer->AnimatorTicker().Remove(this);
		iFlags &= ~ERunMask;
		iNextFrame = 0;
		iCurrentFrame = 0;
		}
	}
	
/** Implements CAnimator::Pause.*/
void CBitmapAnimator::Pause()
	{
	if (iFlags & ERunning && !(iFlags & EPaused))
		{
		iFlags |= EPaused;
		iRenderer->AnimatorTicker().Remove(this);
		}
	}
	
/** Implements CAnimator::Resume.*/
void CBitmapAnimator::Resume()
	{
	if (iFlags & EPaused)
		{
		iFlags &= ~EPaused;
		// Add can fail, but if it does there isn't much we can do about it, we just won't animate.
		iRenderer->AnimatorTicker().Add(this);
		}
	}

/** Implements CAnimator::Hold.*/
void CBitmapAnimator::Hold()
	{
	if (!(iFlags & EHeld))
		{
		iFlags |= EHeld;
		}
	}

/** Implements CAnimator::Unhold.*/
void CBitmapAnimator::Unhold()
	{
	// It isn't possible to jump straight to the current frame, because it will depend on the ones
	// before.
	// It may be possible, some of the time, to use the frame we drew last to skip some of the while
	// loop - this is a possible optimization for the future.
	if (iFlags & EHeld)
		{
		iFlags &= ~EHeld;
		TInt oldCurrent = iCurrentFrame;
		iCurrentFrame = 0;
		iNextFrame = 0;
		while (iCurrentFrame < oldCurrent)
			{
			iRenderer->AnimatorDraw();
			iCurrentFrame = iNextFrame;
			iNextFrame = (iNextFrame + 1) % iFrameArray.Count();
			}
		}
	}

void CBitmapAnimator::InitialisedL()
	{
	iCurrentFrame = iNextFrame = 0;
	iFlags |= ECompleteData;
	iRenderer->AnimatorInitialisedL(iMaxSize);
	if (!(iFlags & EHeld))
		iRenderer->AnimatorDraw();
	if (iFlags & EPending)
		{
		iFlags |= ERunning;
		iFlags &= ~EPending;
		iTicksLeft = 0;
		// Add can fail, but if it does there isn't much we can do about it, we just won't animate.
		iRenderer->AnimatorTicker().Add(this);
		}
	}

void CBitmapAnimator::ResetL()
	{
	Stop();
	iFlags = 0;
	iMaxSize.iWidth = iMaxSize.iHeight = 0;
	iFrameArray.ResetAndDestroy();
	iRenderer->AnimatorResetL();
	}
	
/** Implements CAnimator::DataEventL.*/
void CBitmapAnimator::DataEventL(TInt aEvent, TAny* aData, TInt aDataLength)
	{
	switch (aEvent)
		{
		case EBitmapAnimationNewFrame:
			__ASSERT_ALWAYS(aDataLength==sizeof(CAnimationFrame::THandles),User::Leave(KErrArgument));
			AppendFrameL(*static_cast<CAnimationFrame::THandles*>(aData));
			break;
		case EBitmapAnimationComplete:
			InitialisedL();
			break;
		case EAnimationDataChanged:
			ResetL();
			break;
		default:
			break;
		}
	}
	
/** Implements CAnimator::Draw.*/
void CBitmapAnimator::Draw(CBitmapContext& aBitmapContext) const
	{
	const TUint32 frameFlags = iFrameArray[iCurrentFrame]->FrameInfo().iFlags;
	
	if (frameFlags&TFrameInfo::ERestoreToPrevious)
		RestoreToPrevious(aBitmapContext, EFalse);
	Render(aBitmapContext, iNextFrame);
	}

/** Implements CAnimator::DrawMask.*/
void CBitmapAnimator::DrawMask(CBitmapContext& aBitmapContext) const
	{
	const TUint32 frameFlags = iFrameArray[iCurrentFrame]->FrameInfo().iFlags;

	if (frameFlags&TFrameInfo::ERestoreToPrevious)
		RestoreToPrevious(aBitmapContext, ETrue);
	RenderMask(aBitmapContext, iNextFrame);
	}
	
void CBitmapAnimator::AppendFrameL(CAnimationFrame::THandles& aAnimationFrame)
	{
	CAnimationFrame* frame = CAnimationFrame::NewL(aAnimationFrame);
    CleanupStack::PushL(frame);
    iFrameArray.AppendL(frame);
    CleanupStack::Pop(frame);

    const TSize& size(frame->FrameInfo().iOverallSizeInPixels);
    if (size.iHeight > iMaxSize.iHeight)
        {
        iMaxSize.iHeight = size.iHeight;
        }
    if (size.iWidth > iMaxSize.iWidth)
        {
        iMaxSize.iWidth = size.iWidth;
        }
	}

CBitmapAnimator::CBitmapAnimator(MAnimationDrawer* aRenderer) :
iRenderer(aRenderer)
	{
	}
	
void CBitmapAnimator::ConstructL()
	{ // nothing to do
	}

void CBitmapAnimator::Tick()
	{
	--iTicksLeft;
	if (iTicksLeft < 1)
		{
		iTicksLeft = iFrameArray[iNextFrame]->FrameInfo().iDelay.Int64() / iRenderer->AnimatorTicker().TickLength().Int();
		DoUpdateFrame();
		}
	}

void CBitmapAnimator::DoUpdateFrame()
	{
	if (!((iLoop == 0 && iFlags & EEndOnLastFrame) || iFlags & EHeld))
		iRenderer->AnimatorDraw();

	if (iLoop != 0)
		{
		iCurrentFrame = iNextFrame;
		++iNextFrame;

		if (iLoop > 0 && iFlags & ECountFrames)
			--iLoop;
			
		if (iNextFrame >= iFrameArray.Count())
			{
			iNextFrame = 0;

			if (iLoop > 0 && !(iFlags & ECountFrames))
				--iLoop;
			}
		}
	else
		{
		Stop();
		}
	}

void CBitmapAnimator::Render(CBitmapContext& aBitmapContext, TInt aFrame) const
	{
	aBitmapContext.Reset();

	const CAnimationFrame& nextFrame = *iFrameArray[aFrame];
	const TBool useMask = nextFrame.FrameInfo().iFlags&TFrameInfo::ETransparencyPossible || nextFrame.FrameInfo().iFlags&TFrameInfo::EAlphaChannel;
	
	if (useMask)
		{
		aBitmapContext.BitBltMasked(nextFrame.FrameInfo().iFrameCoordsInPixels.iTl, nextFrame.Bitmap(), nextFrame.FrameInfo().iOverallSizeInPixels, nextFrame.Mask(), EFalse);
		}
	else
		{
		aBitmapContext.BitBlt(nextFrame.FrameInfo().iFrameCoordsInPixels.iTl, nextFrame.Bitmap(), nextFrame.FrameInfo().iOverallSizeInPixels);
		}
	}

void CBitmapAnimator::RenderMask(CBitmapContext& aBitmapContext, TInt aFrame) const
	{
	aBitmapContext.Reset();
	
	const CAnimationFrame& nextFrame = *iFrameArray[aFrame];

	if (aFrame == 0)
		{
		aBitmapContext.SetBrushColor(KRgbBlack);
		aBitmapContext.Clear(iMaxSize);		
		}
	else
		{
		const CAnimationFrame& currentFrame = *iFrameArray[aFrame - 1];
		if (currentFrame.FrameInfo().iFlags & TFrameInfo::ERestoreToBackground)
			{
			aBitmapContext.SetBrushColor(KRgbBlack);
			aBitmapContext.Clear(currentFrame.FrameInfo().iFrameCoordsInPixels);
			}
		}
	const TBool useMask = nextFrame.FrameInfo().iFlags&TFrameInfo::ETransparencyPossible || nextFrame.FrameInfo().iFlags&TFrameInfo::EAlphaChannel;
	if (useMask)
		{
		aBitmapContext.SetDrawMode(CGraphicsContext::EDrawModeOR);
		aBitmapContext.BitBlt(nextFrame.FrameInfo().iFrameCoordsInPixels.iTl, nextFrame.Mask(), nextFrame.FrameInfo().iOverallSizeInPixels);
		}
	else
		{
		aBitmapContext.SetBrushColor(KRgbWhite);
		if (nextFrame.FrameInfo().iOverallSizeInPixels != nextFrame.FrameInfo().iFrameSizeInPixels)
			{
			// If the frame size smaller than the overall size, the mask shall not take effect later in CBasicAnimation::Draw().
			aBitmapContext.Clear(nextFrame.FrameInfo().iOverallSizeInPixels);
			}
		else
			{
			aBitmapContext.Clear(nextFrame.FrameInfo().iFrameCoordsInPixels);
			}
		}
	}

void CBitmapAnimator::RestoreToPrevious(CBitmapContext& aBitmapContext, TBool aMask) const
	{
	TInt frame = 0;
	while (frame < iCurrentFrame)
		{
		if (!(iFrameArray[frame]->FrameInfo().iFlags&TFrameInfo::ERestoreToPrevious))
			{
			if (aMask)
				RenderMask(aBitmapContext, frame);
			else
				Render(aBitmapContext, frame);
			}
		++frame;
		}
	}
