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
// source code for the time-device class and derived classes
// $Workfile:   TIMEDEV.CPP  $
// $Revision:   1.5  $
// $Author:   DougF  $
// $Date:   07 Jul 1999 16:16:18  $
// 
//

#include "CL_STD.H"

_LIT(KFormat1,"%A");
_LIT(KFormat2,"%B");
_LIT(KFormat3,"%H");
_LIT(KFormat4,"%I");
_LIT(KFormat5,"%J");
_LIT(KFormat6,"%T");
_LIT(KFormat7,"%C");
_LIT(KFormat8,"%S");

//  CMinuteTick
CMinuteTick* CMinuteTick::NewL(MObserver& aObserver)
	{
	CMinuteTick* self = new(ELeave)CMinuteTick(aObserver);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}

CMinuteTick::CMinuteTick(MObserver& aObserver) : CTimer(CActive::EPriorityStandard), iObserver(aObserver)
	{
	CActiveScheduler::Add(this);
	}

CMinuteTick::~CMinuteTick()
	{
	}

void CMinuteTick::CalculateTimeAtNextMinute()
	{
	iHomeTimeAtNextMinute.HomeTime();
	// Add a second to make sure we definitely round up
	iHomeTimeAtNextMinute+=TTimeIntervalSeconds(1);
	iHomeTimeAtNextMinute.RoundUpToNextMinute();
	}

void CMinuteTick::ReQueueTimer()
	{
	CalculateTimeAtNextMinute();
	At(iHomeTimeAtNextMinute);
	}

void CMinuteTick::Start()
	{
	// Only start if not already started
	if(!IsActive())
		{
		ReQueueTimer();
		}
	}

void CMinuteTick::Stop()
	{
	Cancel();
	}

void CMinuteTick::RunL()
	{
	if(iStatus.Int() == KErrNone)
		{
		// The observer expects universal time not home time
		// so pass that back
		TTime universalTimeNow;
		universalTimeNow.UniversalTime();
		iObserver.MinuteTickCompleteL(universalTimeNow);
		}
	else if(iStatus.Int() != KErrAbort)
		{
		// Another error has occured assert here to catch it in debug builds
		__ASSERT_DEBUG(EFalse,Panic(EClockServerPanicUnexpectedError));
		return;
		}
	// If the At timer has been aborted - this happens when the system
	// time is changed then we just need to requeue the timer for the 
	// new time
	ReQueueTimer();
	}


// DTimeDevice

DTimeDevice::DTimeDevice() : iFocusChangeCallback(CActive::EPriorityStandard)
	{
	__ASSERT_DEBUG(iDisplay==NULL, Panic(EClockServerPanicNotInitializedToNULL6));
	TCallBack focusChangeCallback(FocusChangeCb,this);
	iFocusChangeCallback.Set(focusChangeCallback);
	}

DTimeDevice::~DTimeDevice()
	{
	TRect rectToInvalidate;
	TBool rectToInvalidateExists=EFalse;

	if (iDisplay!=NULL)
		{
		rectToInvalidate=iDisplay->RectToInvalidate();
		rectToInvalidateExists=ETrue;
		}

	delete iDisplay;

	if (rectToInvalidateExists)
		iWindowFunctions->Invalidate(rectToInvalidate);
	//  Delete CMinuteTick object here
	delete iMinuteTick;

	// Remove ourselves as an event observer
	iFunctions->RegisterForNotifications(0);

	iFocusChangeCallback.Cancel();
	}

void DTimeDevice::ConstructLP(const TUint8* aBytePtr, TBool)
	{
	DoConstructL(aBytePtr);

	MAnimGeneralFunctions::TAnimSync sync=MAnimGeneralFunctions::ESyncNone;
	TDisplayType* displayType=(TDisplayType*)aBytePtr;
	aBytePtr+=sizeof(TDisplayType);
	switch (*displayType)
		{
	case EDisplayDigital:
		{
		SDigitalDisplayConstructorArgs* digitalArgs=(SDigitalDisplayConstructorArgs*)aBytePtr;
		aBytePtr+=sizeof(SDigitalDisplayConstructorArgs);
		TInt numTextSections=digitalArgs->iNumTextSections;
		DDigitalDisplay* digitalDisplay=new(ELeave) DDigitalDisplay(digitalArgs->iPosition, digitalArgs->iSize, digitalArgs->iMargins, digitalArgs->iShadow, digitalArgs->iBackgroundColor, numTextSections);
		CleanupStack::PushL(digitalDisplay);
		iDisplayIsAnalogue = EFalse;
		sync=MAnimGeneralFunctions::ESyncMinute;
		for (TInt i=0; i<numTextSections; ++i)
			{
			SDigitalDisplayTextSectionConstructorArgs* textSectionArgs=(SDigitalDisplayTextSectionConstructorArgs*)aBytePtr;
			aBytePtr+=sizeof(SDigitalDisplayTextSectionConstructorArgs);
			DDigitalDisplayTextSection* textSection=new(ELeave) DDigitalDisplayTextSection(*iFunctions, textSectionArgs->iTextColor,
																textSectionArgs->iHorizontalAlignment, textSectionArgs->iVerticalAlignment,
																textSectionArgs->iHorizontalMargin, textSectionArgs->iVerticalMargin);
			CleanupStack::PushL(textSection);
			TPtrC format=ReadText(aBytePtr, textSectionArgs->iFormatLength);
			HBufC* formatStrippedOfModifiers=format.AllocLC();
			TPtr ptrToformatStrippedOfModifiers=formatStrippedOfModifiers->Des();
			StripOutCharacter(ptrToformatStrippedOfModifiers, '*');
			StripOutCharacter(ptrToformatStrippedOfModifiers, '-');
			StripOutCharacter(ptrToformatStrippedOfModifiers, '+');
			switch (sync)
				{
			case MAnimGeneralFunctions::ESyncNone:
			case MAnimGeneralFunctions::ESyncDay:
				if ((formatStrippedOfModifiers->FindF(KFormat1)!=KErrNotFound) ||
					(formatStrippedOfModifiers->FindF(KFormat2)!=KErrNotFound) ||
					(formatStrippedOfModifiers->FindF(KFormat3)!=KErrNotFound) ||
					(formatStrippedOfModifiers->FindF(KFormat4)!=KErrNotFound) ||
					(formatStrippedOfModifiers->FindF(KFormat5)!=KErrNotFound) ||
					(formatStrippedOfModifiers->FindF(KFormat6)!=KErrNotFound))
					{
					sync=MAnimGeneralFunctions::ESyncMinute;
					}
				// N.B. fall through
			case MAnimGeneralFunctions::ESyncMinute:
				if ((formatStrippedOfModifiers->FindF(KFormat7)!=KErrNotFound) ||
					(formatStrippedOfModifiers->FindF(KFormat8)!=KErrNotFound))
					{
					sync=MAnimGeneralFunctions::ESyncSecond;
					}
				// N.B. fall through
			case MAnimGeneralFunctions::ESyncSecond:
				if (formatStrippedOfModifiers->Locate(TChar(EDigitalDisplayLayoutCharFlashingBlockDelimiter))!=KErrNotFound)
					{
					sync=MAnimGeneralFunctions::ESyncFlash;
					}
				// N.B. fall through
			case MAnimGeneralFunctions::ESyncFlash:
				break;
			default:
				Panic(EClockServerPanicBadSync1);
				break;
				}
			CleanupStack::PopAndDestroy(); // pop and destroy formatStrippedOfModifiers
			textSection->ConstructL(format, textSectionArgs->iFontHandle);
			digitalDisplay->AddTextSectionLP(textSection);
			CleanupStack::Pop(); // pop off textSection
			}

		iDisplay=digitalDisplay;
		CleanupStack::Pop(); // pop off digitalDisplay
		}
		break;
	case EDisplayAnalog:
		{
		SAnalogDisplayConstructorArgs* analogArgs=(SAnalogDisplayConstructorArgs*)aBytePtr;
		aBytePtr+=sizeof(SAnalogDisplayConstructorArgs);
		TInt numHands=analogArgs->iNumHands;
		DAnalogDisplay* analogDisplay=new(ELeave) DAnalogDisplay(analogArgs->iPosition, analogArgs->iSize, analogArgs->iMargins, analogArgs->iShadow, numHands);
		CleanupStack::PushL(analogDisplay);
		analogDisplay->ConstructL(*iFunctions, analogArgs->iFaceHandle, analogArgs->iFaceMaskHandle);
		iDisplayIsAnalogue = ETrue;

		if (analogArgs->iHasAmPm)
			{
			SAnalogDisplayAmPm* dateArgs=(SAnalogDisplayAmPm*)aBytePtr;
			aBytePtr+=sizeof(SAnalogDisplayAmPm);
			analogDisplay->AddAmPmLP(*iFunctions, dateArgs->iPositionRelativeToFace, dateArgs->iSize,
										dateArgs->iShadow, dateArgs->iBackgroundColor, dateArgs->iFontHandle, dateArgs->iTextColor);
			}

		sync=MAnimGeneralFunctions::ESyncMinute;
		for (TInt i=0; i<numHands; ++i)
			{
			SAnalogDisplayHandConstructorArgs* handArgs=(SAnalogDisplayHandConstructorArgs*)aBytePtr;
			aBytePtr+=sizeof(SAnalogDisplayHandConstructorArgs);
			TInt numHandFeatures=handArgs->iNumFeatures;
			TAnalogDisplayHandType handType=handArgs->iType;
			switch (sync)
				{
			case MAnimGeneralFunctions::ESyncNone:
			case MAnimGeneralFunctions::ESyncDay:
			case MAnimGeneralFunctions::ESyncMinute:
				if (handType==EAnalogDisplayHandOneRevPerMinute)
					sync=MAnimGeneralFunctions::ESyncSecond;
				// N.B. fall through
			case MAnimGeneralFunctions::ESyncSecond:
				break;
			case MAnimGeneralFunctions::ESyncFlash:
			default:
				Panic(EClockServerPanicBadSync2);
				break;
				}
			DAnalogDisplayHand* hand=new(ELeave) DAnalogDisplayHand(handType, numHandFeatures);
			CleanupStack::PushL(hand);
			for (TInt j=0; j<numHandFeatures; ++j)
				{
				TAnalogDisplayHandFeatureType* featureType=(TAnalogDisplayHandFeatureType*)aBytePtr;
				aBytePtr+=sizeof(TAnalogDisplayHandFeatureType);
				DAnalogDisplayHandFeature* feature=NULL; // dummy initialization to prevent compiler warning
				switch (*featureType)
					{
				case EAnalogDisplayHandFeatureLine:
					{
					SAnalogDisplayHandLineConstructorArgs* lineArgs=(SAnalogDisplayHandLineConstructorArgs*)aBytePtr;
					aBytePtr+=sizeof(SAnalogDisplayHandLineConstructorArgs);
					DAnalogDisplayHandLine* line=new(ELeave) DAnalogDisplayHandLine(lineArgs->iPenStyle, lineArgs->iPenColor,
																lineArgs->iPenSize, lineArgs->iStartPoint, lineArgs->iEndPoint);
					feature=line;
					}
					break;
				case EAnalogDisplayHandFeaturePolyLine:
					{
					SAnalogDisplayHandPolyLineConstructorArgs* polyLineArgs=(SAnalogDisplayHandPolyLineConstructorArgs*)aBytePtr;
					aBytePtr+=sizeof(SAnalogDisplayHandPolyLineConstructorArgs);
					TInt numPoints=polyLineArgs->iNumPoints;
					DAnalogDisplayHandPolyLine* polyLine=new(ELeave) DAnalogDisplayHandPolyLine(polyLineArgs->iPenStyle,
																polyLineArgs->iPenColor, polyLineArgs->iPenSize, polyLineArgs->iBrushStyle,
																polyLineArgs->iBrushColor, polyLineArgs->iClosed, numPoints);
					CleanupStack::PushL(polyLine);
					for (TInt k=0; k<numPoints; ++k)
						{
						TPoint* point=(TPoint*)aBytePtr;
						aBytePtr+=sizeof(TPoint);
						polyLine->AddPointLP(*point);
						}
					feature=polyLine;
					CleanupStack::Pop(); // pop off polyLine
					}
					break;
				case EAnalogDisplayHandFeatureCircle:
					{
					SAnalogDisplayHandCircleConstructorArgs* circleArgs=(SAnalogDisplayHandCircleConstructorArgs*)aBytePtr;
					aBytePtr+=sizeof(SAnalogDisplayHandCircleConstructorArgs);
					DAnalogDisplayHandCircle* circle=new(ELeave) DAnalogDisplayHandCircle(circleArgs->iPenStyle, circleArgs->iPenColor,
																circleArgs->iPenSize, circleArgs->iBrushStyle, circleArgs->iBrushColor,
																circleArgs->iCircleCenter, circleArgs->iRadius);
					feature=circle;
					}
					break;
				default:
					PanicClientFromServer();
					break;
					}

				CleanupStack::PushL(feature);
				hand->AddFeatureLP(feature);
				CleanupStack::Pop(); // pop off feature
				}

			analogDisplay->AddHandLP(hand);
			CleanupStack::Pop(); // pop off hand
			}

		iDisplay=analogDisplay;
		CleanupStack::Pop(); // pop off analogDisplay
		}
		break;
	default:
		PanicClientFromServer();
		break;
		}

	switch (sync)
		{
	case MAnimGeneralFunctions::ESyncFlash:
	case MAnimGeneralFunctions::ESyncSecond:
		iSecondsPerUpdate=1;
		break;
	case MAnimGeneralFunctions::ESyncMinute:
		iSecondsPerUpdate=60;
		break;
	case MAnimGeneralFunctions::ESyncDay:
		iSecondsPerUpdate=60*60*24;
		break;
	case MAnimGeneralFunctions::ESyncNone:
	default:
		Panic(EClockServerPanicBadSync3);
		}
	iFunctions->SetSync(sync);
	iWindowFunctions->SetRect(iDisplay->RectToInvalidate());
	iUniversalTime=TTime(iFunctions->SystemTime());
	iDisplay->SetInitialTimeP(Time());

	//  Create CMinuteTick object here
	iMinuteTick = CMinuteTick::NewL(*this);
	
	// Add ourselves as an event observer
	iFunctions->RegisterForNotifications(EHeartbeatTimer);
	// Assume that initially the wserv tick is not enabled. This will be corrected later in AnimateP if incorrect
	iAnimatingOnMinTick = ETrue;
	// Start the minute tick if conditions are correct
	SwitchToMinuteTickIfNecessaryL();
	

	__ASSERT_ALWAYS(*(TInt*)aBytePtr==KCheckValueForEndOfTimeDeviceConstructionBuf, Panic(EClockServerPanicBadEndOfConstructionBuf));
	}

TInt DTimeDevice::CommandReplyLP(TInt aOpcode, TAny* aArgs)
	{
	if (aOpcode&EDisplayCommand)
		{
		if(aOpcode==EDisplayCommandSetVisible)
			{
			SDisplayCommandSetVisibleArgs* displayArgs=static_cast<SDisplayCommandSetVisibleArgs*>(aArgs);
			if (iVisible!=displayArgs->iVisible)
				{
				iVisible=displayArgs->iVisible;
				// The visibility of the clock has changed make sure the minute tick is in the
				// appropriate state for the current visibility
				SwitchToMinuteTickIfNecessaryL();
				}
			}
		TFunctions functions(*iFunctions,*iWindowFunctions);
		iDisplay->HandleCommandLP(functions, *iGc, Time(), aOpcode, aArgs);
		}
	else
		return DAnimWithUtils::CommandReplyLP(aOpcode, aArgs);
	return KErrNone;
	}

void DTimeDevice::CommandP(TInt aOpcode, TAny* aArgs)
	{
	DAnimWithUtils::CommandP(aOpcode, aArgs);
	}

void DTimeDevice::AnimateP(TDateTime* aDateTime)
	{
	// The wserv heartbeat is operational
	if(iAnimatingOnMinTick)
		{
		// Stop animating on the minute tick	
		iAnimatingOnMinTick = EFalse;
		// Stop the minute tick
		iMinuteTick->Stop();
		if(iDisplayIsAnalogue) // Only for analogue display
			{
			// Enable the second hand
			((DAnalogDisplay*)iDisplay)->EnableHands(/*hours*/ETrue, /*mins*/ETrue, /*secs*/ETrue);		
			}
		else
			{
			//Enable seconds in digital clock
			((DDigitalDisplay*)iDisplay)->LimitTimeResolutionToMinutes(EFalse);
			}
		} 
		
	if (aDateTime!=NULL)
		iUniversalTime=TTime(*aDateTime);
	else if ((iFunctions->Sync()!=MAnimGeneralFunctions::ESyncFlash) || (iFunctions->FlashStateOn()))
		iUniversalTime+=iSecondsPerUpdate;
	DoAnimateP();
	}

void DTimeDevice::DoAnimateP()
	{
	TFunctions functions(*iFunctions,*iWindowFunctions);
	iDisplay->UpdateLP(functions, *iGc, Time());
	}

//  Minute Tick callback function here
void DTimeDevice::MinuteTickCompleteL(const TTime& aNewUniversalTime)
	{
	if(iAnimatingOnMinTick)
		{
		iUniversalTime = aNewUniversalTime;
		DoAnimateP();
		CompleteAnimation();
		}
	}
void DTimeDevice::CompleteAnimation()
	{
	// Do stuff which window server does when it finishes animating us
	WindowFunctions()->DeactivateGc();
#if defined(__WINS__)
	WindowFunctions()->Update();
#endif
	}

void DTimeDevice::HandleNotification(const TWsEvent& aEvent)
	{
	if(aEvent.Type() == EEventHeartbeatTimerStateChange)
		{
		TBool started = *(aEvent.Int());
		if(started)
			{
			// Heartbeat timer started
			// Indicate we should not animate on the minute tick
			iAnimatingOnMinTick = EFalse;
			// Stop the minute tick
			iMinuteTick->Stop();
			if(iDisplayIsAnalogue) // Only for analogue display
				{
				// Enable the second hand
				((DAnalogDisplay*)iDisplay)->EnableHands(/*hours*/ETrue, /*mins*/ETrue, /*secs*/ETrue);		
				}
			else
				{
				//Enable seconds in digital clock
				((DDigitalDisplay*)iDisplay)->LimitTimeResolutionToMinutes(EFalse);
				}
			}
		else // stopped
			{
			// Heartbeat timer stopped
			// Indicate we should animate on the minute tick
			iAnimatingOnMinTick = ETrue;
			// Start the minute tick if conditions are correct
			SwitchToMinuteTickIfNecessaryL();
			}
		}
	}
	
void DTimeDevice::SwitchToMinuteTickIfNecessaryL()
	{
	if(iAnimatingOnMinTick && iVisible)
		{
		// The clock should be animating on the minute tick and visible
		// Check that the minute tick is not active
		if(!iMinuteTick->IsActive())
			{
			// The minute tick has not been started so start and update display
			// Start the minute tick
			iMinuteTick->Start();
			// Update time
			iUniversalTime=TTime(iFunctions->SystemTime());
			// Update display
			if(iDisplayIsAnalogue) // Only for analogue display
				{
				// Disable the second hand
				((DAnalogDisplay*)iDisplay)->DisableHands(/*hours*/EFalse, /*mins*/EFalse, /*secs*/ETrue);	
				}
			else
				{
				//Remove seconds from digital clock
				((DDigitalDisplay*)iDisplay)->LimitTimeResolutionToMinutes(ETrue);
				}
			DoAnimateP();
			CompleteAnimation();
			}
		}
	else
		{
		// Conditions are not yet right for animating on minute tick
		// make sure tick is Disabled
		iMinuteTick->Stop();
		}
	}

void DTimeDevice::FocusChanged(TBool /*aState*/)
	{
	if(!iFocusChangeCallback.IsActive())
 		{
		iFocusChangeCallback.Call();
 		}
	}

void DTimeDevice::RedrawP()
	{
	iDisplay->DrawP(*iWindowFunctions, *iGc);
	}

TTime DTimeDevice::Time() const
	{
	return TimeGivenUniversalTime(iUniversalTime);
	}

void DTimeDevice::StripOutCharacter(TDes& aText, TChar aCharacter)
	{
	for (TInt positionOfCharacter=aText.Locate(aCharacter); positionOfCharacter!=KErrNotFound; positionOfCharacter=aText.Locate(aCharacter))
		{
		aText.Delete(positionOfCharacter,1);
		}
	}

TInt DTimeDevice::FocusChangeCb(TAny* aThisPtr)
	{
	DTimeDevice* self = (DTimeDevice*)aThisPtr;
	self->SwitchToMinuteTickIfNecessaryL();

	return KErrNone;
	}

// DClock

DClock::DClock()
	{
	__DECLARE_NAME(_S("DClock"));
	}

TInt DClock::CommandReplyLP(TInt aOpcode, TAny* aArgs)
	{
	switch (aOpcode)
		{
	case EClockCommandSetUniversalTimeOffset:
		{
		SClockCommandSetUniversalTimeOffsetArgs* clockArgs=(SClockCommandSetUniversalTimeOffsetArgs*)aArgs;
		if (iUniversalTimeOffset!=clockArgs->iUniversalTimeOffset)
			{
			TFunctions functions(*iFunctions,*iWindowFunctions);
			iUniversalTimeOffset=clockArgs->iUniversalTimeOffset;
			iDisplay->UpdateLP(functions, *iGc, Time());
			}
		}
		return KErrNone;
	default:
		return DTimeDevice::CommandReplyLP(aOpcode, aArgs);
		}
	}

void DClock::DoConstructL(const TUint8*& aBytePtr)
	{
	SClockConstructorArgs* clockArgs=(SClockConstructorArgs*)aBytePtr;
	iUniversalTimeOffset=clockArgs->iUniversalTimeOffset;
	aBytePtr+=sizeof(SClockConstructorArgs);
	}

TTime DClock::TimeGivenUniversalTime(const TTime& aUniversalTime) const
	{
	return aUniversalTime+iUniversalTimeOffset;
	}

