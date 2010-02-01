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

#if !defined(__TMENU1STEP_H__)
#define __TMENU1STEP_H__

#include <test/testexecutestepbase.h>
#include "TMenuTestServer.h"
#include "appfwk_test_AppUi.h"
#include "TMENUASI.H"


enum TMenuCommand
    {
    EMenuCommandBold=EStyleElementBold,
    EMenuCommandItalic=EStyleElementItalic,
    EMenuCommandUnderline=EStyleElementUnderline,
    EMenuCommandStrikethrough=EStyleElementStrikethrough,
    EMenuCommandAddWindow,
    EMenuCommandRemoveWindow,
    EMenuCommandDrag,
	EMenuCommandColor,
	EMenuCommandPlaySound,
    EMenuCommandExit
    };



class CTMenu1Step : public CTmsTestStep
	{
public:
	CTMenu1Step();
	~CTMenu1Step();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CCoeEnv* aCoe);
	};
	
	

class MTestMenu1MenuObserver
	{
public:
	virtual void MenuSelectionMadeL(TMenuCommand aSelection)=0;
	};



class TSimpleMenuItem
    {
private:
    enum { ENominalTextLength=80 };
public:
    TMenuCommand iCommand;
    TBuf<ENominalTextLength> iText; // less than this actually stored
public:
    TInt RealLengthOfData() const;
    };



class CTestMenu1 : public CCoeControl
	{
public:
    ~CTestMenu1();
    void ConstructL(MTestMenu1MenuObserver* aObserver,CCoeAppUi* aStack);
    void CreateMenuL();
    void ReportSelectionMadeL();
    void CloseMenu();
    void HighlightTo(TInt aNewItemSelected);
    TInt iItemSelected;
private: // framework
    TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
    void HandlePointerEventL(const TPointerEvent& aPointerEvent);
    void Draw(const TRect& aRect) const;
private: // new functions
    void InitializeHotKeyCommands();
    void CreateFontL();
    void LoadDataL();
    void DoLoadDataL();
    void FreeData();
    void AddMenuItemL(TMenuCommand aCommand,const TDesC& aText);
    void PrepareGcForDrawingItems() const;
    void DrawItem(TInt aItem,TInt aHighlight) const;
	void CalculateSize(TSize& aSize);
private:
    enum { EBorderWidth=2 };
    MTestMenu1MenuObserver* iObserver;
    CFont* iFont;
    CCoeAppUi* iStack;
    TBool iDisplayed;
    TMenuCommand iHotKeyCommand[27];
    CArrayVarFlat<TSimpleMenuItem>* iItemArray;
	};
	
	

class CMenu1MessageControl : public CCoeControl
    {
public:
    ~CMenu1MessageControl();
    void ConstructL();
    void ToggleFontStyleL(TMessageControlFontStyle aStyleElement);
    void ToggleDragState();
    void SetMessage(const TDesC8& aMessage);
	//static TInt Execute(TAny* aApplication);
	//TInt DoExecute();
	void MoveWindow(TInt aStepX, TInt aStepY);

private: // framework
    TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
    void HandlePointerEventL(const TPointerEvent& aPointerEvent);
    void Draw(const TRect& aRect) const;
	void FocusChanged(TDrawNow aDrawNow);
private: // new functions
    void DrawBorder() const;
    void SetFontL(const TFontSpec& aFontSpec);
    void DrawMessage() const;
    void DrawMessageNow() const;
private:
    TBuf8<40> iMessage;
    TFontSpec iFontSpec;
    TFontUnderline iFontUnderline;
    TFontStrikethrough iFontStrikethrough;
    CFbsFont* iFont;
    TBool iDragsEnabled;
    };
    
    
    
class CTrivialWindow : public CCoeControl
    {
public:
    void ConstructL(const TPoint& aPoint,const TSize& aSize);
private:
    void Draw(const TRect& aRect) const;
    };



class CTestMenu1AppUi : public CTestCoeAppUi, public MCoeMessageObserver, public MTestMenu1MenuObserver
    {
public:
	CTestMenu1AppUi(CTmsTestStep* aStep);
    ~CTestMenu1AppUi();
    void ConstructL();
private: // from MTestMenu1MenuObserver
    void MenuSelectionMadeL(TMenuCommand aSelection);
private: // from CCoeAppUi
	void HandleApplicationSpecificEventL(TInt aType,const TWsEvent& aEvent);
private: // from MCoeMessageObserver
	MCoeMessageObserver::TMessageResponse HandleMessageL(TUint32 aClientHandleOfTargetWindowGroup, TUid aMessageUid, const TDesC8& aMessageParameters);
private: // new functions
    void AddWindowL();
    void RemoveWindow();
	void TestColorOverridesL();
	void TestPlaySoundL();
	void DoTestSoundsL();
	void Wait();
	static TInt TimerCallBack(TAny* aSelf);
    void DoAddWindowL(CTrivialWindow* aWindow,const TPoint& aPoint,const TSize& aSize);
	void RunTestStepL(TInt aNextStep);
private:
    CArrayFixFlat<CTrivialWindow*>* iWindows;
	CPeriodic* iTimer;
public:    
    CMenu1MessageControl* iMessageControl;
    CTestMenu1*		iMenu;
	};

_LIT(KTMenu1Step,"TMenu1");

#endif


