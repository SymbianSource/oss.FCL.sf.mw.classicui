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

#ifndef __ICLANIMATIONDATALOADER_H__
#define __ICLANIMATIONDATALOADER_H__

#include <e32base.h> 
#include <icl/imagedata.h>

#include "AnimationMixins.h"

class CBitmapScaler;
class CImageEncoder;
class CImageDecoder;
class CFbsBitmap;
class CAnimationFrame;

/** @internalComponent */
NONSHARABLE_CLASS(CICLAnimationDataLoader) : public CActive
	{
public:
	IMPORT_C static CICLAnimationDataLoader* NewL(RFs& aFs, MICLAnimationDataLoaderObserver& aCallback);
	~CICLAnimationDataLoader();

	IMPORT_C void LoadImageDataL(const TFileName& aFileName);
	IMPORT_C void GetNextFrameL(CAnimationFrame* aFrame);
	
	IMPORT_C TFrameInfo FrameInfo(const TInt aFrame) const;
	IMPORT_C TInt FrameCount() const;
	IMPORT_C TInt CurrentFrame() const;
	TBool IsMngAnimation();
	
private:
	CICLAnimationDataLoader(RFs& aFs, MICLAnimationDataLoaderObserver& aCallback);
	void ConstructL();
	static MICLAnimationDataLoaderObserver::TDataLoaderEvent NextMngOperation(TInt aFrame, TUint aFlags);
	
	// from CActive
	void RunL(); 
	void DoCancel();
private:
	RFs& iFs;
	MICLAnimationDataLoaderObserver& iCallback;
	TInt iFrameCount;
	TInt iCurrentFrame;
	TBool iIsMngAnimation;
	CImageDecoder* iImageDecoder;
	MICLAnimationDataLoaderObserver::TDataLoaderEvent iOperation;
	};


#endif //__ICLANIMATIONDATALOADER_H__
