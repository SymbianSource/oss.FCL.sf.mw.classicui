// Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
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
// These are a dummy data provider and animation.
// The intent of these is to prove that versions of each basic type can be
// created and added to the framework.  It is more important that this can
// be compiled and linked than that it does anything useful when run.
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code 
*/

#include "AnimationDataProvider.h"
#include "Animation.h"
#include "AnimationTls.h"

_LIT8(KDummyData, "dummy");

class CDummyDataProvider : public CAnimationDataProvider
	{
public:
	virtual void StartL() { };
	virtual TPtrC8 DataType() { return KDummyData(); }
	};

class CDummyAnimation : public CAnimation, public MAnimationDrawer
	{
public:
	static CDummyAnimation * NewLC(CAnimationDataProvider * aDataProvider)
		{
		__ASSERT_ALWAYS(aDataProvider, User::Leave(KErrArgument));
		CDummyAnimation * self = new (ELeave) CDummyAnimation(aDataProvider);
		CleanupStack::PushL(self);
		self->iTls = CAnimationTls::NewL();
		return self;
		}
	~CDummyAnimation() { delete iDataProvider; iTls->Close(); }

	// From CAnimation:
	virtual void Start(const TAnimationConfig& /*aConfig*/) { }
	virtual void Stop() { }
	virtual void Pause() { }
	virtual void Resume() { }
	virtual void Hold() { }
	virtual void Unhold() { }
	virtual void Freeze() { }
	virtual void Unfreeze() { }
	virtual void SetPosition(const TPoint& /*aPoint*/) { }

	// From MAnimationDrawer:
	virtual void AnimatorDraw() { }
	virtual void AnimatorInitialisedL(const TSize& /*aSize*/) { }
	virtual void AnimatorResetL() { }
	virtual const TPtrC8 AnimatorDataType() const { return iDataProvider->DataType(); }
	virtual CAnimationTicker& AnimatorTicker() { return *iTls->Ticker(); }
protected:
	CDummyAnimation(CAnimationDataProvider * aDataProvider) : iDataProvider(aDataProvider) { }
protected:
	CAnimationDataProvider * iDataProvider;
	CAnimationTls* iTls;
	};
