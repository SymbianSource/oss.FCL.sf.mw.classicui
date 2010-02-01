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
// Test colour overriding.\n
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/

#if (!defined __TCOLOVR_STEP_H__)
#define __TCOLOVR_STEP_H__

#include <eikenv.h>
#include <techview/eikdialg.h>
#include <eikappui.h>
#include <eikapp.h>
#include <eikdoc.h>
#include <eikdebug.h>
#include <techview/eikchlst.h>
#include <eikrutil.h>
#include <eikpanic.h>
#include <eiksvdef.h>
#include <techview/eiklabel.h>
#include <techview/eikcmbut.h>
#include <techview/eikmenub.h>
#include <techview/eiktbar.h>
#include <techview/eikchlst.h>
#include <techview/eikchkbx.h>
#include <techview/eikopbut.h>
#include <techview/eikmfne.h>
#include <techview/eikcmbox.h>
#include <techview/eikseced.h>
#include <techview/eikprogi.h>
#include <techview/eikclock.h>
#include <techview/eikconso.h> 
#include <techview/eikcapc.h> 
#include <eikspane.h>

#include <test/testexecutestepbase.h>
#include "appfwk_test_AppUi.h"

//!  A CTColOvrStep test class. 
/**
 Test colour overriding.
*/
class CTColOvrStep : public CTmsTestStep
	{
public:
	CTColOvrStep();
	~CTColOvrStep();
	virtual TVerdict doTestStepPreambleL();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CEikonEnv* aEikEnv);
private:
	};

//!  CStandaloneLabel
/**
 Label control
*/
class CStandaloneLabel : public CEikLabel
    {
public:
	CStandaloneLabel();
public: // from CCoeControl
	void GetColorUseListL (CArrayFix<TCoeColorUse>& aColorUseList) const ;
	void Draw(const TRect& aRect) const ;
	};

//!  CColorOverrideControl
/**
 Control on which all tests are carried out.
*/
class CColorOverrideControl : public CCoeControl, public MEikMenuObserver
    {
public:
	CColorOverrideControl();
    void ConstructL(const TRect& aRect);
	~CColorOverrideControl();
	virtual TInt CountComponentControls() const;
	virtual CCoeControl* ComponentControl(TInt aIndex) const;
	void UserOverrideForeAndBackColorsL(TRgb aForeColor, TRgb aBackColor);
	void SetSystemColorsL();
	void Dim();
	void ToggleFloatingMenuL();
private: // from CCoeControl
	void Draw(const TRect& aRect) const;
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
private: // from MEikMenuObserver
	void SetEmphasis(CCoeControl* aMenuControl,TBool aEmphasis);
	void ProcessCommandL(TInt aCommandId);
private:
	void DrawColorBlocks(CCoeControl& aControl, TInt aXPos, TInt aYPos, CWindowGc& aGc ) const;
	void SetBackgroundColorL(CCoeControl& aControl, TRgb aRgb);
	void SetForegroundColorL(CCoeControl& aControl, TRgb aRgb);
private:
	CStandaloneLabel* iOverrideLabel;
	CEikTextListBox* iListBox;
	CEikTextButton* iButton;
	CEikScrollBar* iScrollBar;
	CEikEdwin* iEdwin;
	CEikChoiceList* iChoiceList;
	CEikCaptionedControl* iCaptionedCheckBox;
	CEikOptionButton* iOpBut[3];
    TEikButtonCoordinator* iBCoord;
	CEikNumberEditor* iNumberEditor;
	CEikComboBox* iComboBox;
	CEikMenuBar* iMenuBar;
	CEikSecretEditor* iSecretEditor;
	CEikProgressInfo* iProgressInfo;
	CEikClock* iClock;
	CEikConsoleControl*	iConsole;
	CEikMenuPane* iMenu; 

	CCoeBrushAndPenContext* iBrushAndPenContext;
	TPtrC iPtr;
	TRect iMenuBarRect;
    };

//!  CColorOverrideAppUi
/**
 Test Ui class.
*/
class CColorOverrideAppUi : public CTestAppUi
    {
public:
	CColorOverrideAppUi(CTmsTestStep* aStep);
    void ConstructL();
    ~CColorOverrideAppUi();
protected: //from CTestAppUi
 	virtual void RunTestStepL(TInt aNumStep);
private: // framework
    void HandleCommandL(TInt aCommand);
private:
	CColorOverrideControl* iColorSchemeControl;
	CEikButtonGroupContainer		*iToolBar;
    };


_LIT(KTColOvrStep,"TColOvr");
#endif


