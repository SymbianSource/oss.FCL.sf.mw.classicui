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

#include "TBasic.h"
#include "AnimationConfig.h"
#include "AnimationTestServer.h"

_LIT(KSymBallFile, "Z:\\Private\\10204F5B\\symball.gif");
_LIT(KSymWaveFile, "Z:\\Private\\10204F5B\\symwave.gif");

//
// Windows:
//
CBasicAnimationWindow::CBasicAnimationWindow(RWsSession& aWsSession, CTestWindowGroup& aGroup, CWindowGc& aGc) : CTestWindow(aWsSession, aGroup, aGc)
	{
	}

void CBasicAnimationWindow::SetAnimation(CBasicAnimation* aAnimation)
	{
	iAnimation = aAnimation;
	}
	
void CBasicAnimationWindow::DrawL()
	{
	if(iAnimation)
		iAnimation->Draw(iGc);
	}
	
CSpriteAnimationWindow::CSpriteAnimationWindow(RWsSession& aWsSession, CTestWindowGroup& aGroup, CWindowGc& aGc) : CTestWindow(aWsSession, aGroup, aGc)
	{
	}

//
// The test:
//
CBasic::CBasic()
	{
	SetTestStepName(KBasicStep);
	}
	
CBasic::~CBasic()
	{
	delete iAnimationGroup;
	delete iBasicAnimation;
	delete iSpriteAnimation;
	delete iBasicWin;
	delete iSpriteWin;
	}

void CBasic::InitialiseL()
	{
	CAnimationTestStep::InitialiseL();
	
	ANIM_INFO1(_L("Begin test BASIC"));

	TInt winborder = 2;
	iWinSize = Screen()->SizeInPixels();
	iWinSize.iWidth /= 2;
	iWinSize.iHeight /= 2;
	iBasicWinPosition = TPoint(iWinSize.iWidth + winborder, winborder);
	iSpriteWinPosition = TPoint(iWinSize.iWidth + winborder, iWinSize.iHeight + winborder);
	iWinSize.iWidth -= winborder * 2;
	iWinSize.iHeight -= winborder * 2;

	iBasicWin = new (ELeave) CBasicAnimationWindow(Ws(), *GroupWin(), *Gc());
	iBasicWin->Window()->SetRequiredDisplayMode(EColor256);
	iBasicWin->Window()->SetExtent(iBasicWinPosition, iWinSize);
	iBasicWin->Window()->SetBackgroundColor(iBackgroundColor1);
	iBasicWin->Window()->SetVisible(ETrue);
	iBasicWin->Window()->Activate();

	iSpriteWin = new (ELeave) CSpriteAnimationWindow(Ws(), *GroupWin(), *Gc());
	iSpriteWin->Window()->SetRequiredDisplayMode(EColor256);
	iSpriteWin->Window()->SetExtent(iSpriteWinPosition, iWinSize);
	iSpriteWin->Window()->SetBackgroundColor(iBackgroundColor1);
	iSpriteWin->Window()->SetVisible(ETrue);
	iSpriteWin->Window()->Activate();

	CICLAnimationDataProvider* dataProvider;
	dataProvider=new(ELeave)CICLAnimationDataProvider;
	CleanupStack::PushL(dataProvider);
	dataProvider->SetFileL(iFs, KSymBallFile());
	CleanupStack::Pop(dataProvider);
	iBasicAnimation = CBasicAnimation::NewL(dataProvider, TPoint(0,0), Ws(), *iBasicWin->Window(), this);
	iBasicWin->SetAnimation(iBasicAnimation);

	dataProvider=new(ELeave)CICLAnimationDataProvider;
	CleanupStack::PushL(dataProvider);
	dataProvider->SetFileL(iFs, KSymBallFile());
	CleanupStack::Pop(dataProvider);
	iSpriteAnimation = CSpriteAnimation::NewL(dataProvider, TPoint(0,0), Ws(), *iSpriteWin->Window(), this);

	iAnimationGroup = CAnimationGroup::NewL();
	iAnimationGroup->Animations().Append(iBasicAnimation);
	iAnimationGroup->Animations().Append(iSpriteAnimation);
	}

// Although this function doesn't leave, it is the intention that it will do
// in future, since it is supposed to be verifying the output:
void CBasic::StartStopL(const TAnimationConfig& aConfig)
	{
	iAnimationGroup->Start(aConfig);
	Wait(5000000);
	iAnimationGroup->Stop();
	Wait(500000);
	}
/**
	@SYMTestCaseID UIF-animation-TBasic-TestLoopsForeverL-0001
*/
/**
	@SYMTestCaseID UIF-animation-TBasic-TestLoopsForeverL-0002

	@SYMPREQ 269
	
	@SYMTestCaseDesc 
	This runs an animation loop forever (actual run time 5 seconds).

	@SYMTestStatus Implemented

	@SYMTestPriority High

	@SYMTestActions 
	The animation must be initialised, and this test is called with an animation
	group with basic and sprite animations.

	@SYMTestExpectedResults Animation displayed.

*/
void CBasic::TestLoopsForeverL()
	{
	TAnimationConfig config;
	config.iFlags = TAnimationConfig::ELoop;
	config.iData = -1;

	StartStopL(config);
	}
	
/**
	@SYMTestCaseID UIF-animation-TBasic-TestLoopsNumberedL

	@SYMTestCaseDesc 
	This runs an animation loop twice.

	@SYMPREQ 269

	@SYMTestStatus Implemented

	@SYMTestPriority High

	@SYMTestActions 
	The animation must be initialised, and this test is called with an animation
	group with basic and sprite animations.

	@SYMTestExpectedResults Animation displayed.

*/
void CBasic::TestLoopsNumberedL()
	{
	TAnimationConfig config;
	config.iFlags = TAnimationConfig::ELoop;
	config.iData = 2;

	StartStopL(config);
	}
	
/**
	@SYMTestCaseID UIF-animation-TBasic-TestNotLoopedL

	@SYMTestCaseDesc 
	This runs an animation displayed without looping.

	@SYMPREQ 269

	@SYMTestStatus Implemented

	@SYMTestPriority High

	@SYMTestActions 
	The animation must be initialised, and this test is called with an animation
	group with basic and sprite animations.

	@SYMTestExpectedResults Animation displayed.
*/
void CBasic::TestNotLoopedL()
	{
	TAnimationConfig config;

	StartStopL(config);
	}
	
/**
	@SYMTestCaseID UIF-animation-TBasic-TestControlL

	@SYMTestCaseDesc 
	This tests animation operations such as start, pause, resume and stop.  

	@SYMPREQ 269

	@SYMTestStatus Implemented

	@SYMTestPriority High

	@SYMTestActions 
	The animation must be initialised, and this test is called with an animation
	group with basic and sprite animations.  After a straightforward sequence of 
	operations: start, pause, resume and stop, invalid operations for the current 
	state are tested, such as stop when already stopped, and resume when stopped.

	@SYMTestExpectedResults Animation displayed.
*/
void CBasic::TestControlL()
	{
	TAnimationConfig config;
	config.iFlags = TAnimationConfig::ELoop;
	config.iData = -1;
	
	// Start, Pause, Resume, Stop:
	iAnimationGroup->Start(config);
	Wait(500000);
	iAnimationGroup->Pause();
	Wait(1000000);
	iAnimationGroup->Resume();
	Wait(700000);
	iAnimationGroup->Stop();
	Wait(500000);
	
	// Start again:
	iAnimationGroup->Start(config);
	Wait(500000);
	iAnimationGroup->Stop();
	
	// Commands for wrong state (stop when already stopped etc):
	iAnimationGroup->Start(config);
	Wait(500000);
	iAnimationGroup->Start(config);
	Wait(500000);
	iAnimationGroup->Resume();
	Wait(500000);
	iAnimationGroup->Stop();
	iAnimationGroup->Stop();
	Wait(500000);	
	iAnimationGroup->Resume();
	Wait(500000);	
	}
	
/**
	@SYMTestCaseID UIF-animation-TBasic-TestMovingL

	@SYMTestCaseDesc 
	This test starts an animation and then moves its position multiple times.  
	The animation is then stopped.

	@SYMPREQ 269

	@SYMTestStatus Implemented

	@SYMTestPriority High

	@SYMTestActions 
	The animation must be initialised, and this test is called with an animation
	group with basic and sprite animations.  After the animation is started it is 
	moved horizontally five pixels to the right for a length of 200 pixels, 
	with a 50ms pause between each step.

	@SYMTestExpectedResults Animation displayed moving to the right.
*/
void CBasic::TestMovingL()
	{
	TAnimationConfig config;
	config.iFlags = TAnimationConfig::ELoop;
	config.iData = -1;
	
	iAnimationGroup->Start(config);

	TInt y = 0;	
	for (TInt x = 0; x < 200; x += 5)
		{
		iAnimationGroup->SetPosition(TPoint(x, y));
		Ws().Flush();
		Wait(50000);
		y += 1;
		}
	iAnimationGroup->Stop();
	}

/**
	@SYMTestCaseID UIF-animation-TBasic-TestDataChangeL

	@SYMTestCaseDesc 
	This test changes the data provider file.

	@SYMPREQ 269

	@SYMTestStatus Implemented

	@SYMTestPriority High

	@SYMTestActions 
	The animation must be initialised, and the data provider for a basic animation and
	a sprite animation are changed.

	@SYMTestExpectedResults 
	No output changed.  The animation test TestLoopsForeverL is run afterwards.
*/
void CBasic::TestDataChangeL()
	{
	static_cast<CICLAnimationDataProvider*>(iBasicAnimation->DataProvider())->SetFileL(iFs, KSymWaveFile());
	static_cast<CICLAnimationDataProvider*>(iSpriteAnimation->DataProvider())->SetFileL(iFs, KSymWaveFile());
	Wait(2000000);
	}

TVerdict CBasic::doActiveTestStepL()
	{
	_LIT(KLoopsForever, "Loops forever");
	_LIT(KLoopsNumbered, "Loops numbered");
	_LIT(KNotLooped, "Not looped");
	_LIT(KControl, "Control");
	_LIT(KMoving, "Moving");
	_LIT(KDataChange, "Data Change");
	
	InitialiseL();

	Wait(2000000);

	TInt stage = 0;
	TBool finished = EFalse;
	while((TestStepResult() == EPass) && !finished)
		{
		switch(stage)
			{
			case 0:
				SetTestStepID(_L("UIF-animation-TBasic-TestLoopsForeverL-0001"));
				ANIM_INFO1(KLoopsForever);
				TestLoopsForeverL();
				RecordTestResultL();
				break;
			case 1:
				SetTestStepID(_L("UIF-animation-TBasic-TestLoopsNumberedL"));
				ANIM_INFO1(KLoopsNumbered);
				TestLoopsNumberedL();
				RecordTestResultL();
				break;
			case 2:
				SetTestStepID(_L("UIF-animation-TBasic-TestNotLoopedL"));
				ANIM_INFO1(KNotLooped);
				TestNotLoopedL();
				RecordTestResultL();
				break;
			case 3:
				SetTestStepID(_L("UIF-animation-TBasic-TestControlL"));
				ANIM_INFO1(KControl);
				TestControlL();
				RecordTestResultL();
				break;
			case 4:
				SetTestStepID(_L("UIF-animation-TBasic-TestMovingL"));
				ANIM_INFO1(KMoving);
				TestMovingL();
				RecordTestResultL();
				break;
			case 5:
				SetTestStepID(_L("UIF-animation-TBasic-TestDataChangeL"));
				ANIM_INFO1(KDataChange);
				TestDataChangeL();
				RecordTestResultL();
				break;
			case 6:
				SetTestStepID(_L("UIF-animation-TBasic-TestLoopsForeverL-0002"));
				ANIM_INFO1(KLoopsForever);
				TestLoopsForeverL();
				RecordTestResultL();
				CloseTMSGraphicsStep();
				break;
			default:
				finished = ETrue;
			}
		++stage;
		}
	return TestStepResult();
	}
	
void CBasic::AnimationEvent(CAnimation& /*aSender*/, TInt aEvent, TAny* aData)
	{
	switch(aEvent)
		{
		case MAnimationObserver::EDataProviderError:
			ANIMTESTERR(*static_cast<TInt*>(aData));
			break;
		default:
			break;
		}
	}
