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

// global and local functions


LOCAL_C void Panic(TClockClientPanic aPanic)
	{
	_LIT(KPanicClockClient,"Clock-client");
	User::Panic(KPanicClockClient, aPanic);
	}

LOCAL_C void AppendTextToBuf(TConstructorBuf8& aBuf, const TDesC& aText)
	{
	TInt textSize=aText.Size(); // N.B. this is different from calling Length() as Size() returns size in bytes regardless of UNICODE or not
	aBuf.Append(TPtrC8((TUint8*)aText.Ptr(), textSize));
	TInt numExtraBytesfor4byteAlign=Align4(textSize)-textSize;
	TUint8 extraBytes[4];
	extraBytes[0]=0;
	extraBytes[1]=0;
	extraBytes[2]=0;
	extraBytes[3]=0;
	aBuf.Append(&extraBytes[0], numExtraBytesfor4byteAlign);
	}

// TDisplayAddition

const TDesC8& TDisplayAddition::Buf() const
	{
	return iBuf;
	}

// TDigitalDisplayTextSection

EXPORT_C TDigitalDisplayTextSection::TDigitalDisplayTextSection(TInt aFontHandle, TRgb aTextColor, TDigitalDisplayHorizontalTextAlignment aHorizontalAlignment,
																TDigitalDisplayVerticalTextAlignment aVerticalAlignment,
																TInt aHorizontalMargin, TInt aVerticalMargin, const TDesC& aFormat)
/** Constructs a text section for a digital clock.

@param aFontHandle A handle to the font to use. This can be obtained with 
CFbsFont::Handle(). This font cannot be destroyed until the RDigitalClock 
has been completely constructed, including all necessary calls to RDigitalClock::AddTextSectionL().
@param aTextColor Text colour
@param aHorizontalAlignment Horizontal alignment
@param aVerticalAlignment Vertical alignment
@param aHorizontalMargin Horizontal margin
@param aVerticalMargin Vertical margin
@param aFormat A formatting string for the time. The allowed characters for 
this are as for TTime::FormatL(), plus those in TDigitalDisplayLayoutChar.
@see TDigitalDisplayLayoutChar
@see TTime::FormatL() */
	{
	TPckgBuf<SDigitalDisplayTextSectionConstructorArgs> textSectionArgs;
	textSectionArgs().iFontHandle=aFontHandle;
	textSectionArgs().iTextColor=aTextColor;
	textSectionArgs().iHorizontalAlignment=aHorizontalAlignment;
	textSectionArgs().iVerticalAlignment=aVerticalAlignment;
	textSectionArgs().iHorizontalMargin=aHorizontalMargin;
	textSectionArgs().iVerticalMargin=aVerticalMargin;
	textSectionArgs().iFormatLength=aFormat.Length();
	iBuf.Append(textSectionArgs);
	AppendTextToBuf(iBuf, aFormat);
	}

// TAnalogDisplayHand

EXPORT_C TAnalogDisplayHand::TAnalogDisplayHand(TAnalogDisplayHandType aType)
/** Constructs a hand for an analogue clock.

@param aType Type of hand */
	{
	TPckgBuf<SAnalogDisplayHandConstructorArgs> handArgs;
	handArgs().iType=aType;
	handArgs().iNumFeatures=0; // this is set to its proper value later in Complete()
	TInt numFeaturesIndex=iBuf.Length()+_FOFF(SAnalogDisplayHandConstructorArgs, iNumFeatures);
	iBuf.Append(handArgs);
	iNumFeaturesPtr=(TInt*)&iBuf[numFeaturesIndex];
	}

EXPORT_C void TAnalogDisplayHand::AddLine(CGraphicsContext::TPenStyle aPenStyle, TRgb aPenColor, const TSize& aPenSize,
																const TPoint& aStartPoint, const TPoint& aEndPoint)
/** Adds a line to the hand.

@param aPenStyle The pen style
@param aPenColor The pen colour
@param aPenSize The pen size
@param aStartPoint The start point for the line
@param aEndPoint The end point for the line */
	{
	AppendType(EAnalogDisplayHandFeatureLine);

	TPckgBuf<SAnalogDisplayHandLineConstructorArgs> lineArgs;
	lineArgs().iPenStyle=aPenStyle;
	lineArgs().iPenColor=aPenColor;
	lineArgs().iPenSize=aPenSize;
	lineArgs().iStartPoint=aStartPoint;
	lineArgs().iEndPoint=aEndPoint;
	iBuf.Append(lineArgs);
	}

EXPORT_C void TAnalogDisplayHand::AddPolyLine(CGraphicsContext::TPenStyle aPenStyle, TRgb aPenColor, const TSize& aPenSize,
																CGraphicsContext::TBrushStyle aBrushStyle, TRgb aBrushColor,
																TBool aClosed, const CArrayFix<TPoint>* aPointList)
/** Adds a polyline to the hand.

@param aPenStyle The pen style
@param aPenColor The pen colour
@param aPenSize The pen size
@param aBrushStyle The brush style
@param aBrushColor The brush colour
@param aClosed True if the polyline forms a closed shape, else false
@param aPointList An array of points for the polyline. The class does not delete 
aPointList. */
	{
	TInt numPoints=aPointList->Count();

	AppendType(EAnalogDisplayHandFeaturePolyLine);

	TPckgBuf<SAnalogDisplayHandPolyLineConstructorArgs> polyLineArgs;
	polyLineArgs().iPenStyle=aPenStyle;
	polyLineArgs().iPenColor=aPenColor;
	polyLineArgs().iPenSize=aPenSize;
	polyLineArgs().iBrushStyle=aBrushStyle;
	polyLineArgs().iBrushColor=aBrushColor;
	polyLineArgs().iClosed=aClosed;
	polyLineArgs().iNumPoints=numPoints;
	iBuf.Append(polyLineArgs);

	for (TInt i=0; i<numPoints; ++i)
		{
		TPckgBuf<TPoint> point;
		point()=(*aPointList)[i];
		iBuf.Append(point);
		}
	}

EXPORT_C void TAnalogDisplayHand::AddCircle(CGraphicsContext::TPenStyle aPenStyle, TRgb aPenColor, const TSize& aPenSize,
																CGraphicsContext::TBrushStyle aBrushStyle, TRgb aBrushColor,
																const TPoint& aCircleCenter, TInt aRadius)
/** Adds a circle to the hand.

@param aPenStyle The pen style
@param aPenColor The pen colour
@param aPenSize The pen size
@param aBrushStyle The brush style
@param aBrushColor The brush colour
@param aCircleCenter The centre of the circle
@param aRadius The radius of the circle */
	{
	AppendType(EAnalogDisplayHandFeatureCircle);

	TPckgBuf<SAnalogDisplayHandCircleConstructorArgs> circleArgs;
	circleArgs().iPenStyle=aPenStyle;
	circleArgs().iPenColor=aPenColor;
	circleArgs().iPenSize=aPenSize;
	circleArgs().iBrushStyle=aBrushStyle;
	circleArgs().iBrushColor=aBrushColor;
	circleArgs().iCircleCenter=aCircleCenter;
	circleArgs().iRadius=aRadius;
	iBuf.Append(circleArgs);
	}

void TAnalogDisplayHand::AppendType(TAnalogDisplayHandFeatureType aType)
	{
	++*iNumFeaturesPtr;

	TPckgBuf<TAnalogDisplayHandFeatureType> featureType;
	featureType()=aType;
	iBuf.Append(featureType);
	}

// RAnimWithUtils

RAnimWithUtils::RAnimWithUtils(RAnimDll& aAnimDll, const RWindowBase& aWindow)
	:RAnim(aAnimDll),
	 iConstructorBuf(NULL),
	 iConstructorBufAlreadySent(EFalse),
	 iWindow(aWindow),
	 iNumAdditionsStillExpected(0)
	{
	}

void RAnimWithUtils::AppendToConstructorBufL(const TDesC8& aData)
	{
	__ASSERT_ALWAYS(!iConstructorBufAlreadySent, Panic(EClockClientPanicAlreadyConstructed));

	if (iConstructorBuf==NULL)
		iConstructorBuf=new(ELeave) TConstructorBuf8;

	iConstructorBuf->Append(aData);
	}

void RAnimWithUtils::SendConstructorBufIfCompleteL(TInt aAnimatedObjectType)
	{
	--iNumAdditionsStillExpected;
	__ASSERT_ALWAYS(iNumAdditionsStillExpected>=0, Panic(EClockClientPanicIncorrectNumberOfAdditions1));
	if (iNumAdditionsStillExpected==0)
		SendConstructorBufL(aAnimatedObjectType);
	}

void RAnimWithUtils::SendConstructorBufL(TInt aAnimatedObjectType)
	{
	__ASSERT_ALWAYS(iNumAdditionsStillExpected==0, Panic(EClockClientPanicIncorrectNumberOfAdditions2));

	TPckgBuf<TInt> checkValue;
	checkValue()=KCheckValueForEndOfTimeDeviceConstructionBuf;
	AppendToConstructorBufL(checkValue);

	TIpcArgs ipcArgs;
	ipcArgs.Set(KIpcSlot, iConstructorBuf);
	User::LeaveIfError(Construct(iWindow, aAnimatedObjectType, KNullDesC8, ipcArgs));
	delete iConstructorBuf;
	iConstructorBuf=NULL;
	iConstructorBufAlreadySent=ETrue;
	}

TBool RAnimWithUtils::ConstructorBufExists() const
	{
	return (iConstructorBuf!=NULL);
	}

TBool RAnimWithUtils::ConstructorBufAlreadySent() const
	{
	return iConstructorBufAlreadySent;
	}

TConstructorBuf8& RAnimWithUtils::ConstructorBuf() const
	{
	__ASSERT_ALWAYS((iConstructorBuf!=NULL), Panic(EClockClientPanicNoConstructorBuf));
	return *iConstructorBuf;
	}

void RAnimWithUtils::SetNumAdditionsStillExpected(TInt aNumAdditionsStillExpected)
	{
	__ASSERT_ALWAYS((iNumAdditionsStillExpected==0) && !iConstructorBufAlreadySent, Panic(EClockClientPanicBadSetNumAdditionsStillExpectedCall));
	iNumAdditionsStillExpected=aNumAdditionsStillExpected;
	}

EXPORT_C void RAnimWithUtils::Close()
/** Closes the clock animation. */
	{
	delete iConstructorBuf;
	iConstructorBuf=NULL;
	RAnim::Close();
	}

// RTimeDevice

RTimeDevice::RTimeDevice(RAnimDll& aAnimDll, const RWindowBase& aWindow)
	:RAnimWithUtils(aAnimDll, aWindow)
	{
	}

void RTimeDevice::AppendDisplayTypeL(TDisplayType aType)
	{
	TPckgBuf<TDisplayType> displayType;
	displayType()=aType;
	AppendToConstructorBufL(displayType);
	}

void RTimeDevice::AppendDigitalDisplayConstructorArgsL(const TPoint& aPosition, const TSize& aSize, const TMargins& aMargins, const STimeDeviceShadow& aShadow,
																TRgb aBackgroundColor, TInt aNumTextSections)
	{
	AppendDisplayTypeL(EDisplayDigital);

	__ASSERT_ALWAYS(aNumTextSections>0, Panic(EClockClientPanicTooFewTextSections));
	TPckgBuf<SDigitalDisplayConstructorArgs> digitalDisplayArgs;
	digitalDisplayArgs().iPosition=aPosition;
	digitalDisplayArgs().iSize=aSize;
	digitalDisplayArgs().iMargins=aMargins;
	digitalDisplayArgs().iShadow=aShadow;
	digitalDisplayArgs().iBackgroundColor=aBackgroundColor;
	digitalDisplayArgs().iNumTextSections=aNumTextSections;
	AppendToConstructorBufL(digitalDisplayArgs);

	SetNumAdditionsStillExpected(aNumTextSections);
	}

void RTimeDevice::AppendAnalogDisplayConstructorArgsL(const TPoint& aPosition, const TSize& aSize, const TMargins& aMargins, const STimeDeviceShadow& aShadow,
																TInt aFaceHandle, TInt aFaceMaskHandle, TInt aNumHands, const SAnalogDisplayAmPm* aAmPm)
	{
	AppendDisplayTypeL(EDisplayAnalog);

	__ASSERT_ALWAYS(aNumHands>0, Panic(EClockClientPanicTooFewHands));
	TPckgBuf<SAnalogDisplayConstructorArgs> analogDisplayArgs;
	analogDisplayArgs().iPosition=aPosition;
	analogDisplayArgs().iSize=aSize;
	analogDisplayArgs().iMargins=aMargins;
	analogDisplayArgs().iShadow=aShadow;
	analogDisplayArgs().iFaceHandle=aFaceHandle;
	analogDisplayArgs().iFaceMaskHandle=aFaceMaskHandle;
	analogDisplayArgs().iNumHands=aNumHands;
	analogDisplayArgs().iHasAmPm=(aAmPm!=NULL);
	AppendToConstructorBufL(analogDisplayArgs);

	if (aAmPm!=NULL)
		{
		TPckgBuf<SAnalogDisplayAmPm> amPmArgs;
		amPmArgs()=*aAmPm;
		AppendToConstructorBufL(amPmArgs);
		}

	SetNumAdditionsStillExpected(aNumHands);
	}

EXPORT_C void RTimeDevice::SetVisible(TBool aVisible)
/** Makes the clock visible. By default, clocks are invisible.

This function can only be called after full construction of the clock.

@param aVisible ETrue makes the clock visible, EFalse invisible */
	{
	__ASSERT_ALWAYS(ConstructorBufAlreadySent(), Panic(EClockClientPanicNotYetFullyConstructed1));
	TPckgBuf<SDisplayCommandSetVisibleArgs> args;
	args().iVisible=aVisible;
	TInt error=CommandReply(EDisplayCommandSetVisible, args);
	__ASSERT_ALWAYS(error==KErrNone, Panic(EClockClientPanicUnexpectedError1));
	}

EXPORT_C void RTimeDevice::SetPositionAndSize(const TPoint& aPosition, const TSize& aSize)
/** Sets the clock's on-screen position and size.

This function can only be called after full construction of the clock.

@param aPosition Clock co-ordinates
@param aSize Clock size */
	{
	__ASSERT_ALWAYS(ConstructorBufAlreadySent(), Panic(EClockClientPanicNotYetFullyConstructed2));
	TPckgBuf<SDisplayCommandSetPositionAndSizeArgs> args;
	args().iPosition=aPosition;
	args().iSize=aSize;
	TInt error=CommandReply(EDisplayCommandSetPositionAndSize, args);
	__ASSERT_ALWAYS(error==KErrNone, Panic(EClockClientPanicUnexpectedError2));
	}

EXPORT_C void RTimeDevice::SetPosition(const TPoint& aPosition)
/** Sets the clock's on-screen position.

This function can only be called after full construction of the clock.

@param aPosition Clock co-ordinates */
	{
	__ASSERT_ALWAYS(ConstructorBufAlreadySent(), Panic(EClockClientPanicNotYetFullyConstructed3));
	TPckgBuf<SDisplayCommandSetPositionArgs> args;
	args().iPosition=aPosition;
	TInt error=CommandReply(EDisplayCommandSetPosition, args);
	__ASSERT_ALWAYS(error==KErrNone, Panic(EClockClientPanicUnexpectedError3));
	}

EXPORT_C void RTimeDevice::SetSize(const TSize& aSize)
/** Sets the clock's on-screen size.

This function can only be called after full construction of the clock.

@param aSize Clock size */
	{
	__ASSERT_ALWAYS(ConstructorBufAlreadySent(), Panic(EClockClientPanicNotYetFullyConstructed4));
	TPckgBuf<SDisplayCommandSetSizeArgs> args;
	args().iSize=aSize;
	TInt error=CommandReply(EDisplayCommandSetSize, args);
	__ASSERT_ALWAYS(error==KErrNone, Panic(EClockClientPanicUnexpectedError4));
	}

EXPORT_C void RTimeDevice::UpdateDisplay()
/** Forces an update to the clock's display.

This function can only be called after full construction of the clock. */
	{
	__ASSERT_ALWAYS(ConstructorBufAlreadySent(), Panic(EClockClientPanicNotYetFullyConstructed5));
	TInt error=CommandReply(EDisplayCommandUpdateDisplay);
	__ASSERT_ALWAYS(error==KErrNone, Panic(EClockClientPanicUnexpectedError5));
	}

EXPORT_C void RTimeDevice::Draw()
/** Draws the clock. */
	{
	__ASSERT_ALWAYS(ConstructorBufAlreadySent(), Panic(EClockClientPanicNotYetFullyConstructed6));
	TInt error=CommandReply(EDisplayCommandDraw);
	__ASSERT_ALWAYS(error==KErrNone, Panic(EClockClientPanicUnexpectedError6));
	}

// RClock

RClock::RClock(RAnimDll& aAnimDll, const RWindowBase& aWindow)
	:RTimeDevice(aAnimDll, aWindow)
	{
	}

void RClock::AppendClockConstructorArgsL(TTimeIntervalSeconds aUniversalTimeOffset)
	{
	TPckgBuf<SClockConstructorArgs> clockConstructorArgs;
	clockConstructorArgs().iUniversalTimeOffset=aUniversalTimeOffset;
	AppendToConstructorBufL(clockConstructorArgs);
	}

EXPORT_C void RClock::SetUniversalTimeOffset(TTimeIntervalSeconds aUniversalTimeOffset)
/** Adjusts the clock's time.

@param aUniversalTimeOffset The time to which to set the clock, expressed 
as an offset from universal time.

@publishedAll
@released*/
	{
	__ASSERT_ALWAYS(ConstructorBufAlreadySent(), Panic(EClockClientPanicNotYetFullyConstructed7));
	TPckgBuf<SClockCommandSetUniversalTimeOffsetArgs> args;
	args().iUniversalTimeOffset=aUniversalTimeOffset;
	TInt error=CommandReply(EClockCommandSetUniversalTimeOffset, args);
	__ASSERT_ALWAYS(error==KErrNone, Panic(EClockClientPanicUnexpectedError7));
	}

// RDigitalClock

EXPORT_C RDigitalClock::RDigitalClock(RAnimDll& aAnimDll, const RWindowBase& aWindow)
	:RClock(aAnimDll, aWindow)
/** Creates a digital clock object.

To complete construction, you must call ConstructL().

@param aAnimDll This RAnimDll must have been loaded with the server-side clock 
animation DLL, clocka.dll
@param aWindow Window to which to add the clock */
	{
	}

EXPORT_C void RDigitalClock::ConstructL(TTimeIntervalSeconds aUniversalTimeOffset, const TPoint& aPosition, const TSize& aSize, const TMargins& aMargins,
																const STimeDeviceShadow& aShadow, TRgb aBackgroundColor, TInt aNumTextSections)
/** Completes construction of a digital clock.

@param aUniversalTimeOffset Initial time for the clock, expressed as an offset 
from universal time
@param aPosition Clock's on-screen position
@param aSize Clock's on-screen size
@param aMargins Margin settings
@param aShadow Shadow settings
@param aBackgroundColor Background color
@param aNumTextSections Number of text sections */
	{
	__ASSERT_ALWAYS(!ConstructorBufExists(), Panic(EClockClientPanicAlreadyConstructedDigitalClock));
	__ASSERT_ALWAYS((aSize.iWidth>=0) && (aSize.iHeight>=0), Panic(EClockClientPanicRectIsNotNormalized));
	AppendClockConstructorArgsL(aUniversalTimeOffset);
	AppendDigitalDisplayConstructorArgsL(aPosition, aSize, aMargins, aShadow, aBackgroundColor, aNumTextSections);
	}

EXPORT_C void RDigitalClock::AddTextSectionL(const TDigitalDisplayTextSection& aTextSection)
/** Adds a text section to the clock.

This function can only be called after full construction of the clock.

@param aTextSection Describes text section to add */
	{
	__ASSERT_ALWAYS(ConstructorBufExists(), Panic(EClockClientPanicNotYetConstructedDigitalClock));
	TInt lengthOfConstructorBufBeforeTextSectionIsAdded=ConstructorBuf().Length();
	AppendToConstructorBufL(aTextSection.Buf());
	const SDigitalDisplayTextSectionConstructorArgs* textSectionConstructorArgs=(const SDigitalDisplayTextSectionConstructorArgs*)(ConstructorBuf().Ptr()+lengthOfConstructorBufBeforeTextSectionIsAdded);
	TPtrC format((const TText*)(textSectionConstructorArgs+1), textSectionConstructorArgs->iFormatLength);
	HBufC* formatWithoutFlashingBlockDelimiter=format.AllocLC();
	TPtr ptr=formatWithoutFlashingBlockDelimiter->Des();
	for (TInt positionOfFlashingBlockDelimiter=ptr.Locate(EDigitalDisplayLayoutCharFlashingBlockDelimiter); positionOfFlashingBlockDelimiter!=KErrNotFound; positionOfFlashingBlockDelimiter=ptr.Locate(EDigitalDisplayLayoutCharFlashingBlockDelimiter))
		ptr.Delete(positionOfFlashingBlockDelimiter, 1);
	TTime time;
	TBuf<128> notUsed;
	TRAPD(error, time.FormatL(notUsed, *formatWithoutFlashingBlockDelimiter));
	CleanupStack::PopAndDestroy();
	if ((error!=KErrNone) && (error!=KErrOverflow))
		User::Leave(error);
	SendConstructorBufIfCompleteL(EAnimClock);
	}

EXPORT_C void RDigitalClock::SetBackgroundColor(TRgb aBackgroundColor, TRgb aShadowColor)
/** Sets the background colour for the clock.

This function can only be called after full construction of the clock.

@param aBackgroundColor Background colour
@param aShadowColor Shadow colour */
	{
	__ASSERT_ALWAYS(ConstructorBufAlreadySent(), Panic(EClockClientPanicNotYetFullyConstructed8));
	TPckgBuf<SDigitalDisplayCommandSetBackgroundColorArgs> args;
	args().iBackgroundColor=aBackgroundColor;
	args().iShadowColor=aShadowColor;
	TInt error=CommandReply(EDigitalDisplayCommandSetBackgroundColor, args);
	__ASSERT_ALWAYS(error==KErrNone, Panic(EClockClientPanicUnexpectedError8));
	}

EXPORT_C void RDigitalClock::SetTextColor(TRgb aTextColor)
/** Sets the text colour.

This function can only be called after full construction of the clock.

@param aTextColor Text colour */
	{
	__ASSERT_ALWAYS(ConstructorBufAlreadySent(), Panic(EClockClientPanicNotYetFullyConstructedDigitalTextColor));
	TPckgBuf<SDigitalDisplayCommandSetTextColorArgs> args;
	args().iTextColor=aTextColor;
	TInt error=CommandReply(EDigitalDisplayCommandSetTextColor, args);
	__ASSERT_ALWAYS(error==KErrNone, Panic(EClockClientPanicUnexpectedErrorDigitalTextColor));
	}


// RAnalogClock

EXPORT_C RAnalogClock::RAnalogClock(RAnimDll& aAnimDll, const RWindowBase& aWindow)
	:RClock(aAnimDll, aWindow)
/** Creates an analogue clock object.

To complete construction, you must call ConstructL().

@param aAnimDll This RAnimDll must have been loaded with the server-side clock 
animation DLL, clocka.dll
@param aWindow Window to which to add the clock */
	{
	}

EXPORT_C void RAnalogClock::ConstructL(TTimeIntervalSeconds aUniversalTimeOffset, const TPoint& aPosition, const TSize& aSize, const TMargins& aMargins,
																const STimeDeviceShadow& aShadow, TInt aFaceHandle, TInt aFaceMaskHandle, TInt aNumHands, const SAnalogDisplayAmPm* aAmPm)
/** Completes construction of an analogue clock.

The bitmaps specified in aFaceHandle and aFaceMaskHandle cannot be destroyed 
until the clock has been completely constructed, including all necessary calls 
to RAnalogClock::AddHandL().

@param aUniversalTimeOffset Initial time for the clock, expressed as an offset 
from universal time
@param aPosition Clock's on-screen position
@param aSize Clock's on-screen size
@param aMargins Margin settings
@param aShadow Shadow settings
@param aFaceHandle Handle to a bitmap of the clock face. You can obtain a bitmap 
handle through CFbsBitmap::Handle().
@param aFaceMaskHandle Handle to a bitmap mask for the clock face. This can 
be 0, if no mask is required.
@param aNumHands Number of hands on the clock. For each hand, you must call 
AddHandL().
@param aAmPm Options for displaying AM/PM
@see CFbsBitmap::Handle() */
	{
	__ASSERT_ALWAYS(!ConstructorBufExists(), Panic(EClockClientPanicAlreadyConstructedAnalogClock));
	AppendClockConstructorArgsL(aUniversalTimeOffset);
	AppendAnalogDisplayConstructorArgsL(aPosition, aSize, aMargins, aShadow, aFaceHandle, aFaceMaskHandle, aNumHands, aAmPm);
	}

EXPORT_C void RAnalogClock::AddHandL(const TAnalogDisplayHand& aHand)
/** Adds a hand to the clock.

This function can only be called after full construction of the clock.

@param aHand Settings for the hand. */
	{
	__ASSERT_ALWAYS(ConstructorBufExists(), Panic(EClockClientPanicNotYetConstructedAnalogClock));
	__ASSERT_ALWAYS(aHand.NumFeatures()>0, Panic(EClockClientPanicTooFewHandFeatures));
	AppendToConstructorBufL(aHand.Buf());
	SendConstructorBufIfCompleteL(EAnimClock);
	}

EXPORT_C void RAnalogClock::SetBackgroundColor(TRgb aBackgroundColor, TRgb aShadowColor)
/** Sets the background colour for the clock.

This function can only be called after full construction of the clock.

@param aBackgroundColor Background colour.
@param aShadowColor Shadow colour. */
	{
	__ASSERT_ALWAYS(ConstructorBufAlreadySent(), Panic(EClockClientPanicNotYetFullyConstructed8));
	TPckgBuf<SDigitalDisplayCommandSetBackgroundColorArgs> args;
	args().iBackgroundColor=aBackgroundColor;
	args().iShadowColor=aShadowColor;
	TInt error=CommandReply(EDigitalDisplayCommandSetBackgroundColor, args);
	__ASSERT_ALWAYS(error==KErrNone, Panic(EClockClientPanicUnexpectedError8));
	}

EXPORT_C void RAnalogClock::SetTextColor(TRgb aTextColor)
/** Sets the text colour.

This function can only be called after full construction of the clock.

@param aTextColor Text colour. */
	{
	__ASSERT_ALWAYS(ConstructorBufAlreadySent(), Panic(EClockClientPanicNotYetFullyConstructedDigitalTextColor));
	TPckgBuf<SDigitalDisplayCommandSetTextColorArgs> args;
	args().iTextColor=aTextColor;
	TInt error=CommandReply(EDigitalDisplayCommandSetTextColor, args);
	__ASSERT_ALWAYS(error==KErrNone, Panic(EClockClientPanicUnexpectedErrorDigitalTextColor));
	}

EXPORT_C void RAnalogClock::SetPenColor(const TRgb aPenColor)
/** Sets the pen colour for the hands.

This function can only be called after full construction of the clock.

@param aPenColor Pen colour. */
	{
	__ASSERT_ALWAYS(ConstructorBufAlreadySent(), Panic(EClockClientPanicNotYetFullyConstructedAnalogPenColor));
	TPckgBuf<SAnalogDisplayHandFeaturesPenColorArgs> args;
	args().iPenColor=aPenColor;
	TInt error=CommandReply(EAnalogDisplayCommandSetPenColor, args);
	__ASSERT_ALWAYS(error==KErrNone, Panic(EClockClientPanicUnexpectedErrorAnalogPenColor));
	}

EXPORT_C void RAnalogClock::SetBrushColor(const TRgb aBrushColor)
/** Sets the brush colour for the hands.

This function can only be called after full construction of the clock.

@param aBrushColor Brush colour. */
	{
	__ASSERT_ALWAYS(ConstructorBufAlreadySent(), Panic(EClockClientPanicNotYetFullyConstructedAnalogBrushColor));
	TPckgBuf<SAnalogDisplayHandFeaturesBrushColorArgs> args;
	args().iBrushColor=aBrushColor;
	TInt error=CommandReply(EAnalogDisplayCommandSetBrushColor, args);
	__ASSERT_ALWAYS(error==KErrNone, Panic(EClockClientPanicUnexpectedErrorAnalogBrushColor));
	}


// RMessageWindow

EXPORT_C RMessageWindow::RMessageWindow(RAnimDll& aAnimDll, const RWindowBase& aWindow)
	:RAnimWithUtils(aAnimDll, aWindow)
/** Constructor.

@param aAnimDll This RAnimDll must have been loaded with the server-side message 
window animation DLL, clocka.dll.
@param aWindow Window to which to add the message window. */
	{
	}

EXPORT_C void RMessageWindow::ConstructL(TInt aBaselineOffset, TInt aFontHandle, TRgb aBackgroundColor, TRgb aTextColor)
/** Performs second-phase construction.

@param aBaselineOffset Height of window in pixels above the font's baseline.
@param aFontHandle Handle to the font to use. This can be obtained with CFbsFont::Handle().
@param aBackgroundColor Window's background colour.
@param aTextColor Message text colour.
@see CFbsFont::Handle() */
	{
	TPckgBuf<SMessageWindowConstructorArgs> messageWindowConstructorArgs;
	messageWindowConstructorArgs().iBaselineOffset=aBaselineOffset;
	messageWindowConstructorArgs().iFontHandle=aFontHandle;
	messageWindowConstructorArgs().iBackgroundColor=aBackgroundColor;
	messageWindowConstructorArgs().iTextColor=aTextColor;
	messageWindowConstructorArgs().iBorderColor=KRgbBlack;
	AppendToConstructorBufL(messageWindowConstructorArgs);
	SendConstructorBufL(EAnimMessageWindow);
	}

EXPORT_C void RMessageWindow::ConstructL(TInt aBaselineOffset, TInt aFontHandle, TRgb aBackgroundColor, TRgb aTextColor, TRgb aBorderColor)
/** Performs second-phase construction, with a window border colour.

@param aBaselineOffset Height of window in pixels above the font's baseline.
@param aFontHandle Handle to the font to use. This can be obtained with CFbsFont::Handle().
@param aBackgroundColor Window's background colour.
@param aTextColor Message text colour.
@param aBorderColor Window border colour.
@see CFbsFont::Handle() */
	{
	TPckgBuf<SMessageWindowConstructorArgs> messageWindowConstructorArgs;
	messageWindowConstructorArgs().iBaselineOffset=aBaselineOffset;
	messageWindowConstructorArgs().iFontHandle=aFontHandle;
	messageWindowConstructorArgs().iBackgroundColor=aBackgroundColor;
	messageWindowConstructorArgs().iTextColor=aTextColor;
	messageWindowConstructorArgs().iBorderColor=aBorderColor;
	AppendToConstructorBufL(messageWindowConstructorArgs);
	SendConstructorBufL(EAnimMessageWindow);
	}

EXPORT_C void RMessageWindow::SetBackgroundColor(TRgb aBackgroundColor)
/** Sets the background colour for the window.

@param aBackgroundColor Background colour. */
	{
	__ASSERT_ALWAYS(ConstructorBufAlreadySent(), Panic(EClockClientPanicNotYetFullyConstructedMsgWindowBackgroundColor));
	TPckgBuf<SMessageWindowBackgroundColorArgs> messageWindowArgs;
	messageWindowArgs().iBackgroundColor=aBackgroundColor;
	TInt error=CommandReply(EMessageWindowCommandSetBackgroundColor, messageWindowArgs);
	__ASSERT_ALWAYS(error==KErrNone, Panic(EClockClientPanicUnexpectedErrorMsgWindowBackgroundColor));
	}

EXPORT_C void RMessageWindow::SetTextColor(TRgb aTextColor)
/** Sets the message text colour.

@param aTextColor Message text colour. */
	{
	__ASSERT_ALWAYS(ConstructorBufAlreadySent(), Panic(EClockClientPanicNotYetFullyConstructedMsgWindowTextColor));
	TPckgBuf<SMessageWindowTextColorArgs> messageWindowArgs;
	messageWindowArgs().iTextColor=aTextColor;
	TInt error=CommandReply(EMessageWindowCommandSetTextColor, messageWindowArgs);
	__ASSERT_ALWAYS(error==KErrNone, Panic(EClockClientPanicUnexpectedErrorMsgWindowTextColor));
	}

EXPORT_C void RMessageWindow::SetBorderColor(TRgb aBorderColor)
/** Sets the window border colour.

@param aBorderColor Window border colour. */
	{
	__ASSERT_ALWAYS(ConstructorBufAlreadySent(), Panic(EClockClientPanicNotYetFullyConstructedMsgWindowBorderColor));
	TPckgBuf<SMessageWindowBorderColorArgs> messageWindowArgs;
	messageWindowArgs().iBorderColor=aBorderColor;
	TInt error=CommandReply(EMessageWindowCommandSetBorderColor, messageWindowArgs);
	__ASSERT_ALWAYS(error==KErrNone, Panic(EClockClientPanicUnexpectedErrorMsgWindowBorderColor));
	}

EXPORT_C void RMessageWindow::SetPlinthColors(TRgb aTl,TRgb aBr)
/** Sets the plinth colours.

@param aTl Colour to use around the top and left borders.
@param aBr Colour to use around the bottom and right borders. */
	{
	__ASSERT_ALWAYS(ConstructorBufAlreadySent(), Panic(EClockClientPanicNotYetFullyConstructedMsgWindowPlinthColor));
	TPckgBuf<SMessageWindowPlinthColorArgs> messageWindowArgs;
	messageWindowArgs().iTlColor=aTl;
	messageWindowArgs().iBrColor=aBr;
	TInt error=CommandReply(EMessageWindowCommandSetPlinthColor, messageWindowArgs);
	__ASSERT_ALWAYS(error==KErrNone, Panic(EClockClientPanicUnexpectedErrorMsgWindowPlinthColor));
	}

EXPORT_C void RMessageWindow::StartDisplay(TBool aFlash, TTimeIntervalMicroSeconds32 aInitialDelay, const TDesC& aText)
/** Displays the message window for a specified time.

@param aFlash Set this to true to make the message window flash.
@param aInitialDelay Duration for which to display the message window.
@param aText Text to put in the window. */
	{
	__ASSERT_ALWAYS(ConstructorBufAlreadySent(), Panic(EClockClientPanicNotYetFullyConstructed9));
	TPckgBuf<SMessageWindowCommandStartDisplayArgs> args;
	args().iFlash=aFlash;
	args().iInitialDelay=aInitialDelay;
	args().iDuration=SMessageWindowCommandStartDisplayArgs::EIndefiniteDuration;
	args().iText=aText;
	TInt error=CommandReply(EMessageWindowCommandStartDisplay, args);
	__ASSERT_ALWAYS(error==KErrNone, Panic(EClockClientPanicUnexpectedError9));
	}

EXPORT_C void RMessageWindow::StartDisplay(TBool aFlash, TTimeIntervalMicroSeconds32 aInitialDelay, TTimeIntervalMicroSeconds32 aDuration, const TDesC& aText)
/** Displays the message window for a specified time with an initial delay.

@param aFlash Set this to true to make the message window flash.
@param aInitialDelay Initial delay before showing the window.
@param aDuration Duration for which to display the message window.
@param aText Text to put in the window. */
	{
	__ASSERT_ALWAYS(ConstructorBufAlreadySent(), Panic(EClockClientPanicNotYetFullyConstructed10));
	TPckgBuf<SMessageWindowCommandStartDisplayArgs> args;
	args().iFlash=aFlash;
	args().iInitialDelay=aInitialDelay;
	args().iDuration=aDuration;
	args().iText=aText;
	TInt error=CommandReply(EMessageWindowCommandStartDisplay, args);
	__ASSERT_ALWAYS(error==KErrNone, Panic(EClockClientPanicUnexpectedError10));
	}

EXPORT_C void RMessageWindow::CancelDisplay()
/** Cancels the display of the window. */
	{
	__ASSERT_ALWAYS(ConstructorBufAlreadySent(), Panic(EClockClientPanicNotYetFullyConstructed11));
	TInt error=CommandReply(EMessageWindowCommandCancelDisplay);
	__ASSERT_ALWAYS(error==KErrNone, Panic(EClockClientPanicUnexpectedError11));
	}

EXPORT_C void RMessageWindow::GetBorders(TMargins& aBorders)
/** Gets the widths of the window's borders.

@param aBorders On return, the widths of the window's borders */
	{
	__ASSERT_ALWAYS(ConstructorBufAlreadySent(), Panic(EClockClientPanicNotYetFullyConstructed12));
	TPckg<TMargins> borders(aBorders);
	TIpcArgs ipcArgs;
	ipcArgs.Set(KIpcSlot, &borders);
	TInt error=CommandReply(EMessageWindowCommandGetBorders, KNullDesC8, ipcArgs);
	__ASSERT_ALWAYS(error==KErrNone, Panic(EClockClientPanicUnexpectedError12));
	}

