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

#ifndef __BITMAPANIMATOR_H__
#define __BITMAPANIMATOR_H__

#include "Animator.h"
#include "AnimationMixins.h"
#include "AnimationFrame.h"

class TAnimationConfig;

/**
CAnimator derived plugin for bitmap frames.

This animator is loaded when the data provider is passing a fixed sequence
of bitmap frames, and a type of "bitmap".  This is the type used by the
CICLAnimationDataProvider.

You do not need to instatiate animators in a client application.  This is
handled by the animation classes.

@see CICLAnimationDataProvider
@internalAll
*/
class CBitmapAnimator : public CAnimator, public MAnimationTickee
	{
protected:
	enum TFlags
		{
		ECompleteData		= 0x0001,
		EHeld				= 0x0002,
		ECountFrames		= 0x0004,
		EEndOnLastFrame		= 0x0008,
		ERunning			= 0x0010,
		EPaused				= 0x0020,
		EPending			= 0x0040,
		ERunMask			= 0x00F0,
		};
public:
    static CBitmapAnimator* NewL(TAny* aRenderer);
    ~CBitmapAnimator();
public:
	virtual void Start(const TAnimationConfig& aConfig);
	virtual void Stop();
	virtual void Pause();
	virtual void Resume();
	virtual void Hold();
	virtual void Unhold();
	virtual void DataEventL(TInt aEvent, TAny* aData, TInt aDataSize);	
	virtual void Draw(CBitmapContext& aBitmapContext) const;
	virtual void DrawMask(CBitmapContext& aBitmapContext) const;
private:
	CBitmapAnimator(MAnimationDrawer* aRenderer);
	void ConstructL();
	void InitialisedL();
	void ResetL();
	void AppendFrameL(CAnimationFrame::THandles& aAnimationFrame);
	void DoUpdateFrame();
	void Render(CBitmapContext& aBitmapContext, TInt aFrame) const;
	void RenderMask(CBitmapContext& aBitmapContext, TInt aFrame) const;
	void RestoreToPrevious(CBitmapContext& aBitmapContext, TBool aMask) const;
	// From MAnimationTickee
	virtual void Tick();
private:
	MAnimationDrawer* iRenderer;
	TInt iFlags;
	RPointerArray<CAnimationFrame> iFrameArray;
	TSize iMaxSize;
	TInt iCurrentFrame;
	TInt iNextFrame;
	TInt iTicksLeft;
	};

#endif //__BITMAPANIMATOR_H__
