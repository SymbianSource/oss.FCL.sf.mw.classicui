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
// Test exercises switchable graphics contexts, hit regions for 
// pointer events, support in public API for separate drawing of
// foreground and background.\n
// Test intend for 9.1 and onward.\n
// 
//

/**
 @file 
 @internalComponent 
*/
#include <coeaui.h>
#include <coemain.h>
#include <coedef.h>
#include <coesndpy.h>
#include <basched.h>
#include <bassnd.h>
#include <ecom/ecom.h>
#include "TConeTransition.h"
#include <gulgcmap.h>


/**
  Second Phase constructor for CTestControlGc Class.\n
  Sets the control name,pen colour and brush colour settings.\n
  Also sets Supress output option is enabled or not.\n
  Activates the control.\n
*/
void CTestControlGc::ConstructL(TPoint aPt, TSize aSize, TRgb aPenColor, TRgb aBrushColor, const TDesC &aControlName)
    {
    iControlName=aControlName;
    iPenColor = aPenColor;
    iBrushColor = aBrushColor;
    iSupressOutput = EFalse;
    SetExtent(aPt, aSize);
    
    ActivateL();
    }

/**
  Destructor for CTestControlGc Class.\n
*/
CTestControlGc::~CTestControlGc()
    {
    }
/**
  This function is called whenever a control gains or loses focus,
  as a result of a call to SetFocus().\n
  A typical use of FocusChanged() is to change the appearance of the control to 
  indicate whether or not it has focus, for example by drawing a focus rectangle around it.\n
 
*/
void CTestControlGc::FocusChanged(TDrawNow aDrawNow)
	{
    if (aDrawNow)
        {
        ActivateGc();
        DeactivateGc();
        }
    }
/**
  Draw Function for the CTestControlGc Class.\n
  Checks if the drawing to control is supressed.\n
  If Yes, the function return.\n
  Else  sets the pen and brush settings and Draws.\n
*/
void CTestControlGc::Draw(const TRect& /*aRect*/) const
    {
    if(iSupressOutput)
    	return;
    
    CWindowGc& gc=SystemGc();

	TRect rc = Rect();
	gc.Clear(rc);
	
    gc.SetPenColor(iPenColor);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.SetBrushColor(iBrushColor);
    
    rc.Shrink(1,1);
    gc.DrawRect(rc);
    rc.Shrink(1,1);
    gc.DrawRect(rc);
	
    }
/**
  Handler for pointer events received by the control.\n
  Gets a pointer to the Application Ui Object.\n
  Later checks if the events are handled by the expected controls.\n 
*/
void CTestControlGc::HandlePointerEventL(const TPointerEvent& )
	{
	User::InfoPrint(iControlName);
	
	CTConeTransitionAppUi* theAppUi = static_cast<CTConeTransitionAppUi*> ((CCoeEnv::Static())->AppUi());
	theAppUi->INFO_PRINTF2(_L("HandlePointerEventL, %S"), &iControlName);
	theAppUi->TEST(iControlName.Compare(theAppUi->iExpectedControlName) == 0);
	theAppUi->iExpectedControlName = _L("");
	}


/**
  Destructor for CTestControlGcTriangle Class.\n
*/
CTestControlGcTriangle::~CTestControlGcTriangle()
	{
	if(iPoints)
		{
		iPoints->Reset();
		delete iPoints;
		}
	}
	
/** Construct triangle control.

	@param TPoint aPt Left top position of control
	@param TSize aSize The size of the control, in pixels.
	@param TRgb aPenColor An RGB colour for the pen
	@param TRgb An RGB colour for the brush
	@param const TDesC &aControlName Control name
*/
void CTestControlGcTriangle::ConstructL(TPoint aPt, TSize aSize, TBool aTop, 
			TRgb aPenColor, TRgb aBrushColor, const TDesC &aControlName)
	{
	CTestControlGc::ConstructL(aPt, aSize, aPenColor, aBrushColor, aControlName);
	TRect rc = Rect();
	
	iPoints = new (ELeave) CArrayFixFlat<TPoint>(3);
	if(aTop)
		{
		iPoints->AppendL(TPoint(rc.iBr.iX, rc.iBr.iY));		
		iPoints->AppendL(TPoint(rc.iBr.iX, rc.iTl.iY));		
		iPoints->AppendL(TPoint(rc.iTl.iX, rc.iTl.iY));		
		}
	else
		{
		iPoints->AppendL(TPoint(rc.iTl.iX, rc.iTl.iY));		
		iPoints->AppendL(TPoint(rc.iTl.iX, rc.iBr.iY));		
		iPoints->AppendL(TPoint(rc.iBr.iX, rc.iBr.iY));		
		}
	SetHitTest(this);	
	}
/**
  Draw function for the CTestControlGcTriangle Class.\n 
  Checks if output to the control is supressed.\n
  If not, obtains a pointer to the Graphics context.\n
  Sets the pen and brush settings and draws using DrawPolygon.\n
*/
void CTestControlGcTriangle::Draw(const TRect& /*aRect*/) const
    {
    if(iSupressOutput)
    	return;
   
    CWindowGc& gc=SystemGc();
	TRect rc = Rect();

    gc.SetPenColor(iPenColor);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.SetBrushColor(iBrushColor);
 	
 	gc.DrawPolygon(iPoints);
    }

/** Overridden function, defined in MCoeControlHitTest as pure virtual

@param const TPoint& aPoint Point coordinate in pixel
@param const CCoeControl& aControl reference to a control
*/    
TBool CTestControlGcTriangle::HitRegionContains(const TPoint& aPoint, const CCoeControl& aControl) const
	{
	TBool theIsInside = IsInside(aPoint);
	CTConeTransitionAppUi* theAppUi = static_cast<CTConeTransitionAppUi*> ((CCoeEnv::Static())->AppUi());
	theAppUi->INFO_PRINTF2(_L("HitRegionContains function for %S has been called"), &iControlName);
	if(theIsInside)
		{
		theAppUi->TEST(this == &aControl);
		theAppUi->TEST(theAppUi->iExpectedControlName == iControlName);
		theAppUi->INFO_PRINTF2(_L("The region has been dectected as inside control %S"), &iControlName);
		return ETrue;
		}
	
	return EFalse;
	}

/** 
  Check if point is inside a triangle
*/
TBool CTestControlGcTriangle::IsInside(const TPoint& pt) const
  {
  TReal b0, b1, b2, b3;
    // first check bounding box
  TRect rc = Rect();  
  if(rc.Contains(pt)) 
  	{
      // if inside, check triangle
    b0 =  ((*iPoints)[1].iX - (*iPoints)[0].iX) * ((*iPoints)[2].iY - (*iPoints)[0].iY) - 
    			((*iPoints)[2].iX - (*iPoints)[0].iX) * ((*iPoints)[1].iY - (*iPoints)[0].iY);
    b1 = (((*iPoints)[1].iX - pt.iX) * ((*iPoints)[2].iY - pt.iY) - ((*iPoints)[2].iX - pt.iX) * ((*iPoints)[1].iY - pt.iY)) / (TReal)b0;
    b2 = (((*iPoints)[2].iX - pt.iX) * ((*iPoints)[0].iY - pt.iY) - ((*iPoints)[0].iX - pt.iX) * ((*iPoints)[2].iY - pt.iY)) / (TReal)b0;
    b3 = (((*iPoints)[0].iX - pt.iX) * ((*iPoints)[1].iY - pt.iY) - ((*iPoints)[1].iX - pt.iX) * ((*iPoints)[0].iY - pt.iY)) / (TReal)b0;

    if((b1 > 0) && (b2 > 0) && (b3 > 0)) 
    	{
        return ETrue;
    	} 
    else 
    	{
        return EFalse;
    	}
    } 
    return EFalse;
  }
   

/**
  Second phase constructor for CTestControlBackground object.\n
  Creates  has 3 component controls.\n
  Creates a fourth control with a bitmap object.\n
  Gets a pointer to Screen Device and creates a bitmapped graphics context.\n
  A mapping is created between the screen device and bitmapped Gc using CWindowToBitMappingGc.\n
  This mapping is used to convert the drawing to bitmap onto the screen.\n
  A Fbs Bitmap is created which is used to draw the background of the component controls.\n
*/
void CTestControlBackground::ConstructL()
    {
    CreateWindowL();
    SetExtent(TPoint(20,20),TSize(600,200));
    
    iControl = new (ELeave) CTestControlGc();
    iControl ->ConstructL(TPoint(10,10),TSize(60,40), KRgbBlue, KRgbMagenta, _L("Control 1")); 

	//top triangle
    iControl2 = new (ELeave) CTestControlGcTriangle();
    iControl2 ->ConstructL(TPoint(10,70),TSize(60,40), ETrue, KRgbBlue, KRgbRed, _L("Control 2")); 
	
	//bottom triangle
    iControl3 = new (ELeave) CTestControlGcTriangle();
    iControl3 ->ConstructL(TPoint(10,70),TSize(60,40), EFalse, KRgbBlue, KRgbYellow, _L("Control 3")); 

    iControlImage = new (ELeave) CTestControlImageGc();
    iControlImage ->ConstructL(TPoint(250,40),TSize(60,40), KRgbWhite, KRgbWhite, _L("Background Control")); 
    
    CWsScreenDevice* screenDevice=CCoeEnv::Static()->ScreenDevice();
    TDisplayMode dispMode = screenDevice -> DisplayMode();


	iMainFbsBitGc=CFbsBitGc::NewL();	// for the main bitmap
	const CCoeEnv* env = CCoeEnv::Static();

    iBitmapView = new (ELeave) CWsBitmap(env->WsSession());
    User::LeaveIfError(iBitmapView->Create(TSize(300,150), dispMode));
	
	iBitmapDevice2 = CFbsBitmapDevice::NewL(iBitmapView);
    
	iGraphContext = CWindowToBitmapMappingGc::NewL(*screenDevice,*iMainFbsBitGc);	// takes place of iMainFbsBitGc (not passing ownership of context here !)

	iMainFbsBitGc->Activate(iBitmapDevice2);
	iControlImage->SetBitmap(iBitmapView);
    
    iBmpBackground = new (ELeave) CFbsBitmap();
    User::LeaveIfError(iBmpBackground->Load(_L("z:\\conetest\\city.mbm")));
    
    ActivateL();
    }
/**
  Returns the number of component controls contained by iViewControl object.\n
  
  @return 4.\n
 
*/
TInt CTestControlBackground::CountComponentControls() const
	{
	return 4;
	}
/**
  Returns the component control at the index aIndex.\n
  
  @return CCoeControl*, the component control pointer at index aIndex.\n
*/	
CCoeControl* CTestControlBackground::ComponentControl(TInt aIndex) const
	{
	if(aIndex == 0)
		return iControl;
	if(aIndex == 1)
		return iControl2;
	if(aIndex == 2)
		return iControl3;
	else if(aIndex == 3)
		return iControlImage;
	return NULL;
	}

/**
  Destructor for CTestControlBackground Class.\n 
  Destroys the component controls and all other member objects.\n
*/
CTestControlBackground::~CTestControlBackground()
    {
    delete iControl;
    delete iControlImage;
    delete iControl2;
    delete iControl3;
    delete iGraphContext;
    delete iMainFbsBitGc;
    
    delete iBitmapDevice2;
    delete iBitmapView;
    delete iBmpBackground; 
    }
/**
  This function is called whenever a control gains or loses focus,
  as a result of a call to SetFocus().\n
  A typical use of FocusChanged() is to change the appearance of the control to 
  indicate whether or not it has focus, for example by drawing a focus rectangle around it.\n
 
*/
void CTestControlBackground::FocusChanged(TDrawNow aDrawNow)
	{
    if (aDrawNow)
        {
        ActivateGc();
        DrawBorder();
        DeactivateGc();
        }
    }
/**
  Draws the border for the control.\n
  Gets a pointer to Graphic context and sets the pen colour depending
  on whether the control is in focus or not.\n
  Draws a border using DrawRect function of the graphic context.\n
*/
void CTestControlBackground::DrawBorder() const
    {
    CWindowGc& gc=SystemGc();
    TRect rect=Rect();

    gc.DrawRect(rect);
    
    if (!IsFocused())
        gc.SetPenColor(KRgbWhite);
    rect.Shrink(1,1);
    gc.DrawRect(rect);
    rect.Shrink(1,1);
    gc.DrawRect(rect);
	}

/**
  Draw a control, called by window server.\n
  This function is used for window server-initiated redrawing of controls, 
  and for some application-initiated drawing.\n
  It should be implemented by each control, but is only called from within 
  CCoeControl's member functions, and not from the derived class.\n
*/
void CTestControlBackground::Draw(const TRect& /*aRect*/) const
    {
    CWindowGc& gc=SystemGc();
	TRect rc = Rect();
	gc.SetBrushColor(KRgbWhite);
	gc.Clear(rc);
	DrawBorder();
    }

/** 
  The function replaces Gc from standard window Gc to offscreen bitmap.\n
  Sets Object of type CWindowToBitmapMappingGc as the Graphic Context.\n
 
  @return Error code, KErrNone if no error.\n
*/
TInt CTestControlBackground::SetChildGc()
	{
	TInt theError = KErrNone;
	if(iControl && iGraphContext)
		{
    	theError = iControl->SetGc(iGraphContext);
		}
	return theError;	
	}
/** 
 Restores standard window Gc.\n
*/
void CTestControlBackground::RestoreChildGc()
	{
	if(iControl)
		{
    	iControl->SetGc(NULL);
		}
	}
/**
  Draw function for the CTestControlBackground class.\n
  The function draws to the screen by using bitmap block transfer.\n
*/
void CTestControlBackground::Draw(CWindowGc& aGc, const CCoeControl& /*aControl*/, const TRect& aRect) const
	{
	TPoint pt = aRect.iTl;

	pt = pt - TPoint(5,5);
	TRect rc = TRect(iBmpBackground->SizeInPixels());
	rc.SetHeight(100);
	aGc.BitBlt(pt, iBmpBackground, rc);
	} 
	   
/** 
  Draw white rectangle to offscreen bitmap 
*/
void CTestControlBackground::ClearOffScreenBitmap()
	{
	iGraphContext->Clear();
	TSize sz = iBitmapView->SizeInPixels();
	
	iGraphContext->SetPenColor(KRgbWhite);
    iGraphContext->SetBrushColor(KRgbWhite);
    TRect rc = TRect(0, 0, sz.iWidth, sz.iHeight);
	iGraphContext->DrawRect(rc);
	}
/**
  The function sets the iControl as the parent of the control iControl2.\n
*/
void CTestControlBackground::SetControlParent()
	{
	if(iControl && iControl2)
		iControl2->SetParent(iControl);
	}

/** 
  Supress/resume output for a given control.\n
*/
void CTestControlBackground::SupressOutput(TInt aNumControl, TBool aSupress)
	{
	switch(aNumControl)
		{
			case 0:
			if(iControl)
				iControl->SupressOutput(aSupress); 
			break;	
			case 1:
			if(iControl2)
				iControl2->SupressOutput(aSupress); 
			break;
			case 2:
			if(iControl3)
				iControl3->SupressOutput(aSupress); 
			break;
			default : break;	
		}
	}

/**
  @SYMTestCaseID UIF-TConeTransition-GeneratePointerEventsOnControl1L
 
  @SYMPREQ
 
  @SYMTestCaseDesc Generates pointer events for Control 1 and later verifies if they
  are handled by the handlers of Control2.\n
 
  @SYMTestPriority High
 
  @SYMTestStatus Implemented
  
  @SYMTestActions : Send pointer event to control 1.\n
 
  @SYMTestExpectedResults : Control1 should handle the generated pointer events.\n
 
  @SYMTestType : CIT 
*/
void CTestControlBackground::GeneratePointerEventsOnControl1L()
	{
	TRect rc = iControl->Rect();
	
	CTConeTransitionAppUi* theAppUi = static_cast<CTConeTransitionAppUi*> ((CCoeEnv::Static())->AppUi());
	theAppUi->iExpectedControlName = iControl->iControlName;
	TPointerEvent thePointer;
	thePointer.iType=TPointerEvent::EButton1Down;
	thePointer.iModifiers = 0;
	thePointer.iPosition=rc.iTl + TPoint(2, 2);
	HandlePointerEventL(thePointer);
	}
/**
  @SYMTestCaseID UIF-TConeTransition-GeneratePointerEventsOnControl2L
 
  @SYMPREQ
 
  @SYMTestCaseDesc Generates pointer events for Control 2 and later verifies if they
  are handled by the handlers of Control2.\n
 
  @SYMTestPriority High
 
  @SYMTestStatus Implemented
  
  @SYMTestActions : Send pointer event to control 2.\n
  The control has unique triangle hit region but occupied an area 
  exactly the same as control3.\n
  
  @SYMTestExpectedResults : Control2 should handle the generated pointer events.\n
 
  @SYMTestType : CIT 
*/	
void CTestControlBackground::GeneratePointerEventsOnControl2L()
	{
	TRect rc2 = iControl2->Rect();
	CTConeTransitionAppUi* theAppUi = static_cast<CTConeTransitionAppUi*> ((CCoeEnv::Static())->AppUi());
	theAppUi->iExpectedControlName = iControl2->iControlName;

	
	TPointerEvent thePointer;
	thePointer.iType=TPointerEvent::EButton1Down;
	thePointer.iModifiers = 0;
	
	
	thePointer.iPosition=TPoint(rc2.iBr.iX - 2, rc2.iTl.iY + 2);
	HandlePointerEventL(thePointer);
	}

/**
  @SYMTestCaseID UIF-TConeTransition-GeneratePointerEventsOnControl3L
 
  @SYMPREQ
 
  @SYMTestCaseDesc Generates pointer events for Control 3 and later verifies if they
  are handled by the handlers of Control3.\n
 
  @SYMTestPriority High
 
  @SYMTestStatus Implemented
  
  @SYMTestActions : Send pointer event to control 3.\n
  The control has unique triangle hit region but occupied an area 
  exactly the same as control3.\n
  
  @SYMTestExpectedResults : Control3 should handle the generated pointer events.\n
 
  @SYMTestType : CIT 
*/
void CTestControlBackground::GeneratePointerEventsOnControl3L()
	{
	TRect rc2 = iControl3->Rect();
	CTConeTransitionAppUi* theAppUi = static_cast<CTConeTransitionAppUi*> ((CCoeEnv::Static())->AppUi());
	theAppUi->iExpectedControlName = iControl3->iControlName;
	
	TPointerEvent thePointer;
	thePointer.iType=TPointerEvent::EButton1Down;
	thePointer.iModifiers = 0;
	
	thePointer.iPosition=TPoint(rc2.iTl.iX + 2, rc2.iBr.iY - 2);
	HandlePointerEventL(thePointer);
	}
/**
  @SYMTestCaseID UIF-TConeTransition-OffScreenDrawing
 
  @SYMPREQ
 
  @SYMTestCaseDesc Test drawing on a bitmap instead of directly on the screen.\n
 
  @SYMTestPriority High
 
  @SYMTestStatus Implemented
  
  @SYMTestActions : CTestControlBackground object is set as the background drawing object
  for control 2 and 3.\n
  The backgrounds of these controls is drawn by the parent control on invalidation.\n
  The foreground is drawn by the iGraphContext using Fbs BitMap.\n
  
  @SYMTestExpectedResults : The drawing should be successful..\n
 
  @SYMTestType : CIT 
*/	
TInt CTestControlBackground::OffScreenDrawing()
	{
	if(!iControl2 || !iControl3 || !iGraphContext)
		return KErrBadHandle;
	
	iControl2->SetBackground(this);
	iControl3->SetBackground(this);
	ActivateGc();
	
	TRect rect = Rect();
	Window().Invalidate(rect);
	Window().BeginRedraw(rect);

	Draw(rect);
	iControl2->DrawBackground(iControl2->Rect());
	iControl3->DrawBackground(iControl3->Rect());
	

   	TInt theError = iControl2->SetGc(iGraphContext);
	if(theError != KErrNone)
		return theError;
		
   	theError = iControl3->SetGc(iGraphContext);
	if(theError != KErrNone)
		{
		iControl2->SetGc(NULL);
		return theError;
		}

	//it should draw to offscreen bitmap
	iControl2->DrawForeground(iControl2->Rect());
	iControl3->DrawForeground(iControl3->Rect());
	
	//output offscreen bitmap for visual check
	iControlImage->Draw(rect);
	
	Window().EndRedraw();
	DeactivateGc();

	return theError;
	}
/**
  @SYMTestCaseID UIF-TConeTransition-DirectScreenDrawing
 
  @SYMPREQ
 
  @SYMTestCaseDesc Test drawing directly on the screen.\n
 
  @SYMTestPriority High
 
  @SYMTestStatus Implemented
  
  @SYMTestActions : Background and Foreground drawing directly to screen Gc.\n
  CTestControlBackground object is set as the background drawer.\n
  Drawing for background and foreground is done separately for each component control.\n
  
  @SYMTestExpectedResults : The drawing should be successful.\n
 
  @SYMTestType : CIT 
*/	
TInt CTestControlBackground::DirectScreenDrawing()
	{
	if(!iControl2 || !iControl3 || !iGraphContext)
		return KErrBadHandle;
	
	iControl2->SetGc(NULL);
	iControl3->SetGc(NULL);
	ClearOffScreenBitmap();
	
	ActivateGc();
	
	TRect rect = Rect();

	Window().Invalidate(rect);
	Window().BeginRedraw(rect);

	Draw(rect);
	iControl2->DrawBackground(iControl2->Rect());
	iControl3->DrawBackground(iControl3->Rect());

	//draw directly to screen
	iControl2->DrawForeground(iControl2->Rect());
	iControl3->DrawForeground(iControl3->Rect());

	iControlImage->Draw(rect);

	Window().EndRedraw();
	DeactivateGc();
	
	return KErrNone;
	}

/**
  Draw function for the CTestControlImageGc Class.\n
  
*/
void CTestControlImageGc::Draw(const TRect& /*aRect*/) const
	{
    CWindowGc& gc=SystemGc();

	TRect rc = Rect();
	gc.Clear(rc);
	if(iBmp)
    	gc.BitBlt(rc.iTl, iBmp);
		
	}

/**
  Constructor for CTConeTransitionAppUi class.\n
*/
CTConeTransitionAppUi::CTConeTransitionAppUi(CTmsTestStep* aStep) :
CTestCoeAppUi(aStep)
{}
/**
  Destructor for the CTConeTransitionAppUi class.\n
  Removes the Control from the control stack.\n
*/
CTConeTransitionAppUi::~CTConeTransitionAppUi()
	{
	RemoveFromStack(iViewControl);
	delete iViewControl;
	}

/**
  Second phase constructor for CTConeTransitionAppUi Class.\n
  Instantiates a container control of type CTestControlBackground.\n
  Starts the automated execution of test cases using test manager.\n
*/
void CTConeTransitionAppUi::ConstructL()
	{
	CTestCoeAppUi::ConstructL();
	
    iViewControl=new(ELeave) CTestControlBackground;
    iViewControl->ConstructL();
    AddToStackL(iViewControl);

	AutoTestManager().StartAutoTest();
	}

/**
  Handler for Key Events received by the TConeTransition application.\n
  Exits the application after receiving Ctrl + E.\n
  @return TKeyRespone, indicating whether key event is handled or not.\n
*/	
TKeyResponse CTConeTransitionAppUi::HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
	TKeyResponse ret=EKeyWasNotConsumed;
    if (aType==EEventKey && aKeyEvent.iCode==CTRL('e'))
		{
		CBaActiveScheduler::Exit();
		ret=EKeyWasConsumed;
		}
	return ret;
    }
/**
   Auxiliary Function for all Test Cases.\n
  
   The method is an override from CTestCoeAppUi. \n
   This function is called asynchronously by RunL function of the
   AutotestManager after previous test case is executed.\n
   Tests the following scenarios one by one.\n
   1. Force the control 1 to use off screen bitmap, instead of screen.\n
   2.Force the control 1 to use off screen bitmap, instead of screen.\n
   3.Resume using of screen Gc for control 1.\n
   4.Set Control 1 as parent for control 2.\n
   5.Supress output for control 2.\n
   6.Restore output for controls and remove off screen bitmat from control1.\n
   7.Trying to generate pointer event on control 1.\n
   8.Trying to generate pointer event on control 2.\n
   9.Generate pointer event on control 3.\n
   10.Separate Drawing of foreground and background, offscreen version.\n
   11.Separate Drawing of foreground and background, direct screen version.\n
   
 */
void CTConeTransitionAppUi::RunTestStepL(TInt aStepNum)
	{

	User::After(TTimeIntervalMicroSeconds32(1000000 * 2));
	switch(aStepNum)
		{
		case 1: 
		//inserted to increase delay before a first test case for a 
		//visual check of initial output
		INFO_PRINTF1(_L("Start all test cases"));
		break;
		case 2:
		INFO_PRINTF1(_L("Force the control 1 to use off screen bitmap, instead of screen"));
		TEST(iViewControl->SetChildGc() == KErrNone);
		iViewControl->DrawNow();
		break;
		case 3:
		INFO_PRINTF1(_L("Resume using of screen Gc for control 1"));
		iViewControl->RestoreChildGc();
		iViewControl->ClearOffScreenBitmap();
		iViewControl->DrawNow();
		break;
		case 4:
		INFO_PRINTF1(_L("Set Control 1 as parent for control 2"));
		TEST(iViewControl->SetChildGc() == KErrNone);
		iViewControl->SetControlParent();
		iViewControl->SupressOutput(0, ETrue);
		iViewControl->SupressOutput(1, EFalse);
		iViewControl->ClearOffScreenBitmap();
		iViewControl->DrawNow();
		break;
		case 5:
		INFO_PRINTF1(_L("Supress output for control 2"));
		iViewControl->SupressOutput(1, ETrue);
		iViewControl->SupressOutput(0, EFalse);
		iViewControl->ClearOffScreenBitmap();
		iViewControl->DrawNow();
		break;
		case 6:
		INFO_PRINTF1(_L("Restore output for controls and remove off screen bitmat from control1"));
		iViewControl->SupressOutput(1, EFalse);
		iViewControl->SupressOutput(0, EFalse);
		iViewControl->RestoreChildGc();
		iViewControl->ClearOffScreenBitmap();
		iViewControl->DrawNow();
		break;
		case 7:
		{
		SetTestStepID(_L("UIF-TConeTransition-GeneratePointerEventsOnControl1L"));		
		INFO_PRINTF1(_L("Trying to generate pointer event on control 1"));
		TRAPD(ret, iViewControl->GeneratePointerEventsOnControl1L());
		TEST(ret==KErrNone);
		RecordTestResultL();		
		}
		break;
		case 8:
		{
		SetTestStepID(_L("UIF-TConeTransition-GeneratePointerEventsOnControl2L"));		
		INFO_PRINTF1(_L("Trying to generate pointer event on control 2"));
		TRAPD(ret, iViewControl->GeneratePointerEventsOnControl2L());
		TEST(ret==KErrNone);
		RecordTestResultL();		
		}
		break;
		case 9:
		{
		SetTestStepID(_L("UIF-TConeTransition-GeneratePointerEventsOnControl3L"));		
		INFO_PRINTF1(_L("Trying to generate pointer event on control 3"));
		TRAPD(ret, iViewControl->GeneratePointerEventsOnControl3L());
		TEST(ret==KErrNone);
		RecordTestResultL();
		}
		break;
		case 10:
		SetTestStepID(_L("UIF-TConeTransition-OffScreenDrawing"));			
		INFO_PRINTF1(_L("Separate Drawing of foreground and background, offscreen version"));
		TEST(iViewControl->OffScreenDrawing() == KErrNone);
		RecordTestResultL();		
		break;
		case 11: 
		SetTestStepID(_L("UIF-TConeTransition-DirectScreenDrawing"));			
		INFO_PRINTF1(_L("Separate Drawing of foreground and background, direct screen version"));
		TEST(iViewControl->DirectScreenDrawing() == KErrNone);
		RecordTestResultL();	
		CloseTMSGraphicsStep();
		break;
		case 12:
			AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
		break;

		}
		
	}


/**
  Completes the construction of the Control Environment(CCoeEnv object).\n
  Instantiates the CTConeTransitionAppUi class which serves as a AppUi class.\n
  Sets the CTConeTransitionAppUi object as the application's user interface object.\n
  Invokes the second phase constructor of the application's UI.\n
*/
void CTConeTransitionStep::ConstructAppL(CCoeEnv* aCoe)
	{ // runs inside a TRAP harness
	aCoe->ConstructL();
	CTConeTransitionAppUi* appUi= new (ELeave) CTConeTransitionAppUi(this);
	aCoe->SetAppUi(appUi);
	appUi->ConstructL();
	}
/**
  Constructor for CTConeTransition Step class.\n
  Sets the test step name.\n
*/
CTConeTransitionStep::CTConeTransitionStep()
	{
	SetTestStepName(KTConeTransitionStep);
	}
/**
  Destructor for CTConeTransition class.\n
*/
CTConeTransitionStep::~CTConeTransitionStep()
{}

/**
  Entry function for CTConeTransition Test Step.\n
  Sets up the control environment.\n
  Constructs and Launches the CTConeTransition Test application.\n
*/
TVerdict CTConeTransitionStep::doTestStepL() // main function called by E32
	{
	INFO_PRINTF1(_L("Test Started"));
	
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

	INFO_PRINTF1(_L("Test Finished"));
	return TestStepResult();
	}




