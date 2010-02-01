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
// t_gfxtranseffect.cpp
// Test code for defect INC109405: Problem with sequential Gfxtranseffect registrations. 
// 
//

/**
 @file 
 @test
 @internalComponent - Internal Symbian test code
*/

#ifndef __T_GFXTRANSEFFECT_H
#define __T_GFXTRANSEFFECT_H

#include "appfwk_test_AppUi.h"

_LIT(KTestGfxTransEffect, "T_GfxTransEffect");


/**
Test step class
*/
class CTestGfxTransEffect : public CTmsTestStep
	{
public:
	CTestGfxTransEffect();
	~CTestGfxTransEffect();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CEikonEnv* aCoe);
private:
	};

/**
A simple control on which all tests are carried out.
*/
class CSimpleGfxTransControl : public CCoeControl
    {
public:
    void ConstructL();
	~CSimpleGfxTransControl();
private: // framework
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	};

/**
UI class to CTestGfxTransEffect test step class.
*/
class CSimpleGfxTransAppUi : public CTestCoeAppUi
    {
public:
	CSimpleGfxTransAppUi(CTmsTestStep* aStep) : CTestCoeAppUi(aStep) {}
    void ConstructL();
	~CSimpleGfxTransAppUi();
private:
 	virtual void RunTestStepL(TInt aNextStep); 
   };

#endif //__T_GFXTRANSEFFECT_H


