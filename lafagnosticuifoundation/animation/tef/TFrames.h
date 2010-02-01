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
//

/**
 @file
 @internalComponent - Internal Symbian test code 
*/


#ifndef __TFRAMES_H__
#define __TFRAMES_H__

#include "AnimationTestStep.h"

#include "TestWindows.h"
#include "BasicAnimation.h"
#include "SpriteAnimation.h"
#include "ICLAnimationDataProvider.h"

_LIT(KFramesStep, "Frames");

//
// Windows used in this test step:
//
class CFramesTestWindow : public CTestWindow
	{
public:
	CFramesTestWindow(RWsSession& aWs, CTestWindowGroup& aGroup, CWindowGc& aGc);
	void DrawL();
	void SetLined(TBool aLined) { iLined = aLined; }
	void SetOpaque(TBool aOpaque) { iOpaque = aOpaque; }
protected:
	TBool iLined;
	TBool iOpaque;
	};

class CFramesAnimationWindow : public CFramesTestWindow
	{
public:
	CFramesAnimationWindow(RWsSession& aWs, CTestWindowGroup& aGroup, CWindowGc& aGc);
	void DrawL();
	void SetAnimations(RPointerArray<CAnimation>* aAnimations, TBool aBasic = ETrue);
protected:
	TBool iBasicAnimations;
	RPointerArray<CAnimation>* iAnimations;
	};

class CAnimationTestServer;

class CFramesFrameWindow : public CFramesTestWindow
	{
public:
	CFramesFrameWindow(RWsSession& aWs, CTestWindowGroup& aGroup, CWindowGc& aGc);
	~CFramesFrameWindow();
	TInt LoadL(const TDesC& aFile);
	void FreeData();
	void DrawL();
	TSize Size() { if (iFrames.Count() > 0) return iFrames[0]->SizeInPixels(); else return TSize(0,0); }
	TInt Count() { return iFrames.Count(); }
protected:
	RPointerArray<CFbsBitmap> iFrames;
	RPointerArray<CFbsBitmap> iMasks;
	};

//
// The test:
//
class CFrames : public CAnimationTestStep
	{
public:
	enum Flags
		{
		ENoSprites = 0x001,
		};
public:
	CFrames();
	~CFrames();
	void TestFramesL(TInt aFlags = 0);
	void TestFramesL(const TDesC& aFile, const TDesC& aMbm, TInt aFlags = 0);
	void TestFramesL(CFramesAnimationWindow& aBasicAnimWin, CFramesAnimationWindow& aSpriteAnimWin, const TDesC& aFile, CFramesFrameWindow& aFrameWin, const TDesC& aMbm, TInt aFlags = 0);
	void InitialiseL();
	// From CActiveTestStep:
	virtual TVerdict doActiveTestStepL();
protected:
	RPointerArray<CAnimation> iBasicAnimations;
	RPointerArray<CAnimation> iSpriteAnimations;
	TInt iCase;
	
	TSize iWinSize;
	TPoint iBasicAnimWinPosition;
	TPoint iSpriteAnimWinPosition;
	TPoint iFrameWinPosition;
	CFramesAnimationWindow* iBasicAnimWin;
	CFramesAnimationWindow* iTransBasicAnimWin;
	CFramesAnimationWindow* iSpriteAnimWin;
	CFramesAnimationWindow* iTransSpriteAnimWin;
	CFramesFrameWindow* iFrameWin;
	CFramesFrameWindow* iTransFrameWin;
	};

#endif //__TFRAMES_H__
