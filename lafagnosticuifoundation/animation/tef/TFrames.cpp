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


#include "TFrames.h"
#include "AnimationConfig.h"
#include "AnimationTestServer.h"

_LIT(KSquares1File, "Z:\\private\\10204F5B\\sqdisp1.gif");
_LIT(KSquares1MbmFile, "Z:\\private\\10204F5B\\sqdisp1.mbm");
_LIT(KSquares2File, "Z:\\private\\10204F5B\\sqdisp2.gif");
_LIT(KSquares2MbmFile, "Z:\\private\\10204F5B\\sqdisp2.mbm");
_LIT(KSquares3File, "Z:\\private\\10204F5B\\previous.gif");
_LIT(KSquares3MbmFile, "Z:\\private\\10204F5B\\previous.mbm");
// These two pairs of files are commented pending defect fixes.
// See comments in doACtiveTestStepL
//_LIT(KDisposalFile, "Z:\\private\\10204F5B\\disposal.gif");
//_LIT(KDisposalMbmFile, "Z:\\private\\10204F5B\\disposal.mbm");
//_LIT(KMovingFile, "Z:\\private\\10204F5B\\moving.gif");
//_LIT(KMovingMbmFile, "Z:\\private\\10204F5B\\moving.mbm");

const TInt KFramesWindowHeight = 32;
const TInt KFramesFrameLength = 100000;

//
// Windows:
//
CFramesTestWindow::CFramesTestWindow(RWsSession& aWsSession, CTestWindowGroup& aGroup, CWindowGc& aGc) : CTestWindow(aWsSession, aGroup, aGc)
	{
	}
	
void CFramesTestWindow::DrawL()
	{
	iGc.Reset();
	if (iOpaque)
		iGc.SetOpaque(ETrue);
	if (iLined)
		{
		for (TInt row = 0; row < KFramesWindowHeight; row += 4)
			{
			iGc.SetPenColor(0x00FF00);
			iGc.SetPenSize(TSize(2,2));
			iGc.SetPenStyle(CGraphicsContext::ESolidPen);
			iGc.DrawLine(TPoint(0, row), TPoint(400,row));
			}		
		}
	}

CFramesAnimationWindow::CFramesAnimationWindow(RWsSession& aWsSession, CTestWindowGroup& aGroup, CWindowGc& aGc) : CFramesTestWindow(aWsSession, aGroup, aGc)
	{
	}

void CFramesAnimationWindow::SetAnimations(RPointerArray<CAnimation>* aAnimations, TBool aBasic)
	{
	iBasicAnimations = aBasic;
	iAnimations = aAnimations;
	}

void CFramesAnimationWindow::DrawL()
	{
	CFramesTestWindow::DrawL();
	if(iBasicAnimations && iAnimations && iAnimations->Count())
		{
		for (TInt frame = 0; frame < iAnimations->Count(); ++frame)
			{
			static_cast<CBasicAnimation*>((*iAnimations)[frame])->Draw(iGc);
			}
		}
	}
	
CFramesFrameWindow::CFramesFrameWindow(RWsSession& aWsSession, CTestWindowGroup& aGroup, CWindowGc& aGc) :
CFramesTestWindow(aWsSession, aGroup, aGc)
	{
	}

CFramesFrameWindow::~CFramesFrameWindow()
	{
	FreeData();
	}

void CFramesFrameWindow::FreeData()
	{
	iFrames.ResetAndDestroy();
	iMasks.ResetAndDestroy();
	}
	
void CFramesFrameWindow::DrawL()
	{
	CFramesTestWindow::DrawL();
	if (iFrames.Count())
		{
		TPoint pos(0,0);
		TSize size = iFrames[0]->SizeInPixels();	
		
		for (TInt frame = 0; frame < iFrames.Count(); ++frame)
			{
			iGc.BitBltMasked(pos, iFrames[frame], size, iMasks[frame], EFalse);
			pos.iX += size.iWidth;
			}
		iGc.BitBltMasked(pos, iFrames[0], size, iMasks[0], EFalse);
		pos.iX += size.iWidth;
		iGc.BitBltMasked(pos, iFrames[1], size, iMasks[1], EFalse);
		pos.iX += size.iWidth;
		iGc.BitBltMasked(pos, iFrames[iFrames.Count() - 1], size, iMasks[iFrames.Count() - 1], EFalse);
		}
	}

TInt CFramesFrameWindow::LoadL(const TDesC& aFile)
	{
	FreeData();
	
	TInt num = 0;
	TInt err = KErrNone;
	CFbsBitmap* frame;
	CFbsBitmap* mask;
	while(err == KErrNone)
		{
		frame = new (ELeave) CFbsBitmap;
		CleanupStack::PushL(frame);
		mask = new (ELeave) CFbsBitmap;
		CleanupStack::PushL(mask);
		err = frame->Load(aFile,num * 2);
		if (!err)
			{
			User::LeaveIfError(mask->Load(aFile,num * 2 + 1));
			User::LeaveIfError(iMasks.Append(mask));
			CleanupStack::Pop(mask);
			User::LeaveIfError(iFrames.Append(frame));
			CleanupStack::Pop(frame);
			++num;
			}
		}
	CleanupStack::PopAndDestroy(mask);
	CleanupStack::PopAndDestroy(frame);
	if (err != KErrEof)
		User::LeaveIfError(err);
	Window()->Invalidate();
	return num;
	}

//
// The test:
//
CFrames::CFrames()
	{
	SetTestStepName(KFramesStep);
	}
	
CFrames::~CFrames()
	{
	iBasicAnimations.ResetAndDestroy();
	iSpriteAnimations.ResetAndDestroy();
	delete iBasicAnimWin;
	delete iSpriteAnimWin;
	delete iTransBasicAnimWin;
	delete iTransSpriteAnimWin;
	delete iFrameWin;
	delete iTransFrameWin;
	}
	
void CFrames::InitialiseL()
	{
	CAnimationTestStep::InitialiseL();
	
	ANIM_INFO1(_L("Begin test FRAMES"));

	TInt winborder = 2;
	iWinSize = Screen()->SizeInPixels();
	iWinSize.iWidth /= 2;
	iWinSize.iHeight = KFramesWindowHeight + winborder * 2;
	iBasicAnimWinPosition = TPoint(iWinSize.iWidth + winborder,winborder);
	iSpriteAnimWinPosition = TPoint(iBasicAnimWinPosition.iX, iBasicAnimWinPosition.iY + iWinSize.iHeight + winborder);
	iFrameWinPosition = TPoint(iSpriteAnimWinPosition.iX, iSpriteAnimWinPosition.iY + iWinSize.iHeight + winborder);
	iWinSize.iWidth -= winborder * 2;
	iWinSize.iHeight -= winborder * 2;

	iBasicAnimWin = new (ELeave) CFramesAnimationWindow(Ws(), *GroupWin(), *Gc());
	iBasicAnimWin->Window()->SetRequiredDisplayMode(iDisplayMode);
	iBasicAnimWin->Window()->SetExtent(iBasicAnimWinPosition, iWinSize);
	iBasicAnimWin->Window()->SetBackgroundColor(iBackgroundColor1);
	iBasicAnimWin->Window()->SetVisible(ETrue);
	iBasicAnimWin->Window()->Activate();
	
	iTransBasicAnimWin = new (ELeave) CFramesAnimationWindow(Ws(), *GroupWin(), *Gc());
	iTransBasicAnimWin->Window()->SetTransparencyFactor(0x808080);
	iTransBasicAnimWin->Window()->SetRequiredDisplayMode(iDisplayMode);
	iTransBasicAnimWin->Window()->SetExtent(iBasicAnimWinPosition, iWinSize);
	iTransBasicAnimWin->Window()->SetBackgroundColor(iBackgroundColor2);
	iTransBasicAnimWin->Window()->SetVisible(EFalse);
	iTransBasicAnimWin->Window()->Activate();

	iSpriteAnimWin = new (ELeave) CFramesAnimationWindow(Ws(), *GroupWin(), *Gc());
	iSpriteAnimWin->Window()->SetRequiredDisplayMode(iDisplayMode);
	iSpriteAnimWin->Window()->SetExtent(iSpriteAnimWinPosition, iWinSize);
	iSpriteAnimWin->Window()->SetBackgroundColor(iBackgroundColor1);
	iSpriteAnimWin->Window()->SetVisible(ETrue);
	iSpriteAnimWin->Window()->Activate();
	
	iTransSpriteAnimWin = new (ELeave) CFramesAnimationWindow(Ws(), *GroupWin(), *Gc());
	iTransSpriteAnimWin->Window()->SetTransparencyFactor(0x808080);
	iTransSpriteAnimWin->Window()->SetRequiredDisplayMode(iDisplayMode);
	iTransSpriteAnimWin->Window()->SetExtent(iSpriteAnimWinPosition, iWinSize);
	iTransSpriteAnimWin->Window()->SetBackgroundColor(iBackgroundColor2);
	iTransSpriteAnimWin->Window()->SetVisible(EFalse);
	iTransSpriteAnimWin->Window()->Activate();

	iFrameWin = new (ELeave) CFramesFrameWindow(Ws(), *GroupWin(), *Gc());
	iFrameWin->Window()->SetRequiredDisplayMode(iDisplayMode);
	iFrameWin->Window()->SetExtent(iFrameWinPosition, iWinSize);
	iFrameWin->Window()->SetBackgroundColor(iBackgroundColor1);
	iFrameWin->Window()->SetVisible(ETrue);
	iFrameWin->Window()->Activate();

	iTransFrameWin = new (ELeave) CFramesFrameWindow(Ws(), *GroupWin(), *Gc());
	iTransFrameWin->Window()->SetTransparencyFactor(0x808080);
	iTransFrameWin->Window()->SetRequiredDisplayMode(iDisplayMode);
	iTransFrameWin->Window()->SetExtent(iFrameWinPosition, iWinSize);
	iTransFrameWin->Window()->SetBackgroundColor(iBackgroundColor2);
	iTransFrameWin->Window()->SetVisible(EFalse);
	iTransFrameWin->Window()->Activate();

	}

/**
	@SYMTestCaseID UIF-animation-TFrames-TestFramesL

	@SYMTestCaseDesc 
	This tests basic animation and sprite animation with frames.

	@SYMPREQ 269

	@SYMTestStatus Implemented

	@SYMTestPriority High

	@SYMTestActions 
	The animation windows are initialised.  Then basic and sprite animations are
	started, the program waits for the animations to finish, and finally the output checked.

	@SYMTestExpectedResults Pass

*/
void CFrames::TestFramesL(TInt aFlags)
	{
	iBasicAnimWin->Window()->Invalidate();
	iTransBasicAnimWin->Window()->Invalidate();
	iSpriteAnimWin->Window()->Invalidate();
	iTransSpriteAnimWin->Window()->Invalidate();
	iFrameWin->Window()->Invalidate();
	iTransFrameWin->Window()->Invalidate();
	Ws().Finish();
	WaitForRedrawsToFinish();
    Ws().Finish();
	
	// Start the animations:
	TAnimationConfig config;
	config.iFlags = TAnimationConfig::ELoop | TAnimationConfig::ECountFrames;
	
	TInt frameCount = iBasicAnimations.Count() - 3;
	
	for (TInt frame = 0; frame < iBasicAnimations.Count(); ++frame)
		{
		// Some special cases:
		switch(frame - frameCount)
			{
			case 2:
				config.iFlags |= TAnimationConfig::EEndOnLastFrame;
				config.iData = frameCount;
				break;
			default:
				config.iData = frame;
				break;
			}
		iBasicAnimations[frame]->Start(config);
		Wait(KFramesFrameLength);
	    Ws().Finish();
	    WaitForRedrawsToFinish();
	    
		iSpriteAnimations[frame]->Start(config);
		Wait(KFramesFrameLength);
	    Ws().Finish();
	    WaitForRedrawsToFinish();
		}
	
	// Why * 4? because we seem to go very slowly?
	Wait(KFramesFrameLength * iBasicAnimations.Count() * 4);
	Ws().Finish();
	WaitForRedrawsToFinish();
    Ws().Finish();
    
    // When verifying output,
    // Should have at least one animation frame drawn 
    ANIMTESTRECT(TRect(iBasicAnimWinPosition, TSize(KFramesWindowHeight,KFramesWindowHeight)), TRect(iFrameWinPosition, TSize(KFramesWindowHeight,KFramesWindowHeight)));
	if(!(aFlags & ENoSprites))
		ANIMTESTRECT(TRect(iSpriteAnimWinPosition, TSize(KFramesWindowHeight,KFramesWindowHeight)), TRect(iFrameWinPosition, TSize(KFramesWindowHeight,KFramesWindowHeight)));
	}
/**
	@SYMTestCaseID UIF-animation-TFrames-TestFramesL2

	@SYMTestCaseDesc 
	This tests basic animation and sprite animation with frames.  

	@SYMPREQ 269

	@SYMTestStatus Implemented

	@SYMTestPriority High

	@SYMTestActions 
	The animation windows are initialised.  This function is used to set up tests by TestFramesL by
	initializing basic and sprite animations for a sequence of frames.

	@SYMTestExpectedResults Tests performed by TestFramesL.

*/
void CFrames::TestFramesL(CFramesAnimationWindow& aBasicAnimWin, CFramesAnimationWindow& aSpriteAnimWin, const TDesC& aFile, CFramesFrameWindow& aFrameWin, const TDesC& aMbm, TInt aFlags)
	{
	iBasicAnimations.ResetAndDestroy();
	iSpriteAnimations.ResetAndDestroy();
	// Load the MBM file into the frame window:
	TInt num = aFrameWin.LoadL(aMbm);
	TSize size = aFrameWin.Size();
	// Load the animation file multiple times:
	CICLAnimationDataProvider * dataProvider;

	// num + 3 = every frame, 2 more looped past the end, and 1 special case
	for(TInt frame = 0; frame < num + 3; ++frame)
		{
		CAnimation* anim;
		
		dataProvider=new (ELeave) CICLAnimationDataProvider;
		CleanupStack::PushL(dataProvider);
		dataProvider->SetFileL(iFs, aFile);
		CleanupStack::Pop(dataProvider);
		anim = CBasicAnimation::NewL(dataProvider, TPoint((size.iWidth * frame), 0), Ws(), *aBasicAnimWin.Window());
		CleanupStack::PushL(anim);
		User::LeaveIfError(iBasicAnimations.Append(anim));
		CleanupStack::Pop(anim);

		dataProvider=new (ELeave) CICLAnimationDataProvider;
		CleanupStack::PushL(dataProvider);
		dataProvider->SetFileL(iFs, aFile);
		CleanupStack::Pop(dataProvider);
		anim = CSpriteAnimation::NewL(dataProvider, TPoint((size.iWidth * frame), 0), Ws(), *aSpriteAnimWin.Window());
		CleanupStack::PushL(anim);
		User::LeaveIfError(iSpriteAnimations.Append(anim));
		CleanupStack::Pop(anim);
		}

	Wait(2000000); // wait for loading to complete
	// Give the animations to the animation window:
	aBasicAnimWin.SetAnimations(&iBasicAnimations, ETrue);
	aSpriteAnimWin.SetAnimations(&iSpriteAnimations, EFalse);

	TestFramesL(aFlags);
	}

void CFrames::TestFramesL(const TDesC& aFile, const TDesC& aMbm, TInt aFlags)
	{
	TestFramesL(*iBasicAnimWin, *iSpriteAnimWin, aFile, *iFrameWin, aMbm, aFlags);
	}

/**
	@SYMTestCaseID UIF-animation-TFrames-doActiveTestStepL

	@SYMTestCaseDesc 
	This tests basic animation and sprite animation with frames.  

	@SYMPREQ 269

	@SYMTestStatus Implemented

	@SYMTestPriority High

	@SYMTestActions 
	The animation windows are initialized.  This function is used to set up tests by function TestFramesL. 
	To begin three different squares files are used, with different disposal methods. Then testing is performed
	under a transparent window, on a transparent window, and using opaque windows.

	@SYMTestExpectedResults Testing performed by TestFramesL.

*/	
TVerdict CFrames::doActiveTestStepL()
	{
	_LIT(KTestMethod1, "Test disposal method 1");
	_LIT(KTestMethod2, "Test disposal method 2");
	_LIT(KTestMethod3, "Test disposal method 3");
	_LIT(KTestMasked, "Test disposal methods on masked images");
	_LIT(KTestMoving, "Test a small moving image");
	_LIT(KTestUnderTransparent, "Test under a transparent window");
	_LIT(KTestOnTransparent, "Test on a transparent window");
	_LIT(KTestOpaque, "Test opaque animation on a transparent window");
	
	InitialiseL();
	
	TInt stage = 0;
	TBool finished = false;
	SetTestStepID(_L("UIF-animation-TFrames-TestFramesL"));
	while(TestStepResult() == EPass && !finished)
		{
		switch(stage)
			{
			case 0:
				ANIM_INFO1(KTestMethod1);
				TestFramesL(KSquares1File, KSquares1MbmFile);
				break;
			case 1:
				ANIM_INFO1(KTestMethod2);
				TestFramesL(KSquares2File, KSquares2MbmFile);
				break;
			case 2:
				ANIM_INFO1(KTestMethod3);
				TestFramesL(KSquares3File, KSquares3MbmFile);
				break;
			case 3:
				ANIM_INFO1(KTestMasked);
				// Skip this test - I think the failure is caused by a disposal method of RestoreToPrevious
				// on an image which is smaller than the full animation, and which is immediately after an
				// image with a disposal method of RestoreToBackground.  However, I am not sure if it is this
				// code which is wrong, or the bitmaps to which the output is being compared.
				// Web browsers generally agree with the bitmaps, but not with the original GIF specification.
				// TestFramesL(KDisposalFile, KDisposalMbmFile); 
				break;
			case 4:
				ANIM_INFO1(KTestMoving);
				// ## Skip this too - defect against ICL because first frame is the wrong size and shape?
				// ## See DEF050484
				//TestFramesL(KMovingFile, KMovingMbmFile);
				stage = 100; // Do transparency last so we don't have to keep setting the windows up.
				break;
			case 101:
				ANIM_INFO1(KTestUnderTransparent);
				iTransBasicAnimWin->Window()->SetVisible(ETrue);
				iTransSpriteAnimWin->Window()->SetVisible(ETrue);
				iTransFrameWin->Window()->SetVisible(ETrue);
				iTransBasicAnimWin->SetLined(ETrue);
				iTransSpriteAnimWin->SetLined(ETrue);
				iTransFrameWin->SetLined(ETrue);
				TestFramesL(KSquares1File, KSquares1MbmFile, ENoSprites);
				break;
			case 102:
				ANIM_INFO1(KTestOnTransparent);
				iTransBasicAnimWin->SetLined(EFalse);
				iTransSpriteAnimWin->SetLined(EFalse);
				iBasicAnimWin->SetAnimations(0);
				iSpriteAnimWin->SetAnimations(0);
				iBasicAnimWin->SetLined(ETrue);
				iSpriteAnimWin->SetLined(ETrue);
				iTransFrameWin->SetLined(EFalse);
				iFrameWin->FreeData();
				iFrameWin->SetLined(ETrue);
				TestFramesL(*iTransBasicAnimWin, *iTransSpriteAnimWin, KSquares2File, *iTransFrameWin, KSquares2MbmFile, ENoSprites);
				break;
			case 103:
				ANIM_INFO1(KTestOpaque);
				iTransBasicAnimWin->SetOpaque(ETrue);
				iTransSpriteAnimWin->SetOpaque(ETrue);
				iTransFrameWin->SetOpaque(ETrue);
				TestFramesL(ENoSprites);
				break;
			default:
				finished = ETrue;
			}
		++stage;
		}

	RecordTestResultL();
	CloseTMSGraphicsStep();

	return TestStepResult();
	}
	
