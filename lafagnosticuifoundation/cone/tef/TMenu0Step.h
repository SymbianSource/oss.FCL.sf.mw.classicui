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

#if !defined(__TMENU0STEP_H__)
#define __TMENU0STEP_H__

#include <e32keys.h>
#include <basched.h>

#include <coeaui.h>
#include <coemain.h>
#include <coecntrl.h>
#include <test/testexecutestepbase.h>
#include "TMenuTestServer.h"
#include "appfwk_test_AppUi.h"
#include "TMENUASI.H"



class MTestMenuObserver
	{
public:
	virtual void MenuSelectionMadeL(TInt aSelection)=0;
	};



class CTestMenu : public CCoeControl
	{
public:
    inline CTestMenu(MTestMenuObserver* aObserver) { iObserver=aObserver; }
private: // framework
    TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
private:
    MTestMenuObserver* iObserver;
    };



class CMessageControl : public CCoeControl
    {
public:
    ~CMessageControl();
    void ConstructL();
    void ToggleFontStyleL(TMessageControlFontStyle aStyleElement);
    void SetMessage(const TDesC& aMessage);
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
    TBuf<40> iMessage;
    TFontSpec iFontSpec;
    TFontUnderline iFontUnderline;
    TFontStrikethrough iFontStrikethrough;
    CFbsFont* iFont;
    };



class CTestMenu0AppUi : public CTestCoeAppUi, public MTestMenuObserver
    {
public:
	CTestMenu0AppUi(CTmsTestStep* aStep);
    ~CTestMenu0AppUi();
    void ConstructL();
private: // from MTestMenuObserver
    void MenuSelectionMadeL(TInt aSelection);
private: // from CCoeAppUi
	void HandleApplicationSpecificEventL(TInt aType,const TWsEvent& aEvent);
private: // new functions
    void ToggleBoldL();
    void ToggleUnderlineL();
    void ToggleItalicL();
    void ToggleStrikethroughL();
	void SendAsiMessageL(TMenuAsiEventSend aEvent);
	void SendMessageL(const TDesC8& aTextMsg);
	void RunTestStepL(TInt aNextStep);
private:
    CMessageControl* iMessageControl;
    CTestMenu* iMenu;
    };
    
    

class CTMenu0Step : public CTmsTestStep
	{
public:
	CTMenu0Step();
	~CTMenu0Step();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CCoeEnv* aCoe);
private:
	};

_LIT(KTMenu0Step,"TMenu0");

#endif


