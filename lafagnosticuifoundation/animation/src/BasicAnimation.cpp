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

#include "BasicAnimation.h"

#include <w32std.h>
#include <coecntrl.h>

#include "AnimationDataProvider.h"
#include "Animator.h"
#include "AnimationConfig.h"
#include "AnimationTls.h"
#include "AnimationEvents.h"
#include "AnimationTicker.h"
#include "coeaui.h" 
#include "basicanimationext.h"
#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <vwsdefpartner.h>
#endif

	
/**
Two stage constructor.

This creates and returns a new basic animation.

@param aDataProvider The data provider from which the animation contents will
be obtained.  The animation takes ownership of this object
@param aPoint The starting position of the animation in the window (top left corner)
@param aWs A session with the window server
@param aWindow The window in which the animation will be drawn
@param aObserver An optional receiver of animation events (such as errors)
@return The new object
*/
EXPORT_C CBasicAnimation* CBasicAnimation::NewL(CAnimationDataProvider* aDataProvider, const TPoint& aPoint, RWsSession& aWs, RWindow& aWindow, MAnimationObserver* aObserver)
	{
	return CBasicAnimation::NewL(aDataProvider, aPoint, aWs, aWindow, aDataProvider->DataType(), aObserver);
	}
	
/**
Two stage constructor.

This is identical to the other NewL except that it allows an alternative data
type to be specified.  Unless you are trying to use a custom animator class
the other form of constructor should be used.

@param aDataProvider The data provider from which the animation contents will
be obtained.  The animation takes ownership of this object
@param aPoint The starting position of the animation in the window (top left corner)
@param aWs A session with the window server
@param aWindow The window in which the animation will be drawn
@param aDataType Overrides the data type specified by the data provider
@param aObserver An optional receiver of animation events (such as errors)
@return The new object
*/
EXPORT_C CBasicAnimation* CBasicAnimation::NewL(CAnimationDataProvider* aDataProvider, const TPoint& aPoint, RWsSession& aWs, RWindow& aWindow, const TDesC8& aDataType, MAnimationObserver* aObserver)
	{
	__ASSERT_ALWAYS(aDataProvider, User::Leave(KErrArgument));
	CleanupStack::PushL(aDataProvider);
	CBasicAnimation* self = new (ELeave) CBasicAnimation(aDataProvider, aPoint, &aWs, &aWindow, aObserver);
	CleanupStack::Pop(aDataProvider);
	CleanupStack::PushL(self);
	self->ConstructL(aDataType);
	CleanupStack::Pop(self);
	
	return self;
	}
	
/**
Two stage constructor.
This creates and returns a new basic animation.

@param aDataProvider The data provider from which the animation contents will
be obtained.  The animation takes ownership of this object
@param aPoint The starting position of the animation in the window (top left corner)
@param aObserver An optional receiver of animation events (such as errors)
@param aHost The CCoeControl responsible for drawing this animation
@return The new object
*/
EXPORT_C CBasicAnimation* CBasicAnimation::NewL(CAnimationDataProvider* aDataProvider, const TPoint& aPoint, MAnimationObserver* aObserver, const CCoeControl* aHost)
	{
	return CBasicAnimation::NewL(aDataProvider, aPoint, aDataProvider->DataType(), aObserver, aHost);
	}

/**
Two stage constructor.

This is identical to the other NewL except that it allows an alternative data
type to be specified.  Unless you are trying to use a custom animator class
the other form of constructor should be used.

@param aDataProvider The data provider from which the animation contents will
be obtained.  The animation takes ownership of this object
@param aPoint The starting position of the animation in the window (top left corner)
@param aDataType Overrides the data type specified by the data provider
@param aObserver An optional receiver of animation events (such as errors)
@param aHost The CCoeControl responsible for drawing this animation
@return The new object
*/
EXPORT_C CBasicAnimation* CBasicAnimation::NewL(CAnimationDataProvider* aDataProvider, const TPoint& aPoint, const TDesC8& aDataType, MAnimationObserver* aObserver, const CCoeControl* aHost)
	{
	__ASSERT_ALWAYS(aDataProvider, User::Leave(KErrArgument));
	CleanupStack::PushL(aDataProvider);
	CBasicAnimation* self = new (ELeave) CBasicAnimation(aDataProvider, aPoint, aObserver);																											
	CleanupStack::Pop(aDataProvider);
	CleanupStack::PushL(self);
	self->ConstructL(aDataType,aHost);	
	CleanupStack::Pop(self);
	return self;
	}

/** Destructor. */
EXPORT_C CBasicAnimation::~CBasicAnimation()
	{
	while (iFreezeCount > 0)
		CBasicAnimation::Unfreeze();
	delete iAnimator;
	delete iRenderGc;
	delete iMaskDevice;
	delete iBitmapDevice;
	delete iMask;
	delete iBitmap;
	delete iDataProvider;
	delete iDataType;
	delete iBasicAnimationExt;
	iObserver = NULL;
	if(iTls)
		{
		iTls->Close();
		iTls = NULL;
		}
	iWs = NULL;
	iWindow = NULL;
	}
	
/** Implements CAnimation::Start.

@param aConfig Flags and possibly data regarding the way in which the animation should be run */
void CBasicAnimation::Start(const TAnimationConfig& aConfig)
	{
	iAnimator->Start(aConfig);
	}
	
/** Implements CAnimation::Stop.*/
void CBasicAnimation::Stop()
	{
	iAnimator->Stop();
	}
	
/** Implements CAnimation::Pause.*/
void CBasicAnimation::Pause()
	{
	iAnimator->Pause();
	}

/** Implements CAnimation::Resume.*/
void CBasicAnimation::Resume()
	{
	iAnimator->Resume();
	}
	
/** Implements CAnimation::Hold.*/
void CBasicAnimation::Hold()
	{
	iAnimator->Hold();
	}
	
/** Implements CAnimation::Unhold.*/
void CBasicAnimation::Unhold()
	{
	iAnimator->Unhold();
	}
	
/** Implements CAnimation::SetPosition.

@param aPoint The new location of the top left corner of the animation, relative to the window in which it is to be drawn */
void CBasicAnimation::SetPosition(const TPoint& aPoint)
	{
	if (iBasicAnimationExt && (iPoint != aPoint))
		{
		iPoint = aPoint;
		}
	else if (iWindow)
		{
		iWindow->Invalidate(TRect(iPoint, iPoint + iSize));
		iPoint = aPoint;
		iWindow->Invalidate(TRect(iPoint, iPoint + iSize));
		}
	}
	
/** Implements CAnimation::Freeze.*/
void CBasicAnimation::Freeze()
	{
	++iFreezeCount;
	iTls->Ticker()->Freeze();
	}
	
/** Implements CAnimation::Unfreeze.*/
void CBasicAnimation::Unfreeze()
	{
	--iFreezeCount;
	iTls->Ticker()->Unfreeze();
	}

/**
This function should be called with a valid graphics context whenever
a redraw event is received for the window this animation resides in.

The graphics context attributes will not be modified, which means effects such
as opacity can be applied to it before the call to Draw.

@param aGc A graphics context which will be used for blitting the animation
frame onto the window
*/
EXPORT_C void CBasicAnimation::Draw(CWindowGc& aGc) const
	{
	if (iFlags & EAnimationInitialised)
		{
		aGc.BitBltMasked(iPoint,iBitmap, TRect(iSize),iMask, EFalse);
		}
	}

/**
This function lets you set the host at a later stage if you haven't got access to it during
construction, or if you for some reason need to change it in run time.

@param aHost 
*/
EXPORT_C void CBasicAnimation::SetHostL(const CCoeControl* aHost)
	{
	if (iBasicAnimationExt)
		{
		iBasicAnimationExt->iHost = aHost;
		}
	else
		{
		// If iBasicAnimationExt is 0 it means the NewL that takes an RWindow was used, 
		// host is not supported in this case
		User::Leave(KErrNotSupported);
		}
	}
	
void CBasicAnimation::AnimatorDraw()
	{
	if (iFlags & EAnimationInitialised)
		{
		iRenderGc->Activate(iBitmapDevice);
		iAnimator->Draw(*iRenderGc);
		iRenderGc->Activate(iMaskDevice);
		iAnimator->DrawMask(*iRenderGc);
		if (iBasicAnimationExt && iBasicAnimationExt->iHost)
			{
			iBasicAnimationExt->iHost->DrawNow();
			}
		else if (iWindow)
			{
			iWindow->Invalidate((TRect(iPoint, iPoint + iSize)));
			iWs->Flush();	
			}
		}
	}
	
void CBasicAnimation::DataProviderEventL(TInt aEvent, TAny* aData, TInt aDataSize)
	{
	if (!(aEvent & ~EAnimationReservedEvents))
		{
		switch(aEvent)
			{
			case EAnimationDataChanged:
				iDataProvider->StartL();
				break;
			case EAnimationDataProviderError:
				if (iObserver)
					{
					iObserver->AnimationEvent(*this, MAnimationObserver::EDataProviderError, aData);
					}
				break;
			default:
				User::Leave(KErrArgument);
			}
		}
	iAnimator->DataEventL(aEvent, aData, aDataSize);
	}

CBasicAnimation::CBasicAnimation(CAnimationDataProvider* aDataProvider, const TPoint& aPoint, RWsSession* aWs, RWindow* aWindow, MAnimationObserver* aObserver) :
iObserver (aObserver),
iDataProvider(aDataProvider),
iPoint(aPoint),
iWs(aWs),
iWindow(aWindow)
	{
	}

CBasicAnimation::CBasicAnimation(CAnimationDataProvider* aDataProvider, const TPoint& aPoint, MAnimationObserver* aObserver) :iObserver(aObserver),iDataProvider(aDataProvider), iPoint(aPoint)
	{
	}

// This ConstructL is called when no RWindow is provided but maybe a host
void CBasicAnimation::ConstructL(const TDesC8& aDataType,const CCoeControl* aHost)
	{
	iDataType = HBufC8::NewL(aDataType.Length());
	(*iDataType) = aDataType;
	
	iTls = CAnimationTls::NewL();
	iAnimator = CAnimator::NewL(this);
	iRenderGc = CFbsBitGc::NewL();
	
	iBasicAnimationExt = CBasicAnimationExt::NewL(aHost);
	if (iBasicAnimationExt->iHost)
		{
		iBitmap = new (ELeave) CWsBitmap(iBasicAnimationExt->iHost->ControlEnv()->WsSession());
		User::LeaveIfError(iBitmap->Create(TSize(0,0), iBasicAnimationExt->iHost->ControlEnv()->ScreenDevice()->DisplayMode()));
		iMask = new (ELeave) CWsBitmap(iBasicAnimationExt->iHost->ControlEnv()->WsSession());
		}
	else
		{
		iBitmap = new (ELeave) CFbsBitmap();
		User::LeaveIfError(iBitmap->Create(TSize(0,0), CCoeEnv::Static()->ScreenDevice()->DisplayMode()));
		iMask = new (ELeave) CFbsBitmap();
		}

	User::LeaveIfError(iMask->Create(TSize(0,0), EGray256));
		
	iDataProvider->SetObserver(this);
	iDataProvider->StartL();
	}

// This ConstructL is called when an RWindow is provided
void CBasicAnimation::ConstructL(const TDesC8& aDataType)
	{
	iDataType = HBufC8::NewL(aDataType.Length());
	(*iDataType) = aDataType;
	
	iTls = CAnimationTls::NewL();
	iAnimator = CAnimator::NewL(this);
	iRenderGc = CFbsBitGc::NewL();
	iBitmap = new (ELeave)  CWsBitmap(*iWs);
	User::LeaveIfError(iBitmap->Create(TSize(0,0), iWindow->DisplayMode()));
	iMask = new (ELeave) CWsBitmap(*iWs);
	User::LeaveIfError(iMask->Create(TSize(0,0), EGray256));
		
	iDataProvider->SetObserver(this);
	iDataProvider->StartL();
	}
	
void CBasicAnimation::AnimatorInitialisedL(const TSize& aSize)
	{
	iSize = aSize;
	User::LeaveIfError(iBitmap->Resize(iSize));
	User::LeaveIfError(iMask->Resize(iSize));

	delete iBitmapDevice;
	iBitmapDevice = NULL;
	delete iMaskDevice;
	iMaskDevice = NULL;

	iBitmapDevice = CFbsBitmapDevice::NewL(iBitmap);
	iMaskDevice = CFbsBitmapDevice::NewL(iMask);

	iRenderGc->Activate(iMaskDevice);
	iRenderGc->SetBrushStyle(CGraphicsContext::ESolidBrush);
	iRenderGc->SetBrushColor(KRgbBlack);
	iRenderGc->Clear();
	
	iFlags |= EAnimationInitialised;

	if(iObserver)
		{
		iObserver->AnimationEvent(*this, MAnimationObserver::EAnimationInitialized, NULL);
		}
	}


void CBasicAnimation::AnimatorResetL()
	{
	iFlags &= ~EAnimationInitialised;
	
	if (iBasicAnimationExt && iBasicAnimationExt->iHost)
		{
		iBasicAnimationExt->iHost->DrawNow();	
		}
	else if (iWindow)
		{
		iWindow->Invalidate(TRect(iPoint, iPoint + iSize));
		}
	iSize.iWidth = 0;
	iSize.iHeight = 0;
	delete iBitmapDevice;
	iBitmapDevice = NULL;
	delete iMaskDevice;
	iMaskDevice = NULL;
	iFlags = 0;
	}

const TPtrC8 CBasicAnimation::AnimatorDataType() const
	{
	return *iDataType;
	}

CAnimationTicker& CBasicAnimation::AnimatorTicker()
	{
	return *iTls->Ticker();
	}
	
/** Reserved for future use */
EXPORT_C void CBasicAnimation::CBasicAnimation_Reserved1() {}

/** Reserved for future use */
EXPORT_C void CBasicAnimation::CBasicAnimation_Reserved2() {}


