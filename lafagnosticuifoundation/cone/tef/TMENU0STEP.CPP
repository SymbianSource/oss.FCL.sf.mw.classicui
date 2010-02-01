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
#include <e32keys.h>
#include <basched.h>
#include "TMenu0Step.h"



//
// class CTestMenu
//

/** The method is an override from CCoeControl.\n
	The function is called to handle key events.\n
	The only thing that is handled is if the control key\n
	was pressed together with another key.\n
*/
TKeyResponse CTestMenu::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
	if (aType==EEventKey)
		{
	    TInt modifiers=aKeyEvent.iModifiers;
	    TInt code=aKeyEvent.iCode;
	    if ((modifiers&EAllStdModifiers)==EModifierCtrl)
	        {
	        iObserver->MenuSelectionMadeL(code);
	        return(EKeyWasConsumed);
	        }
		}
    return(EKeyWasNotConsumed);
    }
    
//
// class CMessageControl
//

/**
  Second phase constructor for CMessageControl.\n
  Creates a control's window.\n
  The created window is the child of the application's window group.\n
  Sets a Font and display a message.\n
 */
void CMessageControl::ConstructL()
    {
    CreateWindowL();
    SetExtent(TPoint(20,20),TSize(600,200));
    TFontSpec spec(_L("Arial"),220);
    SetFontL(spec);
    ActivateL();
    }

/**
  Destructor for the CMessageControl class.\n
  Calls the ReleaseScreenFont API of CCoeEnv to free all resources used by the font.\n
  
 */
CMessageControl::~CMessageControl()
    {
    iCoeEnv->ReleaseScreenFont(iFont);
    }

/**
  Auxiliary Function to a set a new font.\n
 */
void CMessageControl::SetFontL(const TFontSpec& aFontSpec)
    {
    CFbsFont* font=iCoeEnv->CreateScreenFontL(aFontSpec);
    iCoeEnv->ReleaseScreenFont(iFont); // after previous line succeeds
    iFont=font;
    iFontSpec=aFontSpec;
    }

/**
  Auxiliary Function to change the font style.\n
 */
void CMessageControl::ToggleFontStyleL(TMessageControlFontStyle aStyleElement)
    {
    TFontSpec spec=iFontSpec;
    TBool doSet=EFalse;
    switch (aStyleElement)
        {
    case EStyleElementBold:
        spec.iFontStyle.SetStrokeWeight(spec.iFontStyle.StrokeWeight()? EStrokeWeightNormal: EStrokeWeightBold);
        doSet=ETrue;
        break;
    case EStyleElementItalic:
        spec.iFontStyle.SetPosture(spec.iFontStyle.Posture()? EPostureUpright: EPostureItalic);
        doSet=ETrue;
        break;
    case EStyleElementUnderline:
        iFontUnderline=(iFontUnderline? EUnderlineOff: EUnderlineOn);
        break;
    case EStyleElementStrikethrough:
        iFontStrikethrough=(iFontStrikethrough? EStrikethroughOff: EStrikethroughOn);
        }
    if (doSet)
        SetFontL(spec); // otherwise change effective at Draw time
    }

/**
  Auxiliary Function to handle Pointer events.\n
  Just logs that a pointer events has happend and redraws the window.\n
 */
void CMessageControl::HandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    iMessage.Format(_L("Pointer event %d at (%d,%d)"),aPointerEvent.iType,aPointerEvent.iPosition.iX,aPointerEvent.iPosition.iY);
    DrawMessageNow();
    }

/**
  Responds to focus change.\n
  This function is called whenever a control gains or loses focus\n
  as a result of a call to SetFocus().\n
 */
void CMessageControl::FocusChanged(TDrawNow aDrawNow)
	{
    if (aDrawNow)
        {
        ActivateGc();
        DrawBorder();
        DeactivateGc();
        }
    }

/**
  Draws a border around the window CMessageControl owns.\n
 */
void CMessageControl::DrawBorder() const
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
  Draws border and display a message in the window CMessageControl owns.\n
 */
void CMessageControl::Draw(const TRect& /*aRect*/) const
    {
    DrawBorder();
    DrawMessage();
    }

/**
  Displays a message stored in iMessage centered both vertically and horisontally.\n
 */
void CMessageControl::DrawMessage() const
    {
    TRect rect=Rect();
    rect.Shrink(3,3);
    TInt ascent=(rect.iBr.iY-rect.iTl.iY-iFont->HeightInPixels())/2 + iFont->AscentInPixels();
    CWindowGc& gc=SystemGc();
    gc.SetPenColor(KRgbBlack);
	gc.UseFont(iFont);
    if (iFontUnderline)
        gc.SetUnderlineStyle(iFontUnderline);
    if (iFontStrikethrough)
        gc.SetStrikethroughStyle(iFontStrikethrough);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.DrawText(iMessage,rect,ascent,CGraphicsContext::ECenter);
    }

/**
  Displays a message stored in iMessage, centered both vertically and horisontally.\n
  Draw the message as soon as possible.\n
 */
void CMessageControl::DrawMessageNow() const
    {
	ActivateGc();
	DrawMessage();
	DeactivateGc();
    }

/**
  Changed the message displayed in the window.\n
 */
void CMessageControl::SetMessage(const TDesC& aMessage)
    {
    iMessage=aMessage;
    DrawMessageNow();
    }

/**
  The method is an override from CCoeControl.\n
  The function is called to handle the key events. It handles the following key events.\n
  1. Shift + KeyLeft Arrow Key Event.\n
  2. Shift + KeyRight Arrow Key Event.\n
  3. Shift + KeyDown Arrow Key Event.\n
  4. Shift + KeyUp Arrow Key Event.\n 
 */
TKeyResponse CMessageControl::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    if (aType!=EEventKey)
	    return(EKeyWasConsumed);
	TInt modifiers=aKeyEvent.iModifiers;
	TInt code=aKeyEvent.iCode;
	iMessage.Format(_L("Key 0x%x, modifier 0x%x"),code,modifiers);
	DrawMessageNow();
	if ((modifiers&EAllStdModifiers)==(EModifierShift))
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

//
// class CTestMenu0AppUi
//

/**
  Constructor of CTestMenu0AppUi.\n
  Initializes the base constructor CTestCoeAppUi.\n
 */
CTestMenu0AppUi::CTestMenu0AppUi(CTmsTestStep* aStep) :
	CTestCoeAppUi(aStep)
	{}


/**
  Destructor of CTestMenu0AppUi.\n
  Removes the two controls from Cone's control stack and deletes them.\n
 */
CTestMenu0AppUi::~CTestMenu0AppUi()
    {
	RemoveFromStack(iMessageControl);
    delete(iMessageControl);
	RemoveFromStack(iMenu);
    delete(iMenu);
    }

/**
  @SYMTestCaseID UIF-TMenu0Step-ToggleBoldL
 
  @SYMPREQ PREQ0000
 
  @SYMTestPriority High
 
  @SYMTestStatus Implemented
  
  @SYMTestActions Tests that it is possible to toggle text to bold.
  
  SYMTestExpectedResult The font toggles to bold.
 
  @SYMTestType CIT 
 
 */
void CTestMenu0AppUi::ToggleBoldL()
    {
    iMessageControl->ToggleFontStyleL(EStyleElementBold);
    }
    
/**
  @SYMTestCaseID UIF-TMenu0Step-ToggleItalicL
 
  @SYMPREQ PREQ0000
 
  @SYMTestPriority High
 
  @SYMTestStatus Implemented
  
  @SYMTestActions Tests that it is possible to toggle text to Italic.
  
  @SYMTestExpectedResults The font toggles to Italic.
 
  @SYMTestType CIT 
 
 */
void CTestMenu0AppUi::ToggleItalicL()
    {
    iMessageControl->ToggleFontStyleL(EStyleElementItalic);
    }
    
/**
  @SYMTestCaseID UIF-TMenu0Step-ToggleUnderlineL
 
  @SYMPREQ PREQ0000
 
  @SYMTestPriority High
 
  @SYMTestStatus Implemented
  
  @SYMTestActions Test that it is possible to make text underlined.
  
  @SYMTestExpectedResults The font is underlined.
 
  @SYMTestType CIT 
 
 */
void CTestMenu0AppUi::ToggleUnderlineL()
    {
    iMessageControl->ToggleFontStyleL(EStyleElementUnderline);
    }
    
/**
  @SYMTestCaseID UIF-TMenu0Step-ToggleStrikethroughL
 
  @SYMPREQ PREQ0000
 
  @SYMTestPriority High
 
  @SYMTestStatus Implemented
  
  @SYMTestActions Test that it is possible to make text striked through.
  
  @SYMTestExpectedResults The font becomes striked through.
 
  @SYMTestType CIT 
 
 */
void CTestMenu0AppUi::ToggleStrikethroughL()
    {
    iMessageControl->ToggleFontStyleL(EStyleElementStrikethrough);
    }
    
/**
  Sends a text message to all windows in the window group TMenu1GroupName.\n
  Leaves if it failes.\n
 */
void CTestMenu0AppUi::SendMessageL(const TDesC8& aTextMsg)
	{
	RWsSession& wsSession=iCoeEnv->WsSession();
	TInt wgId=wsSession.FindWindowGroupIdentifier(0,TMenu1GroupName,0);
	if (wgId>0)
		User::LeaveIfError(wsSession.SendMessageToWindowGroup(wgId,KNullUid,aTextMsg));
	else
		iMessageControl->SetMessage(_L("TMenu1 is not running"));
	}

/**
  Handles application specific events.\n
  In this case whether it was possible or not to add/remove a window.\n
  A message about the number of windows in the group is also handled.\n
 
 */
void CTestMenu0AppUi::HandleApplicationSpecificEventL(TInt aType,const TWsEvent& aEvent)
	{
	switch (aType)
		{
		case EReplyWindowAdded:
			iMessageControl->SetMessage(_L("Window added"));
			return;
		case EReplyFailedToAddWindow:
			iMessageControl->SetMessage(_L("Failed to add window"));
			return;
		case EReplyWindowRemoved:
			iMessageControl->SetMessage(_L("Window removed"));
			return;
		case EReplyNoWindowToRemove:
			iMessageControl->SetMessage(_L("No window to remove"));
			return;
		case EReplyWindowsCounted:
    		TBuf<40> message;
    		message.Format(_L("Number of windows: %d"),*(TInt*)aEvent.EventData());
    		iMessageControl->SetMessage(message);
			break;
		}
	}

/**
  Sends an event to all windows in window group TMenu1GroupName\n
 
 */
void CTestMenu0AppUi::SendAsiMessageL(TMenuAsiEventSend aEvent)
	{
	RWsSession& wsSession=iCoeEnv->WsSession();
	TInt wgId=wsSession.FindWindowGroupIdentifier(0,TMenu1GroupName);
	if (wgId<=0)
		{
		iMessageControl->SetMessage(_L("TMenu1 is not running"));
		return;
		}
	TWsEvent wsEvent;
	wsEvent.SetType(aEvent);
	*(TInt*)wsEvent.EventData()=iCoeEnv->RootWin().Identifier();
	User::LeaveIfError(wsSession.SendEventToWindowGroup(wgId,wsEvent));
	}

/**
  Simulates different menu selections.\n
 
 */
void CTestMenu0AppUi::MenuSelectionMadeL(TInt aSelection)
    {
    switch (aSelection)
        {
		case CTRL('a'):
			{
			INFO_PRINTF1(_L("Test 1: SendAsiMessageL(ESendAddWindow)"));
			TRAPD(ret, SendAsiMessageL(ESendAddWindow));
			TEST(ret == KErrNone);
			return;
			}
		case CTRL('b'):
			{
			INFO_PRINTF1(_L("Test 2: ToggleBoldL"));
			TRAPD(ret, ToggleBoldL());
			TEST(ret == KErrNone);
			break;
	        }
		case CTRL('c'):
			{
			INFO_PRINTF1(_L("Test 3: SendAsiMessageL(ESendCountWindows)"));
			TRAPD(ret, SendAsiMessageL(ESendCountWindows));
			TEST(ret == KErrNone);
			return;
	        }
		case CTRL('i'):
			{
			INFO_PRINTF1(_L("Test 4: ToggleItalicL()"));
			TRAPD(ret, ToggleItalicL());
			TEST(ret == KErrNone);
			break;
	        }
		case CTRL('m'):
			{
			INFO_PRINTF1(_L("Test 5: SendMessageL(_L8('Greetings from TMenu0'))"));
			TRAPD(ret, SendMessageL(_L8("Greetings from TMenu0")));
			TEST(ret == KErrNone);
			return;
	        }
		case CTRL('o'):
			{
			INFO_PRINTF1(_L("Test 6: iCoeEnv->BringOwnerToFront()"));
			TRAPD(ret, iCoeEnv->BringOwnerToFront());
			TEST(ret == KErrNone);
			break;
	        }
		case CTRL('r'):
			{
			INFO_PRINTF1(_L("Test 7: SendAsiMessageL(ESendRemoveWindow)"));
			TRAPD(ret, SendAsiMessageL(ESendRemoveWindow));
			TEST(ret == KErrNone);
			return;
	        }
		case CTRL('s'):
			{
			INFO_PRINTF1(_L("Test 8: ToggleStrikethroughL()"));
			TRAPD(ret, ToggleStrikethroughL());
			TEST(ret == KErrNone);
			break;
	        }
		case CTRL('u'):
			{
			INFO_PRINTF1(_L("Test 9: ToggleUnderlineL()"));
			TRAPD(ret, ToggleUnderlineL());
			TEST(ret == KErrNone);
			break;
	        }
		default:
			break;
        }
    TBuf<40> message;
    message.Format(_L("Menu command Ctrl+%c chosen"),aSelection+'A'-1);
    iMessageControl->SetMessage(message);
    if (aSelection==CTRL('e'))
        {
		iCoeEnv->Flush(200000);
        CBaActiveScheduler::Exit();
        }
    }

/**
  The method is an override from CTestCoeAppUi.\n
  This function is called asynchronously by RunL function of the
  AutotestManager after previous test case is executed.\n
 
 */
void CTestMenu0AppUi::RunTestStepL(TInt aNextStep)
	{

	User::After(TTimeIntervalMicroSeconds32(1000000));
	

	switch(aNextStep)
		{
	case 1:
		MenuSelectionMadeL(CTRL('a'));
		break;
	case 2:
		SetTestStepID(_L("UIF-TMenu0Step-ToggleBoldL"));
		MenuSelectionMadeL(CTRL('b'));
		RecordTestResultL();
		break;
	case 3:
		MenuSelectionMadeL(CTRL('c'));
		break;
	case 4:
		SetTestStepID(_L("UIF-TMenu0Step-ToggleItalicL"));
		MenuSelectionMadeL(CTRL('i'));
		RecordTestResultL();
		break;
	case 5:
		MenuSelectionMadeL(CTRL('m'));
		break;
	case 6:
		MenuSelectionMadeL(CTRL('o'));
		break;
	case 7:
		MenuSelectionMadeL(CTRL('r'));
		break;
	case 8:
		SetTestStepID(_L("UIF-TMenu0Step-ToggleStrikethroughL"));
		MenuSelectionMadeL(CTRL('s'));
		RecordTestResultL();
		break;
	case 9:
		SetTestStepID(_L("UIF-TMenu0Step-ToggleUnderlineL"));
		MenuSelectionMadeL(CTRL('u'));
		RecordTestResultL();
		CloseTMSGraphicsStep();
		break;
	case 10:
		AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
		break;
		}
	}
    

/**
  Second phase constructor for CTestMenu0AppUi class.\n
  Calls the second phase constructor of base class CTestCoeAppUi.\n
  Creates a control to handle pointer and key events (iMessageControl).\n
  Creates a control to handle menu events (iMenu) which is added
  to Cone's control stack.\n
 */
void CTestMenu0AppUi::ConstructL()
    {
    CTestCoeAppUi::ConstructL();
    iMessageControl=new(ELeave) CMessageControl;
    iMessageControl->ConstructL();
    AddToStackL(iMessageControl);
    iMenu=new(ELeave) CTestMenu(this);
    AddToStackL(iMenu,ECoeStackPriorityMenu,ECoeStackFlagRefusesFocus);

	AutoTestManager().StartAutoTest();
    }

//
// Main
//

/**
  Completes the construction of the Control Environment(CCoeEnv object).\n
  Instantiates the CCone0TestAppUi class which serves as a AppUi class.\n
  Sets the CCone0TestAppUi object as the application's user interface object.\n
  Invokes the second phase constructor of the application's UI.\n
  
 */
void CTMenu0Step::ConstructAppL(CCoeEnv* aCoe)
	{ // runs inside a TRAP harness
	aCoe->ConstructL();
	CTestMenu0AppUi* appUi=new(ELeave) CTestMenu0AppUi(this);
	aCoe->SetAppUi(appUi);
	appUi->ConstructL();
	}

CTMenu0Step::~CTMenu0Step()
	{
	}

CTMenu0Step::CTMenu0Step()
	{
	SetTestStepName(KTMenu0Step);
	}

TVerdict CTMenu0Step::doTestStepL()
	{
	INFO_PRINTF1(_L("Test Started"));

	__UHEAP_MARK;

    CCoeEnv* coe=new CCoeEnv;
    TRAPD(err,ConstructAppL(coe));
    if (!err)
        coe->ExecuteD();
    
	__UHEAP_MARKEND;

	INFO_PRINTF1(_L("Test Finishes"));
	return TestStepResult();
	}




