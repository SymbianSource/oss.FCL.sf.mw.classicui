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
// header for client-side and server-side clock DLL's
// $Workfile:   CL_STD.H  $
// $Revision:   1.7  $
// $Author:   DougF  $
// $Date:   07 Jul 1999 16:16:18  $
// 
//

#if !defined(__CL_STD_H__)
#define __CL_STD_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__W32STD_H__)
#include <w32std.h>
#endif

#if !defined(__W32ADLL_H__)
#include <w32adll.h>
#endif

#if !defined(__CLOCK_H__)
#include <clock.h>
#endif

//
// build flags
//

#undef __SHOW_UPDATE_REGION__
#undef __SLOW_DIGITAL_REGION_CALCULATION__

//
// miscellaneous constants
//

const TInt KCheckValueForEndOfTimeDeviceConstructionBuf=0x3af96b5e; // a random number
const TInt KPanicClientFromServer=1;
const TInt KIpcSlot=1; // must not be zero as this is reserved by the window server

//
// miscellaneous typedefs
//

typedef RRegionBuf<10> RRegionBuf10;

//
// miscellaneous enums
//

enum TClockClientPanic
	{
	EClockClientPanicAlreadyConstructed,
	EClockClientPanicAlreadyConstructedDigitalClock,
	EClockClientPanicAlreadyConstructedAnalogClock,
	EClockClientPanicNotYetConstructedDigitalClock,
	EClockClientPanicNotYetConstructedAnalogClock,
	EClockClientPanicNotYetFullyConstructed1,
	EClockClientPanicNotYetFullyConstructed2,
	EClockClientPanicNotYetFullyConstructed3,
	EClockClientPanicNotYetFullyConstructed4,
	EClockClientPanicNotYetFullyConstructed5,
	EClockClientPanicNotYetFullyConstructed6,
	EClockClientPanicNotYetFullyConstructed7,
	EClockClientPanicNotYetFullyConstructed8,
	EClockClientPanicNotYetFullyConstructed9,
	EClockClientPanicNotYetFullyConstructed10,
	EClockClientPanicNotYetFullyConstructed11,
	EClockClientPanicNotYetFullyConstructed12,
	EClockClientPanicIncorrectNumberOfAdditions1,
	EClockClientPanicIncorrectNumberOfAdditions2,
	EClockClientPanicNoConstructorBuf,
	EClockClientPanicBadSetNumAdditionsStillExpectedCall,
	EClockClientPanicTooFewTextSections,
	EClockClientPanicTooFewHands,
	EClockClientPanicTooFewHandFeatures,
	EClockClientPanicRectIsNotNormalized,
	EClockClientPanicUnexpectedError1,
	EClockClientPanicUnexpectedError2,
	EClockClientPanicUnexpectedError3,
	EClockClientPanicUnexpectedError4,
	EClockClientPanicUnexpectedError5,
	EClockClientPanicUnexpectedError6,
	EClockClientPanicUnexpectedError7,
	EClockClientPanicUnexpectedError8,
	EClockClientPanicUnexpectedError9,
	EClockClientPanicUnexpectedError10,
	EClockClientPanicUnexpectedError11,
	EClockClientPanicUnexpectedError12,
// Setting the colors
	EClockClientPanicNotYetFullyConstructedDigitalTextColor,			// When setting the text color for digital clock
	EClockClientPanicNotYetFullyConstructedAnalogPenColor,				// When setting the pen color for analog clock
	EClockClientPanicNotYetFullyConstructedAnalogBrushColor,			// When setting the brush color for analog clock
	EClockClientPanicNotYetFullyConstructedMsgWindowBackgroundColor,	// When setting the background color for window message
	EClockClientPanicNotYetFullyConstructedMsgWindowTextColor,			// When setting the text color for window message
	EClockClientPanicNotYetFullyConstructedMsgWindowBorderColor,		// When setting the border color for window message
	EClockClientPanicNotYetFullyConstructedMsgWindowPlinthColor,		// When setting the plinth color for window message
	EClockClientPanicUnexpectedErrorDigitalTextColor,					// When setting the text color for digital clock
	EClockClientPanicUnexpectedErrorAnalogPenColor,						// When setting the pen color for analog clock
	EClockClientPanicUnexpectedErrorAnalogBrushColor,					// When setting the brush color for analog clock
	EClockClientPanicUnexpectedErrorMsgWindowBackgroundColor,			// When setting the background color for window message
	EClockClientPanicUnexpectedErrorMsgWindowTextColor,					// When setting the text color for window message
	EClockClientPanicUnexpectedErrorMsgWindowBorderColor,				// When setting the border color for window message
	EClockClientPanicUnexpectedErrorMsgWindowPlinthColor,				// When setting the plinth color for window message
	};

//

enum TClockServerPanic
	{
	EClockServerPanicNotInitializedToNULL1,
	EClockServerPanicNotInitializedToNULL2,
	EClockServerPanicNotInitializedToNULL3,
	EClockServerPanicNotInitializedToNULL4,
	EClockServerPanicNotInitializedToNULL5,
	EClockServerPanicNotInitializedToNULL6,
	EClockServerPanicNotInitializedToNULL7,
	EClockServerPanicNotInitializedToNULL8,
	EClockServerPanicNotInitializedToNULL9,
	EClockServerPanicNotInitializedToZero1,
	EClockServerPanicNotInitializedToZero2,
	EClockServerPanicNotInitializedToZero3,
	EClockServerPanicNotInitializedToZero4,
	EClockServerPanicBadSync1,
	EClockServerPanicBadSync2,
	EClockServerPanicBadSync3,
	EClockServerPanicBadPolyLineState,
	EClockServerPanicInconsistentPointListLengths,
	EClockServerPanicBadEndOfConstructionBuf,
	EClockServerPanicUnexpectedError,
	EClockServerPanicAlreadyVisible,
	EClockServerPanicTimerIsActive,
	EClockServerPanicAnimatingNonFlashingMessageWindow,
	EClockServerPanicBadRect,
	EClockServerPanicBadMessageWindowTimerAction
	};

//

enum TAnimType
	{
	EAnimClock,
	EAnimMessageWindow
	};

//
// constructor argument structs
//

struct SDigitalDisplayConstructorArgs
	{
	TPoint iPosition;
	TSize iSize;
	TMargins iMargins;
	STimeDeviceShadow iShadow;
	TRgb iBackgroundColor;
	TInt iNumTextSections;
	};

//

struct SDigitalDisplayTextSectionConstructorArgs
	{
	TInt iFontHandle;
	TRgb iTextColor;
	TDigitalDisplayHorizontalTextAlignment iHorizontalAlignment;
	TDigitalDisplayVerticalTextAlignment iVerticalAlignment;
	TInt iHorizontalMargin;
	TInt iVerticalMargin;
	TInt iFormatLength;
	};

//

struct SAnalogDisplayConstructorArgs
	{
	TPoint iPosition;
	TSize iSize;
	TMargins iMargins;
	STimeDeviceShadow iShadow;
	TInt iFaceHandle;
	TInt iFaceMaskHandle;
	TInt iNumHands;
	TBool iHasAmPm;
	};

//

struct SAnalogDisplayHandConstructorArgs
	{
	TAnalogDisplayHandType iType;
	TInt iNumFeatures;
	};

//

struct SAnalogDisplayHandLineConstructorArgs
	{
	CGraphicsContext::TPenStyle iPenStyle;
	TRgb iPenColor;
	TSize iPenSize;
	TPoint iStartPoint;
	TPoint iEndPoint;
	};

//

struct SAnalogDisplayHandPolyLineConstructorArgs
	{
	CGraphicsContext::TPenStyle iPenStyle;
	TRgb iPenColor;
	TSize iPenSize;
	CGraphicsContext::TBrushStyle iBrushStyle;
	TRgb iBrushColor;
	TBool iClosed;
	TInt iNumPoints;
	};

//

struct SAnalogDisplayHandCircleConstructorArgs
	{
	CGraphicsContext::TPenStyle iPenStyle;
	TRgb iPenColor;
	TSize iPenSize;
	CGraphicsContext::TBrushStyle iBrushStyle;
	TRgb iBrushColor;
	TPoint iCircleCenter;
	TInt iRadius;
	};

//
struct SAnalogDisplayHandFeaturesPenColorArgs
	{
	TRgb iPenColor;
	};

//
struct SAnalogDisplayHandFeaturesBrushColorArgs
	{
	TRgb iBrushColor;
	};

//

struct SClockConstructorArgs
	{
	TTimeIntervalSeconds iUniversalTimeOffset;
	};

//

struct SMessageWindowConstructorArgs
	{
	TInt iBaselineOffset;
	TInt iFontHandle;
	TRgb iBackgroundColor;
	TRgb iTextColor;
	TRgb iBorderColor;
	};

//
struct SMessageWindowBackgroundColorArgs
	{
	TRgb iBackgroundColor;
	};
//
struct SMessageWindowTextColorArgs
	{
	TRgb iTextColor;
	};
//
struct SMessageWindowBorderColorArgs
	{
	TRgb iBorderColor;
	};

struct SMessageWindowPlinthColorArgs
	{
	TRgb iTlColor;
	TRgb iBrColor;
	};

//
// command opcodes and their argument structs
//

enum TTimeDeviceCommand
	{
	EClockCommand								=0x1000,
	EDisplayCommand								=0x2000,
	EDigitalDisplayCommand						=0x4000|EDisplayCommand,
	EAnalogDisplayCommand						=0x8000|EDisplayCommand,
	EClockCommandSetUniversalTimeOffset			=EClockCommand|1,
	EDisplayCommandSetVisible					=EDisplayCommand|1,
	EDisplayCommandSetPositionAndSize			=EDisplayCommand|2,
	EDisplayCommandSetPosition					=EDisplayCommand|3,
	EDisplayCommandSetSize						=EDisplayCommand|4,
	EDisplayCommandUpdateDisplay				=EDisplayCommand|5,
	EDisplayCommandDraw							=EDisplayCommand|6,
	EDigitalDisplayCommandSetBackgroundColor	=EDigitalDisplayCommand|1,
//!<
	EDigitalDisplayCommandSetTextColor			=EDigitalDisplayCommand|2,
	EAnalogDisplayCommandSetPenColor			=EAnalogDisplayCommand|1,
	EAnalogDisplayCommandSetBrushColor			=EAnalogDisplayCommand|2
//!>
	};

struct SClockCommandSetUniversalTimeOffsetArgs
	{
	TTimeIntervalSeconds iUniversalTimeOffset;
	};

struct SDisplayCommandSetVisibleArgs
	{
	TBool iVisible;
	};

struct SDisplayCommandSetPositionAndSizeArgs
	{
	TPoint iPosition;
	TSize iSize;
	};

struct SDisplayCommandSetPositionArgs
	{
	TPoint iPosition;
	};

struct SDisplayCommandSetSizeArgs
	{
	TSize iSize;
	};

struct SDigitalDisplayCommandSetBackgroundColorArgs
	{
	TRgb iBackgroundColor;
	TRgb iShadowColor;
	};

//
struct SDigitalDisplayCommandSetTextColorArgs
	{
	TRgb iTextColor;
	};

enum TMessageWindowCommand
	{
	EMessageWindowCommandStartDisplay,
	EMessageWindowCommandCancelDisplay,
	EMessageWindowCommandGetBorders,
	EMessageWindowCommandSetBackgroundColor,
	EMessageWindowCommandSetTextColor,
	EMessageWindowCommandSetBorderColor,
	EMessageWindowCommandSetPlinthColor,
	};

struct SMessageWindowCommandStartDisplayArgs
	{
	enum
		{
		EIndefiniteDuration=-1
		};
	TBool iFlash;
	TTimeIntervalMicroSeconds32 iInitialDelay;
	TTimeIntervalMicroSeconds32 iDuration;
	TBuf<RMessageWindow::EMaxTextLength> iText;
	};

//
// utility classes supporting the digital display class
//

class DDigitalDisplayTextSection : public CBase
	{
public:
	DDigitalDisplayTextSection(MAnimGeneralFunctions& aFunctions, TRgb aTextColor, TDigitalDisplayHorizontalTextAlignment aHorizontalAlignment,
																TDigitalDisplayVerticalTextAlignment aVerticalAlignment,
																TInt aHorizontalMargin, TInt aVerticalMargin);
	void ConstructL(const TDesC& aFormat, TInt aFontHandle);
	void SetInitialTimeP(const TTime& aTime, TBool aLimitResolutionToMinutes);
	virtual ~DDigitalDisplayTextSection();
	void DrawP(CAnimGc& aGc, const TRect& aRect, TBool aFlashStateOn, const TRgb* aOverridingColor=NULL) const;
	void UpdateDisplayDataP(const TRect& aRect, const STimeDeviceShadow& aShadow, const TTime& aTime, TBool aFlashStateIsChanging, TRegion* aRegion, TBool aLimitResolutionToMinutes);
	void SetTextColor(TRgb aTextColor);

private:
	void FormatTruncatingIfNecessaryP(const TTime& aTime, TDes& aResult, TBool aLimitResolutionToMinutes) const;
	TRect UpdateRect(const TPoint& aPosition, const SCharWidth& aPixelWidth, TInt aAscentInPixels, TInt aHeightInPixels) const;
	TRect ExpandToIncludeShadows(const TRect& aRect, const STimeDeviceShadow& aShadow) const;
#if defined(__SLOW_DIGITAL_REGION_CALCULATION__)
	void AddUpdateAreasToRegion(TRegion& aRegion, TInt aYPosition, const STimeDeviceShadow& aShadow, TInt aAscentInPixels, TInt aHeightInPixels,
																const TDesC& aOldText, TInt aOldXPosition,
																const TDesC& aNewText, TInt aNewXPosition) const;
#endif
	void InitializeTextBlockIteratorP(const TRect& aRect, const TDesC& aText, TInt& aTextOffset, TInt& aTextLength,
																TInt& aXPosition, SCharWidth& aPixelWidth, TBool& aInFlashingBlock) const;
	TBool GetNextTextBlockP(const TDesC& aText, TInt& aTextOffset, TInt& aTextLength,
																TInt& aXPosition, SCharWidth& aPixelWidth, TBool& aInFlashingBlock) const;
	TInt XPositionP(const TRect& aRect, const TDesC& aText) const;
	TInt YPositionP(const TRect& aRect) const;
	void TextWidthInPixels(const TDesC& aText, SCharWidth& aPixelWidth) const;
private:
	typedef TBuf<48> TDisplayText;
private:
	MAnimGeneralFunctions& iFunctions;
	HBufC* iFormat;
	TDisplayText iDisplayText;
	CFbsFont* iFont;
	TRgb iTextColor;
	TDigitalDisplayHorizontalTextAlignment iHorizontalAlignment;
	TDigitalDisplayVerticalTextAlignment iVerticalAlignment;
	TInt iHorizontalMargin;
	TInt iVerticalMargin;
	HBufC* iTruncatedFormat;
	};

//
// utility classes supporting the analog display class
//

class TFraction
	{
public:
	TFraction();
	TFraction(TInt aNumber, TInt aRightShift);
	TInt operator*(TInt aInt) const;
private:
	TInt iNumber;
	TInt iRightShift;
	};

//

class TTrig
	{
public:
	static TFraction Sin(TInt aDegrees);
	static TFraction Cos(TInt aDegrees);
private:
	enum
		{
		ERightShift=15,
		ENumStepsPer90Degrees=15,
		ENumInterpolations=90/ENumStepsPer90Degrees,
		ENumStored=ENumStepsPer90Degrees+2
		};
private:
	static const TInt iStore[ENumStored];
	};

//

class DAnalogDisplayHandFeature : public CBase
	{
public:
	DAnalogDisplayHandFeature();
	virtual TRect BoundingRectP(const TFraction& aSin, const TFraction& aCos, const TPoint& aHandCenter) const=0;
	virtual void Draw(CAnimGc& aGc, const TFraction& aSin, const TFraction& aCos, const TPoint& aHandCenter, const TRgb* aOverridingColor) const=0;
	virtual void SetPenColor(TRgb aPenColor);
	virtual void SetBrushColor(TRgb aBrushColor);

protected:
	TPoint Rotate(const TPoint& aPoint, const TFraction& aSin, const TFraction& aCos, const TPoint& aOffset) const;
	TRect AdjustRectForPenSizeP(const TRect& aRect, const TSize& aPenSize) const;
	};

//

class DAnalogDisplayHandLine : public DAnalogDisplayHandFeature
	{
public:
	DAnalogDisplayHandLine(CGraphicsContext::TPenStyle aPenStyle, TRgb aPenColor, const TSize& aPenSize, const TPoint& aStartPoint, const TPoint& aEndPoint);
	virtual TRect BoundingRectP(const TFraction& aSin, const TFraction& aCos, const TPoint& aHandCenter) const;
	virtual void Draw(CAnimGc& aGc, const TFraction& aSin, const TFraction& aCos, const TPoint& aHandCenter, const TRgb* aOverridingColor) const;
	void SetPenColor(TRgb aPenColor);

private:
	CGraphicsContext::TPenStyle iPenStyle;
	TRgb iPenColor;
	TSize iPenSize;
	TPoint iStartPoint;
	TPoint iEndPoint;
	};

//

class DAnalogDisplayHandPolyLine : public DAnalogDisplayHandFeature
	{
public:
	DAnalogDisplayHandPolyLine(CGraphicsContext::TPenStyle aPenStyle, TRgb aPenColor, const TSize& aPenSize,
																CGraphicsContext::TBrushStyle aBrushStyle, TRgb aBrushColor,
																TBool aClosed, TInt aNumPoints);
	void AddPointLP(const TPoint& aPoint);
	virtual ~DAnalogDisplayHandPolyLine();
	virtual TRect BoundingRectP(const TFraction& aSin, const TFraction& aCos, const TPoint& aHandCenter) const;
	virtual void Draw(CAnimGc& aGc, const TFraction& aSin, const TFraction& aCos, const TPoint& aHandCenter, const TRgb* aOverridingColor) const;
	void SetPenColor(TRgb aPenColor);
	void SetBrushColor(TRgb aBrushColor);

private:
	struct SPointList
		{
		TInt16 iNumPoints;
		TInt16 iNumPointsAdded;
		TPoint* iPoints;
		};
private:
	void SetScratchPointList(const TFraction& aSin, const TFraction& aCos, const TPoint& aHandCenter) const;
private:
	CGraphicsContext::TPenStyle iPenStyle;
	TRgb iPenColor;
	TSize iPenSize;
	CGraphicsContext::TBrushStyle iBrushStyle;
	TRgb iBrushColor;
	TBool iClosed;
	SPointList iPoints;
	CArrayFix<TPoint>* iScratchPointList;
	};

//

class DAnalogDisplayHandCircle : public DAnalogDisplayHandFeature
	{
public:
	DAnalogDisplayHandCircle(CGraphicsContext::TPenStyle aPenStyle, TRgb aPenColor, const TSize& aPenSize,
																CGraphicsContext::TBrushStyle aBrushStyle, TRgb aBrushColor,
																const TPoint& aCircleCenter, TInt aRadius);
	virtual TRect BoundingRectP(const TFraction& aSin, const TFraction& aCos, const TPoint& aHandCenter) const;
	virtual void Draw(CAnimGc& aGc, const TFraction& aSin, const TFraction& aCos, const TPoint& aHandCenter, const TRgb* aOverridingColor) const;
	void SetPenColor(TRgb aPenColor);
	void SetBrushColor(TRgb aBrushColor);

private:
	TRect Rect(const TFraction& aSin, const TFraction& aCos, const TPoint& aHandCenter) const;
private:
	CGraphicsContext::TPenStyle iPenStyle;
	TRgb iPenColor;
	TSize iPenSize;
	CGraphicsContext::TBrushStyle iBrushStyle;
	TRgb iBrushColor;
	TPoint iCircleCenter;
	TInt iRadius;
	};

//

class DAnalogDisplayHand : public CBase
	{
public:
	DAnalogDisplayHand(TAnalogDisplayHandType aType, TInt aNumFeatures);
	void AddFeatureLP(DAnalogDisplayHandFeature* aFeature);
	void SetInitialTimeP(const TTime& aTime);
	virtual ~DAnalogDisplayHand();
	void DrawP(CAnimGc& aGc, const TPoint& aHandCenter, const TRgb* aOverridingColor=NULL) const;
	void UpdateDisplayDataP(const TTime& aTime, const TPoint& aHandCenter, const STimeDeviceShadow& aShadow, TRegion* aRegion);
	void SetPenColor(const TRgb aPenColor);
	void SetBrushColor(const TRgb aBrushColor);
	TAnalogDisplayHandType Type() const {return iType;};

private:
	TRect BoundingRectP(const TPoint& aHandCenter, const STimeDeviceShadow& aShadow) const;
	void SetDegreesOffUpright(TInt aDegreesOffUpright);
	TInt DegreesOffUprightP(const TTime& aTime) const;
private:
	struct SFeatureList
		{
		TInt16 iNumFeatures;
		TInt16 iNumFeaturesAdded;
		DAnalogDisplayHandFeature** iFeatures;
		};
private:
	TAnalogDisplayHandType iType;
	SFeatureList iFeatures;
	TInt iDegreesOffUpright;
	TFraction iSin;
	TFraction iCos;
	};

//
// utility class
//

// To give our animation the ability to animate itself independent
// to WSERV calling Animate() make it a CFreeTimerWindowAnim
class DAnimWithUtils : public CFreeTimerWindowAnim
	{
public:
	struct TFunctions
		{
		inline TFunctions(MAnimGeneralFunctions& aFunctions,MAnimWindowFunctions& aWindowFunctions) 
			:iFunctions(aFunctions),iWindowFunctions(aWindowFunctions) {}
		MAnimGeneralFunctions& iFunctions;
		MAnimWindowFunctions& iWindowFunctions;
		};
public:
	DAnimWithUtils();
	virtual void ConstructL(TAny* aArgs, TBool aHasFocus);
	virtual TInt CommandReplyL(TInt aOpcode, TAny* aArgs);
	virtual void Command(TInt aOpcode, TAny* aArgs);
	virtual void Animate(TDateTime* aDateTime);
	virtual void Redraw();
	virtual void FocusChanged(TBool aState);
protected:
	virtual void ConstructLP(const TUint8* aBytePtr, TBool aHasFocus)=0;
	virtual TInt CommandReplyLP(TInt aOpcode, TAny* aArgs);
	virtual void CommandP(TInt aOpcode, TAny* aArgs);
	virtual void AnimateP(TDateTime* aDateTime)=0;
	virtual void RedrawP()=0;
	virtual void FocusChangedP(TBool aState);
	static TPtrC ReadText(const TUint8*& aBytePtr, TInt aTextLength);
	//Pure Virtual function from MEventHandler
	virtual TBool OfferRawEvent(const TRawEvent &aRawEvent);
private:
	void HandleErrorIfErrorL(TInt aError);
	};

//  CMinuteTick class definition here
class CMinuteTick : public CTimer
	{
public:
	class MObserver
		{
	public:
		virtual void MinuteTickCompleteL(const TTime& aNewUniversalTime)=0;
		};
public:
	static CMinuteTick* NewL(MObserver& aObserver);
	~CMinuteTick();

	void Start();
	void Stop();
public:  // From CActive (via CTimer)
	virtual void RunL();
private:
	CMinuteTick(MObserver& aObserver);
	void CalculateTimeAtNextMinute();
	void ReQueueTimer();
private:
	MObserver& iObserver;
	TTime iHomeTimeAtNextMinute;
	};

//
// time-device abstract class
//

class DDisplay;

class DTimeDevice : public DAnimWithUtils, public CMinuteTick::MObserver
	{
public:
	DTimeDevice();
	virtual ~DTimeDevice();
public: // Overriding implementations from DAnimWithUtils
	virtual void FocusChanged(TBool aState);
	virtual void HandleNotification(const TWsEvent& aEvent);
public: // from CMinuteTick::MObserver
	virtual void MinuteTickCompleteL(const TTime& aNewUniversalTime); 
protected:
	virtual void ConstructLP(const TUint8* aBytePtr, TBool aHasFocus);
	virtual TInt CommandReplyLP(TInt aOpcode, TAny* aArgs);
	virtual void CommandP(TInt aOpcode, TAny* aArgs);
	virtual void AnimateP(TDateTime* aDateTime);
	virtual void RedrawP();
	TTime Time() const;
	static void StripOutCharacter(TDes& aText, TChar aCharacter);
private:
	virtual void DoConstructL(const TUint8*& aBytePtr)=0;
	virtual TTime TimeGivenUniversalTime(const TTime& aUniversalTime) const=0;
	void DoAnimateP();
	void CompleteAnimation();
	void SwitchToMinuteTickIfNecessaryL();
	static TInt FocusChangeCb(TAny* aThisPtr);
protected:
	DDisplay* iDisplay;
private:
	TTime iUniversalTime;
	TTimeIntervalSeconds iSecondsPerUpdate;
	CMinuteTick* iMinuteTick;
	TBool iDisplayIsAnalogue;
	TBool iAnimatingOnMinTick;
	TBool iVisible;
	CAsyncCallBack iFocusChangeCallback;
	};

//
// time-device concrete classes
//

class DClock : public DTimeDevice
	{
public:
	DClock();
protected:
	virtual TInt CommandReplyLP(TInt aOpcode, TAny* aArgs);
	virtual void DoConstructL(const TUint8*& aBytePtr);
	virtual TTime TimeGivenUniversalTime(const TTime& aUniversalTime) const;
private:
	TTimeIntervalSeconds iUniversalTimeOffset;
	};

//
// message-window class
//

class DMessageWindow : public DAnimWithUtils
	{
public:
	DMessageWindow();
	virtual ~DMessageWindow();
	void StartDisplay();
	void CancelDisplay();
private:
	virtual void ConstructLP(const TUint8* aBytePtr, TBool aHasFocus);
	virtual TInt CommandReplyLP(TInt aOpcode, TAny* aArgs);
	virtual void AnimateP(TDateTime* aDateTime);
	virtual void RedrawP();
	TRect Rect() const;
	void DrawTextPortionOfDisplay(const TRect& aRect) const;
private:
	class DMessageWindowTimer : public CTimer
		{
	public:
		enum TAction
			{
			EActionStartDisplay,
			EActionCancelDisplay
			};
	private:
		DMessageWindowTimer(DMessageWindow& aOwner);
	public:
		static DMessageWindowTimer* NewL(DMessageWindow& aOwner);
		void SetAction(TAction aAction);
	private:
		// framework
		virtual void RunL();
	private:
		DMessageWindow& iOwner;
		TAction iAction;
		};
	enum
		{
		EFlagVisible		=0x01,
		EFlagFlash			=0x02,
		EFlagFlashStateOn	=0x04
		};
	enum
		{
		EBorderWidthLeft=3,
		EBorderWidthRight=4,
		EBorderWidthTop=3,
		EBorderWidthBottom=4
		};
private:
	TTimeIntervalMicroSeconds32 iDuration;
	TInt iBaselineOffset;
	CFbsFont* iFont;
	TRgb iBackgroundColor;
	TRgb iTextColor;
	TRgb iBorderColor;
	TRgb iPlinthTlColor;
	TRgb iPlinthBrColor;
	TUint iFlags;
	TBuf<RMessageWindow::EMaxTextLength> iText;
	DMessageWindowTimer* iTimer;
	};

//
// display classes
//

class DDisplay : public CBase
	{
public:
	DDisplay(const TPoint& aPosition, const TSize& aSize, const TMargins& aMargins, const STimeDeviceShadow& aShadow);
	virtual void SetInitialTimeP(const TTime& aTime)=0;
	void DrawP(MAnimWindowFunctions& aFunctions, CAnimGc& aGc) const;
	void UpdateLP(DAnimWithUtils::TFunctions& aFunctions, CAnimGc& aGc, const TTime& aTime);
	TRect RectDrawnTo() const;
	TRect RectToInvalidate() const;
	virtual void HandleCommandLP(DAnimWithUtils::TFunctions& aFunctions, CAnimGc& aGc, const TTime& aTime, TInt aOpcode, TAny* aArgs);
	virtual void PositionOrSizeHasChanged();
	void SetPosition(const TPoint& aPosition);
protected:
	void DrawClippedToDisplayRegionP(MAnimWindowFunctions& aFunctions, CAnimGc& aGc, TRegion* aRegion=NULL) const;
	virtual void DoDrawP(CAnimGc& aGc, TBool aFullDrawRequired, const TRect& aClippingRect) const=0;
	virtual void UpdateDisplayDataP(MAnimGeneralFunctions& aFunctions, const TTime& aTime, TRegion* aRegion)=0;
	void UpdateDisplayDataAndDrawClippedToDisplayRegionP(DAnimWithUtils::TFunctions& aFunctions, CAnimGc& aGc, const TTime& aTime, TRegion* aRegion);
	TBool IsVisibleAndNotHidden(MAnimWindowFunctions& aFunctions) const;
protected:
	STimeDeviceShadow iShadow;
private:
	TPoint iPosition;
	TSize iSize;
	TBool iVisible;
	TMargins iMargins;
	};

//

class DDigitalDisplay : public DDisplay
	{
public:
	DDigitalDisplay(const TPoint& aPosition, const TSize& aSize, const TMargins& aMargins, const STimeDeviceShadow& aShadow, TRgb aBackgroundColor, TInt aNumTextSections);
	void AddTextSectionLP(DDigitalDisplayTextSection* aTextSection);
	virtual void SetInitialTimeP(const TTime& aTime);
	virtual ~DDigitalDisplay();
	virtual void HandleCommandLP(DAnimWithUtils::TFunctions& aFunctions, CAnimGc& aGc, const TTime& aTime, TInt aOpcode, TAny* aArgs);
	inline void LimitTimeResolutionToMinutes(TBool aLimitToMinutes);
protected:
	virtual void DoDrawP(CAnimGc& aGc, TBool aFullDrawRequired, const TRect& aClippingRect) const;
	virtual void UpdateDisplayDataP(MAnimGeneralFunctions& aFunctions, const TTime& aTime, TRegion* aRegion);
private:
	struct STextSectionList
		{
		TInt16 iNumTextSections;
		TInt16 iNumTextSectionsAdded;
		DDigitalDisplayTextSection** iTextSections;
		};
private:
	TRgb iBackgroundColor;
	STextSectionList iTextSections;
	TBool iFlashStateOn;
	TBool iTimeResolutionLimitedToMinutes;
	};
	
inline void DDigitalDisplay::LimitTimeResolutionToMinutes(TBool aLimitToMinutes)
	{
	iTimeResolutionLimitedToMinutes=aLimitToMinutes;
	}

//

class DAnalogDisplay : public DDisplay
	{
public:
	enum THandsFlag
		{
		ESecondHand = 0x0001,
		EMinuteHand = 0x0002,
		EHourHand	= 0x0004
		};
public:
	DAnalogDisplay(const TPoint& aPosition, const TSize& aSize, const TMargins& aMargins, const STimeDeviceShadow& aShadow, TInt aNumHands);
	void ConstructL(MAnimGeneralFunctions& iFunctions, TInt aFaceHandle, TInt aFaceMaskHandle);
	void AddHandLP(DAnalogDisplayHand* aHand);
	void AddAmPmLP(MAnimGeneralFunctions& aFunctions, const TPoint& aPositionRelativeToFace, const TSize& aSize, const STimeDeviceShadow& aShadow, TRgb aBackgroundColor, TInt aFontHandle, TRgb aTextColor);
	virtual void SetInitialTimeP(const TTime& aTime);
	virtual ~DAnalogDisplay();
	virtual void PositionOrSizeHasChanged();
	TRect FaceRect() const;
	void DisableHands(TBool aHourHand, TBool aMinuteHand, TBool aSecondHand);
	void EnableHands(TBool aHourHand, TBool aMinuteHand, TBool aSecondHand);
private:
	virtual void DoDrawP(CAnimGc& aGc, TBool aFullDrawRequired, const TRect& aClippingRect) const;
	virtual void UpdateDisplayDataP(MAnimGeneralFunctions& aFunctions, const TTime& aTime, TRegion* aRegion);
	TPoint HandCenter() const;
	TPoint AmPmPosition() const;
	virtual void HandleCommandLP(DAnimWithUtils::TFunctions& aFunctions, CAnimGc& aGc, const TTime& aTime, TInt aOpcode, TAny* aArgs);
	void DrawHands(CAnimGc& aGc, const TPoint& aCenter,  const TRgb* aShadowColour=NULL) const;
private:
	class DAmPmDisplay : public DDigitalDisplay
		{
	public:
		DAmPmDisplay(const TPoint& aPosition, const TSize& aSize, const TMargins& aMargins, const STimeDeviceShadow& aShadow, TRgb aBackgroundColor);
		void ConstructLP(MAnimGeneralFunctions& aFunctions, TRgb aTextColor, TInt aFontHandle);
		virtual void DoDrawP(CAnimGc& aGc, TBool aFullDrawRequired, const TRect& aClippingRect) const;
		virtual void UpdateDisplayDataP(MAnimGeneralFunctions& aFunctions, const TTime& aTime, TRegion* aRegion);
		};
	struct SHandList
		{
		TInt16 iNumHands;
		TInt16 iNumHandsAdded;
		DAnalogDisplayHand** iHands;
		TInt iHandsDisabled;
		};
private:
	CFbsBitmap* iFace;
	CFbsBitmap* iFaceMask;
	SHandList iHands;
	DAmPmDisplay* iAmPm;
	TPoint iAmPmPositionRelativeToFace;
	};

//
// clock DLL class
//

class DClockDll : public CAnimDll
	{
public:
	DClockDll();
	virtual CAnim* CreateInstanceL(TInt aType);
	};

//
// global functions
//

GLREF_C void Panic(TClockServerPanic aReason);
GLREF_C void PanicClientFromServer();

//

#endif

