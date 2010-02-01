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


#include "TOomStep.h"
#include "AnimationConfig.h"
#include "AnimationTestServer.h"

_LIT(KSymBallFile, "Z:\\Private\\10204F5B\\symball.gif");

//
// Windows:
//
COomAnimationWindow::COomAnimationWindow(RWsSession& aWsSession, CTestWindowGroup& aGroup, CWindowGc& aGc) : CTestWindow(aWsSession, aGroup, aGc)
	{
	}

void COomAnimationWindow::SetAnimation(CBasicAnimation* aAnimation)
	{
	iAnimation = aAnimation;
	}
	
void COomAnimationWindow::DrawL()
	{
	if(iAnimation)
		iAnimation->Draw(iGc);
	}
	
//
// The test:
//
COomStep::COomStep()
	{
	SetTestStepName(KOomStep);
	}
	
COomStep::~COomStep()
	{
	delete iOomWin;
	}

void COomStep::InitialiseL()
	{
	CAnimationTestStep::InitialiseL();
	
	ANIM_INFO1(_L("Begin test OOM"));

	TInt winborder = 2;
	iWinSize = Screen()->SizeInPixels();
	iWinSize.iWidth /= 2;
	iWinPosition = TPoint(iWinSize.iWidth + winborder, winborder);
	iWinSize.iWidth -= winborder * 2;
	iWinSize.iHeight -= winborder * 2;

	iOomWin = new (ELeave) COomAnimationWindow(Ws(), *GroupWin(), *Gc());
	iOomWin->Window()->SetRequiredDisplayMode(EColor256);
	iOomWin->Window()->SetExtent(iWinPosition, iWinSize);
	iOomWin->Window()->SetBackgroundColor(iBackgroundColor1);
	iOomWin->Window()->SetVisible(ETrue);
	iOomWin->Window()->Activate();
	}

/**
	@SYMTestCaseID UIF-animation-TOomStep-TestLoopingL

	@SYMTestCaseDesc 
	This tests basic animation and sprite animation in a low memory
	condition.

	@SYMPREQ 269

	@SYMTestStatus Implemented

	@SYMTestPriority Medium

	@SYMTestActions 
	The test starts and stops animation for a basic and sprite
	animation group in a low memory condition.  It initializes an animation
	group with a basic and sprite animation and which it then starts and stops.
	Finally the animation group and the animations are destroyed.

	@SYMTestExpectedResults This function leaves with a memory failure if there
	is insufficient memory for the test to run.

*/	
void COomStep::TestLoopingL()
	{
	TAnimationConfig config;
	config.iFlags = TAnimationConfig::ELoop;
	config.iData = -1;

	CICLAnimationDataProvider* dataProvider;
	dataProvider=new(ELeave)CICLAnimationDataProvider;
	CleanupStack::PushL(dataProvider);
	dataProvider->SetFileL(iFs, KSymBallFile());
	CleanupStack::Pop(dataProvider);
	CBasicAnimation * basicAnimation = CBasicAnimation::NewL(dataProvider, TPoint(0,0), Ws(), *iOomWin->Window());
	CleanupStack::PushL(basicAnimation);
	iOomWin->SetAnimation(basicAnimation);

	dataProvider=new(ELeave)CICLAnimationDataProvider;
	CleanupStack::PushL(dataProvider);
	dataProvider->SetFileL(iFs, KSymBallFile());
	CleanupStack::Pop(dataProvider);
	CSpriteAnimation * spriteAnimation = CSpriteAnimation::NewL(dataProvider, TPoint(100,100), Ws(), *iOomWin->Window());
	CleanupStack::PushL(spriteAnimation);

	CAnimationGroup * animationGroup = CAnimationGroup::NewL();
	CleanupStack::PushL(animationGroup);
	animationGroup->Animations().Append(basicAnimation);
	animationGroup->Animations().Append(spriteAnimation);

	Wait(2000000); // Wait for the initialisation to complete
	animationGroup->Start(config);
	Wait(5000000);
	animationGroup->Stop();

	Wait(500000);

	CleanupStack::PopAndDestroy(animationGroup);
	CleanupStack::PopAndDestroy(spriteAnimation);
	CleanupStack::PopAndDestroy(basicAnimation);
	}
	
void COomStep::RunTestL(TInt aTest)
	{
	switch(aTest)
		{
		case 0:
			TestLoopingL();
			break;
		default:
			User::Leave(KErrArgument);
		}
	}
/**

	@SYMTestCaseID UIF-animation-TOomStep-doActiveTestStepL

	@SYMTestCaseDesc 
	This tests basic animation and sprite animation in a low memory
	condition.

	@SYMPREQ 269

	@SYMTestStatus Implemented

	@SYMTestPriority Medium

	@SYMTestActions 
	The test starts and stops animation for a basic and sprite
	animation group in a low memory condition, and records how many cells are 
	required to be available for the test to pass.  It starts at 1 free cell, and calls 
	test RunTestL and increments then increments the number of free cells until TestLoopingL
	operates without leaving.

	@SYMTestExpectedResults Pass

*/	
TVerdict COomStep::doActiveTestStepL()
	{
	InitialiseL();

	// ## Immediately return. It looks as though ICL leaks. Once that is fixed we can
	// ## try running this test.
	// ## see DEF050483
	
	const TInt KNumTests = 1;
	Wait(2000000); // Wait for windows and things to initialise their own memory.
	
	if(TestStepResult() == EPass)
		{
		__UHEAP_MARK;
		SetTestStepID(_L("UIF-animation-TOomStep-TestLoopingL"));
		for (TInt stage = 0; stage < KNumTests; ++stage)
			{
			TInt fail = 1;
			TInt passes = 0;
			while (passes < 6)
				{
				__UHEAP_FAILNEXT(fail);
				TRAPD(err, RunTestL(stage));
				if (err == KErrNone)
					++passes;
				else if (err == KErrNoMemory)
					passes = 0;
				else
					User::Leave(err);
				__UHEAP_RESET;
				++fail;
				}
			INFO_PRINTF3(_L("OOM Test %d passed after %d attempts"), stage, fail - passes);
			}
		REComSession::FinalClose();
	    iAnimTestWin->iScreen.ReleaseFont(iAnimTestWin->iFont);
	    delete iScreen;
	    RFbsSession::Disconnect();
		RecordTestResultL();
		CloseTMSGraphicsStep();
         __UHEAP_MARKEND;
		RFbsSession::Connect();
		}
	
	return TestStepResult();
	}
	
