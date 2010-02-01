// Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
 @test
 @internalComponent - Internal Symbian test code 
*/

#include <barsread.h>
#include <basched.h>
#include <coeaui.h>
#include <eikappui.h>
#include <eikapp.h>
#include <eikdoc.h>
#include <techview/eikdialg.h>
#include <techview/eikchlst.h>
#include <techview/eikchkbx.h>
#include <techview/eikmfne.h>
#include <techview/eikmenup.h>
#include <eikenv.h>
#include <ecom/ecom.h>

#include <tbmpanim.rsg>
#include <tbmpanim.mbg>
#include "Tanctl.h"
#include "TBMPAnim.hrh"

#include <bmpancli.h>
#include "TBmpAnimStep.h"



_LIT(resourceFileName,"z:\\resource\\apps\\tbmpanim\\tbmpanim.rsc");
const TInt KArrayGranularity = 5;



// Panics

void CTestContainer::Panic(TContainerPanic aPanic)
	{
	_LIT(KPanicCat,"TBmpAnim-Animation");
	User::Panic(KPanicCat, aPanic);
	}


TAnimationAttributes::TAnimationAttributes()
	: iNumberOfCycles(-1)
	{
	}


//
// CAnimationDlg
//

CAnimationDlg::CAnimationDlg(TFileName aFileName)
	: iFileName(aFileName)
	{
	}

CAnimationDlg::~CAnimationDlg()
	{
	if(iTimer)
		iTimer->Cancel();
	delete iTimer;
	}
void CAnimationDlg::PostLayoutDynInitL()
	{
	CAnimateFramesCtl* animationCtl = static_cast<CAnimateFramesCtl*>(Control(EBmpAnimationCtlId));
	animationCtl->StartAnimationL();


	TCallBack cb(Execute,this);
	iTimer = CPeriodic::NewL(EPriorityLow);
	iTimer->Start(TTimeIntervalMicroSeconds32(7000000), TTimeIntervalMicroSeconds32(1), cb);
		
	}

TInt CAnimationDlg::Execute(TAny* aDialog)
	{
	CAnimationDlg* theDialog = (CAnimationDlg*) aDialog;
	theDialog->iTimer->Cancel();
	delete theDialog->iTimer;
	theDialog->iTimer = 0;
	theDialog->TryExitL(-2);
	return 0;
	}

TBool CAnimationDlg::OkToExitL(TInt /*aControlId*/)
    {
	static_cast<CAnimateFramesCtl*>(Control(EBmpAnimationCtlId))->CancelAnimationL();
	return(ETrue);
    }

SEikControlInfo CAnimationDlg::CreateCustomControlL(TInt aControlType)
	{
	SEikControlInfo controlInfo;
	controlInfo.iControl = NULL;
	controlInfo.iTrailerTextId = 0;
	controlInfo.iFlags = 0;
	if (aControlType == EBmpAnimationCtlType)
		{
		controlInfo.iControl = CAnimateFramesCtl::NewL();
		static_cast<CAnimateFramesCtl*>(controlInfo.iControl)->SetFileName(iFileName);
		}
    return controlInfo;
	}

//
//
// class CAnimation
//



CAnimation::CAnimation()
	: iIndex(0),
	iType(ENoAnimation)
	{
	}

CAnimation::~CAnimation()
	{
	delete iAnimationCtl;
	}


void CAnimation::SetAnimationExtent()
	{
	TSize animSize = iAnimationCtl->MinimumSize();
	TPoint position(0, 0);
	switch (iType)
		{
	case EDefaultAnimation:
		position.SetXY(0, 0);
		break;
	case EDefaultAnimationSh:
		position.SetXY(100, 50);
		break;
	case EBallAnimation:
		position.SetXY(0, 100);
		break;
	case ERedPurpBallAnimationMaskedBackground:
		position.SetXY(0, 100);
		break;
	case ETBmpAnimBallAnimWindowCovering:
		position.SetXY(0, 100);
		break;
	default:
		return;
		}
	iAnimationCtl->SetExtent(position, animSize);
	}

void CAnimation::CopyAttributesFromClientData()
	{
	CBitmapAnimClientData* animClientData = iAnimationCtl->BitmapAnimData();
	if (animClientData)
		{
		iAttributes.iFrameIntervalInMilliSeconds = animClientData->FrameIntervalInMilliSeconds();
		iAttributes.iPlayMode = animClientData->PlayMode();
		}
	}

class CTestContainer;


//
//
// class CTestContainer
//

CTestContainer::CTestContainer()
	{
	}

CTestContainer::~CTestContainer()
	{
	if (iAnimationsArray)
		iAnimationsArray->ResetAndDestroy();
	delete iAnimationsArray;

	// Delete window used in test cases.
	delete iCoveringWindowControl;
	}

//
//
void CTestContainer::ConstructL()
	{
	iColor = KRgbBlack;
	CreateWindowL();
	RWindow window = Window();
	window.SetTransparencyAlphaChannel();
	window.SetBackgroundColor(TRgb(150,150,150,150));
	iAnimationsArray=new(ELeave) CArrayPtrFlat<CAnimation>(KArrayGranularity);
	
	//Set the background of the container window to the default. 
	iBackgroundType = EBackgroundBlackRedGreenYellowStripes;
	ActivateL();

	//Construct a window that can be used in test cases.
	iCoveringWindowControl = new (ELeave) CTestWindowControl;	
	iCoveringWindowControl->ConstructL();
	}

//
//
void CTestContainer::StartAnimationL(TInt aIndex)
	{
	TInt count = iAnimationsArray->Count();
	__ASSERT_ALWAYS(iAnimationsArray, Panic(TContainerPanicNoArray));
	__ASSERT_ALWAYS((aIndex >= 0 && (aIndex < count || aIndex == EAllAnimations)), Panic(TInvalidIndex));
	TInt startIndex = 0;
	if (aIndex != EAllAnimations)
		{
		count = aIndex;
		startIndex = aIndex;
		}
	else
		count -= 1;
	for (TInt i=startIndex; i<=count; i++)
		{
		CAnimation* singleAnimationCtl = iAnimationsArray->At(i);
		if (singleAnimationCtl->iAttributes.iOnOff)
			{
			singleAnimationCtl->iAnimationCtl->StartAnimationL();

			}
		}
	}

void CTestContainer::CancelAnimationL(TInt aIndex)
	{
	TInt count = iAnimationsArray->Count();
	__ASSERT_ALWAYS(iAnimationsArray, Panic(TContainerPanicNoArray));
	__ASSERT_ALWAYS((aIndex >= 0 && (aIndex < count || aIndex == EAllAnimations)), Panic(TInvalidIndex));
	TInt startIndex = 0;
	if (aIndex != EAllAnimations)
		{
		count = aIndex + 1;
		startIndex = aIndex;
		}
	for (TInt i=startIndex; i<count; i++)
		iAnimationsArray->At(i)->iAnimationCtl->CancelAnimationL();
	}

void CTestContainer::ShowAnimationL(TAnimationFlag aAnimationType)
	{
	TInt index = FindAnimation(aAnimationType);
	if (index == KErrNotFound)
		return;
	else
		StartAnimationL(index);
	}


TInt CTestContainer::FindAnimation(TAnimationFlag aAnimationType)
	{
	TInt count = iAnimationsArray->Count();
	__ASSERT_ALWAYS(iAnimationsArray, Panic(TContainerPanicNoArray));
	TInt index = 0;
	for(index=0; index<count; index++)
		if (iAnimationsArray->At(index)->iType == aAnimationType)
			return index;
	return KErrNotFound;
	}

CAnimation* CTestContainer::CreateAnimationByTypeL(TAnimationFlag aAnimationType)
	{
	__ASSERT_ALWAYS(iAnimationsArray, Panic(TContainerPanicNoArray));
	TInt count = iAnimationsArray->Count();
	CAnimation* singleAnimationCtl = new (ELeave) CAnimation;
	CleanupStack::PushL(singleAnimationCtl);
	singleAnimationCtl->iIndex = count;
	singleAnimationCtl->iType = aAnimationType;
	CAnimateFramesCtl* animationCtl = NULL;
	TRAPD(error, animationCtl = CAnimateFramesCtl::NewL());
	if (error != KErrNone)
		User::Panic(_L("New Animation"), error);

	singleAnimationCtl->iAnimationCtl = animationCtl;
	animationCtl->SetFileName(iFileName);

	TInt resourceReaderId = 0;
	switch (aAnimationType)
		{
	case EDefaultAnimation:
		resourceReaderId = R_TBMPANIM_IMAGE1;
		break;
	case EDefaultAnimationSh:
		resourceReaderId = R_TBMPANIM_IMAGE1;
		break;
	case EBallAnimation:
		resourceReaderId = R_TBMPANIM_IMAGE3;
		break;
	case ERedPurpBallAnimationMaskedBackground:
		resourceReaderId = R_TBMPANIM_IMAGE4;
		break;
	case ETBmpAnimBallAnimWindowCovering:
		resourceReaderId = R_TBMPANIM_IMAGE5;
		break;
	default:
		delete singleAnimationCtl;
		return NULL;
		}

	TResourceReader reader;
	iCoeEnv->CreateResourceReaderLC(reader,resourceReaderId);
	animationCtl->ConstructFromResourceL(reader);
	CleanupStack::PopAndDestroy(); // reader
	singleAnimationCtl->SetAnimationExtent();
	singleAnimationCtl->CopyAttributesFromClientData();
	iAnimationsArray->AppendL(singleAnimationCtl);
	CleanupStack::Pop(); // singleAnimationCtl
	return singleAnimationCtl;
	}

void CTestContainer::SizeChanged()
	{
	TInt count = 0;
	TRect rect = Rect();
	if(iAnimationsArray)
		count = iAnimationsArray->Count();
	for (TInt index = 0; index < count; index++)
		iAnimationsArray->At(index)->iAnimationCtl->SetRect(rect);
	}

TInt CTestContainer::CountComponentControls() const
	{
	return iAnimationsArray->Count();;
	}

void CTestContainer::Draw(const TRect& /*aRect*/) const
	{
	switch(iBackgroundType)
		{	
	case EBackgroundBlackRedGreenYellowStripes:
		{
		const TRect rect=Rect();
		CWindowGc& gc=SystemGc();
		gc.SetPenStyle(CGraphicsContext::ENullPen);
		gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
		gc.SetBrushColor(iColor);
		TInt yOffset = rect.Height() / 4;
		TRect portionRect(rect.iTl.iX, rect.iTl.iY, rect.iBr.iX, rect.iTl.iY + yOffset);
		gc.DrawRect(portionRect);
		gc.SetBrushColor(KRgbRed);
		portionRect.iTl.iY = portionRect.iBr.iY;
		portionRect.iBr.iY += yOffset;
		gc.DrawRect(portionRect);
		gc.SetBrushColor(KRgbGreen);
		portionRect.iTl.iY = portionRect.iBr.iY;
		portionRect.iBr.iY += yOffset;
		gc.DrawRect(portionRect);
		gc.SetBrushColor(KRgbYellow);
		portionRect.iTl.iY = portionRect.iBr.iY;
		portionRect.iBr.iY = rect.iBr.iY;
		gc.DrawRect(portionRect);
		gc.SetBrushColor(KRgbWhite);
		}
		break;
	case EBackgroundYellow:
		{
		const TRect rect=Rect();
		CWindowGc& gc=SystemGc();
		gc.SetPenStyle(CGraphicsContext::ENullPen);
		gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
		gc.SetBrushColor(KRgbYellow);
		gc.DrawRect(rect);
		}
		break;
	case EBackgroundBlue:
		{
		const TRect rect=Rect();
		CWindowGc& gc=SystemGc();
		gc.SetPenStyle(CGraphicsContext::ENullPen);
		gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
		gc.SetBrushColor(KRgbBlue);
		gc.DrawRect(rect);
		}
		break;
	default:
		break;
		}
	}

CCoeControl* CTestContainer::ComponentControl(TInt aIndex) const
	{
	return iAnimationsArray->At(aIndex)->iAnimationCtl;
	}

void CTestContainer::SetAppFileName(TDesC& aAppFileName)
	{
	iFileName = aAppFileName;
	}

void CTestContainer::CreateAndRunAnimationL()
	{
	CAnimateFramesCtl* animationCtl = CAnimateFramesCtl::NewL();
	CleanupStack::PushL(animationCtl);
	animationCtl->SetContainerWindowL(*this);
	animationCtl->SetFileName(iFileName);
	TResourceReader reader;
	iCoeEnv->CreateResourceReaderLC(reader, R_TBMPANIM_IMAGE3);
	animationCtl->ConstructFromResourceL(reader);
	CleanupStack::PopAndDestroy(); // reader
	animationCtl->StartAnimationL();	
	User::After(1000000);
	animationCtl->CancelAnimationL();
	animationCtl->SetFrameIndexL(4);
	User::After(1000000);
	animationCtl->StartAnimationL();
	User::After(1000000);
	animationCtl->SetPosition(TPoint(100, 100));
	User::After(1000000);
	animationCtl->SetFrameIndexL(1);
	User::After(1000000);
	animationCtl->SetFrameIndexL(4);
	User::After(1000000);
	animationCtl->SetFrameIntervalL(100);
	User::After(1000000);
	CleanupStack::PopAndDestroy(); // animationCtl
	}


void CTestContainer::SetAnimationAttributesL(TAnimationFlag aAnimationType)
	{
//	CCoeEnv* coeEnv = CCoeEnv::Static();
//	CSimpleAppUi* theApplication = (CSimpleAppUi*) (coeEnv->AppUi());
	
	CAnimation* animation = NULL;
	TInt animationIndex = FindAnimation(aAnimationType);
	TBool notFound = (animationIndex == KErrNotFound ? ETrue : EFalse);
	if (notFound)
		{
		animation = CreateAnimationByTypeL(aAnimationType);
		if (animation)
			animationIndex = animation->iIndex;
		else
			return;
		}
	else
		animation = iAnimationsArray->At(animationIndex);
	
	animation->iAttributes.iOnOff=ETrue;
		
	if (notFound)
		{
		CAnimateFramesCtl* animationCtl = iAnimationsArray->At(animationIndex)->iAnimationCtl;
		animationCtl->SetAnimationCtlWindowL(this);
		animationCtl->SetExtent(animationCtl->Position(), animationCtl->MinimumSize());
		animationCtl->ActivateL();
		animationCtl->DrawNow();
		}

	ShowAnimationL(aAnimationType);
	}
/*
 * INC 133854, DEF136660
 * 
 * Tests that the background frame is drawn
 * 
 * Actions:
 * 1. Create background frame
 * 2. Create another frame (atleast one frame is required to enter into the animation loop)
 * 3. Start the animation which displays both the frames on the screen
 * 4. Create a bitmap and blit into it the part of the screen where frame with background was displayed
 * 5. Create a bitmap and blit into it the background and frame bitmaps
 * 6. Compare the 2 bitmaps from step 4 and 5 (test fails if the 2 bitmaps dont match)
 * 
 * Expected Result: The background bitmap is drawn and test passes    
 */
TBool CTestContainer::TestRenderBackgroundFrameL()
	{
	TPoint pos(0,0);
	CAnimateFramesCtl* animationCtl = CAnimateFramesCtl::NewL();
	CleanupStack::PushL(animationCtl);
	animationCtl->SetAnimationCtlWindowL(this);
	animationCtl->BitmapAnimData()->SetPlayMode(CBitmapAnimClientData::ECycle);	
	animationCtl->ActivateL();
	
	// set backgroud frame
	CFbsBitmap* backgroundBitmap = iEikonEnv->CreateBitmapL(KTBmpAnimMBMFilePath, EMbmTbmpanimTextured);
	CleanupStack::PushL(backgroundBitmap);
	CBitmapFrameData* backgroundFrame = CBitmapFrameData::NewL(backgroundBitmap);	
	CleanupStack::PushL(backgroundFrame);
	animationCtl->BitmapAnimData()->SetBackgroundFrame(backgroundFrame);
	CleanupStack::Pop(2,backgroundBitmap);

	// set frame 1
	CFbsBitmap* frame1Bitmap = iEikonEnv->CreateBitmapL(KTBmpAnimMBMFilePath, EMbmTbmpanimLink0);
	CleanupStack::PushL(frame1Bitmap);
	CFbsBitmap* frame1BitmapMask = iEikonEnv->CreateBitmapL(KTBmpAnimMBMFilePath, EMbmTbmpanimLink0m);
	CleanupStack::PushL(frame1BitmapMask);	
	CBitmapFrameData* frame1 = CBitmapFrameData::NewL(frame1Bitmap,frame1BitmapMask);	
	CleanupStack::PushL(frame1);
	animationCtl->BitmapAnimData()->AppendFrameL(frame1);
	CleanupStack::Pop(3,frame1Bitmap);	//frame1, frame1BitmapMask, frame1Bitmap
	
	animationCtl->CompleteAnimationInitialisationL();
	animationCtl->Animation()->StartL();
	User::After(1000000);

	TBool ret=CompareScreenContentWithTestBitmapL(*backgroundFrame,*frame1, pos);
	
	animationCtl->Animation()->StopL();		
	CleanupStack::PopAndDestroy();	// animationCtl 		
	return ret;
	}

TBool CTestContainer::CompareScreenContentWithTestBitmapL(const CBitmapFrameData& aBkgdFrame, const CBitmapFrameData& aFrame1, const TPoint& aPos)
	{
	TSize size = aFrame1.Bitmap()->SizeInPixels();

	// Create test bitmap for comparison 
	CFbsBitmap* testBitmap = new (ELeave) CFbsBitmap;
	CleanupStack::PushL(testBitmap);
	User::LeaveIfError( testBitmap->Create(size, iEikonEnv->DefaultDisplayMode()));
	CFbsBitmapDevice* bitmapDevice = CFbsBitmapDevice::NewL(testBitmap);
	CleanupStack::PushL(bitmapDevice);
	CFbsBitGc* bitmapGc = CFbsBitGc::NewL();
	CleanupStack::PushL(bitmapGc);
	bitmapGc->Activate(bitmapDevice);
	// Blit the background bitmap
	bitmapGc->BitBlt(aPos, aBkgdFrame.Bitmap());
	// Blit the frame bitmap with mask
	bitmapGc->BitBltMasked(aPos, aFrame1.Bitmap(), size, aFrame1.Mask(), ETrue);
	
	// Create bitmap and blit the screen contents into it for comparing it with test bitmap created above
	TRect rect(aPos,size);
	CFbsBitmap* scrBitmap = new (ELeave) CFbsBitmap;
	CleanupStack::PushL(scrBitmap);
	User::LeaveIfError(scrBitmap->Create(size, iEikonEnv->DefaultDisplayMode()) );
	User::LeaveIfError( iEikonEnv->ScreenDevice()->CopyScreenToBitmap(scrBitmap,rect) );
	
	TBool ret=CompareBitmapsL(testBitmap,scrBitmap);	

	CleanupStack::PopAndDestroy(4);	//scrBitmap, bitmapGc, bitmapDevice, testBitmap
	return ret;
	}

/**
 Returns true if the contents of aBmp1 match the contents of aBmp2
 */
TBool CTestContainer::CompareBitmapsL(CFbsBitmap* aBmp1, CFbsBitmap* aBmp2)
	{
	if (aBmp1 == NULL || aBmp2 == NULL)
		{
		return EFalse;
		}

	TInt width = aBmp1->SizeInPixels().iWidth;
	TInt height = aBmp1->SizeInPixels().iHeight;	

	if (aBmp1->DisplayMode() == aBmp2->DisplayMode())
		{
		TInt lineLen = CFbsBitmap::ScanLineLength(width,aBmp1->DisplayMode());
		HBufC8* buf1 = HBufC8::NewMaxLC(lineLen);	
		HBufC8* buf2 = HBufC8::NewMaxLC(lineLen);
		TPtr8 ptr1(buf1->Des());
		TPtr8 ptr2(buf2->Des());

		TInt row = 0;

		for (row = 0; row < height; ++row)
			{
			aBmp1->GetScanLine(ptr1,TPoint(0,row),width,aBmp1->DisplayMode());
			aBmp2->GetScanLine(ptr2,TPoint(0,row),width,aBmp2->DisplayMode());
			if (ptr1!=ptr2)
				{
				CleanupStack::PopAndDestroy(buf2);
				CleanupStack::PopAndDestroy(buf1);
				return EFalse;
				}
			}
		CleanupStack::PopAndDestroy(buf2);
		CleanupStack::PopAndDestroy(buf1);
		}
	else
		{
		TRgb p1(0,0,0);
		TRgb p2(0,0,0);

		TInt i = 0;
		for(i = 0; i < width; i++)
			{
			TInt j = 0;
			for(j = 0; j < height; j++)
				{
				aBmp1->GetPixel(p1, TPoint(i, j));
				aBmp2->GetPixel(p2, TPoint(i, j));
				if(p1 != p2)
					{
					return EFalse;
					}
				}
			}
		}
	return ETrue;	
	}


/*
 
  Used by test case to display a gray filled window
 
*/
void CTestContainer::DisplayAnimCoveringWindowL()
	{
	iCoveringWindowControl->MakeVisible(ETrue);
	iCoveringWindowControl->DrawNow();
	}

/*
 
  CTestWindowControl, displays a gray filled window
 
*/
CTestWindowControl::CTestWindowControl()
	{
	}

CTestWindowControl::~CTestWindowControl()
	{
	}

void CTestWindowControl::ConstructL()
	{
	// Set test window control slightly smaller than the size of ball anim window.
	// So that the animation can be seen behind the covering window. 
	CreateWindowL();

	// Set the size before activating.
	SetRect(TRect(0,100,200,200));

	//Set the window invisible
	MakeVisible(EFalse);
	
	ActivateL();
	}

void CTestWindowControl::Draw(const TRect& /*aRect*/) const
	{
	//Set the covering window to be filled gray.
	const TRect rect=Rect();
	CWindowGc& gc=SystemGc();
	gc.SetPenStyle(CGraphicsContext::ENullPen);
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.SetBrushColor(KRgbGray);
	gc.DrawRect(rect);
	}

//
//
// class CSimpleAppUi
//

/**
  
  
   @SYMTestCaseID UIF-TBMPAnimStep-RunAnimWithMaskedBgL
  
   @SYMPREQ CR Number PHAR-5JHGVF.
  
   @SYMTestCaseDesc Tests that the masked background of the animation is displayed correctly\n
   when the bitmap animation passes over the animation masked background area.\n
   Also tests that the masked bitmap of the animation is displayed correctly.\n 
   
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions Call RunAnimWithMaskedBgL() which does the following:\n
   (1) Sets the flag to set the animation container window colour (yellow).\n
   (2) Call the window control DrawNow to display the window control.\n
   (3) Calls the control fn to set up and run the requested animation.\n
   
   API Calls:\n	
   CCoeControl::DrawNow()\n
   RBitmapAnim::StartL(), through the animation control in TAnctl.cpp\n
  
   @SYMTestExpectedResults The ball bitmap animation will be displayed on a yellow background,\n
   with the area surrounding the ball being yellow. The bitmap will then pass over its masked background which is green.\n
   The area surrounding the red ball will then be green and the masked bg will be displayed in place of the yellow window bg.\n
   Additionally, the masked bitmap animation will only display the red ball\n
   and the surrounding pixels of the ball bitmap will be transparent and display\n
   whatever is surrounding the ball at the time of the animation.\n
   The surrounding pixels of the ball bitmap are initially purple before the bitmap mask is applied.\n
  
  
 */
void CSimpleAppUi::RunAnimWithMaskedBgL()
	{
	//Switches from the default window background to a yellow one.
	iContainer->iBackgroundType = CTestContainer::EBackgroundYellow;
	iContainer->DrawNow();

	//Run the animation.
	iContainer->SetAnimationAttributesL(ERedPurpBallAnimationMaskedBackground);
	}


/**
   @SYMTestCaseID UIF-TBMPAnimStep-RunAnimWithWindowCoveringL
  
   @SYMPREQ Defect Numbers	INC039385 & INC040604 implemented in CR Number PHAR-5JHGVF.
  
   @SYMTestCaseDesc Tests that the animation redraws itself correctly,\n 
   when it is initially covered by another window and then the animation is uncovered,\n
   removing the covering window.\n
   
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions Call RunAnimWithWindowCoveringL() which does the following:\n
   (1) Sets the flag to set the container control window colour (blue).\n
   (2) Call the window control DrawNow to display the container window control\n
   (filled in blue).\n
   (3) Calls the control fn to display a gray window partially covering\n
   the ball animation and run the requested animation.\n
   (4) Runs the ball animation and then deletes the covering window.\n
   API Calls:\n	
   CCoeControl::DrawNow()\n
   RBitmapAnim::StartL(), through the animation control in TAnctl.cpp\n
  
   @SYMTestExpectedResults The covering window is displayed in gray on a blue window.\n
   The yellow ball animation starts running behind the gray covering window.\n
   The animation should be seen behind the gray covering window.\n
   The gray covering window is removed. The ball animation should be running,\n
   yellow ball on blue background.\n
   
 */
void CSimpleAppUi::RunAnimWithWindowCoveringL()
	{
	// Set the container window control to be filled blue.
	iContainer->iBackgroundType = CTestContainer::EBackgroundBlue;
	iContainer->DrawNow();

	// Setup and display the window control, filled in grey, which will initially cover animation.
	// Then the window is removed.
	iContainer->DisplayAnimCoveringWindowL();

	// Run the animation.
	iContainer->SetAnimationAttributesL(ETBmpAnimBallAnimWindowCovering);
	}



CSimpleAppUi::CSimpleAppUi(CTmsTestStep* aStep) : 
		CTestAppUi(aStep, resourceFileName, R_ANIM_HOTKEYS,R_ANIM_MENUBAR, R_TANIM_TOOLBAR)
	{
	}

CSimpleAppUi::~CSimpleAppUi()
    {
    delete iContainer;
    }

void CSimpleAppUi::ConstructL()
    {
	CTestAppUi::ConstructL();
	//BaseConstructL();
	ConstructContainerL();
	AutoTestManager().StartAutoTest();
    }

void CSimpleAppUi::ConstructContainerL()
    {
	TRect boundingRect=ClientRect(); // make toolband stretch to the screen width by default
    iContainer=new(ELeave) CTestContainer;
    iContainer->ConstructL();

	ReduceRect(boundingRect);
	iContainer->SetRect(boundingRect);	
    //vmTFileName tempFileName(Application()->BitmapStoreName());
	TFileName tempFileName(KTBmpAnimMBMFilePath);
	iContainer->SetAppFileName(tempFileName);
	iContainer->DrawNow();
    }


void CSimpleAppUi::HandleCommandL(TInt aCommand)
    {
    switch (aCommand)
        {
	case ETBmpAnimCmdStart:
		if (iContainer)
			iContainer->StartAnimationL(EAllAnimations);
		break;
	case ETBmpAnimCmdStop:
		if (iContainer)
			iContainer->CancelAnimationL(EAllAnimations);
		break;
	case ETBmpAnimCmdDefault:
		iContainer->SetAnimationAttributesL(EDefaultAnimation);
		break;
	case ETBmpAnimCmdDefaultSh:
		iContainer->SetAnimationAttributesL(EDefaultAnimationSh);
		break;
	case ETBmpAnimCmdBall:
		iContainer->SetAnimationAttributesL(EBallAnimation);
		break;
	case ETBmpAnimCmdMemoryTest:
		CmdTestOutOfMemoryL();
		break;
	case ETBmpAnimCmdAutoTestDLL:
		break;
	case ETBmpAnimCmdDlgWithAnim1:
		DialogWithAnimationL(R_TBMPANIM_DIALOG_WITH_ANIMATED_BALL);
		break;
	case ETBmpAnimCmdDlgWithAnim2:
		DialogWithAnimationL(R_TBMPANIM_DIALOG_WITH_FLOATING_SHEET);
		break;
	case ETBmpAnimCmdRedPurpBallMaskedBackground:
		// Run ball animation with masked background test case. 
		RunAnimWithMaskedBgL();
		break;
	case ETBmpAnimCmdBallAnimWindowCovering:
		// Run ball animation test case, firstly with an opaque window, partly covering the animation.
		RunAnimWithWindowCoveringL();
		break;
	case ETBmpAnimCmdBackgroundBitmap:
		if (!iContainer->TestRenderBackgroundFrameL())
			{
			iTestResult=CAutoTestManager::EFailed;
			}
		break;
    case EEikCmdExit:
		if (iContainer)
			iContainer->CancelAnimationL(EAllAnimations);
        CBaActiveScheduler::Exit();
        break;
    default:
		break;
        }
    }



void CSimpleAppUi::RunTestStepL(TInt aNumStep)
	{
	switch(aNumStep)
		{
		case 1:
		INFO_PRINTF1(_L("Default animation"));
		HandleCommandL(ETBmpAnimCmdDefault);
		break;
		case 2:
		INFO_PRINTF1(_L("Default animation Sh"));
		HandleCommandL(ETBmpAnimCmdDefaultSh);
		break;
		case 3:
		User::After(5000000);
		INFO_PRINTF1(_L("Ball animation"));
		HandleCommandL(ETBmpAnimCmdBall);
		break;
		case 4:
		INFO_PRINTF1(_L("Stop all animations"));
		User::After(10000000);
		HandleCommandL(ETBmpAnimCmdStop);
		case 5:
		INFO_PRINTF1(_L("Test out of memory"));
		HandleCommandL(ETBmpAnimCmdMemoryTest);
		break;
		case 6:
		INFO_PRINTF1(_L("Test dialog with animated ball"));
		HandleCommandL(ETBmpAnimCmdDlgWithAnim1);
		break;
		case 7:
		INFO_PRINTF1(_L("Test dialog with floating sheet"));
		HandleCommandL(ETBmpAnimCmdDlgWithAnim2);
		break;
		case 8:
			{
			// Stop all animations.
			HandleCommandL(ETBmpAnimCmdStop);

			// Run animation test case to test masked background and masked bitmap anim.
			SetTestStepID(_L("UIF-TBMPAnimStep-RunAnimWithMaskedBgL")); 
			INFO_PRINTF1(_L("Running ball animation with a masked background"));
			HandleCommandL(ETBmpAnimCmdRedPurpBallMaskedBackground);
			RecordTestResultL();
			}
		break;

		case 9:
			{
			// Wait to display test case.
			INFO_PRINTF1(_L("Waiting to display animation on screen......."));
			User::After(5000000);

			// Stop test case.
			INFO_PRINTF1(_L("Stopping Animation......"));
			HandleCommandL(ETBmpAnimCmdStop);

			//Reset container control window back to yellow.
			INFO_PRINTF1(_L("Reset window back to all yellow....."));
			iContainer->iBackgroundType = CTestContainer::EBackgroundYellow;
			iContainer->DrawNow();

			INFO_PRINTF1(_L("Completed reset after test case."));
			}		
		break;
		
		case 10:
			{
			// Run animation test case to test animation redraws correctly after 
			// a window covering the animation is removed.
			SetTestStepID(_L("UIF-TBMPAnimStep-RunAnimWithWindowCoveringL"));
			INFO_PRINTF1(_L("A covering window with ball animation running behind, then window removed to display anim"));
			HandleCommandL(ETBmpAnimCmdBallAnimWindowCovering);
			RecordTestResultL();
			CloseTMSGraphicsStep();
			}
		break;
		
		case 11:
			{
			// Wait to display test case.
			INFO_PRINTF1(_L("Waiting to display animation on screen......."));
			User::After(5000000);

			//Remove the covering window.
			iContainer->iCoveringWindowControl->MakeVisible(EFalse);
			}
		break;

		case 12:
			{	
			// Stop previous animation
			HandleCommandL(ETBmpAnimCmdStop);

			INFO_PRINTF1(_L("TestRenderBackgroundFrame"));
			HandleCommandL(ETBmpAnimCmdBackgroundBitmap);						
			if (iTestResult==CAutoTestManager::EFailed)
				{
				ERR_PRINTF1(_L("TestRenderBackgroundFrame FAILED"));
				iStep->SetTestStepResult(EFail);
				}
			}
			break;
			
		case 13:
			{	
			// Stop all animations.
			HandleCommandL(ETBmpAnimCmdStop);
		
			// Stop test cases running and exit.
			AutoTestManager().FinishAllTestCases(iTestResult);			
			}
		break;
		}	
	}

void CSimpleAppUi::CmdTestOutOfMemoryL()
	{
//	__ASSERT_ALWAYS(iContainer, CTestContainer::Panic(TContainerInalidPointer));
// Creates and deletes to bitmaps in order to allocate filename in the cache for FBserv
	CFbsBitmap* bitmap = iEikonEnv->CreateBitmapL(KTBmpAnimMBMFilePath/*Application()->BitmapStoreName()*/, 0);
	CFbsBitmap* mask = iEikonEnv->CreateBitmapL(KTBmpAnimMBMFilePath/*Application()->BitmapStoreName()*/, 1);
	delete bitmap;
	delete mask;
	iContainer->CancelAnimationL(EAllAnimations);
	TInt error = KErrNoMemory;
	iEikonEnv->BusyMsgL(_L("OOMemory Test"));
	__UHEAP_RESET;
	for(TInt fail=0; error != KErrNone; fail++)
		{
		__UHEAP_SETFAIL(RHeap::EFailNext, fail); // turn failure on
		__UHEAP_MARK;
		TRAP(error, iContainer->CreateAndRunAnimationL());
		if ( (error != KErrNoMemory) && (error != KErrNone) )
			User::Panic(_L("Memory Test"), error);
		REComSession::FinalClose();	
		__UHEAP_MARKEND;
		}
	__UHEAP_SETFAIL(RHeap::ENone, 0); // turn failure off
	iEikonEnv->BusyMsgCancel();
	iEikonEnv->InfoMsg(_L("OOMemory test completed"));
	}

void CSimpleAppUi::DialogWithAnimationL(TInt aResourceId)
	{
    TPtrC ptr;
	ptr.Set(KTBmpAnimMBMFilePath/*Application()->BitmapStoreName()*/);
	
	
	CEikDialog* dialog = new (ELeave) CAnimationDlg(ptr);
	dialog->ExecuteLD(aResourceId);
	}

void CTBmpAnimStep::ConstructAppL(CEikonEnv* aCoe)
    { // runs inside a TRAP harness
	aCoe->ConstructL();
	CSimpleAppUi* appUi=new(ELeave) CSimpleAppUi(this);
    aCoe->SetAppUi(appUi);
    appUi->ConstructL();
    }


CTBmpAnimStep::~CTBmpAnimStep()
/**
   Destructor
 */
	{
	}

CTBmpAnimStep::CTBmpAnimStep()
/**
   Constructor
 */
	{
	// Call base class method to set up the human readable name for logging
	SetTestStepName(KTBmpAnimStep);
	}


TVerdict CTBmpAnimStep::doTestStepL()
	{
	INFO_PRINTF1(_L("Test Started"));

	PreallocateHALBuffer();
	
	__UHEAP_MARK;

	CEikonEnv* coe=new CEikonEnv;
	TRAPD(err,ConstructAppL(coe));

	if (!err)
		coe->ExecuteD();

//	test.End();
	INFO_PRINTF1(_L("Test Finished"));

	REComSession::FinalClose();	
	__UHEAP_MARKEND;
	
	return TestStepResult();
	}


