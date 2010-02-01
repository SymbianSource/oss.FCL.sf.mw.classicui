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

/**
 @file
 @internalComponent 
*/

#if !defined(__BMPANSRV_H__)
#define __BMPANSRV_H__

#include <e32std.h>
#include <w32adll.h>
#include "bmpanconsts.h"
#include "bmpancli.h"
#include <e32math.h>



enum TBitmapAnimServerPanic
	{
	EAnimationServerPanicIndexOutOfRange,
	EAnimationServerPanicFrameIntervalNegative
	};

// For packaging the new animation position offset
struct SBitmapAnimNewPosition
	{
	TPoint iPosition;
	};

// For packaging the new animation index
struct SBitmapAnimIndexFrame
	{
	TInt iIndex;
	};

// For packaging the number of cycles
struct SBitmapAnimNumberOfCycles
	{
	TInt iCycles;
	};



/**
 TFrameData

 This class is used for packaging the data of one frame.
*/
class TFrameData
	{
public:
	TInt iBitmapHandle;
	TInt iMaskBitmapHandle;
	TPoint iPosition;
	TInt iIntervalInMilliSeconds;			// the time is expressed in ms
	};



/**
 TBmpAnimAttributes

 This class is used for packaging the attriutes of the animation.
*/
class TBmpAnimAttributes
	{
public:
	TBool iFlash;
	TInt iFrameIntervalInMilliSeconds;
	CBitmapAnimClientData::TPlayMode iPlayMode;
	};




/**
 class MBitmapAnimTimerObserver
*/
class MBitmapAnimTimerObserver
	{
public:
	virtual void DisplayNextFrameL()=0;
	};



/**
 class CBitmapAnimTimer

 This class is used to determine when to swap the current frame with the next one.
*/
class CBitmapAnimTimer : public CTimer
	{
public:
	~CBitmapAnimTimer();
	static CBitmapAnimTimer* NewL(MBitmapAnimTimerObserver* aObserver);
	void RunL();
private:
	CBitmapAnimTimer(MBitmapAnimTimerObserver* aObserver);
	void ConstructL();
private:
	MBitmapAnimTimerObserver* iAnimate;
	};



/**
 class MBitmapAnimFlashTimerObserver
*/

class MBitmapAnimFlashTimerObserver
	{
public:
	virtual void FlashFrame(TBool aFlash)=0;
	};



/**
 class CBitmapAnimFlashTimer
*/

class CBitmapAnimFlashTimer : public CTimer
	{
public:
	~CBitmapAnimFlashTimer();
	static CBitmapAnimFlashTimer* NewL(MBitmapAnimFlashTimerObserver* aObserver);
	void DoCancel();
	void RunL();
private:
	CBitmapAnimFlashTimer(MBitmapAnimFlashTimerObserver* aObserver);
	void ConstructL();
private:
	MBitmapAnimFlashTimerObserver* iAnimate;
	TBool iFlash;
	};



/**
 class CBitmapAnimFrameData

 This class encapsulates the information of one frame.
*/

class CBitmapAnimFrameData : public CBase
	{
public:
	static CBitmapAnimFrameData* NewL();
	static CBitmapAnimFrameData* NewLC();
	~CBitmapAnimFrameData();
	void FillFrameDataL(const TFrameData& aFrameDataArg);
	void CheckAndCreateBitmapsL();
	
private:
	CBitmapAnimFrameData();
	void InitialiseMembers();
	
public:
	CFbsBitmap* iBitmap;
	CFbsBitmap* iMaskBitmap;
	TPoint iPosition;
	TTimeIntervalMicroSeconds32 iInterval;
	};



/**
 class CBitmapAnim

 This class encapsulates the enire animation: attributes and frames.
*/

class CBitmapAnim : public CFreeTimerWindowAnim, MBitmapAnimTimerObserver//, MBitmapAnimFlashTimerObserver
	{
public:
	~CBitmapAnim();
	static CBitmapAnim* NewL();
private:
	CBitmapAnim();
private:
	enum TAnimateFlags
		{
//	State
		ERunning				= 0x0001,
		EFlashing				= 0x0002,
		EFrozen					= 0x0004,
//	Play mode
		EPlayModeCycle			= 0x0010,
		EPlayModeBounce			= 0x0020,
		EPlayForwards			= 0x0040,
		EPlayBackwards			= 0x0080,
//	General
		EFlash									= 0x0100,
		ENoBitmapWindowRestoring				= 0x0800,
		EDisplayLastFrameWhenFinished			= 0x4000,
		};

private: //Pure Virtual function from CAnim
	virtual void ConstructL(TAny *aArgs, TBool aHasFocus);
	virtual void Command(TInt aOpcode, TAny* aArgs);
	virtual TInt CommandReplyL(TInt aOpcode, TAny *aArgs);
	virtual void Animate(TDateTime* aDateTime);
	virtual void Redraw();
	virtual void FocusChanged(TBool aState);
private: //Pure Virtual function from MEventHandler
	virtual TBool OfferRawEvent(const TRawEvent &aRawEvent);
private: //Pure Virtual function from MBitmapAnimTimerObserver
	virtual void DisplayNextFrameL();
private: //Pure Virtual function from MBitmapAnimFlashTimerObserver
	virtual void FlashFrame(TBool aFlash);
private:
	void AppendFrameL(const TFrameData& aFrameData);
	inline TInt Count() const;
	void DisplayFrame(TInt aPreviousIndex=-1);
	void DrawBitmap(TInt aPreviousIndex=-1, TBool aRedraw=EFalse);
	inline TBool IsFrameDisplayable() const;
	inline TBool IsRunning() const;
	inline TBool IsFrozen() const;
	void ResetAnimation();
	void ClearFrameNow(TInt aIndex);
	void RenderFrameBackground(TInt aIndex);
	TRect CalcFrameRect(TInt aIndex);
	void SetBackgroundFrameL(TFrameData aFrameDataArg);
	void SetFlash(TBmpAnimAttributes aFlash);
	void SetFrameInterval(TBmpAnimAttributes aFrameInterval);
	TInt SetIndexFrame(SBitmapAnimIndexFrame aIndexFrame);
	void SetNumberOfCycles(SBitmapAnimNumberOfCycles aNumberOfCycles);
	void SetPlayMode(TBmpAnimAttributes aPlayMode);
	void SetPosition(SBitmapAnimNewPosition aNewPosition);
	void StartAnimationL();
	void StopAnimation();
	void UpdateCurrentIndex();
	inline TRect WindowRect() const;
	static TBool FrameNeedsRedrawing(const TRegion* aRedrawRegion, TRect aFrameScreenRect);
	void ResetFrameArray();
	void ClearFrameData();
	
private:
	RPointerArray<CBitmapAnimFrameData> iBitmapAnimFrameDataArray;
	CBitmapAnimTimer* iAnimTimer;
	CBitmapAnimFlashTimer* iFlashTimer;
	CBitmapAnimFrameData* iBackgroundFrame;

//
	TInt iDummy;
	TInt iFlags;
	TInt iIndex;
	TInt iNumberOfCycles;
	TPoint iPosition;
	TInt iWindowConfig;
	TTimeIntervalMicroSeconds32 iFrameInterval;	
	};

// Returns the number of frames store in the frame array.
inline TInt CBitmapAnim::Count() const
	{ return iBitmapAnimFrameDataArray.Count(); }

// Returns ETrue every time the index frame is valid, otherwise it returns EFalse.
inline TBool CBitmapAnim::IsFrameDisplayable() const
	{ return ( (iIndex >= 0) && iBitmapAnimFrameDataArray[iIndex]->iBitmap ); }

// Returns ETrue if the animation is running, otherwise it returns EFalse.
inline TBool CBitmapAnim::IsRunning() const
	{ return iFlags&ERunning; }

//Returns ETrue if the animation is frozen (app is not in the foreground)
inline TBool CBitmapAnim::IsFrozen() const
{ return iFlags&EFrozen; }

// Returns the available window rect.
inline TRect CBitmapAnim::WindowRect() const
	{ return TRect(TPoint(0, 0), iWindowFunctions->WindowSize()); }




/**
 CBitmapAnimDll class
*/

class CBitmapAnimDll : public CAnimDll
	{
public:
	CBitmapAnimDll();
	virtual CAnim* CreateInstanceL(TInt aType);
	};


/**
 global functions
*/
GLREF_C void Panic(TBitmapAnimServerPanic aReason);


#endif

