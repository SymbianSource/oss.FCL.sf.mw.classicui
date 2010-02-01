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

#include "bmpansrv.h"


const TInt KAnimationGranularity = 5;

// times
const TInt KMilliToMicroSecondsFactor = 1000;


//
// CBitmapAnimFrameData
//

/** 
 Creates a new empty frame object.

@return A pointer to the new empty frame object.
*/
CBitmapAnimFrameData* CBitmapAnimFrameData::NewL()
	{
	CBitmapAnimFrameData* self = CBitmapAnimFrameData::NewLC();
	CleanupStack::Pop(self);
	return self;
	}

/** 
 Constructs a new bitmap animation frame data object,and puts a pointer to it onto the cleanup stack.

@return A pointer to the new empty frame data object or NULL if the disk is full.
*/
CBitmapAnimFrameData* CBitmapAnimFrameData::NewLC()
	{
	CBitmapAnimFrameData* self = new (ELeave) CBitmapAnimFrameData;
	CleanupStack::PushL(self);
	return self;
	}


/**
 Empty default constructor.
 */
CBitmapAnimFrameData::CBitmapAnimFrameData()
	{
	}

/**
 Frees resources owned by the object prior to deletion.
*/ 
CBitmapAnimFrameData::~CBitmapAnimFrameData()
 	{
	if( iBitmap && (iBitmap != iMaskBitmap) )
		{	
		delete iBitmap;
		}
		
	if( iMaskBitmap )
		{	
		delete iMaskBitmap;
		}
		
	}


/** 
 Initialization of CBitmapAnimFrameData data members to NULL.
*/
void CBitmapAnimFrameData::InitialiseMembers()
	{
	if( iBitmap && (iBitmap != iMaskBitmap) )
		{
		delete iBitmap;
		iBitmap = NULL;	
		}
		
	if( iMaskBitmap )
		{
		delete iMaskBitmap;
		iMaskBitmap = NULL;	
		iBitmap = NULL;
		}

	
	iPosition.SetXY( 0, 0 );
	iInterval = 0;	
	}
	

/** 
 Creates bitmaps if they are not created earlier.
*/
void CBitmapAnimFrameData::CheckAndCreateBitmapsL()
	{
	if (iBitmap == NULL)
		{
		iBitmap = new(ELeave) CFbsBitmap();
		}
	if (iMaskBitmap == NULL)
		{
		iMaskBitmap = new(ELeave) CFbsBitmap();
		}
	}


/**
 Un-packs the frame data arguments, aFrameDataArg, and uses this information to fill the frame
 data with two bitmaps, a position and a time interval.
*/
void CBitmapAnimFrameData::FillFrameDataL( const TFrameData& aFrameDataArg )
	{
// Create the icon by using the bitmap handles
	if ( aFrameDataArg.iBitmapHandle )	// Null member of sequence, time is only valid field in member data
		{
		iBitmap = new(ELeave) CFbsBitmap();
		User::LeaveIfError(iBitmap->Duplicate(aFrameDataArg.iBitmapHandle));
		if (aFrameDataArg.iMaskBitmapHandle)
			{
			iMaskBitmap = new(ELeave) CFbsBitmap();
			User::LeaveIfError(iMaskBitmap->Duplicate(aFrameDataArg.iMaskBitmapHandle));
			}
					
		iPosition = aFrameDataArg.iPosition;
		iInterval = (TTimeIntervalMicroSeconds32) ( aFrameDataArg.iIntervalInMilliSeconds * KMilliToMicroSecondsFactor );
		}
	else
		{
		InitialiseMembers();
		}

	}



/**
 class CBitmapAnim
*/

/**
 Constructs a new bitmap animation object.
*/
CBitmapAnim::CBitmapAnim() :
	iBitmapAnimFrameDataArray(KAnimationGranularity),
	iFlags(ENoBitmapWindowRestoring),
	iIndex(-1),
	iNumberOfCycles(-1),
	iPosition(0,0)
	{
	}



/**
 Frees resources owned by the object prior to deletion.
*/
CBitmapAnim::~CBitmapAnim()
	{
	StopAnimation();
	delete iAnimTimer;
	delete iFlashTimer;
	iBitmapAnimFrameDataArray.ResetAndDestroy();
	iBitmapAnimFrameDataArray.Close();
	delete iBackgroundFrame;
	}



/**
 Creates a new empty bitmap animation object.

@return A pointer to the new empty bitmap animation object.
*/
CBitmapAnim* CBitmapAnim::NewL()
	{
	CBitmapAnim* self = new (ELeave) CBitmapAnim();
	return self;
	}



/**
 Pure virtual function from CAnim it creates the animation timer object.
*/
void CBitmapAnim::ConstructL(TAny* /*aArgs*/, TBool /*aHasFocus*/)
	{
	iAnimTimer = CBitmapAnimTimer::NewL(this);
	}

void CBitmapAnim::Animate(TDateTime* /*aDateTime*/)
	{
	}



/**
 Stops animation and resets animation frame data array.
*/
void CBitmapAnim::ResetFrameArray()
	{
	StopAnimation();
	iBitmapAnimFrameDataArray.ResetAndDestroy();
	}


/**
 Appends a new frame, aFrame, to the frame array.
*/
void CBitmapAnim::AppendFrameL(const TFrameData& aFrameDataArg)
	{
	CBitmapAnimFrameData* dataFrame = CBitmapAnimFrameData::NewLC();
	dataFrame->FillFrameDataL(aFrameDataArg);
	User::LeaveIfError(iBitmapAnimFrameDataArray.Append(dataFrame));
	CleanupStack::Pop(dataFrame);
	}


/**
 Pure virtual function from CAnim.
*/
void CBitmapAnim::Command(TInt aOpcode, TAny* aArgs)
	{
	switch (aOpcode)
		{
	case EBitmapAnimCommandClearDataFrames:
  		ClearFrameData();
  		break;
	case EBitmapAnimCommandSetFlash:
		SetFlash(*(TBmpAnimAttributes*)aArgs);
		break;
	case EBitmapAnimCommandSetFrameIndex:
		SetIndexFrame(*(SBitmapAnimIndexFrame*)aArgs);
		break;
	case EBitmapAnimCommandSetFrameInterval:
		SetFrameInterval(*(TBmpAnimAttributes*)aArgs);
		break;
	case EBitmapAnimCommandSetNumberOfCycles:
		SetNumberOfCycles(*(SBitmapAnimNumberOfCycles*)aArgs);
		break;
	case EBitmapAnimCommandSetPlayMode:
		SetPlayMode(*(TBmpAnimAttributes*)aArgs);
		break;
	case EBitmapAnimCommandSetPosition:
		SetPosition(*(SBitmapAnimNewPosition*)aArgs);
		break;
		}
	}



/**
 Pure virtual function from CAnim it handles the command received by the relative client.
 aOpcode determines the action that has to be taken while aArgs contains the information
 packed by the client. It returns KErrNone if no problem has occurred.
*/
TInt CBitmapAnim::CommandReplyL(TInt aOpcode, TAny* aArgs)
	{
	TInt error = KErrNone;
	switch (aOpcode)
		{
	case EBitmapAnimCommandClearDataFrames:
  	    ClearFrameData();
  	    break;
	case EBitmapAnimCommandStartAnimation:
		StartAnimationL();
		break;
	case EBitmapAnimCommandStopAnimation:
		StopAnimation();
		break;
	case EBitmapAnimCommandSetBackgroundFrame:
		SetBackgroundFrameL(*(TFrameData*)aArgs);
		break;
	case EBitmapAnimCommandSetDataFrame:
		AppendFrameL(*(TFrameData*)aArgs);
		break;
	case EBitmapAnimCommandSetFlash:
		SetFlash(*(TBmpAnimAttributes*)aArgs);
		break;
	case EBitmapAnimCommandSetFrameIndex:
		error = SetIndexFrame(*(SBitmapAnimIndexFrame*)aArgs);
		break;
	case EBitmapAnimCommandSetFrameInterval:
		SetFrameInterval(*(TBmpAnimAttributes*)aArgs);
		break;
	case EBitmapAnimCommandSetNumberOfCycles:
		SetNumberOfCycles(*(SBitmapAnimNumberOfCycles*)aArgs);
		break;
	case EBitmapAnimCommandSetPlayMode:
		SetPlayMode(*(TBmpAnimAttributes*)aArgs);
		break;
	case EBitmapAnimCommandSetPosition:
		SetPosition(*(SBitmapAnimNewPosition*)aArgs);
		break;
	case EBitmapAnimCommandStartAnimationAndKeepLastFrame:
		iFlags |= EDisplayLastFrameWhenFinished;
		StartAnimationL();
		break;
	case EBitmapAnimCommandResetFrameArray:
		ResetFrameArray();
		break;
	default:
		error = KErrNotSupported;
		}
	return error;
	}
	


/**
 Clears Frame data by stopping animation and resetting frame data array.
*/
void CBitmapAnim::ClearFrameData()
 	{
 	StopAnimation();
 	iBitmapAnimFrameDataArray.ResetAndDestroy();
 	iIndex = -1;
 	}



/**
 Pure virtual function from MAnimationTimer it is used to draw the next frame. It first updates
 the index frame, checks if the frame is displayable and if so it draws the frame otherwise it
 stops the animation.
*/
void CBitmapAnim::DisplayNextFrameL()
	{
	if (!IsRunning())
		{
		return;
		}

	const TInt previousIndex = iIndex;
	UpdateCurrentIndex();

	if (IsFrameDisplayable())
		{
		if (!IsFrozen())
			{
			DisplayFrame(previousIndex);
			}
		}
	else
		{
		iIndex = previousIndex;
		StopAnimation();
		}
	}

/**
 Draws the current frame in a particular position.
 */
void CBitmapAnim::DrawBitmap(TInt /*aPreviousIndex*/, TBool aRedraw)
	{
	__ASSERT_ALWAYS((iIndex>=0 && iIndex < Count()), Panic(EAnimationServerPanicIndexOutOfRange));
	CBitmapAnimFrameData* frameData = iBitmapAnimFrameDataArray[iIndex];

	if (frameData->iBitmap)
		{
		if (!aRedraw)
			{
			iWindowFunctions->ActivateGc();
			}

		const TPoint framePosition = frameData->iPosition + iPosition;

		RenderFrameBackground(iIndex);

		if (frameData->iMaskBitmap)
			{
			iGc->BitBltMasked(framePosition, frameData->iBitmap, frameData->iBitmap->SizeInPixels(), frameData->iMaskBitmap, ETrue);
			}
		else
			{
			iGc->BitBlt(framePosition, frameData->iBitmap);
			}

		MAnimFreeTimerWindowFunctions* windowFunctions = WindowFunctions();

		if (!aRedraw)
			{
			windowFunctions->DeactivateGc();
			}

		windowFunctions->Update();
		}
	}

/**
 Sets the next call-back of the timer and draws the new frame.
 */
void CBitmapAnim::DisplayFrame(TInt aPreviousIndex)
	{
	TTimeIntervalMicroSeconds32 time = iBitmapAnimFrameDataArray[iIndex]->iInterval;
	if (time.Int() < 0)
		{
		time = iFrameInterval;
		}

    // Limits frame interval time
    const TTimeIntervalMicroSeconds32 KAnimationMinimumFrameInterval = 30 * KMilliToMicroSecondsFactor;

	__ASSERT_DEBUG(time >= KAnimationMinimumFrameInterval, RDebug::Print(_L("CBitmapAnim: frame interval was %d reset to %d."), time.Int(), KAnimationMinimumFrameInterval.Int()));
	time = Max(time, KAnimationMinimumFrameInterval);
	iAnimTimer->Cancel();
	iAnimTimer->After(time);

	DrawBitmap(aPreviousIndex);
	}



/**
 Flashes and draws the current frame.

@param aFlash ETrue for the animation to flash, otherwise EFalse.
*/
void CBitmapAnim::FlashFrame(TBool aFlash)
	{
	const TTimeIntervalMicroSeconds32 KFlashInterval = 1000;
	
	if (aFlash)
		{
		iFlags |= EFlashing;
		}
	else
		{
		iFlags &= ~EFlashing;
		}

	iFlashTimer->After(KFlashInterval);

	DrawBitmap();
	}



/**
 Notifies change of focus.
Overridden from virtual method CWindowAnim::FocusChanged(TBool aState).
    
@param aState Indicates whether the focus has or has not changed.
@see CWindowAnim::FocusChanged(TBool aState)
*/
void CBitmapAnim::FocusChanged(TBool aState)
	{
	if (aState)
		{
		iFlags &= ~EFrozen;
		if (IsRunning())
			{
			TRAP_IGNORE(DisplayNextFrameL());
			}
		}
	else
		{
		iFlags |= EFrozen;
		}
	}



/** Handles raw events.
Overridden from virtual method MEventHandler::OfferRawEvent().
This function does not handle the incoming events.

@param aRawEvent The raw event to be processed
@return ETrue if the raw event is handled by this function, EFalse if the function
chooses not to process it.
@see MEventHandler
*/
TBool CBitmapAnim::OfferRawEvent(const TRawEvent& /*aRawEvent*/)
	{
	return EFalse;
	}



/**
 Redraws the current animation frame and the background bitmap.
Overridden from virtual method CWindowAnim::Redraw().

@see CWindowAnim
*/
void CBitmapAnim::Redraw()
	{
	TWindowInfo parameter;
	WindowFunctions()->Parameters(parameter);
	const TRegion* redrawRegion;
	const TRegion* redrawShadowRegion;
	parameter.GetRedrawRegionAndRedrawShadowRegion(redrawRegion, redrawShadowRegion);

	// redraw the current animation frame if needed
	if (IsFrameDisplayable())
		{
		// redraw frame unless we're absolutely sure it doesn't need doing
		TRect currentFrameScreenRect = CalcFrameRect(iIndex);
		currentFrameScreenRect.Move(parameter.iScreenPos.iTl);
		if (FrameNeedsRedrawing(redrawRegion, currentFrameScreenRect) || FrameNeedsRedrawing(redrawShadowRegion, currentFrameScreenRect))
			{
			DrawBitmap(-1, ETrue);
			}
		}
	}


/**
 Resets the animation to be in a valid state every time a stop request occurs.
*/
void CBitmapAnim::ResetAnimation()
	{
	iIndex = -1;
	iNumberOfCycles = -1;
	iFlags &= ~(ERunning|EPlayForwards|EPlayBackwards);
	iFlags |= ENoBitmapWindowRestoring;
	}


/**
 Sets the background frame by using the information from aFrameDataArg. This will overwrite the
 existing background frame.
*/
void CBitmapAnim::SetBackgroundFrameL(TFrameData aFrameDataArg)
	{
	if (iBackgroundFrame)
		{
		delete iBackgroundFrame;
		iBackgroundFrame = NULL;
		}

	iBackgroundFrame = CBitmapAnimFrameData::NewL();
	iBackgroundFrame->FillFrameDataL(aFrameDataArg);
	iBackgroundFrame->CheckAndCreateBitmapsL();
	}



/**
 Sets and un-sets the flash flag according to aFlash value. It can be called at any time after
 the animation has been set, and it has an immediate effect.
*/
void CBitmapAnim::SetFlash(TBmpAnimAttributes aFlash)
	{
	if (aFlash.iFlash)
		{
		iFlags |= EFlash;
		}
	else
		{
		iFlags &= ~EFlash;
		}
	}



/**
 Sets the frame interval of the animation to aFrameInterval. It has an immediate effect.
*/
void CBitmapAnim::SetFrameInterval(TBmpAnimAttributes aFrameInterval)
	{
	__ASSERT_ALWAYS(aFrameInterval.iFrameIntervalInMilliSeconds >= 0, Panic(EAnimationServerPanicFrameIntervalNegative));
	iFrameInterval = (aFrameInterval.iFrameIntervalInMilliSeconds * KMilliToMicroSecondsFactor);
	}



/**
 Changes the index frame of the animation to be aIndexFrame and it has an immediate effect.
*/
TInt CBitmapAnim::SetIndexFrame(SBitmapAnimIndexFrame aIndexFrame)
	{
	TInt error = KErrNone;
	TInt backupFlags = iFlags;
	TInt oldNumberOfCycles = iNumberOfCycles;
	StopAnimation();
	iIndex = aIndexFrame.iIndex;
// Restore previous state.
	iNumberOfCycles = oldNumberOfCycles;
	iFlags = backupFlags;

	if (IsFrameDisplayable())
		{
		DisplayFrame();
		iFlags &= ~ENoBitmapWindowRestoring;
		}
	else
		{
		error = KErrOverflow;
		}
	return error;
	}


/**
 Sets the number of times that all the frames have to be displayed. It has an immediate effect.
*/
void CBitmapAnim::SetNumberOfCycles(SBitmapAnimNumberOfCycles aNumberOfCycles)
	{
	TInt value = aNumberOfCycles.iCycles;

	if (value == 0)
		{
		value = 1;
		}

	iNumberOfCycles = value;
	}



/**
 Sets the play mode of the animation to aPlayMode. It has an immediate effect.
*/
void CBitmapAnim::SetPlayMode(TBmpAnimAttributes aPlayMode)
	{
	
	TBool isRunning = IsRunning();
	
	if( isRunning  )
		{
		StopAnimation();
		}
	
	// EPlay = xx0x
	iFlags &= ~( EPlayModeBounce | EPlayModeCycle );
		
	CBitmapAnimClientData::TPlayMode mode = aPlayMode.iPlayMode;
	
	switch (mode)
		{
	case CBitmapAnimClientData::EPlay:
		break;
		
	case CBitmapAnimClientData::ECycle:
		iFlags |= EPlayModeCycle;
		break;
		
	case CBitmapAnimClientData::EBounce:
		iFlags |= EPlayModeBounce;
		break;
		
	default:
		break;
		}
	
	
	if( isRunning )
		{
		TRAP_IGNORE( StartAnimationL() );	
		}
		
	}



/**
 Sets the position of the animation control to aNewPosition.
 aNewPosition is relative to the origin of the control's window
*/
void CBitmapAnim::SetPosition(SBitmapAnimNewPosition aNewPosition)
	{
	ClearFrameNow(iIndex);
	iPosition.iX = aNewPosition.iPosition.iX;
	iPosition.iY = aNewPosition.iPosition.iY;
	if (IsRunning())
		{
		DrawBitmap();
		}
	}



/**
 Starts the animation routine.
*/
void CBitmapAnim::StartAnimationL()
	{
	if (iFunctions->WindowExtension())
		{
		TWindowConfig windowConfig;
		iFunctions->WindowExtension()->WindowConfig(windowConfig);
		iWindowConfig = windowConfig.iFlags;
		}
	if (!IsRunning() && (Count() > 0) )
		{
		iFlags |= EPlayForwards;
		iFlags |= ERunning;
		DisplayNextFrameL();
		iFlags &= ~ENoBitmapWindowRestoring;
		}
	}



/**
 Stops the animation by removing the last frame from the window and replacing the old contents.
*/
void CBitmapAnim::StopAnimation()
	{
	if (IsRunning())
		{
		if (!(iFlags & EDisplayLastFrameWhenFinished))
			{
			ClearFrameNow(iIndex);
			}

		ResetAnimation();
		}
	if (iAnimTimer && iAnimTimer->IsActive())
		{
		iAnimTimer->Cancel();
		}
	}



/**
 Calculates and finds frame's rectangle, relative to animation position.

@param aIndex index value of the frame in frame data array.
@return frame's rectangle.
*/
TRect CBitmapAnim::CalcFrameRect( TInt aIndex )
	{
	TRect rect;
	
	CBitmapAnimFrameData* frameData = iBitmapAnimFrameDataArray[aIndex];
	
	if ( (aIndex >= 0) && frameData && frameData->iBitmap )
		{
		TSize frameSize = frameData->iBitmap->SizeInPixels();
		TPoint framePosition = frameData->iPosition;
		framePosition += iPosition;
		rect.SetRect(framePosition, frameSize);
		}
		
		
	return rect;
	}

/**
Renders the background associated with the specified frame index.

@param aIndex Index of frame to render background for.
*/
void CBitmapAnim::RenderFrameBackground(TInt aIndex)
	{
	if ((aIndex >= 0) && !(iFlags&ENoBitmapWindowRestoring) && iBackgroundFrame && iBackgroundFrame->iBitmap)
		{	
		TRect frameRectOnWindow = CalcFrameRect(aIndex);
		TPoint framePosition = frameRectOnWindow.iTl;
		frameRectOnWindow.Move(-iPosition);
		iGc->BitBlt(framePosition, iBackgroundFrame->iBitmap, frameRectOnWindow);
		}
	}

/**
 Clears the frame by calling ClearFrame function.
 Uses CFreeTimerWindowAnim timer functions which supports animations with their own timers.

@param aIndex index value of the frame in frame data array.
@see CFreeTimerWindowAnim
*/
void CBitmapAnim::ClearFrameNow(TInt /*aIndex*/)
	{
	iWindowFunctions->ActivateGc();
	MAnimFreeTimerWindowFunctions* windowFunctions = WindowFunctions();
	windowFunctions->DeactivateGc();
	windowFunctions->Update();
	}

/**
 Updates the index indicating which frame should be displayed. The index value will be set
 to -1 when the animation routine is completed.
*/
void CBitmapAnim::UpdateCurrentIndex()
	{
	const TInt lastIndexFrame = iBitmapAnimFrameDataArray.Count() - 1;
	if (iIndex == lastIndexFrame)
		{
		if (--iNumberOfCycles == 0)
			{
			iIndex = -1;
			return;
			}
			
			
		if (iFlags&EPlayModeBounce)
			{
			iIndex--;
			
			if (iIndex < 0)
				{
				iIndex = 0;
				}
			
			iFlags &= ~EPlayForwards;
			iFlags |= EPlayBackwards;
			}
		else if (iFlags&EPlayModeCycle)
			{
			iIndex = 0;
			}
		else
			{
			iIndex = -1;
			}
		}
	else if (iIndex == 0)
		{
		if (iFlags&EPlayModeBounce)
			{
			if (--iNumberOfCycles == 0)
				{
				iIndex = -1;
				return;
				}
				
			iIndex ++;
			iFlags &= ~EPlayBackwards;
			iFlags |= EPlayForwards;
			}
		else if (iFlags&EPlayForwards)
			{
			iIndex ++;
			}
		else
			{
			iIndex = -1;
			}
		}
	else
		if (iFlags&EPlayForwards)
			{
			iIndex++;
			}
		else
			{
			iIndex--;
			}
	}

/**
 returns true if there is any chance the frame needs to be redrawn, false otherwise
*/
TBool CBitmapAnim::FrameNeedsRedrawing(const TRegion* aRedrawRegion, TRect aFrameScreenRect)
	{
	// if the region is NULL, empty or doesn't intersect the frame rect,
	// assume we don't need to redraw the frame
	TBool ret = aRedrawRegion!=NULL;
	if (aRedrawRegion)
		{
		if (!aRedrawRegion->CheckError())
			{
			if (aRedrawRegion->IsEmpty())
				{
				ret = EFalse;
				}
			else
				{
				RRegionBuf<10> frameRegion;
				frameRegion.Copy(*aRedrawRegion);
				frameRegion.ClipRect(aFrameScreenRect);
				if (frameRegion.IsEmpty()) // TRegion::IsEmpty only returns true if the region contains no error
					{
					ret = EFalse;
					}
				frameRegion.Close();
				}
			}
		}
	return ret;
	}



//
// CBitmapAnimTimer class
//

/**
 Constructs a new bitmap animation timer object,and adds the specified active object to the current active scheduler.

@param aObserver a pointer to MBitmapAnimTimerObserver
*/
CBitmapAnimTimer::CBitmapAnimTimer(MBitmapAnimTimerObserver* aObserver)
	:CTimer(EPriorityStandard),
	iAnimate(aObserver)
	{
	CActiveScheduler::Add(this);
	}



/**
 Frees resources owned by the object prior to deletion.
*/ 
CBitmapAnimTimer::~CBitmapAnimTimer()
	{
	}



/**
 Creates a new bitmap animation timer object.

@param aObserver A pointer to the MBitmapAnimTimerObserver
@return A pointer to the new bitmap animation timer object.
*/
CBitmapAnimTimer* CBitmapAnimTimer::NewL(MBitmapAnimTimerObserver* aObserver)
	{
	CBitmapAnimTimer* timer=new(ELeave) CBitmapAnimTimer(aObserver);
	CleanupStack::PushL(timer);
	timer->ConstructL();
	CleanupStack::Pop();
	return timer;
	}



/**
 Completes construction of the bitmap animation timer object and
 constructs a new asynchronous timer.
*/
void CBitmapAnimTimer::ConstructL()
	{
	CTimer::ConstructL();
	}



/**
 Handles an active object's request completion event.
 Invokes the function to draw the next frame
*/
void CBitmapAnimTimer::RunL()
	{
	iAnimate->DisplayNextFrameL();
	}



//
// CBitmapAnimFlashTimer class
//

/**
 Constructs a new bitmap animation flash timer object,and adds the specified active object to the current active scheduler.

@param aObserver a pointer to MBitmapAnimFlashTimerObserver
*/
CBitmapAnimFlashTimer::CBitmapAnimFlashTimer(MBitmapAnimFlashTimerObserver* aObserver)
	:CTimer(EPriorityStandard),
	iAnimate(aObserver),
	iFlash(EFalse)
	{
	CActiveScheduler::Add(this);
	}



/**
 Frees resources owned by the object prior to deletion.
*/
CBitmapAnimFlashTimer::~CBitmapAnimFlashTimer()
	{
	}



/**
 Creates a new bitmap animation flash timer object.

@param aObserver A pointer to the MBitmapAnimFlashTimerObserver
@return A pointer to the new bitmap animation flash timer object.
*/
CBitmapAnimFlashTimer* CBitmapAnimFlashTimer::NewL(MBitmapAnimFlashTimerObserver* aObserver)
	{
	CBitmapAnimFlashTimer* timer=new(ELeave) CBitmapAnimFlashTimer(aObserver);
	CleanupStack::PushL(timer);
	timer->ConstructL();
	CleanupStack::Pop();
	return timer;
	}



/**
 Completes construction of the CBitmapAnimFlashTimer object and
 constructs a new asynchronous timer.
*/
void CBitmapAnimFlashTimer::ConstructL()
	{
	CTimer::ConstructL();
	}



void CBitmapAnimFlashTimer::DoCancel()
	{
	}



/**
 Handles an active object's request completion event.
 Invokes the function to flash the animation frame and draw the bitmap.
*/
void CBitmapAnimFlashTimer::RunL()
	{
	iFlash = ~iFlash;
	iAnimate->FlashFrame(iFlash);
	}

