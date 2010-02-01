/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Anim Data
*
*/

// AknAnimData.CPP
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Animation Data class


#include "aknanimdata.h"
#include "aknanim.hrh"
#include "AknPanic.h"
#include <barsread.h>
#include <eikenv.h>


const TInt KAnimStepGranularity=5;



EXPORT_C CAknAnimationData::CAknAnimationData()
:CArrayFixFlat<TAnimStep>(KAnimStepGranularity)
	{
	}

EXPORT_C CAknAnimationData::~CAknAnimationData()
	{
	delete iDrawStepsPerAnimStep;
	delete iPendingSteps;
	}


EXPORT_C void CAknAnimationData::ConstructL()
	{
	if (!iPendingSteps)
		{
		iPendingSteps = new(ELeave)CArrayFixFlat<TAnimMultiStep>(KAnimStepGranularity);
		}
	if (!iDrawStepsPerAnimStep)
		{
		iDrawStepsPerAnimStep = new(ELeave)CArrayFixFlat<TUint8>(KAnimStepGranularity);
		}
	}


EXPORT_C void CAknAnimationData::ConstructFromResourceL(TInt aResourceId)
	{
	ConstructL();
	TResourceReader reader;	
	CEikonEnv::Static()->CreateResourceReaderLC(reader, aResourceId);

	iFlags = (TUint16)reader.ReadInt16();
	iInterval = reader.ReadInt32();
	TInt sections = reader.ReadInt16();
	TResourceReader sectionReader;
	for (TInt sectionCount=0; sectionCount<sections; sectionCount++)
		{
		CEikonEnv::Static()->CreateResourceReaderLC(sectionReader, reader.ReadInt32());		
		TInt animSteps = sectionReader.ReadInt16();
		for (TInt stepCount=0; stepCount<animSteps; stepCount++)
			{
			ReadAnimStepL(sectionReader);
			}
		CleanupStack::PopAndDestroy();	//sectionReader
		if (WaitBetweenSections())
			{
			// Append a wait step between each loaded section
			TAnimStep drawStep;
			drawStep.SetType(EAnimWaitUntilComplete);
			AppendL(drawStep);
			iDrawStepsPerAnimStep->AppendL(1);
			}
		}
	if (WaitForeverAtEnd())
		{
		// Append a wait-forever step at end of animation
		// (Wait-forever is set by a wait step with zero steps)
		TAnimStep drawStep;
		drawStep.SetType(EAnimWait);
		(drawStep.WaitStep())->iSteps = 0;
		AppendL(drawStep);
		iDrawStepsPerAnimStep->AppendL(1);
		}

	CleanupStack::PopAndDestroy();	//reader
	}

void CAknAnimationData::ReadAnimStepL(TResourceReader& aReader)
	{
	TInt drawSteps = aReader.ReadInt16();
	iDrawStepsPerAnimStep->AppendL((TUint8)drawSteps);
	for (TInt stepCount=0; stepCount<drawSteps; stepCount++)
		{
		TAnimStep drawStep;
		TUint8 type = (TUint8)aReader.ReadInt8();
		drawStep.SetType(type);
		switch(type)
			{
			case EAnimBlitPreviousView:
			case EAnimBlitNewView:
				{
				TAnimBlitStep* step = drawStep.BlitStep();
				step->iDestX = (TInt16)aReader.ReadInt16();
				step->iDestY = (TInt16)aReader.ReadInt16();
				}
				break;
			case EAnimBlitPartPreviousView:
				{
				TAnimBlitStep* step = drawStep.BlitStep();
				step->iSrcX = (TInt16)aReader.ReadInt16();
				step->iSrcY = (TInt16)aReader.ReadInt16();
				step->iWidth = (TUint16)aReader.ReadInt16();
				step->iHeight = (TUint16)aReader.ReadInt16();
				step->iDestX = (TInt16)aReader.ReadInt16();
				step->iDestY = (TInt16)aReader.ReadInt16();
				}
			case EAnimBlitPartNewView:
			case EAnimRevealPartNewViewFromLeft:
			case EAnimRevealPartNewViewFromRight:
			case EAnimRevealPartNewViewFromTop:
			case EAnimRevealPartNewViewFromBottom:
				{
				TAnimBlitStep* step = drawStep.BlitStep();
				step->iSteps = (TUint16)aReader.ReadInt16();
				step->iSrcX = (TInt16)aReader.ReadInt16();
				step->iSrcY = (TInt16)aReader.ReadInt16();
				step->iWidth = (TUint16)aReader.ReadInt16();
				step->iHeight = (TUint16)aReader.ReadInt16();
				step->iDestX = (TInt16)aReader.ReadInt16();
				step->iDestY = (TInt16)aReader.ReadInt16();
				if (step->iDestX == -32760) step->iDestX = step->iSrcX;
				if (step->iDestY == -32760) step->iDestY = step->iSrcY;
				}
				break;
			case EAnimBlitSlideNewView:
			case EAnimBlitSlideNewViewClearBehind:
				{
				TAnimSlideStep* step = drawStep.SlideStep();
				step->iSteps = (TUint16)aReader.ReadInt16();
				step->iSrcX = (TInt16)aReader.ReadInt16();
				step->iSrcY = (TInt16)aReader.ReadInt16();
				step->iWidth = (TUint16)aReader.ReadInt16();
				step->iHeight = (TUint16)aReader.ReadInt16();
				step->iSlideToX = (TInt16)aReader.ReadInt16();
				step->iSlideToY = (TInt16)aReader.ReadInt16();
				step->iSlideFromX = (TInt16)aReader.ReadInt16();
				step->iSlideFromY = (TInt16)aReader.ReadInt16();
				}
				break;
			case EAnimWait:
				{
				TAnimWaitStep* step = drawStep.WaitStep();
				step->iSteps = (TUint16)aReader.ReadInt16();
				}
				break;
			case EAnimSetColor:
				{
				TAnimSetColorStep* step = drawStep.SetColorStep();
				step->iRed = (TUint8)aReader.ReadUint8();
				step->iGreen = (TUint8)aReader.ReadUint8();
				step->iBlue = (TUint8)aReader.ReadUint8();
				}
				break;
			case EAnimDrawLine:
			case EAnimDrawRect:
			case EAnimDrawFilledRect:
				{
				TAnimLineDrawStep* step = drawStep.LineDrawStep();
				step->iSteps = (TUint16)aReader.ReadInt16();
				step->iStartX = (TInt16)aReader.ReadInt16();
				step->iStartY = (TInt16)aReader.ReadInt16();
				step->iEndX = (TInt16)aReader.ReadInt16();
				step->iEndY = (TInt16)aReader.ReadInt16();
				}
				break;
			case EAnimWaitUntilComplete:
				// No parameters to be read
				break;
			default:
				ConstructUserAnimationStepL(drawStep, aReader);
				break;
			}
		AppendL(drawStep);
		}
	}

EXPORT_C void CAknAnimationData::ConstructUserAnimationStepL(TAnimStep& /*aAnimStep*/, TResourceReader& /*aReader*/)
	{
	Panic(EAknPanicUnknownAnimationType);
	}



EXPORT_C TBool CAknAnimationData::DrawUserAnimationStep(CBitmapContext& /*aGc*/, TAnimMultiStep& /*aAnimStep*/)
	{
	Panic(EAknPanicNoUserAnimation);
	return ETrue;
	}


EXPORT_C void CAknAnimationData::SetScreenSize(TSize aSize)
	{
	iScreenSize = aSize;
	}

EXPORT_C void CAknAnimationData::SetViewBitmap(CFbsBitmap* aViewBitmap)
	{
	iViewBitmap = aViewBitmap;
	}

EXPORT_C void CAknAnimationData::SetOldBitmap(CFbsBitmap* aOldBitmap)
	{
	iOldBitmap = aOldBitmap;
	}


EXPORT_C void CAknAnimationData::SetClearOldView()
	{
	iFlags |= EAnimClearScreen;
	}

EXPORT_C TBool CAknAnimationData::ClearOldView()
	{
	return iFlags & EAnimClearScreen;
	}

EXPORT_C TBool CAknAnimationData::WaitBetweenSections()
	{
	return iFlags & EAnimWaitBetweenSections;
	}


EXPORT_C void CAknAnimationData::SetWaitForeverAtEnd()
	{
	iFlags |= EAnimClearScreen;	
	}

EXPORT_C TBool CAknAnimationData::WaitForeverAtEnd()
	{
	return iFlags & EAnimWaitForeverAtEnd;
	}

EXPORT_C TInt CAknAnimationData::Interval()
	{
	return iInterval;
	}

EXPORT_C TBool CAknAnimationData::DrawNextAnimationStep(CBitmapContext& aGc)
	{
	if (Count() == 0)
		{
		// Call the user animation step
		TAnimStep step;
		TAnimMultiStep nullStep(step);
		nullStep.iDrawStep.SetType(EAnimNullStep);
		nullStep.iSubStep = (TUint16)iCurrentDrawStep;
		TBool done = DrawUserAnimationStep(aGc, nullStep);
		iCurrentDrawStep++;
		return done;
		}

	if (iCurrentDrawStep < Count())
		{
		TInt drawSteps = (*iDrawStepsPerAnimStep)[iCurrentAnimStep];
		TInt startingDrawStep = iCurrentDrawStep;
		TBool repeatAnimStep = EFalse;

		for (TInt ii=0; ii<drawSteps; ii++)
			{
			TAnimStep* drawStep = &(At(iCurrentDrawStep));

			switch (drawStep->Type())
				{
				case EAnimBlitPreviousView:
					{
					TAnimBlitStep* step = drawStep->BlitStep();
					aGc.BitBlt(TPoint(step->iDestX, step->iDestY), iOldBitmap);
					}
					break;
				case EAnimBlitNewView:
					{
					TAnimBlitStep* step = drawStep->BlitStep();
					aGc.BitBlt(TPoint(step->iDestX, step->iDestY), iViewBitmap);
					}
					break;
				case EAnimBlitPartPreviousView:
					{
					TAnimBlitStep* step = drawStep->BlitStep();
					aGc.BitBlt(TPoint(step->iDestX, step->iDestY), iOldBitmap,
					TRect(TPoint(step->iSrcX, step->iSrcY), TSize(step->iWidth, step->iHeight)));
					}
					break;
				case EAnimBlitPartNewView:
					{
					TAnimBlitStep* step = drawStep->BlitStep();
					aGc.BitBlt(TPoint(step->iDestX, step->iDestY), iViewBitmap,
						TRect(TPoint(step->iSrcX, step->iSrcY), TSize(step->iWidth, step->iHeight)));
					}
					break;
				case EAnimDrawLine:
				case EAnimRevealPartNewViewFromLeft:
				case EAnimRevealPartNewViewFromRight:
				case EAnimRevealPartNewViewFromTop:
				case EAnimRevealPartNewViewFromBottom:
				case EAnimBlitSlideNewView:
				case EAnimBlitSlideNewViewClearBehind:
						{
					// Make this a pending step. Cancel the animation if the append fails
					TRAPD(err, iPendingSteps->AppendL(TAnimMultiStep(*drawStep)));
					if (err != KErrNone)
						return ETrue;
					}
					break;
				case EAnimSetColor:
					{
					TAnimSetColorStep* step = drawStep->SetColorStep();
					iDrawColor = TRgb(step->iRed, step->iGreen, step->iBlue);
					}
					break;
				case EAnimDrawRect:
					{
					TAnimLineDrawStep* step = drawStep->LineDrawStep();
					aGc.SetPenColor(iDrawColor);
					aGc.SetPenStyle(CGraphicsContext::ESolidPen);
					aGc.DrawRect(TRect(TPoint(step->iStartX, step->iStartY),TPoint(step->iEndX, step->iEndY)));
					}
					break;
				case EAnimDrawFilledRect:
					{
					TAnimLineDrawStep* step = drawStep->LineDrawStep();
					aGc.SetBrushColor(iDrawColor);
					aGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
					aGc.SetPenStyle(CGraphicsContext::ENullPen);
					aGc.DrawRect(TRect(TPoint(step->iStartX, step->iStartY),TPoint(step->iEndX, step->iEndY)));
					}
					break;
				case EAnimWait:
					{
					TAnimWaitStep* step = drawStep->WaitStep();
					repeatAnimStep = ETrue;
					if (step->iSteps > 0)
						{
						step->iSteps--;
						if (step->iSteps == 0)
							repeatAnimStep = EFalse;
						}
					}
					break;
				case EAnimWaitUntilComplete:
					if (iPendingSteps->Count())
						repeatAnimStep = ETrue;
					break;
				default:
					// Type is user-defined, so add to the pending steps
					TRAPD(err, iPendingSteps->AppendL(TAnimMultiStep(*drawStep)));
					if (err != KErrNone)
						return ETrue;
					break;
				}
			iCurrentDrawStep++;
			}

		// If this step needs to be repeated, reset the draw step counter
		// otherwise increment the current animation step
		if (repeatAnimStep)
			{
			iCurrentDrawStep = startingDrawStep;
			}
		else
			{
			iCurrentAnimStep++;
			}
		}


	TInt done = DrawPendingAnimationSteps(aGc);

	if (iCurrentDrawStep == Count() && done)
		return ETrue;

	return EFalse;
	}


TBool CAknAnimationData::DrawPendingAnimationSteps(CBitmapContext& aGc)
	{
	TBool finished = ETrue;
	TInt count = iPendingSteps->Count();
	for (TInt ii=0; ii<count; ii++)
		{
		TAnimMultiStep* drawStep = &(*iPendingSteps)[ii];
		TBool done = ExecutePendingAnimationStep(aGc, drawStep);
		if (!done)
			{
			finished = EFalse;
			}
		else
			{
			// Remove step from pending list
			iPendingSteps->Delete(ii);
			ii--;
			count--;
			}
		}
	return finished;
	}


TBool CAknAnimationData::ExecutePendingAnimationStep(CBitmapContext& aGc, TAnimMultiStep* aStep)
	{
	TBool done = EFalse;
	switch (aStep->iDrawStep.Type())
		{
		case EAnimDrawLine:
		    {
		    TAnimLineDrawStep* step = (aStep->iDrawStep.LineDrawStep());
		    
		    if (aStep->iSubStep == step->iSteps -1)
			{
			done = ETrue;
			}
			{
			TInt diffX = step->iEndX - step->iStartX;
			TInt diffY = step->iEndY - step->iStartY;
			TInt startX = step->iStartX + (diffX * aStep->iSubStep / step->iSteps);
			TInt startY = step->iStartY + (diffY * aStep->iSubStep / step->iSteps);
			TInt endX = step->iStartX + (diffX * (aStep->iSubStep+1)/ step->iSteps);
			TInt endY = step->iStartY + (diffY * (aStep->iSubStep+1) / step->iSteps);
			aGc.SetBrushColor(iDrawColor);
			aGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
			aGc.Clear(TRect(TPoint(startX,startY),TPoint(endX+1, endY+1)));
			}
		    }
		    break;
		case EAnimRevealPartNewViewFromLeft:
			{
			TAnimBlitStep* step = (aStep->iDrawStep.BlitStep());
			TPoint offset((step->iWidth * aStep->iSubStep) / step->iSteps, 0);
			TSize size((step->iWidth / step->iSteps)+1, step->iHeight);
			aGc.BitBlt(TPoint(step->iDestX, step->iDestY) + offset, iViewBitmap,
				TRect(TPoint(step->iSrcX, step->iSrcY) + offset, size));
			if (aStep->iSubStep == step->iSteps-1)
				done = ETrue;
			}
			break;
		case EAnimRevealPartNewViewFromRight:
			{
			TAnimBlitStep* step = (aStep->iDrawStep.BlitStep());
			TInt thisStep = (step->iSteps - aStep->iSubStep) - 1;
			TPoint offset((step->iWidth * thisStep) / step->iSteps, 0);
			TSize size((step->iWidth / step->iSteps)+1, step->iHeight);
			aGc.BitBlt(TPoint(step->iDestX, step->iDestY) + offset, iViewBitmap,
				TRect(TPoint(step->iSrcX, step->iSrcY) + offset, size));
			if (aStep->iSubStep == step->iSteps-1)
				done = ETrue;
			}
			break;
		case EAnimRevealPartNewViewFromTop:
			{
			TAnimBlitStep* step = (aStep->iDrawStep.BlitStep());
			TPoint offset(0,(step->iHeight * aStep->iSubStep) / step->iSteps);
			TSize size(step->iWidth,(step->iHeight / step->iSteps)+1);
			aGc.BitBlt(TPoint(step->iDestX, step->iDestY) + offset, iViewBitmap,
				TRect(TPoint(step->iSrcX, step->iSrcY) + offset, size));
			if (aStep->iSubStep == step->iSteps-1)
				done = ETrue;
			}
			break;
		case EAnimRevealPartNewViewFromBottom:
			{
			TAnimBlitStep* step = (aStep->iDrawStep.BlitStep());
			TInt thisStep = (step->iSteps - aStep->iSubStep) - 1;
			TPoint offset(0,(step->iHeight * thisStep) / step->iSteps);
			TSize size(step->iWidth,(step->iHeight / step->iSteps)+1);
			aGc.BitBlt(TPoint(step->iDestX, step->iDestY) + offset, iViewBitmap,
				TRect(TPoint(step->iSrcX, step->iSrcY) + offset, size));
			if (aStep->iSubStep == step->iSteps-1)
				done = ETrue;
			}
			break;
		case EAnimBlitSlideNewView:
			// Slide the bitmap between two screen positions
			{
			TAnimSlideStep* step = (aStep->iDrawStep.SlideStep());
			TSize bitmapSize(step->iWidth, step->iHeight);
			TInt slideDifferenceX = step->iSlideToX - step->iSlideFromX;
			TInt slideDifferenceY = step->iSlideToY - step->iSlideFromY;
			TInt slidePosX = step->iSlideFromX + ((slideDifferenceX * aStep->iSubStep) / step->iSteps);
			TInt slidePosY = step->iSlideFromY + ((slideDifferenceY * aStep->iSubStep) / step->iSteps);
			aGc.BitBlt(TPoint(slidePosX, slidePosY), iViewBitmap,
				TRect(TPoint(step->iSrcX, step->iSrcY), bitmapSize));
			if (aStep->iSubStep == step->iSteps)
				done = ETrue;
			}
			break;
		case EAnimBlitSlideNewViewClearBehind:
			// Slide the bitmap between two screen positions, clearing the screen behind it
			{
			TAnimSlideStep* step = (aStep->iDrawStep.SlideStep());
			TSize bitmapSize(step->iWidth, step->iHeight);
			TInt slideDifferenceX = step->iSlideToX - step->iSlideFromX;
			TInt slideDifferenceY = step->iSlideToY - step->iSlideFromY;
			if (aStep->iSubStep > 0)
				{
				// This is not the first step, so clear over the area of the previous step
				TInt slidePosX = step->iSlideFromX + ((slideDifferenceX * (aStep->iSubStep-1)) / step->iSteps);
				TInt slidePosY = step->iSlideFromY + ((slideDifferenceY * (aStep->iSubStep-1)) / step->iSteps);
				aGc.Clear(TRect(TPoint(slidePosX, slidePosY), bitmapSize));
				}
			TInt slidePosX = step->iSlideFromX + ((slideDifferenceX * aStep->iSubStep) / step->iSteps);
			TInt slidePosY = step->iSlideFromY + ((slideDifferenceY * aStep->iSubStep) / step->iSteps);
			aGc.BitBlt(TPoint(slidePosX, slidePosY), iViewBitmap,
				TRect(TPoint(step->iSrcX, step->iSrcY), bitmapSize));
			if (aStep->iSubStep == step->iSteps)
				done = ETrue;
			}
			break;
		default:
			done = DrawUserAnimationStep(aGc, *aStep);
			break;
		}

	aStep->iSubStep++;
	return done;
	}

// End of File
