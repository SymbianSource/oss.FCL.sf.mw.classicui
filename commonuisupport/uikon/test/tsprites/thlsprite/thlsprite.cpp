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
// The test step performs tests to display sprites from a sprite set.
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/


#include <eikenv.h>
#include <coecntrl.h>
#include <coemain.h>
#include <techview/eikdialg.h>
#include <techview/eikbtgpc.h>

#include <eikappui.h>
#include <eikapp.h>
#include <eikdoc.h>
#include <uikon.hrh>
#include <eikon.mbg>
#include <gulsprite.h>
#include <e32math.h>
#include <techview/eikmenup.h>
#include <techview/eikdialg.h>
#include <ecom/ecom.h>

#include "thlsprite.hrh"
#include "thlsprite.h"



_LIT(KHLSpriteResourceFilePath, "");


CHLSpriteAppView::~CHLSpriteAppView()
/**
  Destructor
*/
	{
	delete iSourceSpriteSet;
	delete iTargetSpriteSet;
	}

/**
   Auxiliary function for all Test Cases
  
   The method creates a view that displays a sprite and invokes method
   CHLSpriteAppView::TryCreateSpriteSetL() which creates objects of class 
   CSpriteSet. The CSpriteSet object created stores number of bitmap/mask
   pairs.
  
 */
void CHLSpriteAppView::ConstructL(const TRect& aRect)
	{
	CreateWindowL();
	SetRect(aRect);
	iMaskIsInverted = EFalse;
	iClippingRect = TRect(0,0,0,0);
	TryCreateSpriteSetL();
	iSpriteSideLength = 0; // start with 0 side for sprite
	iResizeMode = CSpriteSet::ENoResizing;	// start with no resizing
	TInt baseline = (2*(iEikonEnv->TitleFont()->AscentInPixels() + 10)) + 30;
	TInt targetTlX = ((Rect().iBr.iX - 11)/2) + 10;
	iTargetSpriteTl = TPoint(targetTlX,baseline);
	ActivateL();
	iSpriteIsDisplayed = ETrue;
	}


/**
   Auxiliary function for TestCaseID THLSPRITE-HandleCommandL
  
   The method creates two sprite sets by calling CSpriteSet::NewL() to
   initialize member variables iSourceSpriteSet and iTargetSpriteSet. The
   method loads bitmaps/masks pair from a multi-bitmap file and
   packages them into CGulIcon object.They are then added to the sprite set
   pointed by iSourceSpriteSet by calling CSpriteSet::AddMemberL().
  
 */
void CHLSpriteAppView::TryCreateSpriteSetL()
	{
	_LIT(KDefaultBitmapPath,"z:\\Resource\\Uiklaf\\eikon.mbm");

	// following 2 if statements are for the convenience of the appui handlecommand function (not really required for initial construction).
	if(iSourceSpriteSet)
		{
		delete iSourceSpriteSet;
		iSourceSpriteSet = NULL;
		}
	if(iTargetSpriteSet)
		{
		delete iTargetSpriteSet;
		iTargetSpriteSet = NULL;
		}

	CFbsBitmap* sourceBitmap = CEikonEnv::Static()->CreateBitmapL(KDefaultBitmapPath,EMbmEikonMenuhighlight);
	CleanupStack::PushL(sourceBitmap);
	CFbsBitmap* sourceMaskBitmap = CEikonEnv::Static()->CreateBitmapL(KDefaultBitmapPath,EMbmEikonMenuhighlightm);
	CleanupStack::PushL(sourceMaskBitmap);
	CGulIcon* normalSourceSpriteMember = CGulIcon::NewL(sourceBitmap, sourceMaskBitmap);
	CleanupStack::Pop(2, sourceBitmap);
	CleanupStack::PushL(normalSourceSpriteMember);
	iSourceSpriteSet = CSpriteSet::NewL(*DrawableWindow(),iEikonEnv->WsSession(),*iEikonEnv->ScreenDevice(),normalSourceSpriteMember,EFalse);
	CleanupStack::Pop(normalSourceSpriteMember);
	CFbsBitmap* sourceDimmedBitmap = CEikonEnv::Static()->CreateBitmapL(KDefaultBitmapPath,EMbmEikonMenuhighlightd);
	CleanupStack::PushL(sourceDimmedBitmap);
	CFbsBitmap* sourceDimmedMaskBitmap = CEikonEnv::Static()->CreateBitmapL(KDefaultBitmapPath,EMbmEikonMenuhighlightm);
	CleanupStack::PushL(sourceDimmedMaskBitmap);
	CGulIcon* dimmedSourceSpriteMember = CGulIcon::NewL(sourceDimmedBitmap, sourceDimmedMaskBitmap);
	CleanupStack::Pop(2, sourceDimmedBitmap);
	CleanupStack::PushL(dimmedSourceSpriteMember);
	iSourceSpriteSet->AddMemberL(dimmedSourceSpriteMember);
	CleanupStack::Pop(dimmedSourceSpriteMember);

	CFbsBitmap* targetBitmap = CEikonEnv::Static()->CreateBitmapL(KDefaultBitmapPath,EMbmEikonMenuhighlight);
	CleanupStack::PushL(targetBitmap);
	CFbsBitmap* targetMaskBitmap = CEikonEnv::Static()->CreateBitmapL(KDefaultBitmapPath,EMbmEikonMenuhighlightm);
	CleanupStack::PushL(targetMaskBitmap);
	CGulIcon* normalTargetSpriteMember = CGulIcon::NewL(targetBitmap, targetMaskBitmap);
	CleanupStack::Pop(2, targetBitmap);
	CleanupStack::PushL(normalTargetSpriteMember);
	iTargetSpriteSet = CSpriteSet::NewL(*DrawableWindow(),iEikonEnv->WsSession(),*iEikonEnv->ScreenDevice(),normalTargetSpriteMember,iMaskIsInverted);
	CleanupStack::Pop(normalTargetSpriteMember);
	CFbsBitmap* targetDimmedBitmap = CEikonEnv::Static()->CreateBitmapL(KDefaultBitmapPath,EMbmEikonMenuhighlightd);
	CleanupStack::PushL(targetDimmedBitmap);
	CFbsBitmap* targetDimmedMaskBitmap = CEikonEnv::Static()->CreateBitmapL(KDefaultBitmapPath,EMbmEikonMenuhighlightm);
	CleanupStack::PushL(targetDimmedMaskBitmap);
	CGulIcon* dimmedTargetSpriteMember = CGulIcon::NewL(targetDimmedBitmap, targetDimmedMaskBitmap);
	CleanupStack::Pop(2, targetDimmedBitmap);
	CleanupStack::PushL(dimmedTargetSpriteMember);
	iSourceSpriteSet->AddMemberL(dimmedTargetSpriteMember);
	CleanupStack::Pop(dimmedTargetSpriteMember);
	}



void CHLSpriteAppView::HandleTimerCallbackL()
	{
	iSpriteSideLength++;
	DrawTargetSpriteNowL();
	}


/**
   Auxiliary function for TestCaseID THLSPRITE-HandleCommandL
  
   The method is an override from CCoeControl. It refreshes the view. It is
   used to draw the source and target sprite on the view.
  
 */
void CHLSpriteAppView::Draw(const TRect& /*aRect*/) const
	{
	CWindowGc& gc = SystemGc();
	TRect rect = Rect();
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.SetBrushColor(KRgbYellow);
	gc.SetPenStyle(CGraphicsContext::ESolidPen);
	gc.SetPenColor(KRgbBlack);
	gc.DrawRect(rect);
	rect.Shrink(10,10);
	gc.SetBrushStyle(CGraphicsContext::ENullBrush);
	gc.DrawRect(rect);
	rect.Shrink(1,1);
	const CFont* font = iEikonEnv->TitleFont();
	gc.UseFont(font);
	TInt baseline = font->AscentInPixels() + 10;
	gc.DrawText(_L("HIGHLIGHT SPRITES APP"), rect, baseline, CGraphicsContext::ECenter);
	baseline*=2;
	gc.DrawText(_L("SOURCE"), rect, baseline, CGraphicsContext::ELeft);
	gc.DrawText(_L("TARGET"), rect, baseline, CGraphicsContext::ERight);
	baseline+=10;
	gc.DrawLine(TPoint(rect.iBr.iX/2,baseline),TPoint(rect.iBr.iX/2,rect.iBr.iY - 10));
	gc.DiscardFont();

	baseline+=20;
	TInt sourceTlX = rect.iTl.iX + 10;
	TRAPD(err,	//TRAPD is used to stop leavescan errors occurring, and ignore error value.
		iSourceSpriteSet->PrepareSpriteForDisplayL(0,TPoint(sourceTlX,baseline),TSize(),CSpriteSet::ENoResizing); 
		iSourceSpriteSet->StartDisplayingSpriteL();	
		DrawTargetSpriteNowL();
		);
	__ASSERT_ALWAYS(!err,User::Panic(_L("CHLSpriteAppView"),err));	
	gc.SetBrushStyle(CGraphicsContext::ENullBrush);
	gc.SetPenStyle(CGraphicsContext::ESolidPen);
	gc.SetPenColor(KRgbWhite);
	gc.DrawRect(iClippingRect);
	}


/**
   Auxiliary function for TestCaseID THLSPRITE-HandleCommandL
  
   The method prepares and brings the sprite onto the visible area of the
   screen if the variable iSpriteIsDisplayed is set to true and if
   iTargetSpriteSet is not null.If this conditions is not met then the method 
   stops the display of the sprite on the visible area of the screen.
  
 */
void CHLSpriteAppView::DrawTargetSpriteNowL() const
	{
	if(iSpriteIsDisplayed && iTargetSpriteSet)
		{
		iTargetSpriteSet->PrepareSpriteForDisplayL(0,iTargetSpriteTl,TSize(iSpriteSideLength,iSpriteSideLength),iResizeMode);
		iTargetSpriteSet->StartDisplayingSpriteL();
		}
	else
		{
		iTargetSpriteSet->StopDisplayingSprite();
		}
	}



CHLSpriteAppUi::CHLSpriteAppUi(CTmsTestStep *aStep) :
	CTestAppUi(aStep,
		KHLSpriteResourceFilePath)
/**
   Constructor
 */
	{
	}


/**
   Auxiliary function for all Test Cases
  
   The method initiates the creation of a view that displays a sprite and sets
   active object with lowest priority for running test in auto mode. It also
   creates a timer that is used for running tests.
  
 */
void CHLSpriteAppUi::ConstructL()
	{
	CTestAppUi::ConstructL();
	iAppView = new(ELeave) CHLSpriteAppView;
	TRect rect(ClientRect());
	iTimer=CPeriodic::NewL(CActive::EPriorityStandard);
	
	ReduceRect(rect);
	iAppView->ConstructL(rect);
	// setup the random number seed (a singleton)
	TTime time;
	time.HomeTime();
	iSeed = time.Int64();

	AutoTestManager().StartAutoTest();
	}
	

CHLSpriteAppUi::~CHLSpriteAppUi()
/**
   Destructor
 */
	{
	delete iAppView;
	delete iTimer;
	}


/**
   @SYMTestCaseID UIF-THLSPRITE-HandleCommandL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Tests displaying sprite in the set on the screen under various
   conditions.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method performs the following tests:\n
   1) Displaying the sprite in the set for various resize modes namely
   (a) ENoResizing (b) EResizeHorizToFit (c) EResizeVertToFit
   (d) EResizeHorizAndVertToFit\n
   2) Displaying the sprite in the set with size specified by the test.\n
   3) Toggle between displaying & erasing the sprite in the set.\n
   4) Toggle between displaying & erasing a bitmap/mask pair with inverted
   mask in the set.\n
   5) Displaying the sprite in the set at the position specified by the test.\n
   6) Displaying the sprite in the set within boundary specified by a
   rectangle.\n
  
   @SYMTestExpectedResults Each of the tests should display the sprite as
   expected for the values assigned to parameters of methods covered by the
   test.\n
   
 */
void CHLSpriteAppUi::HandleCommandL(TInt aCommand)
	{
	_LIT(KNullAppView,"No App View");
	__ASSERT_ALWAYS(iAppView != NULL, User::Panic(KNullAppView,0));
	switch(aCommand)
		{
	case ECmdNoResizing:
		{
		iAppView->iResizeMode = CSpriteSet::ENoResizing;
		iAppView->DrawTargetSpriteNowL();
		break;
		}
	case ECmdResizeHorizToFit:
		{
		iAppView->iResizeMode = CSpriteSet::EResizeHorizToFit;
		iAppView->DrawTargetSpriteNowL();
		break;
		}
	case ECmdResizeVertToFit:
		{
		iAppView->iResizeMode = CSpriteSet::EResizeVertToFit;
		iAppView->DrawTargetSpriteNowL();
		break;
		}
	case ECmdResizeHorizAndVertToFit:
		{
		iAppView->iResizeMode = CSpriteSet::EResizeHorizAndVertToFit;
		iAppView->DrawTargetSpriteNowL();
		break;
		}
	case ECmdStart:
		{
		if (iTimer && !(iTimer->IsActive()))
			{
			iTimer->Start(1000000,1000000,TCallBack(TimerCallbackL,iAppView));
			iEikonEnv->InfoMsg(_L("Timer Started !"));
			}
		iAppView->DrawTargetSpriteNowL();
		break;
		}
	case ECmdStop:
		{
		if(iTimer->IsActive())
			{
			iTimer->Cancel();
			iEikonEnv->InfoMsg(_L("Timer Cancelled !"));
			iAppView->iSpriteSideLength = 0;	// reset this value
			}
		iAppView->DrawTargetSpriteNowL();
		break;
		}
	case ECmdRandom:
		{
		// pick a random number in the range [0, (iAppView->Rect().Height()/2)]
		TInt randomNum;
		do
			{
			randomNum = Math::Rand(iSeed);
			randomNum = (randomNum & (iAppView->Rect().Height()/2));
			}
		while(randomNum<=0);

		if(iTimer->IsActive())
			{
			iTimer->Cancel();
			iEikonEnv->InfoMsg(_L("Timer Cancelled !"));
			}
		iAppView->iSpriteSideLength = randomNum;	// reset this value
		iAppView->DrawTargetSpriteNowL();
		break;
		}
	case ECmdToggleDisplaySprite:
		{
		iAppView->iSpriteIsDisplayed = (!iAppView->iSpriteIsDisplayed);
		iAppView->DrawTargetSpriteNowL();
		break;
		}
	case ECmdToggleInvertedMask:
		{
		iAppView->iMaskIsInverted = (!iAppView->iMaskIsInverted);
		iAppView->TryCreateSpriteSetL();
		iAppView->DrawTargetSpriteNowL();
		break;
		}
	case ECmdTranslateSprite:
		{
		//TPoint translateOffset(50,50);
		
			if(iAppView->iTargetSpriteSet)
				{
				iAppView->iTargetSpriteTl += iTranslateOffset;
				iAppView->iTargetSpriteSet->TranslateSpritePosition(iTranslateOffset);
				}
		iAppView->DrawTargetSpriteNowL();
		break;
		}
	case ECmdSetClippingRect:
		{
		if(iAppView->iTargetSpriteSet)
			{
			iAppView->iTargetSpriteSet->SetClippingRect(iAppView->iClippingRect);
			}

		iAppView->DrawNow();
		break;
		}
	case EEikCmdExit:
		{
		Exit();
		break;
		}
	default:
		break;
		}
	}



TInt CHLSpriteAppUi::TimerCallbackL(TAny* aPtr)
	// static
	{
	STATIC_CAST(CHLSpriteAppView*,aPtr)->HandleTimerCallbackL();
	return 0;
	}
	
	
/**
   Auxiliary function for all Test Cases
  
   The method is an override from CTestAppUi. The method initiates all tests
   to be performed by calling CHLSpriteAppUi::HandleCommandL().
   
 */
void CHLSpriteAppUi::RunTestStepL(TInt aNumStep)
	{
	//only for debug
//#ifdef FORCE_AUTO
	User::After(TTimeIntervalMicroSeconds32(500000));
//#endif	
	
	switch(aNumStep)
		{
		case 1:
		INFO_PRINTF1(_L("Toggle display sprite"));
		HandleCommandL(ECmdToggleDisplaySprite);
		break;
		case 2:
		INFO_PRINTF1(_L("Toggle display sprite"));
		HandleCommandL(ECmdToggleDisplaySprite);
		break;
		case 3:
		INFO_PRINTF1(_L("Toggle inverted mask"));
		HandleCommandL(ECmdToggleInvertedMask);
		// left sprite might be hidden, so redraw client area
		iAppView->DrawNow();
		break;
		case 4:
		INFO_PRINTF1(_L("Toggle inverted mask"));
		HandleCommandL(ECmdToggleInvertedMask);
		// left sprite might be hidden, so redraw client area
		iAppView->DrawNow();
		break;
		case 5: case 6:
		INFO_PRINTF1(_L("Translate sprite to new position"));
		iTranslateOffset = TPoint(50, 50);
		HandleCommandL(ECmdTranslateSprite);
		break;
		case 7: case 8:
		INFO_PRINTF1(_L("Translate sprite to new position"));
		iTranslateOffset = TPoint(-50, -50);
		HandleCommandL(ECmdTranslateSprite);
		break;
		case 9: 
		INFO_PRINTF1(_L("Set clipping rectangle"));
		iAppView->iClippingRect = TRect(0, 0, 300, 150);
		HandleCommandL(ECmdSetClippingRect);
		break;
		case 10:
		INFO_PRINTF1(_L("Set clipping rectangle"));
		iAppView->iClippingRect = TRect(0, 0, 350, 150);
		HandleCommandL(ECmdSetClippingRect);
		break;
		case 11:
		INFO_PRINTF1(_L("Set clipping rectangle"));
		iAppView->iClippingRect = TRect(0, 0, 0, 0);
		HandleCommandL(ECmdSetClippingRect);
		break;
		case 12:
		INFO_PRINTF1(_L("Resize random number"));
		HandleCommandL(ECmdRandom);
		break;
		case 13:
		INFO_PRINTF1(_L("Set horiz to fit"));
		HandleCommandL(ECmdResizeHorizToFit);
		break;
		case 14:
		INFO_PRINTF1(_L("Set vert to fit"));
		HandleCommandL(ECmdResizeVertToFit);
		break;
		case 15:
		INFO_PRINTF1(_L("Set no resizing"));
		HandleCommandL(ECmdNoResizing);
		break;
		case 16:
		INFO_PRINTF1(_L("Set vert and horiz to fit"));
		HandleCommandL(ECmdResizeHorizAndVertToFit);
		break;
		case 17:
		INFO_PRINTF1(_L("Set no resizing"));
		HandleCommandL(ECmdNoResizing);
		break;
		case 18:
		AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
		break;
		}
	}



CTestThlspriteStep::CTestThlspriteStep()
/**
   Constructor
 */
	{
	SetTestStepName(KHlSpriteStep);
	}



CTestThlspriteStep::~CTestThlspriteStep()
/**
   Destructor
 */
	{
	}



/**
   Auxiliary function for all Test Cases
  
   The method creates & sets the application's user interface object.
   
 */
void CTestThlspriteStep::ConstructAppL(CEikonEnv* aCoe)
    { // runs inside a TRAP harness
	aCoe->ConstructL();

	CTestAppUi* appUi= new (ELeave) CHLSpriteAppUi(this);
    aCoe->SetAppUi(appUi);
    appUi->ConstructL();
    }


/**
   Auxiliary function for all Test Cases
  
   The method creates & sets the application's user interface object to
   launch the application which will initiate the tests.
   
 */
TVerdict CTestThlspriteStep::doTestStepL() // main function called by E32
	{
	PreallocateHALBuffer();
	__UHEAP_MARK;

	CEikonEnv* coe=new CEikonEnv;
	TRAPD(err,ConstructAppL(coe));

	if (!err)
		coe->ExecuteD();

	REComSession::FinalClose();	
	__UHEAP_MARKEND;

	return TestStepResult();
	}

