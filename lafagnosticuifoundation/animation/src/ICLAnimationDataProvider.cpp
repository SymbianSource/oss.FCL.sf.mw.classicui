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
// AnimationDataProvider.cpp
// 
//

#include "ICLAnimationDataProvider.h"

#include <fbs.h>

#include "AnimationMixins.h"
#include "AnimationEvents.h"
#include "ICLAnimationDataLoader.h"

/** Default constructor.*/
EXPORT_C CICLAnimationDataProvider::CICLAnimationDataProvider()
	{
	}
	
/**
Destructor.

It is normal for an animation to take ownership of a data provider, and hence
responsibility for destroying it.
*/
EXPORT_C CICLAnimationDataProvider::~CICLAnimationDataProvider()
	{
	Reset();
	} //lint !e1740 suppress "pointer member not directly freed or zeroed by destructor"

/**
Specifies the file to load the animation from.

This must be called before constructing an animation with this data provider.
It may be called again for other files at any point during the lifespan of
the animation, in which case current animation will be stopped.

@param aFs A session with the file server
@param aFileName The path to the image file to be loaded
*/	
EXPORT_C void CICLAnimationDataProvider::SetFileL(RFs & aFs, const TFileName& aFileName)
	{
	Reset();
	
	iDataLoader = CICLAnimationDataLoader::NewL(aFs, *this);
	iDataLoader->LoadImageDataL(aFileName);
	if (iObserver)
		{
		SendEventL(EAnimationDataChanged);
		}
	}
	
/**
Implmenets CAnimationDataProvider::StartL()

You do not need to call this function unless you are writing a new animation
type.
*/
void CICLAnimationDataProvider::StartL()
	{
	if (!iObserver)
		{
		User::Leave(KErrNotReady);
		}
		
	DataDeliveryL();
	}
	
void CICLAnimationDataProvider::DataDeliveryL()
	{
	if (!iDataLoader)
		{
		User::Leave(KErrNotReady);
		}
	
	if(!iCurrentFrame)
		{
		iCurrentFrame = CAnimationFrame::NewL();
		}
		
	DecodeImageL();
	}
	
void CICLAnimationDataProvider::Reset()
	{
	if (iDataLoader)
		{
		iDataLoader->Cancel();
		delete iDataLoader;
		iDataLoader = NULL;
		}

	delete iCurrentFrame;
	iCurrentFrame = NULL;
	}
	
void CICLAnimationDataProvider::DecodeImageL()
	{
	iDataLoader->GetNextFrameL(iCurrentFrame);
	}

CAnimationFrame::THandles CICLAnimationDataProvider::CurrentFrame() const
	{
	CAnimationFrame::THandles serverFrame;
	iCurrentFrame->GetHandles(serverFrame);
	return serverFrame;
	}

void CICLAnimationDataProvider::DataLoaderEventL(TDataLoaderEvent aEvent, TInt aError)
	{
	if (aError == KErrNone)
		{
		CAnimationFrame::THandles handle;	
		switch(aEvent)
			{
			case MICLAnimationDataLoaderObserver::EImagePartialConvert:
				handle = CurrentFrame();
				SendEventL(EBitmapAnimationNewFrame, &handle, sizeof(CAnimationFrame::THandles));
				DecodeImageL();
				break;
			case MICLAnimationDataLoaderObserver::EImageConvertComplete:
				if (!iDataLoader->IsMngAnimation())
					{
					handle = CurrentFrame();
					SendEventL(EBitmapAnimationNewFrame, &handle, sizeof(CAnimationFrame::THandles));
					}
				// If it is a mng images, the last frame submitted by ICL is superflous 
				// as a blank frame, it should not be received.
				SendEventL(EBitmapAnimationComplete);
				Reset();
				break;
			default:
				break;
			}
		}
	else
		{
		SendEventL(EAnimationDataProviderError, aError);
		}
	}

/** Reserved for future use */
EXPORT_C void CICLAnimationDataProvider::CICLAnimationDataProvider_Reserved1()
	{
	}
	
/** Reserved for future use */
EXPORT_C void CICLAnimationDataProvider::CICLAnimationDataProvider_Reserved2()
	{
	}

// From CAnimationDataProvider
/** Reserved for future use */
EXPORT_C void CICLAnimationDataProvider::CAnimationDataProvider_Reserved1()
	{
	CAnimationDataProvider::CAnimationDataProvider_Reserved1();
	}

/** Reserved for future use */
EXPORT_C void CICLAnimationDataProvider::CAnimationDataProvider_Reserved2()
	{
	CAnimationDataProvider::CAnimationDataProvider_Reserved2();
	}


EXPORT_C TPtrC8 CICLAnimationDataProvider::DataType()
	{
	return(KBitmapAnimationDataType());
	}
