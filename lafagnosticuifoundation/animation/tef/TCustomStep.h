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

#ifndef __TCUSTOMSTEP_H__
#define __TCUSTOMSTEP_H__

#include "AnimationTestStep.h"

#include <f32file.h>
#include <test/testexecutestepbase.h>

#include "TestWindows.h"
#include "BasicAnimation.h"
#include "SpriteAnimation.h"
#include "AnimationGroup.h"
#include "ICLAnimationDataProvider.h"

_LIT(KCustomStep, "Custom");

//
// Windows:
//
class CCustomStepAnimationWindow : public CTestWindow
	{
public:
	CCustomStepAnimationWindow(RWsSession& aWs, CTestWindowGroup& aGroup, CWindowGc& aGc);
	void DrawL();
	};

//
// The test:
//
class CCustomStep : public CAnimationTestStep
	{
public:
	CCustomStep();
	~CCustomStep();
	// From CTestStep:
	virtual TVerdict doActiveTestStepL();
protected:
	void InitialiseL();
	void StartStopL();
protected:
	TSize iWinSize;
	TPoint iWinPosition;
	TRect iWinRect;
	CCustomStepAnimationWindow* iWin;
	};

#endif // __TCUSTOMSTEP_H__
