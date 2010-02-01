// Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
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
// Acts as a very simple run-time colour scheme changer application.\n 
// 
//

/**
 @file
 @test
 @internalComponent - Internal Symbian test code
*/

#ifndef		__TCOLSCM_H
#define		__TCOLSCM_H

#include "appfwk_test_AppUi.h"

_LIT(KTestColscmStep, "TColscm");


//!*****************************  CColorSchemeDlg. 
/**
 Dialog for the colour scheme control.
*/
class CColorSchemeDlg : public CEikDialog
    {
	public:
	    CColorSchemeDlg(TInt& aChoice);
		~CColorSchemeDlg() {};
	private: // from CEikDialog
	    TBool OkToExitL(TInt aKeycode);
		void PreLayoutDynInitL();
		TInt& iChoice;
    };


class CColorSchemeControl;

//!*****************************  A CTColorSchemeAppUi test class. 
/**
 The class performs tests to change colour scheme.
*/
class CTColorSchemeAppUi : public CTestAppUi
    {
	public:
		CTColorSchemeAppUi(CTmsTestStep* aStep);
	    void ConstructL();
	    ~CTColorSchemeAppUi();
		void RunTestStepL(TInt aNextStep);

	private: // from CEikAppUi
	    void HandleCommandL(TInt aCommand);

	private: // new functions
		void StorePrefsL();
		void HandleColorChangesL();
		void ToggleStatusPane();
		void ReadCustomColorResourceL();

	private:
		TInt iResId;
		TInt iChoice;
		CColorSchemeControl* iColorSchemeControl;
    };



//!*****************************  CColorSchemeControl. 
/**
 The class represents colour scheme control on which tests are performed.
*/
class CColorSchemeControl : public CCoeControl
    {
	public:
	    void ConstructL(const TRect& aRect);
		~CColorSchemeControl();

	private: // framework
		void Draw(const TRect& aRect) const;
		TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	private: //new 
		void InitNameArrayL();
	private:
		CDesCArrayFlat* iLogicalNames;
    };



//!*****************************  CBlankerWin. 
/**
 Empty Control
*/
class CBlankerWin : public CCoeControl
    {
	public:
	    void ConstructL();
	private:
		void Draw(const TRect& aRect) const;
    };

//!*****************************  A CTestColscmStep test class. 
/**
 The class creates & sets the application's user interface object.
*/
class CTestColscmStep : public CTmsTestStep
	{
	public:
		CTestColscmStep();
		~CTestColscmStep();

		virtual TVerdict doTestStepL();
		void ConstructAppL(CEikonEnv* aCoe);
	};


#endif


