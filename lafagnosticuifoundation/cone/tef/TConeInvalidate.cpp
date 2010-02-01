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
// Off-screen bitmap Gc test to observe correct redraw behaviour with respect to sub-rect invalidation and redraw capability
// makes use of the introduced CCoeControl::DrawNow(TRect &) function and CWindowGc derivable class.
// Test intended for OS v9.1 and onward.
// The screen display, from left to right is displayed as follows:
// a) The standard control as a sub-divided hierachical component with background
// b) Offscreen bitmap #1 overlayed (blended) onto background
// c) Offscreen bitmap #2 overlayed (blended) onto background
// The original control is set into the offscreen Gcs as a chequer board where "black squares" are drawn to Gc #1 and 
// "white squares" are drawn to Gc #2.
// Note: During the test a blank rectangle is displayed in the DrawNow(TRect&) position on the original control,
// this is the windows server screen invalidate and cannot be overridden by test code. 
// Specifically this code performs the following tests:
// 1) Rectangle refresh drawing down a hierarchical composition of child controls with varied window ownership properties 
// (including background redraw). This is to ensure the integrity of the subrect as the draw code passes down through the 
// control hierarchy.
// 2) Offscreen drawing to multiple Gcs with respect to test 1); the offscreen Gc uses RDrawableWindow::GetDrawRect to 
// obtain current window the draw region. See TTransGC.cpp for offscreen bitmap Gc functionality.
// 3) The correct drawing of background regions with respect to each window, the behaviour of which is in part specified by 
// the Draw client
// The chequer pattern will be drawn within the DRAW_SIZE region on the second two controls (offscreen Gc maps). 
// Note: the second half of the tests will show "black" square regions because each square is a true window owner.
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code 
 @SYMTestCaseID App-Framework/Cone/TConeInvalidate
 @SYMPREQ 915
 @SYMTestCaseDesc
 @SYMTestPriority Medium
 @SYMTestStatus Implemented
 @SYMTestActions 
 @SYMTestExpectedResults
*/

#include <coeaui.h>
#include <coemain.h>
#include <coedef.h>
#include <coesndpy.h>
#include <basched.h>
#include <bassnd.h>
#include <coeccntx.h>
#include <ecom/ecom.h>
#include "TConeInvalidate.h"
#include "TTransGc.h"

//Variable to offset animation start frames
#define KNumAnimFrames 32
#define KNumTestSteps  16
#define KAlphaOpaque   255
TInt g_FrameStart = 0;

//Every background will use the same image
CFbsBitmap* CTestRectGc::iBmpBackground = 0;

/** The COffScreenBitmapGc class handles all variables and functions to maintain an offscreen bitmap for drawing
    in 16M alpha mode. */
COffScreenBitmapGc::COffScreenBitmapGc()
	{
		
	}

COffScreenBitmapGc::~COffScreenBitmapGc()
	{
    delete iGraphContext;
    delete iMainFbsBitGc;    
    delete iBitmapDevice2;
    delete iBitmapView;	
	}

COffScreenBitmapGc* COffScreenBitmapGc::NewL(const TSize &aSize)
	{
	COffScreenBitmapGc *pGC;
	
	pGC = new (ELeave) COffScreenBitmapGc();
	
	const CCoeEnv* env = CCoeEnv::Static();

	
    CWsScreenDevice* screenDevice=env->ScreenDevice();
    
    TDisplayMode dispMode = screenDevice->DisplayMode();
    
    //Override display mode so that we have an alpha channel in the target bitmap;
    dispMode = EColor16MA;
  
	//Allocate windows server bitmap
    pGC->iBitmapView = new (ELeave) CWsBitmap(env->WsSession());
  
    User::LeaveIfError(pGC->iBitmapView->Create(aSize, dispMode));
	
	//Create a device for the bitmap
	pGC->iBitmapDevice2 = CFbsBitmapDevice::NewL(pGC->iBitmapView);
	
	//Graphic Context to draw to 
	pGC->iMainFbsBitGc=CFbsBitGc::NewL();	
	pGC->iMainFbsBitGc->Activate(pGC->iBitmapDevice2);
	    
	pGC->iGraphContext = CTransGc::NewL(*screenDevice,*pGC->iMainFbsBitGc);	// takes place of iMainFbsBitGc (not passing ownership of context here !)
	
	return pGC;
	}

CTransGc *COffScreenBitmapGc::OffScreenGc()
	{
	return iGraphContext;
	}
 
  
CWsBitmap *COffScreenBitmapGc::GetBitmap()
	{
	return iBitmapView;
	}

//-----------------------------------------------------
void CTestRectGc::ConstructL(TPoint aPt, TSize aSize, TRgb aPenColor, TRgb aBrushColor, CGraphicsContext::TBrushStyle aBrushStyle)
    {    
    SetPenColor(aPenColor);
    SetBrushColor(aBrushColor);
    
    SetBrushStyle(aBrushStyle);
    SetDrawType(EDrawRect);
    SetExtent(aPt, aSize);
   
   	iFrameNo = g_FrameStart+=5; //Offset frame start for next control
   	g_FrameStart %= KNumAnimFrames;			
   }



CTestRectGc::~CTestRectGc()
    {
    }


//Basic colour setting functions
void CTestRectGc::SetPenColor(const TRgb &aPenColor)
    {
    	iPenColor = aPenColor;
    }
void CTestRectGc::SetBrushColor(const TRgb &aBrushColor)
    {
    	iBrushColor = aBrushColor;
    }
void CTestRectGc::SetBrushStyle(const CGraphicsContext::TBrushStyle aBrushStyle)
    {
    	iBrushStyle = aBrushStyle;
    }
void CTestRectGc::SetDrawType(const TDrawType DrawType)
    {
    	iDrawType = DrawType;
    }
void CTestRectGc::NextFrame() 
	{		
		iFrameNo = (iFrameNo+1) & 0x1f; 				
	}
		
//Main control drawing function		
void CTestRectGc::Draw(const TRect& aRect) const
    {
    
    CWindowGc& gc=SystemGc();

	TRect rc = Rect();

	gc.SetClippingRect(aRect);	
    
	switch(iDrawType)
		{
		case EDrawRect:		
		
		  	gc.SetPenColor(TRgb(0,0,0,KAlphaOpaque));
		    gc.SetBrushColor(TRgb(0,0,0,KAlphaOpaque));
			gc.SetBrushStyle(CGraphicsContext::ENullBrush);
			gc.DrawRect(rc); 			
			break;    
		
		case EDrawEllipse:		
			{
					
			//Frame index is a ping-pong animation 0->15->0
			TInt FrameIndex = (iFrameNo&0x10)? 0xf - (iFrameNo & 0xf) : iFrameNo & 0xf;
			
			//The shade of red is an offset multiple of the frame number (0-NUM_ANIM_FRAMES-1).
			TRgb col(0xff&(128+(iFrameNo<<3)), 0, 0);		    	
			
			//The size of the ellipse ranges from 0->height->0 over the NUM_ANIM_FRAMES period
			TInt BoxSize = (FrameIndex * ((rc.Height() << 15) / 0x10)) >> 16;
			rc.Shrink(0, BoxSize);

		  	gc.SetPenColor(col);
		    gc.SetBrushColor(col);
			gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
			
			gc.DrawEllipse(rc);  
			break;
			}		
		default: 			
		
			break;	//Do nothing, blank but not erased
		}

	gc.CancelClippingRect();		    			
	
    }


//Background drawing function
void CTestRectGc::Draw(CWindowGc& aGc, const CCoeControl& aControl, const TRect& aRect) const
	{		
		if (iBmpBackground) 
		{
						
			TPoint a = PositionRelativeToScreen();
			TPoint b = aControl.PositionRelativeToScreen();

			//The source rect of the background is the relationship between this control and the control being drawn (child)
			//plus the subrect (aRect) to be drawn.
			TRect SourceRect(b-a+aRect.iTl, aRect.Size());

			aGc.SetDrawMode(CGraphicsContext::EDrawModePEN);
			aGc.BitBlt(aRect.iTl, iBmpBackground, SourceRect);			
			aGc.SetDrawMode(CGraphicsContext::EDrawModePEN);
		}
		else
		{
			TRect rc;
			aGc.SetClippingRect(aRect);
			aGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    		aGc.SetBrushColor(iBrushColor);
    		aGc.SetBrushStyle(iBrushStyle);
			aGc.DrawRect(rc);
			aGc.CancelClippingRect();

		}		
	}
		   
/** Create a child control.
    if the LSB of aOwners is true, then this control is window owning.
    Recursively called aChildren times  */

void CComponentControl::CreateChildControlL(TInt aChildren, TInt aOwners, TPoint aPt, TSize aSize, TRgb aPenColor, TRgb aBrushColor, CGraphicsContext::TBrushStyle aBrushStyle)
	{
	    	CTestRectGc *pControl;
	    	
	    	if (aChildren)
		    	{
				pControl = new (ELeave) CComponentControl();
		    	}    		
	    	else
		    	{
				pControl = new (ELeave) CTestRectGc();    
		    	}
		    		    			    				
			if (aOwners&1)
				{			
				pControl->CreateWindowL(this);	
				}
			else
				{
				pControl->SetContainerWindowL(*this);
				pControl->SetParent(this);	  	
				}

			if (aChildren)
		    	{
	    		((CComponentControl*)pControl)->ConstructL(aChildren-1, aOwners, aPt, aSize, KRgbBlack, KRgbRed, CGraphicsContext::ESolidBrush);     		
		    	}    		
	    	else
		    	{
				pControl->ConstructL(aPt, aSize, aPenColor, aBrushColor, aBrushStyle);				
		    	}
	    	
	    	Components().AppendLC(pControl);
				
		  	pControl->SetDrawType(EDrawEllipse);				
		  		   			
			CleanupStack::Pop(pControl);    					
	}

/**  Construct a control which is recursively sub-divided into four more windows.
     If the LSB of aOwners is true, then the parent control (this) is a window owning control
     Recursively called aChildren times */

void CComponentControl::ConstructL(TInt aChildren, TInt aOwners, TPoint aPt, TSize aSize, TRgb aPenColor, TRgb aBrushColor, CGraphicsContext::TBrushStyle aBrushStyle)
    {
    	//Construct the base window of the control
    	CTestRectGc::ConstructL(aPt, aSize, aPenColor, aBrushColor, aBrushStyle);
    	InitComponentArrayL();

		TSize ChildSize(aSize.iWidth/2, aSize.iHeight/2);
		
		TPoint Offset;
		if (aOwners&1)
			Offset.SetXY(0,0);
		else
			Offset = aPt;
			
		CreateChildControlL(aChildren, aOwners>>1, Offset, ChildSize, aPenColor, aBrushColor, aBrushStyle);
		CreateChildControlL(aChildren, aOwners>>1, Offset+TSize(ChildSize.iWidth, 0), ChildSize, aPenColor, aBrushColor, aBrushStyle);
		CreateChildControlL(aChildren, aOwners>>1, Offset+TSize(0, ChildSize.iHeight), ChildSize, aPenColor, aBrushColor, aBrushStyle);
		CreateChildControlL(aChildren, aOwners>>1, Offset+TSize(ChildSize.iWidth, ChildSize.iHeight), ChildSize, aPenColor, aBrushColor, aBrushStyle);
		    		  		  	  		  	  	
    }
    
//Destroy component controls within this control
CComponentControl::~CComponentControl()
    {
    	while (CountComponentControls())
    	{
    		CCoeControl *pControl;
    		pControl = ComponentControl(0);    		
    		Components().Remove(pControl);  
    		delete pControl;  		
    	}    	
    }
    
 void CComponentControl::Draw(const TRect& /*aRect*/) const
	 {
	// 	CTestRectGc::Draw(aRect);
	 	return;
	 }

//Recursively drill down to each control level and step their frame counters.
void CComponentControl::AnimateComponents()
	{
	for (TInt i=0; i<CountComponentControls(); i++)
		{
			CTestRectGc* pComponent = (CTestRectGc*)ComponentControl(i);
			pComponent->NextFrame();	
			if (pComponent->CountComponentControls())				
				((CComponentControl*)pComponent)->AnimateComponents();
		}
	}

/** Create the compound control, the owner mask defines window ownership for each hierarchical control level
    (LSB = top level parent window). */
void CTestRectBackground::CreateComponentControlL(TInt aNumChildren, TInt aOwnerMask)
{
	Components().RemoveById(999);
	delete iControl;
	
 	iControl = new (ELeave) CComponentControl();
	iControl->CreateWindowL(this);
	Components().AppendLC(iControl, 999);
	  	
    iControl->ConstructL(aNumChildren, aOwnerMask, TPoint(10,36),TSize(128,128), KRgbBlack, KRgbRed, CGraphicsContext::ESolidBrush);
	CleanupStack::Pop(iControl)	;
  	iControl->SetParent(this);
  	iControl->ActivateL();  		
}
	  
void CTestRectBackground::ConstructL()
    {
    CreateWindowL();    
	CTestRectGc::ConstructL(TPoint(20,20),TSize(600,200), KRgbBlack, KRgbYellow, CGraphicsContext::ESolidBrush);
	InitComponentArrayL();

	//Create a default control
    CreateComponentControlL(2, 7);
    	
	//Control to display the offscreen bitmap
    iControlImage = new (ELeave) CTestRectImageGc();
    iControlImage->CreateWindowL(this);
    iControlImage->DrawableWindow()->SetRequiredDisplayMode(EColor16MA); 
    iControlImage->ConstructL(TPoint(200,36),TSize(128,128), KRgbRed, KRgbGreen, CGraphicsContext::ESolidBrush); 
    iControlImage->ActivateL();

	//Second control to display blended overlay
    iControlImage2 = new (ELeave) CTestRectImageGc();
    iControlImage2->CreateWindowL(this); 
    iControlImage2->DrawableWindow()->SetRequiredDisplayMode(EColor16MA); 
    iControlImage2->ConstructL(TPoint(400,36),TSize(128,128), KRgbRed, KRgbGreen, CGraphicsContext::ESolidBrush); 
    iControlImage2->ActivateL();

	//Create an offscreen bitmap     
    iOffScreen = COffScreenBitmapGc::NewL(TSize(128,128));	
	
	//Create a second offscreen bitmap     
    iOffScreen2 = COffScreenBitmapGc::NewL(TSize(128,128));	
	
	//Set up the control images to display the two offscreen maps
	iControlImage->SetBitmap(iOffScreen->GetBitmap());	
	iControlImage2->SetBitmap(iOffScreen2->GetBitmap());	
    
    iBmpBackground = new (ELeave) CFbsBitmap();
    User::LeaveIfError(iBmpBackground->Load(_L("z:\\conetest\\city.mbm")));

	//Set up the Gc origin so that the offscreen bitmaps can be tiled in the same way as the screen drawn control
	TPoint ControlPos = iControl->PositionRelativeToScreen();
	iOffScreen->OffScreenGc()->SetWindowOrigin(ControlPos);
	iOffScreen2->OffScreenGc()->SetWindowOrigin(ControlPos);
	
    ActivateL();
    
    }

	


CTestRectBackground::~CTestRectBackground()
    {
    Components().RemoveById(999);
	delete iControl;

	delete iControlImage;
    delete iControlImage2;

    delete iBmpBackground;     

	delete iOffScreen;
	delete iOffScreen2;
	
	delete iContext;
    }


void CTestRectBackground::Draw(const TRect& aRect) const
    {	
    	CTestRectGc::Draw(aRect);    	   
    }



void CTestRectImageGc::Draw(const TRect& aRect) const
	{

    CWindowGc& gc=SystemGc();

	TRect rc = Rect();
	gc.SetClippingRect(aRect);
	if(iBmp)
		{
    	gc.BitBlt(rc.iTl, iBmp);
		}		
	}
	
CTConeInvalidateAppUi::CTConeInvalidateAppUi(CTmsTestStep* aStep) :
CTestCoeAppUi(aStep)
{}

CTConeInvalidateAppUi::~CTConeInvalidateAppUi()
	{
	RemoveFromStack(iViewControl);
	delete iViewControl;
	}


//Standard Implementation	
void CTConeInvalidateAppUi::ConstructL()
	{
	CTestCoeAppUi::ConstructL();
	
    iViewControl=new(ELeave) CTestRectBackground;
    iViewControl->ConstructL();
    AddToStackL(iViewControl);
	AutoTestManager().StartAutoTest();	
	}

//Standard Implementation	
TKeyResponse CTConeInvalidateAppUi::HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
	TKeyResponse ret=EKeyWasNotConsumed;
    if (aType==EEventKey && aKeyEvent.iCode==CTRL('e'))
		{
		CBaActiveScheduler::Exit();
		ret=EKeyWasConsumed;
		}
	return ret;
    }


void CTConeInvalidateAppUi::RunTestStepL(TInt aStepNum)
	{
		#define DRAW_SIZE   48
		#define DRAW_BORDER 8
		#define PARENT_HALF_WIDTH 64
		
		//Clear the offscreen bitmap to solid black, so that at each iteration we can see what is drawn during that frame.
		CTransGc *pOffGc = ((CTransGc*)iViewControl->iOffScreen->OffScreenGc());
		pOffGc->SetOrigin(TPoint(0,0));
		pOffGc->SetAlphaLevel(KAlphaOpaque);
		pOffGc->SetDrawMode(CGraphicsContext::EDrawModeWriteAlpha);
		pOffGc->SetBrushColor(TRgb(0,0,0,0));
		pOffGc->Clear();		

		//1/4 transparent (or 3/4 opaque).
		pOffGc->SetAlphaLevel(192);

		//Clear the 2nd offscreen bitmap 
		pOffGc = ((CTransGc*)iViewControl->iOffScreen2->OffScreenGc());
		pOffGc->SetOrigin(TPoint(0,0));
		pOffGc->SetAlphaLevel(KAlphaOpaque);
		pOffGc->SetDrawMode(CGraphicsContext::EDrawModeWriteAlpha);
		pOffGc->SetBrushColor(TRgb(0,0,0,0));
		pOffGc->Clear();		
		//1/4 transparent (or 3/4 opaque).
		pOffGc->SetAlphaLevel(192);

		TPoint drawOffset;		
		
		TInt Phase = aStepNum - 1;
				
		if (Phase<KNumTestSteps)
		{			
			//Create the control and setup its parameters. The top 2 bits of Phase define window ownership combination for 
			//the 2 sub levels of the animated control. 
			TInt OwnerMask = (Phase>>2);
			//The LSB is set to 1 (the parent which is always window owning). 
			iViewControl->CreateComponentControlL(1, OwnerMask<<1|1);
			
			//Set backgrounds for the original control and the overlayed controls.
	    	iViewControl->iControl->SetBackground(iViewControl->iControl);
	    	iViewControl->iControlImage->SetBackground(iViewControl->iControlImage);
	    	iViewControl->iControlImage2->SetBackground(iViewControl->iControlImage2);

			//The lower two bits of Phase define the redraw rectangle position in the sequence (tl, tr, br, bl) and repeats this cycle.		
			
			TInt Region = Phase & 3;
																						
			switch (Region)
				{
				case 0: drawOffset = TPoint(DRAW_BORDER,    			   DRAW_BORDER); 					break;
				case 1: drawOffset = TPoint(PARENT_HALF_WIDTH+DRAW_BORDER, DRAW_BORDER);					break;
				case 2: drawOffset = TPoint(PARENT_HALF_WIDTH+DRAW_BORDER, PARENT_HALF_WIDTH+DRAW_BORDER);	break;
				case 3: drawOffset = TPoint(DRAW_BORDER,    			   PARENT_HALF_WIDTH+DRAW_BORDER);	break;
				default : break;
				}
	
	
			INFO_PRINTF6(_L("Invalidate rect: Step=%2d, OwnerMask=%1d%1d%1d, Region=%1d"), aStepNum, OwnerMask>>1&1, OwnerMask&1, 1, Region);

			//Set up the redraw rectangle for this test run																		
			TRect redrawRect(drawOffset, TSize(DRAW_SIZE,DRAW_SIZE));
			
			//Draw the main control, before we set any special Gcs
			iViewControl->iControl->DrawNow();
								
			//Now set each control to an offscreen Gc in "chequer board fashion"
			
			for (TInt j=0; j<4; j++)
				for (TInt k=0; k<4; k++)
				{
					CCoeControl *pControl = iViewControl->iControl-> ComponentControl(j)->
																   ComponentControl(k);
												
					if ((k==0)||(k==3)) //is the chequer pattern
						pControl->SetGc(iViewControl->iOffScreen->OffScreenGc());
					else																												
						pControl->SetGc(iViewControl->iOffScreen2->OffScreenGc());														
					

				}

			
			//and set the control without a background, for the subrect redraw
			iViewControl->iControl->SetBackground(NULL);			
																
			for (TInt i=0; i<50; i++) //Animation cycle whilst the rectangular region is being updated
				{
				
				//Reset the Gcs' window cache variable, required every redraw cycle so the Gc knows when a clear is required
				((CTransGc*)iViewControl->iOffScreen->OffScreenGc())->iWin = NULL;
				((CTransGc*)iViewControl->iOffScreen2->OffScreenGc())->iWin = NULL;
				
				//Animate the controls
				iViewControl->iControl->AnimateComponents();		

				//Instruct the control the redraw the desired rectangle
				iViewControl->iControl->DrawNow(redrawRect);						

				//Draw the whole offscreen image so that we can check the correct part of the rectangle was drawn
				iViewControl->iControlImage->DrawNow();
				
				//Draw the offscreen image blended over background.
				iViewControl->iControlImage2->DrawNow();
				
				User::After(TTimeIntervalMicroSeconds32(1000));			
				}
		}
		else
		{			
			AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
		}										
	}

//----------
void CTConeInvalidateStep::ConstructAppL(CCoeEnv* aCoe)
	{ // runs inside a TRAP harness
	aCoe->ConstructL();
	CTConeInvalidateAppUi* appUi= new (ELeave) CTConeInvalidateAppUi(this);
	aCoe->SetAppUi(appUi);
	appUi->ConstructL();
	}

CTConeInvalidateStep::CTConeInvalidateStep()
	{
	SetTestStepName(KTConeInvalidateStep);
	}

CTConeInvalidateStep::~CTConeInvalidateStep()
	{}


TVerdict CTConeInvalidateStep::doTestStepL() // main function called by E32
	{
	INFO_PRINTF1(_L("Test Started"));
	
	PreallocateHALBuffer();

	__UHEAP_MARK;
	SetTestStepID(_L("UIF-Cone-TConeInvalidate"));
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

	RecordTestResultL();
	CloseTMSGraphicsStep();
	__UHEAP_MARKEND;

	INFO_PRINTF1(_L("Test Finished"));
	return TestStepResult();
	}
