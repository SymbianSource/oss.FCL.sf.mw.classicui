// Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
 @test
 @internalComponent - Internal Symbian test code 
*/

#if !defined(__TANCTL_H__)
#define __TANCTL_H__

#if !defined(__COECNTRL_H__)
#include <coecntrl.h>
#endif

class TResourceReader;
class RAnimDll;
class RBitmapAnim;
class CBitmapAnimClientData;
class CBitmapFrameData;

_LIT(KTBmpAnimMBMFilePath, "z:\\resource\\apps\\tbmpanim\\mbm\\tbmpanim.mbm");

enum TEikAnimationPanic
	{
	EEikPanicAnimationNoControlContext,
	EEikPanicAnimationNoRAnimation,
	EEikPanicAnimationNoWindow
	};

//
//	CBitmapAnimIdler
//

class CBitmapAnimIdler : public CIdle
	{
public:
	static CBitmapAnimIdler* NewL();
private:
	CBitmapAnimIdler() : CIdle(EPriorityLow) { }
	};


class CAnimateFramesCtl : public CCoeControl
	{
public:
	static CAnimateFramesCtl* NewL();
	virtual ~CAnimateFramesCtl();
public:
	inline RBitmapAnim* Animation() { return iAnimation; }
	inline CBitmapAnimClientData* BitmapAnimData() { return iBitmapAnimData; }
	void CancelAnimationL();
	void SetAnimationCtlWindowL(CCoeControl* aParent);
	inline void SetFileName(TDesC& aAppFileName) { iFileName = aAppFileName; }
	void SetBitmapAnimationDataL();
	void SetFrameIndexL(TInt aIndex);
	void SetFrameIntervalL(TInt aInterval);
	void StartAnimationL();
	void StaticConstructL(TInt aResourceId);
	void Panic(TEikAnimationPanic aPanic);
	void CompleteAnimationInitialisationL();
public: // from CCoeControl
	virtual void ConstructFromResourceL(TResourceReader& aResourceReader);
	virtual TSize MinimumSize();
private:
	enum TInternalFlags
		{
		EInitialisationCompleted	=	0x0001,
		EWaitForRedrawing			=	0x0002
		};
private: // from CCoeControl
	virtual void SizeChanged();
	virtual void PositionChanged();
private:
	CAnimateFramesCtl();
	void BaseConstructL();
	inline TBool IsInitialisationComnpleted() { return iFlags&EInitialisationCompleted; }
	CBitmapFrameData* ReadFrameDataFromResourceL(TResourceReader& aFramesReader, const TDesC& aFileName);
	TBool SetWindowOnServerSideL();
	TBool SetAnimationWindowL();
	void CreateAndStartIdlerL();
	static TInt StartAnimationCallBackL(TAny* aThis);
private:
	CBitmapAnimClientData* iBitmapAnimData;
	RAnimDll iAnimDll;
	RBitmapAnim* iAnimation;
	TInt iFlags;
	TFileName iFileName;
	CBitmapAnimIdler* iStartAnimationIdler;
	};

#endif


