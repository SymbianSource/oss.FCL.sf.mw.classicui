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


#ifndef __TSYNCH_H__
#define __TSYNCH_H__

#include "AnimationTestStep.h"

#include <f32file.h>
#include <test/testexecutestepbase.h>

#include "TestWindows.h"
#include "BasicAnimation.h"
#include "SpriteAnimation.h"
#include "AnimationGroup.h"
#include "ICLAnimationDataProvider.h"

_LIT(KSynchStep, "Synch");

//
// Windows:
//
class CSynchAnimationWindow : public CTestWindow
	{
public:
	CSynchAnimationWindow(RWsSession& aWs, CTestWindowGroup& aGroup, CWindowGc& aGc);
	void DrawL();
	void SetAnimations(RPointerArray<CAnimation>* aAnimations);
protected:
	RPointerArray<CAnimation>* iAnimations;
	};

//
// The test:
//
class CSynch : public CAnimationTestStep
	{
public:
	CSynch();
	~CSynch();

	// From CActiveTestStep:
	virtual TVerdict doActiveTestStepL();
protected:
	void InitialiseL();
	void StartStopL(const TAnimationConfig& aConfig, TInt aPeriod=5000000);
	void TestLoopsForeverL();
	void TestLoopsNumberedL();
	void TestNotLoopedL();
	void TestControlL();
	void TestMovingL();
	void LoadBasicAnimationsL();
	void LoadSpriteAnimationsL();
	void UnloadAnimations();
protected:
	RPointerArray<CAnimation> iAnimations;
	CAnimationGroup* iAnimationGroup;
	
	TInt iExtraColors;
	TSize iWinSize;
	TPoint iWinPosition;
	TRect iWinRect;
	CSynchAnimationWindow* iWin;
	};

#endif // __TSYNCH_H__
