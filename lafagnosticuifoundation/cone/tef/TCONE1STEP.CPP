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
// The test step tests CCoeControl Apis. A test control is created and 
// Key and Pointer events are generated asynchronously using AutoTest Manager.\n
// These events are then handled by the appropriate handlers of the test control.\n
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/


#include <coemain.h>
#include <coecntrl.h>
#include <coeaui.h>
#include <e32keys.h>
#include <basched.h>
#include <ecom/ecom.h>

#include "TCone1Step.h"


//#include <e32test.h>
//RTest test(_L("tcone1"));

//#define FORCE_AUTO

//
// class CTestControl
//

/**
  Second phase constructor for Test control.\n
  Creates a control's window.
  The created window is the child of the application's window group.\n
  Creates a Font.\n
  Requests pointer drag events using EnableDragEvents.\n
  This function should be called if a control is required to
  receive pointer drag and move events.\n
*/
void CTestControl::ConstructL()
    {
    CreateWindowL();
    CreateFontL();
    EnableDragEvents();
    SetExtent(TPoint(20,20),TSize(600,200));
    ActivateL();
    }

/**   Creates a font used by the test control.\n */

void CTestControl::CreateFontL()
    {
    TFontSpec spec(_L("Arial"),240);
    iFont=iCoeEnv->CreateScreenFontL(spec);
    }
/**
  Destructor for the CTestControl class.\n
  Calls the ReleaseScreenFont API of CCoeEnv to free all resources used by the font.\n
  
*/
CTestControl::~CTestControl()
    {
    iCoeEnv->ReleaseScreenFont(iFont);
    }
/**
  Responds to focus changed.\n
  This function is called whenever a control gains or loses focus
  as a result of a call to SetFocus().\n 
  A typical use of FocusChanged() is to change the appearance of the control
  to indicate whether or not it has focus, 
  for example by drawing a focus rectangle around it.\n

*/
void CTestControl::FocusChanged(TDrawNow aDrawNow)
	{
    if (aDrawNow)
        {
        ActivateGc();
        DrawBorder();
        DeactivateGc();
        }
    }
/**
  Draws the border for the control window.\n
*/
void CTestControl::DrawBorder() const
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
  Draw function for the Test Control.\n
  The method draws the border using DrawBorder function.\n
  Later draws the message using DrawMessage function.\n
*/
void CTestControl::Draw(const TRect& /*aRect*/) const
    {
	DrawBorder();
    DrawMessage();
    }
/**
  Draw function to draw a message specific to a key event.\n
  Gets a pointer to the Windows Graphic context which enables drawing.\n
  Sets the pen color, brush style and font for drawing message.\n
  Uses CWindowGc::DrawText API to draw the message.\n
*/
void CTestControl::DrawMessage() const
    {
    TRect rect=Rect();
    rect.Shrink(3,3);
    CWindowGc& gc=SystemGc();
    gc.UseFont(iFont);
    TInt ascent=(rect.iBr.iY-rect.iTl.iY-iFont->HeightInPixels())/2 + iFont->AscentInPixels();
    gc.SetPenColor(KRgbBlack);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.DrawText(iMessage,rect,ascent,CGraphicsContext::ECenter);
    }
/**
  This function draws the message on the window after handling a key event or a pointer event
  The method is called by the HandlerPointerEventL and OfferKeyEventL functions.\n
  Activates the Graphic context.\n
  Then invokes the DrawMessage function to draw the message.\n
  De activates the Graphic context.\n
*/
void CTestControl::DrawMessageNow() const
    {
	ActivateGc();
	DrawMessage();
	DeactivateGc();
    }
/**
  Auxilliary Function for Pointer based events.\n
   The method is an override from CCoeControl.\n
  The function handles the following pointer events.\n
  Double click Event.\n 
*/
void CTestControl::HandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    TInt modifiers=aPointerEvent.iModifiers;
	if (modifiers&EModifierDoubleClick)
    	iMessage.Format(_L("Double click event at (%d,%d)"),aPointerEvent.iPosition.iX,aPointerEvent.iPosition.iY);
	else
    	iMessage.Format(_L("Pointer event %d at (%d,%d)"),aPointerEvent.iType,aPointerEvent.iPosition.iX,aPointerEvent.iPosition.iY);
    DrawMessageNow();
    }

/**
   Auxiliary Function for all key event based test cases.\n
  
   The method is an override from CCoeControl.\n
   The function is called to handle the key events. It handles the following key events.\n
   1. (Ctrl or Shift)+ KeyLeft Arrow Key Event.\n
   2. (Ctrl or Shift)+KeyRight Arrow Key Event.\n
   3. (Ctrl or Shift)+ KeyDown Arrow Key Event.\n
   4. (Ctrl or Shift)+ KeyUp Arrow Key Event.\n
   
 */
 
TKeyResponse CTestControl::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    if (aType!=EEventKey)
	    return(EKeyWasConsumed);
    TInt modifiers=aKeyEvent.iModifiers;
    TInt code=aKeyEvent.iCode;
    iMessage.Format(_L("Key 0x%x, modifier 0x%x"),code,modifiers);
    DrawMessageNow();
    if (code==CTRL('e'))
        {
    	iCoeEnv->Flush(200000);
        CBaActiveScheduler::Exit();
        }
	if (((modifiers&EAllStdModifiers)==(EModifierCtrl))|((modifiers&EAllStdModifiers)==(EModifierShift)))
        {
        TPoint pos=Position();
        switch (code)
            {
			case EKeyLeftArrow:
				pos.iX--;
				break;
			case EKeyRightArrow:
				pos.iX++;
				break;
			case EKeyUpArrow:
				pos.iY--;
				break;
			case EKeyDownArrow:
				pos.iY++;
				break;
			default:
				break;
            }
		if (pos != Position())
			{
			SetPosition(pos);
			}
        }
    return(EKeyWasConsumed);
    }



/**
  Constructor for the CCone1Test AppUi class.\n
  Calls the base class CTestCoeAppUi constructor.\n
*/

CCone1TestAppUi::CCone1TestAppUi(CTmsTestStep* aStep) :
	CTestCoeAppUi(aStep)
{}

/**
  Second phase constructor for CCone1Test AppUi class.\n
  Calls the second phase constructor of base class CTestCoeAppUi.\n
  Creates a Test control which handles the received key events.\n
  Adds the control to the control stack so that it can receive key events.\n
  Executes the testcases asynchronously using Autotest Manager.\n
*/

void CCone1TestAppUi::ConstructL()
	{
	CTestCoeAppUi::ConstructL();

    iControl=new(ELeave) CTestControl;
    iControl->ConstructL();
    AddToStackL(iControl);

	AutoTestManager().StartAutoTest();
	}
/**
  Destructor for CCone1TestAppUi class.\n
  Removes the Test control from the control stack.\n
  Deletes the test control.\n
*/
CCone1TestAppUi::~CCone1TestAppUi()
	{
	RemoveFromStack(iControl);
	delete iControl;
	}
	


/**
   @SYMTestCaseID UIF-TCone1Step-TestKeyDownL
  
   @SYMPREQ
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method calls CTestControl::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType) 
   to simulate a key down event.\n
   
   @SYMTestExpectedResults. This test is manually verified, the system will display this string on the screen:
   "Key 0x11, modifier 0xcccccccc".\n
  
   @SYMTestType : CIT 
  
 */
 
void CCone1TestAppUi::TestKeyDownL()
	{
	TKeyEvent		theKeyEvent;
	theKeyEvent.iCode = CTRL('q');
	INFO_PRINTF1(_L("Emulation the event KeyDown"));
	iControl->OfferKeyEventL(theKeyEvent,EEventKey);	
	}
	

/**
   @SYMTestCaseID UIF-TCone1Step-TestButtonDownL
  
   @SYMPREQ
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method calls CTestControl::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
   to simulate a Button 1 or pen down event.\n
   
   @SYMTestExpectedResults. This test is manually verified, the system will display this string on the screen:
   "Pointer event 0 at (10,20)".\n
  
   @SYMTestType : CIT 
  
 */
 
void CCone1TestAppUi::TestButtonDownL()
	{
	TPointerEvent	thePointerEvent;
	
	thePointerEvent.iType=TPointerEvent::EButton1Down;
	thePointerEvent.iModifiers = 0;
	thePointerEvent.iPosition.iX = 10;
	thePointerEvent.iPosition.iY = 20;
	INFO_PRINTF1(_L("Emulation the point event"));
	iControl->HandlePointerEventL(thePointerEvent);	
	}


/**
   @SYMTestCaseID UIF-TCone1Step-TestDoubleClickL
  
   @SYMPREQ
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method calls CTestControl::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
   to simulate a double click event.\n
   
   @SYMTestExpectedResults. This test is manually verified, the system will display this string on the screen:
   "Double click event at (30,40)".\n
  
   @SYMTestType : CIT 
  
 */
 
void CCone1TestAppUi::TestDoubleClickL()
	{
	TPointerEvent	thePointerEvent;
	thePointerEvent.iModifiers = EModifierDoubleClick;
	thePointerEvent.iPosition.iX = 30;
	thePointerEvent.iPosition.iY = 40;
	INFO_PRINTF1(_L("Emulation the double click point event"));
	iControl->HandlePointerEventL(thePointerEvent);
	}
	

/**
   @SYMTestCaseID UIF-TCone1Step-TestCtrlKeyDownKeyRightArrowL
  
   @SYMPREQ
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method calls CTestControl::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
   to simulate prossing the control and right arrow keys together.\n
   
   @SYMTestExpectedResults. This test is manually verified, the system will display this string on the screen:
   "Key 0xf808, modifier 0x80".\n 
   The position of the control on the screen is also moved one unit to the right.\n
  
   @SYMTestType : CIT 
  
 */
 
void CCone1TestAppUi::TestCtrlKeyDownKeyRightArrowL()
	{
	TKeyEvent theKeyEvent;
	theKeyEvent.iModifiers=EModifierCtrl;
	theKeyEvent.iCode = EKeyRightArrow;
	INFO_PRINTF1(_L("Emulation the event KeyDown with code EKeyRightArrow"));
	iControl->OfferKeyEventL(theKeyEvent,EEventKey);
	}
	

/**
   @SYMTestCaseID UIF-TCone1Step-TestCtrlKeyDownKeyLeftArrowL
  
   @SYMPREQ
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method calls CTestControl::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
   to simulate prossing the control and left arrow keys together.\n
   
   @SYMTestExpectedResults. This test is manually verified, the system will display this string on the screen:
   "Key 0xf807, modifier 0x80".\n 
   The position of the control on the screen is also moved one unit to the left.\n
  
   @SYMTestType : CIT 
  
 */
 
void CCone1TestAppUi::TestCtrlKeyDownKeyLeftArrowL()
	{
	TKeyEvent theKeyEvent;
	theKeyEvent.iModifiers=EModifierCtrl;
	theKeyEvent.iCode = EKeyLeftArrow;
	INFO_PRINTF1(_L("Emulation the event KeyDown with code EKeyLeftArrow"));
	iControl->OfferKeyEventL(theKeyEvent,EEventKey);
	}


/**
   @SYMTestCaseID UIF-TCone1Step-TestCtrlKeyDownKeyDownArrowL
  
   @SYMPREQ
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method calls CTestControl::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
   to simulate prossing the control and left arrow keys together.\n
   
   @SYMTestExpectedResults. This test is manually verified, the system will display this string on the screen:
   "Key 0xf80a, modifier 0x80".\n 
   The position of the control on the screen is also moved one unit down.\n
  
   @SYMTestType : CIT 
  
 */
 
void CCone1TestAppUi::TestCtrlKeyDownKeyDownArrowL()
	{
	TKeyEvent theKeyEvent;
	theKeyEvent.iModifiers=EModifierCtrl;
	theKeyEvent.iCode = EKeyDownArrow;
	INFO_PRINTF1(_L("Emulation the event KeyDown with code EKeyDownArrow"));
	iControl->OfferKeyEventL(theKeyEvent,EEventKey);
	}
		


/**
   @SYMTestCaseID UIF-TCone1Step-TestCtrlKeyDownKeyUpArrowL
  
   @SYMPREQ
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method calls CTestControl::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
   to simulate prossing the control and left arrow keys together.\n
   
   @SYMTestExpectedResults. This test is manually verified, the system will display this string on the screen:
   "Key 0xf809, modifier 0x80".\n
   The poition of the control on the screen is also moved one unit up.\n
  
   @SYMTestType : CIT 
  
 */
 
void CCone1TestAppUi::TestCtrlKeyDownKeyUpArrowL()
	{
	TKeyEvent theKeyEvent;
	theKeyEvent.iModifiers=EModifierCtrl;
	theKeyEvent.iCode = EKeyUpArrow;
	INFO_PRINTF1(_L("Emulation the event KeyDown with code EKeyUpArrow"));
	iControl->OfferKeyEventL(theKeyEvent,EEventKey);
	}
	
/**
   Auxiliary Function for all Test Cases.\n
  
   The method is an override from CTestCoeAppUi.\n
   This function is called asynchronously by RunL function of the
   AutotestManager after previous test case is executed.\n
   Generates the following key events iteratively.\n
   Key Down Event.\n
   Button Down Pointer Event.\n
   Double Click Event.\n
   Key Down event for LeftArrow Key.\n
   Key Down event for RightArrow Key.\n
   Key Down event for Up Arrow Key.\n
   Key Down event for Down Arrow Key.\n
 */
 			
void CCone1TestAppUi::RunTestStepL(TInt aStepNum)
	{

	User::After(TTimeIntervalMicroSeconds32(1000000));
	
	switch(aStepNum)
		{
		case 1: 
		SetTestStepID(_L("UIF-TCone1Step-TestKeyDownL"));
		TestKeyDownL();
		RecordTestResultL();
		break;
		
		case 2: 
		SetTestStepID(_L("UIF-TCone1Step-TestButtonDownL"));
		TestButtonDownL();
		RecordTestResultL();
		break;
		case 3: 
		SetTestStepID(_L("UIF-TCone1Step-TestDoubleClickL"));
		TestDoubleClickL();
		RecordTestResultL();
		break;
		case 4:
		SetTestStepID(_L("UIF-TCone1Step-TestCtrlKeyDownKeyRightArrowL"));
		// follow on...
		case 5: case 6: case 7: case 8:
		TestCtrlKeyDownKeyRightArrowL();
		if( aStepNum == 8 )
			{
			RecordTestResultL();
			}
		break;
		
		case 9:
		SetTestStepID(_L("UIF-TCone1Step-TestCtrlKeyDownKeyLeftArrowL"));
		// follow on...
		case 10: case 11: case 12: case 13:
		TestCtrlKeyDownKeyLeftArrowL();
		if( aStepNum == 13 )
			{
			RecordTestResultL();
			}
		break;
		
		case 14:
		SetTestStepID(_L("UIF-TCone1Step-TestCtrlKeyDownKeyDownArrowL"));
		// follow on...
		case 15: case 16: case 17: case 18:
		TestCtrlKeyDownKeyDownArrowL();
		if( aStepNum == 18 )
			{
			RecordTestResultL();
			}
		break;
		
		case 19:
		SetTestStepID(_L("UIF-TCone1Step-TestCtrlKeyDownKeyUpArrowL"));
		// follow on...
		case 20: case 21: case 22: case 23:
		TestCtrlKeyDownKeyUpArrowL();
		if( aStepNum == 23 )
			{
			RecordTestResultL();
			CloseTMSGraphicsStep();
			}
		break;
		
		case 24: 
			AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
		break;

		}
	}


/**
  Completes the construction of the Control Environment(CCoeEnv object).\n
  Instantiates the CCone1TestAppUi class which serves as a AppUi class.\n
  Sets the CCone1TestAppUi object as the application's user interface object.\n
  Sets the system wide double click settings.\n
  Invokes the second phase constructor of the application's UI.\n
*/
void CTCone1Step::ConstructCone1AppL(CCoeEnv* aCoe)
	{ // runs inside a TRAP harness
	aCoe->ConstructL();
	CCone1TestAppUi* appUi=new(ELeave) CCone1TestAppUi(this);
	aCoe->SetAppUi(appUi);
	aCoe->WsSession().SetDoubleClick(1000000,4);
	appUi->ConstructL();
	}

/**
  Constructor for CTCone1Step class.\n
  Sets the test step name as KTCone1Step.\n
*/
CTCone1Step::CTCone1Step()
	{
	SetTestStepName(KTCone1Step);
	}
/**
  Destructor for Cone1Step class.\n
*/
CTCone1Step::~CTCone1Step()
{}
/**
  Entry function for CTCone1 Test Step.\n
  Sets up the control environment.\n
  Constructs and Launches the CTCone1 Test application.\n
 
*/
TVerdict CTCone1Step::doTestStepL() // main function called by E32
	{
	INFO_PRINTF1(_L("Test Started"));

	PreallocateHALBuffer();

	__UHEAP_MARK;

	CCoeEnv* coe=new(ELeave) CCoeEnv;
	TRAPD(err,ConstructCone1AppL(coe));

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
	


