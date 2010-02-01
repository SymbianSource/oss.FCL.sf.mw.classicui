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
// source code for the utility classes
// $Workfile:   UTILS.CPP  $
// $Revision:   1.6  $
// $Author:   DougF  $
// $Date:   07 Jul 1999 16:16:18  $
// 
//

#include "CL_STD.H"

// initializing static const data

const TInt TTrig::iStore[]=
	{
	32768,
	32588,
	32052,
	31164,
	29935,
	28378,
	26510,
	24351,
	21926,
	19261,
	16384,
	13328,
	10126,
	6813,
	3425,
	0,
	0
	};

// DAnimWithUtils

DAnimWithUtils::DAnimWithUtils()
	{
	__DECLARE_NAME(_S("DAnimWithUtils"));
	}

void DAnimWithUtils::ConstructL(TAny*, TBool aHasFocus)
	{
	const RMessagePtr2& message=*iFunctions->Message();
	const TInt bufLength=message.GetDesLength(KIpcSlot);
	__ASSERT_ALWAYS(bufLength>=0, PanicClientFromServer());
	TPtr8 buf((TUint8*)User::AllocLC(bufLength), bufLength, bufLength);
	const TInt error1=message.Read(KIpcSlot, buf);
	__ASSERT_ALWAYS(error1==KErrNone, PanicClientFromServer());

	TRAPD(error2, ConstructLP(buf.Ptr(), aHasFocus));
	HandleErrorIfErrorL(error2);

	CleanupStack::PopAndDestroy(); // pop and destroy the allocated buffer
	}

TInt DAnimWithUtils::CommandReplyL(TInt aOpcode, TAny* aArgs)
	{
	TInt returnVal=0; // dummy initialization to prevent compiler warning
	TRAPD(error, returnVal=CommandReplyLP(aOpcode, aArgs));
	HandleErrorIfErrorL(error);
	return returnVal;
	}

void DAnimWithUtils::Command(TInt aOpcode, TAny* aArgs)
	{
	CommandP(aOpcode, aArgs);
	}

void DAnimWithUtils::Animate(TDateTime* aDateTime)
	{
	AnimateP(aDateTime);
	}

void DAnimWithUtils::Redraw()
	{
	RedrawP();
	}

void DAnimWithUtils::FocusChanged(TBool aState)
	{
	FocusChangedP(aState);
	}

TInt DAnimWithUtils::CommandReplyLP(TInt, TAny*)
	{
	PanicClientFromServer();
	return KErrNone; // dummy return to prevent compiler error
	}

void DAnimWithUtils::CommandP(TInt, TAny*)
	{
	PanicClientFromServer();
	}

void DAnimWithUtils::FocusChangedP(TBool)
	{
	}

TPtrC DAnimWithUtils::ReadText(const TUint8*& aBytePtr, TInt aTextLength)
	{
	TPtrC text((TText*)aBytePtr, aTextLength);
	aBytePtr+=Align4(text.Size());
	return text;
	}

TBool DAnimWithUtils::OfferRawEvent(const TRawEvent& /*aRawEvent*/)
	{
	return EFalse;
	}

void DAnimWithUtils::HandleErrorIfErrorL(TInt aError)
	{
	switch (aError)
		{
	case KErrNone:
		break;
	case KPanicClientFromServer:
		iFunctions->Panic();
		break;
	default:
		User::Leave(aError);
		break;
		}
	}

// DDigitalDisplayTextSection

DDigitalDisplayTextSection::DDigitalDisplayTextSection(MAnimGeneralFunctions& aFunctions, TRgb aTextColor, TDigitalDisplayHorizontalTextAlignment aHorizontalAlignment,
																TDigitalDisplayVerticalTextAlignment aVerticalAlignment,
																TInt aHorizontalMargin, TInt aVerticalMargin)
	:iFunctions(aFunctions),
	 iTextColor(aTextColor),
	 iHorizontalAlignment(aHorizontalAlignment),
	 iVerticalAlignment(aVerticalAlignment),
	 iHorizontalMargin(aHorizontalMargin),
	 iVerticalMargin(aVerticalMargin)
	{
	__DECLARE_NAME(_S("DDigitalDisplayTextSection"));

	__ASSERT_DEBUG(iFormat==NULL, Panic(EClockServerPanicNotInitializedToNULL7));
	}
// The format strings used by TTime to indentify individual elements of the time e.g. hours, mins, secs etc...
_LIT(KMicrosecondsFormat,"*%C*");
_LIT(KSecondsFormat,"*%S*");
_LIT(KTimeSeperatorFormat, "%:*");
static const TInt KCharacterCountSeconds = 2;
static const TInt KCharacterCountMicroSeconds = 6;
void DDigitalDisplayTextSection::ConstructL(const TDesC& aFormat, TInt aFontHandle)
	{
	iFormat=HBufC::NewL(aFormat.Length());
	*iFormat=aFormat;
	iFont=iFunctions.DuplicateFontL(aFontHandle);
			
	iTruncatedFormat = HBufC::NewL(iFormat->Length());
	*iTruncatedFormat = *iFormat;
	TInt secPos = iTruncatedFormat->Match(KSecondsFormat);
	if(secPos != KErrNotFound)
		{
		// Delete the 2 second characters
		iTruncatedFormat->Des().Delete(secPos,KCharacterCountSeconds);
		// Check the preceeding characters to see if it is a time seperator
		// and if so remove that as well
		if( (iTruncatedFormat->Des().Mid(secPos-3,3)).Match(KTimeSeperatorFormat) != KErrNotFound)
			{
			iTruncatedFormat->Des().Delete(secPos-3,3);
			}
		}
	TInt microSecPos = iTruncatedFormat->Match(KMicrosecondsFormat);
	if(microSecPos != KErrNotFound)
		{
		// Delete the 6 microsecond characters
		iTruncatedFormat->Des().Delete(secPos,KCharacterCountMicroSeconds);
		}		
	}

void DDigitalDisplayTextSection::SetInitialTimeP(const TTime& aTime, TBool aLimitResolutionToMinutes)
	{
	FormatTruncatingIfNecessaryP(aTime, iDisplayText,aLimitResolutionToMinutes);
	}

DDigitalDisplayTextSection::~DDigitalDisplayTextSection()
	{
	delete iTruncatedFormat;
	delete iFormat;
	iFunctions.CloseFont(iFont);
	}

void DDigitalDisplayTextSection::DrawP(CAnimGc& aGc, const TRect& aRect, TBool aFlashStateOn, const TRgb* aOverridingColor) const
	{
	aGc.SetPenColor((aOverridingColor!=NULL)? *aOverridingColor: iTextColor);
	aGc.UseFont(iFont);
	TInt yPosition=YPositionP(aRect);
	TInt textOffset;
	TInt textLength;
	TInt xPosition;
	SCharWidth pixelWidth;
	TBool inFlashingBlock;
	InitializeTextBlockIteratorP(aRect, iDisplayText, textOffset, textLength, xPosition, pixelWidth, inFlashingBlock);
	while (GetNextTextBlockP(iDisplayText, textOffset, textLength, xPosition, pixelWidth, inFlashingBlock))
		if (aFlashStateOn || !inFlashingBlock)
			aGc.DrawText(iDisplayText.Mid(textOffset, textLength), TPoint(xPosition, yPosition));
	aGc.DiscardFont();
	}

void DDigitalDisplayTextSection::UpdateDisplayDataP(const TRect& aRect, const STimeDeviceShadow& aShadow, const TTime& aTime, TBool
#if defined(__SLOW_DIGITAL_REGION_CALCULATION__)
																											aFlashStateIsChanging
#endif
																											, TRegion* aRegion, TBool aLimitResolutionToMinutes)
	{
	TDisplayText newDisplayText;
	FormatTruncatingIfNecessaryP(aTime, newDisplayText,aLimitResolutionToMinutes);
#if defined(__SLOW_DIGITAL_REGION_CALCULATION__)
	if (aRegion!=NULL)
		{
		TInt yPosition=YPositionP(aRect);
		TInt ascentInPixels=iFont->AscentInPixels();
		TInt heightInPixels=iFont->HeightInPixels();
		TInt oldTextOffset, newTextOffset;
		TInt oldTextLength, newTextLength;
		TInt oldXPosition, newXPosition;
		SCharWidth oldPixelWidth, newPixelWidth;
		TBool oldInFlashingBlock, newInFlashingBlock;
		InitializeTextBlockIteratorP(aRect, iDisplayText, oldTextOffset, oldTextLength, oldXPosition, oldPixelWidth, oldInFlashingBlock);
		InitializeTextBlockIteratorP(aRect, newDisplayText, newTextOffset, newTextLength, newXPosition, newPixelWidth, newInFlashingBlock);
		FOREVER
			{
			TBool existsOldTextBlock=GetNextTextBlockP(iDisplayText, oldTextOffset, oldTextLength, oldXPosition, oldPixelWidth, oldInFlashingBlock);
			TBool existsNewTextBlock=GetNextTextBlockP(newDisplayText, newTextOffset, newTextLength, newXPosition, newPixelWidth, newInFlashingBlock);

			if (!existsOldTextBlock)
				{
				if (existsNewTextBlock)
					aRegion->AddRect(ExpandToIncludeShadows(UpdateRect(TPoint(newXPosition, yPosition), newPixelWidth, ascentInPixels, heightInPixels), aShadow));
				else
					break;
				}
			else
				{
				if (!existsNewTextBlock)
					aRegion->AddRect(ExpandToIncludeShadows(UpdateRect(TPoint(oldXPosition, yPosition), oldPixelWidth, ascentInPixels, heightInPixels), aShadow));
				else
					{
					if ((oldInFlashingBlock || newInFlashingBlock) && aFlashStateIsChanging)
						{
						TRect rect=UpdateRect(TPoint(oldXPosition, yPosition), oldPixelWidth, ascentInPixels, heightInPixels);
						rect.BoundingRect(UpdateRect(TPoint(newXPosition, yPosition), newPixelWidth, ascentInPixels, heightInPixels));
						aRegion->AddRect(ExpandToIncludeShadows(rect, aShadow));
						}
					else
						{
						TPtrC oldText=iDisplayText.Mid(oldTextOffset, oldTextLength);
						TPtrC newText=newDisplayText.Mid(newTextOffset, newTextLength);
						AddUpdateAreasToRegion(*aRegion, yPosition, aShadow, ascentInPixels, heightInPixels, oldText, oldXPosition, newText, newXPosition);
						}
					}
				}
			}
		}

	iDisplayText=newDisplayText;
#else
	TInt yPosition=0; // dummy initialization to prevent compiler warning
	TInt ascentInPixels=0; // dummy initialization to prevent compiler warning
	TInt heightInPixels=0; // dummy initialization to prevent compiler warning
	SCharWidth pixelWidth;
	if (aRegion!=NULL)
		{
		yPosition=YPositionP(aRect);
		ascentInPixels=iFont->AscentInPixels();
		heightInPixels=iFont->HeightInPixels();
		TextWidthInPixels(iDisplayText, pixelWidth);
		aRegion->AddRect(ExpandToIncludeShadows(UpdateRect(TPoint(XPositionP(aRect, iDisplayText), yPosition), pixelWidth, ascentInPixels, heightInPixels), aShadow));
		}
	iDisplayText=newDisplayText;
	if (aRegion!=NULL)
		{
		TextWidthInPixels(iDisplayText, pixelWidth);
		aRegion->AddRect(ExpandToIncludeShadows(UpdateRect(TPoint(XPositionP(aRect, iDisplayText), yPosition), pixelWidth, ascentInPixels, heightInPixels), aShadow));
		}
#endif
	}

void DDigitalDisplayTextSection::FormatTruncatingIfNecessaryP(const TTime& aTime, TDes& aResult, TBool aLimitResolutionToMinutes) const
	{
	//Check if time resolution has been reduced to minutes
	if(aLimitResolutionToMinutes)
		{
		// Find and remove seconds and microseconds from format string
		TRAP_IGNORE(aTime.FormatL(aResult, *iTruncatedFormat));
		}
	else
		{
		// The resolution has not been limited so use original format string
		TRAP_IGNORE(aTime.FormatL(aResult, *iFormat));
		}
	}

TRect DDigitalDisplayTextSection::UpdateRect(const TPoint& aPosition, const SCharWidth& aPixelWidth, TInt aAscentInPixels, TInt aHeightInPixels) const
	{
	return TRect(TPoint(aPosition.iX+aPixelWidth.iLeftAdjust, aPosition.iY-aAscentInPixels), TSize(aPixelWidth.iWidth, aHeightInPixels));
	}

TRect DDigitalDisplayTextSection::ExpandToIncludeShadows(const TRect& aRect, const STimeDeviceShadow& aShadow) const
	{
	TRect rect=aRect;
	if (aShadow.iIsOn)
		{
		rect.Move(aShadow.iOffset);
		rect.BoundingRect(aRect);
		}
	return rect;
	}

#if defined(__SLOW_DIGITAL_REGION_CALCULATION__)
void DDigitalDisplayTextSection::AddUpdateAreasToRegion(TRegion& aRegion, TInt aYPosition, const STimeDeviceShadow& aShadow, TInt aAscentInPixels, TInt aHeightInPixels,
																const TDesC& aOldText, TInt aOldXPosition,
																const TDesC& aNewText, TInt aNewXPosition) const
	{
	TBool inUpdateArea=EFalse;
	TInt xPosOfUpdateAreaStart=0; // dummy initialization to prevent compiler warning
	TInt oldTextPos=0;
	TInt newTextPos=0;
	SCharWidth oldTotalPixelWidth;
	iFont->TextWidthInPixels(aOldText, oldTotalPixelWidth);
	SCharWidth newTotalPixelWidth;
	iFont->TextWidthInPixels(aNewText, newTotalPixelWidth);
	FOREVER
		{
		SCharWidth oldLeftPixelWidth;
		iFont->TextWidthInPixels(aOldText.Left(oldTextPos), oldLeftPixelWidth);
		TInt oldPixelPosX=aOldXPosition+oldLeftPixelWidth.iMove;
		SCharWidth newLeftPixelWidth;
		iFont->TextWidthInPixels(aNewText.Left(newTextPos), newLeftPixelWidth);
		TInt newPixelPosX=aNewXPosition+newLeftPixelWidth.iMove;

		if ((oldTextPos>=aOldText.Length()) || (newTextPos>=aNewText.Length()))
			{
			if (!inUpdateArea)
				{
				SCharWidth rightOldPixelWidth;
				iFont->TextWidthInPixels(aOldText.Mid(oldTextPos), rightOldPixelWidth);
				SCharWidth rightNewPixelWidth;
				iFont->TextWidthInPixels(aNewText.Mid(newTextPos), rightNewPixelWidth);
				xPosOfUpdateAreaStart=Min(oldPixelPosX+rightOldPixelWidth.iLeftAdjust,
										  newPixelPosX+rightNewPixelWidth.iLeftAdjust);
				}
			TInt maxX=Max(aOldXPosition+oldTotalPixelWidth.iMove-oldTotalPixelWidth.iRightAdjust,
						  aNewXPosition+newTotalPixelWidth.iMove-newTotalPixelWidth.iRightAdjust);
			if (maxX>xPosOfUpdateAreaStart)
				aRegion.AddRect(ExpandToIncludeShadows(TRect(TPoint(xPosOfUpdateAreaStart, aYPosition-aAscentInPixels),
															TSize(maxX-xPosOfUpdateAreaStart, aHeightInPixels)), aShadow));
			break;
			}

		if ((oldPixelPosX!=newPixelPosX) || (aOldText[oldTextPos]!=aNewText[newTextPos]))
			{
			if (!inUpdateArea)
				{
				SCharWidth rightOldPixelWidth;
				iFont->TextWidthInPixels(aOldText.Mid(oldTextPos), rightOldPixelWidth);
				SCharWidth rightNewPixelWidth;
				iFont->TextWidthInPixels(aNewText.Mid(newTextPos), rightNewPixelWidth);
				xPosOfUpdateAreaStart=Min(oldPixelPosX+rightOldPixelWidth.iLeftAdjust,
										  newPixelPosX+rightNewPixelWidth.iLeftAdjust);
				inUpdateArea=ETrue;
				}
			}
		else
			{
			if (inUpdateArea)
				{
				TInt maxX=Max(oldPixelPosX-oldLeftPixelWidth.iRightAdjust,
							  newPixelPosX-newLeftPixelWidth.iRightAdjust);
				if (maxX>xPosOfUpdateAreaStart)
					aRegion.AddRect(ExpandToIncludeShadows(TRect(TPoint(xPosOfUpdateAreaStart, aYPosition-aAscentInPixels),
																TSize(maxX-xPosOfUpdateAreaStart, aHeightInPixels)), aShadow));
				inUpdateArea=EFalse;
				}
			}

		if (oldPixelPosX<=newPixelPosX)
			++oldTextPos;
		if (newPixelPosX<=oldPixelPosX)
			++newTextPos;
		}
	}
#endif

void DDigitalDisplayTextSection::InitializeTextBlockIteratorP(const TRect& aRect, const TDesC& aText, TInt& aTextOffset, TInt& aTextLength,
																TInt& aXPosition, SCharWidth& aPixelWidth, TBool& aInFlashingBlock) const
	{
	aTextOffset=-1;
	aTextLength=0;
	aXPosition=XPositionP(aRect, aText);
	aPixelWidth.iLeftAdjust=0;
	aPixelWidth.iRightAdjust=0;
	aPixelWidth.iMove=0;
	aPixelWidth.iWidth=0;
	aInFlashingBlock=EFalse;
	}

TBool DDigitalDisplayTextSection::GetNextTextBlockP(const TDesC& aText, TInt& aTextOffset, TInt& aTextLength,
																TInt& aXPosition, SCharWidth& aPixelWidth, TBool& aInFlashingBlock) const
	{
	aTextOffset+=aTextLength+1;
	if (aTextOffset>=aText.Length())
		return EFalse;

	TPtrC text=aText.Mid(aTextOffset);
	TInt nextflashingBlockDelimiter=text.Locate(EDigitalDisplayLayoutCharFlashingBlockDelimiter);
	aTextLength=(nextflashingBlockDelimiter!=KErrNotFound)? nextflashingBlockDelimiter: text.Length();
	if ((aTextOffset>0) && (aText[aTextOffset-1]==EDigitalDisplayLayoutCharFlashingBlockDelimiter))
		aInFlashingBlock=!aInFlashingBlock;
	aXPosition+=aPixelWidth.iMove;
	iFont->TextWidthInPixels(text.Left(aTextLength), aPixelWidth);
	return ETrue;
	}

TInt DDigitalDisplayTextSection::XPositionP(const TRect& aRect, const TDesC& aText) const
	{
	TInt xPosOfLine=0; // dummy initialization to prevent compiler warning
	SCharWidth pixelWidth;
	TextWidthInPixels(aText, pixelWidth);
	switch (iHorizontalAlignment)
		{
	case EDigitalDisplayHorizontalTextAlignmentLeft:
		xPosOfLine=aRect.iTl.iX+iHorizontalMargin;
		break;
	case EDigitalDisplayHorizontalTextAlignmentCenter:
	case EDigitalDisplayHorizontalTextAlignmentRight:
		xPosOfLine=(iHorizontalAlignment==EDigitalDisplayHorizontalTextAlignmentCenter)?
							aRect.iTl.iX+(((aRect.iBr.iX-aRect.iTl.iX)-pixelWidth.iMove)/2):
							aRect.iBr.iX-iHorizontalMargin-pixelWidth.iMove;
		break;
	default:
		PanicClientFromServer();
		break;
		}

	return xPosOfLine;
	}

TInt DDigitalDisplayTextSection::YPositionP(const TRect& aRect) const
	{
	TInt yPosition=0; // dummy initialization to prevent compiler warning
	switch (iVerticalAlignment)
		{
	case EDigitalDisplayVerticalTextAlignmentTop:
		yPosition=aRect.iTl.iY+iVerticalMargin+iFont->AscentInPixels();
		break;
	case EDigitalDisplayVerticalTextAlignmentCenterInclDescent:
	case EDigitalDisplayVerticalTextAlignmentCenterExclDescent:
	case EDigitalDisplayVerticalTextAlignmentBottomInclDescent:
	case EDigitalDisplayVerticalTextAlignmentBottomExclDescent:
		{
		TInt descentInPixels=((iVerticalAlignment==EDigitalDisplayVerticalTextAlignmentCenterInclDescent) ||
							  (iVerticalAlignment==EDigitalDisplayVerticalTextAlignmentBottomInclDescent))? iFont->DescentInPixels(): 0;

		if ((iVerticalAlignment==EDigitalDisplayVerticalTextAlignmentBottomInclDescent) ||
			(iVerticalAlignment==EDigitalDisplayVerticalTextAlignmentBottomExclDescent))
			{
			yPosition=aRect.iBr.iY-iVerticalMargin-descentInPixels;
			}
		else
			{
			TInt ascentInPixels=iFont->AscentInPixels();
			yPosition=aRect.iTl.iY+ascentInPixels+(((aRect.iBr.iY-aRect.iTl.iY)-(ascentInPixels+descentInPixels))/2);
			}
		}
		break;
	default:
		PanicClientFromServer();
		break;
		}

	return yPosition;
	}

void DDigitalDisplayTextSection::TextWidthInPixels(const TDesC& aText, SCharWidth& aPixelWidth) const
	{
	aPixelWidth.iMove=0;
	TBool firstIteration=ETrue;
	TPtrC remainder=aText;
	FOREVER
		{
		TInt nextflashingBlockDelimiter=remainder.Locate(EDigitalDisplayLayoutCharFlashingBlockDelimiter);
		TPtrC textBlock=(nextflashingBlockDelimiter!=KErrNotFound)? remainder.Left(nextflashingBlockDelimiter): remainder;
		SCharWidth pixelWidth;
		iFont->TextWidthInPixels(textBlock,pixelWidth);
		aPixelWidth.iMove+=pixelWidth.iMove;
		if (firstIteration)
			{
			aPixelWidth.iLeftAdjust=pixelWidth.iLeftAdjust;
			firstIteration=EFalse;
			}
		if (nextflashingBlockDelimiter==KErrNotFound)
			{
			aPixelWidth.iRightAdjust=pixelWidth.iRightAdjust;
			break;
			}
		remainder.Set(remainder.Mid(nextflashingBlockDelimiter+1));
		}

	aPixelWidth.iWidth=aPixelWidth.iMove-(aPixelWidth.iLeftAdjust+aPixelWidth.iRightAdjust);
	}

void DDigitalDisplayTextSection::SetTextColor(TRgb aTextColor)
	{
	iTextColor = aTextColor;
	}



// TFraction

TFraction::TFraction()
	:iNumber(0),
	 iRightShift(0)
	{
	}

TFraction::TFraction(TInt aNumber, TInt aRightShift)
	:iNumber(aNumber),
	 iRightShift(aRightShift)
	{
	}

TInt TFraction::operator*(TInt aInt) const
	{
	TInt temp=iNumber*aInt;
	return (temp<0)? -((-temp)>>iRightShift): temp>>iRightShift;
	}

// TTrig

TFraction TTrig::Sin(TInt aDegrees)
	{
	return Cos(aDegrees-90);
	}

TFraction TTrig::Cos(TInt aDegrees)
	{
	while (aDegrees<0)
		aDegrees+=360;
	aDegrees%=360;

	TBool negative=EFalse;
	if (aDegrees>180)
		{
		aDegrees%=180;
		negative=!negative;
		}
	if (aDegrees>90)
		{
		aDegrees=180-aDegrees;
		negative=!negative;
		}

	TInt lowerLookUp=aDegrees/ENumInterpolations;
	TInt interpolation=aDegrees%ENumInterpolations;
	TInt denominator=iStore[lowerLookUp];
	if (interpolation>0)
		denominator+=(interpolation*(iStore[lowerLookUp+1]-iStore[lowerLookUp]))/ENumInterpolations;

	return TFraction(negative? -denominator: denominator, ERightShift);
	}

// DAnalogDisplayHandFeature

DAnalogDisplayHandFeature::DAnalogDisplayHandFeature()
	{
	__DECLARE_NAME(_S("DAnalogDisplayHandFeature"));
	}

TPoint DAnalogDisplayHandFeature::Rotate(const TPoint& aPoint, const TFraction& aSin, const TFraction& aCos, const TPoint& aOffset) const
	{
	return TPoint((aCos*aPoint.iX)-(aSin*aPoint.iY), (aCos*aPoint.iY)+(aSin*aPoint.iX))+aOffset;
	}

TRect DAnalogDisplayHandFeature::AdjustRectForPenSizeP(const TRect& aRect, const TSize& aPenSize) const
	{
	__ASSERT_ALWAYS((aPenSize.iWidth>0) && (aPenSize.iHeight>0), PanicClientFromServer());
	return TRect(aRect.iTl.iX-((aPenSize.iWidth-1)/2), aRect.iTl.iY-((aPenSize.iHeight-1)/2),
				 aRect.iBr.iX+(aPenSize.iWidth/2), aRect.iBr.iY+(aPenSize.iHeight/2));
	}

void DAnalogDisplayHandFeature::SetPenColor(TRgb /*aPenColor*/)
	{
	}

void DAnalogDisplayHandFeature::SetBrushColor(TRgb /*aBrushColor*/)
	{
	}



// DAnalogDisplayHandLine

DAnalogDisplayHandLine::DAnalogDisplayHandLine(CGraphicsContext::TPenStyle aPenStyle, TRgb aPenColor, const TSize& aPenSize, const TPoint& aStartPoint, const TPoint& aEndPoint)
	:iPenStyle(aPenStyle),
	 iPenColor(aPenColor),
	 iPenSize(aPenSize),
	 iStartPoint(aStartPoint),
	 iEndPoint(aEndPoint)
	{
	__DECLARE_NAME(_S("DAnalogDisplayHandLine"));
	}

TRect DAnalogDisplayHandLine::BoundingRectP(const TFraction& aSin, const TFraction& aCos, const TPoint& aHandCenter) const
	{
	TRect boundingRect(Rotate(iStartPoint, aSin, aCos, aHandCenter), Rotate(iEndPoint, aSin, aCos, aHandCenter));
	boundingRect.Normalize();
	boundingRect.iBr+=TPoint(1, 1);
	return AdjustRectForPenSizeP(boundingRect, iPenSize);
	}

void DAnalogDisplayHandLine::Draw(CAnimGc& aGc, const TFraction& aSin, const TFraction& aCos, const TPoint& aHandCenter, const TRgb* aOverridingColor) const
	{
	aGc.SetPenStyle(iPenStyle);
	if (iPenStyle!=CGraphicsContext::ENullPen)
		{
		aGc.SetPenColor((aOverridingColor!=NULL)? *aOverridingColor: iPenColor);
		aGc.SetPenSize(iPenSize);
		}

	aGc.DrawLine(Rotate(iStartPoint, aSin, aCos, aHandCenter), Rotate(iEndPoint, aSin, aCos, aHandCenter));
	}

void DAnalogDisplayHandLine::SetPenColor(TRgb aPenColor)
	{
	iPenColor = aPenColor;
	}


// DAnalogDisplayHandPolyLine

DAnalogDisplayHandPolyLine::DAnalogDisplayHandPolyLine(CGraphicsContext::TPenStyle aPenStyle, TRgb aPenColor, const TSize& aPenSize,
																CGraphicsContext::TBrushStyle aBrushStyle, TRgb aBrushColor,
																TBool aClosed, TInt aNumPoints)
	:iPenStyle(aPenStyle),
	 iPenColor(aPenColor),
	 iPenSize(aPenSize),
	 iBrushStyle(aBrushStyle),
	 iBrushColor(aBrushColor),
	 iClosed(aClosed)
#pragma warning (disable: 4705)
	{
#pragma warning (default: 4705)
	__DECLARE_NAME(_S("DAnalogDisplayHandPolyLine"));

	__ASSERT_ALWAYS((aNumPoints>0) && (aNumPoints<=KMaxTInt16), PanicClientFromServer());
	iPoints.iNumPoints=(TInt16)aNumPoints;
	__ASSERT_DEBUG(iPoints.iNumPointsAdded==0, Panic(EClockServerPanicNotInitializedToNULL8));
	__ASSERT_DEBUG(iPoints.iPoints==NULL, Panic(EClockServerPanicNotInitializedToZero3));
	}

void DAnalogDisplayHandPolyLine::AddPointLP(const TPoint& aPoint)
	{
	__ASSERT_ALWAYS(iPoints.iNumPointsAdded<iPoints.iNumPoints, PanicClientFromServer());
	__ASSERT_DEBUG((iPoints.iPoints==NULL)==(iScratchPointList==NULL), Panic(EClockServerPanicBadPolyLineState));
	if (iPoints.iPoints==NULL)
		{
		iPoints.iPoints=new(ELeave) TPoint[iPoints.iNumPoints];
		iScratchPointList=new(ELeave) CArrayFixFlat<TPoint>(iPoints.iNumPoints);
		}
	iScratchPointList->AppendL(aPoint); // this can leave so do this first
	iPoints.iPoints[iPoints.iNumPointsAdded++]=aPoint;
	}

DAnalogDisplayHandPolyLine::~DAnalogDisplayHandPolyLine()
	{
	delete [] iPoints.iPoints;
	delete iScratchPointList;
	}

TRect DAnalogDisplayHandPolyLine::BoundingRectP(const TFraction& aSin, const TFraction& aCos, const TPoint& aHandCenter) const
	{
	__ASSERT_ALWAYS(iPoints.iNumPoints>0, PanicClientFromServer());
	SetScratchPointList(aSin, aCos, aHandCenter);
	TRect boundingRect((*iScratchPointList)[0], (*iScratchPointList)[0]);
	for (TInt i=1; i<iPoints.iNumPoints; ++i)
		{
		TPoint point=(*iScratchPointList)[i];
		if (boundingRect.iTl.iX>point.iX)
			boundingRect.iTl.iX=point.iX;
		if (boundingRect.iTl.iY>point.iY)
			boundingRect.iTl.iY=point.iY;
		if (boundingRect.iBr.iX<point.iX)
			boundingRect.iBr.iX=point.iX;
		if (boundingRect.iBr.iY<point.iY)
			boundingRect.iBr.iY=point.iY;
		}

	boundingRect.iBr+=TPoint(1, 1);
	return AdjustRectForPenSizeP(boundingRect, iPenSize);
	}

void DAnalogDisplayHandPolyLine::Draw(CAnimGc& aGc, const TFraction& aSin, const TFraction& aCos, const TPoint& aHandCenter,
																const TRgb* aOverridingColor) const
	{
	SetScratchPointList(aSin, aCos, aHandCenter);

	aGc.SetPenStyle(iPenStyle);
	if (iPenStyle!=CGraphicsContext::ENullPen)
		{
		aGc.SetPenColor((aOverridingColor!=NULL)? *aOverridingColor: iPenColor);
		aGc.SetPenSize(iPenSize);
		}

	if (!iClosed)
		aGc.DrawPolyLine(iScratchPointList);
	else
		{
		aGc.SetBrushStyle(iBrushStyle);
		if (iBrushStyle!=CGraphicsContext::ENullBrush)
			aGc.SetBrushColor((aOverridingColor!=NULL)? *aOverridingColor: iBrushColor);

		aGc.DrawPolygon(iScratchPointList);
		}
	}

void DAnalogDisplayHandPolyLine::SetScratchPointList(const TFraction& aSin, const TFraction& aCos, const TPoint& aHandCenter) const
	{
	__ASSERT_ALWAYS((iPoints.iNumPoints==iPoints.iNumPointsAdded) && (iPoints.iNumPoints==iScratchPointList->Count()),
																				Panic(EClockServerPanicInconsistentPointListLengths));

	for (TInt i=0; i<iPoints.iNumPoints; ++i)
		(*((DAnalogDisplayHandPolyLine*)this)->iScratchPointList)[i]=Rotate(iPoints.iPoints[i], aSin, aCos, aHandCenter); // casts away the constness
	}

void DAnalogDisplayHandPolyLine::SetPenColor(TRgb aPenColor)
	{
	iPenColor = aPenColor;
	}

void DAnalogDisplayHandPolyLine::SetBrushColor(TRgb aBrushColor)
	{
	iBrushColor = aBrushColor;
	}


// DAnalogDisplayHandCircle

DAnalogDisplayHandCircle::DAnalogDisplayHandCircle(CGraphicsContext::TPenStyle aPenStyle, TRgb aPenColor, const TSize& aPenSize,
																CGraphicsContext::TBrushStyle aBrushStyle, TRgb aBrushColor,
																const TPoint& aCircleCenter, TInt aRadius)
	:iPenStyle(aPenStyle),
	 iPenColor(aPenColor),
	 iPenSize(aPenSize),
	 iBrushStyle(aBrushStyle),
	 iBrushColor(aBrushColor),
	 iCircleCenter(aCircleCenter),
	 iRadius(aRadius)
	{
	__DECLARE_NAME(_S("DAnalogDisplayHandCircle"));
	}

TRect DAnalogDisplayHandCircle::BoundingRectP(const TFraction& aSin, const TFraction& aCos, const TPoint& aHandCenter) const
	{
	return AdjustRectForPenSizeP(Rect(aSin, aCos, aHandCenter), iPenSize);
	}

void DAnalogDisplayHandCircle::Draw(CAnimGc& aGc, const TFraction& aSin, const TFraction& aCos, const TPoint& aHandCenter,
																const TRgb* aOverridingColor) const
	{
	aGc.SetPenStyle(iPenStyle);
	if (iPenStyle!=CGraphicsContext::ENullPen)
		{
		aGc.SetPenColor((aOverridingColor!=NULL)? *aOverridingColor: iPenColor);
		aGc.SetPenSize(iPenSize);
		}

	aGc.SetBrushStyle(iBrushStyle);
	if (iBrushStyle!=CGraphicsContext::ENullBrush)
		aGc.SetBrushColor((aOverridingColor!=NULL)? *aOverridingColor: iBrushColor);

	aGc.DrawEllipse(Rect(aSin, aCos, aHandCenter));
	}

TRect DAnalogDisplayHandCircle::Rect(const TFraction& aSin, const TFraction& aCos, const TPoint& aHandCenter) const
	{
	TPoint center=Rotate(iCircleCenter, aSin, aCos, aHandCenter);
	return TRect(center.iX-iRadius, center.iY-iRadius, center.iX+iRadius+1, center.iY+iRadius+1);
	}

void DAnalogDisplayHandCircle::SetPenColor(TRgb aPenColor)
	{
	iPenColor = aPenColor;
	}

void DAnalogDisplayHandCircle::SetBrushColor(TRgb aBrushColor)
	{
	iBrushColor = aBrushColor;
	}



// DAnalogDisplayHand

DAnalogDisplayHand::DAnalogDisplayHand(TAnalogDisplayHandType aType, TInt aNumFeatures)
	:iType(aType)
#pragma warning (disable: 4705)
	{
#pragma warning (default: 4705)
	__DECLARE_NAME(_S("DAnalogDisplayHand"));

	__ASSERT_ALWAYS((aNumFeatures>0) && (aNumFeatures<=KMaxTInt16), PanicClientFromServer());
	iFeatures.iNumFeatures=(TInt16)aNumFeatures;
	__ASSERT_DEBUG(iFeatures.iNumFeaturesAdded==0, Panic(EClockServerPanicNotInitializedToNULL9));
	__ASSERT_DEBUG(iFeatures.iFeatures==NULL, Panic(EClockServerPanicNotInitializedToZero4));
	}

void DAnalogDisplayHand::AddFeatureLP(DAnalogDisplayHandFeature* aFeature)
	{
	__ASSERT_ALWAYS(iFeatures.iNumFeaturesAdded<iFeatures.iNumFeatures, PanicClientFromServer());
	if (iFeatures.iFeatures==NULL)
		iFeatures.iFeatures=new(ELeave) DAnalogDisplayHandFeature*[iFeatures.iNumFeatures];

	iFeatures.iFeatures[iFeatures.iNumFeaturesAdded++]=aFeature; // ownership is only taken after everything that can leave has succeeded
	}

void DAnalogDisplayHand::SetInitialTimeP(const TTime& aTime)
	{
	SetDegreesOffUpright(DegreesOffUprightP(aTime));
	}

DAnalogDisplayHand::~DAnalogDisplayHand()
	{
	if (iFeatures.iFeatures!=NULL)
		{
		for (TInt i=0; i<iFeatures.iNumFeaturesAdded; ++i)
			delete iFeatures.iFeatures[i];
		delete [] iFeatures.iFeatures;
		}
	}

void DAnalogDisplayHand::DrawP(CAnimGc& aGc, const TPoint& aHandCenter, const TRgb* aOverridingColor) const
	{
	__ASSERT_ALWAYS(iFeatures.iNumFeaturesAdded==iFeatures.iNumFeatures, PanicClientFromServer());
	for (TInt i=0; i<iFeatures.iNumFeatures; ++i)
		iFeatures.iFeatures[i]->Draw(aGc, iSin, iCos, aHandCenter, aOverridingColor);
	}

void DAnalogDisplayHand::UpdateDisplayDataP(const TTime& aTime, const TPoint& aHandCenter, const STimeDeviceShadow& aShadow, TRegion* aRegion)
	{
	TInt degreesOffUpright=DegreesOffUprightP(aTime);
	if (iDegreesOffUpright!=degreesOffUpright)
		{
		if (aRegion!=NULL)
			aRegion->AddRect(BoundingRectP(aHandCenter, aShadow));
		SetDegreesOffUpright(degreesOffUpright);
		if (aRegion!=NULL)
			aRegion->AddRect(BoundingRectP(aHandCenter, aShadow));
		}
	}

TRect DAnalogDisplayHand::BoundingRectP(const TPoint& aHandCenter, const STimeDeviceShadow& aShadow) const
	{
	__ASSERT_ALWAYS((iFeatures.iNumFeaturesAdded==iFeatures.iNumFeatures) && (iFeatures.iNumFeatures>0), PanicClientFromServer());
	TRect boundingRect=iFeatures.iFeatures[0]->BoundingRectP(iSin, iCos, aHandCenter);
	for (TInt i=1; i<iFeatures.iNumFeatures; ++i)
		boundingRect.BoundingRect(iFeatures.iFeatures[i]->BoundingRectP(iSin, iCos, aHandCenter));
	if (aShadow.iIsOn)
		{
		TRect temp=boundingRect;
		temp.Move(aShadow.iOffset);
		boundingRect.BoundingRect(temp);
		}
	return boundingRect;
	}

void DAnalogDisplayHand::SetDegreesOffUpright(TInt aDegreesOffUpright)
	{
	iDegreesOffUpright=aDegreesOffUpright;
	iSin=TTrig::Sin(iDegreesOffUpright);
	iCos=TTrig::Cos(iDegreesOffUpright);
	}

TInt DAnalogDisplayHand::DegreesOffUprightP(const TTime& aTime) const
	{
	TDateTime dateTime=aTime.DateTime();
	TInt degrees=0; // dummy initialization to prevent compiler error
	switch (iType)
		{
	case EAnalogDisplayHandOneRevPer12Hours:
		degrees=(dateTime.Second()+(60*(dateTime.Minute()+(60*dateTime.Hour()))))/120;
		break;
	case EAnalogDisplayHandOneRevPerHour:
		degrees=(dateTime.Second()+(60*dateTime.Minute()))/10;
		break;
	case EAnalogDisplayHandOneRevPerMinute:
		degrees=6*dateTime.Second();
		break;
	default:
		PanicClientFromServer();
		break;
		}
	return degrees;
	}

void DAnalogDisplayHand::SetPenColor(const TRgb aPenColor)
	{
	for (TInt i=0; i<iFeatures.iNumFeatures; ++i)
		iFeatures.iFeatures[i]->SetPenColor(aPenColor);
	}

void DAnalogDisplayHand::SetBrushColor(const TRgb aBrushColor)
	{
	for (TInt i=0; i<iFeatures.iNumFeatures; ++i)
		iFeatures.iFeatures[i]->SetBrushColor(aBrushColor);
	}
