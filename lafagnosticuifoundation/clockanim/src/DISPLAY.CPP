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

#include "CL_STD.H"

_LIT(KFormatText,"%*A");

// DDisplay

DDisplay::DDisplay(const TPoint& aPosition, const TSize& aSize, const TMargins& aMargins, const STimeDeviceShadow& aShadow)
	:iShadow(aShadow),
	 iPosition(aPosition),
	 iSize(aSize),
	 iVisible(EFalse),
	 iMargins(aMargins)
	{
	__DECLARE_NAME(_S("DDisplay"));
	}

void DDisplay::DrawP(MAnimWindowFunctions& aFunctions, CAnimGc& aGc) const
	{
	DrawClippedToDisplayRegionP(aFunctions, aGc);
	}

void DDisplay::UpdateLP(DAnimWithUtils::TFunctions& aFunctions, CAnimGc& aGc, const TTime& aTime)
	{
	aFunctions.iWindowFunctions.ActivateGc();
#if defined(__SHOW_UPDATE_REGION__)
	DrawClippedToDisplayRegionP(aFunctions, aGc);
#endif
	RRegionBuf10 region;
	TRAPD(error, UpdateDisplayDataAndDrawClippedToDisplayRegionP(aFunctions, aGc, aTime, IsVisibleAndNotHidden(aFunctions.iWindowFunctions)? &region: NULL));
	region.Close();
	if (error!=KErrNone)
		{
		__ASSERT_DEBUG(error==KPanicClientFromServer, Panic(EClockServerPanicUnexpectedError));
		User::Leave(error);
		}
	}

TRect DDisplay::RectDrawnTo() const
	{
	return TRect(iPosition, iSize);
	}

TRect DDisplay::RectToInvalidate() const
	{
	TRect rect=RectDrawnTo();
	rect.iTl.iX-=iMargins.iLeft;
	rect.iTl.iY-=iMargins.iTop;
	rect.iBr.iX+=iMargins.iRight;
	rect.iBr.iY+=iMargins.iBottom;
	return rect;
	}

void DDisplay::HandleCommandLP(DAnimWithUtils::TFunctions& aFunctions, CAnimGc& aGc, const TTime& aTime, TInt aOpcode, TAny* aArgs)
	{
	TPoint position=iPosition;
	TSize size=iSize;
	switch (aOpcode)
		{
	case EDisplayCommandSetVisible:
		{
		SDisplayCommandSetVisibleArgs* displayArgs=(SDisplayCommandSetVisibleArgs*)aArgs;
		if (iVisible!=displayArgs->iVisible)
			{
			iVisible=displayArgs->iVisible;
			aFunctions.iWindowFunctions.Invalidate(RectToInvalidate());
			}
		}
		break;
	case EDisplayCommandSetPositionAndSize:
		{
		SDisplayCommandSetPositionAndSizeArgs* displayArgs=(SDisplayCommandSetPositionAndSizeArgs*)aArgs;
		position=displayArgs->iPosition;
		size=displayArgs->iSize;
		}
		goto setPositionAndOrSize;
	case EDisplayCommandSetPosition:
		{
		SDisplayCommandSetPositionArgs* displayArgs=(SDisplayCommandSetPositionArgs*)aArgs;
		position=displayArgs->iPosition;
		}
		goto setPositionAndOrSize;
	case EDisplayCommandSetSize:
		{
		SDisplayCommandSetSizeArgs* displayArgs=(SDisplayCommandSetSizeArgs*)aArgs;
		size=displayArgs->iSize;
		}
		goto setPositionAndOrSize;
	setPositionAndOrSize:
		if ((iPosition!=position) || (iSize!=size))
			{
			TRect oldRectToInvalidate=RectToInvalidate();
			iPosition=position;
			iSize=size;
			PositionOrSizeHasChanged();
			TRect newRectToInvalidate=RectToInvalidate();
			if (newRectToInvalidate.Intersects(oldRectToInvalidate))
				newRectToInvalidate.BoundingRect(oldRectToInvalidate);
			else
				if (iVisible)
					aFunctions.iWindowFunctions.Invalidate(oldRectToInvalidate);
			aFunctions.iWindowFunctions.SetRect(newRectToInvalidate);
			if (iVisible)
				aFunctions.iWindowFunctions.Invalidate(newRectToInvalidate);
			}
		break;
	case EDisplayCommandUpdateDisplay:
		UpdateLP(aFunctions, aGc, aTime);
		break;
	case EDisplayCommandDraw:
		aFunctions.iWindowFunctions.ActivateGc();
		DrawP(aFunctions.iWindowFunctions, aGc);
		break;
	default:
		PanicClientFromServer();
		break;
		}
	}

void DDisplay::PositionOrSizeHasChanged()
	{
	}

void DDisplay::SetPosition(const TPoint& aPosition)
	{
	iPosition=aPosition;
	}

void DDisplay::DrawClippedToDisplayRegionP(MAnimWindowFunctions& aFunctions, CAnimGc& aGc, TRegion* aRegion) const
	{
	if (IsVisibleAndNotHidden(aFunctions))
		{
		TRect rectDrawnTo=RectDrawnTo();
		const TRegionFix<1> regionDrawnTo=rectDrawnTo;
		const TRegion* clippingRegion=NULL;
		TBool fullDrawRequired=ETrue;
		if (aRegion!=NULL)
			{
			aRegion->Intersect(regionDrawnTo);
			aRegion->Tidy();
			if (aRegion->CheckError()==KErrNone)
				{
				clippingRegion=aRegion;
				fullDrawRequired=EFalse;
				}
			}
		if (clippingRegion==NULL)
			clippingRegion=&regionDrawnTo;
		if (!clippingRegion->IsEmpty())
			{
#if defined(__SHOW_UPDATE_REGION__)
			aGc.SetDrawMode(CGraphicsContext::EDrawModeNOTSCREEN);
			aGc.SetPenStyle(CGraphicsContext::ESolidPen);
			aGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
			aGc.DrawRect(rectDrawnTo);
#endif
			TRect clippingRegionBoundingRect=clippingRegion->BoundingRect();
			aGc.SetClippingRect(clippingRegionBoundingRect);
			aGc.SetClippingRegion(*clippingRegion); // N.B. cannot fail
			DoDrawP(aGc, fullDrawRequired, clippingRegionBoundingRect);
			aGc.CancelClippingRegion();
			aGc.CancelClippingRect();
			}
		}
	}

void DDisplay::UpdateDisplayDataAndDrawClippedToDisplayRegionP(DAnimWithUtils::TFunctions& aFunctions, CAnimGc& aGc, const TTime& aTime, TRegion* aRegion)
	{
	UpdateDisplayDataP(aFunctions.iFunctions, aTime, aRegion);
	DrawClippedToDisplayRegionP(aFunctions.iWindowFunctions, aGc, aRegion);
	}

TBool DDisplay::IsVisibleAndNotHidden(MAnimWindowFunctions& aFunctions) const
	{
	return iVisible && !aFunctions.IsHidden();
	}

// DDigitalDisplay

DDigitalDisplay::DDigitalDisplay(const TPoint& aPosition, const TSize& aSize, const TMargins& aMargins, const STimeDeviceShadow& aShadow, TRgb aBackgroundColor, TInt aNumTextSections)
	:DDisplay(aPosition, aSize, aMargins, aShadow),
	 iBackgroundColor(aBackgroundColor),
	 iFlashStateOn(ETrue)
#pragma warning (disable: 4705)
	{
#pragma warning (default: 4705)
	__DECLARE_NAME(_S("DDigitalDisplay"));

	__ASSERT_ALWAYS((aNumTextSections>0) && (aNumTextSections<=KMaxTInt16), PanicClientFromServer());
	iTextSections.iNumTextSections=(TInt16)aNumTextSections;
	__ASSERT_DEBUG(iTextSections.iNumTextSectionsAdded==0, Panic(EClockServerPanicNotInitializedToNULL1));
	__ASSERT_DEBUG(iTextSections.iTextSections==NULL, Panic(EClockServerPanicNotInitializedToZero1));
	}

void DDigitalDisplay::AddTextSectionLP(DDigitalDisplayTextSection* aTextSection)
	{
	__ASSERT_ALWAYS(iTextSections.iNumTextSectionsAdded<iTextSections.iNumTextSections, PanicClientFromServer());
	if (iTextSections.iTextSections==NULL)
		iTextSections.iTextSections=new(ELeave) DDigitalDisplayTextSection*[iTextSections.iNumTextSections];

	iTextSections.iTextSections[iTextSections.iNumTextSectionsAdded++]=aTextSection; // ownership is only taken after everything that can leave has succeeded
	}

void DDigitalDisplay::SetInitialTimeP(const TTime& aTime)
	{
	__ASSERT_ALWAYS(iTextSections.iNumTextSectionsAdded==iTextSections.iNumTextSections, PanicClientFromServer());
	for (TInt i=0; i<iTextSections.iNumTextSections; ++i)
		iTextSections.iTextSections[i]->SetInitialTimeP(aTime,iTimeResolutionLimitedToMinutes);
	}

DDigitalDisplay::~DDigitalDisplay()
	{
	if (iTextSections.iTextSections!=NULL)
		{
		for (TInt i=0; i<iTextSections.iNumTextSectionsAdded; ++i)
			delete iTextSections.iTextSections[i];
		delete [] iTextSections.iTextSections;
		}
	}

void DDigitalDisplay::HandleCommandLP(DAnimWithUtils::TFunctions& aFunctions, CAnimGc& aGc, const TTime& aTime, TInt aOpcode, TAny* aArgs)
	{
	switch (aOpcode)
		{
	case EDigitalDisplayCommandSetBackgroundColor:
		{
		SDigitalDisplayCommandSetBackgroundColorArgs* digitalDisplayArgs=(SDigitalDisplayCommandSetBackgroundColorArgs*)aArgs;
		if ((iBackgroundColor!=digitalDisplayArgs->iBackgroundColor) || (iShadow.iColor!=digitalDisplayArgs->iShadowColor))
			{
			iBackgroundColor=digitalDisplayArgs->iBackgroundColor;
			iShadow.iColor=digitalDisplayArgs->iShadowColor;
			aFunctions.iWindowFunctions.ActivateGc();
			DrawP(aFunctions.iWindowFunctions, aGc);
			}
		}
		break;
	case EDigitalDisplayCommandSetTextColor:
		{
		SDigitalDisplayCommandSetTextColorArgs* digitalDisplayArgs=(SDigitalDisplayCommandSetTextColorArgs*)aArgs;
		for (TInt i=0; i<iTextSections.iNumTextSections; ++i)
			iTextSections.iTextSections[i]->SetTextColor(digitalDisplayArgs->iTextColor);
//		aFunctions.ActivateGc();
//		DrawP(aFunctions, aGc);
		}
		break;
	default:
		DDisplay::HandleCommandLP(aFunctions, aGc, aTime, aOpcode, aArgs);
		break;
		}
	}

void DDigitalDisplay::DoDrawP(CAnimGc& aGc, TBool, const TRect&) const
	{
	__ASSERT_ALWAYS(iTextSections.iNumTextSectionsAdded==iTextSections.iNumTextSections, PanicClientFromServer());
	TRect rectDrawnTo=RectDrawnTo();
	aGc.SetDrawMode(CGraphicsContext::EDrawModePEN);
	aGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	aGc.SetBrushColor(iBackgroundColor);
	aGc.SetPenStyle(CGraphicsContext::ESolidPen);
	aGc.SetPenColor(iBackgroundColor);
	aGc.DrawRect(rectDrawnTo);
	if (iShadow.iIsOn)
		{
		TRect shadowRect=rectDrawnTo;
		shadowRect.Move(iShadow.iOffset);
		for (TInt i=0; i<iTextSections.iNumTextSections; ++i)
			iTextSections.iTextSections[i]->DrawP(aGc, shadowRect, iFlashStateOn, &iShadow.iColor);
		}
	for (TInt i=0; i<iTextSections.iNumTextSections; ++i)
		iTextSections.iTextSections[i]->DrawP(aGc, rectDrawnTo, iFlashStateOn);
	}

void DDigitalDisplay::UpdateDisplayDataP(MAnimGeneralFunctions& aFunctions, const TTime& aTime, TRegion* aRegion)
	{
	__ASSERT_ALWAYS(iTextSections.iNumTextSectionsAdded==iTextSections.iNumTextSections, PanicClientFromServer());
	TBool flashStateIsChanging=EFalse;
	TBool flashStateOn=aFunctions.FlashStateOn();
	if ((!iFlashStateOn)!=(!flashStateOn)) // "logical-not" both sides before comparing for inequality
		{
		iFlashStateOn=flashStateOn;
		flashStateIsChanging=ETrue;
		}
	TRect rectDrawnTo=RectDrawnTo();
	for (TInt i=0; i<iTextSections.iNumTextSections; ++i)
		iTextSections.iTextSections[i]->UpdateDisplayDataP(rectDrawnTo, iShadow, aTime, flashStateIsChanging, aRegion,iTimeResolutionLimitedToMinutes);
	}

// DAnalogDisplay

DAnalogDisplay::DAnalogDisplay(const TPoint& aPosition, const TSize& aSize, const TMargins& aMargins, const STimeDeviceShadow& aShadow, TInt aNumHands)
	:DDisplay(aPosition, aSize, aMargins, aShadow)
#pragma warning (disable: 4705)
	{
#pragma warning (default: 4705)
	__DECLARE_NAME(_S("DAnalogDisplay"));

	__ASSERT_DEBUG(iFace==NULL, Panic(EClockServerPanicNotInitializedToNULL2));
	__ASSERT_DEBUG(iFaceMask==NULL, Panic(EClockServerPanicNotInitializedToNULL3));
	__ASSERT_ALWAYS((aNumHands>0) && (aNumHands<=KMaxTInt16), PanicClientFromServer());
	iHands.iNumHands=(TInt16)aNumHands;
	__ASSERT_DEBUG(iHands.iNumHandsAdded==0, Panic(EClockServerPanicNotInitializedToNULL4));
	__ASSERT_DEBUG(iHands.iHands==NULL, Panic(EClockServerPanicNotInitializedToZero2));
	__ASSERT_DEBUG(iAmPm==NULL, Panic(EClockServerPanicNotInitializedToNULL5));
	}

void DAnalogDisplay::ConstructL(MAnimGeneralFunctions& aFunctions, TInt aFaceHandle, TInt aFaceMaskHandle)
	{
	iFace=aFunctions.DuplicateBitmapL(aFaceHandle);
	if (aFaceMaskHandle!=0)
		iFaceMask=aFunctions.DuplicateBitmapL(aFaceMaskHandle);
	}

void DAnalogDisplay::AddHandLP(DAnalogDisplayHand* aHand)
	{
	__ASSERT_ALWAYS(iHands.iNumHandsAdded<iHands.iNumHands, PanicClientFromServer());
	if (iHands.iHands==NULL)
		iHands.iHands=new(ELeave) DAnalogDisplayHand*[iHands.iNumHands];

	iHands.iHands[iHands.iNumHandsAdded++]=aHand; // ownership is only taken after everything that can leave has succeeded
	}

void DAnalogDisplay::AddAmPmLP(MAnimGeneralFunctions& aFunctions, const TPoint& aPositionRelativeToFace, const TSize& aSize, const STimeDeviceShadow& aShadow, TRgb aBackgroundColor, TInt aFontHandle, TRgb aTextColor)
	{
	__ASSERT_ALWAYS((iAmPm==NULL) && (iFace!=NULL), PanicClientFromServer());
	iAmPmPositionRelativeToFace=aPositionRelativeToFace;
	TMargins margins;
	margins.iLeft=0;
	margins.iRight=0;
	margins.iTop=0;
	margins.iBottom=0;
	iAmPm=new(ELeave) DAmPmDisplay(AmPmPosition(), aSize, margins, aShadow, aBackgroundColor);
	iAmPm->ConstructLP(aFunctions, aTextColor, aFontHandle);
	}

void DAnalogDisplay::SetInitialTimeP(const TTime& aTime)
	{
	__ASSERT_ALWAYS(iHands.iNumHandsAdded==iHands.iNumHands, PanicClientFromServer());
	if (iAmPm!=NULL)
		iAmPm->SetInitialTimeP(aTime);
	for (TInt i=0; i<iHands.iNumHands; ++i)
		iHands.iHands[i]->SetInitialTimeP(aTime);
	}

DAnalogDisplay::~DAnalogDisplay()
	{
	delete iFace;
	delete iFaceMask;
	delete iAmPm;
	if (iHands.iHands!=NULL)
		{
		for (TInt i=0; i<iHands.iNumHandsAdded; ++i)
			delete iHands.iHands[i];
		delete [] iHands.iHands;
		}
	}

void DAnalogDisplay::PositionOrSizeHasChanged()
	{
	if (iAmPm!=NULL)
		iAmPm->SetPosition(AmPmPosition());
	}

TRect DAnalogDisplay::FaceRect() const
	{
	TRect rectDrawnTo=RectDrawnTo();
	TSize sizeDrawnTo=rectDrawnTo.Size();
	TSize faceSize=iFace->SizeInPixels();
	TPoint facePosition=rectDrawnTo.iTl+TPoint((sizeDrawnTo.iWidth-faceSize.iWidth)/2, (sizeDrawnTo.iHeight-faceSize.iHeight)/2);
	return TRect(facePosition, faceSize);
	}

// Function to stop a the specified hand types from being displayed
void DAnalogDisplay::DisableHands(TBool aHourHand, TBool aMinuteHand, TBool aSecondHand)
	{
	if(aHourHand)
		iHands.iHandsDisabled|=EHourHand;
	if(aMinuteHand)
		iHands.iHandsDisabled|=EMinuteHand;
	if(aSecondHand)
		iHands.iHandsDisabled|=ESecondHand;

	}

// Function to re-enable the displaying of the specified hand types after a call to DisableHands()
void DAnalogDisplay::EnableHands(TBool aHourHand, TBool aMinuteHand, TBool aSecondHand)
	{
	if(aHourHand)
		iHands.iHandsDisabled&= ~EHourHand;
	if(aMinuteHand)
		iHands.iHandsDisabled&= ~EMinuteHand;
	if(aSecondHand)
		iHands.iHandsDisabled&= ~ESecondHand;
	}

void DAnalogDisplay::DoDrawP(CAnimGc& aGc, TBool aFullDrawRequired, const TRect& aClippingRect) const
	{
	__ASSERT_ALWAYS(iHands.iNumHandsAdded==iHands.iNumHands, PanicClientFromServer());
	aGc.SetDrawMode(CGraphicsContext::EDrawModePEN);
	TRect rectDrawnTo=RectDrawnTo();
	TRect rectDrawnToRelativeToFace=rectDrawnTo;
	rectDrawnToRelativeToFace.Move(-FaceRect().iTl);
	if ((iFaceMask!=NULL) && aFullDrawRequired)
		aGc.BitBltMasked(rectDrawnTo.iTl, iFace, rectDrawnToRelativeToFace, iFaceMask, EFalse);
	else
		aGc.BitBlt(rectDrawnTo.iTl, iFace, rectDrawnToRelativeToFace);
	if (iAmPm!=NULL)
		{
		TRect temp=iAmPm->RectDrawnTo();
		if (temp.Intersects(aClippingRect))
			{
			temp.Intersection(aClippingRect);
			aGc.SetClippingRect(temp);
			iAmPm->DoDrawP(aGc, aFullDrawRequired, temp);
			aGc.SetClippingRect(aClippingRect);
			}
		}
	TPoint handCenter=HandCenter();
	if (iShadow.iIsOn)
		{
		TPoint shadowHandCenter=handCenter+iShadow.iOffset;
		DrawHands(aGc, shadowHandCenter, &iShadow.iColor);
		}
	DrawHands(aGc, handCenter);
	}
	
void DAnalogDisplay::DrawHands(CAnimGc& aGc, const TPoint& aCenter,  const TRgb* aShadowColour) const
	{
	for (TInt i=0; i<iHands.iNumHands; ++i)
		{
		// Only draw enabled hands
		if( ((iHands.iHands[i]->Type() == EAnalogDisplayHandOneRevPer12Hours)&&(!(iHands.iHandsDisabled&EHourHand)))
			||((iHands.iHands[i]->Type() == EAnalogDisplayHandOneRevPerHour)&&(!(iHands.iHandsDisabled&EMinuteHand)))
			||((iHands.iHands[i]->Type() == EAnalogDisplayHandOneRevPerMinute)&&(!(iHands.iHandsDisabled&ESecondHand))) )
			{
			iHands.iHands[i]->DrawP(aGc, aCenter, aShadowColour);
			}
		}
	}

void DAnalogDisplay::UpdateDisplayDataP(MAnimGeneralFunctions& aFunctions, const TTime& aTime, TRegion* aRegion)
	{
	__ASSERT_ALWAYS(iHands.iNumHandsAdded==iHands.iNumHands, PanicClientFromServer());
	if (iAmPm)
		iAmPm->UpdateDisplayDataP(aFunctions, aTime, aRegion);
	for (TInt i=0; i<iHands.iNumHands; ++i)
		{
		if( ((iHands.iHands[i]->Type() == EAnalogDisplayHandOneRevPer12Hours)&&(!(iHands.iHandsDisabled&EHourHand)))
			||((iHands.iHands[i]->Type() == EAnalogDisplayHandOneRevPerHour)&&(!(iHands.iHandsDisabled&EMinuteHand)))
			||((iHands.iHands[i]->Type() == EAnalogDisplayHandOneRevPerMinute)&&(!(iHands.iHandsDisabled&ESecondHand))) )
			{
			iHands.iHands[i]->UpdateDisplayDataP(aTime, HandCenter(), iShadow, aRegion);
			}
		else
			{
			// When a hand is Disabled in needs to be cleared immediately, in some circumstances
			// the time will be the same as the last time the hand was drawn and this results
			// in the region not being updated (because no change has occured)
			// We need to force the update by tricking the updtae code into thinking the hand has moved
			// This is done by adding 1 to the time.
			TTime tempTime = aTime+TTimeIntervalSeconds(1);
			iHands.iHands[i]->UpdateDisplayDataP(tempTime, HandCenter(), iShadow, aRegion);
			}
		}
	}

TPoint DAnalogDisplay::HandCenter() const
	{
	return FaceRect().Center();
	}

TPoint DAnalogDisplay::AmPmPosition() const
	{
	return FaceRect().iTl+iAmPmPositionRelativeToFace;
	}

// DAnalogDisplay::DAmPmDisplay

DAnalogDisplay::DAmPmDisplay::DAmPmDisplay(const TPoint& aPosition, const TSize& aSize, const TMargins& aMargins, const STimeDeviceShadow& aShadow, TRgb aBackgroundColor)
	:DDigitalDisplay(aPosition, aSize, aMargins, aShadow, aBackgroundColor, 1)
	{
	}

void DAnalogDisplay::DAmPmDisplay::ConstructLP(MAnimGeneralFunctions& aFunctions, TRgb aTextColor, TInt aFontHandle)
	{
	DDigitalDisplayTextSection* textSection=new(ELeave) DDigitalDisplayTextSection(aFunctions, aTextColor,
																EDigitalDisplayHorizontalTextAlignmentCenter,
																EDigitalDisplayVerticalTextAlignmentCenterExclDescent, 0, 0);
	CleanupStack::PushL(textSection);
	textSection->ConstructL(KFormatText, aFontHandle);
	AddTextSectionLP(textSection);
	CleanupStack::Pop(); // pop off textSection
	}

void DAnalogDisplay::DAmPmDisplay::DoDrawP(CAnimGc& aGc, TBool aFullDrawRequired, const TRect& aClippingRect) const
	{
	DDigitalDisplay::DoDrawP(aGc, aFullDrawRequired, aClippingRect);
	}

void DAnalogDisplay::DAmPmDisplay::UpdateDisplayDataP(MAnimGeneralFunctions& aFunctions, const TTime& aTime, TRegion* aRegion)
	{
	DDigitalDisplay::UpdateDisplayDataP(aFunctions, aTime, aRegion);
	}


void DAnalogDisplay::HandleCommandLP(DAnimWithUtils::TFunctions& aFunctions, CAnimGc& aGc, const TTime& aTime, TInt aOpcode, TAny* aArgs)
	{
	switch (aOpcode)
		{
	case EDigitalDisplayCommandSetBackgroundColor:
	case EDigitalDisplayCommandSetTextColor:
		if (iAmPm)
			iAmPm->HandleCommandLP(aFunctions,aGc,aTime,aOpcode,aArgs);
		break;
	case EAnalogDisplayCommandSetPenColor:
		{
		SAnalogDisplayHandFeaturesPenColorArgs* analogDisplayArgs=(SAnalogDisplayHandFeaturesPenColorArgs*)aArgs;
		for (TInt i=0; i<iHands.iNumHands; ++i)
			iHands.iHands[i]->SetPenColor(analogDisplayArgs->iPenColor);
		}
		break;
	case EAnalogDisplayCommandSetBrushColor:
		{
		SAnalogDisplayHandFeaturesBrushColorArgs* analogDisplayArgs=(SAnalogDisplayHandFeaturesBrushColorArgs*)aArgs;
		for (TInt i=0; i<iHands.iNumHands; ++i)
			iHands.iHands[i]->SetBrushColor(analogDisplayArgs->iBrushColor);
//		iBrushColor=analogDisplayArgs->iBrushColor;
//		aFunctions.ActivateGc();
//		DrawP(aFunctions, aGc);
		}
		break;
	default:
		DDisplay::HandleCommandLP(aFunctions, aGc, aTime, aOpcode, aArgs);
		break;
		}
	}
//!>
