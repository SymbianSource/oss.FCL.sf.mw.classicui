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
#include <coesndpy.h>
#include <e32keys.h>
#include <basched.h>
#include <bassnd.h>

#include "TMenu1Step.h"



//#include <e32test.h>
//RTest test(_L("tmenu1"));

//#define FORCE_AUT
// class CTestMenu1

/**
  Returns the number of bytes a menu item actually consists of.\n
*/
TInt TSimpleMenuItem::RealLengthOfData() const
    {
    return(sizeof(TSimpleMenuItem)-(ENominalTextLength-iText.Length())*sizeof(TText));
    }
    

/**
  Destructor\n
  Frees all memory allocated by the menu and fonts.\n
*/
CTestMenu1::~CTestMenu1()
    {
    FreeData();
    iCoeEnv->ReleaseScreenFont(iFont);
    }
    
/**
  Creates a font.\n
*/
void CTestMenu1::CreateFontL()
    {
    TFontSpec spec(_L("Arial"),240);
    iFont=iCoeEnv->CreateScreenFontL(spec);
    }

/**
  Handles pointer events.\n
  Closes the menu if pointer button has been pressed or been released
  and the pointer is outside the displayed menu.\n
  If inside, find out where and highlight the correct menu item. Report
  the event if pointer button was released.\n
*/
void CTestMenu1::HandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    TRect rect=Rect();
    if (!rect.Contains(aPointerEvent.iPosition))
        {
        switch (aPointerEvent.iType)
            {
        case TPointerEvent::EButton1Down:
        case TPointerEvent::EButton1Up:
            CloseMenu();
        default:
            break;
            }
        }
    rect.Shrink(EBorderWidth,EBorderWidth);
    if (!rect.Contains(aPointerEvent.iPosition))
        return;
    TInt n=(aPointerEvent.iPosition.iY-EBorderWidth)/iFont->HeightInPixels();
    HighlightTo(n);
    if (aPointerEvent.iType==TPointerEvent::EButton1Up)
        {
        ReportSelectionMadeL();
        CloseMenu();
        }
    }

/**
  Display the entire menu with the selected item hilighted.\n
 */
void CTestMenu1::Draw(const TRect& /*aRect*/) const
    {
    CWindowGc& gc=SystemGc();
    TRect rect=Rect();
    gc.DrawRect(rect);
    rect.Shrink(1,1);
    gc.SetPenColor(KRgbWhite);
    gc.DrawRect(rect);
    PrepareGcForDrawingItems();
    TInt count=iItemArray->Count();
    for (TInt i=0; i<count; i++)
        DrawItem(i,i==iItemSelected);
    }

/**
  Prepares the system graphical context.\n
 */
void CTestMenu1::PrepareGcForDrawingItems() const
    {
    CWindowGc& gc=SystemGc();
    gc.UseFont(iFont);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    }

/**
  Display a menu item either hilighted or not.\n
 */
void CTestMenu1::DrawItem(TInt aItem,TInt aHighlight) const
    {
    TInt itemHeight=iFont->HeightInPixels();
    TPoint tl(2,2+aItem*itemHeight);
    TSize sz(iSize.iWidth-4,itemHeight);
    TRect rect(tl,sz);
    CWindowGc& gc=SystemGc();
    if (!aHighlight)
       	{
        gc.SetPenColor(KRgbBlack);
        gc.SetBrushColor(KRgbWhite);
        }
    else
       	{
        gc.SetPenColor(KRgbWhite);
        gc.SetBrushColor(KRgbBlack);
        }
    TSimpleMenuItem& tmp=(*iItemArray)[aItem];
    gc.DrawText(tmp.iText,rect,iFont->AscentInPixels());
    }
    
/**
  Report to the window which menu item was selected.\n
 */
void CTestMenu1::ReportSelectionMadeL()
    {
    TSimpleMenuItem& tmp=(*iItemArray)[iItemSelected];
    iObserver->MenuSelectionMadeL(tmp.iCommand);
    }

/**
  Binds hot keys to menu items.\n
 */
void CTestMenu1::InitializeHotKeyCommands()
    {
    iHotKeyCommand[CTRL('b')]=EMenuCommandBold;
    iHotKeyCommand[CTRL('i')]=EMenuCommandItalic;
    iHotKeyCommand[CTRL('u')]=EMenuCommandUnderline;
    iHotKeyCommand[CTRL('s')]=EMenuCommandStrikethrough;
    iHotKeyCommand[CTRL('a')]=EMenuCommandAddWindow;
    iHotKeyCommand[CTRL('r')]=EMenuCommandRemoveWindow;
    iHotKeyCommand[CTRL('d')]=EMenuCommandDrag;
    iHotKeyCommand[CTRL('e')]=EMenuCommandExit;
    iHotKeyCommand[CTRL('c')]=EMenuCommandColor;
    iHotKeyCommand[CTRL('p')]=EMenuCommandPlaySound;
    }
    
/**
  Second phase constructor for the test menu.\n
 */
void CTestMenu1::ConstructL(MTestMenu1MenuObserver* aObserver,CCoeAppUi* aStack)
    {
    iObserver=aObserver;
    iStack=aStack;
    InitializeHotKeyCommands();
	CreateFontL();
    }
    
/**
  Frees the memory the menu occupied.\n
 */
void CTestMenu1::FreeData()
    {
    delete(iItemArray);
    iItemArray=NULL;
    }

/**
  Closes the menu if it is displayed.\n
 */
void CTestMenu1::CloseMenu()
    {
    if (!iDisplayed)
        return;
    CloseWindow();
    iDisplayed=EFalse;
    FreeData();
    }
    
/**
  Constructs a single menu item.\n
 */
void CTestMenu1::AddMenuItemL(TMenuCommand aCommand,const TDesC& aText)
    {
    TSimpleMenuItem tmp;
    tmp.iCommand=aCommand;
    tmp.iText=aText;
    iItemArray->AppendL(tmp,tmp.RealLengthOfData());
    }

/**
  Adds individual menu items.\n
 */
void CTestMenu1::DoLoadDataL()
    {
    AddMenuItemL(EMenuCommandBold,_L("Toggle bold (Ctrl+B)"));
    AddMenuItemL(EMenuCommandItalic,_L("Toggle italic (Ctrl+I)"));
    AddMenuItemL(EMenuCommandUnderline,_L("Toggle underline (Ctrl+U)"));
    AddMenuItemL(EMenuCommandStrikethrough,_L("Toggle strikethrough (Ctrl+S)"));
    AddMenuItemL(EMenuCommandAddWindow,_L("Add window (Ctrl+A)"));
    AddMenuItemL(EMenuCommandRemoveWindow,_L("Remove window (Ctrl+R)"));
    AddMenuItemL(EMenuCommandDrag,_L("Toggle drag enablement (Ctrl+D)"));
    AddMenuItemL(EMenuCommandColor,_L("Override colours (Ctrl+C)"));
    AddMenuItemL(EMenuCommandPlaySound,_L("Play sounds (Ctrl+P)"));
    AddMenuItemL(EMenuCommandExit,_L("Exit (Ctrl+E)"));
    }

/**
  Constructs a menu.\n
 */
void CTestMenu1::LoadDataL()
    {
    iItemArray=new(ELeave) CArrayVarFlat<TSimpleMenuItem> (16);
    TRAPD(ret,DoLoadDataL());
    if (ret)
        {
        FreeData();
        User::Leave(ret);
        }
    }

/**
  Calculates the size of all items in the menu.\n
 */
void CTestMenu1::CalculateSize(TSize& aSize)
    {
    TInt count=iItemArray->Count();
    aSize.iHeight=count*iFont->HeightInPixels();
    aSize.iHeight+=2+2; // 2 pixels at top and 2 at bottom
    for (TInt i=0; i<count; i++)
        {
        TSimpleMenuItem& tmp=(*iItemArray)[i];
        TInt itemWidth=iFont->TextWidthInPixels(tmp.iText);
        if (itemWidth>aSize.iWidth)
            aSize.iWidth=itemWidth;
        }
    aSize.iWidth+=2+2; // 2 pixels at left and 2 at right
    }

/**
  Creates a menu in a newly created window.\n
 */
void CTestMenu1::CreateMenuL()
    {
    LoadDataL();
    TRAPD(err,CreateWindowL());
    if (err)
        {
        FreeData();
        User::Leave(err);
        }
    EnableDragEvents();
    SetPointerCapture();
    iDisplayed=ETrue;
    TSize size;
    CalculateSize(size);
    SetExtent(TPoint(5,5),size);
    ActivateL();
    }

/**
  Hilights the current menu item.\n
 */
void CTestMenu1::HighlightTo(TInt aNewItemSelected)
    {
    if (aNewItemSelected==iItemSelected)
        return;
    ActivateGc();
    PrepareGcForDrawingItems();
    DrawItem(iItemSelected,EFalse);
    iItemSelected=aNewItemSelected;
    DrawItem(iItemSelected,ETrue);
	DeactivateGc();
    }

/**
  The method is an override from CCoeControl.\n
  The function is called to handle key events.\n
  Handles the up and down arrow keys which hilights previous/next item in the menu.\n
  PageUp causes first item in menu to be hilighted and PageDown causes the last to be hilighted.\n
  The enter key executes the current menu item.\n
  The escape key closes the menu.\n
  F9 and Tab show the menu.\n
  If <Ctrl> + key is pressed it is checked if it is a hot key. If so execute the menu selection.\n
 */
TKeyResponse CTestMenu1::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
	if (aType!=EEventKey)
		return(EKeyWasNotConsumed);
    TInt modifiers=aKeyEvent.iModifiers;
    TInt code=aKeyEvent.iCode;
    if ((modifiers&EAllStdModifiers)==EModifierCtrl)
        {
        if (code<27)
            {
            TMenuCommand command=iHotKeyCommand[code];
            if (command)
                {
                iObserver->MenuSelectionMadeL(command);
                CloseMenu();
                }
            }
        return(EKeyWasConsumed);
        }
    if (!iDisplayed)
        {
        if (code==EKeyF9 || code==EKeyTab)
            {
            CreateMenuL();
            return(EKeyWasConsumed);
            }
        }
    else
        {
        TInt count=iItemArray->Count();
        switch (code)
            {
			case EKeyDownArrow:
				if (iItemSelected<count-1)
					HighlightTo(iItemSelected+1);
				break;
			case EKeyUpArrow:
				if (iItemSelected)
					HighlightTo(iItemSelected-1);
				break;
			case EKeyPageUp:
				HighlightTo(0);
				break;
			case EKeyPageDown:
				HighlightTo(count-1);
				break;
			case EKeyEnter:
				ReportSelectionMadeL();
			case EKeyEscape:
				CloseMenu();
				break;
			default:
				break;
            }
        return(EKeyWasConsumed);
        }
    return(EKeyWasNotConsumed);
    }
 

   
//
// class CMenu1MessageControl
//



void CMenu1MessageControl::ToggleDragState()
    {
    TInt filter=EPointerFilterDrag; // means to filter out drags
    if (iDragsEnabled)
        {
        iDragsEnabled=EFalse;
        SetMessage(_L8("Pointer drag events disabled"));
        }
    else
        {
        iDragsEnabled=ETrue;
        SetMessage(_L8("Pointer drag events enabled"));
        filter=0;
        }
    BackedUpWindow().PointerFilter(EPointerFilterDrag,filter);
    }
    
/**
  Second phase constructor for CMenu1MessageControl.\n
  Creates a control's window.\n
  The created window is the child of the application's window group.\n
  Sets a Font and display a message.\n
 */
void CMenu1MessageControl::ConstructL()
    {
    CreateBackedUpWindowL(iCoeEnv->RootWin(),EGray2);
    SetExtent(TPoint(20,20),TSize(600,200));
    TFontSpec spec(_L("Arial"),220);
    SetFontL(spec);
    SetMessage(_L8("Press Tab for Menu..."));
    ActivateL();
    }

/**
  Destructor for the CMenu1MessageControl class.\n
  Calls the ReleaseScreenFont API of CCoeEnv to free all resources used by the font.\n
 */
CMenu1MessageControl::~CMenu1MessageControl()
    {
    iCoeEnv->ReleaseScreenFont(iFont);
	//delete iPeriodic;
    }

/**
  Auxiliary Function to a set a new font.\n
 */
void CMenu1MessageControl::SetFontL(const TFontSpec& aFontSpec)
    {
    CFbsFont* font=iCoeEnv->CreateScreenFontL(aFontSpec);
    iCoeEnv->ReleaseScreenFont(iFont); // after previous line succeeds
    iFont=font;
    iFontSpec=aFontSpec;
    }

/**
  Auxiliary Function to change the font style.\n
 */
void CMenu1MessageControl::ToggleFontStyleL(TMessageControlFontStyle aStyleElement)
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
    DrawMessageNow();
    }

/**
  Handles Pointer events.\n
  Just logs that a pointer events has happend and redraws the window.\n
 */
void CMenu1MessageControl::HandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    iMessage.Format(_L8("Pointer event %d at (%d,%d)"),aPointerEvent.iType,aPointerEvent.iPosition.iX,aPointerEvent.iPosition.iY);
    DrawMessageNow();
    }

/**
  Responds to focus change.\n
  This function is called whenever a control gains or loses focus\n
  as a result of a call to SetFocus().\n
 */
void CMenu1MessageControl::FocusChanged(TDrawNow aDrawNow)
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
void CMenu1MessageControl::DrawBorder() const
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
  Draws border and display a message in the window CMenu1MessageControl owns.\n
 */
void CMenu1MessageControl::Draw(const TRect& /*aRect*/) const
    {
    DrawBorder();
    DrawMessage();
    }

/**
  Displays a message stored in iMessage centered both vertically and horisontally.\n
 */
void CMenu1MessageControl::DrawMessage() const
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
#if !defined(_UNICODE)
    gc.DrawText(iMessage,rect,ascent,CGraphicsContext::ECenter);
#else
    TBuf<40> text;
	text.Copy(iMessage);
    gc.DrawText(text,rect,ascent,CGraphicsContext::ECenter);
#endif
    }

/**
  Displays a message stored in iMessage, centered both vertically and horisontally.\n
  Draw the message as soon as possible.\n
 */
void CMenu1MessageControl::DrawMessageNow() const
    {
	ActivateGc();
	DrawMessage();
	DeactivateGc();
    }

/**
  Changed the message displayed in the window.\n
 */
void CMenu1MessageControl::SetMessage(const TDesC8& aMessage)
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
TKeyResponse CMenu1MessageControl::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    if (aType!=EEventKey)
	    return(EKeyWasConsumed);
	TInt modifiers=aKeyEvent.iModifiers;
	TInt code=aKeyEvent.iCode;
	iMessage.Format(_L8("Key 0x%x, modifier 0x%x"),code,modifiers);
	DrawMessageNow();
	if ((modifiers&EAllStdModifiers)==(EModifierShift|EModifierCtrl))
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
  Moves the window x steps horizontally and y steps vertically.\n
 */
void CMenu1MessageControl::MoveWindow(TInt aStepX, TInt aStepY)
	{
        TPoint pos=Position();
		pos.iX += aStepX;
		pos.iY += aStepY;
		
		SetPosition(pos);

	}
/*
TInt CMenu1MessageControl::Execute(TAny* aControl)
	{
		CMenu1MessageControl*	theControl = (CMenu1MessageControl*)aControl;
		return theControl->DoExecute();
	}

TInt CMenu1MessageControl::DoExecute()
		{
	iNumAttempt++;
	switch(iNumAttempt)
		{
		case 1:
		iPeriodic->Cancel();
		return 1;
		break;
		}

	return 0;	
	}
*/

//
// class CTrivialWindow
//

/**
  Constructs a CTrivialWindow.\n
 */
void CTrivialWindow::ConstructL(const TPoint& aPoint,const TSize& aSize)
    {
    CreateWindowL();
    SetExtent(aPoint,aSize);
    Window().SetShadowHeight(4);
    ActivateL();
    }
    
void CTrivialWindow::Draw(const TRect& /*aRect*/) const
    {
    CWindowGc& gc=SystemGc();
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.DrawRect(Rect());
    }


//
// class CTestAppUi
//


/**
  Destructor of CTestMenu1AppUi.\n
 */

CTestMenu1AppUi::~CTestMenu1AppUi()
    {
	RemoveFromStack(iMessageControl);
    delete(iMessageControl);
    if (!iWindows)
        return;
    TInt i=iWindows->Count();
    while (i--)
        delete((*iWindows)[i]);
    delete(iWindows);
	delete iTimer;
    }
    
void CTestMenu1AppUi::DoAddWindowL(CTrivialWindow* aWindow,const TPoint& aPoint,const TSize& aSize)
    {
    aWindow->ConstructL(aPoint,aSize);
    iWindows->AppendL(aWindow);
    }

/**
  @SYMTestCaseID UIF-TMenu1Step-AddWindowL
 
  @SYMPREQ PREQ0000
 
  @SYMTestPriority High
 
  @SYMTestStatus Implemented
  
  @SYMTestActions Adds a window to the display
  
  @SYMTestExpectedResults Window is added.
 
  @SYMTestType CIT 
 
 */
void CTestMenu1AppUi::AddWindowL()
    {
    TInt offset=iWindows->Count()*5;
    TSize size(40,40);
    TPoint pos(640-40-offset,offset);
    CTrivialWindow* window=new(ELeave) CTrivialWindow;
    TRAPD(err,DoAddWindowL(window,pos,size));
    if (err)
        {
        delete(window);
        User::Leave(err);
        }
    }

/**
  @SYMTestCaseID UIF-TMenu1Step-RemoveWindow
 
  @SYMPREQ PREQ0000
 
  @SYMTestPriority High
 
  @SYMTestStatus Implemented
  
  @SYMTestActions Removes a window from the display
  
  @SYMTestExpectedResults Window is removed.
 
  @SYMTestType CIT 
 
 */
void CTestMenu1AppUi::RemoveWindow()
    {
    TInt i=iWindows->Count();
    if (i--)
        {
        delete((*iWindows)[i]);
        iWindows->Delete(i);
        }
    }

/**
  @SYMTestCaseID UIF-TMenu1Step-TestColorOverridesL
 
  @SYMPREQ PREQ0000
 
  @SYMTestPriority High
 
  @SYMTestStatus Implemented
  
  @SYMTestActions Tests that it possible to override the current colour of a control.
  
  @SYMTestExpectedResults The function doesn't panic by calling User::Invariant (IMHO test code should not be allowed to panic. Better to fail the test. JohanG)
 
  @SYMTestType CIT 
 
 */
void CTestMenu1AppUi::TestColorOverridesL()
	{
	CCoeControl* ctrl=new(ELeave) CCoeControl;
	CleanupStack::PushL(ctrl);
	TRgb color=KRgbDarkYellow;
	if (ctrl->GetColor(0,color))
		User::Invariant();
	ctrl->OverrideColorL(0,KRgbBlack);
	if (!ctrl->GetColor(0,color))
		User::Invariant();
	if (color!=KRgbBlack)
		User::Invariant();
	if (ctrl->GetColor(3,color))
		User::Invariant();
	ctrl->OverrideColorL(6,KRgbMagenta);
	ctrl->OverrideColorL(5,KRgbGreen);
	if (!ctrl->GetColor(5,color))
		User::Invariant();
	if (color!=KRgbGreen)
		User::Invariant();
	if (!ctrl->GetColor(6,color))
		User::Invariant();
	if (color!=KRgbMagenta)
		User::Invariant();
	CleanupStack::PopAndDestroy(); // ctrl
	iMessageControl->SetMessage(_L8("passed tests"));
	}

_LIT(KWavName1,"C:\\system\\systemsounds\\message.wav");
_LIT(KWavName2,"C:\\system\\systemsounds\\ring.wav");

const TUid KTestSoundType1={4567};
const TUid KTestSoundType2={4568};
const TUid KTestSoundType3={4569};
const TUid KTestSoundType4={4570};

/**
  Sets up the sound environment.\n
 */
LOCAL_C void SetupSoundsL(const CCoeEnv& aEnv)
	{
//	TFileName drv;
//	Dll::FileName(drv);
	TBaSystemSoundInfo info;
	info.iVolume=65530;

	info.iType=TBaSystemSoundType(KTestSoundType1);
	info.iPriority=100;
	TFileName name=KWavName1();
//	name.Insert(0,drv.Left(1)); // allow sound files on the same drive as the test code
	info.SetFileName(name);
	BaSystemSound::SetSoundL(aEnv.FsSession(),info);

	info.iType=TBaSystemSoundType(KTestSoundType2);
	info.iPriority=100;
	name=KWavName2();
//	name.Insert(0,drv.Left(1)); // allow sound files on the same drive as the test code
	info.SetFileName(name);
	BaSystemSound::SetSoundL(aEnv.FsSession(),info);

	info.iType=TBaSystemSoundType(KTestSoundType4);
	info.iPriority=180;
	info.SetFixedSequenceNumber(0);
	BaSystemSound::SetSoundL(aEnv.FsSession(),info);

	info.iType=TBaSystemSoundType(KTestSoundType3);
	info.iPriority=120;
	TBaSystemSoundInfo::TTone tone(440,TTimeIntervalMicroSeconds32(250000));
	info.SetTone(tone);
	BaSystemSound::SetSoundL(aEnv.FsSession(),info);
	}

/**
  @SYMTestCaseID UIF-TMenu1Step-DoTestSoundsL
 
  @SYMPREQ PREQ0000
 
  @SYMTestPriority High
 
  @SYMTestStatus Implemented
  
  @SYMTestActions Tests different sounds. This function is never called. Probably because it has nothing to do with menus.
  
  @SYMTestExpectedResults Different sounds can be heard.
 
  @SYMTestType CIT 
 
 */
void CTestMenu1AppUi::DoTestSoundsL()
	{
	// play each sound in turn
	TBaSystemSoundType type(KTestSoundType4);
	CoeSoundPlayer::PlaySound(type);
	Wait();
	type.iMajor=KTestSoundType1;
	CoeSoundPlayer::PlaySound(type);
	Wait();
	type.iMajor=KTestSoundType2;
	CoeSoundPlayer::PlaySound(type);
	Wait();
	type.iMajor=KTestSoundType3;
	CoeSoundPlayer::PlaySound(type,3,TTimeIntervalMicroSeconds32(100000));
	Wait();
	Wait();

	// play then cancel sound 3
	type.iMajor=KTestSoundType3;
	CoeSoundPlayer::PlaySound(type,3,TTimeIntervalMicroSeconds32(200000));
	Wait();
	CoeSoundPlayer::CancelSound(type);

	// start 1, queue 2 then cancel them both
	type.iMajor=KTestSoundType1;
	CoeSoundPlayer::PlaySound(type);
	type.iMajor=KTestSoundType2;
	CoeSoundPlayer::PlaySound(type);
	Wait();
	CoeSoundPlayer::CancelSound(type);

	// start 2 then interrupt it with 1
	type.iMajor=KTestSoundType2;
	CoeSoundPlayer::PlaySound(type);
	type.iMajor=KTestSoundType1;
	CoeSoundPlayer::PlaySoundNow(type,CoeSoundPlayer::ENoRepeat,TTimeIntervalMicroSeconds32(0));
	Wait();

	// interrupt this with the higher priority sound 3
	type.iMajor=KTestSoundType3;
	CoeSoundPlayer::PlaySound(type,3,100000);
	Wait();
	}

/**
  Sets up sound environment and calls the test code.\n
  N.B. Function never called.\n
 */
void CTestMenu1AppUi::TestPlaySoundL()
	{
	SetupSoundsL(*iCoeEnv);
	DoTestSoundsL();
	}

/**
  Sets the timer to 10 sec.\n
 */
void CTestMenu1AppUi::Wait()
	{
	iTimer->Start(10000000,10000000,TCallBack(TimerCallBack,this));
	CActiveScheduler::Start();
	}

/**
  Callback that is called when timer expires.\n
 */
TInt CTestMenu1AppUi::TimerCallBack(TAny* aSelf)
	{ // static
	REINTERPRET_CAST(CTestMenu1AppUi*,aSelf)->iTimer->Cancel();
	CActiveScheduler::Stop();
	return 0;
	}

/**
  Handles different menu selections.\n
 */
void CTestMenu1AppUi::MenuSelectionMadeL(TMenuCommand aSelection)
    {
    switch (aSelection)
        {
		case EMenuCommandBold:
		case EMenuCommandItalic:
		case EMenuCommandUnderline:
		case EMenuCommandStrikethrough:
			{
			TRAPD(ret, iMessageControl->ToggleFontStyleL((TMessageControlFontStyle)aSelection));
			TEST(ret == KErrNone);
			break;
			}
		case EMenuCommandDrag:
			{
			TRAPD(ret, iMessageControl->ToggleDragState());
			TEST(ret == KErrNone);
			break;
			}
		case EMenuCommandExit:
			{
			iMessageControl->SetMessage(_L8("About to exit..."));
			iCoeEnv->Flush(200000);
			CBaActiveScheduler::Exit();
			break;
			}
		case EMenuCommandAddWindow:
			{
			TRAPD(ret, AddWindowL());
			TEST(ret == KErrNone);
			break;
			}
		case EMenuCommandRemoveWindow:
			{
			TRAPD(ret, RemoveWindow());
			TEST(ret == KErrNone);
			break;
			}
		case EMenuCommandColor:
			{
			TRAPD(ret, TestColorOverridesL());
			TEST(ret == KErrNone);
			break;
			}
		case EMenuCommandPlaySound:
			{
			TRAPD(ret, TestPlaySoundL());
			TEST(ret == KErrNone);
			break;
			}
		default:
			break;
        }
    }

/**
  Sets the message in the window to aMessageParameters but never returns a reponse.\n
 */
MCoeMessageObserver::TMessageResponse CTestMenu1AppUi::HandleMessageL(TUint32, TUid, const TDesC8& aMessageParameters)
	{
	iMessageControl->SetMessage(aMessageParameters);
	return EMessageNotHandled;
	}

/**
  Handles application specific events.\n
  In this case it adds/removes a window.\n
  A reply message of how many windows there are in the window group is sent back.\n
 */
void CTestMenu1AppUi::HandleApplicationSpecificEventL(TInt aType,const TWsEvent& aEvent)
	{
	TInt senderWgId=(*(TInt*)aEvent.EventData());
	TInt count=iWindows->Count();
	TMenuAsiEventReply reply=EReplyWindowsCounted;
	switch (aType)
		{
		case ESendCountWindows:
			break;
		case ESendAddWindow:
			reply=EReplyWindowAdded;
			TRAPD(err,AddWindowL());
			if (err)
				reply=EReplyFailedToAddWindow;
			break;
		case ESendRemoveWindow:
			if (!count)
				reply=EReplyNoWindowToRemove;
			else
				{
				RemoveWindow();
				reply=EReplyWindowRemoved;
				}
			break;
		default:
			break;
		}
	TWsEvent data;
	data.SetType(reply);
	*(TInt*)data.EventData()=count;
	iCoeEnv->WsSession().SendEventToWindowGroup(senderWgId,data);
	}

CTestMenu1AppUi::CTestMenu1AppUi(CTmsTestStep* aStep) :
	CTestCoeAppUi(aStep)
	{}



void CTestMenu1AppUi::ConstructL()
    {
    CTestCoeAppUi::ConstructL();
    
	iMessageControl=new(ELeave) CMenu1MessageControl;
    iMessageControl->ConstructL();
    AddToStackL(iMessageControl);
    iMenu=new(ELeave) CTestMenu1;
    iMenu->ConstructL(this,this);
    AddToStackL(iMenu,ECoeStackPriorityMenu,ECoeStackFlagRefusesFocus|ECoeStackFlagOwnershipTransfered);
    iWindows=new(ELeave) CArrayFixFlat<CTrivialWindow*>(4);
	iCoeEnv->RootWin().SetName(TMenu1GroupName);
	iTimer=CPeriodic::NewL(0);
    
	AutoTestManager().StartAutoTest();
	
	}


/**
  The method is an override from CTestCoeAppUi.\n
  This function is called asynchronously by RunL function of the
  AutotestManager after previous test case is executed.\n
*/
void CTestMenu1AppUi::RunTestStepL(TInt aNextStep)
	{

	User::After(TTimeIntervalMicroSeconds32(1000000));
	

	switch(aNextStep)
		{
		case 1: //toggle  bold
        INFO_PRINTF1(_L("toggle  bold"));
		iMenu->CreateMenuL();
		break;
		case 2:
		iMenu->ReportSelectionMadeL();
		iMenu->CloseMenu();
		break;
		
		case 3: //toggle italic
        INFO_PRINTF1(_L("toggle  italic"));
        iMenu->CreateMenuL();
		break;
		case 4:
		iMenu->HighlightTo(iMenu->iItemSelected+1);
		break;
		case 5:
		iMenu->ReportSelectionMadeL();
		iMenu->CloseMenu();
		break;
		
		case 6: //toggle underline
        INFO_PRINTF1(_L("toggle  underline"));
        iMenu->CreateMenuL();
		break;
		case 7:
		iMenu->HighlightTo(iMenu->iItemSelected+1);
		break;
		case 8:
		iMenu->ReportSelectionMadeL();
		iMenu->CloseMenu();
		break;
		
		case 9://toggle strikethrough
        INFO_PRINTF1(_L("toggle  strikethrough\n"));
        iMenu->CreateMenuL();
		break;
		case 10:
		iMenu->HighlightTo(iMenu->iItemSelected+1);
		break;
		case 11:
		iMenu->ReportSelectionMadeL();
		iMenu->CloseMenu();
		break;
		
		case 12://add window
		SetTestStepID(_L("UIF-TMenu1Step-AddWindowL"));
        INFO_PRINTF1(_L("add window"));
        iMenu->CreateMenuL();
        RecordTestResultL();
		break;
		case 13:
		iMenu->HighlightTo(iMenu->iItemSelected+1);
		break;
		case 14: 
		iMenu->ReportSelectionMadeL();
		iMenu->CloseMenu();
		break;
		
		case 15: //remove window
		SetTestStepID(_L("UIF-TMenu1Step-RemoveWindow"));
        INFO_PRINTF1(_L("remove window\n"));
        iMenu->CreateMenuL();
        RecordTestResultL();
		break;
		case 16:
		iMenu->HighlightTo(iMenu->iItemSelected+1);
		break;
		case 17:
		iMenu->ReportSelectionMadeL();
		iMenu->CloseMenu();
		break;
		
		case 18: //toggle drag enablement
        INFO_PRINTF1(_L("toggle drag enablement"));
        iMenu->CreateMenuL();
		break;
		case 19:
		iMenu->HighlightTo(iMenu->iItemSelected+1);
		break;
		case 20:
		iMenu->ReportSelectionMadeL();
		iMenu->CloseMenu();
		break;
		
		case 21: //overide colours
		SetTestStepID(_L("UIF-TMenu1Step-TestColorOverridesL"));
        INFO_PRINTF1(_L("overide colours"));
        iMenu->CreateMenuL();
        RecordTestResultL();
		CloseTMSGraphicsStep();
		break;
		case 22:
		iMenu->HighlightTo(iMenu->iItemSelected+1);
		break;
		case 23:
		iMenu->ReportSelectionMadeL();
		iMenu->CloseMenu();
		break;

/*  	case 24: //play sound
        iMenu->CreateMenuL();
  		break;
  		case 25:
  		iMenu->HighlightTo(iMenu->iItemSelected+1);
  		break;
  		case 26:
  		iMenu->ReportSelectionMadeL();
  		iMenu->CloseMenu();
  		break;
*/
  		case 30: case 31: case 32: case 33: case 34:
		iMessageControl->MoveWindow(5, 0);
        INFO_PRINTF1(_L("Move the window to right"));
		break;
		
		case 35: case 36: case 37: case 38: case 39:
		iMessageControl->MoveWindow(-5, 0);
        INFO_PRINTF1(_L("Move the window to left"));
		break;

		case 40: case 41: case 42: case 43: case 44:
		iMessageControl->MoveWindow(0, 5);
        INFO_PRINTF1(_L("Move the window to down"));
		break;
		
		case 45: case 46: case 47: case 48: case 49:
		iMessageControl->MoveWindow(0, -5);
        INFO_PRINTF1(_L("Move the window to up"));
		break;

		case 50:
			AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);

		break;
		}
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
void CTMenu1Step::ConstructAppL(CCoeEnv* aCoe)
	{ // runs inside a TRAP harness
	aCoe->ConstructL();
	CTestMenu1AppUi* appUi=new(ELeave) CTestMenu1AppUi(this);
	aCoe->SetAppUi(appUi);
	appUi->ConstructL();
	}
	

CTMenu1Step::~CTMenu1Step()
	{
	}


CTMenu1Step::CTMenu1Step()
	{
	SetTestStepName(KTMenu1Step);
	}


TVerdict CTMenu1Step::doTestStepL()// main function called by E32
	{
	INFO_PRINTF1(_L("Test Started"));

	__UHEAP_MARK;

    CCoeEnv* coe=new CCoeEnv;
    TRAPD(err,ConstructAppL(coe));
    if (!err)
        coe->ExecuteD();
    
	__UHEAP_MARKEND;

	INFO_PRINTF1(_L("Test Finished"));
	return TestStepResult();
	}




