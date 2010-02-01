// Copyright (c) 2008-2009 Nokia Corporation and/or its subsidiary(-ies).
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


#if !defined(__TCONETransparency_H__)
#define __TCONETransparency_H__

#include <coecntrl.h>
#include <coeccntx.h>
#include <gulgcmap.h>
#include "TConeTestServer.h"
#include "appfwk_test_AppUi.h"


/** Base control drawing class, with semi-transparent ellipse draw implementation.
	@test
*/
class CTransparentControl : public CCoeControl
{
	friend class CTransparencyParentControl;
	void Draw(const TRect& aRect) const;
};


/** Window owning parent control, which also acts as background, contains a window owning 
 *  child controls for manipulation
	@test
*/
class CTransparencyParentControl : public CTransparentControl, public MCoeControlBackground
{
public:
	
	CTransparencyParentControl():iBackgroundDrawnCount(0)
	{};
	~CTransparencyParentControl();
	void ConstructL(TBool aEnableTransparencyProperly);
	TInt BgDrawnCount() {return iBackgroundDrawnCount;}
	//MCoeControlBackground
	void Draw(CWindowGc &aGc, const CCoeControl &aControl, const TRect &aRect) const;

private:
	CTransparentControl *iControl;
	mutable TInt iBackgroundDrawnCount;
	
};

/** Test step class
	@test
*/
class CTConeTransparencyStep : public CTmsTestStep
	{
public:
	CTConeTransparencyStep();
	~CTConeTransparencyStep();
	virtual TVerdict doTestStepL();
	void ConstructAppL(CCoeEnv* aCoe);

private:
	};
	

class CTConeTransparencyAppUi : public CTestCoeAppUi
    {
    
public:
	CTConeTransparencyAppUi(CTmsTestStep* aStep);
	~CTConeTransparencyAppUi();
	void ConstructL();
private: // from CCoeAppUi
    TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
    
private: // utility
	void RunTestStepL(TInt aStepNum);
protected:
	CTransparencyParentControl* iViewControl1;			//The main application control
	CTransparencyParentControl* iViewControl2;
    };

_LIT(KTConeTransparencyStep,"TConeTransparency");

#endif


