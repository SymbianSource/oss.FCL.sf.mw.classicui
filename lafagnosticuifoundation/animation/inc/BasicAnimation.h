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

#ifndef __BASICANIMATION_H__
#define __BASICANIMATION_H__

#include <animation.h>
#include <w32std.h>

class RWsSession;
class RWindow;
class CWindowGc;
class CFbsBitmap;
class CFbsBitmapDevice;
class CFbsBitGc;
class CAnimationDataProvider;
class CAnimator;
class TAnimationConfig;
class CAnimationTls;
class CAnimationTicker;
class CBasicAnimationExt;
class CCoeControl;

/**
Implementation of CAnimation for purely client side animations.

A basic animation accepts a data provider during construction, loads the
appropriate animator plugin, and implements the interface defined in
CAnimation.

A basic animation must be associated with an RWindow.  Redraw events will be
received by the client application whenever the animation needs to draw a new
frame, and it is the applications responsibility to call Draw() while handling
these events.  It is also the client applications responsibility to handle
visibility events and place the animation on hold when it isn't visible. This
saves on CPU usage and ultimately prolongs battery life.

@see CAnimationDataProvider
@publishedAll
@released
*/
class CBasicAnimation : public CAnimation, public MAnimationDrawer, public MAnimationDataProviderObserver
	{
private:
	enum TFlags
		{
		EAnimationInitialised	=	0x0001,
		};
public:
	IMPORT_C static CBasicAnimation* NewL(CAnimationDataProvider* aDataProvider, const TPoint& aPoint, RWsSession& aWs, RWindow& aWindow, MAnimationObserver* aObserver = 0);
	IMPORT_C static CBasicAnimation* NewL(CAnimationDataProvider* aDataProvider, const TPoint& aPoint, RWsSession& aWs, RWindow& aWindow, const TDesC8& aDataType, MAnimationObserver* aObserver = 0);
	IMPORT_C static CBasicAnimation* NewL(CAnimationDataProvider* aDataProvider, const TPoint& aPoint, MAnimationObserver* aObserver, const CCoeControl* aHost);
	IMPORT_C static CBasicAnimation* NewL(CAnimationDataProvider* aDataProvider, const TPoint& aPoint, const TDesC8& aDataType, MAnimationObserver* aObserver, const CCoeControl* aHost);
	IMPORT_C ~CBasicAnimation();
	
	IMPORT_C void Draw(CWindowGc& aGc) const;
	
	/** Provides an CAnimationDataProvider interface to the client application.
	@return iDataProvider A CAnimationDataProvider */
	inline CAnimationDataProvider* DataProvider() { return iDataProvider; }

	/** Returns the current drawing position.
	@return ipoint const Tpoint& */
	inline const TPoint& Position() const { return iPoint; }
	
	/** Gets the size of the smallest bounding rectangle that will be required to render the animation.

	This function is called when the animator is ready to begin animating. The animator cannot be started 
	until it has called this function.  
	@return iSize The size of the smallest bounding rectangle */
	inline const TSize& Size() const { return iSize; }
	// From CAnimation:
	virtual void Start(const TAnimationConfig& aConfig);
	virtual void Stop();
	virtual void Pause();
	virtual void Resume();
	virtual void Hold();
	virtual void Unhold();
	virtual void SetPosition(const TPoint& aPoint);
	virtual void Freeze();
	virtual void Unfreeze();
public:
	IMPORT_C void SetHostL(const CCoeControl* aHost);
protected:
	CBasicAnimation(CAnimationDataProvider* aDataProvider, const TPoint& aPoint, RWsSession* aWs, RWindow* aWindow, MAnimationObserver* aObserver);
	CBasicAnimation();
	CBasicAnimation(CAnimationDataProvider* aDataProvider, const TPoint& aPoint, MAnimationObserver* aObserver);
	void ConstructL(const TDesC8& aDataType);
	IMPORT_C virtual void CBasicAnimation_Reserved1();
	IMPORT_C virtual void CBasicAnimation_Reserved2();
	void ConstructL(const TDesC8& aDataType,const CCoeControl* aHost);
private:
	CBasicAnimation(const CBasicAnimation&); // no implementation
	CBasicAnimation& operator=(const CBasicAnimation&);		 // no implementation
	// from MAnimationDataProviderObserver
	virtual void DataProviderEventL(TInt aEvent, TAny* aData, TInt aDataSize);
	// From MAnimatorDrawer
	virtual void AnimatorDraw();
	virtual void AnimatorInitialisedL(const TSize& aSize);
	virtual void AnimatorResetL();
	virtual const TPtrC8 AnimatorDataType() const;
	virtual CAnimationTicker& AnimatorTicker();
private:
	CBasicAnimationExt* iBasicAnimationExt;
	MAnimationObserver* iObserver;
	CAnimationDataProvider* iDataProvider;
	CAnimationTls* iTls;
	TPoint iPoint;
	RWsSession* iWs;
	RWindow* iWindow;
	HBufC8* iDataType;
	TInt iFreezeCount;
	TInt iFlags;
	TSize iSize;	
	CAnimator* iAnimator;
	CFbsBitmap* iBitmap;
	CFbsBitmap* iMask;
	CFbsBitmapDevice* iBitmapDevice;
	CFbsBitmapDevice* iMaskDevice;
	CFbsBitGc* iRenderGc;
	};

#endif
