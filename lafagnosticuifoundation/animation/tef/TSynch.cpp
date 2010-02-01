// Copyright (c) 2008-2009 Nokia Corporation and/or its subsidiary(-ies).
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
// NOTE: This test is screen sensitive, so anything appearing on the techview screen while running will cause the image
// comparison algorithm to fail.
// Ones of the culprits can be the techview Heartbeat inactivity timer (see DEF116740), hence, a way to avoid being
// hit by this problem is to keep the test duration shorter than the inactivity timeout (currently set at 60s)
// 
//

/**
 @file
 @test
 @internalComponent - Internal Symbian test code 
*/


#include "TSynch.h"
#include "AnimationConfig.h"
#include "AnimationTestServer.h"

_LIT(KEightStep, "Z:\\private\\10204F5B\\rgb1.gif");
_LIT(KThreeStep, "Z:\\private\\10204F5B\\rgb2.gif");

const TInt KSynchNumAnimations = 10;
const TInt KSynchTestPeriod = 200000;

//
// Windows:
//
CSynchAnimationWindow::CSynchAnimationWindow(RWsSession& aWsSession, CTestWindowGroup& aGroup, CWindowGc& aGc) : CTestWindow(aWsSession, aGroup, aGc)
	{
	}

void CSynchAnimationWindow::SetAnimations(RPointerArray<CAnimation>* aAnimations)
	{
	iAnimations = aAnimations;
	}
	
void CSynchAnimationWindow::DrawL()
	{
	if (iAnimations)
		{
		for(TInt anim = 0; anim < iAnimations->Count(); ++anim)
			{
			static_cast<CBasicAnimation*>((*iAnimations)[anim])->Draw(iGc);
			}
		}
	}
	
//
// The test:
//
CSynch::CSynch()
	{
	SetTestStepName(KSynchStep);
	}
	
CSynch::~CSynch()
	{
	UnloadAnimations();
	delete iAnimationGroup;
	delete iWin;
	}

void CSynch::InitialiseL()
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

	iWin = new (ELeave) CSynchAnimationWindow(Ws(), *GroupWin(), *Gc());
	iWin->Window()->SetRequiredDisplayMode(iDisplayMode);
	iWin->Window()->SetExtent(iWinPosition, iWinSize);
	iWin->Window()->SetBackgroundColor(iBackgroundColor1);
	iWin->Window()->SetVisible(ETrue);
	iWin->Window()->Activate();

	iAnimationGroup = CAnimationGroup::NewL();
	}

void CSynch::StartStopL(const TAnimationConfig& aConfig, TInt aPeriod)
	{
	iAnimationGroup->Start(aConfig);
	for(TInt ii = 0; ii < aPeriod; ii += KSynchTestPeriod)
		{
		Wait(KSynchTestPeriod);
		WaitForRedrawsToFinish();
		ANIMTESTCOLORSL(iWinRect, 2, 2 + iExtraColors);
		}
	iAnimationGroup->Stop();
	WaitForRedrawsToFinish();
	ANIMTESTCOLORSL(iWinRect, 2, 2 + iExtraColors);
	}

/**
	@SYMTestCaseID UIF-animation-TSynch-TestLoopsForeverL

	@SYMTestCaseDesc 
	This runs an animation loop forever, testing synchronization.

	@SYMPREQ 269

	@SYMTestStatus Implemented

	@SYMTestPriority High

	@SYMTestActions 
	The animation must be initialised, and this test is called twice, first with
	a set of synchronized basic animations, and second with an set of synchronized 
	sprite animations.

	@SYMTestExpectedResults Animation displayed in rows

*/
void CSynch::TestLoopsForeverL()
	{
	TAnimationConfig config;
	config.iFlags = TAnimationConfig::ELoop;
	config.iData = -1;

	StartStopL(config, 3000000);
	}

/**
	@SYMTestCaseID UIF-animation-TSynch-TestLoopsNumberedL

	@SYMTestCaseDesc 
	This runs an animation loops twice, testing synchronization.

	@SYMPREQ 269

	@SYMTestStatus Implemented

	@SYMTestPriority High

	@SYMTestActions 
	The animation must be initialised, and this test is called twice, first with
	a set of synchronized basic animations, and second with an set of synchronized 
	sprite animations.

	@SYMTestExpectedResults Animation displayed in rows

*/	
void CSynch::TestLoopsNumberedL()
	{
	TAnimationConfig config;
	config.iFlags = TAnimationConfig::ELoop;
	config.iData = 2;

	StartStopL(config);
	}
	
/**
	@SYMTestCaseID UIF-animation-TSynch-TestNotLoopedL

	@SYMTestCaseDesc 
	This runs an animation is displayed without looping.

	@SYMPREQ 269

	@SYMTestStatus Implemented

	@SYMTestPriority High

	@SYMTestActions 
	The animation must be initialised, and this test is called twice, first with
	a set of synchronized basic animations, and second with an set of synchronized 
	sprite animations.

	@SYMTestExpectedResults Animation displayed in rows
*/	
void CSynch::TestNotLoopedL()
	{
	TAnimationConfig config;
	config.iFlags = 0;

	StartStopL(config);
	}

/**
	@SYMTestCaseID UIF-animation-TSynch-TestControlL

	@SYMTestCaseDesc 
	This tests animation operations such as start, pause, resume and stop.  Tests
	performed on a set of synchronized animations.  

	@SYMPREQ 269

	@SYMTestStatus Implemented

	@SYMTestPriority High

	@SYMTestActions 
	The animation must be initialised, and this test is called twice, first with
	a set of synchronized basic animation, and second with an set of synchronized 
	sprite animations. After a straightforward sequence of operations: start, pause, 
	resume and stop, invalid operations for the current state are tested, such as 
	stop when already stopped, and resume when stopped.

	@SYMTestExpectedResults Animation displayed in rows.
*/	
void CSynch::TestControlL()
	{
	TAnimationConfig config;
	config.iFlags = TAnimationConfig::ELoop;
	config.iData = -1;
	
	// Start, Pause, Resume, Stop:
	iAnimationGroup->Start(config);
	Wait(500000);
	ANIMTESTCOLORSL(iWinRect, 2, 2 + iExtraColors);
	iAnimationGroup->Pause();
	Wait(1000000);
	ANIMTESTCOLORSL(iWinRect, 2, 2 + iExtraColors);
	iAnimationGroup->Resume();
	Wait(700000);
	ANIMTESTCOLORSL(iWinRect, 2, 2 + iExtraColors);
	iAnimationGroup->Stop();
	Wait(500000);
	ANIMTESTCOLORSL(iWinRect, 2, 2 + iExtraColors);
	
	// Start again:
	iAnimationGroup->Start(config);
	Wait(500000);
	ANIMTESTCOLORSL(iWinRect, 2, 2 + iExtraColors);
	iAnimationGroup->Stop();
	ANIMTESTCOLORSL(iWinRect, 2, 2 + iExtraColors);
	
	// Put some of them on hold and make sure they recover:
	iAnimationGroup->Start(config);
	Wait(500000);
	for(TInt i = 0; i < iAnimations.Count(); ++i)
		{
		if(i % 3)
			iAnimations[i]->Hold();
		}
	Wait(2500000);
	iAnimationGroup->Unhold();
	Wait(500000);
	ANIMTESTCOLORSL(iWinRect, 2, 2 + iExtraColors);
	iAnimationGroup->Stop();
	
	// Commands for wrong state (stop when already stopped etc):
	iAnimationGroup->Start(config);
	Wait(500000);
	ANIMTESTCOLORSL(iWinRect, 2, 2 + iExtraColors);
	iAnimationGroup->Start(config);
	Wait(500000);
	ANIMTESTCOLORSL(iWinRect, 2, 2 + iExtraColors);
	iAnimationGroup->Resume();
	Wait(500000);
	ANIMTESTCOLORSL(iWinRect, 2, 2 + iExtraColors);
	iAnimationGroup->Stop();
	iAnimationGroup->Stop();
	Wait(500000);	
	ANIMTESTCOLORSL(iWinRect, 2, 2 + iExtraColors);
	iAnimationGroup->Resume();
	Wait(500000);
	ANIMTESTCOLORSL(iWinRect, 2, 2 + iExtraColors);
	}
	
void CSynch::LoadBasicAnimationsL()
	{
	UnloadAnimations();
	
	CICLAnimationDataProvider* dataProvider;
	
	for (TInt anim = 0; anim < KSynchNumAnimations; ++anim)
		{
		dataProvider = new (ELeave) CICLAnimationDataProvider;
		CleanupStack::PushL(dataProvider);
		dataProvider->SetFileL(iFs, KEightStep());
		CleanupStack::Pop(dataProvider);
		CBasicAnimation* animation = CBasicAnimation::NewL(dataProvider, TPoint(anim * 4,anim * 18), Ws(), *iWin->Window());
		iAnimations.Append(animation);
		iAnimationGroup->Animations().Append(animation);

		dataProvider = new (ELeave) CICLAnimationDataProvider;
		CleanupStack::PushL(dataProvider);
		dataProvider->SetFileL(iFs, KThreeStep());
		CleanupStack::Pop(dataProvider);
		animation = CBasicAnimation::NewL(dataProvider, TPoint(anim * 4 + 2,anim * 18 + 9), Ws(), *iWin->Window());
		iAnimations.Append(animation);
		iAnimationGroup->Animations().Append(animation);		
		}
	iWin->SetAnimations(&iAnimations);
	Wait(3000000);
	}
	
void CSynch::LoadSpriteAnimationsL()
	{
	UnloadAnimations();
	
	CICLAnimationDataProvider* dataProvider;
	
	for (TInt anim = 0; anim < KSynchNumAnimations; ++anim)
		{
		dataProvider = new (ELeave) CICLAnimationDataProvider;
		CleanupStack::PushL(dataProvider);
		dataProvider->SetFileL(iFs, KEightStep());
		CleanupStack::Pop(dataProvider);
		CSpriteAnimation* animation = CSpriteAnimation::NewL(dataProvider, TPoint(anim * 4,anim * 18), Ws(), *iWin->Window());
		iAnimations.Append(animation);
		iAnimationGroup->Animations().Append(animation);

		dataProvider = new (ELeave) CICLAnimationDataProvider;
		CleanupStack::PushL(dataProvider);
		dataProvider->SetFileL(iFs, KThreeStep());
		CleanupStack::Pop(dataProvider);
		animation = CSpriteAnimation::NewL(dataProvider, TPoint(anim * 4 + 2,anim * 18 + 9), Ws(), *iWin->Window());
		iAnimations.Append(animation);
		iAnimationGroup->Animations().Append(animation);		
		}
	Wait(3000000);
	}
	
void CSynch::UnloadAnimations()
	{
	if (iWin)
		{
		iWin->SetAnimations(0);
		iWin->Window()->Invalidate();
		}
	if (iAnimationGroup)
		iAnimationGroup->Animations().Reset();
	iAnimations.ResetAndDestroy();
	}

TVerdict CSynch::doActiveTestStepL()
	{
	_LIT(KBasic, "Load basic animations");
	_LIT(KSprite, "Load sprite animations");
	_LIT(KLoopsForever, "Loops forever");
	_LIT(KLoopsNumbered, "Loops numbered");
	_LIT(KNotLooped, "Not looped");
	_LIT(KControl, "Control");
	
	InitialiseL();
	
	TInt stage = 0;
	TInt animType = 0;
	TBool finished = EFalse;
	while(TestStepResult() == EPass && !finished)
		{
		switch(stage)
			{
			case 0:
				switch(animType)
					{
					case 0:
						ANIM_INFO1(KBasic);
						iExtraColors = 0;
						LoadBasicAnimationsL();
						break;
					case 1:
						ANIM_INFO1(KSprite);
						// 1 extra colour is unfortunate, but unavoidable
						// due to multiple processes/threads being involved.
						iExtraColors = 1; 
						LoadSpriteAnimationsL();
						break;
					default:
						finished = ETrue;
					}
				break;
			case 1:
				SetTestStepID(_L("UIF-animation-TSynch-TestLoopsForeverL"));
				ANIM_INFO1(KLoopsForever);
				TestLoopsForeverL();
				RecordTestResultL();
				break;
			case 2:
				SetTestStepID(_L("UIF-animation-TSynch-TestLoopsNumberedL"));
				ANIM_INFO1(KLoopsNumbered);
				TestLoopsNumberedL();
				RecordTestResultL();
				break;
			case 3:
				SetTestStepID(_L("UIF-animation-TSynch-TestNotLoopedL"));
				ANIM_INFO1(KNotLooped);
				TestNotLoopedL();
				RecordTestResultL();
				break;
			case 4:
				SetTestStepID(_L("UIF-animation-TSynch-TestControlL"));
				ANIM_INFO1(KControl);
				TestControlL();
				RecordTestResultL();
				CloseTMSGraphicsStep();
				break;
			default:
				stage = -1; // ++ later
				++animType;
				break;
			}
		++stage;
		}
	return TestStepResult();
	}
