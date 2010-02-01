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

#if !defined(__CLOCK_H__)
#define __CLOCK_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__W32STD_H__)
#include <w32std.h>
#endif

//exported due to dependancies
#include <graphics/clock/displayaddition.h>

/**
@file
@publishedAll
 */

/** Horizontal alignment options for text in a digital clock's display.

@see TDigitalDisplayTextSection 
@publishedAll
@released */
enum TDigitalDisplayHorizontalTextAlignment
	{
	/** Left align text. */
	EDigitalDisplayHorizontalTextAlignmentLeft,
	/** Centre align text. */
	EDigitalDisplayHorizontalTextAlignmentCenter,
	/** Right align text. */
	EDigitalDisplayHorizontalTextAlignmentRight
	};

/** Vertical alignment options for text in a digital clock's display.

@see TDigitalDisplayTextSection 
@publishedAll
@released */
enum TDigitalDisplayVerticalTextAlignment
	{
	/** Top align text. */
	EDigitalDisplayVerticalTextAlignmentTop,
	/** Centre align text, including the character descent. */
	EDigitalDisplayVerticalTextAlignmentCenterInclDescent,
	/** Centre align text, excluding the character descent. */
	EDigitalDisplayVerticalTextAlignmentCenterExclDescent,
	/** Bottom align text, including the character descent. */
	EDigitalDisplayVerticalTextAlignmentBottomInclDescent,
	/** Bottom align text, excluding the character descent. */
	EDigitalDisplayVerticalTextAlignmentBottomExclDescent
	};

/** Special characters that can be used in a digital clock display.

@see TDigitalDisplayTextSection 
@publishedAll
@released */
enum TDigitalDisplayLayoutChar
	{
	/** A flashing block to delimit different sections of the display.
	 */
	/** A flashing block to delimit different sections of the display. */
	EDigitalDisplayLayoutCharFlashingBlockDelimiter=1
	};

//
/** Different types of hand for an analogue clock. 

@publishedAll
@released */
enum TAnalogDisplayHandType
	{
	/** A hand that performs one revolution every 12 hours. */
	EAnalogDisplayHandOneRevPer12Hours,
	/** A hand that performs one revolution every hour. */
	EAnalogDisplayHandOneRevPerHour,
	/** A hand that performs one revolution every minute. */
	EAnalogDisplayHandOneRevPerMinute
	};

//
// miscellaneous structs
//


/** Determines how shadows are added to the clock display. 

@publishedAll
@released */
struct STimeDeviceShadow
	{
	/** True if shadows should be displayed, else false. */
	TBool iIsOn;
	/** Colour of the shadows. */
	TRgb iColor;
	/** Offset of shadows from foreground. */
	TPoint iOffset;
	};


/** Defines the display parameters of the AM/PM display for an analogue clock.

@see RAnalogClock 
@publishedAll
@released */
struct SAnalogDisplayAmPm
	{
	/** Position relative to the clock face. */
	TPoint iPositionRelativeToFace;
	/** Size. */
	TSize iSize;
	/** Shadow settings. */
	STimeDeviceShadow iShadow;
	/** Background colour. */
	TRgb iBackgroundColor;
	/** Handle to the font to use. This can be obtained using CFbsFont::Handle().
	
	@see CFbsFont::Handle() */
	TInt iFontHandle;
	/** Colour for text. */
	TRgb iTextColor;
	};

//
// display-addition classes
//


/** A text section for a digital clock.

@see RDigitalClock 
@publishedAll 
@released */
class TDigitalDisplayTextSection : public TDisplayAddition
	{
public:
	IMPORT_C TDigitalDisplayTextSection(TInt aFontHandle, TRgb aTextColor, TDigitalDisplayHorizontalTextAlignment aHorizontalAlignment,
																TDigitalDisplayVerticalTextAlignment aVerticalAlignment,
																TInt aHorizontalMargin, TInt aVerticalMargin, const TDesC& aFormat);
																// N.B. the font passed in to aFontHandle cannot be destroyed until the
																// RDigitalClock has been completely constructed, including all necessary
																// calls to RDigitalClock::AddTextSectionL()
	};

//


/** A hand for an analogue clock.

A hand is a vector drawing made from a number of features (lines, circles, 
polylines). These are specified with the hand assumed to be in the 12 o'clock 
position, with TPoint(0,0) being the center of the clock.

@see RAnalogClock 
@publishedAll 
@released */
class TAnalogDisplayHand : public TDisplayAddition
	{
public:
	IMPORT_C TAnalogDisplayHand(TAnalogDisplayHandType aType);
	IMPORT_C void AddLine(CGraphicsContext::TPenStyle aPenStyle, TRgb aPenColor, const TSize& aPenSize,
																const TPoint& aStartPoint, const TPoint& aEndPoint);
	IMPORT_C void AddPolyLine(CGraphicsContext::TPenStyle aPenStyle, TRgb aPenColor, const TSize& aPenSize,
																CGraphicsContext::TBrushStyle aBrushStyle, TRgb aBrushColor,
																TBool aClosed, const CArrayFix<TPoint>* aPointList); // aPointList is not destroyed
	IMPORT_C void AddCircle(CGraphicsContext::TPenStyle aPenStyle, TRgb aPenColor, const TSize& aPenSize,
																CGraphicsContext::TBrushStyle aBrushStyle, TRgb aBrushColor,
																const TPoint& aCircleCenter, TInt aRadius);	
	inline TInt NumFeatures() const 
	/** Gets the number of features added to the hand. */
		{return *iNumFeaturesPtr;}
private:
	void AppendType(TAnalogDisplayHandFeatureType aType);
private:
	TInt* iNumFeaturesPtr;
	};

//
// utility class
//


/** Utility class to support clock animation. 

@publishedAll
@released
*/
class RAnimWithUtils : public RAnim
	{
protected:
	RAnimWithUtils(RAnimDll& aAnimDll, const RWindowBase& aWindow);
	void AppendToConstructorBufL(const TDesC8& aData);
	void SendConstructorBufIfCompleteL(TInt aAnimatedObjectType);
	void SendConstructorBufL(TInt aAnimatedObjectType);
	TBool ConstructorBufExists() const;
	TBool ConstructorBufAlreadySent() const;
	TConstructorBuf8& ConstructorBuf() const;
	void SetNumAdditionsStillExpected(TInt aNumAdditionsStillExpected);
public:
	IMPORT_C virtual void Close();
private:
	TConstructorBuf8* iConstructorBuf; // on the heap as it is only required for construction
	TBool iConstructorBufAlreadySent;
	const RWindowBase& iWindow;
	TInt iNumAdditionsStillExpected;
	};

//
// time-device abstract classes
//



/** Sets display parameters for clocks.
 
@publishedAll
@released
*/
class RTimeDevice : public RAnimWithUtils
	{
protected:
	RTimeDevice(RAnimDll& aAnimDll, const RWindowBase& aWindow);
	void AppendDisplayTypeL(TDisplayType aType);
	void AppendDigitalDisplayConstructorArgsL(const TPoint& aPosition, const TSize& aSize, const TMargins& aMargins, const STimeDeviceShadow& aShadow,
																TRgb aBackgroundColor, TInt aNumTextSections);
	void AppendAnalogDisplayConstructorArgsL(const TPoint& aPosition, const TSize& aSize, const TMargins& aMargins, const STimeDeviceShadow& aShadow,
																TInt aFaceHandle, TInt aFaceMaskHandle, TInt aNumHands, const SAnalogDisplayAmPm* aAmPm);
public:
	IMPORT_C void SetVisible(TBool aVisible); // can only be called after full construction - by default clocks are invisible
	IMPORT_C void SetPositionAndSize(const TPoint& aPosition, const TSize& aSize); // can only be called after full construction
	IMPORT_C void SetPosition(const TPoint& aPosition); // can only be called after full construction
	IMPORT_C void SetSize(const TSize& aSize); // can only be called after full construction
	IMPORT_C void UpdateDisplay(); // can only be called after full construction
	IMPORT_C void Draw(); // can only be called after full construction
	};

//


/** Sets the time for clocks.

@publishedAll
@released */
class RClock : public RTimeDevice
	{
protected:
	RClock(RAnimDll& aAnimDll, const RWindowBase& aWindow);
	void AppendClockConstructorArgsL(TTimeIntervalSeconds aUniversalTimeOffset);
public:
	IMPORT_C void SetUniversalTimeOffset(TTimeIntervalSeconds aUniversalTimeOffset); // can only be called after full construction
	};

//
// time-device concrete classes
//


/** A digital clock.

A digital clock is composed of one or more text sections, which define
how the time information is displayed.

@publishedAll 
@released */
class RDigitalClock : public RClock
	{
public:
	IMPORT_C RDigitalClock(RAnimDll& aAnimDll, const RWindowBase& aWindow);
	IMPORT_C void ConstructL(TTimeIntervalSeconds aUniversalTimeOffset, const TPoint& aPosition, const TSize& aSize, const TMargins& aMargins,
																const STimeDeviceShadow& aShadow, TRgb aBackgroundColor, TInt aNumTextSections);
	IMPORT_C void AddTextSectionL(const TDigitalDisplayTextSection& aTextSection);
	IMPORT_C void SetBackgroundColor(TRgb aBackgroundColor, TRgb aShadowColor); // can only be called after full construction
	IMPORT_C void SetTextColor(TRgb aTextColor);

	};

//



/** An analogue clock.

@see CFbsBitmap::Handle() 
@publishedAll 
@released */
class RAnalogClock : public RClock
	{
public:
	IMPORT_C RAnalogClock(RAnimDll& aAnimDll, const RWindowBase& aWindow);
	IMPORT_C void ConstructL(TTimeIntervalSeconds aUniversalTimeOffset, const TPoint& aPosition, const TSize& aSize, const TMargins& aMargins,
																const STimeDeviceShadow& aShadow, TInt aFaceHandle, TInt aFaceMaskHandle, TInt aNumHands, const SAnalogDisplayAmPm* aAmPm=NULL);
																// N.B. the bitmap(s) passed in to aFaceHandle and aFaceMaskHandle in these
																// ConstructL functions cannot be destroyed until the RAnalogClock has been
																// completely constructed, including all necessary calls to
																// RAnalogClock::AddHandL() - aFaceMaskHandle may be 0
	IMPORT_C void AddHandL(const TAnalogDisplayHand& aHand);
	IMPORT_C void SetBackgroundColor(TRgb aBackgroundColor, TRgb aShadowColor); // can only be called after full construction
	IMPORT_C void SetTextColor(TRgb aTextColor);
	IMPORT_C void SetPenColor(const TRgb aPenColor);
	IMPORT_C void SetBrushColor(const TRgb aBrushColor);
	};

//
// message-window class
//



/** A configurable window that appears for a brief time to display a message to 
the user and then disappears.

This is the basic class that is used by classes such as CEikonEnv and CEikMsgWin 
to provide information and message windows. Such higher-level classes would 
normally be used by client applications rather than RMessageWindow. This class 
can be used though to implement specialist new classes. 

Note that this class is in the same library as the Clock API for implementation 
reasons only.

@see CEikMsgWin
@see CEikonEnv 
@publishedAll 
@released */
class RMessageWindow : public RAnimWithUtils
	{
public:
	/** Defines the maximum length of text in the message. */
	enum
		{
		/** Maximum length of text in the message. */
		EMaxTextLength=80
		};
public:
	IMPORT_C RMessageWindow(RAnimDll& aAnimDll, const RWindowBase& aWindow);
	IMPORT_C void ConstructL(TInt aBaselineOffset, TInt aFontHandle, TRgb aBackgroundColor, TRgb aTextColor);
	IMPORT_C void ConstructL(TInt aBaselineOffset, TInt aFontHandle, TRgb aBackgroundColor, TRgb aTextColor, TRgb aBorderColor);
	IMPORT_C void StartDisplay(TBool aFlash, TTimeIntervalMicroSeconds32 aInitialDelay, const TDesC& aText);
	IMPORT_C void StartDisplay(TBool aFlash, TTimeIntervalMicroSeconds32 aInitialDelay, TTimeIntervalMicroSeconds32 aDuration, const TDesC& aText);
	IMPORT_C void CancelDisplay();
	IMPORT_C void GetBorders(TMargins& aBorders);
	IMPORT_C void SetBackgroundColor(TRgb aBackgroundColor);
	IMPORT_C void SetTextColor(TRgb aTextColor);
	IMPORT_C void SetBorderColor(TRgb aBorderColor);
	IMPORT_C void SetPlinthColors(TRgb aTl,TRgb aBr);
	};

#endif

