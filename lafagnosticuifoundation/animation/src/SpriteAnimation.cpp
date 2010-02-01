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

#include "SpriteAnimation.h"

#include <w32std.h>
#include <coecntrl.h>

#include "AnimationDataProvider.h"
#include "AnimationConfig.h"
#include "SpriteAnimationClient.h"
#include "AnimationEvents.h"
#include "spriteanimationext.h"

_LIT(KAnimationServerDll, "AnimationServer.dll");

/**
Two stage constructor.

This creates and returns a new sprite animation.

@param aDataProvider The data provider from which the animation contents will
be obtained.  The animation takes ownership of this object
@param aPoint The starting position of the sprite in the window
@param aWsSession A session with the window server
@param aWindow The window in which to draw the animation
@param aObserver An optional receiver of animation events (such as errors)
@return The new object
*/
EXPORT_C CSpriteAnimation* CSpriteAnimation::NewL(CAnimationDataProvider* aDataProvider, const TPoint& aPoint, RWsSession& aWsSession, RWindow& aWindow, MAnimationObserver* aObserver)
	{
	return CSpriteAnimation::NewL(aDataProvider, aPoint, aWsSession, aWindow, aDataProvider->DataType(), aObserver);
	}
	
/**
Two stage constructor.

This is identical to the other NewL except that it allows an alternative data
type to be specified.  Unless you are trying to use a custom animator class
the other form of constructor should be used.

@param aDataProvider The data provider from which the animation contents will
be obtained.  The animation takes ownership of this object
@param aPoint The starting position of the sprite in the window
@param aWsSession A session with the window server
@param aWindow The window in which to draw the animation
@param aDataType Overrides the data type specified by the data provider
@param aObserver An optional receiver of animation events (such as errors)
@return The new object
*/
EXPORT_C CSpriteAnimation* CSpriteAnimation::NewL(CAnimationDataProvider* aDataProvider, const TPoint& aPoint, RWsSession& aWsSession, RWindow& aWindow, const TDesC8& aDataType, MAnimationObserver* aObserver)
	{
	CleanupStack::PushL(aDataProvider);
	CSpriteAnimation* self = new (ELeave) CSpriteAnimation(aDataProvider, aWsSession);
	CleanupStack::Pop(aDataProvider);
	CleanupStack::PushL(self);
	self->ConstructL(aPoint, aWindow, aDataType, aObserver);
	CleanupStack::Pop(self);
	return self;
	}

/**
Two stage constructor.

This creates and returns a new sprite animation.

@param aDataProvider The data provider from which the animation contents will
be obtained.  The animation takes ownership of this object
@param aPoint The starting position of the sprite in the window
@param aWsSession A session with the window server
@param aWindow The window in which to draw the animation
@param aObserver An optional receiver of animation events (such as errors)
@return The new object
*/
EXPORT_C CSpriteAnimation* CSpriteAnimation::NewL(CAnimationDataProvider* aDataProvider, const TPoint& aPoint, MAnimationObserver* aObserver, const CCoeControl* aHost)
	{
	return CSpriteAnimation::NewL(aDataProvider, aPoint, aDataProvider->DataType(), aObserver, aHost);
	}
	
/**
Two stage constructor.

This is identical to the other NewL except that it allows an alternative data
type to be specified.  Unless you are trying to use a custom animator class
the other form of constructor should be used.

@param aDataProvider The data provider from which the animation contents will
be obtained.  The animation takes ownership of this object
@param aPoint The starting position of the sprite in the window
@param aWsSession A session with the window server
@param aWindow The window in which to draw the animation
@param aDataType Overrides the data type specified by the data provider
@param aObserver An optional receiver of animation events (such as errors)
@return The new object
*/
EXPORT_C CSpriteAnimation* CSpriteAnimation::NewL(CAnimationDataProvider* aDataProvider, const TPoint& aPoint, const TDesC8& aDataType, MAnimationObserver* aObserver, const CCoeControl* aHost)
	{
	CleanupStack::PushL(aDataProvider);
	CSpriteAnimation* self = new (ELeave) CSpriteAnimation(aDataProvider, aObserver, aHost);
	CleanupStack::Pop(aDataProvider);
	CleanupStack::PushL(self);
	self->ConstructL(aPoint, aDataType);
	CleanupStack::Pop(self);
	
	return self;
	}

/** Destructor.*/
EXPORT_C CSpriteAnimation::~CSpriteAnimation()
	{
	delete iDataProvider;
	iDataProvider = NULL;
	
	if (iWsSprite)
		{
		iWsSprite->Close();
		delete iWsSprite;
		iWsSprite = NULL;
		}
		
		iAnimDll.Close();
		
	if (iClient)
		{
		delete iClient;
		iClient = NULL;
		}
		
	if(iSpriteAnimationExt)
		{
		delete iSpriteAnimationExt;
		iSpriteAnimationExt = NULL;
		}
	
	iObserver = NULL;	
	iWsSession = NULL;
	iHost = NULL;	
	}
	
EXPORT_C void CSpriteAnimation::SetHostL(const CCoeControl* aHost)
	{
	if (iHost)
		{
		Reset();
		}
	iHost = aHost;

	if (iHost)
		{
		InitializeL();
		}
	}

/** Implements CAnimation::Start.
@param aConfig Specifies run time attributes of the animation */
void CSpriteAnimation::Start(const TAnimationConfig& aConfig)
	{
	if (iFlags & EAnimationInitialized)
		{
		iClient->Start(aConfig);
		iWsSession->Flush();
		}
	}
	
/** Implements CAnimation::Stop.*/
void CSpriteAnimation::Stop()
	{
	if (iFlags & EAnimationInitialized)
		{
		iClient->Stop();
		iWsSession->Flush();
		}
	}
	
/** Implements CAnimation::Pause.*/
void CSpriteAnimation::Pause()
	{
	if (iFlags & EAnimationInitialized)
		{
		iClient->Pause();
		iWsSession->Flush();
		}
	}

/** Implements CAnimation::Resume.*/
void CSpriteAnimation::Resume()
	{
	if (iFlags & EAnimationInitialized)
		{
		iClient->Resume();
		iWsSession->Flush();
		}
	}
	
/** Implements CAnimation::Hold.*/
void CSpriteAnimation::Hold()
	{
	if (iFlags & EAnimationInitialized)
		{
		iClient->Hold();
		iWsSession->Flush();
		}
	}
	
/** Implements CAnimation::Unhold.*/
void CSpriteAnimation::Unhold()
	{
	if (iFlags & EAnimationInitialized)
		{
		iClient->Unhold();
		iWsSession->Flush();
		}
	}
	
/** Implements CAnimation::SetPosition.
@param aPoint The new coordinates of the animation (usually the top left corner) */
void CSpriteAnimation::SetPosition(const TPoint& aPoint)
	{
	if (iFlags & EAnimationInitialized)
		{
		iWsSprite->SetPosition(aPoint);
		iWsSession->Flush();
		}
	}
	
/** Implements CAnimation::Size */
EXPORT_C TSize CSpriteAnimation::Size() const
	{
	return (iFlags & EAnimationInitialized) ? iClient->Size() : TSize(0,0);
	}

/** Implements CAnimation::Freeze.*/
void CSpriteAnimation::Freeze()
	{
	if (iFlags & EAnimationInitialized)
		{
		iClient->Freeze();
		iWsSession->Flush();
		}
	}
	
/** Implements CAnimation::Unfreeze.*/
void CSpriteAnimation::Unfreeze()
	{
	if (iFlags & EAnimationInitialized)
		{
		iClient->Unfreeze();
		iWsSession->Flush();
		}
	}

CSpriteAnimation::CSpriteAnimation(CAnimationDataProvider* aDataProvider, MAnimationObserver* aObserver, const CCoeControl* aHost):
	iObserver(aObserver), 
	iDataProvider(aDataProvider),
	iHost(aHost), 
	iFlags(0)
	{
	}

// ConstructL called by the NewL functions that take a host argument		
void CSpriteAnimation::ConstructL(const TPoint& aPoint, const TDesC8& aDataType)
	{
	if (iHost)
		{
		iSpriteAnimationExt = CSpriteAnimationExt::NewL(aPoint,aDataType);
		InitializeL();
		}	
	}

void CSpriteAnimation::InitializeL()
	{
	CCoeEnv* controlEnv = iHost->ControlEnv();
	iWsSession = &controlEnv->WsSession();
	iWsSprite = new (ELeave) RWsSprite(*iWsSession);
	iAnimDll = RAnimDll(*iWsSession);
	iClient = new (ELeave) RSpriteAnimationClient(iAnimDll);
	User::LeaveIfError(iAnimDll.Load(KAnimationServerDll()));
	User::LeaveIfError(iWsSprite->Construct(*iHost->DrawableWindow(), iSpriteAnimationExt->iPoint, ESpriteNoChildClip|ESpriteNoShadows));
	TSpriteMember spriteMember;
	spriteMember.iBitmap = new (ELeave) CFbsBitmap();
	CleanupStack::PushL(spriteMember.iBitmap);
	TDisplayMode displayMode = controlEnv->ScreenDevice()->DisplayMode();
	User::LeaveIfError(spriteMember.iBitmap->Create(TSize(0,0), displayMode));
	spriteMember.iMaskBitmap = new (ELeave) CFbsBitmap();
	CleanupStack::PushL(spriteMember.iMaskBitmap);
	User::LeaveIfError(spriteMember.iMaskBitmap->Create(TSize(0,0), EGray256));
	iWsSprite->AppendMember(spriteMember);
	
	// We have a TDesC8 and we need to pass a TDesC8, but unfortunately the windows server is going
	// to be helpful by unpackaging the one we pass to it.  Packaging a variable length object seems
	// to require jumping through one or two hoops...
	// First, make a descriptor with a known type, instead of a reference to 'something':
	HBufC8* data = HBufC8::NewLC(iSpriteAnimationExt->iDataType.Length());
	*data = iSpriteAnimationExt->iDataType;
	// Second, make another descriptor large enough to hold the first one:
	TInt size = data->Size() + sizeof(HBufC8) - sizeof(TText8);
	HBufC8* datadesc = HBufC8::NewLC(size);
	datadesc->Des().Copy(static_cast<TUint8*>(static_cast<TAny*>(data)), size);
	// Finally, pass the outer descriptor to the server:
	iClient->ConstructL(*iWsSprite, datadesc->Des(), reinterpret_cast<TInt>(iObserver));

	CleanupStack::PopAndDestroy(2, data); // the data descriptors.
	CleanupStack::PopAndDestroy(2, spriteMember.iBitmap); //bitmap and mask
	
	iDataProvider->SetObserver(this);
	iDataProvider->StartL();

	iFlags |= EAnimationInitialized;
	}
	
void CSpriteAnimation::Reset()
	{
	iFlags |= (~EAnimationInitialized);
	
	iWsSession = NULL;
	
	if (iWsSprite)
		{
		iWsSprite->Close();
		delete iWsSprite;
		iWsSprite = NULL;
		}

		iAnimDll.Close();
	
	if (iClient)
		{
		iClient->Close();
		delete iClient;
		iClient = NULL;
		}
		
	if(iSpriteAnimationExt)
		{
		delete iSpriteAnimationExt;
		iSpriteAnimationExt = NULL;
		}
	}

void CSpriteAnimation::DataProviderEventL(TInt aEvent, TAny* aData, TInt aDataSize)
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
				User::Leave(KErrNotSupported);
			}
		}
	iClient->SendEventL(aEvent, aData, aDataSize);
	}

CSpriteAnimation::CSpriteAnimation(CAnimationDataProvider* aDataProvider, RWsSession& aWsSession) :
iWsSession(&aWsSession),
iAnimDll(aWsSession)
	{
	iDataProvider = aDataProvider;
	}

// ConstructL called by the NewL functions that don't take a host argument
void CSpriteAnimation::ConstructL(const TPoint& aPoint, RWindow& aWindow, const TDesC8& aDataType, MAnimationObserver* aObserver)
	{
	iWsSprite = new (ELeave) RWsSprite(*iWsSession);
	iClient = new (ELeave) RSpriteAnimationClient(iAnimDll);
	User::LeaveIfError(iAnimDll.Load(KAnimationServerDll()));
	User::LeaveIfError(iWsSprite->Construct(aWindow, aPoint, ESpriteNoChildClip|ESpriteNoShadows));
	iObserver = aObserver;
	TSpriteMember spriteMember;
	spriteMember.iBitmap = new (ELeave) CFbsBitmap();
	CleanupStack::PushL(spriteMember.iBitmap);
	User::LeaveIfError(spriteMember.iBitmap->Create(TSize(0,0), aWindow.DisplayMode()));
	spriteMember.iMaskBitmap = new (ELeave) CFbsBitmap();
	CleanupStack::PushL(spriteMember.iMaskBitmap);
	User::LeaveIfError(spriteMember.iMaskBitmap->Create(TSize(0,0), EGray256));

	iWsSprite->AppendMember(spriteMember);

	// We have a TDesC8 and we need to pass a TDesC8, but unfortunately the windows server is going
	// to be helpful by unpackaging the one we pass to it.  Packaging a variable length object seems
	// to require jumping through one or two hoops...
	// First, make a descriptor with a known type, instead of a reference to 'something':
	HBufC8* data = HBufC8::NewLC(aDataType.Length());
	*data = aDataType;
	// Second, make another descriptor large enough to hold the first one:
	TInt size = data->Size() + sizeof(HBufC8) - sizeof(TText8);
	HBufC8* datadesc = HBufC8::NewLC(size);
	datadesc->Des().Copy(static_cast<TUint8*>(static_cast<TAny*>(data)), size);
	// Finally, pass the outer descriptor to the server:
	iClient->ConstructL(*iWsSprite, datadesc->Des());
	
	CleanupStack::PopAndDestroy(2, data); // the data descriptors.
	CleanupStack::PopAndDestroy(2, spriteMember.iBitmap); //bitmap and mask

	iDataProvider->SetObserver(this);
	iDataProvider->StartL();
	iFlags |= EAnimationInitialized;
	}

/** Reserved for future use */
EXPORT_C void CSpriteAnimation::CSpriteAnimation_Reserved2()
	{
	}

