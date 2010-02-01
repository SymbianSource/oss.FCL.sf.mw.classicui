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

#include <coeaui.h>
#include <coemain.h>
#include <coecntrl.h>
#include <coefont.h>
#include <coedef.h>
#include <coesndpy.h>
#include <coefontprovider.h>
#include <basched.h>
#include <bassnd.h>
#include <ecom/ecom.h>
#include "TConeZoomFont.h"

_LIT(KConeZoomFontText, "Zoom text!");


class CConeZoomFontControl : public CCoeControl
    {
public:
	static CConeZoomFontControl* NewL(const TRect& aRect);
	CConeZoomFontControl();
	~CConeZoomFontControl();
    void ConstructL(const TRect& aRect);
	TZoomFactor AccZoom();
private:
	           // Inherited from CCoeControl
	void Draw(const TRect& /*aRect*/) const;

private:
	HBufC*  iConeZoomFontText;
	TCoeFont iFont;
    };

class CConeZoomFontView : public CCoeControl
    {
public:
	static CConeZoomFontView* NewL();
	CConeZoomFontView();
	~CConeZoomFontView();
    void ConstructL();
    
    void Test1L();
    void Test2L();
    void Test3L();

    TInt CountComponentControls() const;
    CCoeControl* ComponentControl(TInt aIndex) const;

private:
	           // Inherited from CCoeControl
	void Draw(const TRect& /*aRect*/) const;
	void SizeChanged();

private:
	CConeZoomFontControl*  iControl;
    };


//
//
// CConeZoomFontControl
//
//
CConeZoomFontControl::CConeZoomFontControl():
iFont(TCoeFont::NormalFont())
	{
	}

CConeZoomFontControl* CConeZoomFontControl::NewL(const TRect& aRect)
	{
	CConeZoomFontControl* self = new(ELeave) CConeZoomFontControl();
	CleanupStack::PushL(self);
	self->ConstructL(aRect);
	CleanupStack::Pop(self);
	return self;
	}

CConeZoomFontControl::~CConeZoomFontControl()
	{
	delete iConeZoomFontText;
	}

void CConeZoomFontControl::ConstructL(const TRect& /*aRect*/)
    {
	iConeZoomFontText = KConeZoomFontText().AllocL();
	}

void CConeZoomFontControl::Draw(const TRect& /*aRect*/) const
	{
	CWindowGc& gc = SystemGc();
	TRect      drawRect = Rect();
	gc.Clear();
	drawRect.Shrink(10,10);		   	
	gc.DrawRect(drawRect);
	
	// Testing bit - get the correct font based on the current zoom factor.
	// NB, the Font() function takes a non-const reference to a TZoomFactor as
	// its second argument, so we can't pass the direct return from AccumulatedZoom()
	// as might seem to be the natural thing to do.
	TZoomFactor junk = AccumulatedZoom();
	const CFont& fontUsed = FindFontProvider().Font(TCoeFont::TitleFont(), junk);
	gc.UseFont(&fontUsed);
	TInt   baselineOffset=(drawRect.Height() + fontUsed.HeightInPixels())/2; 
	gc.DrawText(*iConeZoomFontText,drawRect,baselineOffset,CGraphicsContext::ECenter, 0);
	gc.DiscardFont();
	}

TZoomFactor CConeZoomFontControl::AccZoom()
	{
	return AccumulatedZoom();
	}
	
//
//
// CConeZoomFontView
//
//
CConeZoomFontView::CConeZoomFontView()
	{
	}

CConeZoomFontView* CConeZoomFontView::NewL()
	{
	CConeZoomFontView* self = new(ELeave) CConeZoomFontView();
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}

CConeZoomFontView::~CConeZoomFontView()
	{
	delete iControl;
	}
    
TInt CConeZoomFontView::CountComponentControls() const
	{
	return 1;
	}

/**
   @SYMTestCaseID UIF-TConeZoomFont-Test1L
  
   @SYMPREQ 857
  
   @SYMTestCaseDesc
   The parent is set to have relative zoom factor of 1000, and the child a relative zoom 
   of 500 using the CCoeControl:: SetZoomFactorL.  This should give a cumulative zoom 
   factor of 500. The child will draw text in its rectangle based this cumulative zoom factor.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
  
   @SYMTestActions
   Set the zoom factors of the parent and child objects
   Chect the accumulated zoom is calculated correctly
   finally call draw now to display zoomed text
  
   @SYMTestExpectedResults
   Will leave if accumulated zoom factor is incorrect, zoomed text is displayed.
  
 */
void CConeZoomFontView::Test1L()
	{
	TInt viewZoom = 1000;
	TInt controlZoom = 500;
	
	SetZoomFactorL(viewZoom, ERelativeZoom);
	iControl->SetZoomFactorL(controlZoom, ERelativeZoom);
	TZoomFactor viewZoomFactor = AccumulatedZoom();
	TZoomFactor controlZoomFactor = iControl->AccZoom();
	
	//Check to see if the AccumulatedZoom returns the correct values
	if ((viewZoomFactor.ZoomFactor() != viewZoom) ||
	    (controlZoomFactor.ZoomFactor() != ((viewZoom * controlZoom) /1000)))
		{
		User::Leave(-1);	
		}

	DrawNow();
	}

/**
   @SYMTestCaseID UIF-TConeZoomFont-Test2L
  
   @SYMPREQ 857
  
   @SYMTestCaseDesc
   The parent is set to have relative zoom factor of 500, and the child a absolute 
   zoom of 1000.  This should give a cumulative zoom factor of 1000 (because the 
   child's zoom is absolute). The child will draw text in its rectangle based this 
   cumulative zoom factor.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
  
   @SYMTestActions
   Set the zoom factors of the parent and child objects
   Chect the accumulated zoom is calculated correctly
   finally call draw now to display zoomed text
  
   @SYMTestExpectedResults
   Will leave if accumulated zoom factor is incorrect, zoomed text is displayed.
  
 */
void CConeZoomFontView::Test2L()
	{	
	TInt viewZoom = 500;
	TInt controlZoom = 1000;
	
	SetZoomFactorL(viewZoom, ERelativeZoom);
	iControl->SetZoomFactorL(controlZoom, EAbsoluteZoom);
	TZoomFactor viewZoomFactor = AccumulatedZoom();
	TZoomFactor controlZoomFactor = iControl->AccZoom();
	
	//Check to see if the AccumulatedZoom returns the correct values
	if ((viewZoomFactor.ZoomFactor() != viewZoom) ||
	    (controlZoomFactor.ZoomFactor() != (controlZoom)))
		{
		User::Leave(-1);	
		}
	
	DrawNow();
	}

/**
   @SYMTestCaseID UIF-TConeZoomFont-Test3L
  
   @SYMPREQ 857
  
   @SYMTestCaseDesc
   The parent is set to have absolute zoom factor of 1500, and the child 
   a relative zoom of 1500. This should give a cumulative zoom factor of 
   2250. The child will draw text in its rectangle based this cumulative 
   zoom factor.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
  
   @SYMTestActions
   Set the zoom factors of the parent and child objects
   Chect the accumulated zoom is calculated correctly
   finally call draw now to display zoomed text
  
   @SYMTestExpectedResults
   Will leave if accumulated zoom factor is incorrect, zoomed text is displayed.
  
 */
void CConeZoomFontView::Test3L()
	{
	
	TInt viewZoom = 1500;
	TInt controlZoom = 1500;
	
	SetZoomFactorL(viewZoom, EAbsoluteZoom);
	iControl->SetZoomFactorL(controlZoom, ERelativeZoom);
	TZoomFactor viewZoomFactor = AccumulatedZoom();
	TZoomFactor controlZoomFactor = iControl->AccZoom();
	
	//Check to see if the AccumulatedZoom returns the correct values
	if ((viewZoomFactor.ZoomFactor() != viewZoom) ||
	    (controlZoomFactor.ZoomFactor() != ((viewZoom * controlZoom) /1000)))
		{
		User::Leave(-1);	
		}

	DrawNow();
	}

CCoeControl* CConeZoomFontView::ComponentControl(TInt /*aIndex*/) const
	{
	return iControl;
	}

void CConeZoomFontView::ConstructL()
    {
	CreateWindowL();
    	
	iControl = CConeZoomFontControl::NewL(Rect());
	iControl->SetContainerWindowL(*this);
	iControl->SetParent(this);
	
	SetExtent( TPoint(20,20),TSize(600,200) );
	
	SetZoomFactorL(1000);
	iControl->SetZoomFactorL(1000, EAbsoluteZoom);

	ActivateL();
	}

void CConeZoomFontView::Draw(const TRect& /*aRect*/) const
	{
	
	CWindowGc& gc = SystemGc();
	TRect      drawRect = Rect();
	gc.Clear();
	drawRect.Shrink(10,10);		   	
	gc.DrawRect(drawRect);
	
	}
	
void CConeZoomFontView::SizeChanged()
	{
	ComponentControl(1)->SetRect( TRect(TPoint(20,20),TSize(560,160))) ;
	}

//
//
// CConeZoomFontAppUi
//
//
CConeZoomFontAppUi::CConeZoomFontAppUi(CTmsTestStep* aStep) :
CTestCoeAppUi(aStep)
{}

CConeZoomFontAppUi::~CConeZoomFontAppUi()
	{
	delete iView;
	}


void CConeZoomFontAppUi::ConstructL()
	{
	CTestCoeAppUi::ConstructL();
	
	iView = CConeZoomFontView::NewL();
	
	AutoTestManager().StartAutoTest();
	}
	
void CConeZoomFontAppUi::RunTestStepL(TInt aStepNum)
	{

	User::After(TTimeIntervalMicroSeconds32(1000000));
	
	TInt err;

	switch(aStepNum)
		{
		case 1:
			SetTestStepID(_L("UIF-TConeZoomFont-Test1L"));			
			_LIT(KTest1, "Zoom Relative 0.5");
			INFO_PRINTF1(KTest1);
			TRAP(err, iView->Test1L());
			RecordTestResultL();			
			break;
		case 2:
			SetTestStepID(_L("UIF-TConeZoomFont-Test2L"));			
			_LIT(KTest2, "Zoom Absolute 2.0");
			INFO_PRINTF1(KTest2);
			TRAP(err, iView->Test2L());
			RecordTestResultL();			
			break;
		case 3:
			SetTestStepID(_L("UIF-TConeZoomFont-Test3L"));					
			_LIT(KTest3, "Zoom Relative 1.5*1.5");
			INFO_PRINTF1(KTest3);
			TRAP(err, iView->Test3L());
			RecordTestResultL();	
			CloseTMSGraphicsStep();
			break;
		case 4:
			AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
			break;

		}
	}

//
//
// CConeZoomFontStep
//
//
void CTConeZoomFontStep::ConstructAppL(CCoeEnv* aCoe)
	{ // runs inside a TRAP harness
	aCoe->ConstructL();
	CConeZoomFontAppUi* appUi= new (ELeave) CConeZoomFontAppUi(this);
	aCoe->SetAppUi(appUi);
	appUi->ConstructL();
	}

CTConeZoomFontStep::CTConeZoomFontStep()
	{
	SetTestStepName(KTConeZoomFontStep);
	}

CTConeZoomFontStep::~CTConeZoomFontStep()
{}


TVerdict CTConeZoomFontStep::doTestStepL() // main function called by E32
	{
	_LIT(KTestStart, "Test Started");
	INFO_PRINTF1(KTestStart);
	
	PreallocateHALBuffer();

	__UHEAP_MARK;

	CCoeEnv* coe=new(ELeave) CCoeEnv;
	TRAPD(err,ConstructAppL(coe));

	if (!err)
		coe->ExecuteD();
	else
		{
		SetTestStepResult(EFail);
		delete coe;
		}

	REComSession::FinalClose();	

	__UHEAP_MARKEND;
	
	_LIT(KTestFinished, "Test Finished");
	INFO_PRINTF1(KTestFinished);
	return TestStepResult();
	}






