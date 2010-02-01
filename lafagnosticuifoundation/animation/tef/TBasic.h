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


#ifndef __TBASIC_H__
#define __TBASIC_H__

#include "AnimationTestStep.h"

#include <f32file.h>
#include <test/testexecutestepbase.h>

#include "TestWindows.h"
#include "BasicAnimation.h"
#include "SpriteAnimation.h"
#include "AnimationGroup.h"
#include "ICLAnimationDataProvider.h"

_LIT(KBasicStep, "Basic");

//
// Windows:
//
class CBasicAnimationWindow : public CTestWindow
	{
public:
	CBasicAnimationWindow(RWsSession& aWs, CTestWindowGroup& aGroup, CWindowGc& aGc);
	void DrawL();
	void SetAnimation(CBasicAnimation* aAnimation);
protected:
	CBasicAnimation* iAnimation;
	};

class CSpriteAnimationWindow : public CTestWindow
	{
public:
	CSpriteAnimationWindow(RWsSession& aWs, CTestWindowGroup& aGroup, CWindowGc& aGc);
	};

//
// The test:
// This test does not perform any tests on the visual output.  It is useful
// for other issues, but it is also a good base for manual testing.
//
class CAnimationTestServer;

class CBasic : public CAnimationTestStep, public MAnimationObserver
	{
public:
	CBasic();
	~CBasic();
	// From CActiveTestStep:
	virtual TVerdict doActiveTestStepL();
protected:
	void InitialiseL();
	void StartStopL(const TAnimationConfig& aConfig);
	void TestLoopsForeverL();
	void TestLoopsNumberedL();
	void TestNotLoopedL();
	void TestControlL();
	void TestMovingL();
	void TestDataChangeL();
	// from MAnimationObserver:
	void AnimationEvent(CAnimation& aSender, TInt aEvent, TAny * aData);
protected:
	CBasicAnimation* iBasicAnimation;
	CSpriteAnimation* iSpriteAnimation;
	CAnimationGroup* iAnimationGroup;
	
	TInt iInitialisedCount;
	TSize iWinSize;
	TPoint iBasicWinPosition;
	TPoint iSpriteWinPosition;
	CBasicAnimationWindow* iBasicWin;
	CSpriteAnimationWindow* iSpriteWin;
	};

#endif //__TBASIC_H__
