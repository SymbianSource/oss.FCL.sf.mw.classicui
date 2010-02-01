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


#ifndef __TOOM_H__
#define __TOOM_H__

#include "AnimationTestStep.h"

#include <f32file.h>

#include "TestWindows.h"
#include "BasicAnimation.h"
#include "SpriteAnimation.h"
#include "AnimationGroup.h"
#include "ICLAnimationDataProvider.h"

_LIT(KOomStep, "Oom");

//
// Windows:
//
class COomAnimationWindow : public CTestWindow
	{
public:
	COomAnimationWindow(RWsSession& aWs, CTestWindowGroup& aGroup, CWindowGc& aGc);
	void DrawL();
	void SetAnimation(CBasicAnimation* aAnimation);
protected:
	CBasicAnimation* iAnimation;
	};


/** The test:
    This test does not perform any tests on the visual output.  It is useful
    for other issues, but it is also a good base for manual testing.
*/
class CAnimationTestServer;

class COomStep : public CAnimationTestStep
	{
public:
	COomStep();
	~COomStep();
	
	// From CActiveTestStep:
	virtual TVerdict doActiveTestStepL();
protected:
	void InitialiseL();
	void TestLoopingL();
	void RunTestL(TInt aTest);
protected:
	TSize iWinSize;
	TPoint iWinPosition;
	COomAnimationWindow* iOomWin;
	};

#endif //__TOOM_H__
