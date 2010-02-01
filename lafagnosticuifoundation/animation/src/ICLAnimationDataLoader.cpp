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

#include <imageconversion.h>
#include <bitmaptransforms.h>
#include <fbs.h>
#include <e32std.h>
#include <ecom/ecom.h>
#include <icl/icl_uids.hrh>
#include <icl/icl_uids_def.hrh>

#include "ICLAnimationDataLoader.h"
#include "AnimationFrame.h"

EXPORT_C CICLAnimationDataLoader* CICLAnimationDataLoader::NewL(RFs& aFs, MICLAnimationDataLoaderObserver& aCallback)
	{
	CICLAnimationDataLoader* self = new(ELeave) CICLAnimationDataLoader(aFs, aCallback);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}

CICLAnimationDataLoader::~CICLAnimationDataLoader()
	{
	Cancel();
	delete iImageDecoder;
	}
	
EXPORT_C void CICLAnimationDataLoader::LoadImageDataL(const TFileName& aFileName)
	{
	__ASSERT_ALWAYS(!IsActive(),User::Invariant());

	delete iImageDecoder;
	iImageDecoder = NULL;
	
	// mng animations need the EOptionMngSubframesNoLoops to behave as other animations (to not repeat unless told)
	iImageDecoder = CImageDecoder::FileNewL(iFs, aFileName, CImageDecoder::EOptionMngSubframesNoLoops);	
	
	iFrameCount = iImageDecoder->FrameCount();
	iCurrentFrame = KErrNotFound;
	
	TUid type; 
	TUid subtype; 
	iImageDecoder->ImageType(iCurrentFrame+1, type, subtype); 
	iIsMngAnimation = (type.iUid==KMngMimeTypeUidValue);
	}

EXPORT_C TFrameInfo CICLAnimationDataLoader::FrameInfo(const TInt aFrame) const
	{
	__ASSERT_ALWAYS(iImageDecoder, User::Invariant());
	return iImageDecoder->FrameInfo(aFrame);
	}

/**
Not valid for mng animations, for which TFrameInfo::EMngMoreFramesToDecode should be used
to find out if there are any more frames to decode.
@see CImageDecoder::FrameCount()
@see CICLAnimationDataLoader::NextMngOperation()
*/
EXPORT_C TInt CICLAnimationDataLoader::FrameCount() const
	{
	__ASSERT_ALWAYS(iImageDecoder, User::Invariant());
	return iImageDecoder->FrameCount();
	}
	
EXPORT_C TInt CICLAnimationDataLoader::CurrentFrame() const
	{
	return iCurrentFrame;
	}

EXPORT_C void CICLAnimationDataLoader::GetNextFrameL(CAnimationFrame* aFrame)
	{
	__ASSERT_ALWAYS(iImageDecoder, User::Invariant());
	__ASSERT_ALWAYS(aFrame, User::Invariant());
	
	++iCurrentFrame;

	const TFrameInfo& frameInfo = iImageDecoder->FrameInfo(iIsMngAnimation ? 0 : iCurrentFrame);
	aFrame->CreateL(frameInfo);

	if (iIsMngAnimation) 
		{
        iImageDecoder->Convert(&iStatus, *aFrame->Bitmap(), *aFrame->Mask());
        iOperation = NextMngOperation(iCurrentFrame, frameInfo.iFlags);
        }
     else
     	{
     	iImageDecoder->Convert(&iStatus, *aFrame->Bitmap(), *aFrame->Mask(), iCurrentFrame);
     	iOperation = iCurrentFrame < iFrameCount-1 ? 
     		MICLAnimationDataLoaderObserver::EImagePartialConvert : 
     		MICLAnimationDataLoaderObserver::EImageConvertComplete;
     	}
     	 
	SetActive();
	}

/**
To be used to determine if there is more frames to decode in an mng animation.
Returns @c EImagePartialConvert if the first frame is still not decoded or if the 
@c TFrameInfo::EMngMoreFramesToDecode flag was set when decoding the previous frame.

@param aFrame The number of frames already decoded
@param aFlags The flags as set during the previous decode operation.
@return Next @c TDataLoaderEvent
*/
MICLAnimationDataLoaderObserver::TDataLoaderEvent CICLAnimationDataLoader::NextMngOperation(TInt aFrame, TUint aFlags)
	{
	return ((0 == aFrame) || (aFlags & TFrameInfo::EMngMoreFramesToDecode)) ? 
			MICLAnimationDataLoaderObserver::EImagePartialConvert : 
        	MICLAnimationDataLoaderObserver::EImageConvertComplete;
	}
	
CICLAnimationDataLoader::CICLAnimationDataLoader(RFs& aFs, MICLAnimationDataLoaderObserver& aCallback)
	: CActive(CActive::EPriorityStandard), iFs(aFs), iCallback(aCallback)
	{
	}
	
void CICLAnimationDataLoader::ConstructL()
	{
	CActiveScheduler::Add(this);
	}
	
void CICLAnimationDataLoader::RunL()
	{
	iCallback.DataLoaderEventL(iOperation, iStatus.Int());
	}
	
void CICLAnimationDataLoader::DoCancel()
	{
	if(iImageDecoder)
		{
		iImageDecoder->Cancel();
		}	
	}

TBool CICLAnimationDataLoader::IsMngAnimation()
	{
	return iIsMngAnimation;
	}

