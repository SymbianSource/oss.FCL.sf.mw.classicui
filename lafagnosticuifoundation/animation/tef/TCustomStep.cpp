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

#include "TCustomStep.h"
#include "AnimationConfig.h"
#include "AnimationTestServer.h"
#include "DummyAnimation.h"
#include "Animator.h"

_LIT(KWrongAnimator, "Wrong animator created");

//
// Windows:
//
CCustomStepAnimationWindow::CCustomStepAnimationWindow(RWsSession& aWsSession, CTestWindowGroup& aGroup, CWindowGc& aGc) : CTestWindow(aWsSession, aGroup, aGc)
	{
	}

void CCustomStepAnimationWindow::DrawL()
	{
	}
	
//
// The test:
//
CCustomStep::CCustomStep()
	{
	SetTestStepName(KCustomStep);
	}
	
CCustomStep::~CCustomStep()
	{
	delete iWin;
	}

void CCustomStep::InitialiseL()
	{
	CAnimationTestStep::InitialiseL();
	
	ANIM_INFO1(_L("Begin test SYNCH"));

	TInt winborder = 2;
	iWinSize = Screen()->SizeInPixels();
	iWinSize.iWidth /= 2;
	iWinPosition = TPoint(iWinSize.iWidth + winborder, winborder);
	iWinSize.iWidth -= winborder * 2;
	iWinSize.iHeight -= winborder * 2;
	iWinRect = TRect(iWinPosition, iWinSize);

	iWin = new (ELeave) CCustomStepAnimationWindow(Ws(), *GroupWin(), *Gc());
	iWin->Window()->SetRequiredDisplayMode(EColor256);
	iWin->Window()->SetExtent(iWinPosition, iWinSize);
	iWin->Window()->SetBackgroundColor(iBackgroundColor1);
	iWin->Window()->SetVisible(ETrue);
	iWin->Window()->Activate();
	}

/**
	@SYMTestCaseID UIF-animation-TCustomStep-doActiveTestStepL

	@SYMTestCaseDesc This tests a derived class of CAnimator

	@SYMPREQ 269

	@SYMTestStatus Implemented

	@SYMTestPriority High

	@SYMTestActions 
	There are no animation sequences tested here.  
	What is done is derive a class from CAnimator, and test the DataEventL
	function of the class.

	@SYMTestExpectedResults Pass

*/
TVerdict CCustomStep::doActiveTestStepL()
	{
	SetTestStepID(_L("UIF-animation-TCustomStep-doActiveTestStepL"));

	InitialiseL();
	
	CDummyDataProvider * dp = new (ELeave) CDummyDataProvider;
	CDummyAnimation * animation = CDummyAnimation::NewLC(dp);
	CAnimator * animator = CAnimator::NewL(animation);
	TInt verify = 0;
	animator->DataEventL(0, &verify, sizeof(TInt));
	if (verify != 12345)
		{
		ANIM_ERR1(KWrongAnimator);
		SetTestStepResult(EFail);
		}
	delete animator;
	CleanupStack::PopAndDestroy(animation);

	RecordTestResultL();
	CloseTMSGraphicsStep();

	return TestStepResult();
	}
