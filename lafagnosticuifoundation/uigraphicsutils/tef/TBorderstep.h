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

#if (!defined __TBORDER_STEP_H__)
#define __TBORDER_STEP_H__
#include <test/testexecutestepbase.h>
#include "TEgulTestServer.h"
#include <coecntrl.h>
#include <gulbordr.h>
#include "appfwk_test_AppUi.h"

const TInt KMaxBufLength = 40;

class CTBorderStep : public CTmsTestStep
	{
public:
	CTBorderStep();
	~CTBorderStep();
//	virtual TVerdict doTestStepPreambleL();
//	virtual TVerdict doTestStepPostambleL();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CCoeEnv* aCoeEnv);

private:
	};


class CSimpleControl : public CCoeControl
    {
public:
    void ConstructL();
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
private: // framework
	void Draw(const TRect& aRect) const;
	void DrawBorder(CWindowGc& aGC, TRgb aColor, TGulBorder::TBorderType aBorderType, TInt aYPos, TInt aYTextPos, const TDesC &aBorderName) const;
private: // new function
	void DrawText() const;
private:
	TBuf<KMaxBufLength> iBuf1;
	TBuf<KMaxBufLength> iBuf2;
	TRect iRect;
	CGraphicsContext::TTextAlign iAlign;
    };

class CTestBorderUi  : public CTestCoeAppUi
	{
public:
	void ConstructL();
	CTestBorderUi(CTmsTestStep* aStep);
	virtual ~CTestBorderUi();
protected:
	CSimpleControl* iControl;
protected:
	virtual void RunTestStepL(TInt aStep);
	};

_LIT(KTBorderStep,"TBorder");
#endif


